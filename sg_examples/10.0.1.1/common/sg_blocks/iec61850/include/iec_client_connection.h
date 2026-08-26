#ifndef __IEC_CLIENT_CONNECTION_H
#define __IEC_CLIENT_CONNECTION_H

#include "sg_printf.h"
#include "iec_client_transceiver.h"
#include "stdint.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <typeinfo>

namespace iec61850
{
class cClientConnection
{
    private:
	void saveDataModel(void);

    public:

        bool IsFaulty = false;
        uint32_t State = 0;

		uint16_t Transaction_ID = 0;

		void* Node;
		const bool IsClient = true;
		bool Next_TRX = false;
		bool pending = false;
        bool DataItemsAreReady = false;
    
        bool Stop = false;
        bool Saved = false;
        uint16_t ConnectionID = 0;
        uint16_t NumTransceivers = 0;
        uint32_t IpAddr = 0;
        uint16_t TcpPort = 0;
        uint32_t RemIpAddr = 0;
        uint16_t RemTcpPort = 102;
        uint32_t ResponseTimeout = 0;
        uint32_t ResponseIntervall = 0;
        uint64_t StartTime = 0;
        bool EnaReports = false;
        uint32_t NumBlocks = 0;
        uint64_t ReadVar_P = 0;
        uint32_t WriteVar_P = 0;
        bool WantAuthentication = 0;
		char* Enabler;
		uint16_t OSI_AE_Qualifier = 0;
		char* OSI_AP_Title = (char*)"1,3,9999,33";
        char Hostname[16] = "255.255.255.255";
        char RemoteHostname[16] = "255.255.255.255";
        size_t cntr = 0;

        std::vector<ControlObjectClient> ControlVect;
        IedClientError ClientError = IED_ERROR_OK;
        IedConnection CliCon = NULL;
        IsoConnectionParameters ConParam = NULL;
        IedConnectionState ClientState = IED_STATE_CLOSED;

        std::map <uint16_t, cClientTransceiver*> Transceivers;

        int32_t addTransceiver(cClientTransceiver **Transceiver);
        int32_t getTransceiver(uint16_t TransceiverID, cClientTransceiver **Transceiver);
        bool isTransceiver(uint16_t TransceiverID);

        void log(Severity l, const char *m, ...);
        int32_t start();
        int32_t process();
        int32_t terminate();
        int32_t init(uint32_t RemoteIpAddr, uint16_t RemoteTcpPort, bool EnaRequest, bool WantAuthentication, const char* Enabler, const char* AP_Title, uint16_t AE_Qualifier);
        int32_t requestConnection();
    	uint32_t pendingConnection(void);
        uint32_t getTime(void);

        bool areDataItemsReady();

        cClientConnection(uint16_t ConnectionID);
        ~cClientConnection();

};

    
}

#endif
