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
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  12
#define PIN_SHIFT   8

typedef enum {
    // LPC1114 Pin Names (PORT[15:12] + PIN[11:8] + IOCON offset[7:0])

    P0_0  = (0 << PORT_SHIFT) | (0  << PIN_SHIFT) | 0x0c,
    P0_1  = (0 << PORT_SHIFT) | (1  << PIN_SHIFT) | 0x10,
    P0_2  = (0 << PORT_SHIFT) | (2  << PIN_SHIFT) | 0x1c,
    P0_3  = (0 << PORT_SHIFT) | (3  << PIN_SHIFT) | 0x2c,
    P0_4  = (0 << PORT_SHIFT) | (4  << PIN_SHIFT) | 0x30,
    P0_5  = (0 << PORT_SHIFT) | (5  << PIN_SHIFT) | 0x34,
    P0_6  = (0 << PORT_SHIFT) | (6  << PIN_SHIFT) | 0x4c,
    P0_7  = (0 << PORT_SHIFT) | (7  << PIN_SHIFT) | 0x50,
    P0_8  = (0 << PORT_SHIFT) | (8  << PIN_SHIFT) | 0x60,
    P0_9  = (0 << PORT_SHIFT) | (9  << PIN_SHIFT) | 0x64,
    P0_10 = (0 << PORT_SHIFT) | (10 << PIN_SHIFT) | 0x68,
    P0_11 = (0 << PORT_SHIFT) | (11 << PIN_SHIFT) | 0x74,

    P1_0  = (1 << PORT_SHIFT) | (0  << PIN_SHIFT) | 0x78,
    P1_1  = (1 << PORT_SHIFT) | (1  << PIN_SHIFT) | 0x7c,
    P1_2  = (1 << PORT_SHIFT) | (2  << PIN_SHIFT) | 0x80,
    P1_3  = (1 << PORT_SHIFT) | (3  << PIN_SHIFT) | 0x90,
    P1_4  = (1 << PORT_SHIFT) | (4  << PIN_SHIFT) | 0x94,
    P1_5  = (1 << PORT_SHIFT) | (5  << PIN_SHIFT) | 0xa0,
    P1_6  = (1 << PORT_SHIFT) | (6  << PIN_SHIFT) | 0xa4,
    P1_7  = (1 << PORT_SHIFT) | (7  << PIN_SHIFT) | 0xa8,
    P1_8  = (1 << PORT_SHIFT) | (8  << PIN_SHIFT) | 0x14,
    P1_9  = (1 << PORT_SHIFT) | (9  << PIN_SHIFT) | 0x38,
    P1_10 = (1 << PORT_SHIFT) | (10 << PIN_SHIFT) | 0x6c,
    P1_11 = (1 << PORT_SHIFT) | (11 << PIN_SHIFT) | 0x98,

    P2_0  = (2 << PORT_SHIFT) | (0  << PIN_SHIFT) | 0x08,
    P2_1  = (2 << PORT_SHIFT) | (1  << PIN_SHIFT) | 0x28,
    P2_2  = (2 << PORT_SHIFT) | (2  << PIN_SHIFT) | 0x5c,
    P2_3  = (2 << PORT_SHIFT) | (3  << PIN_SHIFT) | 0x8c,
    P2_4  = (2 << PORT_SHIFT) | (4  << PIN_SHIFT) | 0x40,
    P2_5  = (2 << PORT_SHIFT) | (5  << PIN_SHIFT) | 0x44,
    P2_6  = (2 << PORT_SHIFT) | (6  << PIN_SHIFT) | 0x00,
    P2_7  = (2 << PORT_SHIFT) | (7  << PIN_SHIFT) | 0x20,
    P2_8  = (2 << PORT_SHIFT) | (8  << PIN_SHIFT) | 0x24,
    P2_9  = (2 << PORT_SHIFT) | (9  << PIN_SHIFT) | 0x54,
    P2_10 = (2 << PORT_SHIFT) | (10 << PIN_SHIFT) | 0x58,
    P2_11 = (2 << PORT_SHIFT) | (11 << PIN_SHIFT) | 0x70,
   
    P3_0  = (3 << PORT_SHIFT) | (0  << PIN_SHIFT) | 0x84,
    P3_1  = (3 << PORT_SHIFT) | (1  << PIN_SHIFT) | 0x88,
    P3_2  = (3 << PORT_SHIFT) | (2  << PIN_SHIFT) | 0x9c,
    P3_3  = (3 << PORT_SHIFT) | (3  << PIN_SHIFT) | 0xac,
    P3_4  = (3 << PORT_SHIFT) | (4  << PIN_SHIFT) | 0x3c,
    P3_5  = (3 << PORT_SHIFT) | (5  << PIN_SHIFT) | 0x48,

    USBTX = P1_7,
    USBRX = P1_6,

    // Not connected
    NC = (int)0xFFFFFFFF,
} PinName;

typedef enum {
    CHANNEL0 = WAKEUP0_IRQn,
    CHANNEL1 = WAKEUP1_IRQn,
    CHANNEL2 = WAKEUP2_IRQn,
    CHANNEL3 = WAKEUP3_IRQn,
    CHANNEL4 = WAKEUP4_IRQn,
    CHANNEL5 = WAKEUP5_IRQn,
    CHANNEL6 = WAKEUP6_IRQn,
    CHANNEL7 = WAKEUP7_IRQn
} Channel;

typedef enum {
    PullUp = 2,
    PullDown = 1,
    PullNone = 0,
    Repeater = 3,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
