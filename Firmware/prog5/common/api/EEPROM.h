#ifndef COMMON_API_EEPROM_H_
#define COMMON_API_EEPROM_H_

#include <mbed.h>
#include <IAP.h>


namespace EEPROM {

    void init();

    void write(uint32_t address, uint8_t *data, uint32_t bytes);
    void read(uint32_t address, uint8_t *data, uint32_t bytes);

}

#endif
