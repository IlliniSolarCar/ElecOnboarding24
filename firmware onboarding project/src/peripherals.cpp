/*
 * Peripherals that require more initialization than setting their pins
 * or that are otherwise bound to multiple pins should be constructed here.
 * Make sure to #include the required *.h files when declaring various
 * peripherals.
 */

#include <mbed.h>
#include <peripherals.h>
#include <pins.h>

// A representation of the CAN controller. Unlike other microcontrollers,
// the CANTX/RX pins on the LPC1549 can be reassigned, so they
// do not have a traditional mbed pin-name.
// Set the CAN Pins for this board in pins.h

CAN can(P_CAN_rd, P_CAN_td);

// The mbed timer class used to keep track of when to do things.
Timer timer;
//Common timing class to include often used timing functions and handle the
//above timer by taking care of overflow and time comparisons
TimingCommon timing;

//Watchdog timer to reset board if it stops working
//this should be fed only in the main loop
WDT wdt(WDT_TIMEOUT_US);

// Common hardware methods to all boards - debug LEDs, timing classes, CAN
hardware_common_mbed common_(&timer, &can, &wdt);
hardware_common& common = common_;



