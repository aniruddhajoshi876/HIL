/* Curtiss Wright Controls embedded Computing */
/* SCRAMNet GT Init function */


#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         cwcec_scgt_init

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
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#endif

/* Input Arguments */
#define NUMBER_OF_ARGS        (6)
#define NODEID_ARG            ssGetSFcnParam(S, 0)
#define TXRX_ARG              ssGetSFcnParam(S, 1)
#define NODE_ARG              ssGetSFcnParam(S, 2)
#define BMASK_ARG             ssGetSFcnParam(S, 3)
#define SLOT_ARG              ssGetSFcnParam(S, 4)
#define MODULE_ID             ssGetSFcnParam(S, 5)

//#define NO_I_WORKS            (0)
#define NO_I_WORKS            (0)
#define NO_R_WORKS            (0)

#define NO_P_WORKS            (1)
#define BASE_ADDR_P_IND       (0)

static char_T msg[256];

#define VENDOR_ID             (0x1387)
#define DEVICE_ID             (0x5310)
#define DEVICE_NAME           "SCRAMNet GT"

#define BRD_INFO              (0)
#define USR_BRD_CSR           (2)
#define INT_CSR               (3)
#define LINK_CTL              (4)
#define RX_HBI_MSK            (6)
#define RX_HUI_MSK            (7)

#ifndef MATLAB_MEX_FILE
static void setOption(volatile uint32_t *addr, int32_t value, uint32_t reg_mask);
#endif

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

	 ssSetNumInputPorts(S, 0);
   
    ssSetNumOutputPorts(S, 0);
        
    ssSetNumSampleTimes(S, 1);

    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

     for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0); // None of the parameters are tunable
    }


    ssSetOptions(S, SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
   int32_T val, laserEn[2];
	sg_PCIDevice pciInfo;
   uintptr_t ioAddressPtr;
   volatile uint32_t *ioAddress; 
  // volatile uint32_t *bar2out;
   int_T moduleId = (int_T)mxGetPr(MODULE_ID)[0];

   SG_PRINTF(INFO, " Start Initialization \n");
   
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
  
   ioAddressPtr = (uintptr_t)sg_mapMemory(&pciInfo, 0);

   ssSetPWorkValue(S, BASE_ADDR_P_IND, (void *)ioAddressPtr);

   ioAddress = (volatile uint32_t *)ioAddressPtr;


   
   /* Set NodeID */
   val = (int32_t)mxGetPr(NODEID_ARG)[0];
   if ((val >= 0) && (val <= 255))
   {
      ioAddress[LINK_CTL] &= ~(0x0000ff00);
      ioAddress[LINK_CTL] |= ((val & 0xff) << 8);
   }
   
   /* Change Active Transceiver */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(TXRX_ARG)[0], 0x00000010);

   /* Receive Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[0], 0x00020000);

   /* Transmit Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[1], 0x00010000);
   
   /* Retransmit Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[2], 0x00040000);

   /* Write Me Last Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[3], 0x00100000);

   /* Electronic Wrap Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[4], 0x00080000);

   /* Byte Swap GT Memory Enable */
   setOption(&ioAddress[USR_BRD_CSR], (int32_t)mxGetPr(NODE_ARG)[5], 0x00000002);

   /* Word Swap GT Memory Enable */
   setOption(&ioAddress[USR_BRD_CSR], (int32_t)mxGetPr(NODE_ARG)[6], 0x00000001);

   /* D64 Enable */
   setOption(&ioAddress[USR_BRD_CSR], (int32_t)mxGetPr(NODE_ARG)[7], 0x00000010);

   /* Broadcast Interrupt Mask */
   if ((int_T)mxGetPr(NODE_ARG)[8] == 1)
   {
      ioAddress[RX_HBI_MSK] = (uint32_t)mxGetPr(BMASK_ARG)[0];
      //ioAddress32[RX_HBI_MSK] = (int_T)mxGetPr(BMASK_ARG)[0];
	  SG_PRINTF(INFO, "bmask = %x, %x, %f\n", (uint32_T)mxGetPr(BMASK_ARG)[0], (int_T)mxGetPr(BMASK_ARG)[0], mxGetPr(BMASK_ARG)[0] );      
   }

   /* Self Interrupt Enable */
   setOption(&ioAddress[LINK_CTL], (int32_t)mxGetPr(NODE_ARG)[9], 0x00200000);

   /* Unicast Interrupt Enable */
   setOption(&ioAddress[RX_HUI_MSK], (int32_t)mxGetPr(NODE_ARG)[10], 0x00000001);

   /* Link Error Interrupt Enable */
   setOption(&ioAddress[INT_CSR], (int32_t)mxGetPr(NODE_ARG)[11], 0x00040000);

   /* Active Laser Enable */
   val = ((ioAddress[LINK_CTL] & 0x00000010) >> 4);
   laserEn[0] = (int_T)mxGetPr(NODE_ARG)[13];
   laserEn[1] = (int_T)mxGetPr(NODE_ARG)[14];
   
   switch ((int_T)mxGetPr(NODE_ARG)[12])
   {
      case 0:
         laserEn[val] = 0;
         break;
      case 1:
         laserEn[val] = 1;
         break;
    }

   /* Laser 0 Enable */
   setOption(&ioAddress[LINK_CTL], laserEn[0], 0x00000001);

   /* Laser 1 Enable */
   setOption(&ioAddress[LINK_CTL], laserEn[1], 0x00000002);
   
   SG_PRINTF(DEBUG, "mldStart complete for GT card ioAddr=%x\n",ioAddress);
   SG_PRINTF(INFO, "Initialization OK\n");
#endif
}

#ifndef MATLAB_MEX_FILE
static void setOption(volatile uint32_t *addr, int32_t value, uint32_t reg_mask)
{
   switch (value)
   {
      case -1: /* No Change */
         break;
      case 0: /* Disable */
         *addr &= ~(reg_mask);
         break;
      case 1: /* Enable */   
         *addr |= reg_mask;
         break;
   }
}
#endif

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
#endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
