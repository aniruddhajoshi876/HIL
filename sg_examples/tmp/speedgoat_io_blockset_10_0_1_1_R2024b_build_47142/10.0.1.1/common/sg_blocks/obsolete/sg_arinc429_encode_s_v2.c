
#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_arinc429_encode_s_v2

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
#include "sg_printf.h"
#endif

#define NUM_ARGS                15
#define MODE_ARG                ssGetSFcnParam(S,0)
#define LABEL_ARG               ssGetSFcnParam(S,1) // integer in 0-255
#define DATA_TYPE_ARG           ssGetSFcnParam(S,2) // vector of Type_T
#define RESOLUTION_ARG          ssGetSFcnParam(S,3) // vector of double
#define BITS_ARG                ssGetSFcnParam(S,4) // number of bits in a BNR value
#define SDI_ARG                 ssGetSFcnParam(S,5) // vector of 0-3 or -1 to leave SDI bits alone
#define SSM_ARG                 ssGetSFcnParam(S,6) // vector of 0-3 or -1 to auto compute
#define CUSTOM_DATA_TYPE_ARG    ssGetSFcnParam(S,7)
#define DATA_LSB_ARG            ssGetSFcnParam(S,8)
#define DATA_MSB_ARG            ssGetSFcnParam(S,9)
#define BIT_POSITION            ssGetSFcnParam(S,10)
#define SCALE_BNR               ssGetSFcnParam(S,11)
#define BITS_EXPONENT           ssGetSFcnParam(S,12)
#define BITS_MANTISSA           ssGetSFcnParam(S,13)
#define ENABLE_SSM              ssGetSFcnParam(S,14)

#define NUM_I_WORKS      (0)
#define NUM_R_WORKS      (0)
#define NUM_P_WORKS      (0)

#define ONES(n)          ((n) > 31 ? 0xffffffff : (1 << (n)) - 1)
#define BITS(lo,len)     (ONES(len) << lo)

#define MIN_BNR          (-262144)
#define MAX_BNR          ( 262143)
#define MIN_BCD          (-79999)
#define MAX_BCD          ( 79999)

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))

#define CLAMP_BNR(x)     (CLAMP((x), MIN_BNR, MAX_BNR))
#define CLAMP_BCD(x)     (CLAMP((x), MIN_BCD, MAX_BCD))

#define STANDARD 	 	    1
#define MSG_SEQUENCE	    2
#define BIT_ORIENTED	    3
#define CUSTOM_DATA_TYPE    4

#define CUSTOM_DATA_RAW         1
#define CUSTOM_DATA_DISCRETE    2
#define CUSTOM_DATA_BNR         3
#define CUSTOM_DATA_FLOAT       4

#define MAX_PACKET_SIZE 256

typedef struct {uint32_t word, time;} Arinc_T;

typedef enum {RAW = 0, BNR, BCD, DISCRETES} Type_T;

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
    int  width = (int)mxGetN(DATA_TYPE_ARG);	//limit max width?
    int i, numBits;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed", 
            NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    
    if (((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE) &&
        ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_DISCRETE))
    {
        numBits = (int)mxGetN(BIT_POSITION);
        
        if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
        {
            ssSetNumInputPorts(S, numBits+1);
            ssSetInputPortWidth(S, numBits, 1);
            ssSetInputPortDataType(S, numBits, SS_DOUBLE);
            ssSetInputPortDirectFeedThrough(S, numBits, 1);
            ssSetInputPortRequiredContiguous(S, numBits, 1);
        }
        else
        {
            ssSetNumInputPorts(S, numBits);
        }
        
        for (i=0; i<numBits; i++)
        {
            ssSetInputPortWidth(S, i, 1);
            ssSetInputPortDataType(S, i, SS_BOOLEAN);
            ssSetInputPortDirectFeedThrough(S, i, 1);
            ssSetInputPortRequiredContiguous(S, i, 1);
        }
    }
    else
    {
        if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
        {
            ssSetNumInputPorts(S, 2);
            ssSetInputPortDataType(S, 1, SS_DOUBLE);
            ssSetInputPortDirectFeedThrough(S, 1, 1);
            ssSetInputPortRequiredContiguous(S, 1, 1);
            
            if (((int)mxGetPr(MODE_ARG)[0] == STANDARD) ||
                ((int)mxGetPr(MODE_ARG)[0] == MSG_SEQUENCE))
            {
                ssSetInputPortWidth(S, 1, width);
            }
            else
            {
                ssSetInputPortWidth(S, 1, 1);
            }
        }
        else
        {
            ssSetNumInputPorts(S, 1);
        }
        if (((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE) &&
        ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_RAW))
        {
            ssSetInputPortDataType(S, 0, SS_UINT32);
        }
        else
        {
            ssSetInputPortDataType(S, 0, SS_DOUBLE);
        }
        
        if ((int)mxGetPr(MODE_ARG)[0] == BIT_ORIENTED)
        {
            ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
        }
        else if ((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE)
        {
            ssSetInputPortWidth(S, 0, 1);
        }
        else
        {
            ssSetInputPortWidth(S, 0, width);
        }
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        ssSetInputPortRequiredContiguous(S, 0, 1);
    }
    
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);

	if ((int)mxGetPr(MODE_ARG)[0] == BIT_ORIENTED)
	{
		ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
	}
    else if ((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE)
    {
        ssSetOutputPortWidth(S, 0, 1);
    }
	else
	{
		ssSetOutputPortWidth(S, 0, width);
	}

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

#define MDL_SET_INPUT_PORT_WIDTH
static void mdlSetInputPortWidth( SimStruct *S, int_T port, int_T width )
{
	
	if( width > MAX_PACKET_SIZE )
    {
        sprintf(msg, "Input vector width of input port %d must be less than %d\n", port, MAX_PACKET_SIZE);
        ssSetErrorStatus(S,msg);
        return;
    }
    ssSetInputPortWidth( S, port, width );
}

#define MDL_SET_OUTPUT_PORT_WIDTH
static void mdlSetOutputPortWidth( SimStruct *S, int_T port, int_T width )
{
	//printf("Input Port Size %d\n",ssGetInputPortWidth(S, port));
    ssSetOutputPortWidth( S, port, ssGetInputPortWidth(S, port) );
}

#define MDL_START 
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE

    int  width   = (int) ssGetInputPortWidth(S, 0);
    real_T   *inPort  = (real_T *) ssGetInputPortSignal(S, 0);
    Arinc_T  *outPort = (Arinc_T *) ssGetOutputPortSignal(S, 0);

    int i, j;
    int32_t   itemp;
    real_T    resolution, rtemp;
    uint32_t  outWord, label;
    
    
    for (i = 0; i < width; i++)
    {
		if ((int)mxGetPr(MODE_ARG)[0] != STANDARD)
		{
			label = (uint32_t)mxGetPr(LABEL_ARG)[0];
		}
		else
		{
			label = (uint32_t)mxGetPr(LABEL_ARG)[i];
		}
		
        if ((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE)
        {
            uint32_t temp, *inDataRaw;
            real_T range;
            bool *bit;
            int32_t exponent, exponentRaw;
            real_T mantissa, mantissaRaw;
            uint32_t sign = 0;
            int bitMask = (int)mxGetPr(DATA_MSB_ARG)[0]-(int)mxGetPr(DATA_LSB_ARG)[0]+1;
            int32_t ssm;
            real_T *tempSsm;
            
            if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
            {
                if ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_DISCRETE)
                {
                    tempSsm = (real_T*)ssGetInputPortSignal(S, (int)mxGetN(BIT_POSITION));
                }
                else
                {
                    tempSsm = (real_T*)ssGetInputPortSignal(S, 1);
                }
                ssm = (int32_t)tempSsm[0];
            }
            else
            {
                //ssm = (int32_t)mxGetPr(SSM_ARG)[0];
                ssm = -1;   //Mask param not available in custom mode
            }
            
            switch ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0])
            {
                case CUSTOM_DATA_RAW:
                    inDataRaw  = (uint32_t*)ssGetInputPortSignal(S, 0);
                    
                    outWord = label & 0xff;
                    temp = *inDataRaw;
                    temp = temp & ONES(bitMask);
                    outWord |= temp<<((int)mxGetPr(DATA_LSB_ARG)[0]-1);
                break;
                
                case CUSTOM_DATA_DISCRETE:
                    outWord = label & 0xff;
                    for (j=0; j<(int)mxGetN(BIT_POSITION); j++)
                    {
                        bit = (bool*)ssGetInputPortSignal(S, j);
                        outWord |= *bit << ((int)mxGetPr(BIT_POSITION)[j]-1);
                    }
                break;
                
                case CUSTOM_DATA_BNR:
                    resolution = (real_T)mxGetPr(SCALE_BNR)[0];
                    range = pow(2, bitMask-1);
                    
                    outWord = label & 0xff;
                    rtemp = inPort[0] / resolution;   //normalize (value between: -1 .. 0 .. 1)
                    rtemp = rtemp * range;   //Scale to amount of bits
                    if (rtemp > range) rtemp = range;
                    if (rtemp < ((range-1)*(-1))) rtemp = (range-1)*(-1);
                    itemp = (int32_t)rtemp;   // truncate to integer
                    outWord |= (itemp & ONES(bitMask)) << ((int)mxGetPr(DATA_LSB_ARG)[0]-1);
                break;
                
                case CUSTOM_DATA_FLOAT:
                    outWord = label & 0xff;
                    rtemp = fabs(inPort[0]);
                    
                    if (inPort[0] < 0)
                    {
                        sign = 1;
                    }
                    if (rtemp != 0.0)   //prevent overflows
                    {
                        exponent = (int32_t)floor(log2(rtemp));
                        exponentRaw = exponent + (int32_t)pow(2, (int)mxGetPr(BITS_EXPONENT)[0]-1) - 1;  //add bias
                        mantissa = rtemp / pow(2, exponent) - 1;
                        mantissaRaw = mantissa * pow(2, (int)mxGetPr(BITS_MANTISSA)[0]); //Scale to amount of bits
                        outWord |= sign << ((int)mxGetPr(DATA_MSB_ARG)[0]-1);
                        outWord |= (exponentRaw & ONES((int)mxGetPr(BITS_EXPONENT)[0])) << ((int)mxGetPr(DATA_LSB_ARG)[0]+(int)mxGetPr(BITS_MANTISSA)[0]-1);
                        outWord |= ((uint32_t)mantissaRaw & ONES((int)mxGetPr(BITS_MANTISSA)[0])) << ((int)mxGetPr(DATA_LSB_ARG)[0]-1);
                    }
                break;
                
                default:
                ssSetErrorStatus(S, "Unknown input data type"); return;
            }
            
            if (ssm != -1)
            { 
                outWord |= (ssm & 3) << 29;
            }
        }
        else
		{
            Type_T    type;
            real_T    *temp;
            int32_t   sdi, ssm;
            uint32_t  bits;
            
            if ((int)mxGetPr(MODE_ARG)[0] == BIT_ORIENTED)
            {
                //if input DYNAMICALLY_SIZED use same setting for all messages
                sdi        = (int32_t)  mxGetPr(SDI_ARG)[0];
                type       = (Type_T)   mxGetPr(DATA_TYPE_ARG)[0];
                resolution = (real_T)   mxGetPr(RESOLUTION_ARG)[0];
                bits       = (uint32_t) mxGetPr(BITS_ARG)[0];
                
                if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
                {
                    temp = (real_T*)ssGetInputPortSignal(S, 1);
                    ssm = (int32_t)temp[0];
                }
                else
                {
                    ssm = (int32_t)mxGetPr(SSM_ARG)[0];
                }
            }
            else
            {
                sdi        = (int32_t)  mxGetPr(SDI_ARG)[i];
                type       = (Type_T)   mxGetPr(DATA_TYPE_ARG)[i];
                resolution = (real_T)   mxGetPr(RESOLUTION_ARG)[i];
                bits       = (uint32_t) mxGetPr(BITS_ARG)[i];
                
                if ((int)mxGetPr(ENABLE_SSM)[0] == 1)
                {
                    temp = (real_T*)ssGetInputPortSignal(S, 1);
                    ssm = (int32_t)temp[i];
                }
                else
                {
                    ssm = (int32_t)mxGetPr(SSM_ARG)[i];
                }
            }

            switch (type) {

              case RAW:
                    outWord = (uint32_t)inPort[i];
                    break;

              case BNR:
                    outWord = label & 0xff;
                    rtemp = inPort[i] / resolution;  // divide by scale factor
                    rtemp = rtemp * (real_T)0x40000;  // 2**18, an 18 bit left shift, but in double
                    if( rtemp > MAX_BNR ) rtemp = MAX_BNR;
                    if( rtemp < MIN_BNR ) rtemp = MIN_BNR;
                    itemp = (int32_t)rtemp;   // truncate to integer
                    outWord |= (itemp & ONES(19) & ~ONES(19-bits)) << 10;
                    break;

                case BCD:
                    outWord = label & 0xff;
                    rtemp = inPort[i] / resolution;
                    itemp = (int32_t)(rtemp < 0 ? rtemp - 0.5 : rtemp + 0.5);
                    itemp = CLAMP_BCD(itemp);
                    outWord |= encodeBcd(itemp) << 10;

                    // auto SSM processing
                    if (ssm == -1 && itemp < 0) { 
                        outWord |= (3 << 29);    
                    }
                    break;

                case DISCRETES:
                    outWord = label & 0xff;
                    itemp = (int32_t)inPort[i];
                    outWord |= (itemp & ONES(19)) << 10;
                    break;
                    
                default:
                ssSetErrorStatus(S, "Unknown data type"); return;
            }

            if (type != RAW) {

                if (sdi != -1) {
                    outWord |= (sdi & 3) << 8;
                }

                if (ssm != -1) { 
                    outWord |= (ssm & 3) << 29;
                }
            }    
        }
        outPort[i].word = outWord;
        outPort[i].time = 0;
    }
#endif
}

static void mdlTerminate(SimStruct *S)
{
}

#include "sg_sfcn_glue.h"   // Code generation glue
