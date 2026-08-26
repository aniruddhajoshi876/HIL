/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_A717_H_CONST
#define MXF_A717_H_CONST

   #define KMXF_A717_MODULE_RX_FIFO_AGING                      KMXF_MODULE_RX_FIFO_AGING

   #define KMXF_A717_MODULE_RX_FIFO_AF                         KMXF_MODULE_RX_FIFO_AF

   #define KMXF_A717_MODULE_TX_FIFO_AF                         KMXF_MODULE_TX_FIFO_AF

   #define KMXF_A717_MODULE_TX_FIFO_AE                         KMXF_MODULE_TX_FIFO_AE

   #define KMXF_A717_MODULE_RX_TIMETAG_ENABLE                  KMXF_MODULE_RX_TIMETAG_ENABLE


   #define KMXF_A717_SUBFRAME_SIZE                             190000ULL

   #define KMXF_A717_BIT_ENCODING                              190001ULL
      #define VMXF_A717_BIT_ENCODING_HARVARDBIPHASE               0ULL
      #define VMXF_A717_BIT_ENCODING_BIPOLAR_RZ                   1ULL

   #define KMXF_A717_RX_SYNC_WORD_0                            190002ULL
   #define KMXF_A717_RX_SYNC_WORD_1                            190003ULL
   #define KMXF_A717_RX_SYNC_WORD_2                            190004ULL
   #define KMXF_A717_RX_SYNC_WORD_3                            190005ULL

   #define KMXF_A717_RX_DIFF_VOLTAGE_THRESHOLD                 190006ULL

   #define KMXF_A717_TX_RX_TEST_LB                             190007ULL

   #define KMXF_A717_ELECTRICAL_SELECTION                      190008ULL
      #define VMXF_A717_ELECTRICAL_SELECT_DEFAULT                 0ULL
      #define VMXF_A717_ELECTRICAL_SELECT_CUSTOM                  1ULL

   #define KMXF_A717_TX_SLEW_RATE_SELECTION                    190009ULL
      #define VMXF_A717_TX_SLEW_RATE_SELECT_DEFAULT               0ULL
      #define VMXF_A717_TX_SLEW_RATE_SELECT_CUSTOM                1ULL

   #define KMXF_A717_TX_SLEW_RATE                              190010ULL

   #define KMXF_A717_TX_DIFF_VOLTAGE_HIGH                      190011ULL

   #define KMXF_A717_TX_DIFF_VOLTAGE_LOW                       190012ULL

   #define KMXF_A717_TX_VOLTAGE_OFFSET                         190013ULL

   #define MXF_A717_DISCRETE_OUTPUT_TRIG_ON_TX                 0ULL

   #define MXF_A717_TX_REC_CTRL_DISCRETE_OUTPUT_TRIG           0x00080000

#endif

#if !defined(MXF_A717_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_A717_H

   typedef struct
   {
      uint64      timeTag;
      uint32      control;
      uint32      dataSize;
      uint32      repeatCount;
      uint32      reserved;

      uint16      data[8192];
   }
   MXF_A717_DATAREC;


   #ifdef __cplusplus
   extern "C" {
   #endif
 
       uint32 MXF_EXPORTED mxfA717TxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_A717_DATAREC* rec);
       uint32 MXF_EXPORTED mxfA717RxAcqRead(HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, MXF_A717_DATAREC* rec);
       uint32 MXF_EXPORTED mxfA717NextDataRecordPtrGet(MXF_A717_DATAREC* currentRec, MXF_A717_DATAREC** nextRec);
       uint32 MXF_EXPORTED mxfA717EmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                               uint64* recCount, uint64* bytesCount, MXF_A717_DATAREC* rec);
       uint32 MXF_EXPORTED mxfA717EmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_A717_DATAREC* rec, uint64* count );
   #ifdef __cplusplus
   }
   #endif


#endif
