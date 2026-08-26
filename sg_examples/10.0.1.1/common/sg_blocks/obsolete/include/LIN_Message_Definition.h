/*
*   File       : LIN_Message_Definition.h
*   Description: This file includes the common LIN message assembly.
*   Version    : $Revision$
*   Author     : $Author$
*   Date       : $Date$

*/

#ifndef __LIN_MESSAGE_DEFINITION_H__
#define __LIN_MESSAGE_DEFINITION_H__

#include <stdint.h>

#define LIN_MSG_DATA_LEN 8      // Standard length in byte of the LIN data field

/*
    General LIN message structure for Matlab.
*/
typedef struct LINMsg_T
{
    uint8_t ProtID;                 // LIN portected ID
    uint8_t IDOnly;                 // LIN ID only
    uint8_t Type;                   // LIN message type
    uint8_t EnhcdCksm;              // LIN enhanced checksum
    uint8_t PsblDataOvrn;           // LIN possible data overrun
    uint8_t Len;                    // LIN data length
    uint8_t Data[LIN_MSG_DATA_LEN]; // Datafield of the LIN message
    uint32_t TimeStamp;             // Timestamp of the received LIN message in ms
    
} LINMsg;

typedef struct LINMsg2_T
{
    LINMsg msg;
    uint8_t senderOfResponse; // for enabling/disabling messages of msg.ProtID in LIN slave.
    
} LINMsg2;

#define IO61X_LEN_LIN_MSG_DATA_FLD 8 // Standard length in byte for a LIN message.

/*
    Union for the LIN message information with byte and bix access.
*/
typedef union LinMessageInfoObject_U
{
    struct
    {
        uint8_t ProtectedID;    // LIN portected ModuleID
        uint8_t Type;           // LIN message type
        uint8_t Length;         // LIN data length
        uint8_t Flags;          // LIN message flags

    } Bytes;

    struct
    {
        uint32_t ProtectedID : 8;           // LIN protected ModuleID (8 bit)
        uint32_t Type : 8;                  // LIN message type (8 bit)
        uint32_t Length : 8;                // LIN data length (8 bit)
        uint32_t EnhancedChecksum : 1;      // LIN enhanced checksum (1 bit)
        uint32_t SenderOfResponse : 1;      // LIN sender of response (1 bit)
        uint32_t PossibleDataOverrun : 1;   // LIN possible data overrun (1 bit)
        uint32_t IDOnly : 1;                // LIN ModuleID only (1 bit)
        uint32_t Reserved : 4;              // Reserved, currently not used (4 bit)

    } Bits;

} LinMessageInfo;

/*
    Structure for the LIN message.
*/
typedef struct LinMessageObject_T
{
    uint32_t TimeStamp;                         // Timestamp of the received LIN message in ms
    LinMessageInfo Info;                   // Message information
    uint8_t Data[IO61X_LEN_LIN_MSG_DATA_FLD];   // Datafield of the LIN message

} LinMessage;

#endif // !__LIN_MESSAGE_DEFINITION_H__
