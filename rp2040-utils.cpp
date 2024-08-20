#include "pxt.h"
#include "hardware/vreg.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "stdlib.h"

static void set_sys_clock_pll(uint32_t vco_freq, uint post_div1, uint post_div2) {
    if (!running_on_fpga()) {
        clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);

        pll_init(pll_sys, 1, vco_freq, post_div1, post_div2);
        uint32_t freq = vco_freq / (post_div1 * post_div2);

        // Configure clocks
        // CLK_REF = XOSC (12MHz) / 1 = 12MHz
        clock_configure(clk_ref,
                        CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC,
                        0, // No aux mux
                        12 * MHZ,
                        12 * MHZ);

        // CLK SYS = PLL SYS (125MHz) / 1 = 125MHz
        clock_configure(clk_sys,
                        CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                        CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
                        freq, freq);

        clock_configure(clk_peri,
                        0, // Only AUX mux on ADC
                        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                        48 * MHZ,
                        48 * MHZ);
    }
}

static bool check_sys_clock_khz(uint32_t freq_khz, uint *vco_out, uint *postdiv1_out, uint *postdiv_out) {
    uint crystal_freq_khz = clock_get_hz(clk_ref) / 1000;
    for (uint fbdiv = 320; fbdiv >= 16; fbdiv--) {
        uint vco = fbdiv * crystal_freq_khz;
        if (vco < 400000 || vco > 1600000) continue;
        for (uint postdiv1 = 7; postdiv1 >= 1; postdiv1--) {
            for (uint postdiv2 = postdiv1; postdiv2 >= 1; postdiv2--) {
                uint out = vco / (postdiv1 * postdiv2);
                if (out == freq_khz && !(vco % (postdiv1 * postdiv2))) {
                    *vco_out = vco * 1000;
                    *postdiv1_out = postdiv1;
                    *postdiv_out = postdiv2;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool set_sys_clock_khz(uint32_t freq_khz) {
    unsigned int vco, postdiv1, postdiv2;
    if (check_sys_clock_khz(freq_khz, &vco, &postdiv1, &postdiv2))
    {
        set_sys_clock_pll(vco, postdiv1, postdiv2);
        return true;
    }
    return false;
}

//% color=#1a3300 weight=99 icon="\uf1e6" block="RP2040 Utils
namespace rp2040utils {

    int last_frequency = 0;

    //%
    int getClockFrequency()
    {
        return last_frequency;
    }

    //%
    int setClockFrequency(int frequency_khz)
    {
        vreg_set_voltage(VREG_VOLTAGE_MAX);
        if (set_sys_clock_khz(frequency_khz))
        {
            last_frequency = frequency_khz;
            return 1;
        }

        return 0;
    }

    //%
    int isValidClockFrequency(int frequency_khz)
    {
        unsigned int vco, postdiv1, postdiv2;
        if (check_sys_clock_khz(frequency_khz, &vco, &postdiv1, &postdiv2))
            return 1;
       
        return 0;
    }

    REAL_TIME_FUNC
    int _setSSIFlashSpeed(int ssi_clock_divider)
    {
        uint32_t RP2040_SSI_BASE = 0x18000000;
        uint32_t* RP2040_SSI_BAUDR = (uint32_t *) (RP2040_SSI_BASE + 0x00000014);
        uint32_t* RP2040_SSI_SSIENR = (uint32_t *) (RP2040_SSI_BASE + 0x0000008);

        *RP2040_SSI_SSIENR = 0;
        *RP2040_SSI_BAUDR = ssi_clock_divider;
        *RP2040_SSI_SSIENR = 1;

        return 1;
    }

    //%
    int setSSIFlashSpeed(int ssi_clock_divider)
    {     
        return _setSSIFlashSpeed(ssi_clock_divider);
    }


    //%
    int poke(int address, int value) {
        uint32_t *addr = (uint32_t *) address;
        *addr = (uint32_t) value;
        return 1;
    }

    //%
    int peek(int address) {
        uint32_t *addr = (uint32_t *) address;
        return (int) *addr;
    }
};
