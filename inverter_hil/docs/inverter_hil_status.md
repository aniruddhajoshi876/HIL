# Inverter HIL implementation status

Status date: 2026-07-31

> **Update, 2026-08-02.** This document predates the CAN decoder-bank-threading
> commits (`a308a7e`, `d5bcb8d`, `a5dc937`, `97bdea2`, `3bdb6e1`), the GUI
> telemetry/dark-theme finalization (`14c2bca` and later), and a further round
> of fixes made the same day: the IO183 Rail Monitor AI channels are now wired
> into GUI "measured pedal voltage" telemetry; `hil_cmd_inverter*_load_nm` and
> `hil_cmd_dc_link12_v`/`hil_cmd_dc_link34_v` now reach `inverterhil.stepModel`
> for real instead of dead-ending at Terminators; the control torque scale is
> resolved to 1/256 Nm/count (see below); and `hil_cmd_can_drop_control_mask`/
> `hil_cmd_can_drop_status_mask` now genuinely gate received control frames and
> transmitted status frames. Several claims below (test count, "constant-zero
> scaffold", "1/512 selected") are stale as a result and are corrected inline
> rather than rewriting this document's historical narrative wholesale.

## Implemented and host-verified

- R2024b-only workspace setup, reproducible model generator, and verifier.
- Bit-exact decoding for control IDs `0x186`, `0x196`, `0x1A6`, and `0x1B6`.
- Raw torque counts plus parallel 1/256 and 1/512 Nm interpretations.
- Four independent retained command ages with rollover-safe 50 ms and 500 ms
  timeout boundaries.
- Bit-exact 3X3, 3X5, and `0x400` packing for the ordered nine-frame cycle.
- Saturating conversion, malformed-input rejection, CAN write/overrun/warning/
  bus-off diagnostics, and safe-zero pedal/digital authority.
- Four independent Idle, Drive, Error, and Config Error state machines with
  pairwise DC-link and shared-pin behavior, fault latching, reset backoff,
  unsupported-mode diagnostics, and explicit transition reasons.
- Four independent PI/P torque responses, anti-windup, slew, lag, motor/load
  dynamics, Id/Iq and DC estimates, thermal states, and derating outputs.
- `inverter_hil.slx` and `inverter_hil.sldd` saved and reopened in R2024b.
- (2026-07-31, since superseded -- see the 2026-08-02 update above) A
  constant-zero MIL scaffold with the required named architecture and four
  distinct channel paths. The "Ephorus Channel 1-4" subsystem itself
  (`buildChannel`, `Load Demux`/`DC Link Demux`/`Fault Demux`) is still this:
  a deliberately unused, bypassed scaffold. But CAN status packing,
  transmission, reception, and decode are genuinely live, driven by the
  `Ephorus Status Cycle` MATLAB Function block calling
  `inverterhil.stepModel`, not a constant-zero placeholder; see the
  "Deliberately not claimed" section below.
- A commented, callback-gated hardware boundary with 17 resolved installed
  Speedgoat links: IO183 setup/AO/AI/DIO and IO614 setup/read/status plus nine
  CAN writes.
- IO183 AO01-AO04 and DIO01-DIO08 initial/reset values are zero; AI01-AI04,
  DIO09-DIO13, simultaneous AO update, pull-down inputs, raw CAN FIFO, 1 Mbit/s
  CAN, 1 ms I/O, and 5 ms CAN writes are represented and verified. IO183
  AI01-AI04 (the "Rail Monitor" block, actually a pedal-voltage hardware
  self-check loopback -- see `PINOUTS.md` S4.2) is now also routed out to GUI
  "measured pedal voltage" telemetry.

The complete R2024b test suite passed 67 tests as of the original 2026-07-31
status date; the current baseline (2026-08-02, after the CAN decoder-bank-
threading commits and the fixes noted above) is **161+ tests, 0 failures**.

## Deliberately not claimed

(2026-07-31, since substantially superseded -- see the 2026-08-02 update
above.) At the time this was written, the Simulink channel and CAN subsystems
were safe constant-output scaffolds and the host core had not yet been
translated into code-generation-compatible blocks wired into those
subsystems. That is no longer true for CAN: `Ephorus Status Cycle` (a MATLAB
Function block calling `inverterhil.stepModel`) genuinely packs, transmits,
and receives/decodes the nine-frame status cycle and the four control frames,
and the hardware boundary is live on the current bench
(`hil_hardware_preflight_complete = true`; see `PINOUTS.md` for the current
gate state). The "Ephorus Channel 1-4" subsystem
(`buildChannel`/`Load Demux`/`DC Link Demux`/`Fault Demux`) remains the one
genuinely-unused scaffold, deliberately bypassed rather than resurrected --
GUI-commanded per-channel load torque, connected flag, and DC-link voltage
route directly into `Ephorus Status Cycle` instead.

The following planned deliverables remain open:

- Exact-release field-level `setparam` tuning spike and stable target parameter
  mapping, beyond what the current GUI parameter contract already exercises.
- Connected VCU tests and every physical evidence item below.
- A per-channel fault-injection bitmask consumer: `hil_cmd_inverter*_fault_mask`
  is declared and writable but has no effect anywhere in `+inverterhil/` today
  (see `inverterhil.defaultExternalInputs`); documented as a follow-up, not
  invented.

## Hardware and protocol gates

The hardware subsystem must remain commented while
`hil_hardware_preflight_complete` is false. The model initialization callback
rejects an uncommented boundary while that gate is open.

Required evidence before setting the gate true:

- J3 isolation for every driven net.
- IO183/VCU ground strategy and exact module revisions.
- VCU input/output voltage levels, polarity, source/sink behavior, and required
  conditioning, including TP6-TP10 under their existing loads.
- Physical verification that stopped/unloaded/reset IO183 outputs reach their
  configured safe levels and that 0 V pedals are rejected by the VCU.
- CAN1 selection, corner mapping, harness continuity, and exactly two 120 ohm
  terminators.
- Physical queue timing, frame ordering, bus-off/overrun behavior, and status
  acceptance by the VCU.

**RESOLVED 2026-08-02** (was: "Inbound torque remains provisional"). The
dictionary now selects the versioned 1/256 profile (`vcu256`,
`verified = true`), resolved by independent VCU firmware evidence -- see
`+inverterhil/protocol.m`'s `torqueProfiles.vcu256` comment and
`docs/sil_vs_hil_conformance.md`'s CONF-2 finding. The retired 1/512 profile
(`provisional512`) is retained, still `verified = false`, only as a
known-not-the-answer profile exercised by a handful of regression tests.
Quantitative torque, acceleration, current, power, and thermal signoff still
requires independent physical or vendor confirmation on the bench; the scale
ambiguity itself is closed.

## Commands

Run these from the repository root with R2024b:

```powershell
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'inverter_hil')); cd(fullfile(pwd,'inverter_hil')); build_inverter_hil_model(true); verify_inverter_hil_model;"
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'tests','inverter_hil')); run_inverter_hil_tests;"
```
