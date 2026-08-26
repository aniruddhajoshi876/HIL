#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO930_ctrlrel_s

#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#include 		"../common/libsg/sg_common.h"
#endif

#define DEVNAME "Speedgoat IO930"
#define VENDORID 0x10b5
#define DEVICEID 0x9050
#define SUBVENDORID 0x1761
#define SUBDEVICEID 0x1002

/* Input Arguments */
#define NUMBER_OF_ARGS          (6)
#define MODULE_ID_ARG           ssGetSFcnParam(S,0)
#define CHANNEL_ARG             ssGetSFcnParam(S,1)
#define INIT_VAL_ARG            ssGetSFcnParam(S,2)
#define RESET_VAL_ARG           ssGetSFcnParam(S,3)
#define SAMP_TIME_ARG           ssGetSFcnParam(S,4)
#define SLOT_ARG                ssGetSFcnParam(S,5)

#define NO_R_WORKS              (0)
#define NO_I_WORKS              (65)    // 1..64 correspond to ch 1..64
#define NO_P_WORKS              (0)

#define BASE_ADDR_I_IND         (0)

#define THRESHOLD               0.5

// Control register (CR)
#define EEPROMCS0_BIT           0x00000001      // Chip Select
#define LCLK_BIT                0x00000002      // Clock
#define LDATA_BIT               0x00000004      // Data
#define LSTRB1_BIT              0x00000008      // Strobe 1
#define LOE_BIT                 0x00000010      // Output enable

// Output map table
int_T output_map[64] =           
{
    16,24,32,40,48,56,17,25,33,41,
    49,57,18,26,34,42,50,58,19,27,
    35,43,51,59,23,31,39,47,55,63,
    22,30,38,46,54,62,21,29,37,45,
    53,61,20,28,36,44,52,60,10, 8,
    11, 9,14,12,15,13, 2, 0, 3, 1,
    6, 4, 7, 5
} ;

static char_T msg[256];

void writeRelays(SimStruct *S, int_T vector[64]);

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    
    ssSetNumOutputPorts(S, 0);
    ssSetNumInputPorts(S, (int)mxGetN(CHANNEL_ARG));    // Number of input ports
    
    for ( i = 0 ; i < (int)mxGetN(CHANNEL_ARG) ; i++ )
    {
        ssSetInputPortWidth(S, i, 1);
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous( S, i, 1 );
    }

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
    if (mxGetPr(SAMP_TIME_ARG)[0]==-1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;	
	int_T bus, slot;
    uint32_T moduleID;
    volatile uint32_T *cr;      // Control Register address
    int_T i;
     	//PCI slot
	if (mxGetN(SLOT_ARG) == 1)
    {
        bus  = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus  = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }	
	
	//Get PCI device
	moduleID = ((int_T)mxGetPr(MODULE_ID_ARG)[0]);
    if(sg_findPciDevice(&pciinfo,DEVNAME, VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, moduleID, bus,slot) != 0)
    {
        ssSetErrorStatus(S, pSgErrorStr);
        return;
    }
	
	// Memory map bar to user space virtual address
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void*)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE );

    cr=(volatile uint32_T *)pciinfo.VirtAddress[2];            // Control Register address assignment
	
    ssSetIWorkValue(S, BASE_ADDR_I_IND, (uint32_T)cr);  // Save CR address to integer work vector
    
    for(i=1;i<=64;i++)
        ssSetIWorkValue(S, i, 0);  // Init integer work vector
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE

    real_T *channel_val_ptr;        // pointer to the channel value
    uint_T channel_ind;             // channel index
    int_T num_channels;             // number of enabled channels
    uint_T relay_ctrl;              // relay state (on=1, off=0)
    int_T i;
    int_T loop;

    int_T write_vector[64] = {0};    // Output vector

    num_channels = mxGetN(CHANNEL_ARG); // Get number of enabled channels
    
    for (i = 0 ; i < num_channels; i++ ) 
    {
            channel_ind = (uint16_T)mxGetPr(CHANNEL_ARG)[i]-1;  // Get channel index
            channel_val_ptr = (real_T *)ssGetInputPortRealSignal(S,i);  //Get channel value
            
            // Relay state
            if (channel_val_ptr[0] >= THRESHOLD)    // activate relay
                relay_ctrl = 1; 
            
            else                                    // desactivate relay
                relay_ctrl = 0;
            
            ssSetIWorkValue(S, i+1, relay_ctrl);   // Memorize relay state
            
            loop = output_map[channel_ind];         // Output bit assignment
            write_vector[loop] = relay_ctrl;            
    }
    
    writeRelays(S, write_vector);                    // Write output vector

#endif
}

static void mdlTerminate(SimStruct *S)
{   
#ifndef MATLAB_MEX_FILE
    int_T num_channels;
    int_T i;
    int_T channel_ind;
    int_T loop;
    int_T write_vector[64] = {0};    // Output vector
    int_T channel_val; 
    int_T reset_val;
    
    num_channels = mxGetN(CHANNEL_ARG);                         // Get number of enabled channels

    /* MODEL INITIALIZATIONS */
    if(xpcIsModelInit()) 
    {
        
        for (i = 0 ; i < num_channels; i++ ) 
        {
            channel_ind = (uint16_T)mxGetPr(CHANNEL_ARG)[i]-1;  // Get channel index
            channel_val = (uint16_T)mxGetPr(INIT_VAL_ARG)[i];      // Get channel init value

            ssSetIWorkValue(S, i+1, channel_val);              // Memorize relay state
            
            loop = output_map[channel_ind];                     // Output bit assignment
            write_vector[loop] = channel_val;            
        }

        writeRelays(S, write_vector);                           // Write output vector
    }
    
    /* MODEL TERMINATE */
    else
    {
        for (i = 0 ; i < num_channels; i++ ) 
        {
            reset_val = (int_T)mxGetPr(RESET_VAL_ARG)[i];

            channel_ind = (uint16_T)mxGetPr(CHANNEL_ARG)[i]-1;      // Get channel index
            
            if (reset_val == 1)
                channel_val = (int_T)mxGetPr(INIT_VAL_ARG)[i];      // Get channel init value
            else 
                channel_val = ssGetIWorkValue(S, i+1);   // Memorize relay state
            
            loop = output_map[channel_ind];         // Output bit assignment
            write_vector[loop] = channel_val;            
        }
    
        writeRelays(S, write_vector);                    // Write output vector
    }

#endif
}

void writeRelays(SimStruct *S, int_T vector[64])
{
    uint32_T base = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    volatile uint32_T *cr;          // Control Register
    
    int_T i;
    int_T temp;
    
    cr=(void *) base;                   // Assign Control Register address
    
    for (i=0;i<64;i++)
    {
        temp = vector[i];                     // Value to write in loop bit i
        
        // Write in CR: CS=1, LOE=1, LDATA=temp, others = 0
        cr[0x00] = EEPROMCS0_BIT | LOE_BIT | (temp << 2);
        
        // Write in CR: CS=1, LOE=1, LDATA=temp, LCLK=1, others = 0
        cr[0x00] = EEPROMCS0_BIT | LOE_BIT | (temp << 2) | LCLK_BIT;
        //xpcBusyWait(0.0001);
    }
    
    // Write in CR: CS=1, LOE=1, LSTRB1=1 (transfer data to output), others = 0
    cr[0x00] = EEPROMCS0_BIT | LOE_BIT | LSTRB1_BIT;
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif


