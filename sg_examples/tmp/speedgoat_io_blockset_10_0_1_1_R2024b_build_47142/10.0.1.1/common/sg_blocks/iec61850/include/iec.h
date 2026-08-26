#ifndef __IEC_H
#define __IEC_H

#include <iec_sv_root.h>
#include <iec_goose_root.h>
#include "iec_root.h"

namespace iec61850
{
    /* Global MB root node */
    extern cRoot Root;
    extern cGooseRoot GooseRoot;
    extern cSVRoot SVRoot;

    extern char *mystrrev(char *str);
    extern std::vector<std::vector<std::string>> getEthTranslations(void);
    extern std::string getEthInterfaceNameFromLabel(std::string EthLabel);
    extern uint32_t getDataTypeLength(uint32_t DataType);
    extern void *AllocateMemory(size_t s);
    extern std::vector<std::string> extractDataItemPaths(char *ObjectPathList);
    extern uint64_t getMilliCounter(void);
    extern uint64_t getMicroCounter(void);

    void makeMacArrayFromUint64(uint64_t Mac, uint8_t MacArray[6]);
    std::string makeMacStringFromUint64(uint64_t Mac);
    std::vector<uint8_t> makeMacVectorFromUint64(uint64_t Mac);

    std::string removeFc(std::string s, int32_t *fc);
}

#endif
