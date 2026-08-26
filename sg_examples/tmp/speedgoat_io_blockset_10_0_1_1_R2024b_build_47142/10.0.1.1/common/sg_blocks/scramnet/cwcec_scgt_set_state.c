/* Curtiss Wright Controls embedded Computing */
/* SCRAMNet GT Set State function */

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         cwcec_scgt_set_state

#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>

#include        "simstruc.h"
#include        "cwcec_scgtdata.h"

#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif

/* Input Arguments */
#define NUMBER_OF_ARGS        (3)
#define SAMPLETIME_ARG        ssGetSFcnParam(S, 0)
#define SLOT_ARG              ssGetSFcnParam(S, 1)
#define MODULE_ID             ssGetSFcnParam(S, 2)

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
      ssSetErrorStatus(S,msg);
      return;
   }

   ssSetNumContStates(S, 0);
   ssSetNumDiscStates(S, 0);

   ssSetNumOutputPorts(S, 0);

   if(!ssSetNumInputPorts(S, 2)) return;
   
   ssSetInputPortWidth(S, 0, 1);
   ssSetInputPortDataType(S, 0, SS_UINT32);
   ssSetInputPortDirectFeedThrough(S, 0, 1);
   ssSetInputPortRequiredContiguous(S, 0, 1);
   
   ssSetInputPortWidth(S, 1, 1);
   ssSetInputPortDataType(S, 1, SS_UINT32);
   ssSetInputPortDirectFeedThrough(S, 1, 1);
   ssSetInputPortRequiredContiguous(S, 1, 1);

   

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

   /* store pointer to contreol register mapped in bar 0 address*/
   ssSetPWorkValue(S, 0, (void *)ioAddress);
#endif
}



static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
   uint32_T *input1 = (uint32_T *)ssGetInputPortSignal(S, 0);
   uint32_T *input2 = (uint32_T *)ssGetInputPortSignal(S, 1);
//   uint32_T val = (uint32_T)mxGetPr(NEW_VALUE)[0];
//   uint32_T stateId = (uint32_T)mxGetPr(STATE_ID)[0];
   uint32_T val;
   uint32_T valRead;
   uint32_T stateId;
   volatile uint32_T *ioAddress32 =
       (volatile uint32_T *)ssGetPWorkValue(S, 0);

   scgtDevice gtDev;
   scgtDevice *dev;

   dev = &gtDev;
   /* update cregpointer in Gt device stusture */
   dev->cRegPtr = ioAddress32;
   
   stateId = *input1;
   val     = *input2;
   
   switch (stateId)
   {
        case SCGT_NODE_ID:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, ((val & 0xFF) << 8), GTCORE_R_NODE_ID);
            //ioAddress32[GTCORE_R_LINK_CTL] = (dev[GTCORE_R_LINK_CTL] & ~(GTCORE_R_NODE_ID)) | ((val) & (GTCORE_R_NODE_ID));
            
            valRead = scgtReadCReg(dev,GTCORE_R_LINK_CTL) ;
            if(((valRead >>8)& 0xff) != val)
            {
               sprintf(msg,"Error setting Node ID. Read 0x%x. Val=0x%x ",valRead,val);
               ssSetErrorStatus(S,msg);
               return;
            }
            
            break;
           
        case SCGT_ACTIVE_LINK:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                ((val & 0x1) << 4), GTCORE_R_LNK_SEL);
            break;
            
        case SCGT_WRITE_ME_LAST:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, (val)? GTCORE_R_WML : 0, GTCORE_R_WML);
            break;
       
        case SCGT_NET_TIMER_VAL:
            scgtWriteCReg(dev, GTCORE_R_NET_TMR, val);
            break;
            
        case SCGT_LATENCY_TIMER_VAL:
            scgtWriteCReg(dev, GTCORE_R_LAT_TMR, val);
            break;
        
        case SCGT_SM_TRAFFIC_CNT:    
            scgtWriteCReg(dev, GTCORE_R_SM_TRFC_CNTR, val);
            break;
            
        case SCGT_SPY_SM_TRAFFIC_CNT:
            scgtWriteCReg(dev, GTCORE_R_HNT_TRFC_CNTR, val);
            break;
            
        case SCGT_SPY_NODE_ID:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, (val << 24), GTCORE_R_HNT_ID);
            break;
                
        case SCGT_UNICAST_INT_MASK:
            scgtWriteCRegMasked(dev, GTCORE_R_RX_HUI_MSK, val, 0x1);
            break;
            
        case SCGT_BROADCAST_INT_MASK:
            scgtWriteCReg(dev, GTCORE_R_RX_HBI_MSK, val);
            break;

        case SCGT_INT_SELF_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_INT_SELF : 0, GTCORE_R_INT_SELF);
            break;
                     
        case SCGT_EWRAP:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_WRAP : 0, GTCORE_R_WRAP);
            break;
            
        case SCGT_NUM_LINK_ERRS:
            break;
            
        case SCGT_TRANSMIT_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_TX_EN : 0, GTCORE_R_TX_EN);            
            break;
            
        case SCGT_RECEIVE_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_RX_EN : 0, GTCORE_R_RX_EN); 
            break;
            
        case SCGT_RETRANSMIT_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_RT_EN : 0, GTCORE_R_RT_EN); 
            break;
            
        case SCGT_LASER_0_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_LAS_0_EN : 0, GTCORE_R_LAS_0_EN); 
            break;
            
        case SCGT_LASER_1_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_LINK_CTL, 
                                (val)? GTCORE_R_LAS_1_EN : 0, GTCORE_R_LAS_1_EN); 
            break;

        case SCGT_D64_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_USR_BRD_CSR, 
                                (val)? 0 : GTCORE_R_INIT_D64_DIS, GTCORE_R_INIT_D64_DIS); 
            
            break;

        case SCGT_BYTE_SWAP_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_USR_BRD_CSR, 
                                (val)? GTCORE_R_DB_SWAP : 0, GTCORE_R_DB_SWAP);
            break;
            
        case SCGT_WORD_SWAP_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_USR_BRD_CSR,
                                (val)? GTCORE_R_DW_SWAP : 0, GTCORE_R_DW_SWAP);
            break;

        case SCGT_LINK_ERR_INT_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_INT_CSR,
                                (val)? GTCORE_R_LNK_ERR_INT_EN : 0, GTCORE_R_LNK_ERR_INT_EN);
            break;

        case SCGT_READ_BYPASS_ENABLE:
            scgtWriteCRegMasked(dev, GTCORE_R_MISC_FNCTN,
                                (val)? 0 : GTCORE_R_DIS_RD_BYP, GTCORE_R_DIS_RD_BYP);
            break;
    
        default:
            sprintf(msg,"Input StateIdi: %d is not valid. Val=%d.",stateId,val);
            ssSetErrorStatus(S,msg);
            return;
    }
   
   #endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
