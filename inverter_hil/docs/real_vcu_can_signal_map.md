# MFE26 Real-VCU HIL CAN Signal Map

This is the source-level interface contract implemented on branch `CAN`. It
does not prove that a real VCU, physical inverter, harness, or analog connection
is present or safe.

## 1. Bench topology and authority

The Speedgoat model emulates four Ephorus inverters. A real VCU is the device
under test.

```text
CarMaker PC                         Speedgoat                         real VCU
-------------                      ---------                         --------
DrivMan.Gas/Brake --0x500--------> pedal validation --AO01..AO04--> pedal inputs
                                      ^                                  |
                                      +--0x186/196/1A6/1B6---------------+
                                      |
                                      +--0x383..0x400-------------------->
                                      |
CarMaker model <----0x501/0x502-------+
```

The status IDs use the Ephorus wire format, but this HIL transmits them from
Speedgoat to the real VCU. Do not connect physical inverters that transmit the
same IDs without first defining bus ownership.

| Component | Responsibility |
|---|---|
| CarMaker DrivMan | Test-driver throttle and brake demand |
| Speedgoat | Pedal validation/emulation, inverter and sensor emulation, CAN capture, CarMaker telemetry |
| Real VCU | Pedal plausibility, safety and drive-state gates, inverter commands |
| TorqueVect | CarMaker vehicle response to torque/readiness telemetry |

TorqueVect is not a VCU and does not bypass real-VCU safety logic.

## 2. CAN conventions

Unless stated otherwise, every frame is a standard 11-bit CAN data frame with
DLC 8. Byte 1 is the first data byte. Fields use Intel/little-endian DBC
convention (`@1`).

## 3. ID and direction summary

| CAN ID(s) | Frame | Implemented direction | Nominal cycle |
|---|---|---|---|
| `0x500` | `CarMakerPedalDemand` | CarMaker -> Speedgoat | 10 ms |
| `0x186`, `0x196`, `0x1A6`, `0x1B6` | Inverter control | Real VCU -> Speedgoat | VCU-defined |
| `0x383`, `0x393`, `0x3A3`, `0x3B3` | Status A | Speedgoat -> real VCU | 5 ms |
| `0x385`, `0x395`, `0x3A5`, `0x3B5` | Status B | Speedgoat -> real VCU | 5 ms |
| `0x400` | System/DC-link status | Speedgoat -> real VCU | 5 ms |
| `0x501` | Torque telemetry | Speedgoat -> CarMaker | 5 ms |
| `0x502` | Ready telemetry | Speedgoat -> CarMaker | 5 ms |
| `0x032`, `0x034`, `0x2B0` | Sensor payloads | Sensor/emulator -> real VCU | Sensor-defined |

Speedgoat transmits each status burst in this order:

```text
0x383, 0x385, 0x393, 0x395, 0x3A3, 0x3A5, 0x3B3, 0x3B5, 0x400
```

## 4. `0x500` CarMakerPedalDemand

| Bits | Signal | Encoding | Constraint |
|---:|---|---|---|
| 0..15 | `ThrottleDemand` | unsigned u16, raw x 0.01% | raw 0..10000 |
| 16..31 | `BrakeDemand` | unsigned u16, raw x 0.01% | raw 0..10000 |
| 32 | `Active` | Boolean | 1 requests CAN ownership |
| 33..36 | `AliveCounter` | unsigned 4-bit | modulo 16 |
| 37..39 | `Reserved0` | unsigned 3-bit | zero |
| 40..47 | `Integrity` | unsigned 8-bit | CRC below |
| 48..63 | `Reserved1` | unsigned 16-bit | zero |

CRC-8/SAE-J1850 covers Bytes 1..5: polynomial `0x1D`, initial value
`0xFF`, no reflection, final XOR `0xFF`. CAN ID, DLC, Byte 6, and Bytes
7..8 are not covered. Five zero bytes produce `0x10`.

### Implemented sender

`IO_Out` rounds `DrivMan.Gas * 10000` and `DrivMan.Brake * 10000`,
clamps each to 0..10000, sets `Active`, inserts and advances the modulo-16
counter, calculates the CRC, and calls `PCANIO_Send` when
`CycleNo % 10 == 0`.

This is direct PCAN. CarMaker RBS does not bind the PCAN-USB adapter on this
bench.

### Implemented receiver and ownership

Transport decoding rejects an extended or remote frame, wrong ID, DLC other
than 8, malformed payload, out-of-range pedal, nonzero reserved field, or CRC
failure.

Ownership is separate from transport acceptance:

1. The first valid frame is retained but does not establish counter advancement.
2. A later valid frame grants `counterAdvanced` only when its counter is
   exactly the previous counter plus one modulo 16. Repeated and skipped
   counters do not grant ownership.
3. Every structurally valid frame replaces the tuple and refreshes its
   timestamp, including `Active=0` and non-sequential counters.
4. A rejected frame is ignored and does not invalidate the previously retained
   tuple.
5. The tuple is fresh while `ageMs <= 100`; it is stale at 101 ms.
6. `ownsPedals = fresh && counterAdvanced && active`.

Throttle and brake ownership is atomic. When CAN does not own them, both source
switches use their configured GUI-command fallback before voltage calibration.

For `DrivMan.Gas = 0.20`, raw throttle is 2000 (`0x07D0`), so Bytes 1..2
are `D0 07`. This is a pedal demand, not a torque command.

## 5. Speedgoat analog interface

| IO183 output | Signal | Real-VCU destination |
|---|---|---|
| Module 1 AO01 | Throttle channel 1 | J2 pin 21 |
| Module 1 AO02 | Throttle channel 2 | J2 pin 19 |
| Module 1 AO03 | Brake channel 1 | J2 pin 23 |
| Module 1 AO04 | Brake channel 2 | J2 pin 17 |

`Pedal Voltage Calibration` converts percentages to calibrated voltages.
Connector revision, grounding, loading, polarity, and conditioning remain
physical verification items; see `PINOUTS.md`.

## 6. Real-VCU inverter control

| CAN ID | Emulated channel |
|---|---|
| `0x186` | 1 |
| `0x196` | 2 |
| `0x1A6` | 3 |
| `0x1B6` | 4 |

| Bits | Signal | Encoding |
|---:|---|---|
| 0 | `EnableInverter` | Boolean |
| 1 | `ResetError` | Boolean |
| 2 | `ASCallowed` | Boolean |
| 3 | `CurrentControl` | Boolean |
| 4..15 | Reserved/observed | no defined command; decoder exposes raw value |
| 16..31 | `SpeedSetpoint` | signed i16, RPM |
| 32..47 | `TorqueLimitPositive` | signed i16, raw / 256 Nm |
| 48..63 | `TorqueLimitNegative` | signed i16, raw / 256 Nm |

There is no application CRC or alive counter. Speedgoat retains and ages each
channel independently. The real VCU's drive-state implementation is outside
this repository.

## 7. Inverter Status A

IDs `0x383`, `0x393`, `0x3A3`, and `0x3B3` map to channels 1..4.

| Bits | Signal | Encoding |
|---:|---|---|
| 0..1 | `InverterState` | unsigned 2-bit |
| 2 | `InverterReady` | Boolean |
| 3 | `Derating` | Boolean |
| 4..15 | `MaxAllowedCurrent` | unsigned 12-bit, raw / 32 A |
| 16..27 | `TorqueActual` | signed 12-bit, raw / 32 Nm |
| 28..39 | `TorqueSetpoint` | signed 12-bit, raw / 32 Nm |
| 40..51 | `MotorTemperature` | signed 12-bit, raw / 8 degC |
| 52..63 | `SwitchTemperature` | signed 12-bit, raw / 16 degC |

## 8. Inverter Status B

IDs `0x385`, `0x395`, `0x3A5`, and `0x3B5` map to channels 1..4.

| Bits | Signal | Encoding |
|---:|---|---|
| 0..11 | `IdSetpoint` | signed 12-bit, raw / 16 Arms |
| 12..23 | `IdActual` | signed 12-bit, raw / 16 Arms |
| 24..35 | `IqSetpoint` | signed 12-bit, raw / 16 Arms |
| 36..47 | `IqActual` | signed 12-bit, raw / 16 Arms |
| 48..63 | `SpeedActual` | signed i16, RPM |

## 9. `0x400` system/DC-link status

| Bits | Signal | Encoding |
|---:|---|---|
| 0..15 | `DCLinkVoltage12Actual` | unsigned u16, raw / 64 V |
| 16..31 | `DCLinkVoltage34Actual` | unsigned u16, raw / 64 V |
| 32..47 | `SwitchingFrequency` | unsigned u16, raw / 512 kHz |
| 48 | `DCLink12AboveMinimum` | Boolean |
| 49 | `DCLink34AboveMinimum` | Boolean |
| 50 | `ControlEnable` | Boolean |
| 51 | `ControlDisable` | Boolean |
| 52..63 | Reserved | packed as zero |

## 10. CarMaker telemetry

Speedgoat derives both frames from the same four Status A payloads used for the
current status step and transmits them every 5 ms on IO614 channel 1.

### `0x501` torque setpoints

| Bits | Signal | Encoding |
|---:|---|---|
| 0..15 | `Inverter1TorqueSetpointNm` | signed i16, raw / 32 Nm |
| 16..31 | `Inverter2TorqueSetpointNm` | signed i16, raw / 32 Nm |
| 32..47 | `Inverter3TorqueSetpointNm` | signed i16, raw / 32 Nm |
| 48..63 | `Inverter4TorqueSetpointNm` | signed i16, raw / 32 Nm |

### `0x502` ready flags

| Bits | Signal | Encoding/constraint |
|---:|---|---|
| 0 | `Inverter1Ready` | Boolean |
| 1 | `Inverter2Ready` | Boolean |
| 2 | `Inverter3Ready` | Boolean |
| 3 | `Inverter4Ready` | Boolean |
| 4..63 | Reserved | zero; CarMaker rejects otherwise |

Neither frame has an application CRC, alive counter, timestamp, or sequence.
They are separate CAN frames and are not application-level atomic.

CarMaker retains each ID independently. It does not track whether both IDs have
arrived and has no `0x501`/`0x502` freshness timeout. Loss of telemetry
therefore leaves the last torque and ready values retained until valid
replacements arrive or the application is reinitialized.

`MFE_CAN.DriveActive` is deliberately permissive during bring-up:

```text
Inverter1Ready OR Inverter2Ready OR Inverter3Ready OR Inverter4Ready
```

One ready channel is enough to select the CAN torque branch. Review this gate
together with a telemetry timeout before loaded operation.

## 11. Sensor IDs

The aggregate CarMaker DBC reserves `0x032`, `0x034`, and `0x2B0` as
eight-byte raw payloads. Field definitions belong to the dedicated IMU and
steering-sensor protocol code. Do not infer fields from the raw DBC entries.

## 12. CarMaker CM4SL integration

The project is `carmaker/FS_race`; its model is
`carmaker/FS_race/src_cm4sl/TorqueVect.mdl`.

There is no `TorqueVect_HIL_CAN.mdl` in this branch. The CAN-backed changes
are modifications inside `TorqueVect.mdl`, so build, launch, and review
instructions must continue to use that filename.

The `CM_Main.c` cycle order is:

```text
CANIf_In
IO_In          direct PCAN receive of 0x501/0x502
RBS_In
CarMaker/User/model calculation
RBS_OutMap
RBS_Out
IO_Out         direct PCAN transmit of 0x500
CANIf_Out
```

`IO.c` decodes `0x501` into four torque quantities and their sum. It
decodes `0x502` into four ready flags and the OR-based `DriveActive`.
`User.c` publishes:

```text
MFE_CAN.Inverter1TorqueSetpointNm
MFE_CAN.Inverter2TorqueSetpointNm
MFE_CAN.Inverter3TorqueSetpointNm
MFE_CAN.Inverter4TorqueSetpointNm
MFE_CAN.TorqueRequestTotalNm
MFE_CAN.Inverter1Ready
MFE_CAN.Inverter2Ready
MFE_CAN.Inverter3Ready
MFE_CAN.Inverter4Ready
MFE_CAN.DriveActive
```

## 13. TorqueVect source selection

TorqueVect does not contain CAN Unpack blocks for `0x501`/`0x502`.
`IO.c` performs PCAN decoding and publishes Data Dictionary values.

| Existing block label | Current Data Dictionary quantity |
|---|---|
| `Read XcpTorqueRequestNm` | `MFE_CAN.TorqueRequestTotalNm` |
| `Read XcpTorqueActive` | `MFE_CAN.DriveActive` |

The combinational `u Source Switch` uses `u2 ~= 0`:

| Condition | Source |
|---|---|
| `MFE_CAN.DriveActive != 0` | gain-scaled `MFE_CAN.TorqueRequestTotalNm` |
| `MFE_CAN.DriveActive == 0` | `VhclCtrl.Gas` driver-model fallback |

The exact wiring in `TorqueVect.mdl` is:

```text
MFE_CAN.TorqueRequestTotalNm -> Gain 1/(4*T_i_max) -> switch input 1
MFE_CAN.DriveActive --------------------------------> switch input 2
VhclCtrl Gas ---------------------------------------> switch input 3
switch output --------------------------------------> Full Control Loop input 3
```

Because CarMaker does not age `0x502`, a silent link does not itself change
`DriveActive` and does not force fallback.

## 14. Twenty-percent walkthrough

1. `CAN_Bringup` sets `DrivMan.Gas` to 0.20.
2. `IO_Out` encodes raw 2000 as `D0 07`, adds `Active`, counter, and
   CRC, then transmits `0x500` through PCAN.
3. Speedgoat validates and retains it. Ownership begins only after a subsequent
   frame advances the counter exactly by one.
4. While ownership is true, calibration drives AO01/AO02 for throttle and
   AO03/AO04 for brake.
5. A connected real VCU applies its external safety logic and may send the four
   inverter control IDs.
6. Speedgoat decodes those controls and sends the nine status frames.
7. Speedgoat emits `0x501`/`0x502`; CarMaker updates the `MFE_CAN`
   quantities consumed by TorqueVect.

A valid 20% demand does not prove or guarantee nonzero torque.

## 15. Evidence boundary

Repository tests prove source behavior, field packing, and model structure. The
branch history also records:

- commit `39dac6e`: Speedgoat `0x501`/`0x502` captured at approximately
  5 ms with idle zero payloads; and
- commit `61a9dd6`: direct CarMaker-PCAN `0x500` reached Speedgoat with
  ownership in 80/80 samples during a live 14.49% to 20% ramp.

Those observations do not prove:

- real-VCU connection, firmware version, state sequence, or safety behavior;
- AO voltage at the real-VCU connector under load;
- approved grounding, polarity, conditioning, or harness continuity;
- real-VCU transmission of all four control IDs;
- physical inverter reception or response;
- loaded torque production; or
- resolution of the recorded IO614 bus-load/overrun/bus-warning anomaly.

Commit `61a9dd6` explicitly records that the real VCU was absent during the
`0x500` proof. Do not describe the complete real-VCU loop as physically
proven from that capture.

## 16. Source references

| Path | Role |
|---|---|
| `carmaker/FS_race/src_cm4sl/CM_Main.c` | cycle ordering |
| `carmaker/FS_race/src_cm4sl/IO.c` | direct PCAN transmit/receive |
| `carmaker/FS_race/src_cm4sl/User.c` | `MFE_CAN` declarations |
| `carmaker/FS_race/src_cm4sl/TorqueVect.mdl` | source switch and vehicle model |
| `carmaker/FS_race/Data/TestRun/HIL/CAN_Bringup` | 20% TestRun |
| `carmaker/config/MFE26_Inverter_CarMaker.dbc` | CarMaker-facing DBC |
| `inverter_hil/+inverterhil/protocol.m` | IDs, timing, torque scale |
| `inverter_hil/+inverterhil/decodePedalDemandFrame.m` | `0x500` decoder |
| `inverter_hil/+inverterhil/receivePedalDemandFrame.m` | counter/retention |
| `inverter_hil/+inverterhil/pedalDemandSnapshot.m` | freshness/ownership |
| `inverter_hil/+inverterhil/packStatus3X3.m` | Status A layout |
| `inverter_hil/+inverterhil/packStatus3X5.m` | Status B layout |
| `inverter_hil/+inverterhil/packSystemStatus.m` | `0x400` layout |
| `inverter_hil/+inverterhil/packCarMakerTelemetry.m` | telemetry layout |
| `inverter_hil/build_inverter_hil_model.m` | model/hardware construction |
| `PINOUTS.md` | analog mapping and physical gates |
