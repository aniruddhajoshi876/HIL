/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_A708_H_CONST
#define MXF_A708_H_CONST

   #define KMXF_A708_MODULE_RX_FIFO_AGING                      KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_A708_MODULE_RX_FIFO_AF                         KMXF_MODULE_RX_FIFO_AF
   #define KMXF_A708_MODULE_TX_FIFO_AF                         KMXF_MODULE_TX_FIFO_AF
   #define KMXF_A708_MODULE_TX_FIFO_AE                         KMXF_MODULE_TX_FIFO_AE
   #define KMXF_A708_MODULE_RX_TIMETAG_ENABLE                  KMXF_MODULE_RX_TIMETAG_ENABLE
   #define KMXF_A708_MODULE_ACTIVE                             KMXF_MODULE_ACTIVE

   #define KMXF_A708_TX_RX_TEST_LB                             200000ULL
   

   #define MXF_A708_DISCRETE_OUTPUT_TRIG_ON_TX                 0ULL
   #define MXF_A708_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR          1ULL

   #define MXF_A708_TX_REC_CTRL_MANCHESTERBIT_ERROR            0x00000010
   #define MXF_A708_TX_REC_CTRL_BOW_ERROR                      0x00000020
   #define MXF_A708_TX_REC_CTRL_EOW_ERROR                      0x00000040
   #define MXF_A708_TX_REC_CTRL_BITSCNT_ERROR                  0x00000007

   #define MXF_A708_RX_REC_CTRL_TOOLONGWORD_ERROR              0x00001000
   #define MXF_A708_RX_REC_CTRL_MANCHESTER_ERROR               0x00002000
   #define MXF_A708_RX_REC_CTRL_BOWSYNC_ERROR                  0x00004000
   #define MXF_A708_RX_REC_CTRL_EOWSYNC_ERROR                  0x00008000
   #define MXF_A708_RX_REC_CTRL_NOTENOUGHBITS_ERROR            0x00010000
   #define MXF_A708_RX_REC_CTRL_TOOMANYBITS_ERROR              0x00020000
   #define MXF_A708_RX_REC_CTRL_BITSCNT_ERROR                  0x00000007

#endif

#if !defined(MXF_A708_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_A708_H

   typedef struct
   {
      uint64 timeTag;
      uint32 control;
      uint32 dataSize;
      uint32 repeatCount;
      uint32 manchesterBitErr;

      uint16 data[128];
   }
   MXF_A708_DATAREC;

   typedef struct
   {
      uint64 timeTag;
      uint32 control;
      uint32 rate;
      uint32 errorCount;
      uint32 dataSize;
      uint16 data[128];
   }
   MXF_A708_SAMPREC;

   #ifdef __cplusplus
   extern "C" {
   #endif

       uint32 MXF_EXPORTED mxfA708TxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_A708_DATAREC* rec);
       
       uint32 MXF_EXPORTED mxfA708TxPeriodicUpdateMsgWrite(HMXF_BUFFER buffer, uint64 count, MXF_A708_DATAREC* rec);

       uint32 MXF_EXPORTED mxfA708RxAcqMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA708RxAcqMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      
       uint32 MXF_EXPORTED mxfA708RxAcqRead(HMXF_BUFFER buffer, uint64 maxRecCount, uint64 maxBytesCount, uint64* status, uint64* recCount, uint64* bytesCount, MXF_A708_DATAREC* rec);

       uint32 MXF_EXPORTED mxfA708RxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxRecCount, uint64 maxBytesCount, uint64* recCount, uint64* bytesCount, MXF_A708_SAMPREC* rec);
       uint32 MXF_EXPORTED mxfA708RxSamplingSingleRead(HMXF_BUFFER buffer, uint64 flags, uint64 label, MXF_A708_SAMPREC* rec);
      
       uint32 MXF_EXPORTED mxfA708RxSamplingMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA708RxSamplingMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      
       uint32 MXF_EXPORTED mxfA708AsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_A708* msg);
       uint32 MXF_EXPORTED mxfA708AsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_A708* msg);

       uint32 MXF_EXPORTED mxfA708NextDataRecordPtrGet(MXF_A708_DATAREC* currentRec, MXF_A708_DATAREC** nextRec);
       uint32 MXF_EXPORTED mxfA708NextSamplingRecordPtrGet(MXF_A708_SAMPREC* currentRec, MXF_A708_SAMPREC** nextRec);

       uint32 MXF_EXPORTED mxfA708EmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfA708EmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, uint64* labels);
       uint32 MXF_EXPORTED mxfA708EmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                               uint64* recCount, uint64* bytesCount, MXF_A708_DATAREC* rec);
       uint32 MXF_EXPORTED mxfA708EmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_A708_DATAREC* rec, uint64* count );

   #ifdef __cplusplus
   }
   #endif

#endif
