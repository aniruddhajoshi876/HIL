//  
// condor1553bc.c - xPC Target non-inlined S-function driver for the 
// Condor Engineering QPCI-1553 Bus Controller block
// Copyright 2005-2013 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_bcsend_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          7
#define BOARDTYPE_ARG     ssGetSFcnParam(S, 0)
#define CHANNEL_ARG       ssGetSFcnParam(S, 1) // 1-4 for QPCI-1553
#define WAITFLAG_ARG      ssGetSFcnParam(S, 2) // 1 = periodic, 2 = aperiodic
#define WAITTIME_ARG      ssGetSFcnParam(S, 3)
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 4) // seconds
#define PCI_SLOT_ARG      ssGetSFcnParam(S, 5) // integer
#define MODULE_ID_ARG     ssGetSFcnParam(S, 6)

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

    if( !ssSetNumInputPorts(S, 1) ) return;
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
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
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType( S, 0, id );
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 1) ) return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, id );
    // Read responses to another list of messages.

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

extern char *BusToolsError(int code);

#define CHECK(status, fcn) \
    if (status) { SG_PRINTF(INFO, #fcn ": %s\n", BusToolsError(status)); return; }

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    bcmsglist1553  *IPtr = (bcmsglist1553 *)ssGetInputPortSignal(S,0);

    int   chan  = (int) mxGetPr(CHANNEL_ARG)[0];
    BT_UINT cardnum = 0;
    int   i, j; //, status;
 	int moduleId = (int)mxGetPr(MODULE_ID_ARG)[0];
 
    API_BC_MBUF *rcv_msg;
    int  nmsgs;
    bcmsglist1553 *OPtr = ssGetOutputPortSignal(S,0);

    int   boardtype = (int)mxGetPr(BOARDTYPE_ARG)[0];
	uint32_t *barAddr;

    char    *boardname;
    int   maxchannel;
	
	sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;

    switch( boardtype )
    {
        case 1: boardname = "IO672-1-SF"; maxchannel = 1; break;
        case 2: boardname = "IO672-1-MF"; maxchannel = 1; break;
        case 3: boardname = "IO672-2-SF"; maxchannel = 2; break;
        case 4: boardname = "IO672-2-MF"; maxchannel = 2; break;
        case 5: boardname = "IO672-4-SF"; maxchannel = 4; break;
        case 6: boardname = "IO672-4-MF"; maxchannel = 4; break;

        default:
            sprintf(msg, "Unknown IO672 variant\n");
            ssSetErrorStatus(S, msg);
            return;
    }

    if (chan < 1 || chan > maxchannel)
    {
        sprintf(msg, "bad channel %d for %s Bus Controller with ID %d",
                chan, boardname, moduleId);
        ssSetErrorStatus(S, msg);
        return;
    }
    chan = chan - 1;  // Condor library uses 0 based channel number

	//Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bcsend: Failed to retrieve module from registry in ModelStart\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    barAddr = (uint32_t*)mod_info->custom_data;
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO672_BCSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "%s bcsend: Block not registered\n", boardname);
        ssSetErrorStatus(S, msg);
        return;
    }

    cardnum = xpcQPCIInit((uintptr_t)barAddr, chan );
    if( cardnum == -1 )
    {
        sprintf( msg, "%s: Too many channels already initialized\n", boardname );
        ssSetErrorStatus( S, msg );
        return;
    }
    
    pIO672_block = (sg_IO672_block_t*)malloc(sizeof(sg_IO672_block_t));
    pIO672_block->cardnum = cardnum;
    block_info->custom_data = pIO672_block;

//SG_PRINTF(INFO, "bc send: IPtr = 0x%x IPtr[0,1,2, 3] = \n0x%x, 0x%x, 0x%x, 0x%x\n", IPtr, IPtr->token, IPtr->nmsgs, IPtr->ptrlow, IPtr->ptrhigh );

    //if( IPtr->token != (int)'1553' )
	if( memcmp(IPtr,"1553",4) != 0)
    {
        sprintf( msg, "Input signal is not a 1553 Bus Controller List" );
        ssSetErrorStatus( S, msg );
        return;
    }
//SG_PRINTF(INFO, "Exit bc send init\n");
    // Allocate space for the receive messages.
    nmsgs = IPtr->nmsgs;
    rcv_msg = (API_BC_MBUF *)malloc( nmsgs*sizeof( API_BC_MBUF ) );
    if( rcv_msg == NULL )
    {
        sprintf( msg, "Unable to allocate space for %d BC response messages", nmsgs-2 );
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block->bc_msg = rcv_msg;

    //OPtr->token = (uint32_t)'1553';
	memcpy(OPtr,"1553",4);
    OPtr->nmsgs = nmsgs;

    OPtr->ptrlow = (uint32_t)((uint64_t)rcv_msg & 0xffffffff);
    OPtr->ptrhigh = (uint32_t)(((uint64_t)rcv_msg >> 32) & 0xffffffff);

//SG_PRINTF(INFO, "get message OPTR: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", OPtr, OPtr[0], OPtr[1], OPtr[2], OPtr[3] );

    for( i = 0 ; i < nmsgs ; i++ )
    {
        // Initialize the message buffers
        rcv_msg[i].messno = i;
        rcv_msg[i].control = BC_CONTROL_NOP;
        if( i < nmsgs - 1 )
            rcv_msg[i].messno_next = (BT_U16BIT)(i + 1);
        else
        {
            rcv_msg[i].messno_next = (BT_U16BIT)(0);
            rcv_msg[i].control |= BC_CONTROL_LAST;  // Stop the BC here
        }

        rcv_msg[i].mess_command1.rtaddr   = 0;
        rcv_msg[i].mess_command1.subaddr  = 0;
        rcv_msg[i].mess_command1.tran_rec = 0;
        rcv_msg[i].mess_command1.wcount   = 0;
    
        rcv_msg[i].mess_command2.rtaddr   = 0;  // not RT-RT so command2 is 0
        rcv_msg[i].mess_command2.subaddr  = 0;
        rcv_msg[i].mess_command2.tran_rec = 0;
        rcv_msg[i].mess_command2.wcount   = 0;

        rcv_msg[i].errorid = 0;
        rcv_msg[i].gap_time = 0;
        rcv_msg[i].status  = 0;

        // Clear the data area
        for( j = 0 ; j < 32 ; j++ )
        {
            rcv_msg[i].data[0][j] = 0;
        }
    }
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    BT_UINT   cardnum;
    API_BC_MBUF *rcv_msg;
    bcmsglist1553 *IPtr  = (bcmsglist1553 *)ssGetInputPortSignal(S,0);
    API_BC_MBUF *bc_msg;
    uint32_t  bufcnt  = IPtr->nmsgs;
    uint32_t  i, j, status;
    int     waitflag = (int)mxGetPr(WAITFLAG_ARG)[0] - 1;
    // 0 = read before write, 1 = read after completion
    // timeout changed to increments of 10 microseconds, Condor library,
    // time.c, the sleep routine sets the granularity.
    int     waittimeout = (int)(mxGetPr(WAITTIME_ARG)[0]);
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bcsend: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_BCSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 bcsend: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;
    rcv_msg = pIO672_block->bc_msg;

//SG_PRINTF(INFO, "enter BC send routine\n");

    // bc_msg is a 64 bit pointer, assemble it
    bc_msg = (API_BC_MBUF *)((uint64_t)IPtr->ptrlow | ((uint64_t)IPtr->ptrhigh << 32));

    // Add a loop to read responses if set in the parameters
    if( waitflag == 0 )
    {
        for( i = 0 ; i < bufcnt ; i++ )
        {
            status = BusTools_BC_MessageRead( cardnum, i, &rcv_msg[i] );
            //SG_PRINTF(INFO, "i = %d: %d  ", i, status );
            if( status == API_BC_MBLOCK_NOMATCH )
            {
                rcv_msg[i].status  = 0;
                *(short *)&rcv_msg[i].mess_command1 = 0;
                *(short *)&rcv_msg[i].mess_status1 = 0;
                *(short *)&rcv_msg[i].mess_command2 = 0;
                *(short *)&rcv_msg[i].mess_status2 = 0;

                // Clear the data area
                for( j = 0 ; j < 32 ; j++ )
                {
                    rcv_msg[i].data[0][j] = 0;
                }
            }
            else
                CHECK( status, BusTools_BC_MessageRead );
        }
        //SG_PRINTF(INFO, "\n");
    }
//SG_PRINTF(INFO, "after first read response section\n");
    // Loop through the input vector, sending all the messages to the
    // board through the library.
    // We reserved one more than nmsgs.  The last one has BC_CONTROL_LAST set.
//SG_PRINTF(INFO, "BC: ");
    for( i = 0 ; i < bufcnt+1 ; i++ )  // send all, then start BC for one-shot
    {
        uint32_t nextmess = (uint32_t)bc_msg[i].messno_next;
 
//SG_PRINTF(INFO, "0x%x (%d), ", bc_msg[i].control, bc_msg[i].data[0][0] );
//SG_PRINTF(INFO, "0x%x, ", bc_msg[i].control );
//SG_PRINTF(INFO, "%d, ", nextmess );
        status = BusTools_BC_MessageWrite( cardnum, i, &bc_msg[i] );
        CHECK( status, BusTools_BC_MessageWrite );
        // Will get an error if bufcnt is more than the number specified
        // in qpci1553init.
        if( nextmess == 0 )
            break;
    }
//printf("\n");

    status = BusTools_BC_StartStop( cardnum, 1 );
    CHECK( status, BusTools_BC_StartStop );

    if( waitflag == 1 )
    {
        double starttime = sg_getElapsedTime( 0 );
        BT_UINT running;
        double timeout = (double)(waittimeout/1e6);

        running = 1;
        while( running == 1 )
        {
            status = BusTools_BC_IsRunning( cardnum, &running );
            CHECK( status, BusTools_BC_IsRunning );

            sg_wait_s( 1e-5 );  // 10 us wait to avoid hammering the bus
            if(sg_getElapsedTime(0) - starttime > timeout )
            {
                SG_PRINTF(TRACE, "BusTools_BC_StartStop: Timeout waiting for response\n");
                return;
            }
        }
    }

    // Add a loop to read responses if set in the parameters to read
    // responses after running the message list.
    if( waitflag == 1 )
    {
        for( i = 0 ; i < bufcnt ; i++ )
        {
            status = BusTools_BC_MessageRead( cardnum, i, &rcv_msg[i] );
            if( status == API_BC_MBLOCK_NOMATCH )
            {
                rcv_msg[i].status  = 0;
                *(short *)&rcv_msg[i].mess_command1 = 0;
                *(short *)&rcv_msg[i].mess_status1 = 0;
                *(short *)&rcv_msg[i].mess_command2 = 0;
                *(short *)&rcv_msg[i].mess_status2 = 0;

                // Clear the data area
                for( j = 0 ; j < 32 ; j++ )
                {
                    rcv_msg[i].data[0][j] = 0;
                }
//SG_PRINTF(INFO, "%d ", i);
            }
            else
                CHECK( status, BusTools_BC_MessageRead );
        }
    }
//SG_PRINTF(INFO, "leaving BC send\n");
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    API_BC_MBUF *rcv_msg;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bcsend: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_BCSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 bcsend: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    rcv_msg = pIO672_block->bc_msg;

    free(rcv_msg);
    free(pIO672_block);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO672_BCSEND, (uintptr_t)S);
    
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
