/*
 * This is where you should instantiate any simple inputs/outputs, like
 * instances of DigitalOut, DigitalIn, AnalogIn, PwmOut, InterruptIn
 * which you might pass in as arguments to more complicated peripherals
 *
 */

#include <mbed.h>
#include <pins.h>

/*
 * PIN OBJECT INSTANTIATIONS
 */

// PROJECT 2 - You can instantiate your AnalogIn object here
AnalogIn potentiometer(P_POTENTIOMETER);
/*
// PROJECT 1 - You can instantiate your DigitalOut object here
*/
DigitalOut led1(P_LED1);
