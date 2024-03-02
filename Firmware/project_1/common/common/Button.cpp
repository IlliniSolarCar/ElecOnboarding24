/*
 * Button.cpp
 *
 *  Created on: Apr 1, 2020
 *      Author: Jonathan
 */

#include <Button.h>

Button::Button(DigitalIn& ButtonIn, uint8_t debounce_level, Button::mode mode, bool initActive)
	: _buttonIn(ButtonIn), _debounceLevel(debounce_level), _activeMode(mode), _active(initActive) { }

bool Button::read(const uint32_t time){
	bool ret = false;

	//increment count as appropriate
	if(_activeMode == _buttonIn.read()){
		ret = true;
		!_active ? _count++ : _count = 0;
	}else{
		_active ? _count++ : _count = 0;
	}

	//if debounce level toggle state
	if(_count >= _debounceLevel){
		this->_toggleActive(time);
		_count = 0;
	}

	this->_setHoldTime(time);
	return ret;
}

bool Button::onPress(){
	bool ret = _press;
	_press = false;
	return ret;
}

bool Button::onRelease(uint16_t *activeTime /* = nullptr */){
	bool ret = _release;
	if(ret && activeTime)
		*activeTime =  _releasedActiveTime;

	_release = false;
	return ret;
}

uint16_t Button::getActiveTime(){
	return _heldTime;
}

void Button::reset(uint8_t debounce_level, uint32_t time, bool initActive){
	_debounceLevel = debounce_level;
	this->reset(time, initActive);
}

void Button::reset(uint32_t time, bool initActive){
	_startTime = time;
	_heldTime = _releasedActiveTime = 0;
	_press = _release = false;
	_count = 0;
	_active = initActive;
}

void Button::_setHoldTime(const uint32_t currentTime){
	if(!_active){
		_heldTime = 0;
		return;
	}

	uint16_t newHeldTime;
	if(currentTime >= _startTime)
		newHeldTime = (uint16_t)((currentTime - _startTime) / 1000);
	else
		newHeldTime = (uint16_t)((_startTime + (UINT32_MAX - currentTime)) / 1000);

	// Don't wrap, stay at MAX
	if(newHeldTime < _heldTime)
		_heldTime = UINT16_MAX;
	//Don't return 0 when button is held down
	else if(newHeldTime == 0)
		_heldTime = 1;
	else
		_heldTime = newHeldTime;
}

void Button::_toggleActive(const uint32_t currentTime){
	_active = !_active;

	if(_active){
		_startTime = currentTime;
		_press = true;
	}else{
		_release = true;
		_releasedActiveTime = _heldTime;
		_startTime = _heldTime = 0;
	}
}
