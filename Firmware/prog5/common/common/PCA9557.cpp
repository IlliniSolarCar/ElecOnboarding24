/**
 * PCA9557.cpp
 *
 *  Created on: November 6, 2015
 *
 *  Adapted from the PCA9555 class by Devan Lai and Derek Chou
 */

#include <PCA9557.h>

PCA9557::PCA9557(I2C& i2c, DeviceAddress slaveAddr)
    : i2c(i2c), slaveAddr(slaveAddr) {

}

uint8_t PCA9557::readRegister8(MemoryAddress regAddr, bool& success) {
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

bool PCA9557::writeRegister8(MemoryAddress regAddr, uint8_t value) {
    uint8_t data[2] = { regAddr, value };
    int status = i2c.write(slaveAddr, (const char*)data, sizeof(data));
    return status == 0;
}
