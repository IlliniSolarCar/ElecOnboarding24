> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
To power the electronic horn.
- What does this board replace?
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [add link to page]

## High-Level Requirements

A Horn On/Off
A Horn Output (24V) at 150 Ma.

- Microcontroller (list microcontroller if the board has one)
	- Hyperlinked microcontroller name
		- MCU must be either LPC154X (USB-enabled) or LPC151X (no USB) unless there is a necessary reason to use something else
	- List any specific configuration requirements 
	- How will this board be programmed?
	- List any buttons or switches that control signals to or from the microcontroller
- List any features this board must have
	- Describe each feature in a general way
		- (Optional) Describe any requirements this feature might need as open-ended as possible

## Communication Protocols
- List each communication protocol used to send data to/from other systems or boards
	- Does this board need external components to process data using this protocol?
	- List any requirements needed to properly implement this protocol on the board
- Do not list communication protocols that will be used to connect different components within this PCB unless there is a reason to restrict the board design to a specific protocol

## Connectors
Power In
Horn Control
2 Horn outs (linked in series)


## ICs
None


## Buttons/Switches
- If the board needs buttons, describe what they do and how they will connect to the board

## Power System
24Volts
- List each source that the board will need to function within the scope of this document
	- Where does this voltage originate?
	- List what protection this power supply needs
	- List any other requirements for this rail
- List specific details in the wiki documentation

## Test Points
- Which signals should have test points?

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards
