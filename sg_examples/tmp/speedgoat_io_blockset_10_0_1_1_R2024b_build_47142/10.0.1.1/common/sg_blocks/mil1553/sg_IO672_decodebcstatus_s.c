// condor1553decodebcstatus.c - xPC Target non-inlined S-function driver for the 
// 1553 protocol.  Choose the bit to decode.
// Copyright 2005-2013 The MathWorks, Inc.

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_decodebcstatus_s

#include "sg_IO672.h"

#include "sg_mil1553.h"
#include "sg_callback.h"
#include "sg_printf.h"

#define NUM_ARGS          2
#define STAT_ARG          ssGetSFcnParam(S, 0) // Status bit number
#define SAMP_TIME_ARG     ssGetSFcnParam(S, 1) // seconds

#define NUM_I_WORKS       (3)
#define NUM_R_WORKS       (0)
#define NUM_P_WORKS       (0)

#define I_WORD            (0)
#define I_BIT             (1)
#define I_SHIFT           (2)

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;
    DTypeId id = SS_UINT32;
    DTypeId statid = SS_UINT32;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg, "%d input args expected, %d passed", 
                NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if( !ssSetNumInputPorts(S, 1) ) return;

    // Port 0 is the input list of message buffers.
    ssSetInputPortRequiredContiguous( S, 0, 1 ); 
#ifdef          MATLAB_MEX_FILE
    // First create the custom data type for a fifo pointer
    // The Register call defines the signal as a unique type for Simulink
    id = ssRegisterDataType( S, "bcstatus1553" );
    if(id == INVALID_DTYPE_ID)
        return;
    ssSetDataTypeSize( S, id, 24 );  // 6*int32
    if( ssGetDataTypeZero( S, id ) == NULL )
    {
        bcstatus1553 bcstatzero;
        
        bcstatzero.control = 0;
        bcstatzero.cmd1 = 0;
        bcstatzero.stat1 = 0;
        bcstatzero.cmd2 = 0;
        bcstatzero.stat2 = 0;
        bcstatzero.status = 0;
        ssSetDataTypeZero( S, id, &bcstatzero );
    }
    // Neither of these functions can be called from the target side.
#endif
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDataType( S, 0, id );
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if( !ssSetNumOutputPorts(S, 1) ) return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType( S, 0, SS_UINT32 );

    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, NUM_R_WORKS);
    ssSetNumIWork(S, NUM_I_WORKS);
    ssSetNumPWork(S, NUM_P_WORKS);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUM_ARGS; i++)
        ssSetSFcnParamTunable(S, i, 0);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );
}
 
static void mdlInitializeSampleTimes(SimStruct *S)
{
//    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0)
//    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
        ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
//    } else {
//        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
//        ssSetOffsetTime(S, 0, 0.0);
//    }
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    int statid = (int)mxGetPr(STAT_ARG)[0];
    int wordwithbit;
    int bit;
    int shift;

    switch( statid )
    {
        // Status 1, defined in struct bt1553_status as bit fields.
        // Change to literal bit positions here.
      case 1:
        wordwithbit = 2;  // stat1, message error
        bit = 0x0400;
        shift = 10;
        break;
      case 2:
        wordwithbit = 2;  // stat1, Instrumentation
        bit = 0x0200;
        shift = 9;
        break;
      case 3:
        wordwithbit = 2;  // stat1, Service Request
        bit = 0x0100;
        shift = 8;
        break;
      case 4:
        wordwithbit = 2;  // stat1, 3 reserved bits
        bit = 0x00d0;
        shift = 5;
        break;
      case 5:
        wordwithbit = 2;  // stat1, Broadcast
        bit = 0x0010;
        shift = 4;
        break;
      case 6:
        wordwithbit = 2;  // stat1, Busy
        bit = 0x0008;
        shift = 3;
        break;
      case 7:
        wordwithbit = 2;  // stat1, Subsystem flag
        bit = 0x0004;
        shift = 2;
        break;
      case 8:
        wordwithbit = 2;  // stat1, Dynamic bus acceptance
        bit = 0x0002;
        shift = 1;
        break;
      case 9:
        wordwithbit = 2;  // stat1, Terminal flag
        bit = 0x0001;
        shift = 0;
        break;

        // Status 2
      case 10:
        wordwithbit = 4;  // stat2, message error
        bit = 0x0400;
        shift = 10;
        break;
      case 11:
        wordwithbit = 4;  // stat2, Instrumentation
        bit = 0x0200;
        shift = 9;
        break;
      case 12:
        wordwithbit = 4;  // stat2, Service Request
        bit = 0x0100;
        shift = 8;
        break;
      case 13:
        wordwithbit = 4;  // stat2, 3 reserved bits
        bit = 0x00d0;
        shift = 5;
        break;
      case 14:
        wordwithbit = 4;  // stat2, Broadcast
        bit = 0x0010;
        shift = 4;
        break;
      case 15:
        wordwithbit = 4;  // stat2, Busy
        bit = 0x0008;
        shift = 3;
        break;
      case 16:
        wordwithbit = 4;  // stat2, Subsystem flag
        bit = 0x0004;
        shift = 2;
        break;
      case 17:
        wordwithbit = 4;  // stat2, Dynamic bus acceptance
        bit = 0x0002;
        shift = 1;
        break;
      case 18:
        wordwithbit = 4;  // stat2, Terminal flag
        bit = 0x0001;
        shift = 0;
        break;


      case 19:
        wordwithbit = 5;  // Message (Int) status,
        bit = BT1553_INT_HIGH_WORD;
        shift = 0;
        break;
      case 20:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_BIT_COUNT;
        shift = 0;
        break;
      case 21:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_INVALID_WORD;
        shift = 1;
        break;
      case 22:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_LOW_WORD;
        shift = 2;
        break;
      case 23:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_INVERTED_SYNC;
        shift = 3;
        break;
      case 24:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_MID_BIT;
        shift = 4;
        break;
      case 25:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_TWO_BUS;
        shift = 5;
        break;
      case 26:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_PARITY;
        shift = 6;
        break;
      case 27:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_NON_CONT_DATA;
        shift = 7;
        break;
      case 28:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_EARLY_RESP;
        shift = 8;
        break;
      case 29:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_LATE_RESP;
        shift = 9;
        break;
      case 30:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_BAD_RTADDR;
        shift = 10;
        break;
      case 31:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_CHANNEL;
        shift = 11;
        break;
      case 32:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_WRONG_BUS;
        shift = 13;
        break;
      case 33:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_BIT_COUNT;
        shift = 14;
        break;
      case 34:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_NO_IMSG_GAP;
        shift = 15;
        break;
      case 35:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_END_OF_MESS;
        shift = 16;
        break;
      case 36:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_BROADCAST;
        shift = 17;
        break;
      case 37:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_RT_RT_FORMAT;
        shift = 18;
        break;
      case 38:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_RESET_RT;
        shift = 19;
        break;
      case 39:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_SELF_TEST;
        shift = 20;
        break;
      case 40:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_MODE_CODE;
        shift = 21;
        break;
      case 41:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_RETRY;
        shift = 25;
        break;
      case 42:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_NO_RESP;
        shift = 26;
        break;
      case 43:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_ME_BIT;
        shift = 27;
        break;
      case 44:
        wordwithbit = 5;  // Message (Int) status, 
        bit = BT1553_INT_ALT_BUS;
        shift = 31;
        break;
    }
    ssSetIWorkValue( S, I_WORD, wordwithbit );
    ssSetIWorkValue( S, I_BIT, bit );
    ssSetIWorkValue( S, I_SHIFT, shift );
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    int *IPtr = (int *)ssGetInputPortSignal(S,0);
    int index = ssGetIWorkValue( S, I_WORD );
    int bit = ssGetIWorkValue( S, I_BIT );
    int shift = ssGetIWorkValue( S, I_SHIFT );
    // Status output
    unsigned int *sptr    = (unsigned int *)ssGetOutputPortSignal(S,0);
    
    // Use the array form instead of the structure, much simpler code!
    *sptr = (IPtr[index] & bit) >> shift;

//SG_PRINTF(INFO, "%x\n", bc_msg[messno].data[0][0] );
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    // Nothing to do on terminate.
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
