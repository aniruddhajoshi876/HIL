// Copyright 2006-2026 Speedgoat GmbH

#ifndef zd27cba5263
#define zd27cba5263
#include <stdint.h>
typedef struct CanFdMessage_T{uint8_t ProtocolMode;uint8_t Extended;uint8_t Length;uint8_t Remote;uint8_t Error;uint8_t BRS;uint8_t ESI;uint8_t DLC;uint32_t ID;uint32_t Reserved;double Timestamp;uint8_t Data[(0x201+7758-0x200f)];}CanFdMessage;
#endif 

