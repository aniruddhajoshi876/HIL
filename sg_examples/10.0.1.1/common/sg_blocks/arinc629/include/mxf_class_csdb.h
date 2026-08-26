
/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_CSDB_H_CONST
#define MXF_CSDB_H_CONST

   #define KMXF_CSDB_MODULE_RX_TIMETAG_ENABLE                     KMXF_MODULE_RX_TIMETAG_ENABLE
   #define KMXF_CSDB_MODULE_RX_FIFO_AGING                         KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_CSDB_MODULE_RX_FIFO_AF                            KMXF_MODULE_RX_FIFO_AF
   #define KMXF_CSDB_MODULE_TX_FIFO_AF                            KMXF_MODULE_TX_FIFO_AF
   #define KMXF_CSDB_MODULE_TX_FIFO_AE                            KMXF_MODULE_TX_FIFO_AE

   #define KMXF_CSDB_SPEED                                        150000ULL
   #define KMXF_CSDB_BLOCKCOUNT                                   150001ULL
   
   #define KMXF_CSDB_PARITY                                       150002ULL
      #define VMXF_CSDB_PARITY_EVEN                                  0ULL
      #define VMXF_CSDB_PARITY_ODD                                   1ULL
      #define VMXF_CSDB_PARITY_NONE                                  2ULL
   
   #define KMXF_CSDB_STOPBITSIZE                                  150003ULL
   #define KMXF_CSDB_TX_RX_TEST_LB                                150004ULL

   #define KMXF_CSDB_TX_PORT_ENABLE                               150005ULL

   #define KMXF_CSDB_ELECTRICAL_SELECTION                         150006ULL
      #define VMXF_CSDBEH_MULTI_ELECTRICAL_SELECT_DEFAULT            0ULL
      #define VMXF_CSDBEH_MULTI_ELECTRICAL_SELECT_CUSTOM             1ULL
   
   #define KMXF_CSDB_TX_DIFF_VOLTAGE_HIGH                         150007ULL
   #define KMXF_CSDB_TX_DIFF_VOLTAGE_LOW                          150008ULL
   #define KMXF_CSDB_TX_VOLTAGE_OFFSET                            150009ULL
   
   #define KMXF_CSDB_TX_SLEW_RATE_SELECTION                       150010ULL
      #define VMXF_CSDBEH_MULTI_TX_SLEW_RATE_SELECT_DEFAULT          0ULL
      #define VMXF_CSDBEH_MULTI_TX_SLEW_RATE_SELECT_CUSTOM           1ULL
   
   #define KMXF_CSDB_TX_SLEW_RATE                                 150011ULL
   #define KMXF_CSDB_RX_DIFF_VOLTAGE_THRESHOLD                    150012ULL


   #define MXF_CSDB_DISCRETE_OUTPUT_TRIG_ON_TX                    0ULL
   #define MXF_CSDB_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR             1ULL

   #define MXF_CSDB_TX_REC_CTRL_PARITY_ERROR                      0x00004000
   #define MXF_CSDB_TX_REC_CTRL_DISCRETE_OUTPUT_TRIG              0x00002000
   #define MXF_CSDB_TX_REC_CTRL_LONG_WORD_SIZE                    0x00001000
   #define MXF_CSDB_TX_REC_CTRL_SHORT_WORD_SIZE                   0x00000800
   #define MXF_CSDB_TX_REC_CTRL_WORD_ERROR                        0x00000200
   #define MXF_CSDB_TX_REC_CTRL_WORD_ERROR_INDEX                  0x000000FF

   #define MXF_CSDB_RX_REC_CTRL_PARITY_ERROR                      0x00001000
   #define MXF_CSDB_RX_REC_CTRL_STOPBIT_ERROR                     0x00002000

#endif

#if !defined(MXF_CSDB_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_CSDB_H

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   repeatCount;
      uint8    data[12];
      uint32   reserved;
   }
   MXF_CSDB_DATAREC;

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   rate;
      uint32   errorCount;
      uint8    data[12];
   }
   MXF_CSDB_SAMPREC;

   #ifdef __cplusplus
   extern "C" {
   #endif

       uint32 MXF_EXPORTED mxfCSDBRxAcqMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfCSDBRxAcqMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
       uint32 MXF_EXPORTED mxfCSDBRxAcqRead(HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, MXF_CSDB_DATAREC* rec);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingExtEnableSet(HMXF_BUFFER buffer, uint64 state, uint64 count, uint64* labels);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingExtEnableAllGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, MXF_CSDB_SAMPREC* rec);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingSingleRead(HMXF_BUFFER buffer, uint64 flags, uint64 label, uint64 si, MXF_CSDB_SAMPREC* rec);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 maxcount, uint64* labels);
       uint32 MXF_EXPORTED mxfCSDBRxSamplingMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
    
       uint32 MXF_EXPORTED mxfCSDBTxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_CSDB_DATAREC* rec);

       uint32 MXF_EXPORTED mxfCSDBTxPeriodicUpdateMsgWrite(HMXF_BUFFER buffer, uint64 count, MXF_CSDB_DATAREC* rec);

       uint32 MXF_EXPORTED mxfCSDBAsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count,  MXF_MSGID_CSDB* msgid);
       uint32 MXF_EXPORTED mxfCSDBAsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_CSDB* msgid);
    
       uint32 MXF_EXPORTED mxfCSDBNextDataRecordPtrGet(MXF_CSDB_DATAREC* currentRec, MXF_CSDB_DATAREC** nextRec);
       uint32 MXF_EXPORTED mxfCSDBNextSamplingRecordPtrGet(MXF_CSDB_SAMPREC* currentRec, MXF_CSDB_SAMPREC** nextRec);

       uint32 MXF_EXPORTED mxfCSDBEmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_CSDB* msgid);
       uint32 MXF_EXPORTED mxfCSDBEmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_CSDB* msgid);
       uint32 MXF_EXPORTED mxfCSDBEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                               uint64* recCount, uint64* bytesCount, MXF_CSDB_DATAREC* rec);
       uint32 MXF_EXPORTED mxfCSDBEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_CSDB_DATAREC* rec, uint64* recCount );
   
   #ifdef __cplusplus
   }
   #endif


#endif
