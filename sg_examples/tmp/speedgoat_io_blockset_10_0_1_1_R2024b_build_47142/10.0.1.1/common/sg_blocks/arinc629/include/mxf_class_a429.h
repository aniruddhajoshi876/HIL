/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_A429_H_CONST
#define MXF_A429_H_CONST

   #define KMXF_A429_MODULE_RX_FIFO_AGING                      KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_A429_MODULE_RX_FIFO_AF                         KMXF_MODULE_RX_FIFO_AF
   #define KMXF_A429_MODULE_TX_FIFO_AF                         KMXF_MODULE_TX_FIFO_AF
   #define KMXF_A429_MODULE_TX_FIFO_AE                         KMXF_MODULE_TX_FIFO_AE
   #define KMXF_A429_MODULE_RX_TIMETAG_ENABLE                  KMXF_MODULE_RX_TIMETAG_ENABLE

   #define KMXF_A429_SPEED                                     100001ULL
   
   #define KMXF_A429_PARITY                                    100002ULL
      #define VMXF_A429_PARITY_EVEN                               0ULL
      #define VMXF_A429_PARITY_ODD                                1ULL
      #define VMXF_A429_PARITY_NONE                               2ULL
   
   #define KMXF_A429_WORDSIZE                                  100003ULL
      #define VMXF_A429_WORDSIZE_25                               25ULL
      #define VMXF_A429_WORDSIZE_32                               32ULL
   
   #define KMXF_A429_TX_RX_TEST_LB                             100004ULL
   
   #define KMXF_A429_GAP                                       100005ULL

   #define KMXF_A429_ELECTRICAL_SELECTION                      100006ULL
      #define VMXF_A429EH_MULTI_ELECTRICAL_SELECT_DEFAULT         0ULL
      #define VMXF_A429EH_MULTI_ELECTRICAL_SELECT_CUSTOM          1ULL

   #define KMXF_A429_TX_SLEW_RATE_SELECTION                    100007ULL
      #define VMXF_A429EH_MULTI_TX_SLEW_RATE_SELECT_DEFAULT       0ULL
      #define VMXF_A429EH_MULTI_TX_SLEW_RATE_SELECT_CUSTOM        1ULL

   #define KMXF_A429_TX_SLEW_RATE                              100008ULL
      #define VMXF_A429EH_TX_SLEW_RATE_LOW                        0ULL
      #define VMXF_A429EH_TX_SLEW_RATE_HIGH                       1ULL

   #define KMXF_A429_TX_DIFF_VOLTAGE_HIGH                      100009ULL
   #define KMXF_A429_TX_DIFF_VOLTAGE_LOW                       100010ULL
   #define KMXF_A429_TX_VOLTAGE_OFFSET                         100011ULL
   #define KMXF_A429_RX_DIFF_VOLTAGE_THRESHOLD                 100012ULL


   #define MXF_A429_DISCRETE_OUTPUT_TRIG_ON_TX                 0ULL
   #define MXF_A429_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR          1ULL

   #define MXF_A429_TX_REC_CTRL_PARITY_ERROR                   0x00010000
   #define MXF_A429_TX_REC_CTRL_PARITY_ODD                     0x00020000
   #define MXF_A429_TX_REC_CTRL_PARITY_EVEN                    0x00040000
   #define MXF_A429_TX_REC_CTRL_DISCRETE_OUTPUT_TRIG           0x00080000
   #define MXF_A429_TX_REC_CTRL_SHORT_WORD_SIZE                0x00200000
   #define MXF_A429_TX_REC_CTRL_LONG_WORD_SIZE                 0x00400000

   #define MXF_A429_RX_REC_CTRL_PARITY_ERROR                   0x00010000

#endif

#if !defined(MXF_A429_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_A429_H

   typedef struct
   {
      uint64 timeTag;
      uint32 control;
      uint32 repeatCount;
      uint32 data;
      uint32 reserved;
   }
   MXF_A429_DATAREC;

   typedef struct
   {
      uint64 timeTag;
      uint32 control;
      uint32 rate;
      uint32 errorCount;
      uint32 data;
   }
   MXF_A429_SAMPREC;

   #ifdef __cplusplus
   extern "C" {
   #endif

       uint32 MXF_EXPORTED mxfA429TxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_A429_DATAREC* rec);
       
       uint32 MXF_EXPORTED mxfA429TxPeriodicUpdateMsgWrite(HMXF_BUFFER buffer, uint64 count, MXF_A429_DATAREC* rec);

       uint32 MXF_EXPORTED mxfA429RxAcqMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA429RxAcqMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      
       uint32 MXF_EXPORTED mxfA429RxAcqRead(HMXF_BUFFER buffer, uint64 maxRecCount, uint64 maxBytesCount, uint64* status, uint64* recCount, uint64* bytesCount, MXF_A429_DATAREC* rec);
       
       uint32 MXF_EXPORTED mxfA429RxSamplingExtEnableSet(HMXF_BUFFER buffer, uint64 state, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA429RxSamplingExtEnableAllGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      
       uint32 MXF_EXPORTED mxfA429RxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxRecCount, uint64 maxBytesCount, uint64* recCount, uint64* bytesCount, MXF_A429_SAMPREC* rec);
       uint32 MXF_EXPORTED mxfA429RxSamplingSingleRead(HMXF_BUFFER buffer, uint64 flags, uint64 label, uint64 sdi, MXF_A429_SAMPREC* rec);
      
       uint32 MXF_EXPORTED mxfA429RxSamplingMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA429RxSamplingMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      
       uint32 MXF_EXPORTED mxfA429AsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_A429* msg);
       uint32 MXF_EXPORTED mxfA429AsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_A429* msgid);
       
       uint32 MXF_EXPORTED mxfA429NextDataRecordPtrGet(MXF_A429_DATAREC* currentRec, MXF_A429_DATAREC** nextRec);
       uint32 MXF_EXPORTED mxfA429NextSamplingRecordPtrGet(MXF_A429_SAMPREC* currentRec, MXF_A429_SAMPREC** nextRec);
      
       uint32 MXF_EXPORTED mxfA429ArwBnrToReal(uint32 arincw, double range, uint64 sbits, double* real);
       uint32 MXF_EXPORTED mxfA429ArwRealToBnr(double range, uint64 sbits, double* real, uint32* arincw);

       uint32 MXF_EXPORTED mxfA429ArwCompose(uint64 label, uint64 sdi, uint64 data, uint64 ssm, uint64 parity, uint32* arincw);
       uint32 MXF_EXPORTED mxfA429ArwDecompose(uint32 arincw, uint64* label, uint64* sdi, uint64* data, uint64* ssm, uint64* parity);

       uint32 MXF_EXPORTED mxfA429ArwCompose2(uint64 label, uint64 sdi, uint64 data, uint64 parity, uint32* arincw);
       uint32 MXF_EXPORTED mxfA429ArwDecompose2(uint32 arincw, uint64* label, uint64* sdi, uint64* data, uint64* parity);

       uint32 MXF_EXPORTED mxfA429ArwCompose3(uint64 label, uint64 data, uint64 parity, uint32* arincw);
       uint32 MXF_EXPORTED mxfA429ArwDecompose3(uint32 arincw, uint64* label, uint64* data, uint64* parity);

       uint32 MXF_EXPORTED mxfA429ArwCompose25bit(uint64 label, uint64 data, uint64 parity, uint32* arincw);
       uint32 MXF_EXPORTED mxfA429ArwDecompose25bit(uint32 arincw, uint64* label, uint64* data, uint64* parity);

       uint32 MXF_EXPORTED mxfA429EmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_A429* msgid); // label-sdi?
       uint32 MXF_EXPORTED mxfA429EmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_A429* msgid);
       uint32 MXF_EXPORTED mxfA429EmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                               uint64* recCount, uint64* bytesCount, MXF_A429_DATAREC* rec);
       uint32 MXF_EXPORTED mxfA429EmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_A429_DATAREC* rec, uint64* count );

   #ifdef __cplusplus
   }
   #endif

#endif
