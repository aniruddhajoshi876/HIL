#include "sg_blocks/timing/lib/sg_IO821/include/IO821.h"
#include "sg_blocks/common/libsg/sg_common.h"

// sg_interrupt_config.h automatically prepares everything (the public interrupt functions, etc.)
// SG_INT_PREFIX needs to match the prefix that was defined in sg.db.getInterrupts.m
static const int SG_INT_BARS[] = {0};
#define SG_INT_PREFIX IO821
#include "sg_interrupt_config.h"

SG_INT_START_FUNC
{
	void* bar = (void*)SG_INT_MAPPED_BAR(0);
	
    IO821_intStart_start(bar);

    return;
}

SG_INT_ISR_FUNC
{
	int rc;
	void* bar = (void*)SG_INT_MAPPED_BAR(0);
	
	rc = IO821_intPreHook(bar); // returns SG_RUN_ISR (1) or SG_DROP_ISR (0)
    return rc;
}

SG_INT_STOP_FUNC
{
	void* bar = (void*)SG_INT_MAPPED_BAR(0);
	
    IO821_intStop_end(bar);
    
    return;
}
