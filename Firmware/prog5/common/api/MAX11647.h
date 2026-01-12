/*
 * MAX11647.h
 * Header file for MAX11647 10-bit 2ch ADC.
 *
 * Created on: June 12, 2015
 * Author: Derek Chou
 *
 */

#ifndef COMMON_API_MAX11647_H_
#define COMMON_API_MAX11647_H_

#include <mbed.h>


class MAX11647 {
public:
    typedef int DeviceAddress;
    /*
     * According to the datasheet:
     * In internal clock mode: the MAX11646/MAX11647 contain two 10-bit blocks of memory.
     * This should be 2.
     * In external clock mode: we can continuously request samples without problem.
     * Tested up to 1024.
     */

    enum Channel {
        Ain0 = 0b0,
        Ain1 = 0b1
    };

    /**
     * Get the number of continuous reads to perform at once.
     * @return Number of readings to perform.
     */
    inline int numReadings() const {
        return numReads;
    }

    MAX11647(I2C& i2c, DeviceAddress slaveAddr);

    /**
     * Reads an ADC channel.
     * @param Channel The channel to scan
     * @param data 10-bit reading for analog channel
     */
    void readChannel(Channel channel, uint16_t& data);

    /**
     * Reads the differential of Ain1 - Ain0.
     * @param data Output with space for I2C_NUM_READS readings.
     */
    void readDifferential(int16_t* data);

    /**
     * Setup configuration of ADC.
     * @param frequency I2C frequency to use.
     * @param numReads Number of continuous reads to perform at once.
     * @param differential True to read differential (see readDifferential())
     *        false otherwise.
     * @param bipolar True to support both positive and negative voltages;
     *        false otherwise (positive only; negative voltages clipped to 0).
     */
    void configure(int frequency, int numReads, bool differential, bool bipolar);

protected:

private:

    I2C& i2c;
    const DeviceAddress slaveAddr;

    int numReads = 256;

    /**
     * Setup Byte
     * 7 REG Register bit. 1 = setup byte, 0 = configuration byte.
     * 6 SEL2
     * 5 SEL1
     * 4 SEL0
     * 3 CLK 1 = external clock, 0 = internal clock. Defaulted to 0 at power-up.
     * 2 BIP/UNI 1 = bipolar, 0 = unipolar. Defaulted to 0 at power-up (see the Unipolar/Bipolar section).
     * 1 RST 1 = no action, 0 = resets the configuration register to default. Setup register remains unchanged.
     * 0 X Don’t-care bit. This bit can be set to 1 or 0.
     *
     * Three bits select the reference voltage. Default to 000 at power-up.
     * SEL2 SEL1 SEL0   REFERENCE VOLTAGE       REF                 INTERNAL REFERENCE STATE
     * 0    0    X      VDD                     Not connected       Always off
     * 0    1    X      External reference      Reference input     Always off
     * 1    0    0      Internal reference      Not connected*      Always off
     * 1    0    1      Internal reference      Not connected*      Always on
     * 1    1    0      Internal reference      Reference output    Always off
     * 1    1    1      Internal reference      Reference output    Always on
     *
     * Configuration byte
     * 7 REG Register bit. 1= setup byte (see Table 1), 0 = configuration byte.
     * 6 SCAN1
     * 5 SCAN0 Scan-select bits. Two bits select the scanning configuration. Defaults to 00 at power-up.
     * 4 X
     * 3 X
     * 2 X
     * 1 CS0 Channel-select bit. CS0 selects which analog input channels are to be used for conversion.
     * Defaults to 0000 at power-up.
     * 0 SGL/DIF 1 = single-ended, 0 = differential. Defaults to 1 at power-up.
     * SCAN1    SCAN0   SCANNING CONFIGURATION
     * 0        0       Scans up from AIN0 to the input selected by CS0.
     * 0        1       Converts the input selected by CS0 eight times (see Tables 3 and 4).*
     * 1        0       Reserved. Do not use.
     * 1        1       Converts input selected by CS0.*
     */

    /** Various constants for making the configuration and setup bytes. */
    const uint8_t SETUP = (1 << 7);
    const uint8_t CONFIG = (0 << 7);
    const uint8_t EXT_REF = (0b010 << 4);
    const uint8_t EXTERNAL_CLOCK = (1 << 3);
    const uint8_t BIPOLAR = (1 << 2);
    const uint8_t SCAN_SELECTED = (0b11 << 5);
    const uint8_t SCAN_EIGHT_TIMES = (0b01 << 5);
    const uint8_t CS_SHIFT = 0b1;
    const uint8_t SGL = 0b1;
};

#endif /* __MAX11647_H__ */
