#ifndef COMMON_API_IAP_H_
#define COMMON_API_IAP_H_

#include <mbed.h>

/*
 * See UM Chapter 34.9 (Pg 572) IAP Commands for details
 * https://www.nxp.com/docs/en/user-guide/UM10736.pdf
 */

namespace IAP {

    const uint32_t IAP_LOCATION = 0x03000205;

    //See Table 498
    const uint8_t COMMAND_PART_ID = 54;
    const uint8_t COMMAND_UID = 58;
    const uint8_t COMMAND_WRITE_EEPROM = 61;
    const uint8_t COMMAND_READ_EEPROM = 62;

    typedef void (*IAP)(unsigned int [],unsigned int[]);

    const IAP iap_entry = (IAP) IAP_LOCATION;

    /*
     * Gets the part ID of the chip
     * @return - 0 if failed, else the xx part of LPC15xx (i.e. 49 for LPC1549)
     */
    uint8_t getPartID();

    /*
     * Gets the Unique ID of the MCU
     * @param data - uint32_t array of 4. Will have the UID on success
     * @return 0 = Success Else Fail
     */
    bool getUniqueID(uint32_t (&data)[4]);

}

#endif
