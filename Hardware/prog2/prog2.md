> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Board Name
**Board Requirements**


## Overview and Description
- What is the primary function of this board?
	-electronic horn
- What does this board replace?
	-???
- One or two more bullets (if necessary) talking about other things this board does
	-not really
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [add link to page]
	-https://wiki.illinisolarcar.com/w/index.php/Public:Electrical_Onboarding_Fall_2024#GitHub_Setup


	- "We will have 2 of these horns ​ in series, so it would be nice to add the link to the specs"

## High-Level Requirements
- 'A Horn On/Off which will be a digital signal for whether or not it should be on"
- "A Horn Output which will output 24V at 150mA"
	
	- List any specific configuration requirements 
	- How will this board be programmed?
	- List any buttons or switches that control signals to or from the microcontroller
- List any features this board must have
	- Describe each feature in a general way
		- (Optional) Describe any requirements this feature might need as open-ended as possible

## Communication Protocols
- "digital GPIO to switch the horn"

## Connectors
 - List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
 - Then list each connector, specific type/requirements, and pinout such as:
 - Power In (KK 2.54)
	- GND
	- +12V
	- GND

- Horn Control
- 2 Horn outs linked in series

## ICs
- no ICs

## Buttons/Switches
- possibly a button for debugging

## Power System
- List each source that the board will need to function within the scope of this document
	- Where does this voltage originate?
	- List what protection this power supply needs
	- List any other requirements for this rail
- List specific details in the wiki documentation

- "The power system is 24V from the LV Bus"

## Test Points
- Which signals should have test points?

- "You should add test points to any net you would like to add"

## LED Indicators
- List any functions that should have an LED to indicate they are doing something. Include the 4 default debug LEDs for ISC boards

- "You can add LED Indicators to any net you would like"
