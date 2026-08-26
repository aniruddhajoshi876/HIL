// condor1553selectbmmsg.c - xPC Target non-inlined S-function driver for the 
// 1553 protocol.  This is the Bus Monitor decode routine.
// Copyright 2005-2009 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_selectbmmsg_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          8
#define SELECT_ARG        ssGetSFcnParam(S, 0) // Selection type
#define MESSNO_ARG        ssGetSFcnParam(S, 1) // Message number in list
#define RT1_ARG           ssGetSFcnParam(S, 2) // First RT
#define SUB1_ARG          ssGetSFcnParam(S, 3) // First sub addr
#define RT2_ARG           ssGetSFcnParam(S, 4) // second RT
#define SUB2_ARG          ssGetSFcnParam(S, 5) // second sub addr
#define DIR_ARG           ssGetSFcnParam(S, 6) // Direction
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 7) // seconds

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (0)

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

    if( !ssSetNumInputPorts(S, 1) )return;

    // Port 0 is the input list of message buffers.
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
#ifdef          MATLAB_MEX_FILE
    // First create the custom data type for a fifo pointer
    // The Register call defines the signal as a unique type for Simulink
    id = ssRegisterDataType( S, "bmmsglist1553" );
    if(id == INVALID_DTYPE_ID)
        return;
    ssSetDataTypeSize( S, id, 16 );
    if( ssGetDataTypeZero( S, id ) == NULL )
    {
        bmmsglist1553 bmmsgzero;
        
        bmmsgzero.token = 0;
        bmmsgzero.nmsgs = 0;
        bmmsgzero.ptrlow = 0;
        bmmsgzero.ptrhigh = 0;
        ssSetDataTypeZero( S, id, &bmmsgzero );
    }
    // Neither of these functions can be called from the target side.
#endif
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType( S, 0, id );
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 4) )return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, id );

    // Output port 1 is the status from the chosen message buffer
    ssSetOutputPortWidth(S, 1, 1 );
    ssSetOutputPortDataType( S, 1, SS_DOUBLE );

    // Output port 2 is the status from the chosen message buffer
    ssSetOutputPortWidth(S, 2, 7 );
    ssSetOutputPortDataType( S, 2, SS_UINT32 );

    // Output port 3 is the data from the chosen message buffer
    ssSetOutputPortWidth(S, 3, 32 );
    ssSetOutputPortDataType( S, 3, SS_UINT16 );

    ssSetSimStateCompliance( S, HAS_NO_SIM_STATE );

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
    API_BC_MBUF *bc_msg;
    int nmsgs;
    bmmsglist1553 *IPtr = (bmmsglist1553 *)ssGetInputPortSignal(S,0);
    bmmsglist1553 *OPtr = (bmmsglist1553 *)ssGetOutputPortSignal(S,0);
    int messno   = (int)mxGetPr( MESSNO_ARG )[0] - 1;

//SG_PRINTF(INFO, "get message IPTR: 0x%x, 0x%x, 0x%x, 0x%x\n", IPtr, IPtr[0], IPtr[1], IPtr[2] );
    //if( IPtr->token != (uint32_t)'1553' )
	if( memcmp(IPtr,"1553",4) != 0)
    {
        sprintf( msg, "Input signal is not a 1553 Bus Monitor List" );
        ssSetErrorStatus( S, msg );
        return;
    }

    nmsgs = (int)IPtr->nmsgs;
    //bc_msg = (API_BC_MBUF *)IPtr->ptrlow;  // 32 bit only
	
    // bc_msg is a 64 bit pointer, assemble it
    bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    // Copy the input through to the output.  This doesn't change at
    // mdlOutputs time.  Don't have to do it every time.
    //OPtr->token = (uint32_t)'1553';
	memcpy(OPtr,"1553",4);
    OPtr->nmsgs = IPtr->nmsgs;
    //OPtr->ptrlow = IPtr->ptrlow;
	
    OPtr->ptrlow = IPtr->ptrlow;
    OPtr->ptrhigh = IPtr->ptrhigh;

    if( messno < 0 || messno >= nmsgs )
    {
        sprintf( msg, "Message number %d, is out of the range [1,%d] of the supplied message list",
                 messno+1, nmsgs );
        ssSetErrorStatus( S, msg );
        return;
    }
//SG_PRINTF(INFO, "setmsg init exit\n");
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    bmmsglist1553 *IPtr = (bmmsglist1553 *)ssGetInputPortSignal(S,0);
    API_BM_MBUF *bm_msg;
    API_BM_MBUF *this_msg;
    int     nmsgs = (int)IPtr->nmsgs;
    int     i;
    int     select =(int)mxGetPr( SELECT_ARG )[0];

    // bc_msg is a 64 bit pointer, assemble it
    bm_msg = (API_BM_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    // Time output
    double *tptr = ssGetOutputPortSignal(S,1);

    // Status output
    unsigned int *sptr    = (unsigned int *)ssGetOutputPortSignal(S,2);

    // Data output
    short *dptr    = (short *)ssGetOutputPortSignal(S,3);

    int messno;
    //int rt1, sub1, rt2, sub2, dir;
    int found = 0;
    BT1553_COMMAND    command1;
    BT1553_COMMAND    command2;
    unsigned short cmd1, cmd2, c1, c2;

    switch( select )
    {
      case 1: // Read the selected message number, no other ones
        messno = (int)mxGetPr( MESSNO_ARG )[0] - 1;  // convert 1 based to 0 based index
        if( messno >= nmsgs || messno < 0 )
            break;
        this_msg = &bm_msg[messno];
        found = 1;
        break;

      case 2: // Find the first instance of a BC<->RT message that
        // matches the RT, sub and direction given.
        command1.rtaddr = (int)mxGetPr( RT1_ARG )[0];
        command1.subaddr = (int)mxGetPr( SUB1_ARG )[0];
        // DIR_ARG is 1 for R, 2 for T, subtract 1 so R=0, T=1.
        command1.tran_rec = (int)mxGetPr( DIR_ARG )[0] - 1;
        cmd1 = *(unsigned short*)&command1;
//printf("search: 0x%x\n", cmd1 );

        for( messno = 0 ; messno < nmsgs ; messno++ )
        {
            this_msg = &bm_msg[messno];
            if( this_msg->messno == -1 )
                continue;  // empty message slot, skip it.
            c1 = *(unsigned short*)&this_msg->command1;
//SG_PRINTF(INFO, "  msg %d: 0x%x\n", messno, c1 );
            if( ( cmd1 & 0xffe0 ) == ( c1 & 0xffe0 ) ) // skip the count when comparing
            {
                found = 1;
//SG_PRINTF(INFO, "      found\n");
                break;
            }
        }
        break;

      case 3: // Find the first instance of an RT->RT message that
        // matches both RTs and sub addrs.
        command1.rtaddr = (int)mxGetPr( RT1_ARG )[0];
        command1.subaddr = (int)mxGetPr( SUB1_ARG )[0];
        command1.tran_rec = 1;  // transmitting side
        cmd1 = *(unsigned short*)&command1;
        command2.rtaddr = (int)mxGetPr( RT2_ARG )[0];
        command2.subaddr = (int)mxGetPr( SUB2_ARG )[0];
        command2.tran_rec = 0;  // receiving side
        cmd2 = *(unsigned short*)&command2;
        for( messno = 0 ; messno < nmsgs ; messno++ )
        {
            this_msg = &bm_msg[messno];
            if( this_msg->messno == -1 )
                continue;  // empty message slot, skip it.
            c1 = *(unsigned short*)&this_msg->command1;
            c2 = *(unsigned short*)&this_msg->command2;
            if( (( cmd1 & 0xffe0 ) == ( c1 & 0xffe0 ))
                && (( cmd2 & 0xffe0 ) == (c2 & 0xffe0 )))
            {
                found = 1;
                break;
            }
        }
        break;
    }

    if( found == 1 )
    {
        // 2^32 = 4294967296.0
        *tptr = (this_msg->time.topuseconds * 4294967296.0) + this_msg->time.microseconds;

        sptr[0] = this_msg->messno;
        sptr[1] = (int)(0xffff & *(unsigned short *)&(this_msg->command1));
        sptr[2] = (int)(*(unsigned char *)&(this_msg->response1));
        sptr[3] = (int)(*(unsigned short *)&(this_msg->status1));
        sptr[4] = (int)(0xffff & *(unsigned short *)&(this_msg->command2));
        sptr[5] = (int)(*(unsigned char *)&(this_msg->response2));
        sptr[6] = (int)(*(unsigned short *)&(this_msg->status2));

        for( i = 0 ; i < 32 ; i++ )
        {
            dptr[i] = this_msg->value[i];
        }
    }
    else
    {
        sptr[0] = 0;
        sptr[1] = 0;
        sptr[2] = 0;
        sptr[3] = 0;
        sptr[4] = 0;
        sptr[5] = 0;
        sptr[6] = 0;

        for( i = 0 ; i < 32 ; i++ )
        {
            dptr[i] = 0;
        }
    }
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    // Nothing to do on terminate.
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
