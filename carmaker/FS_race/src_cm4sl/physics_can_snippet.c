/*
 * READY-TO-APPLY CM4SL SOURCE SNIPPET -- NOT COMPILED HERE.
 * Apply these additions into
 * IPG-MFE/FCM_Projects/FS_race/src_cm4sl/{IO.c,User.c,User.h}, then rebuild
 * CM4SL in MATLAB R2022a per CM4SL_CAN_apply_note.md.
 */

/* User.h: declarations shared by the generated model and host C. */
extern double MFE_CAN_PhysicsAcceleration[3];
extern double MFE_CAN_PhysicsAngularRate[3];
extern double MFE_CAN_PhysicsVelocity[3];
extern double MFE_CAN_PhysicsEuler[3];

/* User.c: definitions near the existing MFE_CAN quantities. */
double MFE_CAN_PhysicsAcceleration[3];
double MFE_CAN_PhysicsAngularRate[3];
double MFE_CAN_PhysicsVelocity[3];
double MFE_CAN_PhysicsEuler[3];

/* User_DeclQuants(): quantities written by TorqueVect.mdl Read CM Dict wiring. */
for (i=0; i<3; ++i) {
    static const char *Axis[3] = {"x", "y", "z"};
    char sbuf[64];
    sprintf(sbuf, "MFE_CAN.Physics.Acceleration.%s", Axis[i]);
    DDefDouble(NULL, sbuf, "m/s2", &MFE_CAN_PhysicsAcceleration[i], DVA_IO_Out);
    sprintf(sbuf, "MFE_CAN.Physics.AngularRate.%s", Axis[i]);
    DDefDouble(NULL, sbuf, "rad/s", &MFE_CAN_PhysicsAngularRate[i], DVA_IO_Out);
    sprintf(sbuf, "MFE_CAN.Physics.Velocity.%s", Axis[i]);
    DDefDouble(NULL, sbuf, "m/s", &MFE_CAN_PhysicsVelocity[i], DVA_IO_Out);
    sprintf(sbuf, "MFE_CAN.Physics.Euler.%s", Axis[i]);
    DDefDouble(NULL, sbuf, "rad", &MFE_CAN_PhysicsEuler[i], DVA_IO_Out);
}

/* IO.c: file-scope state and helpers. GetCRC_J1850_User is the exact helper
 * already used by the 0x500 path (poly 0x1D, init/xorout 0xFF).
 */
static unsigned char MFE_PCAN_PhysicsGroupCounter;

static short
MFE_PhysicsRoundSaturate(double value, double scale)
{
    double counts = value / scale;
    if (counts > 32767.0) counts = 32767.0;
    if (counts < -32768.0) counts = -32768.0;
    return (short)(counts >= 0.0 ? counts + 0.5 : counts - 0.5);
}

static void
MFE_SendPhysicsFrame(unsigned id, const double value[3], double scale,
                     unsigned char counter)
{
    CAN_Msg Msg;
    int i;
    memset(&Msg, 0, sizeof(Msg));
    Msg.MsgId = id;
    Msg.FrameFmt = 0;
    Msg.RTR = 0;
    Msg.FrameLen = 8;
    for (i=0; i<3; ++i) {
        unsigned short raw = (unsigned short)MFE_PhysicsRoundSaturate(value[i], scale);
        Msg.Data[2*i] = raw & 0xff;
        Msg.Data[2*i+1] = (raw >> 8) & 0xff;
    }
    Msg.Data[6] = counter;
    Msg.Data[7] = GetCRC_J1850_User(Msg.Data, 7, 0xff, 0xff);
    if (PCANIO_Send(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, &Msg) != 0)
        LogErrF(EC_General, "PCAN-USB FD channel %d: physics CAN 0x%03x send failed",
                MFE_PCAN_CHANNEL, id);
}

/* IO_Out(): insert immediately after the existing cyclic 0x500 send. The
 * four consecutive frames use one counter sampled for this 10-ms group.
 */
MFE_SendPhysicsFrame(0x503, MFE_CAN_PhysicsAcceleration, 0.01,
                     MFE_PCAN_PhysicsGroupCounter);
MFE_SendPhysicsFrame(0x504, MFE_CAN_PhysicsAngularRate, 0.002,
                     MFE_PCAN_PhysicsGroupCounter);
MFE_SendPhysicsFrame(0x505, MFE_CAN_PhysicsVelocity, 0.01,
                     MFE_PCAN_PhysicsGroupCounter);
MFE_SendPhysicsFrame(0x506, MFE_CAN_PhysicsEuler, 0.0001,
                     MFE_PCAN_PhysicsGroupCounter);
MFE_PCAN_PhysicsGroupCounter = (unsigned char)(MFE_PCAN_PhysicsGroupCounter + 1U);
