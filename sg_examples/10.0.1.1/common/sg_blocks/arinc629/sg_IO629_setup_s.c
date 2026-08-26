/*
 * This S-function is used to establish and handle the connection to the FM629 device.
 * It declares and initializes the HMXF_SERVER and HMXF_DEVICE handles.
 * It also declares (without initialization)the HXMF_MODULE array in order to allow
 * to be shared among other blocks.
 */

#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO629_setup_s

#include "sg_IO629.h" 

#define DEBUG

#define MODULE_ID_ARG       			ssGetSFcnParam(S, 0)    //parModuleId
#define SLOT_ARG       					ssGetSFcnParam(S, 1) 	//parPciSlot


#define NUMBER_OF_ARGS 						   		   (  2)

/* Integer Work Vectors */
#define NO_I_WORKS              (0)
/* Real Work Vectors */
#define NO_R_WORKS              (0)
/* Pointer Work Vectors */
#define BAR0_IDX				(0)
#define NO_P_WORKS              (1)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Global server handle (declared as extern in other blocks)
HMXF_SERVER  		sg_io629_server		= 0			;
//Global device handle (declared as extern in submodule)
HMXF_DEVICE  		sg_io629_device		= 0			;
////Global modules handle (declared here but used in other blocks)
HMXF_MODULE  		sg_io629_module[4] 	= {0,0,0,0}	;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void load(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	//rc is used to check the return status of function calls
	uint32 rc;
	//holder for the number of devices
	uint64 deviceCount=0;
	
	
	if(!xpcIsModelInit()){
		//connect to the device and fill server 
		rc = mxfServerConnect("0.0.0.0", "", "", FALSE, &sg_io629_server);
		if(rc != MAXT_SUCCESS){printf("Error code\n (Setup: mxfServerConnect) =0x%lX\n", rc);return;}
		else{			
			printf("mxfSystemInit ... ");	
		}
		
		//Resets the hardware device, initializes the library and allocates the base system resources
		rc=mxfSystemInit(sg_io629_server);
		if(rc != MAXT_SUCCESS){
			printf("Error code (Setup:\n mxfSystemInit) =0x%lX\n", rc);
			return;
		}else{
			//additional feature used to terminate properly the API
			//reset the array
			memset(ch_is_enabled,0,sizeof(ch_is_enabled));			
		}		

		rc = mxfSystemDeviceAllGet(sg_io629_server, MXF_DEVICE_FLEXMULTI_629, 1, &deviceCount, &sg_io629_device);
		if(rc != MAXT_SUCCESS){printf("Error code (Setup: mxfSystemDeviceAllGet) =0x%lX\n", rc);return;}
		
		printf("\n%i IO629 I/O Module(s) found\n", (int)deviceCount);
		
		rc = mxfSystemTimeBaseSet(sg_io629_server,MXF_TIMEBASE_DEVICE_USEC);
		if(rc != MAXT_SUCCESS){printf("Error code (Setup: mxfSystemTimeBaseSet) =0x%lX\n", rc);return;}
		
	}
#endif
}
//not used currently
static void unload(void)
{
	#ifndef MATLAB_MEX_FILE
	uint32 rc=0;

	printf("mxfSystemResourcesRelease... ");
	
	//release server
	rc=mxfSystemResourcesRelease(sg_io629_server, 0);
	if(rc != MAXT_SUCCESS){
		printf("Error code (Setup: mxfSystemResourcesRelease) =0x%lX\n", rc);return;
	}else
		printf("done!\n");
	//disconnect from device
	rc=mxfServerDisconnect(sg_io629_server);
	
	if(rc)
		printf("mxfServerDisconnect rc=%08X \n", rc);
	
	printf("**************************************\n");
	#endif
}
			
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

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
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
	
	//if(xpcIsModelInit()){
		load(S);	
	//}

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