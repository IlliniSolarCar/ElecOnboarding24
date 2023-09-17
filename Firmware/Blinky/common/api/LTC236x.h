/**
 * LTC236x.h
 * For the LTC2365/66 voltage sensor chips.
 *
 */

#ifndef COMMON_API_LTC236X_H_
#define COMMON_API_LTC236X_H_

#include <mbed.h>

class LTC236x {
public:
    LTC236x(SPI& spi, DigitalOut& CS);

    bool requestConversion(uint16_t& data);

private:
    SPI& spi;
    DigitalOut& CS;
};

#endif /* __LTC236x_H__ */
