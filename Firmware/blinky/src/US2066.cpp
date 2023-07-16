#include "US2066.h"

#define DUMMY_DATA 0x00

US2066::US2066(SPI & spi, DigitalOut & chip_select, DigitalOut & reset)
	: _chip_select(chip_select), _spi(spi), _reset(reset)
{
}

uint8_t US2066::init(uint8_t contrast)
{
	_reset = 0;
	wait_ms(1);
	_reset = 1;
	wait_ms(1);

	uint8_t readPartId = _readInfo(1);
//	if ((readPartId & 0x7F) != _partID) {
//		return 1;
//	}

	_sendCommand(0x2A); //function set (extended command set)

	_sendCommand(0x71); //function selection A
	_sendData(0x00); // disable internal VDD regulator (2.8V I/O). data(0x5C) = enable regulator (5V I/O)

	_sendCommand(0x28); //function set (fundamental command set)
	_sendCommand(0x08); //display off, cursor off, blink off
	_sendCommand(0x2A); //function set (extended command set)
	_sendCommand(0x79); //OLED command set enabled
	_sendCommand(0xD5); // set display clock divide ratio/oscillator frequency
	_sendCommand(0x70); // set display clock divide ratio/oscillator frequency

	_sendCommand(0x78); //OLED command set disabled
	_sendCommand(0x09); //extended function set (4 line, 5 dot display)

	_sendCommand(0x06); //COM SEG direction

	_sendCommand(0x72); //function selection B
	_sendData(0x00); //ROM CGRAM selection
	_sendCommand(0x2A); //function set (extended command set)
	_sendCommand(0x79); //OLED command set enabled
	_sendCommand(0xDA); //set SEG pins hardware configuration
	_sendCommand(0x10); //set SEG pins hardware configuration
	_sendCommand(0xDC); //function selection C
	_sendCommand(0x00); //function selection C
	setContrast(contrast);
	_sendCommand(0xD9); //set phase length
	_sendCommand(0xF1); //set phase length
	_sendCommand(0xDB); //set VCOMH deselect level
	_sendCommand(0x40); //set VCOMH deselect level
	_sendCommand(0x78); //OLED command set disabled
	_sendCommand(0x28); //function set (fundamental command set)
	_sendCommand(0x01); //clear display
	_sendCommand(0x80); //set DDRAM address to 0x00
	_sendCommand(0x0C); //display ON

	// Check that DDRAM address is set correctly
	if (_readInfo(0) != 0x00) {
		return 2;
	}
	wait_ms(100); //delay required by datasheet
	return 0;
}

void US2066::write(char (&line0)[20], char (&line1)[20],
		char (&line2)[20], char (&line3)[20])
{
	// Clear display, reset to line 1
	_sendCommand(0x01);
	_sendCommand(0x02);
	wait_us(500);
	this->write(0, line0);
	this->write(1, line1);
	this->write(2, line2);
	this->write(3, line3);
}

void US2066::write(int lineIdx, char (&line)[20]) {
	// set DDRAM address to start of appropriate line
	_sendCommand(0x80 + lineIdx * 0x20);
	for (int i = 0; i < 20; i++) {
		_sendData(line[i]);
	}
}

void US2066::displayOn(bool on) {
	_sendCommand(on ? 0x0C : 0x08);
}

void US2066::setContrast(uint8_t contrast) {
	_sendCommand(0x81);
	_sendCommand(contrast);
}

uint8_t US2066::_reverseByte(uint8_t byte)
{
	byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
	byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
	byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
	return byte;
}

void US2066::_sendCommand(uint8_t value)
{
	_send(false, value);
}

void US2066::_sendData(uint8_t value)
{
	_send(true, value);
}

void US2066::_send(bool d_cnot, uint8_t value)
{
	value = _reverseByte(value);
	uint8_t buffer[3];
	buffer[0] = d_cnot ? 0b11111010 : 0b11111000;
	buffer[1] = value & 0b11110000;
	buffer[2] = value << 4;
	_spi.format(8, 3);
	_spi.frequency(_spi_freq);
	_chip_select.write(0);
	_spi.write(buffer[0]);
	_spi.write(buffer[1]);
	_spi.write(buffer[2]);
	_chip_select.write(1);
}

uint8_t US2066::_readInfo(bool infoType) {
	uint8_t readInfo = _read(0);
	// Do a second _read(...) call if necessary to get correct info
	return (infoType != _readCommand) ? readInfo : _read(0);
}

uint8_t US2066::_read(bool d_cnot) {
	uint8_t startByte = d_cnot ? 0xFE : 0xFC;
	_spi.format(8, 2);
	_spi.frequency(_spi_freq);
	_chip_select.write(0);
	_spi.write(startByte);
	uint8_t ret = (uint8_t)_spi.write(DUMMY_DATA);
	_chip_select.write(1);
	_readCommand = !_readCommand;
	return ret;
}
