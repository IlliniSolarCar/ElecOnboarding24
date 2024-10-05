> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.


# Horns Board
**Evan Hsieh**


## Overview and Description
- What is the primary function of this board?
- What does this board replace?
- One or two more bullets (if necessary) talking about other things this board does
- Other board integration (List other boards and communication protocols)
	- Board 1 (CAN)
	- Board 2 (USB)
- Wiki page: [add link to page]

## High-Level Requirements
- Horn on/off, will be a digital signal for on/off status
- Horn output of 24V at 150mA
- 2 electronic air horns; specs: https://www.rootsautomotives.com/horn-manufacturer-in-india/electronic-horn/

## Communication Protocols
- Digital GPIO to switch the horn

## Connectors
 - Power in
 - Horn Control
 - 2 Horn outs linked in series

## Buttons/Switches
- Debugging button; specs: https://www.digikey.com/en/products/detail/same-sky/TS02-66-70-BK-100-LCR-D/15634375?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=Pmax_Shopping_DK%2B%20Supplier_ITECH&utm_term=&utm_content=&utm_id=go_cmp-21147141757_adg-_ad-__dev-c_ext-_prd-15634375_sig-Cj0KCQjw3vO3BhCqARIsAEWblcALr4Cbwqk8Okk8HEPLNASxdI8qeANf1vjlA7RhO_tmaZV7-XqG_OEaAvGxEALw_wcB&gad_source=1&gclid=Cj0KCQjw3vO3BhCqARIsAEWblcALr4Cbwqk8Okk8HEPLNASxdI8qeANf1vjlA7RhO_tmaZV7-XqG_OEaAvGxEALw_wcB

## Power System
- 24V power system from the LV Bus

## Test Point
- Test point; specs: https://www.digikey.com/en/products/detail/koa-speer-electronics-inc/RCUCTE/11476561


