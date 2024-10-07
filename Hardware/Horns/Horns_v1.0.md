> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
Horns Board
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
    - powers an electronic horn
- Other board integration (List other boards and communication protocols)
	- +24V from Low Voltage Bus Board
	- digital signal from Dash Board
- Wiki page: [(https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2024)]

## High-Level Requirements
- List any features this board must have
	- digital signal for Horn On/Off
    - Horn Output of 24V at 150mA

## Communication Protocols
- List each communication protocol used to send data to/from other systems or boards
	- digital GPIO

## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
    - Power in
    - Horn Control
    - 2 Horn outs

## ICs
- Only list specific ICs if the board require this specific component to work
- If you do list an IC here, use the following format:
- Component part number
	- Datasheet (must be direct hyperlink to datasheet)
	- One-line description of part
	- Communication protocols used (if any)

## Buttons/Switches
- If the board needs buttons, describe what they do and how they will connect to the board

## Power System
- List each source that the board will need to function within the scope of this document
	- 24V from LV Bus
## Test Points
- Which signals should have test points?    

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
