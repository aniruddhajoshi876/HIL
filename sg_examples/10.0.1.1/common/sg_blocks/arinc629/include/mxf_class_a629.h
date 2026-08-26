/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_A629_H_CONST
#define MXF_A629_H_CONST

   #define KMXF_A629_MODULE_TI                                                   KMXF_MODULE_TI

   #define KMXF_A629_MODULE_SG                                                   KMXF_MODULE_SG
      #define VMXF_A629_MODULE_SG_16                                                0ULL
      #define VMXF_A629_MODULE_SG_32                                                1ULL
      #define VMXF_A629_MODULE_SG_64                                                2ULL
      #define VMXF_A629_MODULE_SG_127                                               3ULL

   #define KMXF_A629_MODULE_INTERFACE                                            KMXF_MODULE_INTERFACE
      #define VMXF_A629_MODULE_INTERFACE_SIM                                        0ULL
      #define VMXF_A629_MODULE_INTERFACE_TTL                                        1ULL

   #define KMXF_A629_MODULE_RX_ONLY                                              KMXF_MODULE_RX_ONLY
   #define KMXF_A629_MODULE_XPP_FIFO_AGING                                       KMXF_MODULE_XPP_FIFO_AGING
   #define KMXF_A629_MODULE_XPP_FIFO_AF                                          KMXF_MODULE_XPP_FIFO_AF
   #define KMXF_A629_MODULE_XPP_CID_ENABLE                                       KMXF_MODULE_XPP_CID_ENABLE
   #define KMXF_A629_MODULE_XPP_DUAL_ENABLE                                      KMXF_MODULE_XPP_DUAL_ENABLE
   #define KMXF_A629_MODULE_BM_FIFO_AGING                                        KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_A629_MODULE_BM_FIFO_AF                                           KMXF_MODULE_RX_FIFO_AF

   #define KMXF_A629_RT_TG                                                       140000ULL
   #define KMXF_A629_RT_CID                                                      140001ULL
   #define KMXF_A629_RT_ALTERNATE_SCHED                                          140002ULL

   #define KMXF_A629_BM_MODE                                                     140004ULL
      #define VMXF_A629_BM_MODE_STRING                                              1ULL
      #define VMXF_A629_BM_MODE_WORD                                                2ULL

   #define MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES_MODE_BLOCK                    0ULL
   #define MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES_MODE_INDEPENDENT              1ULL

   #define MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_DEFAULT                          0x00000000ULL
   #define MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_SYNC                             0x00000001ULL
   #define MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_UNUSED                           0x00000002ULL
   #define MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_VARIABLE_LENGTH                  0x00000004ULL
   #define MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_CRC_ENABLE                       0x00000010ULL

   #define MXF_A629_TX_REC_CTRL_FC_NO_INC                                        0x01000000
   #define MXF_A629_TX_REC_CTRL_FC_NO_SEND                                       0x02000000
   #define MXF_A629_TX_REC_CTRL_CRC_ERROR                                        0x08000000
   #define MXF_A629_TX_REC_CTRL_ERROR_INJ                                        0x10000000 //When set, use hardware error index (MXF_A629_TX_REC_CTRL_ERROR_INJ_INDEX)
   #define MXF_A629_TX_REC_CTRL_ERROR_INJ_INDEX                                  0x0000007F //Error index used when MXF_A629_TX_REC_CTRL_ERROR_INJ is set (0-99)

   #define MXF_A629_RX_REC_CTRL_WORD_LABEL                                       0x00000002
   #define MXF_A629_RX_REC_CTRL_WORD_MANCHESTER_ERROR                            0x00000004
   #define MXF_A629_RX_REC_CTRL_WORD_PARITY_ERROR                                0x00000008
   #define MXF_A629_RX_REC_CTRL_WORD_BUFFER_OVERFLOW                             0x00000010
   #define MXF_A629_RX_REC_CTRL_WORD_EOS                                         0x00000020
   #define MXF_A629_RX_REC_CTRL_WORD_CRC_ERROR                                   0x00000040
   #define MXF_A629_RX_REC_CTRL_WORD_SOF                                         0x00000080
   #define MXF_A629_RX_REC_CTRL_WORD_INTERNAL_TRANSMIT                           0x00000100
   #define MXF_A629_RX_REC_CTRL_WORD_DATA_SYNC_ERROR                             0x00000200

   #define MXF_A629_RX_REC_CTRL_STRING_BUFFER_OVERFLOW                           0x00000010
   #define MXF_A629_RX_REC_CTRL_STRING_CRC_ERROR                                 0x00000040
   #define MXF_A629_RX_REC_CTRL_STRING_SOF                                       0x00000080
   #define MXF_A629_RX_REC_CTRL_STRING_INTERNAL_TRANSMIT                         0x00000100
   #define MXF_A629_RX_REC_CTRL_STRING_DATA_SYNC_ERROR                           0x00000200

   #define MXF_A629_RX_REC_CTRL_STRING_CRC_ENABLED                               0x00010000
   #define MXF_A629_RX_REC_CTRL_STRING_LABEL_MANCHESTER_ERROR                    0x00020000
   #define MXF_A629_RX_REC_CTRL_STRING_LABEL_PARITY_ERROR                        0x00040000
   #define MXF_A629_RX_REC_CTRL_STRING_DATA_MANCHESTER_ERROR                     0x00080000
   #define MXF_A629_RX_REC_CTRL_STRING_DATA_PARITY_ERROR                         0x00100000
   #define MXF_A629_RX_REC_CTRL_STRING_EOS_ERROR                                 0x00200000

   #define MXF_A629_ERRORID_NONE                                                 0
   #define MXF_A629_ERRORID_GAP                                                  1
   #define MXF_A629_ERRORID_SYNC_INVERT                                          2
   #define MXF_A629_ERRORID_PPSYNC                                               3
   #define MXF_A629_ERRORID_PSYNC                                                4
   #define MXF_A629_ERRORID_SHORT_WORD                                           5
   #define MXF_A629_ERRORID_LONG_WORD                                            6
   #define MXF_A629_ERRORID_PARITY_INVERT                                        7
   #define MXF_A629_ERRORID_DATA_MANCHZEROCROSSING                               8
   #define MXF_A629_ERRORID_SYNC_MANCHZEROCROSSING                               9
   #define MXF_A629_ERRORID_BUS_QUIET                                            10

   #define MXF_A629_DISCRETE_OUTPUT_TRIG_ON_TX                                   0ULL
   #define MXF_A629_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR                            1ULL

#endif

#if !defined(MXF_A629_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_A629_H

   typedef struct
   {
      uint64      timeTag;
      uint32      control;
      uint32      dataSize;
      uint32      repeatCount;
      uint32      reserved;
      uint16      data[258];
      uint16      reserved2[2];
   }
   MXF_A629_DATAREC;

   typedef struct
   {
      uint64      timeTag;
      uint32      control;
      uint32      rate;
      uint32      errorCount;
      uint32      dataSize;
      uint16      data[258];
      uint16      reserved[2];
   }
   MXF_A629_SAMPREC;

   typedef struct
   {
      uint32      mode;
      uint32      reserved;
   }
   MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES;

   typedef struct
   {
      HMXF_BUFFER buffer;
      uint16      options;
      uint16      length;
      uint16      label;
      uint16      cid;
   }
   MXF_A629_TXPERIODIC_MJRFRAME_MSG;

   typedef struct
   {
      uint16      syncIndex;
      uint16      altIndex;
      uint16      reserved[2];
   }
   MXF_A629_TXPERIODIC_MJRFRAME_SYNC;

   typedef struct
   {
      uint64      enable;
      uint64      position;
      uint64      mask;
      uint64      modulo;
   }
   MXF_A629_FC;

   typedef struct
   {
      uint16      error[257];
      uint16      reserved[3];
   }
   MXF_A629_ERROR_INJ;

   #ifdef __cplusplus
   extern "C" {
   #endif

      uint32 MXF_EXPORTED mxfA629AsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 maxCount, MXF_MSGID_A629* msg);
      uint32 MXF_EXPORTED mxfA629AsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_A629* msg);

      uint32 MXF_EXPORTED mxfA629TxPeriodicMajorFrameSyncSet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 columnIndex, MXF_A629_TXPERIODIC_MJRFRAME_SYNC* sync);
      uint32 MXF_EXPORTED mxfA629TxPeriodicMajorFrameSyncGet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 columnIndex, MXF_A629_TXPERIODIC_MJRFRAME_SYNC* sync);
      uint32 MXF_EXPORTED mxfA629TxPeriodicMajorFrameStart(HMXF_CHANNEL channel, uint64 majorIndex, MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES* properties);
      uint32 MXF_EXPORTED mxfA629TxPeriodicMajorFrameGet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 maxCount, uint64* count, MXF_A629_TXPERIODIC_MJRFRAME_MSG* msg);
      uint32 MXF_EXPORTED mxfA629TxPeriodicMajorFrameSet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 count, MXF_A629_TXPERIODIC_MJRFRAME_MSG* msg);
            
      uint32 MXF_EXPORTED mxfA629TxPeriodicUpdateMsgWrite(HMXF_BUFFER buffer, uint64 count, MXF_A629_DATAREC* rec);
      uint32 MXF_EXPORTED mxfA629RxAcqMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxAcqMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 maxCount, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxAcqRead(HMXF_BUFFER buffer, uint64 maxRecCount, uint64 maxBytesCount, uint64* status, uint64* recCount, uint64* bytesCount, MXF_A629_DATAREC* rec);

      uint32 MXF_EXPORTED mxfA629RxSamplingMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxSamplingMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 count, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxSamplingExtEnableSet(HMXF_BUFFER buffer, uint64 state, uint64 count, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxSamplingExtEnableAllGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* labels);
      uint32 MXF_EXPORTED mxfA629RxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxRecCount, uint64 maxBytesCount, uint64* recCount, uint64* bytesCount, MXF_A629_SAMPREC* rec);
      uint32 MXF_EXPORTED mxfA629RxSamplingSingleRead(HMXF_BUFFER buffer, uint64 flags, uint64 label, uint64 cid, MXF_A629_SAMPREC* rec);

      uint32 MXF_EXPORTED mxfA629NextDataRecordPtrGet(MXF_A629_DATAREC *currentRec, MXF_A629_DATAREC** nextRec);
      uint32 MXF_EXPORTED mxfA629NextSamplingRecordPtrGet(MXF_A629_SAMPREC *currentRec, MXF_A629_SAMPREC** nextRec);

      uint32 MXF_EXPORTED mxfA629ErrorInjectionCompose(uint64 id, uint64 param, uint16* error);
      uint32 MXF_EXPORTED mxfA629ErrorInjectionSet(HMXF_CHANNEL channel, uint64 errorIndex, MXF_A629_ERROR_INJ* error);
      uint32 MXF_EXPORTED mxfA629ErrorInjectionGet(HMXF_CHANNEL channel, uint64 errorIndex, MXF_A629_ERROR_INJ* error);
      uint32 MXF_EXPORTED mxfA629ErrorInjectionCountGet(HMXF_CHANNEL channel, uint64* errorCount);

      uint32 MXF_EXPORTED mxfA629RxMsgCrcEnableSet(HMXF_CHANNEL channel, uint64 label, uint64 cid, uint64 enable);
      uint32 MXF_EXPORTED mxfA629RxMsgCrcEnableGet(HMXF_CHANNEL channel, uint64 label, uint64 cid, uint64* enable);

      uint32 MXF_EXPORTED mxfA629MsgFreshnessCounterSet(HMXF_BUFFER buffer, MXF_A629_FC* fc);
      uint32 MXF_EXPORTED mxfA629MsgFreshnessCounterGet(HMXF_BUFFER buffer, MXF_A629_FC* fc);

      uint32 MXF_EXPORTED mxfA629EmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_A629* msgid); // label-si?
      uint32 MXF_EXPORTED mxfA629EmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_A629* msgid);
      uint32 MXF_EXPORTED mxfA629EmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE nvStorage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                              uint64* recCount, uint64* bytesCount, MXF_A629_DATAREC* rec);
      uint32 MXF_EXPORTED mxfA629EmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE nvStorage, uint64 fileIndex, uint64 maxRecCount, MXF_A629_DATAREC* rec, uint64* count);

   #ifdef __cplusplus
   }
   #endif

#endif

