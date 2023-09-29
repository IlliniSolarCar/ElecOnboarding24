> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horns Board
**Board Requirements**


## Overview and Description
- Horn breakout board for horn on the car

## High-Level Requirements
- Horn On/Off which will be a signal for the horn to be on and off
- Horn Output which will output 24V at 150mA

## Communication Protocols
- digital GPIO to switch the horn

## Connectors
 - power in
 - Horn Control
 - 2 Horn outs linked in series

## ICs
- none

## Buttons/Switches
- none

## Power System
- 24V from the LV Bus

## Test Points
- If needed

## LED Indicators
- if needed