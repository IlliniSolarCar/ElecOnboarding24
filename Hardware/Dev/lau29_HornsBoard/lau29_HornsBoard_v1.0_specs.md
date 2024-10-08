> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horns Board
**Board Requirements**


## Overview and Description
This is a Horn Breakout Board that will be used to power the electronic horn. It will get +24V from the Low Voltage Bus Board and a digital signal from the Dash Board to sound a very loud horn. 
- Other board integration
	- Low Voltage Bus
	- Dash Board
- Wiki page: https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2024

## High-Level Requirements
- A Horn On/Off which will be a digital signal for whether or not it should be on
- A Horn Output which will output 24V at 150mA

## Communication Protocols
Digital GPIO to switch the horn

## Connectors
- Power In
- Horn Control
- 2 Horn outs linked in series

## ICs
NO ICs for this board.

## Buttons/Switches
Buttons will be used to debug the board.

## Power System
24V from the Low Voltage Bus

## Test Points
We will test for the 24V output at Horn Output and check that the board is getting the 24V from the Low Voltage Bus.

## LED Indicators
LED indicators will be used to detect if the board is receiving power and to signal if the horns are functioning.
