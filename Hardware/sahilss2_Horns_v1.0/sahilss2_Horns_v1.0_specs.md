# Horns v1.0 Board Specifications

## Overview and Description
- Manage horn function for the car.
- Take digital input from the car and activate the horn(s)

## High-Level Requirements
- A Horn On/Off which will be a digital signal for whether or not it should be on
- A Horn Output which will output 24V at 150mA

## Communication Protocols
- Horn On/Off will be a digital signal
  - 6v? Logic Level

## Connectors
- 1x3 Input Connector for Power (GND/24V/GND)
- 1x2 Input Connector for Horn On/Off (GND/HORN_CTL)
- 2x 1x2 Output Connector for Horn Output (GND/24V) linked in series

## Parts
- MOSFET (IRFR010PBF)
  - S->GND
  - D->HORN_IN
  - G->HORN_CTL
- Rectifier Diode (ES2DA-13-F)
  - HORN_IN<-24V

## Power System
- 24V Rail
  - Caps (3x .1uF, 2x 1uF, 2x 10uF, 1x 100uF)
  - Source: 24V from the LV Bus

## Additional Components
- 1k ohm resistor and a .1uF capacitor between HORN_CTL and GND for noise reduction
- 2A fuse between MOSFET and connectors

## Test Points
- HORN_IN
- HORN_CTL
- 24V
- GND