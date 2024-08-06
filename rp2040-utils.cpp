#include "pxt.h"

/**
* share
* use
*/


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
        if (set_sys_clock_khz(frequency_khz, false))
        {
            frequency = frequency_khz;
            return 1;
        }
        
        return 0;
    }

    //%
    int isValidClockFrequency(int frequency_khz)
    {
        uint vco, postdiv1, postdiv2;
        if (check_sys_clock_khz(freq_khz, &vco, &postdiv1, &postdiv2))
            return 1;

        return 0;
    }
};