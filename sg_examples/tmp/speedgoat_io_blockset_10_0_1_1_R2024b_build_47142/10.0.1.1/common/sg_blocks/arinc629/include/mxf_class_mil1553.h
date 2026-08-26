/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_MIL1553_H_CONST
#define MXF_MIL1553_H_CONST

   #define KMXF_MIL1553_TX_RX_TEST_LB                                            130000ULL
   #define KMXF_MIL1553_TX_VOLTAGE                                               130001ULL
   
   #define KMXF_MIL1553_TRANSMITTER_ENABLE                                       130002ULL
      #define VMXF_MIL1553_TRANSMITTER_NONE                                         0ULL
      #define VMXF_MIL1553_TRANSMITTER_A                                            1ULL
      #define VMXF_MIL1553_TRANSMITTER_B                                            2ULL
      #define VMXF_MIL1553_TRANSMITTER_BOTH                                         3ULL
   
   #define KMXF_MIL1553_MILSTD1553_REV                                           130003ULL
      #define VMXF_MIL1553_MILSTD1553_REVA                                          0ULL
      #define VMXF_MIL1553_MILSTD1553_REVB                                          1ULL
   
   #define KMXF_MIL1553_INTERFACE                                                130004ULL
      #define VMXF_MIL1553_INTERFACE_MILSTD1553                                     0ULL
      #define VMXF_MIL1553_INTERFACE_RS485                                          1ULL
   
   #define KMXF_MIL1553_BM_MIN_RESPONSE_TIME                                     130005ULL
  
   #define KMXF_MIL1553_BM_MODE                                                  130006ULL
      #define VMXF_MIL1553_BM_MODE_WORD                                             0ULL
      #define VMXF_MIL1553_BM_MODE_STRING                                           1ULL
      #define VMXF_MIL1553_BM_MODE_MESSAGE                                          2ULL
  
   #define KMXF_MIL1553_BM_FIFO_AF                                               130007ULL
   #define KMXF_MIL1553_BM_FIFO_AGING                                            130008ULL
   #define KMXF_MIL1553_BM_RESPONSE_TIMEOUT                                      130009ULL
   #define KMXF_MIL1553_BM_UNEXPECTED_FILTER_ENABLE                              130010ULL
   #define KMXF_MIL1553_RT_RESPONSE_TIMEOUT                                      130011ULL
   #define KMXF_MIL1553_RT_RESPONSE_TIME                                         130012ULL
   #define KMXF_MIL1553_RT_DEFAULT_STATUS                                        130013ULL
   
   #define KMXF_MIL1553_RT_SSF_OPT                                               130014ULL
      #define VMXF_MIL1553_RT_SSF_OPT_SOFT                                          0ULL
      #define VMXF_MIL1553_RT_SSF_OPT_DISCRETE                                      1ULL
   
   #define KMXF_MIL1553_RT_TF_OPT                                                130015ULL
      #define VMXF_MIL1553_RT_TF_OPT_SOFT                                           0ULL
      #define VMXF_MIL1553_RT_TF_OPT_DISCRETE                                       1ULL
   
   #define KMXF_MIL1553_RT_ADDRESS                                               130016ULL
   #define KMXF_MIL1553_BC_RESPONSE_TIMEOUT                                      130017ULL
   
   #define KMXF_MIL1553_BC_GLOBAL_BUS_SELECTION                                  130018ULL
      #define VMXF_MIL1553_BUSSELECTION_A                                           0ULL
      #define VMXF_MIL1553_BUSSELECTION_B                                           1ULL
      #define VMXF_MIL1553_BUSSELECTION_BCMSG                                       2ULL
      #define VMXF_MIL1553_BUSSELECTION_BCMSG_ALT                                   3ULL
   
   #define KMXF_MIL1553_BC_APER_FIFO_AF                                          130019ULL
   #define KMXF_MIL1553_BC_APER_FIFO_AE                                          130020ULL
   #define KMXF_MIL1553_START_TIME                                               130021ULL
   
   #define KMXF_MIL1553_RECEIVER_ENABLE                                          130022ULL
      #define VMXF_MIL1553_RECEIVER_NONE                                            0ULL
      #define VMXF_MIL1553_RECEIVER_A                                               1ULL
      #define VMXF_MIL1553_RECEIVER_B                                               2ULL
      #define VMXF_MIL1553_RECEIVER_BOTH                                            3ULL

   #define MXF_MIL1553_MSGTYPE_RX                                                0
   #define MXF_MIL1553_MSGTYPE_TX                                                1
   #define MXF_MIL1553_MSGTYPE_MODECODE                                          2

   #define MXF_MIL1553_BUS_A                                                     0x00000001
   #define MXF_MIL1553_BUS_B                                                     0x00000002

   #define MXF_MIL1553_COMMAND_DIR_RX                                            0
   #define MXF_MIL1553_COMMAND_DIR_TX                                            1

   #define MXF_MIL1553_STATUS_ADDRESS                                            0xF800
   #define MXF_MIL1553_STATUS_MSGERR                                             0x0400
   #define MXF_MIL1553_STATUS_INST                                               0x0200
   #define MXF_MIL1553_STATUS_SRQ                                                0x0100
   #define MXF_MIL1553_STATUS_RES_BITS                                           0x00E0
   #define MXF_MIL1553_STATUS_BCST                                               0x0010
   #define MXF_MIL1553_STATUS_BUSY                                               0x0008
   #define MXF_MIL1553_STATUS_SSF                                                0x0004
   #define MXF_MIL1553_STATUS_DBCA                                               0x0002
   #define MXF_MIL1553_STATUS_TF                                                 0x0001

   #define MXF_MIL1553_RX_REC_CTRL_MSG_BUS_B                                     0x00000001
   #define MXF_MIL1553_RX_REC_CTRL_MSG_OVERLAP                                   0x00000008
   #define MXF_MIL1553_RX_REC_CTRL_MSG_MANCHESTER_ERROR                          0x00000010
   #define MXF_MIL1553_RX_REC_CTRL_MSG_PARITY_ERROR                              0x00000020
   #define MXF_MIL1553_RX_REC_CTRL_MSG_CHECKSUM_ERROR                            0x00000040
   #define MXF_MIL1553_RX_REC_CTRL_MSG_EXTRA_BIT_ERROR                           0x00000080
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS1_TOOFAST_ERROR                     0x00000100
   #define MXF_MIL1553_RX_REC_CTRL_MSG_RT_RT                                     0x00000200
   #define MXF_MIL1553_RX_REC_CTRL_MSG_UNEXPECTED_ERROR                          0x00001000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS2_TOOFAST_ERROR                     0x00002000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS_BADSYNC_ERROR                      0x00004000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS1_RCV                               0x00010000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS2_RCV                               0x00020000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_DATA_RCV                                  0x00040000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_MODECODE                                  0x00080000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_BCST                                      0x00100000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_DATA_LENGTH_ERROR                         0x00200000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_COMMAND                                   0x00400000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS1_ADDRESS_ERROR                     0x00800000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS2_ADDRESS_ERROR                     0x01000000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_STATUS2_DATA_ERROR                        0x02000000
   #define MXF_MIL1553_RX_REC_CTRL_MSG_NO_RESPONSE                               0x04000000

   #define MXF_MIL1553_RX_REC_CTRL_STRING_BUS_B                                  0x00000001
   #define MXF_MIL1553_RX_REC_CTRL_STRING_OVERLAP                                0x00000008
   #define MXF_MIL1553_RX_REC_CTRL_STRING_MANCHESTER_ERROR                       0x00000010
   #define MXF_MIL1553_RX_REC_CTRL_STRING_PARITY_ERROR                           0x00000020
   #define MXF_MIL1553_RX_REC_CTRL_STRING_CHECKSUM_ERROR                         0x00000040
   #define MXF_MIL1553_RX_REC_CTRL_STRING_EXTRA_BIT_ERROR                        0x00000080
   #define MXF_MIL1553_RX_REC_CTRL_STRING_STATUS_TOOFAST_ERROR                   0x00000100
   #define MXF_MIL1553_RX_REC_CTRL_STRING_RT_RT                                  0x00000200
   #define MXF_MIL1553_RX_REC_CTRL_STRING_UNEXPECTED_ERROR                       0x00001000
   #define MXF_MIL1553_RX_REC_CTRL_STRING_STATUS_BADSYNC_ERROR                   0x00004000
   #define MXF_MIL1553_RX_REC_CTRL_STRING_COMMAND                                0x00400000

   #define MXF_MIL1553_RX_REC_CTRL_WORD_BUS_B                                    0x00000001
   #define MXF_MIL1553_RX_REC_CTRL_WORD_MSGTYPE                                  0x00000006
      #define MXF_MIL1553_RX_REC_CTRL_WORD_MSGTYPE_UNEXPECTED                       0x00000000
      #define MXF_MIL1553_RX_REC_CTRL_WORD_MSGTYPE_WITH_BADSYNC                     0x00000002
      #define MXF_MIL1553_RX_REC_CTRL_WORD_MSGTYPE_CMD                              0x00000004
      #define MXF_MIL1553_RX_REC_CTRL_WORD_MSGTYPE_STS                              0x00000006
   #define MXF_MIL1553_RX_REC_CTRL_WORD_OVERLAP                                  0x00000008
   #define MXF_MIL1553_RX_REC_CTRL_WORD_MANCHESTER_ERROR                         0x00000010
   #define MXF_MIL1553_RX_REC_CTRL_WORD_PARITY_ERROR                             0x00000020
   #define MXF_MIL1553_RX_REC_CTRL_WORD_CHECKSUM_ERROR                           0x00000040
   #define MXF_MIL1553_RX_REC_CTRL_WORD_EXTRA_BIT_ERROR                          0x00000080
   #define MXF_MIL1553_RX_REC_CTRL_WORD_EOS                                      0x00000200
   #define MXF_MIL1553_RX_REC_CTRL_WORD_GAP                                      0x0007FC00

   #define MXF_MIL1553_TXAPERIODIC_REC_CTRL_RT_RT                                0x00000001
   #define MXF_MIL1553_TXAPERIODIC_REC_CTRL_BUS_B                                0x00000002
   #define MXF_MIL1553_TXAPERIODIC_REC_CTRL_CHECKSUM_ENABLE                      0x00000008
   #define MXF_MIL1553_TXAPERIODIC_REC_CTRL_ERROR_INJ                            0x00000010
   #define MXF_MIL1553_TXAPERIODIC_REC_CTRL_GAP                                  0x00000040

   #define MXF_MIL1553_TXPERIODIC_REC_CTRL_ERROR_INJ                             0x00000001
   #define MXF_MIL1553_TXPERIODIC_REC_CTRL_UPDATE_COMMAND                        0x00000010

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_PROPERTIES_OPT_MINOR_MODULO_NOW       0x1
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_PROPERTIES_OPT_EXTCLOCK_MODE_RISING   0x4
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_PROPERTIES_OPT_EXTCLOCK_MODE_FALLING  0x2

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES_OPT_BRANCH_DEFAULT   0x00
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES_OPT_BRANCH_GOTO      0x01
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES_OPT_BRANCH_END       0x03
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES_OPT_DURATION_USEC    0x10

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_RT_RT                         0x0001
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_BUS_B                         0x0002
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_CHECKSUM_ENABLE               0x0004
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_GAP                           0x0010
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_NOOP_AND_WAITONCOND           0x0020
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_NEXTFRAME_NOW                 0x0040
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_DELAY                         0x0080
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_OPT_BUS_GAP                       0x0100

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_NORESPONSE_ENABLE           0x0002
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_ERROR_ENABLE                0x0004
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_SWITCH_ENABLE               0x0008

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_STATUSMASK_AND              0x0010
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_STATUSMASK_NOTEQUAL         0x0020
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_STATUSMASK_EQUAL            0x0030

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_ACT_BUS                     0x0040
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_ALT_BUS                     0x0080
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_RETRY_ACT_ALT_BUS                 0x00C0

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_HALT_STATUSMASK_AND               0x0100
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_HALT_STATUSMASK_NOTEQUAL          0x0200
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_HALT_STATUSMASK_EQUAL             0x0300

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_HALT_ERROR_ENABLE                 0x0400

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_ADDRESS                MXF_MIL1553_STATUS_ADDRESS
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_MSGERR                 MXF_MIL1553_STATUS_MSGERR
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_INST                   MXF_MIL1553_STATUS_INST
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_SRQ                    MXF_MIL1553_STATUS_SRQ
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_RESERVED_BITS          MXF_MIL1553_STATUS_RES_BITS
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_BCST                   MXF_MIL1553_STATUS_BCST
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_BUSY                   MXF_MIL1553_STATUS_BUSY
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_SSF                    MXF_MIL1553_STATUS_SSF
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_DBCA                   MXF_MIL1553_STATUS_DBCA
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_STATUSMASK_TERMINAL_FLAG          MXF_MIL1553_STATUS_TF

   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_CONDBRANCH_OPT_NONE               0
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_CONDBRANCH_OPT_AND                1
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_CONDBRANCH_OPT_NOTEQUAL           2
   #define MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG_CONDBRANCH_OPT_EQUAL              3

   #define MXF_MIL1553_MSGINFO_TYPE_BCRT                                         0
   #define MXF_MIL1553_MSGINFO_TYPE_RTBC                                         1
   #define MXF_MIL1553_MSGINFO_TYPE_RTRT                                         2
   #define MXF_MIL1553_MSGINFO_TYPE_MODECODE                                     3
   #define MXF_MIL1553_MSGINFO_TYPE_MODECODE_TXDATA                              4
   #define MXF_MIL1553_MSGINFO_TYPE_MODECODE_RXDATA                              5
   #define MXF_MIL1553_MSGINFO_TYPE_BCRT_BCST                                    6
   #define MXF_MIL1553_MSGINFO_TYPE_RTRT_BCST                                    7
   #define MXF_MIL1553_MSGINFO_TYPE_MODECODE_RXDATA_BCST                         8
   #define MXF_MIL1553_MSGINFO_TYPE_MODECODE_BCST                                9
   #define MXF_MIL1553_MSGINFO_TYPE_UNEXPECTED                                   10

   #define MXF_MIL1553_DISCRETE_OUTPUT_TRIG_ON_BUSA_ERROR                        0ULL
   #define MXF_MIL1553_DISCRETE_OUTPUT_TRIG_ON_BUSB_ERROR                        1ULL
   #define MXF_MIL1553_DISCRETE_OUTPUT_TRIG_ON_BUSA_PROTOCOL_ERROR               2ULL
   #define MXF_MIL1553_DISCRETE_OUTPUT_TRIG_ON_BUSB_PROTOCOL_ERROR               3ULL

   #define MXF_MIL1553_STAT_TYPE_TRANSACTION_GLOBAL                              0ULL
   #define MXF_MIL1553_STAT_TYPE_TRANSACTION_GLOBAL_ALL_ADDRESS                  1ULL
   #define MXF_MIL1553_STAT_TYPE_TRANSACTION_GLOBAL_ALL_SUBADDRESS               2ULL
   #define MXF_MIL1553_STAT_TYPE_TRANSACTION_DETAILS_SUBADDRESS                  3ULL
   #define MXF_MIL1553_STAT_TYPE_ERROR_GLOBAL                                    4ULL
   #define MXF_MIL1553_STAT_TYPE_ERROR_GLOBAL_ALL_ADDRESS                        5ULL
   #define MXF_MIL1553_STAT_TYPE_ERROR_GLOBAL_ALL_SUBADDRESS                     6ULL
   #define MXF_MIL1553_STAT_TYPE_ERROR_DETAILS_SUBADDRESS                        7ULL

   #define MXF_MIL1553_STAT_BUS_A                                                0
   #define MXF_MIL1553_STAT_BUS_B                                                1

   #define MXF_MIL1553_STAT_MSG_TYPE_BCRT                                        0
   #define MXF_MIL1553_STAT_MSG_TYPE_RTBC                                        1
   #define MXF_MIL1553_STAT_MSG_TYPE_RTRT                                        2

   #define MXF_MIL1553_ERRORID_NONE                                              0
   #define MXF_MIL1553_ERRORID_ADDRESS                                           1
   #define MXF_MIL1553_ERRORID_BITCNT                                            2
   #define MXF_MIL1553_ERRORID_INVSYNC                                           4
   #define MXF_MIL1553_ERRORID_ALTBUS                                            5
   #define MXF_MIL1553_ERRORID_TWOBUS                                            6
   #define MXF_MIL1553_ERRORID_PAR                                               7
   #define MXF_MIL1553_ERRORID_WORDCNT                                           8
   #define MXF_MIL1553_ERRORID_MANCHBIPHASEDATA                                  9
   #define MXF_MIL1553_ERRORID_MANCHBIPHASEPARITY                                10
   #define MXF_MIL1553_ERRORID_MANCHSYNCLEVEL                                    11
   #define MXF_MIL1553_ERRORID_STATUS_OV                                         12
   #define MXF_MIL1553_ERRORID_INVBIT                                            13
   #define MXF_MIL1553_ERRORID_OVERRIDE                                          15
   #define MXF_MIL1553_ERRORID_DONOTRESPOND                                      16
   #define MXF_MIL1553_ERRORID_RESPONDONERROR                                    17
   #define MXF_MIL1553_ERRORID_MANCHZEROCROSSING                                 18
   #define MXF_MIL1553_ERRORID_WORDGAP                                           19
   #define MXF_MIL1553_ERRORID_SUPERSEDING                                       20
   #define MXF_MIL1553_ERRORID_NOOP                                              21

#endif

#if !defined(MXF_MIL1553_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_MIL1553_H

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   dataSize;
      uint32   repeatCount;
      uint32   reserved;

      union
      {
         struct
         {
            uint32   errorIndex;
            uint32   delay;
         }
         txAperiodic;

         struct
         {
            uint32   errorIndex;
            uint32   reserved;
         }
         txPeriodicUpdateMsg;

         struct
         {
            uint32   respTime[2];
         }
         rxAcq;
      }
      service;

      uint16   data[36];
   }
   MXF_MIL1553_DATAREC;

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   rate;
      uint32   errorCount;
      uint32   dataSize;

      uint32   respTime[2];

      uint16   data[36];
   }
   MXF_MIL1553_SAMPREC;

   typedef struct
   {
      uint32 options;
      uint32 firstMinorIndex;
      uint64 startTime;
      uint64 stopTime;
      uint32 reserved[2];
   }
   MXF_MIL1553_TXPERIODIC_MJRFRAME_PROPERTIES;

   typedef struct
   {
      HMXF_BUFFER buffer;

      uint32   options;
      uint32   delay;

      uint16   command;
      uint16   command2;

      uint16   retryHaltOptions;
      uint16   statusMask;
      uint16   condBranch;
      uint16   condMask;
      uint16   condData;
      uint16   branchMinorIndex;
      uint16   branchMsgIndex;
      uint16   modulo;
      uint16   reserved[2];
   }
   MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG;

   typedef struct
   {
      uint32   duration;
      uint32   repeatCount;
      uint32   modulo;
      uint32   options;
      uint32   branchIndex;
   }
   MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES;

   typedef struct
   {
      uint16   errors[34];
      uint16   reserved[6];
   }
   MXF_MIL1553_ERROR_INJ;

   typedef struct
   {
      uint16   msgType;
      uint16   dataWordCount;
      uint16   statusIndex[2];
      uint16   dataIndex;
      uint16   reserved;
   }
   MXF_MIL1553_MSGINFO;

   typedef struct
   {
      uint32 manchester;
      uint32 parity;
      uint32 longWord;
      uint32 noRespTimeout;
      uint32 respTooFast;
      uint32 reserved[5];
   }
   MXF_MIL1553_STAT_ERROR_BYMSG;

   typedef struct
   {
      uint32 unexpectedTraffic;
      uint32 badSync;
      uint32 reserved[2];
   }
   MXF_MIL1553_STAT_ERROR_BYBUS;

   typedef struct
   {
      uint32 totalError;
      uint32 reserved;

      struct
      {
         MXF_MIL1553_STAT_ERROR_BYBUS error;
      }
      busTotal[2];

      struct
      {
         struct
         {
            MXF_MIL1553_STAT_ERROR_BYMSG error;
         }
         msg[3];
      }
      busByMsg[2];
   }   
   MXF_MIL1553_STAT_ERROR_GLOBAL;

   typedef struct
   {
      struct
      {
         uint32   error;
      }
      address[32];
   }
   MXF_MIL1553_STAT_ERROR_GLOBAL_ALL_ADDRESS;

   typedef struct
   {
      uint32 address;
      uint32 reserved;

      struct
      {
         uint32   error;
      }
      subAddress[32];
   }
   MXF_MIL1553_STAT_ERROR_GLOBAL_ALL_SUBADDRESS;

   typedef struct
   {
      uint32 address;
      uint32 subAddress;

      struct
      {
         struct
         {
            MXF_MIL1553_STAT_ERROR_BYMSG error;
         }
         msg[3];
      }
      bus[2];
   }
   MXF_MIL1553_STAT_ERROR_DETAILS_SUBADDRESS;

   typedef struct
   {
      uint32 totalCount;
      uint32 reserved;

      struct
      {
         uint32 count;
      }
      busTotal[2];

      struct
      {
         struct
         {
            uint32 count;
         }
         msg[3];
      }
      busByMsg[2];
   }
   MXF_MIL1553_STAT_TRANSACTION_GLOBAL;

   typedef struct
   {
      struct
      {
         uint32 count;
      }
      address[32];
   }
   MXF_MIL1553_STAT_TRANSACTION_GLOBAL_ALL_ADDRESS;

   typedef struct
   {
      uint32 address;
      uint32 reserved;

      struct
      {
         uint32 count;
      }
      subAddress[32];
   }
   MXF_MIL1553_STAT_TRANSACTION_GLOBAL_ALL_SUBADDRESS;

   typedef struct
   {
      uint32 address;
      uint32 subAddress;

      struct
      {
         struct
         {
            uint32 count;
         }
         msg[3];
      }
      bus[2];
   }
   MXF_MIL1553_STAT_TRANSACTION_DETAILS_SUBADDRESS;

   #ifdef __cplusplus
   extern "C" {
   #endif
          
         uint32 MXF_EXPORTED mxfMIL1553TxAperiodicWrite(HMXF_BUFFER buffer, uint64 options, uint64 startTime, uint64 count, MXF_MIL1553_DATAREC* rec);
          
         uint32 MXF_EXPORTED mxfMIL1553TxPeriodicMajorFrameStart(HMXF_CHANNEL channel, uint64 majorIndex, uint64 duration, MXF_MIL1553_TXPERIODIC_MJRFRAME_PROPERTIES* properties);
         uint32 MXF_EXPORTED mxfMIL1553TxPeriodicMajorFrameSet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 count, MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG* msg, MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES* properties);
         uint32 MXF_EXPORTED mxfMIL1553TxPeriodicMajorFrameGet(HMXF_CHANNEL channel, uint64 majorIndex, uint64 minorIndex, uint64 maxCount, uint64* count, MXF_MIL1553_TXPERIODIC_MJRFRAME_MSG* msg, MXF_MIL1553_TXPERIODIC_MJRFRAME_MINOR_PROPERTIES* properties);
          
         uint32 MXF_EXPORTED mxfMIL1553TxPeriodicUpdateMsgWrite(HMXF_BUFFER buffer, uint64 count, MXF_MIL1553_DATAREC* rec);
         
         uint32 MXF_EXPORTED mxfMIL1553RxAcqMsgSelectGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, MXF_MSGID_MIL1553* msg);
         uint32 MXF_EXPORTED mxfMIL1553RxAcqMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 maxcount, MXF_MSGID_MIL1553* msg);
         uint32 MXF_EXPORTED mxfMIL1553RxAcqRead(HMXF_BUFFER buffer, uint64 maxRecCount, uint64 maxBytesCount, uint64* status, uint64* recCount, uint64* byteCount, MXF_MIL1553_DATAREC* rec);
          
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingExtEnableSet(HMXF_BUFFER buffer, uint64 state, uint64 count, uint64* address);
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingExtEnableAllGet(HMXF_BUFFER buffer, uint64 maxCount, uint64* count, uint64* address);
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingMsgSelectSet(HMXF_BUFFER buffer, uint64 select, uint64 maxcount, MXF_MSGID_MIL1553* msg);
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingMsgSelectGet(HMXF_BUFFER buffer, uint64 maxcount, uint64* count, MXF_MSGID_MIL1553* msg);
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingRead(HMXF_BUFFER buffer, uint64 flags, uint64 maxRecCount, uint64 maxBytesCount, uint64* recCount, uint64* byteCount, MXF_MIL1553_SAMPREC* rec);
         uint32 MXF_EXPORTED mxfMIL1553RxSamplingSingleRead(HMXF_BUFFER buffer, uint64 flags, uint64 type, uint64 address, uint64 subAddress, MXF_MIL1553_SAMPREC* rec);
         
         uint32 MXF_EXPORTED mxfMIL1553AsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_MIL1553* msg);
         uint32 MXF_EXPORTED mxfMIL1553AsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_MIL1553* msg);
          
         uint32 MXF_EXPORTED mxfMIL1553ErrorInjectionCompose(uint64 id, uint64 param, uint16* error);
         uint32 MXF_EXPORTED mxfMIL1553ErrorInjectionSet(HMXF_CHANNEL channel, uint64 errorIndex, MXF_MIL1553_ERROR_INJ* error);
         uint32 MXF_EXPORTED mxfMIL1553ErrorInjectionGet(HMXF_CHANNEL channel, uint64 errorIndex, MXF_MIL1553_ERROR_INJ* error);
         uint32 MXF_EXPORTED mxfMIL1553ErrorInjectionCountGet(HMXF_CHANNEL channel, uint64* errorCount);
          
         uint32 MXF_EXPORTED mxfMIL1553DataRecordDecompose(HMXF_CHANNEL channel, uint64 count, MXF_MIL1553_DATAREC* data, MXF_MIL1553_MSGINFO* msginfo);
         uint32 MXF_EXPORTED mxfMIL1553SamplingRecordDecompose(HMXF_CHANNEL channel, uint64 count, MXF_MIL1553_SAMPREC* data, MXF_MIL1553_MSGINFO* msginfo);
          
         uint32 MXF_EXPORTED mxfMIL1553StatisticErrorGlobalGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_ERROR_GLOBAL* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticErrorGlobalByAddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_ERROR_GLOBAL_ALL_ADDRESS* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticErrorGlobalBySubaddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_ERROR_GLOBAL_ALL_SUBADDRESS* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticErrorDetailsBySubaddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_ERROR_DETAILS_SUBADDRESS* stats);
          
         uint32 MXF_EXPORTED mxfMIL1553StatisticTransactionGlobalGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_TRANSACTION_GLOBAL* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticTransactionGlobalByAddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_TRANSACTION_GLOBAL_ALL_ADDRESS* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticTransactionGlobalBySubaddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_TRANSACTION_GLOBAL_ALL_SUBADDRESS* stats);
         uint32 MXF_EXPORTED mxfMIL1553StatisticTransactionDetailsBySubaddressGet(HMXF_CHANNEL channel, MXF_MIL1553_STAT_TRANSACTION_DETAILS_SUBADDRESS* stats);
          
         uint32 MXF_EXPORTED mxfMIL1553NextDataRecordPtrGet(MXF_MIL1553_DATAREC* currentRec, MXF_MIL1553_DATAREC** nextRec);
         uint32 MXF_EXPORTED mxfMIL1553NextSamplingRecordPtrGet(MXF_MIL1553_SAMPREC* currentRec, MXF_MIL1553_SAMPREC** nextRec);
          
         uint32 MXF_EXPORTED mxfMIL1553CommandCompose(uint64 address, uint64 subAddress, uint64 dir, uint64 wordCount, uint16* command);
         uint32 MXF_EXPORTED mxfMIL1553CommandDecompose(uint16 command, uint64* address, uint64* subAddress, uint64* dir, uint64* wordCount);
          
         uint32 MXF_EXPORTED mxfMIL1553ConditionalBranchCompose(uint64 option, uint64 wordIndex, uint16* condition);
         uint32 MXF_EXPORTED mxfMIL1553ConditionalBranchOnDiscreteCompose(uint64 option, uint16* condition);

         uint32 MXF_EXPORTED mxfMIL1553MsgChecksumEnableSet(HMXF_CHANNEL channel, uint64 type, uint64 address, uint64 subAddress, uint64 value);
         uint32 MXF_EXPORTED mxfMIL1553MsgChecksumEnableGet(HMXF_CHANNEL channel, uint64 type, uint64 address, uint64 subAddress, uint64* value);

         uint32 MXF_EXPORTED mxfMIL1553RtSubsystemEnableSet(HMXF_CHANNEL channel, uint64 type, uint64 subAddress, uint64 bus, HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfMIL1553RtSubsystemEnableGet(HMXF_CHANNEL channel, uint64 type, uint64 subAddress, uint64* bus, HMXF_BUFFER* buffer);

         uint32 MXF_EXPORTED mxfMIL1553RtEnableSet(HMXF_CHANNEL channel, uint64 enable);
         uint32 MXF_EXPORTED mxfMIL1553RtEnableGet(HMXF_CHANNEL channel, uint64* enable);

         uint32 MXF_EXPORTED mxfMIL1553EmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, MXF_MSGID_MIL1553* msgid);
         uint32 MXF_EXPORTED mxfMIL1553EmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, MXF_MSGID_MIL1553* msgid);
          
         uint32 MXF_EXPORTED mxfMIL1553EmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount, uint64 maxBytesCount,
                                                                    uint64* recCount, uint64* bytesCount, MXF_MIL1553_DATAREC* rec);
         uint32 MXF_EXPORTED mxfMIL1553EmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 fileIndex, uint64 maxRecCount,  MXF_MIL1553_DATAREC* rec, uint64* recCount);

   #ifdef __cplusplus
   }
   #endif

#endif
