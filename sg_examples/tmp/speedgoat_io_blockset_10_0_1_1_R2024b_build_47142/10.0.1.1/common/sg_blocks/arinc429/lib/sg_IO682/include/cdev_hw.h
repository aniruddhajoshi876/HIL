/*===========================================================================*
 * FILE:                        C D E V _ H W . H
 *===========================================================================*
 *
 * COPYRIGHT (C) 2003-2013  BY
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
 * FUNCTION:   I/O Definition header file for the CEI-x30 Host Interface.
 * 
 *---------------------------------------------------------------------------*
 *          
 * HISTORY:   
 *
 *   Date     By  Comments
 * --------  ---- ------------------------------------------------------
 * 10/30/01  BDW  Created for the CEI-715.
 * 10/21/05  BDW  Added support for the CEI-430 PLX PCI9030 Interface
 * 05/01/06  BDW  Modified the board configuration mask value
 * 08/24/06  BDW  Incorporated CEI_TYPES.H data type definitions in 
 *                  support of 64-bit Linux operating systems.
 * 02/22/07  BDW  Added PCI Manufacturer and Device IDs for x30 products 
 * 07/24/07  BDW  Support for R830RX redefined CEIDEV_MAX_RX_CHAN to 32
 *                  Added Global Enable Reg bit CEIDEV_IRIG_830RX_IRIG_ENABLE
 * 04/15/09  BDW  Incorporated support for the CEI-x30 Enhanced Firmware Design.
 *                Modified register and buffer offsets and bit field constants 
 *                defined for accessing Channel Registers and Buffers, Message 
 *                Schedule Table, Label Filter Table, and Snapshot Buffer.
 *                Added CEIDEV_CSR_FIFO_INVALID_MSG for "bad msg length" status
 * 06/19/09  BDW  Added PLX PROM update constants for enhanced BAR2 size req't
 * 05/19/10  BDW  Added the PCI device ID for RAR-PCIE & FPGA parametric registers
 * 09/13/11  BDW  Added support for the CEI-430A with PCI_DEVICE_ID_430A definition
 * 02/15/12  BDW  Added PCI Device ID definitions for latest 1553 boards
 * 02/21/12  BDW  Added RAR15-XMC UCA Timer (Sync) Register offsets for 1553 CH 1-4
 * 07/10/12  BDW  Due to increased number of configurations, definitions for both
 *                CEIDEV_ALT_CONFIGURATION_717 and CEIDEV_ALT_CONFIGURATION_MASK
 *                had to change, CEIDEV_ALT_CONFIG_717_SHIFT was added to replace 
 *                a fixed value of 4.
 * 08/03/12  BDW  Added def. CEIDEV_CSR_FIFO_OVERFLOW for new Rx Chan Status Reg bit
 * 09/21/12  BDW  Added programmable channel types CEIDEV_CH_TYPE_PROG_ARINC429_TX
 *                and CEIDEV_CH_TYPE_PROG_ARINC429_RX
 * 04/08/13  BDW  Added support for the RCEI-830X820, including the PCI Device
 *                Id assignment for PCI Configuration Space: PCI_DEVICE_ID_830X820
 * 10/03/13  BDW  Added support for the RCEI-830A, including the PCI Device
 *                Id assignment for PCI Configuration Space: PCI_DEVICE_ID_RCEI830A
 *                and reference to new PCI_DEVICE_ID_RP708
 *===========================================================================*/

/*---------------------------------------------------------------------------*
 * Register Addresses
 *---------------------------------------------------------------------------*/

#ifndef CDEV_HW_H
#define CDEV_HW_H

#define CEIDEV_MAX_BRD_IDX                15  /* for use only in configuration file references */
#define CEIDEV_MAX_CHANNEL_NUMBER         255
#define CEIDEV_MAX_CHANNELS               CEIDEV_MAX_CHANNEL_NUMBER + 1     
#define CEIDEV_CHANNEL_MASK               (CEI_UINT32)0x000000ff
#define CEIDEV_MAX_RX_CHAN                32
#define CEIDEV_MAX_TX_CHAN                32
#define CEIDEV_RAR15_XT_MAX_TX_CHAN       8

#define CEIDEV_MAX_BIT_RATE               150000
#define CEIDEV_MIN_BIT_RATE               200


/*---------------------------------------------------------------------------*
 * CEI-x30 BRIDGED PCI INTERFACES
 * Device PLX PCI Interface Register Definitions
 *---------------------------------------------------------------------------*/
#define PLX_CONFIG_MEM_DESCRIPTOR_REG     6                           /* PLX9056 */
#define PLX_CONFIG_INT_CTRL_STAT_REG      26
#define PLX_CONFIG_MEM_CONTROL_REG        27
#define PLX_CONFIG_MEM_FPGA_TYPE          30
#define PLX_CONFIG_MEM_CSUM_READ          31
#define PLX_CONFIG_X30_IDENTITY           31
#define PLX_CONFIG_PWR_MGMT_CTRL_REG      68

#define PLX9056_LOCAL_INT_INP_ENABLE      (CEI_UINT32)0x00000900
#define PLX9056_CTRL_REG_DEFAULT          (CEI_UINT32)0x100D767E
#define PLX9056_CTRL_REG_SET_SW_RESET     (CEI_UINT32)0x500D767E
#define PLX9056_CTRL_REG_SET_EE_RELOAD    (CEI_UINT32)0x300D767E
#define PLX9056_CTRL_REG_SET_USER0_LOW    (CEI_UINT32)0x100C767E
#define PLX9056_MEM_DESC_REG_BUS0_SEL     (CEI_UINT32)0x42030307
#define PLX9056_MEM_DESC_REG_BUS0_NORM    (CEI_UINT32)0x42030343
#define PLX9056_FPGA_LOAD_COMPLETE_MASK   (CEI_UINT32)0x00020000
#define PLX9056_CONFIG_MEM_CSUM_MASK      (CEI_UINT32)0x0001001F

#define PLX_x30_CONFIG_MASK               (CEI_UINT32)0x0000201F
#define PLX_430_CONFIG                    (CEI_UINT32)0x00002000
#define PLX_830_CONFIG                    (CEI_UINT32)0x00000000
#define PLX_x30_32BIT_CONFIG              (CEI_UINT32)0x000000E0
#define PLX_A30_CONFIG                    (CEI_UINT32)0x00000040

#define PLX9030_LOC_AD_SP_BUS0_DESC       10 /* byte offset 28h */
#define PLX9030_CHIP_SEL_0_BASE_ADD       15 /* byte offset 3Ch */
#define PLX9030_CHIP_SEL_1_BASE_ADD       16 /* byte offset 40h */
#define PLX9030_CFG_INT_CTRL_STAT_REG     19 /* byte offset 4Ch */
#define PLX9030_PCI_TARGET_RESPONSE       20 /* byte offset 50h */      /* PLX9030 */
#define PLX9030_GEN_PURP_IO_CTRL          21 /* byte offset 54h */
#define PLX9030_LOCAL_INT_INP_ENABLE      (CEI_UINT32)0x00000041 /* Active Low */
#define PLX9030_CONFIG_MEM_CSM_MASK       (CEI_UINT32)0x00001FF0
#define PLX9030_CTRL_REG_SET_SW_RESET     (CEI_UINT32)0x40245300
#define PLX9030_CTRL_REG_DEFAULT          (CEI_UINT32)0x00245300
#define PLX9030_LOC_ADDR_SPACE_0_DESC     (CEI_UINT32)0x00928000 
#define PLX9030_GPIO_CTRL_REG_1           (CEI_UINT32)0x00000080 
#define PLX9030_GPIO_CTRL_REG_2           (CEI_UINT32)0x00000480 
#define PLX9030_GPIO_CTRL_REG_3           (CEI_UINT32)0x00000481 
#define PLX9030_FPGA_LOAD_COMPLETE_MASK   (CEI_UINT32)0x04000000 

#define PLX_9056                          9056
#define PLX_9056_BAR2_SIZE_WORD_1         0x0000000A
#define PLX_9056_BAR2_SIZE_WORD_2         0x0000000B
#define PLX_9030                          9030
#define PLX_9030_BAR2_SIZE_WORD_1         0x00000014
#define PLX_9030_BAR2_SIZE_WORD_2         0x00000015
#define PLX_BAR2_ENHANCED_SIZE_1          0x0000FFF8
#define PLX_BAR2_ENHANCED_SIZE_2          0
#define PLX_BAR2_ORIGINAL_SIZE_1          0x0000FFFF
#define PLX_BAR2_ORIGINAL_SIZE_2          0x0000F000
#define PLX_EEPROM_SIZE                   24
#define PLX_ENHANCED_CHECK                0
#define PLX_ENHANCED_UPDATE               1
#define PLX_ORIGINAL_RESTORE              2

#define EESK  0x01000000
#define EECS  0x02000000
#define EEDI  0x04000000
#define EEDO  0x08000000
#define EEDS  0x80000000

#define PCI_X30_MANUF_ID                  0x000013C6
#define PCI_DEVICE_ID_830                 0x00000830
#define PCI_DEVICE_ID_830RX               0x00000831
#define PCI_DEVICE_ID_830X820             0x00000832
#define PCI_DEVICE_ID_RCEI830A            0x0000830A
#define PCI_DEVICE_ID_630                 0x00000630
#define PCI_DEVICE_ID_530                 0x00000530
#define PCI_DEVICE_ID_430                 0x00000430
#define PCI_DEVICE_ID_430A                0x0000430A
#define PCI_DEVICE_ID_A30                 0x00001009
#define PCI_DEVICE_ID_RAREC               0x0000100A
#define PCI_DEVICE_ID_RAR_PCIE            0x0000100B
#define PCI_DEVICE_ID_RAR_XMC             0x0000100C

#define PCI_DEVICE_ID_RAR15               0x00001530
#define PCI_DEVICE_ID_RAR15XT             0x00001542

#define PCI_DEVICE_ID_CNIC                0x0000AFD0
#define PCI_DEVICE_ID_EC_CNIC             0x0000AFD1
#define PCI_DEVICE_ID_RCNIC               0x0000AFD2
#define PCI_DEVICE_ID_708                 0x00000708
#define PCI_DEVICE_ID_RP708               0x0000708A
#define PCI_DEVICE_ID_520                 0x00000520
#define PCI_DEVICE_ID_620                 0x00000620
#define PCI_DEVICE_ID_820                 0x00000820
#define PCI_DEVICE_ID_PMD1                0x00001001
#define PCI_DEVICE_ID_PMD2                0x00001002
#define PCI_DEVICE_ID_EPMC                0x00001003
#define PCI_DEVICE_ID_PSER                0x00001004
#define PCI_DEVICE_ID_PMIO                0x00001005
#define PCI_DEVICE_ID_PDIS                0x00001006
#define PCI_DEVICE_ID_P10S                0x00001007
#define PCI_DEVICE_ID_AMC                 0x00001008
#define PCI_DEVICE_ID_1553                0x00001553
#define PCI_DEVICE_ID_QPCI                0x00001554
#define PCI_DEVICE_ID_QCP                 0x00001555
#define PCI_DEVICE_ID_QPCX                0x00001557
#define PCI_DEVICE_ID_R15EC               0x00001558
#define PCI_DEVICE_ID_RXMC                0x00001559
#define PCI_DEVICE_ID_RPCIE               0x0000155A
#define PCI_DEVICE_ID_LPCIE               0x0000155B
#define PCI_DEVICE_ID_RXMC2               0x0000155C

/*---------------------------------------------------------------------------*
 * CEI-x30 HOST INTERFACE
 * Device I/O Register and Buffer Address Definitions
 *---------------------------------------------------------------------------*/
                                                      /* Generic CEI-x30 Registers       */
#define CEIDEV_GLOBAL_ENABLE              0x00000000  /* GLOBAL ENABLE (CONTROL REGISTER)*/

#define CEIDEV_DAC_CONTROL                0x00000001  /* DAC CONTROL_REG                 */
#define CEIDEV_TIMER_LOW                  0x00000002  /* 64-BIT 1USEC TIMER LSW          */
#define CEIDEV_TIMER_HIGH                 0x00000003  /* 64-BIT 1USEC TIMER MSW          */
#define CEIDEV_IRIG_UPDATE                0x00000004  /* IRIG GENERATOR SET TIME         */
#define CEIDEV_IRIG_INPUT_TIME            0x00000005  /* IRIG REFERENCE INPUT            */
#define CEIDEV_IRIG_TIME_TAG_LOW          0x00000006  /* IRIG RECEIVE TIME TAG LSW       */
#define CEIDEV_IRIG_TIME_TAG_HIGH         0x00000007  /* IRIG RECEIVE TIME TAG MSW       */
#define CEIDEV_ACCESS_SRAM_ADDR           0x00000008  /* SRAM ACCESS ADDRESS REG         */
#define CEIDEV_ACCESS_SRAM_DATA           0x00000009  /* SRAM ACCESS DATA REGISTER       */
#define CEIDEV_DISCRETE_INPUT_0           0x0000000A  /* DISCRETE I/O INPUT REGISTER 0   */
#define CEIDEV_DISCRETE_INPUT_1           0x0000000B  /* DISCRETE I/O INPUT REGISTER 1   */
#define CEIDEV_DISCRETE_INPUT_2           0x0000000C  /* DISCRETE I/O INPUT REGISTER 2   */
#define CEIDEV_DISCRETE_INPUT_3           0x0000000D  /* DISCRETE I/O INPUT REGISTER 3   */
#define CEIDEV_INT_QUEUE_HEAD_PTR         0x0000000E
#define CEIDEV_CONFIG_MEM_CSUM            0x0000000F  /* CONFIGURATION CHECKSUM          */

#define CEIDEV_UCA_CH_1_TIME_LSW          0x00000010  /* RAR15-XMC UCA CH 1 ACTIVE TIMER */
#define CEIDEV_UCA_CH_1_TIME_MSW          0x00000011
#define CEIDEV_UCA_CH_2_TIME_LSW          0x00000012  /* RAR15-XMC UCA CH 2 ACTIVE TIMER */
#define CEIDEV_UCA_CH_2_TIME_MSW          0x00000013
#define CEIDEV_UCA_CH_3_TIME_LSW          0x00000014  /* RAR15-XMC UCA CH 3 ACTIVE TIMER */
#define CEIDEV_UCA_CH_3_TIME_MSW          0x00000015
#define CEIDEV_UCA_CH_4_TIME_LSW          0x00000016  /* RAR15-XMC UCA CH 4 ACTIVE TIMER */
#define CEIDEV_UCA_CH_4_TIME_MSW          0x00000017

#define CEIDEV_FPGA_FPGA_TEMPERATURE      0x00000020  /* RAR-PCIE PARAMETRIC ITEM - TEMP */
#define CEIDEV_FPGA_1PT0V_PWR_SUPPLY      0x00000021  /* RAR-PCIE PARAMETRIC ITEM - 1.0V */
#define CEIDEV_FPGA_2PT5V_PWR_SUPPLY      0x00000022  /* RAR-PCIE PARAMETRIC ITEM - 2.5V */

#define CEIDEV_CHANNEL_STATS_START        0x00000100  /* STARTING OFFSET FOR CHAN STATS  */

#define CEIDEV_CHANNEL_REGION_START       0x00001000  /* STARTING OFFSET FOR CHAN REGS   */
#define CEIDEV_CHANNEL_REGION_SIZE        0x00000010  /* OFFSET BETWEEN CHANNEL REG SETS */
                                                      /* OFFSETS INTO EACH CHAN REGION   */
#define CEIDEV_CHANNEL_STATUS             0x00000000  /*    CHANNEL TYPE/STATUS          */
#define CEIDEV_CHANNEL_CONFIG_1           0x00000001  /*    CONFIGURATION REGISTER 1     */
#define CEIDEV_CHANNEL_CONFIG_2           0x00000002  /*    CONFIGURATION REGISTER 2     */
#define CEIDEV_CHANNEL_CONFIG_3           0x00000003  /*    CONFIGURATION REGISTER 3     */
#define CEIDEV_CHANNEL_BUFFER_0           0x00000004  /*    FIFO BUFFER WORD 0           */
#define CEIDEV_CHANNEL_BUFFER_1           0x00000005  /*    FIFO BUFFER WORD 1           */
#define CEIDEV_CHANNEL_BUFFER_2           0x00000006  /*    FIFO BUFFER WORD 2           */
#define CEIDEV_CHANNEL_BUFFER_3           0x00000007  /*    FIFO BUFFER WORD 3           */

#define CEIDEV_INT_QUEUE_START            0x00002000  /* INTERRUPT QUEUE OFFSET          */
#define CEIDEV_INT_QUEUE_SIZE             0x00000800

#define CEIDEV_MSG_SCHED_TABLE_START      0x00008000  /* MESSAGE SCHEDULER TABLE OFFSET  */
#define CEIDEV_MSG_SCHED_TABLE_END        0x0000A000

#define CEIDEV_SNAPSHOT_BUFFER_START      0x00010000  /* SNAPSHOT BUFFER OFFSET          */
#define CEIDEV_SNAPSHOT_BUFFER_END        0x00020000

/*---------------------------------------------------------------------------*
 * Combo Board Specific Host Interface Register and Buffer Addresses/Offsets
 *---------------------------------------------------------------------------*/
                                                      /* The L-Word Offset into the RAR15-XMC BAR0 region for... */
#define CEIDEV_RAR15_1553_CSC_REG         0x00000000  /*    ...the 1553 host interface                           */
#define CEIDEV_RAR15_SM_ARINC_OFFSET      0x00008000  /*    ...ARINC shared/scratch memory                       */
#define CEIDEV_RAR15_SM_1553_CH_OFFSET    0x00008200  /*    ...1553 channel-indexed shared/scratch memory        */
#define CEIDEV_RAR15_SM_1553_CH_SIZE      0x00000080  /*    ...1553 channel-indexed shared/scratch memory size   */
#define CEIDEV_RAR15_429_OFFSET           0x00040000  /*    ...the x30 host interface                            */
#define CEIDEV_RAR15_429_BYTE_OFFSET      0x00100000  /* The Byte Offset into the RAR15-XMC BAR0 region for the x30 host interface */

#define CEIDEV_RAR15_1553_CH_COUNT_MASK   0x000007C0  /* The RAR15-XMC CSC 1553 "chan_num" field mask  */
#define CEIDEV_RAR15_1553_CH_COUNT_SHIFT           6  /* The RAR15-XMC CSC 1553 "chan_num" field shift */

/*---------------------------------------------------------------------------*
 * Protocol-based Device Channel Types (as defined by the hardware)
 * used in determine_channel_support() to assign installed receive/transmit 
 * channel type and count
 *---------------------------------------------------------------------------*/
#define CEIDEV_CH_TYPE_NONE                0
#define CEIDEV_CH_TYPE_MERGED_RX           1
#define CEIDEV_CH_TYPE_ARINC429_RX         2 
#define CEIDEV_CH_TYPE_ARINC429_TX         3
#define CEIDEV_CH_TYPE_ARINC573_RX         4
#define CEIDEV_CH_TYPE_ARINC573_TX         5
#define CEIDEV_CH_TYPE_ARINC561_RX         6
#define CEIDEV_CH_TYPE_ARINC561_TX         7
#define CEIDEV_CH_TYPE_DISC_IN             8
#define CEIDEV_CH_TYPE_DISC_OUT            9
#define CEIDEV_CH_TYPE_DIGL_IN             10
#define CEIDEV_CH_TYPE_DIGL_OUT            11
#define CEIDEV_CH_TYPE_DIFF_IN             12
#define CEIDEV_CH_TYPE_DIFF_OUT            13
#define CEIDEV_CH_TYPE_SERIAL_RX           14
#define CEIDEV_CH_TYPE_SERIAL_TX           15
#define CEIDEV_CH_TYPE_PROG_ARINC429_RX    16
#define CEIDEV_CH_TYPE_PROG_ARINC429_TX    17
#define NUMBER_OF_CHANNEL_TYPES            CEIDEV_CH_TYPE_PROG_ARINC429_TX+1

#if 0
#define CEIDEV_CH_TYPE_CSDB_RX             X
#define CEIDEV_CH_TYPE_CSDB_TX             X
#endif

/*---------------------------------------------------------------------------*
 * Global Enable Register Bit Field Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_GLOBAL_ENABLE_ON            0x00000001
#define CEIDEV_GLOBAL_ENABLE_MASK          ~CEIDEV_GLOBAL_ENABLE_ON     
#define CEIDEV_IRIG_INTERNAL_ENABLE        0x00000002
#define CEIDEV_IRIG_INTERNAL_MASK          ~CEIDEV_IRIG_INTERNAL_ENABLE
#define CEIDEV_IRIG_AVAILABLE              0x00000004
#define CEIDEV_IRIG_EDGE_DETECT_BIT        0x00000008
#define CEIDEV_IRIG_830RX_IRIG_ENABLE      0x00000080
#define CEIDEV_IRIG_830RX_IRIG_MASK        ~CEIDEV_IRIG_830RX_IRIG_ENABLE
#define CEIDEV_SNAPSHOT_STORAGE_LABEL      0x00000000
#define CEIDEV_SNAPSHOT_STORAGE_ENHANCED   0x00000040
#define CEIDEV_SNAPSHOT_STOR_LABEL_MASK    ~CEIDEV_SNAPSHOT_STORAGE_ENHANCED
#define CEIDEV_INTERRUPTS_ENABLED          0x00000020
#define CEIDEV_INTERRUPTS_DISABLED         ~CEIDEV_INTERRUPTS_ENABLED
#define CEIDEV_INTERRUPT_PENDING           0x00000010
#define CEIDEV_FIRMWARE_VERSION_SHIFT      16
#define CEIDEV_FIRMWARE_VERSION_MASK       0x000000FF
#define CEIDEV_DEVICE_DISABLED             0x80000000
#define MIN_DAC_SPAN                       10

#define CEIDEV_GLOBAL_ENABLE_AUTON_CLEAR   0x40000000
#define CEIDEV_GLOBAL_ENABLE_AUTON_SET     0x80000000

#define CEIDEV_ALT_CONFIG_717_SHIFT        8               
#define CEIDEV_ALT_CONFIGURATION_717       0x00000100      /* was 0x0010 */
#define CEIDEV_ALT_CONFIGURATION_717       0x00000100      /* was 0x0010 */
#define CEIDEV_ALT_CONFIGURATION_430       0x00000020 
#define CEIDEV_ALT_CONFIGURATION_A30       0x00000040
#define CEIDEV_ALT_CONFIGURATION_430A      0x00000050 
#define CEIDEV_ALT_CONFIGURATION_530       0x00000060
#define CEIDEV_ALT_CONFIGURATION_630       0x00000080
#define CEIDEV_ALT_CONFIGURATION_ECA30     0x000000A0
#define CEIDEV_ALT_CONFIGURATION_830X820   0x000000BE
#define CEIDEV_ALT_CONFIGURATION_830A      0x000000C8
#define CEIDEV_ALT_CONFIGURATION_MASK      0x000001E0      /* was 0x00F0 */

/*---------------------------------------------------------------------------*
 * General Host Interface Offsets and Feature Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_SRAM_MAX                    0x80000L
#define SELECT_SRAM_TEST_BLOCK_SIZE        512

#define CEIDEV_MSG_SCHED_TBL_ENTRY_SIZE    8
#define CEIDEV_MSG_SCHED_TBL_DATA_OFFSET   7
#define CEIDEV_CHAN_MSG_SCH_TABLE_MAX      0x1FFF
#define CEIDEV_CHAN_MSG_SCH_ENTRY_MAX      1024
#define CEIDEV_MSG_SCHEDULER_TX_ALWAYS     0xFFFFFFFF

#define CEIDEV_SNAPSHOT_BUFFER_CH_SHIFT    10
#define CEIDEV_SNAPSHOT_BUFFER_LB_SHIFT    2
#define CEIDEV_SNAPSHOT_BUFFER_DATA_OFF    3

#define CEIDEV_ENH_LABEL_FILTER_LB_SHIFT   2
#define CEIDEV_ENH_LABEL_ESSM_FILTER_MASK  7
#define CEIDEV_ENH_LABEL_FILTER_START      0x00000000
#define CEIDEV_ENH_LABEL_FILTER_END        0x00010000
#define CEIDEV_ENH_LABEL_FILTER_CHAN_SIZE  0x00000400
#define CEIDEV_ENH_LABEL_ESSM_FILTER_SHIFT 4
#define CEIDEV_ENH_FLTR_BIT_MASK           0x0F


/*---------------------------------------------------------------------------*
 * Protocol Generic Channel Configuration Register Bit Field Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_FAST_SLEW_RATE              0x00000001 
#define CEIDEV_SLEW_RATE_MASK              ~CEIDEV_FAST_SLEW_RATE

#define CEIDEV_PARITY_ENABLE               0x00000002
#define CEIDEV_PARITY_MASK                 ~CEIDEV_PARITY_ENABLE
#define CEIDEV_PARITY_SELECT_EVEN          0x00000004
#define CEIDEV_PARITY_SELECT_MASK          ~CEIDEV_PARITY_SELECT_EVEN

#define CEIDEV_INTERNAL_WRAP_ENABLE        0x00000004
#define CEIDEV_INTERNAL_WRAP_MASK          ~CEIDEV_INTERNAL_WRAP_ENABLE

#define CEIDEV_MERGE_MODE_ENABLE           0x00004000
#define CEIDEV_MERGE_MODE_ENABLE_MASK      ~CEIDEV_MERGE_MODE_ENABLE

#define CEIDEV_TRANSMIT_DISABLE            0x00000040
#define CEIDEV_TRANSMIT_DISABLE_MASK      ~CEIDEV_TRANSMIT_DISABLE

#define CEIDEV_CHANNEL_ENABLE              0x00008000
#define CEIDEV_CHANNEL_ENABLE_MASK         ~CEIDEV_CHANNEL_ENABLE

#define CEIDEV_BAUD_RATE_FIELD             0x0FFF0000
#define CEIDEV_BAUD_RATE_MASK              ~CEIDEV_BAUD_RATE_FIELD;
#define CEIDEV_BAUD_RATE_SHIFT             16

#define CEIDEV_16MHZ_REF_CLOCK             16000000
#define CEIDEV_20MHZ_REF_CLOCK             20000000

#define CEIDEV_BAUD_RATE_100K              158  /* Baud Rate = 16000000 / N+2 */
#define CEIDEV_BAUD_RATE_50K               318
#define CEIDEV_BAUD_RATE_15K               1064
#define CEIDEV_BAUD_RATE_12pt5K            1278
#define CEIDEV_BAUD_RATE_11K               1454

#define CEIDEV_20MHZ_BAUD_RATE_100K        198  /* Baud Rate = 20000000 / N+2 */
#define CEIDEV_20MHZ_BAUD_RATE_50K         398
#define CEIDEV_20MHZ_BAUD_RATE_15K         1331
#define CEIDEV_20MHZ_BAUD_RATE_12pt5K      1598
#define CEIDEV_20MHZ_BAUD_RATE_11K         1816

#define CEIDEV_DIFF_OUT_ENABLE             0x00000002
#define CEIDEV_DIFF_OUT_ENABLE_MASK        ~CEIDEV_CHANNEL_ENABLE

#define CEIDEV_TRANSMIT_INIT               CEIDEV_FAST_SLEW_RATE + CEIDEV_PARITY_ENABLE + (CEIDEV_BAUD_RATE_100K << CEIDEV_BAUD_RATE_SHIFT) 
#define CEIDEV_RECEIVE_INIT                CEIDEV_PARITY_ENABLE + CEIDEV_FAST_SLEW_RATE + (CEIDEV_BAUD_RATE_100K << CEIDEV_BAUD_RATE_SHIFT);

#define CEIDEV_20MHZ_TRANSMIT_INIT         CEIDEV_FAST_SLEW_RATE + CEIDEV_PARITY_ENABLE + (CEIDEV_20MHZ_BAUD_RATE_100K << CEIDEV_BAUD_RATE_SHIFT) 
#define CEIDEV_20MHZ_RECEIVE_INIT          CEIDEV_PARITY_ENABLE + CEIDEV_FAST_SLEW_RATE + (CEIDEV_20MHZ_BAUD_RATE_100K << CEIDEV_BAUD_RATE_SHIFT);

/*-----------------------------------------------------------------------------------*
 * ARINC 429 Specific Channel Configuration Register Bit Field/Mask/Shift Definitions
 *-----------------------------------------------------------------------------------*/
#define CEIDEV_429_TXCFG_PARAM_ENABLE      0x00000080
#define CEIDEV_429_TXCFG_PARAM_MASK        ~CEIDEV_429_TXCFG_PARAM_ENABLE    
#define CEIDEV_429_TXCFG_BIT_COUNT_LO      0x00000008
#define CEIDEV_429_TXCFG_BIT_COUNT_HI      0x00000010
#define CEIDEV_429_TXCFG_BIT_COUNT_MASK    ~(CEIDEV_429_TXCFG_BIT_COUNT_LO + CEIDEV_429_TXCFG_BIT_COUNT_HI + CEIDEV_429_TXCFG_PARAM_ENABLE)
#define CEIDEV_429_TXCFG_GAP_ERROR         0x00000020
#define CEIDEV_429_TXCFG_GAP_MASK          ~(CEIDEV_429_TXCFG_GAP_ERROR + CEIDEV_429_TXCFG_PARAM_ENABLE)

/*---------------------------------------------------------------------------------------*
 * ARINC 573/717 Specific Channel Configuration Register Bit Field/Mask/Shift Definitions
 *---------------------------------------------------------------------------------------*/
#define CEIDEV_573_RX_MODE_RAW             0x00002000
#define CEIDEV_573_RX_MODE_AUTOSYNC        0x00000000
#define CEIDEV_573_RX_MODE_AUTO_MASK       ~CEIDEV_573_RX_MODE_RAW
#define CEIDEV_573_RX_HBP_SELECT           0x00000000
#define CEIDEV_573_RX_BPRZ_SELECT          0x00001000
#define CEIDEV_573_RX_ENCODING_MASK        ~CEIDEV_573_RX_BPRZ_SELECT
#define CEIDEV_573_SLEW_10_SELECT          0x00000000                
#define CEIDEV_573_SLEW_1PT5_SELECT        0x00000001
#define CEIDEV_573_SLEW_SELECT_MASK        ~CEIDEV_573_SLEW_1PT5_SELECT
#define CEIDEV_573_TX_BPRZ_SELECT          0x00001000
#define CEIDEV_573_TX_BPRZ_MASK            ~CEIDEV_573_TX_BPRZ_SELECT
#define CEIDEV_573_TX_HBP_SELECT           0x00002000
#define CEIDEV_573_TX_HBP_MASK             ~CEIDEV_573_TX_HBP_SELECT
                              
#define CEIDEV_573_FRAME_384_32            0x00000000
#define CEIDEV_573_FRAME_768_64            0x00000100
#define CEIDEV_573_FRAME_1536_128          0x00000200
#define CEIDEV_573_FRAME_3072_256          0x00000300
#define CEIDEV_573_FRAME_6144_512          0x00000400
#define CEIDEV_573_FRAME_12288_1024        0x00000500
#define CEIDEV_573_FRAME_24576_2048        0x00000600
#define CEIDEV_573_FRAME_49152_4096        0x00000700
#define CEIDEV_573_FRAME_SPEC_MASK         ~0x00000F00
#define CEIDEV_573_FRAME_SHIFT             8

/*---------------------------------------------------------------------------*
 * ARINC 573 Receive Message Data Mask Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_573_SYNC_MASK               0x00008000
#define CEIDEV_573_SUBFRAME_MASK           0x00003000
#define CEIDEV_573_DATA_MASK               0x00000FFF
#define CEIDEV_573_SYNCH_SHIFT             16

/*---------------------------------------------------------------------------*
 * Protocol Generic Channel Status Register Bit Field Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_CSR_XMIT_FIFO_FULL          0x00000001
#define CEIDEV_CSR_FIFO_COUNT_MASK         0xFFFF0000
#define CEIDEV_CSR_FIFO_COUNT_SHIFT        16
#define CEIDEV_CSR_CHAN_INACTIVE_FLAG      0x00008000
#define CEIDEV_CSR_CHAN_TYPE_MASK          0x00007F00
#define CEIDEV_CSR_CHAN_TYPE_SHIFT         8
#define CEIDEV_CSR_RECV_FIFO_NOT_EMPTY     0x00000001
#define CEIDEV_CSR_RECV_FIFO_INVALID_MSG   0x00000002
#define CEIDEV_CSR_RECV_FIFO_OVERFLOW      0x00000004
#define CEIDEV_CSR_FIFO_INVALID_MSG        CEIDEV_CSR_RECV_FIFO_INVALID_MSG

/*---------------------------------------------------------------------------*
 * Digital I/O and Discretes Register Bit Field Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_DISCRETE_MASK               0xFFFFFFFE

/*---------------------------------------------------------------------------*
 * IRIG DAC Constant Definitions
 *---------------------------------------------------------------------------*/
#define CEIDEV_IRIG_DAC_INIT_THRESHOLD     155
#define CEIDEV_IRIG_DAC_MV_CONVERSION      (float)57.091
#define CEIDEV_IRIG_DAC_OFFSET             128

/*---------------------------------------------------------------------------*
 * IRIG Encoded Time Bit Fields to Microseconds Conversion Definitions
 *---------------------------------------------------------------------------*/
#define IRIG_SHIFT_HUNDREDS_OF_DAYS        28
#define IRIG_MASK_HUNDREDS_OF_DAYS         3
#define IRIG_SHIFT_TENS_OF_DAYS            24
#define IRIG_MASK_TENS_OF_DAYS             15
#define IRIG_SHIFT_ONES_OF_DAYS            20
#define IRIG_MASK_ONES_OF_DAYS             15
#define IRIG_SHIFT_TENS_OF_HOURS           18
#define IRIG_MASK_TENS_OF_HOURS            3
#define IRIG_SHIFT_ONES_OF_HOURS           14
#define IRIG_MASK_ONES_OF_HOURS            15
#define IRIG_SHIFT_TENS_OF_MINUTES         11
#define IRIG_MASK_TENS_OF_MINUTES          7
#define IRIG_SHIFT_ONES_OF_MINUTES         7
#define IRIG_MASK_ONES_OF_MINUTES          15
#define IRIG_SHIFT_TENS_OF_SECONDS         4
#define IRIG_MASK_TENS_OF_SECONDS          7
#define IRIG_MASK_ONES_OF_SECONDS          15
   

#endif /* ifndef CDEV_HW_H */
