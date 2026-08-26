/*
*   File       : sg_esd_setup_v1_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO691/IO602 setup module.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*/

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO602_IO691_setup_s

#include "simstruc.h"

#ifndef MATLAB_MEX_FILE
#include "../common/libsg/sg_common.h"
#else
#include "mex.h"
#endif

#include "../common/libsg/sg_callback.h"
#include "../common/libsg/sg_printf.h"

#include <exception>
#include "include/IO602_IO691_SFunctionInterface.h"

#define QTY_PARAM 3         // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0      // Quantity of the input ports of the S-Function block.
#define QTY_OUT_PORTS 0     // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 0        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 1        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#define pMODULE_INIT_VALUES mxGetPr(ssGetSFcnParam(S, 0))
#define pMODULE_INIT_STRUCT mxGetPr(ssGetSFcnParam(S, 1))
#define pMODULE_TERM_STRUCT mxGetPr(ssGetSFcnParam(S, 2))

static char_T s_ErrorMsg[256];      // String for the error message of the S-Function.

static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S);
static void CreateSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S);
static int CheckSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S);
static void SetSFunctionInputPortProperties(int32_T portNumber, uint32_T portWidth, BuiltInDTypeId dataType, boolean_T isRequiredContiguous, boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S);
static void CreateSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S);
static int CheckSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S);
static void SetSFunctionOutputPortProperties(int32_T portNumber, int32_T portWidth, BuiltInDTypeId dataType, uint8_T propertySelection, SimStruct *S);

void mdlInitializeSizes(SimStruct *S)
{
    // Set and check parameters
    if (0 == SetAndCheckSFunctionParames(0, S))
    {
        sprintf(s_ErrorMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }

    // Set input and output ports
    CreateSFunctionInputPorts(0, S);
    CreateSFunctionOutputPorts(0, S);

    // Set RWork vector
    ssSetNumRWork(S, QTY_R_WORK);

    // Set IWork vector
    ssSetNumIWork(S, QTY_I_WORK);

    // Set PWork vector
    ssSetNumPWork(S, QTY_P_WORK);

    // Default settings
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    // Specify the sim state compliance to be same as a built-in block
    // UNCOMMENT: ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    // Set options
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);     // see SS_OPTION in simstruct.h
}

static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S)
{
    int i = 0;

    ssSetNumSFcnParams(S, QTY_PARAM);

    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return 0;
    }

    for (i = 0; i < QTY_PARAM; i++)
    {
        ssSetSFcnParamTunable(S, i, isTunable);
    }

    return 1;
}

static void CreateSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S)
{
    // Create input ports
    if (0 == quantityOfInputs)
    {
        ssSetNumInputPorts(S, QTY_IN_PORTS);
    }
    else
    {
        ssSetNumInputPorts(S, quantityOfInputs);
    }
}

static int CheckSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S)
{
    if (0 == quantityOfInputs)
    {
        if (QTY_IN_PORTS != ssGetNumInputPorts(S))
        {
            return 0;
        }
    }
    else
    {
        if (quantityOfInputs != ssGetNumInputPorts(S))
        {
            return 0;
        }
    }

    return 1;
}

static void SetSFunctionInputPortProperties(int32_T portNumber, uint32_T portWidth, BuiltInDTypeId dataType, boolean_T isRequiredContiguous,
                                            boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetInputPortDataType(S, portNumber, dataType);
    }
    else if (3 == propertySelection)
    {
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
    }
    else if (4 == propertySelection)
    {
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
    else
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
        ssSetInputPortDataType(S, portNumber, dataType);
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
}

static void CreateSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S)
{
    // Create input ports
    if (0 == quantityOfOutputs)
    {
        ssSetNumOutputPorts(S, QTY_OUT_PORTS);
    }
    else
    {
        ssSetNumOutputPorts(S, quantityOfOutputs);
    }
}

static int CheckSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S)
{
    if (0 == quantityOfOutputs)
    {
        if (QTY_OUT_PORTS != ssGetNumOutputPorts(S))
        {
            return 0;
        }
    }
    else
    {
        if (quantityOfOutputs != ssGetNumOutputPorts(S))
        {
            return 0;
        }
    }

    return 1;
}

static void SetSFunctionOutputPortProperties(int32_T portNumber, int32_T portWidth, BuiltInDTypeId dataType, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
    else
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void sg_ModelLoad(SimStruct *S)
{
    ssSetPWorkValue(S, 0, malloc(1));
}

static void sg_ModelStart (SimStruct* S)
{
    const SetupInitValues* pInitValues = reinterpret_cast<const SetupInitValues*>(pMODULE_INIT_VALUES);
    try
    {
#ifndef MATLAB_MEX_FILE
        // if this Module was registered by a different Setup S-Function instance, don't try initialization again.
        sg::esdSFcn::Setup_ModelStart( \
            *pInitValues \
            ,pMODULE_INIT_STRUCT \
        );
#endif
    }
    catch (const std::exception &e)
    {
        strncpy(s_ErrorMsg, e.what(), sizeof(s_ErrorMsg));
        s_ErrorMsg[sizeof(s_ErrorMsg) - 1] = 0;
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }

    char name[50];
    sprintf(name, "IO691_%d_CAN_Setup_s\0", (uint8_t)pInitValues->mid.Id);
}

static void sg_ModelStep(SimStruct* S) { ; }

static void sg_ModelStop (SimStruct* S)
{
	const SetupInitValues* pInitValues = reinterpret_cast<const SetupInitValues*>(pMODULE_INIT_VALUES);
 	// this is executed once, when model stops, not on application unload. For the latter, consider destructors of global objects.
	try {
#ifndef MATLAB_MEX_FILE
        sg::esdSFcn::Setup_ModelStop (*pInitValues, pMODULE_TERM_STRUCT);
#endif
	}
	catch (const std::exception &e)
	{
#ifndef MATLAB_MEX_FILE
		SG_PRINTF(ERROR, "exception in Setup S-Function: %s \n", e.what());
#endif
        strncpy(s_ErrorMsg, e.what(), sizeof(s_ErrorMsg));
        s_ErrorMsg[sizeof(s_ErrorMsg) - 1] = 0;
        // Note, this is not working properly for mdlTerminate! 
        ssSetErrorStatus(S, s_ErrorMsg);  
        return;
    }
    free (ssGetPWorkValue(S, 0));
}

#include "../common/libsg/sg_sfcn_glue.h"
