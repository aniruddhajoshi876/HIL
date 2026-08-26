#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO644_object_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include "matrix.h"
#endif

/* Defines */
#define MOD_ID_ARG              (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG              (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[1]
#define INDEX_ARG               (uint16_T)mxGetScalar(ssGetSFcnParam(S, 1))
#define SUBINDEX_ARG            (uint8_T)mxGetScalar(ssGetSFcnParam(S, 2))
#define ACCESS_RIGHTS_ARG         (uint16_T)mxGetScalar(ssGetSFcnParam(S, 3))
#define OBJECT_TYPE_ARG           (uint8_T)mxGetScalar(ssGetSFcnParam(S, 4))
#define DATA_TYPE_ARG           (uint16_T)mxGetScalar(ssGetSFcnParam(S, 5))
#define INIT_VALUE_ARG                            ssGetSFcnParam(S, 6)
#define READ_OP_ARG            (boolean_T)mxGetScalar(ssGetSFcnParam(S, 7))
#define WRITE_OP_ARG            (boolean_T)mxGetScalar(ssGetSFcnParam(S, 8))
#define EXTENDED_ARG            (boolean_T)mxGetScalar(ssGetSFcnParam(S, 9))
#define DATA_LEN_ARG            (uint32_T)mxGetScalar(ssGetSFcnParam(S, 10))
#define NUM_ELEMENTS_ARG        (uint32_T)mxGetScalar(ssGetSFcnParam(S, 11))
#define SAMPLE_TIME_ARG                           ssGetSFcnParam(S, 12)    
#define NUMBER_OF_ARGS                                              13

/* Definitions */
static char_T ErrMsg[1024];

/* mdlInitializeSizes */
static void mdlInitializeSizes(SimStruct* S)
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

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }
    
    if (OBJECT_TYPE_ARG != 7) // not VAR
    {
        if (!ssSetNumInputPorts(S, 0)) return;
        if (!ssSetNumOutputPorts(S, 0)) return;
    }
    else
    {
        /* Output ports */
        if (READ_OP_ARG)
        {
            if (EXTENDED_ARG)
            {
                if (!ssSetNumOutputPorts(S, 2)) return;
            }
            else
            {
                if (!ssSetNumOutputPorts(S, 1)) return;
            }

            /* DATA output port */
            ssSetOutputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
            ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));

            if (EXTENDED_ARG)
            {
                /* STATUS output port */
                ssSetOutputPortWidth(S, 1, 1);
                ssSetOutputPortDataType(S, 1, SS_UINT32);
            }
        }
        else
        {
            if (!ssSetNumOutputPorts(S, 0)) return;
        }

        /* Input ports */
        if (WRITE_OP_ARG)
        {
            if (EXTENDED_ARG)
            {
                if (!ssSetNumInputPorts(S, 2)) return;
            }
            else
            {
                if (!ssSetNumInputPorts(S, 1)) return;
            }

            /* DATA input port */
            ssSetInputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
            ssSetInputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
            ssSetInputPortRequiredContiguous(S, 0, 1);
            //ssSetInputPortDirectFeedThrough(S, 0, 1);

            if (EXTENDED_ARG)
            {
                /* ENABLE input port */
                ssSetInputPortWidth(S, 1, 1);
                ssSetInputPortDataType(S, 1, SS_BOOLEAN);
                ssSetInputPortRequiredContiguous(S, 1, 1);
                ssSetInputPortDirectFeedThrough(S, 1, 1);
            }
        }
        else
        {
            if (!ssSetNumInputPorts(S, 0)) return;
        }
    }

    ssSetNumPWork(S, 1);

    
   
    if (OBJECT_TYPE_ARG == 7) // VAR
    {
        ssSetNumDWork(S, 1);
        ssSetDWorkName(S, 0, "Data_D");
        ssSetDWorkWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));
        ssSetDWorkDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
    }
    else
    {
        ssSetNumDWork(S, 0);
    }
    
    ssSetNumSampleTimes(S, 1);
    
    /* SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME prevents the block from being eliminated by the 
     * Simulink Coder in case the model parameter option is INLINED or input and output ports 
     * are not connected */
    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE);
}

/* mdlInitializeSampleTimes */
static void mdlInitializeSampleTimes(SimStruct* S)
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
    if (OBJECT_TYPE_ARG == 7) // VAR
    {
        ssSetNumRunTimeParams(S, 1);
        ssRegDlgParamAsRunTimeParam(S, 6, 0, "Init_P", ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
    }
}

static void mdlStart(SimStruct* S) {}
static void mdlOutputs(SimStruct* S, int_T tid) {}
static void mdlTerminate(SimStruct* S) {}

/* mdlRTW */
#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct* S) {

    int32_T Dummy = 0;
    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint16_T Index = INDEX_ARG;
    uint8_T SubIndex = SUBINDEX_ARG;
    uint16_T AccessRights = ACCESS_RIGHTS_ARG;
    uint8_T ObjectType = OBJECT_TYPE_ARG;
    uint16_T DataType = DATA_TYPE_ARG;
    boolean_T ReadOp = READ_OP_ARG;
    boolean_T WriteOp = WRITE_OP_ARG;
    boolean_T Extended = EXTENDED_ARG;
    uint32_T DataLen = DATA_LEN_ARG;
    uint32_T NumElements = NUM_ELEMENTS_ARG;
    
    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Channel", ssGetNumPWork(S))) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosBlockIdx", &Dummy, SS_INT32)) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosModuleIdx", &Dummy, SS_INT32)) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosObjIdx", &Dummy, SS_INT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 12,
        SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Index", &Index, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "SubIndex", &SubIndex, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "AccessRights", &AccessRights, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ObjectType", &ObjectType, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "DataType", &DataType, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ReadOp", &ReadOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "WriteOp", &WriteOp, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "DataLen", &DataLen, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "NumElements", &NumElements, DTINFO(SS_UINT32, COMPLEX_NO)
    )) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"   
