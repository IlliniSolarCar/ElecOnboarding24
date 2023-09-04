# CAN
CAN (Controller Area Network) message protocols for Electrical and telemetry systems

# Adding a new CAN message
## When should you create a new CAN message?
A new CAN message should be added when a new piece or set of information needs to be transmitted on the CAN bus. If you're starting to code a board from scratch, updating it to work on Brizo or adding a new feature you'll likely need to add new messages. 

It's important that this system is well organized as these messages touch all the boards on the car as well as the Telemetry and strategy system.

## How to chose an ID for your message
CAN messages are sent on the bus with priority given to the lowest ID message ready to be sent. Therefore each board is allocated values in multiple different ranges so that their messages can be given appropriate priority while still being numbered together. Messages should be assigned IDs based on the following:

- 0x0##
    - High Priority / low frequency messages for example, heart beats or messages sent infrequently such as errors and warnings
    - 0x03# BMS
        - 31 BMS Error
        - 32 BMS Warning
        - 33 BMS stats/ configuration
        - etc.
    - 0x04# PDS
    - 0x05# Dash
    - 0x06# MPPT
    - 0x07# Steering Wheel
    - 0x08# MCC Right
    - 0x09# MCC Left
        - Note that Brizo will only have one motor but should still be able to be configured to run with both of Argo's motors
    - 0xA# Telemetry
    - 0xB# Datalogger
- 0x1##
    - Reserved for Testing and Chase Car messages
- 0x2##
    - Critical Power and Drive messages
    - 0x23# Battery
        - For example High low temperatures, current
    - 0x24# PDS info
    - 0x25#, 0x26# Drive Info

- 0x3##
    - Ancillary Control messages for example lights and buttons
- 0x4##
    - Diagnostics info and Raw data
- 0x560 to 0x5FF
    - Reserved for Derek's Neutrino MPPTs
- 0x7F0 to 0x7FF
    - Reserved for Wavesculptor MPPTs
- 0xFxx
    - Calculated Telemetry interface values
If you have any questions do not be afraid to ask on Slack in #elec-code or another appropriate channel.

## What files do you need to change?
### can_id.h
In this file you must add the message name and corresponding ID and rate within the BRIZO_CAN namespace. For example if you were writing code for the dash and the message contained the temperature you create something like
`constexpr can_message_info DASH_TEMP {0x443, 1000000};`
in the curly brackets the first value is the Message ID and the second value is the rate in microseconds. if the message has no regular rate, mark the rate as 0.

### can_data.h
If you'd like to create a message that sends a struct of data or has an enumeration or bitmap, you should add that struct and information to this file within the BRIZO_CAN namespace so that it can be used across projects to make and unpack messages on different boards.

### canDef.json
This file is used by the Telemetry application to decode messages for debugging and diagnostics to create a new message here copy the format of an existing message like this:
```
"0x590": {
    "Source": "Neutrino",
    "DataName": "NEUTRINO0_TEMP",
    "DataFormat": "Uint32LE",
    "Destination": "debug",
    "DataQty": 1,
    "ValueNames": ["Temp Deg C"]
    "Interval": 500,
    "Description": "mppt temperature",
    "Multiplier": 0.001,
    "Units": "C"
  },
```

The message ID in hex as text is the key to the json entry, this should always be 3 digits, ie: 0x032, 0x324, 0x005

- `Source:` 
    - String. optional but recommended.
    - The source is the name of the board that the message comes from.

- `DataName:` 
    - String. Important.
    - This should match the name created in can_id.h

- `DataFormat:` 
    - String or Array of Strings. Important.
    - This describes the data type of the data.
    - If multiple data types are used then they should `DataFormat` should be an array of length `DataQty` 
    - it is important that this is correctly written (case matters!) so that it can be properly decoded within the Telemetry application. 
    - The Data types currently handled by the Telemetry system are
        - FloatLE
        - Uint64LE
        - Int64LE
        - Uint32LE
        - Int32LE
        - Uint16LE
        - Uint16
        - Int16LE
        - Uint8
        - Uint8LE
        - BitMap8LE
        - BitMap16LE
        - BitMap32LE
    - LE Describes the data as being Little Endian. Decoding is handled in Server/ParseData.js

- `Destination:` 
    - String. optional but recommended.
    - Where is this message being sent? if it is important to another board list that here, otherwise write debug or something else more descriptive.

- `DataQty:` 
    - Integer. Important.
    - The number here describes the number of values within the message for example if the message contained an array of 4 temperatures, `"DataQty": 4,`

- `ValueNames:`
    - String or Array of Strings. optional, recommended if applicable.
    - Especially if multiple values are sent in a single message, each value can be given its own name in this field as an array

- `Interval:` 
    - Integer. optional but recommended.
    - The period at which the CAN message is sent. If not sent at a regular interval use `-1`

- `Description:` 
    - String. optional but recommended.
    - more details describing what this message contains can be described here.

- `Multiplier:` 
    - Number or Array of Numbers. optional. Default: 1. 
    - Before being displayed in telemetry the values will be multiplied by these values. if DataQty is greater than 1 an array of multipliers should be specified if a multiplier is needed. for example if the message contains 2 voltages sent as 8bit mV values and you'd like them to be displayed in volts `"Multiplier": [.001, .001],` It is preferred that messages are in SI units after being multiplied by this multiplier

- `Units:` 
    - String or Array of Strings, optional, recommended if applicable.
    - For floats and Ints use a string the unit the value will have after being multiplied by the `Multiplier`
    - If `DataQty` is greater than 1 put the units in an array. For example if there are 3 numbers `["s", "km", "s"]`
    - For bit maps instead of a string utilize an array of strings with strings describing each bit with the most significant bit first. Unused bits should have unit empty string: `""`. 
        - For example if the value has a single 8 bit bit map `"Units": ["MSB", "Bit7", "", "", "", "", "", ""]` In this case only the two most significant bits are being used
        - as another example if there is a bit mask and integer sent in the same message: `"Units": [["", "Bit7", "", "", "", "", "", "LSB"], "Dogs"]`
    - for enums an object should specify the mapping of the enumeration for example `"Units": {"0":"OK", "1":"WARNING", "2": "ERROR"}` the exact words used here should match that used in `can_data.h` if other data types are in the same message nest the object into an array.

## CAN Schema
The can schema will validate any changes made to canDef.json. When you commit and push a change to canDef.json, github will run an action validating the new json. If the job fails (i.e. the json doesn't match the can schema) github will send a notification. If you think you think there is a format that should be valid, but isn't, also message in #strategy-telemetry. It is not completely comprehensive so it should be thought of as the minimum standard for valid json. Required fields are Source, DataName, and DataFormat but other fields are also validated. 
- For DataFormat, the schema includes all fields that are currently in the canDef, but this does not necessarily include all fields we might want. If you need a new data format, add it to the list in schema.json, and message in #strategy-telemetry so the strategy team can add that field to the decoding process. 
- For Source, the schema includes sources that we currently thought of. If your validation fails because the source doesn't match, check schema for valid sources and if possible match one of those. If the source is not included in that list, you may add it.