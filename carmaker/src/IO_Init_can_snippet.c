/*
 * Proposed design not built: transplant this helper into the separate
 * IPG-MFE FCM_Projects/FS_race/src/IO.c.  It is intentionally not compiled
 * from this repository.
 *
 * Local source: C:\IPG\carmaker\win64-12.0.1\include\pcanio.h:31-70.
 */
#include <CarMaker.h>
#include <pcanio.h>

#define MFE_PCAN_DEVICE       pcan_usb
#define MFE_PCAN_CHANNEL      1       /* PCAN_USBBUS1; the only installed bus */
#define MFE_PCAN_BITRATE      1000000

static int
MFE_PCAN_Init (void)
{
    char status_text[256] = { 0 };
    unsigned int status;

    if (PCANIO_Init() != 0) {
        LogErrF(EC_Init, "PCANIO_Init failed");
        return -1;
    }

    /* Classic CAN: nominal/data timing structures are unused and must be NULL. */
    if (PCANIO_SetCommParam(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL,
                            MFE_PCAN_BITRATE, 0, NULL, NULL) != 0) {
        LogErrF(EC_Init, "PCAN-USB FD channel %d: 1 Mbit/s classic-CAN setup failed",
                MFE_PCAN_CHANNEL);
        PCANIO_Terminate();
        return -1;
    }

    status = PCANIO_GetStatus(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, status_text);
    if (status != 0) {
        LogErrF(EC_Init, "PCAN-USB FD channel %d status 0x%x: %s",
                MFE_PCAN_CHANNEL, status, status_text);
        PCANIO_CloseComm(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL);
        PCANIO_Terminate();
        return -1;
    }

    Log("PCAN-USB FD channel %d initialized: 1 Mbit/s classic CAN (%s)\n",
        MFE_PCAN_CHANNEL, status_text);
    return 0;
}

/*
 * Apply-note:
 * 1. In IPG-MFE's IO.c, add #include <pcanio.h> after <CarMaker.h>.
 * 2. Place MFE_PCAN_Init() above IO_Init().
 * 3. In IO_Init(), after the IO_None early return and before the final return,
 *    call `if (MFE_PCAN_Init() < 0) { IO_SelectNone(); return -1; }`.
 * 4. In IO_Cleanup(), call PCANIO_CloseComm(MFE_PCAN_DEVICE,
 *    MFE_PCAN_CHANNEL) followed by PCANIO_Terminate().
 * 5. Wire RBS/the application send-receive path to this opened channel; this
 *    helper alone does not register an RBS interface or transmit 0x500.
 *
 * Confirmed: the PCANIO API and pcan_usb=5 are declared by pcanio.h.
 * Open question: channel value 1 is grounded by the installed adapter's sole
 * PCAN_USBBUS1 identity, but must be verified by a live status/read test
 * before it is relied upon for RBS traffic.
 */
