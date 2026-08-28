# MFE26-VC `controls` branch synchronization

## Scope and provenance

This virtual VCU is pinned to MFE26-VC `controls` commit
`bcd6352e1674ef4b999391f345f675f386718d32` (HEAD message
"changed inputs since imu is flipped"). Firmware citations below are line
numbers at that commit in:

- `Core/Src/driverInputs.cpp`
- `Core/Src/vcComms.cpp`
- `Core/Src/vcStateMachine.cpp`
- `Core/Src/controls.c`, `Core/Inc/controls.h`
- `Drivers/Device_Drivers/Inc/ephorus_driver.hpp`
- `Drivers/Device_Drivers/Src/ephorus_driver.cpp`
- `Drivers/Controls_model/ControlsMFE25.{c,h}` (the pinned generated allocator)

The exact pinned generated allocator C is vendored under
`vendor/controls_model/` with SHA-256 values recorded in
`vendor/controls_model/VENDORED_FROM.md`.

## Embedding approach — decision

**Selected: (a) vendor the pinned generated C and call it from a thin C
wrapper (`vvcu_controls_wrapper.c`) via `coder.ceval` / MEX.**

Rationale:

- The firmware *is* the R2025b-generated `ControlsMFE25.{c,h}` in
  `Drivers/Controls_model` (`ControlsMFE25.h:10-11` — model version 1.9,
  Simulink Coder 25.2 (R2025b)). Vendoring those exact bytes reproduces the
  precise QP allocator / controller artifact the firmware executes, including
  every parameter in `ControlsMFE25_data.c`.
- The generated C is plain C99. It was **compiled successfully under MATLAB
  R2024b with MSVC 2022** for the host MEX (`build_controls_model_mex`), and
  is linked into the Speedgoat build through `set_param(model,'CustomSource',
  ...)` in `configure_controls_model.m` rather than through R2025b's build
  infrastructure (`.mk`/TLC), so the release mismatch does not reach the
  toolchain.
- The only platform substitution is `coder_posix_time.c`. Firmware backs the
  generated `tic/toc` with STM32 TIM2/HAL; the HIL uses a **deliberate no-op
  stub** (round-2 item 5) since `ControlsMFE25.c` discards the `toc` return
  value at its sole call site (line 6806) and nothing else reads the
  timekeeper state — see deviation 11.
- `ControlsMFE25()` `malloc`s the model, block-IO, dwork, input and output
  structs **once** (5 calls, `ControlsMFE25.c:7268-7335`); `ControlsMFE25_step`
  and `ControlsMFE25_initialize` do no allocation. The wrapper calls
  `ControlsMFE25()` once, from the deploy chart's persistent-init branch,
  which in generated code runs on the first 5 ms sample. One-shot heap on
  the first sample is acceptable for Simulink Real-Time (round-2 item 4
  analysis below).

**Rejected: (b) reference / regenerate from the R2022a source model**
(`MFE25-Controls/02 Controls Model/Codegen/Template/ControlsMFE25.slx`,
model version 1.9, saved by R2022a, 32-in/34-out, 0.005 s schedule):

- That `.slx` lives in a *different repository* and is **not part of the
  pinned firmware checkout**; its exact relationship to the firmware's
  generated artifact is not established.
- Regenerating it under R2024b would produce R2024b code, i.e. a *third*
  distinct artifact that is neither what the firmware runs nor what was
  reviewed. A Model block would also re-solve initial conditions and could
  diverge numerically from the firmware binary.

**Rejected: (c) hand-porting to a MATLAB Function** — the normalized QP
torque allocator is far too large to re-implement faithfully.

### Host reference boundary

`+virtualvcu/step.m` deliberately does **not** embed an allocator. It takes a
real `[FL FR RL RR]` allocator result as an optional 6th argument and
unit-tests reset, the 15 Nm cap, interlock gating, frame packing and
physical-corner mapping. `virtualvcu.controlsModelStep` /
`virtualvcu.controlsInputVector` expose the vendored allocator (through the
MEX) so host tests can produce that real result.

## Timing decision

The virtual-VCU chart runs at **5 ms (200 Hz)**, matching the firmware comms
task (`vcComms` `vTaskDelayUntil`) and the required `ControlsMFE25_step`
period. Consequences:

- Precharge / buzzer counters change from firmware's `osDelay(7500)` /
  `osDelay(1500)` ms (`vcStateMachine.cpp:315,351`) to **1500 / 300 ticks**
  (`config.m` `prechargeTicks` / `buzzingTicks`), preserving 7.5 s / 1.5 s.
- The firmware driver-input task runs every 15 ms
  (`driverInputs.cpp` header). The single-chart HIL evaluates pedal
  plausibility on every 5 ms tick instead of adding a second asynchronous
  task. Thresholds, latching and output semantics are exact; a pedal edge can
  become visible up to 10 ms earlier than on the firmware. This approximation
  is isolated from the allocator, which is still stepped at exactly 5 ms.

The surrounding inverter HIL keeps its base solver; a Rate Transition
(`VCU 5 ms Rate Transition` in `patch_virtual_vcu_inputs.m`) sets the chart
rate, and the five Port-A CAN Write blocks run at `ts = 0.005`.

## Firmware fact → where modeled

| Firmware fact (file:line) | HIL location |
|---|---|
| Throttle 1 falling, min 23100 / max 30100, span 7000 (`driverInputs.cpp:172-176`) | `config.m:17,22`; `rawToPedal.m:6-10`; `virtualVcuDeployStep.m` `t1` |
| Throttle 2 falling, min 46500 / max 63600, span 17100 (`driverInputs.cpp:193-197`) | same files, `t2` |
| Brake conversion zero 9025, max 31800, span 22775 (`driverInputs.cpp:213-217`) | `config.m:23,25`; `rawToPedal.m:12-17`; deploy `b1`,`b2` |
| Brake 2 range-check low 8280, *conversion* still uses 9025 (`driverInputs.cpp:213,267`) | `config.m:24` `brakeRangeLowRaw(2)=8280`; deploy `b2` uses 9025 zero |
| Throttle in-range margin 15 % of span (`driverInputs.cpp:233,245`) | `rawToPedal.m:9`; deploy `t1Margin`/`t2Margin` |
| Brake in-range margin 25 % of span (`driverInputs.cpp:257,269`) | `rawToPedal.m:16`; deploy `b1Margin` |
| APPS agreement: `|t1pct - t2pct| <= 0.20` fraction (`driverInputs.cpp:288-294`) | deploy `abs(t1-t2) <= 0.20`; `step.m` uses equivalent 20 pct points |
| `isBrakePlausible()` = brake 1 range only; brake 2 cross-check commented out (`driverInputs.cpp:299-316`) | `step.m:25` `brakePlausible = bv1`; deploy `brakeOk = b1InRange` |
| `brakeValidPct = brake1Pct` (not an average) (`driverInputs.cpp:154-156`) | `step.m:33-34`; deploy `brakeValidPct = b1` |
| Implausible APPS zeroes both throttle channels + `throttleValidPct` (`driverInputs.cpp:149-151`) | `step.m`/deploy `throttleValidPct = 0` branch |
| Implausible brake zeroes both brake channels + `brakeValidPct` (`driverInputs.cpp:158-160`) | `step.m`/deploy `b1 = 0; b2 = 0; brakeValidPct = 0` |
| APPS/brake interlock latches when `throttleValidPct >= 0.25 && brakeValidPct >= 0.25` (`driverInputs.cpp:66-69`) | `step.m:36-37`; deploy `appsErrorLatch = true` |
| Interlock clears only when `throttleValidPct <= 0.05` (`driverInputs.cpp:71-77`) | `step.m:38-39`; deploy `appsErrorLatch = false` branch |
| `torqueRequestPct = (appsPlausible && !appsError) ? throttleValidPct : 0` — brake plausibility **not** required (`driverInputs.cpp:79-82`) | `step.m:41-44`; deploy `torqueRequestPct` |
| Allocator receives **ungated** `throttleValidPct` as `rThrottlePedal` (`vcComms.cpp:410`) | deploy `controlsInputs(18) = throttleValidPct` (not `torqueRequestPct`); test `allocatorThrottleIsNotGatedByAppsLatch` |
| `ControlsMFE25` init constants: min_speed 0.5, P_max 80000, lamda 1/1/0.1, efficiency 0.99, N_long 100, T_i_max 15, R_max 0, yrr/Fz/slip 1 (`controls.c:22-33`) | `controlsInputVector.m`; deploy `controlsInputs(...)`; `vvcu_controls_wrapper.c default_inputs` |
| Init `use_imu_vel_x/y = 0`, `use_pushrod_loadcells = 0`, `BRegenEnabledButton = 0` (`controls.c:36-41`) | `vvcu_controls_wrapper.c default_inputs` (reset state) |
| One reset step at startup: `ResetSignal 1 -> step -> 0`, once (`controls.c:44-46`) | `vvcu_controls_wrapper.c vvcu_controls_reset`; deploy calls it once in persistent-init |
| Per-cycle `ResetSignal = 0` (`vcComms.cpp:378`) | deploy `controlsInputs(1) = 0` |
| Per-cycle runtime override `use_imu_vel_x = use_imu_vel_y = 1`, `use_pushrod_loadcells = 0` (`vcComms.cpp:421-423`) | deploy `controlsInputs(25:27) = [1 1 0]`; `controlsInputVector.m:26` |
| `om_fl<-INV_FL, om_fr<-INV_FR, om_rl<-INV_RL, om_rr<-INV_RR` wheel speed rad/s (`vcComms.cpp:381-384`) | deploy `controlsInputs(8:11) = wheelSpeedRadS([4 3 1 2])` (model FL/FR/RL/RR from physical INV order RL/RR/FR/FL) |
| IMU 180 deg flipped: `vehicle_speed=-v_x, vy=-v_y, ax=-ax, ay=-ay, yaw_rate=Gyrz` (`vcComms.cpp:386-404`) | no physical IMU receive path on this bench; see "Bench inputs" |
| `SWA = steer_sensor.getAngle()`, `rThrottlePedal = throttleValidPct`, `fz_* = 0` (`vcComms.cpp:408-418`) | deploy `controlsInputs(15)=0`, `(18)=throttleValidPct`, `(28:31)=0` |
| `controls_step()` each ordinary RTD cycle (`vcComms.cpp:425`) | deploy calls `vvcu_controls_step` only in the RTD non-reset branch |
| `MAX_TORQUE = 15` (`controls.h:18`), applied as **upper-only** cap `(tau > MAX_TORQUE) ? MAX_TORQUE : tau` (`vcComms.cpp:176,182,189,195`) | deploy `if rawTau(k) > 15 -> 15`; `packControlFrame.m:11`; `step.m:112` |
| Corner enum `INV1=RL, INV2=RR, INV3=FR, INV4=FL` (`ephorus_driver.hpp:19-24`) | `config.m:11` `inverterCorners = {RL,RR,FR,FL}` |
| `INV_RL<-tau3, INV_RR<-tau4, INV_FR<-tau2, INV_FL<-tau1` (`vcComms.cpp:176,182,189,195`) | `config.m:36` `controlsTauToInverter = [3 4 2 1]`; deploy `inverterTau = tau([3 4 2 1])` |
| Control IDs `0x186/0x196/0x1A6/0x1B6` (`ephorus_driver.hpp:27-30`) | `config.m:10`; `add_virtual_vcu_to_model.m` CAN Write UserData |
| Control bit layout: bit0 enable, bit1 resetError, bit2 ascAllowed, bit3 currentMode; bits16-31 speed int16 RPM; bits32-47 torquePos int16 @ 1/256 Nm; bits48-63 torqueNeg (`ephorus_driver.hpp:48-70`) | `packControlFrame.m:9,13-15`; deploy `payloads(base .. base+5)` |
| RTD normal command: `enable=1, resetError=0, ascAllowed=0, currentMode=0, speed=18000, torqueNeg=0` (`vcComms.cpp:166-172`) | `packControlFrame.m`; deploy `payloads(base)=1`, `payloads(base+2:base+3)=[80 70]` (18000 = 0x4650 LE) |
| Reset+enable frame = `enable=1 & resetError=1` -> byte 0 == 0x03 (`ephorus_driver.cpp:327-339`) | `packControlFrame.m:9` (`1 + (1<<1)`); deploy `payloads(9/17/25/33) = 3`; test asserts `[3 0 0 0 0 0 0 0]` |
| Encode: `(int32)(nm / (1/256))` truncates toward zero, then `clampToI16` (`ephorus_driver.cpp:206-210`) | deploy `fix(256*tau)` then clamp to `[-32768, 32767]` |
| First RTD comms cycle: `sendInverterReset()` then `return` — no torque, no `controls_step` (`vcComms.cpp:286-292`) | deploy `~resetSent` branch: 4 reset frames, no model step; `resetSent` latches |
| `resetSent` cleared in LV_ON/PRECHARGING/ENABLE/BUZZING (`vcComms.cpp:269`) | deploy `if state ~= 4, resetSent = false` |
| Internal allocator state retained across RTD exit / re-entry — never re-init/re-reset (`vcComms.cpp` never re-calls `controls_init`) | wrapper `vvcu_model` is static; `vvcu_controls_reset` never re-called after persistent-init |
| Pedal frame `0x1F5` (501): `[0]` throttle 0-100 int %, `[1:2]` front brake uint16 PSI (`650*frac`, clamp 0-650), `[3:4]` rear brake uint16 PSI, `[5:7]` steering = 0 (`vcComms.cpp:219-255`) | `packPedalFrame.m`; deploy `payloads(1:5)` |
| Non-RTD `0x1F5`: `brakeFront=brake1Pct, brakeRear=brake2Pct, throttle=throttleValidPct` (`vcComms.cpp:271-275`) | deploy `frontBrake=650*b1, rearBrake=650*b2, pedalThrottle=throttleValidPct` |
| RTD `0x1F5`: `throttle=torqueRequestPct` (interlock-gated) (`vcComms.cpp:303-307`) | deploy `if state == 4, pedalThrottle = torqueRequestPct` |
| brake 2 still converted and sent as rear pressure though excluded from plausibility (`driverInputs.cpp:130`, `vcComms.cpp:273`) | deploy `b2`, `payloads(4:5)`; test `brakeTwoIsTransmittedAsRearPressure` |
| State sequence `LV_ON -> PRECHARGING -> ENABLE -> BUZZING -> RTD` (`vcStateMachine.cpp:9`) | `config.m:27`; `step.m`; deploy `state` machine |
| RTD entry from ENABLE: `mainButton && brakeValidPct >= 0.25` (`vcStateMachine.cpp:333`) | `step.m:91`; deploy `state == 2 && mainButton && brakeValidPct >= 0.25` |
| RTD `prechargeButton` press -> PRECHARGING (`mainEnable=false; osDelay(50)`) (`vcStateMachine.cpp:367-371`) | `step.m:96`; deploy `state == 4 && precharge -> state 1` (the 50 ms is not modeled) |
| `prechargeComplete()` requires `sys.valid` **then** `dcLink12_v > 350` **and** `dcLink34_v > 350` (`vcStateMachine.cpp:131-146`) | host `step.m`: `dcLink12Valid && dcLink34Valid && dcLink12V > 350 && dcLink34V > 350`, each pair-valid set on a decoded `0x400`; deploy: `~dcLink12Valid \|\| ~dcLink34Valid \|\| dcLinkAccum12 <= 350 \|\| dcLinkAccum34 <= 350`, pair-valid set once the pair's bench-plant ramp has run (simulated `sys.valid`, no `0x400` receive path) |
| Inverter control frames queued **only** in the `RTD` case of `VCComms::run()`; `0x1F5` queued in every state except `ERROR_SHUTDOWN`, and skipped on the first RTD reset-only cycle (`vcComms.cpp:263-320,286-292,314-317`) | Every Port-A `CAN Write` uses its transmission-control input (`enableInput`); `Port A TX Gate` drives control-frame enable = `stateId == 4`, pedal-frame enable = `stateId ~= 5`. Host `step.m` exposes `controlFrameTxEnabled` / `pedalFrameTxEnabled` (the latter also false on the first RTD reset cycle). Deploy chart is unchanged. |
| ENABLE/BUZZING fault if `!prechargeComplete()`; RTD faults if `!prechargeComplete() || sdError` (`vcStateMachine.cpp:195-227`) | `step.m:78-81`; deploy `enterFault` / `enterFaultFromRtd` |
| `allInvertersReady()` inverter-status fault gate **commented out** (`vcStateMachine.cpp:211-213`) | no readiness fault gate anywhere in the HIL |
| PRECHARGING never faults (`vcStateMachine.cpp:198-199`) | deploy `enterFault` only for `state == 2 || state == 3` |
| `prechargeEnable = true` in **PRECHARGING and ENABLE**, dropped on ENABLE->BUZZING (`vcStateMachine.cpp:307,325,334`) | deploy `payloads(43) = state == 1 || state == 2`; `step.m` `prechargeEnable`; test `prechargeEnableHeldClosedThroughEnable` |
| `mainEnable = true` in ENABLE/BUZZING/RTD (`vcStateMachine.cpp:324,342,359`) | deploy `payloads(42) = state >= 2 && state <= 4` |
| `inverterCtrlEnable = true` in PRECHARGING..RTD (`vcStateMachine.cpp:309,327,345,362`) | deploy `payloads(44) = state >= 1 && state <= 4` |
| Cooling every cycle: `coolingSwitch -> griRelay1/2 + cometRelay` (`vcStateMachine.cpp:248-258`) | deploy `payloads(45:47) = DI03` |
| Fan every cycle: `fanSwitch -> fanRelay` (`vcStateMachine.cpp:260-265`) | deploy `payloads(48) = DI04` |
| GPIO inputs are semantic names (PRECH_BTN_IN, MAIN_BTN_IN, COOLING_SW_IN, FAN_SW_IN, SD_FB_IN) (`vcStateMachine.cpp:54-85`) | `config.m:37-38` `digitalMap` — **bench wiring choice**, see deviation below |
| `0x3X5` bits 48-63 actual speed int16 RPM -> rad/s via `2*pi/60 / GEAR_RATIO`, `GEAR_RATIO = 13.39` (`ephorus_driver.cpp:285-289`; `ephorus_driver.hpp:162`) | `decodeStatusFrame.m:29-31`; `models/virtualVcuRxRetain.m` (1 ms retention); deploy chart reads retained `u(26:29)`; `config.m:33` |
| RX FIFO fully drained every comms cycle, updating all four `wheel_speed` slots that arrived (`vcComms.cpp:327-374`) | `models/virtualVcuRxRetain.m` latches all four `0x3X5` frames at the 1 ms base rate ahead of the 5 ms `VCU 5 ms Rate Transition`; host `+virtualvcu/step.m` retains per-corner in `context.can.wheelSpeedRadS` across samples |

## Bench inputs and evidence boundary

- **Wheel speeds**: the allocator's `om_*` are updated only after a physical
  Ephorus `0x385/0x395/0x3A5/0x3B5` frame is actually read on Port A. Before
  the first frame each retained speed is its initialized zero. No
  received/valid flag is set and no status frame is synthesized. Retention
  now happens at the 1 ms base rate in `models/virtualVcuRxRetain.m` (item 2)
  so every frame in a 5 ms window is captured; the block still only latches
  frames the hardware FIFO actually delivered.
- **IMU / steering / load cells**: this Port-A bench has **no physical
  receive path** for MTi velocity/accel/gyro, LWS steering, or pushrod load
  cells. Firmware zeroes those inputs before the first frame and then
  last-value-holds while `use_imu_vel_x/y` stay 1; with no frame ever
  received, "last value held" is identically zero, so the deploy chart feeds
  literal zeros for `vehicle_speed, vy, ax, ay, yaw_rate, SWA, fz_*`. The
  runtime `use_imu_vel_x/y = 1` overrides are still applied, matching
  `update_ctrls_inputs()` which sets them unconditionally.
- **DC link**: `dcLinkAccum12` / `dcLinkAccum34` are two internal bench-plant
  ramps (0 -> 400 V over the precharge window), not a CAN receive claim. The
  bench drives both identically. The fault gate is
  `~dcLink12Valid || ~dcLink34Valid || dcLinkAccum12 <= 350 ||
  dcLinkAccum34 <= 350` (item 1); `dcLink12Valid` / `dcLink34Valid` are the
  simulated per-pair `sys.valid` (true once the pair's ramp has run), so the
  structure matches firmware `prechargeComplete()`
  (`if (!sys.valid) ...; if (v12 <= 350 || v34 <= 350) ...`). The host
  reference (`step.m`) is stricter: `dcLink12Valid` / `dcLink34Valid` are set
  only on a genuinely decoded `0x400`, and both pair voltages must exceed
  350 V.

## Known deviations and firmware issues preserved

1. **`0x1F5` still emitted on the first RTD reset-only cycle** (one 5 ms
   frame). Items 8/9 added per-frame transmission gating: every Port-A
   `CAN Write` now uses its transmission-control input, driven by
   `Port A TX Gate` from the published `VirtualVcuStateId` — control frames
   transmit only in RTD (`state == 4`), `0x1F5` transmits in every state
   except `ERROR_SHUTDOWN` (`state ~= 5`). Firmware additionally skips
   `0x1F5` on the first RTD comms cycle (reset-only, `vcComms.cpp:286-292`);
   the gate keys on state alone, so that single frame is still sent. The
   host reference (`step.m` `pedalFrameTxEnabled`) models the first-cycle
   skip fully. No consumer infers fault state from `0x1F5` presence and the
   RTD-entry gap is one cycle, so this residual is immaterial (orchestrator
   decision, round 2). **Verify via slbuild** — see checklist item F.
2. **`ERROR_SHUTDOWN` recovery**: firmware falls through state 5 to `LV_ON`
   within a single call (`vcStateMachine.cpp:375-383` `forceLvOn()`). In the
   HIL the fault-entry branch runs before the `elseif state == 5` recovery,
   so **any** fault entry — DC-link-only included — parks state 5 for one
   full 5 ms cycle before recovery is evaluated. `shutdownFeedback`
   additionally latches the hold until it clears (deliberate, so the fault is
   observable); a DC-link-only fault clears to `LV_ON` on the next cycle and
   can be re-established by precharge.
3. **Pedal task rate**: 5 ms unified HIL tick vs firmware's independent 15 ms
   driver-input task (see "Timing decision").
4. **RTD -> PRECHARGING** does not model the firmware's `osDelay(50)`
   (`vcStateMachine.cpp:369`).
5. **APPS/brake interlock does not suppress allocator torque.** Firmware zeroes
   `torqueRequestPct` but `update_ctrls_inputs()` feeds ungated
   `throttleValidPct` to `ControlsMFE25` and `sendInverterCommand_ctrl()`
   sends allocator output without checking `appsError`
   (`vcComms.cpp:410,162-201`). The HIL reproduces this exactly; only the
   RTD `0x1F5` throttle byte is interlock-gated. **This warrants a firmware
   safety review before torque-enabled bench operation.**
6. **15 Nm cap is upper-only** (`vcComms.cpp:176`...). Negative / non-finite
   `tau` are not rejected before the int16 clamp. The HIL matches this.
7. **DI index map** (`config.m` `digitalMap`: DI01 precharge, DI02 main/RTD,
   DI03 cooling, DI04 fan, DI05 shutdown feedback) is a **bench wiring
   choice**. Firmware only has semantic GPIO names; it does not mandate these
   indices. `patch_virtual_vcu_inputs.m` documents the empirically confirmed
   Module-1 self-loop pin pairing.
8. **Cooling relays**: firmware `forceLvOn()` blips `griRelay1/2` and
   `cometRelay` low for one cycle inside `ERROR_SHUTDOWN`
   (`vcStateMachine.cpp:186-188`) before `run()` re-evaluates the switch next
   cycle. The HIL drives the relays purely from the switch and ignores that
   one-cycle blip.
9. **DC-link plant, not a receive path.** The deploy chart has no physical
   `0x400` system-status receive path, so its `sys.valid` term is
   **simulated**: `dcLink12Valid` / `dcLink34Valid` (item 1) are set once
   each pair's bench-plant ramp accumulator (`dcLinkAccum12` /
   `dcLinkAccum34`) has been active, not on a received frame. The fault gate
   is `~dcLink12Valid || ~dcLink34Valid || dcLinkAccum12 <= 350 ||
   dcLinkAccum34 <= 350`, structurally mirroring
   `if (!sys.valid) return false; if (v12 <= 350 || v34 <= 350) return
   false;` (`vcStateMachine.cpp:131-146`), even though the bench models a
   single bus driving both ramps identically. The host reference
   `+virtualvcu/step.m` is genuine: `dcLink12Valid` / `dcLink34Valid` are
   set only when a `0x400` is actually decoded, and both pair voltages must
   exceed 350 V. A real dual-pair `0x400` decode on the bench is a follow-up
   once that frame is wired.
10. **Generated-C release**: the vendored allocator C is R2025b-generated and
    the HIL builds under R2024b. The C compiles cleanly (verified for the host
    MEX); the Speedgoat link is covered by the checklist below.
11. **`coder_posix_time.c` is a deliberate no-op stub** (item 5).
    `coderInitTimeFunctions` sets `freq = 1.0`; `coderTimeClockGettimeMonotonic`
    returns constant zeros with no syscall. `ControlsMFE25.c` calls
    `ControlsMFE25_toc` exactly once per step (line 6806 at `bcd6352`) and
    **discards the return**; the timekeeper's state (`savedTime` on the
    stack, `DW->freq*`) is read only by the timing functions themselves, so
    constant zeros cannot change allocator outputs or state evolution. A real
    `clock_gettime`/`clock()` body (in git history) need only be restored if
    a future allocator revision starts consuming `toc`. Rationale: on the
    slrealtime (QNX) target a monotonic-clock syscall every 5 ms is pure
    overhead and a portability risk for a discarded value.
12. **Inverter control frames outside RTD (RESOLVED, item 8).** Every Port-A
    `CAN Write` now uses its transmission-control input; `Port A TX Gate`
    disables the four control-frame writes whenever `stateId ~= 4`, so a
    bench CAN logger sees exactly firmware's wire behaviour (no frame, not a
    disabled zero frame). In RTD, reset and torque-cycle payload bytes are
    exact. **Verify via slbuild** — checklist item F.
13. **CAN RX sub-sampling (RESOLVED pending slbuild, item 2).**
    `models/virtualVcuRxRetain.m` is a 1 ms MATLAB Function inserted ahead of
    `VCU 5 ms Rate Transition` (`patch_virtual_vcu_inputs.m`). On every base
    tick it decodes whichever of `0x385/0x395/0x3A5/0x3B5` is present into a
    persistent per-corner rad/s slot and outputs all four; the chart reads
    the coherent 4-vector as `u(26:29)` and no longer decodes raw RX bytes
    itself. Every `0x3X5` frame in a 5 ms window is now retained, not just
    the last. Host coverage: `rxRetentionKeepsAllFourCornersInAWindow`,
    `hostContextRetainsPerCornerWheelSpeed`. The Simulink wiring itself
    (mux width 8->9, new block) is **verify via slbuild** — checklist item E.
    On the current bench there is still no wheel-speed feedback source.
14. The base `VC_HIL/build/build_inverter_hil_model.m` builds a real-VCU
    topology; this task is constrained to `virtual-vcu/`, so
    `build_controls_synced_virtual_vcu` builds the base artifact and then
    applies the virtual-VCU overlay. No base-builder file was changed.

## Round-2 follow-up items

| # | Item | Status | Where |
|---|---|---|---|
| 1 | Track both DC-link pairs independently + per-pair valid flags | Done (host-verified); chart pending slbuild | `virtualVcuDeployStep.m` (`dcLink12Valid`/`dcLink34Valid`), `+virtualvcu/initialContext.m`, `+virtualvcu/step.m`; tests `neitherDcLinkPairValidFaultsActiveHv`, `onePairValidButBelowFloorFaultsRtd` |
| 2 | Preserve latest RX for all four corners between VCU executions | Done pending slbuild | new `models/virtualVcuRxRetain.m`, `patch_virtual_vcu_inputs.m` (mux 8->9), chart reads `u(26:29)`; tests `rxRetentionKeepsAllFourCornersInAWindow`, `hostContextRetainsPerCornerWheelSpeed` |
| 3 | `slbuild('inverter_hil')` + Speedgoat download | BLOCKED (disk 100 % full, target `10.0.1.1` offline) — ordered steps below | — |
| 4 | Confirm `malloc()` support + when allocation happens | Done (analysis) | this doc, "malloc / one-time allocation" below |
| 5 | Replace/validate the `clock()` timing impl | Done — deliberate no-op stub | `vendor/controls_model/coder_posix_time.c`, `VENDORED_FROM.md`, deviation 11 |
| 6 | Quantize pedal voltages to integer ADC counts | Verified only (already in `076a476`) | `virtualVcuDeployStep.m:27` `raw = round(...)`, matches `+virtualvcu/voltageToRaw.m` |
| 7 | Host torque `round()` -> truncation | Verified only (already in `076a476`) | `+virtualvcu/packControlFrame.m:14` `fix(...)`, matches `ephorus_driver.cpp:206-210`; `packPedalFrame.m` correctly keeps `round` |
| 8 | Gate the 4 control-frame Port-A CAN writes to RTD-only | Done pending slbuild | `add_virtual_vcu_to_model.m` (`enableInput` + `Port A TX Gate`), `verify_virtual_vcu_model.m`; host `step.m` `controlFrameTxEnabled`; test `canFrameTransmissionGatingMatchesFirmwareStates` |
| 9 | Fold `0x1F5` gating into the item-8 mechanism | Done pending slbuild, with one residual | Same as item 8: `pedalFrameTxEnabled` = `state ~= 5`. Firmware's extra first-RTD-reset-cycle skip is modelled host-side only; the Simulink gate sends that one frame (deviation 1, orchestrator-accepted). |

### Item 3 — ordered steps to build + download once disk and target are available

Prerequisites: free **at least ~8 GB on C:** (MATLAB codegen cache/`slprj` and
`VC_HIL\build\.simulink` live on C:), and confirm `ping 10.0.1.1` succeeds
(Speedgoat `TargetPC1` powered and on the link).

```matlab
cd('C:\Users\MFE-HPC\Documents\GitHub\HIL-vvcu-sync')
addpath(fullfile(pwd,'virtual-vcu'))
addpath(fullfile(pwd,'virtual-vcu','models'))
addpath(fullfile(pwd,'virtual-vcu','tests'))
addpath(fullfile(pwd,'VC_HIL','build'))

% 1. Host regression first (no disk cost).
build_controls_model_mex(true);
run_virtual_vcu_tests;                       % expect 22/22

% 2. Rebuild base + overlay, persist chart/custom-C, verify boundary.
result = build_controls_synced_virtual_vcu(true);
verify_virtual_vcu_model(result.modelPath);  % now also checks enableInput + Port A TX Gate
cd(fullfile(pwd,'VC_HIL','build')); verify_inverter_hil_model; cd('..\..')

% 3. Force diagram compilation (validates every MATLAB Function codegen:
%    the chart at u(29), virtualVcuRxRetain, Port A TX Gate).
load_system(result.modelPath);
set_param('inverter_hil','SimulationCommand','update');

% 4. Generate + link the Speedgoat application.
slbuild('inverter_hil');

% 5. Download + run on the target (target must be online).
tg = slrealtime('TargetPC1');
load(tg,'inverter_hil');
start(tg);
% ... bench checks G below ...
stop(tg);
close_system('inverter_hil',0);
```

### Item 4 — malloc / one-time allocation analysis

- `ControlsMFE25(void)` (`vendor/controls_model/ControlsMFE25.c:7268-7335`)
  performs **5 `malloc()` calls** — the `RT_MODEL_ControlsMFE25_T` (7271),
  block-IO `B_ControlsMFE25_T` (7282), `DW_ControlsMFE25_T` (7289), input
  `ExtU_ControlsMFE25_T` (7297) and output `ExtY_ControlsMFE25_T` (7305)
  structs. `ControlsMFE25_initialize` and `ControlsMFE25_step` (entry at
  `:4630`) contain **no** `malloc`/`calloc`/`free` (grep-confirmed: the only
  allocation lines in the file are 7271-7305). `free()` happens only in
  `ControlsMFE25_terminate`.
- Call chain on the HIL: the deploy chart's persistent-init branch
  (`virtualVcuDeployStep.m` `if isempty(state)`) calls `vvcu_controls_reset`
  (host: `vvcu_controls_mex('reset')`), which calls `ControlsMFE25()` once.
  In generated Simulink code that persistent-init branch runs on the **first
  chart execution (first 5 ms sample hit)**, not in `mdlInitialize`. So:
  **allocation = 5 mallocs, once, on the first 5 ms sample**, long before RTD
  (RTD is >= 7.5 s + 1.5 s later).
- Simulink Real-Time (slrealtime, QNX) **does support `malloc` on the
  target**. Dynamic allocation is discouraged for hard-real-time, but a
  one-time allocation on the first sample produces only a **one-time
  first-sample timing transient**, not a per-step cost, and nothing
  allocates once RTD steps the allocator. **Assessment: ACCEPTABLE.**
- Optional future improvement (not required, do not force if it risks
  codegen): regenerate `ControlsMFE25` with Simulink Coder "static memory
  allocation" to remove the heap entirely, or move the `ControlsMFE25()`
  call into an explicit model-init `coder.ceval` so the malloc lands in
  `mdlInitialize` rather than the first step.

### Verify-via-slbuild checklist (per Simulink-side change)

None of the following could be built here (C: at 100 %, target offline).
Each was verified by careful reading + a host-test equivalent; confirm on the
next slbuild:

- **A. Deploy chart input width 25 -> 29.** `set_param('inverter_hil',
  'SimulationCommand','update')` must compile the `Virtual VCU LV_ON` chart
  with `u` width 29; `VCU Input Mux` must be 9 inputs and its output width 29
  into `VCU 5 ms Rate Transition`. Host equiv: `deployedChartUsesResetThenRealAllocator`
  (`u = zeros(29,1)`).
- **B. Item 1 per-pair valid flags in the chart.** New persistents
  `dcLink12Valid` / `dcLink34Valid` must codegen (plain logical persistents,
  not output-aliased). Confirm ENABLE/BUZZING/RTD still fault when a pair
  ramp is forced low. Host equiv: the two new DC-link tests.
- **C. Item 5 stub.** `configure_controls_model` links the same file list;
  confirm `coder_posix_time.c` compiles for the target toolchain (it already
  compiles for the host MEX — re-verified this session) and that `slbuild`
  reports no unresolved `clock`/`clock_gettime`.
- **D. `verify_virtual_vcu_model` additions.** It now asserts every Port-A
  CAN write has `enableInput == 'on'` and that `Port A TX Gate` exists — run
  it after the overlay.
- **E. Item 2 retention block.** `models/virtualVcuRxRetain.m` installed on
  `Virtual VCU/Virtual VCU RX Retain` (6 inputs from the `Port A RX * From`
  blocks, 1 output to `VCU Input Mux/9`), running at the 1 ms base rate.
  Confirm the base-rate persistent survives across chart executions and that
  the `From` tags (`EphorusRx*`) resolve. Host equiv:
  `rxRetentionKeepsAllFourCornersInAWindow`.
- **F. Items 8/9 transmission gating.** `Port A TX Gate` reads
  `VirtualVcuStateId` and drives inport 2 of each `Port A CAN Write` through
  `Port A TX Gate Rate Transition 1/2`. Bench check: with a CAN logger on
  Port A, confirm **no** `0x186/0x196/0x1A6/0x1B6` outside RTD; `0x1F5`
  present in LV_ON..BUZZING and absent in `ERROR_SHUTDOWN`; on RTD entry the
  four reset frames then (next cycle) enable-bit-set torque frames. Confirm
  the transmission-control input type the block expects (double 0/1 is fed;
  the base model's own CAN writes use `enableInput` the same way). Host
  equiv: `canFrameTransmissionGatingMatchesFirmwareStates`.

## Corrections applied to the Codex checkpoint (`d9e306e`)

- ADC full-scale in `virtualVcuDeployStep.m` changed from `3.3` to `5.0 V`
  (matches `config.m io183FullScaleV`, the AI block `parAdRange '0..5V'`, and
  the README loopback map). Deploy test `toVolts` updated to match.
- `PRECH_EN_OUT` now asserted in ENABLE as well as PRECHARGING
  (`vcStateMachine.cpp:325`), in both `virtualVcuDeployStep.m` and
  `+virtualvcu/step.m`.
- Removed a first-order pedal input filter from `virtualVcuDeployStep.m`;
  firmware `driverInputs.cpp` reads the ADC directly with no smoothing.
- Torque count encoding switched from `round` to `fix` + int16 clamp to match
  `ephorus_driver.cpp buildControlFrame`, in **both** `virtualVcuDeployStep.m`
  and the host `+virtualvcu/packControlFrame.m` (`packPedalFrame.m` keeps
  `round`: firmware `pctToByte` / `scalePhysicalToU16` explicitly add 0.5).
- Removed a dead `isfinite(raw)` guard (raws are clamp-bounded).
- `virtualVcuDeployStep.m` voltage->raw now rounds to integer ADC counts,
  matching host `+virtualvcu/voltageToRaw.m`.
- Split the deploy DC-link plant into two pair accumulators
  (`dcLinkAccum12` / `dcLinkAccum34`) gated on `either <= 350`, so the fault
  structure matches firmware `prechargeComplete()` (deviation 9).
- Added tests: `prechargeEnableHeldClosedThroughEnable`,
  `allocatorThrottleIsNotGatedByAppsLatch`,
  `brakeTwoIsTransmittedAsRearPressure`.

The supervisor's "reset frame is bit 1 / byte 0 == 0x03" correction was
already implemented correctly in the checkpoint (`packControlFrame.m:9`,
test `goldenControlBytesAndReset`).

## MATLAB R2024b regeneration, build and test checklist

Run from the repository root in a clean MATLAB R2024b session. Steps 1-2
were re-run during round 2 and passed (22/22, Code Analyzer clean on every
touched `.m`, MEX recompiled with the item-5 stub); steps 3-6 still require a
machine with enough free disk for a full Simulink code-generation
(~several GB) and are **not verified here**. See the round-2
"Verify-via-slbuild checklist" above for the per-change confirmations.

```matlab
cd('C:\Users\MFE-HPC\Documents\GitHub\HIL-vvcu-sync')
addpath(fullfile(pwd,'virtual-vcu'))
addpath(fullfile(pwd,'virtual-vcu','models'))
addpath(fullfile(pwd,'virtual-vcu','tests'))
addpath(fullfile(pwd,'VC_HIL','build'))

% 1. [RUN, PASSED] Compile the vendored R2025b allocator C under R2024b and
%    exercise it, plus all host-reference behavior tests.
build_controls_model_mex(true);
run_virtual_vcu_tests;                 % 22/22 passed

% 2. [RUN, PASSED] Static analysis of every touched .m (Code Analyzer clean).

% 3. Rebuild the controls-branch base model, apply the virtual-VCU overlay,
%    persist the chart / custom-C settings, and verify the boundary.
result = build_controls_synced_virtual_vcu(true);
verify_virtual_vcu_model(result.modelPath);

% 4. Re-run the base topology verifier after the overlay.
cd(fullfile(pwd,'VC_HIL','build')); verify_inverter_hil_model; cd('..\..')

% 5. Force diagram compilation, then generate/link the Speedgoat application.
load_system(result.modelPath);
set_param('inverter_hil','SimulationCommand','update');   % validates the
                                                         % MATLAB Function
                                                         % chart codegen
slbuild('inverter_hil');
close_system('inverter_hil',0);
```

### Hardware-dependent checks (bench, not host)

1. Port A / channel 2 at 1 Mbit/s, standard 11-bit, grounded, terminated
   twice.
2. Torque disabled: capture `0x1F5` plus the four reset frames on the first
   RTD cycle; confirm the next cycle has enable bit 0 set, reset bit 1 clear,
   speed 18000 RPM (`[80 70]`).
3. Inject distinct, physically received `0x3X5` speeds; confirm FL/FR/RL/RR
   maps through INV4/INV3/INV1/INV2 without synthesizing receive evidence.
4. Verify separate front/rear brake bytes, APPS discrepancy, range failures,
   interlock latch/clear, both 350 V DC-link checks, precharge return from
   RTD, shutdown hold/clear, cooling relays, fan relay,
   `PRECH_EN_OUT` asserted in ENABLE.
5. Compare `tau1..tau4` and encoded 1/256 Nm limits against a SIL capture for
   the same 32 inputs before enabling physical torque.

No MATLAB target build, deployment, physical loopback, CAN ACK, or
torque-enabled bench result is claimed by this source-only change.
