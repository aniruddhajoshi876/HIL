# Minimal virtual VCU (MATLAB/Simulink R2024b)

This folder contains the bench-only LV_ON VCU behavior. It reads only the
physical IO183 inputs assigned to I/O Module 3, sends CAN on IO614 Port A
(CAN channel 2), and receives inverter status frames from that port. It never
uses the inverter's Module 1 signals or Port B in software.

The pedal constants and Ephorus frame layout are extracted from MFE26-VC
`todo` commit `39ea8efd3fc4e88f76e876f94fb99d4adabb7749`; firmware source is
referenced, not copied. `+virtualvcu/step.m` starts enabled in `LV_ON` and
produces the minimum pedal plus four inverter-control payloads.

Hardware contract: Module 1 AO01-AO04 -> Module 3 AI01-AI04 through the
documented 17-pin M12 wiring; Module 1 DIO outputs -> Module 3 DI inputs after
level/polarity review. IO614 Port A (channel 2) and Port B (channel 1) are
connected CANH/CANL/ground at 1 Mbit/s with two 120 ohm end terminators.

## Loopback map

| Function | Module 1 source | Module 1 pin | Module 3 input | Module 3 pin | Range/level |
|---|---|---:|---|---:|---|
| Throttle 1 | IO183 AO01 | A1 | AI01 | A7 | 0-5 V |
| Throttle 2 | IO183 AO02 | A2 | AI02 | A8 | 0-5 V |
| Brake 1 | IO183 AO03 | A3 | AI03 | A9 | 0-5 V |
| Brake 2 | IO183 AO04 | A4 | AI04 | A10 | 0-5 V |
| Digital 1-8 | IO183 DIO01-DIO08 | B1-B8 | DI01-DI08 | B1-B8 | conditioned TTL; polarity TBD |

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
and the R2024b Speedgoat build completed locally, producing
`inverter_hil.mldatx`. Target deployment/start, physical Port A/Port B ACKs,
and analog loopback evidence remain hardware-dependent and unverified here.
