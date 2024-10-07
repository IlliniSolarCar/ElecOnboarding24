/**
 * MCP9700AT.h
 *
 *  Created on: Sept 14, 2020
 *      Author: Xinlong (Leroy) Dai
 *
 *  Class for handling the temperature values read from MCP9700AT
 *
 */

#ifndef COMMON_API_MCP9700AT_H_
#define COMMON_API_MCP9700AT_H_

#include <mbed.h>

#define V_0 5000 /* Unit: decimilliV */
#define T_C 1 /* Unit: decimilliV / centi-Deg C */


class MCP9700AT {
public:
	/*
	 * MCP9700AT class constructor
	 * @Param pin the pin connected to the temperature sensor
	 * @param num_of_rdings the number of readings to take before logging it to the lastFewReads (1 <= num_of_rdings <= 5; the default value is 5)
	 */
	MCP9700AT(PinName pin, uint8_t num_of_rdings = 5, uint16_t reference_voltage = 33000);

	/*
	 * Initializes the class, especially _last_few_reads that stores the last 10 reads
	 */
	void initialize();
	/*
	 * Get the average on a number of recently read temperature values
	 * To read the immediate temperature value and to update _last_few_reads, please use read()
	 * @param level_of_avging the level of averaging to do on the result being returned (1 <= level_of_avging <= 10; the default value is 10)
	 * @return the averaged temperature in hundredth of a Deg C
	 */
	int16_t getAvgT(uint8_t level_of_avging = 10);
	/*
	 * Read the immediate temperature
	 * @return the immediate temperature reading in hundredth of a Deg C
	 */
	int16_t read();
private:
	/*
	 * _temperatureIn is the pin of the sensor
	 */
	AnalogIn _temperatureIn;
	/*
	 * _last_few_reads records the latest 10 readings from read()
	 */
	int16_t _last_few_reads[10] = { 0 };
	/*
	 * _count is where the next reading should go, not where the last one was taken
	 */
	uint8_t _count = 0;
	/*
	 * _reference_voltage is the analog reference voltage
	 */
	int32_t _reference_voltage;
	/*
	 * _num_of_rding is the number of readings that the class object will take within one call of read()
	 */
	uint8_t _num_of_rdings;
};



#endif /* COMMON_API_MCP9700AT_H_ */
