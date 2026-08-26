#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO920_ctrlres_s

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

#define DEVNAME "Speedgoat IO920"
#define VENDORID 0x10b5
#define DEVICEID 0x9050
#define SUBVENDORID 0x1761
#define SUBDEVICEID 0x101A

/* Input Arguments */
#define NUMBER_OF_ARGS          (6)
#define MODULE_ID_ARG           ssGetSFcnParam(S,0)
#define CHANNEL_ARG             ssGetSFcnParam(S,1)
#define INIT_VAL_ARG            ssGetSFcnParam(S,2)
#define RESET_VAL_ARG           ssGetSFcnParam(S,3)
#define SAMP_TIME_ARG           ssGetSFcnParam(S,4)
#define SLOT_ARG                ssGetSFcnParam(S,5)

#define NO_R_WORKS              (0)
#define NO_I_WORKS              (11)    // 1..10 correspond to resistor 1..10
#define NO_P_WORKS              (0)

#define BASE_ADDR_I_IND         (0)

// Control register (CR)
#define EEPROMCS0_BIT           0x00000001      // Chip Select
#define LCLK_BIT                0x00000002      // Clock
#define LDATA_BIT               0x00000004      // Data
#define LSTRB1_BIT              0x00000008      // Strobe 1
#define LOE_BIT                 0x00000010      // Output enable
#define LSTRB2_BIT              0x00000020      // Strobe 2          

// Output map table from resistor 1 bit 0 to resistor 5 bit 11
int_T output_map_loop1[80] =           
{
    79,78,77,75,74,73,72,76,64,65,66,67,        // resistor 1
    63,62,61,60,59,58,57,56,48,49,51,50,        // resistor 2
    47,46,45,44,43,42,41,40,32,33,35,34,        // resistor 3
    27,22,18,16,10, 8,12, 2,26,23,19,17,        // resistor 4
    28,25,20,21,24,29,30,31, 0, 6,14,13         // resistor 5
} ;

// Output map table from resistor 6 bit 0 to resistor 10 bit 11
int_T output_map_loop2[80] =           
{
    67,66,65,64,71,70,69,68,79,78,77,76,        // resistor 6
    48,49,50,51,52,53,54,55,63,62,61,60,        // resistor 7
    32,33,34,35,36,37,38,39,47,46,45,44,        // resistor 8
    16,17,18,19,20,21,22,23,31,30,29,28,        // resistor 9
    0 , 1, 2, 3, 4, 5, 6, 7,15,14,13,12         // resistor 10 
} ;

static char_T msg[256];

//void writeRelays(SimStruct *S, int_T vector[64]);
void decToBin12 (int_T dec_value, int_T bin_value[12]);
void prepareVectors(int_T channel_ind, int_T channel_val, int_T vector1[80], int_T vector2[80]);
void writeResistors(SimStruct *S, int_T vector1[80], int_T vector2[80]);

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
    
    for(i=1;i<=10;i++)
        ssSetIWorkValue(S, i, 0);  // Init integer work vector
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE

    real_T *channel_val_ptr;        // pointer to the channel value
    uint_T channel_ind;             // channel index
    int_T num_channels;             // number of enabled channels
    int_T vector1[80] = {0};        // Output vector 1
    int_T vector2[80] = {0};        // Output vector 1
    int_T i;

    num_channels = mxGetN(CHANNEL_ARG); // Get number of enabled channels

    for (i = 0 ; i < num_channels; i++ ) 
    {
            channel_ind = (uint16_T)mxGetPr(CHANNEL_ARG)[i]-1;          // Get channel index
            channel_val_ptr = (real_T *)ssGetInputPortRealSignal(S,i);  // Get channel value
            
            ssSetIWorkValue(S, i+1, (int_T)channel_val_ptr[0]);   // Memorize relay state
            
            prepareVectors(channel_ind, (int_T)channel_val_ptr[0], vector1, vector2);                 
    }
    
    writeResistors(S, vector1, vector2);

#endif
}

static void mdlTerminate(SimStruct *S)
{   
#ifndef MATLAB_MEX_FILE
    int_T num_channels;
    int_T i;
    int_T channel_ind;
    int_T channel_val;
    int_T reset_val;
    int_T vector1[80] = {0};    // Output vector 1
    int_T vector2[80] = {0};    // Output vector 1
    
    num_channels = mxGetN(CHANNEL_ARG);                         // Get number of enabled channels

    /* MODEL INITIALIZATIONS */
    if(xpcIsModelInit()) 
    {

        for (i = 0 ; i < num_channels; i++ ) 
        {
            channel_ind = (uint16_T)mxGetPr(CHANNEL_ARG)[i]-1;      // Get channel index
            channel_val = (uint16_T)mxGetPr(INIT_VAL_ARG)[i];       // Get channel init value

            ssSetIWorkValue(S, i+1, channel_val);                   // Memorize resistor value
            
            prepareVectors(channel_ind, channel_val, vector1, vector2);      
        }
        
        writeResistors(S, vector1, vector2);
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
                channel_val = ssGetIWorkValue(S, i+1);              // Memorize resistor value
            
            prepareVectors(channel_ind, channel_val, vector1, vector2);   
        }
    
        writeResistors(S, vector1, vector2);                        // Write output vector
    }

#endif
}

void prepareVectors(int_T channel_ind, int_T channel_val, int_T vector1[80], int_T vector2[80])
{   
    int_T bin_value[12] = {0};
    int_T bit;
    int_T loop;
    
    if (channel_ind < 5)
    {
//         printf("Channel %i: %i \n", channel_ind, channel_val);
        decToBin12(channel_val, bin_value);

        for(bit = 0; bit < 12; bit++)
        {
            loop = output_map_loop1[channel_ind*12+bit];
            vector1[loop] = bin_value[bit];
//               printf("Vector1[%i]: %i \n", loop, bin_value[bit]);
        }
    }
    
    else
    {
//          printf("Channel %i: %i \n", channel_ind, channel_val);
        decToBin12(channel_val, bin_value);

        for(bit = 0; bit < 12; bit++)
        {
            loop = output_map_loop2[(channel_ind-5)*12+bit];
            vector2[loop] = bin_value[bit];
//              printf("Vector2[%i]: %i \n", loop, bin_value[bit]);
        }
    }
        
}

void decToBin12 (int_T dec_value, int_T bin_value[12])
{
    int_T i;
    
    for (i=0; i<12;i++)   
    {
        bin_value[i]= dec_value%2;
        dec_value = dec_value/2;
        if (dec_value == 0)
            break;
    }
}

void writeResistors(SimStruct *S, int_T vector1[80], int_T vector2[80])
{
    uint32_T base = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    volatile uint32_T *cr;          // Control Register
    
    int_T i;
    int_T temp;
    
    cr=(void *) base;                   // Assign Control Register address

    for (i=0;i<80;i++)  // Loop 1
    {
        if (vector1[i] == 1)
            temp = 0;
        else if (vector1[i] == 0)
            temp = 1;
        else
            printf("error\n");
        
        // Write in CR: CS=1, LOE=1, LDATA=temp, others = 0
        cr[0x00] = LOE_BIT | (temp << 2);
        // Write in CR: CS=1, LOE=1, LDATA=temp, LCLK=1, others = 0
        cr[0x00] = LOE_BIT | (temp << 2) | LCLK_BIT;
        cr[0x00] = LOE_BIT | (temp << 2);
    }

    // Write in CR: CS=1, LOE=1, LSTRB1=1 (transfer data to output), others = 0
    cr[0x00] = LOE_BIT | LSTRB1_BIT;

    for (i=0;i<80;i++)  // Loop 2
    {
        if (vector2[i] == 1)
            temp = 0;
        else if (vector2[i] == 0)
            temp = 1;
        else
            printf("error\n");

        // Write in CR: CS=1, LOE=1, LDATA=temp, others = 0
        cr[0x00] = LOE_BIT | (temp << 2);

        // Write in CR: CS=1, LOE=1, LDATA=temp, LCLK=1, others = 0
        cr[0x00] = LOE_BIT | (temp << 2) | LCLK_BIT;
        cr[0x00] = LOE_BIT | (temp << 2);
    }

    // Write in CR: CS=1, LOE=1, LSTRB2=1 (transfer data to output), others = 0
    cr[0x00] = LOE_BIT | LSTRB2_BIT;
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif


