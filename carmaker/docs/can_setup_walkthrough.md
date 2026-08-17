# CarMaker CAN / RBS setup — MFE HIL bench

## Verified physical baseline

**Confirmed.** Connect the PCAN-USB FD to IO614 connector **B**, which is CAN
channel 1; connector A is channel 2.  The lettering does not follow channel
order.  A 4-second, 1-Mbaud capture on connector B contained 9,561 frames:
status IDs `0x383`, `0x385`, `0x393`, `0x395`, `0x3A3`, `0x3A5`, `0x3B3`,
`0x3B5`, `0x400` at about 207 Hz (5 ms), plus `0x032`, `0x034`, `0x2B0`, with
`0x2B0` at about 105 Hz (10 ms).  Receiver status was No Error and payloads
decoded sensibly.  This is the healthy passive-reception baseline.

**Confirmed.** The CarMaker host has one usable `PCAN_USBBUS1`: PEAK PCAN-USB
FD, USB `VID_0C72 PID_0012`, PnP status OK, and
`C:\Windows\System32\PCANBasic.dll` version 4.9.0.942.  CarMaker 12.0.1
declares `pcan_usb = 5` and PCANIO classic/FD APIs in `pcanio.h`; PCANIO
symbols are linked in `libcarmaker.a`.  Local source:
`C:\IPG\carmaker\win64-12.0.1\include\pcanio.h:31-70`.

**Open question.** Speedgoat persistently reports `busLoad=88`, `txOverrun=1`,
and `busWarning=1`, even after application restart, while measured traffic is
only about 2,390 frames/s of approximately 120-us frames (about 29% utilisation).
This is not fixed.  Inspect termination first: the IO614 supplies none and the
bus requires exactly two 120-ohm terminators across pins 2 and 7.  Local source:
`PINOUTS.md:section 5.2`.

## RBS configuration

**Confirmed.** RBS supports cyclic CAN frames/PDUs; its frame timing derives
from the smallest assigned cyclic PDU time.  Use the already-settled DBC
`CarMakerPedalDemand` as standard ID `0x500`, DLC 8, 10 ms.  Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:97-110`.  Manual citation:
CarMaker/HIL User's Guide 12.0.1, section 4.9, pp. 73-75.

**Proposed design not built.** In the Rest Bus Configurator import
`carmaker/config/MFE26_Inverter_CarMaker.dbc`; set `VC` and `SpeedgoatHIL` as
real ECUs and `CarMaker` as simulated.  Receive the observed inverter/sensor
IDs only; only CarMaker transmits `0x500`.  Map `DM.Gas` and `DM.Brake` to the
percent signals using factor 100 and offset 0.  Map `Active` as the explicitly
armed command; reserved fields must remain zero.

**Confirmed.** Native RBS mapping supports `CRC J1850 [Start Count]` and
`RollCnt Std [Min Max Incr]`.  Configure `Integrity` as `CRC J1850 1 5` only
after confirming the GUI/generated mapping uses the manual's byte numbering
(the contract calls its first data byte “byte 1”); configure `AliveCounter` as
`RollCnt Std 0 15 1`.  Manual citation: CarMaker Programmer's Guide 12.0.1,
section 17.6, pp. 900-901.

**Open question.** The documented CANIf file supports only M51, M410, and
vCAN, not PCAN-USB.  Do not invent `CAN.<n>` syntax for PCAN.  The physical
PCAN setup is the reviewed `PCANIO_*` helper in
`carmaker/src/IO_Init_can_snippet.c`; validate how a GUI-created RBS interface
binds to it before treating RBS traffic as available.  Manual citation:
CarMaker Programmer's Guide 12.0.1, section 15.1, pp. 686-690.

## CRC and C-code fallback

**Confirmed.** SAE J1850 is native, and is the same named algorithm required
by the contract (poly `0x1D`, init `0xFF`, non-reflected, xorout `0xFF`; five
zero bytes produce `0x10`).  Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:105-110`; read-only authority:
`SG-CAN:inverter_hil/docs/can_pedal_demand_frame_spec.md:authoritative wire contract`.

**Proposed design not built.** Prefer native `CRC J1850 1 5`; do not change
the integrity algorithm.  If the generated result fails the zero-byte vector,
use a registered `RBS_Register_MapFunc()` CRC hook and map it with `CRCFunc`.
RBS calls such a Tx CRC hook after signals are encoded and permits it to write
the payload/signal.  Manual citation: CarMaker Programmer's Guide 12.0.1,
section 17.6, pp. 901, 905; local source:
`C:\IPG\carmaker\win64-12.0.1\include\rbs.h:42-63,678-685`.

## ScriptControl result

**Open question.** No documented `RBS::`, `CANIf::`, or Rest Bus Configurator
ScriptControl namespace/command was found in the installed GUI Tcl files or the
Programmer's Guide ScriptControl command reference.  ScriptControl can modify
and flush InfoFile keys, but that is not an RBS configuration API.  Keep the
documented GUI path and archive the generated files.  Manual citation:
CarMaker Programmer's Guide 12.0.1, section 24.4.5, pp. 1164-1167.

## IPG-MFE handoff — model change only in supported tooling

**Proposed design not built.** Replace the two `Read CM Dict` inputs named
`TorqueVect.XcpTorqueRequestNm` and `TorqueVect.XcpTorqueActive` with RBS
receive quantities for **each motor**, not a fabricated aggregate:
`CAN.SpeedgoatHIL.Inverter{1,2,3,4}StatusA.TorqueSetpoint` (N.m) and
`CAN.SpeedgoatHIL.Inverter{1,2,3,4}StatusA.InverterReady` (boolean).  The
first replaces the corresponding per-motor torque request; the second gates it
only as an inverter-ready indication.  Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:49-80`; read-only observation:
`C:\Users\MFE-HPC\Documents\GitHub\IPG-MFE\FCM_Projects\FS_race\src_cm4sl\TorqueVect.mdl:120291-120555`.

**Open question.** The exact RBS Data Dictionary prefix/name must be read from
the GUI-generated configuration: defaults include prefix `CAN` and ECU names,
but the final mapping can change them.  The model owner must not hand-edit any
`.mdl`, `.slx`, `.sldd`, or `.mlapp`; make the block substitutions in the
supported model toolchain.
