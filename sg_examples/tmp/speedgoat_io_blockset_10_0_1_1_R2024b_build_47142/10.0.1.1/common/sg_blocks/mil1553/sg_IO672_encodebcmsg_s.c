// condor1553encodebcmsg.c - xPC Target non-inlined S-function driver for the 
// 1553 protocol.  Set parameters for a message in a list of messages.
// Copyright 2005-2014 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_encodebcmsg_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          11
#define MESSNO_ARG        ssGetSFcnParam(S, 0) // Message number in list
#define TERM1_ARG         ssGetSFcnParam(S, 1) // terminal address 1
#define SUB1_ARG          ssGetSFcnParam(S, 2) // sub address 1
#define TERM2_ARG         ssGetSFcnParam(S, 3) // terminal address 2
#define SUB2_ARG          ssGetSFcnParam(S, 4) // sub address 2
#define MODE_ARG          ssGetSFcnParam(S, 5) // mode command
#define SENDCOUNT_ARG     ssGetSFcnParam(S, 6) // word count
#define DIRECTION_ARG     ssGetSFcnParam(S, 7) // 1 = R, 2 = T
#define GAP_ARG           ssGetSFcnParam(S, 8) // gap time in microseconds
#define BUS_ARG           ssGetSFcnParam(S, 9) // seconds
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 10) // seconds

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

    if( (int)mxGetPr(DIRECTION_ARG)[0] == 1 ) // R (BC->RT)
    {
        if( !ssSetNumInputPorts(S, 2) )return;  // RT receives, add data port
    }
    else
    {
        if( !ssSetNumInputPorts(S, 1) )return;  // RT Sends, no data port
    }

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
    // None of these functions can be called from the target side.
#endif

    // Port 0 is the input list of message buffers.
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType( S, 0, id );
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    // Port 1 is the data to put into the chosen message buffer
    // If RT is sending to BC, then hide this port
    if( (int)mxGetPr(DIRECTION_ARG)[0] == 1 ) // RT receiving
    {
        ssSetInputPortRequiredContiguous( S, 1, 1 ); 
        ssSetInputPortWidth(S, 1, DYNAMICALLY_SIZED );
        ssSetInputPortDataType( S, 1, DYNAMICALLY_TYPED );
        ssSetInputPortDirectFeedThrough(S, 1, 1);
    }

    if( !ssSetNumOutputPorts(S, 1) )return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, id );

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
    ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_SET_INPUT_PORT_WIDTH
static void mdlSetInputPortWidth( SimStruct *S, int port, int width )
{
    int count    = (int)mxGetPr( SENDCOUNT_ARG )[0];

    if( width > 32 || width <= 0 )
    {
        sprintf( msg, "Input port width must be greater than 0 and less than or equal to 32");
        ssSetErrorStatus( S, msg );
        return;
    }
    if( count > width )
    {
        sprintf( msg, "Input port width isn't large enough to supply the specified send count.");
        ssSetErrorStatus( S, msg );
        return;
    }
    ssSetInputPortWidth( S, port, width );
}

#define MDL_SET_OUTPUT_PORT_WIDTH
static void mdlSetOutputPortWidth( SimStruct *S, int port, int width )
{
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType( SimStruct *S, int port, DTypeId id )
{
    if( id == SS_INT16 || id == SS_UINT16 )
        ssSetInputPortDataType( S, port, id );
    else
    {
        sprintf( msg, "Input must be 16 bit signed or unsigned integers." );
        ssSetErrorStatus(S,msg);
        return;
    }        
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE  
    API_BC_MBUF *bc_msg;
    int32_t nmsgs;
    bcmsglist1553 *IPtr = (bcmsglist1553 *)ssGetInputPortSignal(S,0);
    bcmsglist1553 *OPtr = (bcmsglist1553 *)ssGetOutputPortSignal(S,0);
    int messno   = (int)mxGetPr( MESSNO_ARG )[0] - 1;
    //int nextmess = (int)mxGetPr( NEXTMESSNO_ARG )[0];
    int terminal1 = (int)mxGetPr( TERM1_ARG )[0] - 1;
    int subaddr1  = (int)mxGetPr( SUB1_ARG )[0] - 1;
    int terminal2 = (int)mxGetPr( TERM2_ARG )[0] - 1;
    int subaddr2  = (int)mxGetPr( SUB2_ARG )[0];
    int mode      = (int)mxGetPr( MODE_ARG )[0] - 1;
    int count     = (int)mxGetPr( SENDCOUNT_ARG )[0];

    // R -> 0, T -> 1, RT-RT -> 2
    int toRT      = (int)mxGetPr( DIRECTION_ARG )[0] - 1;
    int gap       = (int)mxGetPr( GAP_ARG )[0];

    if( count < 1 ) count = 1;
    if( count > 32 )
    {
        sprintf( msg, "Send count is limited to 32 for 1553 Bus Controller");
        ssSetErrorStatus( S, msg );
        return;
    }

//SG_PRINTF(INFO, "setmsg: IPtr = 0x%x IPtr[0,1,2] = \n0x%x, 0x%x, 0x%x\n", IPtr, IPtr[0], IPtr[1], IPtr[2] );

    //if( IPtr->token != (uint32_t)"1553" )
	if( memcmp(IPtr,"1553",4) != 0)
    {
        sprintf( msg, "Input signal is not a 1553 Bus Controller List" );
        ssSetErrorStatus( S, msg );
        return;
    }

    nmsgs = (int32_t)IPtr->nmsgs;

    // bc_msg is a 64 bit pointer, assemble it
    bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

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

    if( toRT == 2 ) // if RT-RT command
    {
        bc_msg[messno].mess_command1.rtaddr   = terminal1;
        bc_msg[messno].mess_command1.subaddr  = subaddr1 - 1;
        bc_msg[messno].mess_command1.tran_rec = 0;  // Receive
        bc_msg[messno].mess_command1.wcount   = count;

        bc_msg[messno].mess_command2.rtaddr   = terminal2;
        bc_msg[messno].mess_command2.subaddr  = subaddr2 - 2;
        bc_msg[messno].mess_command2.tran_rec = 1;  // Transmit
        bc_msg[messno].mess_command2.wcount   = count;

        bc_msg[messno].control |= BC_CONTROL_MESSAGE | BC_CONTROL_RTRTFORMAT;

        bc_msg[messno].gap_time = gap;
    }
    else // R or T command
    {
        // subaddr == 0 or subaddr == 1 means this is a mode command.
        // Otherwise, subtract 2 from subaddr to get the value to write to
        // the message.

        // Fill in the non-changing fields for the chosen message in the
        // list.
        //SG_PRINTF(INFO, "term %d\n", terminal1 );

        // If this is R or T command, then the board uses mess_command1
        // only.  The value in mess_command2 is ignored.
        // If this is an RT-RT command, then the board uses both.
        // Fill them both in always.  It takes less time than testing and
        // branching and 

        bc_msg[messno].mess_command1.rtaddr   = terminal1;
        bc_msg[messno].control |= BC_CONTROL_MESSAGE;
//SG_PRINTF(INFO, "set: messno %d, control = 0x%x\n", messno, bc_msg[messno].control );

        if( subaddr1 == 0 || subaddr1 == 1 )
        {
            // This is a mode command, mode goes into the count field
            // and 0 or 0x1f goes into subaddr.
            if( subaddr1 == 1 ) subaddr1 = 0x1f;
            bc_msg[messno].mess_command1.subaddr  = subaddr1;
            
            if (mode == 17 || mode == 20 || mode == 21)
            {
                bc_msg[messno].mess_command1.tran_rec = 0;
            }
            else
            {
                bc_msg[messno].mess_command1.tran_rec = 1;
            }
            bc_msg[messno].mess_command1.wcount   = mode;
        } else
        {
            subaddr1 -= 1;
            bc_msg[messno].mess_command1.subaddr  = subaddr1;
            bc_msg[messno].mess_command1.tran_rec = toRT;
            bc_msg[messno].mess_command1.wcount   = count;
        }
        bc_msg[messno].gap_time = gap;
    }
//SG_PRINTF(INFO, "setmsg init exit\n");
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE  
    bcmsglist1553 *IPtr = (bcmsglist1553 *)ssGetInputPortSignal(S,0);
    API_BC_MBUF *bc_msg;
    //uint32_t  nmsgs = IPtr->nmsgs;
    int     i;
    short *sptr;    // Data
    int sendcount  = (int)mxGetPr(SENDCOUNT_ARG)[0];
    int messno   = (int)mxGetPr( MESSNO_ARG )[0] - 1;
    //double stime   = mxGetPr(SAMP_TIME_ARG)[0] * 1.193e6;
    int bus = (int)mxGetPr(BUS_ARG)[0];
    // R -> 0, T -> 1, RT-RT -> 2
    int toRT      = (int)mxGetPr( DIRECTION_ARG )[0] - 1;
    int gap      = (int)mxGetPr( GAP_ARG )[0];

//SG_PRINTF(INFO, "encode start  ");
    if( sendcount > 32 )
    {
        sprintf( msg, "Send count is > 32, count = %d\n", sendcount );
        ssSetErrorStatus(S, msg);
        return;
    }

    // bc_msg is a 64 bit pointer, assemble it
    bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    bc_msg[messno].control |= BC_CONTROL_MESSAGE | BC_CONTROL_BUFFERA;
    if( bus == 1 )
        bc_msg[messno].control |= BC_CONTROL_CHANNELA;
    else
        bc_msg[messno].control |= BC_CONTROL_CHANNELB;

//SG_PRINTF(INFO, "set: bus %d, messno %d, control = 0x%x\n", bus, messno, bc_msg[messno].control );
    if( toRT == 0 )  // If BC -> RT
    {
//SG_PRINTF(INFO, "a\n");
        sptr  = (short *)ssGetInputPortSignal(S,1);
//SG_PRINTF(INFO, "b\n");
        for( i = 0 ; i < sendcount ; i++ )
        {
            bc_msg[messno].data[0][i] = sptr[i];
        }
//SG_PRINTF(INFO, "c\n");

        if( sendcount < 32 )
        {
//SG_PRINTF(INFO, "d\n");
            for( i = sendcount ; i < 32 ; i++ )
            {
                bc_msg[messno].data[0][i] = 0;
                bc_msg[messno].data[1][i] = 0;
            }
        }
    }
//SG_PRINTF(INFO, "e\n");
    bc_msg[messno].gap_time = gap;
//SG_PRINTF(INFO, "encode end\n");
#endif
}

static void sg_ModelStop(SimStruct *S)
{
    // Nothing to do on terminate.
}

#include "sg_sfcn_glue.h"   // Code generation glue
