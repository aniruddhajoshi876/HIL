#define 	S_FUNCTION_LEVEL 	2
#undef 	S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO112_addma_s

#include 	<stddef.h>
#include 	<stdlib.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef     MATLAB_MEX_FILE
#include    <windows.h>
#include    "xpcimports.h"
#endif


// Board 
#define DEVNAME "Speedgoat IO112"
#define VENDORID 0x10b5
#define DEVICEID 0x9056
#define SUBVENDORID 0x10b5
#define SUBDEVICEID 0x3431

//#define DEBUG 1

// Input Arguments
#define NUMBER_OF_ARGS          (11)
#define CAL_ARG                 ssGetSFcnParam(S,0)
#define INITIATOR_ARG           ssGetSFcnParam(S,1)
#define ADCHANNEL_ARG           ssGetSFcnParam(S,2)
#define ADRANGE_ARG             ssGetSFcnParam(S,3)
#define ADCOUPLING_ARG          ssGetSFcnParam(S,4)
#define FRAMESIZE_ARG           ssGetSFcnParam(S,5)
#define CLOCKDIVIDER_ARG        ssGetSFcnParam(S,6)
#define SAMP_TIME_ARG           ssGetSFcnParam(S,7)
#define SLOT_ARG                ssGetSFcnParam(S,8)
#define INVERTIO_ARG            ssGetSFcnParam(S,9)
#define ADRESOLUTION_ARG        ssGetSFcnParam(S,10)

#define NO_I_WORKS              (5)
#define PLX_I_IND               (0)
#define BOARD_I_IND             (1)
#define N_CHANNELS_I_IND        (2)
#define CHAN_BUF                (3)
#define RAW_BUF                 (4)

#define NO_R_WORKS              (2)
#define GAIN_R_IND              (0)
#define OFFSET_R_IND            (1)

#define NO_P_WORKS              (0)

// some constants to make the code more readable
#define TARGET_MODE	 0
#define INTERNAL_A	 1
#define INTERNAL_B	 2
#define BCR_IN_SYNC	 3
#define PLUS_MINUS_10 2
#define PLUS_MINUS_5  1


// global varibles
static char_T msg[256];

// PLX adressing map
struct plxdma { // at BAR[0] + 0x80
    volatile uint32_T dma0mode;
    volatile uint32_T dma0addr;
    volatile uint32_T dma0local;
    volatile uint32_T dma0bcnt;
    volatile uint32_T dma0descr;
    volatile uint32_T dma1mode;
    volatile uint32_T dma1addr;
    volatile uint32_T dma1local;
    volatile uint32_T dma1bcnt;
    volatile uint32_T dma1descr;
    volatile uint8_T dma0csr;
    volatile uint8_T dma1csr; 
    volatile uint16_T d1; 
    volatile uint32_T dmaarb;
    volatile uint32_T dmathresh; 
};

// IO112 addressing map
struct IO112 {
		volatile uint32_T bcr;
		volatile uint32_T icr;
		volatile uint32_T inputDataBuffer;
		volatile uint32_T inputBufferControl;
		volatile uint32_T rateAGenerator;
		volatile uint32_T rateBGenerator;
		volatile uint32_T bufferSize;
		volatile uint32_T burstSize;
		volatile uint32_T scanAndSyncControl;
		volatile uint32_T activeChannelAssignment;
		volatile uint32_T boardConfiguration;
		volatile uint32_T autoCalValues;
		volatile uint32_T auxRWRegisters;
		volatile uint32_T auxSyncIOControl;
		volatile uint32_T scanMarkerUpperWord;
		volatile uint32_T scanMarkerLowerWord;   
		volatile uint32_T tur;	
		volatile uint32_T reserved1; 
		volatile uint32_T reserved2 ;
		volatile uint32_T reserved3 ;
		volatile uint32_T reserved4 ;
		volatile uint32_T reserved5 ;
		volatile uint32_T reserved6 ;
		volatile uint32_T reserved7 ;
		volatile uint32_T reserved8 ;
		volatile uint32_T reserved9 ;
		volatile uint32_T reserved10;
		volatile uint32_T reserved11;
		volatile uint32_T reserved12;
		volatile uint32_T reserved13;
		volatile uint32_T reserved14;
		volatile uint32_T reserved15;
};

static void mdlInitializeSizes(SimStruct *S)
{
    uint16_T i;
    uint32_T nChannels;


	 
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }
    
    //check if any pointer is NULL
    for(i=0; i< NUMBER_OF_ARGS; i++)
    {
        if(mxGetPr(ssGetSFcnParam(S,i)) == NULL)
        {
            sprintf(msg,"Input Argument %d is not valid!\n",i);
            ssSetErrorStatus(S,msg);
            return;
        }
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    /* This block has no input port */
    ssSetNumInputPorts(S, 0);    
	
	//Pseudo diff mode is not supported, differential and single ended modes have the same nb of channels
	 nChannels = (uint32_T)mxGetPr(ADCHANNEL_ARG)[0];
	     
    // One output port per channel...
    ssSetNumOutputPorts(S, nChannels);
    
    // ... Where each channel is wide of number of samples (frame construction)
    for (i = 0; i < nChannels; i++){
        ssSetOutputPortWidth(S, i, (uint32_T)mxGetPr(FRAMESIZE_ARG)[0]);
    }    
            
    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    // We don't allow any modifications on parameters during the runtime...
    for (i = 0 ; i < NUMBER_OF_ARGS ; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
    
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMP_TIME_ARG)[0] == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else {
        ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_START
static void mdlStart(SimStruct *S) {
#ifndef MATLAB_MEX_FILE
    
    xpcPCIDevice pciinfo;
    uint_T i, size;
    real_T ticks, start;
    uint32_T bus, slot;
    uint32_T nChannels, lastChannelPos;
    
    int raw_buffer;
    int direct_buffer;
    volatile struct plxdma *plx;
    volatile struct IO112 *IO112;

    uint32_T adrange, sampleClockSource;
    uint32_T reg;
    
    int frameSize;    

	 
    if (mxGetN(SLOT_ARG) == 1){
        bus = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else{
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }
    
    // Try to find the board by using the bus and slot information. 
    // the PCI device information is stored in the pciinfo variable (reason why we give a pointer as argument)
    if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo)){
        sprintf(msg, "%s (bus %d, slot %d): board not present", DEVNAME, bus, slot );
        ssSetErrorStatus(S,msg);
        return;
    }

    // Configure the virtual addresses. Get pointer to BAR0 and BAR2, respectively the PLX reference and the AD module itself 
    pciinfo.VirtAddress[0] = (uint32_T)xpcReserveMemoryRegion( (void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE );
    pciinfo.VirtAddress[2] = (uint32_T)xpcReserveMemoryRegion( (void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE );     
    
    // Assign to the pointers, the virtual addresses
    IO112 = (struct IO112 *)(pciinfo.VirtAddress[2]); // get the virtual address of the AD module  
    plx = (struct plxdma *)(pciinfo.VirtAddress[0] + 0x80); // get the virtual address of the PCI bridge controller + DMA offset    

    // Compute some values, like the gain and the offset, we store them then into an RWork  
       	
		 
   if ((uint32_T)mxGetPr(ADRESOLUTION_ARG)[0]==1) // 18-bit	
	{  
		switch ((uint16_T)mxGetPr(ADRANGE_ARG)[0]) 
		{
        case 1: // +-10V
            ssSetRWorkValue(S, GAIN_R_IND, 13107.2);
            ssSetRWorkValue(S, OFFSET_R_IND, 10.0);
            adrange = PLUS_MINUS_10;
            break;
            
        case 2: // +-5V 
            ssSetRWorkValue(S, GAIN_R_IND, 26214.4);
            ssSetRWorkValue(S, OFFSET_R_IND, 5.0);      
            adrange = PLUS_MINUS_5;    
            break;            
		}
	}
	else // 16-bit
	{
		switch ((uint32_T)mxGetPr(ADRANGE_ARG)[0]) 
		{
         case 1: // +-10V
				ssSetRWorkValue(S, GAIN_R_IND, 3276.8);
            ssSetRWorkValue(S, OFFSET_R_IND, 10.0);
				adrange = PLUS_MINUS_10;
            break;
         case 2:  // +-5V 
            ssSetRWorkValue(S, GAIN_R_IND, 6553.6);
            ssSetRWorkValue(S, OFFSET_R_IND, 5.0);     
				adrange = PLUS_MINUS_5; 				
            break;
      }
	}
	
    reg = IO112->boardConfiguration;
    reg = reg & 0x40000;    //mask Master Clock 
    if (reg != 0)
    {
        sprintf(msg,"Master Clock not 36MHz");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    //---------------------------------------------------------------------
    // Configure the AD module
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------

    // 1. Reinit the board, we start with a known state.
    IO112->bcr = (1 << 15);
	 IO112->bcr = IO112->bcr &  ~(0x00000030); //set to 0 analog input range
	 
    start = rl32eGetTicksDouble();
    while ( (IO112->bcr & (1 << 15)) == (1 << 15) ) {
        ticks = rl32eGetTicksDouble();
        if( ticks - start > 1193000.0 * 1.0 ) {   // 1 second timeout
            sprintf(msg,"  %s: timeout during init operation", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
    }    
    
    printf("  %s: Board reseted to a known state.\n", DEVNAME);        
    

    // start channel is always 0.
    nChannels  = (uint32_T)mxGetPr(ADCHANNEL_ARG)[0];
    lastChannelPos = nChannels - 1;     
    IO112->activeChannelAssignment = (lastChannelPos << 8);
    
    // 3. Configure the sample clock source and the active channels.
        
    if ((uint16_T)mxGetPr(INITIATOR_ARG)[0] == 1)
    {
        printf("  %s: Board configured as an HW clock / initiator\n", DEVNAME);
        sampleClockSource = INTERNAL_A; // If the board acts as initiator, then we use the Rate-A generator
        IO112->rateAGenerator = (1 << 16) | (uint16_T)mxGetPr(CLOCKDIVIDER_ARG)[0];
        IO112->scanAndSyncControl = (0x7 | (sampleClockSource << 3)); 
        printf("  %s: Sample rate: %4.5f[KHz]\n", DEVNAME, 36000000.0/(double)mxGetPr(CLOCKDIVIDER_ARG)[0]/1000);
    } 
    else 
    {
        printf("  %s: Board configured as a target\n", DEVNAME);
        sampleClockSource = TARGET_MODE;
        IO112->scanAndSyncControl = (0x7 | (sampleClockSource << 3));
    }     
    

    // 4. Configure the Board Control Register
    
    // BCR: set  offset binary and tha adrange (+-10V or +-5V)
    // offset binary: bcr[6] = 1
	 IO112->bcr = IO112->bcr |  (1 << 6)  | (adrange << 4);
        
	 if(((uint16_T)mxGetPr( INVERTIO_ARG )[0] == 1)) //if selected in the driver, invert synch clk pin logic level
	 {
        IO112->scanAndSyncControl = IO112->scanAndSyncControl | (1 << 11);
    } 
	 else 
	 {
        //nothing, register already inizialized to 0
    }	  
	
	
	if ((uint16_T)mxGetPr(ADRESOLUTION_ARG)[0]==1) {
		  //select 18 bit data
        IO112->inputBufferControl = IO112->inputBufferControl | (1<<20);
		  //disable data paking
		  IO112->bcr = IO112->bcr & ( ~(1 << 18) );
		  
		  
    } 
	 else 
	 {
		  //select 16 bit data
        IO112->inputBufferControl = IO112->inputBufferControl & ( ~(1<<20) );
		  
		  //enable data paking
		  IO112->bcr = IO112->bcr | (1 << 18);
		  
		  //disable data markers
		  IO112->bcr = IO112->bcr | (1 << 11);
		  
		  //Enable data packing markers
		  //IO112->scanMarkerUpperWord = 0x0001;
		  //IO112->scanMarkerLowerWord = 0x0001; 
    } 
	

    // 5. Only at the init time and if requested... The autocalibration
    if (xpcIsModelInit() && ((int)mxGetPr(CAL_ARG)[0] == 1)) {
        
        // bit 13 is used to request an autocal operation. And this bit remains high for a certain while.
        // We need to poll this bit to know when the autocalibration is done.
        IO112->bcr |= (1 << 13);

        start = rl32eGetTicksDouble();
        printf("  %s autocalibration started..\n", DEVNAME);
        
        while( (IO112->bcr & (1 << 13)) == (1 << 13) ) {
            ticks = rl32eGetTicksDouble();
            if( ticks - start > 1193000.0 * 5.0 ) {   // 5 second timeout, protection against never ending loops
                sprintf(msg,"  %s autocalibration timed out", DEVNAME);
                ssSetErrorStatus(S, msg);
                return;
            }
        }

        // BCR[14] is high when the operation is a success.
        if ((IO112->bcr & (1 << 14)) == (1 << 14)){
            printf("  %s autocalibration succeeded.\n", DEVNAME);
        }
        else {
            sprintf(msg,"  %s autocalibration failed", DEVNAME );
            ssSetErrorStatus(S, msg);
            return;
        }        
    }      


    // 7. Configure the threshold (the buffer will be cleared at a later time)
    frameSize = (int)mxGetPr(FRAMESIZE_ARG)[0];
    printf("  %s: Frame size set to %d\n", DEVNAME, frameSize);
    
    //if 16 bit resolution is used the samples need half of the memory to be stored
     if ((uint32_T)mxGetPr(ADRESOLUTION_ARG)[0]==1) // if ADC resolution 18bit
     {
         IO112->inputBufferControl = IO112->inputBufferControl  | nChannels * frameSize - 1;    
        // 8. (for 18bit resolution) Allocate DMA pool        
        printf("  %s: Preparing the DMA pool\n", DEVNAME);
        size = nChannels * frameSize * 4;  
     }
     else // if ADC reslution 16bit
     {
        IO112->inputBufferControl = IO112->inputBufferControl  | ((nChannels * frameSize) / 2) - 1;    
        // 8. (for 16bit resolution) Allocate DMA pool        
        printf("  %s: Preparing the DMA pool\n", DEVNAME);
        size = (nChannels * frameSize * 4) / 2;
     }


    raw_buffer = (int)xpcAllocPhysicalMemory(size + 0x1000);

    for (i = 0; i < size / 4; i++){
        *((int *)raw_buffer + i) = 0;
    }

    direct_buffer = raw_buffer;

    // 9. Configure the PLX and assign the DMA parameters    
    plx->dma0addr = direct_buffer;
    plx->dma0local = 0x8;
    plx->dma0bcnt = size;
    plx->dma0descr = 0xA;
    plx->dma0mode = 0x21D43;
    
    // 10. Save the internal values
    ssSetIWorkValue(S, RAW_BUF, raw_buffer);
    ssSetIWorkValue(S, CHAN_BUF, direct_buffer);
    ssSetIWorkValue(S, PLX_I_IND, pciinfo.VirtAddress[0]);
    ssSetIWorkValue(S, BOARD_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, N_CHANNELS_I_IND, (uint32_T)nChannels);    
    
    // 11. Clear the buffer, bit 18 is used for this purpose and then we poll this bit
    // because the board clears it automatically...
    
    printf("  %s: DMA correctly configured\n", DEVNAME);
    
    IO112->inputBufferControl |= (1 << 18);
    
    start = rl32eGetTicksDouble();
    
    while ( (IO112->inputBufferControl & (1 << 18)) == (1 << 18) ) {
        ticks = rl32eGetTicksDouble();
        if( ticks - start > 1193000.0 * 1.0 ) {   // 1 second timeout
            sprintf(msg, "  %s: timeout during clear buffer operation", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
    }
    
    if ( (IO112->inputBufferControl & (1 << 19) ) == (1 << 19) ){
        sprintf(msg, "  %s: clear buffer operation failed", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }
    else {
        printf("  %s: Buffer cleared\n", DEVNAME);
    }
    
    // 12. Finally, we enable the Rate-A Generator.
    printf("  %s: Rate A Generator enabled\n", DEVNAME);
    IO112->rateAGenerator &= ~(1 << 16);
    
    // 13. Clear int, enable and start (voluntary done in two steps).
    printf("  %s: DMA enabled and started\n", DEVNAME);
    plx->dma0csr |= (1 << 0);    
    plx->dma0csr |= (1 << 1);  
	
	//enable ADC clocking (convertion can start)
	IO112->scanAndSyncControl = IO112->scanAndSyncControl | (1 << 5);	 

#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    
    
    uint32_T nChannels = ssGetIWorkValue(S, N_CHANNELS_I_IND);
    volatile struct IO112 *IO112 = (struct IO112 *)ssGetIWorkValue(S, BOARD_I_IND);
    volatile struct plxdma *plx = (struct plxdma *)ssGetIWorkValue(S, PLX_I_IND);
    uint32_T *databuf = (uint32_T *)ssGetIWorkValue( S, CHAN_BUF );    
    uint32_T coupling = (uint32_T)mxGetPr(ADCOUPLING_ARG)[0];
    uint32_T  frameSize = (int_T)mxGetPr(FRAMESIZE_ARG)[0];
    
    
    real_T gain, offset;
    real_T  *y;
    uint32_T i, j;
    uint32_T count, pos;
    
    gain = ssGetRWorkValue(S, GAIN_R_IND);  
    offset = ssGetRWorkValue(S, OFFSET_R_IND);  


    pos = 0;
	 
	 if ((uint32_T)mxGetPr(ADRESOLUTION_ARG)[0]==1) // if ADC resolution 18bit
	{	
		 for (i = 0; i < frameSize; i++)
		 { 
			  for (j = 0; j < nChannels; j++)
			  {
					y = ssGetOutputPortSignal(S, j);  
				 
					count = databuf[pos];	//read the sample form the memory space   
					y[i] = (real_T)(count & 0x3ffff) / gain - offset;                
					pos++;
			  }
		 }
	 }
	 else// AD resolution 16bit (with data packing)
	 {
			for (i = 0; i < frameSize; i++)
			{ 
				for (j = 0; j < nChannels/2; j++)
				{
				count = databuf[pos]; 
				
				y = ssGetOutputPortSignal(S, j*2); 
				y[i]= (real_T)(count & 0x0000ffff) / gain - offset;
				
				y = ssGetOutputPortSignal(S, 1+j*2); 
				y[i]= (real_T)((count & 0xffff0000) >> 16) / gain - offset;
				
				pos++;
				}
			}		
	  }

#endif
}

static void mdlTerminate(SimStruct *S)
{    
#ifndef MATLAB_MEX_FILE
    
    volatile struct IO112 *IO112 = (struct IO112 *)ssGetIWorkValue(S, BOARD_I_IND );
    volatile struct plxdma *plxdma = (struct plxdma *)(ssGetIWorkValue(S, PLX_I_IND) + 0x80);
	 
	 //Disable clocking (no more acquisition is possible)
	 IO112->scanAndSyncControl = IO112->scanAndSyncControl & ( ~(0x00000020) );
	 
    plxdma->dma0mode = 0x3;
    IO112->inputBufferControl = IO112->inputBufferControl | 0x40000; // and clear the buffer    
    IO112->rateAGenerator = IO112->rateAGenerator | 0x10000; //rate a disable 
     
#endif        
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif

