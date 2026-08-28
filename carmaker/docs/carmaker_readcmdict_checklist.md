# R2022a checklist — TorqueVect.mdl Read/Write CM Dict wiring for the CarMaker physics frames

Companion to `VC_HIL/docs/carmaker_imu_truth_source_plan.md` (section 2, 6.1)
and `carmaker/docs/cm4sl_integration.md`. This is the
step-by-step a human executes in **MATLAB R2022a** to feed the CarMaker inertial
sensor into the four new `0x503`–`0x506` CAN frames sent by
`physics_can_snippet.c`.

Do this **after** the `physics_can_snippet.c` additions are applied to
`IPG-MFE/FCM_Projects/FS_race/src_cm4sl/{IO.c,User.c,User.h}` and BEFORE the
CM4SL rebuild — the model must be saved/regenerated first, then CM4SL rebuilt
(`CM4SL_CAN_apply_note.md`).

All `.mdl` edits are done through the Simulink GUI / CarMaker-for-Simulink
library only. Never hand-edit `TorqueVect.mdl`.

---

## 0. Prerequisites

1. MATLAB **R2022a** (not the R2024b `inverter_hil` environment).
2. Add `Documents/GitHub/MFE25-Controls/{01 Vehicle Model, 02 Controls Model}` to
   the path and run the `Control_FL_Combined_Run.m` parameter sections, then add
   `IPG-MFE/FCM_Projects/FS_race/src_cm4sl` to the path and run `cmenv.m`
   (choose "change folder"), wait for "Done." — the working procedure in
   `speedgoat_ipg_integration.md` / memory `ipg_carmaker_hil_setup.md`.
3. Open `TorqueVect.mdl`. Open the CarMaker GUI from the top-level tab.
4. Load the **`Examples_FS/MFE26_V1`** car (the one carrying the inertial
   sensor — see step 1 below).
5. The `IPG-MFE` `src_cm4sl` worktree is currently **dirty** (`IO.c`, `User.c`,
   `TorqueVect.mdl` have uncommitted changes). Reconcile or stash those first so
   this work lands on a known base.

---

## 1. Confirm the inertial sensor exists and is the right one

Open `Data/Vehicle/Examples_FS/MFE26_V1` (or Vehicle → Sensors in the GUI).
Confirmed values (2026-08-27):

```
Sensor.Param.1.Type = Inertial
Sensor.Param.1.Name = Param_B00
Sensor.1.name       = Param_B00
Sensor.1.Ref.Param  = 1
Sensor.1.Mounting   = Fr1A
Sensor.1.pos        = 1.3 0 0.15      # metres, in Fr1A
Sensor.1.rot        = 0.0 0.0 0.0     # sensor axes aligned with Fr1A
Sensor.1.Active     = 1
Sensor.1.CalcClass  = Global+Local
```

(`Sensor.0` / `VehSensor-0` is the side-slip-angle sensor, `Ref.Param = 0`,
type `SAngle` — **not** the inertial one. Don't confuse them.)

- **KEEP `Sensor.1.rot = 0 0 0`.** Do NOT set it to the physical 180° mounting.
  The Speedgoat owns the sensor←vehicle rotation in one place
  (`imuProtocol.mounting`); rotating here too would apply it twice.
- **`Sensor.1.pos = 1.3 0 0.15` is an unconfirmed assumption.** Until the real
  MTi mount is surveyed, either (a) leave it and accept approximate lever-arm
  terms, or (b) set it to the CG-ish reference if lever-arm fidelity matters more
  than realism. Note the choice in the TestRun.
- **Gravity:** a real MTi accelerometer reports specific force (gravity
  included). CarMaker's plain body-frame acceleration (`Acc_B`) includes gravity;
  the `SENS_BODY_FRAME_noGN` variant excludes it (`MBSUtils.h:133-138`). Use the
  gravity-inclusive one and confirm on the bench (stationary ⇒ ≈ +9.81 on the
  vertical axis).

---

## 2. Quantities to READ (Read CM Dict, one block per scalar, or vector where the block allows)

Sensor DD prefix is `Sensor.Inertial.<name>.*` with `<name> = Param_B00`. The
**leaf spellings below are from the C struct `tBdySensor` (`MBSUtils.h:148-158`)
and must be confirmed in the R2022a Read CM Dict quantity browser** (expand
`Sensor` → `Inertial` → `Param_B00`). If the browser exposes 3-vector
quantities, read the vector; otherwise read `.x` / `.y` / `.z` separately.

| # | CarMaker quantity (confirm spelling in browser) | Unit | Goes to |
|---|---|---|---|
| 1 | `Sensor.Inertial.Param_B00.Acc_B.x` | m/s² | `MFE_CAN.Physics.Acceleration.x` |
| 2 | `Sensor.Inertial.Param_B00.Acc_B.y` | m/s² | `MFE_CAN.Physics.Acceleration.y` |
| 3 | `Sensor.Inertial.Param_B00.Acc_B.z` | m/s² | `MFE_CAN.Physics.Acceleration.z` |
| 4 | `Sensor.Inertial.Param_B00.Omega_B.x` | rad/s | `MFE_CAN.Physics.AngularRate.x` |
| 5 | `Sensor.Inertial.Param_B00.Omega_B.y` | rad/s | `MFE_CAN.Physics.AngularRate.y` |
| 6 | `Sensor.Inertial.Param_B00.Omega_B.z` | rad/s | `MFE_CAN.Physics.AngularRate.z` |
| 7 | `Sensor.Inertial.Param_B00.Vel_B.x` | m/s | `MFE_CAN.Physics.Velocity.x` |
| 8 | `Sensor.Inertial.Param_B00.Vel_B.y` | m/s | `MFE_CAN.Physics.Velocity.y` |
| 9 | `Sensor.Inertial.Param_B00.Vel_B.z` | m/s | `MFE_CAN.Physics.Velocity.z` |
| 10 (opt) | `Car.Roll` | rad | `MFE_CAN.Physics.Euler.x` |
| 11 (opt) | `Car.Pitch` | rad | `MFE_CAN.Physics.Euler.y` |
| 12 (opt) | `Car.Yaw` | rad | `MFE_CAN.Physics.Euler.z` |

- `Car.Roll` / `Car.Pitch` / `Car.Yaw` are **confirmed** (radians;
  `Car.h:133-145` and CarMaker result metadata). They are the vehicle's live
  global attitude — do **not** use `Sensor.Inertial.Param_B00.r_zyx`, which is
  the sensor→body mounting orientation.
- `Acc_B` / `Omega_B` / `Vel_B` **stems are confirmed** in the header; only the
  `.x/.y/.z` leaf naming and the exact `Sensor.Inertial.Param_B00` addressing
  need the browser (CM 12 sometimes indexes by instance number, e.g.
  `Sensor.Inertial.1.*`).
- Frames of reference: `Acc_B/Omega_B/Vel_B` are in the sensor body frame `FrB`
  (= Fr1A here, since `rot = 0`). CarMaker uses ISO-8855 (X forward, Y left, Z
  up), matching `stepVehicleState.m`. So axis 1 → vehicle X (longitudinal),
  axis 2 → Y (lateral), axis 3 → Z (vertical). Send these **raw, unrotated** —
  the Speedgoat's `mountingTransform` does the 180°-Z flip.

Existing model reference: `TorqueVect.mdl` already has ~24 "Read CM Dict" blocks
(e.g. for `Car.YawRate`, `Car.v`, wheel slips). Copy one and change its
quantity.

---

## 3. Quantities to WRITE (Write CM Dict)

Target: the 12 `DVA_IO_Out` quantities `physics_can_snippet.c` registers in
`User_DeclQuants()`:

```
MFE_CAN.Physics.Acceleration.x / .y / .z     unit m/s2
MFE_CAN.Physics.AngularRate.x  / .y / .z     unit rad/s
MFE_CAN.Physics.Velocity.x     / .y / .z     unit m/s
MFE_CAN.Physics.Euler.x        / .y / .z     unit rad
```

They do not exist in the dictionary until the modified `User.c` is compiled, so
the browser will not list them yet. **Type the quantity name into the Write CM
Dict block by hand** (the block accepts a free-text quantity string), exactly as
above. Add one Write CM Dict block per scalar (12), or use vector Write CM Dict
if available. `TorqueVect.mdl` already has a "Write CM Dict" block to copy.

---

## 4. Wiring

For each row in the step-2 table:

```
[Read CM Dict: Sensor.Inertial.Param_B00.Acc_B.x] --> [Write CM Dict: MFE_CAN.Physics.Acceleration.x]
```

No scaling, no rotation, no offset — a straight passthrough. If you want a
single tidy subsystem, put all 12 pairs inside a new subsystem
`CarMaker Physics -> MFE_CAN` at the top level of `TorqueVect.mdl`, next to the
existing CM-Dict wiring.

Euler (rows 10-12) is **optional**: `0x506` is not required for freshness and
the VCU has no MTi-Euler handler. Wire it only if you want it for logging.

---

## 5. Sample time

Set every Read CM Dict and Write CM Dict block to the **CM4SL model base step**
(inherited `-1` is fine; the model runs at 1 ms). `IO_Out()` samples the
`MFE_CAN_Physics*` C globals and sends the four CAN frames every 10th 1-ms cycle
(10 ms), so the CM-Dict blocks running at 1 ms just keep the globals current.

---

## 6. Save, regenerate, rebuild

1. `Ctrl+S` in Simulink to save `TorqueVect.mdl` through supported tooling.
2. If the CM4SL workflow requires it, run the model-update / publish step
   (`ModelUpdate_CM12.m` / `publish_changes.m` under `src_cm4sl/ModelUpdate/`) so
   the generated wrapper picks up the new blocks.
3. Rebuild the CarMaker-for-Simulink executable in **R2022a**: open
   `src_cm4sl/CarMaker for Simulink.sln` or run the `src_cm4sl` `Makefile`
   (`CM4SL_CAN_apply_note.md`). Not the R2024b environment.

---

## 7. Verification (no CAN yet)

Before trusting the CAN path:

1. In the CarMaker GUI, add `MFE_CAN.Physics.Acceleration.x` … `Euler.z` to a
   quantity plot / DVA output and run a maneuver.
2. Confirm each `MFE_CAN.Physics.*` value tracks the corresponding
   `Sensor.Inertial.Param_B00.*` value with no lag/scale/sign error.
3. **Stationary level test:** `MFE_CAN.Physics.Acceleration.z` should read
   ≈ +9.81 (gravity present). If it reads ≈ 0, you picked the `noGN` variant —
   switch to the gravity-inclusive one.
4. **Sign checks:** brake ⇒ `Acceleration.x` negative; left turn ⇒
   `AngularRate.z` positive and `Acceleration.y` positive (ISO-8855). Compare
   against `Car.ax`, `Car.YawRate`.
5. Only then apply the `IO.c` sender, rebuild, and move to the plan's §7 bench
   acceptance (capture `0x503`-`0x506`, counter/CRC/byte-order, fallback, fault
   injection).

---

## 8. Gotchas

- **Quantity name drift.** If the browser shows `Sensor.Inertial.1.*` (index)
  rather than `Sensor.Inertial.Param_B00.*` (name), use whatever the browser
  actually lists — the physics_can_snippet target names (`MFE_CAN.Physics.*`)
  are what must stay exact, not the CarMaker source names.
- **`DVA_IO_Out` vs `DVA_IO_In`.** The existing `MFE_CAN.Inverter*` quantities
  are `DVA_IO_In` (IO writes, model reads). The new `MFE_CAN.Physics.*` are
  `DVA_IO_Out` (model writes, IO reads) — that is why these use **Write** CM
  Dict, not Read.
- **Don't rotate.** Neither the CarMaker sensor (`rot = 0 0 0`) nor these blocks
  apply the 180° mount. That lives once in `imuProtocol.mounting` on the
  Speedgoat.
- **Mount position is a guess.** `Sensor.1.pos = 1.3 0 0.15` is unconfirmed;
  lever-arm terms in `Acc_B`/`Vel_B` are only as good as that number.
- **Two MATLAB versions.** This is all R2022a. The Speedgoat side
  (`build_inverter_hil_model.m`, the decoder, the selector) is R2024b and is
  already committed on branch `CAN` (`9637e80`), gated off by
  `defaultVehicleStateConfig.carMakerTruthEnabled = false`.

---

## 9. The whole passthrough set is scripted — prefer the script

Everything in sections 1-8 above, plus the Fanatec steering passthrough and the
two validity writers, is built in one shot by
`carmaker/FS_race/src_cm4sl/apply_torquevect_cm_truth.m` (R2022a):

```matlab
cd  <repo>\carmaker\FS_race\src_cm4sl\vehicle_models
cmenv
load_system('TorqueVect')
apply_torquevect_cm_truth('Model', 'TorqueVect')
```

It adds the port-free `MFE_CAN CarMaker Truth` subsystem — thirteen straight
Read CM Dict → Write CM Dict passthroughs and two Constant → Write CM Dict
validity writers — and is rerunnable with no duplicate blocks or lines. The
hand-wiring steps above remain accurate if you need to inspect or repair one
chain, but the script is the canonical route and is what the committed
`TorqueVect.mdl` was built with.

### Steering (0x507)

| Source | Unit | Target |
|---|---|---|
| `Steer.WhlAng` | `rad` | `MFE_CAN.Steering.WheelAngleRad` |

A **straight passthrough** — no `180/pi` Gain, no Saturation. Radians is the
`0x507` wire unit, and the Speedgoat converts to degrees once, immediately
before Bosch LWS encoding. No angular-speed quantity is transported: the
Speedgoat derives Bosch `LWS_SPEED` from successive 10 ms samples of this angle.

`Steer.WhlAng` is confirmed present with unit `rad` in
`C:\IPG\carmaker\win64-12.0.1\CM4SL\startup.dict`. It is the **applied**
steering-wheel position, after the CarMaker cockpit has scaled the active
Fanatec `Device.0` axis 0. Do not substitute a road-wheel angle
(`Car.SteerAngleFL` / `.FR`), the IPGDriver output, or vehicle yaw.

### Validity

| Source | Target |
|---|---|
| Constant `1` | `MFE_CAN.Physics.Valid` |
| Constant `1` | `MFE_CAN.Steering.Valid` |

These live in the same subsystem as the passthroughs, so they are raised if and
only if that subsystem has executed. `IO.c` refuses to transmit `0x503`-`0x507`
while they are zero — which is what stops an unedited model from putting a
stream of CRC-valid, counter-advancing, all-zero frames on the bus that look
exactly like a stationary, straight-ahead vehicle.

Full signal path, sign convention, provisional CAN ID, and the Speedgoat side
(shipping in manual mode, `defaultVehicleStateConfig.steeringSourceMode = 0`):
`VC_HIL/docs/carmaker_fanatec_lws_steering.md`.
