/*
 *  j1939lib.h
 *
 *  J1939 Tx, RX, Protocol Stack Interface functions.
 *
 * 
 *   Copyright 2009 The MathWorks, Inc.
 *
 */


#ifndef J1939_API_H
#define J1939_API_H


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "tmwtypes.h"
#include "wqutil.h"

#include "xpcimports.h"


/********************/
//#define DEBUG_J1939
/********************/



#ifdef __cplusplus
extern "C" {
#endif 


/***** Preprocessor Definitions *****/


#define GET_NODE_ADDRESS(s,n)				(n>255 ? s->CATable.Entries[n-256]->NodeAddress : n)

#define GET_ELAPSED_TIME_NS(t1, t2)			((t2.U64.NanoSecondsHi - t1.U64.NanoSecondsHi)*(2^32) + (t2.U64.NanoSecondsLo - t1.U64.NanoSecondsLo))


#define LOCK_PGN_ENTRY(a,b)					LockPGNEntry(a,b)
#define UNLOCK_PGN_ENTRY(a,b)				UnlockPGNEntry(a,b)
#define CHECK_PGN_LOCK(a,b)					(a->EnterCS[b])

#define CA_NULL_ADDRESS						254
#define CA_FREE_SLOT                        0xFF

#define MAX_NUM_TX_FRAGMENTS_PER_CTS		16
#define MAX_NUM_RX_FRAGMENTS_PER_CTS		16


#ifdef DEBUG_J1939  
#define SAVEF 	{fclose(gf);fopen("c:\\log.txt","a+");}
#define LOADF    {if(gf==NULL) gf=fopen("c:\\log.txt","w");}
#endif



/*Type Definitions*/


typedef enum
{
    J1939_ERROR_OK = 0,
    J1939_ERROR_INVALID_PARAM,
    J1939_ERROR_MAX_NUM_STACK_EXEEDED,
    J1939_ERROR_MEM_ALLOCATION_ERROR,
    J1939_ERROR_PGN_ALREADY_IN_QUEUE,
    J1939_ERROR_PGN_TABLE_FULL,
    J1939_ERROR_INVALID_CA,
    J1939_ERROR_INVALID_STACK,
    J1939_ERROR_TP_NOT_ENABLED,
    J1939_ERROR_MAXNUM_CA_EXCEEDED,
    J1939_ERROR_INVALID_PGNENTRY,
    J1939_ERROR_SESSION_BUSY,
	J1939_ERROR_DUPLICATE_NODE_ADDRESS,
	J1939_ERROR_MAX_TP_SESSIONS_EXCEEDED,
    J1939_ERROR_WQ,
	J1939_ERROR_CTL,
	J1939_ERROR_ZERO_NODE,
	J1939_ERROR_CA_NOT_FOUND,
	J1939_ERROR_INVALID_NADDR

}j1939Error;


typedef enum{
   LARGE_DATA=0,
   SMALL_DATA
}MESSAGE_TYPE;

typedef enum{
   J1939_APP_TASK =0,
   J1939_PSTACK_TASK
}TASK_TYPE;


typedef enum{
    RX_PGN = 0,
    TX_PGN
}IOType;

typedef enum
{
    BOTH_SPECIFIC_AND_GLOBAL=1,
	GLOBAL_ONLY,
    SPECIFIC_ONLY,
}DESTINATION_TYPE;



typedef union{
    struct{
        uint32_T IdentityNumber:21;
        uint32_T ManufacturerCode:11;
        uint32_T ECUInstance:3;
        uint32_T FunctionInstance:5;
        uint32_T Function:8;
        uint32_T Reserved:1;
        uint32_T VehicleSystem:7;
        uint32_T VehicleSystemInstance:4;
        uint32_T IndustryGroup:3;
        uint32_T ArbitraryAddressCapable:1;
    }fields;
    uint8_T bytes[8];
}CA_NAME_TYPE;

typedef struct{
    xpcTime StartTime;  /*<  Time at the beginning of a wait*/
    uint32_T Duration;   /*<  Duration in milliseconds*/
}TIMER_ENTRY_TYPE;



typedef struct{
	uint8_T			        Active;
	uint8_T                 NodeAddress;
	uint16_T				padding;
	CA_NAME_TYPE            NAME;	
	int32_T					ID;	
	#ifdef DEBUG_J1939
	int32_T					SID;
	#endif
	struct{
		int16_T				RxCount;	
		int16_T				TxCount;
	}TPStatus;
    uint32_T	            ActionState;
    uint32_T                ClaimCount;
    TIMER_ENTRY_TYPE        Timer;
}CaEntry_T;


struct PGN_ENTRY
{
   #ifdef DEBUG_J1939
   int32_T SID;
   #endif
   CaEntry_T* CA;
    union
    {
        uint32_T value;
        struct
        {
            uint8_T byte0;
            uint8_T byte1;
            uint8_T byte2;
            uint8_T dummy;
        }bytes;
    }PGN;
	uint8_T Priority;
    uint16_T DataLength;
    uint8_T DestinationType;
    uint8_T SourceAddress;
    uint8_T TargetAddress;
    uint32_T UpdateRate;  //unused
    uint8_T *DataBufferPtr;
    uint16_T NewMessage;
    uint8_T EnterCS[2];  //0 is the Send/receive block, 1 is the protocol stack
    uint8_T CSTurn;
	uint8_T InQueue;
    struct PGN_ENTRY* NextPtr;
	struct PGN_ENTRY* NextDuplicatePtr;
};

typedef struct PGN_ENTRY PgnEntry_T;

/*************  Transport Protocol  ***************/



struct TP_SESSION{
    uint8_T Active;
    uint8_T ActionState;
	uint16_T DataLength;
    uint8_T NumOfFragments;
	uint8_T NextFragment;
	uint8_T FragmentCounter;
	uint8_T FragmentLimit;
	uint8_T NodeAddress;
	uint8_T PeerNodeAddress;
    PgnEntry_T *PGNEntryPtr;
    TIMER_ENTRY_TYPE Timer;
    struct TP_SESSION *NextSessionPtr;
};

typedef struct TP_SESSION TP_Session_T;


typedef int32_T (*CAN_SEND_FUNC_TYPE)(void*);

typedef int32_T (*CAN_RECEIVE_FUNC_TYPE)(void*);


typedef struct{
	TP_Session_T**  SessionWithAddress;  /*< Array of indices that maps to sessions */
 }TP_ADDRESS_SESSION_MAP;		 /*< Indexing Maps to Local Node Table  */


/*! Protocol Stack Information Block */

typedef struct 
{
   /*General*/
   uint8_T					 Init;
   uint8_T 			         TP_Enabled;
   uint8_T					 AddressClaimEnabled;
   uint8_T   			 	 TP_MaxNumOfTx;
   uint8_T 	   			 	 TP_MaxNumOfRx;  

   #ifdef DEBUG_J1939
   int32_T					Id;
   #endif

   struct{
	   uint8_T					 NumEntries;
	   CaEntry_T*				 Entries;
   }LocalNodeTable;

   /*Non-TP Communication*/

	struct{
		 uint16_T				 NumEntries;
		 PgnEntry_T**			 Entries;
	}RxPGNTable;

	struct{
		 uint16_T                NumEntries;
		 PgnEntry_T**			 Entries;
	}TxPGNTable;
 
   /*Transport Protocol*/

   struct{
	   TP_Session_T*			Entries;
	   TP_Session_T*			NextFreeEntry;
   }TP_SessionTable;


   WORKQUEUE				TxPGNQueue;
   WORKQUEUE				TP_SessionQueue;
   WORKQUEUE				AddressClaimQueue;

   /*!Lookup Table*/
   struct{

	   struct {
		 TP_ADDRESS_SESSION_MAP* ToNode;       
		 TP_ADDRESS_SESSION_MAP  ToAll;
	   }Rx;

	   struct {
		 TP_ADDRESS_SESSION_MAP* FromNode;   
	   }Tx;


   }TP_SessionLookupTable;

   uint8_T					 NodeLookupTable[256];

}PStackInfo_T;


/********* Global Variables ********/

extern FILE* gf;
extern PStackInfo_T g_j1939StackInfos[];




/******* Function Declarations *******/

PgnEntry_T* GetPGNEntryPtr(PStackInfo_T* stack_info, uint32_T pgn, IOType io, int *numOfEntries);

uint8_T     LockPGNEntry(PgnEntry_T*, TASK_TYPE originator);

void        UnlockPGNEntry(PgnEntry_T*, TASK_TYPE originator);

uint8_T     GetNextAvailableAddress(PStackInfo_T* stack_info, uint8_T node_address);

/* API */

/*Registers a Controller Application for a particular Protocol Stack*/
CaEntry_T*  j1939RegisterCA(int32_T stack_id, int32_T ca_id, uint8_T node_addr, CA_NAME_TYPE ca_name, j1939Error* error);

/*Registers a PGN Entry for a particular Protocol Stack*/
PgnEntry_T* j1939RegisterPGN(int32_T stack_id, int32_T ca_id, uint8_T priority, uint32_T pgn,  IOType direction, uint32_T DataLength, int32_T UpdateRate, uint8_T SourceAddress, uint8_T TargetAddress,  j1939Error* error);

/*Sends J1939 Message */
j1939Error  j1939SendMessage(int32_T stack_id,PgnEntry_T *pgn_entry_ptr);

/*Updates Node Address - Reclaim if necessary*/
j1939Error j1939UpdateNodeAddress(int32_T stack_id, CaEntry_T* ca_entry_ptr, uint8_T node_address);

/*Destroys PGN Tables*/
void		j1939DestroyRxPGNTable(int32_T stack_id);

void		j1939DestroyTxPGNTable(int32_T stack_id);

void DestroyPGNEntry(PgnEntry_T* pgn_entry_ptr);

j1939Error j1939DestroyStack(int32_T stack_id);

/*Initializes a Protocol Stack Instance fro a given ID*/
j1939Error  j1939InitializeStack(int32_T stack_id,
							 uint8_T tp_enabled,
							 uint8_T ac_enabled,
                             int32_T num_rx_pgn,
                             int32_T num_tx_pgn,
							 uint8_T num_nodes,
							 int32_T max_sessions);



#ifdef __cplusplus
}
#endif 

#endif

