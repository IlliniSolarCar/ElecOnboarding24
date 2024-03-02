/**
 * PCA9555.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: Devan
 *  Adapted for EE192
 *      Derek Chou, March 2015
 */

#include <PCA9555.h>

PCA9555::PCA9555(I2C& i2c, DeviceAddress slaveAddr)
    : i2c(i2c), slaveAddr(slaveAddr) {

}

uint8_t PCA9555::readRegister8(MemoryAddress regAddr, bool& success) {
    success = false;

    uint8_t data[1] = { regAddr };
    int status = i2c.write(slaveAddr, (const char*)data, sizeof(data), true);
    if (status == 0) {
        status = i2c.read(slaveAddr, (char*)data, sizeof(data));
        success = (status == 0);
        return data[0];
    }

    return 0;
}

uint16_t PCA9555::readRegister16(MemoryAddress regAddr, bool& success) {
    success = false;

    uint8_t data[2] = { regAddr, 0 };
    int status = i2c.write(slaveAddr, (const char*)data, 1, true);
    if (status == 0) {
        status = i2c.read(slaveAddr, (char*)data, sizeof(data));
        success = (status == 0);
        return ((uint16_t)(data[1]) << 8) | (uint16_t)(data[0]);
    }

    return 0;
}

bool PCA9555::writeRegister8(MemoryAddress regAddr, uint8_t value) {
    uint8_t data[2] = { regAddr, value };
    int status = i2c.write(slaveAddr, (const char*)data, sizeof(data));
    return status == 0;
}

bool PCA9555::writeRegister16(MemoryAddress regAddr, uint16_t value) {
    uint8_t data[3] = { regAddr, (uint8_t)(value & 0xFF), (uint8_t)(value >> 8) };
    int status = i2c.write(slaveAddr, (const char*)data, sizeof(data));
    return status == 0;
}
