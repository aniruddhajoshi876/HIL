
// The purpose of this block is to examine an ARINC input stream and extract,
// convert, and output messages of a type described by the input parameters.

// The input port width adapts to that of source block (normally a Receive block).
// The first element of the input port is assumed to be a normal double containing
// a count of the number of valid signals available and the remaining elements,
// while known to Simulink as doubles, are actually of type arinc_T, a structure
// holding an ARINC word and a timestamp, each of which are 32-bit unsigned integers.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_arinc429_decode_s_v2

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

#define NUM_ARGS        	    16
#define MODE_ARG         	    ssGetSFcnParam(S,0)
#define LABEL_ARG       	    ssGetSFcnParam(S,1)  // integer in 0-255
#define DATA_TYPE_ARG   	    ssGetSFcnParam(S,2)  // vector of DataType_T
#define RESOLUTION_ARG  	    ssGetSFcnParam(S,3)  // vector of real_T
#define SYNC_MASK_ARG   	    ssGetSFcnParam(S,4)  // integer
#define SYNC_DATA_ARG   	    ssGetSFcnParam(S,5)  // integer [sync1] or [sync1, sync2]
#define CUSTOM_DATA_TYPE_ARG    ssGetSFcnParam(S,6)
#define DATA_LSB_ARG            ssGetSFcnParam(S,7)
#define DATA_MSB_ARG            ssGetSFcnParam(S,8)
#define BIT_POSITION            ssGetSFcnParam(S,9)
#define SCALE_BNR               ssGetSFcnParam(S,10)
#define BITS_EXPONENT           ssGetSFcnParam(S,11)
#define BITS_MANTISSA           ssGetSFcnParam(S,12)
#define TIME_TAGS_ARG   	    ssGetSFcnParam(S,13)  // boolean
#define HOLD_LAST_VAL_ARG	    ssGetSFcnParam(S,14)  // boolean
#define ENABLE_STATUS           ssGetSFcnParam(S,15)

#define NUM_I_WORKS     (2)
#define STATE_I_IND     (0)
#define COUNT_I_IND     (1)

#define BUFFER_R_IND    (0)

// must get IWorks and RWorks as necessary before using the following macros!

#define STATE           (IWork[STATE_I_IND])        // current State_T
#define COUNT           (IWork[COUNT_I_IND])        // current number of words in BUFFER
#define BUFFER(i)       (RWork[BUFFER_R_IND + i])

#define ONES(n)         ((n) > 31 ? 0xffffffff : (1 << (n)) - 1)
#define FIELD(i,lo,len) ((i >> lo) & ONES(len))

#define SSM(i)          FIELD(i, 29,  2)
#define DATA(i)         FIELD(i, 10, 19)
#define SDI(i)          FIELD(i,  8,  2)
#define LABEL(i)        FIELD(i,  0,  8)

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

typedef enum {INITIAL = 0, SYNCHING, SYNCHED} State_T;

typedef enum {BNR_FAILURE = 0, BNR_NO_DATA, BNR_TEST, BNR_NORMAL} BNR_SSM_T;

typedef enum {BCD_PLUS = 0, BCD_NO_DATA, BCD_TEST, BCD_MINUS} BCD_SSM_T;

static char msg[256];

static real_T decodeBcd(uint32_t w) {
    real_T x = 0;
    int i;

    for (i = 16; i >= 0; i -= 4) {
        x = 10 * x + ((w >> i) & 0xf);
    }
    return x;
}

static real_T decode(uint32_t inWord, Type_T type, real_T resolution)
{
	int temp;
	real_T value=0;
	
	switch (type)
	{
	  case RAW:
		value = inWord;
		break;

	  case BNR:
		temp = FIELD(inWord, 10, 19);
		if (FIELD(inWord, 28, 1))
		{
			temp |= ONES(13) << 19; // extend sign bits
		}
		value = (real_T)temp / (real_T)0x40000;  // divide by 2^18
		value = value * resolution;  // Scale it back to real units
		break;

	  case BCD:
		value = decodeBcd(FIELD(inWord, 10, 19));
		if (SSM(inWord)     == 3) { // BCD negative sign
			value = -value;
		}
		value *= resolution;
		break;

	  case DISCRETES:
		value = DATA(inWord);
		break;
	}
	return value;
}

static void mdlInitializeSizes(SimStruct *S)
{
    bool timeTags = (bool) mxGetPr(TIME_TAGS_ARG)[0];
    bool status = (bool) mxGetPr(ENABLE_STATUS)[0];
    int numWords = (int)mxGetN(DATA_TYPE_ARG);
    int outWidth = 0;
    int numBits;
    int i;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed",
                NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumInputPorts(S, 1);
    ssSetInputPortDimensionInfo( S, 0, DYNAMIC_DIMENSION);
    ssSetInputPortDirectFeedThrough(  S, 0, 1);
    ssSetInputPortRequiredContiguous( S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    
    
    if ((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE)
    {
        if ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_DISCRETE)
        {
            numBits = (int)mxGetN(BIT_POSITION);
            
            if ((timeTags == true) && (status == true))
            {
                ssSetNumOutputPorts(S, (numBits+2));
                ssSetOutputPortWidth(S, numBits, 1); //Timetags
                ssSetOutputPortWidth(S, numBits+1, 1); //Status
                ssSetOutputPortDataType(S, numBits, SS_UINT32); //Timetags
                ssSetOutputPortDataType(S, numBits+1, SS_BOOLEAN); //Status
            }
            else if (timeTags == true)
            {
                ssSetNumOutputPorts(S, (numBits+1));
                ssSetOutputPortWidth(S, numBits, 1);
                ssSetOutputPortDataType(S, numBits, SS_UINT32);
            }
            else if (status == true)
            {
                ssSetNumOutputPorts(S, (numBits+1));
                ssSetOutputPortWidth(S, numBits, 1);
                ssSetOutputPortDataType(S, numBits, SS_BOOLEAN);
            }
            else
            {
                ssSetNumOutputPorts(S, numBits);
            }
            for (i=0; i<numBits; i++)
            {
                ssSetOutputPortWidth(S, i, 1);
                ssSetOutputPortDataType(S, i, SS_BOOLEAN);
            }
        }
        else
        {
            if ((timeTags == true) && (status == true))
            {
                ssSetNumOutputPorts(S, 3);
                ssSetOutputPortWidth(S, 1, 1); //Timetags
                ssSetOutputPortWidth(S, 2, 1); //Status
                ssSetOutputPortDataType(S, 1, SS_UINT32); //Timetags
                ssSetOutputPortDataType(S, 2, SS_BOOLEAN); //Status
            }
            else if (timeTags == true)
            {
                ssSetNumOutputPorts(S, 2);
                ssSetOutputPortWidth(S, 1, 1);
                ssSetOutputPortDataType(S, 1, SS_UINT32);
            }
            else if (status == true)
            {
                ssSetNumOutputPorts(S, 2);
                ssSetOutputPortWidth(S, 1, 1);
                ssSetOutputPortDataType(S, 1, SS_BOOLEAN);
            }
            else
            {
                ssSetNumOutputPorts(S, 1);
            }
            ssSetOutputPortWidth(S, 0, 1);
            if ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_RAW)
            {
                ssSetOutputPortDataType(S, 0, SS_UINT32);
            }
            else    //BNR or FLOAT
            {
                ssSetOutputPortDataType(S, 0, SS_DOUBLE);
            }
        }
    }
    else
    {
        if ((int)mxGetPr(MODE_ARG)[0] == BIT_ORIENTED)
        {
            outWidth = MAX_PACKET_SIZE;
        }
        else
        {
            outWidth = numWords;
        }
        if ((int)mxGetPr(MODE_ARG)[0] == STANDARD)
        {
            if ((timeTags == true) && (status == true))
            {
                ssSetNumOutputPorts(S, 3);
                ssSetOutputPortWidth(S, 1, outWidth); //Timetags
                ssSetOutputPortWidth(S, 2, outWidth); //Status
                ssSetOutputPortDataType(S, 1, SS_UINT32); //Timetags
                ssSetOutputPortDataType(S, 2, SS_BOOLEAN); //Status
            }
            else if (timeTags == true)
            {
                ssSetNumOutputPorts(S, 2);
                ssSetOutputPortWidth(S, 1, outWidth);
                ssSetOutputPortDataType(S, 1, SS_UINT32);
            }
            else if (status == true)
            {
                ssSetNumOutputPorts(S, 2);
                ssSetOutputPortWidth(S, 1, outWidth);
                ssSetOutputPortDataType(S, 1, SS_BOOLEAN);
            }
            else
            {
                ssSetNumOutputPorts(S, 1);
            }
        }
        else
        {
            if ((timeTags == true) && (status == true))
            {
                ssSetNumOutputPorts(S, 4);
                ssSetOutputPortWidth(S, 2, outWidth); //Timetags
                ssSetOutputPortWidth(S, 3, 1); //Status
                ssSetOutputPortDataType(S, 2, SS_UINT32); //Timetags
                ssSetOutputPortDataType(S, 3, SS_BOOLEAN); //Status
            }
            else if (timeTags == true)
            {
                ssSetNumOutputPorts(S, 3);
                ssSetOutputPortWidth(S, 2, outWidth);
                ssSetOutputPortDataType(S, 2, SS_UINT32);
            }
            else if (status == true)
            {
                ssSetNumOutputPorts(S, 3);
                ssSetOutputPortWidth(S, 2, 1);
                ssSetOutputPortDataType(S, 2, SS_BOOLEAN);
            }
            else
            {
                ssSetNumOutputPorts(S, 2);
            }
            //Cnt
            ssSetOutputPortWidth(S, 1, 1);
            ssSetOutputPortDataType(S, 1, SS_UINT32);
        }
        //Data
        ssSetOutputPortWidth(S, 0, outWidth);
        ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumIWork(S, NUM_I_WORKS);
    if (timeTags)
    {
        ssSetNumRWork(S, 2*outWidth);
    }
    else
    {
        ssSetNumRWork(S, outWidth);
    }
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

#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

	int *IWork = ssGetIWork(S);

	//Init IWork vectors
	COUNT = 0;
	STATE = INITIAL;
	
	SG_PRINTF(DEBUG,"numWords %d\n",(int)mxGetN(DATA_TYPE_ARG));
	
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)

// Extract all words with the correct label from the input port and use
// them to assemble a message of length numWords in RWork. When a
// complete message has been assembled, copy it to outData[0:numWords-1],
// keeping a cumulative count of the number of such messages decoded
// during the current sample time in outCnt.

// A nonzero sync mask triggers the sync logic. There are two flavors of
// sync logic - oneSync and twoSync - depending on whether the user has
// specified one or two sync data (sync1 only, or both sync1 and sync2).
// Both flavors of sync logic examine the bits of incoming words specified
// by the sync mask in order to determine where multiword messages begin.

// oneSync logic syncs on the first word whose mask bits contain the pattern
// sync1 (and where the mask bits of the preceding word do not).

// twoSync logic syncs on the first word whose mask bits contain the pattern
// sync2 (and where the mask bits of the preceding word contain the pattern
// sync1).
//
// Once synched, all subsequent input words (with the specified label) are
// added to the message buffer until it has been filled. At that point the
// message is put out on the output port and the state is reset to begin
// looking for the beginning of the next message.

{
#ifndef MATLAB_MEX_FILE
    int *IWork = ssGetIWork(S);
    real_T *RWork = ssGetRWork(S);
    uint32_t mask = (uint32_t)mxGetPr(SYNC_MASK_ARG)[0];
    bool twoSync = (mxGetN(SYNC_DATA_ARG) > 1);
    uint32_t sync1 = (uint32_t)mxGetPr(SYNC_DATA_ARG)[0];
    uint32_t sync2 = (uint32_t)(twoSync ? mxGetPr(SYNC_DATA_ARG)[1] : 0);
    bool timeTags = (bool) mxGetPr(TIME_TAGS_ARG)[0];
    bool status = (bool) mxGetPr(ENABLE_STATUS)[0];
    int numWords = (int)mxGetN(DATA_TYPE_ARG); // number of words per output message
    int inWidth = (int)ssGetInputPortWidth(S, 0);
    Arinc_T *inData = (Arinc_T *) ssGetInputPortSignal(S, 0);
    real_T *outData = (real_T *) ssGetOutputPortSignal(S, 0);
	int outWidth = (int)ssGetOutputPortWidth(S, 0);

    Type_T   type;
    uint32_t sync, inWord;
    real_T   resolution;
    int    i, j, inCount;
	bool endOfPacket, *outStatus;
    uint32_t *outCnt, *outTimeTags;
    
    //Init outputs
    if ((int)mxGetPr(MODE_ARG)[0] == CUSTOM_DATA_TYPE)
    {
        if ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_DISCRETE)
        {
            if ((bool)mxGetPr(HOLD_LAST_VAL_ARG)[0] == false)
            {
                bool *bit;
                for (j=0; j<(int)mxGetN(BIT_POSITION); j++)
                {
                    bit = (bool*) ssGetOutputPortSignal(S, j);
                    *bit = 0;
                }
            }
            if (timeTags)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, (int)mxGetN(BIT_POSITION));
            }
            if (status)
            {
                if (timeTags)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, (int)mxGetN(BIT_POSITION) + 1);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, (int)mxGetN(BIT_POSITION));
                }
            }
        }
        else if ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0] == CUSTOM_DATA_RAW)
        {
            if ((bool)mxGetPr(HOLD_LAST_VAL_ARG)[0] == false)
            {
                uint32_t *outDataRaw = (uint32_t*)ssGetOutputPortSignal(S, 0);
                *outDataRaw = 0;
            }
            if (timeTags)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 1);
            }
            if (status)
            {
                if (timeTags)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 1);
                }
            }
        }
        else
        {
            if ((bool)mxGetPr(HOLD_LAST_VAL_ARG)[0] == false)
            {
                *outData = 0;
            }
            if (timeTags)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 1);
            }
            if (status)
            {
                if (timeTags)
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
    else
    {
        if ((int)mxGetPr(MODE_ARG)[0] == STANDARD)
        {
            if (timeTags)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 1);
            }
            if (status)
            {
                if (timeTags)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 1);
                }
            }
        }
        else
        {
            outCnt = (uint32_t*)ssGetOutputPortSignal(S, 1);
            *outCnt = 0;
            
            if (timeTags)
            {
                outTimeTags = (uint32_t*)ssGetOutputPortSignal(S, 2);
            }
            if (status)
            {
                if (timeTags)
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 3);
                }
                else
                {
                    outStatus = (bool*)ssGetOutputPortSignal(S, 2);
                }
            }
        }
        if ((bool)mxGetPr(HOLD_LAST_VAL_ARG)[0] == false)
        {
            for (i = 0; i<outWidth; i++)
            {
                outData[i] = 0;
            }
        }
    }

    // get count of words available at input port
    // inData[0] holds the count in normal double format
    // inData[i] for i > 0 holds the data and timetags in Arinc_T format

    inCount = (int)((real_T *)inData)[0];
	SG_PRINTF(TRACE,"InCnt %d\n",inCount);

    if (inCount < 0 || inCount > inWidth - 1) { // should never happen
        sprintf(msg, "decode inCount %d inWidth %d", inCount, inWidth);
        ssSetErrorStatus(S, msg);
        return;
    }
    
    //Init status
    if (status)
    {
        if ((int)mxGetPr(MODE_ARG)[0] == STANDARD)
        {
            for (i=0; i<numWords; i++)
            {
                outStatus[i] = false;
            }
        }
        else
        {
            outStatus[0] = false;
        }
    }
	
	switch ((int)mxGetPr(MODE_ARG)[0])
	{
		case STANDARD:
			for (i = 1; i <= inCount; i++)
			{
				inWord = inData[i].word;
				
				j = 0;
				while ((LABEL(inWord) != (unsigned int)mxGetPr(LABEL_ARG)[j]) && (j<(numWords-1)))
				{
					j++;
				}

				if (LABEL(inWord) == (unsigned int)mxGetPr(LABEL_ARG)[j])
				{
					SG_PRINTF(TRACE,"LabelCnt %d\n",j);
					type = (Type_T)mxGetPr(DATA_TYPE_ARG)[j];
					resolution = (real_T)mxGetPr(RESOLUTION_ARG)[j];
					
					outData[j] = decode(inWord, type, resolution);
					if (timeTags)
					{
						outTimeTags[j] = (uint32_t)inData[i].time;
					}
                    if (status)
                    {
                        outStatus[j] = true;
                    }
				}
			}
		break;
		
		case MSG_SEQUENCE:
			for (i = 1; i <= inCount; i++)
			{
				inWord = inData[i].word;
				
				//Sync
				if (mask == 0)
				{
					STATE = SYNCHED;	//Sync disabled
				}
				else
				{
					sync = mask & inWord;
					if (twoSync)	// twoSync logic: look for sync1 followed by sync2
					{
						if (STATE == INITIAL) {  // looking for sync1
							if (sync == sync1) {
								STATE = SYNCHING;
							}
						} else if (STATE == SYNCHING) { // looking for sync2
							if (sync == sync2) {
								STATE = SYNCHED;
							} else if (sync != sync1) {
								STATE = INITIAL;
							}
						}
					} else { // oneSync logic: look for sync1

						if (STATE == INITIAL) { // looking for sync1
							if (sync == sync1) {
								STATE = SYNCHED;
							}
						}
					}
				}
				SG_PRINTF(TRACE,"SyncState %d\n",STATE);
				
				if (STATE != SYNCHED)
				{
					continue; // couldn't sync, so discard current input word
				}
				
				if (LABEL(inWord) != (unsigned int)mxGetPr(LABEL_ARG)[0])
				{
					continue;
				}
                
                if (status)
                {
                    outStatus[0] = true;
				}
                
				//Decode
				type = (Type_T)mxGetPr(DATA_TYPE_ARG)[COUNT];
				resolution = (real_T)mxGetPr(RESOLUTION_ARG)[COUNT];
				
				BUFFER(COUNT) = decode(inWord, type, resolution);
				if (timeTags)
				{
					BUFFER(COUNT + numWords) = (real_T) inData[i].time;
				}
				COUNT++;
				SG_PRINTF(TRACE,"Cnt %d\n",COUNT);
				
				if (COUNT >= numWords)	//write to outputs and start again
				{
					// accumulate valid message count for current sample time
					*outCnt = *outCnt + 1;

					// copy current message to output
					for (j = 0; j < numWords; j++) {
						outData[j] = BUFFER(j);
					}

					// copy current time tags to output if requested
					if (timeTags) {
						for (j = 0; j < numWords; j++) {
							outTimeTags[j] = (uint32_t)BUFFER(numWords + j);
						}
					}

					COUNT = 0;
					
					//reset sync
					STATE = INITIAL;
				}
			}
		break;
		
		case BIT_ORIENTED:
			for (i = 1; i <= inCount; i++)
			{
				inWord = inData[i].word;
				sync = mask & inWord;
				
				//Sync
				if (mask == 0)
				{
					STATE = SYNCHED;	//Sync disabled
				}
				else
				{
					if (STATE == INITIAL)
					{
						if (sync == sync1)
						{
							STATE = SYNCHED;
						}
					}
				}
				SG_PRINTF(TRACE,"SyncState %d\n",STATE);
				
				if (STATE != SYNCHED)
				{
					continue; // couldn't sync, so discard current input word
				}
				
				//Decode
				if (LABEL(inWord) != (unsigned int)mxGetPr(LABEL_ARG)[0])
				{
					continue;
				}
                
                if (status)
                {
                    outStatus[0] = true;
                }
				
				type = (Type_T)mxGetPr(DATA_TYPE_ARG)[0];
				resolution = (real_T)mxGetPr(RESOLUTION_ARG)[0];
				
				BUFFER(COUNT) = decode(inWord, type, resolution);
				if (timeTags)
				{
					BUFFER(COUNT + MAX_PACKET_SIZE) = (real_T) inData[i].time;
				}
				
				if (COUNT < MAX_PACKET_SIZE)
				{
					COUNT++;
				}
				else
				{
					ssSetErrorStatus(S, "IO682 Decode: Overflow occured");
					return;
				}
				
				endOfPacket = false;
				if (twoSync && (mask != 0))	//check if sync enabled and sync2 defined
				{
					if (sync == sync2)
					{
						endOfPacket = true;
					}
				}
				else	//If sync is disabled write to output at the end of for loop
				{
					if (i >= inCount)
					{
						endOfPacket = true;
					}
				}
			
				if (endOfPacket)	//write to output
				{
					*outCnt = COUNT;
					
					// copy current message to output
					for (j = 0; j < COUNT; j++) {
						outData[j] = BUFFER(j);
					}

					// copy current time tags to output if requested
					if (timeTags) {
						for (j = 0; j < COUNT; j++) {
							outTimeTags[j] = (uint32_t)BUFFER(MAX_PACKET_SIZE + j);
						}
					}

					COUNT = 0;
					
					//reset sync
					STATE = INITIAL;
				}
			}
		break;
        
        case CUSTOM_DATA_TYPE:
            for (i = 1; i <= inCount; i++)
			{
                bool *bit;
                int32_t temp;
                real_T value, mantissa, exponent;
                uint32_t mantissaRaw, exponentRaw, *outDataRaw;
                int bitMask = (int)mxGetPr(DATA_MSB_ARG)[0]-(int)mxGetPr(DATA_LSB_ARG)[0]+1;
                
				inWord = inData[i].word;
                
                if (LABEL(inWord) != (unsigned int)mxGetPr(LABEL_ARG)[0])
				{
					continue;
				}
                
                SG_PRINTF(TRACE, "Label %d, Data %X\n", LABEL(inWord), inWord);

                if (bitMask < 1)
                {
                    ssSetErrorStatus(S, "Bit Mask not valid"); return;
                }
                switch ((int)mxGetPr(CUSTOM_DATA_TYPE_ARG)[0])
                {
                    case CUSTOM_DATA_RAW:
                        outDataRaw = (uint32_t*)ssGetOutputPortSignal(S, 0);
                        *outDataRaw = (uint32_t)FIELD(inWord, ((int)mxGetPr(DATA_LSB_ARG)[0]-1), bitMask);
                    break;
                    
                    case CUSTOM_DATA_DISCRETE:
                        for (j=0; j<(int)mxGetN(BIT_POSITION); j++)
                        {
                            bit = (bool*) ssGetOutputPortSignal(S, j);
                            *bit = (bool)FIELD(inWord, ((int)mxGetPr(BIT_POSITION)[j]-1), 1);
                        }
                    break;
                    
                    case CUSTOM_DATA_BNR:
                        temp = FIELD(inWord, ((int)mxGetPr(DATA_LSB_ARG)[0]-1), bitMask);
                        if (FIELD(inWord, ((int)mxGetPr(DATA_MSB_ARG)[0]-1), 1))
                        {
                            temp |= (ONES(32-bitMask) << bitMask); // extend sign bits
                        }
                        value = (real_T)temp / (real_T)pow(2, bitMask-1);   //normalize (value between: -1 .. 0 .. 1)
                        value = value * (real_T)mxGetPr(SCALE_BNR)[0];  // Scale it back to real units
                        outData[0] = value;
                    break;
                    
                    case CUSTOM_DATA_FLOAT:
                        mantissaRaw = FIELD(inWord,((int)mxGetPr(DATA_LSB_ARG)[0]-1),(int)mxGetPr(BITS_MANTISSA)[0]);
                        exponentRaw = FIELD(inWord,((int)mxGetPr(DATA_LSB_ARG)[0]+(int)mxGetPr(BITS_MANTISSA)[0]-1),(int)mxGetPr(BITS_EXPONENT)[0]);
                        mantissa = (real_T)mantissaRaw / pow(2, (int)mxGetPr(BITS_MANTISSA)[0]) + 1;
                        exponent = (real_T)exponentRaw - pow(2, (int)mxGetPr(BITS_EXPONENT)[0]-1) + 1;
                        value = pow(2, exponent) * mantissa;
                        if (FIELD(inWord, ((int)mxGetPr(DATA_MSB_ARG)[0]-1), 1))
                        {
                            value = value * (-1.0);
                        }
                        outData[0] = value;
                    break;
                    
                    default:
                    ssSetErrorStatus(S, "Unknown output data type"); return;
                }
                
                if (timeTags)
                {
                    outTimeTags[0] = (uint32_t)inData[i].time;
                }
                if (status)
                {
                    outStatus[0] = true;
                }
            }
        break;
		
		default:
		ssSetErrorStatus(S, "Unknown mode"); return;
	}
#endif
}

static void mdlTerminate(SimStruct *S)
{

}

#include "sg_sfcn_glue.h"   // Code generation glue
