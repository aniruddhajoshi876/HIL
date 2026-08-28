# CarMaker CAN / RBS setup — MFE HIL bench

## Bus topology — two independent buses

The IO614's connectors A and B are **not bridged**. They are two separate CAN
buses and the Speedgoat is the only node on both:

- **Channel 1 / connector B — CarMaker bus.** CarMaker's PCAN-USB FD ⇄
  Speedgoat only. CarMaker transmits `0x500` (pedal demand); the Speedgoat
  transmits `0x501` (four inverter torque setpoints) and `0x502` (four ready
  bits). CarMaker never sees the raw VC control or inverter-status frames — the
  Speedgoat interprets them and republishes what CarMaker needs.
- **Channel 2 / connector A — VC bus.** The real MFE26-VC ⇄ Speedgoat only.
  VC control `0x186/0x196/0x1A6/0x1B6`; Speedgoat status `0x383…0x400` and
  sensor `0x032/0x034/0x076/0x2B0/0x7C0`.

Each bus needs its own pair of 120 Ω terminators (see `PINOUTS.md` section 5.2).

## Verified physical baseline (single-bus era — superseded)

**Historical.** Before the split, a 4-second, 1-Mbaud capture on connector B
(then bridged to the VC bus) contained 9,561 frames: status IDs `0x383`,
`0x385`, `0x393`, `0x395`, `0x3A3`, `0x3A5`, `0x3B3`, `0x3B5`, `0x400` at about
207 Hz (5 ms), plus `0x032`, `0x034`, `0x2B0`, with `0x2B0` at about 105 Hz
(10 ms).  Receiver status was No Error and payloads decoded sensibly.  On the
split bench that traffic is on channel 2 (connector A); channel 1 carries only
`0x500/0x501/0x502`.

**Confirmed.** The CarMaker host has one usable `PCAN_USBBUS1`: PEAK PCAN-USB
FD, USB `VID_0C72 PID_0012`, PnP status OK, and
`C:\Windows\System32\PCANBasic.dll` version 4.9.0.942.  CarMaker 12.0.1
declares `pcan_usb = 5` and PCANIO classic/FD APIs in `pcanio.h`; PCANIO
symbols are linked in `libcarmaker.a`.  Local source:
`C:\IPG\carmaker\win64-12.0.1\include\pcanio.h:31-70`.

**Open question.** Speedgoat persistently reported `busLoad=88`, `txOverrun=1`,
and `busWarning=1` on the pre-split bridged bus, even after application restart,
while measured traffic was only about 2,390 frames/s of approximately 120-us
frames (about 29% utilisation).  This is not fixed and now applies to the
**channel-2 VC bus**, which carries essentially all of that traffic.  Inspect
termination first: the IO614 supplies none and each bus requires exactly two
120-ohm terminators across pins 2 and 7.  The model now has a separate
`IO614 CarMaker CAN Diagnostics` block on channel 1, so the two buses'
bus-load/overrun/bus-off signatures can be read independently in the operator
GUI.  Local source: `PINOUTS.md:section 5.2`.

## RBS configuration

**Confirmed.** RBS supports cyclic CAN frames/PDUs; its frame timing derives
from the smallest assigned cyclic PDU time.  Use the already-settled DBC
`CarMakerPedalDemand` as standard ID `0x500`, DLC 8, 10 ms.  Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:97-110`.  Manual citation:
CarMaker/HIL User's Guide 12.0.1, section 4.9, pp. 73-75.

**Proposed design not built.** In the Rest Bus Configurator import
`carmaker/config/MFE26_Inverter_CarMaker.dbc` on the **CarMaker bus (channel 1)
only**; set `SpeedgoatHIL` as a real ECU and `CarMaker` as simulated.  After the
bus split CarMaker's only frames are `0x500` (transmit — pedal demand) and
`0x501`/`0x502` (receive — the Speedgoat's interpreted per-inverter torque
setpoints and ready bits).  The raw VC control and inverter-status frames are on
channel 2 and are not visible to CarMaker.  Map `DM.Gas` and `DM.Brake` to the
`0x500` percent signals using factor 100 and offset 0.  Map `Active` as the
explicitly armed command; reserved fields must remain zero.  Map `0x501`'s four
`InverterNTorqueSetpointNm` and `0x502`'s four ready bits into the vehicle
dynamics inputs.

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
