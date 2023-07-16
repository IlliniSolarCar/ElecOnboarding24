/*
 * common.h
 *
 *	This is the wheel common class, with a base of hardware_common_mbed
 *	It adds in common functions for the wheel and some wrappers to common
 *	functions to make them fit better into the wheel firmware
 *
 *  Created on: Nov 25, 2020
 *      Author: Jonathan
 */

#include <mbed.h>
#include <hardware_common_mbed.h>
#include <CAN/can_data.h>
#include "setup.h"
#include "pins.h"

#ifndef WHEEL_COMMON_H_
#define WHEEL_COMMON_H_

class WheelCommon : public hardware_common_mbed {
public:

	/*
	 * Create the common object and provide the needed external objects
	 * @param _timer - timer object for time functions
	 * @param _can - can bus object for communication
	 * @param _wdt - watchdog timer object for watchdogs
	 * @param _timing - timing common object
	 */
	WheelCommon(Timer* _timer, CAN* _can, TimingCommon& _timing);

	/*
	 * Initialize common hardware/functions, call as the first init function
	 * Setups CAN, LEDs, config, and sends relevant can info
	 */
	void init();

	/*
	 * Call last thing before starting the main logic loop to start the timing for the loop
	 * Sends relevant info about starting on CAN
	 */
	void start();

	/*
	 * Send CAN Message indicating the provided warning
	 * If the enum passed in is wheelWarning_none then it will not send
	 * Thus you can always call this and just pass none or an actual warning
	 * @param warning - enum value of the warning
	 */
	void SendWarning(BRIZO_CAN::WheelWarnings warning);

	/*
	 * Send CAN Message indicating the provided error
	 * If the enum passed in is wheelError_none then it will not send
	 * Thus you can always call this and just pass none or an actual error
	 * @param error - enum value of the error
	 */
	void SendError(BRIZO_CAN::WheelErrors error);

	/*
	 * Send the version info of this board (HW, FW, CAN) over CAN
	 */
	void SendVersion();

	/*
	 * Send the current config of this board over CAN
	 */
	void SendConfig();

	/*
	 * Send the current operation mode of the board over CAN
	 */
	void SendOperationMode();

	/*
	 * Set the operation mode to the provided new mode. Will call SendOperationMode after changing
	 * Does not take any action to change behaviors
	 * @param newMode - the mode to change into
	 */
	void SetOperationMode(BRIZO_CAN::operationMode newMode);

	/*
	 * Get the current operating mode of the wheel
	 * @return the current mode enum value
	 */
	BRIZO_CAN::operationMode GetOperationMode() const;

	/*
	 * Override of the base class, adds filtering of messages
	 * @param msg - CAN Message object (use makeMessage)
	 * @return int value: 0 - success, 1 failed to send, -1 did not send due to filter
	 */
	int writeCANMessage(CANMessage msg);

	/*
	 * Set a config param, doesn't take any action to change things based on this
	 * 		should be called by the function that does take those actions
	 * 		or the affected functionality should call checkConfigParam when run
	 * Certain read only params cannot be set with this method and will silently fail
	 * @param param - the parameter enum value to set
	 * @param val - the boolean value to set this param to
	 * @param sendCAN - if we should send a CAN message to note this update. Default to true
	 * 						change to false when setting multiple in quick succession
	 */
	void setConfigParam(BRIZO_CAN::WheelConfig param, bool val, bool sendCAN = true);

	/*
	 * Set multiple config params at once, will send CAN message at end of setting them all
	 * @param toSet - bitmap of which params are being set, see enum in Brizo Can
	 * @param values - values to set the params to, ones not indicated in toSet are ignored
	 */
	void setConfigParams(uint32_t toSet, uint32_t values);

	/*
	 * Check if a config param is set or not
	 * @param param - the enum value of the parameter to check
	 * @return boolean value of if the param is set
	 */
	bool checkConfigParam(BRIZO_CAN::WheelConfig param) const;

	/*
	 * Set lower power mode status
	 * @param lowPower - true if in low power, false if not
	 */
	void setWheelLowPower(bool lowPower);

	/*
	 * Return lower power mode status
	 * @return true if low power, false if normal
	 */
	const bool getWheelLowPower();

	/*
	 * Updated config records and writes all changed records to EEPROM
	 * This function will take notable time, see WheelMemory.h for details
	 * Also sends EEPROM info on CAN.
	 * Will not write or send CAN info if in Low Power mode, instead will send warning
	 */
	void updateEEPROM();

private:

	TimingCommon& _timing;

	// Wheel is in normal operation by default
	bool _wheelLowPower = false;

	/*
	 * Internal helper for sending can message
	 * @param msg - CAN Message Object
	 * @return int 0 success, 1 fail
	 */
	int _sendCANMessage(CANMessage msg);

	/*
	 * Checks if the specified id is of a CAN message that is only for debug purposes
	 * @param id - message id
	 * @return boolean if debug message
	 */
	bool _isDebugMessage(int id) const;

	/*
	 * Internal helper method to set config param, can set the "read only" ones.
	 * @param param - the param to set
	 * @param val - the boolean value to set the param to
	 */
	void _setConfigParam(BRIZO_CAN::WheelConfig param, bool val);

	/*
	 * Current configuration of the wheel
	 */
	uint32_t _config = 0;

	/*
	 * Current operation mode of the wheel
	 */
	BRIZO_CAN::operationMode _wheelOperationMode = BRIZO_CAN::operationMode_startUp;

};

#endif /* INC_WHEEL_HARDWARE_H_ */
