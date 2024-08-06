#include "pxt.h"

/**
* share
* use
*/


//% color=#1a3300 weight=99 icon="\uf1e6" block="RP2040 Utils
namespace rp2040utils {

    //%
    int getClockFrequency()
    {
        return 1;
    }

    //%
    int setClockFrequency(int frequency_khz)
    {
        return 2;
    }

    //%
    int isValidClockFrequency(int frequency_khz)
    {
        return 3;
    }
};