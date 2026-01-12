/*
 * hardware_common.h
 * Common hardware interaction functionalities, including CAN, LEDs, etc.
 *
 *  Created on: Jan 10, 2016
 *      Author: edwardw  (calsol)
 *
 *  Updated on: 17 Sept 2019
 *  	Author: Jonathan Mullen
 */

#ifndef COMMON_API_HARDWARE_COMMON_H_
#define COMMON_API_HARDWARE_COMMON_H_

#include <CAN/can_id.h>
#include <TimingCommon.h>
#include <CAN.h>
#include <WDT.h>

// Note: for CAN applications, include either CAN.h (HW) or can_lite.h (SW)

/**
 * Representation of common board interfaces.
 */
class hardware_common {
public:
    hardware_common() {};
    virtual ~hardware_common() {};
    /**
     * Set up the CAN controller.
     */
    virtual void setupCAN(void) = 0;

    /**
     * Start timing functionality.
     * @param timing class to start
     * @param pointer to bool that will indicate whether the last reset was WDT caused
     */
    virtual void startTimingCommon(TimingCommon* timing, bool* wdtReset) = 0;

    /**
     * Read a CANMessage from the board.
     *
     * @param msg CANMessage to be written
     * @return 0 on success, 1 on failure
     */
    virtual int readCANMessage(CANMessage& msg) = 0;

    /**
     * Write a CANMessage to the board.
     *
     * @param msg A CANMessage to write.
     * @return 0 on success, 1 on failure
     */
    virtual int writeCANMessage(CANMessage msg) = 0;

    /**
     * Check if the CAN controller is alive or not. If it isn't, reset the
     * controller.
     * @return True if the CAN controller was alive; false if it was not and
     *         needed to be reset.
     */
    virtual bool checkCANController(void) = 0;

    /**
     * Set up LEDs (initialize them to all off).
     */
    virtual void setupLEDs(DigitalOut* heartbeatLED, DigitalOut* receiveCANLED, DigitalOut* sendCANLED, DigitalOut* hardwarestatusLED) = 0;

    /**
     *  Toggle the heartbeat LED
     *  @return 0 if LED off, 1 if LED on
     */
    virtual int toggleHeartbeatLED(void) = 0;

    /**
     *  Toggle the CAN Receive LED
     *  @return 0 if LED off, 1 if LED on
     */
    virtual int toggleReceiveCANLED(void) = 0;

    /**
     *  Toggle the CAN Send LED
     *  @return 0 if LED off, 1 if LED on
     */
    virtual int toggleSendCANLED(void) = 0;

    /**
     *  Toggle or set the hardware status LED
     *   @param on boolean to set the LED to, true = on
     *   @return 0 if LED off, 1 if LED on
     *
     */
    virtual int toggleHardwareLED(void) = 0;
    virtual int toggleHardwareLED(bool on) = 0;

    /*
     * Handle timing related tasks for the main loop
     * @param timing common class being used for this loop
     * @param bool pointer where overflow status will be put
     * @return int time running     *
     */
    virtual int loopTime(TimingCommon* timing, bool* outOverflow) = 0;
};

#endif /* API_HARDWARE_COMMON_H_ */
