#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_read_s_3

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h" 


#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
// 
#ifndef MATLAB_MEX_FILE
#include <windows.h>
#include "xpcimports.h"
#include "ioext_xpcimport.h"
#endif

#define DEVNAME                "Speedgoat IO601"
#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#define NUMBER_OF_ARGS          (8)
#define MODULEID_ARG            ssGetSFcnParam(S,0)
#define DEPTHPORT1_ARG          ssGetSFcnParam(S,1)
#define DEPTHPORT2_ARG          ssGetSFcnParam(S,2)
#define MSGTYPE_ARG             ssGetSFcnParam(S,3)
#define SHOWPORT1_ARG           ssGetSFcnParam(S,4)
#define SHOWPORT2_ARG           ssGetSFcnParam(S,5)
#define SAMP_TIME_ARG           ssGetSFcnParam(S,6)
#define SLOT_ARG                ssGetSFcnParam(S,7)

#define NO_I_WORKS              (3)
#define IOADDRESS2_I_IND        (0)
#define POSBUFFER1              (1)
#define POSBUFFER2              (2)

#define NO_R_WORKS              (0)
#define NO_P_WORKS              (0)


static char_T msg[256];

/* CAN message is the datatype as used by Matlab. */
typedef struct
{
    uint8_T Extended;
    uint8_T Length;
    uint8_T Remote;
    uint8_T Error;
    int32_T ID;
    double Timestamp;
    uint8_T Data[8];    
}canMsg;

typedef struct QUEUEENTRY
{
    uint32_T word[5];
}QUEUEENTRY;


#ifndef MATLAB_MEX_FILE


/**************************************************************************
 * This function returns the identifier given in parameter, coded in 
 * Motorola format.
 *
 * Motorola uses a Big Endian format, this means that:
 *
 * In a word (4 bytes):
 * 
 * Intel[0] = Motorola[3]
 * Intel[1] = Motorola[2]
 * Intel[2] = Motorola[1]
 * Intel[3] = Motorola[0] 
 *
 * Important, if the data is not complete (size != 32), we have to align
 * it.
 *************************************************************************/
static uint32_T ConvertIdentifier(uint32_T id, uint32_T nBits)
{
    uint32_T intel;
    
    intel = id; //(id >> (32 - nBits));
    intel = (uint32_T)(((intel & 0x000000FF) << 24) + 
                          ((intel & 0x0000FF00) << 8) +
                          ((intel & 0x00FF0000) >> 8) +
                          ((intel & 0xFF000000) >> 24));
    intel = intel >> (32 - nBits);
    return intel;
}
/**************************************************************************
 * Function name: ReadCANMessage
 *
 * Get one message from the DPRAM and return 1 if the message was found.
 * return 0 if the read failed.
 *
 * The CAN message is written with the message pointer (arg in).
 * a CAN entry contains up to 20 elements, which are:
 * |---------------------------------------|
 * |  n    |   standard    |    extended   |
 * |---------------------------------------|
 * |  0    |   status      |  status       |
 * |  1    |   count       |  count        | 
 * |  2    |   TimeStamp   |  TimeStamp    |
 * |  3    |   TimeStamp   |  TimeStamp    |
 * |  4    |   TimeStamp   |  TimeStamp    |
 * |  5    |   TimeStamp   |  TimeStamp    |
 * |  6    |   Type        |  Type         |
 * |  7    |   Information |  Information  |
 * |  8    |   Identifier  |  Identifier   |
 * |  9    |   Identifier  |  Identifier   |
 * | 10    |   Data        |  Identifier   |
 * | 11    |   Data        |  Identifier   |
 * | 12    |   Data        |  Data         |
 * | 13    |   Data        |  Data         |
 * | 14    |   Data        |  Data         |
 * | 15    |   Data        |  Data         |
 * | 16    |   Data        |  Data         |
 * | 17    |   Data        |  Data         |
 * | 18    |   Reserved    |  Data         |
 * | 19    |   Reserved    |  Data         |
 * |---------------------------------------/
 *************************************************************************/
static uint8_T ReadCANMessage(SimStruct *S, int32_T port, canMsg *message)
{
    uint8_T status, position;    
    QUEUEENTRY *pQueue;
    uint32_T word[5];
    uint8_T bytes[20];
    uint16_T standardID;
    uint32_T extendedID;
    uint32_T base;
    
    base = ssGetIWorkValue(S, IOADDRESS2_I_IND);
    
    /* Get the current position for the required port. */
    if (port == 1)
    {
        position = ssGetIWorkValue(S, POSBUFFER1);
        pQueue = (QUEUEENTRY *)(base + 0x820 + position * sizeof(QUEUEENTRY));
    }
    else
    {
        position = ssGetIWorkValue(S, POSBUFFER2);
        pQueue = (QUEUEENTRY *)(base + 0xC08 + position * sizeof(QUEUEENTRY));
    }
    
    /* Get the status */
    word[0] = pQueue->word[0];
    status = word[0] & 0xFF;
    if (status)
    {
        

        /* Because the status indicated a new message, we can read one complete queue entry. */
        word[1] = pQueue->word[1];
        word[2] = pQueue->word[2];
        word[3] = pQueue->word[3];
        word[4] = pQueue->word[4];
                
        /* now we split the words into bytes, to unpack the CAN frame. */
        memcpy(bytes, word, 20);                            
                
        /* the message type (standard or extended) changes the Frame format. */
        if (bytes[7] & 0x80) /* extended */
        {
            message->Extended = 1;
            message->Length = bytes[7] & 0xF;
            message->Remote = (bytes[7] & 0x40) >> 6;
            message->Error = 0;
            
            extendedID = bytes[8] | (bytes[9] << 8) | (bytes[10] << 16) | (bytes[11] << 24);
            message->ID = ConvertIdentifier(extendedID, 29);
            message->Timestamp = bytes[2] | (bytes[3] << 8) | (bytes[4] << 16) | (bytes[5] << 24);
            message->Data[0] = bytes[12];
            message->Data[1] = bytes[13];
            message->Data[2] = bytes[14];
            message->Data[3] = bytes[15];
            message->Data[4] = bytes[16];
            message->Data[5] = bytes[17];
            message->Data[6] = bytes[18];
            message->Data[7] = bytes[19];
        }
        else
        {
            message->Extended = 0;
            message->Length = bytes[7] & 0xF;
            message->Remote = (bytes[7] & 0x40) >> 6;
            message->Error = 0;            
            standardID = bytes[8] | (bytes[9] << 8);                  
            message->ID = ConvertIdentifier(standardID, 11);
            message->Timestamp = (real_T)(bytes[2] + (bytes[3] << 8) + (bytes[4] << 16) + (bytes[5] << 24));
            message->Data[0] = bytes[10];
            message->Data[1] = bytes[11];
            message->Data[2] = bytes[12];
            message->Data[3] = bytes[13];
            message->Data[4] = bytes[14];
            message->Data[5] = bytes[15];
            message->Data[6] = bytes[16];
            message->Data[7] = bytes[17];

        }
        
        position = (position == 49)? 0 : ++position;        
        if (port == 1)
        {
            ssSetIWorkValue(S, POSBUFFER1, position);
        }
        else
        {
            ssSetIWorkValue(S, POSBUFFER2, position);
        }
        
        /* Clear the buffer entry */        
        pQueue->word[0] = 0;
        
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
    uint32_T nPorts;
    DECL_AND_INIT_DIMSINFO(iDimsInfo);
    int iDims[2];
    int_T msgtype = (int_T)mxGetPr(MSGTYPE_ARG)[0];
    int_T depth;
    

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    
    nPorts = 0;
    if ((uint32_T)mxGetPr(SHOWPORT1_ARG)[0])
    {
        nPorts += 2;
    }
    if ((uint32_T)mxGetPr(SHOWPORT2_ARG)[0])
    {
        nPorts += 2;
    }
    if (!ssSetNumOutputPorts(S, nPorts)) 
        return;

    nPorts = 0;
    if ((uint32_T)mxGetPr(SHOWPORT1_ARG)[0])
    {
        
        depth = (int_T)mxGetPr(DEPTHPORT1_ARG)[0];

        
        switch (msgtype)
        {
        case 1:
            iDimsInfo.width   = 6 * depth;
            iDimsInfo.numDims = 2;
            iDimsInfo.dims    = iDims;
            iDims[0] = depth;
            iDims[1] = 6;

            if (!ssSetOutputPortDimensionInfo(S, nPorts, &iDimsInfo)) return;            
            
            break;

        case 2:

#ifdef MATLAB_MEX_FILE
            {
                int_T canMsgT, status;
                DTypeId id;
                canMsg tmp;
                
                id = ssRegisterDataType(S, "CAN_MESSAGE");
                if(id == INVALID_DTYPE_ID) return;

                status = ssSetDataTypeSize(S, id, sizeof(tmp));
                canMsgT = ssGetDataTypeId(S, "CAN_MESSAGE");     
                ssSetOutputPortDataType(S, nPorts, canMsgT); 
                ssSetOutputPortWidth(S, nPorts, depth);
            }
#endif
            break; 
            
        }
        
        // port with count
        ssSetOutputPortWidth(S, nPorts + 1, 1); 
        nPorts = 2;
    }   

    if ((uint32_T)mxGetPr(SHOWPORT2_ARG)[0])
    {        
        depth = (int_T)mxGetPr(DEPTHPORT2_ARG)[0];
        switch (msgtype)
        {
        case 1:
            iDimsInfo.width   = 6 * depth;
            iDimsInfo.numDims = 2;
            iDimsInfo.dims    = iDims;
            iDims[0] = depth;
            iDims[1] = 6;

            if (!ssSetOutputPortDimensionInfo(S, nPorts, &iDimsInfo)) return;            
            
            break;

        case 2:

#ifdef MATLAB_MEX_FILE
            {
                int_T canMsgT, status;
                DTypeId id;
                canMsg tmp;
                id = ssRegisterDataType(S, "CAN_MESSAGE");
                if(id == INVALID_DTYPE_ID) return;

                status = ssSetDataTypeSize(S, id, sizeof(tmp));

                canMsgT = ssGetDataTypeId( S, "CAN_MESSAGE" );


                ssSetOutputPortDataType( S, nPorts, canMsgT ); // D
                ssSetOutputPortWidth(S, nPorts, depth);
            }
#endif

            break; 

        }
        
        // port with count
        ssSetOutputPortWidth(S, nPorts + 1, 1);  
    }       
        
    ssSetNumInputPorts(S, 0);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i=0;i<NUMBER_OF_ARGS;i++) 
    {
        ssSetSFcnParamNotTunable(S, i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}


static void mdlInitializeSampleTimes(SimStruct *S)
{

    ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
    if (mxGetN(SAMP_TIME_ARG) == 1) 
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
    if (xpcGetPCIDeviceInfo((uint16_T)VENDORID, (uint16_T)DEVICEID, (uint16_T)SUBVENDORID, (uint16_T)SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S,msg);
        return;
    }

    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);    
    ssSetIWorkValue(S, IOADDRESS2_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, POSBUFFER1, 0);
    ssSetIWorkValue(S, POSBUFFER2, 0);
    
       
#endif
}


static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    uint8_T nbMessagesRead, offset;
    uint32_T port, m, i, size;
    real_T *count, *out2;
    canMsg *out;
    canMsg message;
    real_T data = 0.0;
    uint8_T *pData;
    
    message.Extended = 0;
    message.Length = 0;
    message.Remote = 0;
    message.Error = 0;
    message.ID = 0;
    message.Timestamp = 0.0;
    message.Data[0] = 0;
    message.Data[1] = 0;
    message.Data[2] = 0;
    message.Data[3] = 0;
    message.Data[4] = 0;
    message.Data[5] = 0;
    message.Data[6] = 0;
    message.Data[7] = 0; 
    
    /* We clean-up the outputs */
    port = 0;
    if ((uint32_T)mxGetPr(SHOWPORT1_ARG)[0])
    {
        if ((uint32_T)mxGetPr(MSGTYPE_ARG)[0] == 2)
        {
            size = (uint32_T)mxGetPr(DEPTHPORT1_ARG)[0];
            out = (canMsg*)ssGetOutputPortSignal(S, port);
            for (i = 0; i < size; i++)
            {
                out[i].Extended = 0;
                out[i].Length = 0;
                out[i].Remote = 0;
                out[i].Error = 0;
                out[i].ID = 0;
                out[i].Timestamp = 0.0;
                out[i].Data[0] = 0;
                out[i].Data[1] = 0;
                out[i].Data[2] = 0;
                out[i].Data[3] = 0;
                out[i].Data[4] = 0;
                out[i].Data[5] = 0;
                out[i].Data[6] = 0;
                out[i].Data[7] = 0;
            }
        }
        else
        {
            // message is the matrix
            
            out2 = (real_T*)ssGetOutputPortSignal(S, port);
            size = 6 * (uint32_T)mxGetPr(DEPTHPORT1_ARG)[0];
            for (i = 0; i < size; i++)
            {
                out2[i] = 0.0;
            }
            
        }
        
        port++;
    }
    
    if ((uint32_T)mxGetPr(SHOWPORT2_ARG)[0])
    {
        if ((uint32_T)mxGetPr(MSGTYPE_ARG)[0] == 2)
        {
            size = (uint32_T)mxGetPr(DEPTHPORT2_ARG)[0];
            out = (canMsg*)ssGetOutputPortSignal(S, port);
            for (i = 0; i < size; i++)
            {
                out[i].Extended = 0;
                out[i].Length = 0;
                out[i].Remote = 0;
                out[i].Error = 0;
                out[i].ID = 0;
                out[i].Timestamp = 0.0;
                out[i].Data[0] = 0;
                out[i].Data[1] = 0;
                out[i].Data[2] = 0;
                out[i].Data[3] = 0;
                out[i].Data[4] = 0;
                out[i].Data[5] = 0;
                out[i].Data[6] = 0;
                out[i].Data[7] = 0;
            }
        }
        else
        {
            // message is the matrix
            
            out2 = (real_T*)ssGetOutputPortSignal(S, port);
            size = 6 * (uint32_T)mxGetPr(DEPTHPORT2_ARG)[0];
            for (i = 0; i < size; i++)
            {
                out2[i] = 0.0;
            }
            
        }
    }    
    
    
    
    /* read the buffer up to the limit. If the status is wrong, we stop to read. */
    nbMessagesRead = 0;
    
    
    offset = 0;
    if ((uint32_T)mxGetPr(SHOWPORT1_ARG)[0])
    {
        port = 1;
        nbMessagesRead = 0;
        while (ReadCANMessage(S, port, &message))
        {


            if ((uint32_T)mxGetPr(MSGTYPE_ARG)[0] == 2)
            {
                out = (canMsg*)ssGetOutputPortSignal(S, 0);
                out[nbMessagesRead].Extended = message.Extended;
                out[nbMessagesRead].Length = message.Length;
                out[nbMessagesRead].Remote = message.Remote;
                out[nbMessagesRead].Error = message.Error;
                out[nbMessagesRead].ID = message.ID;
                out[nbMessagesRead].Timestamp = message.Timestamp;
                out[nbMessagesRead].Data[0] = message.Data[0];
                out[nbMessagesRead].Data[1] = message.Data[1];
                out[nbMessagesRead].Data[2] = message.Data[2];
                out[nbMessagesRead].Data[3] = message.Data[3];
                out[nbMessagesRead].Data[4] = message.Data[4];
                out[nbMessagesRead].Data[5] = message.Data[5];
                out[nbMessagesRead].Data[6] = message.Data[6];
                out[nbMessagesRead].Data[7] = message.Data[7];                
            }
            else
            {
                m = ssGetOutputPortWidth(S, 0)/6;
                out2 = (real_T*)ssGetOutputPortSignal(S, 0);

                out2[nbMessagesRead + m*0] = (real_T)port;  
                out2[nbMessagesRead + m*1] = (real_T)message.ID; 
                out2[nbMessagesRead + m*2] = (real_T)message.Extended;
                out2[nbMessagesRead + m*3] = (real_T)message.Length;
                out2[nbMessagesRead + m*4] = (real_T)message.Timestamp;                
                
                pData = (uint8_T*)&data;
                pData[0] = message.Data[0];
                pData[1] = message.Data[1];
                pData[2] = message.Data[2];
                pData[3] = message.Data[3];
                pData[4] = message.Data[4];
                pData[5] = message.Data[5];
                pData[6] = message.Data[6];
                pData[7] = message.Data[7];
                out2[nbMessagesRead + m*5] = data;

            }


            nbMessagesRead++;
            
            if (nbMessagesRead == (uint8_T)mxGetPr(DEPTHPORT1_ARG)[0])
                break;
        }



        count = (real_T*)ssGetOutputPortSignal(S, 1);
        count[0] = nbMessagesRead;

        offset = 2;
    }
    
    if ((uint32_T)mxGetPr(SHOWPORT2_ARG)[0])
    {
        port = 2;
        nbMessagesRead = 0;
        while (ReadCANMessage(S, port, &message))
        {


            if ((uint32_T)mxGetPr(MSGTYPE_ARG)[0] == 2)
            {
                out = (canMsg*)ssGetOutputPortSignal(S, offset);
                out[nbMessagesRead].Extended = message.Extended;
                out[nbMessagesRead].Length = message.Length;
                out[nbMessagesRead].Remote = message.Remote;
                out[nbMessagesRead].Error = message.Error;
                out[nbMessagesRead].ID = message.ID;
                out[nbMessagesRead].Timestamp = message.Timestamp;
                out[nbMessagesRead].Data[0] = message.Data[0];
                out[nbMessagesRead].Data[1] = message.Data[1];
                out[nbMessagesRead].Data[2] = message.Data[2];
                out[nbMessagesRead].Data[3] = message.Data[3];
                out[nbMessagesRead].Data[4] = message.Data[4];
                out[nbMessagesRead].Data[5] = message.Data[5];
                out[nbMessagesRead].Data[6] = message.Data[6];
                out[nbMessagesRead].Data[7] = message.Data[7];  
                
            }
            else
            {
                m = ssGetOutputPortWidth(S, 0)/6;
                out2 = (real_T*)ssGetOutputPortSignal(S, offset);


                out2[nbMessagesRead + m*0] = (real_T)port;  
                out2[nbMessagesRead + m*1] = (real_T)message.ID; 
                out2[nbMessagesRead + m*2] = (real_T)message.Extended;
                out2[nbMessagesRead + m*3] = (real_T)message.Length;
                out2[nbMessagesRead + m*4] = (real_T)message.Timestamp;                       
                
                pData = (uint8_T*)&data;
                pData[0] = message.Data[0];
                pData[1] = message.Data[1];
                pData[2] = message.Data[2];
                pData[3] = message.Data[3];
                pData[4] = message.Data[4];
                pData[5] = message.Data[5];
                pData[6] = message.Data[6];
                pData[7] = message.Data[7];
                out2[nbMessagesRead + m*5] = data;       

            }


            nbMessagesRead++;
            
            if (nbMessagesRead == (uint8_T)mxGetPr(DEPTHPORT2_ARG)[0])
                break;
        }



        count = (real_T*)ssGetOutputPortSignal(S, offset + 1);
        count[0] = nbMessagesRead;

    }
    
    //printf("ID: %d ", message.ID);
    //printf("ID (out): %d ", out[nbMessagesRead].ID);
    
    /*
    printf("Port: %d ", port);
    
    printf("Extended: %d ", message.Extended);
    printf("Length: %d ", message.Length);
    printf("Timestamp: %f\n", message.Timestamp);
    printf("Remote: %d ", message.Remote);
    printf("Error: %d \n", message.Error);
    printf("Data0: %d ", message.Data[0]);
    printf("Data1: %d ", message.Data[1]);
    printf("Data2: %d ", message.Data[2]);
    printf("Data3: %d \n", message.Data[3]);
    printf("Data4: %d ", message.Data[4]);
    printf("Data5: %d ", message.Data[5]);
    printf("Data6: %d ", message.Data[6]);
    printf("Data7: %d \n", message.Data[7]);
    */
    
  
    //xpcBusyWait(0.001);


#endif
}

static void mdlTerminate(SimStruct *S)
{
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
