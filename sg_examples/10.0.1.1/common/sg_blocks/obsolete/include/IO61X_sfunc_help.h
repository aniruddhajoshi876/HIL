#ifndef __SG_IO61X_SFUNC_HELP_H__
#define __SG_IO61X_SFUNC_HELP_H__

// S-Function Header Files
#include "simstruc.h"

#define MDL_START

// declarations to be defined in S-Function.
static void sg_ModelStart(SimStruct* S);
//static void sg_ModelStep(SimStruct* S);
static void sg_ModelLoad(SimStruct* S);
static void sg_ModelStop(SimStruct* S);



#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include "../../common/libsg/sg_module_types.h"

static void mdlStart(SimStruct* S)
{
    sg_ModelStart(S);
}

static void mdlTerminate(SimStruct* S)
{
    sg_ModelStop(S);
}

#else   
// Simulink Realtime Headers  for mxArray and mxGetPr are in C:\Program Files\MATLAB\R2019b\rtw\c\src\rt_matrx.h
#include "rt_matrx.h"

//  XPC Header Files
#include "../../common/libsg/sg_common.h"
#include "../../common/libsg/sg_module_types.h"
#include "../../common/libsg/sg_printf.h"

// Standard Header Files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  Driver Header Files
#include "IO61X_iConcurrentExecution.h"

#ifndef _MSC_BUILD 
//_QNX_
#include "StartCallbackAPI.h"
#endif

#ifdef _MSC_BUILD  // ON Time

static void mdlStart(SimStruct* S)
{
    if (sg_isModelInit())
        sg_ModelLoad(S);
    else
        sg_ModelStart(S);
}

static void mdlTerminate(SimStruct* S)
{    
    if(!sg_isModelInit()){
		sg_ModelStop(S);
	}
}

#else  // QNX

static void mdlStart(SimStruct * S)
{
    sg_ModelLoad(S);	
    slrealtime::StartCallbackService::registerCB(std::bind(sg_ModelStart, S));
}
static void mdlTerminate(SimStruct* S)
{
    sg_ModelStop(S);
}

#endif

#endif 

/*
*   This function creates and checks the parameters of the S-Function block.
*/
static int SetAndCheckSFunctionParams(uint8_T isTunable, SimStruct* S, int qty_param)
{
    int i = 0;

    ssSetNumSFcnParams(S, qty_param);

    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return 0;
    }

    for (i = 0; i < qty_param; i++)
    {
        ssSetSFcnParamTunable(S, i, isTunable);
    }

    return 1;
}

/*
*   This function creates the input ports of the S-Function block.
*/
static void CreateSFunctionInputPorts(int quantityOfInputs, SimStruct* S)
{
        ssSetNumInputPorts(S, quantityOfInputs);
}

/*
*   This funciton checks the created input ports of the S-Function block.
*/
static int CheckSFunctionInputPorts(int quantityOfInputs, SimStruct* S)
{
    if (quantityOfInputs != ssGetNumInputPorts(S))
    {
        return 0;
    }

    return 1;
}

/*
*   This function set the properties of the singe input port.
*/
static void SetSFunctionInputPortProperties(int_T portNumber, uint32_T portWidth, /* enum BuiltInDTypeId*/ int dataType, boolean_T isRequiredContiguous,
    boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct* S)
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

/*
*   This function creates the output ports of the S-Function block.
*/
static void CreateSFunctionOutputPorts(int quantityOfOutputs, SimStruct* S)
{
    ssSetNumOutputPorts(S, quantityOfOutputs);
}

/*
*   This funciton checks the created output ports of the S-Function block.
*/
static int CheckSFunctionOutputPorts(int quantityOfOutputs, SimStruct* S)
{
    if (quantityOfOutputs != ssGetNumOutputPorts(S))
    {
        return 0;
    }

    return 1;
}

/*
*   This function set the properties of the singe output port.
*/
static void SetSFunctionOutputPortProperties(int portNumber, int32_T portWidth, /* BuiltInDTypeId*/ int dataType, uint8_T propertySelection, SimStruct* S)
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

#endif // __SG_IO61X_SFUNC_HELP_H__
