/**************************************************************************
 * S-Function: Lin slave read
 *
 * This block has 2 inputs of size M
 * M is a static parameter (number of messages to read).
 *
 * The different inputs are:
 * 1. Identifier
 * 2. Length (between 1 and 8)
 *
 *
 * This block has 15 outputs of size M
 * M is a static parameter (number of messages to read)
 *
 * The different outputs are:
 * 1.  Identifier
 * 2.  Length
 * 3.  Data1
 * 4.  Data2
 * 5.  Data3
 * 6.  Data4
 * 7.  Data5
 * 8.  Data6
 * 9.  Data7
 * 10. Data8
 * 11. TimeStamp 
 * 12. CheckSum
 *
 * At the moment, this is not optimized. Ideally, we would replace these
 * inputs by a LIN_MESSAGE datatype.
 *
 * Data1 to Data8 have their own input to avoid a matrix.
 *
 *************************************************************************/
#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_linslaveread_s

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

#define NUMBER_OF_ARGS         (4)

#define MODULE_ARG             ssGetSFcnParam(S, 0)
#define NBMESSAGES_ARG         ssGetSFcnParam(S, 1)
#define SAMP_TIME_ARG          ssGetSFcnParam(S, 2)
#define SLOT_ARG               ssGetSFcnParam(S, 3)

#define NO_I_WORKS             (2)
#define BASE_ADDR_I_IND        (0)
#define BASE_ADDR0_I_IND       (1)

#define NO_R_WORKS             (0)
#define NO_P_WORKS             (0)



static char_T msg[256];

extern uint8_T ptrReadPointer[];

#ifndef MATLAB_MEX_FILE
typedef struct QUEUEENTRY
{
    uint8_T status;
    uint8_T count;
    uint8_T timeStamp[4];
    uint8_T type;
    uint8_T information;
    uint8_T identifier;
    uint8_T model;
    uint8_T checkSum;
    uint8_T sendData;
    uint8_T length;
    uint8_T dummy;
    uint8_T data[8];    
}QUEUEENTRY;

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

	
    // defines the blocks inputs
    ssSetNumInputPorts(S, 0);    

    ssSetNumOutputPorts(S, 13);
 
    ssSetOutputPortDataType(S, 0, SS_UINT8); 
    ssSetOutputPortWidth(S, 0, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 1, SS_UINT8); 
    ssSetOutputPortWidth(S, 1, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 2, SS_UINT8); 
    ssSetOutputPortWidth(S, 2, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 3, SS_UINT8); 
    ssSetOutputPortWidth(S, 3, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 4, SS_UINT8); 
    ssSetOutputPortWidth(S, 4, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 5, SS_UINT8); 
    ssSetOutputPortWidth(S, 5, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 6, SS_UINT8); 
    ssSetOutputPortWidth(S, 6, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 7, SS_UINT8); 
    ssSetOutputPortWidth(S, 7, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 8, SS_UINT8); 
    ssSetOutputPortWidth(S, 8, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 9, SS_UINT8); 
    ssSetOutputPortWidth(S, 9, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 10, SS_UINT32); 
    ssSetOutputPortWidth(S, 10, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 11, SS_UINT8); 
    ssSetOutputPortWidth(S, 11, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    
    ssSetOutputPortDataType(S, 12, SS_UINT8); 
    ssSetOutputPortWidth(S, 12, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    

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
        sprintf(msg, "%s LSR (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }

    rl32eWaitDouble(0.05); // see sg_IO601_linmasterwrite_s.c comment. Added it here as well just for preventive reasons.

    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);    
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE); 
    ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, BASE_ADDR0_I_IND, pciinfo.VirtAddress[0]);
  
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{    
#ifndef MATLAB_MEX_FILE
    volatile uint8_T *ioaddress;
    uint8_T *out;
    uint32_T *out32;
    uint32_T i;
    uint8_T id;
    uint8_T length;
    uint8_T data[8];
    uint8_T timestamp[4];
    uint8_T checksum;
    uint8_T type;
    volatile QUEUEENTRY *pQueue;  
    uint8_T module;
    uint8_T position;

    uint32_T base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);

    ioaddress = (volatile uint8_T *)base2;   
    module = (uint8_T)mxGetPr(MODULE_ARG)[0] - 1;
        
    // We initialize the output to zero.
    
    for (i = 0; i < (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]; i++)
    {
        out = (uint8_T *)ssGetOutputPortSignal(S, 0);                         
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 1); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 2); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 3); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 4); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 5); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 6); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 7); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 8); 
        out[i] = 0;

        out = (uint8_T *)ssGetOutputPortSignal(S, 9); 
        out[i] = 0;

        out32 = (uint32_T *)ssGetOutputPortSignal(S, 10); 
        out32[i] = 0;            

        out = (uint8_T *)ssGetOutputPortSignal(S, 11); 
        out[i] = 0;
        
        out = (uint8_T *)ssGetOutputPortSignal(S, 12); 
        out[i] = 0;
    }
    
    

    for (i = 0; i < (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]; i++) 
    {   
    
        position = ptrReadPointer[module]; // get the current buffer position for port 1.
        pQueue = (volatile QUEUEENTRY *)(base2 + 0x144C + position * sizeof(QUEUEENTRY));  
        
        
        //while (ioaddress[8192 + 8] != 0x00)
        //{
        //    ioaddress[8192 + 8] = 0x00;
        //};    
        
        if (pQueue->status)
        {            
            timestamp[0] = pQueue->timeStamp[0]; 
            timestamp[1] = pQueue->timeStamp[1]; 
            timestamp[2] = pQueue->timeStamp[2]; 
            timestamp[3] = pQueue->timeStamp[3];             
            id = pQueue->identifier;

            data[0] = pQueue->data[0];
            //printf("new data: %d\n", pQueue->data[0]);
             
            data[1] = pQueue->data[1];
            data[2] = pQueue->data[2];
            data[3] = pQueue->data[3];
            data[4] = pQueue->data[4];            
            data[5] = pQueue->data[5];            
            data[6] = pQueue->data[6];   
            data[7] = pQueue->data[7];
            
            length = pQueue->length;

            
            
            //printf("pQueue->length: %d\n", pQueue->length);
            checksum = pQueue->checkSum;
            type = pQueue->type;
            
            // update the position
            position = (position == 49)? 0 : ++position; 
            ptrReadPointer[module] = position;
            
            pQueue->status = 0;

            
            out = (uint8_T *)ssGetOutputPortSignal(S, 0);                         
            out[i] = id & 0x3F; // we don't output the parity bits.

            out = (uint8_T *)ssGetOutputPortSignal(S, 1); 
            out[i] = length;

            out = (uint8_T *)ssGetOutputPortSignal(S, 2); 
            out[i] = data[0];

            out = (uint8_T *)ssGetOutputPortSignal(S, 3); 
            out[i] = data[1];

            out = (uint8_T *)ssGetOutputPortSignal(S, 4); 
            out[i] = data[2];

            out = (uint8_T *)ssGetOutputPortSignal(S, 5); 
            out[i] = data[3];

            out = (uint8_T *)ssGetOutputPortSignal(S, 6); 
            out[i] = data[4];

            out = (uint8_T *)ssGetOutputPortSignal(S, 7); 
            out[i] = data[5];

            out = (uint8_T *)ssGetOutputPortSignal(S, 8); 
            out[i] = data[6];

            out = (uint8_T *)ssGetOutputPortSignal(S, 9); 
            out[i] = data[7];

            out32 = (uint32_T *)ssGetOutputPortSignal(S, 10); 
            out32[i] = timestamp[0] | (timestamp[1] << 8) | (timestamp[2] << 16) | (timestamp[1] << 24);            

            out = (uint8_T *)ssGetOutputPortSignal(S, 11); 
            out[i] = checksum;

            out = (uint8_T *)ssGetOutputPortSignal(S, 12); 
            out[i] = type;            
        } 
        else
        {
            break;
        }


    }
     
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
