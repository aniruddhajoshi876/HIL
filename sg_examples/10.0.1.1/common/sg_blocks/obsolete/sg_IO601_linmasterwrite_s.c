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
//#define DEBUG_PRINT_FUNCTION_CALLS

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_linmasterwrite_s

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



#define MODULE_ARG             ssGetSFcnParam(S, 0)
#define NBMESSAGES_ARG         ssGetSFcnParam(S, 1)
#define SAMP_TIME_ARG          ssGetSFcnParam(S, 2)
#define SLOT_ARG               ssGetSFcnParam(S, 3)
#define ENHANCED_CS_ARG        ssGetSFcnParam(S, 4)
#define NUMBER_OF_ARGS                       (   5)

#define NO_I_WORKS             (2)
#define BASE_ADDR_I_IND        (0)
#define BASE_ADDR0_I_IND       (1)


#define NO_R_WORKS             (0)

#define NO_P_WORKS             (0)

extern uint8_T ptrWritePointer[];
static char_T msg[256];


#define LIN_k_CLASSIC  (0) // calculate classic checksum for LIN 1.3 and earlier
#define LIN_k_ENHANCED (1) // calculate enhanced checksum for LIN 2.0 and newer (except for id 60 and 61)

#ifndef MATLAB_MEX_FILE

/* LIN message is the datatype as used by IXXAT
 * bId          -> identifier
 * bModel       -> classic or enhanced checksum
 * bCheckSum    -> checksum
 * bSendData    -> 0: send header only, 1: send full frame
 * bLength      -> valid data count of bDataByte field
 * bDummy       -> padding byte
 * bDataByte[8] -> data
 */
typedef struct
{
    uint8_T bId;
    uint8_T bModel;
    uint8_T bCheckSum;
    uint8_T bSendData;  
    uint8_T bLength;
    uint8_T bDummy;
    uint8_T bDataByte[8];
}BCI_t_LIN_MSG;

typedef struct QUEUEENTRY
{
    uint8_T status;
    uint8_T count;
    uint8_T timeStamp[4];
    uint8_T type;
    uint8_T information;
    BCI_t_LIN_MSG sMsg;
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

/*************************************************************************
**
** Function    : CheckSum 
**
** Description : Creates the Checksum in Classic and enhanced form and
**               returns the Checksum
**               (originally "LIN_CreateChecksum" received from Andreas Stobe in Technical Support at IXXAT via email 16-06-2015))
**
** Parameters  : p_Msg (IN)      - LIN-Message
**
** Returnvalue : Checksum
**
*************************************************************************/
static uint8_T CheckSum(uint8_T bModel, uint8_T bId, uint8_T bLength, uint8_T data[])
{
    uint8_T i;
    uint16_T w_LocalHelp = 0;

    // Enhanced checksum
    if (bModel == LIN_k_ENHANCED)
    {
        w_LocalHelp = bId;
        // if addition is over 0xFF then algorithm,
        if (w_LocalHelp > 0xFF)
        {
          w_LocalHelp -= 0xFF;     // see above
        }
    }
 
    for (i = 0; i < bLength; i++)
    {
        w_LocalHelp = w_LocalHelp + data[i];
        if(w_LocalHelp > 0xFF)
        {
            w_LocalHelp -= 0xFF;     // see above
        }
    }
    
    

    
    //printf("data: 0x%X\n", data8);
    //printf("localhelp: 0x%X\n", w_LocalHelp);
    return(~w_LocalHelp); // return the inverted modulo-256 checksum
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
static int8_T SendLINMessage(SimStruct *S, uint32_T base2, uint8_T module, uint8_T id, uint8_T type, uint8_T length, uint8_T *data)
{  
    
    /*
     * Variable declaration:
     */
    int32_T frc, position;
    uint8_T bModel;
    QUEUEENTRY *pQueue;

        
    /*
     * Initialization
     */    
    frc = 1;   

    if ((id < 0 || id > 63) && type == 0)
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
            sprintf(msg, "LMW SendLINMessage: ptrWritePointer is NULL\n");
            ssSetErrorStatus(S, msg);
            return -3;
        }
        position = ptrWritePointer[module]; // get the current buffer position for port 1.
        pQueue = (QUEUEENTRY *)(base2 + 0x1000 + position * sizeof(QUEUEENTRY));      

        /* Is the queue entry free? */
        if (pQueue->status == 0)
        {           
            /* Write the queue entry */                      
            pQueue->count = 12 + length;
            //printf("count: %d (%d)\n", pQueue->count, 12 + length);
            pQueue->type = type; //3 = wakeup, 0= data
            pQueue->information = 0;
            pQueue->sMsg.bId = CreateID(id);
            
            // Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum
            if((id == 60) || (id == 61) || (mxGetPr(ENHANCED_CS_ARG)[0] == 0))
                bModel = LIN_k_CLASSIC;
            else
                bModel = LIN_k_ENHANCED;
            
            pQueue->sMsg.bModel = bModel;            
            pQueue->sMsg.bCheckSum = CheckSum(bModel, CreateID(id), length, data);
            pQueue->sMsg.bSendData = 1;
            pQueue->sMsg.bLength = length;
            pQueue->sMsg.bDummy = 0;
            pQueue->sMsg.bDataByte[0] = data[0];
            pQueue->sMsg.bDataByte[1] = data[1];
            pQueue->sMsg.bDataByte[2] = data[2];
            pQueue->sMsg.bDataByte[3] = data[3];
            pQueue->sMsg.bDataByte[4] = data[4];
            pQueue->sMsg.bDataByte[5] = data[5];
            pQueue->sMsg.bDataByte[6] = data[6];
            pQueue->sMsg.bDataByte[7] = data[7];
            
            //printf("%d <--> %d\n", data[7], pQueue->sMsg.bDataByte[7]);
            
            //memcpy(pQueue->sMsg.bDataByte, data, 8);
            pQueue->status = 1;
            
            /* increment the position in the DPRAM buffer (0 to 49)*/
            //printf("%d\n", position);
            position = (position >= 49)? 0 : ++position;            

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

	ssSetNumInputPorts(S, 11);
    
    for (i = 0; i < 11; i++)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1); 
        ssSetInputPortDataType(S, i, SS_UINT8); 
        ssSetInputPortWidth(S, i, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
    }

    ssSetNumOutputPorts(S, 0);
    
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
    printf("MWstart begin\n");
    #endif

    /* board detection */
    if (mxGetN(SLOT_ARG) == 1)
    {
        bus = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus  = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }
    
    /* look for the PCI-Device */
    if (xpcGetPCIDeviceInfo((uint16_T)VENDORID, (uint16_T)DEVICEID, (uint16_T)SUBVENDORID, (uint16_T)SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s LMW (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }
     
    rl32eWaitDouble(0.05); // the mobile machine crashes without this additional delay. The reason for this is unknown yet.

    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);    
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE); 
    
    ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, BASE_ADDR0_I_IND, pciinfo.VirtAddress[0]);
    
    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MWstart end\n");
    #endif
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{    
#ifndef MATLAB_MEX_FILE       
    
    // variable used to collect data at the input port.
    uint8_T data[8];
    uint8_T id;
    uint8_T length;  
    uint8_T i, j;
    uint8_T *u;
    int8_T frc;
    uint8_T type;
    
    // pointer to PCI memory map.    
    volatile uint32_T *ioaddress0;
    uint32_T base0, base2;

    // interrupt register;
    uint32_T regtemp;   
    uint8_T module;
    
    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MW begin");
    #endif
    
    base0 = ssGetIWorkValue(S, BASE_ADDR0_I_IND);
    ioaddress0 = (void *)base0;   
    
    base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    module = (uint32_T)mxGetPr(MODULE_ARG)[0] - 1;
 
      
    
    /* get the input port data and build the queue entry. */
    for (i = 0; i < (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]; i++)
    {            
        // we read the input port:
        u = (uint8_T *)ssGetInputPortSignal(S, 0);  
        type = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 1);         
        id = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 2);  
        length = (uint8_T)u[i];
        
        for (j = 0; j < 8; j++)
        {
            u = (uint8_T *)ssGetInputPortSignal(S, 3 + j);  
            data[j] = (uint8_T)u[i];     
        }          

        frc = SendLINMessage(S, base2, module, id, type, length, data);
        switch(frc)
        {       
            case 1:
                // we emit the interrupt to the MC.
                regtemp = ioaddress0[0x15];
                ioaddress0[0x15] = regtemp & ~(1 << 2);
                ioaddress0[0x15] = regtemp | (1 << 2);
                break;
                
            case -1:            
                sprintf(msg, "%s LIN queue overloaded.", DEVNAME);
                ssSetErrorStatus(S, msg);
                return;


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
    #ifdef DEBUG_PRINT_FUNCTION_CALLS
    printf("MW end");
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
