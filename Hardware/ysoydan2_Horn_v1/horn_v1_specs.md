
# Horn Board
**Board Requirements**


## Overview and Description
- Prime function: this horn board powers and controls the car's electronic horn system. It takes +24V supply from the LW BUS and a digital control signal from the Dash Board enable or disable the horn.
- What it replaces: Provides a reliable functioning horn.
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration;
	- LV Bus Board(+24V power)
	- Dash Board(digital GPIO control signal)
	-No data comm.
- Wiki page: https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025#Welcome_to_Illini_Solar_Car.21


## High-Level Requirements
- Microcontroller:NA
- Required features:
	- Accept 24 Volts from the LV Bus
	- Accept digital GPIO control input from Dash
	- Connect two horns in series
	- MOSFET-based switching circuit for horn on/off
	- Fuse protection
	- Capacitors for noise supression and stability
	- Test/debug points
	- Diode to prevent reverse conduction

## Communication Protocols
- Digital GPIO
	- Input from Dash Board controls the horn with a MOSFET gate
	- No ICs
	- RC filtering with 1kohm and 0.1microFarad to reduce noise 
- No serial communication protocols

## Connectors
 - Power In
	- GND 
	- +24V
	- GND
- Horn Control
	- GND
	- HORN_CTL
- Horn Out A
	- HORN_IN
	- HORN_OUT_A
- Horn Out B
	- HORN_OUT_A
	- +24V

## ICs
- No ICs
- Discrete Components
	- IRFR010PBF 
	- ES2DA-13-F

## Buttons/Switches
- Debug button:
	- connects control pin to logic high to simulate the Dash Board signal

## Power System
- Input: +24V from LV Bus Board.
- Output: +24V up to 150 mA to horn.
- Protection: 2 A fuse in series with horn output, rectifier diode (ES2DA-13-F or equivalent) between HORN_IN and +24 V.
- Noise reduction: Decoupling capacitors across +24 V/GND (0.1 microF, 1 microF, 10 microF, 100 microF).

## Test Points
- +24 V input
- GND
- HORN_CTL
- HORN_IN / horn output

## LED Indicators
- Default ISC Debug LEDs (4 total):
- Power (+24V alive)
- Horn Control (GPIO active)
- Horn Output active (after MOSFET + fuse)
- Fault indicator (fuse open or diode conducting abnormally)