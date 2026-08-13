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
- **Resolved: `hil_cmd_xcp_pedals_active` (model-side) and `XcpDriving`
  (GUI-side) are now wired together, not two independent flags.**
  `TargetSession.readLiveIo` reads `hil_cmd_xcp_pedals_active` live each
  poll cycle (`Backend.getparam`, same optional/try-catch pattern as the
  existing `appsBrakeFault` port read), and `inverter_hil_app.refreshLiveIo`
  sets `app.XcpDriving` from it every cycle, failing closed to `false`
  (GUI keeps/regains pedal write ownership) on any read failure or
  disconnect. The GUI and the model-side Switch now read the same
  underlying source of truth and cannot disagree. This has not been
  exercised against a real target — the read path is real, but nothing has
  actually called it against live hardware, since none is reachable from
  this environment.
- **The deployed chart (`virtualVcuDeployStep.m`) still has no CAN-RX
  decode path at all.** `valid`, `appsPlausible`, `brakePlausible`, and
  `can.dcLink12V`/`dcLink34V`/`inverterReady`/`inverterFault` exist only in
  the host/SIL reference (`+virtualvcu/step.m`, via
  `virtualvcu.decodeStatusFrame`). Adding these to the deployed path means
  giving the chart a genuinely new CAN RX input (it currently takes only
  physical AI/DI, `u`), porting the decode logic, and adding persistent
  CAN state alongside the existing `state`/`ticks` persistents — real new
  Simulink topology (a new input port, a MUX change upstream), not just a
  new output tap like `torqueRequestNm` was. This was deliberately not
  attempted: it cannot be verified against a real model build in this
  environment (no Speedgoat target block library here at all), and
  unverifiable topology surgery risks landing something that looks
  complete in the `.m` script but is subtly wrong at actual build time —
  worse than leaving it honestly undone. Whoever picks this up should plan
  to iterate against a real `build_inverter_hil_model` run, not trust a
  from-scratch attempt without one.
- **A2L export marking**: checked, not changed. The existing convention
  already applied consistently to every tunable/signal this branch added
  (`hil_cmd_xcp_pedals_throttle/brake/active`, `torqueRequestNm`) is
  `Simulink.Parameter.CoderInfo.StorageClass = 'SimulinkGlobal'` for
  dictionary parameters and `TestPoint = 'on'` on the Signal Copy outputs
  in `Virtual VCU Observability` — both already in place via the same
  helper functions (`parameter()`, the observability loop) every other
  entry uses. No distinct additional ASAP2-specific marking mechanism was
  found in the local model beyond this. Whether Simulink Real-Time's
  "Generate Calibration Files" tool actually honors exactly this
  combination can only be confirmed once a real build exists to run it
  against.
- **No integration test proves `pollCoalescers` suppresses `Session.write`
  end-to-end.** No existing test in this suite instantiates the full
  `inverter_hil_app` class (every GUI test works against the underlying
  `inverterhilgui.*` helper functions directly) — there is no established
  pattern for constructing the app headlessly, and doing so for the first
  time carries real risk of introducing figure/graphics flakiness into a
  batch-mode test suite. What exists instead: `controlPolicy`'s own test
  proves the policy logic is correct, and `pollCoalescers`'s gating
  condition (`~app.XcpDriving`) reads the identical property `controlPolicy`
  is given, so the two cannot diverge by construction — but this is
  reasoning from code inspection, not a running assertion.
