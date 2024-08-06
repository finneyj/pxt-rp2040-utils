// Extension to provide access to low level C/C++ RP2040 functions in MakeCode

//% color=#1a3300 weight=99 icon="\uf1e6" block="RP2040 Utils"
namespace rp2040utils {
   
    let cpu_clock = 0;      // current clock speed of the CPU

    /**
     * Sets the sampling frequency of the magnetic sensor
     * @param period the new sampling period in milliseconds
     */
    //% shim=rp2040utils::getClockFrequency
    export function getClockFrequency(): number {
        return 1;
    }

    /**
     * Sets the CPU clock frequency of the rp2040
     * @param frequency the requested frequency of the CPU in kHz
     */
    //% shim=rp2040utils::setClockFrequency
    export function setClockFrequency(frequency:number): number {
        return 1;
    }

    /**
     * Tests if the given CPU clock frequency is achievable on current harwdare
     * @param frequency the requested frequency of the CPU in kHz
     */
    //% shim=rp2040utils::isValidClockFrequency
    export function isValidClockFrequency(frequency:number): number {
        return 1;
    }
}