/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_BM_H_CONST
#define MXF_BM_H_CONST

   typedef HMXF_HANDLE                                                           HMXF_COND_LIST;
   typedef HMXF_HANDLE                                                           HMXF_BRIDGE;

   #define MXF_RX_STATUS_WORD_LENGTH                                             0x00000001ULL
   #define MXF_RX_STATUS_OVERFLOW                                                0x00000002ULL
   #define MXF_RX_STATUS_STRING_ERROR                                            0x00000004ULL
   #define MXF_RX_STATUS_GAP_LENGTH                                              0x00000010ULL

   #define MXF_RXACQ_MODE_LINEAR                                                 0ULL
   #define MXF_RXACQ_MODE_CIRCULAR                                               1ULL

   #define MXF_RXACQ_FLAG_DEFAULT                                                0x00000000ULL
   #define MXF_RXACQ_FLAG_ABSOLUTE_START_TIME                                    0x00000002ULL

   #define MXF_RXACQ_STATUS_WAIT_START_TIME                                      0x00000001ULL
   #define MXF_RXACQ_STATUS_WAIT_TRIG                                            0x00000002ULL
   #define MXF_RXACQ_STATUS_RUNNING                                              0x00000004ULL
   #define MXF_RXACQ_STATUS_STOPPED                                              0x00000008ULL
   #define MXF_RXACQ_STATUS_OVERFLOW                                             0x00000100ULL
   #define MXF_RXACQ_STATUS_BUFFER_FULL                                          0x00000200ULL
   #define MXF_RXACQ_STATUS_RUN_TIMED_OUT                                        0x00000400ULL
   #define MXF_RXACQ_STATUS_TRIG_TIMED_OUT                                       0x00000800ULL
   #define MXF_RXACQ_STATUS_OUT_OF_RESOURCES                                     0x00002000ULL
   #define MXF_RXACQ_STATUS_TRIG_OCCURRED                                        0x00008000ULL

   #define MXF_RXACQ_TRIG_COND_ID_ACQRUN                                         1ULL
   #define MXF_RXACQ_TRIG_COND_ID_RDATA_DW                                       2ULL

   #define MXF_RXACQ_TRIG_COND_EXPR_OR                                           0ULL
   #define MXF_RXACQ_TRIG_COND_EXPR_AND                                          1ULL

   #define MXF_RXACQ_TRIG_COND_RDATA_OPTIONS_EQUAL                               0ULL
   #define MXF_RXACQ_TRIG_COND_RDATA_OPTIONS_NOTEQUAL                            1ULL

   #define MXF_RXSAMPLING_FLAG_DEFAULT                                           0x00000000ULL
   #define MXF_RXSAMPLING_FLAG_ERASE_WHEN_READ                                   0x00000001ULL

   #define MXF_RXSAMPLING_STATUS_RUNNING                                         0x00000004ULL
   #define MXF_RXSAMPLING_STATUS_STOPPED                                         0x00000008ULL
   #define MXF_RXSAMPLING_STATUS_OVERFLOW                                        0x00000200ULL
   #define MXF_RXSAMPLING_STATUS_OUT_OF_RESOURCES                                0x00002000ULL

   #define MXF_MSG_SELECT_OPTION_DEFAULT                                         0ULL
   #define MXF_MSG_SELECT_OPTION_EXTENDED                                        1ULL

#endif

#if !defined(MXF_BM_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_BM_H

   typedef struct
   {
      uint64         mask;
      uint64         data;
      uint64         offset;
      uint64         options;
   }
   MXF_RXACQ_TRIG_COND_RDATA_DW_PARM;

   typedef struct
   {
      HMXF_CHANNEL   channel[32];
      uint64         count;
      uint64         reserved;
   }
   MXF_RXACQ_TRIG_COND_ACQRUN_PARM;

   #ifdef __cplusplus
   extern "C" {
   #endif

   uint32 MXF_EXPORTED mxfRxAcqBufferAlloc               (HMXF_CHANNEL channel, uint64 size, HMXF_BUFFER* buffer, uint64 *allocated);
   uint32 MXF_EXPORTED mxfRxAcqBufferGet                 (HMXF_CHANNEL channel, HMXF_BUFFER* buffer);
   uint32 MXF_EXPORTED mxfRxAcqBufferFree                (HMXF_BUFFER buffer);
   uint32 MXF_EXPORTED mxfRxAcqBufferStatusGet           (HMXF_BUFFER buffer, uint64* status, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
   uint32 MXF_EXPORTED mxfRxAcqBufferInfoGet             (HMXF_BUFFER buffer, HMXF_CHANNEL* channel);
   uint32 MXF_EXPORTED mxfRxAcqModeGet                   (HMXF_BUFFER buffer, uint64* mode);
   uint32 MXF_EXPORTED mxfRxAcqModeSet                   (HMXF_BUFFER buffer, uint64 mode);
   uint32 MXF_EXPORTED mxfRxAcqMsgSelectGet              (HMXF_BUFFER buffer, uint64 options, uint64 maxCount, uint64* count, void* msg);
   uint32 MXF_EXPORTED mxfRxAcqMsgSelectSet              (HMXF_BUFFER buffer, uint64 options, uint64 select, uint64 count, void* msg);
   uint32 MXF_EXPORTED mxfRxAcqStart                     (HMXF_BUFFER buffer, uint64 flags, uint64 startTime, uint64 duration);
   uint32 MXF_EXPORTED mxfRxAcqStop                      (HMXF_BUFFER buffer);
   uint32 MXF_EXPORTED mxfRxAcqStopTimeGet               (HMXF_BUFFER buffer, uint64* stopTime);
   uint32 MXF_EXPORTED mxfRxAcqClear                     (HMXF_BUFFER buffer);
   uint32 MXF_EXPORTED mxfRxAcqRead                      (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, void* rec);
   uint32 MXF_EXPORTED mxfRxAcqReadAsync                 (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, void* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK readCompletion, void* context);
   uint32 MXF_EXPORTED mxfRxAcqTrigEnableGet             (HMXF_BUFFER buffer, uint64* state);
   uint32 MXF_EXPORTED mxfRxAcqTrigEnableSet             (HMXF_BUFFER buffer, uint64 state);
   uint32 MXF_EXPORTED mxfRxAcqTrigSet                   (HMXF_BUFFER buffer, HMXF_COND_LIST condList, uint64 pretrigCount);
   uint32 MXF_EXPORTED mxfRxAcqTrigTimeGet               (HMXF_BUFFER buffer, uint64* time);
   uint32 MXF_EXPORTED mxfRxAcqTrigConditionListAlloc    (HMXF_SERVER server, HMXF_COND_LIST* condList);
   uint32 MXF_EXPORTED mxfRxAcqTrigConditionListFree     (HMXF_COND_LIST condList);
   uint32 MXF_EXPORTED mxfRxAcqTrigConditionListExprSet  (HMXF_COND_LIST condList, uint64 expression);
   uint32 MXF_EXPORTED mxfRxAcqTrigConditionAdd          (HMXF_COND_LIST condList, uint64 id, void* param);

   uint32 MXF_EXPORTED mxfRxSamplingBufferAlloc          (HMXF_CHANNEL channel, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
   uint32 MXF_EXPORTED mxfRxSamplingBufferGet            (HMXF_CHANNEL channel, HMXF_BUFFER* buffer);
   uint32 MXF_EXPORTED mxfRxSamplingBufferFree           (HMXF_BUFFER buffer);
   uint32 MXF_EXPORTED mxfRxSamplingBufferStatusGet      (HMXF_BUFFER buffer, uint64* status, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
   uint32 MXF_EXPORTED mxfRxSamplingBufferInfoGet        (HMXF_BUFFER buffer, HMXF_CHANNEL* channel);
   uint32 MXF_EXPORTED mxfRxSamplingExtEnableSet         (HMXF_BUFFER buffer, uint64 state, uint64 count, void* msg);
   uint32 MXF_EXPORTED mxfRxSamplingExtEnableAllGet      (HMXF_BUFFER buffer, uint64 maxCount, uint64* count, void* msg);
   uint32 MXF_EXPORTED mxfRxSamplingKilltimeGet          (HMXF_BUFFER buffer, uint64* time);
   uint32 MXF_EXPORTED mxfRxSamplingKilltimeSet          (HMXF_BUFFER buffer, uint64 time);
   uint32 MXF_EXPORTED mxfRxSamplingMaxRecordsGet        (HMXF_BUFFER buffer, uint64* address, uint64* ext);
   uint32 MXF_EXPORTED mxfRxSamplingMsgSelectSet         (HMXF_BUFFER buffer, uint64 options, uint64 select, uint64 count, void* msg);
   uint32 MXF_EXPORTED mxfRxSamplingMsgSelectGet         (HMXF_BUFFER buffer, uint64 options, uint64 maxCount, uint64* count, void* msg);
   uint32 MXF_EXPORTED mxfRxSamplingRead                 (HMXF_BUFFER buffer, uint64 flags, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, void* rec);
   uint32 MXF_EXPORTED mxfRxSamplingReadAsync            (HMXF_BUFFER buffer, uint64 flags, uint64 maxMsgCount, uint64 maxBytesCount, void* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK readCompletion, void* context);
   uint32 MXF_EXPORTED mxfRxSamplingSingleRead           (HMXF_BUFFER buffer, uint64 flags, void* msg, void* rec);
   uint32 MXF_EXPORTED mxfRxSamplingSingleReadAsync      (HMXF_BUFFER buffer, uint64 flags, void* msg, void* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK readCompletion, void* context);
   uint32 MXF_EXPORTED mxfRxSamplingRecordSizeGet        (HMXF_BUFFER buffer, uint64* size);
   uint32 MXF_EXPORTED mxfRxSamplingStart                (HMXF_BUFFER buffer);
   uint32 MXF_EXPORTED mxfRxSamplingStop                 (HMXF_BUFFER buffer);

   uint32 MXF_EXPORTED mxfBridgeConfigGet                (HMXF_BRIDGE bridge, HMXF_CHANNEL* source, HMXF_BUFFER* destination, uint64* delay);
   uint32 MXF_EXPORTED mxfBridgeConfigSet                (HMXF_BRIDGE bridge, uint64 delay);
   uint32 MXF_EXPORTED mxfBridgeCreate                   (HMXF_CHANNEL source, HMXF_BUFFER destination, HMXF_BRIDGE* bridge);
   uint32 MXF_EXPORTED mxfBridgeSelectGet                (HMXF_BRIDGE bridge, uint64 address, uint64* modulo, char* action);
   uint32 MXF_EXPORTED mxfBridgeSelectSet                (HMXF_BRIDGE bridge, uint64 address, uint64 modulo, const char* action);
   uint32 MXF_EXPORTED mxfBridgeStart                    (HMXF_BRIDGE bridge);
   uint32 MXF_EXPORTED mxfBridgeStop                     (HMXF_BRIDGE bridge);
   uint32 MXF_EXPORTED mxfBridgeTerminate                (HMXF_BRIDGE bridge);

   #ifdef __cplusplus
   }
   #endif

#endif
