

#define         DEBUG                   0

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO601_status_s

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

#define         NUMBER_OF_ARGS          (3)
#define         MODULE_ARG              ssGetSFcnParam(S,0)
#define         SAMP_TIME_ARG           ssGetSFcnParam(S,1)
#define         SLOT_ARG                ssGetSFcnParam(S,2)

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

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
   
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 6);
    ssSetOutputPortDataType(S, 0, SS_UINT16);
    
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

    int_T           i;
    uint16_T        *y;
    uint16_T        status[6];
    uint32_T        status_32[3];
    
    uint8_T module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;

    volatile uint32_T *ioaddress0;
    volatile uint32_T *ioaddress2_32;
    volatile uint8_T *ioaddress2;
    uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
    uint32_T  base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);

    ioaddress0=(void *) base0;
    ioaddress2_32=(void *) base2;
    ioaddress2=(void *) base2;
   
    ioaddress2[8192]= 0x00;
    if (ioaddress2[8192]!= 0x00) {
        ioaddress2[8192]= 0x01;
        //printf("return\n");
        return;
    }
    
    for (i=0; i<3; i++) {
        status_32[i]= ioaddress2_32[1020+i];
    }
    
    ioaddress2[8192]= 0x01;    
    memcpy(status, status_32, 12);
    
    y= (uint16_T *) ssGetOutputPortSignal(S,0);
    for (i=0; i<6; i++) {
        //printf("0x%x ", status[i]);
        y[i]= status[i];
    }
    //printf("\n");
   
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
