#include "pxt.h"

//void set_sys_clock_pll(uint32_t vco_freq, uint post_div1, uint post_div2);
//bool check_sys_clock_khz(uint32_t freq_khz, uint *vco_freq_out, uint *post_div1_out, uint *post_div2_out);
/**
* share
* use
*/

/*
static inline bool set_sys_clock_khz(uint32_t freq_khz, bool required) {
    uint vco, postdiv1, postdiv2;
    if (check_sys_clock_khz(freq_khz, &vco, &postdiv1, &postdiv2)) {
        set_sys_clock_pll(vco, postdiv1, postdiv2);
        return true;
    } else if (required) {
        panic("System clock of %u kHz cannot be exactly achieved", freq_khz);
    }
    return false;
}
*/

//% color=#1a3300 weight=99 icon="\uf1e6" block="RP2040 Utils
namespace rp2040utils {

    //int last_frequency = 0;

    //%
    int getClockFrequency()
    {
        return 10;
    }

    //%
    int setClockFrequency(int frequency_khz)
    {
        /*
        vreg_set_voltage(VREG_VOLTAGE_MAX);
        if (set_sys_clock_khz(frequency_khz, false))
        {
            frequency = frequency_khz;
            return 1;
        }
        */
        return 11;
    }

    //%
    int isValidClockFrequency(int frequency_khz)
    {
        /*
        uint vco, postdiv1, postdiv2;
        if (check_sys_clock_khz(freq_khz, &vco, &postdiv1, &postdiv2))
            return 1;
        */
        return 12;
    }
};