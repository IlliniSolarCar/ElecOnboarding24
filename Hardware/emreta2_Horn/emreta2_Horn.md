> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
- Solar Car Horn Controller
**Board Requirements**



## Overview and Description
- This board controls flow of current to the car horn
- Protocols:
	- Digital GPIO for controlling horn on/off
	- 24V input for horn

## High-Level Requirements
- Horn on/off, digital singal
- Horn output, 24V at 150mA

## Communication Protocols
- Receives a single GPIO signal

## Connectors
 - Connectors:
	- Power In
	- Horn Control
	- Horn out * 2

 - Power In (KK 2.54)
	- GND
	- +24V
	- GND
-  Horn Control
	- GND
	- +3.3V
- Horn out (for both)
	- +12V
	- GND
	- Since there are two horns in series, each will have 12V across both terminals

## ICs
- No ICs

## Buttons/Switches
- A single push button, placed in series with control MOSFET to debug faults with transistor

## Power System

- 24V from cars' LV bus
	- Requires one 2A fuse

## Test Points
- HORN_CONNECTION test point for voltage at the wire connecting horns in series.
- MOSFET HORN_IN test pad
- MOSFET HORN_CONTROL test pad

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
- One LED for GPIO receive