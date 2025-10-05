# Horns Board
**Board Requirements**
We will have 2 of these horns ​ in series, so it would be nice to add the link to the specs
We will have 2  main High-Level Requirements
A Horn On/Off which will be a digital signal for whether or not it should be on
A Horn Output which will output 24V at 150mA
As far as communication protocols, we use a digital GPIO to switch the horn
We will have 4 connectors for the board
Power in
Horn Control
And then 2 Horn outs linked in series
There are will be no ICs
You can choose to add a Button that would be used to debug the board
The power system is 24V from the LV Bus
You should add test points to any net you would like to add
You can add LED Indicators to any net you would like

## Overview and Description
We will be having you design a board that we really use on the car. This is the Horn Breakout board which we use to power the electronic horn. It will get +24V from the Low Voltage Bus Board and a digital signal from the Dash Board to sound a very loud horn. You will be going through the whole process, from Specs to Schematic to Layout.


## High-Level Requirements



## Communication Protocols


## Connectors
The first thing to set up for the schematic is the connectors
You will need a 1x3pin connector for power, we use 3 pin connectors for Power so that they do not get plugged in backwards. We put +24V in the middle and two GND pins on the outside
You will want a 1x2pin connector for Horn Control. We want 1 pin to be grounded and another to be connected to a "Net Label" (Click L to add one). Give it a meaningful name
You will want two 1x2pin connectors for Horn Out. You need to link them together in series, from HORN_IN to 24V.
You will next want to add a way of switching from "on to off." To perform a switch at this level, we use a MOSFET. We recommend using the IRFR010PBF (this is the MPN), but you can go to octopart.com to find replacements.
Source should be tied GND, Drain should be tied to the HORN_IN of the series connectors, and Gate should be tied to the horn control net label you created earlier.
You will want a 1k ohm resistor and a .1uF capacitor between HORN_CTL and GND before it reaches the MOSFET to help with noise reduction.
Between the MOSFET and the connectors, add a 2A fuse.
The next thing to add are capacitors between +24V and GND
We recommend adding 3 .1uF capacitors, 2 1uF capacitors, 2 10uF capacitors, and 1 100uF polarized radial capacitor in parallel
Finally, you will want to add a rectifier diode from HORN_IN to +24V to ensure we do not short power to ground. You can use ES2DA-13-F or find an alternative from octopart.com.

## ICs


## Buttons/Switches


## Power System


## Test Points


## LED Indicators

