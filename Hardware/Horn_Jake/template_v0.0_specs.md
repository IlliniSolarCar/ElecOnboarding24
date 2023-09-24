# Horn Circuit
- Opperates the horn of the car


## Overview and Description
- Operates the horn when provided signal to honk
- Replaces manual need to squeeze/push a horn to make sound
- Wiki page: https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2023#Project_2:_Potentiometer_Blink_Rate

## High-Level Requirements
- Digital signal for when horn is on
- Horn output 24V at 150 mA

## Communication Protocols
- Digital GPIO to switch horn

## Connectors
 - Power In
	- GND
	- +24V
	- GND
 - Horn Control
        - HornToggle (Net Label)
        - GND
 - Horn Out
        - HORN_IN
        - +24V

## ICs
- N/A

## Buttons/Switches
- Manual debug button to test horn

## Power System
- 24V from LV Bus

## Test Points
- Horn Control
- Horn Out
- Power In

## LED Indicators
- LED at Horn Out test point
