/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

#ifndef MXF_ATTRIBUTES_H_CONST
#define MXF_ATTRIBUTES_H_CONST

   #define KMXF_DEVICE_IRIGB_INPUT                             0ULL
      #define VMXF_DEVICE_IRIGB_INPUT_NONE                        0ULL
      #define VMXF_DEVICE_IRIGB_INPUT_DEVICE                      1ULL
   #define KMXF_DEVICE_IRIGB_PHASE_COMPENSATION                1ULL
   #define KMXF_DEVICE_IRIGB_INPUT_SIGNAL                      2ULL
      #define VMXF_DEVICE_IRIGB_INPUT_SIGNAL_AM                   0ULL
      #define VMXF_DEVICE_IRIGB_INPUT_SIGNAL_AM_1PPS              1ULL
      #define VMXF_DEVICE_IRIGB_INPUT_SIGNAL_DIGITAL              2ULL
   #define KMXF_DEVICE_EMBEDDED_CODEANDDATA_SIZE               3ULL
   #define KMXF_DEVICE_EMBEDDED_SHARED_SIZE                    4ULL
   #define KMXF_DEVICE_EMBEDDED_RX_QUEUE_NUM                   5ULL
   #define KMXF_DEVICE_EMBEDDED_TX_QUEUE_NUM                   6ULL
   #define KMXF_DEVICE_IRIGB_GEN_BCD_TIME                      7ULL
   #define KMXF_DEVICE_IRIGB_GEN_ENABLE                        8ULL
   #define KMXF_DEVICE_IRIGB_GEN_LOOPBACK_ENABLE               9ULL
   #define KMXF_DEVICE_IRIGB_YEAR_DECODING_ENABLE              10ULL
   #define KMXF_DEVICE_IRIGB_YEAR_RANGE_MIN                    11ULL
   #define KMXF_DEVICE_IRIGB_TIMEOUT                           12ULL
   #define KMXF_DEVICE_IRIGB_DRIFT_MAX                         13ULL
   #define KMXF_DEVICE_TYPE                                    14ULL
   #define KMXF_DEVICE_COMM_QUEUE_NUM                          15ULL

   #define KMXF_MODULE_TYPE                                    10000ULL
   #define KMXF_MODULE_OPTIONS                                 10001ULL
   #define KMXF_MODULE_RX_FIFO_AGING                           10002ULL
   #define KMXF_MODULE_RX_FIFO_AF                              10003ULL
   #define KMXF_MODULE_TX_FIFO_AF                              10004ULL
   #define KMXF_MODULE_TX_FIFO_AE                              10005ULL
   #define KMXF_MODULE_XON_VAL                                 10006ULL
   #define KMXF_MODULE_XOFF_VAL                                10007ULL
   #define KMXF_MODULE_RX_FLOWCTRL_FIFO_AE                     10008ULL
   #define KMXF_MODULE_RX_FLOWCTRL_FIFO_AF                     10009ULL
   #define KMXF_MODULE_TI                                      10010ULL
   #define KMXF_MODULE_SG                                      10011ULL
   #define KMXF_MODULE_INTERFACE                               10012ULL
   #define KMXF_MODULE_RX_ONLY                                 10013ULL
   #define KMXF_MODULE_XPP_FIFO_AGING                          10014ULL
   #define KMXF_MODULE_XPP_FIFO_AF                             10015ULL
   #define KMXF_MODULE_XPP_CID_ENABLE                          10016ULL
   #define KMXF_MODULE_XPP_DUAL_ENABLE                         10017ULL
   #define KMXF_MODULE_RX_TIMETAG_ENABLE                       10018ULL
   #define KMXF_MODULE_ACTIVE                                  10019ULL

   #define KMXF_CHANNEL_CLASS                                  20000ULL
   #define KMXF_CHANNEL_SUBCLASS                               20001ULL

   #define KMXF_MSG_CRC                                        1ULL
   #define KMXF_MSG_CHECKSUM                                   2ULL

   #define VMXF_DISABLE                                        0ULL
   #define VMXF_ENABLE                                         1ULL

   #define MXF_ATTRIBUTE_INFO_TYPE_UINT64                      0ULL
   #define MXF_ATTRIBUTE_INFO_TYPE_DOUBLE                      1ULL

   #define MXF_ATTRIBUTE_INFO_FORMAT_ENUM                      0ULL
   #define MXF_ATTRIBUTE_INFO_FORMAT_RANGE                     1ULL
   #define MXF_ATTRIBUTE_INFO_FORMAT_BITMASK                   2ULL

   #define MXF_ATTRIBUTE_INFO_PROPERTY_READONLY                0x0001ULL
   #define MXF_ATTRIBUTE_INFO_PROPERTY_HARDSET                 0x0040ULL
   #define MXF_ATTRIBUTE_INFO_PROPERTY_INIT                    0x0100ULL

   typedef struct
   {
      uint64   format;
      union
      {
         struct
         {
            uint64   min;
            uint64   max;
            uint64   reserved;
            uint64   reserved1;
         }
         range;

         struct
         {
            uint64   count;
            uint64   reserved;
            struct
            {
               char     name[32];
               uint64   value;
            }
            index[16];
         }
         enumeration;

         struct
         {
            uint64   bitCount;
            uint64   reserved;
            char     name[32];
            uint64   enumCount;
            struct
            {
               char     name[32];
               uint64   value;
            }
            index[16];
         }
         bitMask;
      }
      details;
   }
   MXF_ATTRIBUTE_INFO_UINT64_DETAILS;

   typedef struct
   {
      uint64   format;
      union
      {
         struct
         {
            double   min;
            double   max;
            double   reserved;
            double   reserved1;
         }
         range;

         struct
         {
            uint64   count;
            double   reserved;
            struct
            {
               char     name[32];
               double   value;
            }
            index[16];
         }
         enumeration;
      }
      details;
   }
   MXF_ATTRIBUTE_INFO_DOUBLE_DETAILS;

   typedef struct
   {
      uint64   type;
      uint64   properties;
      char     name[32];
      char     unit[32];
   }
   MXF_ATTRIBUTE_INFO;

   #ifdef __cplusplus
   extern "C" {
   #endif

      typedef uint32 (*MXF_SYSTEM_INIT_ATTRIBUTE_UINT64_HANDLER)(HMXF_SERVER server, uint64 deviceIndex, uint64 moduleIndex, uint64 channelIndex, uint64 attrib, uint64* value);

      uint32 MXF_EXPORTED mxfSystemInitAttributeUint64CallbackHandler(HMXF_SERVER server, MXF_SYSTEM_INIT_ATTRIBUTE_UINT64_HANDLER handler);

      uint32 MXF_EXPORTED mxfAttributeCountGet(HMXF_HANDLE handle, uint64* count);
      uint32 MXF_EXPORTED mxfAttributeListGet(HMXF_HANDLE handle, uint64 maxCount, uint64* count, uint64* attribList);
      uint32 MXF_EXPORTED mxfAttributeInfoGet(HMXF_HANDLE handle, uint64 attrib, MXF_ATTRIBUTE_INFO* info);
      uint32 MXF_EXPORTED mxfAttributeInfoDetailsGet(HMXF_HANDLE handle, uint64 attrib, void* details);

      uint32 MXF_EXPORTED mxfAttributeUint64Set(HMXF_HANDLE handle, uint64 attrib, uint64 value);
      uint32 MXF_EXPORTED mxfAttributeUint64Get(HMXF_HANDLE handle, uint64 attrib, uint64* value);

      uint32 MXF_EXPORTED mxfAttributeDoubleSet(HMXF_HANDLE handle, uint64 attrib, double value);
      uint32 MXF_EXPORTED mxfAttributeDoubleGet(HMXF_HANDLE handle, uint64 attrib, double* value);

      uint32 MXF_EXPORTED mxfChannelMsgAttributeUint64Set(HMXF_CHANNEL channel, uint64 attrib, void* msg, uint64 value);
      uint32 MXF_EXPORTED mxfChannelMsgAttributeUint64Get(HMXF_CHANNEL channel, uint64 attrib, void* msg, uint64* value);

   #ifdef __cplusplus
   }
   #endif

#endif
