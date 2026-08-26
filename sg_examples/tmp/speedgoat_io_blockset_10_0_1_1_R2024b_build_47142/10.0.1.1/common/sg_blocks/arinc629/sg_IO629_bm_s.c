#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO629_bm_s

#include "sg_IO629.h" 

#define DEBUG

//TO DO: REMOVE THIS DEFINE AND MAKE IT MORE CONSISTENT
#define MAX_WORDS   100

//parSubdeviceId, parBmMode,parRxBufferSize,parDataPortSize

#define SUBDEVICEID_ARG       			ssGetSFcnParam(S, 0)    //parModuleId
#define BM_MODE_ARG       				ssGetSFcnParam(S, 1) 	//parBmMode
#define BUFFER_LEN_ARG       			ssGetSFcnParam(S, 2) 	//parRxBufferSize
#define OUT_DATA_PORT_SIZE_ARG       	ssGetSFcnParam(S, 3) 	//parRxBufferSize
#define SAMPLE_TIME_ARG       			ssGetSFcnParam(S, 4)	//parSampleTime

#define NUMBER_OF_ARGS 						   		   (  5)

/* Integer Work Vectors */
#define REC_BUFFER_IDX			(0)
#define RX_BUFF_CLEARED			(1)
#define NO_I_WORKS              (2)


/* Real Work Vectors */
#define NO_R_WORKS              (0)

/* Pointer Work Vectors */
#define RX_BUFF_IDX				(0)
#define A629_BUFF_IDX			(1)
#define NO_P_WORKS              (2)

//error messages holder 
static char_T msg[256];

//static HMXF_BUFFER rxbuffer;
extern HMXF_SERVER 	sg_io629_server;
extern HMXF_MODULE  sg_io629_module[4];

////temporary file logging
//FILE *f;
//real_T counter;

//auxiliary functions prototypes
static void pri(int i);
static void wait_s(real_T t);
static void wait_us(real_T t);
static void mdlInitializeSizes(SimStruct *S)
{
	uint32_T 	i															;
	int_T	out_port_size = 	(int_T)mxGetPr(OUT_DATA_PORT_SIZE_ARG	)[0];		
	int_T	numMaxRecords = 	(int_T)mxGetPr(BUFFER_LEN_ARG			)[0];
	DECL_AND_INIT_DIMSINFO(di);
	int_T dims[2];
	
	di.numDims = 2;
	dims[0] = out_port_size;
	dims[1] = numMaxRecords;
	di.dims = dims;
	di.width = dims[0]*dims[1];
	
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);  /* Number of expected parameters */
	
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
		printf("error while setting input ports\n");
		return;
	}		
    if(!ssSetNumOutputPorts(S, 4))	
	{
		printf("error while setting output ports\n");
		return;
	}    
	
	//hard coded
	ssSetOutputPortWidth(S, 0, numMaxRecords);
	ssSetOutputPortWidth(S, 1, numMaxRecords);
	
	ssSetOutputPortDimensionInfo(S,  2, &di);
	
	ssSetOutputPortDataType(S, 2, SS_UINT16);
	
	ssSetOutputPortWidth(S, 3, 1);
	
	
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

    
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLE_TIME_ARG)[0]==-1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}


#define MDL_START  /* Change to #undef to remove function */
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	
	if(!xpcIsModelInit()){
		
		uint32 						rc 						= 	0;
		HMXF_CHANNEL 				bm						= 	0;
		uint64 						buff_size				= 	(uint32)mxGetPr(BUFFER_LEN_ARG)[0];		
		static MXF_A629_DATAREC* 	hostRxBuffer			= 	NULL;             						// ARINC 629 acquisition rxbuffer
		/*static*/ HMXF_BUFFER 		rxbuffer;
		uint64 						channelIndex 			= 	0;                 						// First BM channel 		
		uint64 						moduleIndex  			= 	(uint64)mxGetPr(SUBDEVICEID_ARG)[0]-1;
		uint64 						allocated	  			= 	0;

		ch_is_enabled[channelIndex+(moduleIndex)*121] = 1;
		
		hostRxBuffer = (MXF_A629_DATAREC*)malloc((size_t)buff_size*sizeof(MXF_A629_DATAREC));
		
		rc = mxfModuleChannelGet(sg_io629_module[moduleIndex], channelIndex, &bm);		
		
		if(rc == MAXT_SUCCESS)
		{	
			//select mode according to mask parameter
			if((uint32_T)mxGetPr(BM_MODE_ARG)[0] == 1)
				rc = mxfAttributeUint64Set(bm, KMXF_A629_BM_MODE, VMXF_A629_BM_MODE_STRING	);  // Configure BM STRING	MODE
			if((uint32_T)mxGetPr(BM_MODE_ARG)[0] == 2)                                                                      
				rc = mxfAttributeUint64Set(bm, KMXF_A629_BM_MODE, VMXF_A629_BM_MODE_WORD	);  // Configure BM WORD 	MODE			
			//return check
			if(rc != MAXT_SUCCESS) 
				printf("BM mxfAttributeUint64Set KMXF_A629_BM_MODE Error code=0x%lX\n", rc);
			
			// Allocate on-board acquisition rxbuffer
			if(rc == MAXT_SUCCESS){		
				//rc = mxfRxAcqBufferAlloc(bm, buff_size*sizeof(MXF_A629_DATAREC), &rxbuffer, NULL);  					
				rc = mxfRxAcqBufferAlloc(bm, buff_size*sizeof(MXF_A629_DATAREC), &rxbuffer, &allocated);  	
				//printf("BM buff alloc: targeted = %llu allocated = %llu\n",buff_size*sizeof(MXF_A629_DATAREC),allocated);
			}
			
			if (!rc)
				rc = mxfRxAcqModeSet(rxbuffer, MXF_RXACQ_MODE_LINEAR);		
				

		
		}else{
			printf("Error code=0x%lX\n", rc);
		}
		
		
		//rc = mxfRxAcqStart(rxbuffer, MXF_RXACQ_FLAG_DEFAULT, 0, 0);
		
		ssSetPWorkValue(S, A629_BUFF_IDX, (void*)hostRxBuffer);	
		ssSetIWorkValue(S, REC_BUFFER_IDX, (int_T)rxbuffer);
		ssSetIWorkValue(S, RX_BUFF_CLEARED, 0);
			
		//counter = 0;
		//f = fopen("io629log.txt","w");
		
	}
	
	

#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
	
	real_T					*pY0, *pY1, *pY3															;
	uint16_T				*pY2 																		;
	uint32_T 				buff_size																	;
	uint32_T				index, word																	;
	MXF_A629_DATAREC *   	rec629				=	NULL												;
	uint32 					rc 					=	0													;
	uint64         			status, 
							msgCount,
							byteCount																	;						
	MXF_A629_DATAREC* 		hostRxBuffer 																;
	int		 				print				=	1													;
	int		 				printData			=	1													;
	HMXF_BUFFER 			rxbuffer																	;
	uint32_T				maxMsgNumber  		= 	(uint32)mxGetPr(BUFFER_LEN_ARG)			[0]			;
	uint32_T				maxMessageLength	= 	(uint32)mxGetPr(OUT_DATA_PORT_SIZE_ARG)	[0]			;
	buff_size									= 	(uint32)mxGetPr(BUFFER_LEN_ARG)			[0]			;
	hostRxBuffer 								= 	(MXF_A629_DATAREC*)ssGetPWorkValue(S, A629_BUFF_IDX);		

	rxbuffer									= 	ssGetIWorkValue(S, REC_BUFFER_IDX);		
	
	
	msgCount = 0;
	
	
	
	
	pY0 = (real_T*)	ssGetOutputPortSignal(S, 0);
	pY1 = (real_T*)	ssGetOutputPortSignal(S, 1);
	pY2 = (uint16_T*)ssGetOutputPortSignal(S, 2);
	pY3 = (real_T*)ssGetOutputPortSignal(S, 3);
	

	
	
	//routine to run the acquisition at the first iteration
	if(!ssGetIWorkValue(S, RX_BUFF_CLEARED)){		
		ssSetIWorkValue(S, RX_BUFF_CLEARED, 1);
		rc = mxfRxAcqClear(rxbuffer);			
		rc = mxfRxAcqStart(rxbuffer, MXF_RXACQ_FLAG_DEFAULT, 0, 0);		
		return;
	}
	//rc  = mxfA629RxAcqRead(rxbuffer, buff_size, buff_size*sizeof(MXF_A629_DATAREC), &status, &msgCount, &byteCount, hostRxBuffer);
	rc  = mxfA629RxAcqRead(rxbuffer, 0, buff_size*sizeof(MXF_A629_DATAREC), &status, &msgCount, &byteCount, hostRxBuffer);

	
	if(status != 4){
		sprintf(msg,"Rx Error (buffer overflow) \n");
		ssSetErrorStatus(S,msg);
		return;
	}
	
	
	if (rc == MAXT_SUCCESS)
	{
		*pY3 = (real_T)msgCount ;
		
		rec629 = hostRxBuffer;
		
		if(msgCount>maxMsgNumber){
			sprintf(msg,"Msg Count is bigger than Max num of wordstrings\n");
			ssWarning(S,msg);
		}
		
		for(index=0; index < maxMsgNumber ; index++){			
			
			if(index < msgCount){
				
				pY0[index] = (real_T)rec629->timeTag;
				pY1[index] = rec629->dataSize/2;		
				
				for(word=0; word<maxMessageLength; word++){
					if(word < rec629->dataSize/2){						
						pY2[index*maxMessageLength+word] = (uint16_T)rec629->data[word];						
					}else{	
						pY2[index*maxMessageLength+word] = 0;
					}
				}				
			}else{			
				pY0[index] = 0;
				pY1[index] = 0;				
			}
			
			rc = mxfA629NextDataRecordPtrGet(rec629, &rec629);
		
		}	
	}else{
		printf("Error code (BusMonitor: mxfA629RxAcqRead = 0x%lX\n", rc);
	}
	
#endif	
}

static void mdlTerminate(SimStruct *S)
{	
#ifndef MATLAB_MEX_FILE
	
	
	if(!xpcIsModelInit())		
	{
		uint32_T rc			;
		HMXF_BUFFER	rxbuffer;
		uint32_T index		;		
		int_T 	channelIndex		=	0	;
		int_T 	moduleIndex  		= 	(int_T)mxGetPr(SUBDEVICEID_ARG)[0]-1;
		
		rxbuffer = 	ssGetIWorkValue(S, REC_BUFFER_IDX);	
		rc = mxfRxAcqStop(rxbuffer);		
		
		
		
		if(rc != MAXT_SUCCESS){
			printf("Error code (BM: mxfRxAcqStop) = 0x%lX\n", rc);return;}
		
		rc = mxfRxAcqClear(rxbuffer);
		if(rc != MAXT_SUCCESS){printf("Error code (BM: mxfRxAcqClear) = 0x%lX\n", rc);return;}
		
		rc = mxfRxAcqBufferFree(rxbuffer);	
		if(rc != MAXT_SUCCESS){printf("Error code (BM: mxfRxAcqBufferFree) = 0x%lX\n", rc);return;}
		
		
		ch_is_enabled[channelIndex+(moduleIndex)*121] = 0;
		
		index = 0;
		
		while(index<sizeof(ch_is_enabled)){
			if(ch_is_enabled[index]){
				break;
			}else{
				index++;
			}
		}
		
		
		if(index == sizeof(ch_is_enabled)){
			
			printf("mxfSystemResourcesRelease... ");
	
			//release server
			rc=mxfSystemResourcesRelease(sg_io629_server, 0);
			if(rc != MAXT_SUCCESS){
				printf("Error code (bm[%i]: mxfSystemResourcesRelease) =0x%lX\n",moduleIndex, rc);return;
			}else
				printf("done!\n");
			
			//disconnect from device
			rc=mxfServerDisconnect(sg_io629_server);
			
			if(rc)
				printf("mxfServerDisconnect rc=%08X \n", rc);			
				printf("**************************************\n");
		}		
		
		//fclose(f);
		
	}
#endif
}

static void wait_s(real_T t)
{
#ifndef MATLAB_MEX_FILE
    xpcTime t_start, t_now, t_elapsed;
    xpcGetElapsedTime(&t_start);

    do{
		xpcGetElapsedTime(&t_now);
        xpcSubtractTime(&t_elapsed, &t_now, &t_start);
    }while( (((real_T)t_elapsed.U64.NanoSecondsLo * 1e-9) + ((real_T)t_elapsed.U64.NanoSecondsHi * 4.294967296)) < t );
#endif
}
	
static void wait_us(real_T t){
	xpcBusyWait(t/(1000000.0));
}

static void pri(int i){
	printf("%i\n",i);
}
#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif