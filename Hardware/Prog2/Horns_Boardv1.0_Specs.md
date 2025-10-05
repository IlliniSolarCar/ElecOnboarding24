> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name   Horns Project
**Board Requirements**


## Overview and Description
Powers and controls the vehicle horn. Receives a digital signal from the Dash Board and drives the horn with 24V at 150mA.
Board Replacement: This board replaces the previous Horn Breakout Board used in the solar car.

Other Functions: Provides protection for the horn circuit, filtering for voltage stability, and optional debug/test features.

Board Integration:

Low Voltage Bus Board (LV Bus Board) – provides 24V power.

Dash Board – provides digital GPIO control signal for horn on/off.

## High-Level Requireme	nts
Microcontroller: None required; the board uses a discrete MOSFET switch.

Required Features:
Horn On/Off Control: Accepts digital GPIO signal to switch MOSFET and control horn.

Horn Output: Drives two horns in series at 24V and 150mA.

Protection and Filtering: 2A fuse in series with horn output.

Decoupling capacitors: 3 × 0.1µF, 2 × 1µF, 2 × 10µF, 1 × 100µF radial capacitor.

Resistor (1kΩ) and capacitor (0.1µF) between control signal and ground for noise reduction.

Diode (ES2DA-13-F) from horn input to +24V to prevent reverse current.

Optional Features: Button for manual horn testing. LED indicators for horn status and debug.

## Communication Protocols
Digital GPIO:

Used to switch the MOSFET controlling the horn.

No external components needed except resistor and capacitor for noise suppression.

Must safely handle switching for 24V horn circuit.
## Connectors
 Power In (1×3 pin connector):
Pin 1: GND
Pin 2: +24V
Pin 3: GND

Horn Control (1×2 pin connector):
Pin 1: GND
Pin 2: Horn Control Signal (connects to MOSFET gate)

Horn Output (2×2 pin connectors in series):
Pin 1: HORN_IN (from MOSFET drain)
Pin 2: Horn output to horn device(s)

## ICs
None

## Buttons/Switches
- If the board needs buttons, describe what they do and how they will connect to the board

## Power System
Source: +24V from LV Bus Board.

Protection: 2A fuse in series.

Other Requirements: Decoupling capacitors to reduce voltage spikes and electrical noise.

## Test Points
Horn Control signal

+24V power rail

GND

MOSFET drain (Horn Output)
## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
