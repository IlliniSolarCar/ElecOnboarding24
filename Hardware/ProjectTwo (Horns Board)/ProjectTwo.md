> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horns Board
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
	Horn Breakout Board to power the electronic horn.
- What does this board replace?
	The Horn Breakout board.
- One or two more bullets (if necessary) talking about other things this board does
	Recieves +24V from the Low Voltage Bus Board and a digital signal from the Dash Board to sound a loud horn.
- Other board integration (List other boards and communication protocols)
	- Dash Board (CAN)
	- Low Voltage Bus Board (USB)
- Wiki page: [https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2025#.28Challenge.29_Project_2:_Horns_Board]

## High-Level Requirements
- Microcontroller (list microcontroller if the board has one)
	- Hyperlinked microcontroller name
		- MCU must be either LPC154X (USB-enabled) or LPC151X (no USB) unless there is a necessary reason to use something else
	- List any specific configuration requirements 
	- How will this board be programmed?
	- List any buttons or switches that control signals to or from the microcontroller

- List any features this board must have
	A Horn On/Off
	- A digital signal for whether the horn should be on or not.
	A Horn Output
	- Outputs 24V at 150mA
	link: [https://www.sameskydevices.com/product/resource/cps-5449-105pm.pdf]



## Communication Protocols
- List each communication protocol used to send data to/from other systems or boards
	Digital GPIO switch, to switch horn.
	- Does this board need external components to process data using this protocol?
	- List any requirements needed to properly implement this protocol on the board
- Do not list communication protocols that will be used to connect different components within this PCB unless there is a reason to restrict the board design to a specific protocol

## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
	Power in 
	Horn Control
	Horn Outs, x2 linked in series 
 - Power In (KK 2.54)
	- GND
	- +12V
	- GND

## ICs
- Only list specific ICs if the board require this specific component to work
- If you do list an IC here, use the following format:
- Component part number
	- Datasheet (must be direct hyperlink to datasheet)
	- One-line description of part
	- Communication protocols used (if any)

## Buttons/Switches
- If the board needs buttons, describe what they do and how they will connect to the board

## Power System
- List each source that the board will need to function within the scope of this document
	24V from LV Bus
	- Where does this voltage originate?
		LV Bus
	- List what protection this power supply needs
	- List any other requirements for this rail
- List specific details in the wiki documentation

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
