# Virtual VCU (MATLAB/Simulink R2024b)

This folder contains the bench-only VCU behavior. It reads only the physical
IO183 AI/DI inputs assigned to I/O Module 2, decodes inverter status frames on
IO614 Port A (CAN channel 2), and sends pedal plus four inverter control
frames on that port. It never uses Module 1 signals or Port B in software.

The pedal constants and Ephorus frame layout are extracted from MFE26-VC
`todo` commit `39ea8efd3fc4e88f76e876f94fb99d4adabb7749`; firmware source is
referenced, not copied. `+virtualvcu/step.m` implements
`LV_ON -> PRECHARGING -> ENABLE -> BUZZING -> RTD`. Precharge and buzzer
timing are 7.5 s and 1.5 s at the 1 ms task rate. RTD requires the main-button
DI and at least 25% brake; shutdown feedback forces `ERROR_SHUTDOWN` and safe
torque. Control frames are disabled outside active HV states and torque is
zero outside RTD.

Hardware contract: Module 1 AO01-AO04 -> Module 2 AI01-AI04 through the
documented 17-pin M12 wiring; Module 1 DIO outputs -> Module 2 DI inputs after
level/polarity review. IO614 Port A (channel 2) and Port B (channel 1) are
connected CANH/CANL/ground at 1 Mbit/s with two 120 ohm end terminators.

## Loopback map

| Function | Module 1 source | Module 1 pin | Module 2 input | Module 2 pin | Range/level |
|---|---|---:|---|---:|---|
| Throttle 1 | IO183 AO01 | A1 | AI01 | A7 | 0-5 V |
| Throttle 2 | IO183 AO02 | A2 | AI02 | A8 | 0-5 V |
| Brake 1 | IO183 AO03 | A3 | AI03 | A9 | 0-5 V |
| Brake 2 | IO183 AO04 | A4 | AI04 | A10 | 0-5 V |
| Digital 1-8 | IO183 DIO01-DIO08 | B1-B8 | DI01-DI08 | B1-B8 | conditioned TTL; polarity TBD |

Digital mapping: DI01 precharge, DI02 main/RTD button, DI03 cooling, DI04 fan,
and DI05 shutdown feedback. DI06-DI08 are reserved.

Analog ground uses A5/A6/A17 and digital reference uses B17 only after the
ground strategy and signal conditioning are verified. Do not connect 12/24 V
directly to IO183 digital pins.

## DBC cross-check

`config/MFE26_Inverter.dbc` is the supplied `MFE26_Inverter.dbc` (SHA-256
`F5AE64DA3A77D0E071419CC11980FB24A69CA3469A703C855CB6C954F7F429C3`). It
matches the model and firmware contract: control IDs `0x186/0x196/0x1A6/0x1B6`,
status IDs `0x383/0x385/0x393/0x395/0x3A3/0x3A5/0x3B3/0x3B5/0x400`, DLC 8,
standard 11-bit identifiers, and torque-limit scale 1/256 Nm/count. The
firmware's pedal broadcast `0x1F5` is not defined in this inverter DBC and is
therefore kept as an explicit VCU-side contract in `packPedalFrame.m`.

Local verification is host-only. No physical analog loopback, CAN ACK, target
build, or deployment is claimed until it is captured on the bench.

## R2024b validation

From the HIL repository root:

```powershell
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'inverter_hil')); build_inverter_hil_model(true);"
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'inverter_hil')); cd(fullfile(pwd,'inverter_hil')); verify_inverter_hil_model;"
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "addpath(fullfile(pwd,'virtual-vcu')); addpath(fullfile(pwd,'virtual-vcu','tests')); run_virtual_vcu_tests;"
```

The GUI remains `inverter_hil/inverter_hil_app.mlapp`; target telemetry is
unknown until a target observation exists. The generated model is integrated,
and R2024b TLC plus object compilation completed locally. The final QNX link
was blocked by the existing OneDrive path-with-spaces toolchain invocation, so
no fresh `inverter_hil.mldatx` claim is made from this pass. Target
deployment/start, physical Port A/Port B ACKs, and analog loopback evidence
remain hardware-dependent and unverified here.
