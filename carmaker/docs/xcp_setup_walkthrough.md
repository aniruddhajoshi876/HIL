# CarMaker XCP setup — manual walkthrough

This is the CarMaker-side GUI walkthrough referenced by
`virtual-vcu/docs/carmaker_speedgoat_interface.md` section 6. It is a
manual procedure, not an automated script: CarMaker's XCP Setup is
GUI-driven, and the project's `Data/Config/ECUParameters` (copied into this
repo at `carmaker/FS_race/Data/Config/ECUParameters`) contains no existing
`XCPParameters` entry to safely derive a scriptable equivalent from — see
the interface doc's "Items not confirmed locally" for why this wasn't
authored as a file edit instead.

Run this against the real `FS_race` project (`Documents\GitHub\IPG-MFE\FCM_Projects\FS_race`
on this machine), not the read-only copy under `carmaker/FS_race/` here — that
copy exists only so this repo has the reference vehicle/config data to build
and test the Speedgoat side against.

## Prerequisite: the A2L must exist first

CarMaker's XCP Setup is created by importing an A2L file. That A2L does not
exist yet — it is generated from a real `inverter_hil.slx` build on a machine
with the Speedgoat R2024B_SLX target library and Embedded Coder license,
using Simulink Real-Time's "Generate Calibration Files" tool (see the
interface doc section 7, "Build and generate the A2L"). This walkthrough
cannot be completed until that A2L is in hand.

## The signal contract this walkthrough assumes

Implemented on the Speedgoat side (this repo, `virtual-vcu`/`inverter_hil`,
commits `2e502ff`, `ca906c6`, and the XCP-tunable-parameters follow-up in
`build_inverter_hil_model.m`):

| Direction | A2L variable (name TBD from the actual generated A2L) | Maps to |
|---|---|---|
| CarMaker → Speedgoat (stimulation) | throttle demand, 0–100% | `hil_cmd_xcp_pedals_throttle` dictionary entry (distinct from the GUI-owned `hil_cmd_pedals_throttle`) |
| CarMaker → Speedgoat (stimulation) | brake demand, 0–100% | `hil_cmd_xcp_pedals_brake` dictionary entry (distinct from the GUI-owned `hil_cmd_pedals_brake`) |
| CarMaker → Speedgoat (stimulation) | source-select flag | `hil_cmd_xcp_pedals_active` (boolean) — set true once CarMaker is actively driving pedals; a Switch block in `build_inverter_hil_model.m` then routes the normalized (÷100) XCP values, instead of the GUI-owned entries, into `Pedal Voltage Calibration`. Default false, so an unwritten build behaves exactly as before this parameter existed. |
| Speedgoat → CarMaker (measurement) | decoded torque request (Nm) | `VirtualVcuTorqueRequestNm` global tag, `Virtual VCU Observability` subsystem port 9 |
| Speedgoat → CarMaker (measurement) | VCU state ID | `VirtualVcuStateId` global tag, `Virtual VCU Observability` port 2 |
| Speedgoat → CarMaker (measurement) | main/precharge/inverter-control enable | `VirtualVcuMainEnable`/`VirtualVcuPrechargeEnable`/`VirtualVcuInverterControlEnable`, ports 3–5 |
| Speedgoat → CarMaker (measurement) | APPS+brake fault | `VirtualVcuAppsBrakeFault`, port 8 |

`valid`/`appsPlausible`/`brakePlausible` and the CAN-decoded
`can.dcLink12V`/`dcLink34V`/`inverterReady`/`inverterFault` fields are **not**
yet wired to the deployed chart's outputs or the observability subsystem —
see the interface doc's open items. Do not reference A2L variables for these
until that follow-up work lands.

## Steps

1. **Confirm the A2L is current.** Re-generate it if the model has changed
   since the last build. Note the exact variable names it actually contains
   for the six rows above — they may not match the tag names listed, since
   Simulink Real-Time's calibration-file export may rename them.
2. **Open XCP Setup.** In the CarMaker GUI, use the XCP LED at the lower
   right of the main window, or the **Realtime System** menu. If
   `ECUParameters` has no `XCPParameters` entry (confirmed true for
   `FS_race` as of this writing), CarMaker raises XCP Setup automatically.
3. **Create the ECU.** Choose **New**, browse to the generated A2L, and give
   the ECU a distinct name (e.g. `SpeedgoatVirtualVCU`).
4. **Configure Ethernet transport.** In General/Transport Layer, choose
   Ethernet, and enter the Speedgoat target's IP and the XCP UDP port
   negotiated with whoever owns the Speedgoat build (neither is fixed yet —
   `TargetPC1` is `10.10.10.5` per `PINOUTS.md`, but that is the target's
   general identity, not a confirmed XCP port).
5. **Review protocol/DAQ settings** CarMaker derived from the A2L. Do not
   invent CAN identifiers or touch CarMaker's separate CAN transport pane —
   this integration is Ethernet-only.
6. **Save** under `Data/Config`, and select **Activate in ECUParameters**.
7. **Activate the ECU** in XCP Configuration (state: active).
8. **Select measurement variables via UAQs.** Move only the six rows above
   (or their actual A2L names) from Available to Selected. This is the
   documented no-code route that adds them to the Data Dictionary.
9. **Map each variable.** For each selected variable, assign it to a sample
   group/DAQ list, then use the Mapping tab's DDict field to map it — this
   is a separate manual step from selecting it as a UAQ; do not assume UAQ
   selection alone creates the mapping (unconfirmed either way locally,
   verify in the GUI).
10. **Map the three stimulation variables** to `hil_cmd_xcp_pedals_throttle`,
    `hil_cmd_xcp_pedals_brake`, and `hil_cmd_xcp_pedals_active` (same Mapping
    tab, STIM direction) — **not** the GUI-owned `hil_cmd_pedals_throttle`/
    `brake` entries, which stay reserved for the GUI. Set `active` true only
    once CarMaker is genuinely ready to drive both pedals continuously: the
    model-side Switch cuts the GUI out of the AO01–04 path the instant it
    sees `active` true, regardless of what the GUI itself is doing. This is
    the one step whose exact GUI behavior for a STIM-direction write the
    manual doesn't separately illustrate — confirm it writes through
    correctly on the bench before relying on it.
11. **Enable XCP acquisition** (XCP LED to orange, "XCP On") and start the
    TestRun. Watch for the LED turning dark green (acquiring) and check the
    UAQ values against the existing GUI's own live readout of the same
    signals as a cross-check.

## What this does not cover

- Creating/updating the A2L itself (Speedgoat-side, physical-target-dependent).
- Any physical network/cabling work between the CarMaker host and the
  Speedgoat target.
- **`hil_cmd_xcp_pedals_active` (model-side) and `XcpDriving` (GUI-side,
  `inverter_hil_app.m`) are two separate flags that are not wired together.**
  Once CarMaker sets `hil_cmd_xcp_pedals_active` true, the model-side Switch
  genuinely redirects AO01–04 to the XCP-sourced pedal values regardless of
  the GUI — that part is real and functional. But the GUI's own
  `XcpDriving` property (which gates whether the GUI's *own* pedal writes
  reach `Session.write`, and whether the sliders show as read-only) stays a
  permanent-false placeholder; it does not read `hil_cmd_xcp_pedals_active`
  back from the target. Consequence: while CarMaker drives, the GUI sliders
  will keep looking live and keep writing to `hil_cmd_pedals_throttle`/
  `brake` — harmlessly, since the model Switch has already cut those
  entries out of the AO01–04 path — but the GUI experience will be
  misleading (an operator could believe the slider is in control when it
  is not) and the audit log will keep recording GUI writes that have no
  physical effect. Closing this requires wiring `app.XcpDriving` to a live,
  per-poll `Backend.getparam('hil_cmd_xcp_pedals_active')` read (the
  existing `TargetValues`/`readAllTargetValues` mechanism in
  `+inverterhilgui/targetSession.m` is a one-time snapshot taken at
  connect, not a live poll, so it is not a drop-in fit) inside whatever
  method drives `app.Telemetry`'s live refresh cycle — deliberately not
  attempted here without first fully understanding that refresh loop, given
  this is a live-polling change in the same GUI safety-relevant path.
