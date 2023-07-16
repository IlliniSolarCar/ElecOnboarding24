/*
 * CANSerialInterface.cpp
 *
 *  Created on: Jan 15, 2021
 *      Author: John Han
 */

#include <CANSerialInterface.h>
#include <encoding.h>

CANSerialInterface::CANSerialInterface(Serial& uart, int baudrate) : _uart(uart){
	_uart.baud(baudrate);
}

uint8_t CANSerialInterface::sendMessage(const CANMessage& msg) {
    uint8_t buffer[MAX_ENCODED_SIZE];
    uint32_t len = encode(msg, buffer);
    uint8_t error = 0;
    for(unsigned i = 0; i < len; i ++) {
        if (_uart.putc(buffer[i]) == EOF) error = 1;
    }
    return error;
}

uint8_t CANSerialInterface::readMessage(CANMessage& msg) {

	bool newBytes = false;
    while(_uart.readable()) {
    	newBytes = true;

        // if buffer is full throw away data and restart
        if(_inBufIdx >= MAX_ENCODED_SIZE) {
            _inBufIdx = 0;
            return 5; // buffer overflow
        }
        
        // copy data to buffer
        uint8_t new_char = _uart.getc();
        if (new_char == DELIMITER_BYTE) {
            // if have one full message, decode
            
            // clear buffer
            uint32_t bufLen = _inBufIdx;
            _inBufIdx = 0;
            
            // if buffer not empty
            if(bufLen > 0) {
                // get message from buffer returns 0 success, 1-4 for failures
                int32_t ret = decode(_inBuf, bufLen + 1, msg);
                resetBuffer();
                return ret;
            }
        } else {
            _inBuf[_inBufIdx] = new_char;
            _inBufIdx++;
        }
    }

    if (newBytes) return 7; // new data but no message
    else return 6; // no new data or message
}

void CANSerialInterface::resetBuffer() {
	for (int i = 0 ; i < MAX_ENCODED_SIZE; i ++) _inBuf[i] = 0;
	_inBufIdx = 0;
}
