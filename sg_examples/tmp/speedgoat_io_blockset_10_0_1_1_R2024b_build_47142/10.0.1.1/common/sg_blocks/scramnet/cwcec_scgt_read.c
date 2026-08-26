/* Curtiss Wright Controls embedded Computing */
/* SCRAMNet GT Read function */

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         cwcec_scgt_read

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
#endif

/* Input Arguments */
#define NUMBER_OF_ARGS        (5)
#define OFFSET_ARG            ssGetSFcnParam(S, 0)
#define NWORDS_ARG            ssGetSFcnParam(S, 1)
#define SAMPLETIME_ARG        ssGetSFcnParam(S, 2)
#define SLOT_ARG              ssGetSFcnParam(S, 3)
#define MODULE_ID             ssGetSFcnParam(S, 4)

#define NO_I_WORKS            (0)
#define NO_R_WORKS            (0)

#define NO_P_WORKS            (1)
#define BASE_ADDR_P_IND       (0)

#define VENDOR_ID             (0x1387)
#define DEVICE_ID             (0x5310)
#define DEVICE_NAME           "SCRAMNet GT"

static char_T msg[256];

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
   ssSetOutputPortWidth(S, 0, (int_T)mxGetPr(NWORDS_ARG)[0]);
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
   //uint32_T memSize;
   sg_PCIDevice pciInfo;
   //uintptr_t ioAddressPtr;
   //volatile uint32_t * ioAddress;
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

   /* Figure out the memory size - NOT USED ANYMORE*/
 /*  switch (ioAddress[0] & 0x00000003)
   {
      case 0:
         memSize = 0x08000000;
         break;
      case 1:
         memSize = 0x10000000;
         break;
      case 2:
         memSize = 0x20000000;
         break;
      default:
         memSize = 0x08000000;
         break;
   } */


   ssSetPWorkValue(S, BASE_ADDR_P_IND, (void *)(uintptr_t)sg_mapMemory(&pciInfo, 2));

#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
   uint32_T i;
   uint32_T *y = (uint32_T *)ssGetOutputPortSignal(S, 0);
   uint32_T nwords = (uint32_T)mxGetPr(NWORDS_ARG)[0];
   uint32_T offset = (uint32_T)mxGetPr(OFFSET_ARG)[0];
   volatile uint32_T *ioAddress32 =
       (volatile uint32_T *)ssGetPWorkValue(S, 0);

   for (i = 0; i < nwords; i++)
   {
      y[i] = ioAddress32[(offset / 4) + i];
   }
#endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
