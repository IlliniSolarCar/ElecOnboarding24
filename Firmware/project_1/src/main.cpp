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
#include "pins.h"

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
	bool hbled_is_on=false;
	float voltage;
	int timing=TASK_1_RATE_US;

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





        if(timing.tickThreshold(last_task_1_time, timing)){
        	//PROJECT 1 - add code here to actually make the LED blink
        	if (hbled.read()){
        		hbled.write(0);
        		hbled_is_on = false;
        	}
        	else{TASK_1_RATE_US
        		hbled.write(1);
        		hbled_is_on = true;
        	}

        }

        //PROJECT 2 - use the potentiometer to change the blink rate


        /* Krishna's notes/thought process on the code;
         * Set two variables on lines 83 and 84 for the voltage and the timing value. The previously used variable for timing, TASK_1_RATE_US, is a private variable and can't be edited.
         * To adjust this timing value, multiply it by 10 times the float value of the voltage from the potentiometer, then cast to an int, since the variable timing is an int.
         * The timing value is reset to its default before every repetition, so timing is only dependent on the voltage, not the previous timing value.
         * For example, timing is initially 1000000. If the voltage is set to 0.3 on the potentiometer, the new timing value will be 0.3*10*1000000 which is 3000000.
         * If the voltage value is now changed to 0.4, the new value will not be 0.4*10*1000000, but it will be 0.4*10*30000000. So timing is set to 10000000 before every cycle.
         */
        voltage=ptmtr.read();
        timing=TASK_1_RATE_US;
        timing=(int)timing*voltage*10;





	}

	shutdown_method();
}
