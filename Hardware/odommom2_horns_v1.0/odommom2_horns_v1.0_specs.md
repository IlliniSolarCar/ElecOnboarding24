# Board Name 
Horns Board

## Overview and Description
The Horns Breakout board is used to power an electronic horn. 
- The board outputs a very loud horn from +24V from a Low Voltage Bus Board and a digital signal from a Dash Board. 
- Other board integration 
	- GPIO
	- Low Voltage Bus Board
- Wiki page: [add link to page]

## High-Level Requirements
- Requires a digital signal which will indicate whether or not the horn should be on (Horn On/Off).
- Requires a Horn Output which will output 24V at 150mA.

## Communication Protocols
The Horn Breakout board uses a digital GPIO to switch the horn.

## Connectors
4 connectors are used for the board:
 - Power in
  - GND
  - +24V LV BUS
 - Horn Control
  - GND
  - GPIO
 - 2 Horn outs linked in series
  - GND
  - Horn Output

## ICs
None

## Buttons/Switches
None

## Power System
- LV Bus provides 24V to power the board

## Test Points
Test points may be added to any net.

## LED Indicators
LED indicators may be added to any net.