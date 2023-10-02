> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
- Horn board
**Board Requirements**
- 2 horns
- On/off switch
- Output for 24V @ 150 mA
- Digital GPIO

## Overview and Description
- What is the primary function of this board?
	- Horn breakout board to power said horn

- What does this board replace?
	- Horn

- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- GPIO 
- Wiki page: [add link to page]

## High-Level Requirements
- On/off digital signal
	- should be on or off?
- Horn output 24V at 150 mA

## Communication Protocols
- GPIO

## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Power in
 - Horn control
 - 2 Horn outputs
	- Series

## ICs
- No ICs

## Buttons/Switches
- If needed for debugging

## Power System
- 24V 
	- From LV Bus
## Test Points
- Added to any net if necessary

## LED Indicators
- If necessary
