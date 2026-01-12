/*
 * TickerMbed.h
 * Tickers implemented with mbed.
 *
 *  Created on: Feb 20, 2016
 *      Author: edwardw
 */

#ifndef COMMON_API_TICKERMBED_H_
#define COMMON_API_TICKERMBED_H_

#include <mbed.h>

class TickerMbed : public AbstractTicker {
public:
    TickerMbed(Ticker& t) : ticker(t) {
    }

    virtual void attach(void (*fn)(void), uint32_t us) {
        ticker.attach(fn, us);
    }

    virtual void detach() {
        ticker.detach();
    }

private:
    Ticker& ticker;
};

#endif
