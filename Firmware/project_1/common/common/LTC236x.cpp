/**
 * LTC236x.cpp
 * For the LTC2365/66 voltage sensor chips.
 *
 */

#include <LTC236x.h>

LTC236x::LTC236x(SPI& spi, DigitalOut& CS) :
        spi(spi), CS(CS) {
    spi.format(16, 3);
    spi.frequency(1000000);
}

/**
 * Requests a conversion from the LTC2365/66, and returns
 * the 12-bit result.
 */
bool LTC236x::requestConversion(uint16_t& data) {
    bool success = false;

    spi.format(16, 3);

    CS = 0;
    wait_us(2);
    uint16_t input = (uint16_t) (spi.write(0x00));

    CS = 1;

    data = (input >> 3);

    return success;
}

