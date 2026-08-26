#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO821_readinterrupt_s

#include <stdint.h>

#ifdef 	 MATLAB_MEX_FILE
	#include "mex.h"
#else
    #include "IO821.h"
#endif

#include "sg_printf.h"
#include "sg_callback.h"

#define GET_SFUNC_PARAM(idx) (mxGetPr(ssGetSFcnParam(S, idx)))

enum SetupParams
{
    SAMPLETIME_ARG,
    MODULE_ID_ARG,
    NUMBER_OF_ARGS
};

enum IntegerWorkVector
{
    NO_I_WORKS
};

enum RealWorkVector
{
    NO_R_WORKS
};

enum PointerWorkVector
{
    NO_P_WORKS
};

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n"
                "%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 0)) return;

    if (!ssSetNumOutputPorts(S, 1)) return;
    
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_UINT16);
    
    ssSetNumSampleTimes(S, 1);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    for( i = 0 ; i < NUMBER_OF_ARGS; i++ )
    {
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );
}


static void mdlInitializeSampleTimes(SimStruct *S)
{

    if (GET_SFUNC_PARAM(SAMPLETIME_ARG)[0]==-1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
        //ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
    }
    else {
        ssSetSampleTime(S, 0, GET_SFUNC_PARAM(SAMPLETIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }

}

static void sg_ModelLoad(SimStruct *S)
{

}

static void sg_ModelStart(SimStruct *S)
{

}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	uint16_t* out;
	
	out = ssGetOutputPortSignal(S, 0);
	*out = (uint16_t)IO821_readInterrupt();
	//SG_PRINTF(INFO,"ISR status %X\n",*out);

#endif
}

static void sg_ModelStop(SimStruct *S)
{

}

#include "sg_sfcn_glue.h"   // Code generation glue

