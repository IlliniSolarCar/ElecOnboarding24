/*
 * CANSerialInterface.h
 *
 * This converts and sends CAN messages in a serial format that
 * is the same format used by the Telemetry application. The format
 * utilizes COBS encoding so that the messages can be seperated and
 * decoded back into CAN messages
 * 
 *  Created on: Jan 16, 2021
 *      Author: John Han
 */
#ifndef COMMON_API_CANSERIALINTERFACE_H_
#define COMMON_API_CANSERIALINTERFACE_H_

#include <mbed.h>
#include <encoding.h>

class CANSerialInterface {
public:

    /**
     * Creates a CAN Serial Interface
     * @param uart the UART serial to interface with
     * @param the baud rate of the serial bus
     */ 
	CANSerialInterface(Serial& uart, int baudrate);

    /**
     * Transmits a CAN Message encoded on serial interface
     * @param msg The CAN message to send.
     * @returns 0 on success, 1 on failure
     */
	uint8_t sendMessage(const CANMessage& msg);
    
    /**
     * Reads last received CAN message on the UART
     * @returns 0 on success, 1 on cobs decode input failure, 2 on cobs decode overflow, 
     *          3 on checksum failure, 4 on invalid cobs decode, 5 on buffer overflow error, 
     *          6 for no new message or data, 7 for new data but no new message
     */ 
	uint8_t readMessage(CANMessage& msg);

	void resetBuffer();
protected:
    Serial& _uart;
private:
    uint8_t _inBuf[MAX_ENCODED_SIZE];
    uint32_t _inBufIdx = 0;
};

#endif /* COMMON_API_CANSERIALINTERFACE_H_ */
