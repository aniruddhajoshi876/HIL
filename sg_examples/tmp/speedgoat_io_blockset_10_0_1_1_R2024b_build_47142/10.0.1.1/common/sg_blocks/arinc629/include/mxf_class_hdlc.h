/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_HDLC_H_CONST
#define MXF_HDLC_H_CONST

   #define KMXF_HDLC_MODULE_RX_FIFO_AGING                      KMXF_MODULE_RX_FIFO_AGING
   #define KMXF_HDLC_MODULE_RX_FIFO_AF                         KMXF_MODULE_RX_FIFO_AF
   #define KMXF_HDLC_MODULE_TX_FIFO_AF                         KMXF_MODULE_TX_FIFO_AF
   #define KMXF_HDLC_MODULE_TX_FIFO_AE                         KMXF_MODULE_TX_FIFO_AE
   #define KMXF_HDLC_MODULE_RX_TIMETAG_ENABLE                  KMXF_MODULE_RX_TIMETAG_ENABLE

   #define KMXF_HDLC_DATA_ENCODING                             160000ULL
      #define VMXF_HDLC_ENCODING_NRZ                              0ULL
      #define VMXF_HDLC_ENCODING_NRZI                             1ULL
      #define VMXF_HDLC_ENCODING_FM1                              2ULL
      #define VMXF_HDLC_ENCODING_FM0                              3ULL
      #define VMXF_HDLC_ENCODING_MANCHESTER                       4ULL

   #define KMXF_HDLC_FCS_TYPE                                  160001ULL
      #define VMXF_HDLC_TX_RX_FCS_NONE                            0ULL
      #define VMXF_HDLC_TX_RX_FCS_CRC16                           1ULL
      #define VMXF_HDLC_TX_RX_FCS_CCITTCRC                        2ULL

   #define KMXF_HDLC_FRAME_SIZE_ENABLE                         160002ULL

   #define KMXF_HDLC_CLOCK_SOURCE                              160003ULL
      #define VMXF_HDLC_CLOCK_SOURCE_EXTERNAL                     0ULL
      #define VMXF_HDLC_CLOCK_SOURCE_INTERNAL                     1ULL

   #define KMXF_HDLC_INTERNAL_CLOCK_FREQ                       160004ULL

   #define KMXF_HDLC_TX_RX_TEST_LB                             160005ULL

   #define KMXF_HDLC_TX_INTERFRAME_TIME_FILL                   160006ULL
      #define VMXF_HDLC_TX_INTERFRAME_TIME_FILL_NONE              0ULL
      #define VMXF_HDLC_TX_INTERFRAME_TIME_FILL_FLAGS             1ULL

   #define KMXF_HDLC_ELECTRICAL_SELECTION                      160007ULL
      #define VMXF_HDLC_ELECTRICAL_SELECT_DEFAULT                 0ULL
      #define VMXF_HDLC_ELECTRICAL_SELECT_CUSTOM                  1ULL

   #define KMXF_HDLC_TX_SLEW_RATE_SELECTION                    160008ULL
      #define VMXF_HDLC_TX_SLEW_RATE_SELECT_DEFAULT               0ULL
      #define VMXF_HDLC_TX_SLEW_RATE_SELECT_CUSTOM                1ULL

   #define KMXF_HDLC_TX_SLEW_RATE                              160009ULL
   #define KMXF_HDLC_TX_DIFF_VOLTAGE_HIGH                      160010ULL
   #define KMXF_HDLC_TX_DIFF_VOLTAGE_LOW                       160011ULL
   #define KMXF_HDLC_TX_VOLTAGE_OFFSET                         160012ULL
   #define KMXF_HDLC_RX_DIFF_VOLTAGE_THRESHOLD                 160013ULL


   #define MXF_HDLC_TX_REC_CTRL_OPENING_FLAG_NOT_SEND          0x00000001
   #define MXF_HDLC_TX_REC_CTRL_CLOSING_FLAG_NOT_SEND          0x00000002
   #define MXF_HDLC_TX_REC_CTRL_ABORT_SEND                     0x00000080
   #define MXF_HDLC_TX_REC_CTRL_FCS_NOT_SEND                   0x00010000
   #define MXF_HDLC_TX_REC_CTRL_FRAMESIZE_NOT_SEND             0x00020000
   #define MXF_HDLC_TX_REC_CTRL_DISCRETE_OUTPUT_TRIG           0x00080000

   #define MXF_HDLC_RX_REC_CTRL_OPENING_FLAG                   0x00000001
   #define MXF_HDLC_RX_REC_CTRL_CLOSING_FLAG                   0x00000002
   #define MXF_HDLC_RX_REC_CTRL_CLOSING_ERROR                  0x00000020
   #define MXF_HDLC_RX_REC_CTRL_ABORT                          0x00000080
   #define MXF_HDLC_RX_REC_CTRL_DECODING_ERROR                 0x00000100
   #define MXF_HDLC_RX_REC_CTRL_FCS_ERROR                      0x00010000
   #define MXF_HDLC_RX_REC_CTRL_FRAMESIZE_ERROR                0x00020000

   #define MXF_HDLC_DISCRETE_OUTPUT_TRIG_ON_TX                 0ULL
   #define MXF_HDLC_DISCRETE_OUTPUT_TRIG_ON_BUS_ERROR          1ULL

#endif

#if !defined(MXF_HDLC_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_HDLC_H

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   dataSize;
      uint32   repeatCount;
      uint32   reserved;

      uint16   data[2048];
   }
   MXF_HDLC_DATAREC;

   #ifdef __cplusplus
   extern "C" {
   #endif

       uint32 MXF_EXPORTED mxfHDLCTxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_HDLC_DATAREC* rec);
       uint32 MXF_EXPORTED mxfHDLCRxAcqRead(HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* status, uint64* msgCount, uint64* byteCount, MXF_HDLC_DATAREC* rec);
       uint32 MXF_EXPORTED mxfHDLCNextDataRecordPtrGet(MXF_HDLC_DATAREC* currentRec, MXF_HDLC_DATAREC** nextRec);
       uint32 MXF_EXPORTED mxfHDLCEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                               uint64* recCount, uint64* bytesCount, MXF_HDLC_DATAREC* rec);
       uint32 MXF_EXPORTED mxfHDLCEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, MXF_HDLC_DATAREC* rec, uint64* count );
   
   #ifdef __cplusplus
   }
   #endif

#endif
