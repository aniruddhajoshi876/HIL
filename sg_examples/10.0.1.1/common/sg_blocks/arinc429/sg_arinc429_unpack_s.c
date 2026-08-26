#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_arinc429_unpack_s

#include <stddef.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
  #include    "mex.h"
#endif

#define GET_SFUNC_PARAM(x)          (mxGetPr(ssGetSFcnParam(S, x)))
#define GET_SFUNC_PARAM_COLUMNS(x)  (mxGetN(ssGetSFcnParam(S, x)))
#define GET_SFUNC_PARAM_ROWS(x)     (mxGetM(ssGetSFcnParam(S, x)))

#define ONES(n)          ((n) > 31 ? 0xffffffff : (1 << (n)) - 1)

#define BNR 1
#define BCD 2
#define DSC 3
#define SSM 4

enum SetupParams
{
    LABEL_ARG,
    SDI_ARG,
    EN_TIME_TAG_ARG,
    EN_STATUS_ARG,
    EN_RAW_ARG,
    SIGNALS_ARG,
    HAS_SSM_ARG,
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

static void decodeBNR(double* signal, uint32_t startBit, uint32_t dataLength, bool isSigned, uint32_t msg);
static void decodeBCD(double* signal, uint32_t startBit, uint32_t dataLength, uint32_t ssm, uint32_t msg);
static void decodeDSC(double* signal, uint32_t startBit, uint32_t dataLength, uint32_t msg);

static void mdlInitializeSizes(SimStruct *S)
{
    int i, nPorts = (int)GET_SFUNC_PARAM_COLUMNS(SIGNALS_ARG);

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n"
                "%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
    {
        if (!ssSetNumInputPorts(S, 3)) return;
        ssSetInputPortWidth(S, 2, DYNAMICALLY_SIZED);
        ssSetInputPortDataType(S, 2, SS_UINT32);
        ssSetInputPortDirectFeedThrough(S, 2, 1);
        ssSetInputPortRequiredContiguous(S, 2, 1);
    }
    else
    {
        if (!ssSetNumInputPorts(S, 2)) return;
    }
    //Cnt
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    //Msg
    ssSetInputPortWidth(S, 1, DYNAMICALLY_SIZED);
    ssSetInputPortDataType(S, 1, SS_UINT32);
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortRequiredContiguous(S, 1, 1);
    
    if (((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1) && ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1) && ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1))
    {
        if (!ssSetNumOutputPorts(S,nPorts+3)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_UINT32);
        ssSetOutputPortWidth(S, nPorts+1, 1);
        ssSetOutputPortDataType(S, nPorts+1, SS_BOOLEAN);
        ssSetOutputPortWidth(S, nPorts+2, 1);
        ssSetOutputPortDataType(S, nPorts+2, SS_UINT32);
    }
    else if (((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1) && ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1))
    {
        if (!ssSetNumOutputPorts(S,nPorts+2)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_UINT32);
        ssSetOutputPortWidth(S, nPorts+1, 1);
        ssSetOutputPortDataType(S, nPorts+1, SS_BOOLEAN);
    }
    else if (((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1) && ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1))
    {
        if (!ssSetNumOutputPorts(S,nPorts+2)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_UINT32);
        ssSetOutputPortWidth(S, nPorts+1, 1);
        ssSetOutputPortDataType(S, nPorts+1, SS_UINT32);
    }
    else if (((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1) && ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1))
    {
        if (!ssSetNumOutputPorts(S,nPorts+2)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_BOOLEAN);
        ssSetOutputPortWidth(S, nPorts+1, 1);
        ssSetOutputPortDataType(S, nPorts+1, SS_UINT32);
    }
    else if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
    {
        if (!ssSetNumOutputPorts(S,nPorts+1)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_UINT32);
    }
    else if ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1)
    {
        if (!ssSetNumOutputPorts(S,nPorts+1)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_BOOLEAN);
    }
    else if ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1)
    {
        if (!ssSetNumOutputPorts(S,nPorts+1)) return;
        ssSetOutputPortWidth(S, nPorts, 1);
        ssSetOutputPortDataType(S, nPorts, SS_UINT32);
    }
    else
    {
        if (!ssSetNumOutputPorts(S,nPorts)) return;
    }

    for (i=0; i<nPorts; i++)
    {
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, SS_DOUBLE);
    }

    ssSetNumSampleTimes(S, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    for( i = 0 ; i < NUMBER_OF_ARGS; i++ )
    {
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE);
}

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    if (!ssSetInputPortDimensionInfo( S, portIndex, dimsInfo)) return;
}

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo( S, portIndex, dimsInfo)) return;
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    int i, j, nMsg, *p_nMsg = (int*)ssGetInputPortSignal(S, 0);
    uint32_t msg, *inWord = (uint32_t*)ssGetInputPortSignal(S, 1);
    int nSignals = (int)GET_SFUNC_PARAM_COLUMNS(SIGNALS_ARG);
    int signalsWidth = (int)GET_SFUNC_PARAM_ROWS(SIGNALS_ARG);
    uint32_t *time, *outTimeTags, *outRaw;
    uint32_t ssm = 0;
    bool *outStatus;

    nMsg = p_nMsg[0];

    if ((int)GET_SFUNC_PARAM(HAS_SSM_ARG)[0] == 0) //Use default SSM instead of input signal
    {
        ssm = ((msg >> 29) & 0x3);
    }

    if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
    {
        time = (uint32_t*)ssGetInputPortSignal(S, 2);
        outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, nSignals);
    }

    if ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1)
    {
        if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
        {
            outStatus = (bool*)ssGetOutputPortSignal(S, nSignals+1);
        }
        else
        {
            outStatus = (bool*)ssGetOutputPortSignal(S, nSignals);
        }
        //Init status
        for (i=0; i<nSignals; i++)
        {
            outStatus[i] = false;
        }
    }

    if ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1)
    {
        if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
        {
            if ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1)
            {
                outRaw = (uint32_t*)ssGetOutputPortSignal(S, nSignals+2);
            }
            else
            {
                outRaw = (uint32_t*)ssGetOutputPortSignal(S, nSignals+1);
            }
        }
        else
        {
            if ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1)
            {
                outRaw = (uint32_t*)ssGetOutputPortSignal(S, nSignals+1);
            }
            else
            {
                outRaw = (uint32_t*)ssGetOutputPortSignal(S, nSignals);
            }
        }
    }
   
    if (nMsg < 0 || nMsg > (int)ssGetInputPortWidth(S, 1))  // should never happen
    {
        ssSetErrorStatus(S, "ARINC429 Unpack: Cnt is negative or bigger than Msg input port size");
        return;
    }

    for (i=0; i<nMsg; i++)  //start from back of the list to save time finding the latest msg?
    {
        msg = inWord[i];

        if ((uint32_t)GET_SFUNC_PARAM(LABEL_ARG)[0] != (msg & 0xff))
        {
            continue;
        }

        if ((int)GET_SFUNC_PARAM(SDI_ARG)[0] != -1)
        {
            if ((uint32_t)GET_SFUNC_PARAM(SDI_ARG)[0] != ((msg & 0x300)>>8))
            {
                continue;
            }
        }

        for (j=0; j<nSignals; j++)
        {
            double *signal = (double*)ssGetOutputPortSignal(S, j);
            uint32_t startBit = (uint32_t)GET_SFUNC_PARAM(SIGNALS_ARG)[0+j*signalsWidth];
            uint32_t dataLength = (uint32_t)GET_SFUNC_PARAM(SIGNALS_ARG)[1+j*signalsWidth];
            double resolution = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[3+j*signalsWidth];
            double offset = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[4+j*signalsWidth];
            double min = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[5+j*signalsWidth];
            double max = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[6+j*signalsWidth];
            bool isSigned = (bool)GET_SFUNC_PARAM(SIGNALS_ARG)[7+j*signalsWidth];

            switch((int)GET_SFUNC_PARAM(SIGNALS_ARG)[2+j*signalsWidth])
            {
                case BNR: decodeBNR(signal, startBit, dataLength, isSigned, msg); break;
                case BCD: decodeBCD(signal, startBit, dataLength, ssm, msg); break;
                case DSC: //Use the same for SSM
                case SSM: decodeDSC(signal, startBit, dataLength, msg); break;
                default: ssSetErrorStatus(S, "ARINC429 Unpack: Unsupported data type\n"); return;
            }

            signal[0] = signal[0] * resolution + offset;

            if (signal[0] < min)
            {
                signal[0] = min;
            }
            if (signal[0] > max)
            {
                signal[0] = max;
            }
        }

        if ((int)GET_SFUNC_PARAM(EN_TIME_TAG_ARG)[0] == 1)
        {
            outTimeTags[0] = time[i];
        }
        if ((int)GET_SFUNC_PARAM(EN_STATUS_ARG)[0] == 1)
        {
            outStatus[0] = true;
        }
        if ((int)GET_SFUNC_PARAM(EN_RAW_ARG)[0] == 1)
        {
            outRaw[0] = msg;
        }
    }
}

static void mdlTerminate(SimStruct *S)
{

}

static void decodeBNR(double* signal, uint32_t startBit, uint32_t dataLength, bool isSigned, uint32_t msg)
{
    int32_t temp = (msg >> (startBit-1)) & ONES(dataLength);

    if (isSigned)
    {
        if (temp & (1<<(dataLength-1)))
        {
            temp |= ONES(32-dataLength) << dataLength; // extend sign bits
        }
    }

    
    signal[0] = (double)temp;
}

static void decodeBCD(double* signal, uint32_t startBit, uint32_t dataLength, uint32_t ssm, uint32_t msg)
{
    uint32_t temp = (msg >> (startBit-1)) & ONES(dataLength);
    double value = 0;
    int i;

    for (i = dataLength-4; i >= 0; i -= 4)
    {
        value = 10 * value + ((temp >> i) & 0xf);
    }

    // BCD negative sign
    if (ssm == 3)
    {
        value = -value;
    }

    signal[0] = value;
}

static void decodeDSC(double* signal, uint32_t startBit, uint32_t dataLength, uint32_t msg)
{
    signal[0] = (double)((msg >> (startBit-1)) & ONES(dataLength));
}

#include "sg_sfcn_glue.h"   // Code generation glue

