#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_setup_s_v3

#include "sg_io682_v3.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "../arinc429/lib/sg_IO682/include/cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum SetupParamNumbers
{
    PAR_MODULE_ID,
    PAR_PCI_SLOT,
    PAR_TIME_SOURCE,
    PAR_DEVICE_ID,
    PAR_TIMER_RATE,
    PAR_SCHEDULED_MESSAGES,
    PAR_CH_IN_CONFIG,
    PAR_CH_OUT_CONFIG,
	PAR_IS_SLREALTIME,
	PAR_IN_BITRATE1,
	PAR_IN_BITRATE2,
	PAR_IN_BITRATE3,
	PAR_IN_BITRATE4,
	PAR_IN_BITRATE5,
	PAR_IN_BITRATE6,
	PAR_IN_BITRATE7,
	PAR_IN_BITRATE8,
	PAR_IN_BITRATE9,
	PAR_IN_BITRATE10,
	PAR_IN_BITRATE11,
	PAR_IN_BITRATE12,
	PAR_IN_BITRATE13,
	PAR_IN_BITRATE14,
	PAR_IN_BITRATE15,
	PAR_IN_BITRATE16,
	PAR_OUT_BITRATE1,
	PAR_OUT_BITRATE2,
	PAR_OUT_BITRATE3,
	PAR_OUT_BITRATE4,
	PAR_OUT_BITRATE5,
	PAR_OUT_BITRATE6,
	PAR_OUT_BITRATE7,
	PAR_OUT_BITRATE8,
	PAR_OUT_BITRATE9,
	PAR_OUT_BITRATE10,
	PAR_OUT_BITRATE11,
	PAR_OUT_BITRATE12,
	PAR_OUT_BITRATE13,
	PAR_OUT_BITRATE14,
	PAR_OUT_BITRATE15,
	PAR_OUT_BITRATE16,
    PAR_NUMBER_OF_ARGS
};

struct SetupParams
{
    int moduleId;       // Is between 1 and 16
    SgParam_IntVec *pciSlot;
    int timeSource;     // 1: IRIG, 2: internal timer (default) -> can't be changed by user
    int deviceId;       // 0x430, 0x530, 0x830, or 0x821
    int timerRate;      // 0:65535 in 250 nanosec units
	int isSlrealtime;
};

enum IntegerWorkVector
{
    LENGTH_I_WORK_VEC
};

enum RealWorkVector
{
    LENGTH_R_WORK_VEC
};

enum PointerWorkVector
{
    P_WORK_PARAMS,
    P_WORK_ERROR,
    LENGTH_P_WORK_VEC
};

static SetupParams *newSetupParams(SimStruct *S);
static void debugPrintParams(const SetupParams *params);

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{	
	int i;

    ssSetNumSFcnParams(S, PAR_NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg, "Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if(!ssSetNumOutputPorts(S, 0)) return;
	ssSetNumInputPorts(S, 0);
    

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, LENGTH_R_WORK_VEC);
    ssSetNumIWork(S, LENGTH_I_WORK_VEC);
    ssSetNumPWork(S, LENGTH_P_WORK_VEC);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

	//Non-Tunable params
    for (i = 0; i < PAR_IN_BITRATE1; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }
	
	//Tunable params
	for (i = PAR_IN_BITRATE1; i < PAR_NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, SS_PRM_TUNABLE);
    }
	
    // ASAP only in Setup block 
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    sgMaskInit_initSampleTimesForSetupBlock(S);
}

#define MDL_SET_WORK_WIDTHS
static void mdlSetWorkWidths(SimStruct *S)
{
	char_T *rtParamName = "InBitrate1";
	ssSetNumRunTimeParams(S, 32);
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE1, 0, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate2";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE2, 1, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate3";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE3, 2, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate4";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE4, 3, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate5";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE5, 4, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate6";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE6, 5, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate7";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE7, 6, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate8";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE8, 7, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate9";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE9, 8, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate10";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE10, 9, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate11";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE11, 10, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate12";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE12, 11, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate13";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE13, 12, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate14";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE14, 13, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate15";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE15, 14, rtParamName, SS_DOUBLE);
	rtParamName = "InBitrate16";
	ssRegDlgParamAsRunTimeParam(S, PAR_IN_BITRATE16, 15, rtParamName, SS_DOUBLE);
	
	rtParamName = "OutBitrate1";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE1, 16, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate2";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE2, 17, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate3";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE3, 18, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate4";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE4, 19, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate5";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE5, 20, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate6";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE6, 21, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate7";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE7, 22, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate8";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE8, 23, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate9";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE9, 24, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate10";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE10, 25, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate11";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE11, 26, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate12";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE12, 27, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate13";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE13, 28, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate14";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE14, 29, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate15";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE15, 30, rtParamName, SS_DOUBLE);
	rtParamName = "OutBitrate16";
	ssRegDlgParamAsRunTimeParam(S, PAR_OUT_BITRATE16, 31, rtParamName, SS_DOUBLE);
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
}

static void sg_ModelStep(SimStruct *S)
{
}

static void sg_ModelStop(SimStruct *S)
{
}

#define MDL_RTW
static void mdlRTW(SimStruct * S)
{
	SetupParams* params = newSetupParams(S);
    debugPrintParams(params);

    // The variables passed to ssWriteRTWParamSettings() need to be exactly the specified type
    int moduleId = params->moduleId;
    int timeSource = params->timeSource;
    int timerRate = params->timerRate;
	int deviceId = params->deviceId;
	int isSlrealtime = params->isSlrealtime;
	int m,n,i;
	int16_t bus;
	int16_t slot;
	uint32_t *schedMsg;
	int16_t *inConfig, *outConfig;
	if (params->pciSlot->len == 1)
    {
		bus = 0;
		slot = params->pciSlot->val[0];
	}
	else
	{
		bus = params->pciSlot->val[0];
		slot = params->pciSlot->val[1];
	}
	n = (int)mxGetN(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES));
	m = (int)mxGetM(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES));
	schedMsg = (uint32_t*)calloc(n*m,sizeof(uint32_t));
	for (i=0;i<n*m;i++)
	{
		schedMsg[i] = (uint32_t)mxGetPr(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES))[i];
	}
	
	n = (int)mxGetN(ssGetSFcnParam(S,PAR_CH_IN_CONFIG));
	m = (int)mxGetM(ssGetSFcnParam(S,PAR_CH_IN_CONFIG));
	inConfig = (int16_t*)calloc(n*m,sizeof(int16_t));
	for (i=0;i<n*m;i++)
	{
		inConfig[i] = (int16_t)mxGetPr(ssGetSFcnParam(S,PAR_CH_IN_CONFIG))[i];
	}
	
	n = (int)mxGetN(ssGetSFcnParam(S,PAR_CH_OUT_CONFIG));
	m = (int)mxGetM(ssGetSFcnParam(S,PAR_CH_OUT_CONFIG));
	outConfig = (int16_t*)calloc(n*m,sizeof(int16_t));
	for (i=0;i<n*m;i++)
	{
		outConfig[i] = (int16_t)mxGetPr(ssGetSFcnParam(S,PAR_CH_OUT_CONFIG))[i];
	}

    if (!ssWriteRTWParamSettings(S, 10,
			SSWRITE_VALUE_DTYPE_2DMAT, "ParSchedMsg", schedMsg,
				mxGetM(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES)),
				mxGetN(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES)), DTINFO(SS_UINT32, COMPLEX_NO),
			SSWRITE_VALUE_DTYPE_2DMAT, "ParInConfig", inConfig,
				mxGetM(ssGetSFcnParam(S,PAR_CH_IN_CONFIG)),
				mxGetN(ssGetSFcnParam(S,PAR_CH_IN_CONFIG)), DTINFO(SS_INT16, COMPLEX_NO),
			SSWRITE_VALUE_DTYPE_2DMAT, "ParOutConfig", outConfig,
				mxGetM(ssGetSFcnParam(S,PAR_CH_OUT_CONFIG)),
				mxGetN(ssGetSFcnParam(S,PAR_CH_OUT_CONFIG)), DTINFO(SS_INT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ParModuleId", &moduleId, DTINFO(SS_INT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ParTimeSource", &timeSource, DTINFO(SS_INT16, COMPLEX_NO),
			SSWRITE_VALUE_DTYPE_NUM, "ParTimerRate", &timerRate, DTINFO(SS_INT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ParDeviceId", &deviceId, DTINFO(SS_INT16, COMPLEX_NO),
			SSWRITE_VALUE_DTYPE_NUM, "ParBus", &bus, DTINFO(SS_INT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ParSlot", &slot, DTINFO(SS_INT16, COMPLEX_NO),
			SSWRITE_VALUE_DTYPE_NUM, "ParIsSlrealtime", &isSlrealtime, DTINFO(SS_INT16, COMPLEX_NO)))
    {
        return; // Error reporting will be handled by Simulink
    }
}

static SetupParams *newSetupParams(SimStruct *S)
{
    SetupParams *params = new SetupParams;

    params->moduleId          = sgParam_getInt(S, PAR_MODULE_ID);
    params->pciSlot           = sgParam_newIntVec(S, PAR_PCI_SLOT);
    params->timeSource        = sgParam_getInt(S, PAR_TIME_SOURCE);
    params->deviceId          = sgParam_getInt(S, PAR_DEVICE_ID);
    params->timerRate         = sgParam_getInt(S, PAR_TIMER_RATE);
	params->isSlrealtime      = sgParam_getInt(S, PAR_IS_SLREALTIME);

    return params;
}

static void debugPrintParams(const SetupParams *params)
{
    SG_PARAM_PRINT_INT(params, moduleId);
    SG_PARAM_PRINT_INT_VEC(params, pciSlot);
    SG_PARAM_PRINT_INT(params, timeSource);
    SG_PARAM_PRINT_INT(params, deviceId);
    SG_PARAM_PRINT_INT(params, timerRate);
	SG_PARAM_PRINT_INT(params, isSlrealtime);
}

#include "sg_sfcn_glue.h"   // Code generation glue
