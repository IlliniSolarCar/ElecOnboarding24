/*
 * TimingCommon.cpp
 *
 * From Calsol Zephyr
 *
 * Updated for Brizo: 9/19/2019
 * Author: Jonathan Mullen
 *
 */

#include "TimingCommon.h"

TimingCommon::TimingCommon() {
	timer = NULL;
	num_callbacks = 0;
	for(int i = 0; i < TIMING_NUM_CALLBACKS; i++) {
		callbacks[i] = NULL;
		thresholds[i] = 0;
		lastTick[i] = 0;
	}
	heartbeat_threshold = 0;
	heartbeat_callback = NULL;
}

TimingCommon::~TimingCommon() {
}

void TimingCommon::resetCallbackLastTicks(uint32_t now) {
	for(int i = 0; i < num_callbacks; i++) {
		lastTick[i] = now;
	}
	heartbeat_lastTick = now;
}

void TimingCommon::start(Timer* t) {
	timer = t;
	timer->start();
	lastTickTime = timer->read_us();
	resetCallbackLastTicks(lastTickTime);
}

uint32_t TimingCommon::onTick(bool* outOverflow) {
	uint32_t now = timer->read_us();

	// Check if the clock has wrapped
	if (now < lastTickTime) {
		if(outOverflow != NULL)
			*outOverflow = true;
		resetCallbackLastTicks(now);
	} else {
		if(outOverflow != NULL)
			*outOverflow = false;

		// Trigger heartbeat callback
		if(heartbeat_callback && now - heartbeat_lastTick > heartbeat_threshold) {
			heartbeat_lastTick = now;
			heartbeat_callback(now);
		}

		// Trigger callbacks, if any
		for(int i = 0; i < num_callbacks; i++) {
			// If threshold has passed for callback
			if(now - lastTick[i] > thresholds[i]) {
				lastTick[i] = now;
				(callbacks[i])();
			}
		}
	}

	lastTickTime = now;

	return now;
}

int TimingCommon::addCallback(uint32_t threshold, void (*callback)(void)) {
	if(num_callbacks >= TIMING_NUM_CALLBACKS) // no more callbacks available
		return -1;

	// Add new callback
	thresholds[num_callbacks] = threshold;
	callbacks[num_callbacks] = callback;
	num_callbacks++;
	return 0;
}

void TimingCommon::setHeartbeatCallback(uint32_t threshold, void (*callback)(int)) {
	heartbeat_threshold = threshold;
	heartbeat_callback = callback;
}

uint32_t TimingCommon::difference(const uint32_t start, const uint32_t end){
	if (start < end) return (end - start);
	else return (UINT32_MAX - start) + end + 1;
}

int TimingCommon::threshold(const uint32_t last, const uint32_t now, const uint32_t interval){
	if(difference(last, now) >= interval)
		return 1;
	return 0;
}

int TimingCommon::tickThreshold(uint32_t &last, const uint32_t interval){
	if(difference(last, lastTickTime) >= interval){
		last = lastTickTime;
		return 1;
	}
	return 0;
}
