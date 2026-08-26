/*
*   File       : CANFD_Message_Definition.h
*   Description: This file includes the common CAN-FD message assembly.
*   Version    : $Revision$
*   Author     : $Author$
*   Date       : $Date$
*/

#ifndef __CANFD_MESSAGE_DEFINITION_H__
#define __CANFD_MESSAGE_DEFINITION_H__

#include <stdint.h>

/*
    Common structure for the CAN-FD message for Matlab.
*/
typedef struct CanFdMessage_T
{
    uint8_t ProtocolMode;   // Is this CAN (0) or CAN FD (1)
    uint8_t Extended;       // Is Extended frame
    uint8_t Length;         // Length
    uint8_t Remote;         // RTR
    uint8_t Error;          // Error
    uint8_t BRS;            // Bit Rate Switch.Possible values 0 or 1. Valid only if ProtocolMode indicates CAN FD
    uint8_t ESI;            // Error State Indicator.Possible values 0 or 1. Valid only if ProtocolMode indicates CAN FD
    uint8_t DLC;            // Data Length Code. Possible values 0-15. Valid only if ProtocolMode indicates CAN FD
    uint32_t ID;            // CAN ID
    uint32_t Reserved;      // Reserved
    double Timestamp;       // Timestamp
    uint8_t Data[64];       // Data field.Indices 8 - 63 (zero - based) are valid only if ProtocolMode indicates CAN FD

} CanFdMessage;


#endif // !__CANFD_MESSAGE_DEFINITION_H__
