/**************************************************************************
 * S-Function: Lin master read
 *
 * This block has 2 inputs of size M
 * M is a static parameter (number of messages to read).
 *
 * The different inputs are:
 * 1. Identifier
 * 2. Length (between 1 and 8)
 *
 *
 * This block has 12 outputs of size M
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

//#define DEBUG_PRINT_FUNCTION_CALLS
//#define DEBUG_VERBOSE

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_linmasterread_s

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

extern uint8_T ptrWritePointer[];
extern uint8_T ptrReadPointer[];

static char_T msg[256];


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

typedef struct
{
  uint8_T o0:1, o1:1, o2:1, o3:1, o4:1, o5:1, o6:1, o7:1;
}
t_BITSINBYTE_S;

typedef union
{
  uint8_T b;
  t_BITSINBYTE_S u;
}
t_BITSINBYTE_U;




/**************************************************************************
 * Two parity bits are computed P0 and P1.
 *
 * P0 = id(0) xor id(1) xor id(2) xor id(4)
 * P1 = !(id(1) xor id(3) xor id(4) xor id(5))
 *
 * The identifier is then:
 * 
 * 0: id0
 * 1: id1
 * 2: id2
 * 3: id3
 * 4: id4
 * 5: id5
 * 6: P0
 * 7: P1 
 *
 *************************************************************************/
static uint8_T CreateID(uint8_T id)
{

  t_BITSINBYTE_U u_id;

  u_id.b = id;                                                  /* get the id */
  u_id.u.o6 = u_id.u.o0 ^ u_id.u.o1 ^ u_id.u.o2 ^ u_id.u.o4;    /* create even parity p0 */
  u_id.u.o7 = ~(u_id.u.o1 ^ u_id.u.o3 ^ u_id.u.o4 ^ u_id.u.o5); /* create odd parity p1 */
  
  return (uint8_T) u_id.b;
  
}

    


/**************************************************************************
 *               
 * a LIN entry contains up to 22 elements (byte), which are:
 *|-----------------------|
 *|  n    |   LIN         |
 *|-----------------------|
 *|  0    |   status      |
 *|  1    |   count       |
 *|  2    |   timeStamp   |
 *|  3    |   timeStamp   |
 *|  4    |   timeStamp   |
 *|  5    |   timeStamp   |
 *|  6    |   type        |
 *|  7    |   information |
 *|  8    |   identifier  |
 *|  9    |   model       |
 *| 10    |   checkSum    |
 *| 11    |   sendData    |
 *| 12    |   length      |
 *| 13    |   dummy       |
 *| 14    |   data        |
 *| 15    |   data        |
 *| 16    |   data        |
 *| 17    |   data        |
 *| 18    |   data        |
 *| 19    |   data        |
 *| 20    |   data        |
 *| 21    |   data        |
 *|-----------------------/
 *
 * TimeStamp is not relevant. Because the MC generates it.
 *
 * Type is 0 for data message
 * Type is 2 for error message
 * Type is 3 for wakeup message
 * 
 * Information (bInfo) is a three bits data (only relevant on RX)
 * 0: 0-> no overrun, 1-> overrun
 * 1: 0-> received message, 1-> sent message (self reception)
 * 2: 0-> identifier and data, 1-> identifier only
 *
 * Model       -> classic or enhanced checksum
 * 
 * sendData    -> 0: send header only, 1: send full frame
 * length      -> valid data count of bDataByte field
 * dummy       -> padding byte
 *     
 *************************************************************************/
static int8_T SendLINMessage(SimStruct *S, uint32_T base2, uint8_T module, uint8_T id, uint8_T length, uint8_T *data)
{  
    
    /*
     * Variable declaration:
     */
    int32_T frc, position;
    volatile QUEUEENTRY *pQueue;

        
    /*
     * Initialization
     */    
    frc = 1;   

    if (id < 0 || id > 63)
    {
        frc = -2; //in standard, identifer cannot be larger 63
    }       
    
    if (length > 8)
    {
        frc = -3;
    }
    
    /* when the frames passed all the tests, we send it. A negative ident
       is a "don't send this message" flag. */
    if (frc > 0)    
    {           
        if(!ptrWritePointer)
        {
            sprintf(msg, "LMR SendLINMessage: ptrWritePointer is NULL\n");
            ssSetErrorStatus(S, msg);
            return -3;
        }
        position = ptrWritePointer[module]; // get the current buffer position for port 1.
        pQueue = (QUEUEENTRY *)(base2 + 0x1000 + position * sizeof(QUEUEENTRY));      

        /* Is the queue entry free? */
        if (pQueue->status == 0)
        {           
            /* Write the queue entry */            
            pQueue->status = 1;
            pQueue->count = 12 + length;
            pQueue->type = 0;
            pQueue->information = 0;
            pQueue->identifier = CreateID(id);
            pQueue->model = 0;
            pQueue->checkSum = 0;
            pQueue->sendData = 0;
            pQueue->length = length;
            //printf("pQueue->length: %d\n", pQueue->length);
            pQueue->dummy = 0;
            pQueue->data[0] = data[0];
            pQueue->data[1] = data[1];
            pQueue->data[2] = data[2];
            pQueue->data[3] = data[3];
            pQueue->data[4] = data[4];
            pQueue->data[5] = data[5];
            pQueue->data[6] = data[6];
            pQueue->data[7] = data[7]; 

            /* increment the position in the DPRAM buffer (0 to 49)*/
            position = (position == 49)? 0 : ++position;

            /* save the position */
            ptrWritePointer[module] = position;  
            
            
        } 
        else
        {
            frc = -1; /* the queue entry wasn't free. */
        }            
    }    
                
    return frc;
    
}

static uint8_T ReadLINBuffer(SimStruct *S, uint32_T base2, uint8_T module, uint8_T *timestamp, uint8_T *data, uint8_T *id, uint8_T *length, uint8_T *checksum, uint8_T *type, uint8_T *info)
{
    uint8_T position;
    volatile QUEUEENTRY *pQueue;
    
    position = ptrReadPointer[module]; // get the current buffer position for port 1.
    pQueue = (QUEUEENTRY *)(base2 + 0x144C + position * sizeof(QUEUEENTRY));  
    //printf("position: %d\n", position);
    
    if (pQueue->status)
    {
        pQueue->status = 0;
        timestamp[0] = pQueue->timeStamp[0]; 
        //printf("pQueue->timeStamp[0]: %d\n", pQueue->timeStamp[0]);
        timestamp[1] = pQueue->timeStamp[1]; 
        timestamp[2] = pQueue->timeStamp[2]; 
        timestamp[3] = pQueue->timeStamp[3]; 
        
        id[0] = pQueue->identifier;        
        //printf("pQueue->identifier: %d\n", pQueue->identifier);
        
        data[0] = pQueue->data[0];
        //printf("pQueue->data[0]: %d\n", pQueue->data[0]);
        data[1] = pQueue->data[1];
        data[2] = pQueue->data[2];
        data[3] = pQueue->data[3];
        data[4] = pQueue->data[4];
        data[5] = pQueue->data[5];
        data[6] = pQueue->data[6];
        data[7] = pQueue->data[7];
        
        length[0] = pQueue->length;
        //printf("pQueue->length: %d\n", pQueue->length);
        
        checksum[0] = pQueue->checkSum;
        type[0] = pQueue->type;
        info[0] = pQueue->information;
        
        // update the position
        position = (position == 49)? 0 : ++position; 
        ptrReadPointer[module] = position;
        return 1;
    }
    else
    {
        return 0;
    }
    
    
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

	
    // defines the blocks inputs
    ssSetNumInputPorts(S, 2);    
    for (i = 0; i < 2; i++)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1); 
        ssSetInputPortDataType(S, i, SS_UINT8); 
        ssSetInputPortWidth(S, i, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    }

    ssSetNumOutputPorts(S, 14);
  
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
    
    ssSetOutputPortDataType(S, 13, SS_UINT8); 
    ssSetOutputPortWidth(S, 13, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);

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
    
    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MRstart begin\n");
    #endif

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
        sprintf(msg, "%s LMR (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }
    
    rl32eWaitDouble(0.05); // see sg_IO601_linmasterwrite_s.c comment. Added it here as well just for preventive reasons.

    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);    
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE); 
    ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, BASE_ADDR0_I_IND, pciinfo.VirtAddress[0]);
           
    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MRstart end\n");
    #endif

#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{    
#ifndef MATLAB_MEX_FILE

    volatile uint8_T *out;
    volatile uint8_T *u;
    uint32_T *out32;
    uint32_T i, j, count, limit, fails;
    uint8_T id;
    uint8_T length;
    uint8_T data[8];
    uint8_T timestamp[4];
    uint8_T checksum;
    uint8_T type;
    uint8_T info;
    volatile uint32_T *ioaddress0;
    uint32_T regtemp;   
    uint8_T module;
    int8_T frc;
    real_T start, ticks;

    uint32_T base0 = ssGetIWorkValue(S, BASE_ADDR0_I_IND);
    uint32_T base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);

    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MR begin");
    #endif

    ioaddress0 = (void *)base0;   
    module = (uint32_T)mxGetPr(MODULE_ARG)[0] - 1;
    
    limit = 0;
    // We send the data.
    for (i = 0; i < (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]; i++)
    {
        // we read the input port:
        u = (uint8_T *)ssGetInputPortSignal(S, 0);         
        id = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 1);           
        length = (uint8_T)u[i];

        for (j = 0; j < 8; j++)
        {    
            data[j] = 0;
        }
        
        if (length == 0 && id == 0)
        {
            limit++;
        }
        else
        {
            frc = SendLINMessage(S, base2, module, id, length, data);
            switch(frc)
            {       
                case 1:
                    // we emit the interrupt to the MC.
                    regtemp = ioaddress0[0x15];
                    ioaddress0[0x15] = regtemp & ~(1 << 2);
                    ioaddress0[0x15] = regtemp | (1 << 2);
                    limit++; // we detect how many messages were successfuly sent.
                    break;
                    
                case -1:
                    printf("%s LIN MR queue overloaded.\n", DEVNAME);
                    // we emit the interrupt to the MC again (so it'll hopefully flush the queue.)
                    regtemp = ioaddress0[0x15];
                    ioaddress0[0x15] = regtemp & ~(1 << 2);
                    ioaddress0[0x15] = regtemp | (1 << 2);
                    
                    // sprintf(msg, "%s LIN queue overloaded.", DEVNAME);
                    // ssSetErrorStatus(S, msg);
                    // return;
                    break;

                case -2:
                    sprintf(msg, "%s Incorrect LIN id.", DEVNAME);
                    ssSetErrorStatus(S, msg);
                    return;
                
                case -3:
                    sprintf(msg, "%s Incorrect message length.", DEVNAME);
                    ssSetErrorStatus(S, msg);
                    return;
                    
                default:
                    sprintf(msg, "%s Unknown error in SendLINMessage().", DEVNAME);
                    ssSetErrorStatus(S, msg);
                    return;
            }
        }
    }     

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
        
        out = (uint8_T *)ssGetOutputPortSignal(S, 13); 
        out[i] = 0;
    }
    fails = 0;
    count = 0;
    start = rl32eGetTicksDouble();    
    while(count != limit) // When the data is written, we expect as many data as sent.        
    {        
        ticks = rl32eGetTicksDouble();
        if( ticks - start > 1193000.0 * 5.0) // 5.0 second timeout
        {
            sprintf(msg, "Failed to acquire valid data in a timely manner.");
            ssSetErrorStatus(S, msg);
            return;
        }
        // we read the queue and if successful we output the data.
        if (ReadLINBuffer(S, base2, module, timestamp, data, &id, &length, &checksum, &type, &info))
        {

        //printf("id: %d\n", id & 0x3F);
            
            out = (uint8_T *)ssGetOutputPortSignal(S, 0);                         
            out[count] = id & 0x3F; // we don't output the parity bits.
            
            out = (uint8_T *)ssGetOutputPortSignal(S, 12); 
            out[count] = type;
            
            if (type != 2)
            {
            
                out = (uint8_T *)ssGetOutputPortSignal(S, 1); 
                out[count] = length;

                out = (uint8_T *)ssGetOutputPortSignal(S, 2); 
                out[count] = data[0];

                out = (uint8_T *)ssGetOutputPortSignal(S, 3); 
                out[count] = data[1];

                out = (uint8_T *)ssGetOutputPortSignal(S, 4); 
                out[count] = data[2];

                out = (uint8_T *)ssGetOutputPortSignal(S, 5); 
                out[count] = data[3];

                out = (uint8_T *)ssGetOutputPortSignal(S, 6); 
                out[count] = data[4];

                out = (uint8_T *)ssGetOutputPortSignal(S, 7); 
                out[count] = data[5];

                out = (uint8_T *)ssGetOutputPortSignal(S, 8); 
                out[count] = data[6];

                out = (uint8_T *)ssGetOutputPortSignal(S, 9); 
                out[count] = data[7];
                
                out = (uint8_T *)ssGetOutputPortSignal(S, 11); 
                out[count] = checksum;
            

            
                out = (uint8_T *)ssGetOutputPortSignal(S, 13); 
                out[count] = info;
                
            }
            
            out32 = (uint32_T *)ssGetOutputPortSignal(S, 10); 
            out32[count] = timestamp[0] | (timestamp[1] << 8) | (timestamp[2] << 16) | (timestamp[1] << 24);               
                       
            

            count++;
        }       
        else
        {
            #ifdef DEBUG_VERBOSE
            printf(".");
            #endif
            fails++;
        }
    }
    
    // we can eventually output the count

    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MR end");
    #endif
    
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
