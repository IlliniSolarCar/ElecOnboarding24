/*
 * AbstractTicker.h
 * Abstraction for hardware tickers.
 *
 *  Created on: Feb 20, 2016
 *      Author: edwardw
 */

#ifndef COMMON_API_ABSTRACTTICKER_H_
#define COMMON_API_ABSTRACTTICKER_H_

class AbstractTicker {
public:
    AbstractTicker() {};
    virtual ~AbstractTicker() {};

    /**
     * Attach the given function to be called every interval_us microseconds.
     */
    virtual void attach(void (*fn)(void), uint32_t interval_us) = 0;
    /**
     * Detach the ticker.
     */
    virtual void detach() = 0;
};

#endif
