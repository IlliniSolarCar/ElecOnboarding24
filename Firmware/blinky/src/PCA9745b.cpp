/*
 * PCA9745B.cpp
 *
 *  Created on: March 21, 2019
 *      Author: Jonathan Mullen
 *
 */

#include <PCA9745b.h>
#include <peripherals.h>
#include <can_struct.h>

#define DUMMY_DATA 0xFFFF

template <typename T_uint>
PCA9745b<T_uint>::PCA9745b(DigitalOut& cs, DigitalOut& reset, DigitalOut& enable, SPI& spi, uint8_t count /* = 0*/, bool exponentialDim /* = true */)
	: _cs(cs), _reset(reset), _enable(enable), _spi(spi),  _deviceCount(count), _exponentialDim(exponentialDim)
{
	static_assert((T_uint)-1 == UINT16_MAX || (T_uint)-1 == UINT32_MAX || (T_uint)-1 == UINT64_MAX, "Not a supported PCA9745b Template Type");
};

template <typename T_uint>
uint8_t PCA9745b<T_uint>::init(uint8_t brightness){

	_cs = 1;
	_reset = 1;

	/*
	 * make sure we have a valid device number for the template type
	 */
	T_uint checker = -1;

	uint64_t maxValues[4] = {UINT16_MAX, UINT32_MAX, UINT64_MAX, UINT64_MAX};

	/*
	 * Automatically detect count if count passed in is 0
	 */
	if(_deviceCount == 0){
			for(int i = 4; i > 0; i--){
				if(checker == maxValues[i - 1]){
					_deviceCount = i;
					break;
				}
			}
	}
	// Make sure given device count it valid
	else if(_deviceCount > 4 || (maxValues[_deviceCount - 1] > checker)){
		return 1;
	}

	/*
	 * Verify Connection.
	 */
	if(!this->_checkConnection()){
		return 2; //connection error
	}

	/*
	 * Reset and Initialize the output
	 */
	this->_resetDevice();
	wait_ms(2);  //per data sheet, up to 1.5ms needed before commands
	this->_init(brightness);

	//Set dimming mode to exponential
	setDimmingMode(true);

	_initialized = true;

	return 0; //all good

}

template <typename T_uint>
void PCA9745b<T_uint>::setBrightness(uint8_t brightness){
	if(_initialized && !_lowPower){
		this->_writePortAll(IRefAll, brightness);
		_brightness = brightness;
	}
}

template <typename T_uint>
void PCA9745b<T_uint>::setDimmingMode(bool setDimMode){
	_exponentialDim = setDimMode;
	uint8_t dimmingModeValue = _exponentialDim ? 0x04 : 0x00;

	T_uint mode2_status = this->_readPortAll(mode2);

	for (int i = 0; i < _deviceCount; i++) {

		// Extracting 5th bit and preserving its values
		// Setting 2nd bit to 1 to change dimming mode to exponential
		this->_writePort(mode2, ((uint8_t) mode2_status & 0x20) | dimmingModeValue, i);
		mode2_status = mode2_status >> 8;
	}
}

template <typename T_uint>
uint8_t PCA9745b<T_uint>::setOutput(T_uint output){
	if(_initialized){
		this->_writeOutputsAll(output);
		return this->_checkIfErrors();
	}
	return 0xFF;
}

template <typename T_uint>
T_uint PCA9745b<T_uint>::checkOpenCkt() {
	return _checkCktErrors(1);
}

template <typename T_uint>
T_uint PCA9745b<T_uint>::checkShortCkt() {
	return _checkCktErrors(0);
}

template <typename T_uint>
void PCA9745b<T_uint>::enable(bool enable){
	if(_initialized)
		_enable.write(!enable);
}

template <typename T_uint>
void PCA9745b<T_uint>::reset(){
	if(_initialized){
		this->enable(false);
		this->_resetDevice();
		_lowPower = 0;
		wait_ms(2);
		this->_init();
		this->enable(true);
	}
}

template <typename T_uint>
void PCA9745b<T_uint>::lowPower(bool lp) {
	if (lp != _lowPower) {
		this->_writePortAll(mode1, lp ? 0x10 : 0x00);
		_lowPower = lp;
	}
}

template<typename T_uint>
bool PCA9745b<T_uint>::isLowPower() {
	return _lowPower;
}

/*
 *
 *    Private Member Functions
 *
 */

template <typename T_uint>
void PCA9745b<T_uint>::_setupSPI(){
	_spi.frequency(20000);
	_spi.format(16,1);
}

template <typename T_uint>
bool PCA9745b<T_uint>::_checkConnection(){
	//shift the dummy data through all the devices
	//and make sure we get it back as expected
	uint16_t testData = 0x1234;
	uint16_t result = 0;
	this->_setupSPI();
	_cs = 0;
	wait_ms(1);
	_spi.write(testData);
	for(int i = 0; i < _deviceCount; i++){
		result = _spi.write(DUMMY_DATA);
	}
	_cs = 1;
	return (result == testData);
}

template <typename T_uint>
void PCA9745b<T_uint>::_init(){
	this->_init(_brightness);
}

template <typename T_uint>
void PCA9745b<T_uint>::_init(uint8_t brightness){
	//set offset
	this->_writePortAll(offset, _offset);

	//set current limit / brightness
	this->lowPower(0);
	this->_writePortAll(IRefAll, brightness);
	_brightness = brightness;

	if(_output != 0)
		this->_writeOutputsAll(_output);
}

template <typename T_uint>
void PCA9745b<T_uint>::_resetDevice(){
	_reset = 0;
	wait_us(3);   //per data sheet pulse width must be > 2.5us
	_reset = 1;

}

template <typename T_uint>
uint8_t PCA9745b<T_uint>::_checkIfErrors(){
	uint8_t retError = 0;
	T_uint data = _readPortAll(mode2);
	for(int i = 0; i < _deviceCount; i++){
		//check overtemp
		if(CHECK_BIT(data, 7 + 8*i))
			retError |= 1 << 2*i;
		//check output error
		if(CHECK_BIT(data, 6 + 8*i))
			retError |= 1 << (1 + 2*i);
	}
	return retError;
}

template <typename T_uint>
T_uint PCA9745b<T_uint>::_checkCktErrors(bool errorType){
	// 2 indicates checking for open circuits, 1 for short circuits (numbers are set according to datasheet table)
	int type = errorType ? 2 : 1;
	_portMap errorPorts[4] = { error0, error1, error2, error3 };
	T_uint ret = 0;
	for (int i = 0; i < 4; i++) {
		T_uint errorFlags = _readPortAll(errorPorts[i]);
		for (int j = 0; j < _deviceCount * 4; j++) {
			// "& 3" extracts the last 2 bits of errorFlags
			ret |= ((errorFlags & 3) == type) << (((j / 4) * 16) + (j % 4) + (i * 4));
			errorFlags = errorFlags >> 2;
		}
	}
	_outputDisable &= ~ret;

	// Rewrite to the display with the disabled outputs
	this->_writeOutputsAll(_output);

	// Clear all error flags in the LED driver (to avoid detecting the same error again)
	T_uint mode2_status = this->_readPortAll(mode2);
	for (int i = 0; i < _deviceCount; i++) {
		// Extract the 2nd and 5th bits of the current status and include in data being put written back to the mode2 register
		// Set the 4th bit to 1 to clear the error flags
		this->_writePort(mode2, ((uint8_t) mode2_status & 0x24) | 0x10, i);
		mode2_status = mode2_status >> 8;
	}



	return ret;
}

template <typename T_uint>
void PCA9745b<T_uint>::_writePortAll(_portMap port, uint8_t data){
	uint16_t sendData = this->_formatData(true, port, data);
	this->_setupSPI();
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		_spi.write(sendData);
	}
	_cs = 1;
}

template <typename T_uint>
void PCA9745b<T_uint>::_writePort(_portMap port, uint8_t data, uint8_t deviceIndex){
	uint16_t sendData = this->_formatData(true, port, data);
	this->_setupSPI();
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		_spi.write(((deviceIndex == i) ? sendData : DUMMY_DATA));
	}
	_cs = 1;
}

template <typename T_uint>
T_uint PCA9745b<T_uint>::_readPortAll(_portMap port){
	uint16_t sendData = this->_formatData(false, port);
	this->_setupSPI();
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		_spi.write(sendData);
	}
	_cs = 1;

	T_uint readData = 0;
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		//get 16 bits back but top 8 are NOP, bottom 8 are data.
		readData |= (uint64_t)((_spi.write(DUMMY_DATA)) & 0x00FF) << (8*i);
	}
	_cs = 1;

	return readData;
}

template <typename T_uint>
uint8_t PCA9745b<T_uint>::_readPort(_portMap port, uint8_t deviceIndex){
	uint16_t sendData = this->_formatData(false, port);
	this->_setupSPI();
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		_spi.write(((deviceIndex == i) ? sendData : DUMMY_DATA));
	}
	_cs = 1;

	uint8_t readData = 0;
	_cs = 0;
	wait_us(1);
	for(int i = 0; i < _deviceCount; i++){
		//Data is only bottom 8 returned
		uint8_t tempData = (uint8_t)_spi.write(DUMMY_DATA);
		if(deviceIndex == i)
			readData = tempData;
	}
	_cs = 1;
	return readData;
}

template <typename T_uint>
uint16_t PCA9745b<T_uint>::_formatData(bool write, _portMap port, uint8_t data /* = 0x00*/){
	uint16_t ret = (uint8_t)port << 9; //port is top 7
	ret |= data;

	//data is bottom 8 (all ones in case of read)
	if(write)
		ret &= 0xFEFF;   //bit 8 is 0 for a write operation
	else
		ret |= 0x01FF; //for read, ensure data all high

	return ret;
}

template <typename T_uint>
void PCA9745b<T_uint>::_writeOutputsAll(T_uint output){

	output = output & _outputDisable;
	_output = output;

	uint16_t outputs[_deviceCount];
	for(int i = 0; i < _deviceCount; i++){
		outputs[i] = (uint16_t)output;
		output = output >> 16;
	}

	_portMap outputPorts[4] = {ledout0, ledout1, ledout2, ledout3};

	this->_setupSPI();
	for(int i = 0; i < 4; i++){
		uint8_t write[_deviceCount] = {0,0,0,0};
		for(int j = 0; j < _deviceCount; j++){
			for(int k = 0; k < 4; k++){
				write[j] |= CHECK_BIT(outputs[j], (4*i) + k) ? (0x01 << (2*k)) : 0x00;
			}
		}
		_cs = 0;
		wait_us(1);
		for(int j = 0; j < _deviceCount; j++){
				_spi.write(this->_formatData(true, outputPorts[i], write[j]));
		}
		_cs = 1;
	}
}
