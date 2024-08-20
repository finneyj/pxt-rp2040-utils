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

    /**
     * Sets the QSPI FLASH clock frequency divider of the rp2040
     * @param frequency the requested frequency of the CPU in kHz
     */
    //% shim=rp2040utils::setSSIFlashSpeed
    export function setSSIFlashSpeed(ssi_clock_divider:number): number {
        return 1;
    }

    /**
     * Writes a given 32 bit value to a given memory location
     * @param address The 32 bit memory address to write
     * @param value The 32 bit value to write
     */
    //% shim=rp2040utils::poke
    export function poke(address:number, value:number): number {
        return 1;
    }

     /**
     * reads a 32 bit value from a given memory location
     * @param address The 32 bit memory address to read
     */
    //% shim=rp2040utils::peek
    export function peek(address:number): number {
        return 1;
    }

}