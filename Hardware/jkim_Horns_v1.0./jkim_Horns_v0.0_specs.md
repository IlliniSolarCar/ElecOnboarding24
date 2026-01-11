> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Breakout Board
**Board Requirements**


## Overview and Description
The primary function of this board is to power the electronic horn.
- Wiki page: [https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025]

## High-Level Requirements
- A Horn On/Off which will be a digital signal for whether or not it should be on
- A Horn Output which will output 24V at 150mA

## Communication Protocols
A digital GPIO will be used to switch the horn. 

## Connectors
There are 4 connectors on this board. 
 - Power In (KK 2.54)
	- GND
	- +24V
- Horn Controll
- Horn Out (2x)
	- Linked in Series

## ICs
There are no ICs for this board

## Buttons/Switches
A button can be added to debug the board, but this board does not have one.

## Power System
- 24V from the LV bus

## Test Points
- Which signals should have test points?

## LED Indicators
General LEDs can be used for debug and status to show that firmare, CAN, power, etc. is working. 
