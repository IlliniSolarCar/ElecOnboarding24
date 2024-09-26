> This template is a general guideline for ISC board specifications. Your board spec should be a high-level overview of what functions the board must have. This document should describe the features of a board, not how the board will be made. This should read like something a non-engineer could look at and understand what this board will do.

> A well-designed board specification should also contain enough information that a reasonably experienced board designer could read the project requirements and design the PCB from scratch. The implementation details should be left up to the person that will actually be designing and making the board.

# Horns Board

**Board Requirements**

## Overview and Description

- What is the primary function of this board?
  - Sound a loud horn, controlled by the dashboard
- What does this board replace?
- Other board integration (List other boards and communication protocols)
  - Dashboard (digital)
- Wiki page: [add link to page]

## High-Level Requirements

- 2 Horns
- Horn On/Off (digital signal)
- Horn Output (24V at 150mA)

## Communication Protocols

- Digital GPIO

## Connectors

- List any general requirements for connectors here (e.g. no through-hole, low-profile, minimum 1A current capacity, etc.)
- Then list each connector, specific type/requirements, and pinout such as:
- Power In (KK 2.54)
  - GND
  - +24V
  - GND
- Horn Control
- 2 Horn Outputs (linked in series)

## ICs

- None

## Buttons/Switches

- Manual horn debug

## Power System

- +24V from Low Voltage Bus Board

## Test Points

- +24V
- GND
- Horn Control
- Horn Output

## LED Indicators

- Horn Output
