#ifndef CWCEC_SCGTDATA_H
#define CWCEC_SCGTDATA_H

typedef uint32_T uint32;
typedef uint16_T uint16;
typedef uint8_T uint8;

/****************************************************************/
/********************** REGISTER DEFS ***************************/
/****************************************************************/

#define GTCORE_REGISTER_SIZE     0x100

/* register offsets */
#define GTCORE_R_BRD_INFO       0x0  
#define GTCORE_R_DRV_BRD_CSR    0x4  
#define GTCORE_R_USR_BRD_CSR    0x8  
#define GTCORE_R_INT_CSR        0xc  
#define GTCORE_R_LINK_CTL       0x10 
#define GTCORE_R_LINK_STAT      0x14 
#define GTCORE_R_RX_HBI_MSK     0x18 
#define GTCORE_R_RX_HUI_MSK     0x1c 
#define GTCORE_R_MISC_FNCTN     0x20 

#define GTCORE_R_NET_TMR        0x40 
#define GTCORE_R_HST_TMR        0x44 
#define GTCORE_R_LAT_TMR        0x48 
#define GTCORE_R_SM_TRFC_CNTR   0x4c 
#define GTCORE_R_INT_TRFC_CNTR  0x50 
#define GTCORE_R_HNT_TRFC_CNTR  0x54 
#define GTCORE_R_NHIQ_INT_CNTR  0x58 
#define GTCORE_R_HST_INT_CNTR   0x5c 

#define GTCORE_R_LNK_ERR_CNTR   0x80 
#define GTCORE_R_LNK_DOWN_CNTR  0x84 
#define GTCORE_R_DEC_ERR_CNTR   0x88 
#define GTCORE_R_SYNC_ERR_CNTR  0x8c 
#define GTCORE_R_CRC_ERR_CNTR   0x90 
#define GTCORE_R_EOF_ERR_CNTR   0x94 
#define GTCORE_R_PRTCL_ERR_CNTR 0x98 
#define GTCORE_R_RXF_ERR_CNTR   0x9c 

#define GTCORE_R_TC_WDT_VAL     0xbc 
#define GTCORE_R_TQ_ADD32_TC0   0xc0 
#define GTCORE_R_TQ_ADD64_TC0   0xc4 
#define GTCORE_R_TQ_CTL_TC0     0xc8 
#define GTCORE_R_TNS_LEN_TC0    0xcc 
#define GTCORE_R_TQ_ADD32_TC1   0xd0 
#define GTCORE_R_TQ_ADD64_TC1   0xd4 
#define GTCORE_R_TQ_CTL_TC1     0xd8  
#define GTCORE_R_TNS_LEN_TC1    0xdc 

/****************************************************************/
/********************* Bit Definitions **************************/
/****************************************************************/

/*** BRD_INFO ***/ 
#define GTCORE_R_MEM_PMS        0x3
#define GTCORE_R_MEM_RTMS       0x3c
#define GTCORE_R_MEM_TYPE       0xc0     /*!! may be removed */
#define GTCORE_R_A64_TSPT       0x100
#define GTCORE_R_A64_ISPT       0x200
#define GTCORE_R_BUS_SPT        0x1c00
#define GTCORE_R_PHY_TYPE       0x6000
#define GTCORE_R_EXT_REV_ID     0x00ff0000
#define GTCORE_R_REV_ID         0xff000000

/*** DRV_BRD_CSR ***/
#define GTCORE_R_STC_A          0xF
#define GTCORE_R_TCB_SWAP       0x10   /* target control byte swap */
#define GTCORE_R_ICB_SWAP       0x20   /* TQE and CE byte swap */

/*** USR_BRD_CSR ***/
#define GTCORE_R_DW_SWAP        0x1    /* data word swap */
#define GTCORE_R_DB_SWAP        0x2    /* data byte swap */
#define GTCORE_R_INIT_D64_DIS   0x10   /* 64-bit initiator disable */

/*** INT_CSR ***/
#define GTCORE_R_TC0_INT        0x1
#define GTCORE_R_TC1_INT        0x2
#define GTCORE_R_LNK_ERR_INT    0x4
#define GTCORE_R_RX_NET_INT     0x8
#define GTCORE_R_TC0_INT_EN     0x10000
#define GTCORE_R_TC1_INT_EN     0x20000
#define GTCORE_R_LNK_ERR_INT_EN 0x40000
#define GTCORE_R_RX_NET_INT_EN  0x80000

#define GTCORE_R_ALL_INT_EN  (GTCORE_R_TC0_INT_EN     | \
                              GTCORE_R_TC1_INT_EN     | \
                              GTCORE_R_LNK_ERR_INT_EN | \
                              GTCORE_R_RX_NET_INT_EN)

/*** LINK_CTL ***/
#define GTCORE_R_LAS_0_EN       0x1
#define GTCORE_R_LAS_1_EN       0x2
#define GTCORE_R_LNK_SEL        0x10
#define GTCORE_R_NODE_ID        0xFF00
#define GTCORE_R_TX_EN          0x10000
#define GTCORE_R_RX_EN          0x20000
#define GTCORE_R_RT_EN          0x40000
#define GTCORE_R_WRAP           0x80000
#define GTCORE_R_WML            0x100000
#define GTCORE_R_INT_SELF       0x200000
#define GTCORE_R_HNT_ID         0xFF000000


/*** LINK_STAT ***/
#define GTCORE_R_LNK_DOWN       0x1
#define GTCORE_R_DEC_ERR        0x2
#define GTCORE_R_SYNC_ERR       0x4
#define GTCORE_R_CRC_ERR        0x8
#define GTCORE_R_EOF_ERR        0x10
#define GTCORE_R_PRTCL_ERR      0x20
#define GTCORE_R_RXF_ERR        0x40
#define GTCORE_R_RX_STRP_ERR    0x80
#define GTCORE_R_EXP_MSG_ERR    0x1000
#define GTCORE_R_LNK_UP         0x20000
#define GTCORE_R_LAS_0_SD       0x40000
#define GTCORE_R_LAS_1_SD       0x80000
#define GTCORE_R_RLC            0x800000
#define GTCORE_R_AGE            0xFF000000

/*** MISC_FNCTN ***/
#define GTCORE_R_DIS_RD_BYP     0x200
#define GTCORE_R_UNID           0xFF000000


/*** TQ_CTL_TC0 ***/
#define GTCORE_R_TQ_PRD_IDX     0x0000001F
#define GTCORE_R_TQ_CON_IDX     0x00001F00
#define GTCORE_R_TQ_LEN         0x001F0000
#define GTCORE_R_TQ_EN          0x01000000
#define GTCORE_R_TQ_RST         0x02000000
#define GTCORE_R_TQ_ABRT        0x04000000
#define GTCORE_R_TQ_PSD         0x20000000
#define GTCORE_R_TQ_AVAIL       0x40000000
#define GTCORE_R_TQ_PRSRV       0x80000000

/******* Network Management Registers ******/
#define GTCORE_NM_REGISTER_SIZE    0x2000

#define GTCORE_NM_NHI_QID     0x0800
#define GTCORE_NM_TX_HBI      0x1000    /* use (GTCORE_NM_TX_HBI + HBI Number * 4) */
#define GTCORE_NM_TX_HUI      0x1800    /* use (GTCORE_NM_TX_HUI + (destination ID * 4)) */

/* NM_NHI_QID bit defs */
#define GTCORE_NM_HI_TYPE   0x10000

/******************************************************************/
/************************ ERROR CODES *****************************/
/******************************************************************/

#define SCGT_SUCCESS                   0
#define SCGT_SYSTEM_ERROR              1
#define SCGT_BAD_PARAMETER             2
#define SCGT_DRIVER_ERROR              3
#define SCGT_TIMEOUT                   4
#define SCGT_CALL_UNSUPPORTED          5
#define SCGT_INSUFFICIENT_RESOURCES    6
#define SCGT_LINK_ERROR                7
#define SCGT_MISSED_INTERRUPTS         8
#define SCGT_DRIVER_MISSED_INTERRUPTS  9
#define SCGT_DMA_UNSUPPORTED          10
#define SCGT_HARDWARE_ERROR           11


/******************************************************************/
/*********************** STATE IDs ********************************/
/******************************************************************/

#define SCGT_NODE_ID                0
#define SCGT_ACTIVE_LINK            1
#define SCGT_NUM_LINK_ERRS          2
#define SCGT_EWRAP                  3
#define SCGT_WRITE_ME_LAST          4
#define SCGT_UNICAST_INT_MASK       5
#define SCGT_BROADCAST_INT_MASK     6
#define SCGT_INT_SELF_ENABLE        7
#define SCGT_RING_SIZE              8
#define SCGT_UPSTREAM_NODE_ID       9
#define SCGT_NET_TIMER_VAL         10
#define SCGT_LATENCY_TIMER_VAL     11
#define SCGT_SM_TRAFFIC_CNT        12
#define SCGT_SPY_SM_TRAFFIC_CNT    13
#define SCGT_SPY_NODE_ID           14
#define SCGT_TRANSMIT_ENABLE       15
#define SCGT_RECEIVE_ENABLE        16
#define SCGT_RETRANSMIT_ENABLE     17
#define SCGT_LASER_0_ENABLE        18
#define SCGT_LASER_1_ENABLE        19
#define SCGT_LINK_UP               20
#define SCGT_LASER_0_SIGNAL_DET    21
#define SCGT_LASER_1_SIGNAL_DET    22
#define SCGT_D64_ENABLE            23
#define SCGT_BYTE_SWAP_ENABLE      24
#define SCGT_WORD_SWAP_ENABLE      25
#define SCGT_LINK_ERR_INT_ENABLE   26
//#define SCGT_READ_BYPASS_ENABLE    27 /* moved to end of list */
#define SCGT_INT_TRFC_CNTR         27
#define SCGT_NHIQ_INT_CNTR         28
#define SCGT_HST_INT_CNTR          29

#define SCGT_READ_BYPASS_ENABLE    30




#define GTCORE_SEQ_NUM_MASK   0xFFFFFFF    /* seqNum cannot be -1 */

#define GTCORE_INTR_Q_SIZE   1024  /* must be power of 2 */

#define GTCORE_DEFAULT_WDT_VAL 0xFFFFF

/** interrupt type bitmask definitions **/
#define GTCORE_ISR_HANDLED           0x1
#define GTCORE_ISR_DMA               0x2
#define GTCORE_ISR_QUEUED_INTR       0x4

/*****************************************************************/
/********************* INTERRUPT TYPES ***************************/
/*****************************************************************/

#define SCGT_UNICAST_INTR     0
#define SCGT_BROADCAST_INTR   1
#define SCGT_ERROR_INTR       2



/******************************************************************/
/******************** Macro functions *****************************/
/******************************************************************/

#define scgtReadCReg( dev, offset ) dev->cRegPtr[(offset)>>2]

#define scgtWriteCReg(dev, regOffset, val)  \
  dev->cRegPtr[ (regOffset) >> 2 ] = val

#define scgtWriteCRegMasked(dev, offset, val, mask)  \
   dev->cRegPtr[(offset)>>2] = (dev->cRegPtr[(offset)>>2] & ~(mask)) | ((val) & (mask))


/*
 * interrupt struct
 */

typedef struct _scgtInterrupt
{
    uint32 type;          /* SCGT_UNICAST_INTR, SCGT_BROADCAST_INTR, or 
                             SCGT_ERROR_INTR */
    uint32 sourceNodeID;  /* source node ID */
    uint32 id;            /* 0 to 31 designating the interrupt number for 
                             broadcast interrupts, destination node ID for 
                             sending unicast interrupts. */ 
    uint32 val;           /* user defined data sent with broadcast or unicast 
                             interrupt or error code if error interrupt */
    uint32 seqNum;
} scgtInterrupt;

typedef volatile struct _gtcoreIntrQData
{
    scgtInterrupt *intrQ;
    uint32 head;
    uint32 seqNum;
} gtcoreIntrQData;

typedef struct scgtDeviceType
{	
    volatile uint32_T *cRegPtr;   /* config/status register pointer */
    volatile uint32_T *nmRegPtr;  /* net management register pointer */
    volatile uint32_T *memPtr;    /* (kernel) pointer to GT memory.. used to map to process */
   
    //uint32 stats[SCGT_STATS_NUM_STATS];    /* statistics */         
    gtcoreIntrQData intrQData;                                      
    uint32 hwNHIQIntCntrVal;
    
} scgtDevice;


#define scgtReadNMReg(pdev, offset) \
        pdev->nmRegPtr[(offset)>>2]

#define scgtWriteNMReg(pdev, offset, val) \
        pdev->nmRegPtr[(offset)>>2]=val


#endif