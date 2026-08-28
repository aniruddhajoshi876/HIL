# CarMaker ↔ Speedgoat HIL integration — how it fits together

## Source of truth

**The HIL repository is the only source of truth for the CarMaker-for-Simulink
(CM4SL) integration.** Every canonical file lives here:

| File | Repo location |
|---|---|
| `IO.c` | `carmaker/FS_race/src_cm4sl/src/IO.c` |
| `User.c` | `carmaker/FS_race/src_cm4sl/src/User.c` |
| `User.h` | `carmaker/FS_race/src_cm4sl/inc/User.h` |
| `Makefile` | `carmaker/FS_race/src_cm4sl/Makefile` |
| `TorqueVect.mdl` | `carmaker/FS_race/src_cm4sl/vehicle_models/TorqueVect.mdl` |
| CAN contract (DBC) | `carmaker/config/MFE26_Inverter_CarMaker.dbc` |
| Apply note | `carmaker/FS_race/src_cm4sl/CM4SL_CAN_apply_note.md` |
| Read CM Dict checklist | `carmaker/docs/carmaker_readcmdict_checklist.md` |
| Design plan | `VC_HIL/docs/carmaker_imu_truth_source_plan.md` |
| Deploy script | `carmaker/deploy/apply_cm4sl.ps1` |

**The local `IPG-MFE/FCM_Projects/FS_race` project is a build/deploy workspace
only.** Do not commit the HIL integration there, and do not develop it there —
edits inside `IPG-MFE/.../src_cm4sl` are overwritten by the next deploy and are
not tracked as canonical.

## What the integration does

Two independent CAN buses on the Speedgoat IO614:

- **Channel 2 / Port A — VC bus.** Speedgoat ↔ real MFE26-VC. The Speedgoat
  transmits the MTi (`0x032` / `0x034` / `0x076` + scalar `0x006` / `0x005` /
  `0x011` / `0x001`) and LWS (`0x2B0`) sensor frames here. CarMaker is not on
  this bus.
- **Channel 1 / Port B — CarMaker bus.** CarMaker's PCAN-USB FD ↔ Speedgoat.
  Frames:

  | ID | Dir | Contents |
  |---|---|---|
  | `0x500` | CarMaker → SG | pedal demand (throttle/brake %, active, alive counter, CRC-8/J1850) |
  | `0x501` / `0x502` | SG → CarMaker | per-inverter torque setpoints / ready bits |
  | `0x503`-`0x506` | CarMaker → SG | vehicle-physics truth: acceleration, angular rate, velocity, Euler — 3× little-endian `int16` @ bytes 0/2/4, shared mod-256 truth-group counter @ byte 6, CRC-8/J1850 @ byte 7. 10 ms. |
  | `0x507` | CarMaker → SG | Fanatec / driver steering-wheel angle, `int16` LE `0.001` **rad**/bit @ bytes 0-1; bytes 2-5 reserved zero; **the same** mod-256 truth-group counter as `0x503`-`0x506` @ byte 6; CRC-8/J1850 @ byte 7. 10 ms. No speed field — the Speedgoat derives Bosch `LWS_SPEED` from successive samples. Speedgoat packs it into the Bosch LWS `0x2B0`. PROVISIONAL ID. See `VC_HIL/docs/carmaker_fanatec_lws_steering.md`. |

`IO.c` (`IO_Out()`) sends `0x503`-`0x507` every 10-ms cycle right after `0x500`,
reading the `MFE_CAN.Physics.*` / `MFE_CAN.Steering.*` dictionary quantities
that `TorqueVect.mdl` populates. All five frames are sampled in one cycle and
stamped with one counter. On the Speedgoat,
`VC_HIL/inverter/rxCAN/decodeCarMakerPhysicsFrame.m` + `receiveCarMakerPhysics.m`
decode and coherently retain a physics group, and
`VC_HIL/inverter/state-machine/selectVehicleObservation.m` substitutes it for
the kinematic vehicle-state estimate — **only when
`defaultVehicleStateConfig.carMakerTruthEnabled` is `true`.** It is `false` by
default.

### The validity gate

`IO.c` transmits `0x503`-`0x507` **only** while the model-written
`MFE_CAN.Physics.Valid` / `MFE_CAN.Steering.Valid` quantities are non-zero.
Without that gate, a `TorqueVect.mdl` with no truth writers still produces a
perfectly formed stream of CRC-valid, counter-advancing, **all-zero** frames
from the moment the PCAN link comes up — and downstream those are
indistinguishable from a genuinely stationary, straight-ahead vehicle. Both
flags are cleared in `User_TestRun_Start_atBegin()`, so validity is a
per-TestRun statement rather than a once-per-process one, and the model raises
them again on its first execution. Suppression is logged once per transition,
never per cycle: an unpopulated model is an expected state, not an error.

## CRC

`GetCRC_J1850_User()` used by `IO.c` is **not** a project function. It is a
CarMaker library function declared in
`C:\IPG\carmaker\win64-12.0.1\include\E2E.h:210` and linked from
`libcarmaker.a` / `librbsutil.a`. `IO.c` already `#include <E2E.h>`. It is
called as `GetCRC_J1850_User(data, n, 0xff, 0xff)` — init `0xFF`, xorout
`0xFF`, poly `0x1D`, non-reflected — matching the Speedgoat decoder's `crc8`
in `decodeCarMakerPhysicsFrame.m`. **Do not add a local definition.**

## TorqueVect.mdl — not auto-synced

As of 2026-08-27 the model has diverged three ways and is **excluded from the
default deploy**:

| Copy | Lines (LF-normalized) |
|---|---|
| HIL `carmaker/FS_race/src_cm4sl/TorqueVect.mdl` (committed) | 176 170 |
| IPG-MFE committed (`HEAD`) | 177 365 |
| IPG-MFE working tree (uncommitted) | 176 252 |

The differences are dominated by Simulink re-serialization churn and cannot be
reconciled by text diff. Both the HIL copy and the IPG working copy carry the
`PTControl_TV_MFE25` `fmincon` constraint-shape fix (`A_ineq = omega' * 13.39`)
while the duplicate `PTControl_TV_MFE3` still has the unfixed line — that state
is the same in both, so nothing is lost by treating HIL's copy as canonical.

**Before enabling CarMaker-as-truth**, open both copies in **MATLAB R2022a**,
run a Simulink model comparison, decide which is canonical, commit it to HIL,
then deploy with `apply_cm4sl.ps1 -IncludeModel`.

---

## Deploy the C sources to a CarMaker project

```powershell
cd carmaker\deploy
.\apply_cm4sl.ps1 -ProjectPath C:\path\to\IPG-MFE\FCM_Projects\FS_race
```

- Prints the plan (which files, and their status: `identical` / `CREATE` /
  `CONFLICT`), then copies the safe files.
- A destination file that differs from the canonical version is an
  **unpreserved difference** — the script refuses to overwrite it unless you
  answer `y` at the prompt or pass `-Force`.
- Never deletes anything; only touches the manifest
  (`IO.c`, `User.c`, `User.h`, `Makefile`; `TorqueVect.mdl` only with
  `-IncludeModel`).
- `-Verify` compares deployed vs canonical SHA-256 and exits non-zero on
  mismatch.

## Rebuild CM4SL in R2022a

1. Open **MATLAB R2022a** (not the R2024b environment used for `inverter_hil`).
2. Follow the working link procedure in `VC_HIL/docs/speedgoat_ipg_integration.md`
   (add `MFE25-Controls` model params, add `IPG-MFE/.../src_cm4sl` to the path,
   run `cmenv.m`, open `TorqueVect.mdl`, open the CarMaker GUI).
3. If `TorqueVect.mdl` changed, save it through Simulink and run the
   `ModelUpdate` publish step if the CM4SL workflow requires it.
4. Build: the `CarMaker for Simulink.sln` solution, or
   `make -C IPG-MFE/FCM_Projects/FS_race/src_cm4sl`.
5. `apply_cm4sl.ps1 -ProjectPath ... -Verify` to confirm.

## The TorqueVect.mdl truth passthroughs

`TorqueVect.mdl` must copy the CarMaker inertial sensor and the steering-wheel
angle into the `MFE_CAN.*` quantities `IO.c` reads, and raise the two validity
flags. This is scripted — run
`carmaker/FS_race/src_cm4sl/apply_torquevect_cm_truth.m` in **R2022a**:

```matlab
cd  <repo>\carmaker\FS_race\src_cm4sl\vehicle_models
cmenv
load_system('TorqueVect')
apply_torquevect_cm_truth('Model', 'TorqueVect')
```

It builds one port-free subsystem `MFE_CAN CarMaker Truth`, rerunnable with no
duplicates, wired to nothing in the existing torque-vectoring path.

| CarMaker source | → target |
|---|---|
| `Sensor.Inertial.Param_B00.Acc_B.{x,y,z}` | `MFE_CAN.Physics.Acceleration.{x,y,z}` |
| `Sensor.Inertial.Param_B00.Omega_B.{x,y,z}` | `MFE_CAN.Physics.AngularRate.{x,y,z}` |
| `Sensor.Inertial.Param_B00.Vel_B.{x,y,z}` | `MFE_CAN.Physics.Velocity.{x,y,z}` |
| `Car.{Roll,Pitch,Yaw}` | `MFE_CAN.Physics.Euler.{x,y,z}` (optional) |
| `Steer.WhlAng` **[rad]** | `MFE_CAN.Steering.WheelAngleRad` **[rad]** |
| Constant `1` | `MFE_CAN.Physics.Valid` |
| Constant `1` | `MFE_CAN.Steering.Valid` |

Every one is a **straight Read CM Dict → Write CM Dict passthrough**: no Gain,
no Saturation, no Memory or Unit Delay, no unit conversion, no MTi scaling and
no IMU mounting transform. All of that belongs downstream of the Speedgoat's
observation selector, so CarMaker truth and the internal kinematic model go
through the same transform. Blocks inherit the CM4SL base step, so `IO_Out()`
samples the current cycle rather than the previous one.

`Steer.WhlAng` is radians and stays radians all the way to the Speedgoat
decoder — the rad → deg conversion happens once, immediately before Bosch LWS
encoding. Step-by-step R2022a GUI instructions, if you would rather wire it by
hand: `carmaker/docs/carmaker_readcmdict_checklist.md`.

### What is and is not confirmed

- `Steer.WhlAng` (`rad`) and `Car.Roll` / `.Pitch` / `.Yaw` (`rad`) are present
  in `C:\IPG\carmaker\win64-12.0.1\CM4SL\startup.dict`.
- `Sensor.Inertial.Param_B00.*` are created **at runtime** by the vehicle's
  inertial sensor instance (`Sensor.Param.1.Type = Inertial`,
  `Sensor.Param.1.Name = Param_B00` in `MFE24_V3` and `MFE26_V1`). They are not
  in `startup.dict`, so the R2022a Read CM Dict browser only lists them once a
  TestRun using such a vehicle is loaded. **Confirm the `.x/.y/.z` leaf names
  there before enabling CarMaker-as-truth.**
- The `MFE_CAN.*` targets do not exist until the modified `User.c` is compiled,
  so the Write browser will not list them either. Type the name and move on.

Verify after wiring: plot each `MFE_CAN.Physics.*` against its
`Sensor.Inertial.Param_B00.*` source; stationary ⇒
`MFE_CAN.Physics.Acceleration.z ≈ +9.81` (a real MTi reports specific force —
if it reads ≈ 0 you picked the `noGN` variant).

Full steering path, sign convention, provisional CAN ID `0x507`, the Speedgoat
selector and its no-silent-fallback stale policy, and the physical acceptance
procedure: `VC_HIL/docs/carmaker_fanatec_lws_steering.md`.

## Enable CarMaker as the IMU truth source

Only after the bench-acceptance sequence in
`VC_HIL/docs/carmaker_imu_truth_source_plan.md` section 7 passes:

1. `VC_HIL/inverter/contructors/defaultVehicleStateConfig.m`:
   `config.carMakerTruthEnabled = true;`
2. In **MATLAB R2024b**, from the repo root:
   ```matlab
   Simulink.data.dictionary.closeAll('-discard'); bdclose('all');
   build_inverter_hil_model(true);
   ```
3. Redeploy the regenerated `VC_HIL/build/inverter_hil.slx` to the Speedgoat
   target `TargetPC1` (10.10.10.5) as its startup application, per the normal
   `deploy_inverter_hil` flow.
4. Confirm on the target: with CarMaker running, the selector reports
   `source = CarMaker`; pausing CarMaker drops it back to the kinematic
   estimate within the 30 ms freshness timeout.

## Return to the safe fallback

1. `defaultVehicleStateConfig.m`: `config.carMakerTruthEnabled = false;`
2. `build_inverter_hil_model(true)` in R2024b, redeploy to `TargetPC1`.

With the flag `false` the CarMaker decode/retain path still runs (for
observability) but `selectVehicleObservation` always returns the kinematic
estimate — byte-identical to the pre-integration behaviour. No CarMaker
changes need to be reverted; leaving `0x503`-`0x506` on channel 1 with the flag
off is harmless.
