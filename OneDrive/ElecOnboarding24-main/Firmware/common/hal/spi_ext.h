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
#ifndef COMMON_HAL_SPI_EXT_H_
#define COMMON_HAL_SPI_EXT_H_

#include "device.h"
#include "spi_api.h"
#if DEVICE_SPI

#ifdef __cplusplus
extern "C" {
#endif

void spi_master_write_array(spi_t* obj, const int* values, int len);
void spi_master_write_array_u8(spi_t* obj, const uint8_t* values, int len);
void spi_master_write_array_u16(spi_t* obj, const uint16_t* values, int len);
void spi_master_read_array(spi_t* obj, int* values, int len);
void spi_master_read_array_u8(spi_t* obj, uint8_t* values, int len);
void spi_master_read_array_u16(spi_t* obj, uint16_t* values, int len);
void spi_master_transfer(spi_t* obj, int* values, int len);
void spi_master_transfer_u8(spi_t* obj, uint8_t* values, int len);
void spi_master_transfer_u16(spi_t* obj, uint16_t* values, int len);

#ifdef __cplusplus
}
#endif

#endif

#endif
