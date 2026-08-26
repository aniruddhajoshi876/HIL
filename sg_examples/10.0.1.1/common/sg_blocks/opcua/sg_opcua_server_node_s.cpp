#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_opcua_server_node_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "opcua_def.h"

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "opcua_server_block.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace opcua;
#endif

/* Defines */
#define SERVER_ID_ARG   	(uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_TYPE_ARG           (uint8_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define READ_OP_ARG           (boolean_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define WRITE_OP_ARG          (boolean_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define READ_ACCESS_ARG           (boolean_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define WRITE_ACCESS_ARG          (boolean_T)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define PARENT_ID_ARG                          ssGetSFcnParam(S, 6)
#define HAS_PARENT_ARG            (boolean_T)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define NAMESPACE_ARG               (uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define NODE_ID_TYPE_ARG               (uint8_T)mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NODE_ID_ARG                        ssGetSFcnParam(S, 10)
#define BROWSE_NAME_ARG                        ssGetSFcnParam(S, 11)
#define DISPLAY_NAME_ARG                        ssGetSFcnParam(S, 12)
#define DESCRIPTION_ARG                        ssGetSFcnParam(S, 13)
#define INIT_VALUE_ARG                        ssGetSFcnParam(S, 14)
#define SAMPLE_TIME_ARG               mxGetPr(ssGetSFcnParam(S, 15))[0]
#define EXTENDED_ARG            (boolean_T)mxGetPr(ssGetSFcnParam(S, 16))[0]
#define FORCE_VECTOR_ARG              (boolean_T)mxGetPr(ssGetSFcnParam(S, 17))[0]
#define NUMBER_OF_ARGS											18

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    int d = 0;
    DimsInfo_T DimInfo = {0};

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (!mxIsEmpty(INIT_VALUE_ARG))
    {

        ssSetSFcnParamTunable(S, 14, 1);
    }

    if (NODE_TYPE_ARG == OPCUA_NODE_TYPE_VARIABLE)
    {
		/* Get Init Value parameter dimensions */
		/* According to the help documentation, mxGetNumberOfDimensions always returns at least 2.
		 * Even scalar and one-dimensional arrays are described by two dimensions.
		 */
		DimInfo.width = mxGetNumberOfElements(INIT_VALUE_ARG);
		DimInfo.numDims = mxGetNumberOfDimensions(INIT_VALUE_ARG);
		DimInfo.dims = (int*)mxGetDimensions(INIT_VALUE_ARG);

		if (WRITE_OP_ARG)
		{
            if (EXTENDED_ARG)
            {
			    ssSetNumInputPorts(S, 2);
            }
            else
            {
                ssSetNumInputPorts(S, 1);
            }

			/* Check whether init values are specified */
			if (!mxIsEmpty(INIT_VALUE_ARG))
			{
                if ((DimInfo.numDims > 1) && (FORCE_VECTOR_ARG))
                {
                    if ((DimInfo.dims[0] == 1) || (DimInfo.dims[1] == 1))
                    {
                        DimInfo.numDims = 1;
                        d = mxGetNumberOfElements(INIT_VALUE_ARG);
                        DimInfo.dims = &d;
                    }
                }
                ssSetInputPortDimensionInfo(S, 0, &DimInfo);
                ssSetInputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
			}
			else
			{
				DimsInfo_T Dims = {0};
				Dims.width = DYNAMICALLY_SIZED;
				Dims.numDims = DYNAMICALLY_SIZED;
				ssSetInputPortDimensionInfo(S, 0, &Dims);
				ssSetInputPortDataType(S, 0, DYNAMICALLY_TYPED);
			}
			ssSetInputPortRequiredContiguous(S, 0, 1);
			ssSetInputPortDirectFeedThrough(S, 0, 1);

            if (EXTENDED_ARG)
            {
                ssSetInputPortDataType(S, 1, SS_BOOLEAN);
                ssSetInputPortWidth(S, 1, 1);
			    ssSetInputPortRequiredContiguous(S, 1, 1);
			    ssSetInputPortDirectFeedThrough(S, 1, 1);
            }
		}
		else
		{
			ssSetNumInputPorts(S, 0);
		}

		if(READ_OP_ARG)
		{
			ssSetNumOutputPorts(S, 1);

			/* Check whether init values are specified */
			if (!mxIsEmpty(INIT_VALUE_ARG))
			{
				ssSetOutputPortDimensionInfo(S, 0, &DimInfo);
				ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));

                if ((DimInfo.numDims > 1) && (FORCE_VECTOR_ARG))
                {
                    if ((DimInfo.dims[0] == 1) || (DimInfo.dims[1] == 1))
                    {
                        DimInfo.numDims = 1;
                        d = mxGetNumberOfElements(INIT_VALUE_ARG);
                        DimInfo.dims = &d;
                    }
                }
                ssSetOutputPortDimensionInfo(S, 0, &DimInfo);
                ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
			}
			else
			{
				ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
				ssSetOutputPortMatrixDimensions(S, 0, DYNAMICALLY_SIZED, DYNAMICALLY_SIZED);
				ssSetOutputPortDataType(S, 0, DYNAMICALLY_TYPED);
			}
		}
		else
		{
			ssSetNumOutputPorts(S, 0);
		}
    }
    else
    {
    	ssSetNumInputPorts(S, 0);
    	ssSetNumOutputPorts(S, 0);
    }


    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumDWork(S, 0);

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (SAMPLE_TIME_ARG == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct *S)
{
    if (!mxIsEmpty(INIT_VALUE_ARG))
    {
        char n[] = "InitValueRun\0";
        ssSetNumRunTimeParams(S, 1);
        ssRegDlgParamAsRunTimeParam(S, 14, 0, n, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
    }
}

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_INPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDimensionInfo(   SimStruct *S, int portIndex,
                                            const DimsInfo_T *dimsInfo) {

    ssSetInputPortDimensionInfo(S, portIndex, dimsInfo);

    if (READ_OP_ARG)
    {
        ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo);
    }
}
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_INPUT_PORT_DATA_TYPE
#if defined(MDL_SET_INPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDataType(SimStruct *S, int_T port, DTypeId id) {

    /* Same types for input and output */
    ssSetInputPortDataType(S, port, id);

    if (READ_OP_ARG)
    {
        ssSetOutputPortDataType(S, port, id);
    }
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex,
                                                   const DimsInfo_T *dimsInfo) {
    if (WRITE_OP_ARG)
    {
        /* Should be set by mdlSetInputPortDimensionInfo */
        sprintf(ErrMsg,  "Input port %i cannot inherit dimensions\n", portIndex);
        ssPrintf(ErrMsg);
    }
    else
    {
        ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo);
    }
}
#endif /* MDL_SET_OUTPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
#if defined(MDL_SET_OUTPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDataType(SimStruct *S, int_T port, DTypeId id) {

    if (WRITE_OP_ARG)
    {
        /* Should be set by mdlSetInputPortDataType */
        sprintf(ErrMsg,  "Input port %i cannot inherit data type\n", port);
        ssPrintf(ErrMsg);
    }
    else
    {
        ssSetOutputPortDataType(S, port, id);
    }
}
#endif /* MDL_SET_OUTPUT_PORT_DATA_TYPE */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetDefaultPortDimensionInfo(SimStruct *S) {

    /* If there is at least one unconnected input port,
     * mdlSetDefaultPortDimensionInfo is called only one time.
     * mdlSetDefaultPortDimensionInfo is called after
     * mdlSetInputPortDimensionInfo has been called for all
     * valid input ports */

    ssSetErrorStatus(S, "Cannot inherit data types\n");
    return;
}
#endif /* MDL_SET_DEFAULT_PORT_DIMENSION_INFO */

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) {}
static void sg_ModelStep(SimStruct *S) {}
static void sg_ModelStop(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct * S) {

    int32_T i = 0;
    uint16_T ServerId = SERVER_ID_ARG;
    uint8_T NodeType = NODE_TYPE_ARG;
    uint32_T UBID = 0;
    boolean_T ReadOp = READ_OP_ARG;
    boolean_T WriteOp = WRITE_OP_ARG;
    boolean_T ReadAccess = READ_ACCESS_ARG;
    boolean_T WriteAccess = WRITE_ACCESS_ARG;
    boolean_T HasParent = HAS_PARENT_ARG;
    boolean_T Extended = EXTENDED_ARG;
    boolean_T ForceVector = FORCE_VECTOR_ARG;
    uint8_T NodeIdType = NODE_ID_TYPE_ARG;
    uint16_t Namespace = NAMESPACE_ARG;
    char_T BrowseName[256] = { 0 };
    char_T DisplayName[256] = { 0 };
    char_T NodeDescription[256] = { 0 };

    char_T *Identifiers = mxArrayToString(NODE_ID_ARG);
    char_T *Parents = mxArrayToString(PARENT_ID_ARG);

    if (mxGetN(BROWSE_NAME_ARG) > 0)
    {
        mxGetString(BROWSE_NAME_ARG, BrowseName, 1 + mxGetN(BROWSE_NAME_ARG));
    }

    if (mxGetN(DISPLAY_NAME_ARG) > 0)
    {
        mxGetString(DISPLAY_NAME_ARG, DisplayName, 1 + mxGetN(DISPLAY_NAME_ARG));
    }

    if (mxGetN(DESCRIPTION_ARG) > 0)
    {
        mxGetString(DESCRIPTION_ARG, NodeDescription, 1 + mxGetN(DESCRIPTION_ARG));
    }

    if (!ssWriteRTWScalarParam(S, "UBID", &UBID, SS_UINT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 17,
        SSWRITE_VALUE_DTYPE_NUM, "ServerID", &ServerId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "NodeType", &NodeType, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ReadOp", &ReadOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "WriteOp", &WriteOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ReadAccess", &ReadAccess, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "WriteAccess", &WriteAccess, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "HasParent", &HasParent, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ForceVector", &ForceVector, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_2DMAT, "InitValue", mxGetPr(INIT_VALUE_ARG), mxGetN(INIT_VALUE_ARG), mxGetM(INIT_VALUE_ARG), DTINFO(ssGetDTypeIdFromMxArray(INIT_VALUE_ARG), COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Namespaces", &Namespace, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "IdentifierTypes", &NodeIdType, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_QSTR , "BrowseName", BrowseName,
        SSWRITE_VALUE_QSTR , "DisplayName", DisplayName,
        SSWRITE_VALUE_QSTR , "NodeDescription", NodeDescription,
        SSWRITE_VALUE_VECT_STR, "Identifiers", Identifiers, 1,
        SSWRITE_VALUE_VECT_STR, "Parents", Parents, 1

    )) {
        return;
    }
}
    //
#endif /* MDL_RTW */

#include "sg_sfcn_glue.h"   // Code generation glue
