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

uint8_t MAX11647::initialize(int frequency, int numReads, bool differential, bool bipolar, bool C0) {

	numReads = numReads;
	uint8_t error = 0;

	i2c.frequency(frequency);

	char toSend[1];
	// sets external ADC ref, in the setup register
	toSend[0] = SETUP | EXT_REF | EXTERNAL_CLOCK | (bipolar ? BIPOLAR : 0);
	if (i2c.write(slaveAddr, toSend, 1, false)) {
		error = 1;
	}

	// in external clock mode, scan 8 times allows for continuous reading
	// in diff mode C0 0: Ain0 - Ain1 1: Ain1 - Ain0, single mode, 0: Ain0, 1: Ain1
	toSend[0] = CONFIG | SCAN_EIGHT_TIMES | (C0 << 1) | (differential ? DIF : SGL);
	if (i2c.write(slaveAddr, toSend, 1, false)) {
		error = 1;
	}

    return error;
}

uint8_t MAX11647::readChannel(Channel channel, uint16_t& data) {

    char toSend[1];

    toSend[0] = CONFIG | SCAN_SELECTED | (channel << CS_SHIFT) | SGL;
    if (i2c.write(slaveAddr, toSend, 1, false)) {
    	return 2;
    }

    char toReceive[2];
    if (i2c.read(slaveAddr, toReceive, 2, false) ) {
    	return 1;
    }

    int toReturn = ((toReceive[0] << 8) | toReceive[1]) & 0x03ff;
    data = toReturn;
    return 0;
}

uint8_t MAX11647::readDifferential(int16_t* data, DiffMode mode) {
	uint8_t error = 0;

	char toSend[1];

	// in diff mode C0 0: Ain0 - Ain1 1: Ain1 - Ain0
	toSend[0] = CONFIG | SCAN_EIGHT_TIMES | (mode << 1) | DIF;
	if (i2c.write(slaveAddr, toSend, 1, false)) {
		return 2;
	}

    // Read extra samples and discard during conversion.
    const int NUM_EXTRA_SAMPLES = 0;

    char toReceive[(numReadings()+NUM_EXTRA_SAMPLES)*2];
    if (i2c.read(slaveAddr, toReceive, (numReadings()+NUM_EXTRA_SAMPLES)*2 /* 2 bytes * # samples */, false)) {
    	error = 1;
    }

    for(int i = 0; i < numReadings(); i++) {
        uint16_t left = ((uint16_t)toReceive[2*(i+NUM_EXTRA_SAMPLES)]);
        uint16_t right = ((uint16_t)toReceive[2*(i+NUM_EXTRA_SAMPLES) + 1]);
        uint16_t unsigned_num = (((left & 0b11) << 8) | right);
        // Preserve sign by moving the number to the left, then sign-extended right shift.
        int16_t s = (int16_t)(unsigned_num << 6);
        s = s >> 6;
        *(data+i) = s;
    }
    return error;
}
