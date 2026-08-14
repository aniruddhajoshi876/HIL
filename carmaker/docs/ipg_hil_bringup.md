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
| Throttle/brake XCP STIM mapping | **BROKEN** — see below |
| Torque reads zero with the VCU drive gate off | **unverified** |
| Torque → four-motor mapping approved by vehicle-dynamics owner | **not started, out of scope for automation** |

The run reached `running` *while the two pedal mappings were failing*. So what
is proven is that the model and dictionary are sound — **not** that the XCP
pedal path works end to end.

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

## Still broken: the two pedal mappings

```
ASAP2_CharMapping:
  ...hil_cmd_xcp_pedals_active    TorqueVect.XcpTorqueActive   1  0   maps clean
  ...hil_cmd_xcp_pedals_brake     VehicleControl.Brake         1  0   FAILS
  ...hil_cmd_xcp_pedals_throttle  VehicleControl.Gas           1  0   FAILS
```

At SIM_START CarMaker logs:

```
WARNING  XCP: Failed to map ASAP2 variable ...hil_cmd_xcp_pedals_brake to quantity VehicleControl.Brake
WARNING  XCP: Failed to map ASAP2 variable ...hil_cmd_xcp_pedals_throttle to quantity VehicleControl.Gas
```

The `active` mapping produces no warning, so the mechanism itself works — only
these two names are wrong. Leading hypothesis: `VehicleControl.Gas` and
`VehicleControl.Brake` are **Simulink bus signal paths** inside `TorqueVect.mdl`
(reached via a Bus Selector on a CarMaker bus), not Data Dictionary quantity
names. The real dictionary names are still unidentified.

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

## Remaining work

1. Identify the correct dictionary quantity names for throttle and brake.
2. Confirm torque reads zero with the VCU drive gate off (bench, by hand).
3. Vehicle-dynamics owner approves the torque-to-four-motor mapping — sign,
   saturation, regen/braking, split and normalization — before torque drives
   wheels. Explicitly out of scope for automation.
