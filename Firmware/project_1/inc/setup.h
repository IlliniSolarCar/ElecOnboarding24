/*
 * This is where all #defines that change the behavior of the system should be.
 * This file is essentially a set-up procedure to make the system function a certain way.
 *	For example this may include the #define for whether to display speed in mph or kph
 *	It could also includes the rate to blink the turn signals. Any functionality of the system
 *	that can be changed should changeable here.
 */

#ifndef MBED15X9_SKELETON_SETUP_H_
#define MBED15X9_SKELETON_SETUP_H_

//how often to check if the CAN controller is working
#define CHECK_CAN_RATE_US 500000

//how long without a feed for watch dog timer to trigger a reset
//be warned this oscialltor is only accurate +/- 40% so make this time bigger than you think you need
#define WDT_TIMEOUT_US 10000000

//task 1 rate
// PROJECT 1 - You can change the macro name to something more descriptive if you'd like
#define BLINK_RATE_US 1000000



#endif /* SETUP_H_ */
