/*
 * common.cpp
 *
 * Implementation of wheel common class defined in inc/common.h
 *
 *  Created on: Nov 25, 2020
 *      Author: Jonathan
 */

#include <common.h>
#include <can_struct.h>
#include "reset.h"

WheelCommon::WheelCommon(Timer* _timer, CAN* _can, TimingCommon& _timing)
	: hardware_common_mbed(_timer, _can),
	  _timing(_timing)
{}

void WheelCommon::init(){
	hardware_common_mbed::setupCAN();
	hardware_common_mbed::setupLEDs(&led1, &led2, &led3, &led4);
	this->SetOperationMode(BRIZO_CAN::operationMode_startUp);
//	this->SendVersion();

	_config = DEFAULT_CONFIG;

#ifdef LOCAL_BUILD
	this->_setConfigParam(BRIZO_CAN::wheelConfig_localBuild, true);
#else
	this->_setConfigParam(BRIZO_CAN::wheelConfig_localBuild, false);
#endif

}

void WheelCommon::start(){
	//start timing
	bool wdt_reset = false;
	hardware_common_mbed::startTimingCommon(&_timing, &wdt_reset);
	if(wdt_reset)
//		this->SendError(BRIZO_CAN::wheelError_watchdogReset);
	//Reset stuff was giving errors, fix later
//	if(Reset::brownOutCausedReset())
//		this->SendError(BRIZO_CAN::wheelError_brownOutReset);
//	if(Reset::externalCausedReset())
//		this->SendError(BRIZO_CAN::wheelError_externalReset);
//	if(Reset::softwareCausedReset())
//		this->SendError(BRIZO_CAN::wheelError_softwareReset);

	this->SetOperationMode(BRIZO_CAN::operationMode_normalAuxPower);
//	this->SendConfig();

}

//void WheelCommon::SendWarning(BRIZO_CAN::WheelWarnings warning){
//	//TODO: Add ability to suppress warnings externally
//	if(warning != BRIZO_CAN::wheelWarning_none)
//		this->_sendCANMessage(makeMessage(BRIZO_CAN::WHEEL_WARN.ID, (uint8_t)warning));
//}
//
//void WheelCommon::SendError(BRIZO_CAN::WheelErrors error){
//	//TODO: Add ability to suppress error externally
//	if(error != BRIZO_CAN::wheelError_none)
//		this->_sendCANMessage(makeMessage(BRIZO_CAN::WHEEL_ERROR.ID, (uint8_t)error));
//}

//void WheelCommon::SendVersion(){
//
//BRIZO_CAN::WheelVersions versions = {
//};
//
//	this->_sendCANMessage(makeMessage(BRIZO_CAN::WHEEL_VERSION.ID, versions));
//}
//
//void WheelCommon::SendConfig(){
//	this->_sendCANMessage(makeMessage(BRIZO_CAN::WHEEL_CONFIG.ID, _config));
//}
//
void WheelCommon::SendOperationMode(){
	this->_sendCANMessage(makeMessage(BRIZO_CAN::WHEEL_MODE.ID, _wheelOperationMode));
}
//
void WheelCommon::SetOperationMode(BRIZO_CAN::operationMode newMode){
	_wheelOperationMode = newMode;
	this->SendOperationMode();
}

BRIZO_CAN::operationMode  WheelCommon::GetOperationMode() const{
	return _wheelOperationMode;
}

int WheelCommon::writeCANMessage(CANMessage msg){
	if(this->checkConfigParam(BRIZO_CAN::wheelConfig_debugMessages) || !this->_isDebugMessage(msg.id))
		return this->_sendCANMessage(msg);
	return -1;
}

int WheelCommon::_sendCANMessage(CANMessage msg){
	this->toggleSendCANLED();
	return hardware_common_mbed::writeCANMessage(msg);
}

bool WheelCommon::_isDebugMessage(int id) const{
	return id >= CAN_DEBUG_ID_THRESHOLD;
}

void WheelCommon::setConfigParam(BRIZO_CAN::WheelConfig param, bool val, bool sendCAN /* = true */){
	// Some params are read only as they are innate to this hw/fw, for ease those are the lowest enum values and ignored here
	if(param <= BRIZO_CAN::wheelConfig_boardID2)
		return;

	this->_setConfigParam(param, val);

	if(sendCAN)
		this->SendConfig();
}

void WheelCommon::setConfigParams(uint32_t toSet, uint32_t values){
	for(uint8_t i = 0; i < BRIZO_CAN::wheelConfig__lastEnumItem; i++){
		if(toSet & (1UL << i))
			this->setConfigParam((BRIZO_CAN::WheelConfig)i, values & (1UL << i), false);
	}
	this->SendConfig();
}

bool WheelCommon::checkConfigParam(BRIZO_CAN::WheelConfig param) const{
	return _config & (1UL << param);
}

void WheelCommon::setWheelLowPower(bool lowPower){
	_wheelLowPower = lowPower;
}

const bool WheelCommon::getWheelLowPower(){
	return _wheelLowPower;
}

void WheelCommon::_setConfigParam(BRIZO_CAN::WheelConfig param, bool val){
	if(val)
		_config |= 1UL << param;
	else
		_config &= ~(1UL << param);
}

//void WheelCommon::updateEEPROM(){
//	BRIZO_CAN::WheelEEPROMInfo eepromInfo;
//	eepromInfo.recordsWritten = 0;
//	if(this->getWheelLowPower()){
//		this->SendWarning(BRIZO_CAN::wheelWarning_EEPROMWriteSkipped);
//	}else if(this->checkConfigParam(BRIZO_CAN::wheelConfig_enableEEPROM)){ //only write if enabled
//		_memory.updateValue(WheelMemory::ee_config, _config);
//		_memory.updateValue(WheelMemory::ee_configBackup, _config);
//		eepromInfo.recordsWritten = _memory.writeEEPROM();
//	}
//	eepromInfo.writeCount = _memory.getWriteCount();
//
//	this->writeCANMessage(makeMessage(BRIZO_CAN::WHEEL_EEPROM_WRITE_INFO.ID, eepromInfo));
//}
