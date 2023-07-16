/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>


//int main(void) {
//	LPC_GPIO0->FIODIR |= (1 << 4);           /* LEDs on PORT0 */
//
//	  while(1)
//	  {
//		LPC_GPIO0->FIOSET = (1 << 4);
//		for(int i = 0; i < 100000; i++){}
//		LPC_GPIO0->FIOCLR = (1 << 4);
//		for(int i = 0; i < 100000; i++){}
//	  }
//}

/*
 * This is where your main program code lives. On reset, after some basic
 * initialization code is run, main() is called.
 */

#include <mbed.h>
#include "pins.h"
#include "peripherals.h"
#include "can_struct.h"
#include "CAN/can_id.h"
#include "CAN/can_data.h"
#include "can_buffer.h"


/*
 * This is an example function. It blinks the heartbeat LED and sends
 * a Heartbeat CAN Message. The message sends when the LED turns on.
 * The heartbeat CAN Message includes the uptime
 */
void heartbeat() {
	if(common.toggleHeartbeatLED())
		common.writeCANMessage(makeMessage(BRIZO_CAN::DEMO_HEART.ID, timer.read_us()));
}

/** Stub to call hardware-interface for checking the CAN controller. */
void checkCANController() {
    common.checkCANController();
}

/*
 * This is where basic, one-time configuration code is run before entering
 * normal operation. It is recommended that you keep your configuration
 * code in setup() and call it at the beginning of main(), but it is not
 * mandatory.
 *
 * If you have global variables that need to be initialized, here would
 * be a good place to do it.
 */
void setup() {

	//set up the CAN interrupts and handling.
	common.init();

	//Set Callbacks:
	//These are side tasks (up to 8) that are run independently of the main
	//algorithm / purpose of this board such as the heartbeat.
	timing.addCallback(BRIZO_CAN::DEMO_HEART.RATE / 2, heartbeat);

	wheelScreen.init();
	driverLeds.init();
	//start timing lol
	common.start();
	driverLeds.enableAll(true);
	common.SetOperationMode(BRIZO_CAN::operationMode_normal);
}

/*
 * The shutdown function may not be required in all projects.
 * Think about what may be needed to be done in case of a car shutdown
 * Typically this may include alerts, turning off things (to avoid hard off), or disconnecting HV parts
 * Don't forget to feed the WDT to avoid a reset!
 */
void shutdown_method() {

	while(1) {
//		wdt.feed();
	}
}

int main() {
	// Configure all of our peripherals and globals
	setup();
	uint32_t last_led_time = timing.onTick(NULL);
	uint32_t last_oled_time = timing.onTick(NULL);

	CANMessage msg;
	bool shutdown = false;
	// Main functionality
	while (!shutdown) {
        MUXEn = 0;
        MUXSel = 1;
		//on time overflow all callbacks will happen and timing reset to 0. Might be needed for other functions that rely on timing.
        bool overflow;
        uint32_t now = common.loopTime(&timing, &overflow);

        //clear CAN Buffer
        while(!common.readCANMessage(msg)) {
        	//you should do something with the relevant CAN messages here
        	//toggle the CAN receive LED for only the messages you need to
        	//receive for this board to function. This should be only a few
        	//total messages. Do nothing for irrelevant messages
        	common.toggleReceiveCANLED();
        }

        if(timing.threshold(last_led_time, now, LED_DISPLAY_RATE_US)){
        	driverLeds.testDisplays(0);
        	last_led_time = now;
        }
        if(timing.threshold(last_oled_time, now, OLED_REFRESH_RATE)){
        	wheelScreen.writeDisplay(now);
        	last_oled_time = now;
		}
	}

	shutdown_method();
}
