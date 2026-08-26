/*
 * xpcdatatypes.h - xPC Target Header File
 *
 * Copyright 2009 The MathWorks, Inc.
 *
 * Define custom data types used by xPC Target blocks.
 */
#ifndef __SG_MIL_1553_H__
#define __SG_MIL_1553_H__

#include <stdint.h>

#ifndef __XPCDATATYPES__
#define __XPCDATATYPES__ 1

#ifdef MATLAB_MEX_FILE
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif

    // FIFO read and write block communication
    typedef struct serialfifo {
        uint32_T ptrlow;
        uint32_T ptrhigh;
        uint32_T token;
    } serialfifoptr;

    // 1553 blocks pass a pointer to an array of messages
    typedef struct bcmsg1553 {
        uint32_T token;
        uint32_T nmsgs;
        uint32_T ptrlow;
        uint32_T ptrhigh;
    } bcmsglist1553;

    typedef struct bcstat {
        uint32_T control;
        uint32_T cmd1;
        uint32_T stat1;
        uint32_T cmd2;
        uint32_T stat2;
        uint32_T status;
    } bcstatus1553;
    
    typedef struct bmmsg {
        uint32_T token;
        uint32_T nmsgs;
        uint32_T ptrlow;
        uint32_T ptrhigh;
    } bmmsglist1553;

#endif

#endif
