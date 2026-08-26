// condor1553decodebcmsg.c - xPC Target non-inlined S-function driver for the 
// 1553 protocol.  Set parameters for a message in a list of messages.
// Copyright 2005-2013 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_decodebcmsg_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          2
#define MESSNO_ARG        ssGetSFcnParam(S, 0) // Message number in list
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 1) // seconds

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (0)

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;
    DTypeId id = SS_UINT32;
    DTypeId statid = SS_UINT32;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg, "%d input args expected, %d passed", 
                NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if( !ssSetNumInputPorts(S, 1) )return;

    // Port 0 is the input list of message buffers.
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
#ifdef          MATLAB_MEX_FILE
    // First create the custom data type for a fifo pointer
    // The Register call defines the signal as a unique type for Simulink
    id = ssRegisterDataType( S, "bcmsglist1553" );
    if(id == INVALID_DTYPE_ID)
        return;
    ssSetDataTypeSize( S, id, 16 );  // 4*int32
    if( ssGetDataTypeZero( S, id ) == NULL )
    {
        bcmsglist1553 bcmsgzero;
        
        bcmsgzero.token = 0;
        bcmsgzero.nmsgs = 0;
        bcmsgzero.ptrlow = 0;
        bcmsgzero.ptrhigh = 0;
        ssSetDataTypeZero( S, id, &bcmsgzero );
    }
    // Neither of these functions can be called from the target side.
#endif
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType( S, 0, id );
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 3) )return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, id );

    // Output port 1 is the status from the chosen message buffer
#ifdef          MATLAB_MEX_FILE
    // First create the custom data type for a fifo pointer
    // The Register call defines the signal as a unique type for Simulink
    statid = ssRegisterDataType( S, "bcstatus1553" );
    if(statid == INVALID_DTYPE_ID)
        return;
    ssSetDataTypeSize( S, statid, 24 );  // 6*int32
    if( ssGetDataTypeZero( S, id ) == NULL )
    {
        bcstatus1553 bcstatzero;
        
        bcstatzero.control = 0;
        bcstatzero.cmd1 = 0;
        bcstatzero.stat1 = 0;
        bcstatzero.cmd2 = 0;
        bcstatzero.stat2 = 0;
        bcstatzero.status = 0;
        ssSetDataTypeZero( S, id, &bcstatzero );
    }
    // Neither of these functions can be called from the target side.
#endif
    ssSetOutputPortWidth(S, 1, 1 );
    ssSetOutputPortDataType( S, 1, statid );

    // Output port 2 is the data from the chosen message buffer
    ssSetOutputPortWidth(S, 2, 32 );
    ssSetOutputPortDataType( S, 2, SS_UINT16 );

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, NUM_R_WORKS);
    ssSetNumIWork(S, NUM_I_WORKS);
    ssSetNumPWork(S, NUM_P_WORKS);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUM_ARGS; i++)
        ssSetSFcnParamTunable(S, i, 0);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );
}
 
static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
        ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
    } else {
        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    //int   i;
    //int inwidth;
    //API_BC_MBUF *bc_msg;
    int nmsgs;
    bcmsglist1553 *IPtr = (bcmsglist1553 *)ssGetInputPortSignal(S,0);
    bcmsglist1553 *OPtr = (bcmsglist1553 *)ssGetOutputPortSignal(S,0);
    int messno   = (int)mxGetPr( MESSNO_ARG )[0] - 1;

//SG_PRINTF(INFO, "get message IPTR: 0x%x, 0x%x, 0x%x, 0x%x\n", IPtr, IPtr[0], IPtr[1], IPtr[2] );
    //if( IPtr->token != (uint32_t)'1553' )
	if( memcmp(IPtr,"1553",4) != 0)
    {
        sprintf( msg, "Input signal is not a 1553 Bus Controller List" );
        ssSetErrorStatus( S, msg );
        return;
    }

    nmsgs = (int)IPtr->nmsgs;
    //bc_msg = (API_BC_MBUF *)IPtr->ptrlow;  // 32 bit only
	
    // bc_msg is a 64 bit pointer, assemble it
    //bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    // Copy the input through to the output.
    //OPtr->token = (uint32_t)'1553';
	memcpy(OPtr,"1553",4);
    OPtr->nmsgs = IPtr->nmsgs;
    OPtr->ptrlow = IPtr->ptrlow;
    OPtr->ptrhigh = IPtr->ptrhigh;

    if( messno < 0 || messno >= nmsgs )
    {
        sprintf( msg, "Message number %d, is out of the range [0,%d] of the supplied message list",
                 messno, nmsgs-1 );
        ssSetErrorStatus( S, msg );
        return;
    }
//SG_PRINTF(INFO, "setmsg init exit\n");
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    bcmsglist1553 *IPtr = (bcmsglist1553 *)ssGetInputPortSignal(S,0);
    API_BC_MBUF   *bc_msg;
    //uint32_t      nmsgs = IPtr->nmsgs;
    int         i; //, status;
	
    // bc_msg is a 64 bit pointer, assemble it
    bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    // Status
    bcstatus1553 *sptr    = (bcstatus1553 *)ssGetOutputPortSignal(S,1);

    // Data
    short *dptr    = (short *)ssGetOutputPortSignal(S,2);

    int messno   = (int)mxGetPr( MESSNO_ARG )[0] - 1;

    sptr->control = 0xffff & (uint32_t)bc_msg[messno].control;
    sptr->cmd1    = 0xffff & *(uint32_t *)&bc_msg[messno].mess_command1;
    sptr->stat1   = 0xffff & *(uint32_t *)&bc_msg[messno].mess_status1;
    sptr->cmd2    = 0xffff & *(uint32_t *)&bc_msg[messno].mess_command2;
    sptr->stat2   = 0xffff & *(uint32_t *)&bc_msg[messno].mess_status2;
    sptr->status  = *(uint32_t *)&bc_msg[messno].status; // BT1553_INT_* defined bits

    for( i = 0 ; i < 32 ; i++ )
    {
        dptr[i] = bc_msg[messno].data[0][i];
    }
//SG_PRINTF(INFO, "%x\n", bc_msg[messno].data[0][0] );
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    // Nothing to do on terminate.
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
