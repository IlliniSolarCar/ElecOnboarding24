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
#include "EventCounter.h"
#include "counter_api.h"

//note:  this class not compatible with LPC15xx -- kept for LPC11x1x legacy compatibility

namespace mbed {

EventCounter::EventCounter(EventType type, int prescale) {
	mode(type, prescale);
    reset();
}

void EventCounter::start() {
	_start = counter_read();
    _running = 1;
}

void EventCounter::stop() {
    _count += slicetime();
    _running = 0;
}

uint32_t EventCounter::read() {
    return _count + slicetime();
}

uint32_t EventCounter::slicetime() {
    if (_running) {
        return counter_read() - _start;
    } else {
        return 0;
    }
}

void EventCounter::reset() {
    _start = counter_read();
    _count = 0;
}

void EventCounter::mode(EventType type, int prescale) {
    counter_init((counter_event_type)type, prescale);
}

#ifdef MBED_OPERATORS
EventCounter::operator uint32_t() {
    return read();
}
#endif

} // namespace mbed
