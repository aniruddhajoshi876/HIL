#ifndef __MB_DEF_H
#define __MB_DEF_H

#include "sg_common.h"
#include "sg_module_types.h"
#include "sg_printf.h"
#include "stdint.h"

#pragma pack(push, 1)

#ifndef MATLAB_MEX_FILE

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif


#define MB_MAX_NUM_BLOCKS 1024

#define MB_MODULE_TYPE_UNDEF    0x00000000
#define MBTCP_NODE_TYPE_CLIENT  0x00000001
#define MBTCP_NODE_TYPE_SERVER  0x00000002
#define MBRTU_NODE_TYPE_CLIENT  0x00000003
#define MBRTU_NODE_TYPE_SERVER  0x00000004

#define MB_BLOCK_TYPE_UNDEF             0x00000000
#define MB_BLOCK_TYPE_SERVER_SETUP      0x00000001
#define MB_BLOCK_TYPE_SERVER_READ       0x00000002
#define MB_BLOCK_TYPE_COMMAND           0x00000003
#define MB_BLOCK_TYPE_POINT             0x00000004
#define MB_BLOCK_TYPE_CLIENT_SETUP      0x00000005
#define MB_BLOCK_TYPE_CLIENT_CONNECTION 0x00000006
#define MB_BLOCK_TYPE_CLIENT_READ       0x00000007

#define MB_PORT_TYPE_VALUE    1
#define MB_PORT_TYPE_FLAG     2
#define MB_PORT_TYPE_TIME     3
#define MB_PORT_TYPE_ENABLE   4
#define MB_PORT_TYPE_NEWDATA  5
#define MB_PORT_TYPE_TON      6
#define MB_PORT_TYPE_TOFF     7
#define MB_PORT_TYPE_CTRLCODE 8
#define MB_PORT_TYPE_COUNT    9
#define MB_BROADCAST_NO_SEND  10

#define MB_ERROR_OFFSET -500

#define MB_NO_ERROR                     0
#define MB_ERROR_GENERAL                MB_ERROR_OFFSET - 1
#define MB_ERROR_INTERFACE_NOT_FOUND    MB_ERROR_OFFSET - 2
#define MB_ERROR_NODE_NOT_FOUND         MB_ERROR_OFFSET - 3
#define MB_ERROR_MODULE_NOT_INIT        MB_ERROR_OFFSET - 4
#define MB_ERROR_REMOTE_NOT_INIT        MB_ERROR_OFFSET - 5
#define MB_ERROR_LICENSE                MB_ERROR_OFFSET - 6
#define MB_ERROR_WRONG_NODE             MB_ERROR_OFFSET - 7
#define MB_ERROR_UNFINISHED_MESSAGE     MB_ERROR_OFFSET - 8
#define MB_ERROR_WRONG_CRC              MB_ERROR_OFFSET - 10
#define MB_ERROR_MSG_INCOMPLETE         MB_ERROR_OFFSET - 11
#define MB_ERROR_MSG_BROKEN             MB_ERROR_OFFSET - 12

#define MB_TABLE_TYPE_COIL              1 // Read
#define MB_TABLE_TYPE_DISCRETE          2 // Read
#define MB_TABLE_TYPE_HOLDING           3 // Read
#define MB_TABLE_TYPE_INPUT             4 // Read
#define MB_TABLE_TYPE_COIL_W            5 // Write
#define MB_TABLE_TYPE_REGISTER_W        6 // Write
#define MB_TABLE_TYPE_MULTI_COILS_W     7 // Write
#define MB_TABLE_TYPE_MULTI_REGISTERS_W 8 // Write

#define MB_FC_READ_COILS            1
#define MB_FC_READ_DISCRETE_INPUTS  2
#define MB_FC_READ_HOLDING_REGS     3
#define MB_FC_READ_INPUT_REGS       4
#define MB_FC_WRITE_COIL            5
#define MB_FC_WRITE_HOLDING_REG     6
#define MB_FC_WRITE_COILS           15
#define MB_FC_WRITE_HOLDING_REGS    16

#define MB_ERROR_CODE_BASE  0x80
#define MB_EXEPTION_FC      0x01
#define MB_EXEPTION_INDEX   0x02
#define MB_EXEPTION_LENGTH  0x03
#define MB_EXEPTION_PROCESS 0x04
#define MB_EXEPTION_ACK     0x05
#define MB_EXEPTION_BUSY    0x06

/* Number of points per frame defined by the Modbus spec */
#define MB_MAX_NUM_READ_WORDS  0x007D
#define MB_MAX_NUM_WRITE_WORDS 0x007B
#define MB_MAX_NUM_READ_BITS   0x07D0
#define MB_MAX_NUM_WRITE_BITS  0x07B0

#define MB_MAX_RX_LOAD TCP_MAXWIN
#define MB_MAX_TX_LOAD 1500

#define MB_RTU_MAX_BUF_SIZE 1024
#define MB_RTU_MAX_MESSAGE_LEN  256

#define MB_IDLE_DELAY       10000   // 10us
#define MBRTU_IDLE_DELAY    100000 //  100us

#define MBRTU_RESPONSE_TIMEOUT  1000 // ms

#define MB_FI_MODE_PEER                 1
#define MB_FI_MODE_MSG                  2

#define MB_FI_RULE_STATE_OFF            1
#define MB_FI_RULE_STATE_ENABLED        2
#define MB_FI_RULE_STATE_TRIGGERED      3

#define MB_FI_RULE_ACTION_UNDEF         0
#define MB_FI_RULE_ACTION_NONE          1
#define MB_FI_RULE_ACTION_ACCEPT        2
#define MB_FI_RULE_ACTION_REJECT        3

#define MB_FI_RULE_REACTION_UNDEF       0
#define MB_FI_RULE_REACTION_NONE        1
#define MB_FI_RULE_REACTION_NORESP      2
#define MB_FI_RULE_REACTION_TRIM        3
#define MB_FI_RULE_REACTION_EXTEND      4
#define MB_FI_RULE_REACTION_ERROR       5 
#define MB_FI_RULE_REACTION_TRANSID     6  
#define MB_FI_RULE_REACTION_LENGTH      7 
#define MB_FI_RULE_REACTION_UNIT        8
#define MB_FI_RULE_REACTION_FC          9
#define MB_FI_RULE_REACTION_INDEX       10
#define MB_FI_RULE_REACTION_QUANTITY    11 
#define MB_FI_RULE_REACTION_BYTECOUNT   12

namespace modbusTCP
{
typedef struct MB_SEND_FRAME_t {
    bool IsLocked = false;
    uint64_t TimeStamp = 0;
    uint32_t Size = 0;
    uint8_t Data[MB_MAX_TX_LOAD] = {0};

} MB_SEND_FRAME_T;

typedef struct MB_HEADER_t {
    uint16_t TransactionID;
    uint16_t ProtocolID;
    uint16_t Length;
    uint8_t UnitID;
} T_MB_HEADER;

typedef struct MB_REQUEST_t {
    T_MB_HEADER Head;
    uint8_t FunctionCode;

} MB_REQUEST_T;

typedef struct MB_RESPONSE_t {
    T_MB_HEADER Head;
    uint8_t FunctionCode;

} MB_RESPONSE_T;

typedef struct MB_ERROR_RESPONSE_t {
    uint8_t ErrorCode;
    uint8_t ExceptionCode;

} MB_RESPONSE_ERROR_T;

typedef struct MB_01_REQUEST_t {
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;

} MB_REQUEST_01_T;

typedef struct MB_01_RESPONSE_t {
    uint8_t FunctionCode;
    uint8_t ByteCount;

} MB_RESPONSE_01_T;

typedef struct MB_05_REQUEST_t {
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Value;

} MB_REQUEST_05_T;

typedef struct MB_05_RESPONSE_t {
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Value;

} MB_RESPONSE_05_T;

typedef struct MB_15_REQUEST_t {
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;
    uint8_t ByteCount;

} MB_REQUEST_15_T;

typedef struct MB_15_RESPONSE_t {
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;

} MB_RESPONSE_15_T;

#define MB_REQUEST_02_T MB_REQUEST_01_T
#define MB_REQUEST_03_T MB_REQUEST_01_T
#define MB_REQUEST_04_T MB_REQUEST_01_T
#define MB_REQUEST_06_T MB_REQUEST_05_T
#define MB_REQUEST_16_T MB_REQUEST_15_T

#define MB_RESPONSE_02_T MB_RESPONSE_01_T
#define MB_RESPONSE_03_T MB_RESPONSE_01_T
#define MB_RESPONSE_04_T MB_RESPONSE_01_T
#define MB_RESPONSE_06_T MB_RESPONSE_05_T
#define MB_RESPONSE_16_T MB_RESPONSE_15_T

} // namespace modbusTCP

namespace modbusRTU
{

#ifndef MATLAB_MEX_FILE
// Block Registry Block Type
enum blockTypes { SERIAL_SETUP = 1, SERIAL_READ, SERIAL_WRITE, MODBUS_RTU_INTERFACE };
static const char *const INTERFACENAME[] = {"IO503", "IO504", "IO505", "IO581", "Onboard UART"};
static const int INTERFACE_TYPE[] = {   SG_MODULE_TYPE_IO503, SG_MODULE_TYPE_IO504,
                                        SG_MODULE_TYPE_IO505, SG_MODULE_TYPE_IO581, SG_ONBOARD_SERIAL_UART
};

// Taken from sg_serial.h                                    
#if defined(__QNX__)
#define MAX_LENGTH_SERIAL_DEVICE_NAME 12
#elif defined(__linux__)
#define MAX_LENGTH_SERIAL_DEVICE_NAME 22
#endif
#define MAX_SERIAL_CHANNELS           8

typedef enum
{
    DrainOnly = 0,
    FlushOnly,
    DrainAndClose,
    FlushAndClose
} buffer_fd_behavior;

#ifdef __cplusplus
extern "C" {
#endif

int sg_serial_device_open(int port);
int sg_serial_device_close(int port);
int sg_serial_device_flush(int port, buffer_fd_behavior behavior);

}

typedef struct {
    int moduleType;
    int moduleId;
    int isIO581;
    int bus;
    int slot;
    int nCh;
#if defined(__QNX__)
    int devNumber; // index X for /dev/serX
    int pid;       // process Id
    int intr;
#elif defined(__linux__)
    int ttyNumberList[MAX_SERIAL_CHANNELS]; // indexes X for /dev/ttySTDRV002_X
#endif // __QNX__
    uint8_t enabled[MAX_SERIAL_CHANNELS];
    uint32_t *pci_info;
    uint32_t *baseAddress0;
    bool modelStopMsgEn[MAX_SERIAL_CHANNELS];
} Io5xx_Device_t;

typedef struct {
    int nCh;
    bool enabled[MAX_SERIAL_CHANNELS];
    bool modelStopMsgEn[MAX_SERIAL_CHANNELS];
} OnBoardSerial_Device_t;

typedef struct tSerialInfo {
    void *Interface;
    uint16_t ModuleType;
    uint16_t ModuleID;
    uint8_t SerialIndex;
    int fd;
    uint8_t enabled;
} MB_SERIAL_INFO_T;
#endif

typedef struct MB_REQUEST_t {
    uint8_t NodeID;
    uint8_t FunctionCode;

} MB_REQUEST_T;

typedef struct MB_RESPONSE_t {
    uint8_t NodeID;
    uint8_t FunctionCode;

} MB_RESPONSE_T;

typedef struct MB_REQUEST_01_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;
} MB_REQUEST_01_T;

typedef struct MB_RESPONSE_01_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint8_t ByteCount;
} MB_RESPONSE_01_T;

typedef struct MB_REQUEST_05_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Value;
} MB_REQUEST_05_T;

typedef struct MB_RESPONSE_05_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Value;
} MB_RESPONSE_05_T;

typedef struct MB_REQUEST_08_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t SubFunction;
    uint16_t Data;

} MB_REQUEST_08_T;

typedef struct MB_RESPONSE_08_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t SubFunction;
    uint16_t Data;

} MB_RESPONSE_08_T;

typedef struct MB_REQUEST_15_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;
    uint8_t ByteCount;
} MB_REQUEST_15_T;

typedef struct MB_15_RESPONSE_t {
    uint8_t NodeID;
    uint8_t FunctionCode;
    uint16_t Index;
    uint16_t Quantity;
} MB_RESPONSE_15_T;

typedef struct MB_ERROR_RESPONSE_t {
    uint8_t NodeID;
    uint8_t ErrorCode;
    uint8_t ExceptionCode;
} MB_RESPONSE_ERROR_T;

#define MB_REQUEST_02_T MB_REQUEST_01_T
#define MB_REQUEST_03_T MB_REQUEST_01_T
#define MB_REQUEST_04_T MB_REQUEST_01_T

#define MB_REQUEST_06_T MB_REQUEST_05_T

#define MB_REQUEST_16_T MB_REQUEST_15_T

#define MB_RESPONSE_02_T MB_RESPONSE_01_T
#define MB_RESPONSE_03_T MB_RESPONSE_01_T
#define MB_RESPONSE_04_T MB_RESPONSE_01_T

#define MB_RESPONSE_06_T MB_RESPONSE_05_T

#define MB_RESPONSE_16_T MB_RESPONSE_15_T

} // namespace modbusRTU

#pragma pack(pop)

#endif
