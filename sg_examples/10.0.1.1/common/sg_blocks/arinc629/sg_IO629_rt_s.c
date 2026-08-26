#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO629_rt_s

#include "sg_IO629.h"
#include <time.h>

//parModuleId,parChId,parTg,parTxBuffSize,parRtCid
#define MODULE_ID_ARG       			ssGetSFcnParam(S, 0)    // parModuleId
#define CHANNEL_ID_ARG 					ssGetSFcnParam(S, 1) 	// parChId
#define TG_ARG 							ssGetSFcnParam(S, 2)	// parTg
#define RT_CID_ARG						ssGetSFcnParam(S, 3)	//
#define XPP_ARRAY_ARG					ssGetSFcnParam(S, 4)	// parCId
#define SAMPLE_TIME_ARG       			ssGetSFcnParam(S, 5)	// parSampleTime
#define RT_MODE_ARG						ssGetSFcnParam(S, 6)
#define REDUCED_XPP_ARG					ssGetSFcnParam(S, 7)
#define INDEP_MODE_COUNTER_ARRAY_ARG	ssGetSFcnParam(S, 8)
#define INDEP_MOD_OPT_ARG				ssGetSFcnParam(S, 9) //to remove
    
#define NUMBER_OF_ARGS 						   		  (   10)

#define XPP_FIELD_LABEL			2
#define XPP_FIELD_LENGTH		3


/* Integer Work Vectors */
#define RT_IDX					(0)
#define XPP_COUNTER				(1)
#define NO_I_WORKS              (2) 


/* Real Work Vectors */
#define NO_R_WORKS              (0)

/* Pointer Work Vectors */
#define TX_BUFF_P_IDX			(0)
#define VALID_CELL_P_IDX		(1)
#define NO_P_WORKS              (2)

//error messages holder (i guess)
static char_T msg[256];

//FILE *f;



//externs
extern HMXF_SERVER sg_io629_server;
extern HMXF_MODULE  sg_io629_module[4];
//to remove(for debugging)
extern HMXF_DEVICE  sg_io629_device;

//auxiliary functions prototypes
static void wait_s(real_T t);
static void wait_us(real_T t);

//returns the number of lines of the XPP
static uint8_T getNumMinorFrames(SimStruct *S);

//returns the number of columns of the largest minorframe
static uint16_T maxMinorFrameLength(SimStruct *S);

//returns the number of columns of the n-th minor frame
static uint8_T getMinorFrameLength(SimStruct *S,uint8_T n);

//returns the number of columns of the n-th minor frame
static uint16_T getNumUsedCells(SimStruct *S);

//return xpp n-th column depth
static uint16_T getColumnDepth(SimStruct *S,uint8_T n);


//
static uint16_T getXppField(SimStruct *S,uint8_T line,uint8_T column,uint8_T field);

//


static void mdlInitializeSizes(SimStruct *S)
{
	uint32_T i,itemp;
	//uint16_T  numCells = (uint16_T)mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;
	uint16_T  numCells = (uint16_T)mxGetN(REDUCED_XPP_ARG);
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
		sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);	
	
	if(!ssSetNumInputPorts(S, numCells))
	{
		printf("error while setting input ports\n");
		return;
	}		
	
	for ( i = 0 ; i < numCells; i++ )
    {
		itemp =(uint32_T)mxGetPr(REDUCED_XPP_ARG)[i]-1;
        ssSetInputPortWidth(S, i, (int_T)mxGetPr(XPP_ARRAY_ARG)[3+CSV_LINE_LEN*itemp]);
		ssSetInputPortDataType(S, i, SS_UINT16);
		ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous(S, i, 1 );
    }
	
	
    if(!ssSetNumOutputPorts(S, 0))	
	{
		printf("error while setting output ports\n");
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

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE );
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
		HMXF_BUFFER          						*txBuffer				;
		uint32_T									index					;
		uint8_T										lineIndex,columnIndex	;
		uint8_T										numMinorFrames			;
		uint16_T									txBufferCounter			;	
		uint16_T									maxMinFrameLength		;
		uint8_T										currentMinFrameLength	;	
		uint32_T									numCells				;		
		uint32 										rc 				= 	0	;
		HMXF_CHANNEL 								rt				= 	0	;
		int_T 										channelIndex	=	(int_T)mxGetPr(CHANNEL_ID_ARG)[0];
		int_T		 								moduleIndex		= 	(int_T)mxGetPr(MODULE_ID_ARG)[0]-1;
		
		MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES   	majorProperties			;
		MXF_A629_TXPERIODIC_MJRFRAME_MSG          	*minorFrame				;
		uint64										allocated				;
		//from mdlOutputs, used to initialize the XPP at startup
		//uint32_T  								cellIndex				;
		//int_T										itemp					;
		//MXF_A629_DATAREC							txRec629				;
		//int_T										portWidth				;
		//uint16_T 									*uPtr					;
		//int_T										i						;

		
		
		//f = fopen("i0629log.txt","w");  
		
		
		
		
		
				
		numCells = (uint32_T)mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;	
		
		txBuffer = (void*)xpcAllocPhysicalMemory(numCells*sizeof(HMXF_BUFFER));
		ssSetPWorkValue(S,TX_BUFF_P_IDX,txBuffer);		
		
		ch_is_enabled[channelIndex+(moduleIndex)*121] = 1;
		
		//number of raws of the xpp
		numMinorFrames = getNumMinorFrames(S);		
		
		
		//number of cells of the longest row in the XPP
		maxMinFrameLength = maxMinorFrameLength(S);
		
				
		//variable used in the construction of the major frame (=XPP)
		minorFrame = malloc(maxMinFrameLength*sizeof(MXF_A629_TXPERIODIC_MJRFRAME_MSG));	

		
		//get the channel according to index----------------------------------------------------------------		
		rc = mxfModuleChannelGet(sg_io629_module[moduleIndex], channelIndex, &rt);
		if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfModuleChannelGet) =0x%lX\n", rc);return;}
		ssSetIWorkValue(S,RT_IDX,(int_T)rt);
		ssSetIWorkValue(S,XPP_COUNTER,0);
		
		//set the TG----------------------------------------------------------------------------------------		
		rc = mxfAttributeUint64Set(rt, KMXF_A629_RT_TG,(uint64)mxGetPr(TG_ARG)[0]); 
		if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfAttributeUint64Set, KMXF_A629_RT_TG) = 0x%lX\n", rc);return;}		

		
	   //set CID--------------------------------------------------------------------------------------------
	   	rc = mxfAttributeUint64Set(rt, KMXF_A629_RT_CID, (int_T)mxGetPr(RT_CID_ARG)[0]-1);
		if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfAttributeUint64Set, KMXF_A629_RT_CID) = 0x%lX\n", rc);return;}

		//--------------------------------------------------------------------------------------------------				
		
		
		for(index=0; index<numCells && !rc; index++){
			//allocate buffer on the FM629 hardware
			rc = mxfTxPeriodicUpdateMsgBufferAlloc(rt, index, sizeof(MXF_A629_DATAREC), &txBuffer[index], &allocated);				
			if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfTxPeriodicUpdateMsgBufferAlloc) = 0x%lX\n", rc);return;}
		}
		
		
		//clear major frame		
		rc = mxfTxPeriodicMajorFrameClear(rt, 0);
		if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfTxPeriodicMajorFrameClear) = 0x%lX\n", rc);return;}
	
		// 
		txBufferCounter	=	0;
		
		//Instatiation (creation) of the XPP
		for(lineIndex = 1; lineIndex <= numMinorFrames;lineIndex++){ //loop over all the lines in the xpp
	
			//get length of the current line of the XPP
			currentMinFrameLength = getMinorFrameLength(S,lineIndex);	
			
			//set to 0
			memset(minorFrame, 0, maxMinFrameLength*sizeof(*minorFrame));
			xpcBusyWait(0.1);
				for(columnIndex = 1;columnIndex <= currentMinFrameLength;columnIndex++){	
					
					//if label exists (either normal or dummy label)
					if(getXppField(S,lineIndex,columnIndex,XPP_FIELD_LABEL)<4096){
						
						//fill in the information from every cell on the current line of the XPP
						minorFrame[columnIndex-1].length  = getXppField(S,lineIndex,columnIndex,XPP_FIELD_LENGTH); 
						minorFrame[columnIndex-1].buffer  = txBuffer[txBufferCounter];						
						minorFrame[columnIndex-1].label   = getXppField(S,lineIndex,columnIndex,XPP_FIELD_LABEL);																
						txBufferCounter++;								
					}else{//skip empty/missing labels (getXppField returns -1 if not found)				
						//printf("skipped: lin[%i] col[%i], label %i\n",lineIndex,columnIndex,getXppField(S,lineIndex,columnIndex,XPP_FIELD_LABEL));
						minorFrame[columnIndex-1].buffer  = 0;							
						minorFrame[columnIndex-1].label   = 0;
						minorFrame[columnIndex-1].cid     = 0;
						minorFrame[columnIndex-1].length  = 0;
						minorFrame[columnIndex-1].options = MXF_A629_TXPERIODIC_MJRFRAME_MSG_OPT_UNUSED;															
					}
					
				}
			
			//assign the information to the XPP			
			rc = mxfA629TxPeriodicMajorFrameSet(rt, 0, lineIndex-1, currentMinFrameLength, minorFrame);				
			if(rc != MAXT_SUCCESS){printf("Error code (RT: MajorFrameSet)[%i] = 0x%lX\n",lineIndex, rc);}								
			
		}
		
		
		
		
		
		
		//set mode and start transmission
		

		if(!rc)
		{
			//set block or indipendent mode
			if((int_T)mxGetPr(RT_MODE_ARG)[0] == 1){				
				//printf("block mode\n");
				majorProperties.mode = MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES_MODE_BLOCK;			
			}else if((int_T)mxGetPr(RT_MODE_ARG)[0] == 2){				
				//printf("independent mode\n");
				majorProperties.mode = MXF_A629_TXPERIODIC_MJRFRAME_PROPERTIES_MODE_INDEPENDENT;
			}
			majorProperties.reserved = 0;			
					
			//starts transmitting 
			rc = mxfA629TxPeriodicMajorFrameStart(rt, 0, &majorProperties);			
			if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfA629TxPeriodicMajorFrameStart) = 0x%lX\n", rc);}			
		}

		
	}
	
	
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
	
	
	
	uint16_T 			*uPtr		;
	uint32_T  			numCells	;	
	uint32_T  			cellIndex	;
	int_T				i			;
	int_T				itemp		;
	int_T				portWidth	;
	MXF_A629_DATAREC	txRec629	;	
	uint32 				rc 			;	
	HMXF_BUFFER         *txBuffer	;
	uint32_T			counter, lcm;
	


	
	
	
	//get the buffer address (allocated in the mdlStart)
	txBuffer = ssGetPWorkValue(S,TX_BUFF_P_IDX);
	counter  = (uint32_T)ssGetIWorkValue(S,XPP_COUNTER);
	lcm = (uint32_T)mxGetPr(INDEP_MODE_COUNTER_ARRAY_ARG)[((uint32_T)mxGetN(INDEP_MODE_COUNTER_ARRAY_ARG))-1];
	
	
	
	
	numCells = (uint16_T)mxGetN(REDUCED_XPP_ARG);
	
	
	//iterate over the input ports		
	for(cellIndex = 0; cellIndex < numCells ; cellIndex++){
	
		//added
		itemp =(uint32_T)mxGetPr(REDUCED_XPP_ARG)[cellIndex]-1;		
		
		//fill in datarec---------------------------------------------------
		//set txRec629 to 0
		memset(&txRec629, 0, sizeof(txRec629));
		
		//get the width of the current input port
		portWidth = ssGetInputPortWidth(S, cellIndex);		
	
		//get the input port data pointer
		uPtr = (uint16_T*)ssGetInputPortSignal(S,cellIndex);
		
		//fill txRec629 structure
		txRec629.control     	= 0;
		txRec629.repeatCount 	= 1;
		txRec629.dataSize    	= 2+2*portWidth;
		txRec629.data[0] 		= 0;
				
		for(i = 1; i<= portWidth;i++){	
			//assign data from input port (uPtr) to the data field of txRec629			
			txRec629.data[i] 	= uPtr[i-1];			
		}
		
		if((int_T)mxGetPr(RT_MODE_ARG)[0] == 1)//if block mode				
		{ 
			rc = mxfA629TxPeriodicUpdateMsgWrite(txBuffer[itemp], 1, &txRec629);
		}else if((int_T)mxGetPr(RT_MODE_ARG)[0] == 2)//if indipendent mode	
		{
			if((int_T)mxGetPr(INDEP_MOD_OPT_ARG)[0]){ //optimize if optimization is enabled				
			
				if((counter)%((uint32_T)mxGetPr(INDEP_MODE_COUNTER_ARRAY_ARG)[cellIndex])== (uint32_T)mxGetPr(XPP_ARRAY_ARG)[itemp*CSV_LINE_LEN]-1){					
					rc = mxfA629TxPeriodicUpdateMsgWrite(txBuffer[itemp], 1, &txRec629);														
				}			
			}else{//update all if optimization is disbled							
				rc = mxfA629TxPeriodicUpdateMsgWrite(txBuffer[itemp], 1, &txRec629);				
				if(rc != MAXT_SUCCESS){printf("Error code (RT: mxfA629TxPeriodicUpdateMsgWrite) = 0x%lX\n", rc);}		
			}
		}		
	}
	
	if(counter == lcm-1 ){
		counter = 0;
	}else{
		counter++;
	}
	ssSetIWorkValue(S,XPP_COUNTER,counter);
	
	

#endif	
}
//==========================================================================================
static void mdlTerminate(SimStruct *S)
{	
#ifndef MATLAB_MEX_FILE
	
	if(!xpcIsModelInit()){
		HMXF_BUFFER  *txBuffer;
		uint32_T index, numCells;
		uint32 rc = 0;
		int_T 										channelIndex	=	(int_T)mxGetPr(CHANNEL_ID_ARG)[0]	;
		int_T		 								moduleIndex		= 	(int_T)mxGetPr(MODULE_ID_ARG)[0]-1	;
		
		HMXF_CHANNEL rt = (HMXF_CHANNEL)ssGetIWorkValue(S,RT_IDX);
		numCells 		= (uint8_T)mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;
		
		mxfTxPeriodicMajorFrameStop(rt,0,0);
		
		txBuffer = (HMXF_BUFFER*)ssGetPWorkValue(S,TX_BUFF_P_IDX);
		
		
		for(index=0; index<numCells && !rc; index++){
				rc = mxfTxPeriodicUpdateMsgClear(txBuffer[index],MXF_TXPERIODIC_UPDATEMSG_CLEAR_OPT_DEFAULT);
				
				rc = mxfTxPeriodicUpdateMsgBufferFree(txBuffer[index]);						
				if(rc != MAXT_SUCCESS){printf("Error code (RT: FreetxBuffer) = 0x%lX\n", rc);return;}
		}
		
		xpcFreePhysicalMemory(txBuffer);	
		
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
				printf("Error code (rt[%i]: mxfSystemResourcesRelease) =0x%lX\n",channelIndex, rc);return;
			}else
				printf("done!\n");
			
			//disconnect from device
			rc=mxfServerDisconnect(sg_io629_server);
			
			if(rc)
				printf("mxfServerDisconnect rc=%08X \n", rc);
			
			printf("**************************************\n");
		}	
		
	}
	
#endif
}
//==========================================================================================
static uint8_T getNumMinorFrames(SimStruct *S){
	 
	uint8_T retVal = (uint8_T)mxGetPr(XPP_ARRAY_ARG)[mxGetN(XPP_ARRAY_ARG)-CSV_LINE_LEN];
	
	return retVal;
}
//==========================================================================================
static uint16_T maxMinorFrameLength(SimStruct *S){
	uint8_T retVal = (uint8_T)mxGetPr(XPP_ARRAY_ARG)[1];
	uint8_T i;	
	
	for(i = 1; i < mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;i++){
		//printf("line[%i] = %i\n",i,(uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*5+1]);
		if((uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1] > retVal){
			retVal = (uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1];
			
		}
	}
	return retVal;
}
//==========================================================================================
static uint8_T getMinorFrameLength(SimStruct *S,uint8_T n){
	uint8_T retVal = 0;
	uint8_T i;	
		
	for(i = 0; i < (uint16_T)mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;i++){	
	
	
	if((uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN] == n){
			//printf("entered n = %i\n",n);
			if((uint16_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1] > retVal){			
			
				retVal = (uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1];		
				
			}
		}				
	}
	return retVal;	
}
//==========================================================================================
static uint16_T getXppField(SimStruct *S,uint8_T line,uint8_T column,uint8_T field){
	uint16_T i;	
	uint16_T retVal = -1;
	//field == 2 ->label
	//field == 3 ->length		
	for(i = 0; i < (uint16_T)mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;i++){
		
		if((uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN] == line && (uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1] == column){
				retVal = (uint16_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+field];		
		}			
	}
	
	return retVal;	
}
//==========================================================================================
static uint16_T getNumUsedCells(SimStruct *S){
	uint16_T retVal = 0;
	uint16_T i;
	
	for(i = 0; i < mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;i++){
		if(mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+XPP_FIELD_LABEL] != 0){
			retVal++;			
		}		
	}
	
	return retVal;
	
}
//==========================================================================================
static uint16_T getColumnDepth(SimStruct *S,uint8_T n){
	uint16_T retVal = 0;
	uint16_T i;
	
	for(i = 0; i < mxGetN(XPP_ARRAY_ARG)/CSV_LINE_LEN;i++){
		if((uint8_T)mxGetPr(XPP_ARRAY_ARG)[i*CSV_LINE_LEN+1] == n){
			retVal++;
		}
	}
	
	
	return retVal;
	
}
//==========================================================================================
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
//==========================================================================================





static void wait_us(real_T t){
	xpcBusyWait(t/(1000000.0));
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif