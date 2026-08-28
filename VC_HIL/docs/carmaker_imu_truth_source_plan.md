# CarMaker as the virtual-IMU truth source — design plan

## 0. Scope, labels, recommendation

**Confirmed — goal.** Replace the toy kinematic vehicle-state estimate that
currently feeds the virtual MTi-680G with live IPG CarMaker vehicle-physics
truth, delivered to the Speedgoat over the existing private channel-1 CAN bus.
The Speedgoat — not CarMaker — stays the sole owner of the MTi wire contract
(IDs, DLC, scale, byte order, mounting rotation, output rates, health words,
dropout injection).

**Confirmed — labels.** Every substantive claim is **Confirmed** (traced to a
source line or cited manual), **Proposed design not built**, or **Open
question**. Matches the convention of
`carmaker_real_vcu_can_interface_plan.md`.

**Confirmed — current state.**
- Virtual IMU: `VC_HIL/imu/` (`imuProtocol.m`, `stepImuSimulation.m`,
  `mountingTransform.m`, `packMti680Frame.m`, `packMti680ScalarFrame.m`,
  `packMti680Payload.m`, `imuScheduler.m`, `imuTxIds.m`, `imuScalarTxIds.m`).
  Runs on the Speedgoat inside `VC_HIL/build/build_inverter_hil_model.m`
  (`Synchronized Sensor Payloads` + `Scalar Sensor Payloads` MATLAB Function
  blocks).
- Vehicle state: `VC_HIL/inverter/state-machine/stepVehicleState.m` — a
  single-track longitudinal model. `longAccel = sum(torqueActualNm) /
  (mass·wheelRadius)`; `speed = ∫`; `yawRate = speed·tan(steer)/wheelbase`.
  Observation vector `[ax 0 0 | 0 0 yawRate | vx 0 0]`, vehicle frame X-forward
  / Y-left / Z-up, yaw rate on **index 6 (Z)** (`stepVehicleState.m:26-47`).
- `mountingTransform` applies the 180-deg-about-Z sensor←vehicle rotation (the
  physical MTi is mounted backwards). `imuProtocol.mounting` is the single
  constant (`imuProtocol.m:55-72`).
- CarMaker (`carmaker/FS_race/src_cm4sl/TorqueVect.mdl`, CM4SL) runs on the
  host PC in **MATLAB R2022a** — not on the Speedgoat. `inverter_hil` builds in
  **R2024b**. `carmaker/config/MFE26_Inverter_CarMaker.dbc` is the shared
  contract across that version boundary.
- CAN topology: two independent IO614 buses. Channel 2 / Port A = VC bus
  (Speedgoat ↔ real VCU; Speedgoat transmits the MTi/LWS frames here). Channel
  1 / Port B = a private CarMaker↔Speedgoat bus over CarMaker's PCAN-USB FD,
  currently carrying only `0x500` `CarMakerPedalDemand` (CarMaker→Speedgoat)
  and `0x501`/`0x502` (Speedgoat→CarMaker). `carmaker/docs/can_setup_walkthrough.md:3-17`.

**Proposed — recommendation.** Extend the proven hand-written PCANIO transmit
path in `carmaker/FS_race/src_cm4sl/IO.c` to send four new cyclic
vehicle-physics frames (`0x503`–`0x506`) on channel 1. On the Speedgoat, add a
physics decoder / coherent-group retainer and a fresh-vs-stale selector that
overrides `stepVehicleState`'s output with CarMaker truth when fresh and falls
back when stale. Everything downstream of the selector is unchanged.

## 0a. Status ledger (last updated 2026-08-27)

All code is committed and pushed to `origin/CAN` (`af58d9e`..`b94ad17`).
`defaultVehicleStateConfig.carMakerTruthEnabled = false`, so nothing below has
changed deployed behaviour yet — the selector still returns the kinematic
estimate byte-for-byte.

### DONE — code (committed, tested where testable)

| Area | What | Commit | Verified |
|---|---|---|---|
| DBC | `0x503`-`0x506` physics frames (3× signed Intel int16 @ 0/16/32, `PhysicsGroupCounter` @48, `PhysicsIntegrity` @56, `GenMsgCycleTime=10`), owner `CarMaker`; header topology comment | `81d5249` | parses; IDs unique |
| SG decode | `rxCAN/decodeCarMakerPhysicsFrame.m` — ID/DLC/extended/RTR/CRC-8-J1850/range checks, LE int16, per-message scale | `9637e80` | `TestCarMakerPhysics` |
| SG retain | `rxCAN/receiveCarMakerPhysics.m` + `carMakerPhysicsSnapshot.m` + `contructors/initialCarMakerPhysicsBank.m` — coherent-group retainer keyed on the mod-256 counter, 30 ms freshness timeout, typed reject codes, accepted/rejected counts | `9637e80` | `TestCarMakerPhysics` (6/6) |
| SG selector | `state-machine/selectVehicleObservation.m` — atomic fresh-CarMaker vs warm-kinematic; `stepVehicleState` physics untouched; default-off gate in `defaultVehicleStateConfig.m` | `9637e80` | `TestCarMakerPhysics` |
| SG model | `build_inverter_hil_model.m` — `CarMaker Pedal Retention` → `CarMaker RX Retention` (one channel-1 FIFO, dispatches `0x500` vs `0x503`-`0x506`), `CarMaker Physics Snapshot RT` rate transition, `selectVehicleObservation` after `stepVehicleState()` in the status cycle | `9637e80` | `TestModelArtifacts` 15/15; full suite 225 pass / 7 pre-existing fail |
| SG model regen | `inverter_hil.slx` / `.sldd` rebuilt via `build_inverter_hil_model(true)` | `9637e80` | regen clean bar IO183 deprecation notices |
| Scalar frames | (prerequisite work) `imuScalarTxIds.m`, `packMti680ScalarPayload.m`, `Scalar Sensor Payloads` block + `0x006/0x005/0x011/0x001` writes | `af58d9e` | full suite |
| CM4SL C | `carmaker/FS_race/src_cm4sl/IO.c` + `User.c` — `MFE_CAN.Physics.*` `DVA_IO_Out` quantities in `User_DeclQuants()`, `MFE_PhysicsRoundSaturate()` + `MFE_SendPhysicsFrame()`, cyclic `0x503`-`0x506` sends in `IO_Out()` after `0x500` sharing one counter | `f73d319` | **not compiled** (needs R2022a); brace-balanced, style-matched |

### DONE — investigation

| Item | Result | Commit |
|---|---|---|
| **A9 — which gyro axis the VCU reads as yaw** | RESOLVED: MFE26-VC `controls` branch `gyroCANRx` → `imu_data.Gyrz` (byte offset 4), `vcComms.cpp` `controls_inputs->yaw_rate = Gyrz`. The HIL's yaw-on-Z (obs index 6) is correct. | `03c7536` |
| Byte order (A1) | VCU decoder reads big-endian — matches. Still unverified vs a *physical* sensor. | `03c7536` |
| VelocityXYZ ID (A3) | Firmware `MTI680G_ID_VELOCITY_RAW 0x076u` — matches. Datasheet still self-contradicts. | `03c7536` |
| IDs / scales / ranges | All match `imuProtocol.m` (`0x034/0x032/0x076`, `2^-8/2^-9/2^-6`, `100/35/500`). | `03c7536` |
| Backwards mount | Firmware-confirmed: `vcComms.cpp` "IMU is placed 180 deg flipped", negates `ax/ay/v_x/v_y`, passes `Gyrz`. HIL transform ∘ firmware compensation = identity. | `03c7536` |
| CAN acceptance filter | `BoardManager_create(0, 1024)` → admits `0x000`-`0x400`. All MTi frames + LWS `0x2B0` pass; LWS config `0x7C0` is dropped in hardware. Old "`0x383`-`0x400` only" note was stale. | `03c7536` |

### LEFT — manual, in order (nothing here is code an agent can write)

1. **`TorqueVect.mdl` CM-Dict wiring (R2022a).** Add Read CM Dict blocks for
   `Sensor.Inertial.Param_B00.{Acc_B,Omega_B,Vel_B}.{x,y,z}` (+ optional
   `Car.{Roll,Pitch,Yaw}`) and Write CM Dict blocks to
   `MFE_CAN.Physics.{Acceleration,AngularRate,Velocity,Euler}.{x,y,z}`, straight
   passthrough. Full step-by-step: `carmaker/docs/carmaker_readcmdict_checklist.md`.
2. **Confirm the exact CarMaker DD quantity spellings** in the R2022a Read CM
   Dict browser (`Acc_B/Omega_B/Vel_B` stems are header-confirmed; the
   `.x/.y/.z` leaves and the `Sensor.Inertial.Param_B00` addressing are not).
3. **Deploy the canonical CM4SL sources and rebuild in R2022a.** Run
   `carmaker/deploy/apply_cm4sl.ps1 -ProjectPath <CarMaker project>`, then build
   the `CarMaker for Simulink.sln` / `Makefile` in R2022a. Full procedure:
   `carmaker/docs/cm4sl_integration.md`. (`GetCRC_J1850_User()` is resolved — it
   is a CarMaker library function from `<E2E.h>`, not a project gap.)
4. **Reconcile `TorqueVect.mdl`.** HIL, IPG-`HEAD`, and IPG-working have diverged
   (176 170 / 177 365 / 176 252 lines). Run a Simulink model comparison in
   R2022a, decide the canonical `.mdl`, commit it to HIL, then deploy with
   `apply_cm4sl.ps1 -IncludeModel`. See `carmaker/docs/cm4sl_integration.md`.
5. **Survey the real MTi mount** — vehicle-frame X/Y/Z from Fr1, and orientation.
   `Sensor.1.pos = 1.3 0 0.15` is an unconfirmed guess; lever-arm terms in
   `Acc_B`/`Vel_B` are only as good as it. Then update the vehicle config.
6. **Confirm `Acc_B` gravity semantics** — a real MTi reports specific force
   (gravity included). CarMaker's plain `Acc_B` should too; `SENS_BODY_FRAME_noGN`
   excludes it. Bench: stationary ⇒ `Acceleration.z ≈ +9.81`.
7. **Axis-sign proof** — isolated positive-axis maneuvers, `_B.x/y/z` match the
   Speedgoat vehicle convention; verify the Euler sequence/wrap before enabling
   `0x506`.
8. **Get `0x503`-`0x506` approved** against the vehicle-wide CAN registry.
9. **Run the section-7 bench acceptance** (capture the frames; counter/CRC/byte
   order; fresh↔stale fallback; fault injection; channel-2 MTi capture; compare
   against a real MTi).
10. **Then** set `defaultVehicleStateConfig.carMakerTruthEnabled = true`,
    re-run `build_inverter_hil_model(true)`, and redeploy to `TargetPC1`.
    Revert with the same two steps and the flag back to `false`.

### LEFT — optional / later

- `0x506` Euler wiring is not required for freshness and the VCU has no Euler
  handler. (Velocity **is** consumed by the controls model — `vcComms.cpp`
  forces `use_imu_vel_x/y = 1.0` every cycle, overriding the `0` default in
  `controls.c` / `CONTROLS.md`; a wrong sign or scale on `0x505` would corrupt
  vehicle control, so treat it as load-bearing.)
- Migrate the CM4SL transmitter to RBS if a supported CarMaker-side physical CAN
  adapter is ever proven (the largest gate below).
- `references/sensors/imu_contract_delta.md` still carries A9 as open — update
  it to point at `protocol.md`.

---

**Confirmed — largest gate (unchanged from the earlier plan).** RBS needs a
*supported* CarMaker-side physical CAN adapter. PCAN-USB FD's RBS binding is
unproven; the documented `CANIf` modules are M51, M410, and vCAN only
(`carmaker/docs/can_setup_walkthrough.md:74-79`;
`carmaker_real_vcu_can_interface_plan.md:15-21`). The `0x500` frame is
transmitted through a hand-written `PCANIO_Send()` helper, not RBS. This plan
follows that precedent; RBS remains a later replacement option only after a
bench proof that it can bind PCAN-USB FD.

---

## 1. CarMaker-side transmit mechanism

### 1.1 PCANIO vs RBS

- **Confirmed — PCANIO is implemented, not planned.** `IO.c` selects
  `pcan_usb`, probes channel values `{0, 1, 0x51}`, configures 1-Mbit/s classic
  CAN, and records interface readiness (`IO.c:66-89`, `IO.c:273-316`).
- **Confirmed — bidirectional use exists.** `IO_In()` drains up to 16 messages
  per cycle and decodes `0x501`/`0x502`; `IO_Out()` builds standard DLC-8
  `0x500`, increments a 4-bit alive counter, computes CRC-8/SAE-J1850, and
  calls `PCANIO_Send()` every tenth 1-ms cycle (`IO.c:424-503`, `IO.c:509-562`).
- **Confirmed — installed API support.** CarMaker 12.0.1 declares the PCAN
  device and classic/FD APIs in `C:/IPG/carmaker/win64-12.0.1/include/pcanio.h:31-70`;
  the host has a detected PCAN-USB FD and PCANBasic DLL
  (`carmaker/docs/can_setup_walkthrough.md:29-34`).
- **Open question — RBS/PCAN binding.** Nothing inspected proves a
  GUI-generated RBS network can bind to the already-open hand-written PCANIO
  channel, or that a supported CarMaker automation path exists to generate RBS
  configuration (`carmaker/docs/can_setup_walkthrough.md:74-79, 97-104`).

**Proposed — decision.** Extend the PCANIO path. Smallest hardware
uncertainty; preserves one host-side CAN owner. **Do not** run PCANIO and RBS
transmitters against the same adapter concurrently (double-open risk).

### 1.2 Source boundary inside CM4SL

**Proposed.** Obtain physics values through `Read CM Dict` blocks in
`TorqueVect.mdl` and expose them to `IO.c` through explicitly declared
`MFE_CAN.Physics.*` Data Dictionary quantities, mirroring the current
`User_DeclQuants()` / `DDefDouble()` pattern (`User.c:240-267`).

---

## 2. CarMaker Data Dictionary quantities

### 2.1 The vehicle already has an inertial sensor

- **Confirmed.** `carmaker/FS_race/Data/Vehicle/Examples_FS/MFE26_V1:914-949`
  defines an **active inertial sensor `Param_B00`**, mounted on `Fr1A`,
  currently at position `[1.3, 0, 0.15]` m, zero rotation,
  calculation mode `Global+Local`.
- **Confirmed — body-sensor field families.** CarMaker's inertial body sensor
  computes `Vel_B[3]`, `Acc_B[3]`, `Omega_B[3]` in its mounted body frame, plus
  `_0` global-frame variants and angular acceleration
  (`C:/IPG/carmaker/win64-12.0.1/include/Vehicle/MBSUtils.h:143-162`).
- **Confirmed — Data Dictionary prefix.** Inertial sensor quantities are
  `Sensor.Inertial.<instance>.*`; the configured instance is `Param_B00`
  (`C:/IPG/carmaker/win64-12.0.1/include/Vehicle/Sensor_Inertial.h:38-44`).

**Proposed — quantities to select in the R2022a `Read CM Dict` browser:**
- `Sensor.Inertial.Param_B00.Acc_B.x / .y / .z`
- `Sensor.Inertial.Param_B00.Omega_B.x / .y / .z`
- `Sensor.Inertial.Param_B00.Vel_B.x / .y / .z`

The `Acc_B` / `Omega_B` / `Vel_B` stems and the instance name are
source-confirmed; the exact `.x/.y/.z` member spelling must be confirmed in the
supported UI before wiring (**Open question**).

### 2.2 Orientation

**Proposed.** Use `Car.Roll`, `Car.Pitch`, `Car.Yaw` (radians, confirmed in
result metadata and `C:/IPG/carmaker/win64-12.0.1/include/Car/Car.h:133-145`).
**Not** `tBdySensor.r_zyx`, which is the configured sensor-to-body mounting
orientation, not the vehicle's live global attitude.

### 2.3 Raw quantities (fallback / cross-check)

- **Confirmed.** `Car.ax`, `Car.ay` (m/s²), `Car.YawRate`, `Car.RollVel`,
  `Car.PitchVel` (rad/s; `Car.h:133-146`), `Car.v` (m/s scalar).
- **Open question.** Raw vertical acceleration `Car.az` did not appear in the
  inspected result quantity list; verify in the CarMaker 12 Data Dictionary
  before use. Vector CG kinematics `v_1`/`a_1` exist in Fr1 in the C API
  (`Car.h:97-130`) but their exact UAQ aliases (`Car.ConBdy1.*` /
  `Car.GenBdy1.*`) must be selected from the R2022a browser, not guessed.

### 2.4 Mounting-rotation hazard

- **Confirmed.** `mountingTransform` negates X/Y and offsets Euler for the
  180-deg-Z mount (`mountingTransform.m:25-42`). If the CarMaker `Param_B00`
  sensor is *also* given the physical 180-deg rotation, the rotation is applied
  twice.

**Proposed.** Keep the CarMaker sensor rotation at `[0 0 0]`. Send
vehicle/Fr1-aligned physical values. The Speedgoat's `imuProtocol.mounting`
remains the single mounting location.

### 2.5 What TorqueVect already reads

- **Confirmed.** `TorqueVect.mdl` already has `Read CM Dict` blocks for wheel
  slips, `Car.v`, `Car.YawRate` (`TorqueVect.mdl:72154-72411`,
  `TorqueVect.mdl:89637-89669`). No inspected block reads the full nine-axis
  IMU physics group.

---

## 3. Frame design — channel 1, CarMaker → Speedgoat

**Confirmed — namespace.** `carmaker/config/MFE26_Inverter_CarMaker.dbc`
contains `0x500`/`0x501`/`0x502` on the private bus; `0x503`–`0x506` are unused
(repo-local audit only, `dbc:137-161`).

**Proposed — four standard classic-CAN frames, DLC 8:**

| ID | Name | Bytes 0–5 | Byte 6 | Byte 7 | Cycle |
|---|---|---|---|---|---|
| `0x503` | `CarMakerPhysicsAcceleration` | `ax, ay, az` | group counter | CRC | 10 ms |
| `0x504` | `CarMakerPhysicsAngularRate` | `wx, wy, wz` | group counter | CRC | 10 ms |
| `0x505` | `CarMakerPhysicsVelocity` | `vx, vy, vz` | group counter | CRC | 10 ms |
| `0x506` | `CarMakerPhysicsEuler` | `roll, pitch, yaw` | group counter | CRC | 10 ms |

- **Proposed — encoding.** Three signed `int16`, little-endian (matches the
  Intel-order DBC convention of `0x500`/`0x501`, `dbc:137-150`;
  `IO.c:455-474`). Unsigned `PhysicsGroupCounter` at bit 48, unsigned
  `PhysicsIntegrity` at bit 56.
- **Proposed — scaling / limits:**

  | Signal | Factor | Encoded range | Speedgoat acceptance gate |
  |---|---:|---:|---:|
  | acceleration | `0.01 m/s²/bit` | ±327.67 | ±100 m/s² (MTi contract) |
  | angular rate | `0.002 rad/s/bit` | ±65.534 | ±35 rad/s (MTi contract) |
  | velocity | `0.01 m/s/bit` | ±327.67 | ±200 m/s (initial) |
  | Euler | `0.0001 rad/bit` | ≈±3.2767 | roll/yaw ±π, pitch ±π/2 |

  Acceleration/rate gates align with `imuProtocol.m:15-27`.
- **Proposed — physical contract.** SI, **vehicle / Fr1 frame**, not
  MTi-scaled or sensor-frame. Euler stays in **radians** on this private
  contract; degrees conversion happens only at the existing MTi boundary.
- **Proposed — group counter.** Byte 6 carries one modulo-256 counter,
  identical across all frames sampled in one CarMaker step. The Speedgoat
  publishes a new observation only when `0x503`/`0x504`/`0x505` share a
  counter. Never mix acceleration from counter N with velocity from N−1.
- **Proposed — integrity.** Byte 7 is CRC-8/SAE-J1850 over bytes 0–6 (poly
  `0x1D`, init `0xFF`, non-reflected, xorout `0xFF`). Unlike `0x500`, each
  physics message is one member of a multi-frame atomic snapshot; a counter +
  CRC is warranted. The `0x500` implementation already provides this CRC family
  (`IO.c:545-558`, `carmaker/docs/can_setup_walkthrough.md:81-95`).
- **Proposed — Euler optionality.** Implement `0x506` in the DBC and
  transmitter, but do **not** require it for freshness: the VCU has no MTi
  Euler handler and `imuProtocol.defaultOutputRateHz.eulerAngles` is 0 Hz
  (`imuProtocol.m:35-39, 74-78`).
- **Open question — ID approval.** Reserve `0x503`–`0x506` only after checking
  the complete private-bus capture and the organizational CAN registry. A
  repo-local collision audit is not vehicle-wide proof
  (`carmaker_real_vcu_can_interface_plan.md:92-96`).

**Proposed — DBC additions.** Four `BO_` entries owned by `CarMaker`, DLC 8,
three signed Intel `int16` at bits 0/16/32, unsigned `PhysicsGroupCounter` at
48, unsigned `PhysicsIntegrity` at 56. `GenMsgCycleTime = 10` for all four.
`CM_ BO_` comments defining the Fr1 frame, scale, counter coherency rule, and
J1850 coverage.

---

## 4. Speedgoat-side receive + integration

- **Confirmed — reusable hardware path.** `IO614 CarMaker FIFO Read` pops one
  channel-1 message per 1-ms tick and exposes ID / format / DLC / data through
  `CarMaker Rx Bus Selector` and global Gotos
  (`build_inverter_hil_model.m:710-743`).
- **Proposed — do not add a second FIFO Read block.** Two readers on one FIFO
  consume each other's messages. Extend the existing channel-1 retention
  consumer so the single stream dispatches `0x500` → pedal decoder and
  `0x503`–`0x506` → the new physics retainer.
- **Proposed — block placement.** In `buildSystemStatus()`, broaden
  `CarMaker Pedal Retention` into a `CarMaker RX Retention` block at the same
  1-ms location (construction `build_inverter_hil_model.m:325-356`; generated
  function `:1362-1400`). It takes the existing six `CarMakerRx*` signals and
  emits both the unchanged pedal vector and a physics snapshot.
- **Proposed — decoded shape:**

  ```
  physics = [ax ay az wx wy wz vx vy vz roll pitch yaw ageMs fresh complete counter]
  ```

  First 12 values `double`, vehicle-frame SI, Euler in radians; `fresh`,
  `complete`, counter status derived atomically. A fixed vector (not a struct)
  matches the generated model's interface style.
- **Proposed — validation.** Reject wrong ID/DLC, extended/RTR frames, bad
  CRC, non-finite decoded values, physical-range violations, duplicate /
  out-of-order counters, incomplete counter groups. Keep accepted/rejected
  counts and a last-reject code.
- **Proposed — freshness.** 30-ms timeout (three missed 10-ms groups).
  Acquisition needs one complete valid counter group; continued ownership needs
  complete advancing groups. Do not refresh age from one member of a partial
  group. Mirrors the pedal ownership contract
  (`VC_HIL/inverter/rxCAN/receivePedalDemandFrame.m:12-20`,
  `pedalDemandSnapshot.m:4-10`).
- **Proposed — selector.** Keep running `stepVehicleState()` so the fallback
  integrator stays warm. Add a separate
  `selectVehicleObservation(kinematic, carMakerSnapshot)` invoked immediately
  after `stepVehicleState()` in the status-cycle script
  (`build_inverter_hil_model.m:1530-1537`). It atomically picks fresh-complete
  CarMaker `[a, ω, v]` or the kinematic 1×9 estimate. **Do not** modify
  `stepVehicleState`'s physics.
- **Confirmed — downstream is preserved.** `Synchronized Sensor Payloads`
  consumes the 1×9 contract at 5 ms (`:827-859`, `:1546-1565`).
  `stepImuSimulation` applies `mountingTransform` before packing
  (`stepImuSimulation.m:54-72`). Scale/range gates stay in `imuProtocol`
  (`imuProtocol.m:12-27`). The 100-Hz scheduler, four scalar group frames, and
  vector dropout are independent of the upstream state source
  (`imuScheduler.m:8-27`, `build_inverter_hil_model.m:910-979`).
- **Open question — Euler into the deployed model.** The deployed observation
  is 1×9; host `stepImuSimulation` accepts optional `eulerAnglesDeg`
  (`stepImuSimulation.m:82-86`). If `0x506` is enabled later, extend the
  selected-state interface deliberately — do not silently append fields to the
  asserted 1×9 (`build_inverter_hil_model.m:1558-1564`).

---

## 5. Timing and frames of reference

### 5.1 Timing

- **Confirmed.** `IO_In()`/`IO_Out()` treat `CycleNo` as incrementing every
  1-ms loop; `0x500` uses `CycleNo % 10` (`IO.c:509-540`). Speedgoat channel 1
  drained per 1-ms tick (`build_inverter_hil_model.m:710-723`). Internal
  plant/status and shared vehicle-state cycle is 5 ms via an explicit rate
  transition (`:282-307, 358-360`). MTi vector rate 100 Hz → scheduler base
  tick 10 ms (`imuProtocol.m:74-78`, `imuScheduler.m:8-12`).
- **Proposed — transmit cadence.** Sample and send the physics group every 10
  CarMaker cycles, after the current step's inertial quantities update. Send
  the frames consecutively with one shared counter.
- **Proposed — latency budget.** CarMaker sampling 0–1 ms + four frames
  ≈0.5 ms wire + Speedgoat FIFO pickup 0–1 ms + 5-ms status alignment 0–5 ms +
  100-Hz MTi alignment 0–10 ms ≈ **2–17 ms truth-to-MTi, normally <20 ms**.
  Analytical bound — measure it, do not treat it as bench proof.
- **Proposed — coherency.** Timestamp freshness at completion of the required
  three-frame counter group; keep the CarMaker sample counter for diagnostics.

### 5.2 Frames of reference

- **Confirmed.** Speedgoat shared state is vehicle X-forward / Y-left / Z-up,
  yaw about +Z (`stepVehicleState.m:26-44`). CarMaker `v_1`/`a_1` and
  body-sensor `_B` values are Fr1/body coordinates (`Car.h:97-130`,
  `MBSUtils.h:148-157`); roll/pitch/yaw use ISO-8855 terminology and `YawRate`
  is yaw velocity (`Car.h:133-146`).
- **Confirmed.** Physical MTi mount: vehicle→backward-sensor is `[-1,-1,+1]`;
  yaw rate stays on Z and is sign-invariant under the 180-deg-Z rotation
  (`imuProtocol.m:55-72`, `stepVehicleState.m:38-47`).
- **Proposed — sign proof.** Before integration, run isolated positive-axis
  maneuvers and verify `_B.x/y/z` match the Speedgoat convention. Header frame
  annotations establish locality, not a complete sign proof.
- **Open question — A9.** Repo simulation establishes physical yaw is the Z
  component published at MTi byte offset 4, but not which decoded gyro axis the
  deployed MFE26-VC control algorithm consumes. Resolve against current VC
  firmware or a bench axis-injection test.

---

## 6. Concrete change list

### 6.1 R2022a CM4SL / CarMaker side (rebuild in R2022a per `CM4SL_CAN_apply_note.md`)

- **Proposed — vehicle config.** Set `Param_B00` position to the surveyed MTi
  location; keep `Fr1A`, zero rotation, `Global+Local`. Save through CarMaker
  tooling (`MFE26_V1:929-949`).
- **Proposed — `TorqueVect.mdl`.** Via R2022a / CarMaker-supported model
  tooling only (no hand-edit of `.mdl`), add `Read CM Dict` blocks for the nine
  inertial `_B` quantities and optionally `Car.Roll/Pitch/Yaw`; route to
  declared interface quantities or an output consumed by host C. Pattern:
  `TorqueVect.mdl:72114-72612, 89637-89669`.
- **Proposed — `User.c` / `User.h`.** Declare the selected physics values as
  stable `MFE_CAN.Physics.*` Data Dictionary quantities via `DDefDouble()`
  (`User.c:240-267`).
- **Proposed — `IO.c`.** Add saturation/rounding helpers, group counter, CRC,
  and cyclic sends for `0x503`–`0x506`. Preserve the current PCAN init and
  shared channel ownership (`IO.c:66-89, 539-560`).
- **Confirmed — rebuild.** Apply `IO.c`/`User.c` back to the live IPG-MFE
  project and rebuild the CM4SL executable with the CarMaker for Simulink
  solution or the `src_cm4sl` Makefile in **R2022a**, not R2024b
  (`CM4SL_CAN_apply_note.md:1-6`).

### 6.2 R2024b `inverter_hil` / Speedgoat side (model regen)

- **Proposed — DBC.** Add `0x503`–`0x506`, signal definitions, `CM_` comments,
  and 10-ms cycle attributes to `carmaker/config/MFE26_Inverter_CarMaker.dbc`.
- **Proposed — new functions** (rigor equal to
  `decodePedalDemandFrame` / `receivePedalDemandFrame`):
  - a physics-frame decoder (`decodeCarMakerPhysicsFrame`): CRC, range,
    ID/DLC, sign/scale;
  - a coherent-group retainer (`receiveCarMakerPhysics` +
    `carMakerPhysicsSnapshot`): counter matching, completeness, age;
  - `selectVehicleObservation(kinematic, snapshot)`: atomic fresh vs warm
    fallback.
- **Proposed — `build_inverter_hil_model.m`.** Extend the channel-1 retention
  block (no second FIFO reader); add one 1-ms→5-ms rate transition for the
  physics snapshot; invoke the selector right after `stepVehicleState()`.
  Integration points: `:325-360, 710-743, 1530-1537`.
- **Proposed — regen.** Re-run `build_inverter_hil_model(true)` in R2024b;
  rebuild/deploy the Simulink Real-Time application.
- **Proposed — tests.** Golden-vector decoder tests; CRC / counter / wrap;
  partial-group and reordered-frame; stale↔fresh transition; range /
  saturation; selector fallback; generated-model topology / rate assertions;
  end-to-end mounting (CarMaker vehicle +X/+Y/+Z → expected backward-mounted
  MTi payload). Existing IMU protocol / scheduler / concurrency / artifact /
  dropout suites must still pass, except `TestModelArtifacts` topology
  assertions that must recognize the new retention/selector blocks
  (`VC_HIL/tests/inverter_hil/TestSensorProtocol.m`, `TestSensorConcurrency.m`,
  `TestModelArtifacts.m`, `TestCarMakerTelemetry.m`).

---

## 7. Risks, open questions, bench proof

**Open questions to close before trusting CarMaker truth:**
1. Exact `Sensor.Inertial.Param_B00.{Acc_B,Omega_B,Vel_B}.{x,y,z}` UAQ spellings
   (confirm in the R2022a `Read CM Dict` selector).
2. Accelerometer semantics — does `Acc_B` give specific force (gravity) like a
   real MTi? Config is `Global+Local`; `SENS_BODY_FRAME_noGN` exists
   (`MBSUtils.h:133-138`, `MFE26_V1:949`). Compare stationary level, pitched
   stationary, and slope cases against a real MTi.
3. Real MTi mount survey — vehicle-frame X/Y/Z from Fr1, and whether Fr1A / body
   flexibility is the right attachment. The `[1.3, 0, 0.15]` is not confirmed
   as the surveyed location.
4. Axis signs and Euler sequence / wrap — prove positive roll, pitch, yaw,
   acceleration, velocity individually before enabling `0x506`.
5. **A9** — which MTi gyro field the real VCU uses for yaw (inject one nonzero
   axis at a time, observe the VCU's decoded/control signal).
6. `0x503`–`0x506` reservation against the complete private-bus namespace.
7. 30-ms freshness timeout vs worst host scheduling jitter.
8. PCAN transmit burst — five host frames per 10 ms (`0x500` + four physics).
   Verify no driver queueing, reordering, or send errors; log `PCANIO_Send()`
   failures and capture bus timestamps.

**Confirmed — pre-existing concern.** Historical Speedgoat diagnostics showed
unexplained `busLoad=88`, overrun, and bus-warning on the (then bridged) bus;
this now belongs mainly to channel 2 and is independent of this private-bus
extension (`carmaker/docs/can_setup_walkthrough.md:36-45`).

**Confirmed — non-claim.** Passing CarMaker-through-Speedgoat tests cannot
resolve the MTi real-sensor byte order or the `0x075`/`0x076` velocity-ID
discrepancy — the Speedgoat and the VCU share the same assumptions
(`imuProtocol.m:24-27, 86-94`).

**Mandatory bench acceptance sequence:**
1. Capture `0x503`–`0x506`; verify 10-ms period, counter equality, byte order,
   CRC, no PCAN errors.
2. Compare decoded Speedgoat values with CarMaker Data Dictionary traces for
   steady, transient, and combined-axis maneuvers.
3. Stationary, pitch/slope, constant-yaw-rate, rapid-yaw tests — validate
   gravity and lever-arm / centripetal behavior.
4. Pause/disconnect CarMaker; demonstrate fallback within the timeout with no
   discontinuous unsafe output and no partial-group acceptance.
5. Inject CRC corruption, missing members, duplicate counters, reordering,
   range overflow, counter wrap.
6. Capture channel-2 MTi frames; prove the Speedgoat alone owns
   `0x032`/`0x034`/`0x076` and the scalar frames.
7. Compare against a real MTi at known orientations — settle byte order, signs,
   gravity convention, and A9.

---

## 8. Recommended implementation sequence

1. Survey the physical MTi position / orientation; resolve the VCU yaw-axis A9
   item.
2. In R2022a, confirm the exact inertial UAQs and log them with no CAN changes;
   validate gravity, frame, and lever-arm semantics.
3. Approve `0x503`–`0x506`; freeze the DBC contract, golden vectors, CRC, and
   timeout.
4. Extend the PCANIO transmitter; rebuild CM4SL in R2022a.
5. Implement the Speedgoat decoder, coherent-group retainer, and fresh/stale
   selector with unit tests.
6. Regenerate and build `inverter_hil` in R2024b; keep all MTi packing,
   mounting, scheduling, scalar, and dropout logic downstream.
7. Complete the bench acceptance sequence before enabling CarMaker truth by
   default or trusting it for closed-loop vehicle-control validation.

---

*Investigation basis: Codex read-only investigation, 2026-08-27, against branch
`CAN` and `C:/IPG/carmaker/win64-12.0.1/`. Companion documents:
`carmaker_real_vcu_can_interface_plan.md`, `speedgoat_ipg_integration.md`,
`carmaker/docs/can_setup_walkthrough.md`.*
