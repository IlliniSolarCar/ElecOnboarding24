> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
HORNS
**Board Requirements**


## Overview and Description
- Turns on output to car horn when digital signal is received from Dash Board
- Outputs 24V at 150mA


- What is the primary function of this board?
- What does this board replace?
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [add link to page]

## High-Level Requirements
NONE

## Communication Protocols
GPIO pins are used to receive incoming signals and to send signals from horn control to downstream horn output boards

- List each communication protocol used to send data to/from other systems or boards
	- Does this board need external components to process data using this protocol?
	- List any requirements needed to properly implement this protocol on the board
- Do not list communication protocols that will be used to connect different components within this PCB unless there is a reason to restrict the board design to a specific protocol

## Connectors
- Power In (KK 2.54mm)
	- GND
	- +24V
	- GND
- Horn Control (KK 2.54mm)
	- GND
	- HORN_CTRL
- Horn Out 1 (KK 2.54mm)
	- HORN_IN
	- Horn Out 2
- Horn Out 2 (KK 2.54mm)
	- +24V
	- Horn Out 1


 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
 - Power In (KK 2.54)
	- GND
	- +12V
	- GND

## ICs
NONE


## Buttons/Switches
- If the board needs buttons, describe what they do and how they will connect to the board

## Power System
+24V Bus In from LV Bus

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
