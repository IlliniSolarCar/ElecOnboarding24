/*
 * This is where all #defines that change the behavior of the system should be.
 * This file is essentially a set-up procedure to make the system function a certain way.
 *	For example this may include the #define for whether to display speed in mph or kph
 *	It could also includes the rate to blink the turn signals. Any functionality of the system
 *	that can be changed should changeable here.
 */

#ifndef MBED15X9_SKELETON_SETUP_H_
#define MBED15X9_SKELETON_SETUP_H_

#define DEFAULT_CONFIG  0b1001000010000
#define CAN_DEBUG_ID_THRESHOLD	0x400


//how often to check if the CAN controller is working
#define CHECK_CAN_RATE_US 500000

//how long without a feed for watch dog timer to trigger a reset
//be warned this oscialltor is only accurate +/- 40% so make this time bigger than you think you need
#define WDT_TIMEOUT_US 10000000

//task 1 rate
#define TASK_1_RATE_US 1000000

// DATA CALCULATION CONSTANTS
#define PI 			3.14159
#define WHEEL_RAD	0.278   //279 mm radius for 95/80 tire
#define WHEEL_CIR	2 * PI * WHEEL_RAD  // circumference

//Wheel 7 segment display default brightness
#define DISPLAY_DEFAULT_BRIGHTNESS 0x05
constexpr uint8_t SEVEN_SEG_BRIGHTNESS[8] = {75, 90, 110, 130, 150, 170, 190, 220};

//Rate to update data on 7-Segment display
#define LED_DISPLAY_RATE_US 	600000

//Wheel 7 segment display timeout when not getting data
#define WHEEL_DISPLAY_TIMEOUT_US	5000000

#define OLED_REFRESH_RATE 100000


#endif /* SETUP_H_ */
