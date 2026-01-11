> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


Horns Board
**Board Requirements**


## Overview and Description
Horns board to power electric horns. replaces old horns board.
	- receives 24V from Low Voltage Bus Board
	- receives digital signal from the Dash Board indicating when to sound the horn
	- link to Horn specs:

## High-Level Requirements
	- A Horn On/Off which will be a digital signal for whether or not the horn should be on
	- A Horn Output which will output 24V at 150mA

## Communication Protocols
	- Digital GPIO to switch the horn

## Connectors
	- Power in
	- Horn Control
	- 2 Horn outs in series

## Buttons/Switches
	- Board Debug Button

## Power System
	- 24V from LV Bus

## LED Indicators
	- LED to Horn Control
