/**
 * PCA9555.h
 *
 *  Created on: Jun 19, 2014
 *      Author: Devan
 *
 *  Class for manipulating the PCA9555 IO expander over I2C
 * 
 *  Adapted for EE192
 *      Derek Chou, March 2015
 */

#ifndef COMMON_API_PCA9555_H_
#define COMMON_API_PCA9555_H_

#include <mbed.h>
#include <stdint.h>

class PCA9555 {
public:
    typedef int DeviceAddress;

    /** Create a PCA9555 slave device interface
     *
     *  @param i2c I2C master interface
     *  @param slaveAddr 7-bit I2C slave device address
     */
    PCA9555(I2C& i2c, DeviceAddress slaveAddr);

    /** Set the input/output direction for all 16 IO pins
     *
     *  A high bit indicates that the output is an input
     *
     *  @param selectedInputBits mask of IO pins that are inputs
     *
     *  @returns
     *    true if direction set successfully, false otherwise
     */
    bool setDirection16(uint16_t selectedInputBits);

    /** Set the input/output direction for the first 8 IO pins
     *
     *  A high bit indicates that the output is an input
     *  The remaining 8 IO pins are configured as inputs
     *
     *  @param selectedInputBits mask of IO pins that are inputs
     *
     *  @returns
     *    true if direction set successfully, false otherwise
     */
    bool setDirection(uint8_t selectedInputBits);

    /** Set the input polarity for any of the 16 IO pins
     *
     *  A high bit indicates that the input is active low
     *
     *  @param invertedInputBits mask of input pins that are active-low
     *
     *  @returns
     *    true if polarity set successfully, false otherwise
     */
    bool setInputPolarity16(uint16_t invertedInputBits);

    /** Set the input polarity for the first 8 IO pins
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

    /** Read the logic level for all of the 16 IO pins
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
    bool readOutputs16(uint16_t& outputHighBits);

    /** Read the logic level for the second 8 IO pins
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
    bool readOutputs1(uint8_t& outputHighBits);

    /** Read the logic level for the first 8 IO pins
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
    bool readOutputs0(uint8_t& outputHighBits);

    /** Set the output state for any of the 16 IO pins
     *
     *  A high bit indicates that the output is on
     *
     *  @param outputHighBits mask of output pins that are on
     */
    bool writeOutputs16(uint16_t outputHighBits);

    /** Set the output state for the second 8 IO pins
     *
     *  A high bit indicates that the output is on
     *  The remaining 8 IO pins are left unchanged
     *
     *  @param outputHighBits mask of output pins that are on
     */
    bool writeOutputs1(uint8_t outputHighBits);

    /** Set the output state for the first 8 IO pins
     *
     *  A high bit indicates that the output is on
     *  The remaining 8 IO pins are left unchanged
     *
     *  @param outputHighBits mask of output pins that are on
     */
    bool writeOutputs0(uint8_t outputHighBits);

    /** Read the logic level for all of the 16 IO pins
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
    bool readInputs16(uint16_t& inputLogicHighBits);

    /** Read the logic level for the first 8 IO pins
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
    bool readInputs0(uint8_t& inputLogicHighBits);

    /** Read the logic level for the last 8 IO pins
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
    bool readInputs1(uint8_t& inputLogicHighBits);

protected:
    enum MemoryAddress {
        INPUT_0 = 0,
        INPUT_1 = 1,
        OUTPUT_0 = 2,
        OUTPUT_1 = 3,
        POLARITY_0 = 4,
        POLARITY_1 = 5,
        CONFIG_0 = 6,
        CONFIG_1 = 7
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

    /** Read a pair of registers as a single 16-bit value
     *
     *  Note that the register at `regAddr` will be placed into
     *  the LSB and the paired register will be placed into the MSB
     *
     *  @param regAddr register address to read the LSB from
     *  @param success status of the operation, returned by reference
     *
     *  @returns
     *    the register values as a 16-bit integer
     *    true if successful, false if failed (via &success)
     */
    uint16_t readRegister16(MemoryAddress regAddr, bool& success);

    /** Write a byte to a device register
     *
     *  @param regAddr register address to write to
     *  @param regValue value to write
     *
     *  @returns
     *    true if successful, false if failed
     */
    bool writeRegister8(MemoryAddress address, uint8_t value);

    /** Write to a pair of device registers
     *
     *  Note that the register at `regAddr` will receive the LSB
     *  and the corresponding paired register will receive the MSB
     *
     *  @param regAddr register address to write the LSB to
     *  @param regValue value to write
     *
     *  @returns
     *    true if successful, false if failed
     */
    bool writeRegister16(MemoryAddress address, uint16_t value);

private:
    I2C& i2c;
    const DeviceAddress slaveAddr;
};

inline bool PCA9555::setDirection16(uint16_t selectedInputBits) {
    return writeRegister16(CONFIG_0, selectedInputBits);
}

inline bool PCA9555::setDirection(uint8_t selectedInputBits) {
    // Configure port 1 as inputs
    uint16_t inputBits = 0xFF00 | selectedInputBits;
    return writeRegister16(CONFIG_0, inputBits);
}

inline bool PCA9555::setInputPolarity16(uint16_t invertedInputBits) {
    return writeRegister16(POLARITY_0, invertedInputBits);
}

inline bool PCA9555::setInputPolarity(uint8_t invertedInputBits) {
    // Configure port 1 as not inverted
    return writeRegister16(POLARITY_0, (uint16_t) invertedInputBits);
}

inline bool PCA9555::readOutputs16(uint16_t& outputHighBits) {
    bool success0 = false;
    bool success1 = false;
    uint8_t in0;
    uint8_t in1;

    in0 = readRegister8(OUTPUT_0, success0);
    in1 = readRegister8(OUTPUT_1, success1);

    if (!success0 || !success1) {
        outputHighBits = 0xFFFF;
    } else {
        outputHighBits = ((in1 << 8) & 0xFF00) | (in0 & 0x00FF);
    }

    return success0 && success1;
}

inline bool PCA9555::readOutputs1(uint8_t& outputHighBits) {
    bool success = false;
    outputHighBits = readRegister8(OUTPUT_1, success);

    if (!success) {
        outputHighBits = 0xFF;
    }

    return success;
}

inline bool PCA9555::readOutputs0(uint8_t& outputHighBits) {
    bool success = false;
    outputHighBits = readRegister8(OUTPUT_0, success);

    if (!success) {
        outputHighBits = 0xFF;
    }

    return success;
}

inline bool PCA9555::writeOutputs16(uint16_t outputHighBits) {
    return writeRegister8(OUTPUT_0, outputHighBits & 0xFF)
            && writeRegister8(OUTPUT_1, (outputHighBits >> 8) & 0xFF);
}

inline bool PCA9555::writeOutputs1(uint8_t outputHighBits) {
    return writeRegister8(OUTPUT_1, outputHighBits);
}

inline bool PCA9555::writeOutputs0(uint8_t outputHighBits) {
    return writeRegister8(OUTPUT_0, outputHighBits);
}

inline bool PCA9555::readInputs16(uint16_t& inputLogicHighBits) {
    bool success = false;
    inputLogicHighBits = readRegister16(INPUT_0, success);

    if (!success) {
        inputLogicHighBits = 0xFFFF;
    }

    return success;
}

inline bool PCA9555::readInputs0(uint8_t& inputLogicHighBits) {
    bool success = false;
    inputLogicHighBits = readRegister8(INPUT_0, success);

    if (!success) {
        inputLogicHighBits = 0xFF;
    }

    return success;
}

inline bool PCA9555::readInputs1(uint8_t& inputLogicHighBits) {
    bool success = false;
    inputLogicHighBits = readRegister8(INPUT_1, success);

    if (!success) {
        inputLogicHighBits = 0xFF;
    }

    return success;
}

#endif /* __PCA9555_H__ */
