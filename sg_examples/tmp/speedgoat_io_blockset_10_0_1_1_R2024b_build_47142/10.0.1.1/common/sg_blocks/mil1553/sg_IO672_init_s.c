//  
/*
Adapted from condor1553init.c
Supports only the QPM-1553 (PMC) variant

 I/O module  Channels	Single/Multi-function
----------------------------------------------
 IO672-1-SF     1              single
 IO672-1-MF     1              multi
 IO672-2-SF     2              single
 IO672-2-MF     2              multi
 IO672-4-SF     4              single
 IO672-4-MF     4              multi

 */

// This block is for per-channel initialization for a bus controller

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_init_s

#include "sg_IO672.h"

#define SG_HAS_MDL_EXIT //Causes sg_ModelExit() to be called upon process exit
#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          19                    //
#define BOARDTYPE_ARG     ssGetSFcnParam(S, 0)  // boardtype
#define CHANNEL_ARG       ssGetSFcnParam(S, 1)  // channel
#define COUPLING_ARG      ssGetSFcnParam(S, 2)  // coupling
#define VOLTAGE_ARG       ssGetSFcnParam(S, 3)  // voltage
#define LOOPBACK_ARG      ssGetSFcnParam(S, 4)  // loopback
#define INITBC_ARG        ssGetSFcnParam(S, 5)  // initbc
#define NBCBUFFS_ARG      ssGetSFcnParam(S, 6)  // nbcbuffs
#define RETRY_ARG         ssGetSFcnParam(S, 7)  // retryenabled
#define NRTIMEOUT_ARG     ssGetSFcnParam(S, 8)  // nrtimeout
#define LRTIMEOUT_ARG     ssGetSFcnParam(S, 9)  // lrtimeout
#define INITBM_ARG        ssGetSFcnParam(S, 10) // initbm
#define MONA_ARG          ssGetSFcnParam(S, 11) // mona
#define MONB_ARG          ssGetSFcnParam(S, 12) // monb
#define NBMBUFFS_ARG      ssGetSFcnParam(S, 13) // nbmbuffs
#define INITRT_ARG        ssGetSFcnParam(S, 14) // initrt
#define BROADCAST_ARG     ssGetSFcnParam(S, 15) // broadcast
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 16) // sampleTime
#define PCI_SLOT_ARG      ssGetSFcnParam(S, 17) // slot
#define MODULE_ID_ARG     ssGetSFcnParam(S, 18)

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

    if( !ssSetNumInputPorts(S, 0) ) return;

    if( !ssSetNumOutputPorts(S, 1) ) return;
    ssSetOutputPortWidth(S, 0, 4);

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
#ifndef MATLAB_MEX_FILE
    int   channel  = (int)mxGetPr(CHANNEL_ARG)[0];

    int   pciSlot;
    int   pciBus;
    int   i, status;
    unsigned int  flag;
    int   cardnum;
    int   initbm = (int)mxGetPr(INITBM_ARG)[0];
    int   initbc = (int)mxGetPr(INITBC_ARG)[0];
    int   initrt = (int)mxGetPr(INITRT_ARG)[0];
    int   loopback = (int)mxGetPr(LOOPBACK_ARG)[0];
    uint32_t coupling = (uint32_t)mxGetPr(COUPLING_ARG)[0] - 1;
    double  voltage = mxGetPr(VOLTAGE_ARG)[0];
    uint32_t ivolt = (uint32_t)(voltage * 100);  // for Bustools API

    sg_PCIDevice     pDev;
    int moduleId = (int)mxGetPr(MODULE_ID_ARG)[0];


    // BM init variables
    int   mon_a = (int)mxGetPr(MONA_ARG)[0];
    int   mon_b = (int)mxGetPr(MONB_ARG)[0];
    int   nbmbuffs = (int)mxGetPr(NBMBUFFS_ARG)[0];
    int   allocated;

    // BC_Init variables
    int   bcIntEnable = 0;
    // Allocate one extra BC buffer since we don't use the first (0) one.
    // That one is the dummy periodic list and is a noop message.
    // Also have to add one more on the back end since I need to finish
    // with a noop to make sure the last real message is finished.
    int   nbcbuffs      = (int)mxGetPr(NBCBUFFS_ARG)[0] + 2;
    int   bcRetryEnable = 0;
    int   noRespUs      = (int)mxGetPr(NRTIMEOUT_ARG)[0];
    int   lateRespUs    = (int)mxGetPr(LRTIMEOUT_ARG)[0];
    int   minorFrameUs  = 1000000;  // hard coded 1 second for the NOP buffer
    API_BC_MBUF bc_msg;  // Single NOP buffer for periodic execution
//SG_PRINTF(INFO, "voltage=%i\n",voltage);
//SG_PRINTF(INFO, "coupling=%i\n",coupling);
//SG_PRINTF(INFO, "channel=%i\n",channel);
//SG_PRINTF(INFO, "initbm = %i initbc = %i initrt = %i \n",initbm,initbc,initrt);
//SG_PRINTF(INFO, "mon_a = %i mon_b = %i nbmbuffs = %i\n",mon_a,mon_b,nbmbuffs);

    int   boardtype    = (int)mxGetPr(BOARDTYPE_ARG)[0];
    int   devicetoken  = QPM1553;
    int   haveloopback = 0;

    char    *boardname;
    int   maxchannel;
    int   multifunction;
	
	uint32_t *barAddr;
	sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;
    
    if((int)mxGetPr(RETRY_ARG)[0] == 1)
    {
        bcRetryEnable = 0x000FFFFF; //These bits enable the conditons for BC_CONTROL_RETRY retries in the API_BC_MBUF.
    }

    switch( boardtype )
    {
        case 1: boardname = "IO672-1-SF"; maxchannel = 1; multifunction = 0; break;
        case 2: boardname = "IO672-1-MF"; maxchannel = 1; multifunction = 1; break;
        case 3: boardname = "IO672-2-SF"; maxchannel = 2; multifunction = 0; break;
        case 4: boardname = "IO672-2-MF"; maxchannel = 2; multifunction = 1; break;
        case 5: boardname = "IO672-4-SF"; maxchannel = 4; multifunction = 0; break;
        case 6: boardname = "IO672-4-MF"; maxchannel = 4; multifunction = 1; break;

        default:
            sprintf(msg, "Unknown IO672 variant\n");
            ssSetErrorStatus(S, msg);
            return;
    }

    // map memory for the given bus/slot/chan combination if no other
    // block has yet done so.
    if( mxGetN(PCI_SLOT_ARG) == 1 )
    {
        pciBus = 0;
        pciSlot = (int) mxGetPr(PCI_SLOT_ARG)[0];
    } else
    {
        pciBus = (int) mxGetPr(PCI_SLOT_ARG)[0];
        pciSlot = (int) mxGetPr(PCI_SLOT_ARG)[1];
    }

    if (channel < 1 || channel > maxchannel)
    {
        sprintf(msg, "bad channel %d for %s Bus Controller at slot [%d,%d]",
                channel, boardname,
                pciBus, pciSlot );
        ssSetErrorStatus(S, msg);
        return;
    }
    channel = channel - 1 + CHANNEL_1;
	
	// Check if another block has already registered for the same module
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
    if (mod_info == NULL)
    {
        //attach pci dev
        if (sg_findPciDevice(&pDev, boardname, VENDOR_ID, DEVICE_ID, -1, -1, moduleId, pciBus, pciSlot) != 0)
        {
            ssSetErrorStatus(S, pSgErrorStr);
            return;
        }
        
        mod_info = sg_module_register(SG_MODULE_TYPE_IO672, (uint32_t)moduleId);
        SG_PRINTF(DEBUG,"Setup: Register %s module\n",boardname);
        
        // The QPCI1553 board only uses BAR0.  Only map that address.
        barAddr = (uint32_t*)sg_mapMemory(&pDev, 0);
        mod_info->custom_data = barAddr;
    }
    else
    {
        barAddr = (uint32_t*)mod_info->custom_data;
    }
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO672_INIT, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "%s init: Block not registered\n", boardname);
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

    SG_PRINTF(DEBUG, "init base %p, chan %d => num %d\n", barAddr, channel, cardnum );


    flag = API_SW_INTERRUPT | API_B_MODE;

//    SG_PRINTF(INFO, "Initializing %s with\n",boardname);
//    SG_PRINTF(INFO, "  cardnum      = 0x%08X\n", cardnum);
//    SG_PRINTF(INFO, "  base_address = 0x%08X\n", barAddr);
//    SG_PRINTF(INFO, "  ioaddr       = 0\n");
//    SG_PRINTF(INFO, "  flag         = API_SW_INTERRUPT | API_B_MODE (0x%08X)\n", flag);
//    SG_PRINTF(INFO, "  platform     = PLATFORM_PC\n");
//    SG_PRINTF(INFO, "  boardType    = 0x%08X (-> devicetoken)\n", devicetoken);
//    SG_PRINTF(INFO, "  carrier      = NATIVE\n");
//    SG_PRINTF(INFO, "  slot         = 0x%08X\n", channel);
//    SG_PRINTF(INFO, "  mapping      = CARRIER_MAP_DEFAULT\n");
    
    // For xPC Target, the base address is passed in directly from this
    // level.  The doc discusses passing in a device ID for Windows.
    // It makes a difference in the routines in lowlevel.c where the
    // second arg to this call is converted to a virtual address to
    // access the board.  For xPC Target, the mapping is just 1-1.
    status = BusTools_API_InitExtended(cardnum,  // represents board+channel
                                       (uintptr_t)barAddr, // mapped addr
                                       0,   // ioaddr, none for any board
                                       &flag,
                                       PLATFORM_PC,
                                       devicetoken,
                                       NATIVE,
                                       channel,
                                       CARRIER_MAP_DEFAULT); // relevant to IP carrier
    
    CHECK(status, API_InitExtended);
    if(status)
    {
        sprintf(msg, "API_InitExtended failed: %s.",BusToolsError(status) );
        ssSetErrorStatus(S, msg);
        return;
    }

    //SG_PRINTF(INFO, "Back from init extended\n");
    //SG_PRINTF(INFO, "BusTools_SetVoltage()\n "
    //       "   cardnum = %i\n"
    //       "   ivolt   = %i\n"
    //       "   coupling= %i\n", cardnum, ivolt, coupling);
    status = BusTools_SetVoltage( cardnum, ivolt, coupling );
    if( status != API_HARDWARE_NOSUPPORT )
        CHECK(status, SetVoltage);
   
    //SG_PRINTF(INFO, "INIT: mona = %d, monb = %d\n", mon_a, mon_b );

    // BM init must precede BC and RT init, always do it!
    status = BusTools_BM_Init(cardnum, mon_a, mon_b);
    CHECK(status, BM_Init); 

    status = BusTools_SetInternalBus(cardnum, 0);
    CHECK(status, SetInternalBus); 

    if( haveloopback == 1 )
    {
        int lb;
        //SG_PRINTF(INFO, "BC: loopback = %d\n", loopback );
        if( loopback == 1 )
            lb = TEST_BUS_ENABLE;
        else
            lb = TEST_BUS_DISABLE;
        // Set Test bus state from block param checkbox.
        status = BusTools_SetTestBus( cardnum, lb );
        CHECK(status, SetTestBus);
    }
 
    if(!multifunction && (initbm + initrt + initbc != 1))
    {
        sprintf( msg, "%s: Only one function supported per channel.\n", boardname );
        ssSetErrorStatus(S, msg);
        return;
    }
   
    if( initbm == 1 )
    {
        // Allow lots of room for collecting BM messages
        status = BusTools_BM_MessageAlloc( cardnum, nbmbuffs, (unsigned int*)&allocated, 0 ); // flag );
        CHECK(status, BM_MessageAlloc);
        if( allocated < nbmbuffs )
        {
            sprintf( msg, "BM unable to allocate the \nrequested (%d) buffers", nbmbuffs );
            ssSetErrorStatus(S, msg);
            return;
        }

        // Start BM 
        status = BusTools_BM_StartStop(cardnum, START);
        CHECK(status, BM_StartStop ); 
    }
 
    if( initrt == 1 )
    {
        int bcast = (int)mxGetPr( BROADCAST_ARG )[0];
        status = BusTools_SetBroadcast( cardnum, bcast );
        CHECK( status, SetBroadcast );

        status = BusTools_RT_Init( cardnum, 0); // second param must be 0
        CHECK(status, RT_Init); 

        // Start RT
        status = BusTools_RT_StartStop(cardnum, START);
        CHECK(status, RT_StartStop ); 
    }

    if( initbc == 1 )
    {
        status = BusTools_BC_Init(cardnum,
                                  REL_GAP,
                                  bcIntEnable,
                                  bcRetryEnable,
                                  noRespUs,
                                  lateRespUs,
                                  minorFrameUs,
                                  NUM_DATA_BUFS);  // 2 buffers
        CHECK(status, BC_Init); 

        status = BusTools_BC_MessageAlloc( cardnum, nbcbuffs );
        CHECK(status, BC_MessageAlloc); 

        // Initialize the first BC buffer on the board, just to get it started
        bc_msg.messno = 0;
        bc_msg.control = BC_CONTROL_NOP;

        bc_msg.control |= BC_CONTROL_MFRAME_BEG;
        bc_msg.messno_next = (BT_U16BIT)(0);

        bc_msg.mess_command1.rtaddr   = 0;
        bc_msg.mess_command1.subaddr  = 0;
        bc_msg.mess_command1.tran_rec = 0;
        bc_msg.mess_command1.wcount   = 0;
    
        bc_msg.mess_command2.rtaddr   = 0;  // not RT-RT so command2 is 0
        bc_msg.mess_command2.subaddr  = 0;
        bc_msg.mess_command2.tran_rec = 0;
        bc_msg.mess_command2.wcount   = 0;

        bc_msg.errorid = 0;
        bc_msg.gap_time = 5;
        bc_msg.status  = 0;

        // Clear the data area
        for( i = 0 ; i < 32 ; i++ )
            bc_msg.data[0][i] = 0;

        status = BusTools_BC_MessageWrite( cardnum, 0, &bc_msg );
        CHECK( status, BusTools_BC_MessageWrite );

    }
    status = BusTools_TimeTagInit( cardnum );
    CHECK( status, BusTools_BC_TimeTagInit );

    SG_PRINTF(INFO, "%s: Initialized, chan %d\n", boardname, channel+1);

#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    int channel = (int)mxGetPr(CHANNEL_ARG)[0];
    int *OPtr = ssGetOutputPortSignal(S,0);
    
    channel = channel - 1 + CHANNEL_1;
    
    memcpy(OPtr,"RT53",4);  //NOTE: Output ports are not accessible in sg_ModelLoad!
    OPtr[1] = channel;
    //OPtr[2] = pciBus; //Not used anymore
    //OPtr[3] = pciSlot;
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    BT_UINT cardnum;
    int status;
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    sg_IO672_block_t *pIO672_block;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    if (mod_info == NULL)
    {
        sprintf(msg, "IO672 init: Failed to retrieve module from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO672_INIT, (uintptr_t)S);
    if (block_info == NULL)
    {
        sprintf(msg, "IO672 init: Failed to retrieve block from registry in ModelStop\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    pIO672_block = (sg_IO672_block_t*)block_info->custom_data;
    cardnum = pIO672_block->cardnum;
    SG_PRINTF(DEBUG, "cardnum %d\n", cardnum);

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
    sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO672_INIT, (uintptr_t)S);
    
#endif
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    //Unregister
    sg_module_unregister(SG_MODULE_TYPE_IO672, (uint32_t)mxGetPr(MODULE_ID_ARG)[0]);
    SG_PRINTF(DEBUG,"Unregister Module\n");
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
