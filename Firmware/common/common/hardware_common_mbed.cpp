/*
 * hardware_common_mbed.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: edwardw (calsol)
 *  Updated on:  17 Sept, 2019
 *  	Author: Jonathan Mullen
 */

#include "hardware_common_mbed.h"

hardware_common_mbed::hardware_common_mbed(Timer* _timer, CAN* _can, WDT* _wdt) {
    p_timer = _timer;
    p_can = _can;
    p_canBuffer = new CANRXTXBuffer<32, 16>(*_can); //TODO remove dynamic allocation
    p_wdt = _wdt;
}

hardware_common_mbed::~hardware_common_mbed() {
    p_timer = NULL;
    delete p_canBuffer;
    p_canBuffer = NULL;
    p_can = NULL;
}

static CANRXTXBuffer<32, 16>* _handleCANMessageBuffer = NULL;
// handleCANMessage is attached to the CAN RX interrupt.
void _handleCANMessage() {
    _handleCANMessageBuffer->handleIrq();
}

void hardware_common_mbed::setupCAN(void) {
    p_can->frequency(CAN_FREQUENCY);
    _handleCANMessageBuffer = p_canBuffer;
    p_can->attach(_handleCANMessage, CAN::RxIrq);
    p_can->attach(_handleCANMessage, CAN::TxIrq);
}

void hardware_common_mbed::startTimingCommon(TimingCommon* timing, bool* wdtReset) {
    *wdtReset = p_wdt->causedReset();
	timing->start(p_timer);
    p_wdt->enable();
}

int hardware_common_mbed::readCANMessage(CANMessage& msg) {
    return p_canBuffer->read(msg) != 1; // 1=failure
}

int hardware_common_mbed::writeCANMessage(CANMessage msg) {
    return p_canBuffer->write(msg) != 1; // 1=failure
}

bool hardware_common_mbed::checkCANController() {
	//implemented for LPC15xx only!
	if (LPC_C_CAN0->CANCNTL & (1 << 0)) {
			LPC_C_CAN0->CANCNTL &= ~(1 << 0);
			return false;
	}

    return true;
}

void hardware_common_mbed::setupLEDs(DigitalOut* heartbeatLED, DigitalOut* receiveCANLED, DigitalOut* sendCANLED, DigitalOut* hardwareLED) {
	p_heartbeatLED = heartbeatLED;
	p_receiveCANLED = receiveCANLED;
	p_sendCANLED = sendCANLED;
	p_hardwareLED = hardwareLED;

	*p_heartbeatLED = *p_receiveCANLED = *p_sendCANLED = *p_hardwareLED = 0;

}

int hardware_common_mbed::toggleHeartbeatLED(){
	*p_heartbeatLED = !*p_heartbeatLED;
	return *p_heartbeatLED;
}

int hardware_common_mbed::toggleReceiveCANLED(){
	*p_receiveCANLED = !*p_receiveCANLED;
	return *p_receiveCANLED;
}

int hardware_common_mbed::toggleSendCANLED(){
	*p_sendCANLED = !*p_sendCANLED;
	return *p_sendCANLED;
}

int hardware_common_mbed::toggleHardwareLED(){
	*p_hardwareLED = !*p_hardwareLED;
	return *p_hardwareLED;
}

int hardware_common_mbed::toggleHardwareLED(bool on){
	*p_hardwareLED = on;
	return *p_hardwareLED;
}

int hardware_common_mbed::loopTime(TimingCommon* timing, bool* isOverflow){
	p_wdt->feed();
	return timing->onTick(isOverflow);
}
