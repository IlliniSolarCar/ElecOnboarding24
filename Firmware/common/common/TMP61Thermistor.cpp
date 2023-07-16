/*
 * TMP61Thermistor.cpp
 *
 *  Created on: Mar 14, 2021
 *      Author: Priyal
 */

#include "TMP61Thermistor.h"

uint16_t convertToDegreesCTMP61(uint16_t thermResistance) {
	if(resistanceLookup[0] > thermResistance) {
		return 0;
	}
	else if(resistanceLookup[NUM_DEGREES_CELCIUS - 1] <= thermResistance) {
		return NUM_DEGREES_CELCIUS;
	}

	for(int i = 1; i < NUM_DEGREES_CELCIUS; i++) {
		if(resistanceLookup[i] >= thermResistance) {
			uint16_t low_temp_index = (i-1) * 100;	// Multiply index by 100 to get return value in 0.01 degrees Celcius
			uint16_t temp = low_temp_index + ((thermResistance-resistanceLookup[i-1]) * 100)/(resistanceLookup[i]-resistanceLookup[i-1]);
			return temp;
			// TODO edge cases and testing
		}
	}
	return NUM_DEGREES_CELCIUS;
}





