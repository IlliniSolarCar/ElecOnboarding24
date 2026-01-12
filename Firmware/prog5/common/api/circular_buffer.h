/*
 * circular_buffer.h
 *
 *  Created on: Jan 28, 2017
 *      Author: Devan Lai, Jean-Etienne Tremblay
 */

#ifndef COMMON_API_CIRCULAR_BUFFER_H_
#define COMMON_API_CIRCULAR_BUFFER_H_

constexpr bool isPowerOfTwo(int x) {
	return x > 0 && ((x & (x-1)) == 0);
}
/*
 * Circular buffer template class
 */
template <class T, int N>
class CircularBuffer {
	static_assert(isPowerOfTwo(N), "Buffer size must be a power of 2 for efficiency");

public:
	/** Constructs a new, empty circular buffer capable of storing up to
	 *  N - 1 elements.
	 */
	CircularBuffer() : start(0), end(0) {};

	/** Check if the buffer is full
	 *
	 *  @returns
	 *    true if full
	 *    false if not full
	 */
	bool full() const {
		return (this->end + 1) % N == this->start;
	}

	/** Check if the buffer is empty
	 *
	 *  @returns
	 *    true if empty
	 *    false if not empty
	 */
	bool empty() const {
		return this->start == this->end;
	}

	/** Adds an element of type T to the end of the buffer
	 *
	 *  Note: the caller is responsible for checking that
	 *        the buffer is not already full
	 *
	 *  @param s element to append
	 */
	void write(T s) {
		this->buffer[this->end] = s;
		this->end = (this->end + 1) % N;
	}

	/** Pops the element at the front of the buffer
	 *
	 *  Note: the caller is responsible for checking that
	 *        the buffer is not empty
	 *
	 *  @returns
	 *    element at front of the buffer
	 */
	T read() {
		T s = this->buffer[this->start];
		this->start = (this->start + 1) % N;
		return s;
	}

	/** Reads the element at the front of the buffer without removing it
	 *
	 *  Note: the caller is responsible for checking that
	 *        the buffer is not empty
	 *
	 *  @returns
	 *    element at front of the buffer
	 */
	const T& peek() {
		return this->buffer[this->start];
	}

	/** Removes the element at the front of the buffer without reading it
	 *
	 *  Note: the caller is responsible for checking that
	 *        the buffer is not empty
	 *
	 */
	void discard() {
		this->start = (this->start + 1) % N;
	}

	/** Empties the buffer
	 *
	 *  Note: does not actually destroy any objects
	 *
	 */
	void clear() {
		this->start = this->end = 0;
	}

private:
	T buffer[N];
	volatile int start, end;
};

#endif /* COMMON_API_CIRCULAR_BUFFER_H_ */
