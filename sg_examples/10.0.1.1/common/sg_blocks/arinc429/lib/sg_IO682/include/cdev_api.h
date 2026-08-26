/*===========================================================================*
 * FILE:                    C D E V _ A P I . H
 *===========================================================================*
 *
 * COPYRIGHT (C) 2002-2014
 *          GE INTELLIGENT PLATFORMS, INC. SANTA BARBARA, CALIFORNIA
 *          ALL RIGHTS RESERVED.
 *
 *          THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND
 *          COPIED ONLY IN ACCORDANCE WITH THE TERMS OF SUCH LICENSE AND WITH
 *          THE INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR ANY
 *          OTHER COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE
 *          AVAILABLE TO ANY OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF THE
 *          SOFTWARE IS HEREBY TRANSFERRED.
 *
 *          THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT
 *          NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY GE 
 *          INTELLIGENT PLATFORMS.
 *
 *===========================================================================*
 *
 * FUNCTION:    Header file for all CEI-x30 API public contants, public
 *              and local API data structure definitions, and public 
 *              API function prototypes.
 * 
 *---------------------------------------------------------------------------*
 *          
 * HISTORY:   
 *
 *   Date    By   Ver. Comments
 * -------- ----- ---- ------------------------------------------------------------
 * 10/26/01  BDW  1.00 Created.
 * 11/06/03  BDW  1.01 Added CEI-830 channel types.
 * 09/14/05  BDW  1.20 Added support for Linux via inclusion of CDEV_LNX.H
 *                     Included relocating some compiler directive defines from
 *                     CDEV_API.C
 * 10/21/05  BDW  1.30 Added support for the CEI-430 firmware load:        
 *                      - constants for new channel types DIFFERENTIAL_IN_CHANNEL
 *                        and DIFFERENTIAL_OUT_CHANNEL (API internal usage only)
 *                        modifying the value of NUMBER_OF_CHANNEL_TYPES
 *                      - added the new h/w type CEIDEV_CHANNEL_TYPE_DIFFERENTIAL
 *                        modifying the value of CEIDEV_CHANNEL_TYPE_MAX
 *                      - added new board identifier CEIDEV_ALT_CONFIGURATION_430
 * 12/06/05  BDW  1.30 Added channel count report options for AR_Get_Device_Config
 *                        ARU_CHAN_COUNT_429        448
 *                        ARU_CHAN_COUNT_573        449
 *                        ARU_CHAN_COUNT_DISC       450
 *                        ARU_CHAN_COUNT_DIFF       451
 * 09/19/06  BDW  1.32 Added the AMC-A30 board type constant AMCA30
 *                     Increased the VxWorks & Linux MAX_BOARDS definition to 
 *                        support up to 8 devices
 * 05/11/07  BDW  1.40 Added support for the EC-A30, CEI-530, -630 and -830RX boards
 * 07/25/07  BDW  1.40 Support for R830RX ARU_IRIG_OUTPUT_ENABLE option added
 *                        to arx30_set_device_config/arx30_get_device_config
 * 10/24/07  BDW  1.41 Added the configuration values CEIDEV_CONFIG_RAR_CPCI (12) 
 *                                                    CEIDEV_CONFIG_RAR_EC (13)
 *                     Increased CEIDEV_NUM_CONFIGURATIONS from 12 to 14
 * 01/07/08  BDW  1.50 Added the member "serialNumber" to the ARINC_DEVICE_TYPE
 *                        data structure, supporting RAR-EC PPROM serial number
 * 02/18/08  BDW  1.51 Removed the data structure type def CDEV_CHANNEL_IDENT_TYPE
 * 03/19/08  BDW  1.60 Modified the prototype for arx30_get_boardnameLV.
 * 11/19/08  BDW  1.70 Updated compiler directive usage in support of Integrity o/s.
 * 06/23/09  BDW  2.00 Added Enhanced CEI-x30 Interface support constants used in
 *                        arx30_get/set_device_config, ARU_HW_ENHANCE_CHECK & ARU_HW_ENHANCE_UPDATE 
 * 05/19/10  BDW  2.10 Added support for the RAR-PCIE to the following items:
 *                        define CEIDEV_CONFIG_RAR_PCIE to the RAR-PCIE Configuration code
 *                        set CEIDEV_LAST_CEIX30_CONFIG to CEIDEV_CONFIG_RAR_PCIE                       
 * 11/01/10  BDW  3.00 Modified the return type for arx30_get_base_addr to be a pointer
 * 09/16/11  BDW  3.10 Added CEI-430A support with CEIDEV_CONFIG_CEI430A and CEI430A definitions
 * 02/17/12  BDW  3.11 Modified the definition of MAX_BOARDS to 128 for Windows o/s's
 * 05/21/12  BDW  4.00 Added support for the new combo ARINC/1553 boards
 *    to                 - new board types for the RAR15-XMC and RAR15-XMC-XT
 * 09/28/12              - new x30 configurations for the RAR15-XMC and RAR15-XMC-XT
 *                       - new 1553 timestamp sync options AR_TIMETAG_SYNC_1553_CHn
 *                       - new routine prototype for arx30_get_rx_channel_status
 *                       - new channel indexing info structure type and routine                   
 *                         AR_CHANNEL_INDEX_INFO_TYPE and arx30_get_channel_index_info                 
 * 08/03/12  BDW  4.01 Beta release for RAR15-XMC-XT Integrity Support
 * 04/08/13  BDW  4.20 Added support for the RCEI-830X820, including the Board Type
 *                     Identifier assignment - CEI830X820 with a value of 34
 * 06/13/13  BDW  4.30 Release full distribution for the (R)AR15-XMC-XT and
 *                     RCEI-830X820 boards
 * 10/03/13  BDW  4.40 Added support for the RCEI-830A, including constants for
 *                     the board type RCEI830A and configuration type CEIDEV_CONFIG_RCEI830A
 * 10/25/13  BDW  4.40 Change the address parameters for the routine arx30_set_base_addresses
 *                     from fixed 32-bit values to compiler-directed 32-bit or 64-bit values
 * 01/08/14  BDW  4.50 Modified the data type for the Linux build definition of ARINC_LOCAL_TYPE 
 *                     member sharedMemoryHandle 
 *===========================================================================*/
#ifndef CEIDEV_API_H
#define CEIDEV_API_H

#ifndef LABVIEW_RT
#define API_VERSION             "4.50"
#else
#define API_VERSION             "RT_4.50"
#endif
#define CEI_EARLIEST_COMPATIBLE_FW 0x0000004D
/*---------------------------------------------------------------------------*
 *  Microsoft C protected mode program
 *---------------------------------------------------------------------------*/

#if defined (_WINDOWS)  
   #define _Windows
#elif defined(_WINDLL)
   #define _Windows
#elif defined(WIN32)
   #define _Windows
#endif 
                      
/*------------------------------------------------------------------------* 
 *  For CVI and Borland C++ Compilers
 *------------------------------------------------------------------------*/
                   
#if defined (__WIN32__)    
   #if !defined(_CVI_)
      #if !defined(_WIN32)
         #define _WIN32
      #endif
   #endif
#endif 

#if !defined (_WIN32)
   #define EXPORT __export
   #define EXPORT32
#else
   #include <windows.h>
   #define EXPORT32  

   #if !defined (_CVI_)
      #include <windowsx.h>
   #endif
   #if defined(__BORLANDC__)
      #define EXPORT __export
   #else         
      #define EXPORT
   #endif
#endif

#if 0 // Not for Simulink Real-Time
#ifndef LABVIEW_RT
   #if defined(_LINUX_X86_) || defined(_LINUX_PPC_)
      #include <stdio.h>
      #include <stdlib.h>
      #include <time.h>
      #include <sys/types.h>
      #include <sys/timeb.h>
   #else
      #include <ctype.h>
      #include <time.h>
      #include <stdio.h>
   #endif
#endif
#endif

#include "cei_types.h"

#if defined (VXWORKS) || defined (_LINUX_X86_) || defined (_LINUX_PPC_) || defined (INTEGRITY_PCI_PPC)
   #ifndef MAX_BOARDS
      #define MAX_BOARDS  8
   #endif
#elif defined (NIVISA_PXI)
   #define MAX_BOARDS 16
   #define LABVIEW
#else
   #define MAX_BOARDS 16
#endif

#include "cdev_hw.h"

/*===========================================================================*
 * Internal API Usage - Device Description Structures and Definitions
 *===========================================================================*
 */
typedef float CEI_FLOAT;
typedef CEI_UINT32 ARINC;
typedef CEI_UINT64 TIME_TAG_TYPE;       /* __int64 */

/* GE Intelligent Platforms, Santa Barbara Division Products,
   Product Identification Assignments
 */
#define UNSUPPORTED   1

/* this next group are from UTILDEFS.H and are used universally */
#define CEI520        6 
#define CEI620       10 
#define CEI820       11 
#define CEI715       16 
#define CEI830       19     /* supported by this API */
#define PMC708       20
#define CEI430       21     /* supported by this API */
#define AMCA30       22     /* supported by this API */
#define CEI530       26     /* supported by this API */
#define R830RX       27     /* supported by this API */
#define RARCPCI      28     /* supported by this API */
#define RAREC        29     /* supported by this API */
#define RARPCIE      30     /* supported by this API */
#define CEI430A      31     /* supported by this API */
#define MAC          32
#define RARUSB       33
#define CEI830X820   34
#define RARXMC       35     /* supported by this API */
#define RCEI830A     36     /* supported by this API */
#define RP_708       37
#define RAR15       118     /* supported by this API */
#define RAR15XT     119     /* supported by this API */

/* this group is defined solely for use with arx30_query_device()  */
#define CNIC        100
#define PMCD1       101
#define PMCD2       102
#define EPMC        103
#define PSER        104
#define PMIO        105
#define PDIS        106
#define P10SF       107
#define PCx1553     109
#define QD_QPCI     110
#define QD_QCP      111
#define QD_QPCX     112
#define QD_AMC1553  108
#define QD_R15EC    113
#define QD_RXMC     114
#define QD_RPCIE    115
#define QD_LCPIE    116
#define QD_RXMC2    117
#define EC_CNIC     120
#define RCNIC       121

#define CEI630       28     /* redundant board type for the RAR-CPCI using new board name format */


#define MAX_LABEL               256
#define MAX_SDI                 4
#define MAX_ESSM                8
#define MAX_CHANNEL             32
#define MAX_SCHEDULED_MSGS      1024
#define NUM_SUBFRAME_SYNC_WORDS 4

/*---------------------------------------------------------------------------*
 * Channel Types used in the AR_CHANNEL_INDEX_INFO chan_type structure member
 *---------------------------------------------------------------------------*/
typedef enum 
{
   AR_CHAN_TYPE_429_RX = 0,     
   AR_CHAN_TYPE_429_TX = 1,     
   AR_CHAN_TYPE_429_RX_OR_TX = 2,
   AR_CHAN_TYPE_UNDEFINED = 255
} channelType;

/*---------------------------------------------------------------------------*
 * Channel allocation on the CEI-x30 board
 *---------------------------------------------------------------------------*/
typedef struct
{
   CEI_UINT32 num_channels;                       /* total number of channels               */
   CEI_UINT32 chan_type[CEIDEV_MAX_CHANNELS];     /* channel type constant AR_CHAN_TYPE_<x> */
   CEI_UINT32 chan_rx_index[CEIDEV_MAX_CHANNELS]; /* associated receive channel index       */
   CEI_UINT32 chan_tx_index[CEIDEV_MAX_CHANNELS]; /* associated transmit channel index      */
} AR_CHANNEL_INDEX_INFO_TYPE;


/*---------------------------------------------------------------------------*
 * The ARINC_LOCAL_TYPE structure contains local-process parameters
 *   regarding specific device mapping and API usage
 *---------------------------------------------------------------------------*/

typedef struct ARINC_LOCAL {
   pCEI_UINT32 baseAddr;           /* Plug'n'Play Address to which the device is mapped */
   pCEI_UINT32 devicePtr;          /* Pointer to location at which the device is mapped */
#if defined (_LINUX_X86_) || defined (_LINUX_PPC_)
   CEI_INT32   sharedMemoryHandle; /* handle to multi-process shared memory region      */
#else
   pCEI_VOID   sharedMemoryHandle; /* handle to multi-process shared memory region      */
#endif
   CEI_UINT32  multiThreadProtect; /* multi-thread/process Mutex protection flag        */
} ARINC_LOCAL_TYPE;

/*---------------------------------------------------------------------------*
 * The ARINC_LOCAL_TYPE structure contains global configuration and  
 *   operational information regarding the specific device
 *---------------------------------------------------------------------------*/

typedef struct ARINC_GLOBAL {
   CEI_UINT16  numRx;                      /* Total number of Receivers on device      */
   CEI_UINT16  numTx;                      /* Total number of Transmitters on device   */
   CEI_UINT32  boardInitialized;           /* Indicates this board f/w has been loaded */
   CEI_UINT32  attachedProcessCount;       /* Number of processes actively attached to this device */
   CEI_UINT32  receiveMode;                /* Receive buffer operational mode, BUFFERED or MERGED */
   CEI_UINT32  transmitMode;               /* Transmitter configuration as CSDB, 573-HBP, or 573-BPRZ */
   CEI_UINT32  serialNumber;               /* RAR-EC Serial Number, stored in EEPROM */
   CEI_UINT32  firmwareVersion;            /* Firmware version loaded on this device */
   CEI_UINT32  configuration;              /* Board configuration for this device */
   CEI_UINT32  alternateJconfiguration;    /* ARINC 717 configuration flag for this device */
   CEI_UINT32  irigInstalled;              /* Indication that IRIG is installed on the device   */
   CEI_UINT32  deviceTimeTagReference;     /* The active time-tag reference selected for this device */
   CEI_UINT32  deviceX20CompatibleResolution; /* Selected x20-compatible time-ref resolution for this device */
   CEI_UINT32  numberOfChannels[NUMBER_OF_CHANNEL_TYPES]; /* the following 4 items track channel types and */
   CEI_UINT32  firstChannel[NUMBER_OF_CHANNEL_TYPES];     /* channel counts installed on this device       */
   CEI_UINT32  lastChannel[NUMBER_OF_CHANNEL_TYPES];
   CEI_UINT32  channelActive[CEIDEV_MAX_CHANNEL_NUMBER];
   CEI_UINT32  receiveChannelMessageCount[CEIDEV_MAX_RX_CHAN]; /* current msg count logged via arx30_clr_rx_count */
   CEI_UINT32  ceiPciInterruptEnabled;        /* Set when PCI Interrupts & ISR are Enabled */
   TIME_TAG_TYPE userProgrammableIrigOffset;  /* IRIG sample time offset used to coordinate with other IRIG devices */
#if defined (NO_INT64)
   double currentIrigTimeUsec;             /* 64-bit 1usec IRIG time-of-year placeholder  */
   double irigReferenceTimeTag;
#else
   TIME_TAG_TYPE currentIrigTimeUsec;
   TIME_TAG_TYPE irigReferenceTimeTag;  
#endif
   CEI_UINT32  comboBoard1553chanCount;       /* The 1553 channel count installed on a combo card */
   AR_CHANNEL_INDEX_INFO_TYPE boardChannelIndexInfoStruct;
} ARINC_GLOBAL_TYPE;


/*---------------------------------------------------------------------------*
 * Hardware Configuration Definitions (as defined by the hardware)
 *---------------------------------------------------------------------------*/
#define CEIDEV_NUM_CONFIGURATIONS 21    /* 19 number of configurations avail.   */
#define CEIDEV_NUM_ALT_CONFIGURATIONS 3 /* number of alt. configs avail.     */
#define CEIDEV_CONFIGURATION_NULL 0     /* configurations 1-6 are CEI-715    */
#define CEIDEV_CONFIG_CEI830      7     /* Unspecified CEI-830 configuration */
#define CEIDEV_CONFIG_CEI430      8     /* Unspecified CEI-430 configuration */
#define CEIDEV_CONFIG_AMCA30      9     /* Unspecified AMC-A30 configuration */
#define CEIDEV_CONFIG_CEI530     10     /* Unspecified CEI-530 configuration */
#define CEIDEV_CONFIG_R830RX     11     /* CEI-830RX - fixed configuration   */
#define CEIDEV_CONFIG_RAR_CPCI   12     /* Unspecified RAR-CPCI configuration*/
#define CEIDEV_CONFIG_RAR_EC     13     /* Unspecified RAR-EC configuration  */
#define CEIDEV_CONFIG_RAR_PCIE   14     /* Unspecified RAR-PCIE configuration*/
#define CEIDEV_CONFIG_CEI430A    15     /* Unspecified CEI-430 configuration */
#define CEIDEV_CONFIG_RAR15      16     /* Unspecified RAR15-XMC combo configuration */
#define CEIDEV_CONFIG_RAR15XT    17     /* Unspecified RAR15-XMC-XT combo configuration */
#define CEIDEV_CONFIG_R830X820   18     /* Unspecified RCEI-830X820 configuration */
#define CEIDEV_CONFIG_RAR_XMC    19     /* Unspecified RAR-XMC configuration */
#define CEIDEV_CONFIG_RCEI830A   20     /* Unspecified RCEI-830A configuration */
#define CEIDEV_FIRST_CEIX30_CONFIG CEIDEV_CONFIG_CEI830
#define CEIDEV_LAST_CEIX30_CONFIG CEIDEV_CONFIG_RCEI830A
#define CEIDEV_CONFIGURATION_MASK       0x001F

/* Pre-430 legacy defines */
#define CEIDEV_FIRST_CEI830_CONFIG CEIDEV_CONFIG_CEI830
#define CEIDEV_LAST_CEI830_CONFIG CEIDEV_CONFIG_CEI830

/*===========================================================================*
 * External API Usage - Device Description Definitions and Structures
 *===========================================================================*

 *----------------------------------------------------------------------------*
 *  Utility return status codes
 *----------------------------------------------------------------------------*
 *  IMPORTANT NOTE: These constants mirror those defined in INTERFACE.H for 
 *                  the IP-Avionics BusTools/LabVIEW error definitions.
 *----------------------------------------------------------------------------*/

#define ARS_FAILURE             -1    /* General API routine failed           */
#define ARS_NODATA               0    /* No data returned from "get" routine  */
#define ARS_NORMAL               1    /* Normal successful completion         */
#define ARS_MOREDATA             3    /* not used                             */
#define ARS_GOTDATA              4    /* Some data returned from "get" routine*/
#define ARS_BAD_MESSAGE          5    /* Invalid ARINC 429 message detected   */
#define ARS_INVHARCMD         1002    /* Requested operation not supported    */
#define ARS_INVHARVAL         1003    /* Specified attribute was invalid      */
#define ARS_XMITOVRFLO        1004    /* Transmit buffer overflow             */
#define ARS_INVBOARD          1005    /* Invalid device ID was specified      */
#define ARS_NOSYNC            1006    /* Transmitter flush failed completion  */
#define ARS_BADLOAD           1007    /* Device firmware load failed          */
#define ARS_BRDNOTLOAD        1008    /* not used                             */
#define ARS_SYNCTIMEOUT       1009    /* not used                             */
#define ARS_SYNCOVERRUN       1010    /* not used                             */
#define ARS_BADINIT           1011    /* not used                             */
#define ARS_MEMADERR          1012    /* not used                             */
#define ARS_MEMWRERR          1013    /* Memory Test failure                  */
#define ARS_INVSTRING         1014    /* not used                             */
#define ARS_INVEQID           1015    /* not used                             */
#define ARS_CHECKSUM          1016    /* not used                             */
#define ARS_NORESPONSE        1017    /* not used                             */
#define ARS_UNSUPTYPE         1018    /* not used                             */
#define ARS_INVARG            1019    /* Specified function arg was invalid   */
#define ARS_INVLABEL          1020    /* not used                             */
#define ARS_DRIVERFAIL        1021    /* Generic dev driver session open fail */
#define ARS_WINRTFAIL         1022    /* Obsolete WinRT device driver failure */
#define ARS_CHAN_TIMEOUT      1023    /* Time out while waiting for data      */
#define ARS_NO_HW_SUPRT       1024    /* Function not supported by hardware   */
#define ARS_BAD_DAC_VAL       1025    /* Specified DAC value bad (<0 or >255) */
#define ARS_BAD_FPGA          1026    /* Bad num of transmitters or receivers */
#define ARS_BAD_STATIC        1027    /* Internal memory read/write failure   */
#define ARS_LAST_ERROR        1028    /* Returns addn'l info about prev error */
#define ARS_HW_CONSISTENCY    1029    /* Hardware config is not consistant    */
#define ARS_HW_DETECT         1030    /* Failed to detect CEI-xxx hardware    */
#define ARS_WRAP_DATA_FAIL    1031    /* Internal wrap test data failure      */ 
#define ARS_WRAP_RATE_FAIL    1032    /* Wrap Test timetag/baud rate mismatch */
#define ARS_SHORT_DATA_FRAME  1033    /* Incomplete ARINC-708 data frame      */
#define ARS_LONG_DATA_FRAME   1034    /* Too much data in ARINC-708 frame     */
#define ARS_WRAP_FLUSH_FAIL   1035    /* BIT cannot execute due to extern rx  */
#define ARS_WRAP_DROP_FAIL    1036    /* Wrap Test missing data failure       */
#define ARS_INT_ISR           1037    /* Failed to install/uninstall ISR      */
#define ARS_BOARD_MUTEX       1038    /* Failed to acquire/release board lock */
#define ARS_CONFIG_MUTEX      1039    /* Failed to acquire/release cfg lock   */
#define ARS_NOT_SUPPORTED     1040    /* Requested feature not supported      */
#define ARS_NO_OS_SUPPORT     1041    /* No oper sys support for req feature  */
#define ARS_NOT_EXCLUSIVE     1042    /* Cannot grant exclusive load request  */
#define ARS_NO_INT_SUPPORT    1043    /* Interrupt handling not supported     */
#define ARS_NO_INT_ENABLED    1044    /* Interrupt handling not enabled       */
#define ARS_ISR_ALREADY_INST  1045    /* Another proc already installed ISR   */
#define ARS_THREAD_WAITING    1046    /* Already thread waiting for rcv data  */
#define ARS_WAIT_FAILED       1047    /* Failed to wait for rcv data          */
#define ARS_SIGNAL_FAILED     1048    /* Failed to signal waiting thread      */
#define ARS_CHANNEL_TYPE      1049    /* Invalid channel type for req func    */
#define ARS_ERR_SH_MEM_OBJ    1050    /* Failed to allocate shared mem region */
#define ARS_ERR_SH_MEM_MAP    1051    /* Failed to allocate shared mem region */
#define ARS_FW_NOT_SUPPORTED  1052    /* The f/w on board is API-incompatible */

#define INTFC_BASE_ERR_CODES  1900

/*------------------------------------------------------------------------* 
 * General Function Constants used for various things
 *------------------------------------------------------------------------*/
#define EXIT_KEY                   27    /* ASCII <ESC> key for exit            */

#ifndef TRUE
#define TRUE                       1
#define FALSE                      0
#endif

#define ARU_ENABLE_TIMETAG         1     /* Enable receiver time tagging         */
#define ARU_DISABLE_TIMETAG        0     /* Disable receiver time tagging        */
#define ARU_ENABLE_INT             1     /* Enable interrupts to the host        */
#define ARU_DISABLE_INT            2     /* Disable interrupts to the host       */
#define ARU_RECEIVER               0     /* Apply parameter to receiver          */
#define ARU_TRANSMITTER            1     /* Apply parameter to transmitter       */
#define ARU_SCHED_MSG_INFINITE     CEIDEV_MSG_SCHEDULER_TX_ALWAYS
#define CHAN_NOT_IMPLEMENTED       0x00  /* Channel is not implemented           */
#define CHAN_ARINC429              0x01  /* Channel is an ARINC-429 channel      */
#define CHAN_ARINC717              0x02  /* Channel is an ARINC-573/717 channel  */
#define ARU_PARAMETRIC_SUPPORT     170  /* H/W supports variable parametrics?   */

#define INTERNAL                   0
#define EXTERNAL                   1
#define EXIT_ROUTINE               9999

/* Time-tag source selection "timeSource" parm, used with internal routine a429_utl_acquire_formatted_time_tag */
#define AR_TIMER_REGISTER_SET          0   /* 64-bit time value source is the CEI-x30 internal timer registers */
#define AR_RECEIVER_FIFO_TIMETAG       1   /* 64-bit time value source is the specified Rx channel time-stamp  */
#define AR_BYPASS_TIMER_READ           2   /* used by arx30_getblock_t to force a single IRIG sample translation  */

/* Time-tag format selection "timeTagFormat" parm, used with internal routine a429_utl_acquire_formatted_time_tag,
 * as well as selective use in conjunction with the ARU_RX_TIMETAG_MODE by the following CEI-x30 API routines:
 *   arx30_get_config
 *   arx30_get_device_config
 *   arx30_get_time
 *   arx30_set_config
 *   arx30_set_device_config
 *   arx30_set_time
 */
#define AR_TIMETAG_EXT_IRIG_64BIT      0   /* convert the timer/time-stamp to ext IRIG terms, 64-bit 1usec */
#define AR_TIMETAG_INT_USEC_64BIT      1   /* leave the timer/time-stamp value in standard 64-bit 1usec format */
#define AR_TIMETAG_HOST_USEC_64BIT     2   /* supported by arx30_get_time only, returns host o/s time as 64-bit 1usec */
#define AR_TIMETAG_INT_20USEC_32BIT    3   /* convert the timer/time-stamp value to 32-bit 20usec resolution */
#define AR_TIMETAG_INT_MSEC_32BIT      4   /* convert the timer/time-stamp value to 32-bit 1msec resolution */
#define AR_TIMETAG_EXT_IRIG_REF_64BIT  5   /* used only to determine the validity of an ext IRIG timer source */
#define AR_TIMER_X20_COMPAT_32BIT      6   /* convert the timer/time-stamp to a 32-bit app programmable resolution */
#define AR_TIMETAG_HOST_SEC_32BIT      7   /* supported by arx30_get_time only, returns host o/s time as 32-bit 1sec */
#define AR_TIMETAG_REF_IRIG_64BIT      8   /* used by arx30_getblock_t to ref a single IRIG sample for time conversion  */
#define AR_LOG_EXT_IRIG_SAMPLE         9   /* convert the current IRIG sample to 64-bit 1usec w/no extrapolation */
#define AR_TIMETAG_EXT_IRIG_RAW        10  /* return the current raw 30-bit IRIG sample value with no conversion */
#define AR_TIMETAG_SYNC_1553_CH1       11  /* combo board only, convert the timer/time-stamp to 1553 chan 1 terms, 64-bit 1usec */
#define AR_TIMETAG_SYNC_1553_CH2       12  /* combo board only, convert the timer/time-stamp to 1553 chan 2 terms, 64-bit 1usec */
#define AR_TIMETAG_SYNC_1553_CH3       13  /* combo board only, convert the timer/time-stamp to 1553 chan 3 terms, 64-bit 1usec */
#define AR_TIMETAG_SYNC_1553_CH4       14  /* combo board only, convert the timer/time-stamp to 1553 chan 4 terms, 64-bit 1usec */
#define AR_TIMETAG_LAST_OPTION         (CEI_INT32)(AR_TIMETAG_SYNC_1553_CH4+1)
#define AR_DEFAULT_RECEIVE_DATA_TIMETAG_FORMAT   AR_TIMETAG_INT_MSEC_32BIT

#if defined (_LINUX_X86_) || defined (_LINUX_PPC_)
   #define AR_MAX_TIMETAG_VALUE           (TIME_TAG_TYPE)0xFFFFFFFFFFFFFFFFULL 
   #define AR_X20_MAX_TIMETAG_VALUE       (TIME_TAG_TYPE)0x3FFFFFFFFFFFFFFFULL
   #define AR_IRIG_ROLLOVER_NON_LEAP_YEAR (TIME_TAG_TYPE)(31536000000000ULL)
   #define AR_IRIG_ROLLOVER_LEAP_YEAR     (TIME_TAG_TYPE)(31622400000000ULL)
#else
   #define AR_MAX_TIMETAG_VALUE           (TIME_TAG_TYPE)0xFFFFFFFFFFFFFFFF
   #define AR_X20_MAX_TIMETAG_VALUE       (TIME_TAG_TYPE)0x3FFFFFFFFFFFFFFF
   #define AR_IRIG_ROLLOVER_NON_LEAP_YEAR (TIME_TAG_TYPE)31536000000000
   #define AR_IRIG_ROLLOVER_LEAP_YEAR     (TIME_TAG_TYPE)31622400000000
#endif

#define AR_IRIG_TIMETAG_BIAS           (TIME_TAG_TYPE)1010000
#define AR_X20_SCALE_TIMETAG_VALUE     (TIME_TAG_TYPE)4
#define AR_X20_QTR_MICROSEC_PER_MSEC   (CEI_UINT32)4000
#define AR_MICROSECONDS_PER_SECOND     (TIME_TAG_TYPE)(1000000)
#define AR_MICROSEC_PER_MILLISEC       (TIME_TAG_TYPE)(1000)
#define AR_SECONDS_PER_DAY             86400
#define AR_LOCAL_TIME_YEAR_BASIS       1900
#define AR_LEAP_YEAR_DIVISOR           4
#define AR_LEAP_YEAR_EXCEPTION         2100

/* Receive Channel Status bits used to indicate channel status in arx30_get_rx_channel_status() */
#define AR_BUFFER_MSG_AVAILABLE        1
#define AR_INVALID_MSG_DETECTED        2
#define AR_BUFFER_OVERFLOW_DETECTED    4


/* Time-tag string conversion format selection and array size */
#define AR_TD_DATE                 0
#define AR_TD_IRIG                 1
#define AR_TD_REL_MIDNIGHT         2
#define AR_TD_STRING_SIZE          24

/* BIT execution selection */
#define AR_BIT_BASIC_STARTUP       0
#define AR_BIT_FULL_STARTUP        1
#define AR_BIT_PERIODIC            2
#define AR_BIT_INT_LOOPBACK        3
#define AR_BIT_EXT_LOOPBACK        4
#define AR_BIT_PARTIAL_SRAM        8
#define AR_BIT_FULL_SRAM           9
#define AR_BIT_SELECT_SRAM_MIN     100
#define AR_BIT_SELECT_SRAM_MAX     1123

/* the following constants are used with the function ceidev_memory_test() */
#define FULL_SRAM                  0
#define UNUSED_SRAM                1
#define SELECT_SRAM                2
#define MSG_SCHEDULE_TABLE         3

/* the following constants are used with the function arx30_board_test() */
#define EXTERNAL_WRAP              0
#define INTERNAL_WRAP              1

#define BAUD_100_TIMETAG_DEV       18
#define BAUD_125_TIMETAG_DEV       144
#define BAUD_11_TIMETAG_DEV        150

#define MAX_OUTPUT_DISCRETES       4
#define MAX_DIGITAL_OUTPUT         12
#define MAX_DIGITAL_INPUT          4

/* the following constants are used with the function arx30_set_storage_mode() */
#define ARU_BUFFERED               0
#define ARU_DEDICATED              1
#define ARU_MERGED                 2

/* the following constants are used with the function arx30_set_transmitter_mode() */
#define ARU_XMIT_573_HBP           1
#define ARU_XMIT_573_BPRZ          2

/* channel set/get config internal validation definitions */
#define ARU_GET_DATA               34
#define ARU_PUT_DATA               35
#define ARU_FILTER_LABEL           36
#define ARU_ENHANCED_FILTER_LABEL  37
#define ARU_ADD_SCHEDULED_MSG      39

/* the following constants are used with the function arx30_label_filter()      */
#define ARU_ALL_LABELS             0x1FF /* Enable/disable ALL label filtering  */
#define ARU_ALL_SDI                4     /* Enable/disable all sdi filtering for this label */
#define ARU_ALL_ESSM               8     /* Enable/disable all ssm filtering for this label */
#define ARU_FILTER_OFF             0     /* Filter off--pass specified label(s) */
#define ARU_FILTER_ON              1     /* Filter on--delete specified label(s)*/
#define FILTER_SEQUENTIAL          0x10
#define FILTER_SNAPSHOT            0x20
#define FILTER_INTERRUPT           0x40
#define ARINC_LABEL_SDI_MASK       0x000003ff
#define ARINC_LABEL_MASK           0x000000ff
#define ARINC_SDI_MASK             0x00000300

#define PARITY_BIT                 0x80000000
#define DATA_BITS                  0x7FFFFFFF
#define MERGED_CHANNEL_MASK        (TIME_TAG_TYPE)0x7FFFFFF
#define MERGED_CHANNEL_SHIFT       27
#define A573_AUTOSYNC_TIMEOUT      1000
#define A573_RAW_TIMEOUT           2

/*---------------------------------------------------------------------------*
 *  This set of configuration constants are specifically used with calls to 
 *  satisfy the LabVIEW VIs and LabWindows/CVI Applications.  Invocations of
 *  arx30_set_arinc_config() (in INTERFACE.DLL) are translated by the function
 *  arx30_set_device_config() within the API DLL.  Direct access to this
 *  DLL should use this function with the following constants or use
 *  arx30_set_config() using other constants defined below.
 *---------------------------------------------------------------------------*/
#define ARU_RX_BITRATE               1
#define ARU_RX_PARITY                3
#define ARU_RECV_MODE                5
#define ARU_RX_STORAGE_MODE          7
#define ARU_RX_DISABLE               9
                                     
#define ARU_TX_BITRATE               2
#define ARU_TX_PARITY                4
#define ARU_TX_BIT_ERROR             6
#define ARU_TX_GAP_ERROR             8
#define ARU_TX_DISABLE               10

/* arx30_set_raw_mode channel types */
#define ARU_XMIT                     34
#define ARU_RECV                     35
#define TRANSMIT_CHANNEL             0
#define RECEIVE_CHANNEL              1

/*---------------------------------------------------------------------------*
 *  This set of configuration "value parameter" constants are used with calls 
 *  to either the function arx30_set_config() or arx30_set_device_config()
 *---------------------------------------------------------------------------*/
#define AR_WRAP_ON                   0  /* Receiver Internal wrap enable        */
#define AR_WRAP_OFF                  1  /* Receiver Internal wrap disable       */
#define AR_ON                        7  /* General "Enable" flag                */
#define AR_OFF                       8  /* General "Disable" flag               */
#define AR_LO                        0  /* Discrete & digital I/O states        */
#define AR_HI                        1  
#define AR_RAW                       0x2000
#define AR_BIT_HIGH                  1
#define AR_BIT_LOW                   2
#define AR_SHORT_GAP                 3
#define AR_PE_NONE                   4
                                     
#define ARU_SPEED_HIGH               0  /* Bus speed fixed 100Kbps assignment   */
#define ARU_SPEED_LOW                1  /* Bus speed fixed 12.5Kbps assignment  */
#define AR_HIGH                      0  /* Used to set HIGH speed (100 Kbaud)      */
#define AR_LOW                       1  /* Used to set LOW speed (12.5 Kbaud)      */
#define ARU_PARITY_ODD               0  
#define AR_ODD                       0
#define ARU_PARITY_EVEN              1
#define AR_EVEN                      1
#define ARU_PARITY_NONE              2
#define AR_RAW                       0x2000

#define ARU_LABEL_ONLY               0
#define ARU_LABEL_WITH_SDI           1

/*----------------------------------------------------------------------------*
 * arx30_set_preload_config constants
 * used along with ON/OFF in arx30_set_multithread_protect
 *----------------------------------------------------------------------------*/
#define ARU_CONCURRENCY_MODE         1
#define ARU_INSTALL_INT_HANDLER      2
#define AR_CONC_NONE                 0
#define AR_CONC_MULTITHRD            1
#define AR_CONC_MULTIPROC            2

/*---------------------------------------------------------------------------*
 *  This set of configuration constants are specifically used for the 
 *  "item" parameter with invocations to the arx30_set/get_config() and 
 *  arx30_set/get_device_config() functions for CEI-x30-specific operations.
 *---------------------------------------------------------------------------*/
#define ARU_CHANNEL_ENABLE            11
#define ARU_DISCRETE_OUT              12
#define ARU_DIGITAL_OUT               13
#define ARU_DISCRETE_IN               14
#define ARU_DIGITAL_IN                15
#define ARU_RX_FIFO_ENABLE            16
#define ARU_TX_FIFO_ENABLE            17
#define ARU_RX_MERGED_MODE            18
#define ARU_TX_FIFO_COUNT             19
#define ARU_FW_VERSION                20
#define ARU_CONFIGURATION             21
#define ARU_DIFFERENTIAL_IN           22
#define ARU_DIFFERENTIAL_OUT          23
#define ARU_RX_RESET                  24
#define ARU_TX_RESET                  25
#define ARU_IRIG_OUTPUT_ENABLE        26
#define ARU_IRIG_INPUT_TIME           27
#define ARU_RX_FIFO_COUNT             28
#define ARU_HW_INTERRUPT_ENABLE       29
#define ARU_HW_ENHANCE_CHECK          30
#define ARU_HW_ENHANCE_UPDATE         31
#define ARU_BYPASS_FW_LOAD            32
#define ARU_WAIT_ON_EVENT             33
#define ARU_RX_MSG_COUNT              35
#define ARU_TX_MSG_COUNT              36
#define ARU_INSERT_INT_Q_ENTRY        37
#define ARU_ACCESS_SNAPSHOT_BUFFER    38
#define ARU_DEVICE_DISABLE            39

#define ARU_DISCRETE_IN1             260
#define ARU_DISCRETE_IN2             261
#define ARU_DISCRETE_IN3             262
#define ARU_DISCRETE_IN4             263
#define ARU_DIGITAL_IN1              264
#define ARU_DIGITAL_IN2              265
#define ARU_DIGITAL_IN3              266
#define ARU_DIGITAL_IN4              267
#define ARU_DISCRETE_OUT1            268
#define ARU_DISCRETE_OUT2            269
#define ARU_DISCRETE_OUT3            270
#define ARU_DISCRETE_OUT4            271
#define ARU_DIGITAL_OUT1             272
#define ARU_DIGITAL_OUT2             273
#define ARU_DIGITAL_OUT3             274
#define ARU_DIGITAL_OUT4             275
#define ARU_DIGITAL_OUT5             276
#define ARU_DIGITAL_OUT6             277
#define ARU_DIGITAL_OUT7             278
#define ARU_DIGITAL_OUT8             279
#define ARU_DIGITAL_OUT9             280
#define ARU_DIGITAL_OUT10            281
#define ARU_DIGITAL_OUT11            282
#define ARU_DIGITAL_OUT12            283

#define ARU_BYPASS_INIT_WRAP_TEST    320
#define ARU_MULTITHREAD_PROTECT      321
#define ARU_DISCRETE_RAW             322
#define ARU_FAST_SLEW_RATE           323

#define ARU_RX_TIMETAG_MODE          440
#define ARU_IRIG_WRAP_ENABLE         441           
#define ARU_IRIG_INPUT_THRESHOLD     442
#define ARU_IRIG_ADJUST_THRESHOLD    443
#define ARU_IRIG_QUICK_ADJUSTMENT    444
#define ARU_IRIG_AVAILABLE           445
#define ARU_IRIG_SET_BIAS            446
#define ARU_IRIG_CALIBRATED          447
#define ARU_CHAN_COUNT_429           448
#define ARU_CHAN_COUNT_573           449
#define ARU_CHAN_COUNT_DISC          450
#define ARU_CHAN_COUNT_DIFF          451
#define ARU_SERIAL_NUMBER            452
#define ARU_HW_FPGA_TEMPERATURE      453
#define ARU_HW_1PT0V_PWR_SUPPLY      454
#define ARU_HW_2PT5V_PWR_SUPPLY      455


                                     
/*---------------------------------------------------------------------------*
 *  This HUGE set of configuration constants are specifically used for the 
 *  "item" parameter with invocations to arx30_set_config() to satisfy the board
 *  -level configuration usage with BusTools/ARINC and CEI-x20 interfaces.
 *---------------------------------------------------------------------------*/
#define ARU_XMIT_RATE                1 /* AR_SPEED_HIGH/_LOW for 100/12.5 Kb    */
#define ARU_RECV_RATE                2 /* AR_SPEED_HIGH/_LOW for 100/12.5 Kb    */
#define ARU_PARITY                   3 /* To assign all channels AR_PARITY_**** */
#define ARU_INTERNAL_WRAP            4 /* Internal wrap a single 429 channel    */
#define ARU_EXTERNAL_WRAP            5 /* External wrap a single 429 channel    */

#define ARU_RX_CH01_BIT_RATE         500 /* Configure receive ch one bit rate    */
#define ARU_RX_CH02_BIT_RATE         501 /* AR_HIGH or AR_LOW                    */
#define ARU_RX_CH03_BIT_RATE         502 /* AR_HIGH or AR_LOW select 100Kbaud    */
#define ARU_RX_CH04_BIT_RATE         503 /*  and 12.5 Kbaud respectively.        */
#define ARU_RX_CH05_BIT_RATE         504
#define ARU_RX_CH06_BIT_RATE         505
#define ARU_RX_CH07_BIT_RATE         506
#define ARU_RX_CH08_BIT_RATE         507
#define ARU_RX_CH09_BIT_RATE         508
#define ARU_RX_CH10_BIT_RATE         509
#define ARU_RX_CH11_BIT_RATE         510
#define ARU_RX_CH12_BIT_RATE         511
#define ARU_RX_CH13_BIT_RATE         512
#define ARU_RX_CH14_BIT_RATE         513
#define ARU_RX_CH15_BIT_RATE         514
#define ARU_RX_CH16_BIT_RATE         515
#define ARU_RX_CH17_BIT_RATE         516
#define ARU_RX_CH18_BIT_RATE         517
#define ARU_RX_CH19_BIT_RATE         518
#define ARU_RX_CH20_BIT_RATE         519
#define ARU_RX_CH21_BIT_RATE         520
#define ARU_RX_CH22_BIT_RATE         521
#define ARU_RX_CH23_BIT_RATE         522
#define ARU_RX_CH24_BIT_RATE         523
#define ARU_RX_CH25_BIT_RATE         524
#define ARU_RX_CH26_BIT_RATE         525
#define ARU_RX_CH27_BIT_RATE         526
#define ARU_RX_CH28_BIT_RATE         527
#define ARU_RX_CH29_BIT_RATE         528
#define ARU_RX_CH30_BIT_RATE         529
#define ARU_RX_CH31_BIT_RATE         530
#define ARU_RX_CH32_BIT_RATE         531

#define ARU_TX_CH01_BIT_RATE         700 /* Configure transmit ch one bit rate   */
#define ARU_TX_CH02_BIT_RATE         701 /* AR_HIGH or AR_LOW select 100Kbaud    */
#define ARU_TX_CH03_BIT_RATE         702 /*  and 12.5 Kbaud respectively.        */
#define ARU_TX_CH04_BIT_RATE         703
#define ARU_TX_CH05_BIT_RATE         704
#define ARU_TX_CH06_BIT_RATE         705
#define ARU_TX_CH07_BIT_RATE         706
#define ARU_TX_CH08_BIT_RATE         707
#define ARU_TX_CH09_BIT_RATE         708
#define ARU_TX_CH10_BIT_RATE         709
#define ARU_TX_CH11_BIT_RATE         710
#define ARU_TX_CH12_BIT_RATE         711
#define ARU_TX_CH13_BIT_RATE         712
#define ARU_TX_CH14_BIT_RATE         713
#define ARU_TX_CH15_BIT_RATE         714
#define ARU_TX_CH16_BIT_RATE         715
#define ARU_TX_CH17_BIT_RATE         716
#define ARU_TX_CH18_BIT_RATE         717
#define ARU_TX_CH19_BIT_RATE         718
#define ARU_TX_CH20_BIT_RATE         719
#define ARU_TX_CH21_BIT_RATE         720
#define ARU_TX_CH22_BIT_RATE         721
#define ARU_TX_CH23_BIT_RATE         722
#define ARU_TX_CH24_BIT_RATE         723
#define ARU_TX_CH25_BIT_RATE         724
#define ARU_TX_CH26_BIT_RATE         725
#define ARU_TX_CH27_BIT_RATE         726
#define ARU_TX_CH28_BIT_RATE         727
#define ARU_TX_CH29_BIT_RATE         728
#define ARU_TX_CH30_BIT_RATE         729
#define ARU_TX_CH31_BIT_RATE         730
#define ARU_TX_CH32_BIT_RATE         731
                                     
#define ARU_RX_CH01_PARITY           900 /* Configure receive ch one parity     */
#define ARU_RX_CH02_PARITY           901 /* Parity detection AR_ON or AR_OFF    */
#define ARU_RX_CH03_PARITY           902 /* Defaults to AR_ON, where parity     */
#define ARU_RX_CH04_PARITY           903 /*  detection is enabled.              */
#define ARU_RX_CH05_PARITY           904 /* If parity enabled, MSB of received  */
#define ARU_RX_CH06_PARITY           905 /*  word is 1 if odd parity detected,  */
#define ARU_RX_CH07_PARITY           906 /*  and 0 if even parity was detected. */
#define ARU_RX_CH08_PARITY           907 
#define ARU_RX_CH09_PARITY           908
#define ARU_RX_CH10_PARITY           909
#define ARU_RX_CH11_PARITY           910
#define ARU_RX_CH12_PARITY           911
#define ARU_RX_CH13_PARITY           912
#define ARU_RX_CH14_PARITY           913
#define ARU_RX_CH15_PARITY           914
#define ARU_RX_CH16_PARITY           915
#define ARU_RX_CH17_PARITY           916
#define ARU_RX_CH18_PARITY           917
#define ARU_RX_CH19_PARITY           918
#define ARU_RX_CH20_PARITY           919
#define ARU_RX_CH21_PARITY           920
#define ARU_RX_CH22_PARITY           921
#define ARU_RX_CH23_PARITY           922
#define ARU_RX_CH24_PARITY           923
#define ARU_RX_CH25_PARITY           924
#define ARU_RX_CH26_PARITY           925
#define ARU_RX_CH27_PARITY           926
#define ARU_RX_CH28_PARITY           927
#define ARU_RX_CH29_PARITY           928
#define ARU_RX_CH30_PARITY           929
#define ARU_RX_CH31_PARITY           930
#define ARU_RX_CH32_PARITY           931
                                     
#define ARU_TX_CH01_PARITY           1100 /* Configure transmit ch one parity   */
#define ARU_TX_CH02_PARITY           1101 /* ARU_PARITY_ODD, ARU_PARITY_EVEN or */
#define ARU_TX_CH03_PARITY           1102 /*   ARU_PARITY_NONE (or AR_OFF)      */
#define ARU_TX_CH04_PARITY           1103 /* Defaults to ARU_PARITY_ODD         */
#define ARU_TX_CH05_PARITY           1104 /* If parity enabled, MSB of transmit */
#define ARU_TX_CH06_PARITY           1105 /*  word is overwritten with the      */
#define ARU_TX_CH07_PARITY           1106 /*  parity bit value calculated by hw.*/
#define ARU_TX_CH08_PARITY           1107
#define ARU_TX_CH09_PARITY           1108
#define ARU_TX_CH10_PARITY           1109
#define ARU_TX_CH11_PARITY           1110
#define ARU_TX_CH12_PARITY           1111
#define ARU_TX_CH13_PARITY           1112
#define ARU_TX_CH14_PARITY           1113
#define ARU_TX_CH15_PARITY           1114
#define ARU_TX_CH16_PARITY           1115
#define ARU_TX_CH17_PARITY           1116
#define ARU_TX_CH18_PARITY           1117
#define ARU_TX_CH19_PARITY           1118
#define ARU_TX_CH20_PARITY           1119
#define ARU_TX_CH21_PARITY           1120
#define ARU_TX_CH22_PARITY           1121
#define ARU_TX_CH23_PARITY           1122
#define ARU_TX_CH24_PARITY           1123
#define ARU_TX_CH25_PARITY           1124
#define ARU_TX_CH26_PARITY           1125
#define ARU_TX_CH27_PARITY           1126
#define ARU_TX_CH28_PARITY           1127
#define ARU_TX_CH29_PARITY           1128
#define ARU_TX_CH30_PARITY           1129
#define ARU_TX_CH31_PARITY           1130
#define ARU_TX_CH32_PARITY           1131
                                 
#define ARU_RX_CH01_SDI_FILTER       1300  /* Enable SDI prefilter ch 1           */
#define ARU_RX_CH02_SDI_FILTER       1301  /* AR_ON or AR_OFF                     */
#define ARU_RX_CH03_SDI_FILTER       1302
#define ARU_RX_CH04_SDI_FILTER       1303
#define ARU_RX_CH05_SDI_FILTER       1304
#define ARU_RX_CH06_SDI_FILTER       1305
#define ARU_RX_CH07_SDI_FILTER       1306
#define ARU_RX_CH08_SDI_FILTER       1307
#define ARU_RX_CH09_SDI_FILTER       1308
#define ARU_RX_CH10_SDI_FILTER       1309
#define ARU_RX_CH11_SDI_FILTER       1310
#define ARU_RX_CH12_SDI_FILTER       1311
#define ARU_RX_CH13_SDI_FILTER       1312
#define ARU_RX_CH14_SDI_FILTER       1313
#define ARU_RX_CH15_SDI_FILTER       1314
#define ARU_RX_CH16_SDI_FILTER       1315
#define ARU_RX_CH17_SDI_FILTER       1316
#define ARU_RX_CH18_SDI_FILTER       1317
#define ARU_RX_CH19_SDI_FILTER       1318
#define ARU_RX_CH20_SDI_FILTER       1319
#define ARU_RX_CH21_SDI_FILTER       1320
#define ARU_RX_CH22_SDI_FILTER       1321
#define ARU_RX_CH23_SDI_FILTER       1322
#define ARU_RX_CH24_SDI_FILTER       1323
#define ARU_RX_CH25_SDI_FILTER       1324
#define ARU_RX_CH26_SDI_FILTER       1325
#define ARU_RX_CH27_SDI_FILTER       1326
#define ARU_RX_CH28_SDI_FILTER       1327
#define ARU_RX_CH29_SDI_FILTER       1328
#define ARU_RX_CH30_SDI_FILTER       1329
#define ARU_RX_CH31_SDI_FILTER       1330
#define ARU_RX_CH32_SDI_FILTER       1331
                                 
#define ARU_RX_CH01_SDI_VALUE        1500  /* SDI prefilter value for ch 1 (0-3)  */
#define ARU_RX_CH02_SDI_VALUE        1501
#define ARU_RX_CH03_SDI_VALUE        1502
#define ARU_RX_CH04_SDI_VALUE        1503
#define ARU_RX_CH05_SDI_VALUE        1504
#define ARU_RX_CH06_SDI_VALUE        1505
#define ARU_RX_CH07_SDI_VALUE        1506
#define ARU_RX_CH08_SDI_VALUE        1507
#define ARU_RX_CH09_SDI_VALUE        1508
#define ARU_RX_CH10_SDI_VALUE        1509
#define ARU_RX_CH11_SDI_VALUE        1510
#define ARU_RX_CH12_SDI_VALUE        1511
#define ARU_RX_CH13_SDI_VALUE        1512
#define ARU_RX_CH14_SDI_VALUE        1513
#define ARU_RX_CH15_SDI_VALUE        1514
#define ARU_RX_CH16_SDI_VALUE        1515
#define ARU_RX_CH17_SDI_VALUE        1516
#define ARU_RX_CH18_SDI_VALUE        1517
#define ARU_RX_CH19_SDI_VALUE        1518
#define ARU_RX_CH20_SDI_VALUE        1519
#define ARU_RX_CH21_SDI_VALUE        1520
#define ARU_RX_CH22_SDI_VALUE        1521
#define ARU_RX_CH23_SDI_VALUE        1522
#define ARU_RX_CH24_SDI_VALUE        1523
#define ARU_RX_CH25_SDI_VALUE        1524
#define ARU_RX_CH26_SDI_VALUE        1525
#define ARU_RX_CH27_SDI_VALUE        1526
#define ARU_RX_CH28_SDI_VALUE        1527
#define ARU_RX_CH29_SDI_VALUE        1528
#define ARU_RX_CH30_SDI_VALUE        1529
#define ARU_RX_CH31_SDI_VALUE        1530
#define ARU_RX_CH32_SDI_VALUE        1531
                                          /* DAC values to read or write          */
#define ARU_RX1_4_THRESH_VALUE       160  /* Thresh = 10 * (2.5 - Vdac)           */
#define ARU_RX5_8_THRESH_VALUE       161  /* Vdac = 5 * n / 256 Volts             */
#define ARU_RX9_10_THRESH_VALUE      162  /* Thresh = 0x72 = 2.73 Volts default   */
#define ARU_RX11_12_THRESH_VALUE     163
#define ARU_INPUT_THRESH_VALUE       164  /* Thresh = 20 * n / 256 Volts = 1.56V  */
#define ARU_TRANSMIT_VOLT_VALUE      165  /* Level  = 10 * n / 256 Volts = 9.96V  */
                                     
#define ARU_PARAMETERIC_SUPPORT      170  /* H/W supports variable parametrics?   */
                                          /* This includes Rcvr Thresh Adj, Xmt   */
                                          /*  Output Adj and Extra/Too Few bits   */
                                          /* Returns AR_ON or AR_OFF              */
                                     
#define ARU_DISCRETE_VALUES          175  /* Read/Write Discrete Inputs/Outputs   */
                                          /* Discretes are active high.           */
#define ARU_DISCRETE_OUTPUTS         176  /* Read/Write discrete output values    */
#define ARU_DISCRETE_INPUTS          177  /* Read discrete input values           */

#define ARU_TX_CH01_SHUT_OFF         1700  /* Shut off the ARINC transmitter       */
#define ARU_TX_CH02_SHUT_OFF         1701  /* AR_ON or AR_OFF                      */
#define ARU_TX_CH03_SHUT_OFF         1702  /* AR_ON turns the transmitter OFF      */
#define ARU_TX_CH04_SHUT_OFF         1703
#define ARU_TX_CH05_SHUT_OFF         1704
#define ARU_TX_CH06_SHUT_OFF         1705
#define ARU_TX_CH07_SHUT_OFF         1706
#define ARU_TX_CH08_SHUT_OFF         1707
#define ARU_TX_CH09_SHUT_OFF         1708
#define ARU_TX_CH10_SHUT_OFF         1709
#define ARU_TX_CH11_SHUT_OFF         1710
#define ARU_TX_CH12_SHUT_OFF         1711
#define ARU_TX_CH13_SHUT_OFF         1712
#define ARU_TX_CH14_SHUT_OFF         1713
#define ARU_TX_CH15_SHUT_OFF         1714
#define ARU_TX_CH16_SHUT_OFF         1715
#define ARU_TX_CH17_SHUT_OFF         1716  
#define ARU_TX_CH18_SHUT_OFF         1717  
#define ARU_TX_CH19_SHUT_OFF         1718  
#define ARU_TX_CH20_SHUT_OFF         1719
#define ARU_TX_CH21_SHUT_OFF         1720
#define ARU_TX_CH22_SHUT_OFF         1721
#define ARU_TX_CH23_SHUT_OFF         1722
#define ARU_TX_CH24_SHUT_OFF         1723
#define ARU_TX_CH25_SHUT_OFF         1724
#define ARU_TX_CH26_SHUT_OFF         1725
#define ARU_TX_CH27_SHUT_OFF         1726
#define ARU_TX_CH28_SHUT_OFF         1727
#define ARU_TX_CH29_SHUT_OFF         1728
#define ARU_TX_CH30_SHUT_OFF         1729
#define ARU_TX_CH31_SHUT_OFF         1730
#define ARU_TX_CH32_SHUT_OFF         1731

#define ARU_TX_CH01_HB_INJ           3300  /* Enable Extra Bit error injection     */
#define ARU_TX_CH02_HB_INJ           3301  /* AR_ON or AR_OFF                      */
#define ARU_TX_CH03_HB_INJ           3302  /* This function when enabled increases */
#define ARU_TX_CH04_HB_INJ           3303  /*  the normal number of bits send per  */
#define ARU_TX_CH05_HB_INJ           3304  /*  label from 32 to 33.                */
#define ARU_TX_CH06_HB_INJ           3305
#define ARU_TX_CH07_HB_INJ           3306
#define ARU_TX_CH08_HB_INJ           3307
#define ARU_TX_CH09_HB_INJ           3308
#define ARU_TX_CH10_HB_INJ           3309
#define ARU_TX_CH11_HB_INJ           3310
#define ARU_TX_CH12_HB_INJ           3311
#define ARU_TX_CH13_HB_INJ           3312
#define ARU_TX_CH14_HB_INJ           3313
#define ARU_TX_CH15_HB_INJ           3314
#define ARU_TX_CH16_HB_INJ           3315
#define ARU_TX_CH17_HB_INJ           3316
#define ARU_TX_CH18_HB_INJ           3317
#define ARU_TX_CH19_HB_INJ           3318
#define ARU_TX_CH20_HB_INJ           3319
#define ARU_TX_CH21_HB_INJ           3320
#define ARU_TX_CH22_HB_INJ           3321
#define ARU_TX_CH23_HB_INJ           3322
#define ARU_TX_CH24_HB_INJ           3323
#define ARU_TX_CH25_HB_INJ           3324
#define ARU_TX_CH26_HB_INJ           3325
#define ARU_TX_CH27_HB_INJ           3326
#define ARU_TX_CH28_HB_INJ           3327
#define ARU_TX_CH29_HB_INJ           3328
#define ARU_TX_CH30_HB_INJ           3329
#define ARU_TX_CH31_HB_INJ           3330
#define ARU_TX_CH32_HB_INJ           3331

#define ARU_TX_CH01_LB_INJ           3500  /* Enable Too Few Bits error injection  */
#define ARU_TX_CH02_LB_INJ           3501  /* AR_ON or AR_OFF                      */
#define ARU_TX_CH03_LB_INJ           3502  /* This function when enabled reduces   */
#define ARU_TX_CH04_LB_INJ           3503  /*  the normal number of bits send per  */
#define ARU_TX_CH05_LB_INJ           3504  /*  label from 32 to 31.                */
#define ARU_TX_CH06_LB_INJ           3505
#define ARU_TX_CH07_LB_INJ           3506
#define ARU_TX_CH08_LB_INJ           3507
#define ARU_TX_CH09_LB_INJ           3508
#define ARU_TX_CH10_LB_INJ           3509
#define ARU_TX_CH11_LB_INJ           3510
#define ARU_TX_CH12_LB_INJ           3511
#define ARU_TX_CH13_LB_INJ           3512
#define ARU_TX_CH14_LB_INJ           3513
#define ARU_TX_CH15_LB_INJ           3514
#define ARU_TX_CH16_LB_INJ           3515
#define ARU_TX_CH17_LB_INJ           3516
#define ARU_TX_CH18_LB_INJ           3517
#define ARU_TX_CH19_LB_INJ           3518
#define ARU_TX_CH20_LB_INJ           3519
#define ARU_TX_CH21_LB_INJ           3520
#define ARU_TX_CH22_LB_INJ           3521
#define ARU_TX_CH23_LB_INJ           3522
#define ARU_TX_CH24_LB_INJ           3523
#define ARU_TX_CH25_LB_INJ           3524
#define ARU_TX_CH26_LB_INJ           3525
#define ARU_TX_CH27_LB_INJ           3526
#define ARU_TX_CH28_LB_INJ           3527
#define ARU_TX_CH29_LB_INJ           3528
#define ARU_TX_CH30_LB_INJ           3529
#define ARU_TX_CH31_LB_INJ           3530
#define ARU_TX_CH32_LB_INJ           3531
                                     
#define ARU_TX_CH01_GAP_INJ          3700  /* Enable Short Gap error injection     */
#define ARU_TX_CH02_GAP_INJ          3701  /* AR_ON or AR_OFF                      */
#define ARU_TX_CH03_GAP_INJ          3702  /* This function when enabled reduces   */
#define ARU_TX_CH04_GAP_INJ          3703  /*  the normal 4 bit time gap between   */
#define ARU_TX_CH05_GAP_INJ          3704  /*  labels to 2 bit times.              */
#define ARU_TX_CH06_GAP_INJ          3705
#define ARU_TX_CH07_GAP_INJ          3706
#define ARU_TX_CH08_GAP_INJ          3707
#define ARU_TX_CH09_GAP_INJ          3708
#define ARU_TX_CH10_GAP_INJ          3709
#define ARU_TX_CH11_GAP_INJ          3710
#define ARU_TX_CH12_GAP_INJ          3711
#define ARU_TX_CH13_GAP_INJ          3712
#define ARU_TX_CH14_GAP_INJ          3713
#define ARU_TX_CH15_GAP_INJ          3714
#define ARU_TX_CH16_GAP_INJ          3715
#define ARU_TX_CH17_GAP_INJ          3716
#define ARU_TX_CH18_GAP_INJ          3717
#define ARU_TX_CH19_GAP_INJ          3718
#define ARU_TX_CH20_GAP_INJ          3719
#define ARU_TX_CH21_GAP_INJ          3720
#define ARU_TX_CH22_GAP_INJ          3721
#define ARU_TX_CH23_GAP_INJ          3722
#define ARU_TX_CH24_GAP_INJ          3723
#define ARU_TX_CH25_GAP_INJ          3724
#define ARU_TX_CH26_GAP_INJ          3725
#define ARU_TX_CH27_GAP_INJ          3726
#define ARU_TX_CH28_GAP_INJ          3727
#define ARU_TX_CH29_GAP_INJ          3728
#define ARU_TX_CH30_GAP_INJ          3729
#define ARU_TX_CH31_GAP_INJ          3730
#define ARU_TX_CH32_GAP_INJ          3731

/*---------------------------------------------------------------------------*
 *  This set of configuration constants are specifically used for the 
 *  "item" parameter with invocations to arx30_set_config() to satisfy the 
 *  legacy BusTools/ARINC & CEI-x20 interface.
 *---------------------------------------------------------------------------*/
#define ARU_OLD_RX_CH01_BIT_RATE     40  /* Configure receiver bit rate      */
#define ARU_OLD_RX_CH16_BIT_RATE     55
#define ARU_OLD_TX_CH01_BIT_RATE     60  /* Configure transmitter bit rate   */
#define ARU_OLD_TX_CH16_BIT_RATE     75
#define ARU_OLD_RX_CH01_PARITY       80  /* Configure receiver parity        */
#define ARU_OLD_RX_CH16_PARITY       95
#define ARU_OLD_TX_CH01_PARITY       100 /* Configure transmitter parity     */
#define ARU_OLD_TX_CH16_PARITY       115
#define ARU_OLD_RX_CH01_SDI_FILTER   120 /* Enable SDI prefilter             */
#define ARU_OLD_RX_CH16_SDI_FILTER   135
#define ARU_OLD_RX_CH01_SDI_VALUE    140 /* SDI prefilter value              */ 
#define ARU_OLD_RX_CH16_SDI_VALUE    155
#define ARU_OLD_TX_CH01_HB_INJ       180 /* Enable Extra Bit error inj       */
#define ARU_OLD_TX_CH16_HB_INJ       195
#define ARU_OLD_TX_CH01_LB_INJ       200 /* Enable Too Few Bits error inj    */ 
#define ARU_OLD_TX_CH16_LB_INJ       215
#define ARU_OLD_TX_CH01_GAP_INJ      220 /* Enable Short Gap error inj       */
#define ARU_OLD_TX_CH16_GAP_INJ      235
#define ARU_OLD_TX_CH01_SHUT_OFF     240 /* Shut off the ARINC transmitter   */
#define ARU_OLD_TX_CH16_SHUT_OFF     255


/* ARINC 717/573-specific Item parameters for Set/Get 573 Config */
#define ARU_573_RX_ENABLE            300
#define ARU_573_RX_AUTO_DETECT       301
#define ARU_573_RX_BPRZ_SELECT       302
#define ARU_573_RX_SUBFRAME_SIZE     304
#define ARU_573_TX_SLEW_RATE         305
#define ARU_573_SYNC_WORD1           307
#define ARU_573_SYNC_WORD2           308
#define ARU_573_SYNC_WORD3           309
#define ARU_573_SYNC_WORD4           310
#define ARU_573_TX_BPRZ_SELECT       313
#define ARU_573_TX_HBP_SELECT        314

/* ARINC 573 specific value parameters for Set/Get Config Items */
#define ARU_573_RATE_SIZE_384_32      0
#define ARU_573_RATE_SIZE_768_64      1   
#define ARU_573_RATE_SIZE_1536_128    2    
#define ARU_573_RATE_SIZE_3072_256    3    
#define ARU_573_RATE_SIZE_6144_512    4    
#define ARU_573_RATE_SIZE_12288_1024  5     
#define ARU_573_RATE_SIZE_24576_2048  6
#define ARU_573_RATE_SIZE_49152_4096  7     
#define A717_NUM_SUPPORTED_BUS_SPEEDS 8

#define ARU_573_TX_SLEW_10PT0        0
#define ARU_573_TX_SLEW_1PT5         1

/* These ARINC 573 items are only supported for backward compatibility
 * with the CEI-710 API, as their is no seperate subframe size attribute
 * on this device
 */
#define ARU_573_SPEED_384            384
#define ARU_573_SPEED_768            768
#define ARU_573_SPEED_1536           1536
#define ARU_573_SPEED_3072           3072
#define ARU_573_SPEED_6144           6144
#define ARU_573_SPEED_12288          12288
#define ARU_573_SPEED_24576          24576
#define DEFAULT_BUS_SPEED            ARU_573_SPEED_768

#define ARU_573_SUB_FRAME_32         32
#define ARU_573_SUB_FRAME_64         64
#define ARU_573_SUB_FRAME_128        128
#define ARU_573_SUB_FRAME_256        256
#define ARU_573_SUB_FRAME_512        512
#define ARU_573_SUB_FRAME_1024       1024
#define ARU_573_SUB_FRAME_2048       2048
#define ARU_573_SUB_FRAME_4096       4096

#define DEFAULT_FRAME_SIZE           ARU_573_SUB_FRAME_64
#define ARU_717_AUTOSYNC             0x0000   /* Autosync mode                     */
#define ARU_717_RAW                  0x2000   /* RAW mode                          */
#define ARU_717_H_BI_PHASE           0x2000   /* Harvard Bi-Phase Encoding (HBP)   */
#define ARU_717_BIPOLAR              0x1000   /* Bipolar R-T-Z Encoding    (BPRZ)  */


/*---------------------------------------------------------------------------*
 * Combo Board Shared Host Interface Memory Access Constants for use with
 * AR_GET_DEVICE_CONFIG.  When using these item values, the channel parameter
 * is used to index the 1553 channel number, with a valid range from 0 to 4.
 *---------------------------------------------------------------------------*/
#define ARU_1553_CHANNEL_INITIALIZED 10000   /*                     */
#define ARU_1553_CHANNEL_STATUS      10001   /*                     */
#define ARU_1553_DISCRETE_USE        10002   /*                     */
#define ARU_1553_TRIGGER_USE         10003   /*                     */
#define ARU_1553_RT_ADDRESS          10004   /*                     */
#define ARU_1553_OPERATIONAL_MODE    10005   /*                     */
#define ARU_1553_TIME_TAG_MODE       10006   /*                     */
#define ARU_1553_TIME_TAG_INIT       10007   /*                     */
#define ARU_1553_TIME_TAG_DISPLAY    10008   /*                     */
#define ARU_1553_TIME_PERIOD         10009   /*                     */
#define ARU_1553_INITIAL_TIME_LOW    10010   /*                     */
#define ARU_1553_INITIAL_TIME_HIGH   10011   /*                     */



/*---------------------------------------------------------------------------*
 * Message Scheduler API routine data structure for the definition and
 * parameter usage of CEI-x30 periodic message scheduling data.
 * See the CEI-x30-SW User Manual, chapter "CEI-x30 Hardware Interface" for
 * a detailed explanation of the host interface scheduler table definition.
 *---------------------------------------------------------------------------*/
typedef struct MESSAGE_SCHEDULER_ENTRY {
   CEI_UINT32 messageIndex;
   CEI_UINT32 board; 
   CEI_UINT32 channel;
   CEI_UINT32 rate;
   CEI_UINT32 start;
   CEI_UINT32 txCount;
   CEI_UINT32 data;
} AR_SCHEDULED_MSG_ENTRY_TYPE, *pAR_SCHEDULED_MSG_ENTRY_TYPE;

typedef struct LV_MESSAGE_SCHEDULER_ENTRY {
  CEI_UINT32 array_size;
  AR_SCHEDULED_MSG_ENTRY_TYPE msgEntries[CEIDEV_CHAN_MSG_SCH_ENTRY_MAX];
} LV_AR_SCHEDULED_MSG_ENTRY_TYPE, *pLV_AR_SCHEDULED_MSG_ENTRY_TYPE;

/*---------------------------------------------------------------------------*
 * Time-tag definition structure for any routine passing a 64-bit time-tag
 * parameter supporting the IRIG time-reference (routines with an _xt suffix)
 * LabVIEW-RT support doesn't provide 64-bit integer capability, so limit the
 * time-tag support to 32-bit integer
 *---------------------------------------------------------------------------*/
typedef struct TIMETAG_PARAMETER_STRUCT {
   TIME_TAG_TYPE timeTagFormat;
   TIME_TAG_TYPE timeTag;
   TIME_TAG_TYPE referenceTimeTag;
} AR_TIMETAG_TYPE, *pAR_TIMETAG_TYPE;

/*---------------------------------------------------------------------------*
 * The following definitions and structure were added to support compilation 
 * for legacy CEI-520/620/820 applications.
 * This structure is not used in any way, shape, or form by the CEI-830 API.
 *---------------------------------------------------------------------------*/
#ifndef UTILDEFS_H
#define IS_6WIRE              0x1000 /* CEI-x20 board with 6-wire support    */
#define IS_717                0x2000 /* CEI-x20 board with -717/573 support  */
#define IS_CSDB               0x4000 /* CEI-x20 board with CSDB support      */
typedef struct ar_channel_parms 
{
   CEI_INT32  BaudRate;     
   CEI_INT32  ChannelType;  
   CEI_INT32  InternalWrap; 
   CEI_INT32  IntCount;     
   CEI_INT32  Parity;       
   CEI_INT32  AutoSync;     
   CEI_INT32  HWEncoding;   
   CEI_INT32  Sync1;        
   CEI_INT32  Sync2;        
   CEI_INT32  Sync3;        
   CEI_INT32  Sync4;        
   CEI_INT32  NumSubFrames; 
   CEI_INT32  OperateMode;  
   CEI_INT32  TimeTagMode;  
   CEI_UINT32 Parametrics; 
   CEI_INT32  Reserved2;
} AR_CHANNEL_PARMS, *pAR_CHANNEL_PARMS;
#endif

/*===========================================================================*
 *  F U N C T I O N   P R O T O T Y P E S 
 *===========================================================================*/
 
#ifdef __cplusplus 

   /*------------------------------------------------------------------------*  
    *  handle .cpp files
    *------------------------------------------------------------------------*/

   extern "C" {
#endif

//#if defined (_Windows)                 
//  #if !defined (_WIN32)
//    #define DLL_EXPORTED FAR PASCAL EXPORT 
//  #else
//    #define DLL_EXPORTED _stdcall           
//  #endif
//#else  
// Ignore both of these for Simulink Real-Time
  #define DLL_EXPORTED
  #define EXPORT32
//#endif

      
/*===========================================================================*
 *     A P I     E X T E R N A L   F U N C T I O N   P R O T O T Y P E S 
 *===========================================================================*/
                     
/*===========================================================================*
 * ENTRY POINT:          A R _ B O A R D _ T E S T
 *===========================================================================*
 *
 * FUNCTION:    This routine tests the functionality of the x30 device as part
 *              of the initialization process.
 *
 * PARAMETERS:  CEI_INT16 board    -- (input) board to reference (0 to 127)
 *              CEI_INT16 testType -- (input) type of test to execute
 *                                            INTERNAL_WRAP - perform an
 *                                               ARINC 429 internal wrap test 
 *                                            EXTERNAL_WRAP - perform an
 *                                               ARINC 429 external wrap test 
 *
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL          Success
 *                           ARS_INVBOARD        Invalid board parameter
 *                           ARS_BOARD_MUTEX     Access to the Board Lock timed-out/failed
 *                           ARS_MEMWRERR        Memory test failure
 *                           ARS_WRAP_DROP_FAIL  Wrap Data Missing
 *                           ARS_WRAP_DATA_FAIL  Wrap Data Pattern Mismatch
 *                           ARS_WRAP_FLUSH_FAIL Unknown External data received
 *                           ARS_XMITOVRFLO      Transmit buffer overrun has occurred
 *
 * DESCRIPTION: This routine performs an internal or external wrap from each 
 *              ARINC 429 transmit channel matched to a respective receive
 *              channel, (unbalanced channels are not tested).  It is followed
 *              by a complete reinitialization of the host interface to a
 *              semi-power-up state.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_board_test 
(
   CEI_INT16 board,                  /* (input) board to reference (0 to 127) */
   CEI_INT16 testType                /* (input) type of test to execute      */
);

/*===========================================================================*
 * ENTRY POINT:          A R _ B Y P A S S _ W R A P _ T E S T
 *===========================================================================*
 *
 * FUNCTION:    This routine saves the application's request to bypass
 *              the internal wrap test during board initialization
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *              CEI_INT16 bypass -- (input) AR_ON  bypass internal wrap test
 *                                          AR_OFF execute internal wrap test
 *
 * RETURN VAL:  CEI_INT16        -- ARS_NORMAL       Success
 *                                  ARS_INVBOARD     Invalid board parameter
 *
 * GLOBALS:     bypassWrapTest[]
 * 
 * DESCRIPTION: This routine saves the app's request for internal wrap
 *              execution during board initialization.  This is supplied
 *              in case the board is initialized while ARINC data is
 *              active on any receiver channel, which would cause the
 *              wrap test invoked via arx30_loadslv() to fail.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_bypass_wrap_test 
(
   CEI_INT16 board,            /* (input) board to reference (0 to 127)       */
   CEI_INT16 bypass            /* (input) bypass (or not) internal wrap test */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ C L O S E 
 *===========================================================================*
 *
 * FUNCTION:    Release all resources for the specified device.
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *
 * RETURN:      CEI_INT16 -- ARS_NORMAL      - Succesful completion of routine
 *                           ARS_INVBOARD    - Invalid board number specified
 *                                             or board never initialized
 *                           ARS_BOARD_MUTEX - Access to the Board Lock timed-out/failed
 *                           ARS_INT_ISR     - Interrupt was not terminated successfully
 *                           ARS_WINRTFAIL   - Windows Driver Close Device failed
 *                           ARS_FAILURE     - Failed to close driver or terminate the ISR
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: Call into the respective low-level library to free the resources 
 *              associated with this board, then terminate the session.
 *
 *===========================================================================*/                              
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_close
(
   CEI_INT16 board             /* (input) board to reference (0 to 127)       */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ C L R _ R X _ C O U N T
 *===========================================================================*
 *
 * FUNCTION:    Reset the counter for received messages on this channel
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) Board to reference (0 to 127)
 *              CEI_INT16 channel -- (input) Receive channel to use (0 to 31)
 * 
 * RETURN VAL   none
 * 
 * GLOBALS:     deviceGlobal[board]
 *              device[board]
 * 
 * DESCRIPTION: The device maintains a count of the number of ARINC data 
 *              messages received over the interface for each channel since 
 *              the device was last initialized (see AR_LOADSLV). 
 *              This routine resets that counter to zero.
 *
 *===========================================================================*/
EXPORT32 CEI_VOID DLL_EXPORTED arx30_clr_rx_count 
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel             /* (input)  recv channel to ref (0 to 31)   */
);

/*===========================================================================*
 * ENTRY POINT:    A R _ C O N V E R T _ T I M E _ T O _ S T R I N G   
 *===========================================================================*
 *
 * FUNCTION:    Convert standard x30 64-bit time value to character string
 * 
 * PARAMETERS:  CEI_INT16 board         --  (input)  Board number (0 to 127)  
 *              CEI_INT16 displayFormat --  (input)  Format for returned string:
 *                       AR_TD_REL_MIDNIGHT  Relative to Midnight Format and
 *                       AR_TD_IRIG          Full IRIG Format, both defined 
 *                                           as "(DDD)hh:mm:ss.uuuuuu"           
 *                       AR_TD_DATE          Date Format defined as
 *                                              "(MM/DD)hh:mm:ss.uuuuuu"
 * 
 *              pAR_TIMETAG_TYPE timeIn -- (input)  Source 64-bit time structure      
 *              pCEI_CHAR timeString    -- (output) Pointer to destination string    
 * 
 * RETURN VAL:  none
 *
 * DESCRIPTION: This routine converts the time value provided in the timeIn
 *              structure to a character string representation of date/time,
 *              format based on what is specified via the displayFormat parm.
 *              The supplied time format (LSB resolution) must be specified
 *              in the timeIn structure member "timeTagFormat", representing
 *              the resolution of the respective "timeTag" member data.
 *
 *===========================================================================*/  
EXPORT32 CEI_VOID DLL_EXPORTED arx30_convert_time_to_string 
( 
   CEI_INT16 board,
   CEI_INT16 displayFormat,
   pAR_TIMETAG_TYPE timeTagIn,
   pCEI_CHAR timeString 
);

/*===========================================================================*
 * ENTRY POINT:  A R _ C O N V E R T _ 1 5 5 3 _ T I M E _ T O _ S T R I N G   
 *===========================================================================*
 *
 * FUNCTION:    Convert a 1553 synchronized 64-bit time value to a character 
 *              string
 * 
 * PARAMETERS:  CEI_INT16 board         --  (input)  Board number (0 to 127)  
 *              CEI_INT16 displayFormat --  (input)  Format for returned string:
 *                       AR_TD_REL_MIDNIGHT  Relative to Midnight Format and
 *                       AR_TD_IRIG          Full IRIG Format, both defined 
 *                                           as "(DDD)hh:mm:ss.uuuuuu"           
 *                       AR_TD_DATE          Date Format defined as
 *                                              "(MM/DD)hh:mm:ss.uuuuuu"
 * 
 *              pAR_TIMETAG_TYPE timeIn -- (input)  Source 64-bit time structure      
 *              pCEI_CHAR timeString    -- (output) Pointer to destination string    
 * 
 * RETURN VAL:  none
 *
 * DESCRIPTION: This routine converts the time value provided in the timeIn
 *              structure to a character string representation of date/time,
 *              format based on what is specified via the displayFormat parm.
 *              The supplied time format (LSB resolution) must be specified
 *              in the timeIn structure member "timeTagFormat", representing
 *              the resolution of the respective "timeTag" member data.
 * 
 *              Since this routine is only provided for use with UCA32 Combo
 *              cards, the timeIn.timeTag member will have a ONE NANOSECOND 
 *              resolution.  timeIn.referenceTimeTag will still have a one
 *              microsecond resolution, as it retains the original CEI-x30
 *              64-bit time-stamp associated with the timer/time-stamp
 *              value read from the ARINC host interface source.
 * 
 *===========================================================================*/  
EXPORT32 CEI_VOID  DLL_EXPORTED arx30_convert_1553_time_to_string 
( 
   CEI_INT16 board,               /* (input) Board number (0 to 127)          */
   CEI_INT16 displayFormat,       /* (input)  format of returned time string */
   pAR_TIMETAG_TYPE timeIn,       /* (input)  64-bit time-tag structure      */
   pCEI_CHAR timeString           /* (output) Pointer to store time string   */ 
);

/*===========================================================================*
 * ENTRY POINT:            A R _ D E F I N E _ M S G
 *===========================================================================*
 *
 * FUNCTION:    Define a message on the device for scheduled transmission.
 *
 * PARAMETERS:  CEI_INT16 board    -- (input) Board number (0 to 127)  
 *              CEI_INT16 channel  -- (input) 429 Tx channel selection,
 *                                            valid range is 0 to N, where 
 *                                            N-1 refers to the last 429 
 *                                            Tx channel installed
 *              CEI_INT16 rate     -- (input) transmission rate (in msec)
 *              CEI_UINT16 start   -- (input) initial delay from the current 
 *                                            time until the message will be 
 *                                            transmitted for the first time  
 *                                            (subsequent transmissions at "rate")
 *              CEI_INT32 data     -- (input) the ARINC word to transmit
 *
 * RETURN VAL:  ARS_FAILURE    One of the following errors occurred:
 *                                board number out of range
 *                                board not loaded and initialized
 *                                an invalid channel was specified 
 *                                the maximum number of messages has already 
 *                                    been defined
 *                                feature is not supported by the hardware
 *
 *              Message Index  a return value in the range of 0 to 1023
 *                             indicates success, to be used by the host
 *                             application as the unique message number
 *                             assigned to this message.
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine defines an ARINC 429 message for periodic
 *              retransmission, causing the data word to be transmitted
 *              at a specific rate. Once a message has been defined, it 
 *              can be modified by calling AR_MODIFY_MSG. 
 *
 *              Messages can be defined anytime after AR_LOADSLV() has been 
 *              called.
 *
 *              The message rate is defined in milliseconds.  Based on h/w 
 *              design considerations, it is recommended that messages with  
 *              faster rates be defined before the slower ones. If the rate is
 *              set to zero, the message is considered to be removed and 
 *              eligable to be reused.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_define_msg 
(
   CEI_INT16  board,               /* (input) Board number (0 to 127)         */
   CEI_INT16  channel,             /* (input) 429 Tx channel selection       */
   CEI_INT16  rate,                /* (input) transmission rate (in msec)    */
   CEI_UINT16 start,               /* (input) initial delay from the current */
   CEI_INT32  data                 /* (input) the ARINC word to transmit     */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ D E F I N E _ M S G _ B L O C K
 *===========================================================================*
 *
 * FUNCTION:    Define a block of messages for scheduled transmission.
 *
 * PARAMETERS:  CEI_INT32 numberOfEntries -- (input) the number of entries to
 *                                                define, used as a reference
 *                                                for the number of structure
 *                                                elements defined via the
 *                                                messageEntry pointer
 *              pAR_SCHEDULED_MSG_ENTRY_TYPE
 *                  messageEntry     -- (input) array of structures of message 
 *                                              content, each element defined 
 *                                              as follows:
 *                                                 struct {
 *                                                    CEI_INT16 messageIndex;                  
 *                                                    CEI_INT16 board;                         
 *                                                    CEI_INT16 channel;                       
 *                                                    CEI_INT16 rate;                          
 *                                                    CEI_INT16 start;                         
 *                                                    CEI_UINT32 txCount;               
 *                                                    CEI_UINT32 data; } 
 *                                                    
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVARG      Invalid number of entries argument
 *                              ARS_INVHARVAL   Invalid transmit channel entry
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_FAILURE     The number of entries requested
 *                                              exceeds the available number
 *                                              of remaining table entries
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine defines the supplied message(s) in the device
 *              message scheduler table.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_define_msg_block
(
   CEI_INT32 numberOfEntries,                /* (input) number of entries    */
   pAR_SCHEDULED_MSG_ENTRY_TYPE messageEntry /* (input) ptr to struct of msgs*/
);

/*===========================================================================*
 * ENTRY POINT:         A R _ D E F I N E _ M S G _ B L O C K _ L V
 *===========================================================================*
 *
 * FUNCTION:    Define a block of messages for scheduled transmission,
 *              supporting LabVIEW structure array formatting
 *
 * PARAMETERS:  CEI_INT32 numberOfEntries -- (input) the number of entries to
 *                                                define, used as a reference
 *                                                for the number of structure
 *                                                elements defined via the
 *                                                messageEntry pointer
 *              pLV_AR_SCHEDULED_MSG_ENTRY_TYPE
 *                  messageEntry     -- (input) structure containing the size
 *                                              of the array along with the 
 *                                              array of structures of message 
 *                                              content, each element defined 
 *                                              as follows:
 *                                                 struct {
 *                                                    CEI_UINT32 messageIndex;                  
 *                                                    CEI_UINT32 board;                         
 *                                                    CEI_UINT32 channel;                       
 *                                                    CEI_UINT32 rate;                          
 *                                                    CEI_UINT32 start;                         
 *                                                    CEI_UINT32 txCount;               
 *                                                    CEI_UINT32 data; } 
 *                                                    
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVARG      Invalid number of entries argument
 *                              ARS_INVHARVAL   Invalid transmit channel entry
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_FAILURE     The number of entries requested
 *                                              exceeds the available number
 *                                              of remaining table entries
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine defines the supplied message(s) in the device
 *              message scheduler table.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_define_msg_block_lv
(
   CEI_INT32 numberOfEntries,                /* (input) number of entries    */
   pLV_AR_SCHEDULED_MSG_ENTRY_TYPE messageEntry /* (input) ptr to msg array  */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ E N H _ L A B E L _ F I L T E R
 *===========================================================================*
 *
 * FUNCTION:    Function to enable/disable enhanced label filtering on device.
 * 
 * PARAMETERS:  CEI_INT16 board     -- (input) Board number (0 to 127)  
 *              CEI_INT16 channel   -- (input) 429 receive channel selection,
 *                                     valid range is 0 to N, where N refers
 *                                     to the ARINC 561 channel, and N-1
 *                                     refers to the last 429 channel installed
 *              CEI_UINT16 label    -- (input) Label of interest.  Valid range
 *                                     is 0-255.  Also valid is ARU_ALL_LABELS
 *                                     which takes the action for all labels. 
 *              CEI_UINT16 sdi      -- (input) SDI of interest.  Valid range
 *                                     is 0-3.  Also valid is ARU_ALL_SDI
 *                                     which takes the action for all SDI values. 
 *              CEI_UINT16 essm     -- (input) ESSM of interest.  Valid range
 *                                     is 0-7.  Also valid is ARU_ALL_ESSM
 *                                     which takes the action for all ESSM values. 
 *              CEI_INT16 action    -- (input) Enable or disable filtering for
 *                                     this board/channel/label.  Valid values
 *                                     are: 
 * 
 *                 FILTER_SEQUENTIAL  0x10  if CLEAR add label to sequential
 *                                          receive buffer
 *                 FILTER_SNAPSHOT    0x20  If CLEAR add label to snapshot
 *                                          receive buffer
 *                 FILTER_INTERRUPT   0x40  If SET on reception insert channel #
 *                                          in the interrupt queue and if 
 *                                          enabled generate a PCI interrupt
 * 
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Success
 *                        -- ARS_INVBOARD    Invalid board argument
 *                        -- ARS_INVHARVAL   Invalid receive channel argument
 *                        -- ARS_INVARG      Invalid label, sdi, essm, or action argument
 *                        -- ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: The device supports hardware label filtering based on the
 *              label value for standard label filtering, or the combination
 *              of the label, SDI, and ESSM field values for enhanced label
 *              filtering.  This routine is designed to support enhanced
 *              label filtering for channel types 5 and 6 (enhanced ARINC 
 *              429).  This routine assigns the specified filter action to 
 *              the respective enhanced label filter table location for the 
 *              device receive channel.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_enh_label_filter 
(
   CEI_INT16  board,                    /* (input) Board number (0 to 127)    */
   CEI_INT16  channel,                  /* (input) 429 Rx channel selection  */
   CEI_UINT16 label,                    /* (input) Label of interest         */
   CEI_UINT16 sdi,                      /* (input) SDI of interest           */
   CEI_UINT16 essm,                     /* (input) ESSM of interest          */
   CEI_INT16  action                    /* (input) Filtering Enable/Disable  */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ E X E C U T E _ B I T
 *===========================================================================*
 *
 * FUNCTION:    This routine performs BIT functionality testing of the 
 *              device as specified by the host application.
 *
 * PARAMETERS:  CEI_INT16 board    -- (input) board to reference (0 to 127)
 *              CEI_INT16 testType -- (input) type of BIT to execute
 *                                        AR_BIT_BASIC_STARTUP
 *                                        AR_BIT_FULL_STARTUP
 *                                        AR_BIT_PERIODIC
 *                                        AR_BIT_INT_LOOPBACK
 *                                        AR_BIT_EXT_LOOPBACK
 *                                        AR_BIT_PARTIAL_SRAM   
 *                                        AR_BIT_FULL_SRAM      
 *                                        AR_BIT_SELECT_SRAM_MIN
 *                                        AR_BIT_SELECT_SRAM_MAX
 *
 * RETURN VAL:  CEI_INT16  ARS_NORMAL          Success
 *                         ARS_BOARD_MUTEX     Access to the Board Lock timed-out/failed
 *                         ARS_MEMWRERR        Memory test failure
 *                         ARS_WRAP_DROP_FAIL  Wrap Data Missing
 *                         ARS_WRAP_DATA_FAIL  Wrap Data Pattern Mismatch
 *                         ARS_WRAP_FLUSH_FAIL Unknown External data received
 *                         ARS_INVARG          Invalid testType parameter
 *                         ARS_INVBOARD        Invalid board parameter
 *                         ARS_FAILURE         Timer-deviation test failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine performs various tests of the hardware device.
 *              While none of these tests are "built-in" per se, they do
 *              provide basic health-status of the hardware.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_execute_bit
(
   CEI_INT16 board,                  /* (input) board to reference (0 to 127) */
   CEI_INT16 testType                /* (input) type of test to execute      */
);

/*===========================================================================*
 * ENTRY POINT:     A R _ G E T _ B A S E _ A D D R 
 *===========================================================================*
 *
 * FUNCTION:    This routine returns a pointer to the base address assigned
 *              to the device from the (plug and play) host.
 *
 * PARAMETERS:  CEI_INT16 board       -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  pCEI_UINT32 devicePtr -- pointer to the respective device host 
 *                                       interface location in virtual memory.
 * 
 * GLOBALS:     device[board].devicePtr
 * 
 * DESCRIPTION: Return the base address of the device.  Using the address 
 *              returned, any register on the device can be accessed directly.
 * 
 *===========================================================================*/
EXPORT32 pCEI_UINT32 DLL_EXPORTED arx30_get_base_addr
(
   CEI_INT16 board                   /* (input) board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:               A R _ G E T B L O C K
 *===========================================================================*
 *
 * FUNCTION:    Retrieve multiple messages from a specified receive buffer.
 *
 * PARAMETERS:  CEI_UINT32 board       -- (input)  board to reference (0 to 127)
 *              CEI_UINT32 channel     -- (input)  recvr channel to use (0 to 31)
 *              CEI_INT32  maxMessages -- (input)  number of messages to retrieve
 *              CEI_INT32  offset      -- (input)  unused parameter (legacy support)
 *              pCEI_INT32 actualCount -- (output) number of messages retrieved
 *              pCEI_INT32 data        -- (output) location to store data
 *              pCEI_INT32 timeTags    -- (output) location to store timetags
 *
 * RETURN VAL:  ARS_GOTDATA       one or more ARINC messages were retrieved
 *              ARS_NODATA        no ARINC messages were available in the buffer
 *              ARS_INVBOARD      invalid board number
 *              ARS_INVHARVAL     Item was invalid or channel
 *              ARS_INVARG        invalid parameter value
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *              ARS_BAD_MESSAGE   An invalid length msg was received
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine retrieves all of the available ARINC messages 
 *              from the requested receive channel buffer and copies them to 
 *              the desired destination.
 *
 *              If the TimeTag pointer is not NULL, the time tags associated
 *              with each retrieved message are also copied; however, only
 *              32-bit time-tagging options are supported.
 *
 *              If the buffer is empty this routine returns ARS_NODATA.
 *
 *              If the return value for actualCount is equal to maxMessages,
 *              additional unread data may be available in the receive buffer. 
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_getblock
(
   CEI_UINT32 board,           /* (input)  board to reference (0 to 127)      */
   CEI_UINT32 channel,         /* (input)  recvr channel to use (0 to 31)    */
   CEI_INT32  maxMessages,     /* (input)  number of messages to retrieve    */
   CEI_INT32  offset,          /* (input)  unused parameter (legacy support) */
   pCEI_INT32 actualCount,     /* (output) number of messages retrieved      */
   pCEI_INT32 data,            /* (output) location to store data            */
   pCEI_INT32 timeTags         /* (output) location to store timetags        */
);

/*===========================================================================*
 * ENTRY POINT:               A R _ G E T B L O C K _ T
 *===========================================================================*
 *
 * FUNCTION:    Retrieve multiple messages from a specified receive buffer,
 *              supporting 64-bit time-tag retrieval.
 *
 * PARAMETERS:  CEI_UINT32  board       -- (input)  board to reference (0 to 127)
 *              CEI_UINT32  channel     -- (input)  recvr channel to use (0 to 31)
 *              CEI_INT32   maxMessages -- (input)  number of messages to retrieve
 *              pCEI_INT32  actualCount -- (output) number of messages retrieved
 *              pCEI_UINT32 msgChan     -- (output) location to store receive channel
 *              pCEI_INT32  data        -- (output) location to store data
 *              pCEI_INT32  timeTagMsw  -- (output) location to store time-tag MSW
 *              pCEI_INT32  timeTagLsw  -- (output) location to store time-tag LSW
 *
 * RETURN VAL:  ARS_GOTDATA       one or more ARINC messages were retrieved
 *              ARS_NODATA        no ARINC messages were available in the buffer
 *              ARS_INVBOARD      invalid board number
 *              ARS_INVHARVAL     Unsupported channel parameter
 *              ARS_INVARG        invalid parameter value
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *              ARS_BAD_MESSAGE   An invalid length msg was received
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine retrieves all of the available ARINC messages 
 *              from the requested receive channel buffer and copies them to 
 *              the desired destination.
 *
 *              If the TimeTag pointers are not NULL, the 64-bit time-tag associated
 *              with each retrieved message are also copied, in separate 32-bit
 *              MSW and LSW arrays.
 *
 *              If the buffer is empty this routine returns ARS_NODATA.
 *
 *              If the return value for actualCount is equal to maxMessages,
 *              additional unread data may be available in the receive buffer. 
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_getblock_t
(
   CEI_UINT32  board,          /* (input)  board to reference (0 to 127)      */
   CEI_UINT32  channel,        /* (input)  recvr channel to use (0 to 31)    */
   CEI_INT32   maxMessages,    /* (input)  number of messages to retrieve    */
   pCEI_INT32  actualCount,    /* (output) number of messages retrieved      */
   pCEI_UINT32 msgChan,        /* (output) location to store rx chan (mrg md)*/
   pCEI_INT32  data,           /* (output) location to store data            */
   pCEI_INT32  timeTagMsw,     /* (output) location to store time-tag MSW    */
   pCEI_INT32  timeTagLsw      /* (output) location to store time-tag LSW    */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ B O A R D N A M E L V
 *===========================================================================*
 *
 * FUNCTION:    Return a reference to a string describing the board type 
 *                       
 * PARAMETERS:  CEI_UINT32 board     -- The board number of interest
 *              pCEI_CHAR  boardName -- reference to store a board type string
 *
 *                                      Typical strings are:   
 *                                      "CEI-830", "CEI-430", "CEI-530",
 *                                      "RAR-CPCI", "RAR-EC", or "RAR-PCIE",
 *                                      "RAR15-XMC", "RAR15-XMC-XT", "RAR-XMC",
 *                                      "RCEI-830A"
 *
 * RETURN VAL:  CEI_INT32 -- ARS_NORMAL   Normal succesful completion.
 *                           ARS_INVBOARD Board parameter value invalid or
 *                                        board has not been initialized
 *                           ARS_INVARG   boardName parameter not valid memory
 * 
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine returns this API-defined board name string for 
 *              device referenced by the specified board index, defined
 *              specifically for compatibility with the LabVIEW API.
 * 
 *===========================================================================*/ 
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_get_boardnameLV 
(
   CEI_UINT32 board,                /* (input)  board to reference (0 to 127) */
   pCEI_CHAR  boardName             /* (output) reference to store the name  */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ B O A R D N A M E
 *===========================================================================*
 *
 * FUNCTION:    Return the respective CEI-x30 board name
 *                       
 * PARAMETERS:  CEI_UINT32 board    The board number of interest
 *              pCEI_CHAR boardName Reference to char array to store the name
 *
 * RETURN VAL:  NULL                Board parameter value invalid or
 *                                     board has not been initialized
 *              pointer to char     Ptr to string for the board type detected
 *
 *                                  Typical strings are:   
 *                                     "CEI-830", "CEI-430", "CEI-530",
 *                                     "RAR-CPCI", "RAR-EC", "RAR-PCIE",
 *                                     "RAR15-XMC", "RAR15-XMC-XT", "RAR-XMC",
 *                                     "RCEI-830A"
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine returns this API-defined board name string for 
 *              device referenced by the specified board index.
 * 
 *===========================================================================*/ 
EXPORT32 pCEI_CHAR DLL_EXPORTED arx30_get_boardname 
(
   CEI_UINT32 board,                /* (input)  board to reference (0 to 127) */
   pCEI_CHAR  boardName             /* (output) reference to store the name  */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ B O A R D T Y P E
 *===========================================================================*
 *
 * FUNCTION:    Return the CEI-x30 board type for the specified board index.
 *                       
 * PARAMETERS:  CEI_INT16 board -- The board number of interest
 * 
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL     Normal succesful completion.
 *                           ARS_INVBOARD   Board parameter value invalid or
 *                                          board has not been initialized
 *
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine returns the CEI-x30 specific board type 
 *              referenced by the specified board index.
 * 
 *===========================================================================*/ 
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_boardtype
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:       A R _ G E T _ C H A N N E L _ I N D E X _ I N F O
 *===========================================================================*
 *
 * FUNCTION:    Retrieve channel indexing information for the specified board.
 *
 * PARAMETERS:  CEI_INT16                    board -- The board number of interest
 *              AR_CHANNEL_INDEX_INFO_TYPE * chan_index_info - structure containing
 *                                           the channel index information
 *                                           num_channels    number of channels supported at the interface
 *                                           chan_type[]     receive, transmit, or programmable
 *                                           chan_rx_index[] receive channel index values
 *                                           chan_tx_index[] transmit channel index values
 *
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL     Normal succesful completion.
 *                           ARS_INVBOARD   Board parameter value invalid or
 *                                          board has not been initialized
 *
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine returns the CEI-x30 channel indexing configuration
 *              for the specified board.
 *
 *              For each chan_type entry, the respective chan_*x_index references
 *              the respective receive/transmit channel index available.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_channel_index_info
(
   CEI_INT16 board,                              /* (input)  desired board id            */
   AR_CHANNEL_INDEX_INFO_TYPE * chan_index_info  /* (output) receives channel index info */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ C O N F I G
 *===========================================================================*
 *
 * FUNCTION:    Retrieve board and channel configuration attributes (legacy)
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board to reference (0 to 127)
 *              CEI_INT16 item  -- (input) item for which to return the 
 *                                     current state:
 * 
 *                     ARU_RX_CH0*_BIT_RATE        ARU_CONFIGURATION
 *                     ARU_RX_CH1*_BIT_RATE        ARU_DISCRETE_IN1          
 *                     ARU_TX_CH0*_BIT_RATE        ARU_DISCRETE_IN2          
 *                     ARU_TX_CH1*_BIT_RATE        ARU_DISCRETE_IN3          
 *                     ARU_RX_CH0*_PARITY          ARU_DISCRETE_IN4          
 *                     ARU_RX_CH1*_PARITY          ARU_DISCRETE_OUT1         
 *                     ARU_TX_CH0*_PARITY          ARU_DISCRETE_OUT2         
 *                     ARU_TX_CH1*_PARITY          ARU_DISCRETE_OUT2         
 *                     ARU_TX_CH0*_SHUT_OFF        ARU_DISCRETE_OUT3         
 *                     ARU_TX_CH1*_SHUT_OFF        ARU_ACCESS_SNAPSHOT_BUFFER
 *                     ARU_TX_CH**_HB_INJ          ARU_IRIG_WRAP_ENABLE      
 *                     ARU_TX_CH**_LB_INJ          ARU_IRIG_AVAILABLE        
 *                     ARU_TX_CH**_GAP_INJ         ARU_IRIG_CALIBRATED       
 *                     ARU_FW_VERSION              ARU_IRIG_INPUT_TIME
 *                     ARU_SERIAL_NUMBER
 *                     ARU_RX_TIMETAG_MODE w/values of:                          
 *
 *                              AR_TIMETAG_EXT_IRIG_64BIT                         
 *                              AR_TIMETAG_INT_USEC_64BIT                         
 *                              AR_TIMETAG_INT_20USEC_32BIT                       
 *                              AR_TIMETAG_INT_MSEC_32BIT                         
 *                              AR_TIMER_X20_COMPAT_32BIT
 *                              AR_TIMETAG_SYNC_1553_CH1 (for combo cards only)               
 *                              AR_TIMETAG_SYNC_1553_CH2                
 *                              AR_TIMETAG_SYNC_1553_CH3                
 *                              AR_TIMETAG_SYNC_1553_CH4                
 *
 * RETURN VAL:  CEI_INT32 state -- the state of the item specified
 *                             ARS_INVARG     "item" parameter value is not 
 *                                            supported by this API function
 *                             ARS_INVHARVAL  Channel not supported on device
 *                             ARS_INVBOARD   Board parameter value invalid or
 *                                            board has not been initialized
 *                             ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: Supplies the current state of the "item" requested.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_get_config 
(
   CEI_INT16 board,          /* board to reference (0 to 127)                 */
   CEI_INT16 item            /* item for which to return the current state   */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ G E T _ D A T A  
 *===========================================================================*
 *
 * FUNCTION:    Read the next data and 64-bit time-tag from a receive FIFO.
 *
 * PARAMETERS:  CEI_INT16 board    -- (input)  board to reference (0 to 127)
 *              pCEI_INT16 channel -- (input)  recv channel to reference (0 to 255)
 *                                    (output) in merged mode, the channel this
 *                                             data was actually received on
 *              pCEI_UINT32 
 *                  data           -- (output) location to store received data
 *
 *              pCEI_UINT32 
 *                  timeTagLo      -- (output) location to store timetag lsw
 *
 *              pCEI_UINT32 
 *                  timeTagHi      -- (output) location to store timetag msw
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA     Success
 *                              ARS_NODATA      No data availalble
 *                              ARS_INVHARVAL   Unsupported channel parameter
 *                              ARS_INVBOARD    Invalid board parameter
 *                                                 or board not initialized
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE An invalid length msg was received
 *
 * GLOBALS:     none
 * 
 * DESCRIPTION: This routine reads the most recently received entry (data and
 *              timetag) from the specified receive channel FIFO.  The 
 *              channel number passed to this routine corresponds to the
 *              hardware channel assignment on the device.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_data 
( 
   CEI_INT16 board,            /* (input)  board to reference (0 to 127)      */
#if defined (LABVIEW_RT)
   CEI_INT16 channel,          /* (input)  channel number to receive from    */
#else   
   pCEI_INT16 channel,         /* (output) in merged mode, chan received on  */
#endif
   pCEI_UINT32 data,           /* (output) location to store received data   */
   pCEI_UINT32 timeTagLo,      /* (output) location to store time-tag low wd */
   pCEI_UINT32 timeTagHi       /* (output) location to store time-tag hi wrd */
);

/*===========================================================================*
 * ENTRY POINT:                A R _ G E T _ D A T A _ X T
 *===========================================================================*
 *
 * FUNCTION:    Read the next data and 64-bit time-tag from a receive FIFO,
 *              returns the extended time-tag structure supporting IRIG.
 *
 * PARAMETERS:  CEI_INT16  board   -- (input)  board to reference (0 to 127)
 *              pCEI_INT16 channel -- (input)  recv channel to reference (0 to 255)
 *                                    (output) in merged mode, the channel this
 *                                             data was actually received on
 *              pCEI_UINT32 data   -- (output) location to store received data
 *
 *              pAR_TIMETAG_TYPE timeTagRef
 *                                 -- (output) location for time-tag struct
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA     Success
 *                              ARS_INVHARVAL   Unsupported channel parameter
 *                              ARS_INVARG      NULL data parameter value
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_NODATA      No data availalble
 *                              ARS_INVBOARD    Invalid board parameter
 *                                                 or board not initialized
 *                              ARS_BAD_MESSAGE An invalid length msg was received
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine reads the most recently received entry (data and
 *              timetag) from the specified receive channel FIFO.  The 
 *              channel number passed to this routine corresponds to the
 *              hardware channel assignment on the device.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_data_xt
(
   CEI_INT16   board,           /* (input)  board to reference (0 to 127)     */
   pCEI_INT16  channel,         /* (input)  recv channel to ref (0 to 255)   */
   pCEI_UINT32 data,            /* (output) location to store received data  */
   pAR_TIMETAG_TYPE timeTagRef  /* (output) location to store data time-tags */
);

/*===========================================================================*
 * ENTRY POINT:        A R _ G E T _ D E V I C E _ C O N F I G          
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the current state of protocol-generic device 
 *              configuration register and board-level/API attributes 
 * 
 * PARAMETERS:  CEI_INT16  board    -- (input)  board to reference (0 to 127)
 *              CEI_INT16  channel  -- (input)  channel number (0 to 31)
 *              CEI_INT16  item     -- (input)  selected channel config item
 *              pCEI_INT16 value    -- (output) current bit field state
 * 
 *              Valid combinations of item / value parameters are:
 * 
 *              for this "item"        valid options for "value" returned are:
 * 
 *              ARU_RX_FIFO_ENABLE     AR_ON           AR_OFF
 *              ARU_TX_FIFO_ENABLE     AR_ON           AR_OFF
 *              ARU_TX_DISABLE         AR_ON           AR_OFF
 *
 *              ARU_RX_BITRATE         ARU_SPEED_LOW   ARU_SPEED_HIGH  Custom
 *              ARU_RX_PARITY          AR_ON           AR_OFF
 *              ARU_RX_MERGED_MODE     AR_ON           AR_OFF
 *              ARU_RECV_MODE          AR_WRAP_OFF     AR_WRAP_ON
 * 
 *              ARU_TX_BITRATE         ARU_SPEED_LOW   ARU_SPEED_HIGH  Custom
 *              ARU_TX_PARITY          ARU_PARITY_NONE ARU_PARITY_ODD  ARU_PARITY_EVEN
 *              ARU_TX_GAP_ERROR       AR_ON           AR_OFF
 *              ARU_TX_BIT_ERROR       AR_HI   AR_LO   AR_OFF
 *              ARU_FAST_SLEW_RATE     AR_ON           AR_OFF
 *
 *              ARU_DISCRETE_VALUES    $0000           $FFFF
 *              ARU_DISCRETE_INPUTS    $0000           $FFFF
 *              ARU_DISCRETE_IN        AR_HI           AR_LO
 *              ARU_DIGITAL_IN         AR_HI           AR_LO
 *              ARU_DISCRETE_OUT       AR_HI           AR_LO
 *              ARU_DIGITAL_OUT        AR_HI           AR_LO
 *              ARU_DIFFERENTIAL_IN    AR_HI           AR_LO
 *              ARU_DIFFERENTIAL_OUT   AR_ON           AR_OFF
 *              ARU_HW_INTERRUPT_ENABLE    AR_ON       AR_OFF       
 *
 *              ARU_IRIG_AVAILABLE     TRUE            FALSE
 *              ARU_IRIG_WRAP_ENABLE   AR_ON           AR_OFF
 *              ARU_IRIG_OUTPUT_ENABLE AR_ON           AR_OFF
 *              ARU_IRIG_CALIBRATED
 *              ARU_IRIG_INPUT_TIME
 *              ARU_ACCESS_SNAPSHOT_BUFFER     ARU_LABEL_ONLY  ARU_LABEL_WITH_SDI
 *              ARU_RX_FIFO_COUNT      0 to 8191
 *              ARU_TX_FIFO_COUNT      0 to 8191
 *              ARU_RX_MSG_COUNT       0 to 65535
 *              ARU_TX_MSG_COUNT       0 to 65535
 *              ARU_RX_TIMETAG_MODE w/values of:                          
 *
 *                 AR_TIMETAG_EXT_IRIG_64BIT                         
 *                 AR_TIMETAG_INT_USEC_64BIT                         
 *                 AR_TIMETAG_INT_20USEC_32BIT                       
 *                 AR_TIMETAG_INT_MSEC_32BIT                         
 *                 AR_TIMER_X20_COMPAT_32BIT
 *                 AR_TIMETAG_SYNC_1553_CH1 (for combo cards only)               
 *                 AR_TIMETAG_SYNC_1553_CH2                
 *                 AR_TIMETAG_SYNC_1553_CH3                
 *                 AR_TIMETAG_SYNC_1553_CH4                
 *
 *              ARU_CHAN_COUNT_429
 *              ARU_CHAN_COUNT_573
 *              ARU_CHAN_COUNT_DISC
 *              ARU_CHAN_COUNT_DIFF
 *              ARU_CONFIGURATION
 *              ARU_DEVICE_DISABLE
 *              ARU_FW_VERSION
 *              ARU_HW_ENHANCE_CHECK
 *              ARU_HW_FPGA_TEMPERATURE
 *              ARU_HW_1PT0V_PWR_SUPPLY
 *              ARU_HW_2PT5V_PWR_SUPPLY
 *
 *              ARU_1553_CHANNEL_INITIALIZED
 *              ARU_1553_CHANNEL_STATUS     
 *              ARU_1553_DISCRETE_USE       
 *              ARU_1553_TRIGGER_USE        
 *              ARU_1553_RT_ADDRESS         
 *              ARU_1553_OPERATIONAL_MODE   
 *              ARU_1553_TIME_TAG_MODE      
 *              ARU_1553_TIME_TAG_INIT      
 *              ARU_1553_TIME_TAG_DISPLAY   
 *              ARU_1553_TIME_PERIOD        
 *              ARU_1553_INITIAL_TIME_LOW   
 *              ARU_1553_INITIAL_TIME_HIGH  
 *
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Normal succesful completion.
 *                           ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                           ARS_INVARG      "item" parameter value is not
 *                                              supported by this function
 *                           ARS_INVHARVAL   Item was invalid or channel
 *                                              not supported on this device
 *                           ARS_INVBOARD    Board parameter value invalid or
 *                                              board has not been initialized
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This function returns the state of the device configuration
 *              register attribute based on the combined item/value
 *              parameter selections.  It is designed to support the 
 *              ARINC 429 and all discrete and digital I/O configuration  
 *              register attributes available to the device.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_device_config 
( 
   CEI_INT16  board,        /* (input)  board to reference (0 to 127)         */
   CEI_INT16  channel,      /* (input)  channel number (0 to 31)             */
   CEI_INT16  item,         /* (input)  selected channel configuration item  */
   pCEI_INT16 value         /* (output) current bit field state              */
);


/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ E R R O R
 *===========================================================================*
 *
 * FUNCTION:    Function to return a message string associated with an error.
 * 
 * PARAMETERS:  CEI_INT16 error_num -- (input) A status value returned by  
 *                                             any API routine
 * 
 *              pCEI_CHAR errorStringOut (LV-x30 only output) error string
 * 
 * RETURN VAL:  pCEI_CHAR -- (std API) string containing associated error 
 *
 * GLOBALS:     arx30_830_errors_1[]
 *              arx30_830_errors_2[]
 *              arx30_830_intfc_errors[]
 *              arw_830_errors[]
 * 
 * DESCRIPTION: Many of the ARINC functions described here return status 
 *              values which may indicate an error condition.  This function 
 *              is passed such an error value and returns a pointer to a  
 *              message string describing the error. 
 *
 *===========================================================================*/  
#ifdef LABVIEW
EXPORT32 void DLL_EXPORTED arx30_get_error
(
   CEI_INT16 error_num,
   pCEI_CHAR errorStringOut
);
#else
EXPORT32 pCEI_CHAR DLL_EXPORTED arx30_get_error
(
   CEI_INT16 error_num
);
#endif

// Support routine for arx30_get_error
pCEI_CHAR ceix30_get_open_error (CEI_VOID);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T _ 4 2 9 _ M E S S A G E
 *===========================================================================*
 *
 * FUNCTION:    Read a 429 message from the ARINC 429 receiver FIFO 
 *              buffer specified via the channel parameter.
 *
 * PARAMETERS:  CEI_INT16 board     -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel   -- (input)  429 recvr channel to use (0 to 31)
 *              CEI_INT16 waitState -- (input)  to wait for 1/2 second or not
 *                                              designated as AR_ON or AR_OFF
 *              pCEI_VOID data      -- (output) location to store received data
 *              pCEI_VOID timeTag   -- (output) location to store data timeTag
 *
 * RETURN VAL   CEI_INT16 status -- ARS_GOTDATA       Success
 *                                  ARS_NODATA        No data available (no wait)
 *                                  ARS_CHAN_TIMEOUT  No data available (w/wait)
 *                                  ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *                                  ARS_INVBOARD      Invalid board parameter
 *                                                       or board not initialized
 *                                  ARS_INVHARVAL     Unsupported channel parameter
 *                                  ARS_INVARG        NULL data parameter value
 *                                  ARS_BAD_MESSAGE   An invalid length msg was received
 * GLOBALS:     none
 * 
 * DESCRIPTION: This routine invokes one of the two generic get-data  
 *              routines based on whether or not the waitState indicates to  
 *              delay 1/2 second.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_429_message  
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel,            /* (input)  channel number to ref (0 to 31) */
   CEI_INT16 waitState,          /* (input)  to wait for 1/2 second or not   */
   pCEI_VOID data,               /* (output) location to store received data */
   pCEI_VOID timeTag             /* (output) location to store data timeTag  */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ 5 7 3 _ C O N F I G
 *===========================================================================*
 *
 * FUNCTION:    Retrieve an ARINC 573 channel configuration register bit field def.
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) board to reference (0 to 127)
 *              CEI_INT16 item    -- (input) item to process, valid items are:
 *                                          ARU_RECV_MODE           
 *                                          ARU_RX_BITRATE          
 *                                          ARU_TX_BITRATE          
 *                                          ARU_RX_FIFO_ENABLE
 *                                          ARU_TX_FIFO_ENABLE
 *                                          ARU_573_RX_ENABLE
 *                                          ARU_573_RX_SUBFRAME_SIZE       
 *                                          ARU_573_RX_AUTO_DETECT  
 *                                          ARU_573_RX_BPRZ_SELECT  
 *                                          ARU_573_TX_BPRZ_SELECT
 *                                          ARU_573_TX_HBP_SELECT
 *                                          ARU_573_TX_SLEW_RATE    
 *                                          ARU_573_SYNC_WORD1
 *                                          ARU_573_SYNC_WORD2
 *                                          ARU_573_SYNC_WORD3
 *                                          ARU_573_SYNC_WORD4
 * 
 *              pCEI_INT32 value  -- (output) the state of the item specified
 *                                        with valid item/value combinations:
 *
 *                  item                     valid values
 * 
 *                 ARU_RECV_MODE            AR_WRAP_OFF, AR_WRAP_ON
 *                 ARU_RX_FIFO_ENABLE       AR_OFF, AR_ON
 *                 ARU_573_RX_ENABLE        AR_OFF, AR_ON (same as ARU_RX_FIFO_ENABLE)
 *                 ARU_573_RX_AUTO_DETECT   AR_OFF, AR_ON
 *                 ARU_573_RX_BPRZ_SELECT   AR_OFF, AR_ON
 *                 ARU_573_TX_BPRZ_SELECT   AR_OFF, AR_ON
 *                 ARU_573_TX_HBP_SELECT    AR_OFF, AR_ON
 *                 ARU_RX_BITRATE &         ARU_573_RATE_SIZE_384_32    
 *                 ARU_TX_BITRATE           ARU_573_RATE_SIZE_768_64    
 *                                          ARU_573_RATE_SIZE_1536_128  
 *                                          ARU_573_RATE_SIZE_3072_256  
 *                                          ARU_573_RATE_SIZE_6144_512  
 *                                          ARU_573_RATE_SIZE_12288_1024
 *                                          ARU_573_RATE_SIZE_24576_2048
 *                                          ARU_573_RATE_SIZE_49152_4096
 *                 ARU_573_RX_SUBFRAME_SIZE ARU_573_SUB_FRAME_64  
 *                                          ARU_573_SUB_FRAME_128 
 *                                          ARU_573_SUB_FRAME_256 
 *                                          ARU_573_SUB_FRAME_512 
 *                                          ARU_573_SUB_FRAME_1024
 *                                          ARU_573_SUB_FRAME_2048
 *                                          ARU_573_SUB_FRAME_4096
 *                 ARU_TX_FIFO_ENABLE       AR_OFF, AR_ON
 *                 ARU_TX_DISABLE           AR_OFF, AR_ON (inverse of ARU_TX_FIFO_ENABLE)
 *                 ARU_573_TX_SLEW_RATE     ARU_573_TX_SLEW_1PT5
 *                                          ARU_573_TX_SLEW_10PT0
 *                 ARU_RX_MERGED_MODE       AR_ON, AR_OFF
 *                 ARU_573_SYNC_WORD1       value from 0x0000 to 0x0fff
 *                 ARU_573_SYNC_WORD2       value from 0x0000 to 0x0fff
 *                 ARU_573_SYNC_WORD3       value from 0x0000 to 0x0fff
 *                 ARU_573_SYNC_WORD4       value from 0x0000 to 0x0fff
 *                 ARU_TX_FIFO_COUNT        value from 0 to 8191
 *      
 * RETURN VAL:  CEI_INT16     -- ARS_NORMAL      Normal succesful completion.
 *                               ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                               ARS_INVARG      "item" parameter value is not
 *                                                  supported by this function
 *                               ARS_INVHARVAL   Item was invalid or channel
 *                                                  not supported on this device
 *                               ARS_INVBOARD    Board parameter value invalid or
 *                                                  board has not been initialized
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *              
 * DESCRIPTION: Supplies the current state of the "item" requested from the device.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_573_config 
( 
   CEI_INT16 board,                 /* (input)  board to reference (0 to 127) */
   CEI_INT16 item,                  /* (input)  item to process              */
   pCEI_INT32 value                 /* (output) state of the item            */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ 5 7 3 _ F R A M E
 *===========================================================================*
 *
 * FUNCTION:    Receive an ARINC 573 frame from the ARINC 573 FIFO. 
 *
 * PARAMETERS:  CEI_INT16 board         -- (input) Board number of interest (0-8)                          
 *              pCEI_UINT32 numberWords -- (input/output) Number of ARINC 573 
 *                                          words to read / number actually read
 *              pCEI_UINT16 arincData   -- (output) Pointer to the ARINC 573 buffer
 * 
 * RETURN VAL:  CEI_INT16    -- ARS_NODATA      No 573 frame data was available
 *                              ARS_GOTDATA     Some 573 frame data was retrieved
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_INVBOARD    Invalid board parameter or board not initialized
 *                              ARS_INVHARVAL   Protocol not available on device
 *                              ARS_INVARG      Invalid numberWords or arincData parameter
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: When the ARINC 573 receiver is configured for auto-sync, 
 *      this routine will read an entire ARINC 573 frame based on the 
 *      specified sub-frame size (from speed selection).  If the receiver
 *      is configured for raw reception, all available data will be retrieved
 *      from the receiver channel FIFO buffer.  If the receive buffer doesn't  
 *      contain any data, it will return a zero; otherwise, it will
 *      read and return what is available.
 * 
 *      The data is returned as an array of 16-bit unsigned values.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_573_frame 
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   pCEI_UINT32 numberWords,      /* (in/output) number words to read/actual  */
   pCEI_UINT16 arincData         /* (output) data read from 717 FIFO         */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ G E T F I L T E R
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the label interrupt and filter buffer definition used 
 *              by the device enhanced label filter feature.
 * 
 * PARAMETERS:  CEI_UINT32 board      -- (input) Board number (0 to 127)  
 *              CEI_UINT32 channel    -- (input) 429 Rx channel selection,
 *                                               valid range is 0 to one less
 *                                               than the number of enhanced
 *                                               ARINC 429 channels installed
 *              pCEI_CHAR filterTable -- (input) pointer to the host filter table
 *                                               at least 8Kb in size.
 * 
 * RETURN VAL:  ARS_NORMAL        operation completed successfully
 *              ARS_INVBOARD      invalid board number or board not initialized
 *              ARS_INVARG        invalid argument
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine copies the specified label filter buffer entry
 *              from the enhanced label filter table on the device to 
 *              the caller's memory space.  Each element of the enhanced label 
 *              filter buffer consists of a bit field defined as follows:
 *
 *                 FILTER_SEQUENTIAL  0x10   if CLEAR add label to sequential
 *                                              receive buffer
 *                 FILTER_SNAPSHOT    0x20   If CLEAR add label to snapshot
 *                                              receive buffer
 *                 FILTER_INTERRUPT   0x40   If SET on reception insert channel #
 *                                              in the interrupt queue and if 
 *                                              enabled generate a PCI interrupt
 *
 *              The filter buffer for a single channel is defined as follows:
 *
 *                 CEI_UCHAR filterTable[MAX_ESSM][MAX_SDI][MAX_LABEL]
 *
 *              where the bits of the ARINC word are split up as follows:
 *
 *              field   ---eSSM---  -SDI-  --------label---------
 *               bits   30  29  28   9 8   7  6  5  4  3  2  1  0
 *                    
 *              On the device each 32-bit entry in the filter table is 
 *              allocated once for each label/SDI combination, divided 
 *              into individual filter activation fields by eSSM:
 *
 *                 Label Filter Table [MAX_LABEL][MAX_SDI]
 *
 *               bits   31 30 29 28 27 ... 8  7  6  5  4  3  2  1  0
 *              field  | eSSM = 7  |   ...   | eSSM = 1  | eSSM = 0 |
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_getfilter 
(
   CEI_UINT32 board,             /* (input) Board number (0 to 127)           */
   CEI_UINT32 channel,           /* (input) 429 Rx channel selection         */
   pCEI_CHAR filterTable         /* (input) pointer to the host filter table */
);
   
/*===========================================================================*
 * ENTRY POINT:        A R _ G E T _ L A B E L _ F I L T E R
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the active state of filtering for all receive
 *              channels for the specified label
 * 
 * PARAMETERS:  CEI_INT16 board    -- (input) Board number (0 to 127)  
 *              CEI_UINT16 label   -- (input) label to query the filter state
 * 
 * RETURN VAL:  Label Filter State -- each bit indicates the label state on
 *                                    the respective receive channel 0-15
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine indicates the active state of label filtering
 *              for the specified label on each receive channel.  The state
 *              indicates active filtering with a "1" bit state for the bit 
 *              respective to the receive channel.  Active filtering is 
 *              defined as any label filter table entry for any Enhanced SSM
 *              and SDI value combination where the following filtering is
 *              enabled
 *                 FILTER_SEQUENTIAL  0x01   if CLEAR add label to sequential
 *                                              receive buffer
 *                 FILTER_SNAPSHOT    0x02   If CLEAR add label to snapshot
 *                                              receive buffer
 *
 *===========================================================================*/ 
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_label_filter 
(
   CEI_INT16  board,          /* (input) Board number (0 to 127)              */
   CEI_UINT16 label           /* (input) the label to query the filter state */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ G E T _ L A T E S T
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the latest message received for the specified 
 *              channel/label combination from the snapshot buffer
 * 
 * PARAMETERS:  CEI_INT16 board    -- (input)  Board number (0 to 127)  
 *              CEI_INT16 channel  -- (input)  429 Rx channel selection,
 *                                             valid range is 0 to one less
 *                                             than the number of enhanced
 *                                             ARINC 429 channels installed
 *              CEI_UINT16 label   -- (input)  Label of interest
 *              pCEI_VOID data     -- (output) pointer to the host data storage
 *              pCEI_CHAR seq_num  -- (n/a)    legacy parameter, not supported
 * 
 * RETURN VAL:  NONE
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine copies the latest ARINC 492/561 message received 
 *              for the specified channel/label comb. from the snapshot buffer.
 *              When using this routine, the host application should set the
 *              snapshot storage mode to "label field only".  This will setup
 *              the device to store snapshot data based on the label field value
 *              only, ignoring the SDI bit field value.
 *
 *              The snapshot buffer access by this routine for a single label/channel
 *              combination is defined with the bits of the ARINC word as follows:
 *
 *                     field    --------label---------
 *                      bits    7  6  5  4  3  2  1  0
 *
 *              If the label requested is label 256 (an ARINC label that does 
 *              not exist) or the value "ARU_ALL_LABELS", this function returns
 *              all 255 ARINC labels for the specified channel (000-255), in sequence, 
 *              in successive "data" array elements.  This function assumes the caller
 *              has allocated at least 256*4 bytes for "data" when used in this mode.
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_VOID  DLL_EXPORTED arx30_get_latest 
(
   CEI_INT16 board,             /* (input)  Board number (0 to 127)           */
   CEI_INT16 channel,           /* (input)  429 Rx channel selection         */
   CEI_UINT16 label,            /* (input)  Label of interest                */
   pCEI_VOID data,              /* (output) pointer to the host data storage */
   pCEI_CHAR seq_num            /* (n/a)    legacy parameter, not supported  */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ L A T E S T _ T
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the latest message & time-stamp for the specified 
 *              channel/label combination from the snapshot buffer
 * 
 * PARAMETERS:  CEI_INT16 board   -- (input)  Board number (0 to 127)  
 *              CEI_INT16 channel -- (input)  429 Rx channel selection,
 *                                               valid range is 0 to one less
 *                                               than the number of enhanced
 *                                               ARINC 429 channels installed
 *              CEI_UINT16 label  -- (input)  Label of interest
 *              pCEI_UINT32 data  -- (output) pointer to the host data storage
 *              TIME_TAG_TYPE timeTag -- (output) pointer to time-stamp storage
 * 
 * 
 * RETURN VAL:  ARS_NORMAL        Operation completed successfully
 *              ARS_INVBOARD      Invalid board number or board not initialized
 *              ARS_INVHARVAL     Invalid receive channel argument
 *              ARS_INVARG        Invalid label argument, null data ptr
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine copies the latest ARINC 492/561 message received 
 *              for the specified channel/label comb. from the snapshot buffer.
 *              When using this routine, the host application should set the
 *              snapshot storage mode to "label field only".  This will setup
 *              the device to store snapshot data based on the label field value
 *              only, ignoring the SDI bit field value.
 *
 *              The snapshot buffer for a single channel is defined as follows:
 *
 *                 CEI_UCHAR snapshot[MAX_SDI][MAX_LABEL]
 *
 *              where the bits of the ARINC word are split up as follows:
 *
 *                     field   -SDI-  --------label---------
 *                      bits    9 8   7  6  5  4  3  2  1  0
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_get_latest_t 
(
   CEI_INT16 board,            /* (input)  Board number (0 to 127)            */
   CEI_INT16 channel,          /* (input)  429 Rx channel selection          */
   CEI_UINT16 label,           /* (input)  Label of interest                 */
   pCEI_UINT32 data,           /* (output) pointer to the host data storage  */
   TIME_TAG_TYPE * timeTag     /* (output) pointer to time-stamp storage     */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T N E X T
 *===========================================================================*
 *
 * FUNCTION:    Read a message from the specified Receive FIFO.  Give the 
 *              message a maximum of 1/2 second to arrive before timing out.
 *
 * PARAMETERS:  CEI_INT16 board        -- (input)  board to reference
 *              CEI_INT16 channel      -- (input)  recvr channel to use (0 to 31)
 *              pCEI_VOID destination  -- (output) location to receive data
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA       Success
 *                              ARS_INVHARVAL     Unsupported channel #
 *                              ARS_INVARG        NULL data parameter value
 *                              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *                              ARS_CHAN_TIMEOUT  No data available
 *                              ARS_BAD_MESSAGE   An invalid length msg was received
 *                              ARS_INVBOARD      Invalid board parameter
 *                                                or board not initialized
 * GLOBALS:     none
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC 429 data.
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 * 
 *              This routine polls the receiver continuously, incorporating a
 *              1 millisecond sleep/task delay until:
 *                 1) An ARINC word is received or
 *                 2) The timeout threshold of 1/2 second is reached.
 * 
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getnext 
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel,            /* (input)  recv channel to ref (0 to 31)   */
   pCEI_VOID destination         /* (output) location to store received data */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T N E X T T
 *===========================================================================*
 *
 * FUNCTION:    Read the next incoming ARINC data word and its timetag.  Give
 *              the word a maximum of 1/2 second to arrive before timing out.
 *
 * PARAMETERS:  CEI_INT16 board       -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel     -- (input)  recvr channel to use (0 to 31)
 *              pCEI_VOID destination -- (output) location to receive data
 *              pCEI_VOID timeTag     -- (output) location to place timetag
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA       Success
 *                              ARS_CHAN_TIMEOUT  No data available
 *                              ARS_INVHARVAL     Unsupported channel parameter
 *                              ARS_INVARG        NULL data parameter value
 *                              ARS_INVBOARD      Invalid board parameter
 *                              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE   An invalid length msg was received
 *
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC 429 data.
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 * 
 *              This routine polls the receiveer continuously until:
 *                 1) An ARINC word is received or
 *                 2) The timeout threshold (1/2 second) is reached.
 * 
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getnextt 
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel,            /* (input)  recv channel to ref (0 to 31)   */
   pCEI_VOID destination,        /* (output) location to store received data */
   pCEI_VOID timeTag             /* (output) location to store data time-tag */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T N E X T _ X T
 *===========================================================================*
 *
 * FUNCTION:    Read the next incoming ARINC data word and its timetag.  Give
 *              the word a maximum of 1/2 second to arrive before timing out.
 *              Return the extended time-tag structure supporting IRIG.
 *
 * PARAMETERS:  CEI_INT16 board    -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel  -- (input)  recvr channel to use (0 to 7)
 *              pCEI_UINT32 data   -- (output) location for receive data
 *              pAR_TIMETAG_TYPE timeTagRef
 *                                 -- (output) location for time-tag struct
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA       Success
 *                              ARS_CHAN_TIMEOUT  No data available
 *                              ARS_INVHARVAL     Unsupported channel parameter
 *                              ARS_INVARG        NULL data parameter value
 *                              ARS_INVBOARD      Invalid board parameter
 *                              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE   An invalid length msg was received
 *
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC 429 data.
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 * 
 *              This routine polls the receiveer continuously until:
 *                 1) An ARINC word is received or
 *                 2) The timeout threshold (1/2 second) is reached.
 * 
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getnext_xt 
( 
   CEI_INT16 board,             /* (input)  board to reference (0 to 127)     */
   CEI_INT16 channel,           /* (input)  recv channel to ref (0 to 31)    */
   pCEI_UINT32 data,            /* (output) location to store received data  */
   pAR_TIMETAG_TYPE timeTagRef  /* (output) location to store data time-tags */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ G E T _ S N A P _ D A T A
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the latest message received for the specified 
 *              channel/label combination from the snapshot buffer
 * 
 * PARAMETERS:  CEI_INT16 board   -- (input)  Board number (0 to 127)  
 *              CEI_INT16 channel -- (input)  429 Rx channel selection,
 *                                               valid range is 0 to one less
 *                                               than the number of enhanced
 *                                               ARINC 429 channels installed
 *              CEI_UINT16 label  -- (input)  Label of interest
 *              CEI_UINT16 sdi    -- (input)  SDI Field Value of interest
 *              pCEI_INT32 data   -- (output) pointer to the host data storage
 * 
 * RETURN VAL:  ARS_NORMAL        Operation completed successfully
 *              ARS_INVBOARD      Invalid board number or board not initialized
 *              ARS_INVHARVAL     Invalid receive channel argument
 *              ARS_INVARG        Invalid label or SDI argument, null data ptr
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine copies the latest ARINC 492/561 message received 
 *              for the specified channel/label combination from the snapshot buffer.
 *              When using this routine, the host application should set the
 *              snapshot storage mode to "label/sdi storage".  This will setup
 *              the device to store snapshot data based on the label field value
 *              in combination with the SDI bit field value.
 *
 *              The snapshot buffer for a single channel is defined as follows:
 *
 *                 CEI_UCHAR snapshot[MAX_SDI][MAX_LABEL]
 *
 *              where the bits of the ARINC word are split up as follows:
 *
 *                     field   -SDI-  --------label---------
 *                      bits    9 8   7  6  5  4  3  2  1  0
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_get_snap_data 
(
   CEI_INT16 board,            /* (input)  Board number (0 to 127)            */
   CEI_INT16 channel,          /* (input)  429 Rx channel selection          */
   CEI_UINT16 label,           /* (input)  Label of interest                 */
   CEI_UINT16 sdi,             /* (input)  SDI Field Value of interest       */
   pCEI_INT32 data             /* (output) pointer to the host data storage  */
);

/*===========================================================================*
 * ENTRY POINT:      A R _ G E T _ R X _ C H A N N E L _ S T A T U S
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the current receive channel buffer status and 
 *              fill level.
 *
 * PARAMETERS:  CEI_INT16 board          -- (input)  Board to reference (0 to 127)
 *              CEI_INT16 channel        -- (input)  Receive channel to use (0 to 31)
 *              pCEI_INT32 channelStatus -- (output) Bitwise reflection of the Rx
 *                                                   channel status register bits 0-2
 *                                                     AR_BUFFER_MSG_AVAILABLE     1
 *                                                     AR_INVALID_MSG_DETECTED     2
 *                                                     AR_BUFFER_OVERFLOW_DETECTED 4
 *              pCEI_INT32 messageCount  -- (output) Buffer fill level acquired from the
 *                                                   MSW of the status register; valid
 *                                                   if b0 is set, range is 1 - 2047.
 * 
 * RETURN VAL   CEI_UINT32 -- ARS_NORMAL     Success
 *                            ARS_INVHARVAL  Unsupported channel parameter
 *                            ARS_INVARG     NULL channelStatus or messageCount parameter value
 *                            ARS_INVBOARD   Invalid board parameter
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine returns the current status of the specified
 *              receive channel buffer.  If either an ARINC 429 protocol 
 *              error or buffer overflow bit was set in the receive channel 
 *              buffer status register, it will be cleared upon return from 
 *              this routine.
 *
 *===========================================================================*/
EXPORT32 CEI_UINT32 DLL_EXPORTED arx30_get_rx_channel_status 
( 
   CEI_INT16  board,        /* (input)  board to reference (0 to 127)         */
   CEI_INT16  channel,      /* (input)  channel to reference (0 to 32)       */
   pCEI_INT32 channelStatus,/* (output) status bits from each Rx status reg. */
   pCEI_INT32 messageCount  /* (output) buffer fill level from ea rx st reg. */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ R X _ C O U N T
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the count of received messages on this channel
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) Board to reference (0 to 127)
 *              CEI_INT16 channel -- (input) Receive channel to use (0 to 31)
 * 
 * RETURN VAL   CEI_UINT32                   Count of ARINC messages received
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: The device maintains a count of the number of ARINC data 
 *              messages received over the interface for each channel since 
 *              the device was last initialized (see AR_LOADSLV). 
 *              This routine returns that number.
 *
 *===========================================================================*/
EXPORT32 CEI_UINT32 DLL_EXPORTED arx30_get_rx_count
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel             /* (input)  recv channel to ref (0 to 31)   */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ S T A T U S
 *===========================================================================*
 *
 * FUNCTION:    Retrieve FIFO Data Available bit status for all receivers
 *
 * PARAMETERS:  CEI_INT16  board -- (input)  board to reference (0 to 127)
 *              pCEI_INT16 state -- (output) value if interrupt status reg.
 * 
 * RETURN VAL   CEI_INT16        -- ARS_NORMAL       Success
 *                                  ARS_INVBOARD      Invalid board parameter
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: Supplies the combined state of each Rx FIFO status register
 *              FIFO Data Available bit.  Supports up to 16 multi-protocol 
 *              receivers.
 *
 *              For the CEI-830, this routine returns the combined state of 
 *              the Rx FIFO Status Register Data Available Bit for each of
 *              the individual receiver FIFOs. 
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_status 
( 
   CEI_INT16 board,         /* (input)  board to reference (0 to 127)         */
   pCEI_INT16 state         /* (output) bit value from each FIFO status reg. */
);

/*===========================================================================*
 * ENTRY POINT:      A R _ G E T _ S T O R A G E _ M O D E
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the board-level receive data storage mode
 *
 * PARAMETERS:  CEI_INT16  board -- (input)  board index (0 to 127)
 *              pCEI_INT16 mode  -- (output) valid values are:
 *                                  ARU_BUFFERED individual buffer per channel
 *                                  ARU_MERGED   one merged circular buffer
 * 
 * RETURN VAL:  ARS_NORMAL        success
 *              ARS_INVBOARD      invalid board parameter or board not 
 *                                initialized
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine returns the current "global" storage mode to the
 *              application .
 *
 *              This routine is provided for backward compatibility with
 *              the CEI-710 API.  The proper method to retrieve the Merged
 *              Receive Mode is provided for individual channels via the 
 *              respective channel get-config routine using the item
 *              parameter value ARU_RX_MERGED_MODE and its ON/OFF selection.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_storage_mode 
(
   CEI_INT16 board,   /* (input)  board index (0 to 127)                      */
   pCEI_INT16 mode    /* (output) storage mode (ARU_BUFFERED or ARU_MERGED)  */
); 

/*===========================================================================*
 * ENTRY POINT:             A R _ G E T _ T I M E
 *===========================================================================*
 *
 * FUNCTION:    This routine returns the current time reference value scaled 
 *              from either the CEI-x30 internal 64-bit timer or the most 
 *              recently received IRIG timer reference, as specified via 
 *              the format parameter.  If the requested timer reference is 
 *              IRIG, the syncTime parameter will contain the timer-
 *              referenced time-tag assigned when the IRIG time reference 
 *              was received by the CEI-x30 board.
 *
 * PARAMETERS:  CEI_INT16 board  -- (input)  Board number (0 to 127)  
 * 
 *              CEI_INT16 format -- (input)  Format of time value to be returned     
 * 
 *              pAR_TIMETAG_TYPE timeTagRef    -- (output)
 *                             ->timeTagFormat -- format of timeTag member
 *                                              AR_TIMETAG_EXT_IRIG_64BIT
 *                                              AR_TIMETAG_INT_USEC_64BIT
 *                                              AR_TIMETAG_HOST_USEC_64BIT
 *                                              AR_TIMETAG_INT_20USEC_32BIT
 *                                              AR_TIMETAG_INT_MSEC_32BIT
 *                                              AR_TIMER_X20_COMPAT_32BIT
 * 
 *                             ->timeTag -- timer value in the resolution and 
 *                                          size selected via "format" parameter
 * 
 *                             ->referenceTimeTag -- a 64-bit 1 microsecond
 *                                          indicating one of the following:
 * 
 *                                  1) The current device timer value, or
 *                                  2) For IRIG, the device timer value 
 *                                     when the last IRIG update was received.
 * 
 * RETURN VAL:  CEI_INT32    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVARG      Invalid timeTagFormat structure member
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_time 
(
   CEI_INT16 board,                 /* (input)  board to reference (0 to 127) */
   CEI_INT16 format,                /* (input)  requested format of time     */
   pAR_TIMETAG_TYPE timeTag         /* (output) formatted time-tag value     */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ G E T _ T I M E R C N T L
 *===========================================================================*
 *
 * FUNCTION:    This routine returns the value of the device timer in a
 *              32-bit format.  If the current selected system time format
 *              is 64-bit or IRIG, the 1 millisecond 32-bit format is used.
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) Board number (0 to 127)  
 * 
 * RETURN VAL:  CEI_UINT32 -- the value of the device timer
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 *===========================================================================*/
EXPORT32 CEI_UINT32 DLL_EXPORTED arx30_get_timercntl
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:      A R _ G E T _ T R A N S M I T T E R _ M O D E
 *===========================================================================*
 *
 * FUNCTION:    Retrieve the ARINC 573 multi-protocol transmitter mode
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board index (0 to 127)
 *              pCEI_INT16 mode -- (input) valid values are:
 *                                            ARU_XMIT_573_HBP
 *                                            ARU_XMIT_573_BPRZ
 *
 * RETURN VAL:  ARS_NORMAL        success
 *              ARS_INVBOARD      invalid board parameter or board not 
 *                                initialized
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine returns the currently enabled ARINC 573/717
 *              transmitter configuration to the application, which applies
 *              to a limited subset of CEI-x30 products (most do both simultaneously).
 *
 *              This routine is provided for backward compatibility with
 *              the CEI-710 API.  The proper method to retrieve the ARINC 573
 *              Encoding as BPRZ or HBP is provided for individual channel(s) 
 *              via the arx30_get_573_config routine using the item parameter
 *              values ARU_573_TX_HBP_SELECT and ARU_573_TX_BPRZ_SELECT.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_get_transmitter_mode 
(
   CEI_INT16 board,       /* (input)  board index (0 to 127)                  */
   pCEI_INT16 mode        /* (output) transmitter mode (717-HBP or 717-BPRZ) */
); 

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T W O R D
 *===========================================================================*
 *
 * FUNCTION:    Read the ARINC message from a receiver FIFO buffer.
 *
 * PARAMETERS:  CEI_INT16 board       -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel     -- (input)  recvr channel to use (0 to *)
 *              pCEI_VOID destination -- (output) location to receive data
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA     Success
 *                              ARS_NODATA      No data available
 *                              ARS_INVHARVAL   Protocol not available on device
 *                              ARS_INVARG      NULL data parameter value
 *                              ARS_INVBOARD    Invalid board parameter
 *                                              or board not initialized
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE An invalid length msg was received
 * GLOBALS:     deviceGlobal[]
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC data.
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 receive channel index, starting with zero.  If it 
 *              exceeds the 429 receive channel count and an ARINC 573/717
 *              receiver exists, it will be used as the designated receiver.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getword 
( 
   CEI_INT16 board,              /* (input)  board to reference (0 to 127)    */
   CEI_INT16 channel,            /* (input)  recv channel to ref (0 to 31)   */
   pCEI_VOID destination         /* (output) location to store received data */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T W O R D T
 *===========================================================================*
 *
 * FUNCTION:    Read the ARINC message and timetag from a receiver FIFO buffer.
 *
 * PARAMETERS:  CEI_INT16 board       -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel     -- (input)  recvr channel to use (0 to 255)
 *              pCEI_VOID destination -- (output) location to receive data
 *              pCEI_VOID timeTag     -- (output) location to receive timetag
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA     Success
 *                              ARS_NODATA      No data availalble
 *                              ARS_INVHARVAL   Protocol not available on device
 *                              ARS_INVARG      NULL data parameter value
 *                              ARS_INVBOARD    Invalid board parameter
 *                                              or board not initialized
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE An invalid length msg was received
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC word 
 *              and timetag from the specified channel buffer.  The 
 *              channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getwordt 
( 
   CEI_INT16 board,             /* (input)  board to reference (0 to 127)     */
   CEI_INT16 channel,           /* (input)  recv channel to ref (0 to 31)    */
   pCEI_VOID destination,       /* (output) location to store received data  */
   pCEI_VOID timeTag            /* (output) location to store data time-tags */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ G E T W O R D _ X T
 *===========================================================================*
 *
 * FUNCTION:    Read the ARINC word and time-tag from a receiver FIFO buffer,
 *              returning the extended time-tag structure supporting IRIG
 *
 * PARAMETERS:  CEI_INT16 board    -- (input)  board to reference (0 to 127)
 *              CEI_INT16 channel  -- (input)  recvr channel to ref (0 to 31)
 *              pCEI_UINT32 data   -- (output) location for receive data
 *              pAR_TIMETAG_TYPE timeTagRef
 *                                 -- (output) location for time-tag struct
 *
 * RETURN VAL   CEI_INT16    -- ARS_GOTDATA     Success
 *                              ARS_NODATA      No data availalble
 *                              ARS_INVHARVAL   Protocol not available on device
 *                              ARS_INVARG      NULL data parameter value
 *                              ARS_INVBOARD    Invalid board parameter
 *                                              or board not initialized
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_BAD_MESSAGE An invalid length msg was received
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine reads the most recently received ARINC word 
 *              and 64-bit timetag from the specified channel buffer.  The 
 *              channel number passed to this routine corresponds to the
 *              ARINC 429 channel number index, starting with zero.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_getword_xt
(
   CEI_INT16 board,             /* (input)  board to reference (0 to 127)     */
   CEI_INT16 channel,           /* (input)  recv channel to ref (0 to 31)    */
   pCEI_UINT32 data,            /* (output) location to store received data  */
   pAR_TIMETAG_TYPE timeTagRef  /* (output) location to store data time-tags */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ G O
 *===========================================================================*
 *
 * FUNCTION:    Enable the transmitter and receiver FIFOs on the device
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid board parameter
 *                                              or board not initialized
 *                              ARS_BOARD_MUTEX Access to the Board Lock 
 *                                              timed-out/failed
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: Sets the global enable register global enable bit to ENABLE
 *              and enables the CEI-830 Message Scheduler
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_go
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);
      
/*===========================================================================*
 * ENTRY POINT:            A R _ I N I T I A L I Z E _ A P I
 *===========================================================================*
 *
 * FUNCTION:    Initialize the API local variables
 * 
 * PARAMETERS:  CEI_INT32 board   -- (input) device number to open (0-127)
 *
 * RETURN VAL:  CEI_INT16   -- ARS_NORMAL      Success
 *                             ARS_DRIVERFAIL  Board session open failed
 *                             ARS_INVBOARD    Invalid board parameter
 *                             ARS_BADLOAD     FPGA load process failed
 *                             ARS_HW_DETECT   Supported device not detected
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *                                    
 * DESCRIPTION: This routine opens a session to the device, loads f/w, and
 *              defines the API I/O register pointers.  This routine should
 *              not be directly invoked without first invoking arx30_loadslv.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_initialize_api
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
); 

/*===========================================================================*
 * ENTRY POINT:            A R _ I N I T I A L I Z E _ D E V I C E
 *===========================================================================*
 *
 * FUNCTION:    Initialize the device to a ready state
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) device number to reference (0-127)
 *
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL       Success
 *                              ARS_BAD_STATIC     Memory test failure
 *                              ARS_MEMWRERR     Memory test failure
 *                              ARS_INVBOARD     Invalid board parameter
 *                              ARS_BOARD_MUTEX  Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine initializes the device I/O configuration 
 *              registers to a state ready for use by the host application.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_initialize_device 
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:     A R _ H W _ I N T E R R U P T _ B U F F E R _ R E A D
 *===========================================================================*
 *
 * FUNCTION:    Read from the local API copy of the device h/w interrupt queue
 *
 * PARAMETERS:  board         -- (input)  device number to reference (0-127)
 *              numberOfWords -- (in/output) number of words to read & no. read
 *              data          -- (output) the queue entry value(s) read
 *
 * RETURN VAL:  ARS_GOTDATA   -- Data was successfully retrieved
 *              ARS_NODATA    -- No data was retrieved
 *              ARS_INVBOARD  -- Invalid device ID parameter
 *              ARS_INVARG    -- Invalid data buffer parameter
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *              lastApplicationReadIntQueueLocation[]
 *
 * DESCRIPTION: This routine provides read access to the local API copy of
 *              the CEI-x30 device interrupt queue.  The local API copy is
 *              filled via h/w interrupt processing within the default API ISR.
 *              If the host application replaces the default API ISR with a
 *              custom ISR, this routine will not be usable.
 *
 *              For each invocation of this routine, the specified number of 
 *              queue entries will be read from the buffer region starting at
 *              the location last referenced by the API and ending at the 
 *              location referenced by the interrupt queue pointer.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_hw_interrupt_buffer_read 
(
   CEI_INT32   board,                        /* device number (0-127)         */
   pCEI_UINT32 numberOfWords,                /* number of words to read      */
   pCEI_UINT32 data                          /* data read from the buffer    */
);

/*===========================================================================*
 * ENTRY POINT:     A R _ I N T E R R U P T _ Q U E U E _ R E A D
 *===========================================================================*
 *
 * FUNCTION:    Provides application read access to the h/w interrupt queue
 *
 * PARAMETERS:  board         -- (input)  device number to reference (0-127)
 *              numberOfWords -- (in/output) number of words to read & no. read
 *              data          -- (output) the queue entry value(s) read
 *
 * RETURN VAL:  ARS_GOTDATA     -- Data was successfully retrieved
 *              ARS_NODATA      -- No data was retrieved
 *              ARS_INVBOARD    -- Invalid device ID parameter
 *              ARS_INVARG      -- Invalid data buffer parameter
 *              ARS_BOARD_MUTEX -- Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     deviceConfig[].deviceAcquired
 *              device[].devicePtr
 *              lastApplicationReadIntQueueLocation[]
 *
 * DESCRIPTION: This routine provides read access to the h/w interrupt queue.
 *              For each invocation, the specified number of queue entries
 *              will be read from the buffer region starting at the location
 *              last referenced by the API and ending at the location
 *              referenced by the interrupt queue pointer.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_interrupt_queue_read 
(
   CEI_INT32   board,                        /* device number (0-127)         */
   pCEI_UINT32 numberOfWords,                /* number of words to read      */
   pCEI_UINT32 data                          /* data read from the buffer    */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ L A B E L _ F I L T E R
 *===========================================================================*
 *
 * FUNCTION:    Function to enable/disable standard label filtering on device.
 * 
 * PARAMETERS:  CEI_INT16 board   -- (input) Board number (0 to 127)  
 *              CEI_INT16 channel -- (input) 429 Rx channel selection,
 *                                    valid range is 0 to N, where N refers
 *                                    to the ARINC 561 channel, and N-1
 *                                    refers to the last 429 channel installed
 *              CEI_UINT16 label  -- (input) Label of interest.  Valid range
 *                                    is 0-255.  Also valid is ARU_ALL_LABELS
 *                                    which takes the action for all labels. 
 *              CEI_INT16 action  -- (input) Enable or disable filtering for
 *                                    this board/channel/label.  Valid values
 *                                    are: ARU_FILTER_ON/ARU_FILTER_OFF
 * 
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Success
 *                           ARS_INVBOARD    Invalid board argument
 *                           ARS_INVHARVAL   Invalid receive channel argument
 *                           ARS_INVARG      Invalid label or action argument
 *                           ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: The device supports hardware label filtering based on the
 *              label value for standard label filtering, or the combination
 *              of the label, SDI, and ESSM field values for enhanced label
 *              filtering.  This routine is designed to support standard
 *              label filtering for channel types 1 and 3 (basic ARINC 429).
 *              This routine assigns the specified filter action to the
 *              respective label filter table location for the device receive
 *              channel.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_label_filter 
( 
   CEI_INT16  board,                 /* (input) Board number (0 to 127)       */
   CEI_INT16  channel,               /* (input) 429 Rx channel selection     */
   CEI_UINT16 label,                 /* (input) Label of interest.           */
   CEI_INT16  action                 /* (input) Enable or disable filtering  */
);

/*===========================================================================*
 * ENTRY POINT:                A R _ L O A D S L V
 *===========================================================================*
 *
 * FUNCTION:    This routine initializes the API and device.
 *
 * PARAMETERS:  CEI_INT16 board     -- (input) device number (0-127)
 *              CEI_UINT32 base_seg -- (input) not used       (present for
 *              CEI_INT32 base_port -- (input) not used  API compatibility
 *              CEI_UINT16 ram_size -- (input) not used              only)
 *
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL    Success!!!
 *                              ARS_INVBOARD  board parm value not supported
 *                              ARS_BADLOAD   FPGA load process failed
 *                              ARS_BOARD_MUTEX Access to or creation of the
 *                                              Board Lock timed-out/failed
 *                              ARS_DRIVERFAIL Board session open failed
 *                              ARS_HW_DETECT Supported device not detected
 *                              ARS_MEMWRERR  Device memory test failure
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine fulfills the standard Condor ARINC API
 *              initialization functionality.  It invokes the following:
 *              arx30_initialize_api()    - acquires the device resources & loads FPGA
 *              arx30_initialize_device() - initializes the device to the default settings
 *              arx30_board_test()        - performs a simple internal wrap test
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_loadslv 
(
   CEI_INT16  board,                 /* (input) device number (0-127)         */
   CEI_UINT32 base_seg,              /* (input) legacy parameter, not used   */
   CEI_INT32  base_port,             /* (input) legacy parameter, not used   */
   CEI_UINT16 ram_size               /* (input) legacy parameter, not used   */
);
 
/*===========================================================================*
 * ENTRY POINT:            A R _ M O D I F Y _ M S G
 *===========================================================================*
 *
 * FUNCTION:    Modify a message already defined for scheduled transmission.
 *
 * PARAMETERS:  CEI_INT16 board     -- (input) Board number (0 to 127)  
 *              CEI_INT16 channel   -- (input) 429 Tx channel selection,
 *                                         valid range is 0 to N, where N 
 *                                         refers to the ARINC 561 channel, 
 *                                         and N-1 refers to the last 429 
 *                                         Tx channel installed
 *              CEI_INT16 msgNumber -- (input) the message ident to modify
 *              CEI_INT16 rate      -- (input) transmission rate (in msec)
 *              CEI_INT32 data      -- (input) the ARINC word to transmit
 *
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVARG      Invalid channel
 *                              ARS_INVHARVAL   Message scheduling is not
 *                                              supported on the specified channel
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_FAILURE     The supplied msg table index
 *                                              exceeds the available number
 *                                              of table entries
 *
 * GLOBALS:     device[board].multiThreadProtect
 *
 * DESCRIPTION: This routine modifies an existing ARINC 429 or 561 message 
 *              already defined for periodic retransmission. 
 *
 *              The message rate is defined in milliseconds.  Based on h/w 
 *              design considerations, it is recommended that messages with  
 *              faster rates be defined before the slower ones. If the rate is
 *              set to zero, the message is considered to be removed and 
 *              eligable to be reused.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_modify_msg 
(
   CEI_INT16 board,                   /* (input) Board number (0 to 127)      */
   CEI_INT16 channel,                 /* (input) 429 Tx channel selection    */
   CEI_INT16 msgNumber,               /* (input) message index (from arx30_def) */
   CEI_INT16 rate,                    /* (input) transmission rate (in msec) */
   CEI_INT32 data                     /* (input) the ARINC word to transmit  */
);

/*===========================================================================*
 * ENTRY POINT:            A R _ M O D I F Y _ M S G _ B L O C K
 *===========================================================================*
 *
 * FUNCTION:    Modify multiple messages previously defined for scheduled 
 *              transmission.
 *
 * PARAMETERS:  CEI_INT32 numberOfEntries -- (input) the number of entries to
 *                                                define or modify, used as a
 *                                                reference for the number of 
 *                                                structure elements defined
 *                                                via the messageEntry pointer
 *              pAR_SCHEDULED_MSG_ENTRY_TYPE
 *                        messageEntry    -- (input) array of structures of  
 *                                              message content, each element  
 *                                              defined as follows:
 *                                                struct {
 *                                                  CEI_UINT32 messageIndex;                  
 *                                                  CEI_UINT32 board;                         
 *                                                  CEI_UINT32 channel;                       
 *                                                  CEI_UINT32 rate;                          
 *                                                  CEI_UINT32 start;                         
 *                                                  CEI_UINT32 txCount;               
 *                                                  CEI_UINT32 data; } 
 *                                                    
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVHARVAL   Message scheduling is not
 *                                              supported on the specified channel
 *                              ARS_INVARG      Invalid channel
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_FAILURE     The supplied msg table index
 *                                              exceeds the available number
 *                                              of table entries
 *
 * GLOBALS:     device[board].multiThreadProtect
 *
 * DESCRIPTION: This routine modifies multiple existing ARINC 429 messages
 *              already defined for periodic retransmission. 
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_modify_msg_block 
(
   CEI_INT32 numberOfEntries,                /* (input) number of entries    */
   pAR_SCHEDULED_MSG_ENTRY_TYPE messageEntry /* (input) ptr to struct of msgs*/
);

/*===========================================================================*
 * ENTRY POINT:         A R _ N U M _ R C H A N S
 *===========================================================================*
 *
 * FUNCTION:    Return the number of receive channels on the board.
 * 
 * PARAMETERS:  CEI_INT16 board -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  CEI_INT16       -- number of receive channels on this board.
 *                              ARS_INVBOARD  board parm value not supported
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: Supply the number of receiver channels for this device
 *              NOTE: The board must have been initialized via arx30_loadslv().
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_num_rchans
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);
                
/*===========================================================================*
 * ENTRY POINT:         A R _ N U M _ X C H A N S
 *===========================================================================*
 *
 * FUNCTION:    Return the number of transmit channels on the board.
 * 
 * PARAMETERS:  CEI_INT16 board -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  CEI_INT16       -- number of transmit channels on this board.
 *                              ARS_INVBOARD  board parm value not supported
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: Supply the number of receiver channels for this device
 *              NOTE: The board must have been initialized via arx30_loadslv().
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_num_xchans
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);  

/*===========================================================================*
 * ENTRY POINT:              A R _ P U T B L O C K
 *===========================================================================*
 *
 * FUNCTION:    Put multiple words into the specified channel's sequential
 *              transmit buffer.
 *
 * PARAMETERS:  CEI_UINT32 board       -- (input)  board to reference (0 to 127)
 *              CEI_UINT32 channel     -- (input)  recvr channel to use (0 to 255)
 *              CEI_INT32  maxMessages -- (input)  number of messages to transmit
 *              CEI_INT32  offset      -- (input)  unused parameter (legacy support)
 *              pCEI_INT32 data        -- (input)  source of data
 *              pCEI_INT32 actualCount -- (output) number of messages transmitted
 *
 * RETURN VAL:  ARS_NORMAL        Success
 *              ARS_INVBOARD      Invalid board number
 *              ARS_INVHARVAL     Invalid receive channel argument
 *              ARS_INVARG        Invalid argument value
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *              ARS_XMITOVRFLO    Transmit buffer overflow - indicates that 
 *                                there was not enough room in the transmit 
 *                                buffer for all of the ARINC words specified
 *                                ('ActualCount' receives the number of words
 *                                actually transfered)
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine puts multiple ARINC words in the transmit queue
 *              for a particular channel. When this routine returns, the data
 *              has not necessarily been sent, it has only been placed in the
 *              transmit buffer. If other data is in the transmit buffer ahead
 *              of it, it will be transmitted in turn.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_putblock
(
   CEI_UINT32 board,           /* (input)  board to reference (0 to 127)      */
   CEI_UINT32 channel,         /* (input)  recvr channel to use (0 to 255)   */
   CEI_INT32  maxMessages,     /* (input)  number of messages to transmit    */
   CEI_INT32  offset,          /* (input)  unused parameter (legacy support) */
   pCEI_INT32 data,            /* (input)  source of data                    */
   pCEI_INT32 actualCount      /* (output) number of messages transmitted    */
);

/*===========================================================================*
 * ENTRY POINT:              A R _ P U T B L O C K _ M U L T I _ C H A N
 *===========================================================================*
 *
 * FUNCTION:    Place multiple transmit messages into the multiple channel's 
 *              transmit buffers.
 *
 * PARAMETERS:  CEI_UINT32 board       -- (input)  board to reference (0 to 127)
 *              CEI_INT32 maxMessages  -- (input)  number of messages to transmit
 *              pCEI_UINT32 channels   -- (input)  ARINC 429 transmit channels on
 *                                                 which to transmit data (0 to 127)
 *              pCEI_INT32 data        -- (input)  source of data
 *              pCEI_INT32 actualCount -- (output) number of messages transmitted
 *
 * RETURN VAL:  ARS_NORMAL        Success
 *              ARS_INVBOARD      Invalid board number
 *              ARS_INVHARVAL     Invalid receive channel argument
 *              ARS_INVARG        Invalid argument value
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *              ARS_XMITOVRFLO    Transmit buffer overflow - indicates that 
 *                                there was not enough room in the transmit 
 *                                buffer for all of the ARINC words specified
 *                                ('ActualCount' receives the number of words
 *                                actually transfered)
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine puts multiple ARINC words in the transmit queue
 *              for a multiple channels. When this routine returns, the data
 *              has not necessarily been sent, it has only been placed in the
 *              respective transmit buffer. If other data is in the transmit
 *              buffer ahead of it, it will be transmitted in turn.
 *
 *              Each element of the message data array will be placed in the
 *              transmitter buffer designated by the same "channels" array
 *              element, on an element-by-element basis.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_putblock_multi_chan
(
   CEI_UINT32  board,          /* (input)  board to reference (0 to 127)      */
   CEI_INT32   maxMessages,    /* (input)  number of messages to transmit    */
   pCEI_UINT32 channels,       /* (input)  transmit channels to use (0 to 127)*/
   pCEI_INT32  data,           /* (input)  source of data                    */
   pCEI_INT32  actualCount     /* (output) number of messages transmitted    */
);

/*===========================================================================*
 * ENTRY POINT:                 A R _ P U T F I L T E R
 *===========================================================================*
 *
 * FUNCTION:    Copy the label interrupt and filter buffer definition used 
 *              by the device enhanced label filter feature.
 * 
 * PARAMETERS:  CEI_UINT32 board      -- (input) Board number (0 to 127)  
 *              CEI_UINT32 channel    -- (input) 429 Rx channel selection,
 *                                               valid range is 0 to one less
 *                                               than the number of enhanced
 *                                               ARINC 429 channels installed
 *              pCEI_CHAR filterTable -- (input) pointer to the host filter table
 * 
 * RETURN VAL:  ARS_NORMAL        operation completed successfully
 *              ARS_INVBOARD      invalid board number or board not initialized
 *              ARS_INVARG        invalid receive channel or null table ptr
 *              ARS_BOARD_MUTEX   Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This routine copies the specified label filter table entry
 *              from the caller's memory space to the enhanced label filter
 *              table on the device.  Each element of the enhanced label 
 *              filter buffer consists of a bit field defined as follows:
 *
 *                 FILTER_SEQUENTIAL  0x10   if CLEAR add label to sequential
 *                                              receive buffer
 *                 FILTER_SNAPSHOT    0x20   If CLEAR add label to snapshot
 *                                              receive buffer
 *                 FILTER_INTERRUPT   0x40   If SET on reception insert channel #
 *                                              in the interrupt queue and if 
 *                                              enabled generate a PCI interrupt
 *
 *              The filter buffer for a single channel is defined as follows:
 *
 *                 CEI_UCHAR filterTable[MAX_ESSM][MAX_SDI][MAX_LABEL]
 *
 *              where the bits of the ARINC word are split up as follows:
 *
 *              field   ---eSSM---  -SDI-  --------label---------
 *               bits   30  29  28   9 8   7  6  5  4  3  2  1  0
 *                    
 *              On the device each 32-bit entry in the filter table is 
 *              allocated once for each label/SDI combination, divided 
 *              into individual filter activation fields by eSSM:
 *
 *                 Label Filter Table [MAX_LABEL][MAX_SDI]
 *
 *               bits   31 30 29 28 27 ... 8  7  6  5  4  3  2  1  0
 *              field  | eSSM = 7  |   ...   | eSSM = 1  | eSSM = 0 |
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_putfilter 
(
   CEI_UINT32 board,             /* (input) Board number (0 to 127)           */
   CEI_UINT32 channel,           /* (input) 429 Rx channel selection         */
   pCEI_CHAR filterTable         /* (input) pointer to the host filter table */
);
   
/*===========================================================================*
 * ENTRY POINT:              A R _ P U T _ 4 2 9 _ M E S S A G E
 *===========================================================================*
 *
 * FUNCTION:    Put a message in the specified ARINC 429 transmit FIFO.
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) board to reference (0 to 127)
 *              CEI_INT16 channel -- (input) 429 transmit channel to use
 *              CEI_INT32  data   -- (input) 32-bit ARINC 429 data to transmit 
 *
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Success
 *                           ARS_INVBOARD    Invalid board or board not initialized
 *                           ARS_INVHARVAL   Invalid transmit channel argument
 *                           ARS_XMITOVRFLO  Transmit buffer overrun has occurred
 *                           ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 * GLOBALS:     none
 * 
 * DESCRIPTION: This routine utilizes the common arx30_putword() routine to
 *              stuff a message into the respective ARINC 429 transmit FIFO.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_put_429_message  
( 
   CEI_INT16 board,             /* (input) board to reference (0 to 127)      */
   CEI_INT16 channel,           /* (input) 429 transmit channel to use       */
   CEI_INT32 data               /* (input) 32-bit ARINC 429 data to transmit */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ P U T _ 5 7 3 _ F R A M E
 *===========================================================================*
 *
 * FUNCTION:    Transmit ARINC 573 frame data on the ARINC 573 channel. 
 *
 * PARAMETERS:  CEI_INT16   board         -- (input) Board number of interest (0-127)
 *              CEI_UINT32  numberWords   -- (input) no. of ARINC 573 words to send
 *                                                   NOTE: must be an even number
 *              pCEI_UINT32 transmitCount -- (input) number of words transmitted,
 *                                                   a return value of 0 indicates 
 *                                                   a failure to transmit data
 *              pCEI_UINT16 arincData     -- (input) Pointer to the frame data
 * 
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL        success
 *                              ARS_INVBOARD      invalid board parameter or  
 *                                                board not initialized
 *                              ARS_INVHARVAL     invalid channel parameter
 *                              
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine will stuff the ARINC 573 frame data into 
 *              the respective transmit FIFO.  Once the FIFO is full or the
 *              specified number of elements have been copied to the FIFO,
 *              the number of elements "transmitted" will be returned.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_put_573_frame 
( 
   CEI_INT16   board,             /* (input) Board number of interest (0-127) */
   CEI_UINT32  numberWords,       /* (input) no. of ARINC 573 words to send  */
   pCEI_UINT32 transmitCount,     /* (input) number of words transmitted     */
   pCEI_UINT16 arincData          /* (input) Pointer to the frame data       */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ P U T W O R D
 *===========================================================================*
 *
 * FUNCTION:    Put a message into the generic device channel FIFO. 
 *
 * PARAMETERS:  CEI_INT16 board     -- (input) board to reference (0 to 127)
 *              CEI_INT16 channel   -- (input) Transmit channel (0 to *)
 *              CEI_INT32 arincdata -- (input) message data to transmit
 * 
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Success
 *                           ARS_INVBOARD    Invalid board or board not initialized
 *                           ARS_INVHARVAL   Invalid transmit channel argument
 *                           ARS_XMITOVRFLO  Transmit buffer overrun has occurred
 *                           ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine will place the specified message in the
 *              respective channel FIFO.  
 *              The channel number passed to this routine corresponds to the
 *              ARINC 429 transmit channel index, starting with zero.  If it *
 *              exceeds the 429 transmit channel count and an ARINC 573/717
 *              transmitter exists, it will be used as the designated transmitter.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_putword 
( 
   CEI_INT16 board,                 /* (input) board to reference (0 to 127)  */
   CEI_INT16 channel,               /* (input) transmit channel to use       */
   CEI_INT32 arincdata              /* (input) 32/16-bit data to transmit    */
);   
         
/*===========================================================================*
 * ENTRY POINT:            A R _  Q U E R Y _ D E V I C E
 *===========================================================================*
 *
 * FUNCTION:    Open a session to the board and identify the board type
 * 
 * PARAMETERS:  CEI_INT16  board     -- (input)  device number to open (0-127)
 *              pCEI_INT16 boardType -- (output) if supported, the board type
 *
 *                                                  PRODUCT     DEFINE  VALUE
 *                                                  CEI-830   - CEI830   19
 *                                                  CEI-430   - CEI430   21
 *                                                  AMC-830   - AMC830   22
 *                                                  CEI-530   - CEI530   26
 *                                                  R-830RX   - R830RX   27
 *                                                  RAR-CPCI  - RARCPCI  28
 *                                                  RAR-EC    - RAREC    29
 *
 *                                               unsupported by the API but 
 *                                               reported includes the following:
 *
 *                                                  CEI-520   - CEI520    6 
 *                                                  CEI-620   - CEI620   10 
 *                                                  CEI-820   - CEI820   11 
 *                                                  CEI-715   - CEI715   16 
 *                                                  PMC-708   - PMC708   20
 *                                                  CNIC-A2P  - CNIC    100
 *                                                  PMC-D1    - PMCD1   101
 *                                                  PMC-D2    - PMCD2   102
 *                                                  EPMC      - EPMC    103
 *                                                  P-SER     - PSER    104
 *                                                  P-MIO     - PMIO    105
 *                                                  P-DIS     - PDIS    106
 *                                                  P-10SF    - P10SF   107
 *                                                  AMC-1553  - QD_AMC1553 108
 *                                                  PCI-1553  - PCx1553 109
 *                                                  & cPCI-1553
 *                                                  QPCI-1553 - QD_QPCI    110
 *                                                  QCP-1553  - QD_QCP     111
 *                                                  QPCX-1553 - QD_QPCX    112
 *
 *                                               if not, "UNSUPPORTED"
 *
 * RETURN VAL:  CEI_INT16   -- ARS_NORMAL      Success
 *                             ARS_INVBOARD    Invalid board parameter
 *
 * GLOBALS:     None
 *                                    
 * DESCRIPTION: This routine opens a WinRT session to the device and
 *              checks the PCI manufacturer and device ID.  If these IDs
 *              are of supported x30 products, identify the board;
 *              otherwise report it as "unsupported".
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_query_device 
(
    CEI_INT16 board,                /* (input)  device number to open (0-127) */
    pCEI_INT16 boardType            /* (output) if supported, the board type */
);

/*===========================================================================*
 * ENTRY POINT:    A R _ R E A D _ S C H E D U L E D _ M S G _ B L O C K
 *===========================================================================*
 *
 * FUNCTION:    Read a block of defined messages from the scheduler table.
 *
 * PARAMETERS:  CEI_INT16 board           -- (input) Board number (0 to 127)  
 *                                                    
 *              CEI_INT32 startingEntry   -- (input) the first entry from
 *                                                   which to begin reading
 *                                                    
 *              CEI_INT32 numberOfEntries -- (input) number of entries to read
 *                                                    
 *              pAR_SCHEDULED_MSG_ENTRY_TYPE
 *                  messageEntry          -- (input) array of structures of  
 *                                                message content read, each
 *                                                element defined as follows:
 *                                                  struct {
 *                                                    CEI_UINT32 messageIndex;                  
 *                                                    CEI_UINT32 board;                         
 *                                                    CEI_UINT32 channel;                       
 *                                                    CEI_UINT32 rate;                          
 *                                                    CEI_UINT32 start;                         
 *                                                    CEI_UINT32 txCount;               
 *                                                    CEI_UINT32 data; } 
 *                                                    
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                              ARS_INVARG      The starting entry plus the number of 
 *                                              entries requested to read exceeds the 
 *                                              size of the message scheduler table
 * 
 * GLOBALS:     device[]
 * 
 * DESCRIPTION: This routine returns the contents of the specified block of
 *              entries from the message scheduler table.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_read_scheduled_msg_block
(
   CEI_INT16 board,                          /* (input) board number (0-127)  */
   CEI_INT32 startingEntry,		            /* (input) first entry to read  */
   CEI_INT32 numberOfEntries,                /* (input) number of entries    */
   pAR_SCHEDULED_MSG_ENTRY_TYPE messageEntry /* (input) ptr to struct of msgs*/
);

/*===========================================================================*
 * ENTRY POINT:        AR_READ_MESSAGE_SCHEDULE_TABLE_ENTRY
 *===========================================================================*
 *
 * FUNCTION:    Retrieve an entry from the message scheduler table
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *              pCEI_UINT32 msgSchedTableEntry -- (output) array of 8 uint
 *
 * RETURN VAL:  CEI_INT16  -- ARS_NORMAL    success
 *                            ARS_INVBOARD  board parm value not supported
 *
 * GLOBALS:     device[]
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_read_message_schedule_table_entry 
(
   CEI_INT16   board,
   CEI_UINT32  messageIndex,
   pCEI_UINT32 msgSchedTableEntry
);

/*===========================================================================*
 * ENTRY POINT:             A R _ R E S E T
 *===========================================================================*
 *
 * FUNCTION:    Reset the device to the initial state
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  CEI_INT16  -- ARS_NORMAL    success
 *                            ARS_INVBOARD  board parm value not supported
 *
 * GLOBALS:     none
 * 
 * DESCRIPTION: see description for arx30_initialize_device()
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_reset
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ R E S E T _ T I M E R C N T
 *===========================================================================*
 *
 * FUNCTION:    This routine resets the 64-bit device timer to zero.
 * 
 * PARAMETERS:  CEI_INT16 board        -- (input) Board number (0 to 127)  
 *
 * GLOBALS:     device[]
 *
 *===========================================================================*/
EXPORT32 CEI_VOID DLL_EXPORTED arx30_reset_timercnt
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ S E T _ C O N F I G
 *===========================================================================*
 *
 * FUNCTION:    Initialize channel configuration, BusTools product specific.
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *              CEI_INT16 item   -- (input) item for which to set the 
 *                                             current state:
 * 
 *                    ARU_RX_CH**_BIT_RATE          ARU_DISCRETE_OUT*
 *                    ARU_TX_CH**_BIT_RATE          ARU_DISCRETE_OUT
 *                    ARU_RX_CH**_PARITY            ARU_DISCRETE_VALUES/ARU_DISCRETE_OUTPUTS
 *                    ARU_TX_CH**_PARITY            ARU_IRIG_INPUT_THRESHOLD  
 *                    ARU_TX_CH**_SHUT_OFF          ARU_INTERNAL_WRAP         
 *                    ARU_TX_CH**_HB_INJ            ARU_IRIG_QUICK_ADJUSTMENT 
 *                    ARU_TX_CH**_LB_INJ            ARU_IRIG_SET_BIAS         
 *                    ARU_TX_CH**_GAP_INJ           ARU_IRIG_WRAP_ENABLE
 *                    ARU_ACCESS_SNAPSHOT_BUFFER    ARU_IRIG_ADJUST_THRESHOLD
 *                                                  
 *                    ARU_RX_TIMETAG_MODE w/values of:                          
 *                                                     
 *                              AR_TIMETAG_EXT_IRIG_64BIT                         
 *                              AR_TIMETAG_INT_USEC_64BIT                         
 *                              AR_TIMETAG_INT_20USEC_32BIT                       
 *                              AR_TIMETAG_INT_MSEC_32BIT                         
 *                              AR_TIMETAG_HOST_SEC_32BIT                       
 *                              AR_TIMETAG_SYNC_1553_CH1 (for combo cards only)               
 *                              AR_TIMETAG_SYNC_1553_CH2                
 *                              AR_TIMETAG_SYNC_1553_CH3                
 *                              AR_TIMETAG_SYNC_1553_CH4                
 *                                                     
 *              CEI_UINT32 value -- (input) this is the value to which
 *                                      the specified item will be set
 * 
 * RETURN VAL:  CEI_INT16 -- ARS_NORMAL      Normal succesful completion.
 *                           ARS_INVARG      "item" parameter value is not
 *                                           supported by this function
 *                           ARS_INVHARVAL   Item was invalid or channel
 *                                           not supported on this device
 *                           ARS_INVBOARD    Board parameter value invalid or
 *                                           board has not been initialized
 *                           ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 * 
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: Calls the function arx30_set_device_config () with the
 *      channel(s) of interest based on the expected item definition.
 *      
 *      arx30_set_device_config() writes a 16-bit data word to a transmit or 
 *      receive channel configuration register, and should be used by any 
 *      application other than BusTools.
 *
 *      NOTE: The value passed into arx30_set_config is UNSIGNED SHORT, the 
 *            value passed here is CEI_UINT32, yet only the least
 *            signifciant 16 bits are considered.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_config 
( 
   CEI_INT16 board,                 /* (input)  board to reference (0 to 127) */
   CEI_INT16 item,                  /* (input)  item to process              */
   CEI_UINT32 value                 /* (input)  state of the item            */
);
               
/*===========================================================================*
 * ENTRY POINT:        A R _ S E T _ D E V I C E _ C O N F I G          
 *===========================================================================*
 *
 * FUNCTION:    Assign protocol-specific device configuration register attributes 
 * 
 * PARAMETERS:  CEI_INT16 board   -- (input) board to reference (0 to 127)
 *              CEI_INT16 channel -- (input) channel number (0 to # 429 channels)
 *              CEI_INT16 item    -- (input) channel config item to (re)set
 *              CEI_INT16 value   -- (input) value to set item to
 * 
 *              Valid combinations of item / value parameters are:
 * 
 *              for this "item"        valid options for "value" are:
 * 
 *              ARU_RX_BITRATE         ARU_SPEED_LOW   ARU_SPEED_HIGH  Custom Speed
 *              ARU_RX_PARITY          ARU_PARITY_NONE ARU_PARITY_ODD  ARU_PARITY_EVEN
 *                                     representing AR_OFF or AR_ON  
 *              ARU_RECV_MODE          AR_WRAP_OFF     AR_WRAP_ON
 * 
 *              ARU_TX_BITRATE         ARU_SPEED_LOW   ARU_SPEED_HIGH  Custom
 *              ARU_TX_PARITY          ARU_PARITY_NONE ARU_PARITY_ODD  ARU_PARITY_EVEN
 *
 *              ARU_RX_DISABLE         AR_ON           AR_OFF
 *              ARU_RX_FIFO_ENABLE     AR_ON           AR_OFF
 *              ARU_TX_DISABLE         AR_ON           AR_OFF
 *              ARU_TX_FIFO_ENABLE     AR_ON           AR_OFF
 *
 *              ARU_TX_GAP_ERROR       AR_ON           AR_OFF
 *              ARU_TX_BIT_ERROR       AR_HI   AR_LO   AR_OFF
 *
 *              ARU_DISCRETE_OUT       AR_HI           AR_LO
 *              ARU_DIGITAL_OUT        AR_HI           AR_LO
 *              ARU_DIFFERENTIAL_OUT   AR_ON   AR_OFF  AR_HI    AR_LO
 *
 *              ARU_RX_MERGED_MODE     AR_ON           AR_OFF
 *              ARU_FAST_SLEW_RATE     AR_ON           AR_OFF
 * 
 *              ARU_ACCESS_SNAPSHOT_BUFFER ARU_LABEL_ONLY   ARU_LABEL_WITH_SDI
 *              ARU_BYPASS_INIT_WRAP_TEST  AR_ON       AR_OFF
 *              ARU_MULTITHREAD_PROTECT    AR_ON       AR_OFF
 *              ARU_HW_INTERRUPT_ENABLE    AR_ON       AR_OFF       
 * 
 *              ARU_IRIG_WRAP_ENABLE   AR_ON           AR_OFF
 *              ARU_IRIG_OUTPUT_ENABLE AR_ON           AR_OFF
 *              ARU_IRIG_INPUT_THRESHOLD      threashold voltage in millivolts
 *              ARU_IRIG_ADJUST_THRESHOLD     display DAC settings AR_ON/AR_OFF
 *              ARU_IRIG_QUICK_ADJUSTMENT
 *              ARU_IRIG_SET_BIAS             user IRIG offset 0 to +/-32768 milliseconds
 *              ARU_HW_ENHANCE_UPDATE  AR_ON           AR_OFF
 *              ARU_RX_TIMETAG_MODE w/values of:                          
 *                                     AR_TIMETAG_EXT_IRIG_64BIT                         
 *                                     AR_TIMETAG_INT_USEC_64BIT                         
 *                                     AR_TIMETAG_INT_20USEC_32BIT                       
 *                                     AR_TIMETAG_INT_MSEC_32BIT
 *                                     AR_TIMETAG_SYNC_1553_CH1 (for combo cards only)               
 *                                     AR_TIMETAG_SYNC_1553_CH2                
 *                                     AR_TIMETAG_SYNC_1553_CH3                
 *                                     AR_TIMETAG_SYNC_1553_CH4                
 *                                                     
 * RETURN VAL:  CEI_INT16 status  -- ARS_NORMAL      Normal succesful completion.
 *                                   ARS_INVARG      "item" parameter value is not
 *                                                      supported by this function
 *                                   ARS_INVHARVAL   "value" was invalid or channel
 *                                                      not supported on this device
 *                                   ARS_INVBOARD    Board parameter value invalid or
 *                                                      board has not been initialized
 *                                   ARS_INT_ISR  &  Interrupt was either not initialized
 *                                   ARS_DRIVERFAIL     or not terminated successfully
 *                                   ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This function assigns the respective device configuration
 *              register attributes based on the combined item/value
 *              parameter selections.  It is designed to support the 
 *              ARINC 429 and all discrete and digital I/O configuration  
 *              register attributes available to the device.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_device_config 
( 
   CEI_INT16 board,          /* (input) board to reference (0 to 127)         */
   CEI_INT16 channel,        /* (input) channel number (0 to # 429 channels) */
   CEI_INT16 item,           /* (input) channel config item to (re)set       */
   CEI_INT16 value           /* (input) value to set item to                 */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ S E T _ 5 7 3 _ C O N F I G
 *===========================================================================*
 *
 * FUNCTION:    Set ARINC 573 channel configuration register attributes
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board to reference (0 to 127)
 *              CEI_INT16 item  -- (input) config register attribute to set
 *              CEI_INT32 value -- (input) value applied to item attribute
 * 
 *                  item                 valid values
 * 
 *              ARU_RECV_MODE            AR_WRAP_OFF, AR_WRAP_ON
 *              ARU_573_RX_AUTO_DETECT   AR_OFF, AR_ON
 *              ARU_573_RX_BPRZ_SELECT   AR_OFF, AR_ON
 *              ARU_573_TX_BPRZ_SELECT   AR_OFF, AR_ON
 *              ARU_573_TX_HBP_SELECT    AR_OFF, AR_ON
 *
 *              ARU_RX_BITRATE &         ARU_573_RATE_SIZE_384_32    
 *              ARU_TX_BITRATE           ARU_573_RATE_SIZE_768_64    
 *                                       ARU_573_RATE_SIZE_1536_128  
 *                                       ARU_573_RATE_SIZE_3072_256  
 *                                       ARU_573_RATE_SIZE_6144_512  
 *                                       ARU_573_RATE_SIZE_12288_1024
 *                                       ARU_573_RATE_SIZE_24576_2048
 *                                       ARU_573_RATE_SIZE_49152_4096
 * 
 *              ARU_573_TX_SLEW_RATE     ARU_573_TX_SLEW_1PT5
 *                                       ARU_573_TX_SLEW_10PT0
 * 
 *              ARU_TX_DISABLE           AR_OFF, AR_ON
 *              ARU_TX_FIFO_ENABLE       AR_OFF, AR_ON
 *              ARU_RX_FIFO_ENABLE       AR_OFF, AR_ON
 *              ARU_573_RX_ENABLE        AR_OFF, AR_ON
 * 
 *              ARU_573_SYNC_WORD1       value from 0x0000 to 0x0fff
 *              ARU_573_SYNC_WORD2       value from 0x0000 to 0x0fff
 *              ARU_573_SYNC_WORD3       value from 0x0000 to 0x0fff
 *              ARU_573_SYNC_WORD4       value from 0x0000 to 0x0fff
 *              ARU_RX_MERGED_MODE       AR_ON, AR_OFF
 * 
 *              (Following supported for legacy CEI-710 API only)
 *              ARU_RX_BITRATE &         ARU_573_SPEED_384  
 *              ARU_TX_BITRATE           ARU_573_SPEED_768  
 *                                       ARU_573_SPEED_1536 
 *                                       ARU_573_SPEED_3072 
 *                                       ARU_573_SPEED_6144 
 *                                       ARU_573_SPEED_12288
 *                                       ARU_573_SPEED_24576
 * 
 *              ARU_573_RX_SUBFRAME_SIZE ARU_573_SUB_FRAME_64  
 *                                       ARU_573_SUB_FRAME_128 
 *                                       ARU_573_SUB_FRAME_256 
 *                                       ARU_573_SUB_FRAME_512 
 *                                       ARU_573_SUB_FRAME_1024
 *                                       ARU_573_SUB_FRAME_2048
 *                                       ARU_573_SUB_FRAME_4096
 * 
 * RETURN VAL:  CEI_INT16 status -- ARS_NORMAL      Normal succesful completion.
 *                                  ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                                  ARS_INVARG      "item" parameter value is not supported by this 
 *                                                  function or device configuration. 
 *                                  ARS_INVHARVAL   "value" parameter value is not supported for "item"
 *                                  ARS_INVBOARD    board parameter value invalid or
 *                                                     board not initialized or ARINC 
 *                                                     573 not supported on this device
 * 
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *
 * DESCRIPTION: This function assigns the respective device configuration
 *              register attributes based on the combined item/value
 *              parameter selections.  It is designed to support the ARINC
 *              573/717 protocol configuration register attributes only.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_573_config 
( 
   CEI_INT16 board,                 /* (input)  board to reference (0 to 127) */
   CEI_INT16 item,                  /* (input)  item to process              */
   CEI_INT32 value                  /* (input)  state of the item            */
);  

/*===========================================================================*
 * ENTRY POINT:    A R _ S E T _ M U L T I T H R E A D _ P R O T E C T
 *===========================================================================*
 *
 * FUNCTION:    Enable/Disable Mutex Protection around device channel access
 * 
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *              CEI_INT16 state  -- (input) AR_ON / AR_OFF 
 *
 * GLOBALS:     device[]
 * 
 * RETURN VAL:  ARS_NORMAL       - Success
 *              ARS_INVARG       - state value not supported
 * 
 * DESCRIPTION: This function controls the execution of Win32 Mutex 
 *      protection around every Receive and Transmit Buffer access in the API.
 *      ON enables Mutex protection, OFF disables it.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_multithread_protect 
( 
   CEI_INT16 board,                  /* (input) board to reference (0 to 127) */ 
   CEI_INT16 state                   /* (input) AR_ON / AR_OFF               */
);

/*===========================================================================*
 * ENTRY POINT:        A R _ S E T _ I S R _ F U N C T I O N
 *===========================================================================*
 *
 * FUNCTION:    Define an application supplied ISR routine
 *
 * PARAMETERS:  deviceIndex   -- (input) device to reference (0 to 127)
 *              function      -- (input) void function to execute from ISR
 *
 * RETURN VAL:  ARS_NORMAL    -- Success
 *              ARS_INVBOARD  -- Invalid device ID parameter
 *              ARS_INVARG    -- State parameter value is invalid
 *
 * GLOBALS:     x30InterruptFunctionPtr[]
 *
 * DESCRIPTION: This routine assigns the supplied function pointer to an
 *              array of pointers indexed by device id.  This function will
 *              be invoked from cei_utl_interrupt_handler() instead of
 *              executing the "flush the h/w interrupt queue" processing.
 *
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_set_isr_function 
(
   CEI_INT32 deviceIndex,             /* the device identifier               */
   pCEI_VOID function                 /* multithread protect state selection */
);

/*===========================================================================*
 * ENTRY POINT:        A R _ S E T _ P R E L O A D _ C O N F I G
 *===========================================================================*
 *
 * FUNCTION:    Update a pre-load configuration setting.
 *
 * PARAMETERS:  CEI_INT16 board   -- (input) board to reference (0 to 127)
 *              CEI_INT16 item    -- (input) the item to define, with
 *                                           valid selections from:
 *                                              ARU_CONCURRENCY_MODE           
 *              CEI_UINT32 value  -- (input) the value to define the item 
 *                                           valid selections from:
 *                                              AR_CONC_NONE
 *                                              AR_CONC_MULTITHRD
 *                                              AR_CONC_MULTIPROC
 *           
 * GLOBALS:     device[]
 *              deviceGlobal[]
 *           
 * RETURN VAL:  ARS_NORMAL   -- semaphore was opened successfully
 *              ARS_INVBOARD -- invalid board number 
 *              ARS_INVARG   -- invalid item or value parameter
 *              ARS_NO_OS_SUPPORT -- item not supported on host o/s
 *              ARS_BOARD_MUTEX -- failed to create/open the semaphore
 *
 * DESCRIPTION: Call this routine before calling AR_LOADSLV to update the 
 *              value of a particular load configuration setting.  This 
 *              routine should not be called after the calling process has 
 *              executed AR_LOADSLV.
 *
 *              If 'item' is ARU_CONCURRENCY_MODE, the 'value' parameter 
 *              specifies the board concurrency mode.  One of three modes may
 *              be selected: AR_CONC_NONE, AR_CONC_MULTITHRD, or 
 *              AR_CONC_MULTIPROC.  Note that some modes are only supported
 *              on certain boards and operating systems.  Refer to the
 *              AR_SET_PRELOAD_CONFIG documentation in the CEI-x30 User's 
 *              Manual to determine if a particular concurrency mode is 
 *              supported on a certain board and operating system.
 *
 *              The default concurrency mode, AR_CONC_NONE, provides no multi-
 *              thread protection and no multi-process support.  The user 
 *              application must ensure that at most one thread is calling 
 *              into the API at any given time, and only a single process may 
 *              interface with a particular board.
 *
 *              If AR_CONC_MULTITHRD concurrency mode is selected, thread
 *              protection is provided internally within the API.  The user 
 *              application may call into the API from multiple threads, but
 *              all threads must belong to a single process.  The main user
 *              application thread should initialize the board with a call to
 *              AR_LOADSLV before other threads attempt to call into the API.
 *
 *              If AR_CONC_MULTIPROC concurrency mode is selected, thread
 *              protection is provided internally within the API and multiple
 *              processes may interface with a single board.  If any process 
 *              requests multi-process mode, all other processes must also
 *              request multi-process mode.
 *
 *              Some coordination is required when using multiple processes in
 *              conjunction with a single CEI-x30 device.  A single "board" 
 *              process should be launched to configure board-specific and 
 *              application-wide attributes and invoke data processing using
 *              AR_GO.  After the "board" process launches the board it is
 *              then permissible to launch one or more "channel" processes.
 *              A "channel" process should first attach to the board via 
 *              AR_LOADSLV, then execute operations strictly confined to the 
 *              particular channel(s) that process is associated with (e.g., 
 *              AR_GETWORD, AR_PUTWORD, AR_SET_CONFIG, etc.).  When finished,
 *              the "channel" process should invoke AR_CLOSE and terminate.
 *              The "board" process should remain running until all "channel"
 *              processes have terminated; afterwhich, it should invoke 
 *              AR_CLOSEand terminate.
 *
 *              All processes must exercise caution when modifying board
 *              settings that may impact other concurrently-running processes.
 *
 *              Note that board setup/initialization is only executed in 
 *              AR_LOADSLV if no other processes have the board open.  If
 *              another process has the board open (that is, if another process
 *              has opened the board using AR_LOADSLV but hasn't yet closed the
 *              board using AR_CLOSE), AR_LOADSLV attaches to the device
 *              without re-initializing the board or modifying board settings.
 *              Similarly, AR_CLOSE only shuts down the board if no other 
 *              processes have the board open.  If another process has the 
 *              board open, AR_CLOSE detaches from the board without shutting 
 *              it down.  Thus, board settings are preserved across "channel" 
 *              process invocations of AR_LOADSLV and AR_CLOSE.  Note the 
 *              importance of matching every call to AR_LOADSLV with a call to
 *              AR_CLOSE in multi-process mode.
 *              
 *              Multi-process mode is only required when accessing a single 
 *              board from multiple processes.  If multiple boards are 
 *              installed, AR_CONC_NONE concurrency mode can be used as long
 *              as only one process interfaces with each board.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_preload_config
(
   CEI_INT16  board,                 /* (input) board to reference (0 to 127) */ 
   CEI_INT16  item,                  /* (input) the item to define           */
   CEI_UINT32 value                  /* (input) the value to define the item */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ S E T _ R A W _ M O D E
 *===========================================================================*
 *
 * FUNCTION:    Enable/Disable ARINC 429 Parity Mode
 * 
 * PARAMETERS:  CEI_INT16 board     -- (input) board to reference (0 to 127)
 *              CEI_INT16 direction -- (input) TRANSMIT_CHANNEL / RECEIVE_CHANNEL
 *                                         alternates: ARU_XMIT / ARU_RECV
 *              CEI_INT16 channel   -- (input) channel number (0 to 7)
 *              CEI_INT16 control   -- (input) AR_ON / AR_OFF
 *
 * GLOBALS:     none
 * 
 * RETURN VAL:  CEI_INT16     -- ARS_NORMAL     Normal succesful completion.
 *                               ARS_INVARG     direction, channel or control  
 *                                              parameter value is invalid
 *                               ARS_INVBOARD   Board parameter value invalid or
 *                                              board has not been initialized
 *                               ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 * 
 * DESCRIPTION: This routine assigns the state of the transmitter and receiver
 *              parity control bits based on the specified state of "Raw Mode"; 
 *              where raw mode ON disables parity for the respective channel 
 *              and OFF enables ODD parity by default.  The OFF mode defaults 
 *              to ODD PARITY.
 * 
 *              This routine is provided for x20 compatibility.  The proper
 *              method of assigning parity is via arx30_set_device_config().
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_raw_mode 
( 
   CEI_INT16 board,            /* (input) board to reference (0 to 127)       */
   CEI_INT16 direction,        /* (input) TRANSMIT_CHANNEL / RECEIVE_CHANNEL */
   CEI_INT16 channel,          /* (input) channel number (0 to 7)            */
   CEI_INT16 control           /* (input) AR_ON / AR_OFF                     */
);

/*===========================================================================*
 * ENTRY POINT:      A R _ S E T _ S T O R A G E _ M O D E
 *===========================================================================*
 *
 * FUNCTION:    Set board-level receive data storage mode
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board index (0 to 127)
 *              CEI_INT16 mode  -- (input) valid values are:
 *                                 ARU_BUFFERED  individual buffer per channel
 *                                 ARU_DEDICATED individual buffer per channel
 *                                 ARU_MERGED    one merged circular buffer
 *
 * RETURN VAL:  ARS_NORMAL      Success
 *              ARS_INVARG      "mode" parameter value is not supported
 *              ARS_INVBOARD    Invalid board parameter or board not initialized
 *              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine assigns the respective storage mode to all
 *              receiver channels, all Merged or all Buffered.
 *
 *              This routine is provided for backward compatibility with
 *              the CEI-710 API.  The proper method to assign the Merged
 *              Receive Mode is provided for individual channels via the 
 *              respective channel set-config routine using the item
 *              parameter value ARU_RX_MERGED_MODE and its ON/OFF selection.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_storage_mode 
(  
   CEI_INT16 board,    /* (input) board index (0 to 127)                      */
   CEI_INT16 mode      /* (input) storage mode (ARU_BUFFERED or ARU_MERGED)  */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ S E T _ T I M E
 *===========================================================================*
 *
 * FUNCTION:    This routine sets either the CEI-830 internal 64-bit timer   
 *              or the IRIG output time based on an application-supplied value.
 *
 * PARAMETERS:  CEI_INT16 board -- (input)  Board number (0 to 127)  
 * 
 *              pAR_TIMETAG_TYPE timeTagRef -- (input)
 *                             ->timeTagFormat -- timer to assign and format
 *                                                of the "timeTag" value
 *                                              AR_TIMETAG_EXT_IRIG_64BIT
 *                                              AR_TIMETAG_INT_USEC_64BIT
 * 
 *                             ->timeTag -- timer value to assign in the 
 *                                          format specified via "timeTagFormat"
 *                                          For timeTagFormat of ...IRIG... the
 *                                          format of timeTag is BCD, as defined
 *                                          in the User Manual for the IRIG time
 *                                          register.
 *                                          For timeTagFormat of ...USEC... the
 *                                          format of timeTag is a 64-bit integer 
 *                                          value with a 1 microsecond resolution.
 *
 *                             ->referenceTimeTag -- not used
 * 
 * RETURN VAL:  CEI_INT32    -- ARS_NORMAL      Success
 *                              ARS_INVBOARD    Invalid or uninitialized board
 *                              ARS_INVARG      Invalid timeTagFormat selection
 *                              ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_time 
(
   CEI_INT16 board,                  /* (input) board to reference (0 to 127) */
   pAR_TIMETAG_TYPE timeTag          /* (input) selected timer and value     */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ S E T _ T I M E R R A T E
 *===========================================================================*
 *
 * FUNCTION:    This routine assigns the CEI-x20 compatible timer resolution
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board index (0 to 127)
 *              CEI_INT16 rate  -- (input) resolution of the CEI-x20-type timer
 *                                         in 250 nanoseconds.  Note the CEI-x30
 *                                         message scheduler rate resolution is
 *                                         1ms, so the resolution of the rate
 *                                         value should be 4000 to match.
 * RETURN VAL:  none
 *
 * GLOBALS:     deviceGlobal[]
 * 
 *===========================================================================*/
EXPORT32 CEI_VOID  DLL_EXPORTED arx30_set_timerrate 
(
   CEI_INT16 board,  /* (input) board index (0 to 127)                        */
   CEI_INT16 rate    /* (input) resolution of the CEI-x20-type timer (usec)  */
);

/*===========================================================================*
 * ENTRY POINT:      A R _ S E T _ T R A N S M I T T E R _ M O D E
 *===========================================================================*
 *
 * FUNCTION:    Set the ARINC 717 transmitter mode
 *
 * PARAMETERS:  CEI_INT16 board -- (input) board index (0 to 127)
 *              CEI_INT16 mode  -- (input) valid values are:
 *
 * RETURN VAL:  ARS_NORMAL       Success
 *              ARS_INVHARVAL    "mode" parameter value is not supported
 *                               Or selected protocol is not available
 *              ARS_INVBOARD     Invalid board parameter or board not initialized
 *              ARS_BOARD_MUTEX  Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 *              deviceGlobal[]
 * 
 * DESCRIPTION: This routine enables the respective transmitter definition
 *              for the ARINC 573/717 channel. 
 *
 *              This routine is provided for backward compatibility with
 *              the CEI-710 API.  The proper method to assign the ARINC 573
 *              Encoding as BPRZ or HBP is provided for individual channel(s) 
 *              via the arx30_set_573_config routine using the item parameter
 *              values ARU_573_TX_HBP_SELECT and ARU_573_TX_BPRZ_SELECT.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_set_transmitter_mode 
(
   CEI_INT16 board,   /* (input)  board index (0 to 127)                      */
   CEI_INT16 mode     /* (input)  transmitter mode (CSDB 717-HBP or 717-BPRZ */
);

/*===========================================================================*
 * ENTRY POINT:             A R _ S T O P
 *===========================================================================*
 *
 * FUNCTION:    Disable the transmitter and receiver FIFOs on the device
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) board to reference (0 to 127)
 *
 * RETURN VAL:  CEI_INT16  -- ARS_NORMAL       Success
 *                            ARS_INVBOARD     Invalid board parameter
 *                                                or board not initialized
 *                            ARS_BOARD_MUTEX  Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     device[]
 * 
 * DESCRIPTION: Sets the global enable register global enable bit to DISABLE
 *              and disables the CEI-830 message scheduler
 *
 *===========================================================================*/
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_stop
(
   CEI_INT16 board                  /* (input)  board to reference (0 to 127) */
);

/*===========================================================================*
 * ENTRY POINT:         A R _ V E R S I O N
 *===========================================================================*
 *
 * FUNCTION:    Return the software version
 * 
 * PARAMETERS:  pCEI_CHAR verstr -- (output) string containing version.
 * 
 * RETURN VAL:  CEI_VOID 
 *
 * GLOBALS:     none
 * 
 * DESCRIPTION: The software version API_VERSION defined in cdev_api.h is 
 *      copied to the string parameter (verstr) passed into this function.
 * 
 *===========================================================================*/ 
EXPORT32 CEI_VOID DLL_EXPORTED arx30_version
(
   pCEI_CHAR verstr
);

/*===========================================================================*
 * ENTRY POINT:   A R _ W A I T 
 *===========================================================================*
 *
 * FUNCTION:    Wait for the specified number of seconds
 * 
 * PARAMETERS:  CEI_FLOAT nsecs -- (input) number of seconds to wait for
 * 
 * RETURN VAL:  CEI_VOID
 *
 * GLOBALS:     none
 * 
 * DESCRIPTION: Delay the specified number of seconds based on the OS
 *              timer function clock() and the value of TIMER_CLOCK_TICKS_PER_SECOND
 *              (see <time.h>)
 *                    
 *===========================================================================*/ 
EXPORT32 CEI_VOID DLL_EXPORTED arx30_wait
(
   CEI_FLOAT nsecs
);


/*===========================================================================*
 * ENTRY POINT:            A R _ I N I T _ S L A V E
 *===========================================================================*
 *
 * FUNCTION:    Initialize the device transmit and receive buffers
 *
 * PARAMETERS:  CEI_INT16 board  -- (input) device number to reference (0-127)
 *
 * RETURN VAL:  CEI_INT16    -- ARS_NORMAL       Success
 *                              ARS_INVBOARD     Invalid board parameter
 *                              ARS_BOARD_MUTEX  Access to the Board Lock timed-out/failed
 *
 * GLOBALS:     deviceGlobal[board]
 * 
 * DESCRIPTION: This routine initializes/flushes the device's transmit and 
 *              receive buffers.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT16  DLL_EXPORTED arx30_init_slave (CEI_INT16 board);

/*===========================================================================*
 * ENTRY POINT:         A R _ X M I T _ S Y N C
 *===========================================================================*
 *
 * FUNCTION:    This routine is used to wait for all of the data in the
 *              transmit queue to be sent.  It is useful for a program
 *              that wants to reset the slave, but needs to wait for it
 *              to complete transmission before halting it.  It will
 *              self-terminate if the transmit FIFO hasn't completed
 *              flushing all messages after 12 seconds.
 *
 * PARAMETERS:  CEI_INT16 cardnum  -- (input) The board number of interest
 *              CEI_INT16 channel  -- (input) The transmit channel
 *
 * RETURN VAL:  CEI_INT16   -- ARS_NORMAL      Success
 *                             ARS_INVBOARD    Board parameter value invalid or
 *                                                board has not been initialized
 *                             ARS_NOSYNC      Twelve seconds elapsed without
 *                                                completing the Tx FIFO flush
 *                             ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *                             ARS_NODATA      The board is not in active processing mode
 *
 * GLOBALS:     deviceGlobal[board].boardInitialized
 *              device[board].arincDevicePtr
 *
 * DESCRIPTION: This is a utility that waits for all the data in the transmit
 *              buffer to be loaded into the ARINC transmitter.  It is useful
 *              in an application that is sending data out but doesn't want
 *              to halt the interface until everything has been sent.
 *
 *===========================================================================*/
EXPORT32 CEI_INT16  DLL_EXPORTED arx30_xmit_sync (CEI_INT16 board, CEI_INT16 channel);

/*===========================================================================*
 * ENTRY POINT:              A R _ S E T C H P A R M S
 *===========================================================================*
 *
 * FUNCTION:    Define the operating parameters and modes for an ARINC 429
 *              receiver and/or transmitter.  This routine provides compatibility
 *              with the CEI-x20 API method for assigning channel configurations.
 *
 * PARAMETERS:  CEI_UINT32 cardnum    (i) The board number of interest
 *              CEI_UINT32 channel    (i) The channel to which to set the data (0-based)
 *              CEI_INT32 TransRcv    (i) Set parameters for ARU_TRANSMITTER or ARU_RECEIVER
 *              pAR_CHANNEL_PARMS def (i) Pointer to channel parameter structure
 *
 * RETURN VAL:  CEI_INT32 status ARS_NORMAL      Normal succesful completion.
 *                               ARS_INVARG      Invalid channel parameter value 
 *                                                  was supplied for the TransRcv value
 *                               ARS_INVHARVAL   Structure member value is invalid
 *                               ARS_INVBOARD    Board parameter value invalid or
 *                                                  board has not been initialized
 *                               ARS_BOARD_MUTEX Access to the Board Lock timed-out/failed
 *
 * DESCRIPTION: This function is used to configure an ARINC 429 transmitter or
 *              receiver.
 *
 * GLOBALS:     deviceGlobal[board]
 *
 *===========================================================================*/
EXPORT32 CEI_INT32  DLL_EXPORTED arx30_setchparms (CEI_UINT32 cardnum, CEI_UINT32 channel, CEI_INT32 TransRcv, pAR_CHANNEL_PARMS def);


/*===========================================================================*
 * ENTRY POINT:             A R _ S L E E P
 *===========================================================================*
 *
 * FUNCTION:    Execute the o/s specific C library Sleep function
 *
 * PARAMETERS:  CEI_UINT32 sleep_ms    (i) The number of milliseconds to sleep
 *
 * DESCRIPTION: This function is used to invoke the current o/s supported C
 *              Sleep routine with the specified number of milliseconds to
 *              sleep.  If the current o/s uses a task delay invocation instead
 *              of a sleep routine, the sleep_ms will be converted based on
 *              that task delay duration resolution.
 *
 *===========================================================================*/
EXPORT32 CEI_VOID DLL_EXPORTED arx30_sleep (CEI_UINT32 sleep_ms);

#if 1 //defined (_LINUX_X86_) || defined (_LINUX_PPC_)
/*===========================================================================*
 * ENTRY POINT:     A R _ S E T _ B A S E _ A D D R E S S E S
 *===========================================================================*
 *
 * FUNCTION:    This routine provides a method to supply the BAR0 and BAR2
 *              virtual address pointers to the base address assigned
 *              to the device acquired from a custom embedded host device driver.
 *
 * PARAMETERS:  CEI_INT16  board       -- (input) board to reference (0 to 127)
 *              CEI_ULONG  bar0Address -- (input) virtual address for BAR0
 *              CEI_ULONG  bar2Address -- (input) virtual address for BAR2
 *
 * RETURN VAL:  ARS_INVBOARD  board parm invalid
 * 
 * GLOBALS:     device[board].devicePtr
 * 
 * DESCRIPTION: This routine provides a method for any embedded platform
 *              application to bypass the standard device driver/host interface
 *              to acquire the device memory resources and supply the device
 *              BAR0 and BAR2 virtual base addresses to the API.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_set_base_addresses
(
   CEI_INT16 board,                 /* (input) board to reference (0 to 127) */
   uintptr_t bar0Address,           /* (input) virtual address for BAR0      */
   uintptr_t bar2Address,           /* (input) virtual address for BAR2      */
   CEI_UINT16 vendID,               /* vendor ID */
   CEI_UINT16 devID                 /* device ID */
);

#if 0
/*===========================================================================*
 * ENTRY POINT:     A R _ S E T _ B O A R D _ I D E N T I T Y
 *===========================================================================*
 *
 * FUNCTION:    This routine provides a method to supply the PCI Configuration
 *              space attributes for Manufacturer and Device ID when the API
 *              is used in conjunction with a user-supplied Linux driver
 *
 * PARAMETERS:  CEI_INT16  board          -- (input) board to reference (0 to 127)
 *              CEI_UINT32 manufacturerId -- (input) virtual address for BAR0
 *              CEI_UINT32 deviceId       -- (input) virtual address for BAR2
 *
 * RETURN VAL:  ARS_INVBOARD  board parm invalid
 * 
 * GLOBALS:     device[board].devicePtr
 * 
 * DESCRIPTION: This routine provides a method for any embedded platform
 *              application to bypass the standard device driver/host interface
 *              to acquire the board's PCI Configuration space attributes for 
 *              Manufacturer and Device ID.
 * 
 *===========================================================================*/
EXPORT32 CEI_INT32 DLL_EXPORTED arx30_set_board_identity
(
   CEI_INT16  board,                 /* (input) board to reference (0 to 127)    */
   CEI_UINT32 manufacturerId,        /* (input) PCI Manufacturer Identification */
   CEI_UINT32 deviceId               /* (input) PCI Device Identification       */
);
#endif
#endif
/*===========================================================================*  
 *  CEI-x20 Link-Compatibility API Function prototypes 
 *===========================================================================*/             
#if 0   // Not needed for Simulink Real-Time
EXPORT32 CEI_INT16  DLL_EXPORTED ar_init_dual_port (CEI_INT16 board);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_get_raw_mode (CEI_INT16 board, CEI_INT16 direction, CEI_INT16 channel);
EXPORT32 CEI_UINT16 DLL_EXPORTED ar_get_timercnt (CEI_INT16 board);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_int_control (CEI_INT16 board, CEI_INT16 channel, CEI_INT16 flag);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_recreate_parity (pCEI_UCHAR word);
#ifndef INTEGRITY_PCI_PPC
EXPORT32 CEI_INT32  DLL_EXPORTED ar_dump_dp(CEI_INT16 board, pCEI_CHAR file_name, pCEI_CHAR msg);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_force_version (CEI_INT16 board, CEI_INT16 number);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_formatarinclabel (CEI_UINT32 label_data, pCEI_CHAR labelstr);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_formatbinarylabel (CEI_UINT32 label_data, CEI_INT32 trunc_label, CEI_CHAR *labelstr);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_get_errorLV (pCEI_CHAR string, CEI_INT16 status);
EXPORT32 CEI_INT32  DLL_EXPORTED ar_get_harris (CEI_INT16 board, CEI_INT16 item);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_int_set (CEI_INT16 board, CEI_INT32 int_num);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_int_slave (CEI_INT16 board);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_loadslv_init_discrete (CEI_INT16 board, CEI_UINT32 base_seg, CEI_INT32 base_port, CEI_UINT16 ram_size, CEI_UINT32 disc_init);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_msg_control (CEI_INT16 board, CEI_INT16 control);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_putword2x16 (CEI_INT16 board, CEI_INT16 channel, CEI_INT16 lsw, CEI_INT16 msw);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_reformat (pCEI_VOID lsw, pCEI_VOID msw);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_reset_int (CEI_INT16 board);
EXPORT32 CEI_INT32  DLL_EXPORTED ar_setinterrupts (CEI_UINT32 cardnum, CEI_UINT32 channel, CEI_INT32 TransRcv, CEI_UINT32 Count, CEI_UINT32 Mask);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_set_arinc_config (CEI_INT16 board, CEI_INT16 channel, CEI_INT16 item, CEI_UINT32 value);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_set_harris (CEI_INT16 board, CEI_INT16 item, CEI_UINT32 value);
EXPORT32 CEI_INT16  DLL_EXPORTED ar_timetag_control (CEI_INT16 board, CEI_INT16 flag);
EXPORT32 CEI_VOID   DLL_EXPORTED ar_unformat (pCEI_INT16 lsword, pCEI_INT16 msword);
#endif
#endif

#if defined (_WIN32) || defined (__QNX__)
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_config_channels_from_txt_file
(
	CEI_INT16 BoardIdx,			   /* (input) Board Index for channel configuration*/
	pCEI_CHAR cfgFileName          /* (input) channel configuration file name */
);
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_define_messages_from_txt_file
(
   pCEI_CHAR cfgFileName          /* (input) channel configuration file name */
);
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_channel_configuration_from_xml_file
(
   pCEI_CHAR pcCfgFileName, /* (input) channel configuration XML file name */
   CEI_INT16 cint16BrdIdx   /* (input) board index*/
);
EXPORT32 CEI_INT16 DLL_EXPORTED arx30_define_messages_from_xml_file
(
   pCEI_CHAR pcSMFileName /* (input) schedule message XML file name */
);
#endif

#ifdef __cplusplus
}
#endif
#endif /* CEIDEV_API_H */
