#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO781_receive_s

#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>		
#include <stdint.h>
	
#include "sg_printf.h"
#include "sg_callback.h"
	 
#ifdef 	 MATLAB_MEX_FILE
	#include "mex.h"
#else
    #include "a664_api.h"
    #include "sg_IO781.h"

//extern A664EndSystemHandle 		esHandle[10] ;
//extern uint16_t					module_id;      
#endif

#define MODULE_ID_ARG       			ssGetSFcnParam(S, 0)     	//parModuleId
#define PORT_ID_ARG						ssGetSFcnParam(S, 1)
#define RX_MSG_LEN_ARG					ssGetSFcnParam(S, 2)
#define SAMP_TIME_ARG					ssGetSFcnParam(S, 3)		//block sample time	
#define NUMBER_OF_ARGS 		   							 (4)


#define MESSAGE_SIZE			(1)

//#define DEBUG_MODE



/* Integer Work Vectors */
#define NO_I_WORKS              (0)

/* Real Work Vectors */
#define NO_R_WORKS              (0)

/* Pointer Work Vectors */
#define NO_P_WORKS              (0)

//error messages holder (i guess)
static char msg[256];


static void mdlInitializeSizes(SimStruct *S)
{
	uint32_t i, rx_msg_length;
	
	
	rx_msg_length = (uint32_t)mxGetPr(RX_MSG_LEN_ARG)[0];
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
		SG_PRINTF(INFO, "error while setting input ports\n");
		return;
	}		
    if(!ssSetNumOutputPorts(S, 2))	
	{
		SG_PRINTF(INFO, "error while setting output ports\n");
		return;
	}    
	
	ssSetOutputPortWidth(S, 0, rx_msg_length);
	ssSetOutputPortDataType(S, 0, SS_UINT8);

	ssSetOutputPortWidth(S, 1, 1);
	ssSetOutputPortDataType(S, 1, SS_UINT16);
	
	
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

    //ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMP_TIME_ARG)[0]==-1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct *S) 
{
#ifndef MATLAB_MEX_FILE
    
#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    // Open the Rx ports and get the handles
    uint8_t module_id_corr = (uint8_t)mxGetPr(MODULE_ID_ARG)[0]-1;
    int32_t retval = 0;
    uint8_t *readData;
    //extern A664EndSystemHandle esHandle[10];
    A664RxComUdpHandle *rxComUdpHandles;
    uint32_t port_id = (uint32_t)mxGetPr(PORT_ID_ARG)[0];
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO781_rx_t *pIO781_rx;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 receive: Module not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO781_RECEIVE, (uintptr_t)S);
    
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 receive: Block not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    rxComUdpHandles =  (A664RxComUdpHandle*)malloc(sizeof(A664RxComUdpHandle));
	SG_PRINTF(DEBUG,"Receive, EsHandle %p\n",esHandle[module_id_corr].handle);
    
    retval = a664RxComUdpOpen( esHandle[module_id_corr], port_id, rxComUdpHandles);
    
    if(retval != A664_API_OK)
    {		
        sprintf(msg,"Error: a664RxComUdpOpen (error code = %d)\n",retval);
        ssSetErrorStatus(S,msg);
        return;
    }
    
    readData = (uint8_t*)malloc((int)mxGetPr(RX_MSG_LEN_ARG)[0] * sizeof(uint8_t));
    
    pIO781_rx = calloc(1, sizeof(sg_IO781_rx_t));
    pIO781_rx->readData = readData;
    pIO781_rx->rxComUdpHandles = rxComUdpHandles;
    block_info->custom_data = pIO781_rx;
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	int 					i				;
	uint8_t 				*pY				;	
	uint8_t 				*readData		;
	uint16_t 				*N_port			;
	A664Timestamp 			timeStamp		;
	A664RxComUdpHandle  	*rxComUdpHandles;
	uint16_t 				byteCount, 
							rx_msg_length	;
	A664NetworkInterface 	network			;
	int32_t             	retval = 0		;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO781_rx_t *pIO781_rx;

    //Retrieve from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 receive: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO781_RECEIVE, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 receive: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO781_rx = (sg_IO781_rx_t*)block_info->custom_data;
	
	rx_msg_length = (uint16_t)mxGetPr(RX_MSG_LEN_ARG)[0];
	
	rxComUdpHandles = pIO781_rx->rxComUdpHandles;
	readData = pIO781_rx->readData;
	
	retval = a664RxComUdpRead(*rxComUdpHandles, rx_msg_length, readData, &byteCount, &network, &timeStamp);	
    
	if(retval != A664_API_OK)
    {	
		sprintf(msg,"Error: a664RxComUdpRead(error code = %d)\n",retval);
		SG_PRINTF(WARNING, "%s", msg);
	}
	
	
	pY = (uint8_t*)ssGetOutputPortSignal(S, 0);		
	
	N_port = (uint16_t*)ssGetOutputPortSignal(S,1);	
	*N_port = byteCount ;
	
	for(i=0;i<byteCount;i++){		
		pY[i] = readData[i];
	}
	
#endif	
}
 
static void sg_ModelStop(SimStruct *S)
{	
#ifndef MATLAB_MEX_FILE
	A664RxComUdpHandle *rxComUdpHandles;
    uint8_t *readData;
    int32_t retval = 0;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO781_rx_t *pIO781_rx;

    //Retrieve from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 receive: Failed to retrieve module from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO781_RECEIVE, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 receive: Failed to retrieve block from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    pIO781_rx = (sg_IO781_rx_t*)block_info->custom_data;
    
    if (pIO781_rx != NULL)
    {
        rxComUdpHandles = pIO781_rx->rxComUdpHandles;
        readData = pIO781_rx->readData;

        retval = a664RxComUdpClose(*rxComUdpHandles);
        
        if(retval != A664_API_OK){		
            sprintf(msg,"Error: a664RxComUdpClose (error code = %d)\n",retval);
            SG_PRINTF(WARNING, "%s", msg);
        }
    }
    
	free(rxComUdpHandles);
    free(readData);
    free(pIO781_rx);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO781_RECEIVE, (uintptr_t)S);
#endif	
}

#include "sg_sfcn_glue.h"   // Code generation glue
