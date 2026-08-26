# CarMaker 12.0.1 ↔ Speedgoat Baseline interface research

## Executive summary

- The documented close-coupled route is to put CarMaker in the **same generated/compiled real-time application** as the control model. CarMaker for Simulink is an S-function integration, and its blocks run at CarMaker's fixed application step (default 1 ms); the Simulink-Coder route instead makes a CarMaker executable containing generated model code. Neither local manual identifies Speedgoat as a supported CarMaker/HIL target, so applicability to TargetPC1 is **not verified**. [ProgrammersGuide.pdf, §6, p. 172; §6.2.1, p. 180; §8.2, pp. 269-270]
- If that target integration can be licensed/supported, expose only the closed-loop boundary needed by the bench: driver/pedal demand into CarMaker and vehicle longitudinal/wheel-speed/torque-relevant feedback out, as explicitly named Simulink signals or CarMaker dictionary quantities. The CarMaker subsystem documents Driver/VehicleControl and powertrain/wheel interfaces; the exact chosen signals and units remain an engineering design decision. [ProgrammersGuide.pdf, §6.3, pp. 228-234]
- A physical CAN route is documented on the CarMaker/HIL side: its Rest Bus Configurator imports a CANdb (`.dbc`), separates real from simulated ECUs, maps signals to CarMaker Data Dictionary quantities/functions, and selects a configured physical CAN channel. This makes `MFE26_Inverter.dbc` a plausible **CarMaker-side contract**, but it does not make CarMaker's CAN interface appear on the Speedgoat automatically. A physical CAN adapter/channel on the CarMaker real-time host and a terminated bus still have to exist. [UsersGuide_HIL.pdf, §4, pp. 53-56, 58, 68]
- Do not treat IPGControl, the CM4SL GUI TCP port, or XCP-on-Ethernet as a documented deterministic Speedgoat plant-data link. The local manuals document IPGControl visibility of Data Dictionary quantities, GUI connection on TCP 12350, and XCP configuration for an ECU/A2L with CAN or Ethernet transports; they do not document a generic CarMaker-to-Speedgoat real-time signal protocol. [ProgrammersGuide.pdf, §6.1.1, p. 174; §6.2.3, pp. 182-185; UsersGuide_HIL.pdf, §5.1-5.2, pp. 81-85, 101-107]

## 1. Real-time coupling mechanisms actually evidenced in the local documentation

### A. CarMaker embedded in a Simulink/real-time application — documented concept; Speedgoat support unverified

CarMaker for Simulink is described as an S-function/API integration inside Matlab/Simulink, explicitly “not a loosely coupled co-simulation.” The CarMaker blocks are connected like Simulink blocks. The blockset runs direct-feedthrough at the fixed CarMaker application step (default 1 ms), independently of the rest of the model; its block chain must execute in order and exactly once, with no algebraic loops through individual CarMaker blocks. [ProgrammersGuide.pdf, §6, p. 172; §6.2.1-6.2.2, pp. 180-181]

For a generated application, the Simulink Coder interface generates C code and links it with CarMaker libraries so that the Simulink model is an integral part of the CarMaker executable, “standalone or under realtime conditions.” The manual’s listed HIL architectures are Xpack4, dSPACE DS1006/SCALEXIO, and NI PXI (through the corresponding templates); the HIL user guide gives detailed build flows for dSPACE and NI, not Speedgoat. Therefore, **the integration pattern is documented, but a supported CarMaker 12.0.1 build/deployment to this Speedgoat Baseline target is not established by the installed documents**. [ProgrammersGuide.pdf, §8, pp. 269-270, 279; UsersGuide_HIL.pdf, §2.2.4, pp. 12-19; §2.2.6, pp. 20-23]

What must be exposed/configured if a supported Speedgoat route is obtained:

- Put the CarMaker subsystem and the existing virtual-VCU/inverter model in one fixed-step generated model/application. For generated plug-ins, the documented baseline is fixed-step, `ode1`, 0.001 s and SingleTasking; variable-step solvers are not supported. This is a CarMaker generated-plugin requirement, not proof of the existing target model's solver settings. [ProgrammersGuide.pdf, §8.5.1, p. 278]
- Preserve the CarMaker block-chain ordering and use `Sync_In`/`Sync_Out` to select the point at which dictionary quantities are read/overridden. [ProgrammersGuide.pdf, §6.2.2, p. 181]
- Use top-level Inports/Outports in a generated plug-in, which the wrapper moves to/from CarMaker C variables around `DoOneStep`; alternatively use the documented CarMaker `From/To CM Var` blocks. [ProgrammersGuide.pdf, §8.5.3, p. 282]
- Use one of the documented model-class wrappers (for example `VehicleControl`, `PTMotor`, `PTMotorCU`, `PowerTrain`, `Vehicle_Car`) when it matches the intended insertion point; otherwise the Plain wrapper requires manual calls. The interface buses and their signal names are documented in the CarMaker subsystem tables. [ProgrammersGuide.pdf, §8.2.2, pp. 271-273; §8.3, pp. 274-275; §6.3, pp. 228-234; §8.6, p. 284]

The existing `src_cm4sl` project corroborates the local installation context, not Speedgoat compatibility: `CM_Main.c` identifies CarMaker 12.0.1 and includes `CarMaker4SL.h`; `CM_Vehicle.c` registers CM4SL vehicle components; `IO.c` has `-io can`/`-io flexray` configuration entries and CarMaker/HIL MIO initialization. `ModelUpdate_CM12.m` treats `generic.mdl` as a CM4SL model and updates IPG S-functions. None of those files names Speedgoat, its I/O modules, TargetPC1, or an interface protocol for it.

### B. CarMaker/HIL CAN Rest Bus Simulation — documented, but requires CarMaker CAN I/O

The HIL Rest Bus Configurator accepts FIBEX, AUTOSAR, and CANdb network descriptions and generates the communication/interface information plus a mapping table between bus protocol elements and CarMaker quantities/functions. A `.dbc` is an accepted database; ECUs are explicitly classified as simulated or real. [UsersGuide_HIL.pdf, §4, pp. 53, 55-56]

For CAN, the RBS configuration selects one CAN channel at a time. It gets channel information from the IO Configurator and requires that channel to be active. If the CAN interface is not otherwise used, the manual says an `IO.c` `IO_Init()` extension is required to set the slot and initialize the CAN/CANFD module, followed by a freshly compiled CarMaker executable. [UsersGuide_HIL.pdf, §4.5.2 “CAN”, p. 68]

The signal mapping choices include Data Dictionary mapping (with factor/offset/min/max conversion) and constants; the RBS generator also supports rolling counters, CRC/E2E mapping, real-time-expression triggers, and C-code hooks. CAN frame/PDU transmission can be cyclic or on-event; cyclic PDUs use their configured cycle time and CarMaker distributes CAN-frame timing to avoid overflow. [UsersGuide_HIL.pdf, §4.5, pp. 58-62; §4.9, pp. 73-75]

This is a viable mechanism only in this topology:

```text
CarMaker/HIL real-time host + configured physical CAN channel
       ↕ physical, terminated 1-Mbit/s CAN
Speedgoat IO614 Port A / CAN channel 2 ↔ virtual VCU + inverter HIL
```

The manuals support the CarMaker half of that diagram; they do **not** state that a Windows/Office CarMaker virtual CAN network is bridgeable to a Speedgoat CAN port. The documented virtual-CAN module is a CarMaker virtual network (up to eight nodes) enabled with `-io can`; it is not documented as an Ethernet CAN tunnel or external-PC interface. [UsersGuide_HIL.pdf, §3.6.4 “virtual CAN Module - vCAN”, p. 51]

### C. XCP/CCP — documented for ECU calibration/measurement, not verified as a CarMaker vehicle-dynamics link

CarMaker's XCP dialog selects one or more ECUs, reads measurement/characteristic variables from the referenced ASAP2/A2L data, and maps selected variables to CarMaker Data Dictionary quantities. XCP configuration supports CAN (interface selected from the IO Configurator, CAN IDs, CAN-FD settings and DAQ lists) and Ethernet (TCP or UDP preference, IP/hostname, and port); DAQ/STIM events include a cycle time and timestamp options. [UsersGuide_HIL.pdf, §5.1-5.2, pp. 81-85, 98-103, 106-108]

Thus XCP is potentially usable if the external application deliberately implements an XCP ECU/slave interface with a valid A2L and compatible timing. It is **not** documented here as a generic way to step CarMaker's vehicle dynamics remotely, nor do the manuals name a Speedgoat XCP server/client configuration or an XCP data model for this bench. It should not be selected as the primary closed-loop architecture without vendor confirmation and an explicit A2L/role design.

### D. Standalone CarMaker on a separate PC using a generic network protocol — not confirmed

The CM4SL manual documents TCP port 12350 only for Matlab to contact the CarMaker GUI, and the model configuration gives an APO server application name discoverable in IPGControl. It documents dictionary read/write/definition blocks for simulation and monitoring. [ProgrammersGuide.pdf, §6.1.1, p. 174; §6.2.3-6.2.4, pp. 182-185]

Those statements do not specify a real-time user-signal protocol, message schema, peer role, timing contract, or network port for a separate Speedgoat target. I found no local-PDF support for claiming a standalone-PC-over-Ethernet hard-real-time coupling path. The CarMaker FMU also does not fill this gap: it is explicitly limited to CarMaker Office and is driven by an FMI master using `fmi2DoStep`; it is a software co-simulation interface, not a documented Speedgoat deployment path. [ProgrammersGuide.pdf, §10, pp. 319-322]

## 2. Required exposed signals and configuration for this bench

### Minimum closed-loop boundary (recommended design, not an existing CarMaker configuration)

The bench needs an explicit contract; CarMaker does not infer the virtual-VCU CAN contract from vehicle dynamics. A conservative boundary is:

| Direction | Boundary signal family | Why / local basis |
|---|---|---|
| CarMaker → bench | accelerator demand, service-brake demand, key/driver-state as required | CarMaker exposes Driver/VehicleControl gas, brake, key, selector, gear and steering interfaces. [ProgrammersGuide.pdf, §6.3, pp. 229-230] |
| CarMaker → bench | wheel speeds/vehicle velocity and, if modeled, motor/shaft speed/load | CarMaker documents wheel/powertrain interface quantities, but the exact virtual-VCU consumption and scaling are not established in this repository. [ProgrammersGuide.pdf, §6.3, pp. 231-234] |
| Bench → CarMaker | actual/available drive torque, inverter/VCU fault and readiness state | This is needed for a physical closed loop, but no existing virtual-VCU-to-CarMaker mapping was found. The actual bench currently exchanges inverter frames, not CarMaker signals. |

For embedded CM4SL, these should be named Simulink ports or dictionary variables. `Read CM Dict`, `Write CM Dict`, `Define CM Dict`, and Signal Access blocks are documented ways to read, write, define, and make quantities visible to IPGControl/DVA; they are not a substitute for the Speedgoat I/O or CAN marshalling block itself. [ProgrammersGuide.pdf, §6.2.3-6.2.4, pp. 182-185]

For CAN RBS, import `MFE26_Inverter.dbc`, select real versus simulated ECUs, activate/select the physical CAN channel in CarMaker's IO Configurator, map each selected signal to a CarMaker Data Dictionary quantity/function, and configure the DBC-defined frame cycle/trigger behavior. The configurator saves the RBS mapping and CAN communication information in `Data/Config`; it can also place the resulting RBS parameters reference in `ECUParameters`. [UsersGuide_HIL.pdf, §4.2, pp. 55-56; §4.5, pp. 58-62; §4.6, pp. 70-71; §4.9, pp. 73-75]

## 3. Assessment against the actual TargetPC1 CAN contract

### Verified bench facts

- TargetPC1 is `10.10.10.5`. `PINOUTS.md` identifies IO614 as the four-channel HS-CAN/LIN module, maps connector A to CAN channel 2 and connector B to CAN channel 1, and records the virtual VCU on Port A/channel 2 at 1 Mbit/s. `README.md` says the existing virtual VCU reads inverter status and transmits pedal plus four control frames on that port.
- `virtual-vcu/+virtualvcu/config.m` sets CAN channel 2, Port A, `1e6` bit/s, DLC 8, control IDs `0x186/0x196/0x1A6/0x1B6`, status IDs `0x383/0x385/0x393/0x395/0x3A3/0x3A5/0x3B3/0x3B5/0x400`, and pedal CAN ID `0x1F5` (501 decimal). `README.md` records standard 11-bit IDs and that `0x1F5` is not in `MFE26_Inverter.dbc`.
- The same README records a 1 ms virtual-VCU task with 7.5 s precharge and 1.5 s buzzer states. It expressly says physical CAN ACK and target deployment remain unverified. `PINOUTS.md` records that the IO614 interface itself has no termination and uses HS CANL pin 2 / CANH pin 7, so the physical bus must have two end terminators.

### Is CAN coupling plausible?

**Yes, conditionally:** CarMaker 12.0.1 HIL documents a DBC-driven CAN RBS that can communicate with real ECUs and map received/transmitted DBC signals to CarMaker quantities. The bench's `MFE26_Inverter.dbc` is therefore a suitable input artifact for CarMaker's RBS configuration. [UsersGuide_HIL.pdf, §4, pp. 53-56, 58; §4.5.2 “CAN”, p. 68]

**But it is not proven deployable with the installed components:** the local documentation does not say that CarMaker 12.0.1 can run its CAN RBS on the Speedgoat machine, directly use Speedgoat IO614, or bridge CarMaker virtual CAN across Ethernet into IO614. A real CAN connection requires CarMaker to run on a supported HIL/real-time platform with a configured CAN channel, then cable that channel to the Speedgoat Port A bus with bitrate, 11-bit-ID filters, grounding, and termination checked. The existing Port A already has a virtual VCU transmitter, so the CarMaker ECU assignment must prevent duplicate transmitters for `0x186/0x196/0x1A6/0x1B6`, `0x1F5`, or the status IDs.

### What CarMaker should calculate versus what the bench must marshal

If CAN RBS is chosen, CarMaker should calculate vehicle dynamics locally and expose/map the specific quantities that correspond to DBC signals; its RBS layer then performs the DBC frame encoding/decoding. The existing bench application remains responsible for its current virtual-VCU and inverter state machines. This follows the documented RBS quantity mapping model; it does not mean CarMaker natively understands the MFE26 torque semantics. [UsersGuide_HIL.pdf, §4, pp. 53, 58-62]

If embedded CM4SL is chosen, CarMaker can provide ordinary Simulink signals/dictionary quantities such as gas/brake and wheel/powertrain data. The existing virtual-VCU application would need explicit new signal-to-CAN marshalling to its current `0x1F5` pedal and inverter-control/status contract; neither the bench files nor CarMaker manuals show such a marshaller today. [ProgrammersGuide.pdf, §6.3, pp. 228-234; §8.5.3, p. 282]

## 4. Evidence boundary and recommended decision

### Recommended sequencing

1. Obtain written IPG confirmation of CarMaker 12.0.1 support for the exact Speedgoat Baseline/target OS and R2024b code-generation path. Do not start from an assumption that dSPACE/NI instructions apply to Speedgoat.
2. If unsupported, use a separate supported CarMaker/HIL machine with a physical CAN interface and make `MFE26_Inverter.dbc` the only inter-machine contract. Configure CarMaker RBS as the simulated vehicle-side ECU(s), the Speedgoat virtual VCU/inverter endpoints as real ECU(s), and create an ID ownership/cycle-time table before connecting the bus.
3. If supported in one target application, make the connection at fixed-step Simulink ports/dictionary variables first, then add a deliberately specified CAN marshaller only where the existing VCU/inverter behavior must see frames. Keep one timing owner and avoid algebraic loops.

## Open questions / unverified

- No local manual passage found that lists **Speedgoat**, `TargetPC1`, Speedgoat IO614, Simulink Real-Time/Speedgoat target files, or a supported CarMaker 12.0.1 deployment recipe for this hardware. Whether CarMaker can be compiled into the existing R2024b Speedgoat application is unverified.
- No local manual passage found for a generic standalone CarMaker ↔ Speedgoat Ethernet real-time signal protocol, its port numbers, synchronization/clock discipline, or latency/jitter limits. The TCP 12350 reference is GUI/Matlab connection only. [ProgrammersGuide.pdf, §6.1.1, p. 174]
- No local manual passage found that turns CarMaker virtual CAN into external CAN, an Ethernet tunnel, or a Speedgoat IO614 endpoint. Virtual CAN therefore cannot be assumed to close this physical bench loop. [UsersGuide_HIL.pdf, §3.6.4, p. 51]
- The exact vehicle model, wheel/motor topology, torque-to-wheel mapping, pedal interpretation, and feedback signals necessary for a meaningful vehicle-dynamics loop are absent from the specified bench contract. `MFE26_Inverter.dbc` defines the inverter-side frames but does not by itself define a CarMaker vehicle interface.
- Physical status is not confirmed: the virtual-VCU README explicitly withholds claims of target deployment, Port A/Port B CAN ACK, and analog loopback; CAN termination and transmitter ownership must be checked on the actual wiring before energizing the bus.

## 5. Outcome (2026-08-14)

An XCP-over-Ethernet architecture was carried as the chosen direction for two
days and then abandoned. Bench evidence showed the installed setup produced
MEASUREMENT/DAQ reads but never CHARACTERISTIC writes, so CarMaker could
observe the Speedgoat but could not command it — which is the half this bench
actually needs. The build checklists that accompanied that direction have been
removed along with the implementation.

The bench uses physical CAN instead: CarMaker drives pedal demand on ID `0x500`
(`inverter_hil/docs/can_pedal_demand_frame_spec.md`) and reads inverter status
back over the same bus. See `carmaker_real_vcu_can_interface_plan.md` for the
current interface contract and `carmaker/docs/can_setup_walkthrough.md` for the
CarMaker-side configuration.
