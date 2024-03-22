> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horn Board (Breakout)
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
Toggle a loud horn upon receiving an  digital signal from the dash board
- What does this board replace?
Direct, Uncontrollable horns connected to Dashboard, unsafe, error might occur. 
- One or two more bullets (if necessary) talking about other things this board does
  Horn Breakout Board receives +24 voltages from the Low Voltage Bus
  Turn Horns on upon digital signal tells to do so, else off
- Other board integration (List other boards and communication protocols)
	- digital GPIO
- Wiki page: [add link to page]

## High-Level Requirements
- Microcontroller (list microcontroller if the board has one)
	- No Microcontroller
- Digital Signal On/Off


## Communication Protocols
- GPIO
	- Used for Digital Signal to toggle Horn On/Off
- List each communication protocol used to send data to/from other systems or boards
	- Does this board need external components to process data using this protocol?
	- List any requirements needed to properly implement this protocol on the board
- Do not list communication protocols that will be used to connect different components within this PCB unless there is a reason to restrict the board design to a specific protocol

## Connectors
- 1 Connector for Power in
- 1 Connector for Horn Control (digital signal from dash)
- 2 Connector for Horns Out in Series
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
 - Power In (1x3 pin)
	- GND
	- +24V
	- GND
 - Horn Control(1x2pin)
	- GND
	- Net Label
 - Horn Out (1x2pin)
	- HORN_IN to 24V

## ICs
- no ICs

## Buttons/Switches
- 1 Button used to debug the board 
	- Enable Horn upon press

## Power System
- List each source that the board will need to function within the scope of this document
	- Where does this voltage originate?

	- List what protection this power supply needs
	- List any other requirements for this rail
- List specific details in the wiki documentatison
- +24V from Low Voltage Bus
## Test Points
- Which signals should have test points?
- Power Supply
- GND
- GPIO Pin
- Horn Out (In & Out)
- Mosfet (Before & After)
- Around the Fuse
- LEDs


## LED Indicators
- 4 default debug LEDs 
