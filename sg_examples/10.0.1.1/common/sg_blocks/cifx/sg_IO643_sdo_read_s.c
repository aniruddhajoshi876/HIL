#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO643_sdo_read_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define CAN_NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SDO_INDEX_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SDO_SUBINDEX_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define INIT_VALUE_ARG ssGetSFcnParam(S, 4)
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 5)
#define NUMBER_OF_ARGS 6

/* Definitions */
static char_T ErrMsg[1024];
char_T *DWorkName1 = "ErrMsg";
char_T *DWorkName2 = "Enable";

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg,
                "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    if (!ssSetNumInputPorts(S, 1))
        return;

    /* 1. ENABLE input port */
    ssSetInputPortDataType(S, 0, SS_BOOLEAN);
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    /* Output ports */
    if (!ssSetNumOutputPorts(S, 3))
        return;

    /* 1. DATA output port */
    /* Check whether init value is specified */
    if (mxIsEmpty(INIT_VALUE_ARG))
    {
        sprintf(ErrMsg, "Init Value parameter must not be empty");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    else
    {
        /* DATA output port derives type and dimensions from the init value parameter */
        ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
        ssSetOutputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
    }

    /* 2. STATUS output port */
    ssSetOutputPortDataType(S, 1, SS_UINT32);
    ssSetOutputPortWidth(S, 1, 1);

    /* 3. ERROR output port */
    ssSetOutputPortDataType(S, 2, SS_UINT32);
    ssSetOutputPortWidth(S, 2, 1);

    /* Options */
    ssSetNumIWork(S, 1);
    ssSetNumPWork(S, 1);
    ssSetNumDWork(S, 2);
    /* Error string DWORK */
    ssSetDWorkName(S, 0, DWorkName1);
    ssSetDWorkDataType(S, 0, SS_UINT8);
    ssSetDWorkWidth(S, 0, 256);
    /* DWORK for remembering the ENABLE input port value */
    ssSetDWorkName(S, 1, DWorkName2);
    ssSetDWorkWidth(S, 1, 1);
    ssSetDWorkDataType(S, 1, SS_BOOLEAN);

    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLE_TIME_ARG)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

/* mdlSetWorkWidths */
#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct* S)
{
    ssSetNumRunTimeParams(S, 1);
    ssRegDlgParamAsRunTimeParam(S, 4, 0, "Init_P", ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
}

#define MDL_START
static void mdlStart(SimStruct *S) {}
static void mdlOutputs(SimStruct *S, int_T tid) {}
static void mdlTerminate(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{
    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint32_T CanNodeId = CAN_NODE_ID_ARG;
    uint32_T SdoIndex = SDO_INDEX_ARG;
    uint32_T SdoSubIndex = SDO_SUBINDEX_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Channel", ssGetNumPWork(S)))
    {
        return;
    }
    if (!ssWriteRTWWorkVect(S, "IWork", 1, "BlockId", ssGetNumPWork(S)))
    {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 5,
                                 SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "CanNodeId", &CanNodeId, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "SdoIndex", &SdoIndex, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "SdoSubIndex", &SdoSubIndex, DTINFO(SS_UINT32, COMPLEX_NO)))
    {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"
