/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef COMMON_API_EVENTCOUNTER_H_
#define COMMON_API_EVENTCOUNTER_H_

#include "platform.h"

//note:  this class not compatible with LPC15xx -- kept for LPC11x1x legacy compatibility

namespace mbed {

/** A general purpose event counter
 *
 * Example:
 * @code
 * // Count the number of rising edges
 *
 * #include "mbed.h"
 *
 * EventCounter counter;
 * int begin, end;
 *
 * int main() {
 *     counter.start();
 *     wait_ms(1000);
 *     counter.stop();
 *
 *     int count = counter.read();
 *     printf("%d edges in 1 second", count);
 * }
 * @endcode
 */
class EventCounter {

public:
    enum EventType {
        RisingEdge = 0x1,
        FallingEdge = 0x2,
        EitherEdge = 0x3
    };


	EventCounter(EventType type=RisingEdge, int prescale=1);

	/** Set the event type and prescaler
	 *
	 *  @param type which edges to count as events
	 *  @param prescale event count prescaler
	 */
	void mode(EventType type, int prescale=1);

    /** Start the counter
     */
    void start();

    /** Stop the counter
     */
    void stop();

    /** Reset the counter to 0.
     *
     * If it was already counting, it will continue
     */
    void reset();

    /** Get the number of events that have occurred
     */
    uint32_t read();

#ifdef MBED_OPERATORS
    operator uint32_t();
#endif

protected:
    uint32_t slicetime();
    int _running;      // whether the counter is running
    uint32_t _start;   // the start count of the latest slice
    uint32_t _count;   // any accumulated counts from previous slices
};

} // namespace mbed

#endif
