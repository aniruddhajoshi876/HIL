# Fanatec steering wheel → CarMaker → Bosch LWS `0x2B0`

How the physical Fanatec steering wheel drives the emulated Bosch LWS the real
MFE26-VC reads. Companion to `carmaker/docs/cm4sl_integration.md` (the
CarMaker↔Speedgoat bus contract) and `VC_HIL/steering-sensor/protocol.md` (the
independent Bosch LWS contract).

---

## 1. The signal path, with units and signs at every stage

```
Fanatec wheel
  │  physical hand angle
  ▼
CarMaker driver / vehicle-control model
  │  CM Data Dictionary quantity  DM.Steer.Ang            [rad]  left-hand +
  │  (see §4 for the quantity choice — CONFIRM against this rig)
  ▼
TorqueVect.mdl  ── subsystem "MFE_CAN Driver Steering" (built by
                   carmaker/FS_race/src_cm4sl/apply_torquevect_steering.m)
  │  Read CM Dict  DM.Steer.Ang                           [rad]
  │  Gain  180/pi                (rad → deg, visible, no magic constant)  [deg]
  │  Gain  +1                    (sign; CarMaker & Bosch LWS are both
  │                               left-hand-positive, so no flip)         [deg]
  │  Saturation  [-780, +780]    (Bosch LWS measuring range)              [deg]
  │  Write CM Dict  MFE_CAN.Driver.SteeringAngleDeg                       [deg]
  │  (same chain for DM.Steer.AngVel → MFE_CAN.Driver.SteeringSpeedDegPerSec,
  │   Gain 180/pi, saturate [-3600, +3600] deg/s)
  ▼
IO.c  IO_Out()  (carmaker/FS_race/src_cm4sl/src/IO.c)
  │  samples the two MFE_CAN.Driver.* dictionary quantities every 10th 1-ms
  │  cycle (100 Hz), right after the 0x503–0x506 physics group
  │  packs internal transport frame  0x507 CarMakerDriverSteering:
  │    bytes 0-1  SteeringWheelAngleDeg        int16 LE, 0.1 deg/bit
  │    bytes 2-3  SteeringWheelSpeedDegPerSec  int16 LE, 0.5 (deg/s)/bit
  │    bytes 4-5  reserved, zero
  │    byte  6    own alive counter, mod 256  (NOT the physics group counter)
  │    byte  7    CRC-8/SAE-J1850 over bytes 0-6  (poly 0x1D, init 0xFF,
  │                non-reflected, xorout 0xFF)
  │  PCAN-USB FD → IO614 channel 1 / Port B  (the CarMaker bus)
  ▼
Speedgoat  CarMaker RX Retention   (1 ms, sole channel-1 FIFO consumer)
  │  VC_HIL/inverter/rxCAN/decodeCarMakerSteeringFrame.m  — validate + decode
  │  VC_HIL/inverter/rxCAN/receiveCarMakerSteering.m      — retain latest valid,
  │                                                          prove counter +1
  │  VC_HIL/inverter/rxCAN/carMakerSteeringSnapshot.m     — fresh = value AND
  │       age ≤ carMakerSteeringFreshnessMs (30 ms) AND counter advancing
  ▼
Speedgoat  Steering Source Select  (1 ms, inside "Ephorus System Status")
  │  VC_HIL/inverter/state-machine/selectSteeringSource.m
  │  enabled + fresh   → CarMaker 0x507 angle      (source 1)   [deg]
  │  enabled + stale   → GUI steering dial         (source 2)   [deg]
  │  disabled          → GUI steering dial         (source 0)   [deg]
  │  output saturated to [-780, +780] deg on every path
  │  published on global Goto  HILSelectedSteeringAngleDeg
  ▼
Speedgoat  Synchronized Sensor Payloads  (5 ms; LWS transmits every 2nd tick
  │                                        → 100 Hz / 10 ms)
  │  the SELECTED angle replaces the raw GUI dial value here and in the shared
  │  vehicle state (stepVehicleState → MTi yaw). LWS_SPEED is derived on the
  │  Speedgoat from successive 10 ms selected-angle samples (init-safe,
  │  clamped to 1016 deg/s), NOT from the 0x507 speed field.
  │  packLwsPayload → CAN Pack 0x2B0
  │    bytes 0-1  LWS_ANGLE int16 LE, 0.1 deg/count       (Bosch, left-hand +)
  │    byte  2    LWS_SPEED uint8, 4 deg/s per count, 0..254, 0xFF = invalid
  │    byte  3    status: bit2 TRIM, bit1 CAL, bit0 OK  (calibrated = 0x07)
  │    byte  4    reserved
  │  DLC 5, 100 Hz
  ▼
Speedgoat  IO614 channel 2 / Port A  (the VC bus)
  ▼
real MFE26-VC   (reads 0x2B0 as its steering-wheel angle sensor)
```

The Speedgoat — not CarMaker — owns Bosch LWS packing, status bits, calibration
state, scheduling, sentinels, dropout, stale behaviour, malformed-DLC injection
and invalid-status injection. `0x2B0` is transmitted only on channel 2. `0x507`
is received only on channel 1 and is never forwarded to the VC bus.

---

## 2. Canonical file locations (HIL repo)

| Concern | File |
|---|---|
| Transport frame sender | `carmaker/FS_race/src_cm4sl/src/IO.c` (`MFE_SendSteeringFrame`, called in `IO_Out()`) |
| Dictionary quantity registration | `carmaker/FS_race/src_cm4sl/src/User.c` (`User_DeclQuants`, `MFE_CAN.Driver.SteeringAngleDeg` / `.SteeringSpeedDegPerSec`, `DVA_IO_Out`) |
| TorqueVect.mdl model-edit script | `carmaker/FS_race/src_cm4sl/apply_torquevect_steering.m` |
| CAN contract | `carmaker/config/MFE26_Inverter_CarMaker.dbc` (`BO_ 1287 CarMakerDriverSteering`) |
| Transport decode | `VC_HIL/inverter/rxCAN/decodeCarMakerSteeringFrame.m` |
| Retainer | `VC_HIL/inverter/rxCAN/receiveCarMakerSteering.m`, `VC_HIL/inverter/contructors/initialCarMakerSteeringBank.m` |
| Snapshot / freshness | `VC_HIL/inverter/rxCAN/carMakerSteeringSnapshot.m` |
| Source selector | `VC_HIL/inverter/state-machine/selectSteeringSource.m` |
| Build-time gate | `VC_HIL/inverter/contructors/defaultVehicleStateConfig.m` (`carMakerSteeringEnabled`, `carMakerSteeringFreshnessMs`) |
| Speedgoat model wiring | `VC_HIL/build/build_inverter_hil_model.m` (`carMakerRxRetentionScript`, `steeringSourceSelectScript`, `Steering Source Select` block) |
| GUI / monitoring | `VC_HIL/inverter/+inverterhilgui/+live_telemetry/targetSession.m`, `blankTelemetry.m` (`snapshot.steering.source` / `.carMakerFresh` / `.carMakerAgeMs` / `.carMakerAngleDeg`) |
| Golden vectors | `references/sensors/golden_vectors/carmaker_steering/` |
| Tests | `VC_HIL/tests/inverter_hil/TestCarMakerSteering.m`, additions in `TestModelArtifacts.m` |

---

## 3. Transport CAN ID — PROVISIONAL

`0x507` (`1287`) `CarMakerDriverSteering`, CarMaker → SpeedgoatHIL on the
CarMaker bus (IO614 channel 1 / Port B).

**Status: PROVISIONAL — team approval still required.** It is the natural
continuation of the CarMaker-bus block (`0x500`, `0x503`–`0x506`), collides with
nothing in `MFE26_Inverter_CarMaker.dbc` or
`VC_HIL/docs/real_vcu_can_signal_map.md`, and is DLC 8 / standard 11-bit like
the rest of that block. But **no authoritative vehicle-wide CAN ID registry
exists** in this repository, so the ID must be ratified by whoever owns the
MFE26 CAN allocation before the bench is trusted.

---

## 4. The Fanatec CM Data Dictionary quantity — CONFIRM against this rig

The model-edit script defaults to **`DM.Steer.Ang`** (rad) and
**`DM.Steer.AngVel`** (rad/s) — the DrivMan desired steering-wheel angle,
chosen for consistency with the `0x500` pedal path, which `IO.c` sources from
`DrivMan.Gas` / `DrivMan.Brake`.

This has **not** been verified against the live sim (that needs a running
CarMaker engine + testrun, which is out of scope for a source-only change). All
of the candidates below are confirmed present in
`C:\IPG\carmaker\win64-12.0.1\CM4SL\startup.dict`; open the **R2022a "Read CM
Dict" quantity browser** (or run a maneuver and plot them) and pick the one the
Fanatec actually drives:

| Quantity | Meaning | Use when |
|---|---|---|
| `DM.Steer.Ang` | DrivMan desired wheel angle | Fanatec feeds DrivMan (matches the pedal path) — **current default** |
| `VC.Steer.Ang` | VehicleControl external interface | Fanatec feeds VehicleControl |
| `Driver.Steer.Ang` | IPGDriver output | the IPGDriver is the steering authority (already read by a Read CM Dict block in `TorqueVect.mdl`) |
| `Steer.WhlAng` / `Vhcl.Steer.Ang` | post-steering-column **actual** wheel angle | you want what a column-mounted LWS physically measures, after steering-system dynamics |

It must be the steering **wheel** angle. Never a road-wheel angle
(`Car.SteerAngle.FL` / `.FR`) and never vehicle yaw.

**Sign:** CarMaker steering-wheel angle is left-hand-positive (ISO 8855). The
Bosch LWS is also left-hand-positive ("CCW" positive). So the default sign Gain
is `+1`. If a bench capture shows a left turn producing a negative `0x2B0`
angle, rerun the script with `'SignConvention', -1`.

---

## 5. How to apply the change

### 5.1 TorqueVect.mdl (MATLAB **R2022a**)

`TorqueVect.mdl` is deliberately **not** regenerated by a headless save (same
policy as the `0x503`–`0x506` physics work, which shipped C + a checklist only).
Run the idempotent model-edit script instead:

```matlab
% R2022a, with the CarMaker-for-Simulink library resolvable
% (cmenv, or addpath <CarMakerInstall>\CM4SL\R2022a)
cd  <repo>\carmaker\FS_race\src_cm4sl
open_system('vehicle_models\TorqueVect.mdl')
apply_torquevect_steering                       % defaults: DM.Steer.Ang, save
% or, after confirming the quantity in the browser:
apply_torquevect_steering('AngleQuantity','VC.Steer.Ang', ...
                          'SpeedQuantity','VC.Steer.AngVel')
```

It builds one port-free subsystem `MFE_CAN Driver Steering` (Read CM Dict →
`180/pi` Gain → sign Gain → Saturation → Write CM Dict, for angle and speed).
Rerunning deletes and rebuilds the subsystem, so there are never duplicate
blocks or lines and existing TorqueVect behaviour is untouched. Save through
Simulink (`Ctrl+S` / the script's default `'Save', true`).

`MFE_CAN.Driver.SteeringAngleDeg` does not exist in the CarMaker dictionary
until the modified `User.c` is compiled, so the browser will not list it and a
model *update* will complain — that is expected; type the name and move on, the
same way the physics `MFE_CAN.Physics.*` Write blocks are handled.

### 5.2 Deploy the C sources into a local IPG-MFE build tree

`src/IO.c` and `src/User.c` are already in the `apply_cm4sl.ps1` manifest:

```powershell
cd  <repo>\carmaker\deploy
.\apply_cm4sl.ps1 -ProjectPath C:\Users\<you>\Documents\GitHub\IPG-MFE\FCM_Projects\FS_race
.\apply_cm4sl.ps1 -ProjectPath ...\FS_race -Verify      # confirm SHA-256 match
```

Never edit these files inside the IPG-MFE project; edits there are overwritten
and are not tracked as canonical.

### 5.3 Rebuild CM4SL (MATLAB **R2022a**)

Open `src_cm4sl\CarMaker for Simulink.sln`, or run the `src_cm4sl` `Makefile`,
in R2022a (not the R2024b `inverter_hil` environment). See
`carmaker/FS_race/src_cm4sl/CM4SL_CAN_apply_note.md`. `GetCRC_J1850_User` is
supplied by CarMaker's own libraries — do not add a local CRC.

### 5.4 Enable CarMaker steering on the Speedgoat (MATLAB **R2024b**)

The Speedgoat path ships **disabled**, exactly like `carMakerTruthEnabled`. To
turn it on:

```matlab
% VC_HIL/inverter/contructors/defaultVehicleStateConfig.m
config.carMakerSteeringEnabled = true;
```

then rebuild and redeploy the Speedgoat model:

```matlab
build_inverter_hil_model(true)     % R2024b
deploy_inverter_hil                % as usual
```

`carMakerSteeringEnabled` is a compile-time gate (it is read inside the
`Steering Source Select` MATLAB Function block via `defaultVehicleStateConfig`),
so changing it requires a rebuild — there is no runtime toggle, by design.

### 5.5 Return to GUI steering

Set `config.carMakerSteeringEnabled = false`, rebuild, redeploy. `0x507` is
then ignored entirely and the GUI steering dial is the only source. Even with
it enabled, losing the CarMaker link (`0x507` stale > 30 ms, or a
frozen-but-repeating counter) falls back to the live GUI dial automatically
(source `2`). The GUI fault-injection controls (dropout / stale / malformed /
invalid-status / angle-sentinel / speed-sentinel / calibration) are unchanged
and still act on whatever angle the selector picked.

---

## 6. Verifying with PCAN + the real VCU

1. **0x507 on the CarMaker bus.** With CarMaker running and the modified CM4SL
   build loaded, capture channel 1 with a PCAN tool. Turn the Fanatec wheel:
   `0x507` at ~100 Hz, byte 6 incrementing every frame, byte 7 a valid
   CRC-8/SAE-J1850 over bytes 0-6. Bytes 0-1 = angle × 10 as signed LE int16;
   left turn ⇒ positive.
2. **Golden vectors.** `references/sensors/golden_vectors/carmaker_steering/`
   `derive_carmaker_steering_vectors.py` regenerates `golden_carmaker_steering.json`
   (hand-derived, not from the decoder). `TestCarMakerSteering` checks the
   MATLAB decoder against it; cross-check a live capture by eye.
3. **Selection on the Speedgoat.** With `carMakerSteeringEnabled = true`, the
   GUI steering panel shows source `CarMaker (0x507)` and a small
   `carMakerAgeMs`. Pull the CarMaker PCAN cable: within ~30 ms the panel flips
   to `GUI dial (CarMaker stale)` and the LWS `0x2B0` angle follows the GUI
   dial with no jump to a retained value.
4. **0x2B0 on the VC bus.** Capture channel 2. `0x2B0` DLC 5 at 100 Hz; byte 3
   `0x07` when calibrated; bytes 0-1 = angle × 10 signed LE, matching the
   Fanatec position through the whole chain (allow the encoder's 0.1 deg
   quantisation). `0x507` must **never** appear on channel 2.
5. **Real VCU.** Confirm the MFE26-VC's decoded steering-wheel angle tracks the
   Fanatec wheel and that its own `0x7C0` calibration behaviour is unchanged
   (see §7).

### Physical Fanatec + real-VCU acceptance procedure

1. Bench powered, both CAN buses terminated (2 × 120 Ω per bus), real MFE26-VC
   connected on channel 2 only, CarMaker PC's PCAN-USB FD on channel 1 only.
2. CM4SL rebuilt (§5.3) with the deployed `IO.c` / `User.c`; TorqueVect.mdl
   carries the `MFE_CAN Driver Steering` subsystem (§5.1) with the **confirmed**
   quantity (§4).
3. Speedgoat model rebuilt with `carMakerSteeringEnabled = true` (§5.4) and
   deployed.
4. Start CarMaker with a testrun that lets the driver steer freely.
5. Centre the Fanatec wheel: `0x2B0` angle ≈ 0 (± the 0.1 deg quantum). Turn
   full lock each way: angle saturates at ±780 deg, sign matches the turn
   direction, VCU-decoded angle agrees.
6. Sweep the wheel quickly: `0x2B0` LWS_SPEED rises, clamped ≤ 1016 deg/s,
   never emits the 0xFF sentinel from a live reading.
7. Disconnect / reconnect the CarMaker PCAN cable: selection flips to GUI
   fallback and back, no unsafe angle step at either transition.
8. Exercise each GUI fault-injection control and confirm `0x2B0` shows the
   frame a faulted Bosch sensor would put on the wire.

---

## 7. Calibration topology (documented, not implemented here)

- `0x2B0`: simulated LWS → VCU. **Implemented** (this path).
- `0x7C0`: VCU → simulated LWS (LWS_Config: `0x05` reset calibration, `0x03`
  zero angle). The **HIL does not send `0x7C0` to the VCU** and this change
  does not add that. The Speedgoat's existing GUI calibration sequence
  (`hil_cmd_steering_calibration_sequence` → the enforced reset → checked wait →
  zero sequencer inside `Synchronized Sensor Payloads`) is a **manual
  self-test** of the simulated LWS: it pulses `0x7C0` on channel 2 as if a VCU
  had, so the emulator's calibration state machine can be exercised without a
  VCU in the loop. It remains a self-test unless/until the HIL is wired to
  receive and respond to the *real* VCU's `0x7C0`.

The Fanatec steering source does not change any of this. When
`carMakerSteeringEnabled` is true, a GUI "zero angle" still zeroes the
*emulator's* reported angle relative to whatever the selected source (CarMaker
or dial) is currently reporting — `zeroOffsetDeg` in `sensorPayloadScript` is
applied to the selected angle, unchanged.
