#include <CAT9554.h>

CAT9554::CAT9554(I2C& i2c, DeviceAddress slaveAddr):
	i2c(i2c), slaveAddr(slaveAddr){
	io_vals = 0xff;
	config_vals = 0xff;
}

bool CAT9554::configPins(const uint8_t pins){
	uint8_t data[2] = {Config_Reg, pins};\
	int status = i2c.write(slaveAddr, (const char*)data, sizeof(data));
	config_vals = pins;
	return status == 0;
}

bool CAT9554::readInputReg(uint8_t& value){
	uint8_t data[1] = {Input_Reg};
	int status = i2c.write(slaveAddr, (const char*)data, sizeof(data), true);
	if(status == 0){
		status = i2c.read(slaveAddr, (char*)data, sizeof(data));
		value = data[0];
		io_vals = data[0];
		return status == 0;
	}
	return 1;
}

bool CAT9554::writeOutputReg(const uint8_t value){
	io_vals = value;
	uint8_t data[2] = {Output_Reg, value};
	io_vals = value;
	int status = i2c.write(slaveAddr, (const char*)data, sizeof(data));
	return status == 0;
}

bool CAT9554::togglePins(const uint8_t toggle){
	uint8_t value = toggle ^ io_vals;
	io_vals = value;
	return writeOutputReg(value);
}

uint8_t CAT9554::readIoValues(){
	return io_vals;
}
