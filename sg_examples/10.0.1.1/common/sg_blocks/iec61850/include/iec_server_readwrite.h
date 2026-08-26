#ifndef __IEC_SERVER_READWRITE_H
#define __IEC_SERVER_READWRITE_H

#include "stdint.h"
#include "iec_def.h"
#include "iec_node.h"
#include <map>
#include <list>
#include "iec61850_server.h"
#include "hal_thread.h"
#include <vector>
#include "sg_printf.h"


namespace iec61850
{
class cServerReadWrite
{
    private:

    public:

        bool IsFaulty = false;
        uint32_t State = 0;

		uint32_t DataType = 0;

        uint16_t ReadWriteID = 0;
        uint64_t timestamp = 0;
        uint32_t PollingInterval = 0;
        uint32_t Timeout = 0;
        bool dataInit=false;

        void log(Severity l, const char *m, ...);
        int32_t process();
        int32_t init(uint16_t ReadDim, uint16_t WriteDim, uint16_t TimeDim, uint16_t ControlDim, int type);
        int32_t start();
        int32_t read(void *Destination);
        int32_t write(void *Source);
		int32_t terminate();

		void processInputPort(uint32_t PortIndex, void* PortAddress);
		void updateOutputPort(uint32_t PortIndex, void* PortAddress);

        void *DataAddress_IN = NULL;
        void *DataAddress_OUT = NULL;
        uint16_t ReadDim = 0;
        uint16_t WriteDim = 0;
        uint16_t TimeDim = 0;
        uint16_t ControlDim = 0;

        std::vector<std::string> stWriteVect;
        std::vector<DataAttribute> DAWrite;
		std::vector<FunctionalConstraint> fcWriteVect;
		std::vector<std::string> stReadVect;
        std::vector<DataAttribute> DARead;
        std::vector<FunctionalConstraint> fcReadVect;
		std::vector<std::string> stTimeVect;
        std::vector<DataAttribute> DATime;
        std::vector<FunctionalConstraint> fcTimeVect;
		std::vector<std::string> stControlVect;
        std::vector<DataObject> DAControl;
        std::vector<FunctionalConstraint> fcControlVect;

        uint8_t stringReadVect[IEC_MAX_STRING_SIZE] = {32};
        uint8_t stringWriteVect[IEC_MAX_STRING_SIZE] = {32};

		std::string remFcConstraint(std::string MyString, std::vector<FunctionalConstraint>& tVect);

        //TODO: einlesen: buffer[] with bytecount+malloc -> semafore&mutex (handshake/counter) atomic calls

        void *Node;

        cServerReadWrite(uint16_t ID);
        virtual ~cServerReadWrite();

        uint32_t getTime(void);
};
}

#endif
