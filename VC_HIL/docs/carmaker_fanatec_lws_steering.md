# Fanatec steering wheel → CarMaker → Bosch LWS `0x2B0`

How the physical Fanatec steering wheel drives the emulated Bosch LWS the real
MFE26-VC reads. Companion to `carmaker/docs/cm4sl_integration.md` (the
CarMaker↔Speedgoat bus contract) and `VC_HIL/steering-sensor/protocol.md` (the
independent Bosch LWS contract).

---

## 1. The signal path, with units and signs at every stage

```
Fanatec wheel   (FANATEC Wheel (Haptic), Device.0, hardware axis 0,
  │              range −105 … +105 deg — carmaker/FS_race/Data/Config/mfe_setup)
  │  physical hand angle
  ▼
CarMaker cockpit → vehicle model
  │  CM Data Dictionary quantity  Steer.WhlAng            [rad]  left-hand +
  │  the APPLIED steering-wheel position, after the cockpit has scaled the
  │  Fanatec axis. Unit "rad" per <CarMakerInstall>\CM4SL\startup.dict.
  ▼
TorqueVect.mdl  ── subsystem "MFE_CAN CarMaker Truth" (built by
                   carmaker/FS_race/src_cm4sl/apply_torquevect_cm_truth.m)
  │  Read CM Dict  Steer.WhlAng                            [rad]
  │  Write CM Dict MFE_CAN.Steering.WheelAngleRad          [rad]
  │  — a straight passthrough. No Gain, no Saturation, no delay. Radians is
  │    the wire unit, so there is nothing to convert here and nothing for the
  │    Speedgoat to undo.
  │  Constant 1 → Write CM Dict  MFE_CAN.Steering.Valid
  ▼
IO.c  IO_Out()  (carmaker/FS_race/src_cm4sl/src/IO.c)
  │  samples MFE_CAN.Steering.WheelAngleRad every 10th 1-ms cycle (100 Hz),
  │  in the SAME cycle as the 0x503–0x506 physics group
  │  packs internal transport frame  0x507 CarMakerSteeringTruth:
  │    bytes 0-1  SteeringWheelAngleRad  int16 LE, 0.001 rad/bit
  │    bytes 2-5  reserved, zero          (a non-zero byte is rejected)
  │    byte  6    truth-group counter, mod 256 — THE SAME counter 0x503–0x506
  │                carry this cycle, so the Speedgoat can prove steering and
  │                physics describe one instant
  │    byte  7    CRC-8/SAE-J1850 over bytes 0-6  (poly 0x1D, init 0xFF,
  │                non-reflected, xorout 0xFF)
  │  SUPPRESSED entirely while MFE_CAN.Steering.Valid is 0
  │  PCAN-USB FD → IO614 channel 1 / Port B  (the CarMaker bus)
  ▼
Speedgoat  CarMaker RX Retention   (1 ms, sole channel-1 FIFO consumer)
  │  VC_HIL/inverter/rxCAN/decodeCarMakerSteeringFrame.m  — validate + decode;
  │       accepts |angle| ≤ 13.614 rad (the Bosch ±780 deg limit in whole
  │       counts) and converts rad → deg ONCE, here
  │  VC_HIL/inverter/rxCAN/receiveCarMakerSteering.m      — retain latest valid,
  │       prove FORWARD counter progress (duplicate and reordered rejected)
  │  VC_HIL/inverter/rxCAN/carMakerSteeringSnapshot.m     — fresh = value AND
  │       age ≤ carMakerSteeringFreshnessMs (30 ms) AND counter advancing
  ▼
Speedgoat  Steering Source Select  (1 ms, inside "Ephorus System Status")
  │  VC_HIL/inverter/state-machine/selectSteeringSource.m
  │  mode 1 CARMAKER + fresh  → CarMaker angle   (source 1, valid)   [deg]
  │  mode 1 CARMAKER + stale  → NO measurement   (source 2, INVALID)
  │  mode 0 MANUAL            → GUI dial         (source 0, valid)   [deg]
  │  publishes BOTH  HILSelectedSteeringAngleDeg  and
  │                  HILSelectedSteeringValid     on global Gotos
  ▼
Speedgoat  Synchronized Sensor Payloads  (5 ms; LWS transmits every 2nd tick
  │                                        → 100 Hz / 10 ms)
  │  the SELECTED angle replaces the raw GUI dial value here and in the shared
  │  vehicle state (stepVehicleState → MTi yaw). LWS_SPEED is derived by
  │  VC_HIL/steering-sensor/lwsAngularSpeed.m from successive 10 ms
  │  selected-angle samples and clamped to 1016 deg/s — never from vehicle
  │  yaw rate, which is a different quantity on a different sensor.
  │  If HILSelectedSteeringValid is low it encodes the Bosch FAILURE state
  │  instead of a measurement (see §5).
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

The Speedgoat — not CarMaker — owns Bosch LWS packing, status bits, angular
speed, calibration state, scheduling, sentinels, dropout, stale behaviour,
malformed-DLC injection and invalid-status injection. `0x2B0` is transmitted
only on channel 2. `0x507` is received only on channel 1 and is never forwarded
to the VC bus.

### Why radians on the wire

`Steer.WhlAng` is radians in the CarMaker dictionary and the Bosch LWS wants
degrees, so a conversion has to happen somewhere. Putting it on the CarMaker
side means a Gain block inside a model that only opens in R2022a, an extra
unit in the DBC, and a value the Speedgoat has to trust rather than derive.
Putting it at decode means one line, in a host-testable function, on the side
that owns sensor protocol encoding — and the transported number stays directly
comparable to what a bench operator reads off `Steer.WhlAng` in the CarMaker
GUI, which is what makes the Phase-17 comparison meaningful.

`0.001 rad/count` in an int16 spans ±32.767 rad (±1877 deg). That covers the
current ±105 deg Fanatec range, the disabled ±450 deg `Device.1` range, and the
Bosch ±780 deg measuring range with room to spare. Resolution is 0.0573 deg —
about half the Bosch encoder's own 0.1 deg count, so the transport is not the
limiting quantiser.

---

## 2. Canonical file locations (HIL repo)

| Concern | File |
|---|---|
| Transport frame sender | `carmaker/FS_race/src_cm4sl/src/IO.c` (`MFE_SendSteeringFrame`, called in `IO_Out()`) |
| Dictionary quantity registration | `carmaker/FS_race/src_cm4sl/src/User.c` (`User_DeclQuants`, `MFE_CAN.Steering.WheelAngleRad` / `.Valid`, `DVA_IO_Out`) |
| Per-TestRun validity clear | `carmaker/FS_race/src_cm4sl/src/User.c` (`User_TestRun_Start_atBegin`) |
| TorqueVect.mdl model-edit script | `carmaker/FS_race/src_cm4sl/apply_torquevect_cm_truth.m` |
| CAN contract | `carmaker/config/MFE26_Inverter_CarMaker.dbc` (`BO_ 1287 CarMakerSteeringTruth`) |
| Transport decode | `VC_HIL/inverter/rxCAN/decodeCarMakerSteeringFrame.m` |
| Counter policy | `VC_HIL/inverter/rxCAN/counterForwardDistance.m` |
| Retainer | `VC_HIL/inverter/rxCAN/receiveCarMakerSteering.m`, `VC_HIL/inverter/contructors/initialCarMakerSteeringBank.m` |
| Snapshot / freshness | `VC_HIL/inverter/rxCAN/carMakerSteeringSnapshot.m` |
| Source selector | `VC_HIL/inverter/state-machine/selectSteeringSource.m` |
| LWS angular speed | `VC_HIL/steering-sensor/lwsAngularSpeed.m` |
| Build-time gate | `VC_HIL/inverter/contructors/defaultVehicleStateConfig.m` (`steeringSourceMode`, `carMakerSteeringFreshnessMs`) |
| Speedgoat model wiring | `VC_HIL/build/build_inverter_hil_model.m` (`carMakerRxRetentionScript`, `steeringSourceSelectScript`, `sensorPayloadScript`, `Steering Source Select` block) |
| GUI / monitoring | `VC_HIL/inverter/+inverterhilgui/+live_telemetry/targetSession.m`, `blankTelemetry.m` (`snapshot.steering.source` / `.sourceValid` / `.carMakerFresh` / `.carMakerAgeMs` / `.carMakerAngleDeg` / `.carMakerAngleRad`) |
| Golden vectors | `references/sensors/golden_vectors/carmaker_steering/` |
| Tests | `VC_HIL/tests/inverter_hil/TestCarMakerSteering.m`, `TestCm4slTruthSources.m`, additions in `TestModelArtifacts.m` |

---

## 3. Transport CAN ID — PROVISIONAL

`0x507` (`1287`) `CarMakerSteeringTruth`, CarMaker → SpeedgoatHIL on the
CarMaker bus (IO614 channel 1 / Port B).

**Status: PROVISIONAL — team approval still required.** It is the natural
continuation of the CarMaker-bus block (`0x500`, `0x503`–`0x506`), is DLC 8 /
standard 11-bit like the rest of that block, and a repository-wide grep finds
it nowhere else: not in `MFE26_Inverter_CarMaker.dbc`, not in
`VC_HIL/docs/real_vcu_can_signal_map.md`, not in any source, test or golden
vector outside this path. `TestCm4slTruthSources` re-checks DBC ID uniqueness
on every run.

**That is a HIL-local audit, not vehicle-wide approval.** No authoritative
vehicle-wide CAN ID registry exists in this repository, so the ID must still be
ratified by whoever owns the MFE26 CAN allocation before the bench is trusted.

---

## 4. The Fanatec CM Data Dictionary quantity

The source is **`Steer.WhlAng`** — radians, left-hand-positive, confirmed
present with unit `rad` in `C:\IPG\carmaker\win64-12.0.1\CM4SL\startup.dict`
(line 1556). It is the applied steering-wheel position: what the vehicle model
actually steers with after the CarMaker cockpit has read and scaled the active
Fanatec axis.

### Why this one and not the alternatives

| Rejected | Why |
|---|---|
| `Car.SteerAngleFL` / `.FR` | Road-wheel angles, downstream of the steering rack. A different physical quantity from what a column-mounted LWS measures. |
| `GuiCmdSteeringAngleDeg` | Not the driver's wheel at all — the Speedgoat's own GUI dial. Available as the explicit MANUAL mode, never as a silent substitute. |
| `Driver.Steer.Ang` | The IPGDriver's output. Correct only if the IPGDriver is the steering authority; it is not the applied wheel position when a human is driving. |
| vehicle yaw rate | Not a steering angle. Also explicitly not the source of Bosch `LWS_SPEED` — see `lwsAngularSpeed.m`. |
| raw Fanatec USB/HID counts | Bypasses the CarMaker cockpit's calibration and scaling entirely, so the number would not correspond to the angle the vehicle model is steering with. |

### Cockpit configuration (`carmaker/FS_race/Data/Config/mfe_setup`)

| Key | Value |
|---|---|
| `Device.0.Name` | `FANATEC Wheel (Haptic)` |
| `Device.0.Enable` | `1` |
| `Device.0.Axis.Steering` | `0` |
| `Device.0.Steer.Whl_MinDeg` / `Whl_MaxDeg` | `−105.0` / `+105.0` |
| `Device.1.Enable` | `0` (configured for ±450 deg, disabled) |

**Static configuration is not proof the wheel is plugged in.** That the file
names a Fanatec device says nothing about whether the hardware is connected,
enumerated, or driving `Steer.WhlAng` right now. Only the §6 runtime check —
move the wheel, watch `Steer.WhlAng`, watch `0x507`, watch `0x2B0` — establishes
that.

**Sign:** CarMaker steering-wheel angle is left-hand-positive (ISO 8855). The
Bosch LWS is also left-hand-positive ("CCW" positive). No sign flip is applied
anywhere in the chain. If a bench capture shows a left turn producing a negative
`0x2B0` angle, the fix belongs in the CarMaker cockpit axis configuration, not
as a hidden Gain in the transport path.

---

## 5. Stale-source policy — no silent fallback

**In CarMaker mode, a stale `0x507` does not fall back to the GUI dial.**

Substituting the dial would put a plausible, well-formed steering angle on the
VC bus that no longer corresponds to the wheel the driver is holding, with
nothing on the wire to say so. A VCU cannot detect that, and neither can an
operator watching the car. It is the one failure mode this path must not be
able to produce, so the selector refuses to produce it.

Instead the selector clears `HILSelectedSteeringValid` and the LWS emulator
encodes the **Bosch failure state** at the normal 100 Hz:

| Field | Value |
|---|---|
| `LWS_ANGLE` | `0x7FFF` (the datasheet failure sentinel) |
| `LWS_SPEED` | `0xFF` (the datasheet invalid sentinel) |
| status byte | `0x04` — TRIM=1, OK=0, CAL=0 |

This is a legal frame a real broken LWS would put on the wire, so the VCU's
existing plausibility handling sees a state the datasheet defines. The frame
keeps flowing on purpose: that distinguishes "the sensor reports itself broken"
from "the bus went quiet", which are different faults with different causes.

Suppressing `0x2B0` entirely was the alternative. It stays available as the
existing GUI **dropout** injection, which is the right tool when bus silence is
specifically what you want to test.

Recovering GUI steering is an explicit mode change to MANUAL — visible in the
telemetry (`snapshot.steering.source` reads `GUI dial (manual)`), auditable, and
never something the bench does on its own.

Every existing GUI fault injection (dropout, stale payload, wrong DLC, invalid
status, angle sentinel, speed sentinel, calibration sequence) is unchanged and
still acts on whatever the selector picked.

---

## 6. How to apply the change

### 6.1 TorqueVect.mdl (MATLAB **R2022a**)

`TorqueVect.mdl` is an R2022a model and must never be saved from R2024b. Run
the idempotent model-edit script:

```matlab
% R2022a, with the CarMaker-for-Simulink library resolvable
cd  <repo>\carmaker\FS_race\src_cm4sl\vehicle_models
cmenv                                    % or addpath <CarMakerInstall>\CM4SL\R2022a
load_system('TorqueVect')
apply_torquevect_cm_truth('Model', 'TorqueVect')     % defaults + save
```

It builds one port-free subsystem `MFE_CAN CarMaker Truth` containing thirteen
Read CM Dict → Write CM Dict passthroughs (twelve physics + steering) and two
Constant → Write CM Dict validity writers. Rerunning deletes and rebuilds the
subsystem, so there are never duplicate blocks or lines. The subsystem has no
ports and is wired to nothing, so existing torque-vectoring behaviour is
untouched.

**Already applied** on this branch: the subsystem is in the committed
`TorqueVect.mdl` and `TestCm4slTruthSources.torqueVectActuallyContainsTheTruthWriters`
fails if it is ever lost.

The `MFE_CAN.*` target names do not exist in the CarMaker dictionary until the
modified `User.c` is compiled, so the Write CM Dict browser will not list them
and a model *update* will complain — that is expected; type the name and move
on. The `Sensor.Inertial.Param_B00.*` source names are created at runtime by
the vehicle's inertial sensor instance (`Sensor.Param.1.Name = Param_B00` in
`MFE24_V3` / `MFE26_V1`), so the **Read** browser only lists them once a TestRun
using such a vehicle is loaded. `Steer.WhlAng` and `Car.Roll/Pitch/Yaw` are in
the base `startup.dict` and are always listed.

### 6.2 Deploy the C sources into a local IPG-MFE build tree

`src/IO.c` and `src/User.c` are already in the `apply_cm4sl.ps1` manifest:

```powershell
cd  <repo>\carmaker\deploy
.\apply_cm4sl.ps1 -ProjectPath C:\Users\<you>\Documents\GitHub\IPG-MFE\FCM_Projects\FS_race
.\apply_cm4sl.ps1 -ProjectPath ...\FS_race -Verify      # confirm SHA-256 match
```

Never edit these files inside the IPG-MFE project; edits there are overwritten
and are not tracked as canonical.

### 6.3 Rebuild CM4SL (MATLAB **R2022a**)

Open `src_cm4sl\CarMaker for Simulink.sln`, or run the `src_cm4sl` `Makefile`,
in R2022a (not the R2024b `inverter_hil` environment). See
`carmaker/FS_race/src_cm4sl/CM4SL_CAN_apply_note.md`. `GetCRC_J1850_User` is
supplied by CarMaker's own libraries — do not add a local CRC.

### 6.4 Select CarMaker steering on the Speedgoat (MATLAB **R2024b**)

The Speedgoat path ships in **MANUAL** mode. To select CarMaker steering:

```matlab
% VC_HIL/inverter/contructors/defaultVehicleStateConfig.m
config.steeringSourceMode = uint8(1);     % 0 MANUAL, 1 CARMAKER
```

then rebuild and redeploy:

```matlab
build_inverter_hil_model(true)     % R2024b
deploy_inverter_hil                % as usual
```

`steeringSourceMode` is a compile-time selection (it is read inside the
`Steering Source Select` MATLAB Function block via `defaultVehicleStateConfig`),
so changing it requires a rebuild — there is no runtime toggle, by design.

### 6.5 Rollback

Set `config.steeringSourceMode = uint8(0)`, rebuild, redeploy. `0x507` is then
decoded for diagnostics but ignored by the selector, and the GUI steering dial
is the only source. This is the documented rollback and it is always available.

---

## 7. Verifying with PCAN + the real VCU

1. **`0x507` on the CarMaker bus.** With CarMaker running and the modified CM4SL
   build loaded, capture channel 1 with a PCAN tool. Turn the Fanatec wheel:
   `0x507` at ~100 Hz, byte 6 incrementing every frame **in step with the
   0x503–0x506 group counter**, byte 7 a valid CRC-8/SAE-J1850 over bytes 0-6,
   bytes 2-5 all zero. Bytes 0-1 = angle in rad × 1000 as signed LE int16;
   left turn ⇒ positive.
2. **The validity gate.** Before the model has run, or with a `TorqueVect.mdl`
   that has no truth writers, `0x503`–`0x507` must be **absent** from the bus
   entirely — not present-and-zero. The CarMaker log prints one suppression
   line per transition, not per cycle.
3. **Golden vectors.** `references/sensors/golden_vectors/carmaker_steering/`
   `golden_carmaker_steering.json` is hand-derived from the DBC, not from the
   decoder. `TestCarMakerSteering` checks the MATLAB decoder against it;
   cross-check a live capture by eye.
4. **Selection on the Speedgoat.** In CarMaker mode the GUI steering panel shows
   source `CarMaker (0x507)` and a small `carMakerAgeMs`. Pull the CarMaker
   PCAN cable: within ~30 ms the panel flips to
   `CarMaker unavailable - LWS failure state` and `0x2B0` shows the failure
   frame — **not** the GUI dial, and **not** the last retained angle.
5. **`0x2B0` on the VC bus.** Capture channel 2. `0x2B0` DLC 5 at 100 Hz; byte 3
   `0x07` when calibrated; bytes 0-1 = angle × 10 signed LE, matching the
   Fanatec position through the whole chain (allow the encoder's 0.1 deg
   quantisation). `0x507` must **never** appear on channel 2.
6. **Real VCU.** Confirm the MFE26-VC's decoded steering-wheel angle tracks the
   Fanatec wheel and that its own `0x7C0` calibration behaviour is unchanged
   (see §8).

### Physical Fanatec + real-VCU acceptance procedure

1. Bench powered, both CAN buses terminated (2 × 120 Ω per bus), real MFE26-VC
   connected on channel 2 only, CarMaker PC's PCAN-USB FD on channel 1 only.
   High-voltage / powered vehicle hardware disabled unless a separately
   approved procedure permits it.
2. CM4SL rebuilt (§6.3) with the deployed `IO.c` / `User.c`; `TorqueVect.mdl`
   carries the `MFE_CAN CarMaker Truth` subsystem (§6.1).
3. Confirm the cockpit device: `Device.0` = `FANATEC Wheel (Haptic)`, enabled,
   `Axis.Steering = 0`. Then **move the physical wheel and watch
   `Steer.WhlAng`** in the CarMaker GUI. If it does not move, nothing further
   in this list is meaningful.
4. Speedgoat model rebuilt with `steeringSourceMode = uint8(1)` (§6.4) and
   deployed.
5. Start CarMaker with a testrun that lets the driver steer freely.
6. Compare, at the same instant, all six stages: physical wheel position,
   `Steer.WhlAng`, the `0x507` payload, the Speedgoat's retained angle, the
   `0x2B0` encoded angle, and the VCU-decoded angle. Centre the wheel: all read
   ≈ 0. Turn to each Fanatec limit: all read ≈ ±105 deg with matching sign.
7. Sweep the wheel quickly: `0x2B0` `LWS_SPEED` rises, clamps at 1016 deg/s,
   and never emits the `0xFF` sentinel from a live reading.
8. Disconnect / reconnect the CarMaker PCAN cable: `0x2B0` flips to the Bosch
   failure state and back, with no unsafe angle step at either transition and
   no interval in which the GUI dial appears as CarMaker steering.
9. Exercise each GUI fault-injection control and confirm `0x2B0` shows the
   frame a faulted Bosch sensor would put on the wire.

---

## 8. Calibration topology (documented, not implemented here)

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

The Fanatec steering source does not change any of this. In CarMaker mode a GUI
"zero angle" still zeroes the *emulator's* reported angle relative to whatever
the selected source is currently reporting — `zeroOffsetDeg` in
`sensorPayloadScript` is applied to the selected angle, unchanged.
