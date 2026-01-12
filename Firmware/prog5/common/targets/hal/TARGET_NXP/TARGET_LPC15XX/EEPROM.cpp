#include <EEPROM.h>

void EEPROM::init() {
    LPC_SYSCON->PDRUNCFG &= ~(1 << 6);
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 9);
}

void EEPROM::write(uint32_t address, uint8_t *data, uint32_t bytes) {
    unsigned int command_param[5];
    unsigned int status_result[5];

    command_param[0] = IAP::COMMAND_WRITE_EEPROM;
    command_param[1] = address;
    command_param[2] = (uint32_t)data;
    command_param[3] = bytes;
    command_param[4] = SystemCoreClock / 1000;

    IAP::iap_entry(command_param, status_result);
}

void EEPROM::read(uint32_t address, uint8_t *data, uint32_t bytes) {
    unsigned int command_param[5];
    unsigned int status_result[5];

    command_param[0] = IAP::COMMAND_READ_EEPROM;
    command_param[1] = address;
    command_param[2] = (uint32_t)data;
    command_param[3] = bytes;
    command_param[4] = SystemCoreClock / 1000;

    IAP::iap_entry(command_param, status_result);
}
