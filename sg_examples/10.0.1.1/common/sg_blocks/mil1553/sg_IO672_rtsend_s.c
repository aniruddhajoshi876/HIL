//  
// condor1553rtsend.c - xPC Target non-inlined S-function driver for the 
// Condor Engineering QPCI-1553 Bus Controller block
// Copyright 2005-2014 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_rtsend_s

#include "sg_IO672.h"

#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          8
#define BOARDTYPE_ARG     ssGetSFcnParam(S, 0)
#define CHANNEL_ARG       ssGetSFcnParam(S, 1) // 1-4 for QPCI-1553
#define TERM_ARG          ssGetSFcnParam(S, 2) // terminal address
#define SUB_ARG           ssGetSFcnParam(S, 3) // sub address
#define SENDCOUNT_ARG     ssGetSFcnParam(S, 4) // word count
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 5) // seconds
#define PCI_SLOT_ARG      ssGetSFcnParam(S, 6) // integer
#define MODULE_ID_ARG     ssGetSFcnParam(S, 7)

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (0)

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;
    int inwidth;

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

    inwidth = (int)mxGetPr( SENDCOUNT_ARG )[0];
    if( inwidth < 1 ) inwidth = 1;
    if( inwidth > 32 )
    {
        sprintf( msg, "Send count is limited to 32 for 1553 Bus Controller");
        ssSetErrorStatus( S, msg );
        return;
    }
    ssSetInputPortRequiredContiguous( S, 0, 1 ); // data port
    ssSetInputPortWidth(S, 0, inwidth);
    ssSetInputPortDataType( S, 0, DYNAMICALLY_TYPED );
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 0) )return;

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

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType( SimStruct *S, int port, DTypeId id )
{
    if( id == SS_INT16 || id == SS_UINT16 || id == SS_INT32 || id == SS_UINT32 )
        ssSetInputPortDataType( S, port, id );
    else
    {
        sprintf( msg, "Input must be either 16 or 32 bit integers." );
        ssSetErrorStatus(S,msg);
        return;
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
    int chan  = (int) mxGetPr(CHANNEL_ARG)[0];
    BT_UINT cardnum = 0;
	int moduleId = (int)mxGetPr(MODULE_ID_ARG)[0];

    int boardtype = (int)mxGetPr(BOARDTYPE_ARG)[0];
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

    if (chan < 1 || chan > maxchannel )
    {
        sprintf(msg, "bad channel %d for %s Remote Terminal with ID %d",
                chan, boardname, moduleId);
        ssSetErrorStatus(S, msg);
        return;
    }
    chan = chan - 1 + CHANNEL_1;  // Condor library uses 0 based channel number

	//Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 rtsend: Failed to retrieve module from registry in ModelStart\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    barAddr = (uint32_t*)mod_info->custom_data;
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO672_RTSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "%s rtsend: Block not registered\n", boardname);
        ssSetErrorStatus(S, msg);
        return;
    }

    cardnum = xpcQPCIInit( (uintptr_t)barAddr, chan );
    if( cardnum == -1 )
    {
        sprintf( msg, "%s: Too many channels already initialized\n", boardname );
        ssSetErrorStatus( S, msg );
        return;
    }
    
    pIO672_block = (sg_IO672_block_t*)malloc(sizeof(sg_IO672_block_t));
    pIO672_block->cardnum = cardnum;
    block_info->custom_data = pIO672_block;

//SG_PRINTF(INFO, "base %p, chan %d => num %d\n", barAddr, chan, cardnum );
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    BT_UINT   cardnum;
    int     i, status;
    void *DPtr     = (void *)ssGetInputPortSignal(S,0);  // Data
    DTypeId inTypeData   = ssGetInputPortDataType( S, 0 );
    int sendcount = (int)mxGetPr(SENDCOUNT_ARG)[0];
    int *lptr = (int *)DPtr;  // if input is 32 bit
    short *sptr = (short *)DPtr;  // if input is 16 bit
    API_RT_MBUF_WRITE data;
    int rt = (int)mxGetPr(TERM_ARG)[0];
    int sub = (int)mxGetPr(SUB_ARG)[0];
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 rtsend: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_RTSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 rtsend: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;
    
    
    for( i = 0 ; i < sendcount ; i++ )
    {
        switch( inTypeData )
        {
          case SS_INT16:
          case SS_UINT16:
            data.mess_data[i] = (unsigned short)sptr[i];
            break;
          case SS_INT32:
          case SS_UINT32:
            data.mess_data[i] = (unsigned short)lptr[i];
            break;
        }
    }
    data.enable = 0;  // No interrupt bits (yet)
    data.error_inj_id = 0; // No error injection (yet)

    status = BusTools_RT_MessageWrite( cardnum, rt, sub, 1, 0, &data );
    CHECK(status, RT_MessageWrite );
#if 0  // Enable this for debugging
    {
        API_CHANNEL_STATUS *chanstat;
        status = BusTools_GetChannelStatus( cardnum, &chanstat );
        SG_PRINTF(INFO, "send: func return %x\n", status);
        SG_PRINTF(INFO, "channel status: %x\n", (int)chanstat );
    }
#endif
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 rtsend: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_RTSEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 rtsend: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    
    free(pIO672_block);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO672_RTSEND, (uintptr_t)S);
    
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
