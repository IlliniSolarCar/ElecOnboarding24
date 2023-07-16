/*
 * HASS_LTC2453.h
 *
 * Implementation of HASS sensor using the LTC2453 ADC.
 *  Created on: May 18, 2020
 *      Author: Priyal Gosar
 */

#ifndef COMMON_API_HASS_LTC2453_H_
#define COMMON_API_HASS_LTC2453_H_


#include <mbed.h>
// CAN send rate / ADC read rate: 100000/16667
constexpr int numReadings = 6;

const uint32_t LTC2453_Slave_Addr = 0b00101000;	// Fixed slave device address from the data sheet
const uint32_t LTC2453_Offset = 0x8000;         // Fixed value for conversion of output data (Decimal = 32768)

class HASS_LTC2453 {
public:

    /**
     * Create a HASS sensor, reading from the specified I2c objects
     * @param i2c I2C for ADC to communicate with the and read the current sensor outputs.
     * @param offset unique offset value in centiAmps for calibration when we put it into the car
     */
    HASS_LTC2453 (I2C &i2c, int offset);
    /**
	 * Reads the current value in centiAmps and sets_packCurrent to it
	 *
	 * @param avgReading variable to store latest value into
	 * @return an 1 if it could not read the value from ADC
	 */
    bool readCurrent(int* avgReading);

	/* readValue() uses i2c to communicate and receive the value output from the LTC2453ADC
	* and stores that value in the int data passed in
	*
	*
	* @param pointer to the data that should be filled in with the current value from the current sensor in centiAmps
	* @returns 0 if no error in reading and an updated value was successfully read in,
	* -1 if the ADC received a NAK from the i2c bus,
	* or 1 if we read too quickly
	*/
	bool readValue(int& data);

	/* getPackCurrent() returns _packCurrent value
	*
	* @returns an int that represents an averaged value of _packCurrent in centiAmps
	*/
	int getPackCurrent();


private:
	int _currentValues[numReadings] = { 0 };		// array of last x current values read from ADC
    int _index = 0;							// index to place new value
    int _sum = 0;							// running sum used for averaging and updated every read
    int _offset;							// offset of actual current value based on ADC, wiring, actual current sensor, etc.

    int _packCurrent;

    /* LTC2453 ADC specific objects */
    I2C& _i2c;
    int _lastReading=0;

};


#endif /* COMMON_API_HASS_LTC2453_H_ */

