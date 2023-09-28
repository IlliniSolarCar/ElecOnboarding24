> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name: Horns
**Board Requirements**


## Overview and Description
- Sounds 2 very loud horns
- This is the Horn Breakout Board

## High-Level Requirements
- Horn On/Off - a digital signal for whether or not the horn should be on
- Horn Output - 24V at 150mA

## Communication Protocols
- Digital GPIO

## Connectors
- Power In
- Horn Control
- 2 Horn Outs in series

## Buttons/Switches
- Button for debugging

## Power System
- 24V from the LV Bus

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
