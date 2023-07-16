/*
 * This is the driver class for the CAT9554 I2C IO Expander
 *
 */

#ifndef COMMON_API_CAT9554_H_
#define COMMON_API_CAT9554_H_

#include <mbed.h>
#include <stdint.h>

#define CAT_P_0 0b00000001
#define CAT_P_1 0b00000010
#define CAT_P_2 0b00000100
#define CAT_P_3 0b00001000
#define CAT_P_4 0b00010000
#define CAT_P_5 0b00100000
#define CAT_P_6 0b01000000
#define CAT_P_7 0b10000000

class CAT9554 {

public :
	typedef uint8_t DeviceAddress;

	//Constructor
	CAT9554(I2C& i2c, DeviceAddress slaveAddr);


	/*
	 * Read the Input register
	 * @param value The reference to the 8-bit value corresponding to each pin read
	 * @returns boolean set true on successful read
	 */
	bool readInputReg(uint8_t& value);


	/*
	 * Write to output register. Data written to pins configured as outputs is ignored
	 * @param value The 8-bits of data to be written to each of 8 pins.
	 * @returns boolean set true on successful write
	 *
	 */
	bool writeOutputReg(const uint8_t value);


	/*
	 * Set the Input/Output direction of each pin
	 * @param pins the 8 bits of pin values to set. 1 is input with weak pull-up 0 is output
	 * @returns boolean set true on successful write
	 */
	bool configPins(const uint8_t pins);


	/*
	 * Toggle selected pins regardless of initial state
	 * @param toggle 8-bit value set to 1 for each pin to toggle
	 * @returns true on successful write
	 */
	bool togglePins(const uint8_t toggle);

	/*
	 * Read the stored input or output values from the last i2c command
	 * @returns io_vals holding the most recent input or output values from the device
	 */
	uint8_t readIoValues();


private:
	I2C& i2c;
	const DeviceAddress slaveAddr;
	uint8_t io_vals; //keep a local track of all the output values sent to the expander
	uint8_t config_vals; //Stores configuration of each pin on IO expander, 1 for input, 0 for output

	enum MemoryAddr{
		Input_Reg = 0x00,
		Output_Reg = 0x01,
		Polarity_Reg = 0x02,
		Config_Reg = 0x03,
	};

protected:


};

#endif /*COMMON_API_CAT9554_H_ */
