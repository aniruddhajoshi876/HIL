/*
*   File       : CAN_Message_Definition.h
*   Description: This file includes the common CAN message assembly, defined by Mathworks.
*   Version    : $Revision$
*   Author     : $Author$
*   Date       : $Date$
*/

#ifndef __CAN_MESSAGE_DEFINITION_H__
#define __CAN_MESSAGE_DEFINITION_H__

#include <stdint.h>

/*
    CAN message assembly.
*/
typedef struct CANMsg_T
{
    uint8_t Extended;   // CAN message has a 11 bit standard identifier (=0) or a 29 bit estended identifier (=1)
    uint8_t Length;     // Length in byte of the CAN message data (DLC)
    uint8_t Remote;     // n/a
    uint8_t Error;      // n/a
    int32_t ID;         // CAN message ID.
    double Timestamp; // Timestamp is set by the CAN controller if the message was received.
    uint8_t Data[8];    // CAN messae data array.
} CANMsg;

#endif // !__CAN_MESSAGE_DEFINITION_H__
