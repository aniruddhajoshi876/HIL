#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_dnp3_client_class_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "dnp3.h"
#include "dnp3_api.h"
#include "dnp3_root.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace dnp3;
#endif

/* Defines */
#define NETWORK_ID_ARG      (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CLIENT_ID_ARG       (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SERVER_ID_ARG   (uint16_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SAMPLE_TIME_ARG               mxGetPr(ssGetSFcnParam(S, 3))[0]
#define UNSOLICITED_ARG      (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define POLL_ARG             (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define CLASS_CFG_ARG                         ssGetSFcnParam(S, 6)
#define NUMBER_OF_ARGS											7

#define CLASS_GROUP_ID(i)   ((uint8_T)(mxGetPr(CLASS_CFG_ARG)[i + 0 * (int_T)mxGetM(CLASS_CFG_ARG)]))
#define CLASS_START_IDX(i)  ((uint16_T)(mxGetPr(CLASS_CFG_ARG)[i + 1 * (int_T)mxGetM(CLASS_CFG_ARG)]))
#define CLASS_STOP_IDX(i)   ((uint16_T)(mxGetPr(CLASS_CFG_ARG)[i + 2 * (int_T)mxGetM(CLASS_CFG_ARG)]))
#define CLASS_ID(i)         ((uint8_T)(mxGetPr(CLASS_CFG_ARG)[i + 3 * (int_T)mxGetM(CLASS_CFG_ARG)]))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < 0; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (POLL_ARG == 0)
    {
        ssSetNumInputPorts(S, 0);
    }
    else
    {
        ssSetNumInputPorts(S, 1);
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }

    ssSetNumOutputPorts(S, 0);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 1);
    ssSetNumPWork(S, 3);
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

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    uint32_t i = 0;
    int32_t ret = 0;
    dnp3::CLIENT_BLOCK_T* Block = NULL;
    cClientStation* Station = NULL;
    cConnection* Connection = NULL;

    /* Add a master to the network */
    ret = Root.addStation(CLIENT_ID_ARG, true, (cStation**)&Station);
    if (ret != 0)
    {
        sprintf(ErrMsg, "DNP3 | Failed to add station %i", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a connection to the master */
    ret = Station->addConnection(SERVER_ID_ARG, (cConnection**)&Connection);
    if (ret != 0)
    {
        sprintf(ErrMsg, "DNP3 | Failed to add connection %i to station %i", SERVER_ID_ARG, CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    {
        /* Add a virtual Simulink block to the connection for integrity poll*/
        if (0 != Connection->addBlock(&Block))
        {
            sprintf(ErrMsg, "DNP3 | Failed to a add block to connection %i", SERVER_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        uint8_t* c = (uint8_t*)Block->Value;

        Block->Type = DNP3_BLOCK_TYPE_UNDEF;
        Block->Group = 60;
        Block->FcnCode = 1;
        *c = POLL_ARG;

        ssSetPWorkValue(S, 0, Block);
    }

    {
        /* Add a virtual Simulink block to the connection for unsolicited messages */
        if (0 != Connection->addBlock(&Block))
        {
            sprintf(ErrMsg, "DNP3 | Failed to add a block to connection %i", SERVER_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        uint8_t* c = (uint8_t*)Block->Value;

        Block->Type = DNP3_BLOCK_TYPE_UNDEF;
        Block->Group = 60;
        Block->FcnCode = 20;
        *c = UNSOLICITED_ARG;

        ssSetPWorkValue(S, 1, Block);
    }


    {
        /* Add a virtual Simulink block to the connection for class assignment */
        if (0 != Connection->addBlock(&Block))
        {
            sprintf(ErrMsg, "DNP3 | Failed to add a block to connection %i", SERVER_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        DNP3_DATA_6022_T* Data = (DNP3_DATA_6022_T*)Block->Value;

        Block->Type = DNP3_BLOCK_TYPE_UNDEF;
        Block->Group = 60;
        Block->FcnCode = 22;
        Block->PointQty = (int_T)mxGetM(CLASS_CFG_ARG);

        /* For each class assignment */
        for (i = 0; i < (uint32_T)mxGetM(CLASS_CFG_ARG); i++)
        {
            Data[i].Group = CLASS_GROUP_ID(i);
            Data[i].StartIdx = CLASS_START_IDX(i);
            Data[i].StopIdx = CLASS_STOP_IDX(i);
            Data[i].Class = CLASS_ID(i);
        }

        ssSetPWorkValue(S, 2, Block);
    }

    ssSetIWorkValue(S, 0, 0);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    boolean_T IsCom = false;
    boolean_T WasCom = (boolean_T)ssGetIWorkValue(S, 0);
    dnp3::CLIENT_BLOCK_T* PollBlock = (dnp3::CLIENT_BLOCK_T*)ssGetPWorkValue(S, 0);
    dnp3::CLIENT_BLOCK_T* UnsolBlock = (dnp3::CLIENT_BLOCK_T*)ssGetPWorkValue(S, 1);
    dnp3::CLIENT_BLOCK_T* AssignBlock = (dnp3::CLIENT_BLOCK_T*)ssGetPWorkValue(S, 2);
    cConnection* Connection = (cConnection*)PollBlock->Parent;

    IsCom = Connection->isConnected();

    if (IsCom != 0)
    {
        if (IsCom > WasCom)
        {
            PollBlock->HostFlagsTx++;
            UnsolBlock->HostFlagsTx++;
            AssignBlock->HostFlagsTx++;
        }
        else
        {
            if (POLL_ARG != 0)
            {
                boolean_T* Poll = (boolean_T*)ssGetInputPortSignal(S, 0);

                if (*Poll != 0)
                {
                    PollBlock->HostFlagsTx++;
                }
            }
        }
    }

    ssSetIWorkValue(S, 0, IsCom);
#endif
}

static void sg_ModelStop(SimStruct *S)
{
}

#include "sg_sfcn_glue.h"   // Code generation glue
