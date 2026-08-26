#ifndef __SG_IO601_DATATYPES_C__
#define __SG_IO601_DATATYPES_C__


/* CAN message is the datatype as used by Matlab. */
typedef struct canMsg_T
{
    uint8_T Extended;
    uint8_T Length;
    uint8_T Remote;
    uint8_T Error;
    int32_T ID;
    real_T Timestamp;
    uint8_T Data[8];    
} canMsg;

typedef struct CAN_QUEUEENTRY
{
    volatile uint32_T word[5];
} CAN_QUEUEENTRY;

typedef struct BCICOMMAND
{
    uint8_T synch;
    uint8_T count;
    uint16_T reserved;
    uint8_T command;
    uint8_T data[75];
} BCICOMMAND;

typedef struct BCI_t_LIN_MSG
{
    uint8_T bId;
    uint8_T bModel;
    uint8_T bCheckSum;
    uint8_T bSendData;  
    uint8_T bLength;
    uint8_T bDummy;
    uint8_T bDataByte[8];
} BCI_t_LIN_MSG;

typedef struct t_BITSINBYTE_S
{
    uint8_T o0:1, o1:1, o2:1, o3:1, o4:1, o5:1, o6:1, o7:1;

} t_BITSINBYTE_S;

typedef union t_BITSINBYTE_U
{
    uint8_T b;
    t_BITSINBYTE_S u;

} t_BITSINBYTE_U;

typedef struct t_semaphores
{
    uint16_T CANStatusBuffer;
    uint16_T LINStatusBuffer;
    uint16_T LINUpdateBuffer1;
    uint16_T LINUpdateBuffer2;
} t_semaphores;

typedef struct T_CANSTATUS
{
    uint16_T status0;
    uint16_T busLast0;
    uint16_T status1;
    uint16_T busLast1;
    uint16_T CPUlast;
    uint16_T liveCounter;
} T_CANSTATUS;

#endif