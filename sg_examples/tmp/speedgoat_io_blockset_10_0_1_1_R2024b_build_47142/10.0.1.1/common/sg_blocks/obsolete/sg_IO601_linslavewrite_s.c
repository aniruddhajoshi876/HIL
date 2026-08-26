/**************************************************************************
 * S-Function: Lin master write
 *
 * This block has 10 inputs of size M
 * M is a static parameter (number of messages to read).
 *
 * The different inputs are:
 * 1.  Identifier
 * 2.  Length (between 1 and 8)
 * 3.  Data1
 * 4.  Data2
 * 5.  Data3
 * 6.  Data4
 * 7.  Data5
 * 8.  Data6
 * 9.  Data7
 * 10. Data8
 *
 * At the moment, this is not optimized. Ideally, we would replace these
 * inputs by a LIN_MESSAGE datatype.
 *
 *
 * TODO: use real Semaphores instead of t_semaphores!
 *
 *
 *
 *************************************************************************/
#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_linslavewrite_s

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
#define SHOWVALIDINPUT_ARG     ssGetSFcnParam(S, 1)
#define NBMESSAGES_ARG         ssGetSFcnParam(S, 2)
#define SAMP_TIME_ARG          ssGetSFcnParam(S, 3)
#define SLOT_ARG               ssGetSFcnParam(S, 4)
#define ENHANCED_CS_ARG        ssGetSFcnParam(S, 5)
#define NUMBER_OF_ARGS                       (   6)

#define NO_I_WORKS             (2)
#define BASE_ADDR_I_IND        (0)
#define BASE_ADDR0_I_IND       (1)

#define NO_R_WORKS             (0)
#define NO_P_WORKS             (0)

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

typedef struct
{
    uint16_T CANStatusBuffer;
    uint16_T LINStatusBuffer;
    uint16_T LINUpdateBuffer1;
    uint16_T LINUpdateBuffer2;
}t_semaphores;

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
static uint8_T CheckSum(volatile BCI_t_LIN_MSG* p_Msg)
{
    uint8_T i;
    uint16_T w_LocalHelp = 0;

    // Enhanced checksum
    if (p_Msg->bModel == LIN_k_ENHANCED)
    {
        w_LocalHelp = p_Msg->bId;
        // if addition is over 0xFF then algorithm,
        if (w_LocalHelp > 0xFF)
        {
          w_LocalHelp -= 0xFF;     // see above
        }
    }
 
    for (i = 0; i < p_Msg->bLength; i++)
    {
        w_LocalHelp = w_LocalHelp + (uint8_T)p_Msg->bDataByte[i];
        // if addition is over 0xFF then algorithm,
        if(w_LocalHelp > 0xFF)
        {
            w_LocalHelp -= 0xFF;     // see above
        }
    }
    return(~w_LocalHelp); // return the inverted modulo-256 checksum
}

    

static int8_T UpdateLinTxBufDpramEntry(SimStruct *S, uint32_T base, uint8_T id, uint8_T length, uint8_T* data, uint8_T valid)
{  
    
    // Variable declaration:
    
    int32_T frc;
    volatile BCI_t_LIN_MSG *pMsg;
    volatile t_semaphores *pSema;
    uint8_T update0, update1;
        
    // Initialization        
    update0 = 0;
    update1 = 0;
    frc = 0;   
    pSema = (t_semaphores *)(base + 0x2000);

    if (id < 0 || id > 63)
    {
        frc = -2; //in standard, identifer cannot be larger 63
    }       
    
    if (length > 8)
    {
        frc = -3;
    }
    
    // No frame error: buffers are updated
    if (frc == 0)    
    {          
        while (!update0 || !update1)
        {
            // we try to obtain the semaphore of buffer image 1    
            if (!update0 && (pSema->LINUpdateBuffer1 & 1))  
            {
                while ((pSema->LINUpdateBuffer1 & 1) != 0)     
                {
                    pSema->LINUpdateBuffer1 &= ~1;
                };   

                pMsg = (BCI_t_LIN_MSG *)(base + 0x18A8 + id * sizeof(BCI_t_LIN_MSG));
                pMsg->bId = CreateID(id);
                pMsg->bSendData = valid;
                pMsg->bLength = length;
                pMsg->bDummy = 0;
                memcpy((uint8_T*)pMsg->bDataByte, data, 8);

                // Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum
                if ((id == 60) || (id == 61) || (mxGetPr(ENHANCED_CS_ARG)[0] == 0))
                    pMsg->bModel = LIN_k_CLASSIC;
                else
                    pMsg->bModel = LIN_k_ENHANCED;

                pMsg->bCheckSum = CheckSum(pMsg);

                // we release the semaphore
                pSema->LINUpdateBuffer1 |= 1;
                update0 = 1;

            }

             // we try to obtain the semaphore of buffer image 2    
            if (!update1 && (pSema->LINUpdateBuffer2 & 1))  
            {

                while ((pSema->LINUpdateBuffer2 & 1) != 0)     
                {
                    pSema->LINUpdateBuffer2 &= ~1;
                };   


                pMsg = (BCI_t_LIN_MSG *)(base + 0x1C28 + id * sizeof(BCI_t_LIN_MSG));
                pMsg->bId = CreateID(id);

                // Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum
                if((id == 60) || (id == 61) || (mxGetPr(ENHANCED_CS_ARG)[0] == 0))
                    pMsg->bModel = LIN_k_CLASSIC;
                else
                    pMsg->bModel = LIN_k_ENHANCED;


                pMsg->bSendData = valid;
                pMsg->bLength = length;
                pMsg->bDummy = 0;
                memcpy((uint8_T*)pMsg->bDataByte, data, 8);
                pMsg->bCheckSum = CheckSum(pMsg);

                // we release the semaphore
                pSema->LINUpdateBuffer2 |= 1; 
                update1 = 1;
            }    
        }
    }
                
    return frc;
    
}
#endif


static void mdlInitializeSizes(SimStruct *S)
{

    int_T i, nbPorts;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg, "Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    
    // define the inputs
    
    if ((uint32_T)mxGetPr(SHOWVALIDINPUT_ARG)[0])
    {
        nbPorts = 11;
    }
    else
    {
        nbPorts = 10;
    }
    ssSetNumInputPorts(S, nbPorts); 
        
    for (i = 0; i < nbPorts; i++)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1); 
        ssSetInputPortDataType(S, i, SS_UINT8); 
        ssSetInputPortWidth(S, i, (uint32_T)mxGetPr(NBMESSAGES_ARG)[0]);
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
        sprintf(msg, "%s LSW (bus %d, slot %d): board not present", DEVNAME, bus, slot);
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

    uint8_T *u;
    uint8_T id, length, valid;
    uint8_T data[8];
    
    

    uint32_T i;
    volatile uint32_T *ioaddress0;
    uint32_T regtemp;   


    uint32_T base0 = ssGetIWorkValue(S, BASE_ADDR0_I_IND);
    uint32_T base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    ioaddress0 = (void *)base0;    
    
    //printf("test 1 lin slave write\n");
    for (i = 0; i < (uint8_T)mxGetPr(NBMESSAGES_ARG)[0]; i++)
    {             

        // we read the input port:
        u = (uint8_T *)ssGetInputPortSignal(S, 0);  
        id = (uint8_T)u[i];   
        
        u = (uint8_T *)ssGetInputPortSignal(S, 1);        
        length = (uint8_T)u[i];
                
        u = (uint8_T *)ssGetInputPortSignal(S, 2);
        data[0] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 3); 
        data[1] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 4); 
        data[2] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 5); 
        data[3] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 6); 
        data[4] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 7); 
        data[5] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 8); 
        data[6] = (uint8_T)u[i];
        
        u = (uint8_T *)ssGetInputPortSignal(S, 9); 
        data[7] = (uint8_T)u[i];        
                
        if ((uint32_T)mxGetPr(SHOWVALIDINPUT_ARG)[0])
        {
            u = (uint8_T *)ssGetInputPortSignal(S, 10); 
            valid = u[i];
        }
        else
        {
            valid = 1;
        }
        
                
        //printf("test 2 lin slave write\n");
        if (UpdateLinTxBufDpramEntry(S, base2, id, length, data, valid) == 1)
        {
            regtemp = ioaddress0[0x15];
            ioaddress0[0x15] = regtemp & ~(1 << 2);
            ioaddress0[0x15] = regtemp | (1 << 2);
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
