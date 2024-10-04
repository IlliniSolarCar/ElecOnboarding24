> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Breakout Board
**Board Requirements**


## Overview and Description
- The function of this board is to power the electronic horn.
- It will get +24V from the Low Voltage Bus Board and a digital signal from the Dash Board to sound a very loud horn
- Wiki page: [https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2024]

## High-Level Requirements
- A Horn On/Off which will be a digital signal for whether or not it should be on
- A Horn Output which will output 24V at 150mA

## Communication Protocols
- Digital GPIO to switch the horn

## Connectors
- Power In
- Horn Control
- 2 Horn outs linked in series

## ICs
None

## Buttons/Switches
None

## Power System
- 24V from the LV Bus

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
