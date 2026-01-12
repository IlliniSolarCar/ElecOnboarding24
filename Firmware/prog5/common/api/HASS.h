/*
 * HASS.h
 *
 *  Created on: Jun 3, 2014
 *      Author: Devan
 *
 *  Header-only template class for the HASS XXX-S current transducer.
 *  The template parameter is the part-number current I_PN (eg, the HASS 100-S
 *  has an I_PN of 100)
 */

#ifndef COMMON_API_HASS_H_
#define COMMON_API_HASS_H_

#include <mbed.h>

template<int IPN>
class HASS {
public:

    /** Read the current in amps, represented as a float
     *
     * @returns A floating-point value representing the current current, measured in amps
     */
    float read() {
        // delta V = 0.625 * I_P/I_PN
        // I_P = dV * I_PN / 0.625
        return read_avg() * IPN / 0.625;
    }

    /**
     * Read the voltage across the current sensor in volts.
     */
    virtual float read_avg() = 0;

    /** An operator shorthand for read()
     *
     * The float() operator can be used as a shorthand for read() to simplify common code sequences
     *
     * Example:
     * @code
     * float x = volume.read();
     * float x = volume;
     *
     * if(volume.read() > 0.25) { ... }
     * if(volume > 0.25) { ... }
     * @endcode
     */
    operator float() {
        return read();
    }
};

#endif /* __HASS_H__ */
