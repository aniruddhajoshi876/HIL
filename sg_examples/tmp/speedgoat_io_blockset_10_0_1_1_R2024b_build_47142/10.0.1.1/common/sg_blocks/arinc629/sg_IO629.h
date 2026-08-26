#ifndef SG_IO629_H
#define SG_IO629_H

#include <stddef.h>
#include <stdlib.h>			 

#include "simstruc.h" 		
#include 		"include/mxfapi.h"

	 
#ifdef 	 MATLAB_MEX_FILE
	#include "mex.h"
#endif   

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#endif

#define DEVNAME "Speedgoat IO629"
#define VENDORID 0x1957
#define DEVICEID 0x0012
#define SUBVENDORID 0x154a
#define SUBDEVICEID 0x0012

#define CSV_LINE_LEN	4


uint8_T api_is_init;
uint8_T ch_is_enabled[484]	;







#endif

