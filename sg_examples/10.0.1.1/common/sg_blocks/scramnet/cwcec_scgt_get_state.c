/* Curtiss Wright Controls embedded Computing */
/* SCRAMNet GT Get State function */

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         cwcec_scgt_get_state

#include        <stddef.h>
#include        <stdlib.h>

#include        "simstruc.h"
#include        "cwcec_scgtdata.h"

#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif

/* Input Arguments */
#define NUMBER_OF_ARGS        (4)
#define STATE_ID              ssGetSFcnParam(S, 0)
#define SAMPLETIME_ARG        ssGetSFcnParam(S, 1)
#define SLOT_ARG              ssGetSFcnParam(S, 2)
#define MODULE_ID             ssGetSFcnParam(S, 3)

#define NO_I_WORKS            (0)
#define NO_R_WORKS            (0)
#define NO_P_WORKS            (1)

#define VENDOR_ID             (0x1387)
#define DEVICE_ID             (0x5310)
#define DEVICE_NAME           "SCRAMNet GT"

static char_T msg[256];

#include "cwcec_scgtdata.h"
#include "sg_callback_legacy.h"


static void mdlInitializeSizes(SimStruct *S)
{
  uint16_T i;

   ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
   if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
   {
      sprintf(msg, "Wrong number of input arguments passed.\n"
                   "%d arguments are expected\n", NUMBER_OF_ARGS);
      ssSetErrorStatus(S, msg);
      return;
   }

   ssSetNumContStates(S, 0);
   ssSetNumDiscStates(S, 0);

   ssSetNumInputPorts(S, 0);

   ssSetNumOutputPorts(S, 1);
   ssSetOutputPortWidth(S, 0, 1);
   ssSetOutputPortDataType(S, 0, SS_UINT32);

   ssSetNumSampleTimes(S, 1);

   ssSetNumRWork(S, NO_R_WORKS);
   ssSetNumIWork(S, NO_I_WORKS);
   ssSetNumPWork(S, NO_P_WORKS);

   ssSetNumModes(S, 0);
   ssSetNumNonsampledZCs(S, 0);

      for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0); // None of the parameters are tunable
    }

   ssSetOptions(S, SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
   if (mxGetPr(SAMPLETIME_ARG)[0]==-1.0)
   {
      ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
      ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
   }
   else
   {
      ssSetSampleTime(S, 0, mxGetPr(SAMPLETIME_ARG)[0]);
      ssSetOffsetTime(S, 0, 0.0);
   }
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

   sg_PCIDevice pciInfo;
   uintptr_t ioAddress;
   int_T moduleId = (int_T)mxGetPr(MODULE_ID)[0];

   if ((int_T)mxGetPr(SLOT_ARG)[0] < 0)
   {
      /* Look for the SCRAMNet GT Device */
      if (sg_findPciDevice(&pciInfo, DEVICE_NAME, (unsigned short)VENDOR_ID, (unsigned short)DEVICE_ID, SG_NO_SUB, SG_NO_SUB, moduleId, SG_NO_BUS_SLOT, SG_NO_BUS_SLOT))
      {
          ssSetErrorStatus(S, pSgErrorStr);
          return;
      }
   }
   else
   {
      int_T bus, slot;
      if (mxGetN(SLOT_ARG) == 1)
      {
         bus  = 0;
         slot = (int_T)mxGetPr(SLOT_ARG)[0];
      }
      else
      {
         bus  = (int_T)mxGetPr(SLOT_ARG)[0];
         slot = (int_T)mxGetPr(SLOT_ARG)[1];
      }
      /* Look for the SCRAMNet GT Device */
      if (sg_findPciDevice(&pciInfo, DEVICE_NAME, (unsigned short)VENDOR_ID, (unsigned short)DEVICE_ID, SG_NO_SUB, SG_NO_SUB, moduleId, bus, slot))
      {
          ssSetErrorStatus(S, pSgErrorStr);
          return;
      }
   }

   /* Show Device Information */
   //[THIS CANNOT BE USED ANYMORE]pciInfo);

   /* Map GT CSRs */

   
   //ioAddress32  = (void *)PhysicalAddr;
   ioAddress  = (uintptr_t)sg_mapMemory(&pciInfo, 0);
   
   ssSetPWorkValue(S, 0, (void *)ioAddress);
#endif
}

#ifndef MATLAB_MEX_FILE
/*
 * gtcoreGetState()
 *     fills in val with state denoted by stateID
 */
uint32_T gtcoreGetState(scgtDevice *dev, uint32_T stateID, uint32_T *val)
{
    switch (stateID)
    {
        case SCGT_NET_TIMER_VAL:
            *val = scgtReadCReg(dev, GTCORE_R_NET_TMR);
            break;
            
        case SCGT_LATENCY_TIMER_VAL:
            *val = scgtReadCReg(dev, GTCORE_R_LAT_TMR);
            break;
        
        case SCGT_SM_TRAFFIC_CNT:
            *val = scgtReadCReg(dev, GTCORE_R_SM_TRFC_CNTR);
            break;
            
        case SCGT_SPY_SM_TRAFFIC_CNT:
            *val = scgtReadCReg(dev, GTCORE_R_HNT_TRFC_CNTR);
            break;
            
        case SCGT_SPY_NODE_ID:
            *val = scgtReadCReg(dev, GTCORE_R_LINK_CTL) >> 24;
            break;
            
        case SCGT_NODE_ID:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_NODE_ID) >> 8;
            break;
            
        case SCGT_ACTIVE_LINK:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LNK_SEL)? 1 : 0;
            break;

        case SCGT_WRITE_ME_LAST:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_WML)? 1 : 0;
            break;
        
        case SCGT_UNICAST_INT_MASK:
            *val = scgtReadCReg(dev, GTCORE_R_RX_HUI_MSK) & 0x1;
            break;
            
        case SCGT_BROADCAST_INT_MASK:
            *val = scgtReadCReg(dev, GTCORE_R_RX_HBI_MSK);
            break;

        case SCGT_INT_SELF_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_INT_SELF)? 1 : 0;
            break;

        case SCGT_RING_SIZE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) >> 24) + 1;
            break;
            
        case SCGT_UPSTREAM_NODE_ID:
            *val = scgtReadCReg(dev, GTCORE_R_MISC_FNCTN) >> 24;
            break;
            
        case SCGT_EWRAP:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_WRAP)? 1 : 0;
            break;
            
        case SCGT_NUM_LINK_ERRS:
            *val = scgtReadCReg(dev, GTCORE_R_LNK_ERR_CNTR);
            break;
        
        case SCGT_TRANSMIT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_TX_EN)? 1 : 0;
            break;
            
        case SCGT_RECEIVE_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_RX_EN)? 1 : 0;
            break;
            
        case SCGT_RETRANSMIT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_RT_EN)? 1 : 0;
            break;
            
        case SCGT_LASER_0_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LAS_0_EN)? 1 : 0;
            break;
            
        case SCGT_LASER_1_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LAS_1_EN)? 1 : 0;
            break;
            
        case SCGT_LINK_UP:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LNK_UP)? 1 : 0;
            break;
            
        case SCGT_LASER_0_SIGNAL_DET:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LAS_0_SD)? 1 : 0;
            break;
            
        case SCGT_LASER_1_SIGNAL_DET:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LAS_1_SD)? 1 : 0;
            break;
        
        case SCGT_D64_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_INIT_D64_DIS)? 0 : 1;
            break;
            
        case SCGT_BYTE_SWAP_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_DB_SWAP)? 1 : 0;
            break;
            
        case SCGT_WORD_SWAP_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_DW_SWAP)? 1 : 0;
            break;
        
        case SCGT_LINK_ERR_INT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_INT_CSR) & GTCORE_R_LNK_ERR_INT_EN)? 1 : 0;
            break;

        case SCGT_READ_BYPASS_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_MISC_FNCTN) & GTCORE_R_DIS_RD_BYP)? 0 : 1;
            break;
                
		case SCGT_INT_TRFC_CNTR:
			*val = scgtReadCReg(dev,GTCORE_R_INT_TRFC_CNTR);
			break;

        case SCGT_NHIQ_INT_CNTR:
			*val = scgtReadCReg(dev,GTCORE_R_NHIQ_INT_CNTR);
			break;

		case SCGT_HST_INT_CNTR:
			*val = scgtReadCReg(dev,GTCORE_R_HST_INT_CNTR);
			break;       

        default:
            return SCGT_BAD_PARAMETER;
    }
    return SCGT_SUCCESS;
}
#endif


static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
   uint32_T *val = (uint32_T *)ssGetOutputPortSignal(S, 0);
   uint32_T stateId = (uint32_T)mxGetPr(STATE_ID)[0];
   volatile uint32_T *ioAddress32 =
       (volatile uint32_t *)ssGetPWorkValue(S, 0);
   scgtDevice gtDev;
   scgtDevice *dev;

   dev = &gtDev;
   /* update memory pointer in GT structure */
   dev->cRegPtr = ioAddress32;
   
   if(gtcoreGetState(dev, stateId, val) == SCGT_BAD_PARAMETER)
   {
       sprintf(msg,"Input StateId value 0x%x is not valid",stateId);
       ssSetErrorStatus(S,msg);
       return;            
   }

/*
   switch (stateId)
    {
         case SCGT_NET_TIMER_VAL:
            *val = scgtReadCReg(dev, GTCORE_R_NET_TMR);
            break;
            
        case SCGT_LATENCY_TIMER_VAL:
            *val = scgtReadCReg(dev, GTCORE_R_LAT_TMR);
            break;
        
        case SCGT_SM_TRAFFIC_CNT:
            *val = scgtReadCReg(dev, GTCORE_R_SM_TRFC_CNTR);
            break;
            
        case SCGT_SPY_SM_TRAFFIC_CNT:
            *val = scgtReadCReg(dev, GTCORE_R_HNT_TRFC_CNTR);
            break;
            
        case SCGT_SPY_NODE_ID:
            *val = scgtReadCReg(dev, GTCORE_R_LINK_CTL) >> 24;
            break;
            
        case SCGT_NODE_ID:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_NODE_ID) >> 8;
            break;
            
        case SCGT_ACTIVE_LINK:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LNK_SEL)? 1 : 0;
            break;

        case SCGT_WRITE_ME_LAST:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_WML)? 1 : 0;
            break;
        
        case SCGT_UNICAST_INT_MASK:
            *val = scgtReadCReg(dev, GTCORE_R_RX_HUI_MSK) & 0x1;
            break;
            
        case SCGT_BROADCAST_INT_MASK:
            *val = scgtReadCReg(dev, GTCORE_R_RX_HBI_MSK);
            break;

        case SCGT_INT_SELF_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_INT_SELF)? 1 : 0;
            break;

        case SCGT_RING_SIZE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) >> 24) + 1;
            break;
            
        case SCGT_UPSTREAM_NODE_ID:
            *val = scgtReadCReg(dev, GTCORE_R_MISC_FNCTN) >> 24;
            break;
            
        case SCGT_EWRAP:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_WRAP)? 1 : 0;
            break;
            
        case SCGT_NUM_LINK_ERRS:
            *val = scgtReadCReg(dev, GTCORE_R_LNK_ERR_CNTR);
            break;
        
        case SCGT_TRANSMIT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_TX_EN)? 1 : 0;
            break;
            
        case SCGT_RECEIVE_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_RX_EN)? 1 : 0;
            break;
            
        case SCGT_RETRANSMIT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_RT_EN)? 1 : 0;
            break;
            
        case SCGT_LASER_0_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LAS_0_EN)? 1 : 0;
            break;
            
        case SCGT_LASER_1_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_CTL) & GTCORE_R_LAS_1_EN)? 1 : 0;
            break;
            
        case SCGT_LINK_UP:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LNK_UP)? 1 : 0;
            break;
            
        case SCGT_LASER_0_SIGNAL_DET:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LAS_0_SD)? 1 : 0;
            break;
            
        case SCGT_LASER_1_SIGNAL_DET:
            *val = (scgtReadCReg(dev, GTCORE_R_LINK_STAT) & GTCORE_R_LAS_1_SD)? 1 : 0;
            break;
        
        case SCGT_D64_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_INIT_D64_DIS)? 0 : 1;
            break;
            
        case SCGT_BYTE_SWAP_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_DB_SWAP)? 1 : 0;
            break;
            
        case SCGT_WORD_SWAP_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_USR_BRD_CSR) & GTCORE_R_DW_SWAP)? 1 : 0;
            break;
        
        case SCGT_LINK_ERR_INT_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_INT_CSR) & GTCORE_R_LNK_ERR_INT_EN)? 1 : 0;
            break;

        case SCGT_READ_BYPASS_ENABLE:
            *val = (scgtReadCReg(dev, GTCORE_R_MISC_FNCTN) & GTCORE_R_DIS_RD_BYP)? 0 : 1;
            break;
                
        default:
			sprintf(msg,"Input StateId value 0x%x is not valid",stateId);
            ssSetErrorStatus(S,msg);
            return;            
    }    
 */
#endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
