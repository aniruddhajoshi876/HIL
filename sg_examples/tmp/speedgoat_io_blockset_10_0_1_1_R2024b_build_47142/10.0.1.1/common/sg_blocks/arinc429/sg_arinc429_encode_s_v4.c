
#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_arinc429_encode_s_v4

#include <stddef.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "simstruc.h" 

#ifdef  MATLAB_MEX_FILE
#include "mex.h"
#else
#include "utildefs.h"
#endif

#define NUM_ARGS                8
#define LABEL_ARG               ssGetSFcnParam(S,0) // integer in 0-255
#define DATA_TYPE_ARG           ssGetSFcnParam(S,1) // vector of Type_T
#define RESOLUTION_ARG          ssGetSFcnParam(S,2) // vector of double
#define BITS_ARG                ssGetSFcnParam(S,3) // number of bits in a BNR value
#define SDI_ARG                 ssGetSFcnParam(S,4) // vector of 0-3 or -1 to leave SDI bits alone
#define SSM_ARG                 ssGetSFcnParam(S,5) // vector of 0-3 or -1 to auto compute
#define ENABLE_SSM              ssGetSFcnParam(S,6)
#define ENABLE_SDI_BITS         ssGetSFcnParam(S,7)

#define NUM_I_WORKS      (0)
#define NUM_R_WORKS      (0)
#define NUM_P_WORKS      (0)

#define ONES(n)          ((n) > 31 ? 0xffffffff : (1 << (n)) - 1)
#define BITS(lo,len)     (ONES(len) << lo)

#define MIN_BNR          (-262144)
#define MAX_BNR          ( 262143)
#define MIN_BCD          (-79999)
#define MAX_BCD          ( 79999)

#define STANDARD_DATA_BITS  19
#define EXTENDED_DATA_BITS  21
#define STANDARD_BIT_SHIFT  10
#define EXTENDED_BIT_SHIFT  8

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))

#define CLAMP_BNR(x)     (CLAMP((x), MIN_BNR, MAX_BNR))
#define CLAMP_BCD(x)     (CLAMP((x), MIN_BCD, MAX_BCD))

#define MAX_PACKET_SIZE 256

typedef enum {RAW = 1, BNR, BCD, DISCRETES} Type_T;

static char msg[256];

static uint32_t encodeBcd(int x) {
    uint32_t v = (x < 0) ? -x : x;
    uint32_t w = 0;
    int i;

    for (i = 0; i <= 16; i += 4) {
        w |= (v % 10) << i;
        v /= 10;
    }
    return w;
}

static void mdlInitializeSizes(SimStruct *S)
{
    int width = (int)mxGetN(LABEL_ARG);	//limit max width?
    int i;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed", 
            NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
    {
        ssSetNumInputPorts(S, 2);
        ssSetInputPortWidth(S, 1, width);
        ssSetInputPortDataType(S, 1, SS_UINT8);
        ssSetInputPortDirectFeedThrough(S, 1, 1);
        ssSetInputPortRequiredContiguous(S, 1, 1);
    }
    else
    {
        ssSetNumInputPorts(S, 1);
    }

    ssSetInputPortWidth(S, 0, width);
    if (((int)mxGetPr(DATA_TYPE_ARG)[0] == 2) || ((int)mxGetPr(DATA_TYPE_ARG)[0] == 3))  //BNR or BCD
    {
        ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }
    else
    {
        ssSetInputPortDataType(S, 0, SS_UINT32);
    }
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, width);
    ssSetOutputPortDataType(S, 0, SS_UINT32);

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumRWork(S, NUM_R_WORKS);
    ssSetNumIWork(S, NUM_I_WORKS);
    ssSetNumPWork(S, NUM_P_WORKS);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUM_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );
}
 
static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
}



static void mdlOutputs(SimStruct *S, int_T tid)
{
//#ifndef MATLAB_MEX_FILE -> Allow Simulink desktop use
    int width = (int)ssGetInputPortWidth(S, 0);
    double *inPortDouble = (double *)ssGetInputPortSignal(S, 0);
    uint32_t *inPort = (uint32_t *)ssGetInputPortSignal(S, 0);
    uint32_t *outPort = (uint32_t *)ssGetOutputPortSignal(S, 0);

    int i, dataBits, bitShift;
    Type_T    type;
    int32_t   itemp;
    double    resolution, rtemp, range;
    uint32_t  label, bits, outWord;
    int32_t   sdi, ssm;

    if ((int)mxGetPr(ENABLE_SDI_BITS)[0] == 1)
    {
        dataBits = EXTENDED_DATA_BITS;
        bitShift = EXTENDED_BIT_SHIFT;
        range = pow(2, dataBits-1);
    }
    else
    {
        dataBits = STANDARD_DATA_BITS;
        bitShift = STANDARD_BIT_SHIFT;
        range = pow(2, dataBits-1);
    }
    
    for (i = 0; i < width; i++)
    {
        label      = (uint32_t) mxGetPr(LABEL_ARG)[i];
        type       = (Type_T)   mxGetPr(DATA_TYPE_ARG)[i];
        resolution = (double)   mxGetPr(RESOLUTION_ARG)[i];
        bits       = (uint32_t) mxGetPr(BITS_ARG)[i];
        
        if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
        {
            uint8_t *temp;
            temp = (uint8_t*)ssGetInputPortSignal(S, 1);
            ssm = (int32_t)temp[i];
        }
        else
        {
            ssm = (int32_t)mxGetPr(SSM_ARG)[i];
        }

        switch (type) {

            case RAW:
                outWord = label & 0xff;
                outWord |= (inPort[i] & ONES(24)) << 8; //Allow to set parity bit if mode None is selected
                break;

            case BNR:
                outWord = label & 0xff;
                rtemp = inPortDouble[i] / resolution;  // divide by scale factor
                rtemp = rtemp * range;  // scale to amount of bits
                if( rtemp >= range ) rtemp = range-1;
                if( rtemp < (range*(-1)) ) rtemp = range*(-1);
                itemp = (int32_t)rtemp;   // truncate to integer
                outWord |= (itemp & ONES(dataBits) & ~ONES(dataBits-bits)) << bitShift;
                break;

            case BCD:
                outWord = label & 0xff;
                rtemp = inPortDouble[i] / resolution;
                itemp = (int32_t)(rtemp < 0 ? rtemp - 0.5 : rtemp + 0.5);   //round(rtemp)
                itemp = CLAMP_BCD(itemp);
                outWord |= encodeBcd(itemp) << 10;

                // auto SSM processing
                if (ssm == -1 && itemp < 0) { 
                    outWord |= (3 << 29);    
                }
                break;

            case DISCRETES:
                outWord = label & 0xff;
                outWord |= (inPort[i] & ONES(dataBits)) << bitShift;
                break;
                
            default:
            ssSetErrorStatus(S, "Unknown data type"); return;
        }

        if (type != RAW) {

            if ((int)mxGetPr(ENABLE_SDI_BITS)[0] == 0)
            {
                sdi = (int32_t)mxGetPr(SDI_ARG)[i];

                if (sdi != -1) {
                    outWord |= (sdi & 3) << 8;
                }
            }

            if (ssm != -1) { 
                outWord |= (ssm & 3) << 29;
            }
        }    
        
        outPort[i] = outWord;
    }
//#endif
}

static void mdlTerminate(SimStruct *S)
{
}

#include "sg_sfcn_glue.h"   // Code generation glue
