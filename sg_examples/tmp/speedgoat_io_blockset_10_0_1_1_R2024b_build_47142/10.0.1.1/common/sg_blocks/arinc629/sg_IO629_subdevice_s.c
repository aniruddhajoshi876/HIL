/*
 * This S-function gets the HMXF_DEVICE device and HMXF_MODULE  module handlers
 * from the setup S-function and initializes their parameters (Ti, TTL/SIM, Rx Only,
 * XPP CID EN,XPP DUAL EN). Other "subblocks (RT, BM) will refer to the subdevice
 * by its Subdevice ID).
 */

#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO629_subdevice_s

#include "sg_IO629.h" 

#define SUBDEVICE_ARG       			ssGetSFcnParam(S, 0)    //parModuleId
#define TI_ARG							ssGetSFcnParam(S, 1)	//parTg
#define SG_ARG							ssGetSFcnParam(S, 2)
#define INTERFACE_ARG                   ssGetSFcnParam(S, 3)    //parInterface
#define RXONLY_ARG						ssGetSFcnParam(S, 4)    //parRxOnly
#define XPPDUALEN_ARG                   ssGetSFcnParam(S, 5)    //parXppDualEn
#define NUMBER_OF_ARGS 						   		  (   6)

/* Integer Work Vectors */
#define NO_I_WORKS              (0)


/* Real Work Vectors */
#define NO_R_WORKS              (0)

/* Pointer Work Vectors */
#define BAR0_IDX				(0)
#define NO_P_WORKS              (1)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern HMXF_DEVICE  sg_io629_device;
extern HMXF_MODULE  sg_io629_module[4];

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void print_args(SimStruct *S){
	
	printf("SUBDEVICE_ID_ARG = %i\n"	,(uint16_T)mxGetPr(SUBDEVICE_ARG)[0]);   	
	printf("TI_ARG = %i\n"		    	,(uint32_T)mxGetPr(TI_ARG		)[0]);
	printf("INTERFACE_ARG = %i\n"   	,(uint32_T)mxGetPr(INTERFACE_ARG)[0]);
	printf("RXONLY_ARG	= %i\n"     	,(uint32_T)mxGetPr(RXONLY_ARG	)[0]);	
	printf("XPPDUALEN_ARG = %i\n"		,(uint32_T)mxGetPr(XPPDUALEN_ARG)[0]);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//error messages holder 
static char_T msg[256];

//auxiliary functions prototypes
static void wait_s(real_T t);
static void wait_us(real_T t);
static void mdlInitializeSizes(SimStruct *S)
{
	uint32_T i;
	
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
		sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);	
	
	if(!ssSetNumInputPorts(S, 0)) 
	{
		printf("error while setting input ports\n");
		return;
	}		
    if(!ssSetNumOutputPorts(S, 0))	
	{
		printf("error while setting output ports\n");
		return;
	}    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
	
    ssSetNumModes(S, 0);
	
    ssSetNumNonsampledZCs(S, 0); 
	
	for( i = 0 ; i < NUMBER_OF_ARGS ; i++ )
	{
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }
}


static void mdlInitializeSampleTimes(SimStruct *S)
{	
	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}


#define MDL_START  /* Change to #undef to remove function */
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	if(!xpcIsModelInit() /*&& api_is_init*/){
		uint32 rc 				= 0										;
		uint16_T i 				= 0										;
		uint64 moduleIndex  	= (uint64)mxGetPr(SUBDEVICE_ARG)[0]-1	;	// First module
		uint64 moduleIndexCorr  = moduleIndex							;
		
		
		
		//For FM629 with 4 a629 modules 3rd and 4th modules are addressed with indexes 6 and 7
		if(moduleIndex>1){
			moduleIndexCorr = moduleIndex+4;
		}
		
		
		rc = mxfDeviceModuleGet(sg_io629_device, moduleIndexCorr, &sg_io629_module[moduleIndex]);
		if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfDeviceModuleGet) =0x%lX\n", rc);return;}
		
		
		
		if(rc == MAXT_SUCCESS)
			rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_TI,(uint32_T)mxGetPr(TI_ARG)[0]);
		else 
			printf("Error code=0x%lX\n", rc);
		
		
		

		//interface (SIM vs TTL)
		if((uint32_T)mxGetPr(INTERFACE_ARG)[0] == 2){
			rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_INTERFACE, VMXF_A629_MODULE_INTERFACE_TTL);
			if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(VMXF_A629_MODULE_INTERFACE_TTL)) = 0x%lX\n", rc);return;}
		}else{
			rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_INTERFACE, VMXF_A629_MODULE_INTERFACE_SIM);
			if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(VMXF_A629_MODULE_INTERFACE_SIM)) = 0x%lX\n", rc);return;}
		}

		
			
		//RX onlx		
		//printf("Rx only = %i\n",(uint32_T)mxGetPr(RXONLY_ARG)[0]);
		
		if((uint32_T)mxGetPr(RXONLY_ARG)[0]){			
			rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_RX_ONLY, VMXF_ENABLE);
			if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(KMXF_A629_MODULE_RX_ONLY)) = 0x%lX\n", rc);return;}
			printf("Subdevice %i is in RX ONLY MODE\n",(uint16_T)mxGetPr(SUBDEVICE_ARG)[0]);
		}else{
			rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_RX_ONLY, VMXF_DISABLE);
			if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(KMXF_A629_MODULE_RX_ONLY)) = 0x%lX\n", rc);return;}
		}
		
		
		rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_XPP_CID_ENABLE, VMXF_DISABLE);
		if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(KMXF_A629_MODULE_XPP_CID_ENABLE)) = 0x%lX\n", rc);return;}
					
		
		
		//XPP DUAL 
		//if((uint32_T)mxGetPr(XPPDUALEN_ARG)[0] == 0)
		rc = mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_XPP_DUAL_ENABLE, VMXF_DISABLE);
		if(rc != MAXT_SUCCESS){printf("Error code (Subdevice: mxfAttributeUint64Set(KMXF_A629_MODULE_XPP_DUAL_ENABLE)) = 0x%lX\n", rc);return;}
	    
	    switch((int_T)mxGetPr(SG_ARG)[0]){
			case 1:			mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_SG , VMXF_A629_MODULE_SG_16);	break;
			case 2:			mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_SG , VMXF_A629_MODULE_SG_32);	break;
			case 64:		mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_SG , VMXF_A629_MODULE_SG_127);	break;
			case 127:		mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_SG , VMXF_A629_MODULE_SG_127);	break;			
			default: 		mxfAttributeUint64Set(sg_io629_module[moduleIndex], KMXF_A629_MODULE_SG , VMXF_A629_MODULE_SG_16);			
		}
		
	}		
	
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
	
	
#endif	
}

static void mdlTerminate(SimStruct *S)
{		
#ifndef MATLAB_MEX_FILE		
	if(!xpcIsModelInit()){

	}
#endif
}

static void wait_s(real_T t){
#ifndef MATLAB_MEX_FILE

    xpcTime t_start, t_now, t_elapsed;
    xpcGetElapsedTime(&t_start);

    do{
		xpcGetElapsedTime(&t_now);
        xpcSubtractTime(&t_elapsed, &t_now, &t_start);
    }while( (((real_T)t_elapsed.U64.NanoSecondsLo * 1e-9) + ((real_T)t_elapsed.U64.NanoSecondsHi * 4.294967296)) < t );
#endif
}
	
static void wait_us(real_T t){
	xpcBusyWait(t/(1000000.0));
	

}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif