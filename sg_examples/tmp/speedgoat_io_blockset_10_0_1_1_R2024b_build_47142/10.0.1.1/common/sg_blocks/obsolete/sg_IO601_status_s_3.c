#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_status_s_3

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
#include "ioext_xpcimport.h"
#endif

#define NUMBER_OF_ARGS         (3)
#define MODULEID_ARG           ssGetSFcnParam(S,0)
#define SAMP_TIME_ARG          ssGetSFcnParam(S,1)
#define SLOT_ARG               ssGetSFcnParam(S,2)

#define DEVNAME                "Speedgoat IO601"
#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#define NO_I_WORKS             (1)
#define IOADDRESS_I_IND        (0)
#define NO_R_WORKS             (0)


static char_T msg[256];

typedef struct 
{
    uint16_T status0;
    uint16_T busLast0;
    uint16_T status1;
    uint16_T busLast1;
    uint16_T CPUlast;
    uint16_T liveCounter;
} CANSTATUS;


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
    
    ssSetNumOutputPorts(S, 6);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortWidth(S, 1, 1);
    ssSetOutputPortWidth(S, 2, 1);
    ssSetOutputPortWidth(S, 3, 1);
    ssSetOutputPortWidth(S, 4, 1);
    ssSetOutputPortWidth(S, 5, 1);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUMBER_OF_ARGS; i++) 
    {
        ssSetSFcnParamNotTunable(S,i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}


#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;
    int32_T bus, slot;
    volatile CANSTATUS *status;
    
    uint32_T nbOccurences, temp;


    /* board detection */
    if (mxGetN(SLOT_ARG) == 1)
    {
        if ((int32_T)mxGetPr(SLOT_ARG)[0] == -1)
        {
            nbOccurences = 0;
              
            // browse bus and slot until deviceID and vendorID have been found
            for (bus = 0; bus < 256; bus++)
            {
                for (slot = 0; slot < 32; slot++)
                {
                    xpcOutpDW(0xCF8, 0x80000000 | (bus << 16) | (slot << 11));
                    temp = xpcInpDW(0xCFC);

                    if ((temp & 0xFFFF) == VENDORID && ((temp >> 16)& 0xFFFF) == DEVICEID)
                    {
                        
                        nbOccurences += 1;
                        if (nbOccurences == ((uint32_T)mxGetPr(MODULEID_ARG)[0]))     
                        {
                            break;
                        }
                    }

                }

                if (nbOccurences == ((uint32_T)mxGetPr(MODULEID_ARG)[0]))
                {
                    break;
                }              
            };
            
            if (nbOccurences < ((uint32_T)mxGetPr(MODULEID_ARG)[0]))     
            {
                sprintf(msg, "%s: Failed to find I/O Module with ID %d", DEVNAME, (uint32_T)mxGetPr(MODULEID_ARG)[0]);
                ssSetErrorStatus(S, msg);
                return;
            }
        }
        else
        {
            bus = 0;
            slot = (int_T)mxGetPr(SLOT_ARG)[0];
        }
    }
    else
    {
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }

    /* look for the PCI-Device */
    if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }

    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE);  
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);  
    
    //ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    status = (volatile CANSTATUS *)(pciinfo.VirtAddress[2]);    
    ssSetIWorkValue(S, IOADDRESS_I_IND, pciinfo.VirtAddress[2]);
    
#endif

}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE  
    uint32_T base;
    volatile CANSTATUS *status;
    real_T *out;
    volatile uint8_T *ioaddress2;
    
    ioaddress2=(void *)ssGetIWorkValue(S, IOADDRESS_I_IND);
    
    ioaddress2[8192]= 0x00;
    if (ioaddress2[8192]!= 0x00) {
        ioaddress2[8192]= 0x01;
        //printf("return\n");
        return;
    }
    
    base = ssGetIWorkValue(S, IOADDRESS_I_IND);
    status = (CANSTATUS *)(base + 0xFF0);
    
    out = (real_T*)ssGetOutputPortSignal(S, 0);    
    out[0] = status->status0;
    
    out = (real_T*)ssGetOutputPortSignal(S, 1);    
    out[0] = status->busLast0;
    
    out = (real_T*)ssGetOutputPortSignal(S, 2);    
    out[0] = status->status1;
    
    out = (real_T*)ssGetOutputPortSignal(S, 3);    
    out[0] = status->busLast1;
    
    out = (real_T*)ssGetOutputPortSignal(S, 4);    
    out[0] = status->CPUlast;
    
    out = (real_T*)ssGetOutputPortSignal(S, 5);    
    out[0] = status->liveCounter;   

    
    ioaddress2[8192]= 0x01;  
    
#endif
}

static void mdlTerminate(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE      
#endif 
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
