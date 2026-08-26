// Copyright 2006-2026 Speedgoat GmbH

#ifndef z96e4108ffa
#define z96e4108ffa
#include <stdint.h>
#define z23dbb45ae9 (0xc2c+5754-0x229e)      
typedef struct LINMsg_T{uint8_t ProtID;uint8_t IDOnly;uint8_t Type;uint8_t EnhcdCksm;uint8_t PsblDataOvrn;uint8_t Len;uint8_t Data[z23dbb45ae9];uint32_t TimeStamp;}LINMsg;typedef struct zd43b1050b7{LINMsg msg;uint8_t senderOfResponse;}LINMsg2;
#define z8253b0fc59 (0x136b+2970-0x1efd) 
typedef union z49dcdee224{struct{uint8_t z3c15e36fc6;uint8_t Type;uint8_t Length;uint8_t Flags;}Bytes;struct{uint32_t z3c15e36fc6:(0xcc0+4433-0x1e09);uint32_t Type:(0x5f4+7347-0x229f);uint32_t Length:(0x1a58+485-0x1c35);uint32_t z5f94e955f1:(0x19bb+1757-0x2097);uint32_t z288e5ffb91:(0x988+4186-0x19e1);uint32_t z6888ef4613:(0x153+3183-0xdc1);uint32_t IDOnly:(0x80f+728-0xae6);uint32_t Reserved:(0xcf1+5048-0x20a5);}Bits;}z3f861cb1b3;typedef struct z3f9b824b4b{uint32_t TimeStamp;z3f861cb1b3 Info;uint8_t Data[z8253b0fc59];}z1bb2e71a03;
#endif 

