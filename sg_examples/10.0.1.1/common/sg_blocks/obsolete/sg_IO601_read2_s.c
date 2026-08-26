

#define         DEBUG                   0

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO601_read2_s

#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>

#include        "tmwtypes.h"
#include        "simstruc.h" 


#ifdef          MATLAB_MEX_FILE
	#include        "mex.h"
	//#include        "can_datatype.h"
#else
	#include        <windows.h>
	#include        "xpcimports.h"
	#include 		"../common/libsg/sg_common.h"
#endif

#define         DEVNAME                 "Speedgoat IO601"
#define         VENDORID                0x10b5
#define         DEVICEID                0x9030
#define         SUBVENDORID             0x10b5
#define         SUBDEVICEID             0x2977

#define         NUMBER_OF_ARGS          (7)
#define         MODULE_ARG              ssGetSFcnParam(S,0)
#define         PORT_ARG                ssGetSFcnParam(S,1)
#define         DEPTH_ARG               ssGetSFcnParam(S,2)
#define         MSGTYPE_ARG             ssGetSFcnParam(S,3)
#define         STATUS_ARG              ssGetSFcnParam(S,4)
#define         SAMP_TIME_ARG           ssGetSFcnParam(S,5)
#define         SLOT_ARG                ssGetSFcnParam(S,6)

#define         NO_I_WORKS              (2)
#define         IOADDRESS0_I_IND        (0)
#define         IOADDRESS2_I_IND        (1)

#define         NO_R_WORKS              (0)

#define         NO_P_WORKS              (0)

#ifndef MATLAB_MEX_FILE

#ifndef  LOW8
#define  LOW8(wert)  *( (uint8_T *) &wert)
#endif

#ifndef  HIGH8
#define  HIGH8(wert)  *(((uint8_T *) &wert) + 1)
#endif

#ifndef  LOW16
#define  LOW16(wert)  *( (uint16_T *) &wert)
#endif

#ifndef  HIGH16
#define  HIGH16(wert)  *(((uint16_T *) &wert) + 1)
#endif

#ifndef SWAP16
#define SWAP16(wert)       { uint8_T temp; temp = HIGH8(wert); HIGH8(wert) = (uint8_T) wert; LOW8(wert) = temp; }
#endif

#ifndef SWAP32
#define SWAP32(wert)       { uint16_T temp; temp = HIGH16(wert); HIGH16(wert) = (uint16_T) wert; LOW16(wert) = temp; }
#endif

#endif

static char_T msg[256];

typedef struct{
    uint8_T Extended;
    uint8_T Length;
    uint8_T Remote;
    uint8_T Error;
    uint32_T ID;
    double Timestamp;
    uint8_T Data[8];    
}canMsg;

// struct canMsg  
// {
//     uint8_T Extended;
//     uint8_T Length;
// 	uint8_T Remote;
//     uint8_T Error;
// 	uint32_T ID;
//     double Timestamp;
//     uint8_T Data[8];
// 
// };


#ifndef MATLAB_MEX_FILE

extern uint8_T SGXPCCANIPCIXC16PMC[];

static uint32_T GetId11 (uint32_T id)
{
  SWAP16 (HIGH16 (id));
  SWAP16 (LOW16 (id));
  SWAP32 (id);

  id = id >> 21;
  return id;
}

static uint32_T GetId29 (uint32_T id)
{
  SWAP16 (HIGH16 (id));
  SWAP16 (LOW16 (id));
  SWAP32 (id);

  id = id >> 3;
  return id;
}
    
static unsigned char get_double_byte(double value, int n)
{
    unsigned char *p;

    p = (unsigned char *) &value;
    return p[n];
}
#endif


static void mdlInitializeSizes(SimStruct *S)
{
    int_T i;
    DECL_AND_INIT_DIMSINFO(iDimsInfo);

    int_T msgtype = (int_T)mxGetPr(MSGTYPE_ARG)[0];
    int_T depth = (int_T)mxGetPr(DEPTH_ARG)[0];

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

#ifdef MATLAB_MEX_FILE
    int iDims[2];
    int_T canMsgT, status;
    canMsg tmp;
    DTypeId id;

    switch( msgtype )
    {
    case 1:
        if ((int_T)mxGetPr(STATUS_ARG)[0])
        {
            if( !ssSetNumOutputPorts(S, 2) ) return;
            ssSetOutputPortWidth(S, 1, 2); // lost msgs and bus state
        } else
        {
            if( !ssSetNumOutputPorts(S, 1) ) return;
        }

        iDimsInfo.width   = 6 * depth;
        iDimsInfo.numDims = 2;
        iDimsInfo.dims    = iDims;
        iDims[0] = depth;
        iDims[1] = 6;

        if (!ssSetOutputPortDimensionInfo(S, 0, &iDimsInfo)) return;
        break;
    
    case 2:
        // Initialize CAN Datatype
        //mdlInitialize_CAN_datatype(S);
        id = ssRegisterDataType(S, "CAN_MESSAGE");
        if(id == INVALID_DTYPE_ID) return;
        
        status = ssSetDataTypeSize(S, id, sizeof(tmp));
        
        canMsgT = ssGetDataTypeId( S, "CAN_MESSAGE" );

        if ((int_T)mxGetPr(STATUS_ARG)[0])
        {
            if( !ssSetNumOutputPorts(S, 3) ) return; // D, N and S
            ssSetOutputPortDataType( S, 0, canMsgT ); // D
            ssSetOutputPortWidth(S, 0, depth );
            ssSetOutputPortWidth(S, 1, 1 );
            ssSetOutputPortWidth(S, 2, 2); // lost msgs and bus state
        } else
        {
            if( !ssSetNumOutputPorts(S, 2) ) return; // D and N
            ssSetOutputPortDataType( S, 0, canMsgT ); // D
            ssSetOutputPortWidth(S, 0, depth );
            ssSetOutputPortWidth(S, 1, 1 );
        }
        break;
        
    case 3:
        // Initialize CAN Datatype
        //mdlInitialize_CAN_datatype(S);
        id = ssRegisterDataType(S, "CAN_MESSAGE");
        if(id == INVALID_DTYPE_ID) return;
        
        status = ssSetDataTypeSize(S, id, sizeof(tmp));
        
        canMsgT = ssGetDataTypeId( S, "CAN_MESSAGE" );
        if ((int_T)mxGetPr(STATUS_ARG)[0])
        {
            if( !ssSetNumOutputPorts(S, 3) ) return; // f(), D and S
            ssSetOutputPortDataType( S, 1, canMsgT ); // D
            ssSetOutputPortWidth(S, 0, 1 );
            ssSetOutputPortWidth(S, 1, 1 );
            ssSetOutputPortWidth(S, 2, 2); // lost msgs and bus state
        } else
        {
            if( !ssSetNumOutputPorts(S, 2) ) return; // f() and D
            ssSetOutputPortDataType( S, 1, canMsgT ); // D
            ssSetOutputPortWidth(S, 0, 1 );
            ssSetOutputPortWidth(S, 1, 1 );
        }
        break;
    }
#endif


    ssSetNumInputPorts(S, 0);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i=0;i<NUMBER_OF_ARGS;i++) {
        ssSetSFcnParamNotTunable(S,i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}


static void mdlInitializeSampleTimes(SimStruct *S)
{

    ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
    if (mxGetN((SAMP_TIME_ARG))==1) {
        ssSetOffsetTime(S, 0, 0.0);
    } else {
        ssSetOffsetTime(S, 0, mxGetPr(SAMP_TIME_ARG)[1]);
    }

}

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;	
	int_T bus, slot;
    uint32_T moduleID;
    volatile uint32_T *ioaddress0;
    volatile uint8_T *ioaddress2;
	
   	//PCI slot
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
	
	//Get PCI device
	moduleID = ((int_T)mxGetPr(MODULE_ARG)[0]);
    if(sg_findPciDevice(&pciinfo,DEVNAME, VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, moduleID, bus,slot) != 0)
    {
        ssSetErrorStatus(S, pSgErrorStr);
        return;
    }
	
	// Memory map bar to user space virtual address
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void*)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE );
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void*)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE );
    ioaddress0 = (volatile uint32_T *)pciinfo.VirtAddress[0];
    ioaddress2 = (volatile uint8_T *)pciinfo.VirtAddress[2];
	
    
    ssSetIWorkValue(S, IOADDRESS0_I_IND, (uint32_T)ioaddress0);
    ssSetIWorkValue(S, IOADDRESS2_I_IND, (uint32_T)ioaddress2);
    
       
#endif
}


static void mdlOutputs(SimStruct *S, int_T tid)
{

#ifndef MATLAB_MEX_FILE

    int_T           i, j, m, k, messageRead;
    canMsg          *y1;
    real_T          *y, *y2;
    uint8_T module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;
    uint8_T port= (uint8_T)mxGetPr(PORT_ARG)[0]-1;
    uint8_T message[20];
    uint32_T message_32[5];
    
    //struct canMsg *ptr;
    volatile uint32_T *ioaddress0;
    volatile uint32_T *ioaddress2_32;
    uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
    uint32_T  base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);

    ioaddress0=(volatile uint32_T *) base0;
    ioaddress2_32=(volatile uint32_T *) base2;
    
    

    m=ssGetOutputPortWidth(S,0)/6;
    //printf("m: %d\n", m);
    
    k= SGXPCCANIPCIXC16PMC[2+port + module*4];
        
    
    if ( (int_T)mxGetPr(MSGTYPE_ARG)[0] == 2){ //CAN_MESSAGE
        y1 = (canMsg *) ssGetOutputPortSignal(S,0);
        y2= (double *) ssGetOutputPortSignal(S,1);
        messageRead = 0;
        for (i=0;i<(int_T)mxGetPr(DEPTH_ARG)[0];i++) {
            //ptr = (struct canMsg *)(&y[i]);
            
            if (port==0) {
                for (j=0; j<5; j++) {
                    message_32[j]= ioaddress2_32[520+k*5+j];
                    //printf("data: 0x%x ", message_32[i]);
                }
                //printf("\n");
            } else {
                for (j=0; j<5; j++) {
                    message_32[j]= ioaddress2_32[770+k*5+j];
                    //printf("data: 0x%x ", message_32[i]);
                }
                //printf("\n");
            }
            memcpy(message, message_32, 20);

            if (message[0]) {
                if (port==0) {
                    ioaddress2_32[520+k*5+0]= message_32[0] & 0xffffff00;
                } else {
                    ioaddress2_32[770+k*5+0]= message_32[0] & 0xffffff00;
                }
                k++;
                if (k==50) k=0;
                
                if ((message[7] & 0x80) == 0x00) { // standard
                    
                    y1[i].ID = (uint32_T)((real_T)GetId11(message[8] | (message[9]<<8)));
                    y1[i].Extended = (uint8_T)0.0; //type
                    y1[i].Data[0] =  message[10];
                    y1[i].Data[1] =  message[11];
                    y1[i].Data[2] =  message[12];
                    y1[i].Data[3] =  message[13];
                    y1[i].Data[4] =  message[14];
                    y1[i].Data[5] =  message[15];
                    y1[i].Data[6] =  message[16];
                    y1[i].Data[7] =  message[17];

                } else {
                    
                    y1[i].ID = (uint32_T)((real_T)GetId29(message[8] | (message[9]<<8) | (message[10]<<16) | (message[11]<<24)));
                    y1[i].Extended = (uint8_T)1.0; //type
                    y1[i].Data[0] =  message[12];
                    y1[i].Data[1] =  message[13];
                    y1[i].Data[2] =  message[14];
                    y1[i].Data[3] =  message[15];
                    y1[i].Data[4] =  message[16];
                    y1[i].Data[5] =  message[17];
                    y1[i].Data[6] =  message[18];
                    y1[i].Data[7] =  message[19];
                    
                    /*
                    printf("ID: %d\n", y1[i].ID);
                    printf("Data:\n");
                    printf("%d    %d    %d    %d\n", y1[i].Data[0], y1[i].Data[1], y1[i].Data[2], y1[i].Data[3]);
                    printf("%d    %d    %d    %d\n", y1[i].Data[4], y1[i].Data[5], y1[i].Data[6], y1[i].Data[7]);
                    */
                    
                }
                y1[i].Length = message[7] & 0x0f;   /* Data length */
                y1[i].Timestamp = (real_T) *((uint32_T *)&message[2]);  /* Time */
                /*printf("Timestamp: %d\n", y1[i].Timestamp);
                printf("Length: %d\n", y1[i].Length);*/
                messageRead++;
                
            } else {
                y1[i].ID = (uint32_T)-1.0;/* Identifier */

                y1[i].Error = (uint8_T)0.0;   /* FRC */
                y1[i].Length = (uint8_T)0.0;   /* Data length */
                y1[i].Timestamp = -1.0;  /* Time */
                y1[i].Data[0] = 0;/* Data */
                y1[i].Data[1] = 0;
                y1[i].Data[2] = 0;
                y1[i].Data[3] = 0;
                y1[i].Data[4] = 0;
                y1[i].Data[5] = 0;
                y1[i].Data[6] = 0;
                y1[i].Data[7] = 0;   
            }
            
            //printf("Data[0]: %d\n", ptr->Data[0]);
        }
        
        y2[0] = messageRead;
        
      
    }
    else{ // Matrix of double
        
        y= (real_T *) ssGetOutputPortSignal(S,0);
        
        for (i=0;i<(int_T)mxGetPr(DEPTH_ARG)[0];i++) {

            if (port==0) {
                for (j=0; j<5; j++) {
                    message_32[j]= ioaddress2_32[520+k*5+j];
                    //printf("data: 0x%x ", message_32[i]);
                }
                //printf("\n");
            } else {
                for (j=0; j<5; j++) {
                    message_32[j]= ioaddress2_32[770+k*5+j];
                    //printf("data: 0x%x ", message_32[i]);
                }
                //printf("\n");
            }
            memcpy(message, message_32, 20);

            if (message[0]) {
                if (port==0) {
                    ioaddress2_32[520+k*5+0]= message_32[0] & 0xffffff00;
                } else {
                    ioaddress2_32[770+k*5+0]= message_32[0] & 0xffffff00;
                }
                k++;
                if (k==50) k=0;
                if (port==0) {
                    y[i+m*0]=1.0;   /* CAN channel */
                } else {
                    y[i+m*0]=2.0;   /* CAN channel */
                }
                if ((message[7] & 0x80) == 0x00) { // standard
                    y[i+m*1]=(real_T)GetId11(message[8] | (message[9]<<8));
                    y[i+m*2]=1.0; // Type
                    y[i+m*5]=(real_T) *((real_T *)&message[10]);   /* Data */
                } else {
                    y[i+m*1]=(real_T)GetId29(message[8] | (message[9]<<8) | (message[10]<<16) | (message[11]<<24));
                    y[i+m*2]=9.0; // Type
                    y[i+m*5]=(real_T) *((real_T *)&message[12]);   /* Data */
                    //printf("%d    %d\n", message[12], message[13]);
                }
                y[i+m*3]=message[7] & 0x0f;   /* Data length */
                y[i+m*4]=(real_T) *((uint32_T *)&message[2]);  /* Time */ 
            } else {
                y[i+m*0]=0.0;   /* CAN channel */
                y[i+m*1]=-1.0;  /* Identifier */
                y[i+m*2]=0.0;   /* FRC */
                y[i+m*3]=0.0;   /* Data length */
                y[i+m*4]=-1.0;  /* Time */
                y[i+m*5]=0.0;   /* Data */
            }

        }
    }
    
    SGXPCCANIPCIXC16PMC[2+port + module*4]= k;
    
    if ((int_T)mxGetPr(STATUS_ARG)[0]) {

        y= (real_T *) ssGetOutputPortSignal(S,1);

        if (!ssGetT(S)>0.0) {
            y[0]=0.0;
            y[1]=0.0;
        } else {
            y[0]= 0.0;
            y[1]= 0.0;
        }
    }


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
