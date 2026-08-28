# eVTOL Powertain HIL

**About**

This reference example demonstrates system-level and component-level hardware-in-the-loop (HIL) testing for powertrain ECUs of a fully-electric vertical take-off and landing aircraft (eVTOL). The eVTOL powertrain includes a 400V lithium battery pack, implemented using Simscape™ Battery™, and four 200kW propulsion motor drives modeled as permanent magnet synchronous motors (PMSMs) with two-level three-phase inverters. In addition to the powertrain, the eVTOL plant model also includes a flight controller and flight dynamics.

HIL simulation of the powertrain components is powered by FPGA-based motor drive simulation, featuring encoder and current sensing emulation, as well as realistic battery cell-level emulation for 24 of the 100 cells in the eVTOL battery pack. The aircraft and environment can be visualized in a photorealistic 3D environment powered by Unreal Engine® from Epic Games.

The provided HIL setup enables testing of the following powertrain ECUs:
- The motor control unit (MCU) governing one of the 200kW electric drives
- The battery management system (BMS), which includes a battery management unit (BMU) and two cell monitoring units (CMUs).

**Learn how to:**

- Model a 400V battery system using Simscape™ Battery™.
- Interface the battery model with battery cell emulation hardware.
- Simulate eVTOL propulsion motor drives, capturing current ripples and switching harmonics.
- Implement bus and signal-level communication with real ECUs.
- Perform HIL testing at both system and component levels.
- Accelerate testing with automated and continuous integration workflows.
- Visualize the aircraft and environment in a photorealistic 3D environment.
----------

**Getting started**

    1. Open MATLAB® and open Simulink® Project File
    2. Click in 'Getting Started' project shortcut
    3. Follow steps in live script documentation

----------

**Release notes**

> **R2024b_v1 - OCT 2024**
 -  MATLAB® R2024b release

> **R2024a_v1 - OCT 2024**
 -  MATLAB® R2024a release

**© 2007 – 2024 Speedgoat GmbH**
