/*
HASS S-50 + LTC2453
Current Sensor + ADC Combo
 *
 * Created on: Feb 2021
 * Author: Priyal
 *
*/
#include "HASS_LTC2453.h"

HASS_LTC2453::HASS_LTC2453(I2C &i2c, int offset): _i2c(i2c), _offset(offset) {
	 _i2c.frequency(100000);
}


bool HASS_LTC2453::readCurrent(int* avgReading) {
	int new_reading;
	int error = readValue(new_reading);
	// only increment index and update sum if there is no error
	if (!error) {
		// update running sum
		_sum = _sum + new_reading - _currentValues[_index];
		// set value in the array to the new value just read
		_currentValues[_index] = new_reading;
		// increment index for next time read_avg is called
		_index = (_index + 1) % numReadings;
		 // divide sum by number of readings and set this to the averageReading value
		 _packCurrent = _sum / numReadings + _offset;
	}
	else  _packCurrent = _lastReading + _offset;

	*avgReading = _packCurrent;
	return error;
}


bool HASS_LTC2453::readValue(int& data) {
	int reading = 0;
	int ack;
	char toReceive[2];
	ack = _i2c.read(LTC2453_Slave_Addr, toReceive, 2, false);		// read from ADC using i2c

	if(ack == 0) {
		reading = (toReceive[0] << 8) | toReceive[1];
		ack = 0;
		reading = reading - LTC2453_Offset;					// subtract 32768 from output code
		_lastReading = reading;								// set private variable to new updated reading
		data = reading;									// data is set to new data
		return 0;											// no error in reading new data
	}
	// A NAK was received - couldn't perform an I2C read on the ADC - data should be ignored
	// set data to previous reading value and return 0 (not ready to read a new value)
	data = _lastReading;
	return 1;
}


int HASS_LTC2453::getPackCurrent() {
	return _packCurrent;
}
