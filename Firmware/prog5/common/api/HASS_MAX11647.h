/*
 * HASS_MAX11647.h
 *
 * Implementation of HASS sensor using a MAX11647 external ADC.
 */

#ifndef COMMON_API_HASS_MAX11647_H_
#define COMMON_API_HASS_MAX11647_H_

#include <mbed.h>
#include "HASS.h"
#include "MAX11647.h"

template<int IPN>
class HASS_MAX11647 : public HASS<IPN> {
public:

    /**
     * Create a HASS sensor, reading from the specified AnalogIn objects
     * @param adc ADC to read the current sensor outputs.
     */
    HASS_MAX11647<IPN>(MAX11647* adc) {
        ADC = adc;
    }

    /**
     * Resistive divider correction factor for current sensor.
     * V_adc = 10 / (10 + 6.8) * V_hass
     * We want V_real, so V_real = V_adc * 16.8/10.0.
     */
    const float RESDIV_INV = 16.8 / 10.0;

    float read_avg() {
        int16_t data[ADC->numReadings()];
        ADC->readDifferential(&data[0]);
        int32_t s = 0;
        for(int i = 0; i < ADC->numReadings(); i++) {
            s += data[i];
        }
        s = s / ADC->numReadings();

        // ConvertRES MAX11647 voltage steps to real readings.
        // raw_reading / 1024 * 3.0 [Vref]
        float v_adc = s / 1024.0 * 3;
        return v_adc * RESDIV_INV;
    }

private:
    MAX11647* ADC;
};

#endif /* __HASS_MAX11647_H__ */
