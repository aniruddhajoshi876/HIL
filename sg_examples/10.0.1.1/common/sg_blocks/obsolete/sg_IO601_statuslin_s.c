/**************************************************************************
 * S-Function: Lin master write
 *
 * This block has 10 inputs of size M
 * M is a static parameter (number of messages to send).
 *
 * The different inputs are:
 * 1. Identifier
 * 2. Length (between 1 and 8)
 * 3. Data1
 * 4. Data2
 * 5. Data3
 * 6. Data4
 * 7. Data5
 * 8. Data6
 * 9. Data7
 * 10. Data10
 *
 * At the moment, this is not optimized. Ideally, we would replace these
 * inputs by a LIN_MESSAGE datatype.
 *
 * Data1 to Data8 have their own input to avoid a matrix.
 *
 *************************************************************************/

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_statuslin_s

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include <windows.h>
#include "xpcimports.h"
#endif

#define DEVNAME                "Speedgoat IO601"
#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#define NUMBER_OF_ARGS         (2)


#define SAMP_TIME_ARG          ssGetSFcnParam(S, 0)
#define SLOT_ARG               ssGetSFcnParam(S, 1)

#define NO_I_WORKS             (2)
#define BASE_ADDR_I_IND        (0)
#define BASE_ADDR0_I_IND       (1)


#define NO_R_WORKS             (0)

#define NO_P_WORKS             (0)

#define CMD_GET_LIN_STAT       (0x29)


static char_T msg[256];


typedef struct 
{
    uint8_T synch;
    uint8_T count;
    uint16_T reserved;
    uint8_T command;
    uint8_T data[75];
}BCICOMMAND;


#ifndef MATLAB_MEX_FILE



static void InterruptMicroController(volatile uint32_T *ioaddress0)
{
    uint32_T regtemp;  
    
    /* generate MC interrupt */
    regtemp = ioaddress0[0x15];
    ioaddress0[0x15] = regtemp & ~(1 << 2);
    ioaddress0[0x15] = regtemp | (1 << 2);
}

static uint8_T GetLINStatus(volatile uint32_T *ioaddress0, volatile BCICOMMAND *bci)
{  
   bci->synch = 0;
   bci->count = 2;
   bci->command = CMD_GET_LIN_STAT;
   bci->synch = 1; 
   
   InterruptMicroController(ioaddress0);

   while (bci->synch != 2);  
   
   return bci->data[0];

}


#endif




static void mdlInitializeSizes(SimStruct *S)
{

    int_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg, "Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

	ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 4);
    for (i = 0; i < 4; i++)
    {
        ssSetOutputPortDataType(S, i, SS_UINT32); 
        ssSetOutputPortWidth(S, i, 1);
    }

    
    
    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamNotTunable(S, i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}



static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
    if (mxGetN((SAMP_TIME_ARG)) == 1)
    {
        ssSetOffsetTime(S, 0, 0.0);
    } 
    else 
    {
        ssSetOffsetTime(S, 0, mxGetPr(SAMP_TIME_ARG)[1]);
    }

}

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;
    int32_T  bus, slot;
    
    /* board detection */
    if (mxGetN(SLOT_ARG) == 1)
    {
        bus = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }

    /* look for the PCI-Device */
    if (xpcGetPCIDeviceInfo((uint16_T)VENDORID, (uint16_T)DEVICEID, (uint16_T)SUBVENDORID, (uint16_T)SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }

    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);    
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE); 
    ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, BASE_ADDR0_I_IND, pciinfo.VirtAddress[0]);
    
           
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{    
#ifndef MATLAB_MEX_FILE       
    
    // variable used to collect data at the input port.
    uint32_T *out;
    uint8_T retCode;
    volatile BCICOMMAND *bci;
    
    // pointer to PCI memory map.    
    volatile uint32_T *ioaddress0;
    uint32_T base0, base2;
 

    base0 = ssGetIWorkValue(S, BASE_ADDR0_I_IND);
    ioaddress0 = (void *)base0;   
    
    base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    bci = (volatile BCICOMMAND *)(base2);    
    
 
    retCode = GetLINStatus(ioaddress0, bci);
    if (retCode == 0)
    {
        sprintf(msg, "%s: Strong error detected, please contact Speedgoat.", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }
    else if (retCode == 2)
    {
        sprintf(msg, "%s: Firmware does not support LIN.", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }
    out = (uint32_T *)ssGetOutputPortSignal(S, 0);  
    out[0] = bci->data[1]; // OpMode
    
    out = (uint32_T *)ssGetOutputPortSignal(S, 1);  
    out[0] = bci->data[2]; // BusLoad
    
    out = (uint32_T *)ssGetOutputPortSignal(S, 2);  
    out[0] = bci->data[3] | (bci->data[4] << 8); // Baudrate
    
    out = (uint32_T *)ssGetOutputPortSignal(S, 3);  
    out[0] = bci->data[5] | (bci->data[6] << 8) | (bci->data[7] << 16) | (bci->data[8] << 24); // status
    
   
#endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef  MATLAB_MEX_FILE    
#endif
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
