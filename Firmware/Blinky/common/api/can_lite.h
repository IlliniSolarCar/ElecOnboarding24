/*
 * can_lite.h
 * Lightweight CAN definitions where mbed is not present.
 */

#ifndef COMMON_API_CAN_LITE_H_
#define COMMON_API_CAN_LITE_H_

#ifndef MBED_CAN_HELPER_H

#include <string.h>

enum CANFormat {
    CANStandard = 0,
    CANExtended = 1,
    CANAny = 2
};
typedef enum CANFormat CANFormat;

enum CANType {
    CANData   = 0,
    CANRemote = 1
};
typedef enum CANType CANType;

struct CAN_Message {
    unsigned int   id;                 // 29 bit identifier
    unsigned char  data[8];            // Data field
    unsigned char  len;                // Length of data field in bytes
    CANFormat      format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
    CANType        type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
};
typedef struct CAN_Message CAN_Message;

/** CANMessage class
 */
class CANMessage : public CAN_Message {

public:
    /** Creates empty CAN message.
     */
    CANMessage() : CAN_Message() {
        len    = 8;
        type   = CANData;
        format = CANStandard;
        id     = 0;
        memset(data, 0, 8);
    }

    /** Creates CAN message with specific content.
     */
    CANMessage(int _id, const char *_data, char _len = 8, CANType _type = CANData, CANFormat _format = CANStandard) {
      len    = _len & 0xF;
      type   = _type;
      format = _format;
      id     = _id;
      memcpy(data, _data, _len);
    }

    /** Creates CAN remote message.
     */
    CANMessage(int _id, CANFormat _format = CANStandard) {
      len    = 0;
      type   = CANRemote;
      format = _format;
      id     = _id;
      memset(data, 0, 8);
    }
};

#endif // MBED_CAN_HELPER_H

#endif /* API_CAN_LITE_H_ */
