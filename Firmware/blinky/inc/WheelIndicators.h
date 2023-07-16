/*
 * WheelIndicators.h
 *
 * This handles the 7-segment display and lights indicators on the wheel
 * Intended for asynchronous update of 7-segment display data.
 * Data can be passed to this class at any time, call writeDisplay to update 7 segs.
 *
 *  Created on: Apr 15, 2020
 *      Author: Jonathan
 */

#ifndef WHEEL_WHEELINDICATORS_H_
#define WHEEL_WHEELINDICATORS_H_

#include <mbed.h>
#include "pins.h"
#include "setup.h"
#include "PCA9745b.h"
#include "TimingCommon.h"
#include "can_struct.h"
#include "common.h"

const float KMHtoMPH = 0.621371;

class WheelIndicators {
public:
	/*
	 * Create the wheel indicators class for handling 7 segment leds and indicator leds
	 * @param SPI - spi object for PCA9745b communication
	 * @param common - Wheel Common Object
	 */
	WheelIndicators(SPI& spi, WheelCommon& common);

	/*
	 * Initialize all the LEDs. Everything will be off.
	 * @return errors from PCA974b initialization (0 if no error)
	 */
	uint8_t init();

	/*
	 * Turn the hazard indicators on or off
	 * @param on - whether or not the hazards are on
	 */
	void hazards(bool on);

	/*
	 * Turn the left turn signal indicator on or off
	 * @param on - whether or not the left Turn Signal is on
	 */
	void leftTurnSignal(bool on);

	/*
	 * Turn the right turn signal indicator on or off
	 * @param on - whether or not the right Turn Signal is on
	 */
	void rightTurnSignal(bool on);

	/*
	 * Turn the head light indicator on or off
	 * @param on - whether or not the headlights are on
	 */
	void headLights(bool on);

	/*
	 * Turn the cruise light indicator on or off
	 * @param on - whether or not cruise is on
	 */
	void cruiseLights(bool on);

	/*
	 * Records the speed of the car for display on the 7 segment display
	 * @param rpm - speed in RPM
	 * @param time - current time
	 */
	void setSpeed(uint32_t rpm, const uint32_t time);

	/*
	 * Records the voltage of the battery for display on the 7 segment display
	 * @param voltage - the voltage in tenths of a mV
	 * @param time - current time
	 */
	void setVoltage(uint32_t voltage, const uint32_t time);

	/*
	 * Set the current time to the nearest minute
	 * @param current hour (24 hr)
	 * @param current minute
	 */
	void setTime(const uint8_t hour, const uint8_t minute);

	/*
	 * Increment time by one minute
	 */
	void tickMinute();


	enum sevenSegMode {
		displaySpeed,
		displayVoltage,
		displayTime
	};
	/*
	 * Set the mode for what to display on the 7 segment display
	 * @param mode - the display mode
	 */
	void setMode(sevenSegMode mode);

	/*
	 * Public wrapper to Write to the 7 segment display
	 * Will display data based on the last set display mode
	 * Checks if the wheel is in low power mode and changes the brightness accordingly
	 * @param time - current time
	 * @return see _writeDisplay
	 */
	uint8_t writeDisplay(const uint32_t time);

	/*
	 * Set the brightness of the seven segment display
	 * @param brightness - the desired brightness level
	 */
	void setDisplayBrightness(uint8_t brightness);

	/*
	 * Update the brightness of the display from Config
	 */
	void updateBrightness();

	/*
	 * Check for 7-seg open/short circuit errors
	 * Send CAN messages (as necessary) indicating which LEDs have such errors
	 * Although method should be called periodically to check for errors, will only send a CAN message once per faulty LED
	 * @return bool - 1 if error, 0 if no errors
	 */
	bool sendCktErrors();

	/*

	 * Enable/Disable all 7-seg LEDs
	 * After enabling LEDs, the output will display dashes until displayable data is received
	 * @param on - true if enabling all LEDs, false if disabling all
	 */
	void enableAll(bool on);
	/*
	 * Test a single segment on all the 7 segment displays
	 * Do not also call write display when using this!
	 * @param led - the led strip to test on each 7 segment display
	 * 					simultaneously. 0 - 7 is DP, C, D, E, G, F, A, B
	 * 					led >= 8 is all off
	 * 					https://en.wikipedia.org/wiki/Seven-segment_display_character_representations#/media/File:7_segment_display_labeled.svg
	 * @return PCA9745b setOutput() return value
	 */
	uint8_t testDisplays(uint8_t led);



private:

	// Wheel Common Object
	WheelCommon& _common;

	/* LED Indicators */
	DigitalOut _leftTurnLED;
	DigitalOut _rightTurnLED;
	DigitalOut _headLightLED;
	DigitalOut _parkingLightLED;

	/* 7 Segment Display */
	DigitalOut _sevenSegCS;
	DigitalOut _sevenSegReset;
	DigitalOut _sevenSegEn;
	PCA9745b <uint32_t> _sevenSegment;
	const int _deviceCount = 2;
	sevenSegMode _mode = displaySpeed;
	uint8_t brightnessLevel = 99; //init to invalid number

	/*
	 * Saved data for 7 segment. Used to display when write is called
	 */
	float _speed = -1;
	float _voltage = -1;
	float _time = -1;
	uint32_t _lastSpeedTime;
	uint32_t _lastVoltageTime;
	bool _timeKnown = false;

	/*
	 * Track statuses of each
	 * They can be on at the same time and we need to track
	 * If one turns off we will need to know to keep the LED on
	 * due to the other
	 */
	bool _hazardStatus = false;
	bool _leftTurnStatus = false;
	bool _rightTurnStatus = false;

	/*
	 * Update the blinking outputs to the turn LEDs
	 */
	void _updateTurnLEDs();

	/*
	 * 7 Segment Mapping from wheel v7.1
	 * same on each PCA9745b. Each has 2x 7 segment displays - upper and lower
	 * following standard 7 Segment Display segment letter convention
	 */
	enum _sevenSegMap{
		upperG = 0,
		upperF,
		upperA,
		upperB,
		lowerG,
		lowerF,
		lowerA,
		lowerB,
		lowerDP,
		lowerC,
		lowerD,
		lowerE,
		upperDP,
		upperC,
		upperD,
		upperE
	};

	/*
	 * Format the data to write to the 7 segment display
	 * @param data - the data to write to the display
	 * 					will display dashes for negative numbers
	 * @param decimalCount - how many decimal digits there are
	 * @param showDecimalPoint - if the decimal point should be on
	 * @param showDecimalDigits - if the decimal digits should be shown
	 * @return see PCA9745b setOutput()
	 */
	uint8_t _writeDisplay(float data, uint8_t decimalCount = 1, bool showDecimalPoint = false, bool showDecimalDigits = false);

	/*
	 * Helper function to actual translate numbers to the bits on the 7-seg.
	 * Designed for the output scheme of wheel v7.1 with single PCA8745b for 2 displays
	 * Does not handle the decimals. Will not show anything if number > 9 is passed in
	 * @param upperNum - the number for the upper display
	 * @param lowerNum - the number for the lower display
	 */
	uint16_t _writeSingleDisplayHelper(uint8_t upperNum, uint8_t lowerNum);

};

#endif /* WHEEL_WHEELINDICATORS_H_ */
