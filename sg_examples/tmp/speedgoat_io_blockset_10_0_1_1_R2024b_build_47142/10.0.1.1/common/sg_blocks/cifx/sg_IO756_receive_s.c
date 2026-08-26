#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO756_receive_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "EIS_api.h"
#include "cifx_common.h"
#include "cifxapi.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG        (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG       (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLETIME_ARG    ssGetSFcnParam(S, 1)
#define DATA_LEN_ARG      (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define PORT_TYPE_ARG     (uint8_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define CONFIG_MODE_ARG   (uint8_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define ASSEMBLIES_ARG    ssGetSFcnParam(S, 5)
#define BLOCK_VERSION_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define NUMBER_OF_ARGS    7

/* Convenient access to m x n matrices which are stored as vectors */
#define ASSEMBLY_ID_ARG(i) (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 0 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_LEN_ARG(i)                                                                        \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 1 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_OFFSET_ARG(i)                                                                     \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 2 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_TYPE_ARG(i)                                                                       \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 3 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_FORMAT_ARG(i)                                                                     \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 4 * (int_T)mxGetM(ASSEMBLIES_ARG)]

#define NUM_ASSEMBLIES (int_T) mxGetM(ASSEMBLIES_ARG)

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Ports */
    if (!ssSetNumInputPorts(S, 0))
        return;

    if (BLOCK_VERSION_ARG == 1) {

        /* Old setup block */

        if (PORT_TYPE_ARG == 1) {

            /* Multiple ports */

            if (!ssSetNumOutputPorts(S, DATA_LEN_ARG))
                return;

            for (i = 0; i < DATA_LEN_ARG; i++) {
                ssSetOutputPortWidth(S, i, 1);
                ssSetOutputPortDataType(S, i, SS_UINT8);
            }

        } else if (PORT_TYPE_ARG == 2) {

            /* Single port */

            if (!ssSetNumOutputPorts(S, 1))
                return;

            ssSetOutputPortWidth(S, 0, DATA_LEN_ARG);
            ssSetOutputPortDataType(S, 0, SS_UINT8);
        }

    } else {

        /* New setup block */

        if (CONFIG_MODE_ARG == 0) {

            /* Simple configuration mode */
            /* Single port */

            if (!ssSetNumOutputPorts(S, 1))
                return;

            ssSetOutputPortWidth(S, 0, DATA_LEN_ARG);
            ssSetOutputPortDataType(S, 0, SS_UINT8);

        } else {

            /* Extended configuration mode */
            /* Multiple ports */

            /* Get number of output and configuration assemblies */
            uint32_T n = 0;
            /* For each assembly */
            for (i = 0; i < NUM_ASSEMBLIES; i++) {
                if ((ASSEMBLY_TYPE_ARG(i) == 0) || (ASSEMBLY_TYPE_ARG(i) == 2)) {
                    /* Is output or configuration assembly */
                    if ((ASSEMBLY_LEN_ARG(i) > 0)) {
                        /* Has length */
                        n++;
                    }
                }
            }

            /* Set number of output ports */
            if (!ssSetNumOutputPorts(S, n))
                return;

            n = 0;
            /* For each assembly */
            for (i = 0; i < NUM_ASSEMBLIES; i++) {
                if ((ASSEMBLY_TYPE_ARG(i) == 0) || (ASSEMBLY_TYPE_ARG(i) == 2)) {
                    /* Is output or configuration assembly */
                    if ((ASSEMBLY_LEN_ARG(i) > 0)) {
                        /* Has length */
                        ssSetOutputPortWidth(S, n, ASSEMBLY_LEN_ARG(i));
                        ssSetOutputPortDataType(S, n, SS_UINT8);
                        n++;
                    }
                }
            }
        }
    }

    /* Options */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLETIME_ARG)[0] == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLETIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S) { ssSetPWorkValue(S, 0, NULL); }

static void sg_ModelStep(SimStruct *S)
{
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    EIS_PARAM_2_T *Param = NULL;

    /* Find corresponding node structure in global driver array */
    if (Channel == NULL) {
        CIFX_NODE_T *Node = NULL;

        if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node)) {
            ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
            return;
        }

        Channel = Node->Channels[0];
        ssSetPWorkValue(S, 0, Channel);
    }

    Param = (EIS_PARAM_2_T *)(Channel->Param);

    if (BLOCK_VERSION_ARG == 1) {

        /* Old setup block */

        if (PORT_TYPE_ARG == 1) {
            uint8_T data[5760] = {0};

            if (Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)data)) {

                for (uint32_T i = 0; i < DATA_LEN_ARG; i++) {
                    uint8_t *pOutPort = (uint8_T *)ssGetOutputPortSignal(S, i);
                    pOutPort[0] = data[i];
                }
            }
        } else {
            Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)ssGetOutputPortSignal(S, 0));
        }

    } else {

        /* New setup block */

        if (CONFIG_MODE_ARG == EIS_CONFIG_MODE_SIMPLE) {

            /* Simple configuration mode */

            Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)ssGetOutputPortSignal(S, 0));

        } else {

            uint8_T data[5760] = {0};
            uint32_T DataLen = 0;
            uint32_T n = 0;

            /* Add up overall data length over all output assemblies */
            for (uint32_T i = 0; i < NUM_ASSEMBLIES; i++) {
                if (ASSEMBLY_TYPE_ARG(i) == EIS_ASSEMBLY_TYPE_OUTPUT) {
                    /* Is output assembly */
                    DataLen += ASSEMBLY_LEN_ARG(i);
                }
            }

            Cifx_RecDataExt(Channel, DataLen, (void *)data);

            /* For each assembly */
            for (uint32_T i = 0; i < NUM_ASSEMBLIES; i++) {

                if (ASSEMBLY_TYPE_ARG(i) == EIS_ASSEMBLY_TYPE_OUTPUT) {

                    /* Is output assembly */

                    if ((ASSEMBLY_LEN_ARG(i) > 0)) {
                        /* Has length */
                        uint8_t *p = (uint8_T *)ssGetOutputPortSignal(S, n);
                        memcpy(p, &data[ASSEMBLY_OFFSET_ARG(i)], ASSEMBLY_LEN_ARG(i));
                        n++;
                    }
                } else if (ASSEMBLY_TYPE_ARG(i) == EIS_ASSEMBLY_TYPE_CONFIG) {

                    /* Is configuration assembly */

                    if ((ASSEMBLY_LEN_ARG(i) > 0)) {
                        /* Has length */
                        uint8_t *p = (uint8_T *)ssGetOutputPortSignal(S, n);
                        memcpy(p, Param->Assemblies[i].Data, ASSEMBLY_LEN_ARG(i));
                        n++;
                    }
                }
            }
        }

        EIS_AcyclicHandler(Channel);
    }
}

static void sg_ModelStop(SimStruct *S) {}

#endif

#include "sg_sfcn_glue.h"
