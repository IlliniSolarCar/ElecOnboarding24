/*
 * This is where your main program code lives. On reset, after some basic
 * initialization code is run, main() is called.
 */

#include <mbed.h>
// PROJECT 1 - Include something here!
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
	common.setupCAN();
	//set up LEDs and turn them all off
	common.setupLEDs(&led1, &led2, &led3, &led4);

	//Set Callbacks:
	//These are side tasks (up to 8) that are run independently of the main
	//algorithm / purpose of this board such as the heartbeat.
	timing.addCallback(BRIZO_CAN::DEMO_HEART.RATE / 2, heartbeat);
	timing.addCallback(CHECK_CAN_RATE_US, checkCANController);

	bool wdt_reset;
	//start the timing and check for wdt caused reset
	common.startTimingCommon(&timing, &wdt_reset);

	//if watchdog caused reset do something (probably log on CAN)
	if(wdt_reset){

	}
}

/*
 * The shutdown function may not be required in all projects.
 * Think about what may be needed to be done in case of a car shutdown
 * Typically this may include alerts, turning off things (to avoid hard off), or disconnecting HV parts
 * Don't forget to feed the WDT to avoid a reset!
 */
void shutdown_method() {

	while(1) {
		wdt.feed();
	}
}

int main() {
	// Configure all of our peripherals and globals
	setup();
	uint32_t last_task_1_time = timing.onTick(NULL);

	CANMessage msg;
	bool shutdown = false;
	// Main functionality
	while (!shutdown) {

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

        if(timing.tickThreshold(last_task_1_time, TASK_1_RATE_US)){
        	//PROJECT 1 - add code here to actually make the LED blink
        	if(led0.read() == 0){
        		led0.write(1);
        	}
        	else{
        		led0.write(0);
        	}
        }

        //PROJECT 2 - use the potentiometer to change the blink rate


	}

	shutdown_method();
}
