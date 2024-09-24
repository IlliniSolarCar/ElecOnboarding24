> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Project
**Board Requirements**
## Overview and Description
- What is the primary function of this board?
	Control 2 horns
- What does this board replace?
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [add link to page]

## High-Level Requirements
- Microcontroller (list microcontroller if the board has one)
- List any features this board must have
	Horn on off digital signal
	Horn output of 24V at 150 mA

## Communication Protocols
- Digital GIPO

## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
 - Power In (KK 2.54)
	- GND
	- +24V
	- GND
 - Horn Control
 - 2 Horn outs in series

## ICs


## Buttons/Switches

## Power System
 - LV Bus

## Test Points
 - Horn On/Off
 - Horn output

## LED Indicators

