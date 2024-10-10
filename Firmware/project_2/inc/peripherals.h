/*
 * Peripherals that require more initialization that setting their pins
 * or that are otherwise bound to multiple pins should be declared here with
 * extern so that other files can reference them.
 * Make sure to #include the required *.h files when declaring various
 * peripherals.
 */

#ifndef MBED15X9_SKELETON_PERIPHERALS_H_
#define MBED15X9_SKELETON_PERIPHERALS_H_

#include <mbed.h>
#include <pins.h>
#include <hardware_common_mbed.h>
#include <TimingCommon.h>
#include "setup.h"


// The extern keyword allows code that imports peripherals.h to use the variables
// defined here. Functions and structs have an implicit extern.
extern CAN can;
extern Timer timer;
extern WDT wdt;
extern hardware_common& common;
extern TimingCommon timing;


#endif // __MBED1549_SKELETON_PERIPHERALS_H__
