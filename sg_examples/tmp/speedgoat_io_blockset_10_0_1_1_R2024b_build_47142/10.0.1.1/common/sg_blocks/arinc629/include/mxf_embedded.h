/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef _MXF_EMBEDDED_H_CONST_
#define _MXF_EMBEDDED_H_CONST_

#include "mxfapi.h"
#include <stdarg.h>

#ifdef __MX_EMBEDDED
   #define printf mxfEmbeddedPrintf
#endif

typedef struct
{
   uint32 channelClass;
   uint32 moduleType;
   uint32 moduleIndex;
   uint32 portIndex;
   uint64 handle;

   void*  rec;
   uint64 *reserved;

   struct
   {
      uint32 rxAcqTrigFound;
   }
   Trigger;

   struct
   {
      uint32 rxAcqIgnore;
      uint32 rxSamplingIgnore;
   }
   Filter;

   uint32   reserved2[5];

} MXF_EMBEDDED_RX_INFO;

typedef struct
{
   uint32   channelClass;
   uint32   moduleType;
   uint32   moduleIndex;
   uint32   portIndex;
   uint64   handle;

   uint32   bufferIndex;
   uint32   reserved2[9];

} MXF_EMBEDDED_TXPERIODIC_UPDATEMSG_INFO;

typedef struct
{
   uint32   channelClass;
   uint32   moduleIndex;
   uint32   portIndex;
   uint32   reserved1;
   uint64   handle;

   uint32   priority;
   uint32   options;

   uint32   reserved2;
   uint32   bufferCount;
   void*    buffer;
   uint64*  reserved;

   uint32   reserved3[4];

} MXF_EMBEDDED_TXAPERIODIC_MSG;

typedef struct
{
   uint32   channelClass;
   uint32   moduleIndex;
   uint32   portIndex;
   uint32   options;
   uint64   handle;

   uint32   reserved1;
   uint32   bufferIndex;

   uint32   reserved2;
   uint32   bufferCount;
   void*    buffer;
   uint64*  reserved;

   uint32   reserved3[4];

} MXF_EMBEDDED_TXPERIODIC_UPDATEMSG;

#define MXF_EMBEDDED_TXAPERIODIC_FLAG_DEFAULT                     MXF_TXAPERIODIC_FLAG_DEFAULT
#define MXF_EMBEDDED_TXAPERIODIC_FLAG_USE_RECORD_ABSOLUTE_TIME    MXF_TXAPERIODIC_FLAG_USE_RECORD_ABSOLUTE_TIME

#define MXF_EMBEDDED_TXAPERIODIC_PRIORITY_LOW                     MXF_TXAPERIODIC_PRIORITY_LOW
#define MXF_EMBEDDED_TXAPERIODIC_PRIORITY_NORMAL                  MXF_TXAPERIODIC_PRIORITY_NORMAL
#define MXF_EMBEDDED_TXAPERIODIC_PRIORITY_HIGH                    MXF_TXAPERIODIC_PRIORITY_HIGH

#define MXF_EMBEDDED_TXPERIODIC_UPDATEMSG_OPTIONS_DEFAULT         0
#define MXF_EMBEDDED_TXPERIODIC_UPDATEMSG_OPTIONS_CLEAR           1

#define MXF_EMBEDDED_RECTYPE_DATAREC                              MXF_RECTYPE_DATAREC

#ifdef __MXF_EMBEDDED

uint32 mxfEmbeddedTxAperiodicWrite(MXF_EMBEDDED_TXAPERIODIC_MSG* txWriteInfo);
uint32 mxfEmbeddedTxPeriodicUpdateMsgWrite(MXF_EMBEDDED_TXPERIODIC_UPDATEMSG* txWriteInfo);

uint32 mxfEmbeddedDeviceTimerGet(uint64* timer);

uint32 mxfEmbeddedSharedBufferRead(uint32 offset, uint32 size, uint32* data);
uint32 mxfEmbeddedSharedBufferWrite(uint32 offset, uint32 size, uint32* data);

uint32 mxfEmbeddedTimerHandlerEnableSet(uint32 period, uint32 enable);

uint32 mxfEmbeddedRxBufferWrite(uint32 index, uint32 count, MXF_EMBEDDED_DATAREC* rec);
uint32 mxfEmbeddedRxBufferCountGet(uint32 index, uint32* count);

uint32 mxfEmbeddedTxBufferRead(uint32 index, uint32 maxMsgCount, uint32 maxBytesCount, uint32* msgCount, uint32* byteCount, MXF_EMBEDDED_DATAREC* rec);
uint32 mxfEmbeddedTxBufferCountGet(uint32 index, uint32* count);

uint32 mxfEmbeddedPortDiscreteWrite(uint32 moduleIndex, uint32 portIndex, uint32 mask, uint32 data);
uint32 mxfEmbeddedPortDiscreteRead(uint32 moduleIndex, uint32 portIndex, uint32 mask, uint32* data);

uint32 mxfEmbeddedNextRecordPtrGet(uint32 channelClass, uint32 recType, void* currentRec, void** nextRec);

extern int mxfEmbeddedPrintf(const char* format, ...);

#endif

#endif
