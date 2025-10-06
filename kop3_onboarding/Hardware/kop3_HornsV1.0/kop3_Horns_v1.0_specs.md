> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Breakout Board

**Board Requirements**


## Overview and Description
- What is the primary function of this board?

The primary function of the Horn Breakout Board is to allow the driver to power the electronic horn from the Dash Board. This is done by taking in a digital signal from the Dash Board and sending +24V to the Electronic Horn from the Low Voltage Bus if the signal is high. 


- What does this board replace?

The board dosen't replace anything it is a neccessity for the driver to be able to turn the horn on and off from the drivers seat. 


- Wiki page: [(https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025#Planned_Dates_and_Deadlines)]

## High-Level Requirements
- There will be a Horn On/Off which will be a digital signal from the Dashboard for determining whether or not the horn should be on. 
	- A Horn Output from the Low Voltage Bus which will output 25V at 150mA that powers two horns in series
	- How will this board be programmed?
		- N/A

## Communication Protocols
- List each communication protocol used to send data to/from other systems or boards
	- We will use a digital GPIO coming from the dashboard to switch the horn on and off.

## Connectors
 - Power In (KK 2.54)
	- GND
	- +12V
	- GND
 - Horn Control
 - Two Horn Outs linked in series 

## ICs
- No IC's 

## Buttons/Switches
- Button will be connected to High Voltage and Horn Control. If pressed circuit will complete and horn should turn on without having to press a button from the dashboard, thus debugging the circuit of failures from the dash board and MOSFET. 

## Power System
- Power System is 24V from the Low Voltage Bus
	- 2A Fuse 
	- Three .1uF capacitors
	- Two 1 uF capacitors
	- Two 10 uF capacitors 
	- 1 100 uF polarized radial capacitor in parallel 
	- Rectifier Diode from HORN_IN to +24V
		- Prevent shorting power to GND

## Test Points
- Horn_1
- Horn_2
- Horn_Control
- Horn_IN

## LED Indicators
- HORN_CONTROL
- HORN_IN 
