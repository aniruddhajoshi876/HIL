#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO203_read_s

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

#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#include "sg_callback.h"

/* Input Arguments */
#define NUMBER_OF_ARGS          (5)
#define PORTTYPE_ARG            ssGetSFcnParam(S,0)
#define GROUP_ARG               ssGetSFcnParam(S,1)
#define SAMP_TIME_ARG           ssGetSFcnParam(S,2)
#define SLOT_ARG                ssGetSFcnParam(S,3)
#define MODULE_ID_ARG       	ssGetSFcnParam(S,4)

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

    if (!ssSetNumInputPorts(S, 0)) return;
    
    switch ((uint8_T)mxGetPr(PORTTYPE_ARG)[0]) {
        case 1:
            if (!ssSetNumOutputPorts(S, 32)) return;
            for ( i = 0 ; i < 32; i++ ) {
                ssSetOutputPortWidth(S, i, 1);
            }
            break;
        case 2:
            if (!ssSetNumOutputPorts(S, 32)) return;
            for ( i = 0 ; i < 32; i++ ) {
                ssSetOutputPortWidth(S, i, 1);
                ssSetOutputPortDataType(S, i, SS_BOOLEAN);
            }
            break;
        case 3:
            if (!ssSetNumOutputPorts(S, 1)) return;
            ssSetOutputPortWidth(S, 0, 32);
            break;
        case 4:
            if (!ssSetNumOutputPorts(S, 1)) return;
            ssSetOutputPortWidth(S, 0, 32);
            ssSetOutputPortDataType(S, 0, SS_BOOLEAN);
            break;            
        case 5:
            if (!ssSetNumOutputPorts(S, 1)) return;
            ssSetOutputPortWidth(S, 0, 1);
            ssSetOutputPortDataType(S, 0, SS_UINT32);
            break;               
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

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
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


#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
}       


static void sg_ModelStep(SimStruct *S)
{
    uint32_T i, input;
    real_T  *y1;
    boolean_T  *y2;
    uint32_T *y3;
    Io203_Device_t *dev = NULL;
    uint32_t moduleID;

    moduleID = ((uint32_t)mxGetPr(MODULE_ID_ARG)[0]);

    // Get data structure from global data base
    dev = (Io203_Device_t*)sg_module_get_custom_data(MOD_TYPE, moduleID);
    if(!dev)
    {
        sprintf(msg, "%s (ID %d): Failed to retrieve module from registry in Read ModelStep\n",
            DEVNAME, moduleID);
        ssSetErrorStatus(S, msg);
        return;
    }

    
    if (((uint8_T)mxGetPr(GROUP_ARG)[0])==1) {
        input= dev->ioaddress2[0x02];
    } else {
        input= dev->ioaddress2[0x03];
    }
    
    switch ((uint8_T)mxGetPr(PORTTYPE_ARG)[0]) {
        case 1:
            for (i=0; i<32; i++ ) {
                y1= (real_T *)ssGetOutputPortSignal(S,i);
                y1[0]= (real_T)((input >> i) & 0x1);
            }
            break;
        case 2:
            for (i=0; i<32; i++ ) {
                y2 = (boolean_T *)ssGetOutputPortSignal(S,i);
                y2[0] = (boolean_T)((input >> i) & 0x1);
            }
            break;
        case 3:
            y1= (real_T *)ssGetOutputPortSignal(S,0);
            for (i=0; i<32; i++ ) {
                y1[i] = (real_T)((input >> i) & 0x1);
            }
            break;
        case 4:
            y2= (boolean_T *)ssGetOutputPortSignal(S,0);
            for (i=0; i<32; i++ ) {
                y2[i] = (boolean_T)((input >> i) & 0x1);
            }
            break;
        case 5:
            y3= (uint32_T *)ssGetOutputPortSignal(S,0);
            y3[0]= (uint32_T)input;
            break;               
    }
}

static void sg_ModelStop(SimStruct *S)
{   
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
