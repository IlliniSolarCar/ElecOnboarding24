/*
 * MCP9700AT.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: Xinlong (Leroy) Dai
 */

#include <MCP9700AT.h>


MCP9700AT::MCP9700AT(PinName pin, uint8_t num_of_rdings, uint16_t reference_voltage) : _temperatureIn(pin), _reference_voltage(reference_voltage) {
	if (num_of_rdings < 1) {
		num_of_rdings = 1;
	} else if (num_of_rdings > 5) {
		num_of_rdings = 5;
	}
	_num_of_rdings = num_of_rdings;
}

void MCP9700AT::initialize() {
	for (uint8_t i = 0; i < 10; i++) {
		_last_few_reads[i] = read();
	}
}

int16_t MCP9700AT::getAvgT(uint8_t level_of_avging) {
	int32_t sum = 0;
	if (level_of_avging < 1) {
		level_of_avging = 1;
	} else if (level_of_avging > 10) {
		level_of_avging = 10;
	}
	// Since _last_few_reads is taking data in a rolling fashion, we need to
	// break the averaging process into 2 cases.
	uint8_t index = (_count == 0) ? 9 : _count - 1;
	for (uint8_t i = 0; i < level_of_avging; i++) {
		sum += (int32_t) _last_few_reads[index];
		index = (index == 0) ? 9 : (index - 1);
	}
	int16_t toRet = (int16_t) (sum / (int32_t) level_of_avging);
	return toRet;
}

int16_t MCP9700AT::read() {
	int32_t temp = 0;
	for (uint8_t i = 0; i < _num_of_rdings; i++) {
		temp += (int32_t) _temperatureIn.read_u16();
	}

	int64_t preprocess = temp * ((int64_t)_reference_voltage) / UINT16_MAX / _num_of_rdings;
	int16_t toStore = ((preprocess - V_0) / T_C);

	// the maximum temperature that it can read is 12500 hundredth of Deg C
	if (toStore > 12500) {
		toStore = 12500;
	}

	_last_few_reads[_count] = toStore;
	_count++;
	if (_count == 10) {
		_count = 0;
	}
	return toStore;
}
