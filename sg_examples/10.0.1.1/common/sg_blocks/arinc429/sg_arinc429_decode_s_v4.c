
// The purpose of this block is to examine an ARINC input stream and extract,
// convert, and output messages of a type described by the input parameters.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_arinc429_decode_s_v4

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "simstruc.h"

#ifdef  MATLAB_MEX_FILE
#include "mex.h"
#else
#include "utildefs.h"
#endif

#define NUM_ARGS        	    10
#define LABEL_ARG       	    ssGetSFcnParam(S,0)  // integer in 0-255
#define DATA_TYPE_ARG   	    ssGetSFcnParam(S,1)  // vector of DataType_T
#define RESOLUTION_ARG  	    ssGetSFcnParam(S,2)  // vector of double
#define SDI_ARG                 ssGetSFcnParam(S,3)
#define ENABLE_SDI_BITS         ssGetSFcnParam(S,4)
#define TIME_TAGS_ARG   	    ssGetSFcnParam(S,5)  // boolean
#define HOLD_LAST_VAL_ARG	    ssGetSFcnParam(S,6)  // boolean
#define ENABLE_STATUS           ssGetSFcnParam(S,7)
#define LABEL_OUTPUT            ssGetSFcnParam(S,8)
#define SSM_OUTPUT              ssGetSFcnParam(S,9)

#define NUM_I_WORKS     (0)

#define ONES(n)         ((n) > 31 ? 0xffffffff : (1 << (n)) - 1)
#define FIELD(i,lo,len) ((i >> lo) & ONES(len))

#define SSM(i)          FIELD(i, 29,  2)
#define DATA(i)         FIELD(i, 10, 19)
#define SDI(i)          FIELD(i,  8,  2)
#define LABEL(i)        FIELD(i,  0,  8)

#define STANDARD_DATA_BITS  19
#define EXTENDED_DATA_BITS  21
#define STANDARD_BIT_SHIFT  10
#define EXTENDED_BIT_SHIFT  8

#define MAX_PACKET_SIZE 256

typedef enum {RAW = 1, BNR, BCD, DISCRETES} Type_T;

static char msg[256];

static double decodeBcd(uint32_t w) {
    double x = 0;
    int i;

    for (i = 16; i >= 0; i -= 4) {
        x = 10 * x + ((w >> i) & 0xf);
    }
    return x;
}

static void mdlInitializeSizes(SimStruct *S)
{
    bool labelOutput = (bool)mxGetPr(LABEL_OUTPUT)[0];
    bool ssmOutput = (bool)mxGetPr(SSM_OUTPUT)[0];
    bool timeTags = (bool)mxGetPr(TIME_TAGS_ARG)[0];
    bool status = (bool)mxGetPr(ENABLE_STATUS)[0];
    int i, numWords = (int)mxGetN(LABEL_ARG);

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed",
                NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    if (timeTags == true)
    {
        ssSetNumInputPorts(S, 3);
        ssSetInputPortDimensionInfo( S, 2, DYNAMIC_DIMENSION);
        ssSetInputPortDataType(S, 2, SS_UINT32);
        ssSetInputPortDirectFeedThrough(  S, 2, 1);
        ssSetInputPortRequiredContiguous( S, 2, 1);
    }
    else
    {
        ssSetNumInputPorts(S, 2);
    }
    
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortDirectFeedThrough(  S, 0, 1);
    ssSetInputPortRequiredContiguous( S, 0, 1);
    ssSetInputPortDimensionInfo( S, 1, DYNAMIC_DIMENSION);
    ssSetInputPortDataType(S, 1, SS_UINT32);
    ssSetInputPortDirectFeedThrough(  S, 1, 1);
    ssSetInputPortRequiredContiguous( S, 1, 1);


    if ((timeTags == true) && (status == true) && (labelOutput == true) && (ssmOutput == true))
    {
        ssSetNumOutputPorts(S, 5);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //SSM
        ssSetOutputPortWidth(S, 3, numWords); //Timetags
        ssSetOutputPortWidth(S, 4, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 3, SS_UINT32); //Timetags
        ssSetOutputPortDataType(S, 4, SS_BOOLEAN); //Status
    }
    else if ((timeTags == true) && (status == true) && (labelOutput == true))
    {
        ssSetNumOutputPorts(S, 4);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //Timetags
        ssSetOutputPortWidth(S, 3, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT32); //Timetags
        ssSetOutputPortDataType(S, 3, SS_BOOLEAN); //Status
    }
    else if ((timeTags == true) && (status == true) && (ssmOutput == true))
    {
        ssSetNumOutputPorts(S, 4);
        ssSetOutputPortWidth(S, 1, numWords); //SSM
        ssSetOutputPortWidth(S, 2, numWords); //Timetags
        ssSetOutputPortWidth(S, 3, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 2, SS_UINT32); //Timetags
        ssSetOutputPortDataType(S, 3, SS_BOOLEAN); //Status
    }
    else if ((timeTags == true) && (ssmOutput == true) && (labelOutput == true))
    {
        ssSetNumOutputPorts(S, 4);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //SSM
        ssSetOutputPortWidth(S, 3, numWords); //Timetags
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 3, SS_UINT32); //Timetags
    }
    else if ((ssmOutput == true) && (status == true) && (labelOutput == true))
    {
        ssSetNumOutputPorts(S, 4);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //SSM
        ssSetOutputPortWidth(S, 3, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 3, SS_BOOLEAN); //Status
    }
    else if ((labelOutput == true) && (timeTags == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //Timetags
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT32); //Timetags
    }
    else if ((labelOutput == true) && (status == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_BOOLEAN); //Status
    }
    else if ((timeTags == true) && (status == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //Timetags
        ssSetOutputPortWidth(S, 2, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT32); //Timetags
        ssSetOutputPortDataType(S, 2, SS_BOOLEAN); //Status
    }
    else if ((ssmOutput == true) && (timeTags == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //SSM
        ssSetOutputPortWidth(S, 2, numWords); //Timetags
        ssSetOutputPortDataType(S, 1, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 2, SS_UINT32); //Timetags
    }
    else if ((ssmOutput == true) && (status == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //SSM
        ssSetOutputPortWidth(S, 2, numWords); //Status
        ssSetOutputPortDataType(S, 1, SS_UINT8); //SSM
        ssSetOutputPortDataType(S, 2, SS_BOOLEAN); //Status
    }
    else if ((ssmOutput == true) && (labelOutput == true))
    {
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 1, numWords); //Label
        ssSetOutputPortWidth(S, 2, numWords); //SSM
        ssSetOutputPortDataType(S, 1, SS_UINT16); //Label
        ssSetOutputPortDataType(S, 2, SS_UINT8); //SSM
    }
    else if (labelOutput == true)
    {
        ssSetNumOutputPorts(S, 2);
        ssSetOutputPortWidth(S, 1, numWords);
        ssSetOutputPortDataType(S, 1, SS_UINT16);
    }
    else if (ssmOutput == true)
    {
        ssSetNumOutputPorts(S, 2);
        ssSetOutputPortWidth(S, 1, numWords);
        ssSetOutputPortDataType(S, 1, SS_UINT8);
    }
    else if (timeTags == true)
    {
        ssSetNumOutputPorts(S, 2);
        ssSetOutputPortWidth(S, 1, numWords);
        ssSetOutputPortDataType(S, 1, SS_UINT32);
    }
    else if (status == true)
    {
        ssSetNumOutputPorts(S, 2);
        ssSetOutputPortWidth(S, 1, numWords);
        ssSetOutputPortDataType(S, 1, SS_BOOLEAN);
    }
    else
    {
        ssSetNumOutputPorts(S, 1);
    }

    //Data
    ssSetOutputPortWidth(S, 0, numWords);
    if (((int)mxGetPr(DATA_TYPE_ARG)[0] == 2) || ((int)mxGetPr(DATA_TYPE_ARG)[0] == 3))  //BNR or BCD
    {
        ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    }
    else
    {
        ssSetOutputPortDataType(S, 0, SS_UINT32);
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumIWork(S, NUM_I_WORKS);
    ssSetNumRWork(S, 0);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUM_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );
}

#ifdef MATLAB_MEX_FILE
// We only set the dimension info when this is a MEX file, not on the target.
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(
                                         SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    if (!ssSetInputPortDimensionInfo( S, portIndex, dimsInfo)) return;
}

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(
                                          SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo( S, portIndex, dimsInfo)) return;
}
#endif

static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
}



static void mdlOutputs(SimStruct *S, int_T tid)
{
//#ifndef MATLAB_MEX_FILE -> Allow Simulink desktop use
    bool labelOutput = (bool) mxGetPr(LABEL_OUTPUT)[0];
    bool ssmOutput = (bool) mxGetPr(SSM_OUTPUT)[0];
    bool timeTags = (bool) mxGetPr(TIME_TAGS_ARG)[0];
    bool status = (bool) mxGetPr(ENABLE_STATUS)[0];
    int numWords = (int)mxGetN(LABEL_ARG); // number of words per output message
    int inWidth = (int)ssGetInputPortWidth(S, 1);
    uint32_t *inCnt = (uint32_t *) ssGetInputPortSignal(S, 0);
    uint32_t *inData = (uint32_t *) ssGetInputPortSignal(S, 1);
    uint32_t *outData = (uint32_t *) ssGetOutputPortSignal(S, 0);
    double *outDataDouble = (double *) ssGetOutputPortSignal(S, 0);

    Type_T   type;
    uint32_t inWord, *time, *outTimeTags;
    uint16_t *outLabel;
    uint8_t *outSSM;
    double   resolution;
    int    i, j, inCount;
	bool   *outStatus;

    int temp, dataBits, bitShift;
	double range, value=0;
	
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

    if (labelOutput)
    {
        outLabel = (uint16_t*)ssGetOutputPortSignal(S, 1);
    }

    if (ssmOutput)
    {
        if (labelOutput)
        {
            outSSM = (uint8_t*)ssGetOutputPortSignal(S, 2);
        }
        else
        {
            outSSM = (uint8_t*)ssGetOutputPortSignal(S, 1);
        }
    }

    if (timeTags)
    {
        time = (uint32_t *) ssGetInputPortSignal(S, 2);
        if (labelOutput)
        {
            if (ssmOutput)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 3);
            }
            else
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 2);
            }
        }
        else
        {
            if (ssmOutput)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 2);
            }
            else
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 1);
            }
        }
    }

    if (status)
    {
        if (labelOutput)
        {
            if (timeTags)
            {
                if (ssmOutput)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 4);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 3);
                }
            }
            else
            {
                if (ssmOutput)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 3);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
            }
        }
        else
        {
            if (timeTags)
            {
                if (ssmOutput)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 3);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
            }
            else
            {
                if (ssmOutput)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 1);
                }
            }
        }
    }
    
    //Init status
    if (status)
    {
        for (i=0; i<numWords; i++)
        {
            outStatus[i] = false;
        }
    }

    //Init outputs
    if ((bool)mxGetPr(HOLD_LAST_VAL_ARG)[0] == false)
    {
        for (i = 0; i<numWords; i++)
        {
            outData[i] = 0;
        }
    }

    //Init label output
    if (labelOutput)
    {
        for (i = 0; i < numWords; i++)
        {
            uint8_t r, n = 0;
            uint16_t num = (uint16_t)mxGetPr(LABEL_ARG)[i];

            outLabel[i] = 0;

            while (num != 0)    //Convert to octal
            {
                r = num % 8;
                outLabel[i] += r * pow(10, n);
                n++;
                num = num / 8;
            }
        }
    }

    inCount = (int)(inCnt)[0];
	//SG_PRINTF(TRACE,"InCnt %d\n",inCount);

    if (inCount < 0 || inCount > inWidth) { // should never happen
        sprintf(msg, "decode inCount %d inWidth %d", inCount, inWidth);
        ssSetErrorStatus(S, msg);
        return;
    }
	
    for (i = 0; i < inCount; i++)
    {
        inWord = inData[i];
        
        j = 0;
        while ((LABEL(inWord) != (unsigned int)mxGetPr(LABEL_ARG)[j]) && (j<(numWords-1)))  //Why numWords -1? -> post increment of j
        {
            j++;
        }

        if (LABEL(inWord) == (unsigned int)mxGetPr(LABEL_ARG)[j])
        {
            //SG_PRINTF(TRACE,"LabelCnt %d\n",j);

            if ((Type_T)mxGetPr(DATA_TYPE_ARG)[j] != RAW)
            {
                if ((int)mxGetPr(SDI_ARG)[j] != -1)
                {
                    if (SDI(inWord) != (int)mxGetPr(SDI_ARG)[j])
                    {
                        continue;
                    }
                }
            }
            type = (Type_T)mxGetPr(DATA_TYPE_ARG)[j];
            resolution = (double)mxGetPr(RESOLUTION_ARG)[j];

            switch (type)
            {
            case RAW:
                outData[j] = FIELD(inWord, 8, 24);   //Allow to read parity bit
                break;

            case BNR:
                temp = FIELD(inWord, bitShift, dataBits);
                if (FIELD(inWord, 28, 1))
                {
                    temp |= ONES(32-dataBits) << dataBits; // extend sign bits
                }
                value = (double)temp / range;  // normalize
                value = value * resolution;  // Scale it back to real units
                outDataDouble[j] = value;
                break;

            case BCD:
                value = decodeBcd(FIELD(inWord, 10, 19));
                if (SSM(inWord) == 3) { // BCD negative sign
                    value = -value;
                }
                value *= resolution;
                outDataDouble[j] = value;
                break;

            case DISCRETES:
                outData[j] = FIELD(inWord, bitShift, dataBits);
                break;
            }

            if (ssmOutput)
            {
                outSSM[j] = (uint8_t)SSM(inWord);
            }

            if (timeTags)
            {
                outTimeTags[j] = time[i];
            }
            if (status)
            {
                outStatus[j] = true;
            }
        }
        else
        {
            //ssPrintf("Label not found");
        }
    }	
	
//#endif
}

static void mdlTerminate(SimStruct *S)
{
}

#include "sg_sfcn_glue.h"   // Code generation glue
