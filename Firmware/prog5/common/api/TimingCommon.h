/*
 * TimingCommon.h
 *
 * A class for handling common timing functions.
 * Only handles Timer overflow after 71 minutes (2^32 - 1 microseconds) and some calculations for now.
 * This adapts a signed time value (from the Timer class in mbed) into an unsigned uint32_t value.
 *
 * From Calsol Zephyr
 *
 * Updated for Brizo: 9/19/2019
 * Author: Jonathan Mullen and Priyal Gosar
 */

#ifndef COMMON_API_TIMINGCOMMON_H_
#define COMMON_API_TIMINGCOMMON_H_

#ifdef _TESTING_
class Timer;
#else
#include <mbed.h>
#endif

// Number of possible timing-based callbacks
#define TIMING_NUM_CALLBACKS 12

class TimingCommon {
public:
	TimingCommon();
	virtual ~TimingCommon();

	/**
	 * Start timing.
	 * Will start the time with timer.start() if not already started.
	 * @param timer Timer to use.
	 */
	void start(Timer* t);

	/**
	 * Runs each time at the top of the board main run while(1).
	 * @param outOverflow
	 * 	Will be set true on timer overflow, false otherwise.
	 * 	Can be NULL if unused.
	 * @return Current time now (us)
	 */
	uint32_t onTick(bool* outOverflow);

	/**
	 * Add a callback to be triggered periodically during onTick().
	 * @param threshold Period of callback (us)
	 * @param callback Callback function
	 * @return 0 on success, -1 on failure (too many callbacks added already)
	 */
	int addCallback(uint32_t threshold, void (*callback)(void));

	/**
	 * Add a callback for heartbeat messages to be triggered periodically.
	 * @param threshold Period of heartbeats (us)
	 * @param callback Callback function taking an int (current time)
	 */
	void setHeartbeatCallback(uint32_t threshold, void (*callback)(int));

	/*
	 * Calculate the time difference between two times (unitless)
	 * @param start time
	 * @param end time
	 * @return time difference
	 */
	static uint32_t difference(const uint32_t start, const uint32_t end);

	/*
	 * Determine if a time threshold has been met
	 * @param last time the function was run
	 * @param now - current time
	 * @param the interal at which the task is supposed to run
	 * @return 1 - the threshold to run again has been met; 0 the threshold has not been met
	 */
	static int threshold(const uint32_t last, const uint32_t now, const uint32_t interval);

	/*
	 * Determine if as threshold has been met as of current tick
	 * @param last time the function was run, will be changed to last tick if 1 is returned
	 * @param the interal at which the task is supposed to run
	 * @return 1 - the threshold to run again has been met; 0 the threshold has not been met
	 */
	int tickThreshold(uint32_t& last, const uint32_t interval);

private:
	uint32_t lastTickTime;
	Timer* timer;

	uint32_t thresholds[TIMING_NUM_CALLBACKS];
	uint32_t lastTick[TIMING_NUM_CALLBACKS];
	void (*callbacks[TIMING_NUM_CALLBACKS])(void);
	int num_callbacks;

	uint32_t heartbeat_threshold;
	uint32_t heartbeat_lastTick;
	void (*heartbeat_callback)(int);

	/**
	 * Reset all callback last tick times to the given time.
	 */
	void resetCallbackLastTicks(uint32_t now);
};

#endif /* TIMINGCOMMON_H_ */
