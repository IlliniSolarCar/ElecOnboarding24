/*
 * hardware_common_mbed.h
 * mbed-based implementation of hardware_common.
 * Compare to unit testing implementation of hardware_common.
 *
 *  Created on: Jan 10, 2016
 *      Author: edwardw (calsol)
 *  Updated on: 17 Sept, 2019
 *  	Author: Jonathan Mullen
 */

#ifndef COMMON_API_HARDWARE_COMMON_MBED_H_
#define COMMON_API_HARDWARE_COMMON_MBED_H_

#include <mbed.h>
#include <can_buffer.h>
#include <hardware_common.h>

class hardware_common_mbed : public hardware_common {
public:
    /**
     * Create a new instance of mbed implementation of hardware_common.
     * @param _timer Pointer to Timer object (required)
     * @param _can Pointer to CAN object, or null if this board does not use CAN
     * @param _wdt Pointer to WDT object Null if no WDT
     */
    hardware_common_mbed(Timer* _timer, CAN* _can = NULL, WDT* _wdt = NULL);
    virtual ~hardware_common_mbed();

    /** Helper function to handle a CAN message interrupt. */
    void handleCANMessage();

    virtual void setupCAN(void);
    virtual void startTimingCommon(TimingCommon* timing, bool* wdtReset);
    virtual int readCANMessage(CANMessage& msg);
    virtual int writeCANMessage(CANMessage msg);
    virtual bool checkCANController(void);
    virtual void setupLEDs(DigitalOut* heartbeatLED, DigitalOut* receiveCANLED, DigitalOut* sendCANLED, DigitalOut* hardwarestatusLED);
    virtual int toggleHeartbeatLED(void);
    virtual int toggleReceiveCANLED(void);
    virtual int toggleSendCANLED(void);
    virtual int toggleHardwareLED(void);
    virtual int toggleHardwareLED(bool on);
    virtual int loopTime(TimingCommon* timing, bool* outOverflow);

private:
    // 32-message buffer.
    CANRXTXBuffer<32, 16>* p_canBuffer;

    CAN* p_can;
    Timer* p_timer;
    WDT* p_wdt;
    DigitalOut* p_heartbeatLED;
    DigitalOut* p_receiveCANLED;
    DigitalOut* p_sendCANLED;
    DigitalOut* p_hardwareLED;
};

#endif /* API_HARDWARE_COMMON_MBED_H_ */
