# CM4SL CAN apply note

This directory holds the **canonical** CarMaker-for-Simulink integration
sources. The HIL repository is the source of truth; the local
`IPG-MFE/FCM_Projects/FS_race` project is only a build/deploy workspace.

**Do not edit these files inside the IPG-MFE project and expect them to
survive.** Edit them here, then deploy with
`carmaker/deploy/apply_cm4sl.ps1` (see `carmaker/docs/cm4sl_integration.md`).

## Canonical files

| File | Purpose |
|---|---|
| `IO.c` | PCANIO channel-1 traffic: `0x500` pedal demand out, `0x501`/`0x502` in, `0x503`-`0x506` CarMaker vehicle-physics out, and `0x507` CarMaker steering truth out. The truth frames are gated on the model-written validity quantities. |
| `User.c` | `User_DeclQuants()` — registers `MFE_CAN.*` dictionary quantities, including `MFE_CAN.Physics.{Acceleration,AngularRate,Velocity,Euler}.{x,y,z}`, `MFE_CAN.Physics.Valid`, `MFE_CAN.Steering.WheelAngleRad` and `MFE_CAN.Steering.Valid` (all `DVA_IO_Out`). `User_TestRun_Start_atBegin()` clears the two validity flags at the start of every TestRun. |
| `User.h` | Unchanged from IPG's baseline — the `MFE_CAN*` globals are defined in `IO.c` and re-declared `extern` in `User.c`. |
| `security_cookie_stub.c` | Provides `__security_cookie` for the MinGW-w64 link (IPG's prebuilt `libcarmaker4sl.a` references it; MinGW does not supply it). Originated in the IPG-MFE working tree during CM4SL link bring-up; imported here 2026-08-27. |
| `Makefile` | Adds `security_cookie_stub.cm4sl.o` to `OBJS`. Same origin as the stub. |
| `TorqueVect.mdl` | The CM4SL vehicle/controls model. See the reconciliation note in `carmaker/docs/cm4sl_integration.md` — the HIL and IPG copies have diverged and this file is **not** synced automatically. |

## Frames on channel 1

- `0x500` `CarMakerPedalDemand` — CarMaker → Speedgoat. Throttle/brake %, active,
  4-bit alive counter, CRC-8/SAE-J1850 over bytes 1-5.
- `0x501` / `0x502` — Speedgoat → CarMaker. Per-inverter torque setpoints and
  ready bits.
- `0x503`-`0x506` `CarMakerPhysics{Acceleration,AngularRate,Velocity,Euler}` —
  CarMaker → Speedgoat. Three little-endian `int16` at bytes 0/2/4, the shared
  modulo-256 truth-group counter at byte 6, CRC-8/SAE-J1850 over bytes 0-6 at
  byte 7. Sent every 10-ms cycle in `IO_Out()` right after `0x500`. Vehicle/Fr1
  frame, SI units — the Speedgoat applies the sensor mounting transform, not
  this side. Scales match `carmaker/config/MFE26_Inverter_CarMaker.dbc`
  (`0.01` / `0.002` / `0.01` / `0.0001`).

  The values come from the `MFE_CAN.Physics.*` dictionary quantities, which
  `TorqueVect.mdl` populates through the `MFE_CAN CarMaker Truth` subsystem —
  see `carmaker/docs/cm4sl_integration.md`.

- `0x507` `CarMakerSteeringTruth` — CarMaker → Speedgoat. Fanatec / driver
  steering-wheel angle, `int16` LE at `0.001` **rad**/bit in bytes 0-1; bytes
  2-5 reserved zero; **the same** modulo-256 truth-group counter as
  `0x503`-`0x506` at byte 6; CRC-8/SAE-J1850 over bytes 0-6 at byte 7. Sent in
  the same 10-ms cycle as the physics group, from the
  `MFE_CAN.Steering.WheelAngleRad` dictionary quantity that `TorqueVect.mdl`
  populates as a straight `Steer.WhlAng` passthrough — no unit conversion on
  this side. No angular-speed field: the Speedgoat derives Bosch `LWS_SPEED`
  from successive samples. The Speedgoat, not CarMaker, turns this into the
  Bosch LWS `0x2B0`. PROVISIONAL CAN ID. Full detail in
  `VC_HIL/docs/carmaker_fanatec_lws_steering.md`.

## The validity gate

`IO_Out()` transmits `0x503`-`0x507` **only** while the model-written
`MFE_CAN.Physics.Valid` / `MFE_CAN.Steering.Valid` quantities are non-zero.
Without the gate, a `TorqueVect.mdl` that has never been given the truth
passthroughs still yields a well-formed stream of CRC-valid, counter-advancing,
all-zero frames — downstream, indistinguishable from a stationary,
straight-ahead vehicle. `User_TestRun_Start_atBegin()` clears both flags so the
statement is per-TestRun rather than per-process, and `MFE_ReportTruthGate()`
logs suppression once per transition (via `Log`, not `LogErrF`: an unpopulated
model is an expected state, not an error, and a 100 Hz error stream would bury
the CarMaker log).

## CRC — resolved

`GetCRC_J1850_User()` is **not** a project function. It is declared in
`C:\IPG\carmaker\win64-12.0.1\include\E2E.h:210`:

```c
unsigned char GetCRC_J1850_User (unsigned char *Data, int nBytes,
                                 unsigned char StartVal, unsigned char XORVal);
```

and supplied at link time by `libcarmaker.a` / `librbsutil.a`. `IO.c` already
`#include <E2E.h>`. Both the `0x500` path and the `0x503`-`0x506` path call it
as `GetCRC_J1850_User(data, n, 0xff, 0xff)` (init `0xFF`, xorout `0xFF`,
poly `0x1D` — matches the Speedgoat decoder's `crc8` in
`VC_HIL/inverter/rxCAN/decodeCarMakerPhysicsFrame.m`). No local definition is
needed; do not add one.

## Build

Rebuild with `carmaker/deploy/apply_cm4sl.ps1 -Verify` after deploy, then the
`CarMaker for Simulink.sln` solution or the `Makefile` in **MATLAB R2022a**.
Do not use the R2024b environment used for `inverter_hil`.
