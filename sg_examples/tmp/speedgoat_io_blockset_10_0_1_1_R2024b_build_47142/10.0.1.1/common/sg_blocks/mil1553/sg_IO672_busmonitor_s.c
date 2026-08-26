//  
// condor1553bm.c - xPC Target non-inlined S-function driver for the 
// Condor Engineering QPCI-1553 Bus Monitor Initialize block
// Copyright 2005-2014 The MathWorks, Inc.


// This block is for per-channel initialization for a bus controller

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_busmonitor_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          6
#define BOARDTYPE_ARG     ssGetSFcnParam(S, 0)
#define CHANNEL_ARG       ssGetSFcnParam(S, 1) // 1-4 for QPCI-1553
#define MSGCNT_ARG        ssGetSFcnParam(S, 2)
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 3) // seconds
#define PCI_SLOT_ARG      ssGetSFcnParam(S, 4) // integer
#define MODULE_ID_ARG     ssGetSFcnParam(S, 5)

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (0)

//#define RECEIVE           (0)
//#define TRANSMIT          (1)
#define NUM_DATA_BUFS     (2)
#define WORD_COUNT        (10)
#define START             (1)
#define STOP              (0)


static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;
    DTypeId id = SS_UINT32;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed", 
            NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumInputPorts(S, 0);

    ssSetNumOutputPorts(S, 1);
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

    // BM list output
    ssSetOutputPortDataType( S, 0, id );
    ssSetOutputPortWidth(S, 0, 1);

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
    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
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
    int   channel  = (int)mxGetPr(CHANNEL_ARG)[0];

    int   cardnum;
    uint32_t nmsgs = (uint32_t)mxGetPr(MSGCNT_ARG)[0];
    bmmsglist1553 *OPtr = (bmmsglist1553 *)ssGetOutputPortSignal(S,0);
    API_BM_MBUF *rcv_msg;
    int moduleId = (int)mxGetPr(MODULE_ID_ARG)[0];
  
    int  boardtype = (int)mxGetPr(BOARDTYPE_ARG)[0];
	uint32_t *barAddr;

    char   *boardname;
    int  maxchannel;
	
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


    // Check channel number to make sure its in range for the QPCI board
    if (channel < 1 || channel > maxchannel)
    {
        sprintf(msg, "bad channel %d for %s Bus Monitor with ID %d",
                channel, boardname, moduleId);
        ssSetErrorStatus(S, msg);
        return;
    } 

    channel = channel - 1 + CHANNEL_1;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bm: Failed to retrieve module from registry in ModelStart\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    barAddr = (uint32_t*)mod_info->custom_data;
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO672_BM, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "%s bm: Block not registered\n", boardname);
        ssSetErrorStatus(S, msg);
        return;
    }

    cardnum = xpcQPCIInit( (uintptr_t)barAddr, channel );
    if( cardnum == -1 )
    {
        sprintf( msg, "%s: Too many channels already initialized\n", boardname );
        ssSetErrorStatus( S, msg );
        return;
    }
    
    pIO672_block = (sg_IO672_block_t*)malloc(sizeof(sg_IO672_block_t));
    pIO672_block->cardnum = cardnum;
    block_info->custom_data = pIO672_block;

    rcv_msg = (API_BM_MBUF *)malloc( nmsgs*sizeof( API_BM_MBUF ) );
    if( rcv_msg == NULL )
    {
        sprintf( msg, "Unable to allocate space for %d BM messages", nmsgs );
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block->bm_msg = rcv_msg;

    //OPtr->token = (uint32_t)'1553';
	memcpy(OPtr,"1553",4);
    OPtr->nmsgs = nmsgs;
    //OPtr->ptrlow = (uint32_t)rcv_msg;  // 32 bit only
    //OPtr->ptrhigh = 0;
	
    OPtr->ptrlow = (uint32_t)((uint64_t)rcv_msg & 0xffffffff);
    OPtr->ptrhigh = (uint32_t)(((uint64_t)rcv_msg >> 32) & 0xffffffff);

#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    BT_INT      status;
    BT_UINT     cardnum;
    API_BM_MBUF *rcv_msg;
    int       nmsgs = (int)mxGetPr(MSGCNT_ARG)[0];
    BT_UINT     count = 0;
    bmmsglist1553 *OPtr = (bmmsglist1553 *)ssGetOutputPortSignal(S,0);
    int      i;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bm: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_BM, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 bm: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;
    rcv_msg = pIO672_block->bm_msg;

    // Perform low level fetch of BM messages from the board
    BM_MsgReadBlock( cardnum );
    
    for( i = 0 ; i < nmsgs ; i++ )
    {
        rcv_msg[i].messno = -1;  // mark all messages as cleared
    }

    // Fill in the first entry in rcv_msg.  Need to loop to pick up all.
    //status = BusTools_BM_ReadLastMessageBlock( cardnum, -1, -1, -1, &count, rcv_msg );
    //status = BusTools_BM_ReadNextMessage( cardnum, 1, -1, -1, -1, rcv_msg );
    status = BusTools_BM_MessageReadBlock( cardnum, rcv_msg, nmsgs, 0, &count );

    // Skip the timeout condition!  That just means a message wasn't pending.
    if( (status != API_BM_READ_TIMEOUT)
     && (status != API_SUCCESS)
     && (status != API_BM_READ_NODATA) )
        CHECK(status, BM_ReadNextMessage ); 

    //SG_PRINTF(INFO, "%d ", count );
//SG_PRINTF(INFO, "BM: cardnum %d, nmsgs %d, count %d\n", cardnum, nmsgs, count );
    //OPtr[3] = count;  // The number returned from the read.
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    API_BM_MBUF *rcv_msg;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 bm: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_BM, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 bm: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    rcv_msg = pIO672_block->bm_msg;

    free(rcv_msg);
    free(pIO672_block);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO672_BM, (uintptr_t)S);
    
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
