

# Horn Breakout Board  
**Board Requirements**

## Overview and Description  
- This board powers and controls two electronic horns in series using a 24V supply and a digital GPIO signal.  
- It replaces manual horn wiring with a controlled breakout board for safe and reliable activation.  
- It filters noise and protects the horn circuit using capacitors, a fuse, and a diode.  
- Other board integration:  
  - Dash Board (GPIO signal)  
  - Low Voltage Bus Board (24V power)  
- Wiki page: [add link to page]

## High-Level Requirements  
- **Microcontroller**: None  
- **Features**:  
  - Accepts a digital signal (`HORN_CTL`) to turn the horn on/off  
  - Outputs 24V @ 150mA to two horns connected in series  
  - Includes a MOSFET switch for horn control  
  - Includes filtering components (capacitor + resistor) for noise reduction  
  - Includes a fuse for overcurrent protection  
  - Optional debug button and LED indicators

## Communication Protocols  
- Digital GPIO signal from Dash Board  
  - No external components needed  
  - Signal must be filtered before reaching the MOSFET gate

## Connectors  
- General Requirements:  
  - Use keyed connectors to prevent reverse plugging  
  - Minimum 1A current capacity  
- **Power In** (1x3, KK 2.54):  
  - GND  
  - +24V  
  - GND  
- **Horn Control** (1x2):  
  - GND  
  - `HORN_CTL`  
- **Horn Out #1** (1x2):  
  - `HORN_IN`  
  - GND  
- **Horn Out #2** (1x2):  
  - +24V  
  - GND

## ICs  
- None required

## Buttons/Switches  
- Optional debug button to manually trigger horn signal  
  - Connects between `HORN_CTL` and GND

## Power System  
- 24V from Low Voltage Bus Board  
  - Must include fuse protection (2A)  
  - Must include parallel capacitors for filtering  
  - Must include diode to prevent reverse current

## Test Points  
- Add test points on:  
  - `+24V`  
  - `GND`  
  - `HORN_CTL`  
  - `HORN_IN`

## LED Indicators  
- Optional LED on `HORN_CTL` to show when horn is active  
- Optional LED on `+24V` to show power is present  
- Include 4 default debug LEDs if space allows

