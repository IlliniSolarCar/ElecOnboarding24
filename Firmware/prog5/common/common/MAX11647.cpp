/**
 * MAX11647.cpp
 * Implementation for MAX11647 10-bit 2ch ADC chip.
 *
 * Created on: June 12, 2015
 * Author: Derek Chou
 *
 */

#include <MAX11647.h>

MAX11647::MAX11647(I2C& i2c, DeviceAddress slaveAddr) :
        i2c(i2c), slaveAddr(slaveAddr) {

}

void MAX11647::configure(int frequency, int numReads, bool differential, bool bipolar) {
    i2c.frequency(frequency);

    char toSend[1];
    // sets external ADC ref, in the setup register
    toSend[0] = SETUP | EXTERNAL_CLOCK | EXT_REF | (bipolar ? BIPOLAR : 0);
    i2c.write(slaveAddr, toSend, 1, false);

    if(differential) {
        // Configure differential mode (Ain1/vout - Ain0/vref)
        // Scan eight times continuously in one I2C session.
        toSend[0] = CONFIG | (CS_SHIFT << 1) | SCAN_EIGHT_TIMES;
        i2c.write(slaveAddr, toSend, 1, false);
    }
}

void MAX11647::readChannel(Channel channel, uint16_t& data) {

    char toSend[1];

    toSend[0] = CONFIG | SCAN_SELECTED | (channel << CS_SHIFT) | SGL;
    i2c.write(slaveAddr, toSend, 1, false);

    char toReceive[2];
    i2c.read(slaveAddr, toReceive, 2, false);

    int toReturn = ((toReceive[0] << 8) | toReceive[1]) & 0x03ff;
    data = toReturn;
}

void MAX11647::readDifferential(int16_t* data) {
    // Read extra samples and discard during conversion.
    const int NUM_EXTRA_SAMPLES = 0;

    char toReceive[(numReadings()+NUM_EXTRA_SAMPLES)*2];
    i2c.read(slaveAddr, toReceive, (numReadings()+NUM_EXTRA_SAMPLES)*2 /* 2 bytes * # samples */, false);

    for(int i = 0; i < numReadings(); i++) {
        uint16_t left = ((uint16_t)toReceive[2*(i+NUM_EXTRA_SAMPLES)]);
        uint16_t right = ((uint16_t)toReceive[2*(i+NUM_EXTRA_SAMPLES) + 1]);
        uint16_t unsigned_num = (((left & 0b11) << 8) | right);
        // Preserve sign by moving the number to the left, then sign-extended right shift.
        int16_t s = (int16_t)(unsigned_num << 6);
        s = s >> 6;
        *(data+i) = s;
    }
}
