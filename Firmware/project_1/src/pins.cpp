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
AnalogIn potentiometer1(P_POT1);
/*
 * COMMON PIN OBJECT INSTANTIATIONS
 */

DigitalOut led1(P_LED1);
DigitalOut led2(P_LED2);
DigitalOut led3(P_LED3);
DigitalOut led4(P_LED4);
// PROJECT 1 - You can instantiate your DigitalOut object here
DigitalOut led5(P_LED5);
