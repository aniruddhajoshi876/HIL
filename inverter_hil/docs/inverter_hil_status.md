# Inverter HIL implementation status

Status date: 2026-07-31

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
- A constant-zero MIL scaffold with the required named architecture and four
  distinct channel paths.
- A commented, callback-gated hardware boundary with 17 resolved installed
  Speedgoat links: IO183 setup/AO/AI/DIO and IO614 setup/read/status plus nine
  CAN writes.
- IO183 AO01-AO04 and DIO01-DIO08 initial/reset values are zero; AI01-AI04,
  DIO09-DIO13, simultaneous AO update, pull-down inputs, raw CAN FIFO, 1 Mbit/s
  CAN, 1 ms I/O, and 5 ms CAN writes are represented and verified.

The complete R2024b test suite currently passes 67 tests with no failures or
incomplete results.

## Deliberately not claimed

The Simulink channel and CAN subsystems are safe constant-output scaffolds. The
host core has not yet been translated into code-generation-compatible blocks and
wired into those subsystems. Therefore the model is not yet a functional closed-
loop MIL, an IO-disconnected Speedgoat application build, or a deployable HIL.

The following planned deliverables remain open:

- Code-generation-compatible Simulink integration of decoder, state, plant,
  packer, queue-drain, rate, and observability logic.
- Successful `slrealtime.tlc` build and IO-disconnected target smoke test.
- Exact-release field-level `setparam` tuning spike and stable target parameter
  mapping.
- `inverter_hil_app.mlapp`, target instruments, command audit log, and heartbeat
  integration.
- Connected VCU tests and every physical evidence item below.

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

Inbound torque remains provisional. The dictionary selects the versioned 1/512
profile while retaining both candidates, but quantitative torque, acceleration,
current, power, and thermal signoff requires independent physical or vendor
evidence resolving 1/256 versus 1/512 Nm/count.

## Commands

Run these from the repository root with R2024b:

```powershell
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'inverter_hil')); cd(fullfile(pwd,'inverter_hil')); build_inverter_hil_model(true); verify_inverter_hil_model;"
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'tests','inverter_hil')); run_inverter_hil_tests;"
```
