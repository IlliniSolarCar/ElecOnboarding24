#ifndef WHEEL_US2066_H_
#define WHEEL_US2066_H_

/*
 * Basic driver for Wheel OLED display
 * Author: Daniel Wong
 * Original code found from:
 * https://os.mbed.com/users/mattjarvisast/code/NHD0216MWSB3/
 */

#include "mbed.h"

class US2066
{
public:
	/*
	 * Create a US2066 slave device interface
	 * @param spi - SPI master instance
	 * @param chip_select - chip select pin for SPI
	 * @param reset - reset pin
	 */
	US2066(SPI & spi, DigitalOut & chip_select, DigitalOut & reset);

	/*
	 * Initializes the OLED display, setting it up to write text.
	 * NOTE: This method takes approx. 105ms as required by the US2066 datasheet
	 * @param contrast - sets display contrast (0 being the lowest ("least bright") contrast)
	 * @return 0  - success, 1 - improper partID read, 2 - incorrect DDRAM address read
	 */
	uint8_t init(uint8_t contrast = 127);

	/*
	 * Clear display and write new text to OLED display
	 * @param linex - array of chars to put on line x
	 */
	void write(char (&line0)[20], char (&line1)[20],
			char (&line2)[20], char (&line3)[20]);

	/*
	 * Clear line and write line to OLED display
	 * @param lineIdx - line index (0-3) to write to
	 * @param line - array of chars to write to line
	 */
	void write(int lineIdx, char (&line)[20]);

	/*
	 * Turn display on or off
	 * @param on - 1 if turning display on, 0 if turning off
	 */
	void displayOn(bool on);

	/*
	 * Set display contrast (brightness)
	 * @param contrast - sets display contrast (0 being the lowest ("least bright") contrast)
	 */
	void setContrast(uint8_t contrast);

private:
	DigitalOut & _chip_select;
	DigitalOut & _reset;
	SPI & _spi;
	const int _spi_freq = 1000000; // Units Hz
	const uint8_t _partID = 0x21; // Part US2066

	// Keep track of what will be returned on the next _read(...) call
	// 0 - address counter, 1 - part ID
	bool _readCommand = 1;

	/*
	 * Reverse bits in given byte
	 * @param byte - byte to be reversed
	 * @return reversed byte
	 */
	uint8_t _reverseByte(uint8_t byte);

	/*
	 * Send command to OLED driver
	 * @param value - command byte
	 */
	void _sendCommand(uint8_t value);

	/*
	 * Send data to OLED driver
	 * @param value - data byte
	 */
	void _sendData(uint8_t value);

	/*
	 * Helper function, send command or data to OLED driver
	 * @param d_cnot - 1 if sending data, 0 if sending command
	 * @param value - command/data byte
	 */
	void _send(bool d_cnot, uint8_t value);

	/*
	 * Read part ID or address counter
	 * @param infoType - 0 if address counter, 1 if partID;
	 */
	uint8_t _readInfo(bool infoType);

	/*
	 * Read data from current address in OLED driver
	 * @param d_cnot - 1 if sending data, 0 if sending command
	 */
	uint8_t _read(bool d_cnot);

};

#endif /* WHEEL_US2066_H_ */
