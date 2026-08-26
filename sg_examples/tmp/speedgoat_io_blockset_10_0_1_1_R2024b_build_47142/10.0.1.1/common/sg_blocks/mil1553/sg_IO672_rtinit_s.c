//  
// condor1553rtinit.c - xPC Target non-inlined S-function driver for the 
// Condor Engineering QPCI-1553 Initialize block
// Copyright 2005-2013 The MathWorks, Inc.


// This block is for per-remote terminal initialization

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_rtinit_s

#include "sg_IO672.h"

#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          15
#define BOARDTYPE_ARG     ssGetSFcnParam(S, 0)
#define RT_ARG            ssGetSFcnParam(S, 1)
#define ENABLEA_ARG       ssGetSFcnParam(S, 2)
#define ENABLEB_ARG       ssGetSFcnParam(S, 3)
#define STATUS_ARG        ssGetSFcnParam(S, 4)
#define BIT_ARG           ssGetSFcnParam(S, 5)
#define ITF_ARG           ssGetSFcnParam(S, 6)
#define TSUBS_ARG         ssGetSFcnParam(S, 7)
#define TLENGTHS_ARG      ssGetSFcnParam(S, 8)
#define RSUBS_ARG         ssGetSFcnParam(S, 9)
#define RLENGTHS_ARG      ssGetSFcnParam(S, 10)
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 11) // seconds
#define EN_BUS_A_ARG      ssGetSFcnParam(S, 12)
#define EN_BUS_B_ARG      ssGetSFcnParam(S, 13)
#define MODULE_ID_ARG     ssGetSFcnParam(S, 14)

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

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed", 
            NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (((int)mxGetPr(EN_BUS_A_ARG)[0] == 1) && ((int)mxGetPr(EN_BUS_B_ARG)[0] == 1))
    {
        if(!ssSetNumInputPorts(S, 3))return;
        ssSetInputPortWidth(S, 1, 1);
        ssSetInputPortRequiredContiguous( S, 1, 1); 
        ssSetInputPortDirectFeedThrough(S, 1, 1);
        ssSetInputPortWidth(S, 2, 1);
        ssSetInputPortRequiredContiguous( S, 2, 1); 
        ssSetInputPortDirectFeedThrough(S, 2, 1);
    }
    else if (((int)mxGetPr(EN_BUS_A_ARG)[0] == 1) || ((int)mxGetPr(EN_BUS_B_ARG)[0] == 1))
    {
        if(!ssSetNumInputPorts(S, 2))return;
        ssSetInputPortWidth(S, 1, 1);
        ssSetInputPortRequiredContiguous( S, 1, 1); 
        ssSetInputPortDirectFeedThrough(S, 1, 1);
    }
    else
    {
        if(!ssSetNumInputPorts(S, 1))return;
    }
    ssSetInputPortWidth(S, 0, 4);
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 1) )return;
    ssSetOutputPortWidth(S, 0, 4);

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
    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0) {
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
    int   channel;

    int  boardtype = (int)mxGetPr(BOARDTYPE_ARG)[0];
	uint32_t *barAddr;

    char   *boardname;
    int  maxchannel;

    int   i, status;
    int   cardnum;

	sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;

    API_RT_ABUF   abuf;
    API_RT_CBUF   cbuf;
	int moduleId = (int)mxGetPr(MODULE_ID_ARG)[0];


    int rt      = (int)mxGetPr(RT_ARG)[0];  // zero based Remote Terminal number
    int enableA = (int)mxGetPr(ENABLEA_ARG)[0];
    int enableB = (int)mxGetPr(ENABLEB_ARG)[0];
    int statusval = (int)mxGetPr(STATUS_ARG)[0];
    int bit     = (int)mxGetPr(BIT_ARG)[0];
    int itf     = (int)mxGetPr(ITF_ARG)[0]; // Inhibit Terminal Flag
    int ntsubs  = mxGetN(TSUBS_ARG);
    int nrsubs  = mxGetN(RSUBS_ARG);
    int sub;
    uint32_t   fulllegal[32];

    int *IPtr = (int*)ssGetInputPortSignal(S,0);
    int *OPtr = ssGetOutputPortSignal(S,0);

    //if( IPtr[0] != 'RT53' )
	if( memcmp(IPtr,"RT53",4) != 0)
    {
        sprintf(msg, "RT Init not connected to a board Init block." );
        ssSetErrorStatus(S, msg);
        return;     // Not connected to an init block.
    }

    //NOTE: In/Output ports are not accessible in sg_ModelLoad!
    channel = IPtr[1];
    //pciBus  = IPtr[2];    //Not used anymore
    //pciSlot = IPtr[3];

    OPtr[0] = IPtr[0];
    OPtr[1] = IPtr[1];
    //OPtr[2] = IPtr[2];
    //OPtr[3] = IPtr[3];

    //SG_PRINTF(INFO, "From INIT, channel = %d, bus = %d, slot = %d\n",
    //       channel, pciBus, pciSlot );

    // We got bus, slot and channel from the INIT block through the input port.

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
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
    if (mod_info == NULL)
    {
        sprintf(msg, "%s rtinit: Failed to retrieve module from registry in ModelLoad\n", boardname);
        ssSetErrorStatus(S, msg);
        return;
    }
    barAddr = (uint32_t*)mod_info->custom_data;
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO672_RTINIT, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "%s rtinit: Block not registered\n", boardname);
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
    
    SG_PRINTF(DEBUG, "rtinit base %p, chan %d => num %d\n", barAddr, channel, cardnum );

    // Stop all of the RTs on this board, configure, then start again.
    // Will do this for each RT we configure.
    status = BusTools_RT_StartStop(cardnum, STOP);
    CHECK(status, RT_StartStop ); 

    // Compute the contents of the ABUF and CBUF here and write them.

    abuf.enable_a = enableA;
    abuf.enable_b = enableB;
    abuf.inhibit_term_flag = itf;
    abuf.status = statusval;
    abuf.bit_word = bit;
    status = BusTools_RT_AbufWrite( cardnum, rt, &abuf );
    CHECK( status, BusTools_RT_AbufWrite );

    if( ntsubs == 0 && nrsubs == 0 )
    {
        // The number of legal length words was checked in mask init.  It is the same
        // as the number of sub addresses if we got this far.
        sprintf( msg, "No subaddresses enabled for RT %d.", rt );
        ssSetErrorStatus( S, msg );
        return;
    }

    // Need to loop through all 32 sub addresses.  If a sub address
    // is specifed from the block, then use that legal count value,
    // else set the legal count value to 0.
    for( i = 0 ; i < 32 ; i++ )
        fulllegal[i] = 0;  // Preset to no legal message counts
    if( ntsubs > 0 )
    {
//SG_PRINTF(INFO, "trans: ");
        for( i = 0 ; i < ntsubs ; i++ )
        {
            sub = (int)mxGetPr(TSUBS_ARG)[i];
            fulllegal[sub] = (uint32_t)mxGetPr(TLENGTHS_ARG)[i];
//SG_PRINTF(INFO, "%x(%d) ", fulllegal[sub], sub );
        }
//SG_PRINTF(INFO, "\n");
    }
    for( i = 0 ; i < 32 ; i++ )
    {
        cbuf.legal_wordcount = fulllegal[i];
        status = BusTools_RT_CbufWrite( cardnum, rt, i, 1, 1, &cbuf );
//SG_PRINTF(INFO, "TR: status = %d, rt=%d, sub=%d\n", status, rt, i );
        CHECK( status, CbufWrite_Transmit );
    }

    for( i = 0 ; i < 32 ; i++ )
        fulllegal[i] = 0;  // Preset to no legal message counts
    if( nrsubs > 0 )
    {
//SG_PRINTF(INFO, "rec: ");
        for( i = 0 ; i < nrsubs ; i++ )
        {
            sub = (int)mxGetPr(RSUBS_ARG)[i];
            fulllegal[sub] = (uint32_t)mxGetPr(RLENGTHS_ARG)[i];
//SG_PRINTF(INFO, "%x(%d) ", fulllegal[sub], sub );
        }
//SG_PRINTF(INFO, "\n");
    }
    for( i = 0 ; i < 32 ; i++ )
    {
        cbuf.legal_wordcount = fulllegal[i];
        status = BusTools_RT_CbufWrite( cardnum, rt, i, 0, 1, &cbuf );
//SG_PRINTF(INFO, "Rcv: status = %d, rt=%d, sub=%d\n", status, rt, i );
        CHECK( status, CbufWrite_Receive );
    }

    // Start RT
    status = BusTools_RT_StartStop(cardnum, START);
    CHECK(status, RT_StartStop );

#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    API_RT_ABUF abuf = {0};
    int status, rt = (int)mxGetPr(RT_ARG)[0];
    BT_UINT cardnum;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 rtinit: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_RTINIT, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 rtinit: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;

    if ((int)mxGetPr(EN_BUS_A_ARG)[0] == 1)
    {
        double enable = *(double*)ssGetInputPortSignal(S, 1);

        if (enable > 0)
        {
            abuf.enable_a = 1;
        }
        else
        {
            abuf.enable_a = 0;
        }
    }
    
    if ((int)mxGetPr(EN_BUS_B_ARG)[0] == 1)
    {
        double enable;
        if ((int)mxGetPr(EN_BUS_A_ARG)[0] == 1)
        {
            enable = *(double*)ssGetInputPortSignal(S, 2);
        }
        else
        {
            enable = *(double*)ssGetInputPortSignal(S, 1);
        }
        if (enable > 0)
        {
            abuf.enable_b = 1;
        }
        else
        {
            abuf.enable_b = 0;
        }
    }
    
    if (((int)mxGetPr(EN_BUS_A_ARG)[0] == 1) || ((int)mxGetPr(EN_BUS_B_ARG)[0] == 1))
    {
        status = BusTools_RT_AbufWrite(cardnum, rt, &abuf);
        CHECK(status, BusTools_RT_AbufWrite);
    }

#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    BT_UINT  cardnum;
    int status;
	sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 rtinit: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_RTINIT, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 rtinit: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;

    // Stop BC 
    status = BusTools_BC_StartStop(cardnum, STOP);

    xpcQPCIClose( cardnum );
    status = BusTools_API_Close( cardnum );
    if( status != API_SUCCESS && status == API_BUSTOOLS_NOTINITED )
    {
        // already closed, quit quietly.
    }
    else
    {
        CHECK( status, API_Close );
    }
    
    free(pIO672_block);
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO672_RTINIT, (uintptr_t)S);

#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
