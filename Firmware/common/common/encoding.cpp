/*
 * encoding.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: Devan
 */

#include <encoding.h>
#include <mbed.h>

/**
 * Encodes a given buffer using constant ovehead byte stuffing
 * @param inBuffer a pointer the input buffer to be read and encoded
 * @param inLen the length of inBuffer
 * @param *outBuffer a pointer the output buffer where the encoded buffer can be written
 * @returns the length of the encoded buffer
 */
uint32_t cobs_encode(uint8_t* inBuffer, uint32_t inLen, uint8_t* outBuffer) {
  const uint8_t* inEnd = inBuffer + inLen;
  uint8_t* lastCodePos = outBuffer;
  uint8_t* outPos = outBuffer+1;
  while (inBuffer < inEnd) {
    if (*inBuffer == 0) {
      *lastCodePos = outPos - lastCodePos;
      lastCodePos = outPos;
      outPos++;
    } else {
      *outPos = *inBuffer;
      outPos++;
    }
    inBuffer++;
  }
  *lastCodePos = outPos - lastCodePos;
  return outPos - outBuffer;
}

/**
 * Decodes the given buffer previously encoded using constant ovehead byte stuffing
 * @param inBuffer the input buffer to be decoded
 * @param inLen the length of inBuffer
 * @param outBuffer the output buffer where the decoded buffer should be written
 * @return the length of the output buffer returns -1 in invalid input -2 on output buffer overflow
 */
int32_t cobs_decode(const uint8_t* inBuffer, const uint32_t inLen, uint8_t* outBuffer, const uint32_t outSize) {

	uint32_t curPos = 0;
	uint32_t outLen = 0;
	while(curPos < inLen) {
		int32_t numTilDel = (uint32_t) inBuffer[curPos]; // length till next deliminator (next 0)
		
		// up until the next zero, copy into output
		for(int32_t i = 0; i < numTilDel - 1; i++) {
			curPos++;
			if (curPos >= inLen) return -1;

			// push buffer[curPos] to decoded
			// return -2 on out overflow
			if (outLen >= outSize) {
				return -2;
			}
			outBuffer[outLen] = inBuffer[curPos];
			outLen++;
		}
		curPos++;

		// push zeros between to decoded
		if (outLen >= outSize) return -2;
		outBuffer[outLen] = 0;
		outLen++;
	}
	// returns length of out buffer, -1 on failure
	return outLen;
}

/**
 * Uses the checksum value at the end of the message to vertify that it is valid
 * @param *buffer the buffer to be checked
 * @param len the length of buffer
 * @returns True if valid False otherwise
 */
bool checkSum(const uint8_t* buffer, const uint32_t len) {
    int32_t sum = 0;

    // to determine length of buffer, keep going to you get to undefined values.
    for(uint32_t i = 0; i < len; i ++) {
        sum -= (int32_t) buffer[i];
    }
    return (sum & 0xFF) == buffer[len-2];
}

/**
 * Parses a CAN message from a vertified decoded message
 * @param *decoded a buffer of bytes containing a decoded CAN message
 * @param len the length of decoded
 * @returns a CAN message from the decoded buffer
 */ 
CANMessage getMessageFromDecoded(const uint8_t* decoded, const uint32_t len) {
	int id = ((decoded[1] & 0x0F) << 8) | (decoded[0] & 0xFF);
	const int data_len = (decoded[1] & 0xF0) >> 4;

	uint8_t data_val[data_len];

	// copy data of message to data val array
	for (int i = 0; i < data_len; i++) {
		data_val[i] = decoded[2 + i];
	}

	return CANMessage(id, reinterpret_cast<const char*>(&data_val), sizeof(data_val));
}

uint32_t encode(const mbed::CANMessage& msg, uint8_t* buffer) {
	uint8_t inBuffer[MAX_ENCODED_SIZE];
	uint32_t length;

	inBuffer[0] = (uint8_t)(msg.id & 0xFF);
	inBuffer[1] = (uint8_t)((msg.id >> 8) & 0x07);
	inBuffer[1] |= ((uint8_t)(msg.len) << 4);
	for(int i = 0; i < msg.len; i++) {
		inBuffer[2+i] = msg.data[i];
	}

	// Checksum
	inBuffer[msg.len+2] = 0;
	for(int i = 0 ; i < msg.len+2; i++)
	{
	  inBuffer[msg.len+2] -= inBuffer[i];
	}

	length = cobs_encode(inBuffer,msg.len+3,buffer);
	buffer[length] = DELIMITER_BYTE;
	return length+1;
}

int32_t decode(const uint8_t* buffer, const uint32_t len, CANMessage& decodedMessage) {

	uint8_t decoded_buf[MAX_DECODED_SIZE];

	// cobs decode message
	int32_t decoded_len = cobs_decode(buffer, len, decoded_buf, MAX_DECODED_SIZE);

	// -1 for invalid input
	// -2 for output buffer overflow
	if (decoded_len < 0) return - decoded_len;

	if (decoded_len < 3) return 4; // must be at least 3 bytes long to contain a can message
	if (decoded_len > MAX_DECODED_SIZE) return 4;
	// perform checksum to ensure that message is valid
	if (checkSum(decoded_buf, decoded_len) == 0) {
		return 3;
	}
	// convert byte array to CANMessage
	decodedMessage = getMessageFromDecoded(decoded_buf, decoded_len);
	return 0;
}
