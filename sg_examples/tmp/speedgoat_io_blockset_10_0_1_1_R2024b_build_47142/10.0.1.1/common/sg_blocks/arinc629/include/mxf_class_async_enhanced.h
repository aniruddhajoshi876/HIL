/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_ASYNC_ENHANCED_H_CONST
#define MXF_ASYNC_ENHANCED_H_CONST

   #define KMXF_ASYNCEH_MODULE_RX_TIMETAG_ENABLE                  KMXF_MODULE_RX_TIMETAG_ENABLE
   #define KMXF_ASYNCEH_MODULE_RX_FIFO_AGING                      KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_ASYNCEH_MODULE_RX_FIFO_AF                         KMXF_MODULE_RX_FIFO_AF
   #define KMXF_ASYNCEH_MODULE_TX_FIFO_AF                         KMXF_MODULE_TX_FIFO_AF
   #define KMXF_ASYNCEH_MODULE_TX_FIFO_AE                         KMXF_MODULE_TX_FIFO_AE

   #define KMXF_ASYNCEH_MODULE_XON_VAL                            KMXF_MODULE_XON_VAL
   #define KMXF_ASYNCEH_MODULE_XOFF_VAL                           KMXF_MODULE_XOFF_VAL
   #define KMXF_ASYNCEH_MODULE_RX_FLOWCTRL_FIFO_AE                KMXF_MODULE_RX_FLOWCTRL_FIFO_AE
   #define KMXF_ASYNCEH_MODULE_RX_FLOWCTRL_FIFO_AF                KMXF_MODULE_RX_FLOWCTRL_FIFO_AF

   #define KMXF_ASYNCEH_ELECTRICAL_INTERFACE                      110000ULL
      #define VMXF_ASYNCEH_ELECTRICAL_INTERFACE_RS422                0ULL
      #define VMXF_ASYNCEH_ELECTRICAL_INTERFACE_RS485                1ULL
      #define VMXF_ASYNCEH_ELECTRICAL_INTERFACE_RS232                2ULL

   #define KMXF_ASYNCEH_SPEED                                     110001ULL
   
   #define KMXF_ASYNCEH_PARITY                                    110002ULL
      #define VMXF_ASYNCEH_PARITY_EVEN                               0ULL
      #define VMXF_ASYNCEH_PARITY_ODD                                1ULL
      #define VMXF_ASYNCEH_PARITY_NONE                               2ULL

   #define KMXF_ASYNCEH_STOPBITSIZE                               110003ULL
   #define KMXF_ASYNCEH_WORDSIZE                                  110004ULL
   #define KMXF_ASYNCEH_TX_RX_TEST_LB                             110005ULL

   #define KMXF_ASYNCEH_RX_WORD_MODE_ENABLE                       110006ULL
   #define KMXF_ASYNCEH_RX_STRING_GAP                             110007ULL

   #define KMXF_ASYNCEH_TX_FLOWCTRL_RX_INDEX                      110008ULL
   #define KMXF_ASYNCEH_RX_FLOWCTRL_TX_INDEX                      110009ULL
   #define KMXF_ASYNCEH_HANDSHAKE_MODE                            110010ULL
      #define VMXF_ASYNCEH_HANDSHAKE_DISABLED                        0ULL
      #define VMXF_ASYNCEH_HANDSHAKE_LOW                             1ULL
      #define VMXF_ASYNCEH_HANDSHAKE_HIGH                            2ULL
   #define KMXF_ASYNCEH_XONXOFF_TRANSMIT_ENABLE                   110011ULL
   #define KMXF_ASYNCEH_XONXOFF_DETECTION_ENABLE                  110012ULL
   #define KMXF_ASYNCEH_XONXOFF_RX_FIFO_ENABLE                    110013ULL
   #define KMXF_ASYNCEH_TX_PORT_ENABLE                            110014ULL
   #define KMXF_ASYNCEH_TX_STRING_GAP                             110015ULL
   #define KMXF_ASYNCEH_TX_SELF_RECEPTION_ENABLE                  110016ULL

   #define KMXF_ASYNCEH_ELECTRICAL_SELECTION                      110017ULL
      #define VMXF_ASYNCEH_MULTI_ELECTRICAL_SELECT_DEFAULT           0ULL
      #define VMXF_ASYNCEH_MULTI_ELECTRICAL_SELECT_CUSTOM            1ULL
   
   #define KMXF_ASYNCEH_TX_DIFF_VOLTAGE_HIGH                      110018ULL
   #define KMXF_ASYNCEH_TX_DIFF_VOLTAGE_LOW                       110019ULL
   #define KMXF_ASYNCEH_TX_VOLTAGE_OFFSET                         110020ULL
   
   #define KMXF_ASYNCEH_TX_SLEW_RATE_SELECTION                    110021ULL
      #define VMXF_ASYNCEH_MULTI_TX_SLEW_RATE_SELECT_DEFAULT         0ULL
      #define VMXF_ASYNCEH_MULTI_TX_SLEW_RATE_SELECT_CUSTOM          1ULL
   
   #define KMXF_ASYNCEH_TX_SLEW_RATE                              110022ULL
   #define KMXF_ASYNCEH_RX_DIFF_VOLTAGE_THRESHOLD                 110023ULL


   #define MXF_ASYNCEH_DISCRETE_OUTPUT_TRIG_ON_TX                 0ULL
   #define MXF_ASYNCEH_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR          1ULL

   #define MXF_ASYNCEH_TX_REC_CTRL_PARITY_ERROR                   0x00004000
   #define MXF_ASYNCEH_TX_REC_CTRL_DISCRETE_OUTPUT_TRIG           0x00002000
   #define MXF_ASYNCEH_TX_REC_CTRL_LONG_WORD_SIZE                 0x00001000
   #define MXF_ASYNCEH_TX_REC_CTRL_SHORT_WORD_SIZE                0x00000800
   #define MXF_ASYNCEH_TX_REC_CTRL_WORD_ERROR                     0x00000200
   #define MXF_ASYNCEH_TX_REC_CTRL_WORD_ERROR_INDEX               0x000000FF

   #define MXF_ASYNCEH_RX_REC_CTRL_EOS                            0x00008000
   #define MXF_ASYNCEH_RX_REC_CTRL_SOS                            0x00004000
   #define MXF_ASYNCEH_RX_REC_CTRL_STOPBIT_ERROR                  0x00002000
   #define MXF_ASYNCEH_RX_REC_CTRL_PARITY_ERROR                   0x00001000
   
#endif

#if !defined(MXF_ASYNCEH_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_ASYNCEH_H

   typedef struct
   {
      uint64      timeTag;
      uint32      control;
      uint32      dataSize;
      uint32      repeatCount;
      uint32      reserved;
      uint8       data[256];
   }
   MXF_ASYNCEH_DATAREC;

   #ifdef __cplusplus
   extern "C" {
   #endif
 
       uint32 MXF_EXPORTED mxfASYNCEHTxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_ASYNCEH_DATAREC* rec);
       uint32 MXF_EXPORTED mxfASYNCEHRxAcqRead(HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, MXF_ASYNCEH_DATAREC* rec);
       uint32 MXF_EXPORTED mxfASYNCEHNextDataRecordPtrGet(MXF_ASYNCEH_DATAREC* currentRec, MXF_ASYNCEH_DATAREC** nextRec);

       uint32 MXF_EXPORTED mxfASYNCEHEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                                  uint64* recCount, uint64* bytesCount, MXF_ASYNCEH_DATAREC* rec);
       uint32 MXF_EXPORTED mxfASYNCEHEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount,
                                                                   MXF_ASYNCEH_DATAREC* rec, uint64* recCount);

   #ifdef __cplusplus
   }
   #endif


#endif
