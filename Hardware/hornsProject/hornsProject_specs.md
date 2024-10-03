> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name: Horns Project
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
- What does this board replace?
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2024]

## High-Level Requirements
- A Horn On/Off that is operated by a digital signal indicating whether the horn should be on or off

- A Horn Output which will output 24V at 150mA (the signal to activate the horn)
## Communication Protocols
- A digital GPIO is used to switch the horn on and off
## Connectors
- Power in
- Horn Control
- 2x Horn Out in series with each other

## Buttons/Switches
- A button may be used to debug the board

## Power System
- 24V from the LV Bus

## LED Indicators
- Not sure yet, will update later
