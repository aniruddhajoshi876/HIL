#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO203_setup_s

#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>

#include "sg_io203.h"

#include 	"simstruc.h" 

#ifndef MATLAB_MEX_FILE
    #include "sg_printf.h"
    #include "sg_common.h"
    #include "sg_module_registry.h"
    #include "sg_module_types.h"
    static const int MOD_TYPE = SG_MODULE_TYPE_IO203;
#else
    #include "mex.h"
#endif

#define SG_HAS_MDL_EXIT //Causes sg_ModelExit() to be called upon process exit
#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#include "sg_callback.h"

/* Input Arguments */
#define NUMBER_OF_ARGS          (9)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define LOWER_DIRECTION_ARG     ssGetSFcnParam(S,1)
#define LOWER_RESET_ARG         ssGetSFcnParam(S,2)
#define LOWER_VALUE_ARG         ssGetSFcnParam(S,3)
#define UPPER_DIRECTION_ARG     ssGetSFcnParam(S,4)
#define UPPER_RESET_ARG         ssGetSFcnParam(S,5)
#define UPPER_VALUE_ARG         ssGetSFcnParam(S,6)
#define OUTPUT_LEVEL_ARG        ssGetSFcnParam(S,7)
#define MODULE_ID_ARG       	ssGetSFcnParam(S,8)

#define NO_I_WORKS              (0)
#define NO_R_WORKS              (0)
#define NO_P_WORKS              (0)

#define THRESHOLD               0.5

static char_T msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint16_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    /* Block has no input ports */
    if (!ssSetNumInputPorts(S, 0)) return;

    if (!ssSetNumOutputPorts(S, 0)) return;
  
    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for( i = 0 ; i < NUMBER_OF_ARGS ; i++ )
    {
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    	ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}


#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S)
{
    sg_PCIDevice pciinfo;
    uint_T i;
    uint32_T outEnLo,outEnHi;
    uint32_T outLo, outHi;
    int_T bus, slot;
    Io203_Device_t *dev = NULL;
    uint32_t moduleID;
    sg_mod_info *mod_info = NULL;
    
    if (mxGetN(SLOT_ARG) == 1)
    {
        bus = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }

    moduleID = ((uint32_t)mxGetPr(MODULE_ID_ARG)[0]);

    // Check if another block has already registered for the same module.
    // This is required for referenced model support:
    // Multiple Setup blocks for the same module might be present in different models.
    // This is to avoid doing the same configuration again if another block has done it already
    if (sg_module_get_single(MOD_TYPE, moduleID))
    {
        SG_PRINTF(DEBUG,"%s (ID %d) Setup: Module already registered!\n", DEVNAME, moduleID); 
        return;
    }
    SG_PRINTF(DEBUG,"%s (ID %d) Setup: Registering module\n", DEVNAME, moduleID);

    // Register I/O module & allocate memory for custom data structure
    mod_info = sg_module_register(MOD_TYPE, moduleID);
    dev = (Io203_Device_t*)malloc(sizeof(Io203_Device_t));
    mod_info->custom_data = (void*)dev;

    // look for the PCI-Device
    if (sg_findPciDevice(&pciinfo, DEVNAME, (uint16_T)VENDORID, (uint16_T)DEVICEID, SG_NO_SUB, SG_NO_SUB, (int)moduleID, bus, slot))
    {
        ssSetErrorStatus(S, pSgErrorStr);
        return;
    }
    
    dev->pciinfo = pciinfo;

    dev->ioaddress0 = (volatile uint32_t *)sg_mapMemory(&pciinfo, 0);
    dev->ioaddress2 = (volatile uint32_t *)sg_mapMemory(&pciinfo, 2);
    
    //SG_PRINTF(INFO, "Base Address: 0x%x\n", dev->ioaddress2);
    
    // set to little endianess
    dev->ioaddress0[0x0a]= dev->ioaddress0[0x0a] & 0xfeffffff;
    
    // set lower direction
    outLo = 0x00;
    outHi = 0x00;

    dev->ioaddress2[0x00] = 0x0;
    outEnLo= 0x00;
    for (i=0; i<32; i++) {
        if (mxGetPr(LOWER_DIRECTION_ARG)[i]>=THRESHOLD) {
            outEnLo|= 1<<i;
        }
    }
    dev->ioaddress2[0x04]= outEnLo;
    dev->outEnLo = outEnLo;
    
    // set upper direction
    dev->ioaddress2[0x01] = 0x0;
    outEnHi= 0x00;
    for (i=0; i<32; i++) {
        if (mxGetPr(UPPER_DIRECTION_ARG)[i]>=THRESHOLD) {
            outEnHi|= 1<<i;
        }
    }
    dev->ioaddress2[0x05]= outEnHi;
    dev->outEnHi = outEnHi;
    
    //Set init values
    for (i=0 ; i<32 ; i++) {            
        if (mxGetPr(LOWER_VALUE_ARG)[i]>=THRESHOLD) {
            outLo |= 1<<i;
        }
        if (mxGetPr(UPPER_VALUE_ARG)[i]>=THRESHOLD) {
            outHi |= 1<<i;
        }
    }
    if((uint32_T)mxGetPr(OUTPUT_LEVEL_ARG)[0] == 1)
    {
        dev->ioaddress2[0x04]= outEnLo & (~outLo);
        dev->ioaddress2[0x05]= outEnHi & (~outHi);
    }
    else
    {
        dev->ioaddress2[0x00]= outLo;
        dev->ioaddress2[0x01]= outHi;
    }
}

static void sg_ModelStart(SimStruct *S)
{
}

static void sg_ModelStep(SimStruct* S)
{
}

static void sg_ModelStop(SimStruct* S)
{   
    uint16_T i;
    uint32_T outLo, outHi;
    uint32_T outEnLo, outEnHi;
    Io203_Device_t *dev = NULL;
    uint32_t moduleID;

    moduleID = ((uint32_t)mxGetPr(MODULE_ID_ARG)[0]);

    // Get data structure from global data base
    dev = (Io203_Device_t*)sg_module_get_custom_data(MOD_TYPE, moduleID);
    if(!dev)
    {
        sprintf(msg, "%s (ID %d): Failed to retrieve module from registry in Setup ModelStop\n",
            DEVNAME, moduleID);
        ssSetErrorStatus(S, msg);
        return;
    }

    outEnLo = dev->outEnLo;
    outEnHi = dev->outEnHi;
    
    //Set reset values
    outLo = dev->ioaddress2[0x00];
    outHi = dev->ioaddress2[0x01];
    for (i=0 ; i<32 ; i++) {
        if((uint32_T)mxGetPr(LOWER_RESET_ARG)[i] ) {              
            if (mxGetPr(LOWER_VALUE_ARG)[i]>=THRESHOLD) {
                outLo |= 1<<i;
            } else {
                outLo &= ~(1<<i); 
            }
        }
        if( (uint32_T)mxGetPr(UPPER_RESET_ARG)[i] ) {              
            if (mxGetPr(UPPER_VALUE_ARG)[i]>=THRESHOLD) {
                outHi |= 1<<i;
            } else {
                outHi &= ~(1<<i); 
            }
        }
    }
    if((uint32_T)mxGetPr(OUTPUT_LEVEL_ARG)[0] == 1)
    {
        dev->ioaddress2[0x04]= outEnLo & (~outLo);
        dev->ioaddress2[0x05]= outEnHi & (~outHi);
    }
    else
    {
        dev->ioaddress2[0x00]= outLo;
        dev->ioaddress2[0x01]= outHi;
    }
}

static void sg_ModelExit(SimStruct *S)
{
    // Retrieve state from module registry
    int moduleID = (int)mxGetPr(MODULE_ID_ARG)[0];  
    SG_PRINTF(DEBUG, "%s (ID %d) Setup: sg_ModelExit\n", DEVNAME, moduleID);  
    Io203_Device_t *dev = (Io203_Device_t*)sg_module_get_custom_data(MOD_TYPE, moduleID);
    
    // If state exists, clean up
    if(dev)
    {
        SG_PRINTF(DEBUG, "%s (ID %d) Setup: Free device struct\n", DEVNAME, moduleID);  
        free(dev);

        SG_PRINTF(DEBUG, "%s (ID %d) Setup: Unregister module\n", DEVNAME, moduleID);
        sg_module_unregister(MOD_TYPE, moduleID);
    }
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
