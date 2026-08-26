#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_arinc429_pack_s

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
    SSM_ARG,
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

static void encodeBNR(uint32_t* msg, uint32_t startBit, uint32_t dataLength, bool isSigned, double value);
static void encodeBCD(uint32_t* msg, uint32_t startBit, uint32_t dataLength, int32_t ssm, double value);
static void encodeDSC(uint32_t* msg, uint32_t startBit, uint32_t dataLength, double value);

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

    if (!ssSetNumInputPorts(S, nPorts)) return;

    for (i=0; i<nPorts; i++)
    {
        ssSetInputPortWidth(S, i, 1);
        ssSetInputPortDataType(S, i, SS_DOUBLE);
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1);
    }

    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_UINT32);

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

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    uint32_t msg, *outWord;
    int i, nSignals = (int)GET_SFUNC_PARAM_COLUMNS(SIGNALS_ARG);
    int signalsWidth = (int)GET_SFUNC_PARAM_ROWS(SIGNALS_ARG);
    double *signal, value;
    int32_t sdi, ssm = 0;

    sdi = (int32_t)GET_SFUNC_PARAM(SDI_ARG)[0];
    msg = (uint32_t)GET_SFUNC_PARAM(LABEL_ARG)[0] & 0xff;

    if ((int)GET_SFUNC_PARAM(HAS_SSM_ARG)[0] == 0) //Use default SSM instead of input signal
    {
        ssm = (int32_t)GET_SFUNC_PARAM(SSM_ARG)[0];
        if (ssm != -1)
        { 
            msg |= (ssm & 3) << 29;
        }
    }

    if (sdi != -1)
    { 
        msg |= (sdi & 3) << 8;
    }

    for (i=0; i<nSignals; i++)
    {
        signal = (double*)ssGetInputPortSignal(S, i);
        uint32_t startBit = (uint32_t)GET_SFUNC_PARAM(SIGNALS_ARG)[0+i*signalsWidth];
        uint32_t dataLength = (uint32_t)GET_SFUNC_PARAM(SIGNALS_ARG)[1+i*signalsWidth];
        double resolution = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[3+i*signalsWidth];
        double offset = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[4+i*signalsWidth];
        double min = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[5+i*signalsWidth];
        double max = (double)GET_SFUNC_PARAM(SIGNALS_ARG)[6+i*signalsWidth];
        bool isSigned = (bool)GET_SFUNC_PARAM(SIGNALS_ARG)[7+i*signalsWidth];

        if (signal[0] < min)
        {
            value = min;
        }
        else if (signal[0] > max)
        {
            value = max;
        }
        else
        {
            value = signal[0];
        }

        value = (value - offset) / resolution;

        switch((int)GET_SFUNC_PARAM(SIGNALS_ARG)[2+i*signalsWidth])
        {
            case BNR: encodeBNR(&msg, startBit, dataLength, isSigned, value); break;
            case BCD: encodeBCD(&msg, startBit, dataLength, ssm, value); break;
            case DSC: //Use the same for SSM
            case SSM: encodeDSC(&msg, startBit, dataLength, value); break;
            default: ssSetErrorStatus(S, "ARINC429 Pack: Unsupported data type\n"); return;
        }
    }

    outWord = (uint32_t*)ssGetOutputPortSignal(S, 0);
    outWord[0] = msg;
}

static void mdlTerminate(SimStruct *S)
{

}

static void encodeBNR(uint32_t* msg, uint32_t startBit, uint32_t dataLength, bool isSigned, double value)
{
    double temp, range;

    if (isSigned)
    {
        range = pow(2, dataLength-1);
    }
    else
    {
        range = pow(2, dataLength);
    }

    temp = round(value);

    if( temp >= range ) temp = range-1;

    if (isSigned)
    {
        if( temp < (range*(-1)) ) temp = range*(-1);
    }
    else
    {
        if( temp < 0 ) temp = 0;
    }
    
    *msg |= ((int32_t)temp & ONES(dataLength)) << (startBit-1);
}


static void encodeBCD(uint32_t* msg, uint32_t startBit, uint32_t dataLength, int32_t ssm, double value)
{
    uint32_t bcdVal = 0;
    uint32_t temp = (uint32_t)abs(round(value));
    int i;

    for (i = 0; i < dataLength; i += 4)
    {
        bcdVal |= (temp % 10) << i;
        temp /= 10;
    }

    *msg |= (bcdVal & ONES(dataLength)) << (startBit-1);

    // auto SSM processing if SSM signal is not used
    if (ssm == -1 && value < 0)
    { 
        *msg |= (3 << 29);    
    }
}


static void encodeDSC(uint32_t* msg, uint32_t startBit, uint32_t dataLength, double value)
{

    *msg |= ((uint32_t)value & ONES(dataLength)) << (startBit-1);
}

#include "sg_sfcn_glue.h"   // Code generation glue

