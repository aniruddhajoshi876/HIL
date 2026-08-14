# IPG CarMaker ↔ Speedgoat HIL bring-up

State as of 2026-08-14. Records what is **proven**, what is **assumed**, and
what is **still broken**, because several earlier conclusions here turned out
to rest on a verification method that did not actually verify anything.

## Current status

| Step | State |
|---|---|
| `inverter_hil` builds for the SLRT/Speedgoat target | proven |
| A2L generated with the four HIL symbols at real addresses | proven |
| CarMaker imports the A2L, XCP ECU `SpeedgoatVirtualVCU` created and active | proven |
| Simulation reaches `SimulationStatus = running` | proven 2026-08-14 14:17 |
| Speedgoat AO/AI loop confirmed at the bench | proven (by hand, not by script) |
| Throttle/brake XCP STIM mapping | fixed 2026-08-14 — `DM.Gas` / `DM.Brake`, warnings gone |
| XCP master/slave DAQ mismatch | fixed 2026-08-14 — log now warning-free |
| Torque reads zero with the VCU drive gate off | **unverified** |
| Torque → four-motor mapping approved by vehicle-dynamics owner | **not started, out of scope for automation** |

Scope of what "proven" means here: the model and dictionary are sound, the sim
runs to completion, and all three XCP char mappings now bind without warnings.
What is **not** proven is that a pedal value actually moves the simulated car,
or that the torque readback carries a correct value — the first run reached
`running` while both pedal mappings were still failing, which is a reminder
that "the sim runs" and "the XCP path works" are independent claims.

## The blocking chain, and what each fix actually was

### 1. A2L could not be generated from the GUI

`inverter_hil.slx` targets `speedgoat.tlc` with `TargetLang = 'C++'`. Simulink
Coder's ASAP2 export supports C only, so `set_param(cs,'GenerateASAP2','on')`
throws `Changing property 'GenerateASAP2' is not allowed`. `TargetLang` itself
is immutable for this target, so switching to C is not available.

Fix: bypass the config-set entirely with `coder.asap2.export`:

```matlab
coder.asap2.export('inverter_hil', 'Folder', outFolder, ...
                   'FileName', 'inverter_hil', 'MapFile', symFile);
```

### 2. CarMaker's A2L importer choked on `HOST_NAME`

`XCP::Setup::GenASAP2Parameters` failed with a Tcl parse error. CarMaker's own
intermediate file showed it double-quoting any `HOST_NAME` value into `""""`.

Fix: delete the `HOST_NAME` line from the A2L, leaving:

```
/begin XCP_ON_UDP_IP
  0x0100
  0x15B3
/end XCP_ON_UDP_IP
```

### 3. `PT.Motor.rotv not in dictionary`

Not a broken block — the **wrong vehicle**. `TorqueVect.mdl` reads ten
quantities that only a four-motor BEV registers:

```
PT.Motor{,1,2,3}.Trq   PT.Motor{,1,2,3}.rotv   PT.PwrSupply.HV1.Pwr
```

`FSC_TestAutomation` is `PowerTrain.Kind = Generic 1` — a combustion vehicle
with zero motors — and **every** `Data/TestRun/Validation/*` TestRun uses it.
So the whole Validation family is incompatible with `TorqueVect.mdl`; no single
TestRun is uniquely broken.

Cheap pre-flight check before running anything:

```bash
grep -m1 '^Vehicle = ' <testrun>
grep -m1 '^PowerTrain.Kind' Data/Vehicle/<that vehicle>   # want BEV + 4x Motor*.Kind
```

Fix: `Data/TestRun/HIL/XCP_Bringup` (copied into this repo for reference) on
`Examples_FS/MFE24_V3`. Note BEV TestRuns omit `DrivMan.Man.Start.GearNo`
entirely.

**Design point:** its longitudinal dynamics are `Dyn = Manual` with Gas/Brake
pinned to `0.0 0.0 0.0 abs`, not an IPGDriver speed target. The XCP STIM path
writes the pedal quantities directly, so an IPGDriver longitudinal step would
fight the Speedgoat for the same two quantities and you would not know whose
pedal you were looking at.

### 4. `Fmincon cannot continue`

`PTControl_TV_MFE25/Full Control Loop/MATLAB Function` had its tire-load guard
commented out:

```matlab
%     F(F < 100) = 500;
```

With the car stationary at t=0, a tire normal load `F(i)` of 0 makes
`w = sqrt(F_total./F)` → `Inf`, so `D = diag(w)` holds `Inf`. At
`x0 = zeros(4,1)`, `D*x0` evaluates `Inf*0 = NaN`, so `fun(x0) = NaN` →
*"Objective or nonlinear constraint undefined at initial point."*

Fixed in IPG-MFE `0076f02` (branch `parameters`). This is **distinct** from the
`A_ineq` shape bug fixed in `f774da6`; that transpose is present and correct,
and fmincon reaching objective evaluation proves the shape already validates.

A second commented copy exists in `PTControl_TV_MFE3` (chart_42) and was left
alone deliberately — that subsystem is disabled. Do not "fix" it.

### 5. `XCP: Cannot connect to ECU #0 (Timeout)`

→ `CM_Main.c: Initialization failed (CM_Main_Begin()=-3)` → SIM_ABORT at 0s.

The Speedgoat app was simply not loaded. **Ping success does not mean the app
is up.** After any reboot or restart the target comes back `isLoaded=0`:

```matlab
tg = slrealtime; tg.TargetSettings.address = '10.10.10.5';
connect(tg); load(tg, '<...>/inverter_hil.mldatx'); start(tg);
% want: status=running  isLoaded=1  isRunning=1
```

## The pedal mappings (fixed)

`VehicleControl.Gas` and `VehicleControl.Brake` are **C struct members**, not
dictionary quantities — `include/VehicleControl.h` declares `tVehicleControl`,
and `FS_race/src/ExtraModels/MyCar.c:420` does
`Car.Driver.Throttle = VehicleControl.Gas;`. They were never going to map.

The correct XCP STIM write targets are **`DM.Gas`** and **`DM.Brake`**, access
point `DVA_DM` ("after DrivMan"). That is upstream of VehicleControl, so a write
there overrides the TestRun's pinned `Manual` Gas/Brake = 0 and propagates into
the model. `VC.Gas`/`VC.Brake` also exist but sit *downstream* of the
VehicleControl computation, which is the wrong injection point for a driver
pedal command.

```
ASAP2_CharMapping:
  ...hil_cmd_xcp_pedals_active    TorqueVect.XcpTorqueActive  1  0
  ...hil_cmd_xcp_pedals_brake     DM.Brake                    1  0
  ...hil_cmd_xcp_pedals_throttle  DM.Gas                      1  0
```

Verified: the two `XCP: Failed to map` warnings are absent from
`SimOutput/Shop_Computer_Sim/Log/Shop_Computer_Sim_20260814_143939.log`.

Existence confirmed for `DM.Gas`, `DM.Brake`, `VC.Gas`, `VC.Brake`,
`DM.Clutch`, `DM.Handbrake`, `Driver.Gas`, `Driver.Brake`. Not existing:
`VehicleControl.Gas`, `VehicleControl.Brake`, `VC.Gas_trg`.

## Do not use `DVARead` to check whether a quantity exists

This invalidated several earlier conclusions, including the claim that the two
pedal names above had been "confirmed real". Proven with explicit controls:

- **Sim stopped** — returns `0.0` for *everything*: real quantities,
  `Nonsense.Totally.Fake`, `PT.Motor9.rotv`, and `PT.Motor.rotv` on a vehicle
  that provably lacks it. Known-good and known-bad vehicles gave byte-identical
  output.
- **Sim running** — returns the literal string `err` for *everything*,
  including `Time` and the bogus control.

There is no sim state in which it discriminates present from absent.

**But the CarMaker simulation log does answer it.** Every failed DVA read is
logged as `DVA read: Unknown quantity '<name>'`, and known names log nothing.
So the working existence test is: start a run, `DVARead` each candidate,
ignore the return value entirely, then grep the newest
`SimOutput/<host>/Log/<host>_<stamp>.log` for `Unknown quantity`. Interleave a
uniquely-named bogus control after every real candidate — if the controls do
not all show up as unknown, the probe did not run and silence means nothing.

Two related traps:

- `cmguicmd` returns Tcl errors as ordinary **return strings**, it does not
  raise. `cmguicmd('ScriptVersion')` returns the text
  `invalid command name "ScriptVersion"` without throwing, so `try/catch`
  around it catches nothing and "didn't throw" means nothing. Check the
  returned string.
- Always run a deliberately bogus control alongside any probe.

**The trustworthy signal** for a mapping is the CarMaker simulation log at
SIM_START: a wrong name prints `WARNING XCP: Failed to map ...`, a correct one
prints nothing.

## Starting a run

`cmguicmd('StartSim')` deadlocks — `CM4SL: concurrent execution of cmguicmd and
MatlabEval denied`. The CarMaker GUI's own Start button is also inert whenever
it warns `CarMaker command engine task not running`.

Start from Simulink instead:

```matlab
set_param('TorqueVect', 'SimulationCommand', 'start')
```

Prerequisites in order: run `Control_FL_Combined_Run.m` lines 1–95 (through
"Other Controller and Optimization Parameters") to define `pid_kp_long` etc.,
set the alias variables the PID blocks read (`kp`/`ki`/`kd`/`N`/`ka`/`Kp`/`Ki`/`Kd`),
then `cmenv.m`, `load_system('TorqueVect')`, open the "Open CarMaker GUI" block,
then `LoadTestRun HIL/XCP_Bringup`.

Model edits to `TorqueVect.mdl` must be made in **R2022a**. Also note
`save_system` rewrites Data Inspector `Persistence` and `TestPointedSignal`
bookkeeping — a one-line logic change came out as 63 insertions / 1685
deletions. For a reviewable diff, patch the `.mdl` text directly instead.

## XCP master/slave DAQ mismatch (fixed)

Every run used to print:

```
XCP: ECU #0 - Detected Processor info mismatch:
  > Overload Indication (Master: OVERLOAD_INDICATION_PID Slave: OVERLOAD_INDICATION_EVENT)
  > TimeStamp Support   (Master: 0 Slave: 1)
XCP: ECU #0 - Detected Resolution info mismatch:
  > TimeStamp Fixed     (Master: 0 Slave: 1)
  > TimeStamp Size      (Master: NO_TIME_STAMP Slave: SIZE_DWORD)
WARNING  XCP: Difference in DAQ programming setup between Master and Slave detected
```

Cause: CarMaker's A2L importer populated `XCPParameters` with the A2L's
`DAQ.Config` / `DAQ.Opt` / `DAQ.Settings` / `DAQ.OptODT` / `DAQ.Events` — but
silently **dropped the `TIMESTAMP_SUPPORTED` block**, leaving the master with no
timestamp configuration at all. The A2L itself was correct all along:

```
/begin TIMESTAMP_SUPPORTED
  0x0001
  SIZE_DWORD
  UNIT_1US
  TIMESTAMP_FIXED
/end TIMESTAMP_SUPPORTED
```

`ECU.0.OverrideASAP2 = 1` means XCPParameters overrides the ASAP2 file
(Programmer's Guide p. 942), so XCPParameters is the correct place to fix it —
do **not** flip that flag to 0, which would discard the other reconciled DAQ
values.

Fix, per Programmer's Guide p. 945 (`ECU.<n>.DAQ.Timestamp = Ticks Size Unit Fixed`):

```
ECU.0.DAQ.Settings = OVERLOAD_INDICATION_EVENT PRESCALER_SUPPORTED RESUME_NOT_SUPPORTED PID_OFF_NOT_SUPPORTED
ECU.0.DAQ.Timestamp = 1 SIZE_DWORD UNIT_1US TIMESTAMP_FIXED
```

Verified: `Shop_Computer_Sim_20260814_144727.log` contains no XCP warnings at
all — SIM_START straight to SIMULATE to SIM_END.

Two things deliberately left alone:

- **The A2L still says `OVERLOAD_INDICATION_PID`** while the slave reports
  `EVENT`. The override makes XCPParameters win, but a re-import of the A2L
  reintroduces `PID`. Worth fixing at the generator.
- **`DAQ.STIM` is absent from XCPParameters** even though the A2L declares
  `GRANULARITY_ODT_ENTRY_SIZE_STIM_BYTE 0xFF`. CarMaker has a
  `> STIM Entry Granularity` mismatch message and it never fired, so STIM is not
  currently mismatched. The docs list only `..._DAQ_*` values for that key,
  which looks like a doc error — not worth guessing through.

## Remaining work

1. Confirm a pedal value actually moves the simulated car, and that the torque
   readback carries a correct value. Neither is proven yet.
2. Confirm torque reads zero with the VCU drive gate off (bench, by hand).
3. Vehicle-dynamics owner approves the torque-to-four-motor mapping — sign,
   saturation, regen/braking, split and normalization — before torque drives
   wheels. Explicitly out of scope for automation.
