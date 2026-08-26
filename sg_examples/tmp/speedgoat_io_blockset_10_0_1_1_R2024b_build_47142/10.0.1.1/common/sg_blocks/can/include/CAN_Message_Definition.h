// Copyright 2006-2026 Speedgoat GmbH

#ifndef zc722e95a06
#define zc722e95a06
#include <stdint.h>
typedef struct CANMsg_T{uint8_t Extended;uint8_t Length;uint8_t Remote;uint8_t Error;int32_t ID;double Timestamp;uint8_t Data[(0x126d+4505-0x23fe)];}CANMsg;
#endif 

