#ifndef __MBTCP_UNIT_H
#define __MBTCP_UNIT_H

#include "stdint.h"
#include "mb_def.h"
#include "mbtcp_node.h"
#include "mbtcp_server_block.h"

namespace modbusTCP
{
class cUnit
{
    private:



    public:
    
		bool InitDone = false;

        uint16_t ID = 0;
        uint32_t NumBlocks = 0;

        cServerBlock *Blocks[MB_MAX_NUM_BLOCKS];

        uint8_t *Coils = NULL;
        uint8_t *DiscreteInputs = NULL;
        uint16_t *HoldingRegisters = NULL;
        uint16_t *InputRegisters = NULL;

        uint16_t NumCoils = 0;
        uint16_t NumDiscreteInputs = 0;
        uint16_t NumHoldingRegisters = 0;
        uint16_t NumInputRegisters = 0;

        void log(Severity l, const char *m, ...);
        int32_t addBlock(uint8_t BlockType, cServerBlock **Block);
        int32_t process();
        int32_t init(uint16_t NumCoil, uint16_t NumDiscrete, uint16_t NumHolding, uint16_t NumInput);
        int32_t getDataAddress(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity, void **Address);

        void *Node;

        cUnit(uint16_t ID);
        ~cUnit();
};
    
}

#endif
