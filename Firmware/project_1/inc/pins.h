/*
 * This is where you should declare any simple inputs/outputs, like
 * instances of DigitalOut, DigitalIn, AnalogIn, PwmOut, InterruptIn
 * which you might pass in as arguments to more complicated peripherals
 * or use directly.
 *
 * If using macros for pin names do so like so:
 * #define P_LED_FOO P2_4
 *
 * You should place those definitions here.
 */

#ifndef MBED15X9_SKELETON_PINS_H_
#define MBED15X9_SKELETON_PINS_H_

#include <mbed.h>

/*
 *    COMMON PIN DEFINITIONS
 *    UPDATE FOR EACH BOARD!
 */
#define P_CAN_rd P0_13
#define P_CAN_td P0_18
#define P_LED1 P0_9
#define P_LED2 P0_5
#define P_LED3 P0_6
#define P_LED4 P0_7
// PROJECT 1 - You can define a pin macro here
#define P_LEDmain P0_4
#define P_POT1 P0_10 // what is the potentiometer pin???

/*
 * COMMON PIN OBJECT DECLARATIONS
 */

extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;
extern DigitalOut led4;
// PROJECT 1 - You can declare a DigitalOut object here

/*
 * BOARD SPECIFIC PINS
 */
extern DigitalOut ledmain;

// PROJECT 2 - You can declare a AnalogIn object here
extern AnalogIn pot1;


/*
 * BOARD SPECIFIC PIN OBJECT DECLARATIONS
 */





#endif // __MBED1549_SKELETON_PINS_H__
