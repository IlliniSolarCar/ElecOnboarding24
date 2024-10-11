
#include <mbed.h>
// PROJECT 1 - Include something here!
#include "peripherals.h"
#include "can_struct.h"
#include "CAN/can_id.h"
#include "CAN/can_data.h"
#include "can_buffer.h"
#include "led_blinker"cs



void heartbeat() {
	if(common.toggleHeartbeatLED())
		common.writeCANMessage(makeMessage(BRIZO_CAN::DEMO_HEART.ID, timer.read_us()));
}
void checkCANController() {
    common.checkCANController();
}

void setup() {

	common.setupCAN();
	common.setupLEDs(&led1, &led2, &led3, &led4);

	timing.addCallback(BRIZO_CAN::DEMO_HEART.RATE / 2, heartbeat);
	timing.addCallback(CHECK_CAN_RATE_US, checkCANController);
	bool wdt_reset;

	common.startTimingCommon(&timing, &wdt_reset);

	if(wdt_reset){
	}
}

void shutdown_method() {
	while(1) {
		wdt.feed();
	}
}
int main() {

	setup();
	uint32_t last_task_1_time = timing.onTick(NULL);
	CANMessage msg;
	bool shutdown = false;

	while (!shutdown) {

		double blink_rate = potentiometer.read() * 1000000;

        bool overflow;
        uint32_t now = common.loopTime(&timing, &overflow);

        while(!common.readCANMessage(msg)) {

        	common.toggleReceiveCANLED();
        }

        if(timing.tickThreshold(last_task_1_time, TASK_1_RATE_US)){
        if(timing.tickThreshold(last_task_1_time, blink_rate)){
        	led5.write(not led5.read());

        }


	}
	shutdown_method();
}
