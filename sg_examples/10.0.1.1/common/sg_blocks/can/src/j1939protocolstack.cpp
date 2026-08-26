/*
 * File : j1939protocolstack.cpp
 * Abstract:
 *
 * J1939 Protocol Stack S-Function (see also tlc file)
 *
 * Copyright 2009 The MathWorks, Inc.
 */

#define         DEBUG                   0

#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         j1939protocolstack

#include        <stddef.h>
#include        <stdlib.h>

#ifndef         MATLAB_MEX_FILE
#include        "xpcPCFunctions.h"
#endif

#include        "tmwtypes.h"
#include        "simstruc.h"
#include        "can_datatype.h"


#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#else
#include        <windows.h>
#include        "xpctarget.h"
#endif


#include "include/j1939lib.h"




#define         NUMBER_OF_ARGS          (10)


#define         STACK_ID_ARG            ssGetSFcnParam(S, 0)
#define         MAX_RX_ARG              ssGetSFcnParam(S, 1)
#define         MAX_TX_ARG              ssGetSFcnParam(S, 2)
#define         TP_ENABLED_ARG          ssGetSFcnParam(S, 3)
#define         AC_ENABLED_ARG          ssGetSFcnParam(S, 4)
#define         NUM_TX_PGN_ARG          ssGetSFcnParam(S, 5)
#define         NUM_RX_PGN_ARG          ssGetSFcnParam(S, 6)
#define         NUM_CA_ARG				ssGetSFcnParam(S, 7)
#define         MAX_TP_SESSIONS         ssGetSFcnParam(S, 8)
#define         SAMPLE_TIME_ARG         ssGetSFcnParam(S, 9)


#define         NO_I_WORKS              (0)
#define         NO_R_WORKS              (0)


#define         MAXEXTIDENT            536870911
#define         MAXSTDIDENT            2047


static char_T msg[256];



static void mdlInitializeSizes(SimStruct *S) {
    int i;
    
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }
    
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);


    /* Initialize CAN Datatype */
    mdlInitialize_CAN_datatype(S);
    
   /*1 Input Port 1: (CAN FIFO READ) 2: (count)*/
    if ( !ssSetNumInputPorts(S, 2) ){
        return;
    }

    /*Output Port 1: (CAN FIFO WRITE) 2: (count)*/
    if ( !ssSetNumOutputPorts(S, 2) ){
        return;
    }


	/*CAN FIFO SEND -> CAN Msg*/
    ssSetOutputPortDataType(S, 0, ssGetDataTypeId(S,SL_CAN_MESSAGE_DTYPE_NAME));
    ssSetOutputPortWidth(S, 0, (int_T)mxGetScalar(MAX_TX_ARG)); 

	/*CAN FIFO SEND -> Msg Count*/
	ssSetOutputPortWidth(S,1,1);  /*single double value for the number of messages to send*/
	ssSetOutputPortDataType(S, 1, SS_DOUBLE);

	/*CAN FIFO RECEIVE -> CAN Msg*/
	ssSetInputPortRequiredContiguous(S , 0, true);
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, true);
    ssSetInputPortDataType(S, 0, ssGetDataTypeId(S,SL_CAN_MESSAGE_DTYPE_NAME) );

	/*CAN FIFO RECEIEVE -> Msg Count*/
	ssSetInputPortWidth(S,1,1);  /*single double value for the number of messages received*/
	ssSetInputPortDataType(S, 1, SS_DOUBLE);


    ssSetNumSampleTimes(S, 1);
            
    ssSetSimStateCompliance( S, DISALLOW_SIM_STATE );
    
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    
	/*Nothing is tunable*/
    for (i=0;i<NUMBER_OF_ARGS;i++) {
        ssSetSFcnParamNotTunable(S, i);
    }
     
    ssSetOptions( S, SS_OPTION_EXCEPTION_FREE_CODE      |
 	 				 SS_OPTION_CALL_TERMINATE_ON_EXIT   |
					 SS_OPTION_USE_TLC_WITH_ACCELERATOR|
					 SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME);



}


static void mdlInitializeSampleTimes(SimStruct *S) {
    
    ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
    ssSetOffsetTime(S, 0, 0.0); 
}


#ifdef MATLAB_MEX_FILE
# define MDL_SET_INPUT_PORT_WIDTH
static void mdlSetInputPortWidth(SimStruct *S, int_T port,int_T inputPortWidth) {

    ssSetInputPortWidth(S, port, inputPortWidth);
}

# define MDL_SET_OUTPUT_PORT_WIDTH
static void mdlSetOutputPortWidth(SimStruct *S, int_T port,int_T outputPortWidth) {

    ssSetOutputPortWidth(S, port, outputPortWidth);
}


#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
static void mdlSetDefaultPortDimensionInfo(SimStruct *S) {

    
  if(ssGetInputPortWidth(S, 0)==DYNAMICALLY_SIZED)
  {
      ssSetInputPortWidth(S, 0, 1); /*read repth is not known. we can receive only one message*/
  } 

  if(ssGetInputPortWidth(S, 1)==DYNAMICALLY_SIZED)
  {
      ssSetInputPortWidth(S, 1, 1);
  } 
}

#endif


static void mdlOutputs(SimStruct *S, int_T tid) {

}


#define MDL_RTW
static void mdlRTW(SimStruct *S)
{

	int32_T stack_id     = (int32_T) mxGetPr(STACK_ID_ARG)[0];
	int32_T max_tx       = (int32_T) mxGetPr(MAX_TX_ARG)[0];
	int32_T max_rx       = (int32_T) mxGetPr(MAX_RX_ARG)[0];
	uint8_T tp_enabled   = (uint8_T) mxGetPr(TP_ENABLED_ARG)[0];
	uint8_T ac_enabled   = (uint8_T) mxGetPr(AC_ENABLED_ARG)[0];
	int32_T num_rx_pgn   = (int32_T) mxGetPr(NUM_RX_PGN_ARG)[0];
	int32_T num_tx_pgn   = (int32_T) mxGetPr(NUM_TX_PGN_ARG)[0];
	uint8_T num_ca       = (int32_T) mxGetPr(NUM_CA_ARG)[0];
	int32_T max_tp       = (int32_T) mxGetPr(MAX_TP_SESSIONS)[0];


	ssWriteRTWParamSettings(S,9,
            SSWRITE_VALUE_DTYPE_NUM, "STACKID",
            &stack_id,
            DTINFO(SS_INT32,0),

            SSWRITE_VALUE_DTYPE_NUM, "MAXTX",
            &max_tx,
            DTINFO(SS_INT32,0),

            SSWRITE_VALUE_DTYPE_NUM, "MAXRX",
            &max_rx,
            DTINFO(SS_INT32,0),

            SSWRITE_VALUE_DTYPE_NUM, "TPENABLED",
            &tp_enabled,
            DTINFO(SS_UINT8,0),

            SSWRITE_VALUE_DTYPE_NUM, "ACENABLED",
            &ac_enabled,
            DTINFO(SS_UINT8,0),

            SSWRITE_VALUE_DTYPE_NUM, "NUMRXPGN",
            &num_rx_pgn,
            DTINFO(SS_INT32, 0),

            SSWRITE_VALUE_DTYPE_NUM, "NUMTXPGN",
            &num_tx_pgn,
            DTINFO(SS_INT32, 0),

            SSWRITE_VALUE_DTYPE_NUM, "NUMCA",
            &num_ca,
            DTINFO(SS_UINT8, 0),

            SSWRITE_VALUE_DTYPE_NUM, "MAXTP",
            &max_tp,
            DTINFO(SS_INT32, 0)
	);
}




static void mdlTerminate(SimStruct *S) {
}



#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif



