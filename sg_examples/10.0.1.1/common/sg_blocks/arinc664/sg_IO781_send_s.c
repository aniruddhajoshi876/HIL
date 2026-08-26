#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO781_send_s

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

#define MODULE_ID_ARG       			ssGetSFcnParam(S, 0)     //parModuleId
#define PORT_ID_ARG						ssGetSFcnParam(S, 1)
#define TX_MSG_LEN_ARG					ssGetSFcnParam(S, 2)
#define SAMP_TIME_ARG					ssGetSFcnParam(S, 3)		//block sample time	
#define NUMBER_OF_ARGS 		   						  (	  4)
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
	uint32_t i, tx_msg_length;
	tx_msg_length = (uint32_t)mxGetPr(TX_MSG_LEN_ARG)[0];
	
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
		sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }
	
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);	
	if(!ssSetNumInputPorts(S, 1)) 
	{
		SG_PRINTF(INFO, "error while setting input ports\n");
		return;
	}		
	
	
	ssSetInputPortWidth(S, 0, tx_msg_length);
	//ssSetInputPortWidth(S, 1, 1);
	//if(!ssSetInputPortMatrixDimensions(S, 0, DYNAMICALLY_SIZED){ 
	//	return;
	//}
	ssSetInputPortDataType(S, 0, SS_UINT8);

	
	
	ssSetInputPortDirectFeedThrough	( S, 0, 1);
	ssSetInputPortRequiredContiguous( S, 0, 1);
	
	//ssSetInputPortDirectFeedThrough	( S, 1, 1);
	//ssSetInputPortRequiredContiguous( S, 1, 1);
    
	
	if(!ssSetNumOutputPorts(S, 0))	
	{
		SG_PRINTF(INFO, "error while setting output ports\n");
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
    // Open the Tx port and get the handles
    A664TxComUdpHandle *txComUdpHandles;
    //extern A664EndSystemHandle esHandle[10];
    uint8_t module_id_corr = (uint8_t)mxGetPr(MODULE_ID_ARG)[0]-1;
    int32_t retval = 0;
    uint32_t port_id = (uint32_t)mxGetPr(PORT_ID_ARG)[0];
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 send: Module not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO781_SEND, (uintptr_t)S);
    
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 send: Block not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    txComUdpHandles =  (A664TxComUdpHandle*)malloc(sizeof(A664TxComUdpHandle));
    SG_PRINTF(DEBUG,"Send, EsHandle %p\n",esHandle[module_id_corr].handle);
    
    retval = a664TxComUdpOpen( esHandle[module_id_corr], port_id, txComUdpHandles);
	
    if(retval != A664_API_OK)
    {		
        sprintf(msg,"Error: a664TxComUdpOpen (error code = %d)\n",retval);
        ssSetErrorStatus(S,msg);
        return;
    }
    
    block_info->custom_data = txComUdpHandles;
#endif
}

static void sg_ModelStep(SimStruct *S)
{	
#ifndef MATLAB_MEX_FILE
	
	uint8_t 				*uPtr				; 		
	int32_t        			retval = 0			;

	A664TxComUdpHandle  	*txComUdpHandles	;
	uint16_t 				byteCount, 
							tx_msg_length		;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 send: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO781_SEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 send: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
	
	txComUdpHandles = (A664TxComUdpHandle*)block_info->custom_data;
	tx_msg_length = (uint16_t)mxGetPr(TX_MSG_LEN_ARG)[0];
	
	//uPtr= (uint8_t *)ssGetInputPortRealSignal(S,0);		
	uPtr= (uint8_t *)ssGetInputPortSignal(S,0);		
	
	
	retval = a664TxComUdpWrite(*txComUdpHandles, tx_msg_length, uPtr, &byteCount);
	if(retval != A664_API_OK)
    {	
		sprintf(msg,"Error: a664TxComUdpWrite (error code = %d)\n",retval);
		SG_PRINTF(WARNING, "%s", msg);
	}

#endif	
}

static void sg_ModelStop(SimStruct *S)
{	
#ifndef MATLAB_MEX_FILE
	A664TxComUdpHandle  *txComUdpHandles;
    int32_t retval = 0;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO781 send: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO781_SEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO781 send: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    txComUdpHandles = (A664TxComUdpHandle*)block_info->custom_data;
    
    if (txComUdpHandles != NULL)
    {
        retval = a664TxComUdpClose(*txComUdpHandles);

        if(retval != A664_API_OK)
        {		
            sprintf(msg,"Error: a664TxComUdpClose (error code = %d)\n",retval);
            SG_PRINTF(WARNING, "%s", msg);
        }
    }
    
	free(txComUdpHandles);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO781_SEND, (uintptr_t)S);
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
