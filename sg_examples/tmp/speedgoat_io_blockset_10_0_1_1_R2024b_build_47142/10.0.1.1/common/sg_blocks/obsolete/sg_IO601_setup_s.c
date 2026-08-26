

#define DEBUG 0


#define         S_FUNCTION_LEVEL        2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO601_setup_s

#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>

#ifndef         MATLAB_MEX_FILE
#endif

#include        "tmwtypes.h"
#include        "simstruc.h"

#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#include 		"../common/libsg/sg_common.h"
#endif


#define         NUMBER_OF_ARGS              (16)
#define         MODULE_ARG                  ssGetSFcnParam(S,0)
#define         CAN1_ENABLE_ARG             ssGetSFcnParam(S,1)
#define         CAN1_BUS_ARG                ssGetSFcnParam(S,2)
#define         CAN1_USER_BAUDRATE_ARG      ssGetSFcnParam(S,3)
#define         ACC1_ARG                    ssGetSFcnParam(S,4)
#define         FILTERSTD1_ARG              ssGetSFcnParam(S,5)
#define         FILTEREXT1_ARG              ssGetSFcnParam(S,6)
#define         CAN2_ENABLE_ARG             ssGetSFcnParam(S,7)
#define         CAN2_BUS_ARG                ssGetSFcnParam(S,8)
#define         CAN2_USER_BAUDRATE_ARG      ssGetSFcnParam(S,9)
#define         ACC2_ARG                    ssGetSFcnParam(S,10)
#define         FILTERSTD2_ARG              ssGetSFcnParam(S,11)
#define         FILTEREXT2_ARG              ssGetSFcnParam(S,12)
#define         CAN_INIT_ARG                ssGetSFcnParam(S,13)
#define         CAN_TERM_ARG                ssGetSFcnParam(S,14)
#define         SLOT_ARG                    ssGetSFcnParam(S,15)

#define DEVNAME "Speedgoat IO601"
#define VENDORID 0x10b5
#define DEVICEID 0x9030
#define SUBVENDORID 0x10b5
#define SUBDEVICEID 0x2977

#define         NO_I_WORKS                  (2)
#define         IOADDRESS0_I_IND            (0)
#define         IOADDRESS2_I_IND            (1)

#define         NO_R_WORKS                  (0)



// Acceptance filter
#define         ACCEPT_MASK_1               0x0000
#define         ACCEPT_CODE_1               0x0000
#define         ACCEPT_MASK_XTD_1           0x00000000L
#define         ACCEPT_CODE_XTD_1           0x00000000L

#define         ACCEPT_MASK_2               0x0000
#define         ACCEPT_CODE_2               0x0000
#define         ACCEPT_MASK_XTD_2           0x00000000L
#define         ACCEPT_CODE_XTD_2           0x00000000L

#ifndef  LOW8
#define  LOW8(wert)  *( (uint8_T *) &wert)
#endif

#ifndef  HIGH8
#define  HIGH8(wert)  *(((uint8_T *) &wert) + 1)
#endif

#ifndef  LOW16
#define  LOW16(wert)  *( (uint16_T *) &wert)
#endif

#ifndef  HIGH16
#define  HIGH16(wert)  *(((uint16_T *) &wert) + 1)
#endif

#ifndef SWAP16
#define SWAP16(wert)       { uint8_T temp; temp = HIGH8(wert); HIGH8(wert) = (uint8_T) wert; LOW8(wert) = temp; }
#endif

#ifndef SWAP32
#define SWAP32(wert)       { uint16_T temp; temp = HIGH16(wert); HIGH16(wert) = (uint16_T) wert; LOW16(wert) = temp; }
#endif


static char_T msg[256];

#ifndef MATLAB_MEX_FILE

uint8_T SGXPCCANIPCIXC16PMC[40];

static uint32_T GenId11 (uint32_T value)
{
  value = value << 21;

  SWAP16 (HIGH16 (value));
  SWAP16 (LOW16 (value));
  SWAP32 (value);

  return (value);
}

static uint32_T GenId29 (uint32_T value)
{
  value = value << 3;

  SWAP16 (HIGH16 (value));
  SWAP16 (LOW16 (value));
  SWAP32 (value);

  return (value);
}
    
    
static void volatile_memcpy(uint8_T * dest, volatile uint8_T * src, uint32_T n)
{
    uint32_T i=0;
    while (i++ < n) {
      *dest++= *src++;
    }
}

static uint8_T InitCAN(volatile uint32_T * ioaddress0, volatile uint8_T * ioaddress2, uint8_T can_num, uint8_T bt0, uint8_T bt1, uint8_T mode) 
{    
    uint32_T regtemp, i;
    
    ioaddress2[0x000] = 0;
    ioaddress2[0x001] = 5;
    ioaddress2[0x002] = 0;
    ioaddress2[0x003] = 0;
   
    ioaddress2[0x004] = 4;
    ioaddress2[0x005] = can_num;
    ioaddress2[0x006] = bt0;
    ioaddress2[0x007] = bt1;
    ioaddress2[0x008] = mode;
    
    // set sync
    ioaddress2[0x000] = 1;

    // generate MC interrupt
    regtemp= ioaddress0[0x15];
    ioaddress0[0x15]= regtemp & ~(1 << 2);
    ioaddress0[0x15]= regtemp | (1 << 2);
     
    
    i=0;
    while (ioaddress2[0x000]==1) {
        i++;
    }
    //printf("InitCAN: ");
    //printf("loops: %d, ", i);
    /*
    printf("size: %d, ", ioaddress2[0x001]);
    for (i=0;i<2; i++) { 
      printf("0x%x ", ioaddress2[0x004+i]);
    }
    printf("\n");
    */
    
    return 0;
}

static uint8_T StartCAN(volatile uint32_T * ioaddress0, volatile uint8_T * ioaddress2, uint8_T can_num)
{
    // start CAN
    // port= 0
    
    uint32_T regtemp, i;
    
    ioaddress2[0x000] = 0;
    ioaddress2[0x001] = 2;
    ioaddress2[0x002] = 0;
    ioaddress2[0x003] = 0;
   
    ioaddress2[0x004] = 6;
    ioaddress2[0x005] = can_num;
    
    // set sync
    ioaddress2[0x000] = 1;

    // generate MC interrupt
    regtemp= ioaddress0[0x15];
    ioaddress0[0x15]= regtemp & ~(1 << 2);
    ioaddress0[0x15]= regtemp | (1 << 2);
      
    
    i=0;
    while (ioaddress2[0x000]==1) {
        i++;
    }
    //printf("StartCAN: ");
    //printf("loops: %d, ", i);
    /*
    printf("size: %d, ", ioaddress2[0x001]);
    for (i=0;i<2; i++) { 
      printf("0x%x ", ioaddress2[0x004+i]);
    }
    printf("\n");
     */
    
    return 0;
}

static uint8_T ConfigRxQueue(volatile uint32_T * ioaddress0, volatile uint8_T * ioaddress2, uint8_T can_num, uint8_T mode)
{   
    uint32_T regtemp, i;
    
    ioaddress2[0x000] = 0;
    ioaddress2[0x001] = 3;
    ioaddress2[0x002] = 0;
    ioaddress2[0x003] = 0;
   
    ioaddress2[0x004] = 11;
    ioaddress2[0x005] = can_num;
    ioaddress2[0x006] = mode;
    
    // set sync
    ioaddress2[0x000] = 1;

    // generate MC interrupt
    regtemp= ioaddress0[0x15];
    ioaddress0[0x15]= regtemp & ~(1 << 2);
    ioaddress0[0x15]= regtemp | (1 << 2);
       
    
    i=0;
    while (ioaddress2[0x000]==1) {
        i++;
    }
    //printf("ConfigRxQueue: ");
    //printf("loops: %d, ", i);
    /*
    printf("size: %d, ", ioaddress2[0x001]);
    for (i=0;i<2; i++) { 
      printf("0x%x ", ioaddress2[0x004+i]);
    }
    printf("\n");
    */
    
    return 0;
    
}

static uint8_T StopCAN(volatile uint32_T * ioaddress0, volatile uint8_T * ioaddress2, uint8_T can_num)
{    
    uint32_T regtemp, i;
    
    ioaddress2[0x000] = 0;
    ioaddress2[0x001] = 2;
    ioaddress2[0x002] = 0;
    ioaddress2[0x003] = 0;
   
    ioaddress2[0x004] = 7;
    ioaddress2[0x005] = can_num;
    
    // set sync
    ioaddress2[0x000] = 1;

    // generate MC interrupt
    regtemp= ioaddress0[0x15];
    ioaddress0[0x15]= regtemp & ~(1 << 2);
    ioaddress0[0x15]= regtemp | (1 << 2);
     
    
    i=0;
    while (ioaddress2[0x000]==1) {
        i++;
    }
    //printf("StopCAN: ");
    //printf("loops: %d, ", i);
    /*
    printf("size: %d, ", ioaddress2[0x001]);
    for (i=0;i<2; i++) { 
      printf("0x%x ", ioaddress2[0x004+i]);
    }
    printf("\n");
     */
    
    return 0;
    
}

static uint8_T GetBoardStatus(volatile uint32_T * ioaddress0, volatile uint8_T * ioaddress2)
{
   
    uint16_T status;    
    uint32_T i;
    
    //printf("BoardStatus: ");
    
    for (i = 0;  i < 6; i++) {
        status= ioaddress2[4080+i*2];
        status|=  ioaddress2[4080+i*2+1] << 8;
        //printf("0x%x ", status);
    }
    //printf("\n");
    
    return 0;
           
}

#endif



static void mdlInitializeSizes(SimStruct *S)
{

    int_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 0);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i=0;i<NUMBER_OF_ARGS;i++) {
        ssSetSFcnParamNotTunable(S,i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);


}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}



#define MDL_START
static void mdlStart(SimStruct *S)
{

#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;	
	int_T bus, slot;
    uint32_T moduleID;
    volatile uint32_T *ioaddress0;
    volatile uint8_T *ioaddress2;
    volatile uint32_T *ioaddress2_32;
    uint_T i, k1, k2, m;
    int_T j;
    uint8_T name[128];
    uint8_T version[16];
    uint32_T regtemp, temp;
    char FirmwareName[4];
    uint8_T CommandResult;
    uint8_T message[20];
    uint32_T message_32[5];
    uint8_T bt0, bt1;
    int_T port;
	uint32_T ident;
	int_T type;
	int_T fsize;
    uint8_T module, can1Enable, can2Enable, can1Bus, can2Bus;
    
    module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;
    can1Enable= (uint8_T)mxGetPr(CAN1_ENABLE_ARG)[0];
    can2Enable= (uint8_T)mxGetPr(CAN2_ENABLE_ARG)[0];
    can1Bus=    (uint8_T)mxGetPr(CAN1_BUS_ARG)[0]-1;
    can2Bus=    (uint8_T)mxGetPr(CAN2_BUS_ARG)[0]-1;
    

   	//PCI slot
	if (mxGetN(SLOT_ARG) == 1)
    {
        bus  = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus  = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }	
	
	//Get PCI device
	moduleID = ((int_T)mxGetPr(MODULE_ARG)[0]);
    if(sg_findPciDevice(&pciinfo,DEVNAME, VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, moduleID, bus,slot) != 0)
    {
        ssSetErrorStatus(S, pSgErrorStr);
        return;
    }
	
	// Memory map bar to user space virtual address
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void*)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE );
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void*)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE );
    ioaddress0 = (volatile uint32_T *)pciinfo.VirtAddress[0];
    ioaddress2 = (volatile uint8_T *)pciinfo.VirtAddress[2];
	
    ioaddress2_32=(volatile uint32_T *)pciinfo.VirtAddress[2];
    //printf("Base Address 2: 0x%x\n", ioaddress2);
    
    //if( xpceIsModelInit()) {
        
        //reset board
        regtemp= ioaddress0[0x15];
        //printf("original register content: 0x%x\n", regtemp);
        regtemp&= ~(1 << 11);
        ioaddress0[0x15]= regtemp;
        //ioaddress0[0x15]= regtemp;
        rl32eWaitDouble(0.050); 


        regtemp= ioaddress0[0x15];
        //printf("reset register content: 0x%x\n", ioaddress0[0x15]);
        regtemp|= (1 << 11);
        ioaddress0[0x15]= regtemp;
        regtemp= ioaddress0[0x15];
        //printf("after reset register content: 0x%x\n", regtemp);
        rl32eWaitDouble(0.050);

        //get board name

        memcpy(name, (void *)(ioaddress2+0x10), 64);
        name[64]='\0';
        //printf("Name: %s\n", name);

        //get version
        memcpy(version, (void *)(ioaddress2+0x30), 9);
        version[9]='\0';
        //printf("Version: %s\n", version);

        ioaddress2[0x00] = 0;
        ioaddress2[0x01] = 0;
        ioaddress2[0x02] = 0;
        ioaddress2[0x03] = 2;
        ioaddress2[0x04] = 7;
        ioaddress2[0x05] = 0; 
        ioaddress2[0x00] = 1;
        rl32eWaitDouble(0.050);
        ioaddress2[0x01] = 0;
        rl32eWaitDouble(0.050);

        volatile_memcpy(FirmwareName, ioaddress2+26, 3);
        if (strncmp(FirmwareName, "BCI", 3)) {
                sprintf(msg,"%s: FLASH contains wrong firmware version",DEVNAME);
                ssSetErrorStatus(S,msg);
                return;
        }

        // restart firmware
        ioaddress2[0x00] = 0;
        ioaddress2[0x01] = 0;
        ioaddress2[0x02] = 0;
        ioaddress2[0x03] = 3;
        ioaddress2[0x04] = 2;
        ioaddress2[0x05] = 0;
        ioaddress2[0x06] = 1;
        ioaddress2[0x00] = 1;
        rl32eWaitDouble(0.050);
        ioaddress2[0x01] = 0;
        rl32eWaitDouble(0.050);

        //rl32eWaitDouble(0.5);
        //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
        
        bt0= (((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[1] -1) << 6) | ((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[0] -1);
        bt1= (((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[3] -1) << 4) | ((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[2] -1);
        //printf("bt0: 0x%x, bt1: 0x%x\n", bt0, bt1);
        
        if (can1Enable) {
            printf("        initialize Speedgoat IO601 module %d CAN 1\n", module+1);
            CommandResult= InitCAN(ioaddress0, ioaddress2, 0, bt0, bt1, can1Bus);
            //rl32eWaitDouble(0.5);
            //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
        }

        SGXPCCANIPCIXC16PMC[0 + module*4]= 0;
        SGXPCCANIPCIXC16PMC[2 + module*4]= 0;
        
        bt0= (((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[1] -1) << 6) | ((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[0] -1);
        bt1= (((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[3] -1) << 4) | ((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[2] -1);
        //printf("bt0: 0x%x, bt1: 0x%x\n", bt0, bt1);

        if (can2Enable) {
            printf("        initialize Speedgoat IO601 module %d CAN 2\n", module+1);
            CommandResult= InitCAN(ioaddress0, ioaddress2, 1, bt0, bt1, can2Bus);
            //rl32eWaitDouble(0.5);
            //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
        }

        SGXPCCANIPCIXC16PMC[1 + module*4]= 0;
        SGXPCCANIPCIXC16PMC[3 + module*4]= 0;

        if (can1Enable) {
            CommandResult= ConfigRxQueue(ioaddress0, ioaddress2, 0, 0);
            //rl32eWaitDouble(0.5);
            //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
        }

        if (can2Enable) {
            CommandResult= ConfigRxQueue(ioaddress0, ioaddress2, 1, 0);
            //rl32eWaitDouble(0.5);
            //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
        }
    
    //}
    
    if (can1Enable) {
        CommandResult= StartCAN(ioaddress0, ioaddress2, 0);
        //rl32eWaitDouble(0.5);
        //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
    }
    
    if (can2Enable) {
        CommandResult= StartCAN(ioaddress0, ioaddress2, 1);
        //rl32eWaitDouble(0.5);
        //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
    }
    
    ssSetIWorkValue(S, IOADDRESS0_I_IND, (uint32_T)ioaddress0);
    ssSetIWorkValue(S, IOADDRESS2_I_IND, (uint32_T)ioaddress2);

    // Excute Initialization if necessary

    {
        int_T   start;
        uint8_T data[8];

        if ((int_T)mxGetPr(CAN_INIT_ARG)[0]) {

			k1= SGXPCCANIPCIXC16PMC[0 + module*4];
			k2= SGXPCCANIPCIXC16PMC[1 + module*4];

            start=1;
            
            //printf("Init arg: %d\n", (int_T)mxGetPr(CAN_INIT_ARG)[0]);
            
            //for (i = 0; i < (int_T)mxGetPr(CAN_INIT_ARG)[0]; i++){
               
                

				m = (uint_T)mxGetPr(CAN_INIT_ARG)[0]; 
                
                //printf("m: %d\n", m);

				for (i = 0; i < m; i++) {
                    
                    //printf("data: ");
                
                    for (j = 0; j < (int_T)mxGetPr(CAN_INIT_ARG)[start + 3]; j++) {
                        data[j] = (uint8_T)mxGetPr(CAN_INIT_ARG)[start + 4 + j];
                        //printf("%d  ", data[j]);
                    }
                    //printf("\n");
        
					//printf("%f %f %f %f %f\n",u[i+m*0], u[i+m*1], u[i+m*2], u[i+m*3], u[i+m*4]);

					port = (int_T)mxGetPr(CAN_INIT_ARG)[start];
					ident = (uint32_T)mxGetPr(CAN_INIT_ARG)[start+2];
					type = (int_T)mxGetPr(CAN_INIT_ARG)[start+1];
					fsize = (int_T)mxGetPr(CAN_INIT_ARG)[start+3];
                    
                    //printf("INIT: Module: %d Port: %d, Id: %d, Type: %d, Size: %d\n", module, port, ident, type, fsize);
            
					message[0]= 1;
					message[1]= 18;
        
					message[2]= 0;
					message[3]= 0;
					message[4]= 0;
					message[5]= 0;
        
					message[6]= 0;
        
					if (type==0) { // standard
						message[7]= fsize;
						temp= GenId11(ident);
						message[8]= temp & 0xff;
						message[9]= (temp >> 8) & 0xff;
						for (j=0;j<fsize;j++) { 
							message[10+j]= data[j];
						}
					} else { // extended
						message[7]= 0x80 | fsize;
						temp= GenId29(ident);
						message[8]= temp & 0xff;
						message[9]= (temp >> 8) & 0xff;
						message[10]= (temp >> 16) & 0xff;
						message[11]= (temp >> 24) & 0xff;
						for (j=0;j<fsize;j++) { 
							message[12+j]= data[j];
						}
					}
                   
					memcpy(message_32, message, 20);
                    
					if (port==1) {
						for (j=0;j<5;j++) {
							ioaddress2_32[20+k1*5+j]= message_32[j];
                            //printf("%d   ", message_32[j]);
						}
						k1++;
						if (k1 == 50) 
                            k1=0;
					} else {
						for (j=0;j<5;j++) {
							ioaddress2_32[270+k2*5+j]= message_32[j];
                            //printf("%d   ", message_32[j]);
						}
						k2++;
						if (k2 == 50) 
                            k2=0;
					}
                    
                    //printf("\n");
                    
                    // generate MC interrupt
                    regtemp= ioaddress0[0x15];
                    ioaddress0[0x15]= regtemp & ~(1 << 2);
                    ioaddress0[0x15]= regtemp | (1 << 2);

                    //wait specified ms
                    //printf("Wait for %f [ms]\n", mxGetPr(CAN_INIT_ARG)[start+12]);
                    rl32eWaitDouble(mxGetPr(CAN_INIT_ARG)[start + 12]);

                    start += 13;
                    
                }

			//}
    
			SGXPCCANIPCIXC16PMC[0 + module*4]= k1;
			SGXPCCANIPCIXC16PMC[1 + module*4]= k2;

		}

    }
       
#endif

}

static void mdlOutputs(SimStruct *S, int_T tid)
{
}

/* Function to compute model update */

static void mdlTerminate(SimStruct *S)
{

#ifndef MATLAB_MEX_FILE      

   uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
   uint32_T   base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);
   volatile uint32_T *ioaddress0;
   volatile uint8_T *ioaddress2;
   volatile uint32_T *ioaddress2_32;
   uint8_T CommandResult;
   uint8_T can1Enable, can2Enable;
   uint_T i, k1, k2, m;
   int_T j;
   uint8_T module;
   uint8_T message[20];
   uint32_T message_32[5];
   uint32_T regtemp, temp;
   int_T port;
	uint32_T ident;
	int_T type;
	int_T fsize;
	 
   module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;
    
   can1Enable= (uint8_T)mxGetPr(CAN1_ENABLE_ARG)[0];
   can2Enable= (uint8_T)mxGetPr(CAN2_ENABLE_ARG)[0];
   
   ioaddress0=(void *) base0;
   ioaddress2=(void *) base2;
   ioaddress2_32=(void *) base2;
    
   // Excute Termination if necessary

   {
      int_T   start;
      uint8_T data[8];

      if ((int_T)mxGetPr(CAN_TERM_ARG)[0]) {

			k1 = SGXPCCANIPCIXC16PMC[0 + module*4];
			k2 = SGXPCCANIPCIXC16PMC[1 + module*4];

         start = 1;
    
			m = (uint_T)mxGetPr(CAN_TERM_ARG)[0]; 
                //printf("m: %d\n", m);

				for (i = 0; i < m; i++){
        
					for(j=0;j<(int_T)mxGetPr(CAN_TERM_ARG)[start+3];j++) {
                    data[j]=(uint8_T)mxGetPr(CAN_TERM_ARG)[start+4+j];
               }
		  
					//printf("%f %f %f %f %f\n",u[i+m*0], u[i+m*1], u[i+m*2], u[i+m*3], u[i+m*4]);

					port = (int_T)mxGetPr(CAN_TERM_ARG)[start];
					ident = (uint32_T)mxGetPr(CAN_TERM_ARG)[start+2];
					type = (int_T)mxGetPr(CAN_TERM_ARG)[start+1];
					fsize = (int_T)mxGetPr(CAN_TERM_ARG)[start+3];
                    
                    //printf("TERM: Module: %d Port: %d, Id: %d, Type: %d, Size: %d\n", module, port, ident, type, fsize);
            
					message[0]= 1;
					message[1]= 18;
        
					message[2]= 0;
					message[3]= 0;
					message[4]= 0;
					message[5]= 0;
        
					message[6]= 0;
        
					if (type==0) { // standard
						message[7]= fsize;
						temp= GenId11(ident);
						message[8]= temp & 0xff;
						message[9]= (temp >> 8) & 0xff;
						for (j=0;j<fsize;j++) { 
							message[10+j]= data[j];
						}
					} 
					else { // extended
						message[7]= 0x80 | fsize;
						temp= GenId29(ident);
						message[8]= temp & 0xff;
						message[9]= (temp >> 8) & 0xff;
						message[10]= (temp >> 16) & 0xff;
						message[11]= (temp >> 24) & 0xff;
						
						for (j=0;j<fsize;j++) { 
							message[12+j]= data[j];
						}
					}
                   
					memcpy(message_32, message, 20);
        
					if (port == 1) {
						
						for (j = 0; j < 5; j++) {
							ioaddress2_32[20 + k1 * 5 + j]= message_32[j];
						}
						
						k1++;
						
						if (k1 == 50) 
							k1 = 0;
					} 
					else {
						
						for (j = 0; j < 5; j++) {
							ioaddress2_32[270 + k2 * 5 + j] = message_32[j];
						}
						
						k2++;
						
						if (k2==50) 
							k2=0;
					}

                    // generate MC interrupt
                    regtemp = ioaddress0[0x15];
                    ioaddress0[0x15] = regtemp & ~(1 << 2);
                    ioaddress0[0x15] = regtemp | (1 << 2);

                    //wait specified ms
                    rl32eWaitDouble(mxGetPr(CAN_TERM_ARG)[start + 12]);

                    start += 13;
                    
            }
    
			SGXPCCANIPCIXC16PMC[0 + module*4]= k1;
			SGXPCCANIPCIXC16PMC[1 + module*4]= k2;

		}

   }

   if (can1Enable) {
      CommandResult= StopCAN(ioaddress0, ioaddress2, 0);
      //rl32eWaitDouble(0.5);
      //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
   }
    
   if (can1Enable) {
      CommandResult= StopCAN(ioaddress0, ioaddress2, 1);
      //rl32eWaitDouble(0.5);
      //CommandResult= GetBoardStatus(ioaddress0, ioaddress2);
   }
    
#endif 


}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
