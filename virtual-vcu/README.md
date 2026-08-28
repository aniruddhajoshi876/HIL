# Virtual VCU (MATLAB/Simulink R2024b)

Bench VCU stand-in synchronized to MFE26-VC `controls` commit
`bcd6352e1674ef4b999391f345f675f386718d32`. It reads the physical IO183
Module 2 pedal/digital loopback and IO614 Port A (CAN channel 2) traffic,
broadcasts pedal frame `0x1F5` (501), and sends Ephorus control IDs
`0x186/0x196/0x1A6/0x1B6`.

## Torque path

The torque commands come from the **real generated `ControlsMFE25` allocator**
vendored under `vendor/controls_model/` (the exact R2025b-generated C the
firmware runs — see `vendor/controls_model/VENDORED_FROM.md`), not a
throttle-scaled approximation. A thin C wrapper (`vvcu_controls_wrapper.c`)
owns one model instance and is called from the deploy chart via `coder.ceval`
and from host tests via a MEX built from the same sources.

The deploy chart runs at **5 ms**, performs the firmware reset sequence
(`ResetSignal 1 -> step -> 0`) once at model init, sends a one-cycle
inverter reset+enable frame (`byte 0 == 0x03`) on the first RTD comms cycle
with no torque, then steps the allocator once per ordinary RTD cycle. Internal
allocator state is retained across RTD exit/re-entry and never re-initialized.
`tau1..tau4 = FL,FR,RL,RR` map to `INV4,INV3,INV1,INV2`; the positive torque
limit is capped upper-only at 15 Nm and encoded at 1/256 Nm/count.

## Pedal and state machine

Pedal processing follows the controls branch: 15 % throttle / 25 % brake
in-range margins, `|t1-t2| <= 0.20` APPS agreement, brake-1-only plausibility
(`brakeValidPct = brake1Pct`), and the latched 25 %/25 % APPS-brake interlock
that clears at 5 % throttle. The interlock zeroes `torqueRequestPct` and the
RTD `0x1F5` throttle byte but, matching firmware, does **not** suppress the
allocator (`rThrottlePedal` gets ungated `throttleValidPct`). Pedal frame
front/rear pressure bytes come from brake 1 and brake 2 separately; brake 2 is
still transmitted even though it is excluded from plausibility.

`LV_ON -> PRECHARGING -> ENABLE -> BUZZING -> RTD` with 1500/300 tick
(7.5 s / 1.5 s) timers. RTD entry needs the main button and brake 1 >= 25 %.
Both DC-link pairs must exceed 350 V for active HV states to stay healthy;
`PRECH_EN_OUT` is asserted in PRECHARGING and ENABLE. Inverter-ready status is
not a fault gate (that firmware check is commented out).

## Bench evidence boundary

The bench never invents received inverter status. Only a physical `0x3X5`
frame updates its retained wheel speed. With no physical IMU, steering, or
load-cell receive path, those allocator inputs stay zero while the firmware
runtime `use_imu_vel_x/y = 1` overrides are still applied. Analog loopback is
0-5 V (IO183 Module 1 self-loop). The DI01-DI05 index map is a bench wiring
choice, not a firmware requirement.

See `docs/controls_branch_sync.md` for the full firmware fact -> file:line
mapping, the embedding-approach decision and rejected alternatives, every
deviation, provenance hashes, and the exact R2024b regen/build/test steps.

## Verification status

- Host: `build_controls_model_mex` (R2025b C compiled under R2024b + MSVC
  2022) and `run_virtual_vcu_tests` (17/17) pass; Code Analyzer clean.
- Not verified here: `build_controls_synced_virtual_vcu`, `verify_*`, the
  Speedgoat `slbuild`, target deployment, CAN ACK capture, and physical
  loopback. Local source inspection is not bench evidence.
