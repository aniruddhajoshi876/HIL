#ifndef _IO821_H_
#define _IO821_H_

//#include "tsync.h"

#if defined(_MSC_VER)
   #if _MSC_VER < 1800
	#error "sg_IO821 lib only supported with VS > 11.0 (VS2012)"
   #endif
#endif

#include <stdint.h>
#include <stdbool.h>	//not available on VS2012 and older

typedef struct RefTab_t
{
    uint8_t enabled;
    uint8_t prio;
    uint8_t time;
    uint8_t pps;
}RefTab_T;

//added in v2:
typedef struct OutputTime_t
{
    double datenum;
    double subsec;
    double ymdhmsArray[6];
    double uSecOfYear;
}OutputTime_t;

#define NUM_REF_TAB_ENTRIES 6

typedef struct IO821_config_tag
{
    int PeriodicIntEnable;
    int NanoPeriod;
    int PeriodicIntAlign;

    RefTab_T RefTab[NUM_REF_TAB_ENTRIES]; // pointer to Reference Table array
    int rt_entries;  // Number of RefTab[] entries
    int showActiveRef;     // output port enabled?
    int showSyncState;     // output port enabled?
    int showHoldoverState; // output port enabled?
    int showAlarmState;    // output port enabled?
    int showTime;    // output port enabled?
    int TimeOffset;    // Time zone offset from UTC in seconds (+/-) (inclues DST!)
    double InitialTime; // datenum
    //added in v2:
    int moduleTimeFormat;     //array or datenum?
    int gpi0EdgeDetectActive; //output port enabled?
    int gpi0SignalEdgeFormat; //falling or rising edge?
    int gpi1EdgeDetectActive; //output port enabled?
    int gpi1SignalEdgeFormat; //falling or rising edge?
    int edgeDetectTimeFormat; //array or datenum?

	int irigEnable;           //output enabled
	int irigExpression;       //IRIG Expression
	int irigCfConfig;         //Control Field mode
	int dt1;                  //lead time until output enable
    int dt2;                  //lead time until output activation

	int hwTrig1Enable;        //HW Trigger 1 enabled
	uint64_t hwTrig1LeadTime;      //HW Trigger 1 Lead Time
	int hwTrig1SignalEdge;    //HW Trigger 1 Signal Edge
	int hwTrig2Enable;        //HW Trigger 2 enabled
	uint64_t hwTrig2LeadTime;      //HW Trigger 2 Lead Time
	int hwTrig2SignalEdge;    //HW Trigger 2 Signal Edge

    int dutyCycle;            //Periodic Int duty cycle
} IO821_config_T;

typedef struct IO821_data_tag
{
    int ActiveRef;               // currently selected reference table entry (1-based)
    bool SyncState;         // TRUE if in sync
    bool HoldoverState;     // TRUE if in holdover
    bool AlarmState;        // TRUE if in alarm state
    double datenum;         // Lower Resolution Time output - datenum or array 
    double subsec;        // Higher Res Time Output - usec of year or subsec
    //added in v2:
    OutputTime_t moduleTime;
    OutputTime_t gpi0Time;
    OutputTime_t gpi1Time;
} IO821_data_T;


#ifdef __cplusplus
extern "C" {
#endif

int IO821_mdlStart_init(void* bar, IO821_data_T* pData, IO821_config_T* pCfg);
int IO821_mdlStart_start(void* bar);
int IO821_mdlOutputs(void* bar);
int IO821_mdlTerminate_init(void* bar);
int IO821_mdlTerminate_end(void* bar);
int IO821_intStart_init(void* bar);
int IO821_intStart_start(void* bar);
int IO821_intPreHook(void* bar);
int IO821_intStop_init(void* bar);
int IO821_intStop_end(void* bar);
int IO821_readInterrupt();

#ifdef __cplusplus
}
#endif

#endif
