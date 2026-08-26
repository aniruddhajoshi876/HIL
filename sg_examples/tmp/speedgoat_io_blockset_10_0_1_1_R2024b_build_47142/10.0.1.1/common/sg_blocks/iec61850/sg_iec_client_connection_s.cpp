#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_iec_client_connection_s

/* Includes */
#include <tmwtypes.h>
#include <simstruc.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include <string>
#include <sstream>
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "iec.h"
#include "iec_client_node.h"
#include <string>
#include <sstream>
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

/* Defines */
#define CLIENT_ID_ARG		   	(uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG   	(uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define REMOTE_IP_ADDR_ARG  	(uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define REMOTE_TCP_PORT_ARG		(uint16_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define ENABLE_REPORTS_ARG		 (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define ENABLER_ARG		        	       	  	  ssGetSFcnParam(S, 5)
#define AUTHENTICATE_ARG	   (boolean_T)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define AP_TITLE_ARG		        	       	  ssGetSFcnParam(S, 7)
#define AE_QUALIFIER_ARG		(uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define SAMPLE_TIME_ARG        	       	  mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NUMBER_OF_ARGS												10

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
//	printf("mdlInitializeSizes");
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

	ssSetNumInputPorts(S, 0);
//	ssSetInputPortWidth(S, 0, 1);
//	ssSetInputPortDataType(S, 0, SS_UINT32);
//	ssSetInputPortRequiredContiguous(S, 0, 1);
//	ssSetInputPortDirectFeedThrough(S, 0, 1);

	ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_UINT8);
//    ssSetOutputPortWidth(S, 1, 1);
//    ssSetOutputPortDataType(S, 1, SS_INT32);
//    ssSetOutputPortWidth(S, 2, 10);
//	ssSetOutputPortDataType(S, 2, SS_INT32);

    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
//	printf("mdlInitializeSampleTimes");
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

    int32_t ret = 0;
	cClientConnection* Connection = NULL;
    cClientNode* Node = NULL;

    /* Add a client node */
    ret = Root.addNode(CLIENT_ID_ARG, true, (cNode**)&Node);
    if (ret != 0)
    {
        sprintf(ErrMsg, "MMS | Failed to add client node %i\n", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a connection relation to the master module */
    ret = Node->addConnection(CONNECTION_ID_ARG, (cClientConnection**)&Connection);
    if (ret != 0)
    {
        sprintf(ErrMsg, "MMS | Failed to add connection %i\n", CONNECTION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    std::string stringr = "";
    const char* Enabler = "";
    const char* AP_Title = "";
//     if(AUTHENTICATE_ARG){
//         char_T* Interface;
//         Interface = (char_T*) malloc(mxGetN(ENABLER_ARG)+1);
//         if (mxGetString(ENABLER_ARG, Interface, 1 + mxGetN(ENABLER_ARG)) != 0){
//             sprintf(ErrMsg, "Unable to read authentication parameter");
//             ssSetErrorStatus(S, ErrMsg);
//             return;}
//         std::stringstream ssr(Interface);
//         while (getline(ssr, stringr, '\n')){
//                 SG_PRINTF_INFO("MMS Client(%d) Connection(%d)\ninputed password: '%s'\n", Node->ID, Connection->ConnectionID, stringr.c_str());
//         }
//         Enabler = stringr.c_str();
//         free(Interface);

//         Interface = (char_T*) malloc(mxGetN(AP_TITLE_ARG)+1);
//         if (mxGetString(AP_TITLE_ARG, Interface, 1 + mxGetN(AP_TITLE_ARG)) != 0){
//             sprintf(ErrMsg, "Unable to read authentication parameter");
//             ssSetErrorStatus(S, ErrMsg);
//             return;}
//         std::stringstream sst(Interface);
//         while (getline(sst, stringr, '\n')){
// //					SG_PRINTF_INFO("MMS Client(%d) Connection(%d)\ninputed ap title: '%s'\n", Node->ID, Connection->ConnectionID, stringr.c_str());
//         }
//         AP_Title = stringr.c_str();
//         free(Interface);
//     }

    /* Initialize connection */
    ret = Connection->init(REMOTE_IP_ADDR_ARG, REMOTE_TCP_PORT_ARG, ENABLE_REPORTS_ARG, AUTHENTICATE_ARG, Enabler, AP_Title, AE_QUALIFIER_ARG);
    if (ret != 0)
    {
        sprintf(ErrMsg, "Error %i while initializing MMS Client on connection  %i!\n", ret, CONNECTION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

	ssSetPWorkValue(S, 0, Connection);

#endif

}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    cClientConnection* Connection = (cClientConnection*)ssGetPWorkValue(S, 0);

//	/* Read the input to check if user wants to connect to server */
//    uint32_t* InPort = (uint32_t*)ssGetInputPortSignal(S, 0);
//	Connection->WriteVar_P = *InPort;

	/* Write to output to let the user check if he is connected to the server */
	uint8_t* OutPort = (uint8_t*)ssGetOutputPortSignal(S, 0);
	if(Connection->ClientState == 0){
		*OutPort = Connection->ClientState;
	}else if(Connection->ClientState == 2){
		*OutPort = 1;
	}else{
		*OutPort = 0;
	}

	ssSetPWorkValue(S, 0, Connection);

#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif

}

#include "sg_sfcn_glue.h"   // Code generation glue
