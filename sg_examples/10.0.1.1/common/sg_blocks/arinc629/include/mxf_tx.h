/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_GEN_H_CONST
#define MXF_GEN_H_CONST

   typedef HMXF_HANDLE                                                    HMXF_SCHED;
   typedef HMXF_HANDLE                                                    HMXF_SCHED_MSG;
                                                                        
   #define MXF_TX_STATUS_OVERLOAD                                         0x00000001ULL
   #define MXF_TX_STATUS_TIMING_LOST                                      0x00000002ULL
   #define MXF_TX_STATUS_OVERFLOW                                         0x00000008ULL
   #define MXF_TX_STATUS_OVERHEAT                                         0x00000010ULL

   #define MXF_TXAPERIODIC_PRIORITY_LOW                                   0ULL
   #define MXF_TXAPERIODIC_PRIORITY_NORMAL                                1ULL
   #define MXF_TXAPERIODIC_PRIORITY_HIGH                                  2ULL

   #define MXF_TXAPERIODIC_CLEAR_OPT_NO_BLOCKING                          0x00000001ULL
   #define MXF_TXAPERIODIC_CLEAR_OPT_HWFIFO                               0x00000002ULL

   #define MXF_TXAPERIODIC_FLAG_DEFAULT                                   0x00000000ULL
   #define MXF_TXAPERIODIC_FLAG_USE_RECORD_ABSOLUTE_TIME                  0x00000001ULL
   #define MXF_TXAPERIODIC_FLAG_ABSOLUTE_START_TIME                       0x00000004ULL
   #define MXF_TXAPERIODIC_FLAG_USE_RECORD_RELATIVE_TIME                  0x00000008ULL

   #define MXF_TXPERIODIC_MJRFRAME_STATUS_STARTED                         0x00000001ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_STOPPED                         0x00000002ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_SIM_ERROR                       0x00000004ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_TX_OVERFLOW                     0x00000010ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_HALTED                          0x00000020ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_OVERLOAD                        0x00000040ULL
   #define MXF_TXPERIODIC_MJRFRAME_STATUS_BUS_QUIET                       0x00000080ULL

   #define MXF_TXPERIODIC_UPDATEMSG_CLEAR_OPT_DEFAULT                     0x00000000ULL
   #define MXF_TXPERIODIC_UPDATEMSG_CLEAR_OPT_WAIT                        0x00000001ULL

#endif


#if !defined(MXF_GEN_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_GEN_H

   #ifdef __cplusplus
   extern "C" {
   #endif

      uint32 MXF_EXPORTED mxfTxAperiodicBufferAlloc                  (HMXF_CHANNEL channel, uint64 priority, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
      uint32 MXF_EXPORTED mxfTxAperiodicBufferGet                    (HMXF_CHANNEL channel, uint64 priority, HMXF_BUFFER* buffer);
      uint32 MXF_EXPORTED mxfTxAperiodicBufferFree                   (HMXF_BUFFER buffer);
      uint32 MXF_EXPORTED mxfTxAperiodicBufferStatusGet              (HMXF_BUFFER buffer, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
      uint32 MXF_EXPORTED mxfTxAperiodicBufferInfoGet                (HMXF_BUFFER buffer, HMXF_CHANNEL* channel, uint64* priority);
      uint32 MXF_EXPORTED mxfTxAperiodicClear                        (HMXF_BUFFER buffer, uint64 options);
      uint32 MXF_EXPORTED mxfTxAperiodicWrite                        (HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, void* rec);
      uint32 MXF_EXPORTED mxfTxAperiodicWriteAsync                   (HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, void* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK writeCompletion, void* context);
 
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgBufferAlloc          (HMXF_CHANNEL channel, uint64 bufferIndex, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgBufferGet            (HMXF_CHANNEL channel, uint64 bufferIndex, HMXF_BUFFER* buffer);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgBufferFree           (HMXF_BUFFER buffer);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgBufferInfoGet        (HMXF_BUFFER buffer, HMXF_CHANNEL* channel, uint64* bufferIndex);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgBufferStatusGet      (HMXF_BUFFER buffer, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgWrite                (HMXF_BUFFER buffer, uint64 count, void* rec);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgWriteAsync           (HMXF_BUFFER buffer, uint64 count, void* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK writeCompletion, void* context);
      uint32 MXF_EXPORTED mxfTxPeriodicUpdateMsgClear                (HMXF_BUFFER handle, uint64 options);

      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameSet                 (HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 count, void* msg, void* properties);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameGet                 (HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 maxCount, uint64* count, void* msg, void* properties);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameMinorCountGet       (HMXF_CHANNEL channel, uint64 majorIndex, uint64* count);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameStart               (HMXF_CHANNEL channel, uint64 majorIndex, uint64 duration, void* properties);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameStop                (HMXF_CHANNEL channel, uint64 majorIndex, uint64 stopTime);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameClear               (HMXF_CHANNEL channel, uint64 majorIndex);
      uint32 MXF_EXPORTED mxfTxPeriodicMajorFrameStatusGet           (HMXF_CHANNEL channel, uint64 majorIndex, uint64* status);

      uint32 MXF_EXPORTED mxfTxPeriodicScheduleNew                   (HMXF_CHANNEL channel, HMXF_SCHED* sched);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleFree                  (HMXF_SCHED sched);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleMsgAdd                (HMXF_SCHED sched, uint64 period, uint64 phase, HMXF_SCHED_MSG* msg);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleMsgResume             (HMXF_SCHED_MSG msg);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleMsgSuspend            (HMXF_SCHED_MSG msg);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleBufferListAdd         (HMXF_SCHED_MSG msg, uint64 count, uint64 delay, HMXF_BUFFER* buffer);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleSingleMsgAdd          (HMXF_SCHED sched, uint64 period, uint64 phase, HMXF_BUFFER buffer, HMXF_SCHED_MSG* msg);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleResume                (HMXF_SCHED sched);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleRun                   (HMXF_SCHED sched);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleRunMulti              (uint64 count, HMXF_SCHED* sched);
      uint32 MXF_EXPORTED mxfTxPeriodicScheduleSuspend               (HMXF_SCHED sched);

   #ifdef __cplusplus
   }
   #endif

#endif
