/*
 * HASS_LPC.h
 *
 * Implementation of HASS sensor using the LPC processor's built-in ADC.
 */

#ifndef COMMON_API_HASS_LPC_H_
#define COMMON_API_HASS_LPC_H_

#include <mbed.h>
#include "HASS.h"

template<int IPN>
class HASS_LPC : public HASS<IPN> {
public:

    /**
     * Create a HASS sensor, reading from the specified AnalogIn objects
     * @param vref Pin name of the voltage reference
     * @param vout Pin name of the voltage output
     * @param adcVref Voltage reference connected to the microcontroller
     */
        HASS_LPC<IPN>(PinName vref, PinName vout, float adcVref) :
            _vref(vref), _vout(vout), _adcVref(adcVref) {}

    float read_avg() {
        float s = 0;
        for(int i = 0; i < 16; i++)
                s += (_adcVref * (_vout - _vref));
        return s / 16.0;
    }

private:
    AnalogIn _vref;
    AnalogIn _vout;
    float _adcVref;
};

#endif /* __HASS_LPC_H__ */
