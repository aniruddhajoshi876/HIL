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
- The only platform substitution is `coder_posix_time.c` (firmware backs the
  generated `tic/toc` with STM32 TIM2/HAL; the HIL backs it with the C
  runtime `clock()`). `ControlsMFE25.c` discards the `toc` return value, so
  the substitution cannot change allocator state or outputs.
- `ControlsMFE25()` `malloc`s the model, block-IO, dwork, input and output
  structs **once** (`ControlsMFE25.c:7295-7335`); `ControlsMFE25_step` does no
  allocation. The wrapper calls `ControlsMFE25()` once, from the deploy
  chart's persistent-init branch. One-shot heap at model init is acceptable
  for Simulink Real-Time.

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
| `prechargeComplete()` requires `dcLink12_v > 350` **and** `dcLink34_v > 350` and `sys.valid` (`vcStateMachine.cpp:131-146`) | `step.m:73-75` (needs a decoded `0x400`, both > 350); deploy `dcLinkAccum12 <= 350 \|\| dcLinkAccum34 <= 350` on two bench-plant ramp accumulators |
| ENABLE/BUZZING fault if `!prechargeComplete()`; RTD faults if `!prechargeComplete() || sdError` (`vcStateMachine.cpp:195-227`) | `step.m:78-81`; deploy `enterFault` / `enterFaultFromRtd` |
| `allInvertersReady()` inverter-status fault gate **commented out** (`vcStateMachine.cpp:211-213`) | no readiness fault gate anywhere in the HIL |
| PRECHARGING never faults (`vcStateMachine.cpp:198-199`) | deploy `enterFault` only for `state == 2 || state == 3` |
| `prechargeEnable = true` in **PRECHARGING and ENABLE**, dropped on ENABLE->BUZZING (`vcStateMachine.cpp:307,325,334`) | deploy `payloads(43) = state == 1 || state == 2`; `step.m` `prechargeEnable`; test `prechargeEnableHeldClosedThroughEnable` |
| `mainEnable = true` in ENABLE/BUZZING/RTD (`vcStateMachine.cpp:324,342,359`) | deploy `payloads(42) = state >= 2 && state <= 4` |
| `inverterCtrlEnable = true` in PRECHARGING..RTD (`vcStateMachine.cpp:309,327,345,362`) | deploy `payloads(44) = state >= 1 && state <= 4` |
| Cooling every cycle: `coolingSwitch -> griRelay1/2 + cometRelay` (`vcStateMachine.cpp:248-258`) | deploy `payloads(45:47) = DI03` |
| Fan every cycle: `fanSwitch -> fanRelay` (`vcStateMachine.cpp:260-265`) | deploy `payloads(48) = DI04` |
| GPIO inputs are semantic names (PRECH_BTN_IN, MAIN_BTN_IN, COOLING_SW_IN, FAN_SW_IN, SD_FB_IN) (`vcStateMachine.cpp:54-85`) | `config.m:37-38` `digitalMap` — **bench wiring choice**, see deviation below |
| `0x3X5` bits 48-63 actual speed int16 RPM -> rad/s via `2*pi/60 / GEAR_RATIO`, `GEAR_RATIO = 13.39` (`ephorus_driver.cpp:285-289`; `ephorus_driver.hpp:162`) | `decodeStatusFrame.m:29-31`; deploy wheel-speed decode; `config.m:33` |

## Bench inputs and evidence boundary

- **Wheel speeds**: the allocator's `om_*` are updated only after a physical
  Ephorus `0x385/0x395/0x3A5/0x3B5` frame is actually read on Port A. Before
  the first frame each retained speed is its initialized zero. No
  received/valid flag is set and no status frame is synthesized.
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
  bench drives both identically, but the fault gate is
  `dcLinkAccum12 <= 350 || dcLinkAccum34 <= 350`, so the structure matches
  firmware `prechargeComplete()`. The host reference (`step.m`) is stricter:
  it will not consider DC link healthy until a real `0x400` payload has been
  decoded and both pair voltages exceed 350 V.

## Known deviations and firmware issues preserved

1. **`0x1F5` is emitted every 5 ms** on the bench. Firmware skips it entirely
   on the first RTD (reset) cycle (`vcComms.cpp:286-292`) and in
   `ERROR_SHUTDOWN` (`vcComms.cpp:314-317`). The Port-A CAN Write path is not
   gated per cycle; adding a per-frame enable is the correct future fix.
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
   `0x400` system-status receive path, so it cannot assert firmware's
   `sys.valid` term. It stands in with two identical bench-plant ramp
   accumulators (`dcLinkAccum12` / `dcLinkAccum34`) and gates the fault on
   `either <= 350`, matching the *structure* of firmware
   `prechargeComplete()` (`vcStateMachine.cpp:131-145`) even though the bench
   models a single bus. The host reference `+virtualvcu/step.m:73-75` is
   stricter: it requires a decoded `0x400` and both pair voltages > 350 V.
   A real dual-pair `0x400` decode is a follow-up once that frame is wired.
10. **Generated-C release**: the vendored allocator C is R2025b-generated and
    the HIL builds under R2024b. The C compiles cleanly (verified for the host
    MEX); the Speedgoat link is covered by the checklist below.
11. **`coder_posix_time.c`** is a portable `clock()` substitution for the
    firmware's STM32 TIM2 timer; the generated code discards `toc`.
12. **Outside RTD** the model's four periodic CAN Write blocks still publish
    disabled zero control payloads. Firmware queues no normal inverter
    control frames outside RTD. In RTD, reset and torque-cycle payload bytes
    are exact.
13. **CAN RX sub-sampling (open item).** The base boundary's Port-A FIFO
    reader publishes one frame's fields per base tick; the chart samples them
    through a 5 ms Rate Transition, so when several Ephorus `0x3X5` frames
    arrive inside one 5 ms window only the last is seen and
    `virtualVcuDeployStep.m` updates at most one corner's retained wheel
    speed per tick. The persistent `wheelSpeedRadS` degrades to stale-but-held
    rather than lost. A 1 ms multi-corner retention/latch subsystem ahead of
    the Rate Transition is the correct fix; it is a Simulink wiring change
    that could not be built or verified in this environment. On the current
    bench there is no wheel-speed feedback source, so this does not affect
    present operation.
14. The base `VC_HIL/build/build_inverter_hil_model.m` builds a real-VCU
    topology; this task is constrained to `virtual-vcu/`, so
    `build_controls_synced_virtual_vcu` builds the base artifact and then
    applies the virtual-VCU overlay. No base-builder file was changed.

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
were run during this sync and passed; steps 3-6 still require a machine with
enough free disk for a full Simulink code-generation (~several GB) and are
**not verified here**.

```matlab
cd('C:\Users\MFE-HPC\Documents\GitHub\HIL-vvcu-sync')
addpath(fullfile(pwd,'virtual-vcu'))
addpath(fullfile(pwd,'virtual-vcu','models'))
addpath(fullfile(pwd,'virtual-vcu','tests'))
addpath(fullfile(pwd,'VC_HIL','build'))

% 1. [RUN, PASSED] Compile the vendored R2025b allocator C under R2024b and
%    exercise it, plus all host-reference behavior tests.
build_controls_model_mex(true);
run_virtual_vcu_tests;                 % 17/17 passed

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
