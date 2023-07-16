/*
 * encoding.h
 *
 *  Created on: Mar 8, 2015, Modfied Jan 15, 2020
 *      Author: Devan, John Han
 */

#ifndef COMMON_API_ENCODING_H_
#define COMMON_API_ENCODING_H_

#include <stdint.h>
#include <can_struct.h>


// 2 bytes from ID, 1 for length, 8 for payload, 1 for delimiter and 1 extra overhead
constexpr int32_t MAX_ENCODED_SIZE = 1024; // extra big to avoid errors
constexpr int32_t MAX_DECODED_SIZE = 1024; // extra big to avoid errors
constexpr uint8_t DELIMITER_BYTE = 0;

/**
 * Encodes a CAN message into byte array with same format used by the Telemetry app
 * @param msg The CAN message to be encoded
 * @param buffer a pointer to an array where the encded message is to be written
 * @returns the number of bytes written
 */
uint32_t encode(const mbed::CANMessage& msg, uint8_t* buffer);

/**
 * decodes a byte array into a CAN message using same form as Telemetry app
 * @param buffer the buffer to be decoded
 * @param len the length of the buffer to be decoded
 * @param *decodedMessage a place for the decoded message to be placed
 * @returns 0 on success, 1 on cobs decode input failure, 2 on cobs decode overflow 3 on checksum failure 4 invalid cobs decode
 */

int32_t decode(const uint8_t* buffer, const uint32_t len, CANMessage& decodedMessage);


#endif /* COMMON_API_ENCODING_H_ */
