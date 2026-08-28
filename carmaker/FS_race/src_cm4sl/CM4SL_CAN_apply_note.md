# CarMaker CAN apply note

Copy `IO.c` and `User.c` back over
`IPG-MFE/FCM_Projects/FS_race/src_cm4sl/{IO.c,User.c}`, then rebuild with the
CarMaker for Simulink solution file or the `src_cm4sl` Makefile in MATLAB
R2022a. Do not use the MATLAB R2024b environment used for `inverter_hil`.

`User.h` is unchanged — the `MFE_CAN*` globals are defined in `IO.c` and
re-declared `extern` locally in `User.c`, matching the existing pedal/torque
quantities.

## Contents

- **`0x500` / `0x501` / `0x502`** — CarMaker pedal demand out, per-inverter
  torque setpoints and ready bits in. Original channel-1 link.
- **`0x503`-`0x506`** — CarMaker vehicle-physics truth out (acceleration,
  angular rate, velocity, Euler), added so the Speedgoat can pack the MTi
  frames from CarMaker instead of its kinematic estimate. `IO_Out()` sends
  the four frames every 10-ms cycle right after `0x500`, sharing one
  modulo-256 counter, CRC-8/SAE-J1850 over bytes 0-6. The values come from
  the `MFE_CAN.Physics.*` dictionary quantities, which `TorqueVect.mdl` must
  populate — see `VC_HIL/docs/carmaker_readcmdict_checklist.md` for the
  Read/Write CM Dict wiring to add before rebuilding.

## Known unresolved

`GetCRC_J1850_User()` (used by both the `0x500` and the `0x503`-`0x506`
paths) has no definition in these files or the CarMaker 12.0.1 headers. If
the `0x500` frame currently links and transmits a correct CRC, the physics
frames inherit that. If it does not, that is a pre-existing gap in the
`0x500` work, not introduced here — resolve it once for both.
