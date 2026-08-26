/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_BASE_H_CONST
#define MXF_BASE_H_CONST

   typedef HMXF_HANDLE                                                           HMXF_SERVER;
   typedef HMXF_HANDLE                                                           HMXF_DEVICE;
   typedef HMXF_HANDLE                                                           HMXF_MODULE;
   typedef HMXF_HANDLE                                                           HMXF_CHANNEL;
   typedef HMXF_HANDLE                                                           HMXF_ASYNCEVENT;
   typedef HMXF_HANDLE                                                           HMXF_BUFFER;
   typedef HMXF_HANDLE                                                           HMXF_NVSTORAGE;
   typedef HMXF_HANDLE                                                           HMXF_VL;
   typedef HMXF_HANDLE                                                           HMXF_PORT;

   #define MXF_DEVICE_ALL                                                        0ULL
   #define MXF_DEVICE_FLEX1553_PCIE                                              19ULL
   #define MXF_DEVICE_FLEXMULTI_1553                                             20ULL
   #define MXF_DEVICE_FLEXMULTI_629                                              21ULL

   #define MXF_MODULE_ALL                                                        0ULL
   #define MXF_MODULE_MIL1553MRT_EH                                              36ULL
   #define MXF_MODULE_DIOFIFO_EH                                                 39ULL
   #define MXF_MODULE_A429_EH                                                    40ULL
   #define MXF_MODULE_ASYNC_EH                                                   41ULL
   #define MXF_MODULE_MULTI_EH                                                   42ULL
   #define MXF_MODULE_A629MRT_EH                                                 43ULL
   #define MXF_MODULE_A708_EH                                                    45ULL

   #define MXF_CLASS_ALL                                                         0ULL
   #define MXF_CLASS_A429                                                        2ULL
   #define MXF_CLASS_CSDB                                                        4ULL
   #define MXF_CLASS_DISCRETE                                                    7ULL
   #define MXF_CLASS_A629                                                        8ULL
   #define MXF_CLASS_MIL1553                                                     13ULL
   #define MXF_CLASS_A717                                                        14ULL
   #define MXF_CLASS_A708                                                        15ULL
   #define MXF_CLASS_HDLC                                                        17ULL
   #define MXF_CLASS_CLOCK                                                       18ULL
   #define MXF_CLASS_HANDSHAKE                                                   21ULL
   #define MXF_CLASS_EMBEDDED                                                    22ULL
   #define MXF_CLASS_ASYNC_ENHANCED                                              24ULL

   #define MXF_SCLASS_ALL                                                        0x00000000ULL
   #define MXF_SCLASS_RX_CHANNEL                                                 0x00000001ULL
   #define MXF_SCLASS_TX_CHANNEL                                                 0x00000002ULL
   #define MXF_SCLASS_RXSAMPLING_SRV                                             0x00000004ULL
   #define MXF_SCLASS_TXAPERIODIC_SRV                                            0x00000010ULL
   #define MXF_SCLASS_RXACQ_SRV                                                  0x00000020ULL
   #define MXF_SCLASS_TXPERIODIC_MJRFRAME_SRV                                    0x00000100ULL
   #define MXF_SCLASS_TXPERIODIC_UPDATEMSG_SRV                                   0x00000200ULL
   #define MXF_SCLASS_BM_CHANNEL                                                 0x00000400ULL
   #define MXF_SCLASS_BC_CHANNEL                                                 0x00000800ULL
   #define MXF_SCLASS_RT_CHANNEL                                                 0x00001000ULL
   #define MXF_SCLASS_TXPERIODIC_SCHEDULE_SRV                                    0x00002000ULL

   #define MXF_SCLASS_SAP_TX_CHANNEL                                             0x00004000ULL
   #define MXF_SCLASS_SAP_RXSAMPLING_SRV                                         0x00008000ULL
   #define MXF_SCLASS_SAP_RXACQ_SRV                                              0x00010000ULL
   #define MXF_SCLASS_COM_TX_CHANNEL                                             0x00020000ULL
   #define MXF_SCLASS_COM_RXACQ_SRV                                              0x00040000ULL
   #define MXF_SCLASS_COM_RXSAMPLING_SRV                                         0x00080000ULL

   #define MXF_CHANNEL_RX                                                        1ULL
   #define MXF_CHANNEL_TX                                                        2ULL
   #define MXF_CHANNEL_TXRX                                                      3ULL

   #define MXF_MSG_DESELECT                                                      0ULL
   #define MXF_MSG_SELECT_ADD                                                    1ULL
   #define MXF_MSG_SELECT_ONLY                                                   2ULL

   #define MXF_ASYNCEVENT_COND_RX_MSG                                            0ULL
   #define MXF_ASYNCEVENT_COND_RX_ERROR                                          1ULL
   #define MXF_ASYNCEVENT_COND_TX_ERROR                                          2ULL
   #define MXF_ASYNCEVENT_COND_TXAPERIODIC_BUFFER_THRESHOLD                      3ULL
   #define MXF_ASYNCEVENT_COND_RXACQ_BUFFER_THRESHOLD                            4ULL
   #define MXF_ASYNCEVENT_COND_TXPERIODIC_UPDATEMSG_BUFFER_THRESHOLD             5ULL
   #define MXF_ASYNCEVENT_COND_EMBEDDED_RX_BUFFER_THRESHOLD                      6ULL
   #define MXF_ASYNCEVENT_COND_EMBEDDED_TX_BUFFER_THRESHOLD                      7ULL
   #define MXF_ASYNCEVENT_COND_IRIGB_EVENTS                                      9ULL
      #define MXF_ASYNCEVENT_IRIGB_EVENT_LOCKED                                  0x1ULL
      #define MXF_ASYNCEVENT_IRIGB_EVENT_UNLOCKED                                0x2ULL
      #define MXF_ASYNCEVENT_IRIGB_EVENT_LEAP_SECOND_INS                         0x4ULL
      #define MXF_ASYNCEVENT_IRIGB_EVENT_LEAP_SECOND_DEL                         0x8ULL
   #define MXF_ASYNCEVENT_COND_COMM_RX_BUFFER_THRESHOLD                          10ULL
   #define MXF_ASYNCEVENT_COND_COMM_TX_BUFFER_THRESHOLD                          11ULL

   #define MXF_SYSTEM_OPTION_RESET_DEVICES                                       0x1ULL

   #define MXF_IRIGB_STATUS_LOCKED                                               0ULL
   #define MXF_IRIGB_STATUS_WAITING_SIGNAL                                       1ULL
   #define MXF_IRIGB_STATUS_NO_SIGNAL                                            2ULL
   #define MXF_IRIGB_STATUS_DISABLED                                             3ULL
   #define MXF_IRIGB_STATUS_LOCKING                                              4ULL

   #define MXF_TIMEBASE_DEVICE_USEC                                              1ULL
   #define MXF_TIMEBASE_COMPUTER_USEC                                            2ULL
   #define MXF_TIMEBASE_IRIGB_USEC                                               4ULL
   #define MXF_TIMEBASE_DEVICE_NSEC                                              5ULL
   #define MXF_TIMEBASE_COMPUTER_NSEC                                            6ULL
   #define MXF_TIMEBASE_IRIGB_NSEC                                               7ULL

   #define MXF_EMBEDDED_HANDLER_ID_RX                                            0ULL
   #define MXF_EMBEDDED_HANDLER_ID_TX_PERIODIC_UPDATE_MSG                        1ULL

   #define MXF_DEVICE_SENSOR_ID_FPGA_TEMP                                        0ULL
   #define MXF_DEVICE_SENSOR_ID_CPU_TEMP                                         1ULL
   #define MXF_DEVICE_SENSOR_ID_3_3V_VOLTAGE                                     2ULL
   #define MXF_DEVICE_SENSOR_ID_3_3V_CURRENT                                     3ULL
   #define MXF_DEVICE_SENSOR_ID_12V_VOLTAGE                                      4ULL
   #define MXF_DEVICE_SENSOR_ID_12V_CURRENT                                      5ULL
   #define MXF_DEVICE_SENSOR_ID_5V_VOLTAGE                                       6ULL
   #define MXF_DEVICE_SENSOR_ID_5V_CURRENT                                       7ULL
   #define MXF_DEVICE_SENSOR_ID_3_3V_SWITCHERS_VOLTAGE                           8ULL
   #define MXF_DEVICE_SENSOR_ID_3_3V_SWITCHERS_CURRENT                           9ULL
   #define MXF_MODULE_SENSOR_ID_MULTI_UST0_3_TEMP                                10ULL
   #define MXF_MODULE_SENSOR_ID_MULTI_UST4_7_TEMP                                11ULL

   #define MXF_DEVICE_FILE_MXFCORE                                               0ULL
   #define MXF_DEVICE_FILE_BOOT                                                  1ULL
   #define MXF_DEVICE_FIRMWARE_PKG_VERSION                                       2ULL

   #define MXF_DEVICE_FILETYPE_FILE                                              0ULL
   #define MXF_DEVICE_FILETYPE_APPLICATION                                       1ULL

   #define MXF_RECTYPE_DATAREC                                                   0ULL
   #define MXF_RECTYPE_SAMPREC                                                   1ULL

   #define MXF_DEVICE_FIRMWARE_BLOCK_KERNEL_LOADER                               0ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_KERNEL                                      1ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_KERNEL_CFG                                  2ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_MXF_FILESYSTEM                              3ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_FPGA                                        4ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_USER_CODE                                   5ULL
   #define MXF_DEVICE_FIRMWARE_BLOCK_ALL                                         6ULL

   #define MXF_DEVICE_FIRMWARE_STATE_ERASING                                     0ULL
   #define MXF_DEVICE_FIRMWARE_STATE_PROGRAMMING                                 1ULL
   #define MXF_DEVICE_FIRMWARE_STATE_VERIFYING                                   2ULL

   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_RAW_SECTOR                             0ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_A429                                   2ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_CSDB                                   4ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_DISCRETE                               7ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_A629                                   8ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_MIL1553                                13ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_A717                                   14ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_A708                                   15ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_HDLC                                   17ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_USERDEF                                22ULL
   #define MXF_EMBEDDED_NVSTORAGE_MSGTYPE_ASYNC_ENHANCED                         24ULL

   #define MXF_EMBEDDED_NVSTORAGE_TYPE_SANDISK_H3                                0ULL

   #define MXF_REGION_MAX                                                        8
   #define MXF_MODULE_REGION_MAX                                                 4
   #define MXF_MODULE_MAX                                                        32
   #define MXF_FLASH_REV_MAX                                                     16

   #define MXF_DEVICE_SERIES_FLEX                                                5ULL

   #define MXF_DEVICE_REGION_PCICTRL                                             0ULL
   #define MXF_DEVICE_REGION_DRAM                                                1ULL
   #define MXF_DEVICE_REGION_CTRL                                                2ULL
   #define MXF_DEVICE_REGION_MODULE                                              3ULL
   #define MXF_DEVICE_REGION_EPROM                                               4ULL
   #define MXF_DEVICE_REGION_MODULE_MEM                                          5ULL
   #define MXF_DEVICE_REGION_NANDFLASH                                           5ULL
   #define MXF_DEVICE_REGION_FPGA_UPM                                            6ULL

   #define MXF_MODULE_REGION_MEM                                                 0ULL
   #define MXF_MODULE_REGION_IO                                                  1ULL
   #define MXF_MODULE_REGION_INT                                                 2ULL
   #define MXF_MODULE_REGION_ID                                                  3ULL

   #define MXF_ACCESS_WIDTH_8BIT                                                 0ULL
   #define MXF_ACCESS_WIDTH_16BIT                                                1ULL
   #define MXF_ACCESS_WIDTH_32BIT                                                2ULL

   #define MXF_SELFTEST_LEVEL_QUICK                                              0ULL
   #define MXF_SELFTEST_LEVEL_EXHAUSTIVE                                         1ULL

   #define MXF_SELFTEST_IRIGB_SIGNAL_AM                                          0ULL
   #define MXF_SELFTEST_IRIGB_SIGNAL_AM_1PPS                                     1ULL
   #define MXF_SELFTEST_IRIGB_SIGNAL_DIGITAL                                     2ULL

   #define MXF_SELFTEST_PASS                                                     0ULL
   #define MXF_SELFTEST_FAIL                                                     1ULL

   #define MXF_DEVICE_INFO_DHCP_STATUS_ENABLED                                   0x1
   #define MXF_DEVICE_INFO_DHCP_STATUS_SUCCESS                                   0x2

   #define MXF_SERVER_ACL_USER_PRIVILEGE_ADMIN                                   0
   #define MXF_SERVER_ACL_USER_PRIVILEGE_ADVANCED                                1
   #define MXF_SERVER_ACL_USER_PRIVILEGE_USER                                    2

#endif

#if !defined(MXF_BASE_H) && !defined(DEF_CONSTANTS_ONLY)
#define MXF_BASE_H

   typedef uint32 (*MXF_ASYNCEVENT_HANDLER)(HMXF_HANDLE asyncEvent, void* pParam);

   typedef void (*MXF_ASYNCHRONOUS_CALLBACK)(HMXF_BUFFER bufferHandle, uint32 result, void* context, uint64* output);

   typedef void (*MXF_DEVICE_FIRMWARE_STATUS_CALLBACK)(uint64 block, uint64 state, uint64 percent);

   typedef struct
   {
      uint64   type;
      uint64   address;
      uint64   subAddress;
      uint64   reserved;
   }
   MXF_MSGID_MIL1553;
   
   typedef struct
   {
      uint64   label;
      uint64   sdi;
      uint64   reserved[2];
   }
   MXF_MSGID_A429;

   typedef struct
   {
      uint64   label;
      uint64   cid;
      uint64   reserved[2];
   }
   MXF_MSGID_A629;

#ifdef AFDX_DETECT
   typedef struct
   {
      uint64   port;
      uint64   vl;
      uint64   reserved[2];
   }
   MXF_MSGID_A664;
#endif

   typedef struct
   {
      uint64   label;
      uint64   si;
      uint64   reserved[2];
   }
   MXF_MSGID_CSDB;

   typedef struct
   {
      uint64   label;
      uint64   reserved[3];
   }
   MXF_MSGID_A708;

   typedef struct
   {
      uint64   timeTag;
      uint32   control;
      uint32   dataSize;
      uint32   repeatCount;
      uint32   reserved;
      uint32   data[256];
   }
   MXF_EMBEDDED_DATAREC;

   typedef struct
   {
      uint32   command,
               queueAdd,
               queueRemove,
               outOfBuffer,
               rxFifoOverflow,
               txFifoOverflow,
               bridgeOverflow,
               rxWordString,
               sharedQueueAdd,
               sharedQueueRemove,
               schedulerUnderrun,
               txLate,
               txMsgOverflow,
               bufferTrashed,
               moduleError,
               moduleException,
               a629Sim,
               txFatal,
               rxWordLength,
               moduleRxUnderflow,
               moduleTxUnderflow,
               overload,
               nvstorageReadWrite,
               overheat,
               rxGapLength,
               reserved[33];
   }
   MXF_DEVICE_STAT_ERROR_DETAILS;

   typedef struct
   {
      struct
      {
         uint32   usage;
         uint32   reserved;
      }
      cpu;

      struct
      {
         uint32   count;
         uint32   state;
      }
      led;

      struct
      {
         uint32   total;
         uint32   free;
      }
      periodicEvent;

      struct
      {
         uint32   total;
         uint32   free;
         uint32   segment;
         uint32   reserved;
      }
      bufferMemory;

      uint32   reserved[32];
   }
   MXF_DEVICE_STAT_RESOURCES;

   typedef struct
   {
      uint64   userID;
      char     userName[128];
      char     url[128];
   }
   MXF_NETWORK_SERVER_USER_INFO;

   typedef struct
   {
      uint64 condID;
      uint64 reserved;

      union
      {
         struct
         {
            HMXF_CHANNEL   channel;
         }
         rxMsg;

         struct
         {
            HMXF_CHANNEL   channel;
         }
         rxErr;

         struct
         {
            HMXF_CHANNEL   channel;
         }
         txErr;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         txAperiodicBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         rxAcqBufferThreshold;

         struct
         {
            HMXF_CHANNEL   channel;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         txPeriodicUpdateMsgBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         embeddedRxBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         embeddedTxBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         commBufferThreshold;

         struct
         {
            HMXF_DEVICE    device;
            uint64         status;
            uint64         reserved;
         }
         irigbEvents;
      }
      condition;
   }
   MXF_ASYNCEVENT_CONDITION;

   typedef struct
   {
      uint64 condID;
      uint64 reserved;

      union
      {
         struct
         {
            HMXF_CHANNEL   channel;
            union
            {
               MXF_MSGID_MIL1553 mil1553;
               MXF_MSGID_A429 a429;
               MXF_MSGID_CSDB csdb;
               MXF_MSGID_A629 a629;
#ifdef AFDX_DETECT
            MXF_MSGID_A664 a664;
#endif
               MXF_MSGID_A708 a708;
            }
            msg;
         }
         rxMsg;

         struct
         {
            HMXF_CHANNEL   channel;
            uint64         status;
            uint64         reserved;
            union
            {
               MXF_MSGID_MIL1553 mil1553;
               MXF_MSGID_A429 a429;
               MXF_MSGID_CSDB csdb;
               MXF_MSGID_A629 a629;
#ifdef AFDX_DETECT
            MXF_MSGID_A664 a664;
#endif
               MXF_MSGID_A708 a708;
            }
            msg;
         }
         rxErr;

         struct
         {
            HMXF_CHANNEL   channel;
            uint64         status;
            uint64         reserved;
         }
         txErr;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         txAperiodicBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         rxAcqBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         txPeriodicUpdateMsgBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         embeddedRxBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         embeddedTxBufferThreshold;

         struct
         {
            HMXF_BUFFER    buffer;
            uint64         almostEmpty;
            uint64         almostFull;
         }
         commBufferThreshold;

         struct
         {
            HMXF_DEVICE    device;
            uint64         timeTag;
            uint64         status;
            uint64         reserved;
         }
         irigbEvents;
      }
      condition;
   }
   MXF_ASYNCEVENT_PENDING_INFO;

   typedef struct 
   {
      uint64   deviceTime;
      uint64   irigbTimeBcd;
      uint64   irigbTime;
      uint64   reserved;
   }
   MXF_TIMER_IRIGB;

   typedef struct
   {
      uint64   sensorId;
      uint64   status;
      uint64   reserved;
      double   value;
   }
   MXF_SENSOR_VALUE;

   typedef struct
   {
      char     name[64];
      char     unit[16];
      double   valueMin;
      double   valueMax;
      uint64   reserved;
   }
   MXF_SENSOR_INFO;

   typedef struct
   {
      uint64   type;
      uint64   sectorCount;
      uint64   sectorSize;
      uint64   reserved;
   }
   MXF_NVSTORAGE_INFO;

   typedef struct
   {
      char     name[64];
      char     rev[64];
   }
   MXF_REV;

   typedef struct
   {
      char     productModel[64];
      char     partNumber[64];
      char     modificationRev[64];
      char     serialNumber[64];
      char     pcbVersion[64];
      char     ipAddress[64];
      char     ipNetMask[64];
      char     macAddress[64];
      char     reserved1[4][64];
      uint64   revisionCount;
      uint64   reserved2[7];
      MXF_REV  revisions[MXF_FLASH_REV_MAX];
   }
   MXF_FLASH_INFO;

   typedef struct
   {
      char     filename[64];
      char     description[64];
      char     version[64];
      char     buildDate[64];
      uint64   reserved[8];
   }
   MXF_SOFT_INFO;

   typedef struct
   {
      uint64   len;
      uint64   reserved;
      uint64   address;
   }
   MXF_DEVICE_REGION;

   typedef struct
   {
      uint64                     type;
      int64                      position;
      char                       name[64];
      char                       options[64];
      char                       rev[64];
      uint64                     rxCount;
      uint64                     txCount;
      uint64                     discreteCount;

      MXF_DEVICE_REGION          regions[MXF_MODULE_REGION_MAX];
   }
   MXF_DEVICE_MODULE_INFO;

   typedef struct
   {
      char                       name[64];

      uint64                     deviceIndex;
      uint64                     deviceType;
      uint64                     deviceSeries;
      uint64                     deviceId;
      char                       deviceRev[64];
      uint64                     busNumber;
      uint64                     deviceNumber;
      uint64                     bootDone;
      uint64                     master;
      uint64                     extRef;
      uint64                     sramSize;
      uint64                     sdramSize;
      uint64                     moduleCount;
      uint64                     revisionCount;
      uint64                     dhcpStatus;
      uint64                     reserved[14];

      MXF_REV                    revisions[MXF_FLASH_REV_MAX];

      MXF_DEVICE_REGION          regions[MXF_REGION_MAX];

      MXF_DEVICE_MODULE_INFO     modules[MXF_MODULE_MAX];

      char                       ipAddress[32];
      char                       ipNetMask[32];

      uint64                     reserved4[32];
   }
   MXF_DEVICE_INFO;

   typedef struct
   {
      uint64 telnet;
      uint64 reserved[7];
   }
   MXF_ACL_PERMISSIONS;

   typedef struct
   {
      char                 username[128];
      char                 password[128];
      uint64               privilege;
      MXF_ACL_PERMISSIONS  permissions;
   }
   MXF_ACL_USER;

   #ifdef __cplusplus
   extern "C" {
   #endif

      #ifndef __MXFIRMWARE

         uint32 MXF_EXPORTED mxfSystemInit(HMXF_SERVER server);
         uint32 MXF_EXPORTED mxfSystemTerminate(HMXF_SERVER server);

         uint32 MXF_EXPORTED mxfSystemApplicationCountGet(HMXF_SERVER server, uint64* count);
         uint32 MXF_EXPORTED mxfSystemResourcesInit(HMXF_SERVER server, uint64 options);
         uint32 MXF_EXPORTED mxfSystemResourcesRelease(HMXF_SERVER server, uint64 options);

         uint32 EXPORTED     mxfSystemErrorStringGet(HMXF_SERVER server, uint32 error, uint32 msgMaxSize, char* msg);
         uint32 MXF_EXPORTED mxfSystemWarningCountGet(HMXF_SERVER server, uint64* count);
         uint32 MXF_EXPORTED mxfSystemWarningGet(HMXF_SERVER server, uint64 maxCount, uint64* count, uint32* warnings);

         uint32 MXF_EXPORTED mxfSystemVersionGet(HMXF_SERVER server, uint64* major, uint64* minor, uint64* subminor);
         uint32 MXF_EXPORTED mxfClientVersion(uint64* major, uint64* minor, uint64* subminor);

         uint32 MXF_EXPORTED mxfSystemDeviceCountGet(HMXF_SERVER server, uint64 type, uint64* count);
         uint32 MXF_EXPORTED mxfSystemDeviceGet(HMXF_SERVER server, uint64 index, HMXF_DEVICE* device);
         uint32 MXF_EXPORTED mxfSystemDeviceAllGet(HMXF_SERVER server, uint64 type, uint64 maxCount, uint64* count, HMXF_DEVICE* devices);

         uint32 MXF_EXPORTED mxfModuleCountGet(HMXF_SERVER server, uint64 moduleType, uint64* count);
         uint32 MXF_EXPORTED mxfModuleGet(HMXF_SERVER server, uint64 moduleType, uint64 moduleIndex, HMXF_MODULE* module);
         uint32 MXF_EXPORTED mxfModuleAllGet(HMXF_SERVER server, uint64 moduleType, uint64 maxModule, uint64* count, HMXF_MODULE* modules);

         uint32 MXF_EXPORTED mxfChannelCountGet(HMXF_SERVER server, uint64 channelClass, uint64 subClass, uint64 moduleType, uint64* count);
         uint32 MXF_EXPORTED mxfChannelGet(HMXF_SERVER server, uint64 channelClass, uint64 subClass, uint64 moduleType, uint64 channelIndex, HMXF_CHANNEL* channel);
         uint32 MXF_EXPORTED mxfChannelAllGet(HMXF_SERVER server, uint64 channelClass, uint64 subClass, uint64 moduleType, uint64 maxChannel, uint64* count, HMXF_CHANNEL* channels);

         uint32 MXF_EXPORTED mxfSystemTimeBaseGet(HMXF_SERVER server, uint64* timebase);
         uint32 MXF_EXPORTED mxfSystemTimeBaseSet(HMXF_SERVER server, uint64 timebase);

         uint32 MXF_EXPORTED mxfBonjourIdGet(HMXF_SERVER server, uint64 size, char* name);
         uint32 MXF_EXPORTED mxfSystemNameSet(HMXF_SERVER server, const char* name);
         uint32 MXF_EXPORTED mxfSystemNameGet(HMXF_SERVER server, uint64 size, char* name);

         uint32 MXF_EXPORTED mxfFlexMultiReset(HMXF_SERVER server);

         uint32 MXF_EXPORTED mxfSleep(uint64 delay);

         uint32 MXF_EXPORTED mxfSoftInfoCountGet(HMXF_SERVER server, uint64* count);
         uint32 MXF_EXPORTED mxfSoftInfoGet(HMXF_SERVER server, uint64 maxCount, uint64* count, MXF_SOFT_INFO* info);
         uint32 MXF_EXPORTED mxfDeviceInfoGet(HMXF_DEVICE device, MXF_DEVICE_INFO* info);
         uint32 MXF_EXPORTED mxfDeviceFlashInfoRead(HMXF_DEVICE device, int64 index, MXF_FLASH_INFO* info);

         uint32 MXF_EXPORTED mxfSelfTestMEMORY(HMXF_DEVICE device, uint64 level, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestMILSTD1553(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestEBR1553(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestSERIALASYNC(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestARINC429(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestARINC629(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestARINC717(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestARINC708(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestHDLC(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestCSDB(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestDISCRETE(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestVOLTAGE(HMXF_DEVICE device, uint64 zone, double *value, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestCURRENT(HMXF_DEVICE device, uint64 zone, double *value, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestTEMPERATURE(HMXF_DEVICE device, uint64 zone, double *value, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestRTCLK(HMXF_DEVICE device, uint64 level, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestDEBUGCOMPORT(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestETHERNET(HMXF_DEVICE device, uint64 port, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestSYNCIO(HMXF_DEVICE device, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestIRIGB(HMXF_DEVICE device, uint64 signal, uint64 level, uint64 extLoopback, uint64 *result, char *info, char *diagnostic);
         uint32 MXF_EXPORTED mxfSelfTestNVSTORAGE(HMXF_DEVICE device, uint64 level, uint64 *result, char *info, char *diagnostic);

         uint32 MXF_EXPORTED mxfDeviceFirmwareUpload(HMXF_DEVICE device, const char* file, uint64 reset, MXF_DEVICE_FIRMWARE_STATUS_CALLBACK callback);
         uint32 MXF_EXPORTED mxfDeviceFirmwareErase(HMXF_DEVICE device, uint64 reset, MXF_DEVICE_FIRMWARE_STATUS_CALLBACK callback);
         uint32 MXF_EXPORTED mxfDeviceFileUpload(HMXF_DEVICE device, uint64 type, const char* name);
         uint32 MXF_EXPORTED mxfStandAloneFileGenerate(const char* app, const char* trapHandlers, uint64 fileNum, const char** files, const char* name);

         uint32 MXF_EXPORTED mxfDeviceCommBufferAlloc     (HMXF_DEVICE device, uint64 index, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
         uint32 MXF_EXPORTED mxfDeviceCommBufferGet       (HMXF_DEVICE device, uint64 index, HMXF_BUFFER* buffer);
         uint32 MXF_EXPORTED mxfDeviceCommBufferFree      (HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfDeviceCommBufferStatusGet (HMXF_BUFFER buffer, uint64* status, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
         uint32 MXF_EXPORTED mxfDeviceCommBufferInfoGet   (HMXF_BUFFER buffer, HMXF_DEVICE* device, uint64* index);
         uint32 MXF_EXPORTED mxfDeviceCommBufferWrite     (HMXF_BUFFER buffer, uint64 count, MXF_EMBEDDED_DATAREC* rec);
         uint32 MXF_EXPORTED mxfDeviceCommBufferWriteAsync(HMXF_BUFFER buffer, uint64 count, MXF_EMBEDDED_DATAREC* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK writeCompletion, void* context);
         uint32 MXF_EXPORTED mxfDeviceCommBufferRead      (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgReadCount, uint64* byteReadCount, MXF_EMBEDDED_DATAREC* rec);
         uint32 MXF_EXPORTED mxfDeviceCommBufferReadAsync (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, MXF_EMBEDDED_DATAREC* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK readCompletion, void* context);
         uint32 MXF_EXPORTED mxfDeviceCommBufferClear     (HMXF_BUFFER buffer);

         uint32 MXF_EXPORTED mxfDeviceBuffersFree(HMXF_DEVICE device);

         uint32 MXF_EXPORTED mxfNextRecordPtrGet(uint64 channelClass, uint64 recType, void* currentRec, void** nextRec);

         uint32 MXF_EXPORTED mxfDeviceLocationGet(HMXF_DEVICE device, uint64* index);

         uint32 MXF_EXPORTED mxfDeviceModuleCountGet(HMXF_DEVICE device, uint64 type, uint64* count);
         uint32 MXF_EXPORTED mxfDeviceModuleGet(HMXF_DEVICE device, uint64 index, HMXF_MODULE* module);
         uint32 MXF_EXPORTED mxfDeviceModuleAllGet(HMXF_DEVICE device, uint64 type, uint64 maxCount, uint64* count, HMXF_MODULE* modules);

         uint32 MXF_EXPORTED mxfDeviceFileVersionGet(HMXF_SERVER server, uint64 index, uint64 type, uint64* major, uint64* minor, uint64* subminor);
         uint32 MXF_EXPORTED mxfDeviceFileVersionWantedGet(HMXF_SERVER server, uint64 index, uint64 type, uint64* major, uint64* minor, uint64* subminor);
         uint32 MXF_EXPORTED mxfDeviceIpAddressSet(HMXF_DEVICE device, const char* ipAddress, const char* ipNetMask);
         uint32 MXF_EXPORTED mxfDeviceIpAddressGet(HMXF_DEVICE device, uint64 ipAddressSize, uint64 ipNetMaskSize, char* ipAddress, char* ipNetMask);
         uint32 MXF_EXPORTED mxfDeviceLedSet(HMXF_DEVICE device, uint64 mask, uint64 state);
         uint32 MXF_EXPORTED mxfDeviceLedGet(HMXF_DEVICE device, uint64* mask, uint64* state);

         uint32 MXF_EXPORTED mxfSensorsCountGet(HMXF_HANDLE handle, uint64* count);
         uint32 MXF_EXPORTED mxfSensorsRead(HMXF_HANDLE handle, uint64 id, double* value);
         uint32 MXF_EXPORTED mxfSensorsReadAll(HMXF_HANDLE handle, uint64 maxCount, uint64* count, MXF_SENSOR_VALUE* value);
         uint32 MXF_EXPORTED mxfSensorsInfoGet(HMXF_HANDLE handle, uint64 id, MXF_SENSOR_INFO *info);

         uint32 MXF_EXPORTED mxfDeviceStatisticsErrorDetailsGet(HMXF_DEVICE device, MXF_DEVICE_STAT_ERROR_DETAILS* stats);
         uint32 MXF_EXPORTED mxfDeviceStatisticsResourcesGet(HMXF_DEVICE device, MXF_DEVICE_STAT_RESOURCES* stats);

         uint32 MXF_EXPORTED mxfDeviceStatisticReset(HMXF_DEVICE device, uint64 options);

         uint32 MXF_EXPORTED mxfDeviceIrigbStatusGet(HMXF_DEVICE device, uint64* status);
         uint32 MXF_EXPORTED mxfDeviceIrigbTimerGet(HMXF_DEVICE device, MXF_TIMER_IRIGB* timer);
         uint32 MXF_EXPORTED mxfDeviceIrigbBcdCompose(uint64 years, uint64 days, uint64 hours, uint64 minutes, uint64 seconds, uint64* bcd);
         uint32 MXF_EXPORTED mxfDeviceIrigbBcdDecompose(uint64 bcd, uint64* years, uint64* days, uint64* hours, uint64* minutes, uint64* seconds);
         uint32 MXF_EXPORTED mxfDeviceIrigbBcdToBinary(uint64 bcd, uint64* seconds);

         uint32 MXF_EXPORTED mxfDeviceTimerGet(HMXF_DEVICE device, uint64* timer);

         uint32 MXF_EXPORTED mxfModuleInfoGet(HMXF_MODULE module, HMXF_DEVICE* device);
         uint32 MXF_EXPORTED mxfModuleChannelCountGet(HMXF_MODULE module, uint64 channelClass, uint64 subClass, uint64* count);
         uint32 MXF_EXPORTED mxfModuleChannelGet(HMXF_MODULE module, uint64 channelIndex, HMXF_CHANNEL* channel);
         uint32 MXF_EXPORTED mxfModuleChannelAllGet(HMXF_MODULE module, uint64 channelClass, uint64 subClass, uint64 maxChannel, uint64* count, HMXF_CHANNEL* channels);

         uint32 MXF_EXPORTED mxfChannelInfoGet(HMXF_CHANNEL channel, HMXF_DEVICE* device, HMXF_MODULE* module);
         uint32 MXF_EXPORTED mxfChannelDirectionGet(HMXF_CHANNEL channel, uint64* direction);
         uint32 MXF_EXPORTED mxfChannelLocationGet(HMXF_CHANNEL channel, uint64* deviceIndex, uint64* moduleIndex, uint64* channelIndex);
         uint32 MXF_EXPORTED mxfChannelRecordSizeGet(HMXF_CHANNEL channel, uint64* size);
         uint32 MXF_EXPORTED mxfChannelRxStatusGet(HMXF_CHANNEL channel, uint64* status);
         uint32 MXF_EXPORTED mxfChannelTxStatusGet(HMXF_CHANNEL channel, uint64* status);
         uint32 MXF_EXPORTED mxfChannelTxPortEnableSet(HMXF_CHANNEL channel, uint64 enable);
         uint32 MXF_EXPORTED mxfChannelTxPortEnableGet(HMXF_CHANNEL channel, uint64* enable);

         uint32 MXF_EXPORTED mxfChannelStatisticGet(HMXF_CHANNEL channel, uint64 type, void* stat);
         uint32 MXF_EXPORTED mxfChannelStatisticReset(HMXF_CHANNEL channel, uint64 options);
         uint32 MXF_EXPORTED mxfChannelStatisticEnableSet(HMXF_CHANNEL channel, uint64 enable);
         uint32 MXF_EXPORTED mxfChannelStatisticEnableGet(HMXF_CHANNEL channel, uint64* enable);

         uint32 MXF_EXPORTED mxfChannelDiscreteOutputTriggerEnableSet(HMXF_CHANNEL channel, uint64 trigEvent, uint64 enable, uint64 discretePort);
         uint32 MXF_EXPORTED mxfChannelDiscreteOutputTriggerEnableGet(HMXF_CHANNEL channel, uint64 trigEvent, uint64* enable, uint64* discretePort);

         uint32 MXF_EXPORTED mxfAsyncEventHandlerInit(HMXF_SERVER server, MXF_ASYNCEVENT_HANDLER handler, void* param, HMXF_ASYNCEVENT* asyncEvent);
         uint32 MXF_EXPORTED mxfAsyncEventHandlerTerminate(HMXF_ASYNCEVENT asyncEvent);
         uint32 MXF_EXPORTED mxfAsyncEventConditionsGet(HMXF_ASYNCEVENT asyncEvent, uint64 maxCount, uint64* count, MXF_ASYNCEVENT_CONDITION* conditions);
         uint32 MXF_EXPORTED mxfAsyncEventConditionsSet(HMXF_ASYNCEVENT asyncEvent, uint64 enable, uint64 count, MXF_ASYNCEVENT_CONDITION* conditions);
         uint32 MXF_EXPORTED mxfAsyncEventPendingCountGet(HMXF_ASYNCEVENT asyncEvent, uint64* count);
         uint32 MXF_EXPORTED mxfAsyncEventPendingGet(HMXF_ASYNCEVENT asyncEvent, uint64 maxCount, uint64* count, MXF_ASYNCEVENT_PENDING_INFO* pendingInfo);
         uint32 MXF_EXPORTED mxfAsyncEventPendingClear(HMXF_ASYNCEVENT asyncEvent);
         uint32 MXF_EXPORTED mxfAsyncEventRxMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count, void* msg);
         uint32 MXF_EXPORTED mxfAsyncEventRxMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, void* msg);
         uint32 MXF_EXPORTED mxfAsyncEventTxPeriodicUpdateMsgSelectSet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 select, uint64 count, HMXF_BUFFER* bufferArray);
         uint32 MXF_EXPORTED mxfAsyncEventTxPeriodicUpdateMsgSelectGet(HMXF_ASYNCEVENT asyncEvent, HMXF_CHANNEL channel, uint64 maxCount, uint64* count, HMXF_BUFFER* bufferArray);

         #if !defined(__MXF_EMBEDDED)

         uint32 MXF_EXPORTED mxfEmbeddedCodeDownload(HMXF_DEVICE device, const char* name);
         uint32 MXF_EXPORTED mxfEmbeddedDataDownload(HMXF_DEVICE device, uint64 size, uint32* data);
         uint32 MXF_EXPORTED mxfEmbeddedCommandSend(HMXF_DEVICE device, uint64 command, uint64 paramSize, uint32* param);
         uint32 MXF_EXPORTED mxfEmbeddedHandlerEnableSet(HMXF_CHANNEL channel, uint64 id, uint64 enable, uint64 param);
         uint32 MXF_EXPORTED mxfEmbeddedSharedBufferRead(HMXF_DEVICE device, uint64 offset, uint64 size, uint32* data);
         uint32 MXF_EXPORTED mxfEmbeddedSharedBufferWrite(HMXF_DEVICE device, uint64 offset, uint64 size, uint32* data);

         uint32 MXF_EXPORTED mxfEmbeddedRxBufferAlloc       (HMXF_DEVICE device, uint64 index, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferGet         (HMXF_DEVICE device, uint64 index, HMXF_BUFFER* buffer);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferFree        (HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferStatusGet   (HMXF_BUFFER buffer, uint64* status, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferInfoGet     (HMXF_BUFFER buffer, HMXF_DEVICE* device, uint64* index);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferClear       (HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferRead        (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, MXF_EMBEDDED_DATAREC* rec);
         uint32 MXF_EXPORTED mxfEmbeddedRxBufferReadAsync   (HMXF_BUFFER buffer, uint64 maxMsgCount, uint64 maxBytesCount, MXF_EMBEDDED_DATAREC* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK readCompletion, void* context);

         uint32 MXF_EXPORTED mxfEmbeddedTxBufferAlloc       (HMXF_DEVICE device, uint64 index, uint64 size, HMXF_BUFFER* buffer, uint64* allocated);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferGet         (HMXF_DEVICE device, uint64 index, HMXF_BUFFER* buffer);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferFree        (HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferStatusGet   (HMXF_BUFFER buffer, uint64* msgCount, uint64* pendingBytes, uint64* freeBytes);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferInfoGet     (HMXF_BUFFER buffer, HMXF_DEVICE* device, uint64* index);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferClear       (HMXF_BUFFER buffer);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferWrite       (HMXF_BUFFER buffer, uint64 count, MXF_EMBEDDED_DATAREC* rec);
         uint32 MXF_EXPORTED mxfEmbeddedTxBufferWriteAsync  (HMXF_BUFFER buffer, uint64 count, MXF_EMBEDDED_DATAREC* hostBuffer, MXF_ASYNCHRONOUS_CALLBACK writeCompletion, void* context);

         #endif

         uint32 MXF_EXPORTED mxfEmbeddedNVStorageHandleGet(HMXF_DEVICE device, HMXF_NVSTORAGE* nvStorage);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageLocationGet(HMXF_NVSTORAGE nvStorage, uint64* index);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFormat(HMXF_NVSTORAGE nvStorage);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageInfoGet(HMXF_NVSTORAGE nvStorage, MXF_NVSTORAGE_INFO* info);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileCreate(HMXF_NVSTORAGE nvStorage, uint64 count, uint64* index);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileCountGet(HMXF_NVSTORAGE nvStorage, uint64* count);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileSizeGet(HMXF_NVSTORAGE nvStorage, uint64 index, uint64* size);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileReset(HMXF_NVSTORAGE nvStorage, uint64 index);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileRewind(HMXF_NVSTORAGE nvStorage, uint64 index);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgTypeSet(HMXF_NVSTORAGE nvStorage, uint64 index, uint64 type);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgTypeGet(HMXF_NVSTORAGE nvStorage, uint64 index, uint64* type);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgSelectEnableSet(HMXF_CHANNEL channel, uint64 index, uint64 options, uint64 enable);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgSelectEnableGet(HMXF_CHANNEL channel, uint64* index, uint64* options, uint64* enable);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgSelectSet(HMXF_CHANNEL channel, uint64 select, uint64 count, void* msg);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgSelectGet(HMXF_CHANNEL channel, uint64 maxCount, uint64* count, void* msg);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE nvStorage, uint64 index, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, void* msg);
         uint32 MXF_EXPORTED mxfRawEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE nvStorage, uint64 index, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, uint8* msg);
         uint32 MXF_EXPORTED mxfUserDefEmbeddedNVStorageFileMsgRead(HMXF_NVSTORAGE nvStorage, uint64 index, uint64 maxMsgCount, uint64 maxBytesCount, uint64* msgCount, uint64* byteCount, MXF_EMBEDDED_DATAREC* msg);
         uint32 MXF_EXPORTED mxfRawEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 index, uint64 maxCount, uint8* rec, uint64* count);
         uint32 MXF_EXPORTED mxfUserDefEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE storage, uint64 index, uint64 maxCount, MXF_EMBEDDED_DATAREC* rec, uint64* count);
         #if !defined(__MXF_EMBEDDED)
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileStatusGet(HMXF_NVSTORAGE nvStorage, uint64 index, uint64* freeByte, uint64* unreadByte, uint64* bufferedWriteByte, uint64* overflow);
         uint32 MXF_EXPORTED mxfEmbeddedNVStorageFileMsgWrite(HMXF_NVSTORAGE nvStorage, uint64 index, uint64 maxCount, void* msg, uint64* count);
         #endif

         uint32 EXPORTED mxfServerConnect(const char* url, const char* userName, const char* password, uint64 exclusive, HMXF_SERVER* server);
         uint32 EXPORTED mxfServerDisconnect(HMXF_SERVER server);
         uint32 EXPORTED mxfServerVersionGet(HMXF_SERVER server, uint64* major, uint64* minor, uint64* subminor);
         uint32 EXPORTED mxfServerUserCountGet(HMXF_SERVER server, uint64* count);
         uint32 EXPORTED mxfServerUserListGet(HMXF_SERVER server, uint64 maxCount, uint64* count, MXF_NETWORK_SERVER_USER_INFO* users);
         uint32 EXPORTED mxfServerUserDisconnect(HMXF_SERVER server, uint64 id);
         uint32 EXPORTED mxfSystemUSBDetect(uint64* count);
         uint32 EXPORTED mxfSystemUSBServerConnect(uint64 index,  HMXF_SERVER* server);

         uint32 EXPORTED mxfServerACLUserCountGet     (HMXF_SERVER server, uint64* count);
         uint32 EXPORTED mxfServerACLUserListGet      (HMXF_SERVER server, uint64 maxCount, uint64* count, MXF_ACL_USER* users);
         uint32 EXPORTED mxfServerACLUserGet          (HMXF_SERVER server, MXF_ACL_USER* user);
         uint32 EXPORTED mxfServerACLUserSet          (HMXF_SERVER server, MXF_ACL_USER* user);
         uint32 EXPORTED mxfServerACLUserAdd          (HMXF_SERVER server, MXF_ACL_USER* user);
         uint32 EXPORTED mxfServerACLUserRemove       (HMXF_SERVER server, MXF_ACL_USER* user);
         uint32 EXPORTED mxfServerACLUserWriteToFlash (HMXF_SERVER server);


      #endif

   #ifdef __cplusplus
   }
   #endif

#endif
