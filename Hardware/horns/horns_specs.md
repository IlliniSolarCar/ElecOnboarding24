> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Breakout
**Board Requirements**


## Overview and Description
- This board powers the horn using +24V from the LV Bus board and sounds the horn based on a digital signal from the dashboard.
- Board connects to Dashboard

## High-Level Requirements
- Requires Horn On/Off digital signal
- Requires Horn Output, rated 24V at 150 mA
	- Horn Output will connect to two horns in series
- No microcontroller

## Communication Protocols
- Requires implementation of Digital GPIO
	- Communication with Dashboard

## Connectors
- Power In (1x3 Molex)
- Horn Control (1x2 Molex)
- Horn Out (1x2 Molex)
- Horn Out (1x2 Molex)

## ICs
- No ICs

## Buttons/Switches
- Debug button for board testing

## Power System
- 24V from LV Bus

## Test Points
- GPIO input
- Horn output

## LED Indicators
- 4 Debug LEDs
- LED displaying Horn On/Off