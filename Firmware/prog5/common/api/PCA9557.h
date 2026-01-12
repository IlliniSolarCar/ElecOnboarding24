/**
 * PCA9557.h
 *
 *  Created on: November 6, 2015
 *
 *  Class for manipulating the PCA9557 IO expander over I2C
 *  Adapted from the PCA9555 class by Devan Lai and Derek Chou
 */

#ifndef COMMON_API_PCA9557_H_
#define COMMON_API_PCA9557_H_

#include <mbed.h>
#include <stdint.h>

class PCA9557 {
public:
    typedef int DeviceAddress;

    /** Create a PCA9557 slave device interface
     *
     *  @param i2c I2C master interface
     *  @param slaveAddr 7-bit I2C slave device address
     */
    PCA9557(I2C& i2c, DeviceAddress slaveAddr);

    /** Set the input/output direction for the 8 IO pins
     *
     *  A high bit indicates that the output pin is an input
     *
     *  @param selectedInputBits mask of IO pins that are inputs
     *
     *  @returns
     *    true if direction set successfully, false otherwise
     */
    bool setDirection(uint8_t selectedInputBits);

    /** Set the input polarity for the 8 IO pins
     *
     *  A high bit indicates that the input is active low
     *  The remaining 8 IO pins are configured as active high
     *
     *  @param invertedInputBits mask of input pins that are active-low
     *
     *  @returns
     *    true if polarity set successfully, false otherwise
     */
    bool setInputPolarity(uint8_t invertedInputBits);

    /** Read the logic level for the 8 IO pins
     *
     *  A high bit indicates that the IO pin is logic high, as dictated
     *  by the polarity.
     *
     *  @param outputHighBits mask of IO pins that are logic high, returned
     *                            by reference
     *  @returns
     *    true if IO state read successfully, false otherwise
     *    mask of IO pins that are logic high, returned via &inputLogicHighBits
     */
    bool readOutputs(uint8_t& outputHighBits);

    /** Set the output state for the 8 IO pins
     *
     *  A high bit indicates that the output is on
     *  The remaining IO pins are left unchanged
     *
     *  @param outputHighBits mask of output pins that are on
     */
    bool writeOutputs(uint8_t outputHighBits);

    /** Read the logic level for the 8 IO pins
     *
     *  A high bit indicates that the IO pin is logic high, as dictated
     *  by the polarity.
     *
     *  @param inputLogicHighBits mask of IO pins that are logic high, returned
     *                            by reference
     *  @returns
     *    true if IO state read successfully, false otherwise
     *    mask of IO pins that are logic high, returned via &inputLogicHighBits
     */
    bool readInputs(uint8_t& inputLogicHighBits);

protected:
    enum MemoryAddress {
        INPUT = 0b00,
        OUTPUT = 0b01,
        POLARITY = 0b10,
        CONFIG = 0b11
    };

    /** Read a single 8-bit register
     *
     *  @param regAddr register address to read from
     *  @param success status of the operation, returned by reference
     *
     *  @returns
     *    the byte-value of the register
     *    true if successful, false if failed (via &success)
     */
    uint8_t readRegister8(MemoryAddress regAddr, bool& success);

    /** Write a byte to a device register
     *
     *  @param regAddr register address to write to
     *  @param regValue value to write
     *
     *  @returns
     *    true if successful, false if failed
     */
    bool writeRegister8(MemoryAddress address, uint8_t value);

private:
    I2C& i2c;
    const DeviceAddress slaveAddr;
};

inline bool PCA9557::setDirection(uint8_t selectedInputBits) {
    return writeRegister8(CONFIG, selectedInputBits);
}


inline bool PCA9557::setInputPolarity(uint8_t invertedInputBits) {
    return writeRegister8(POLARITY, invertedInputBits);
}

inline bool PCA9557::readOutputs(uint8_t& outputHighBits) {
    bool success = false;
    outputHighBits = readRegister8(OUTPUT, success);

    if (!success) {
        outputHighBits = 0xFF;
    }

    return success;
}

inline bool PCA9557::writeOutputs(uint8_t outputHighBits) {
    return writeRegister8(OUTPUT, outputHighBits);
}

inline bool PCA9557::readInputs(uint8_t& inputLogicHighBits) {
    bool success = false;
    inputLogicHighBits = readRegister8(INPUT, success);

    if (!success) {
        inputLogicHighBits = 0xFF;
    }

    return success;
}

#endif /* __PCA9557_H__ */
