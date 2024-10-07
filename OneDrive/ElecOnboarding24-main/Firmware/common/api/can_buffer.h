/*
 * can_buffer.h
 *
 *  Created on: Jun 10, 2014
 *      Author: Devan
 */

#ifndef COMMON_API_CAN_BUFFER_H_
#define COMMON_API_CAN_BUFFER_H_
#include <stdint.h>

#ifndef ___COMMON_NO_MBED__
#include <mbed.h>
#endif // ___COMMON_NO_MBED__

#include "circular_buffer.h"

/** CAN Message circular buffer template class + IRQ handler
 *
 *  @param RXSize size of receive buffer in messages; must be a power of 2
 *
 *  Typical usage:
 *    // 32 message buffer
 *    CANRXBuffer<32> canBuffer(can);
 *
 *    void handleCANMessage() {
 *        canBuffer.handleIrq();
 *    }
 *
 *    void setup() {
 *       // Do your other setup
 *       can.attach(handleCANMessage, CAN::RxIrq);
 *    }
 *
 *    void main() {
 *        while (1) {
 *            CANMessage msg;
 *            // Use CANRXBuffer::read instead of CAN::read
 *            if (canBuffer.read(msg)) {
 *                doStuff(msg);
 *            }
 *        }
 *    }
 */
template <int RXSize>
class CANRXBuffer {
public:
	/** Constructs a new, empty CAN message buffer
	 *
	 *  @param can CAN interface to read messages from
	 *  @param handle message filter handle (0 for any message)
	 */
	CANRXBuffer(CAN& can, int handle=0) : can(can), handle(handle) {

	}

	/** Check if the receive buffer is empty
	 *
	 *  @returns
	 *    true if empty
	 *    false if not empty
	 */
	bool rxEmpty() const {
		return rxBuffer.empty();
	}

	/** Check if the receive buffer is full
	 *
	 *  @returns
	 *    true if full
	 *    false if not full
	 */
	bool rxFull() const {
		return rxBuffer.full();
	}

    /** Read a CANMessage from the buffer.
     *
     *  @param msg A CANMessage to read to.
     *
     *  @returns
     *    0 if no message arrived,
     *    1 if message arrived
     */
	int read(CANMessage& msg) {
		int messageValid = 0;
		if (!rxEmpty()) {
			msg = rxBuffer.read();
			messageValid = 1;
		}

		return messageValid;
	}

	/** CAN receive message IRQ handler
	 *  Reads any pending CAN messages into the RX buffer
	 *  Stops when there are no more pending messages or the RX buffer is full
	 */
	void handleIrq() {
		CANMessage msg;
		while (can.read(msg, handle) && !rxFull()) {
			rxBuffer.write(msg);
		}
	}

private:
	CircularBuffer<CANMessage, RXSize> rxBuffer;
	CAN& can;
	const int handle;
};

/** CAN Message circular buffer template class + IRQ handler
 *
 *  @param RXSize size of receive buffer in messages; must be a power of 2
 *  @param TXSize size of transmit buffer in messages; must be a power of 2
 *
 *  Typical usage:
 *    // 32 message RX buffer, 16 message TX buffer
 *    CANRXTXBuffer<32, 16> canBuffer(can);
 *
 *    void handleCANMessage() {
 *        canBuffer.handleIrq();
 *    }
 *
 *    void setup() {
 *       // Do your other setup
 *       can.attach(handleCANMessage, CAN::RxIrq);
 *       can.attach(handleCANMessage, CAN::TxIrq);
 *    }
 *
 *    void main() {
 *        while (1) {
 *            CANMessage msg;
 *            // Use CANRXTXBuffer::read instead of CAN::read
 *            if (canBuffer.read(msg)) {
 *                doStuff(msg);
 *            }
 *            // Use CANRXTXBuffer::write instead of CAN::write
 *            for (int i=0; i < 5; i++) {
 *                CANMessage someMessage = makeAMessage();
 *                canBuffer.write(someMessage);
 *            }
 *        }
 *    }
 */
template <int RXSize, int TXSize>
class CANRXTXBuffer {
public:
	/** Constructs a new, empty CAN message buffer
	 *
	 *  @param can CAN interface to read messages from
	 *  @param handle message filter handle (0 for any message)
	 */
	CANRXTXBuffer(CAN& can, int handle=0) : can(can), handle(handle) {

	}

	/** Check if the receive buffer is empty
	 *
	 *  @returns
	 *    true if empty
	 *    false if not empty
	 */
	bool rxEmpty() const {
		return rxBuffer.empty();
	}

	/** Check if the transmit buffer is empty
	 *
	 *  @returns
	 *    true if empty
	 *    false if not empty
	 */
	bool txEmpty() const {
		return txBuffer.empty();
	}

	/** Check if the receive buffer is full
	 *
	 *  @returns
	 *    true if full
	 *    false if not full
	 */
	bool rxFull() const {
		return rxBuffer.full();
	}

	/** Check if the transmit buffer is full
	 *
	 *  @returns
	 *    true if full
	 *    false if not full
	 */
	bool txFull() const {
		return txBuffer.full();
	}

    /** Read a CANMessage from the buffer.
     *
     *  @param msg A CANMessage to read to.
     *
     *  @returns
     *    0 if no message arrived,
     *    1 if message arrived
     */
	int read(CANMessage& msg) {
		int messageValid = 0;
		if (!rxEmpty()) {
			msg = rxBuffer.read();
			messageValid = 1;
		}

		return messageValid;
	}

	/** Write a CANMessage to the buffer.
	 *
	 *  @param msg A CANMessage to write.
	 *
	 *  @returns
	 *    0 if no space in buffer,
	 *    1 if message added to buffer
	 */
	int write(CANMessage msg) {
		int messageQueued = 0;

		if (txEmpty() && (can.txstatus() == CAN::Idle)) {
			messageQueued = can.write(msg);
		} else if (!txFull()) {
			txBuffer.write(msg);
			messageQueued = 1;
		}

		return messageQueued;
	}

	/**
	 * Clear TX send buffer.
	 */
	void clearTX() {
		txBuffer.clear();
	}

	/** CAN receive/transmit message IRQ handler
	 *  Reads any pending CAN messages into the RX buffer
	 *  Stops when there are no more pending messages or the RX buffer is full
	 *  If the CAN interface is idle, transmits a message from the TX buffer
	 */
	void handleIrq() {
		CANMessage msg;
		while (can.read(msg, handle) && !rxFull()) {
			rxBuffer.write(msg);
		}

		while (!txEmpty()) {
			if (can.write(txBuffer.peek()) != 0) {
				txBuffer.discard();
			} else {
				break;
			}
		}
	}

private:
	CircularBuffer<CANMessage, RXSize> rxBuffer;
	CircularBuffer<CANMessage, TXSize> txBuffer;
	CAN& can;
	const int handle;
};


#endif // __COMMON_CAN_BUFFER_H__
