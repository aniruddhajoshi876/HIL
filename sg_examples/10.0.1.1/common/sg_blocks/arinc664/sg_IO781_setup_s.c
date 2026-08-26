#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO781_setup_s

#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>		
#include <stdint.h>


#ifdef 	 MATLAB_MEX_FILE
	#include "mex.h"
#else
    #include "a664_api.h"
    #include "sg_IO781.h"
#endif

#define SG_HAS_MDL_EXIT //Causes sg_ModelExit() to be called upon process exit
#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#include "sg_callback.h"
#include "sg_printf.h"

#define CONFIG_FILE_1 "/sg/configFiles/io781_config_"
#define CONFIG_FILE_2 ".hex"

#define MODULE_ID_ARG       			ssGetSFcnParam(S, 0)    //parModuleId
#define CONFIG_FILE_ARG					ssGetSFcnParam(S, 1)    //not used
#define NUMBER_OF_ARGS 		   							 (2)                        

/* Integer Work Vectors */
#define NO_I_WORKS              (0)
                
/* Real Work Vectors */                
#define NO_R_WORKS              (0)
                
/* Pointer Work Vectors */
#define NO_P_WORKS              (0)
                
//error messages holder
static char msg[256];

#ifndef 	 MATLAB_MEX_FILE
	A664EndSystemHandle esHandle[10];
#endif

//auxiliary functions prototypes
#ifndef         MATLAB_MEX_FILE
void printVersion(const char* prefix, A664Version version);
#endif

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_t i;
    
	/* Number of expected parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);  
	
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    
	if(!ssSetNumInputPorts(S, 0))
    {
        SG_PRINTF(INFO, "error while setting input ports\n");
        return;
    }
    
	if(!ssSetNumOutputPorts(S, 0))
    {
        SG_PRINTF(INFO, "error while setting output ports\n");
        return;
    }
    
	ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
    
    ssSetNumModes(S, 0);
    
    ssSetNumNonsampledZCs(S, 0);
    
    for( i = 0 ; i < NUMBER_OF_ARGS ; i++ )
    {
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }
    
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void sg_ModelLoad(SimStruct *S) 
{
#ifndef MATLAB_MEX_FILE
    FILE* configurationFile;
    uint8_t* data;
    A664EndSystemInfo esInfo = {0};
    char filePath[128];
    char filename[50];
    uint8_t module_id_corr = (uint8_t)mxGetPr(MODULE_ID_ARG)[0]-1;
    //extern A664EndSystemHandle esHandle[10];
    int32_t retval = 0;
    uint32_t deviceCount=0;
    uint32_t moduleId = (uint32_t)mxGetPr(MODULE_ID_ARG)[0];
    sg_mod_info *mod_info;

    // Check if another block has already registered for the same module
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO781, moduleId);
    if (mod_info == NULL)
    {
        mod_info = sg_module_register(SG_MODULE_TYPE_IO781, moduleId);
    }
    else
    {
        SG_PRINTF(DEBUG,"Do not register IO781 module\n");
        return;
    }
    
    // First, initialize the hardware and get a device count
	if(deviceCount == 0)
    {
        SG_PRINTF(INFO, "IO781 Init ...\n");

        //CHECK_RETVAL(a664Init(A664_API_IO_VERSION, &deviceCount));
        retval = a664Init(A664_API_IO_VERSION, &deviceCount);	
        if(retval != A664_API_OK){			
            sprintf(msg,"Error: a664Init (error code = %d)\n",retval);
            //sprintf(msg,"%s\n", a664GetErrorString);
            ssSetErrorStatus(S,msg);
            return;
        }

        if (deviceCount == 0)
        {
            SG_PRINTF(INFO, "No devices found.\n");
            return;
        }
        else
        {
            SG_PRINTF(INFO, "Found %d IO781 Module(s)\n", (int)deviceCount);
        }
    }
    
    //Get info about the first discovered device	
	retval = a664ESGetInfo(module_id_corr, &esInfo);	
	if(retval != A664_API_OK){		
		sprintf(msg,"Error: a664ESGetInfo (error code = %d)\n",retval);
        ssSetErrorStatus(S,msg);
        return;
	}
	
	
	SG_PRINTF(DEBUG, "--------------- IO781: Device %i ---------------\n",module_id_corr+1);
	SG_PRINTF(DEBUG, "ES Id: %u\n", esInfo.aESId);
	SG_PRINTF(DEBUG, "ES Part Number: 0x%08X\n", esInfo.aESPartNumber);
	SG_PRINTF(DEBUG, "Network Interface Count: %u\n", esInfo.aNumNetworkInterfaces);
	printVersion("sNIC Version", esInfo.sNicVersion);
	printVersion("Tx NIOS Version", esInfo.txNIOSVersion);
	printVersion("Rx NIOS Version", esInfo.rxNIOSVersion);
	printVersion("Tx NIOS Boot App Version", esInfo.txBootNIOSVersion);
	printVersion("Rx NIOS Boot App Version", esInfo.rxBootNIOSVersion);
	
	// Open the device
	SG_PRINTF(INFO, "Opening IO781 module %i\n",module_id_corr+1);
	//CHECK_RETVAL(a664ESOpen(module_id_corr, &esHandle[module_id_corr]));
	
	retval = a664ESOpen(module_id_corr, &esHandle[module_id_corr]);
	if(retval != A664_API_OK){		
		sprintf(msg,"Error: a664ESOpen (error code = %d)\n",retval);
        ssSetErrorStatus(S,msg);
        return;
	}
    
    SG_PRINTF(DEBUG,"Setup, EsHandle %p\n",esHandle[module_id_corr].handle);

	// Configure the device
	// Load the configuration file
    if(sg_getModelBaseDir(filePath, 128))
	{
		ssSetErrorStatus(S, pSgErrorStr);
		return;
	}

	SG_PRINTF(DEBUG, "Base Dir: %s\n", filePath);
    sprintf(filename, "%s%u%s",CONFIG_FILE_1, module_id_corr+1, CONFIG_FILE_2);
    strcat(filePath, filename);
	SG_PRINTF(DEBUG, "Target file: %s\n", filePath);
	
	SG_PRINTF(INFO, "Loading configuration file ... \n");
	configurationFile = fopen(filePath, "r");
	if (configurationFile != 0)
	{
		long fileSize;
		size_t result;
		fseek(configurationFile, 0, SEEK_END);
		fileSize = ftell(configurationFile);
		rewind(configurationFile);
		data = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);
		if (data == 0) {fputs("Memory allocation error", stderr); return;}
		result = fread(data, 1, fileSize, configurationFile);
		if (result <= 0) {fputs("Read error", stderr); return;}
		
		fclose(configurationFile);
		configurationFile = 0;
	}
	else
	{
		// Close the device and api
		// CHECK_RETVAL(a664ESClose(esHandle[module_id_corr]));		
		retval = a664ESClose(esHandle[module_id_corr]);	
		if(retval != A664_API_OK){			
			sprintf(msg,"Error: a664ESClose (error code = %d)\n",retval);
			ssSetErrorStatus(S,msg);
            return;
		}
		
		SG_PRINTF(INFO, "Closing the device...\n");
		//CHECK_RETVAL(a664Close());
		
		a664Close(); //Do not check return value -> Always error -5

		sprintf(msg,"Error opening file: %s (missing file?)\n", filePath);
        ssSetErrorStatus(S,msg);
		return;
	}
	
	//CHECK_RETVAL(a664ESConfigureEx(esHandle[module_id_corr], data));
    retval = a664ESConfigureEx(esHandle[module_id_corr], data);	
    if(retval != A664_API_OK){
        //SG_PRINTF(INFO, "%s returned %d\n", a664ESConfigureEx, (int)retval);
        sprintf(msg,"Error: a664ESConfigureEx (error code = %d)\n",retval);
        ssSetErrorStatus(S,msg);
        return;
    }
	
	free(data);
	SG_PRINTF(INFO, "Device configured successfully!\n");
	
	//SG_PRINTF(INFO, "------------------------------------------------\n");
#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE 

#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    
#endif
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    uint32_t moduleId = (uint32_t)mxGetPr(MODULE_ID_ARG)[0];
    
    sg_module_unregister(SG_MODULE_TYPE_IO781, moduleId);
    SG_PRINTF(DEBUG, "IO781: Unregister module\n");

#endif
}

#ifndef         MATLAB_MEX_FILE
void printVersion(const char* prefix, A664Version version)
{
	SG_PRINTF(DEBUG, "%s: %u.%u.%u.%u\n", prefix, version.mVersionMajor, version.mVersionMinor,
	version.mVersionMaintenance, version.mVersionRevision);
}				
#endif


#include "sg_sfcn_glue.h"   // Code generation glue
