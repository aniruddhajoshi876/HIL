# MFE26 HIL - Real-VCU CAN Signal Map

Interface contract for the **real-VCU bench**. Every CAN frame on the bench is
defined here: direction, cycle time, bit layout, encoding, and acceptance rules.

> **This is a source/interface contract, not evidence.** Host code, a model, and
> a DBC do not by themselves prove that the physical CarMaker PC, Speedgoat, real
> VCU, CAN harness, or inverters are connected and operating. See
> [Section 11 - Evidence boundaries](#11-evidence-boundaries).

---

## CAN ID quick reference

|                              Sec                              | CAN ID(s)                               | Frame                          | Direction                     | Cycle            |
| :-----------------------------------------------------------: | --------------------------------------- | ------------------------------ | ----------------------------- | ---------------- |
|              [1](#1-0x500---carmakerpedaldemand)              | `0x500`                               | CarMakerPedalDemand            | CarMaker -> Speedgoat         | 10 ms            |
| [3](#3-0x186--0x196--0x1a6--0x1b6---real-vcu-inverter-control) | `0x186` `0x196` `0x1A6` `0x1B6` | Inverter control               | Real VCU -> inverters         | per VCU logic    |
|     [4](#4-0x383--0x393--0x3a3--0x3b3---inverter-status-a)     | `0x383` `0x393` `0x3A3` `0x3B3` | Inverter Status A              | Inverters -> Speedgoat        | inverter-defined |
|     [5](#5-0x385--0x395--0x3a5--0x3b5---inverter-status-b)     | `0x385` `0x395` `0x3A5` `0x3B5` | Inverter Status B              | Inverters -> Speedgoat        | inverter-defined |
|                  [6](#6-0x400---dclinkstatus)                  | `0x400`                               | DCLinkStatus                   | Inverters -> Speedgoat        | inverter-defined |
|         [7](#7-0x501---carmakerinvertertorquesetpoint)         | `0x501`                               | CarMakerInverterTorqueSetpoint | Speedgoat -> CarMaker         | 5 ms             |
|             [8](#8-0x502---carmakerinverterready)             | `0x502`                               | CarMakerInverterReady          | Speedgoat -> CarMaker         | 5 ms             |
|       [9](#9-0x032--0x034--0x2b0---raw-sensor-messages)       | `0x032` `0x034` `0x2B0`           | Raw sensor messages            | Sensors -> Speedgoat/CarMaker | undefined here   |

## Section index

**Frames and interfaces**
[1. `0x500` CarMakerPedalDemand](#1-0x500---carmakerpedaldemand) |
[2. Speedgoat analog interface](#2-speedgoat-analog-interface-to-the-real-vcu) |
[3. Inverter control](#3-0x186--0x196--0x1a6--0x1b6---real-vcu-inverter-control) |
[4. Status A](#4-0x383--0x393--0x3a3--0x3b3---inverter-status-a) |
[5. Status B](#5-0x385--0x395--0x3a5--0x3b5---inverter-status-b) |
[6. `0x400` DC link](#6-0x400---dclinkstatus) |
[7. `0x501` torque telemetry](#7-0x501---carmakerinvertertorquesetpoint) |
[8. `0x502` ready telemetry](#8-0x502---carmakerinverterready) |
[9. Raw sensors](#9-0x032--0x034--0x2b0---raw-sensor-messages)

**Behaviour and integration**
[10. 20% example](#10-real-vcu-only-end-to-end-example-at-20-throttle) |
[11. Evidence boundaries](#11-evidence-boundaries) |
[12. CarMaker FS_race / CM4SL](#12-carmaker-fs_race-and-cm4sl-integration) |
[13. IO.c receive path](#13-ioc-receive-path-for-carmaker-telemetry) |
[14. TorqueVect interface](#14-torquevect_hil_canmdl-interface) |
[15. CAN state machines](#15-can-state-machines) |
[16. Full 20% walkthrough](#16-end-to-end-20-real-vcu-example) |
[17. Source references](#17-source-level-references-in-this-checkout)

---

## Scope

This document describes the **intended real-VCU bench only**. It does not use the
virtual VCU as a system participant.

### Forward path

```
  CarMaker
      |
      | 0x500 CarMakerPedalDemand over CAN
      v
  Speedgoat IO614
      |
      | validated throttle/brake demand converted to analog voltages
      v
  Speedgoat IO183 analog outputs
      |
      | physical wiring
      v
  Real VCU pedal inputs
      |
      | real VCU safety/state/torque logic
      v
  Real VCU CAN output
      |
      | 0x186, 0x196, 0x1A6, 0x1B6
      v
  Ephorus inverters
```

### Return path

```
  Ephorus inverters
      |
      | inverter status frames
      v
  Speedgoat IO614
      |
      +--> status observation
      +--> CarMaker telemetry 0x501 and 0x502
```

---

## CAN conventions

All frames below are **standard 11-bit CAN data frames with DLC 8** unless stated
otherwise.

**Intel / little-endian convention**

- Byte 1 is the first CAN data byte.
- Bit 0 is the least-significant bit of Byte 1.
- A 16-bit field starting at bit 0 sends its low byte first.
- Unassigned bits are reserved or unused and are **not** additional commands.

---

---

# 1. `0x500` - CarMakerPedalDemand

|                         |                                                                         |
| ----------------------- | ----------------------------------------------------------------------- |
| **Direction**     | CarMaker -> Speedgoat IO614 -> Speedgoat pedal-output logic -> real VCU |
| **Nominal cycle** | 10 ms                                                                   |

**Purpose.** CarMaker provides the requested accelerator and brake values.
Speedgoat receives and validates this frame, then converts the values into the
calibrated analog signals presented to the real VCU pedal inputs.

### Bit map

|   Bits |       Bytes | Signal             | Encoding / scale                | Meaning                                         |
| -----: | ----------: | ------------------ | ------------------------------- | ----------------------------------------------- |
|  0..15 |        1..2 | `ThrottleDemand` | Unsigned u16, raw x 0.01%       | Requested accelerator percentage; 2000 = 20.00% |
| 16..31 |        3..4 | `BrakeDemand`    | Unsigned u16, raw x 0.01%       | Requested brake percentage                      |
|     32 |     5 bit 0 | `Active`         | Boolean                         | Requests CAN ownership of both pedals           |
| 33..36 | 5 bits 1..4 | `AliveCounter`   | Unsigned 4-bit, modulo 16       | Must advance on each accepted cyclic frame      |
| 37..39 | 5 bits 5..7 | `Reserved0`      | Must be zero                    | Nonzero invalidates the pedal tuple             |
| 40..47 |           6 | `Integrity`      | CRC-8/SAE-J1850 over Bytes 1..5 | Application integrity check                     |
| 48..63 |        7..8 | `Reserved1`      | Must be zero                    | Nonzero invalidates the pedal tuple             |

### Speedgoat acceptance rules

All of the following must hold:

- Standard, non-extended frame.
- Not a remote frame.
- ID = `0x500`.
- DLC = 8.
- Both pedal values <= 10000.
- `Reserved0` and `Reserved1` are zero.
- CRC is correct.
- `AliveCounter` advances.
- Latest accepted frame is less than 100 ms old.
- `Active` = 1.

> **If any required condition fails**, Speedgoat must not present the invalid CAN
> value as a valid real-VCU pedal command. The throttle and brake pair must lose
> CAN ownership **together**.

### Worked value - 20% accelerator demand

```
  ThrottleDemand = 2000 decimal = 0x07D0
  Bytes 1..2     = D0 07
```

This does **not** directly command inverter torque. It commands the real VCU
pedal input. The real VCU still decides whether torque is permitted.

---

# 2. Speedgoat analog interface to the real VCU

The `0x500` percentage values do not go directly into the real-VCU CAN control
frames. Speedgoat converts them to calibrated analog pedal signals.

| Channel    | IO183 output  | Real VCU input     |
| ---------- | ------------- | ------------------ |
| Throttle 1 | Module 1 AO01 | throttle channel 1 |
| Throttle 2 | Module 1 AO02 | throttle channel 2 |
| Brake 1    | Module 1 AO03 | brake channel 1    |
| Brake 2    | Module 1 AO04 | brake channel 2    |

> The exact real-VCU connector pins, voltage polarity, source/sink behavior,
> grounding, and conditioning must be verified against the approved harness and
> real VCU electrical documentation. **The CAN frame map cannot prove these
> analog-electrical details.**

The real VCU then performs its own:

- dual-throttle plausibility check;
- brake plausibility check;
- accelerator/brake interlock;
- LV/HV/precharge state handling;
- RTD/drive authorization;
- shutdown/fault handling; and
- torque-request generation.

---

# 3. `0x186` / `0x196` / `0x1A6` / `0x1B6` - Real-VCU inverter control

|                     |                                     |
| ------------------- | ----------------------------------- |
| **Direction** | Real VCU -> CAN -> Ephorus inverter |

### ID mapping

| CAN ID    | Target             |
| --------- | ------------------ |
| `0x186` | Inverter 1 control |
| `0x196` | Inverter 2 control |
| `0x1A6` | Inverter 3 control |
| `0x1B6` | Inverter 4 control |

Each ID has the same layout. **The ID selects the inverter.**

### Bit map

|   Bits |          Bytes | Signal                  | Encoding / scale         | Meaning                       |
| -----: | -------------: | ----------------------- | ------------------------ | ----------------------------- |
|      0 |        1 bit 0 | `EnableInverter`      | Boolean                  | Requests inverter enable      |
|      1 |        1 bit 1 | `ResetError`          | Boolean                  | Requests inverter error reset |
|      2 |        1 bit 2 | `ASCallowed`          | Boolean                  | Allows ASC behavior           |
|      3 |        1 bit 3 | `CurrentControl`      | Boolean                  | Selects current-control mode  |
|  4..15 | 1 bits 4..7, 2 | `Reserved`            | Unused                   | No defined command            |
| 16..31 |           3..4 | `SpeedSetpoint`       | Signed i16, RPM          | Motor speed setpoint          |
| 32..47 |           5..6 | `TorqueLimitPositive` | Signed i16, raw / 256 Nm | Positive torque limit         |
| 48..63 |           7..8 | `TorqueLimitNegative` | Signed i16, raw / 256 Nm | Negative/regen torque limit   |

These existing inverter control frames have **no application-level alive counter
or application CRC** in the branch contract. They still use normal CAN
link-layer error detection.

> The real VCU should transmit these frames only according to its actual safety
> and drive-state logic. A 20% pedal request does not imply that
> `EnableInverter` must be 1 or that a nonzero torque command must be accepted.

---

# 4. `0x383` / `0x393` / `0x3A3` / `0x3B3` - Inverter Status A

|                     |                                                               |
| ------------------- | ------------------------------------------------------------- |
| **Direction** | Ephorus inverter -> CAN -> Speedgoat and CarMaker observation |

### ID mapping

| CAN ID    | Source              |
| --------- | ------------------- |
| `0x383` | Inverter 1 Status A |
| `0x393` | Inverter 2 Status A |
| `0x3A3` | Inverter 3 Status A |
| `0x3B3` | Inverter 4 Status A |

### Bit map

|   Bits |          Bytes | Signal             | Encoding / scale           | Meaning             |
| -----: | -------------: | ------------------ | -------------------------- | ------------------- |
|   0..1 |    1 bits 0..1 | `InverterState`  | Unsigned 2-bit, 0..3       | Inverter state code |
|      2 |        1 bit 2 | `InverterReady`  | Boolean                    | Inverter ready flag |
|  3..15 | 1 bits 3..7, 2 | `Reserved`       | Unused                     | No defined status   |
| 16..27 | 3..4 bits 0..3 | `TorqueActual`   | Signed 12-bit, raw / 32 Nm | Actual torque       |
| 28..39 | 4 bits 4..7, 5 | `TorqueSetpoint` | Signed 12-bit, raw / 32 Nm | Torque setpoint     |
| 40..63 |           6..8 | `Reserved`       | Unused                     | No defined status   |

---

# 5. `0x385` / `0x395` / `0x3A5` / `0x3B5` - Inverter Status B

|                     |                                                               |
| ------------------- | ------------------------------------------------------------- |
| **Direction** | Ephorus inverter -> CAN -> Speedgoat and CarMaker observation |

### ID mapping

| CAN ID    | Source              |
| --------- | ------------------- |
| `0x385` | Inverter 1 Status B |
| `0x395` | Inverter 2 Status B |
| `0x3A5` | Inverter 3 Status B |
| `0x3B5` | Inverter 4 Status B |

### Bit map

|   Bits |                    Bytes | Signal          | Encoding / scale             | Meaning           |
| -----: | -----------------------: | --------------- | ---------------------------- | ----------------- |
|  0..11 | 1 bits 0..7, 2 bits 0..3 | `Reserved`    | Unused                       | No defined status |
| 12..23 | 2 bits 4..7, 3 bits 0..3 | `IdActual`    | Signed 12-bit, raw / 16 Arms | d-axis current    |
| 24..35 | 3 bits 4..7, 4 bits 0..3 | `Reserved`    | Unused                       | No defined status |
| 36..47 | 4 bits 4..7, 5 bits 0..3 | `IqActual`    | Signed 12-bit, raw / 16 Arms | q-axis current    |
| 48..63 |                     7..8 | `SpeedActual` | Signed i16, RPM              | Motor speed       |

---

# 6. `0x400` - DCLinkStatus

|                     |                                                               |
| ------------------- | ------------------------------------------------------------- |
| **Direction** | Ephorus inverter -> CAN -> Speedgoat and CarMaker observation |

### Bit map

|   Bits | Bytes | Signal                    | Encoding / scale         | Meaning                       |
| -----: | ----: | ------------------------- | ------------------------ | ----------------------------- |
|  0..15 |  1..2 | `DCLinkVoltage12Actual` | Unsigned u16, raw / 64 V | DC link for inverter pair 1/2 |
| 16..31 |  3..4 | `DCLinkVoltage34Actual` | Unsigned u16, raw / 64 V | DC link for inverter pair 3/4 |
| 32..63 |  5..8 | `Reserved`              | Unused                   | No defined status             |

---

# 7. `0x501` - CarMakerInverterTorqueSetpoint

|                         |                                                      |
| ----------------------- | ---------------------------------------------------- |
| **Direction**     | Speedgoat observation system -> CAN -> CarMaker      |
| **Nominal cycle** | 5 ms                                                 |
| **Integrity**     | No application-level CRC or alive counter is defined |

**Purpose.** Telemetry only. This frame does **not** command the real VCU or the
inverters.

### Bit map

|   Bits | Bytes | Signal                        | Encoding / scale        | Meaning                     |
| -----: | ----: | ----------------------------- | ----------------------- | --------------------------- |
|  0..15 |  1..2 | `Inverter1TorqueSetpointNm` | Signed i16, raw / 32 Nm | Inverter 1 torque telemetry |
| 16..31 |  3..4 | `Inverter2TorqueSetpointNm` | Signed i16, raw / 32 Nm | Inverter 2 torque telemetry |
| 32..47 |  5..6 | `Inverter3TorqueSetpointNm` | Signed i16, raw / 32 Nm | Inverter 3 torque telemetry |
| 48..63 |  7..8 | `Inverter4TorqueSetpointNm` | Signed i16, raw / 32 Nm | Inverter 4 torque telemetry |

---

# 8. `0x502` - CarMakerInverterReady

|                         |                                                      |
| ----------------------- | ---------------------------------------------------- |
| **Direction**     | Speedgoat observation system -> CAN -> CarMaker      |
| **Nominal cycle** | 5 ms                                                 |
| **Integrity**     | No application-level CRC or alive counter is defined |

**Purpose.** Telemetry only. Reports inverter readiness to CarMaker.

### Bit map

|  Bits |             Bytes | Signal             | Encoding / scale | Meaning                                |
| ----: | ----------------: | ------------------ | ---------------- | -------------------------------------- |
|     0 |           1 bit 0 | `Inverter1Ready` | Boolean          | Inverter 1 ready                       |
|     1 |           1 bit 1 | `Inverter2Ready` | Boolean          | Inverter 2 ready                       |
|     2 |           1 bit 2 | `Inverter3Ready` | Boolean          | Inverter 3 ready                       |
|     3 |           1 bit 3 | `Inverter4Ready` | Boolean          | Inverter 4 ready                       |
| 4..63 | 1 bits 4..7, 2..8 | `Reserved`       | Must be zero     | Receiver rejects nonzero reserved bits |

---

# 9. `0x032` / `0x034` / `0x2B0` - Raw sensor messages

|                     |                                                                        |
| ------------------- | ---------------------------------------------------------------------- |
| **Direction** | Physical sensor or sensor emulator -> CAN -> Speedgoat and/or CarMaker |

### ID mapping

| CAN ID    | Name          |
| --------- | ------------- |
| `0x032` | `Sensor032` |
| `0x034` | `Sensor034` |
| `0x2B0` | `Sensor2B0` |

### Bit map

|    CAN ID |  Bits | Signal         | Encoding / scale   | Meaning                                 |
| --------: | ----: | -------------- | ------------------ | --------------------------------------- |
| `0x032` | 0..63 | `RawPayload` | Raw 64-bit payload | Field-level meaning is not defined here |
| `0x034` | 0..63 | `RawPayload` | Raw 64-bit payload | Field-level meaning is not defined here |
| `0x2B0` | 0..63 | `RawPayload` | Raw 64-bit payload | Field-level meaning is not defined here |

---

# 10. Real-VCU-only end-to-end example at 20% throttle

1. CarMaker calculates or requests 20.00% accelerator demand.
2. CarMaker places raw value 2000 (`0x07D0`) in `ThrottleDemand` of `0x500`:

   ```
   Byte 1 = D0
   Byte 2 = 07
   ```
3. CarMaker sets `Active` = 1, advances `AliveCounter`, zeroes reserved bits,
   calculates CRC over Bytes 1..5, and transmits the frame.
4. Speedgoat IO614 receives `0x500` and validates ID, DLC, pedal ranges,
   `Active`, counter, reserved bits, CRC, and freshness.
5. Speedgoat converts 20.00% to its analog throttle-output command and drives
   the two redundant throttle channels toward the real VCU.
6. The real VCU reads the two throttle signals and applies its own plausibility
   and safety logic. It may reject the request, reduce it, or authorize a torque
   request depending on state, brake input, faults, RTD, HV readiness, shutdown
   feedback, and inverter readiness.
7. If authorized, the real VCU transmits one control frame per inverter:

   ```
   0x186 -> Inverter 1
   0x196 -> Inverter 2
   0x1A6 -> Inverter 3
   0x1B6 -> Inverter 4
   ```
8. The inverters return their status frames. Speedgoat receives those frames and
   can send summarized telemetry to CarMaker through `0x501` and `0x502`.

> **20% throttle is a pedal demand, not a guaranteed torque value.** The real VCU
> remains the authority that decides whether the car is allowed to produce torque.

---

# 11. Evidence boundaries

The branch contains model-side definitions and decoders for the CAN paths. The
following still require **physical evidence** before claiming real-VCU operation:

- [ ] CarMaker RBS actually transmits `0x500` on the selected physical CAN port.
- [ ] Speedgoat receives valid `0x500` frames without overrun or bus-off.
- [ ] The `0x500` demand produces the intended IO183 output voltages.
- [ ] Analog voltage levels, polarity, grounds, and connector pinout are safe and
  correct at the real VCU.
- [ ] The real VCU emits the four control IDs with expected bytes.
- [ ] The real inverters acknowledge and respond to those control frames.
- [ ] The status and telemetry frames are observed on the physical bus.

---

# 12. CarMaker FS_race and CM4SL integration

The real-VCU CarMaker side is the CarMaker project under `carmaker/FS_race/`,
with CM4SL source and model integration under `carmaker/FS_race/src_cm4sl/`.

### Component roles

| File                       | Role                                                                                                                                                                              |
| -------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `CM_Main.c`              | Owns CarMaker startup, cycle-level initialization, and the ordering of CANIf/RBS input and output calls around the CarMaker simulation loop.                                      |
| `IO.c`                   | Owns the reviewed PCAN-USB path used by this bench. Sends the`0x500` pedal-demand frame and receives the `0x501`/`0x502` telemetry frames.                                  |
| `User.c`                 | Declares the received CAN values as CarMaker Data Dictionary quantities.                                                                                                          |
| `TorqueVect_HIL_CAN.mdl` | CarMaker powertrain/torque-vectoring model with the Speedgoat CAN torque-feedback subsystem. Unpacks`0x501` and `0x502` and exposes the values to the torque-vectoring model. |
| `FS_race`                | Provides the vehicle, powertrain, road, TestRun, CAN configuration, and CM4SL executable context in which TorqueVect runs.                                                        |

## CM4SL cycle order

```
  startup
     |
     +--> CANIf_Init_First / RBS_Init_First
     +--> CANIf_Init / RBS_Init
     +--> model and quantity declaration
     +--> CANIf_Init_Finalize / RBS_MapQuants / RBS_Start
     |
  each CarMaker simulation cycle
     |
     +--> CANIf_In       receive CAN input
     +--> RBS_In         process Rest Bus Simulation input
     +--> CarMaker model step, including TorqueVect
     +--> RBS_OutMap     map outgoing quantities
     +--> RBS_Out        transmit RBS output
     +--> CANIf_Out      transmit CAN output
     |
  shutdown
     |
     +--> RBS_Cleanup
     +--> CANIf_Cleanup
```

This ordering matters because CarMaker must **receive** inverter telemetry before
TorqueVect consumes the values, and must **generate** the current pedal demand
before its CAN output stage transmits `0x500`.

## CarMaker source table

| Component                  | Input/output                | CAN role                                  |
| -------------------------- | --------------------------- | ----------------------------------------- |
| `DrivMan.Gas`            | CarMaker driver/test demand | Source for`0x500` `ThrottleDemand`    |
| `DrivMan.Brake`          | CarMaker driver/test demand | Source for`0x500` `BrakeDemand`       |
| `IO.c` / `IO_Out`      | CarMaker output hook        | Encodes and sends`0x500`                |
| `IO.c` / `IO_In`       | CarMaker input hook         | Receives`0x501` and `0x502`           |
| `User.c`                 | Data Dictionary declaration | Publishes`MFE_CAN` quantities           |
| `TorqueVect_HIL_CAN.mdl` | CarMaker powertrain model   | Consumes`MFE_CAN` telemetry             |
| `FS_race` TestRun        | Scenario/timing setup       | Selects vehicle, road, and pedal maneuver |

## Direct PCAN `0x500` implementation

The current CM4SL `IO.c` source contains a direct PCAN transmit path:

- The CarMaker simulation cycle is treated as a 1-ms cycle.
- `IO_Out` sends only when `CycleNo` modulo 10 equals zero.
- Therefore `0x500` is emitted nominally every 10 ms.
- `DrivMan.Gas` is multiplied by 10000 and clamped to 0..10000.
- `DrivMan.Brake` is multiplied by 10000 and clamped to 0..10000.
- `Active` is set in bit 0 of Byte 5.
- `AliveCounter` occupies bits 1..4 of Byte 5.
- CRC is calculated into Byte 6.

> This is the source-level CarMaker-to-Speedgoat path. The separate CarMaker RBS
> configuration remains a configuration/bring-up concern and **must not be treated
> as proof of physical transmission** until the PCAN capture confirms ID, payload,
> timing, counter, and CRC.

## CarMaker `0x500` source conversion

| CarMaker quantity            | Conversion                               | `0x500` field         |
| ---------------------------- | ---------------------------------------- | ----------------------- |
| `DrivMan.Gas` = 0.0..1.0   | `round(Gas * 10000)`, clamp 0..10000   | `ThrottleDemand`      |
| `DrivMan.Brake` = 0.0..1.0 | `round(Brake * 10000)`, clamp 0..10000 | `BrakeDemand`         |
| Internal alive counter       | modulo-16 increment each frame           | `AliveCounter`        |
| Constant command enable      | bit value 1                              | `Active`              |
| Bytes 1..5                   | CRC-8/SAE-J1850                          | `Integrity` in Byte 6 |

**Example**

```
  DrivMan.Gas          = 0.20
  ThrottleDemand       = round(0.20 * 10000) = 2000
  ThrottleDemand bytes = D0 07
```

---

# 13. `IO.c` receive path for CarMaker telemetry

`IO.c` polls the PCAN receive queue and ignores frames that are not standard
8-byte data frames. It currently handles `0x501` and `0x502` as follows.

## `0x501` receive path

```
  PCAN frame 0x501
       |
       +--> Bytes 1..2 -> signed raw -> /32 -> Inverter 1 torque setpoint
       +--> Bytes 3..4 -> signed raw -> /32 -> Inverter 2 torque setpoint
       +--> Bytes 5..6 -> signed raw -> /32 -> Inverter 3 torque setpoint
       +--> Bytes 7..8 -> signed raw -> /32 -> Inverter 4 torque setpoint
       |
       +--> sum four values -> MFE_CAN.TorqueRequestTotalNm
```

The exact Data Dictionary variables are:

```
  MFE_CAN.Inverter1TorqueSetpointNm
  MFE_CAN.Inverter2TorqueSetpointNm
  MFE_CAN.Inverter3TorqueSetpointNm
  MFE_CAN.Inverter4TorqueSetpointNm
  MFE_CAN.TorqueRequestTotalNm
```

## `0x502` receive path

```
  PCAN frame 0x502
       |
       +--> Byte 1 bit 0 -> MFE_CAN.Inverter1Ready
       +--> Byte 1 bit 1 -> MFE_CAN.Inverter2Ready
       +--> Byte 1 bit 2 -> MFE_CAN.Inverter3Ready
       +--> Byte 1 bit 3 -> MFE_CAN.Inverter4Ready
       +--> Byte 1 bits 4..7 and Bytes 2..8 must be zero
       +--> OR of four ready bits -> MFE_CAN.DriveActive
```

> **Bring-up gate is deliberately permissive.**
>
> ```
> MFE_CAN.DriveActive = Inverter1Ready OR Inverter2Ready OR
>                       Inverter3Ready OR Inverter4Ready
> ```
>
> One ready inverter can make `DriveActive` true during bring-up. That is **not**
> equivalent to proving that all four inverters are ready, and it must be reviewed
> before loaded real-vehicle operation.

## CarMaker Data Dictionary table

| Dictionary quantity                   | Type          | Source                      | Consumer                 |
| ------------------------------------- | ------------- | --------------------------- | ------------------------ |
| `MFE_CAN.Inverter1TorqueSetpointNm` | double, N*m   | `0x501` bits 0..15        | TorqueVect / logging     |
| `MFE_CAN.Inverter2TorqueSetpointNm` | double, N*m   | `0x501` bits 16..31       | TorqueVect / logging     |
| `MFE_CAN.Inverter3TorqueSetpointNm` | double, N*m   | `0x501` bits 32..47       | TorqueVect / logging     |
| `MFE_CAN.Inverter4TorqueSetpointNm` | double, N*m   | `0x501` bits 48..63       | TorqueVect / logging     |
| `MFE_CAN.TorqueRequestTotalNm`      | double, N*m   | Sum of four`0x501` values | TorqueVect request input |
| `MFE_CAN.Inverter1Ready`            | unsigned char | `0x502` bit 0             | readiness/diagnostics    |
| `MFE_CAN.Inverter2Ready`            | unsigned char | `0x502` bit 1             | readiness/diagnostics    |
| `MFE_CAN.Inverter3Ready`            | unsigned char | `0x502` bit 2             | readiness/diagnostics    |
| `MFE_CAN.Inverter4Ready`            | unsigned char | `0x502` bit 3             | readiness/diagnostics    |
| `MFE_CAN.DriveActive`               | unsigned char | OR of four ready flags      | TorqueVect active gate   |

---

# 14. `TorqueVect_HIL_CAN.mdl` interface

TorqueVect is the CarMaker powertrain/torque-vectoring model. **It is not the real
VCU.** It represents the vehicle-side model that consumes the real-VCU and
inverter feedback needed to calculate the vehicle response.

The CAN feedback subsystem is conceptually:

```
  PCAN receive
       |
       +--> CAN Unpack 0x501
       |       |
       |       +--> four torque setpoints
       |
       +--> CAN Unpack 0x502
               |
               +--> four inverter-ready bits
       |
       +--> MFE_CAN.TorqueRequestTotalNm
       +--> MFE_CAN.DriveActive
       |
       v
  TorqueVect powertrain / torque-vectoring logic
       |
       v
  CarMaker vehicle response and logged quantities
```

## Interface replacement table

| Previous conceptual input         | Current CAN-backed input                |
| --------------------------------- | --------------------------------------- |
| `TorqueVect.XcpTorqueRequestNm` | `MFE_CAN.TorqueRequestTotalNm`        |
| `TorqueVect.XcpTorqueActive`    | `MFE_CAN.DriveActive`                 |
| XCP per-inverter observation      | `0x501` per-inverter torque setpoints |
| XCP active observation            | `0x502` per-inverter ready flags      |

The source notes that the CAN-backed aggregate replaces the superseded XCP
request/active pair. The sum is formed in `IO.c`, while the ready flags are
retained individually and also combined into `DriveActive`.

## TorqueVect authority boundary

TorqueVect receives feedback and uses it in the CarMaker vehicle/powertrain
model. **TorqueVect does not replace the real-VCU safety logic.** The real VCU
remains responsible for deciding whether the inverter control frames should
enable torque and what torque limits to request.

| Layer            | Owns                                                                |
| ---------------- | ------------------------------------------------------------------- |
| CarMaker DrivMan | Test-driver pedal demand                                            |
| Speedgoat        | CAN transport, pedal emulation, capture, telemetry                  |
| Real VCU         | Pedal plausibility, state machine, safety gates, torque command     |
| Ephorus inverter | Motor/inverter control and status                                   |
| TorqueVect       | CarMaker powertrain/vehicle response to measured/commanded feedback |

---

# 15. CAN state machines

## A. CarMaker pedal-command state machine

```
  +---------+
  | DISABLED|
  +----+----+
       | Active=1, frame constructed
       v
  +---------+       ID/DLC/range/CRC/counter failure
  | CANDIDATE|----------------------------------+
  +----+----+                                  |
       | valid and counter accepted           v
       v                                  +----------+
  +---------+   frame age >= 100 ms        | REJECTED |
  | CAN OWN |------------------------------+----------+
  +----+----+
       | next valid frame
       | updates demand and counter
       |
       +--------------------------+
                                  |
                                  v
                             +---------+
                             | CAN OWN |
                             +---------+
```

From `CAN OWN`, any of these conditions withdraws ownership:

- `Active` becomes 0.
- CRC fails.
- Reserved bit is nonzero.
- Counter repeats.
- Pedal value is out of range.
- No valid frame is received for 100 ms.

> The throttle and brake ownership decision is **atomic**. The real VCU must not
> receive a new throttle source while retaining an old CAN brake source.

## B. Real VCU drive state machine

The CAN frames do **not** independently create a drive state. The real VCU state
machine uses pedal inputs, digital controls, HV/precharge feedback, shutdown
feedback, inverter status, and safety plausibility.

The intended high-level sequence is:

```
  +-------+
  | LV_ON |
  +---+---+
      | precharge request
      v
  +------------+
  | PRECHARGING|
  +------+-----+
         | precharge complete / DC-link healthy
         v
  +--------+
  | ENABLE |
  +----+---+
       | main/RTD command and brake condition
       v
  +---------+
  | BUZZING |
  +----+----+
       | buzzer/RTD delay complete
       v
  +-----+
  | RTD |
  +--+--+
     | valid pedals, no fault, inverter authorization
     v
  +----------------+
  | TORQUE REQUEST |
  +----------------+
```

Fault from an active HV/drive state:

```
  ENABLE / BUZZING / RTD -- DC-link or shutdown fault --> ERROR_SHUTDOWN
```

> Torque authority is gated by the real VCU. A valid `0x500` frame only supplies
> the requested pedal input. It does **not** bypass the RTD, brake, APPS,
> shutdown, precharge, or inverter-ready gates.

## C. Real VCU to inverter CAN state machine

```
  +----------------+
  | VCU NOT READY  |
  +--------+-------+
           | state and safety gates permit
           v
  +----------------+
  | SEND SAFE CMD  |
  | enable=0       |
  | torque=0       |
  +--------+-------+
           | inverter/VCU conditions valid
           v
  +----------------+
  | SEND DRIVE CMD |
  | enable=1       |
  | torque limits  |
  +--------+-------+
           | inverter fault, stale input, shutdown,
           | APPS/brake fault, or state exit
           v
  +----------------+
  | RETURN TO SAFE |
  | enable=0       |
  | torque=0       |
  +----------------+
```

The same four control IDs are emitted per inverter. The ID identifies the
inverter; the payload carries that inverter enable, mode, speed, and torque
limits.

## D. Inverter status/telemetry state machine

```
  +------------------+
  | NO VALID STATUS  |
  +---------+--------+
            | valid 3X3/3X5/0x400 received
            v
  +------------------+
  | STATUS RETAINED  |
  +---------+--------+
            | status-cycle processing
            v
  +------------------+
  | PACK 0x501/0x502 |
  +---------+--------+
            | CarMaker PCAN transmit
            v
  +------------------+
  | CARMAKER/TORQUE  |
  | VECT FEEDBACK    |
  +------------------+
```

> `0x501` and `0x502` are companion telemetry frames, but they are separate CAN
> frames and are **not application-level atomic**. CarMaker should not assume that
> receiving only one of them proves a complete same-cycle status sample.

## E. TorqueVect torque-source switch

`TorqueVect.mdl`'s `u Source Switch` block (`Criteria: u2 ~= 0`) is the one
branch point in the vectoring model. It is **combinational, not a latching
state machine**: it re-evaluates `MFE_CAN.DriveActive` every simulation step
and holds no memory of the previous cycle.

```
  MFE_CAN.DriveActive != 0          MFE_CAN.DriveActive == 0
  +-------------------------+   +-------------------------+
  | CAN-SOURCED             |   | DRIVER-MODEL FALLBACK   |
  | in1 = Gain(             |   | in3 = VhclCtrl.Gas      |
  |  MFE_CAN.TorqueRequest  |   | (CarMaker test pedal,   |
  |  TotalNm)               |   |  not CAN telemetry)     |
  +-------------------------+   +-------------------------+
```

> Both branches feed the same `u Source Switch out1` into `Full Control Loop in:3`. The instant an inverter drops out of the `0x502` OR (or the CAN link
> goes stale and `IO_In` stops updating the dictionary), the very next cycle
> falls back to the driver-model pedal — not to whatever torque it was last
> reading.

**Naming note.** The two `Read CM Dict` blocks feeding this switch are still
named `Read XcpTorqueActive` and `Read XcpTorqueRequestNm` in the `.mdl` file.
Only their `xname` was repointed, from `TorqueVect.XcpTorqueActive` /
`TorqueVect.XcpTorqueRequestNm` to `MFE_CAN.DriveActive` /
`MFE_CAN.TorqueRequestTotalNm` — the block names (and the downstream
`XcpTorque to u` gain) were deliberately left alone to avoid disturbing the
`ReferenceBlockSourceInfo` path cache elsewhere in the file. The diagram above
uses the real, current source of each value, not the leftover block labels.

---

# 16. End-to-end 20% real-VCU example

1. `FS_race` DrivMan sets `DrivMan.Gas` = 0.20.
2. CM4SL `IO.c` / `IO_Out` converts it to 2000 counts.
3. `IO.c` creates `0x500` with Bytes 1..2 = `D0 07`.
4. `IO.c` sets `Active`, advances `AliveCounter`, computes CRC, and sends `0x500`
   through the configured CarMaker PCAN interface.
5. Speedgoat IO614 receives and validates `0x500`.
6. Speedgoat converts the accepted percentage into calibrated AO01/AO02 throttle
   voltages.
7. The real VCU reads the redundant throttle channels.
8. The real VCU applies APPS plausibility, brake interlock, HV state, RTD,
   shutdown, and inverter readiness gates.
9. If torque is authorized, the real VCU sends `0x186`, `0x196`, `0x1A6`, and
   `0x1B6` with the per-inverter control values.
10. The inverters return `0x383`..`0x3B5` and `0x400` status frames.
11. Speedgoat packages the selected torque/ready values into `0x501` and `0x502`.
12. CarMaker `IO.c` receives those frames and updates `MFE_CAN` quantities.
13. `TorqueVect_HIL_CAN.mdl` consumes `MFE_CAN.TorqueRequestTotalNm` and
    `MFE_CAN.DriveActive` to model the vehicle/powertrain response.

> At no point does TorqueVect directly command the real-VCU pedal input in this
> CAN architecture. At no point does a valid 20% pedal frame guarantee that the
> real VCU will authorize nonzero inverter torque.

---

# 17. Source-level references in this checkout

| Path                                                   | Contents                                                                         |
| ------------------------------------------------------ | -------------------------------------------------------------------------------- |
| `carmaker/FS_race/src_cm4sl/CM_Main.c`               | CM4SL/CANIf/RBS startup and per-cycle call ordering.                             |
| `carmaker/FS_race/src_cm4sl/IO.c`                    | Direct PCAN receive of`0x501`/`0x502` and direct PCAN transmit of `0x500`. |
| `carmaker/FS_race/src_cm4sl/User.c`                  | `MFE_CAN` Data Dictionary quantity declarations.                               |
| `carmaker/FS_race/src_cm4sl/TorqueVect_HIL_CAN.mdl`  | TorqueVect CAN feedback subsystem and CarMaker model integration.                |
| `carmaker/FS_race/Data/TestRun/HIL/CAN_Bringup`      | CarMaker CAN bring-up maneuver and its current proof/status notes.               |
| `carmaker/config/MFE26_Inverter_CarMaker.dbc`        | CarMaker-side CAN identifiers and field definitions.                             |
| `inverter_hil/+inverterhil/protocol.m`               | Speedgoat-side identifier groups and timing/scale constants.                     |
| `inverter_hil/+inverterhil/decodePedalDemandFrame.m` | Speedgoat-side`0x500` field validation and CRC decoding.                       |
| `inverter_hil/docs/can_pedal_demand_frame_spec.md`   | Detailed`0x500` wire contract and current proposed/not-built caveats.          |
