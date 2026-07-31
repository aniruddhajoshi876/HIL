# Inverter HIL operator GUI acceptance checklist

Scope: plan section 8 parts 29-35, governed by plan sections 7.1-7.4.
Release gate: MATLAB/Simulink R2024b only.

Verification legend:
- `R2024b batch` - checked with `C:\Program Files\MATLAB\R2024b\bin\matlab.exe -batch`.
- `lint` - checked with the MATLAB Code Analyzer.
- `unittest` - covered by a `tests/inverter_hil` case wired into `run_inverter_hil_tests.m`.
- `manual` - checked by launching the app and reading the screen.

## E. Environment facts established before implementation

| ID | Item | Established value |
|---|---|---|
| E1 | Installed releases | R2024a, R2024b, R2026a |
| E2 | MATLAB MCP session release | **R2026a** - must NOT be used to save `.mlapp`, run the suite, or touch any authoritative artifact. MCP is permitted for lint only. |
| E3 | Authoritative verification path | `R2024b batch` via the Bash/PowerShell tool |
| E4 | `appdesigner.internal.serialization.MLAPPSerializer` in R2024b | Present (`exist == 8`), properties include `FullFileName`, `MatlabCodeText`, `UIFigure`, `Callbacks`, `StartupCallback`, `ClassName`, `OverwriteTargetFile`; methods include `save` |
| E5 | Simulink Real-Time in R2024b | Installed |
| E6 | **Baseline test suite state** | **66 passed / 1 failed of 67.** Pre-existing failure `TestModelArtifacts/executionAndDictionaryAttachmentAreExact`: model `SystemTargetFile` is `speedgoat.tlc`, test expects `slrealtime.tlc`. Unrelated to the GUI. **Must not be fixed here** (would require editing `inverter_hil.slx`) and must not get worse. |

## A. Architecture and workspace constraints

| ID | Requirement | Verify |
|---|---|---|
| A1 | Every new file lives under `mfe\HIL\inverter_hil\`; no write outside the workspace | manual |
| A2 | `inverter_hil_app.mlapp` sits in the workspace root (supersedes plan 1.1 `mfe\HIL\`) | manual |
| A3 | `.mlapp` is a thin shell: layout construction plus callbacks that immediately delegate to `+inverterhilgui` | manual |
| A4 | All behavioral logic lives in plain `.m` files under `+inverterhilgui\` | manual |
| A5 | `inverter_hil_app.m` classdef (programmatic `uifigure`) is the reviewable source of truth for the app | R2024b batch |
| A6 | `build_inverter_hil_app.m` regenerates the `.mlapp` from the classdef source and guards on `version('-release')` being `2024b` | R2024b batch |
| A7 | `inverter_hil.slx`, `.sldd`, `+inverterhil\`, `inverter_hil_sg_rtw\`, `slprj\`, `.simulink\` are unmodified | manual (`git status`) |
| A8 | No `git commit`/`push`/`checkout`/`reset`/`clean`/`restore` was run | manual |
| A9 | Naming, `%FUNCNAME Summary` headers, `inverterhilgui:*` error identifiers, and validation idiom match `+inverterhil` | lint + manual |
| A10 | Every produced `.m` file is Code-Analyzer clean | lint |
| A11 | Generated `.mlapp` opens and its class instantiates in R2024b | R2024b batch |

## B. Part 29 - App shell, connection lifecycle, theme

| ID | Requirement | Verify |
|---|---|---|
| B1 | App launches with no Speedgoat target present and does not error | R2024b batch |
| B2 | Overview tab is the first screen; no landing page | manual |
| B3 | Tabs present: Overview, Inverters, I/O & CAN, Faults & Scenarios, Logging | manual |
| B4 | Toolbar shows `MFE26 VC INVERTER HIL`, target name, connection state, application state, elapsed target time | manual |
| B5 | Toolbar has Connect, Load, Start, Stop, Reset controls | manual |
| B6 | Disconnected state shows `DISCONNECTED`, disabled controls, and blank/dashed readouts | manual + unittest |
| B7 | No invented, simulated, or animated telemetry when disconnected | manual |
| B8 | Any demo/replay mode is off by default and unmistakably labeled on screen | manual |
| B9 | Theme: background `#090C0E`, panels `#19232D`, green healthy, blue TX/electrical, amber waiting, red fault, muted blue-gray secondary | manual |
| B10 | Dense square layout, compact spacing, small panel radii, no decorative graphics | manual |
| B11 | Connection lifecycle state machine (disconnected/connecting/connected/loaded/running/stopped/error) lives in `+inverterhilgui` and is unit-testable | unittest |
| B12 | Low-rate connection/status/reconciliation uses an App Designer timer, not a busy loop | manual |
| B13 | High-rate observation uses a Simulink Real-Time `Instrument` with callbacks, not a tight `getsignal` poll | manual |
| B14 | Persistent red `TORQUE SCALE UNVERIFIED` banner naming the active provisional 1/512 profile | manual |

## C. Parameter contract indirection (plan 7.1, 7.2)

| ID | Requirement | Verify |
|---|---|---|
| C1 | A single indirection layer maps logical names (`pedals.throttle`, ...) to target parameter paths | unittest |
| C2 | Contract is discovered from the built application on connect | unittest (injected fake) |
| C3 | Missing required path produces a clear version-mismatch error, not a silent fallback | unittest |
| C4 | Layer supports both nested-struct and flat-scalar backings so open decision 16 can be answered later without touching callbacks | unittest |
| C5 | No GUI-side read-modify-write of a whole shared struct anywhere | manual grep + unittest |
| C6 | `getparam` reads target values before controls are enabled | manual + unittest |
| C7 | No automatic push of host defaults on connect | unittest |
| C8 | Normal writes never pass `Force=true` | manual grep |
| C9 | Every logical control declares type, range, and clamp; values are validated and clamped before write | unittest |

## D. Part 30 - Runtime throttle/brake/digital controls

| ID | Requirement | Verify |
|---|---|---|
| D1 | Throttle and brake sliders in percent with numeric readback | manual |
| D2 | Four applied pedal-sensor voltages (AO01-AO04) displayed | manual |
| D3 | Rapid slider movement coalesced to newest value at a 20-50 ms host update rate | unittest |
| D4 | Coalescer drops intermediate values and never reorders | unittest |
| D5 | Digital stimulus toggles for main button, cooling switch, shutdown feedback | manual |
| D6 | Momentary commands (precharge, main button) issued as a `uint32` sequence-counter increment, not a host-timed pulse | unittest |
| D7 | Sequence counter wraps safely and is monotonic modulo 2^32 | unittest |
| D8 | Interlock checkbox required before intentional pedal-plausibility violations are permitted | unittest |
| D9 | Requested and applied values both shown for every command | manual + unittest |
| D10 | Mismatch or failed write shown inline AND written to the session log | unittest |
| D11 | The GUI cannot arm the pedal interface against an unhealthy target | unittest |

## E2. Part 31 - State strip, transition guards, TP6-TP10

| ID | Requirement | Verify |
|---|---|---|
| F1 | State strip `LV_ON > PRECHARGING > ENABLE > BUZZING > RTD` with separate red `ERROR` | manual |
| F2 | Time-in-state displayed | manual |
| F3 | `NEXT TRANSITION` guard panel with pass/fail rows | manual |
| F4 | Guard rows: main button, brake threshold (actual vs required), DC-link 1/2, DC-link 3/4, driver-input plausibility | manual + unittest |
| F5 | Guard evaluation logic is a pure function in `+inverterhilgui` | unittest |
| F6 | Twin DC-link mimic: pair 1/2 and pair 3/4 voltages, raw counts, above-minimum flags, switching frequency | manual |
| F7 | Quiet `CAPTURE PENDING` marker on DC-link and motor-temperature rows | manual |
| F8 | Output-pin cards `VC_SD_OUT` (TP6), `MAIN_EN_OUT` (TP7), `PRECH_EN_OUT` (TP8), `INV_CTRL_EN` (TP9), `INV_CTRL_DIS` (TP10) | manual |
| F9 | Pin cards use ON/OFF text plus color; state is never conveyed by color alone | manual + unittest |
| F10 | AI01-AI04 rail readouts present | manual |

## G. Part 32 - Four inverter panels

| ID | Requirement | Verify |
|---|---|---|
| G1 | Four compact panels `INV1`-`INV4` | manual |
| G2 | Corner label always reads `UNVERIFIED` beside the canonical inverter number | manual + unittest |
| G3 | Each panel shows state, ready, command age | manual |
| G4 | Torque command/actual plus raw torque count | manual |
| G5 | Both 1/256 and 1/512 candidate torque values shown for the raw count | unittest |
| G6 | Speed, Id/Iq shown | manual |
| G7 | Motor and switch temperatures with raw counts | manual |
| G8 | Derating and active fault shown | manual |
| G9 | Per-inverter formatting is a pure function; no cross-channel leakage | unittest |

## H. Part 33 - CAN tables, dual torque, capture status, rates

| ID | Requirement | Verify |
|---|---|---|
| H1 | Left table VCU TX / HIL RX: `0x186`, `0x196`, `0x1A6`, `0x1B6` | manual |
| H2 | Right table HIL TX / VCU RX: `0x383 0x385 0x393 0x395 0x3A3 0x3A5 0x3B3 0x3B5 0x400` | manual |
| H3 | Columns: live state, ID/name, decoded signal, value, measured rate | manual |
| H4 | Recently changed payload rows highlighted | manual + unittest |
| H5 | Measured rate computed from observed timestamps, not assumed from the 5 ms nominal | unittest |
| H6 | CAN diagnostics strip: write status, receive overrun, error warning, bus-off, queue depth, burst duration | manual |
| H7 | Dual-interpreted torque formatting shared with G5 | unittest |

## I. Part 34 - Faults/scenarios, heartbeat, safe fallback

| ID | Requirement | Verify |
|---|---|---|
| I1 | Per-inverter `fault_mask`, `load_nm`, `connected` controls | manual |
| I2 | CAN `drop_control_mask` / `drop_status_mask` controls | manual |
| I3 | GUI heartbeat written as a `uint32` counter on the app timer | unittest |
| I4 | Heartbeat loss, target stop, or application unload returns analog outputs to 0 V and digital stimuli to verified inactive levels | unittest |
| I5 | Fallback logic is a pure function and fails closed on malformed input | unittest |
| I6 | Multi-inverter fault injection requires stopped/Idle plus expert interlock | unittest |
| I7 | Unsafe voltage commands and calibration edits require stopped or expert interlock | unittest |

## J. Control-enable policy (plan open decision 18 - UNRESOLVED)

| ID | Requirement | Verify |
|---|---|---|
| J1 | Exactly one control-policy function in `+inverterhilgui`, keyed by application state, VCU state, and interlock status | unittest |
| J2 | Conservative default: during Drive permit only pedal and digital stimuli | unittest |
| J3 | Calibration, plant params, and fault injection require stopped or Idle plus expert interlock | unittest |
| J4 | The assumption is documented in the function header and in the final report | manual |
| J5 | No callback re-derives enable state independently of the policy function | manual grep |
| J6 | Policy matrix covered by a table-driven unit test over every state x interlock combination | unittest |

## K. Part 35 - Session logging and audit trail

| ID | Requirement | Verify |
|---|---|---|
| K1 | Every operator command records host time, target time, old value, new value, result | unittest |
| K2 | Record construction is a pure function with a fixed field order | unittest |
| K3 | Failed writes and requested/applied mismatches appear in the log | unittest |
| K4 | Log viewable in the Logging tab and exportable to disk | manual |
| K5 | Log is append-only in memory; export does not mutate it | unittest |
| K6 | Log survives disconnect/reconnect within a session | unittest |

## L. Testing

| ID | Requirement | Verify |
|---|---|---|
| L1 | New unittest classes under `tests/inverter_hil` in the existing style | manual |
| L2 | Discovered by `run_inverter_hil_tests.m` (folder-based discovery; confirm it picks them up) | R2024b batch |
| L3 | No test requires a live Speedgoat target | manual |
| L4 | Coverage: contract discovery + version mismatch, validation/clamping, slider coalescing, control-enable policy matrix, audit-record construction, heartbeat/fallback, torque dual-interpretation formatting | manual |
| L5 | Full suite run in R2024b; real counts reported | R2024b batch |
| L6 | The 66 previously passing tests still pass; E6 remains the only pre-existing failure | R2024b batch |

## M. Open assumptions to be called out explicitly

| ID | Assumption |
|---|---|
| M1 | **Open decision 16** (field-level `setparam`): unresolved. The Part 2 spike has not been run. The indirection layer must work with either backing and must not hard-code nested paths in callbacks. |
| M2 | **Open decision 18** (controls allowed during Drive): unresolved. Conservative default per section J, documented in code. |
| M3 | The target parameter contract (Part 3) does not exist yet, so contract discovery cannot be validated against a real MLDATX. It must be tested against an injected fake and must fail loudly, not silently, against a real target that lacks the paths. |
| M4 | Simulink Real-Time target/instrument APIs cannot be exercised without hardware; all target interaction must sit behind a seam that tests can substitute. |
| M5 | Torque scale remains 1/512 provisional; corner mapping remains `UNVERIFIED`. |
| M6 | E6: the model's `SystemTargetFile` is `speedgoat.tlc`, not `slrealtime.tlc`. Out of scope here; the user must decide whether the model or the test is wrong. |
