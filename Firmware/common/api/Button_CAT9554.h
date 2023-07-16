/*
 * Button_CAT9554.h
 *
 *  Created on: March 24, 2021
 *      Author: Rohan Kamatar
 *      Adapted from Button.h by Jonathan Mullen
 */

#include <mbed.h>
#include <CAT9554.h>

#ifndef COMMON_API_BUTTON_CAT9554_H_
#define COMMON_API_BUTTON_CAT9554_H_

class Button_CAT9554 {
public:
	enum mode{
		activeLow = 0,
		activeHigh = 1
	};

    /**
     * Set up the button object.
     * @param buttonIn - integer for the address of the button on the IO expander
     * @param IO - CAT9954 object the is connected to the button
     * @param debounce_level - how many consecutive readings required to change active status
     * @param mode - active mode (active high or low) for button.
     * @param initActive - if the button should start active or inactive
     */
	Button_CAT9554(uint8_t buttonIn,  CAT9554& IO, uint8_t debounce_level = 3, Button_CAT9554::mode mode = activeLow, bool initActive = false);

    /**
     * Take a single reading from the Digital Input and return the raw reading
     * Call this function at the desired sampling rate of the button
     * @param time - the current time in us
     * @return raw read (not debounced) true on active, false on inactive
     */
	bool read(uint32_t time);

    /**
     * Return if the button has been pressed since last checked
     * Check regularly to clear status, even if value is only required sometimes
     * @return true if pressed, false if not
     * @sideeffect - clears pressed status
     */
	bool onPress();

	/**
	 * Return if the button has been released since last checked
	 * Check regularly to clear status, even if value is only required sometimes
	 * @param activeTime - uint16_t pointer. If return value is true this will contain the
	 *                     time (in ms) the button was active before release. (Optional)
	 * @return true if released, false if not
	 * @sideeffect - clears released status
	 */
	bool onRelease(uint16_t *activeTime = nullptr);

	/**
	 * How long the button has been active, if active
	 * Guaranteed to be non-zero if button is active and 0 if inactive
	 * Time caps at 65.5 seconds, no wrap
	 * @return how long the button has been active for in milliseconds
	 */
	uint16_t getActiveTime();

	/**
	 * Reset the button, clearing any counts. Set the active state and debounce level
	 * @param debounce_level - how many consecutive readings required to change active status
	 * @param time - current time, required to set active state to non-false
	 * @param initActive - if the button should start active or inactive
	 */
	void reset(uint32_t time = 0, bool initActive = false);
	void reset(uint8_t debounce_level, uint32_t time = 0, bool initActive = false);

private:

	//Input object and settings
	uint8_t _buttonIn;
	CAT9554& _IO;
	uint8_t _debounceLevel;
	mode _activeMode;

	// Hold Timing
	uint32_t _startTime = 0;
	uint16_t _heldTime = 0;
	uint16_t _releasedActiveTime = 0;

	// store presses and releases
	bool _press = false;
	bool _release = false;

	// Count active/inactive readings
	uint8_t _count = 0;

	//track state
	bool _active = false;

	/*
	 * Calculate and store the current time it has been held active
	 * @param currentTime - the current time
	 */
	void _setHoldTime(const uint32_t currentTime);

	/*
	 * Update all data needed in event of active mode changing.
	 * @param the current time
	 */
	void _toggleActive(const uint32_t currentTime);

};

#endif /* COMMON_API_BUTTON_CAT9554_H_  */
