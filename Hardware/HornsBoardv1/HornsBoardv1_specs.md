> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
Horns Board


## Overview and Description
- The function of this board is to make a loud horn sound from a digital signal.
- There will be two of these horn boards in series.

## High-Level Requirements
- A digital signal to turn the horn on and off
- A horn output which outputs 24V at 150mA

## Communication Protocols
- A digital GPIO is used to switch the horn

## Connectors
 - Power In 01x03 pin
	-GND
	-+24V
	-GND
 - Horn Control
	-GND
	-Net Label
 - 2 Power Outs
	- Connected in series
	-Horn in
	-24V 

## ICs
 - No ICs

## Buttons/Switches
- Button used to debug the board

## Power System
- 24V
	- from LV Bus
- List specific details in the wiki documentation

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
