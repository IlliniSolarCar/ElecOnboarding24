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
#ifndef COMMON_HAL_COUNTER_API_H_
#define COMMON_HAL_COUNTER_API_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef enum {
    EVENT_NONE = 0x0,
    EVENT_RISE = 0x1,
    EVENT_FALL = 0x2,
    EVENT_BOTH = 0x3
} counter_event_type;

void counter_init(counter_event_type event, int prescale);
void counter_mode(counter_event_type event, int prescale);
uint32_t counter_read(void);

#ifdef __cplusplus
}
#endif

#endif
