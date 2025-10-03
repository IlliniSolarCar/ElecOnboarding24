> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Solar Car Horns
**Board Requirements**


## Overview and Description
- Primary function: to control the horns on the solar car
- Replacement for: N/A
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025

## High-Level Requirements
- A horn on/off based on a digital signal
- A horn output of 24 V at 150 mA

## Communication Protocols
- Digital GPIO to switch the horn

## Connectors
 - Power In (KK 254)
	- GND
	- +24V
	- GND
 - Horn Control (KK 254)
	- GND
	- Digital Signal
 - Horn Output 1 (KK 254)
	- GND
	- +24V
 - Horn Output 2 (KK 254)
	- GND
	- +24V

## ICs
- None

## Buttons/Switches
- None

## Power System
- 24 V from LV Bus

## Test Points
- N/A

## LED Indicators
- N/A
