> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
**Board Requirements**


## Overview and Description
- This board functions to sound the horn of the car
- Wiki page: [\[add link to page\]](https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025#Project_1:_LED_Circuit)

## High-Level Requirements
- Board should take in a digital signal for whether the horn is on or off
- Horn outputs 24V at 150 mA
- Microcontroller: LPC154X
- Horn will be programmed through a gate connection in the microprocessor connected to a switch
- Button controlling horn sound

## Communication Protocols
- Utilizes a digital signal through the microprocessor gate (a basic high-low signal)

## Connectors
 - Power In: 1x3 pin connector, GND +24 GND, nominal 150mA
 - Control: Signal and GND
 - Outputs: 2x 1x2 pin connectors, one horn (power/gnd) for each ofthe connectors, nominally 150mA
 - Outputs: 2x 1x2 pin connectors, one horn (power/gnd) for each ofthe connectors, nominally 150mA, direction doesnt matter
 - this design uses molex connectors kk-254 connectors but they can be substituted for whatever connector is actually needed, holes for connectors
 - are 0.1 inch spaced

## ICs
-  n/a

## Buttons/Switches
- One button controlling the sound of the horn. This is connected to the microcontroller, as if the button is pushed down, it should turn off the microcontroller, which in turn supplies the gate with 3.3V, making the horn sound turn on

## Power System
- Voltage supplied from a 24 LV bus, a 2A fuse, and a flyback diode

## Test Points
- We will have a test point for the signal and the voltage going through

## LED Indicators
- Red led indicates 24V is plugged in, green led indicates microcontroller signal is going through
