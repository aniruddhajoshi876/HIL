# CarMaker ↔ Speedgoat HIL integration — how it fits together

## Source of truth

**The HIL repository is the only source of truth for the CarMaker-for-Simulink
(CM4SL) integration.** Every canonical file lives here:

| File | Repo location |
|---|---|
| `IO.c` | `carmaker/FS_race/src_cm4sl/IO.c` |
| `User.c` | `carmaker/FS_race/src_cm4sl/User.c` |
| `User.h` | `carmaker/FS_race/src_cm4sl/User.h` |
| `security_cookie_stub.c` | `carmaker/FS_race/src_cm4sl/security_cookie_stub.c` |
| `Makefile` | `carmaker/FS_race/src_cm4sl/Makefile` |
| `TorqueVect.mdl` | `carmaker/FS_race/src_cm4sl/TorqueVect.mdl` |
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
  | `0x503`-`0x506` | CarMaker → SG | vehicle-physics truth: acceleration, angular rate, velocity, Euler — 3× little-endian `int16` @ bytes 0/2/4, shared mod-256 group counter @ byte 6, CRC-8/J1850 @ byte 7. 10 ms. |

`IO.c` (`IO_Out()`) sends `0x503`-`0x506` every 10-ms cycle right after `0x500`,
reading the `MFE_CAN.Physics.*` dictionary quantities that `TorqueVect.mdl`
populates. On the Speedgoat, `VC_HIL/inverter/rxCAN/decodeCarMakerPhysicsFrame.m`
+ `receiveCarMakerPhysics.m` decode and coherently retain a physics group, and
`VC_HIL/inverter/state-machine/selectVehicleObservation.m` substitutes it for
the kinematic vehicle-state estimate — **only when
`defaultVehicleStateConfig.carMakerTruthEnabled` is `true`.** It is `false` by
default.

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
  (`IO.c`, `User.c`, `User.h`, `security_cookie_stub.c`, `Makefile`;
  `TorqueVect.mdl` only with `-IncludeModel`).
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

## Add the nine Read CM Dict → Write CM Dict passthroughs

`TorqueVect.mdl` must copy the CarMaker inertial sensor into the
`MFE_CAN.Physics.*` quantities `IO.c` reads. Step-by-step (R2022a GUI):
`carmaker/docs/carmaker_readcmdict_checklist.md`.

| CarMaker source (confirm the exact leaf names in the R2022a Read CM Dict browser) | → target |
|---|---|
| `Sensor.Inertial.Param_B00.Acc_B.{x,y,z}` | `MFE_CAN.Physics.Acceleration.{x,y,z}` |
| `Sensor.Inertial.Param_B00.Omega_B.{x,y,z}` | `MFE_CAN.Physics.AngularRate.{x,y,z}` |
| `Sensor.Inertial.Param_B00.Vel_B.{x,y,z}` | `MFE_CAN.Physics.Velocity.{x,y,z}` |

**The `.x/.y/.z` leaf names and the `Sensor.Inertial.Param_B00` addressing are
NOT verified.** The `Acc_B` / `Omega_B` / `Vel_B` stems are confirmed in
`C:\IPG\carmaker\win64-12.0.1\include\Vehicle\MBSUtils.h`; the rest must be
confirmed by selecting them in the R2022a Read CM Dict browser before enabling
CarMaker-as-truth.

Verify after wiring: plot each `MFE_CAN.Physics.*` against its
`Sensor.Inertial.Param_B00.*` source; stationary ⇒
`MFE_CAN.Physics.Acceleration.z ≈ +9.81` (a real MTi reports specific force —
if it reads ≈ 0 you picked the `noGN` variant).

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
