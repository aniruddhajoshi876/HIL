#include "[model].h"
#include "[model]_private.h"
#include "sg_printf.h"
#include "sg_early_init.h"
#include "simstruc.h" // This is required if there are no S-function blocks in the model

static RTWSfcnInfo sgEarlyInitSfcnInfo;
struct _ssBlkInfo2 sgEarlyInitBlkInfo2 = {.rtwSfcnInfo = &sgEarlyInitSfcnInfo};

void sg_init_sfcns(void)
{
    sg_printf(sg_debug, "Initializing [EARLY INIT] S-functions\n");
    //[INSERT INIT CODE HERE]
}

__attribute__((constructor)) void early_init_setup(void)
{
    sg_register_early_init_function(sg_init_sfcns);
}
