/*
 * WheelIndicators.cpp
 *
 *  Created on: Apr 15, 2020
 *      Author: Jonathan
 */

#include "WheelIndicators.h"

WheelIndicators::WheelIndicators(SPI& spi, WheelCommon& common)
	: _common(common),
	  _leftTurnLED(P_LSIGNAL),
	  _rightTurnLED(P_RSIGNAL),
	  _headLightLED(P_LLED),
	  _parkingLightLED(P_RLED),
	  _sevenSegCS(P_CS_LED),
	  _sevenSegReset(P_RES_LED),
	  _sevenSegEn(P_EN_LED),
	  _sevenSegment(_sevenSegCS, _sevenSegReset, _sevenSegEn, spi, _deviceCount)
{
}

uint8_t WheelIndicators::init(){
	_leftTurnLED = 0;
	_rightTurnLED = 0;
	_headLightLED = 0;
	_parkingLightLED = 0;

	//TODO figure out default brightness and save
	uint8_t ret = _sevenSegment.init(0x01);
	if (!ret) {
		// Flash LEDs to check for short/open circuits
		this->_writeDisplay(888.8, true);
		wait_us(100);
		this->sendCktErrors();
		// Update display to turn off short/open-circuited LEDs
		this->_writeDisplay(-1, false);
		this->setDisplayBrightness(0x10);
	}
	// Disable all LEDs (should be enabled once battery is fully on)
	this->enableAll(false);
	return ret;
}

void WheelIndicators::hazards(bool on){
	if(on != _hazardStatus){
		_hazardStatus = on;
		this->_updateTurnLEDs();
	}
}

void WheelIndicators::leftTurnSignal(bool on){
	if(on != _leftTurnStatus){
		_leftTurnStatus = on;
		this->_updateTurnLEDs();
	}
}

void WheelIndicators::rightTurnSignal(bool on){
	if(on != _rightTurnStatus){
		_rightTurnStatus = on;
		this->_updateTurnLEDs();
	}
}

void WheelIndicators::headLights(bool on){
	if(on != _headLightLED.read())
		_headLightLED.write(on);
}

void WheelIndicators::cruiseLights(bool on){
	if(on != _parkingLightLED.read())
		_parkingLightLED.write(on);
}


void WheelIndicators::setSpeed(uint32_t rpm, const uint32_t time){
	//TODO Figure out how to handle one vs two MCCs.
	//convert to meters per minute
	float temp = (float)rpm * WHEEL_CIR;
	//convert to kilometers per hour
	temp = temp / 1000.0 * 60.0;
	if(!_common.checkConfigParam(BRIZO_CAN::wheelConfig_useKMH))
		temp = temp * KMHtoMPH;
	_speed = temp;
	_lastSpeedTime = time;
}

void WheelIndicators::setVoltage(uint32_t voltage, const uint32_t time){
	_voltage = (float)voltage / 10000.0;
	_lastVoltageTime = time;
}

void WheelIndicators::setTime(uint8_t hour, uint8_t minute){
	_time = (float)hour;
	_time += ((float)minute)/100;
	_timeKnown = true;
}

void WheelIndicators::tickMinute(){
	_time += 0.01;
	if((int)(_time * 100) % 100 >= 60){
		if(_time > 23)
			_time = 0;
		else
			_time = (int)time + 1;
	}

}

void WheelIndicators::setMode(sevenSegMode mode){
	_mode = mode;
}

uint8_t WheelIndicators::writeDisplay(const uint32_t time){
	float value;
	bool showDecimal = false;
	uint8_t decimalCount = 1;
	bool showDecimalDigits = true;

	switch(_mode){
		case displaySpeed:
			if(TimingCommon::threshold(_lastSpeedTime, time, WHEEL_DISPLAY_TIMEOUT_US))
				value = -1;
			else{
				value = _speed;
				showDecimalDigits = false;
			}
			break;
		case displayVoltage:
			if(TimingCommon::threshold(_lastVoltageTime, time, WHEEL_DISPLAY_TIMEOUT_US))
				value = -1;
			else{
				value = _voltage;
				showDecimal = true;
			}
			break;
		case displayTime:
			if(!_timeKnown)
				value = -1;
			else{
				value = _time;
				decimalCount = 2;
				showDecimal = true;
			}
			break;
		default:
			value = -1;
			break;
	}

	//Checks if the wheel is in low power mode, if it is the brightness is reduced
	//TODO: Test and figure out what the best default and low power mode brightnesses are
//	if(common.getWheelLowPower())
//		setDisplayBrightness(DISPLAY_DEFAULT_BRIGHTNESS / 2);
//	else
//		setDisplayBrightness(DISPLAY_DEFAULT_BRIGHTNESS);

	uint8_t error = this->_writeDisplay(value, decimalCount, showDecimal, showDecimalDigits);

	//handle sending errors
	//bits 1 & 3 are over-temp error device 0 & 1 respectively
//	if(error & 0x05)
//		_common.SendError(BRIZO_CAN::wheelError_sevenSegOverTemp);
//	//bits 2 & 4 are output error device 0 & 1 respectively
//	if(error & 0x0A) {
//		_common.SendError(BRIZO_CAN::wheelError_sevenSegOutput);
//		bool cktErrors = this->sendCktErrors();
//	}
	return error;
}


void WheelIndicators::setDisplayBrightness(uint8_t brightness){
	_sevenSegment.setBrightness(brightness);
}

void WheelIndicators::updateBrightness(){
	uint8_t newLevel = 0;
	newLevel |= _common.checkConfigParam(BRIZO_CAN::wheelConfig_7SegBrightness0);
	newLevel |= _common.checkConfigParam(BRIZO_CAN::wheelConfig_7SegBrightness1) << 1;
	newLevel |= _common.checkConfigParam(BRIZO_CAN::wheelConfig_7SegBrightness2) << 2;
	if(newLevel != brightnessLevel){
		brightnessLevel = newLevel;
		if(brightnessLevel > 7){
			brightnessLevel = 7;
		}

		uint8_t brightness = SEVEN_SEG_BRIGHTNESS[brightnessLevel];

		//half brightness (not less than level 1 if low power)
		if(_common.getWheelLowPower()){
			brightness = brightness / 2;
			if(brightness < SEVEN_SEG_BRIGHTNESS[0]){
				brightness = SEVEN_SEG_BRIGHTNESS[0];
			}
		}

		this->setDisplayBrightness(brightness);
	}
}

bool WheelIndicators::sendCktErrors() {
	uint32_t openCktErrors = _sevenSegment.checkOpenCkt();
	uint32_t shortCktErrors = _sevenSegment.checkShortCkt();

	if (openCktErrors || shortCktErrors) {
		for (int deviceIndex = 0; deviceIndex < _deviceCount; deviceIndex++) {
			uint16_t errors[2] = {(uint16_t) openCktErrors, (uint16_t) shortCktErrors};
			for (int i = 0; i < 2; i++) {
				if (errors[i]) {
					BRIZO_CAN::Wheel7SegDriverDevice device = static_cast<BRIZO_CAN::Wheel7SegDriverDevice>(deviceIndex);
					BRIZO_CAN::Wheel7SegDriverCktError cktError = { (uint8_t) i, device, errors[i] };
					_common.writeCANMessage(makeMessage(BRIZO_CAN::WHEEL_7SEG_DRIVER_CKT_ERROR.ID, cktError));
				}
			}
			openCktErrors = openCktErrors >> 16;
			shortCktErrors = shortCktErrors >> 16;
		}
		return 1;
	}
	return 0;
}

void WheelIndicators::enableAll(bool on) {
	_sevenSegment.enable(on);
	if (on) {
		this-> writeDisplay(
				(_lastSpeedTime > _lastVoltageTime ? _lastSpeedTime : _lastVoltageTime)
				+ WHEEL_DISPLAY_TIMEOUT_US);
	}
}

uint8_t WheelIndicators::testDisplays(uint8_t led){
	uint32_t output = 0;
	if(led < 8){
		uint16_t singleDriver = 0x0000;
		// bits 1-3 and 12-15 are display 1, and 4-11 is the 2nd
		singleDriver |= 1 << ((led < 4) ? led : led + 8);
		singleDriver |= 1 << (led + 4);
		output = singleDriver | (singleDriver << 16);
	}

	return _sevenSegment.setOutput(output);
}

void WheelIndicators::_updateTurnLEDs(){
	if(_hazardStatus || _leftTurnStatus){
		if(!_leftTurnLED.read())
			_leftTurnLED = 1;
	}else{
		_leftTurnLED = 0;
	}

	if(_hazardStatus || _rightTurnStatus){
		if(!_rightTurnLED.read())
			_rightTurnLED = 1;
	}else{
		_rightTurnLED = 0;
	}
}

uint8_t WheelIndicators::_writeDisplay(float data, uint8_t decimalCount, bool showDecimalPoint, bool showDecimalDigits){
	//static_assert(decimalCount < 4, "Can only show 3 decimal points");
	uint32_t writeData = 0;
	if(decimalCount > 3)
		decimalCount = 3; //can't do more than 3
	//write dashes
	if(data < 0){
		writeData |= (1 << lowerG) | (1 << upperG) | (1 << (lowerG + 16)) | (1 << (upperG + 16));
	}
	else{
		uint8_t writeArray[4];
		for(int i = 0; i < 4; i++){
			if(i < decimalCount){
				if(showDecimalDigits)
					writeArray[i] = (uint8_t)(data * pow(10, decimalCount - i))%10;
				else
					writeArray[i] = 100; //use to indicate it should be blank
			}else{
				writeArray[i] = (uint8_t)(data / pow(10, i - decimalCount ))%10;
			}
		}

		//lower data is upper two digits; top digit should be all off if value is 0
		writeData |= (uint32_t)this->_writeSingleDisplayHelper((writeArray[3] == 0 && decimalCount < 3) ? 0xFF : writeArray[3], writeArray[2]);
		//if not show decimal lowest digit should be all off
		writeData |= ((uint32_t)this->_writeSingleDisplayHelper(writeArray[1], writeArray[0])) << 16;
		if(showDecimalPoint){
			if(decimalCount == 1)
				writeData |= (1 << upperDP) << 16;
			else if(decimalCount == 2)
				writeData |= (1 << lowerDP);
			else
				writeData |= (1 << upperDP);
		}
	}

	return _sevenSegment.setOutput(writeData);
}

uint16_t WheelIndicators::_writeSingleDisplayHelper(uint8_t upperNum, uint8_t lowerNum){
	uint16_t writeData = 0;
	//set the lower number
	switch (lowerNum){
	case 0:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerC) | (1 << lowerD)
						| (1 << lowerD) | (1 << lowerE) | (1 << lowerF);
		break;
	case 1:
		writeData |= (1 << lowerB) | (1 << lowerC);
		break;
	case 2:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerD) | (1 << lowerE)
						| (1 << lowerG);
		break;
	case 3:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerC) | (1 << lowerD)
						| (1 << lowerG);
		break;
	case 4:
		writeData |= (1 << lowerB) | (1 << lowerC) | (1 << lowerF) | (1 << lowerG);
		break;
	case 5:
		writeData |= (1 << lowerA) | (1 << lowerC) | (1 << lowerD) | (1 << lowerF)
						| (1 << lowerG);
		break;
	case 6:
		writeData |= (1 << lowerA) | (1 << lowerC) | (1 << lowerD) | (1 << lowerE)
						| (1 << lowerF) | (1 << lowerG);
		break;
	case 7:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerC);
		break;
	case 8:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerC) | (1 << lowerD)
						| (1 << lowerE) | (1 << lowerF) | (1 << lowerG);
		break;
	case 9:
		writeData |= (1 << lowerA) | (1 << lowerB) | (1 << lowerC) | (1 << lowerF)
						| (1 << lowerG);
		break;
	}
	//set the upper number
	switch (upperNum){
	case 0:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperC) | (1 << upperD)
						| (1 << upperD) | (1 << upperE) | (1 << upperF);
		break;
	case 1:
		writeData |= (1 << upperB) | (1 << upperC);
		break;
	case 2:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperD) | (1 << upperE)
						| (1 << upperG);
		break;
	case 3:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperC) | (1 << upperD)
						| (1 << upperG);
		break;
	case 4:
		writeData |= (1 << upperB) | (1 << upperC) | (1 << upperF) | (1 << upperG);
		break;
	case 5:
		writeData |= (1 << upperA) | (1 << upperC) | (1 << upperD) | (1 << upperF)
						| (1 << upperG);
		break;
	case 6:
		writeData |= (1 << upperA) | (1 << upperC) | (1 << upperD) | (1 << upperE)
						| (1 << upperF) | (1 << upperG);
		break;
	case 7:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperC);
		break;
	case 8:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperC) | (1 << upperD)
						| (1 << upperE) | (1 << upperF) | (1 << upperG);
		break;
	case 9:
		writeData |= (1 << upperA) | (1 << upperB) | (1 << upperC) | (1 << upperF)
						| (1 << upperG);
		break;
	}

	return writeData;
}


