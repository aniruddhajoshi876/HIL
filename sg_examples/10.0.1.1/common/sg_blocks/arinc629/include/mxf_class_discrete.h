/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_DISCRETE_H_CONST
#define MXF_DISCRETE_H_CONST

   #define KMXF_DISCRETE_MODULE_RX_TIMETAG_ENABLE                       KMXF_MODULE_RX_TIMETAG_ENABLE
   #define KMXF_DISCRETE_MODULE_RX_FIFO_AGING                           KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_DISCRETE_MODULE_RX_FIFO_AF                              KMXF_MODULE_RX_FIFO_AF
   #define KMXF_DISCRETE_MODULE_TX_FIFO_AF                              KMXF_MODULE_TX_FIFO_AF
   #define KMXF_DISCRETE_MODULE_TX_FIFO_AE                              KMXF_MODULE_TX_FIFO_AE

   #define KMXF_DISCRETE_NUMPORT                                        120000ULL
   #define KMXF_DISCRETE_RX_EDGE_FALLING                                120001ULL
   #define KMXF_DISCRETE_RX_EDGE_RISING                                 120002ULL
   #define KMXF_DISCRETE_TX_RX_TEST_LB                                  120003ULL
   #define KMXF_DISCRETE_RX_PULSE_WIDTH_FILTER                          120004ULL
   #define KMXF_DISCRETE_RX_FIFO_SAMP_PERIOD                            120005ULL
   #define KMXF_DISCRETE_RX_FIFO_SAMP_INTER_EDGE_ENABLE                 120006ULL

   #define KMXF_DISCRETE_ELECTRICAL_SELECTION                           120007ULL
      #define VMXF_DISCRETE_MULTI_ELECTRICAL_SELECT_DEFAULT              0ULL
      #define VMXF_DISCRETE_MULTI_ELECTRICAL_SELECT_CUSTOM               1ULL

   #define KMXF_DISCRETE_TX_SLEW_RATE_SELECTION                         120008ULL
      #define VMXF_DISCRETE_MULTI_TX_SLEW_RATE_SELECT_DEFAULT            0ULL
      #define VMXF_DISCRETE_MULTI_TX_SLEW_RATE_SELECT_CUSTOM             1ULL

   #define KMXF_DISCRETE_TX_SLEW_RATE                                   120009ULL
      #define VMXF_DISCRETE_TX_SLEW_RATE_LOW                             0ULL
      #define VMXF_DISCRETE_TX_SLEW_RATE_HIGH                            1ULL

   #define KMXF_DISCRETE_TX_DIFF_VOLTAGE_HIGH                           120010ULL
   #define KMXF_DISCRETE_TX_DIFF_VOLTAGE_LOW                            120011ULL
   #define KMXF_DISCRETE_TX_VOLTAGE_OFFSET                              120012ULL
   #define KMXF_DISCRETE_RX_DIFF_VOLTAGE_THRESHOLD                      120013ULL


   #define MXF_DISCRETE_TX_REC_CTRL_WAIT_EOP                            0x20000000
   #define MXF_DISCRETE_TX_REC_CTRL_WAIT_EOR                            0x10000000
   #define MXF_DISCRETE_TX_REC_CTRL_PULSE_START                         0x08000000

#endif

#if !defined(MXF_DISCRETE_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_DISCRETE_H

   typedef struct
   {
      uint64      timeTag;
      uint32      control;
      uint32      repeatCount;
      uint32      highDuration;   //Tx only
      uint32      lowDuration;    //Tx only
      uint32      data;
      uint32      edge;
   }
   MXF_DISCRETE_DATAREC;

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   rate;
      uint32   errorCount;
      uint32   reserved;
      uint32   data;
      uint32   edge;
   }
   MXF_DISCRETE_SAMPREC;

   #ifdef __cplusplus
   extern "C" {
   #endif
          
      uint32 MXF_EXPORTED mxfDiscreteTxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_DISCRETE_DATAREC* rec);
          
      uint32 MXF_EXPORTED mxfDiscreteRxAcqRead(HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, MXF_DISCRETE_DATAREC* rec);
      uint32 MXF_EXPORTED mxfDiscreteRxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, MXF_DISCRETE_SAMPREC* rec);
         
      uint32 MXF_EXPORTED mxfDiscreteNextDataRecordPtrGet(MXF_DISCRETE_DATAREC* currentRec, MXF_DISCRETE_DATAREC** nextRec);
          
      uint32 MXF_EXPORTED mxfDiscreteChannelRead(HMXF_CHANNEL channel, uint64 mask, uint64* data);
      uint32 MXF_EXPORTED mxfDiscreteChannelWrite(HMXF_CHANNEL channel, uint64 mask, uint64 data);

      uint32 MXF_EXPORTED mxfDiscreteEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                                  uint64* recCount, uint64* bytesCount, MXF_DISCRETE_DATAREC* rec);
      uint32 MXF_EXPORTED mxfDiscreteEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_DISCRETE_DATAREC* rec, uint64* recCount);

   #ifdef __cplusplus
   }
   #endif

#endif
