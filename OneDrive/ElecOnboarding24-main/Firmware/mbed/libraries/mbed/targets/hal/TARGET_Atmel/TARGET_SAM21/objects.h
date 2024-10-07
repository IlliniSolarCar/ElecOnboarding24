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
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "gpio_object.h"

#ifdef __cplusplus
extern "C" {
#endif

struct gpio_irq_s {
    uint32_t port;
    uint32_t pin;
    uint32_t ch;
};

struct port_s {
    __IO uint32_t *OUTCLR;
    __IO uint32_t *OUTSET;
    __I uint32_t *IN;

    PortName port;
    uint32_t mask;
};

struct serial_s {
    Sercom *usart;
    uint32_t index;
    uint32_t parity;
    uint32_t stopbits;
    uint32_t character_size;
    uint32_t mux_setting;
    uint32_t baudrate;
    uint32_t pinmux_pad0;
    uint32_t pinmux_pad1;
    uint32_t pinmux_pad2;
    uint32_t pinmux_pad3;
    PinName rxpin;
    PinName txpin;
#if DEVICE_SERIAL_ASYNCH
    uint32_t events;
#endif
};
/*
struct pwmout_s {
    __IO uint32_t *MR;
    PWMName pwm;
};

struct serial_s {
    LPC_UART_TypeDef *uart;
    int index;
};

struct analogin_s {
    ADCName adc;
};

struct dac_s {
    DACName dac;
};

struct can_s {
    LPC_CAN_TypeDef *dev;
    int index;
};

struct i2c_s {
    LPC_I2C_TypeDef *i2c;
};
*/

struct spi_s {
    Sercom *spi;
    uint8_t mode;
#if DEVICE_SPI_ASYNCH
    uint8_t status;
    uint32_t mask;
    uint32_t event;
    void *tx_buffer;
    void *rx_buffer;
    uint8_t dma_usage;
#endif
};

#ifdef __cplusplus
}
#endif

#endif
