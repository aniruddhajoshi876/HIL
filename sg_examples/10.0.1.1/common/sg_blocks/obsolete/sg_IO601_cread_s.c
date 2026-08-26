

#define         DEBUG                   0

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO601_cread_s

#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>

#include        "tmwtypes.h"
#include        "simstruc.h" 

#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#include 		"../common/libsg/sg_common.h"
#endif

#define         DEVNAME                 "Speedgoat IO601"
#define         VENDORID                0x10b5
#define         DEVICEID                0x9030
#define         SUBVENDORID             0x10b5
#define         SUBDEVICEID             0x2977

#define         NUMBER_OF_ARGS          (5)
#define         MODULE_ARG              ssGetSFcnParam(S,0)
#define         DEPTH_ARG               ssGetSFcnParam(S,1)
#define         STATUS_ARG              ssGetSFcnParam(S,2)
#define         SAMP_TIME_ARG           ssGetSFcnParam(S,3)
#define         SLOT_ARG                ssGetSFcnParam(S,4)

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
    int iDims[2];

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);


    iDimsInfo.width   = 6 * ((int_T)mxGetPr(DEPTH_ARG)[0]+(int_T)mxGetPr(DEPTH_ARG)[1]);
    iDimsInfo.numDims = 2;
    iDimsInfo.dims    = iDims;
    iDims[0] = (int_T)mxGetPr(DEPTH_ARG)[0]+(int_T)mxGetPr(DEPTH_ARG)[1];
    iDims[1] = 6;

    if ((int_T)mxGetPr(STATUS_ARG)[0]) {
        ssSetNumOutputPorts(S, 2);
        ssSetOutputPortWidth(S,1,2);
    } else {
        ssSetNumOutputPorts(S, 1);
    }
    if (!ssSetOutputPortDimensionInfo(S, 0, &iDimsInfo)) return;

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

    int_T           i, j, m, k;
    real_T          *y;
   
    uint8_T module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;
    uint8_T message[20];
    uint32_T message_32[5];
    
    volatile uint32_T *ioaddress0;
    volatile uint32_T *ioaddress2_32;
    uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
    uint32_T  base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);

    ioaddress0=(void *) base0;
    ioaddress2_32=(void *) base2;
    
    y= (real_T *) ssGetOutputPortSignal(S,0);

    m=ssGetOutputPortWidth(S,0)/6;
    //printf("m: %d\n", m);
    
    k= SGXPCCANIPCIXC16PMC[2 + module*4];
    
    for (i=0;i<(int_T)mxGetPr(DEPTH_ARG)[0];i++) {
        
        for (j=0; j<5; j++) {
            message_32[j]= ioaddress2_32[520+k*5+j];
            //printf("data: 0x%x ", message_32[i]);
        }
        //printf("\n");
        
        memcpy(message, message_32, 20);
        
        if (message[0]) {
            ioaddress2_32[520+k*5+0]= message_32[0] & 0xffffff00;
            k++;
            if (k==50) k=0;
            y[i+m*0]=1.0;   /* CAN channel */
            if ((message[7] & 0x80) == 0x00) { // standard
                y[i+m*1]=(real_T)GetId11(message[8] | (message[9]<<8));
                y[i+m*2]=1.0; // Type
                y[i+m*5]=(real_T) *((real_T *)&message[10]);   /* Data */
            } else {
                y[i+m*1]=(real_T)GetId29(message[8] | (message[9]<<8) | (message[10]<<16) | (message[11]<<24));
                y[i+m*2]=9.0; // Type
                y[i+m*5]=(real_T) *((real_T *)&message[12]);   /* Data */
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
    
    SGXPCCANIPCIXC16PMC[2 + module*4]= k;
    
    k= SGXPCCANIPCIXC16PMC[3 + module*4];
    //printf("%d\n", k);
    
    for (i=(int_T)mxGetPr(DEPTH_ARG)[0];i<(int_T)mxGetPr(DEPTH_ARG)[0]+(int_T)mxGetPr(DEPTH_ARG)[1];i++) {
        
        for (j=0; j<5; j++) {
            message_32[j]= ioaddress2_32[770+k*5+j];
            //printf("data: 0x%x ", message_32[j]);
        }
        //printf("\n");
        
        memcpy(message, message_32, 20);
        //for (j=0; j<20; j++) {
        //    printf("0x%x ", message[j]);
        //}
        //printf("\n");
        
        if (message[0]) {
            ioaddress2_32[770+k*5+0]= message_32[0] & 0xffffff00;
            k++;
            if (k==50) k=0;
            y[i+m*0]=2.0;   /* CAN channel */
            if ((message[7] & 0x80) == 0x00) { // standard
                y[i+m*1]=(real_T)GetId11(message[8] | (message[9]<<8));
                y[i+m*2]=1.0; // Type
                y[i+m*5]=(real_T) *((real_T *)&message[10]);   /* Data */
            } else {
                y[i+m*1]=(real_T)GetId29(message[8] | (message[9]<<8) | (message[10]<<16) | (message[11]<<24));
                y[i+m*2]=9.0; // Type
                y[i+m*5]=(real_T) *((real_T *)&message[12]);   /* Data */
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
    
    SGXPCCANIPCIXC16PMC[3 + module*4]= k;
    
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
