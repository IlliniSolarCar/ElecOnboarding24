/*
 * WDT.h
 *
 * Watchdog timer implementation
 */
#ifndef COMMON_API_WDT_H_
#define COMMON_API_WDT_H_

#include <cstdint>

class WDT {
    public:
        /**
         * Create a Watchdog Timer Object, that starts disabled
         * @param timeout The maximum time (in us) between watchdog feeds without a reset (Be warned, the oscialltor is accurate to +/-40%, so this won't be terribly precise. Make this longer than you think you need.
         */
        WDT(uint32_t timeout_us);

        /**
         * Set the Watchdog Timer timeout
         * @param timeout The maximum time (in us) between watchdog feeds without a reset (Be warned, the oscialltor is accurate to +/-40%, so this won't be terribly precise. Make this longer than you think you need.
         */
        void setTimeout(uint32_t timeout_us);

        /**
         * Enable the Watchdog Timer. Once the WDT is enabled it cannot be disabled!
         */
        void enable();

        /**
         * Check if the Watchdog caused the last reset
         */
        bool causedReset();

        /**
         * Feed the Watchdog Timer, must be done before timeout expires
         */
        void feed();
};

#endif /* __WDT_H__*/
