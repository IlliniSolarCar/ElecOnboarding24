> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horns Board
**Board Requirements**


## Overview and Description
- The primary function of this board is to control and drive two vehicle horns connected in series.
- This board receives a digital On/Off control signal to activate or deactivate the horns.
- The board outputs 24V at 150mA to power the horns.
- Other board integration (List other boards and communication protocols)
	- Main Control Board (GPIO)
- Horns specifications link: [insert horn datasheet link here]
- Wiki page: [add link to page]


## High-Level Requirements
- Microcontroller (list microcontroller if the board has one)
	- *None required* – this board operates using discrete components and a digital GPIO control signal.
	- No programming interface is necessary.
	- Optional: include a debug button for manual horn activation testing.
- List any features this board must have
	- **Horn On/Off Control:** A digital GPIO input determines whether the horns are active.
	- **Horn Output:** Outputs 24V at 150mA to drive two horns in series.
	- **Optional Debug Button:** Allows manual toggling of the horn output for testing.
	- **Optional LED Indicators:** Indicate power, control signal, and horn activation states.


## Communication Protocols
- **Digital GPIO**
	- Used to receive the horn On/Off control signal.
	- No external data processing or ICs are required.
	- Must be compatible with the controlling system’s GPIO voltage (e.g. 3.3V or 5V logic levels).


## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
	 - All connectors should be rated for at least 24V and 150mA.
	 - Prefer low-profile locking connectors (KK 2.54 or equivalent).
 - Power In (KK 2.54)
	 - GND
	 - +24V (LV Bus Input)
 - Horn Control (KK 2.54)
	 - GND
	 - Horn Control Signal (GPIO)
 - Horn Output 1 (KK 2.54)
	 - +24V Output to Horn #1
	 - GND/Return
 - Horn Output 2 (KK 2.54)
	 - +24V Output to Horn #2
	 - GND/Return
	 - Horn 1 and Horn 2 will be wired in series externally.


## ICs
- None required – this board will use discrete components only (transistors, diodes, resistors, etc.) for switching and protection.


## Buttons/Switches
- One optional momentary push button can be added to manually toggle the horn output for debugging.
- The button connects between the Horn Control line and logic voltage.


## Power System
- Power Source: 24V DC from the LV Bus.
- Protection: Include reverse-polarity and overcurrent protection.
- Power Requirements: 150mA current draw when horns are active.
- No additional voltage rails are needed.


## Test Points
- Horn Control Signal
- 24V Power In
- Horn Output (24V Line)
- Ground


## LED Indicators
- LED 1 – Indicates 24V Power Present
- LED 2 – Indicates Horn Control Signal Active
- LED 3 – Indicates Horn Output Active
- LED 4 – Debug/Status LED (optional)
