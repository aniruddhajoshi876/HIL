#define         DEBUG                  0

#define         S_FUNCTION_LEVEL       2
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME        sg_IO601_write2_s

#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>

#include        "simstruc.h"


#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
//#include    "can_datatype.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#include 		"../common/libsg/sg_common.h"
#endif

#define DEVNAME "Speedgoat IO601"
#define VENDORID 0x10b5
#define DEVICEID 0x9030
#define SUBVENDORID 0x10b5
#define SUBDEVICEID 0x2977

#define         MAXEXTIDENT            536870911
#define         MAXSTDIDENT            2047


#define         NUMBER_OF_ARGS         (8)
#define         MODULE_ARG             ssGetSFcnParam(S,0)
#define         STATUS_ARG             ssGetSFcnParam(S,1)
#define         INPORT_DATA_TYPE_ARG   ssGetSFcnParam(S,2)
#define         COUNT_ARG              ssGetSFcnParam(S,3)
#define         MAXMSG_ARG             ssGetSFcnParam(S,4)
#define         PORT_ARG               ssGetSFcnParam(S,5)
#define         SAMP_TIME_ARG          ssGetSFcnParam(S,6)
#define         SLOT_ARG               ssGetSFcnParam(S,7)

#define NO_I_WORKS              (2)
#define IOADDRESS0_I_IND        (0)
#define IOADDRESS2_I_IND        (1)

#define NO_R_WORKS              (0)

#define NO_P_WORKS              (0)

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

// struct canMsg  
// {
//     uint8_T Extended;
//     uint8_T Length;
// 	uint8_T Remote;
//     uint8_T Error;
// 	uint32_T ID;
//     double Timestamp;
//     uint8_T Data[8];
// 
// };

typedef struct{
    uint8_T Extended;
    uint8_T Length;
    uint8_T Remote;
    uint8_T Error;
    uint32_T ID;
    double Timestamp;
    uint8_T Data[8];    
}canMsg;

#ifndef MATLAB_MEX_FILE

extern uint8_T SGXPCCANIPCIXC16PMC[];

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

static unsigned char get_double_byte(double value, int n)
{
    unsigned char *p;

    p = (unsigned char *) &value;
    return p[n];
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

#ifdef MATLAB_MEX_FILE
    int_T canMsgT, status;
    DTypeId id;
    canMsg tmp;

	if ( (int_T)mxGetPr(COUNT_ARG)[0] ) {
		ssSetNumInputPorts(S, 2);
		ssSetInputPortWidth(S, 1, 1);
        ssSetInputPortDirectFeedThrough(S, 1, 1);
        ssSetInputPortRequiredContiguous( S, 1, 1 );
	}
	else{
		ssSetNumInputPorts(S, 1);
	}


	// inport datatype can be either a matrix (m*6 or m*5)
	if ((int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 1){
		if (!ssSetInputPortMatrixDimensions(S, 0, DYNAMICALLY_SIZED, DYNAMICALLY_SIZED)) return;

	}
	else{ //or CAN_MESSAGE
		//mdlInitialize_CAN_datatype(S);
        //canMsgT = ssGetDataTypeId( S, SL_CAN_MESSAGE_DTYPE_NAME );
        id = ssRegisterDataType(S, "CAN_MESSAGE");
        if(id == INVALID_DTYPE_ID) return;
        
        status = ssSetDataTypeSize(S, id, sizeof(tmp));
        
        canMsgT = ssGetDataTypeId( S, "CAN_MESSAGE" );
        
		ssSetInputPortDataType( S, 0, canMsgT );
		ssSetInputPortWidth(S, 0, mxGetPr(MAXMSG_ARG)[0]);
	}
	ssSetInputPortDirectFeedThrough(S, 0, 1);
	ssSetInputPortRequiredContiguous(S, 0, 1);  
	


    if ((int_T)mxGetPr(STATUS_ARG)[0] && (int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 1)
    {
        ssSetNumOutputPorts(S, 1);
        ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
    } 
    else if ((int_T)mxGetPr(STATUS_ARG)[0] && (int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 2)
    {
        ssSetNumOutputPorts(S, 1);
        ssSetOutputPortWidth(S, 0, mxGetPr(MAXMSG_ARG)[0]);
    }
    else
    {
        ssSetNumOutputPorts(S, 0);
    }

#endif
    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i=0;i<NUMBER_OF_ARGS;i++) {
        ssSetSFcnParamNotTunable(S,i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

}

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
	if( (int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 1){
		if (dimsInfo->dims[1] != 5 && dimsInfo->dims[1] != 6) {
			sprintf(msg,"Input must be a m*5 or a m*6  matrix");
			ssSetErrorStatus(S,msg);
			return;
		}
		if (!ssSetInputPortDimensionInfo(S, portIndex, dimsInfo)) return;
		if ((int_T)mxGetPr(STATUS_ARG)[0]) {
			if (!ssSetOutputPortVectorDimension(S, 0, dimsInfo->dims[0])) return;
		}
	}

}

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo)) return;
}

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
	if( (int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 1){
		if (!ssSetInputPortMatrixDimensions(S, 0, 1, 5)) return;
		if ((int_T)mxGetPr(STATUS_ARG)[0]) {
			if (!ssSetOutputPortVectorDimension(S, 0, 1)) return;
		}
	}

}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, mxGetPr(SAMP_TIME_ARG)[0]);
    if (mxGetN((SAMP_TIME_ARG))==1) {
        ssSetOffsetTime(S, 0, 0.0);
    } else {
        ssSetOffsetTime(S, 0, mxGetPr(SAMP_TIME_ARG)[1]);
    }

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
    
    ssSetIWorkValue(S, IOADDRESS0_I_IND, (uint32_T)ioaddress0);
    ssSetIWorkValue(S, IOADDRESS2_I_IND, (uint32_T)ioaddress2);
    
       
#endif
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    
#ifndef MATLAB_MEX_FILE

    int_T      frc, i, m, j, k1, k2;
    uint8_T   *p_data;
    real_T    *u, *y, *in, dataReal;
    canMsg    *u1;
    int_T idx;
    int_T cnt;

    int_T     *dims;
    int_T      control, doSend, doMC;
    
    uint32_T regtemp, temp;
    uint8_T module= (uint8_T)mxGetPr(MODULE_ARG)[0]-1;
    uint8_T message[20];
    uint32_T message_32[5];
    
    volatile uint32_T *ioaddress0;
    volatile uint32_T *ioaddress2_32;
    uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
    uint32_T  base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);

    ioaddress0=(volatile uint32_T *) base0;
    ioaddress2_32=(volatile uint32_T *) base2;
    
    if ( (int_T)mxGetPr(INPORT_DATA_TYPE_ARG)[0] == 2 ) { // input is of type CAN_MESSAGE
        
        u1 = (canMsg *)ssGetInputPortSignal(S,0);
        
        if ((int_T)mxGetPr(STATUS_ARG)[0]) {
            y= (real_T *) ssGetOutputPortSignal(S,0);
        }
        
        dims= ssGetInputPortDimensions(S,0);



        if ( (int_T)mxGetPr(COUNT_ARG)[0] ){ // if inport count is displayed
            // count limits the send
            in = (real_T *)ssGetInputPortSignal(S, 1);

            cnt = (int_T)in[0];

            // saturate cnt
            if (cnt > dims[0]){
                cnt = dims[0];
            }
        }
        else{
            cnt = dims[0];
        }
              
        for (idx = 0; idx < cnt; idx++){ // browse all the CAN_MESSAGE, input width is equal to CAN_MESSAGE count
            
            int32_T ident = u1[idx].ID;
            uint8_T type = u1[idx].Extended;
            uint8_T fsize = u1[idx].Length;
            uint8_T remote = u1[idx].Remote;
            int_T doSend = 1; // the frame is supposed to be send... except if there is a reason to not send it.
            
           
//             printf("ID: %d\n", u1[idx].ID);
//             printf("Extended: %d\n", u1[idx].Extended);
//             printf("Length: %d\n", u1[idx].Length);
//             printf("Remote: %d\n", u1[idx].Remote);
                    
            
            if (ident < 0){ //negative ID is a "don't send this one" flag.
                doSend = 0;                
            }

            if (type != 0 && type != 1){
                doSend = 0;
                frc = -11; // type is not standard and not extended.
            }

            switch (type){

                case 0:
                    if (ident > 2047){
                        doSend = 0;
                        frc = -12; //in standard, identifer cannot be larger than 2
                    }
                    break;

                case 1:
                    if (ident > 536870911){
                        doSend = 0;
                        frc = -13;
                    }
                    break;
            }

            if (fsize > 8){
                doSend = 0;
                frc = -14;
            }

            if (doSend){              

                
                if (remote){
                
                    /* This functionality isn't implemented yet. */
                    sprintf(msg, "Remote frame are not supported yet.");
                    ssSetErrorStatus(S, msg);
                    return;
                    
                }
                else{
                    
                }  
                
                /*
                 *
                 **/
                k1= SGXPCCANIPCIXC16PMC[0 + module*4];
                k2= SGXPCCANIPCIXC16PMC[1 + module*4];
                
                doMC=1;

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
                        message[10+j]= u1[idx].Data[j];
                    }

                } else { // extended
                    message[7]= 0x80 | fsize;
                    temp= GenId29(ident);
                    message[8]= temp & 0xff;
                    message[9]= (temp >> 8) & 0xff;
                    message[10]= (temp >> 16) & 0xff;
                    message[11]= (temp >> 24) & 0xff;
                   
                    for (j=0;j<fsize;j++) { 
                        message[12+j]= u1[idx].Data[j];
                        //printf("%d   ", ptr->Data[j]);
                    }
                    //printf("\n");
                }

                memcpy(message_32, message, 20);

                if ( (int_T)mxGetPr(PORT_ARG)[0] == 1 ) {
                    //printf("%d\n", ioaddress2_32[20+k1*5+3]);
                    for (j=0;j<5;j++) {
                        ioaddress2_32[20+k1*5+j]= message_32[j];
                    }
                    k1++;
                    if (k1==50) k1=0;
                } else {
                    for (j=0;j<5;j++) {
                        ioaddress2_32[270+k2*5+j]= message_32[j];
                    }
                    k2++;
                    if (k2==50) k2=0;
                }

            }

            if ((int_T)mxGetPr(STATUS_ARG)[0]) {
                y[idx]= (real_T)frc;
            }
            
            if (doMC) {   
                // generate MC interrupt
                regtemp= ioaddress0[0x15];
                ioaddress0[0x15]= regtemp & ~(1 << 2);
                ioaddress0[0x15]= regtemp | (1 << 2);
            }

            SGXPCCANIPCIXC16PMC[0 + module*4]= k1;
            SGXPCCANIPCIXC16PMC[1 + module*4]= k2;           

        }

    }
    else { // input is a matrix of double
        dims= ssGetInputPortDimensions(S,0);
        if (dims[1] == 5) {
            control=0;
            m=dims[0];
        } else {
            control=1;
            m=6;
        }
        //m=dims[0];

        u= (real_T *) ssGetInputPortSignal(S,0);

        if ((int_T)mxGetPr(STATUS_ARG)[0]) {
            y= (real_T *) ssGetOutputPortSignal(S,0);
        }

        k1= SGXPCCANIPCIXC16PMC[0 + module*4];
        k2= SGXPCCANIPCIXC16PMC[1 + module*4];

        doMC=0;

        for (i=0;i<m;i++) {
            //printf("%f %f %f %f %f\n",u[i+m*0], u[i+m*1], u[i+m*2], u[i+m*3], u[i+m*4]);

            int_T           port= (int_T)u[i+m*0];
            uint32_T        ident= (uint32_T)u[i+m*1];
            int_T           type=  (int_T)u[i+m*2];
            int_T           fsize=  (int_T)u[i+m*3];

            frc=0;

            doSend=1;
            if (control) {
                if (u[i+m*5] < 0.5) {
                    doSend=0;  
                }
            }

            /* check for valid format */

            if (port!=1 && port!=2) {
                doSend=0;
                frc=-10;
            }

            if (type!=0 && type!=1) {
                doSend=0;
                frc=-11;
            }

            switch (type) {
              case 0:
                if (ident<0 || ident>MAXSTDIDENT) {
                    doSend=0;
                    frc=-12;
                }
                break;
              case 1:
                if (ident<0 || ident>MAXEXTIDENT) {
                    doSend=0;
                    frc=-13;
                }
                break;
            }

            if (fsize<0 || fsize>8) {
                doSend=0;
                frc=-14;
            }

            if ((int_T)mxGetPr(STATUS_ARG)[0]) {
                if (port==1) {
                    if (ioaddress2_32[20+k1*5+0] & 0x000000ff) {
                        doSend=0;
                        frc= -1;
                    }
                } else {
                    if (ioaddress2_32[270+k2*5+0] & 0x000000ff) {
                        doSend=0;
                        frc= -1;
                    }
                }
            }

            if (doSend) {

                doMC=1;

                dataReal= u[i+m*4];
                p_data= (uint8_T *) &dataReal;

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
                        message[10+j]= p_data[j];
                    }

                } else { // extended
                    message[7]= 0x80 | fsize;
                    temp= GenId29(ident);
                    message[8]= temp & 0xff;
                    message[9]= (temp >> 8) & 0xff;
                    message[10]= (temp >> 16) & 0xff;
                    message[11]= (temp >> 24) & 0xff;
                    for (j=0;j<fsize;j++) { 
                        message[12+j]= p_data[j];
                    }
                }

                memcpy(message_32, message, 20);

                if (port==1) {                    
                    for (j=0;j<5;j++) {
                        ioaddress2_32[20+k1*5+j]= message_32[j];
                    }
                    k1++;
                    if (k1==50) k1=0;
                } else {
                    for (j=0;j<5;j++) {
                        ioaddress2_32[270+k2*5+j]= message_32[j];
                    }
                    k2++;
                    if (k2==50) k2=0;
                }

            }

            if ((int_T)mxGetPr(STATUS_ARG)[0]) {
                y[0]= (real_T)frc;
            }

        }

        if (doMC) {   
            // generate MC interrupt
            regtemp= ioaddress0[0x15];
            //ioaddress0[0x15]= regtemp & ~(1 << 2);
            //ioaddress0[0x15]= regtemp | (1 << 2);
        }

        SGXPCCANIPCIXC16PMC[0 + module*4]= k1;
        SGXPCCANIPCIXC16PMC[1 + module*4]= k2;
    }

#endif

}

static void mdlTerminate(SimStruct *S)
{
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
