#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_opcua_client_read_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "fixedpoint.c"
#include "fixedpoint.h"
#include "mex.h"
#endif

#include "opcua_def.h"

#ifndef MATLAB_MEX_FILE
#include "opcua_server_block.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace opcua;
#endif

/* Defines */
#define INIT_ARG_POS 5

#define CLIENT_ID_ARG           (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG       (uint16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define NAMESPACE_ARG           ssGetSFcnParam(S, 2)
#define IDENTIFIER_TYPE_ARG     ssGetSFcnParam(S, 3)
#define IDENTIFIER_ARG          ssGetSFcnParam(S, 4)
#define INIT_VALUE_ARG          ssGetSFcnParam(S, 5)
#define SAMPLE_TIME_ARG         mxGetPr(ssGetSFcnParam(S, 6))[0]
#define FORCE_VECTOR_ARG        mxGetPr(ssGetSFcnParam(S, 7))[0]
#define DATA_TYPE_ARG           ssGetSFcnParam(S, 8)
#define DIMENSION_ARG           ssGetSFcnParam(S, 9)
#define DATA_PORT_TYPE          (boolean_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define PARAM_VALID_ARG         (boolean_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define STRUCT_CONFIG_ARG       (boolean_T) mxGetPr(ssGetSFcnParam(S, 12))[0]
#define CREATE_SUBSCRIPTION_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 13))[0]
#define PUBLISHING_INTERVAL_ARG ssGetSFcnParam(S, 14)
#define MONITORING_MODE_ARG     ssGetSFcnParam(S, 15)
#define SAMPLING_INTERVAL_ARG   ssGetSFcnParam(S, 16)
#define BUS_NAME_ARG            ssGetSFcnParam(S, 17)
#define ADD_OUTPUT_ARG          (boolean_T) mxGetPr(ssGetSFcnParam(S, 18))[0]
#define NUMBER_OF_ARGS          19

#define DIM_M(i)                                                                                   \
    ((uint32_T)(((uint32_T *)mxGetPr(DIMENSION_ARG))[i + 0 * (int_T)mxGetM(DIMENSION_ARG)]))
#define DIM_N(i)                                                                                   \
    ((uint32_T)(((uint32_T *)mxGetPr(DIMENSION_ARG))[i + 1 * (int_T)mxGetM(DIMENSION_ARG)]))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T NumItems = mxGetN(NAMESPACE_ARG);
    DTypeId Uint64TypeId = 0;

    /* Register uint64 data type */
#ifdef MATLAB_MEX_FILE
    Uint64TypeId = ssRegisterDataTypeInteger(S, 0, 64, 1);
    if (Uint64TypeId == INVALID_DTYPE_ID) {
        sprintf(ErrMsg, "Cannot register 64 bit integer type");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
#else
    Uint64TypeId = SS_DOUBLE;
#endif

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    if (CREATE_SUBSCRIPTION_ARG) {
        ssSetNumInputPorts(S, 0);
    } else {
        ssSetNumInputPorts(S, 1);
        /* 1. ENABLE input port */
        ssSetInputPortDataType(S, 0, DYNAMICALLY_TYPED);
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }

    /* Output ports */
    if ((ADD_OUTPUT_ARG) && (DATA_PORT_TYPE == 0)) {
        ssSetNumOutputPorts(S, 3);
    } else {
        ssSetNumOutputPorts(S, 1);
    }

    /* 1. DATA output ports */
    /* Check whether vector or bus output */
    if (DATA_PORT_TYPE == 0) {

        /* Vector output */

        /* Check whether we have one or multiple items */
        if (NumItems == 1) {

            /* One item */

            int m = DIM_M(0);
            int n = DIM_N(0);
            int d[] = {m, n};
            DimsInfo_T DimInfo = {0};

            DimInfo.width = m * n;
            DimInfo.numDims = 2;
            DimInfo.dims = d;

            if ((m == 0) || (n == 0)) {
                DimInfo.numDims = 1;
                DimInfo.width = m > n ? m : n;
                d[0] = m > n ? m : n;
            }

            ssSetOutputPortDimensionInfo(S, 0, &DimInfo);
            ssSetOutputPortDataType(S, 0, ((uint32_T)(((uint32_T *)mxGetPr(DATA_TYPE_ARG))[0])));

        } else {

            /* Multiple items with same data type and dimension */

            ssSetOutputPortWidth(S, 0, NumItems);
            ssSetOutputPortDataType(S, 0, ((uint32_T)(((uint32_T *)mxGetPr(DATA_TYPE_ARG))[0])));
        }

    } else {

        /* Bus output */

        char BusName[OPCUA_STR_LEN + 1] = {0};
        DTypeId BusDtId = -1;

        /* Get bus type name form params */
        mxGetString(BUS_NAME_ARG, BusName, 1 + mxGetN(BUS_NAME_ARG));

        /* Register the bus type */
        ssRegisterTypeFromNamedObject(S, BusName, &BusDtId);
        if (BusDtId == INVALID_DTYPE_ID) {
            ssPrintf("Unable to register bus type %s\n", BusName);
        }

        ssSetOutputPortDataType(S, 0, BusDtId);
        ssSetOutputPortWidth(S, 0, 1);
        ssSetBusOutputAsStruct(S, 0, 1);
        ssSetBusOutputObjectName(S, 0, BusName);
    }

    if ((ADD_OUTPUT_ARG) && (DATA_PORT_TYPE == 0)) {

        /* 2. STATUS output port */
        ssSetOutputPortDataType(S, 1, SS_UINT32);
        ssSetOutputPortWidth(S, 1, NumItems);

        /* 3. TIME output port */
        ssSetOutputPortDataType(S, 2, Uint64TypeId);
        ssSetOutputPortWidth(S, 2, NumItems);
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
    if (SAMPLE_TIME_ARG == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct *S)
{
    if (!STRUCT_CONFIG_ARG) {
        if (!mxIsEmpty(INIT_VALUE_ARG)) {
            char n[] = "InitValueRun\0";
            ssSetNumRunTimeParams(S, 1);
            ssRegDlgParamAsRunTimeParam(S, INIT_ARG_POS, 0, n,
                                        ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
        }
    }
}

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_INPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetInputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_INPUT_PORT_DATA_TYPE
#if defined(MDL_SET_INPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetInputPortDataType(S, port, id);
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_OUTPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
#if defined(MDL_SET_OUTPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetOutputPortDataType(S, port, id);
}
#endif /* MDL_SET_OUTPUT_PORT_DATA_TYPE */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
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
static void mdlRTW(SimStruct *S)
{
    int32_T i = 0;
    uint16_T ConnectionId = CONNECTION_ID_ARG;
    uint16_T ClientId = CLIENT_ID_ARG;
    boolean_T DataPortType = DATA_PORT_TYPE;
    boolean_T StructConfig = STRUCT_CONFIG_ARG;
    boolean_T CreateSubscription = CREATE_SUBSCRIPTION_ARG;
    uint32_T UBID = 0;
    uint32_T NumItems = mxGetN(NAMESPACE_ARG);
    boolean_T AddOutput = ADD_OUTPUT_ARG;

    boolean_T ReadOp = 1;
    boolean_T WriteOp = 0;

    char_T *Identifiers = mxArrayToString(IDENTIFIER_ARG);

    if (!ssWriteRTWScalarParam(S, "UBID", &UBID, SS_UINT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 17, SSWRITE_VALUE_DTYPE_NUM, "ClientID", &ClientId, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ConnectionID", &ConnectionId, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_2DMAT, "Dimensions", mxGetPr(DIMENSION_ARG), mxGetM(DIMENSION_ARG),
            mxGetN(DIMENSION_ARG), DTINFO(ssGetDTypeIdFromMxArray(DIMENSION_ARG), COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_VECT, "Namespaces", mxGetPr(NAMESPACE_ARG), NumItems,
            DTINFO(ssGetDTypeIdFromMxArray(NAMESPACE_ARG), COMPLEX_NO), SSWRITE_VALUE_DTYPE_VECT,
            "IdentifierTypes", mxGetPr(IDENTIFIER_TYPE_ARG), NumItems,
            DTINFO(ssGetDTypeIdFromMxArray(IDENTIFIER_TYPE_ARG), COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_VECT, "DataTypes", mxGetPr(DATA_TYPE_ARG), NumItems,
            DTINFO(ssGetDTypeIdFromMxArray(DATA_TYPE_ARG), COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM,
            "ReadOp", &ReadOp, DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "WriteOp",
            &WriteOp, DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "DataPortType",
            &DataPortType, DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "StructConfig",
            &StructConfig, DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "NumItems",
            &NumItems, DTINFO(SS_UINT32, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "CreateSubscription",
            &CreateSubscription, DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM,
            "PublishingInterval", mxGetPr(PUBLISHING_INTERVAL_ARG),
            DTINFO(ssGetDTypeIdFromMxArray(PUBLISHING_INTERVAL_ARG), COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_VECT, "MonitoringModes", mxGetPr(MONITORING_MODE_ARG),
            NumItems, DTINFO(ssGetDTypeIdFromMxArray(MONITORING_MODE_ARG), COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_VECT, "SamplingIntervals", mxGetPr(SAMPLING_INTERVAL_ARG),
            NumItems,
            DTINFO(ssGetDTypeIdFromMxArray(SAMPLING_INTERVAL_ARG), COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "AddOutput", &AddOutput, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_VECT_STR, "Identifiers", Identifiers, NumItems)) {
        return;
    }
}

#endif /* MDL_RTW */

#include "sg_sfcn_glue.h" // Code generation glue
