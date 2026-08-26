#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO752_record_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define API_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SUBSLOT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define RECORD_INDEX_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define INIT_VALUE_ARG ssGetSFcnParam(S, 5)
#define READ_OP_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define WRITE_OP_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define EXTENDED_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 9)
#define NUMBER_OF_ARGS 10

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Output ports */
    if (READ_OP_ARG)
    {
        if (EXTENDED_ARG)
        {
            if (!ssSetNumOutputPorts(S, 3))
                return;
        }
        else
        {
            if (!ssSetNumOutputPorts(S, 1))
                return;
        }

        /* DATA output port */
        ssSetOutputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
        ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));

        if (EXTENDED_ARG)
        {
            /* STATUS output port */
            ssSetOutputPortWidth(S, 1, 1);
            ssSetOutputPortDataType(S, 1, SS_UINT32);

            /* DATA LEN output port */
            ssSetOutputPortWidth(S, 2, 1);
            ssSetOutputPortDataType(S, 2, SS_UINT32);
        }
    }
    else
    {
        if (!ssSetNumOutputPorts(S, 0))
            return;
    }

    /* Input ports */
    if (WRITE_OP_ARG)
    {
        if (EXTENDED_ARG)
        {
            if (!ssSetNumInputPorts(S, 3))
                return;
        }
        else
        {
            if (!ssSetNumInputPorts(S, 2))
                return;
        }

        /* DATA input port */
        ssSetInputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
        ssSetInputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);

        /* ENABLE input port */
        ssSetInputPortWidth(S, 1, 1);
        ssSetInputPortDataType(S, 1, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, 1, 1);
        ssSetInputPortDirectFeedThrough(S, 1, 1);

        if (EXTENDED_ARG)
        {
            /* DATA LEN input port */
            ssSetInputPortWidth(S, 2, 1);
            ssSetInputPortDataType(S, 2, SS_UINT32);
            ssSetInputPortRequiredContiguous(S, 2, 1);
            ssSetInputPortDirectFeedThrough(S, 2, 1);
        }
    }
    else
    {
        if (!ssSetNumInputPorts(S, 0))
            return;
    }

    /* Options */
    ssSetNumPWork(S, 2);
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

#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct *S)
{
    ssSetNumRunTimeParams(S, 1);
    ssRegDlgParamAsRunTimeParam(S, 5, 0, "InitValue", ssGetDTypeIdFromMxArray(ssGetSFcnParam(S, 5)));
}

#define MDL_START

static void mdlStart(SimStruct *S)
{
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
}

static void mdlTerminate(SimStruct *S)
{
}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{

    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint32_T Api = API_ARG;
    uint16_T Slot = SLOT_ARG;
    uint16_T SubSlot = SUBSLOT_ARG;
    uint16_T RecordIndex = RECORD_INDEX_ARG;
    boolean_T ReadOp = READ_OP_ARG;
    boolean_T WriteOp = WRITE_OP_ARG;
    boolean_T Extended = EXTENDED_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 2, "Channel", 1, "Record", 1))
    {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 9,
                                 SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "Api", &Api, DTINFO(SS_UINT32, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "Slot", &Slot, DTINFO(SS_UINT16, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "SubSlot", &SubSlot, DTINFO(SS_UINT16, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "RecordIndex", &RecordIndex, DTINFO(SS_UINT16, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "ReadOp", &ReadOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "WriteOp", &WriteOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
                                 SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO)))
    {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"
