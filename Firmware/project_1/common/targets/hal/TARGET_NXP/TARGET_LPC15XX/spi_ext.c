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
#include "spi_ext.h"
#include "cmsis.h"

static inline int ssp_readable(spi_t *obj) {
    return obj->spi->STAT & (1 << 0);
}

static inline int ssp_writeable(spi_t *obj) {
    return obj->spi->STAT & (1 << 1);
}

static inline int ssp_read(spi_t *obj) {
    while (!ssp_readable(obj));
    return obj->spi->RXDAT;
}

void spi_master_write_array(spi_t *obj, const int* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            obj->spi->RXDAT;
            wordsRead++;
        }
    }

    while (wordsRead < len) {
    	ssp_read(obj);
    	wordsRead++;
    }
}

void spi_master_write_array_u8(spi_t *obj, const uint8_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            obj->spi->RXDAT;
            wordsRead++;
        }
    }

    while (wordsRead < len) {
    	ssp_read(obj);
    	wordsRead++;
    }
}

void spi_master_write_array_u16(spi_t *obj, const uint16_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            obj->spi->RXDAT;
            wordsRead++;
        }
    }

    while (wordsRead < len) {
    	ssp_read(obj);
    	wordsRead++;
    }
}

void spi_master_read_array(spi_t *obj, int* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = 0;
            wordsWritten++;
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}

void spi_master_read_array_u8(spi_t *obj, uint8_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = 0;
            wordsWritten++;
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}

void spi_master_read_array_u16(spi_t *obj, uint16_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = 0;
            wordsWritten++;
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}

void spi_master_transfer(spi_t *obj, int* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}


void spi_master_transfer_u8(spi_t *obj, uint8_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}

void spi_master_transfer_u16(spi_t *obj, uint16_t* values, int len) {
	int wordsWritten = 0;
	int wordsRead = 0;
    while (!ssp_writeable(obj));
    while ((wordsWritten < len) || (wordsRead < len)) {
        while (ssp_writeable(obj) && (wordsWritten < len)) {
            obj->spi->TXDAT = values[wordsWritten++];
        }
        while (ssp_readable(obj) && (wordsRead < len)) {
            values[wordsRead++] = obj->spi->RXDAT;
        }
    }
}
