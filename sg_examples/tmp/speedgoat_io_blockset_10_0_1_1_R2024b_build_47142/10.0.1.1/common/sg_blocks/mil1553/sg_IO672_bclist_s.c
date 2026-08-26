// condor1553bclist.c - xPC Target non-inlined S-function to create a list
// of empty Bus Controller buffers for the Condor 1553 blocks.
// Copyright 2005-2013 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_bclist_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          2
#define NUM_ARG           ssGetSFcnParam(S, 0)
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 1)

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (1)

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;
    DTypeId id = SS_UINT32;

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

    if( !ssSetNumInputPorts(S, 0) )return;
    if( !ssSetNumOutputPorts(S, 1) )return;
    // Just pass a pointer to malloc'ed memory where the fifo exists
    // Assume that a pointer is 32 bits wide.
#ifdef          MATLAB_MEX_FILE
    // First create the custom data type for a fifo pointer
    // The Register call defines the signal as a unique type for Simulink
    id = ssRegisterDataType( S, "bcmsglist1553" );
    if(id == INVALID_DTYPE_ID)
        return;
    ssSetDataTypeSize( S, id, 16 );
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
    // '1553', N, pointer low, pointer high allows for a 64 bit pointer
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, id );

    ssSetSimStateCompliance( S, DISALLOW_SIM_STATE );

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
    void   **PWork = ssGetPWork(S);
    int   i, j;
    int  nmsgs = (int)mxGetPr( NUM_ARG )[0] + 1;
    API_BC_MBUF *bc_msg;
    bcmsglist1553 *OPtr = (bcmsglist1553 *)ssGetOutputPortSignal(S,0);

    if( nmsgs <= 0 )
    {
        sprintf( msg, "Illegal message count in bclist preparation" );
        ssSetErrorStatus(S, msg);
        return;
    }

    // Allocate N message buffers, free them in mdlTerminate.
    // Allocate one more than specified in the block parameters since
    // the very first one has control with BC_CONTROL_MFRAME_BEG.
    // The next to last one has control BC_CONTROL_MFRAME_END and can have
    // a real message as well.
    // The very last one has control set to BC_CONTROL_LAST and can't contain
    // a real message.
    // Use calloc to make sure there's nothing in any of the buffers.
    bc_msg = (API_BC_MBUF *)calloc( (nmsgs+1), sizeof( API_BC_MBUF ) );
    if( bc_msg == NULL )
    {
        sprintf( msg, "Unable to allocate space for %d BC messages", nmsgs-1 );
        ssSetErrorStatus(S, msg);
        return;
    }
    PWork[0] = (void *)bc_msg;

    //OPtr->token = '1553';
	memcpy(OPtr,"1553",4);
    OPtr->nmsgs = (uint32_t)nmsgs;  // +1 is implied as the CONTROL_LAST buffer
    OPtr->ptrlow = (uint32_t)((uint64_t)bc_msg & 0xffffffff);
    OPtr->ptrhigh = (uint32_t)(((uint64_t)bc_msg >> 32) & 0xffffffff);

//SG_PRINTF(INFO, "bclist: OPtr = 0x%x OPtr[0,1,2,3] = \n0x%x, 0x%x, 0x%x, 0x%x\n", OPtr, OPtr->token, OPtr->nmsgs, OPtr->ptrlow, OPtr->ptrhigh );

    for( i = 0 ; i < nmsgs ; i++ )
    {
        // Initialize the message buffers
        bc_msg[i].messno = i;
        bc_msg[i].control = BC_CONTROL_NOP | BC_CONTROL_RETRY;
        if( i == 0 )
            bc_msg[i].control |= BC_CONTROL_MFRAME_BEG;
        if( i < nmsgs - 1 )
            bc_msg[i].messno_next = (BT_U16BIT)(i + 1);
        else
        {
            bc_msg[i].messno_next = (BT_U16BIT)(0);
            bc_msg[i].control |= BC_CONTROL_LAST; // | BC_CONTROL_MFRAME_END;  // Stop the BC here
        }
        // CONTROL_LAST must be a separate no-op, not with MFRAME_END

        bc_msg[i].mess_command1.rtaddr   = 0;
        bc_msg[i].mess_command1.subaddr  = 0;
        bc_msg[i].mess_command1.tran_rec = 0;
        bc_msg[i].mess_command1.wcount   = 0;
    
        bc_msg[i].mess_command2.rtaddr   = 0;  // not RT-RT so command2 is 0
        bc_msg[i].mess_command2.subaddr  = 0;
        bc_msg[i].mess_command2.tran_rec = 0;
        bc_msg[i].mess_command2.wcount   = 0;

        bc_msg[i].errorid = 0;
        bc_msg[i].gap_time = 15;
        bc_msg[i].status  = 0;

        // Clear the data area
        for( j = 0 ; j < 32 ; j++ )
        {
            bc_msg[i].data[0][j] = 0;
        }
    }
//SG_PRINTF(INFO, "create list init exit\n");
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE  
    void   **PWork = ssGetPWork(S);
    int   i;
    int  nmsgs = (int)mxGetPr( NUM_ARG )[0];
    API_BC_MBUF *bc_msg;

    // Reset all buffers to NOP, the message block for each
    // message must be executed or the message isn't sent.
    bc_msg = (API_BC_MBUF *)PWork[0];

    bc_msg[0].control |= BC_CONTROL_MFRAME_BEG;
    for( i = 0 ; i < nmsgs ; i++ )
    {
        // Don't clear the CONTROL_LAST type
        // Initialize the message buffers
        bc_msg[i].control &= ~BC_CONTROL_TYPEMASK;  // clears the message type
        // all the messages are now NO-OPs.
        if( i == nmsgs - 1 )
            bc_msg[i].control |= BC_CONTROL_MFRAME_END;
    }
    bc_msg[nmsgs].control |= BC_CONTROL_HALT;
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE  
    void   **PWork  = ssGetPWork(S);
    API_BC_MBUF *msg = (API_BC_MBUF *)PWork[0];

    free( msg );
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
