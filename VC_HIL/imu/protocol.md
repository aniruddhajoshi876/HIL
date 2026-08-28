# MTi-680G HIL protocol

The independent contract in `imuProtocol.m` is based on Xsens **MT CAN
Protocol Documentation**, document MT1604P, **Revision A, 16 Sept 2019**
(`references/sensors/datasheets/MTCANProtocolDocumentation.pdf`). No
`2020.A` revision of this document exists; that earlier citation was wrong.

Full verified contract, assumption register and findings:
`references/sensors/mti680_can_contract.md` and
`references/sensors/imu_contract_delta.md`. Independently derived golden
vectors: `references/sensors/golden_vectors/mti680/`.

## Vector messages

Three signed `int16` fields at byte offsets 0, 2, 4.

| Message | CAN ID | DLC | Scale | Documented range | Decoded by MFE26-VC |
|---|---:|---:|---:|---:|---|
| Acceleration | `0x034` | 6 | `2^-8 m/s^2` | +/-100 m/s^2 | yes |
| Rate of turn | `0x032` | 6 | `2^-9 rad/s` | +/-35 rad/s | yes |
| Euler angles | `0x022` | 6 | `2^-7 deg` | roll +/-180, pitch +/-90, yaw +/-180 | **no** |
| Velocity XYZ | `0x076` | 6 | `2^-6 m/s` | +/-500 m/s | yes |

The **documented range is narrower than the `int16` encoding limit**, and
the MFE26-VC firmware discards the entire frame if any axis exceeds it. The
encoders therefore reject out-of-range values (`mti680:DocRange`,
`mti680:PayloadRange`) instead of saturating silently at `int16`, which
would emit frames the VCU throws away and make an out-of-range stimulus look
like a dead sensor.

The range guard is **per axis**: `imuProtocol.m` carries `rangeMax` as a
scalar for the symmetric messages and as a `1x3` vector for Euler angles,
which are the only message with different bounds per axis (MT1604P section
6.3.2: roll `+/-180`, pitch `+/-90`, yaw `+/-180`). `packMti680Frame` rejects
a pitch outside `+/-90` even though roll/yaw at the same magnitude pass.

`0x022` Euler is kept in the contract and covered by tests because the
encoding is correct per the document, but the VCU has no handler for it and
every such frame merely increments its unknown-ID counter. Its default
output rate is therefore **0 Hz** and the model does not transmit it.

## Scalar messages

| Message | CAN ID | DLC | Format |
|---|---:|---:|---|
| Group counter | `0x006` | 2 | `uint16` |
| Sample time | `0x005` | 4 | `uint32` |
| Status word | `0x011` | 4 | `uint32` |
| Error code | `0x001` | 1 | `uint8` |

These are unsigned, unlike every vector message. `packMti680Frame` rejects
them rather than vector-packing them; `packMti680ScalarFrame` big-endian-packs
the single `uintN` value into its DLC. `stepImuSimulation` emits all four on
every inertial group: `groupCounter` increments once per group (wraps at
`2^16`), `sampleTime` is a free-running microsecond `uint32`, `statusWord`
carries the nominal healthy value `imuProtocol.nominalStatusWord`
(`0x00000003` = Selftest passed + Filter Valid, per MT Low Level doc Table 27)
and `errorCode` is `imuProtocol.nominalErrorCode` (`0x00`, no error) until a
fault is injected.

## Output rates and scheduling

`imuProtocol.defaultOutputRateHz` is the single source of truth for
per-message rates (acceleration / rateOfTurn / velocityXyz at 100 Hz,
eulerAngles at 0 Hz = not transmitted). `imuScheduler` derives its base group
tick from that table (`1 / fastest non-zero rate` = `0.01 s` = 100 Hz) rather
than a hardcoded value, and returns a per-message `due` flag for each so a
message can run at its own rate; `0 Hz` yields a permanently-false flag. An
explicit third argument still overrides the base tick for tests and callers
that want a different group rate.

## Mounting orientation

The physical MTi-680G is mounted **rotated 180 deg about the vehicle vertical
(Z / yaw) axis** (sensor `+X` points vehicle-rearward, sensor `+Y` points
vehicle-rightward, sensor `+Z` stays vehicle up; vehicle frame is X forward,
Y left, Z up). `mountingTransform.m` is the single place this is applied when
shared vehicle state becomes sensor-frame CAN payloads, driven by the
`imuProtocol.mounting` constant:

* acceleration, rate of turn and velocity XYZ: `X` and `Y` negate, `Z` keeps
  sign (`axisSign = [-1 -1 1]`);
* Euler angles: roll and pitch negate (the angles about the axes
  perpendicular to Z), yaw offsets by `180 deg` and wraps to `(-180, 180]`.

Set `axisSign = [1 1 1]`, `eulerRollSign = 1`, `eulerPitchSign = 1`,
`eulerYawOffsetDeg = 0` in `imuProtocol.mounting` if the mounting is ever
corrected to align with the vehicle frame.

MT1604P specifies **no per-message data-invalid sentinel** for the MTi.
Health is signalled out of band by the status word and error code. The Bosch
LWS sentinel convention (`0x7FFF` / `0xFF`) must not be carried onto this bus.

## Open assumptions

- **A1 — byte order matches the VCU, not verified against a real sensor.**
  MT1604P never states the byte order of CAN output payloads. Big-endian is
  inherited from the MT Low Level Communication Protocol Documentation
  section 5.1.1. Confirmed 2026-08-27 that the MFE26-VC `controls`-branch
  decoder reads big-endian: `MTi680G_driver.cpp` decodes each field as
  `((uint16_t)data[0] << 8) | data[1]` with the comment "DBC @0 (Motorola)
  => big-endian". Both sides now provably agree, but a passing HIL test
  still proves nothing about what the *physical* sensor emits.
  `imuProtocol.byteOrderVerified` stays `false`; golden vector
  `edge_little_endian_confusion_probe` exists to settle it against hardware.
- **A3 — VelocityXYZ ID.** MT1604P Table 4 lists `0x75` while section 6.8.3
  lists `0x076`. `0x076` is adopted because that is what the firmware
  decodes — confirmed 2026-08-27: `MTi680G_driver.hpp:14`
  `MTI680G_ID_VELOCITY_RAW 0x076u`. Still unresolved against a real sensor
  (the datasheet contradicts itself).
- **Output rates are a simulator choice.** MT1604P gives a per-message
  frequency field and no default; mirror whatever the real MTi-680G is
  programmed to.
- **Sensor configuration.** The MTi's factory default is 250 kbit/s with CAN
  output disabled. It must be reconfigured to baud code 10 (`0x0A`) before
  it will talk to this VCU at 500 kbit/s.
- **Yaw-rate axis — RESOLVED.** The physical MTi mounting is now known: the
  sensor is rotated 180 deg about the vehicle Z (yaw) axis (see *Mounting
  orientation* above). `stepVehicleState.m` publishes the shared observation
  vector in the **vehicle frame** with yaw rate on **index 6 (vehicle Z)**;
  roll-rate and pitch-rate are index 4/5 (vehicle X/Y) and are a genuine zero
  in this single-track model. The sensor<-vehicle transform is then applied at
  the CAN boundary — by `mountingTransform.m` on the host path and by
  `imuProtocol.mounting.axisSign` in the deployed model's
  `synchronizedSensorPayloads` — so yaw rate keeps its sign on the sensor Z
  axis while X/Y negate. The remaining open item is whether the 180 deg mount
  is the *intended* installation or an integration error to be corrected in
  hardware — `imuProtocol.mounting` is a one-line change if so.
- **Which gyro axis the VCU reads as vehicle yaw — RESOLVED against firmware
  (2026-08-27).** MFE26-VC `controls` branch: `gyroCANRx` decodes the third
  field (byte offset 4) into `imu_data.Gyrz`, commented "yaw rate", and
  `vcComms.cpp` does `controls_inputs->yaw_rate = MTiDriver.imu_data.Gyrz`
  unconditionally. So the VCU reads yaw rate from the Z field, exactly where
  this simulator now emits it. `ax`, `ay`, `yaw_rate` and **velocity** all feed
  the controls model: `vcComms.cpp` `update_ctrls_inputs()` forces
  `use_imu_vel_x = use_imu_vel_y = 1.0` every cycle, overriding the `0` default
  set once in `controls_init()` (and the tuning-guidance default in
  `CONTROLS.md`). A wrong sign or scale on the velocity path (`0x076`, fed from
  CarMaker `0x505`) would therefore corrupt vehicle control, not just a
  readout.
- **The 180 deg mount is confirmed by the firmware too.** `vcComms.cpp`
  `update_ctrls_inputs()` carries the comment "IMU is placed 180 deg
  flipped" and negates `ax`, `ay`, `v_x`, `v_y` while passing `Gyrz`
  through — the exact mirror of `imuProtocol.mounting.axisSign`. The
  HIL transform and the firmware compensation compose to identity, so the
  round trip is correct. Open item is unchanged: whether the flip is the
  intended install or an error to fix in hardware.
- **No DBC exists in MFE26-VC** for these messages, so there is no third
  artifact to cross-check against — but the driver constants
  (`MTi680G_driver.hpp`) now serve that role and agree with `imuProtocol.m`
  on every ID, scale, and range.

The MFE26-VC CAN acceptance filter — `CANDriver::initialize` sets a
`FDCAN_FILTER_RANGE` with `ConfigGlobalFilter(REJECT, REJECT, ...)`, and
`main.c` calls `BoardManager_create(0, 1024)` — admits standard IDs
**`0x000`-`0x400` inclusive**. Every MTi frame this simulator sends
(`0x032` / `0x034` / `0x076` and the four scalars `0x006` / `0x005` /
`0x011` / `0x001`) and the LWS standard frame `0x2B0` are inside that range
and reach the VCU. The LWS configuration frame `0x7C0` (1984) is outside it
and is dropped in hardware. Any earlier note here about a `0x383`-`0x400`
-only filter is stale.

The simulator must not import or call the VCU MTi decoder. Its golden
vectors are the test oracle for both simulator encoding and VCU decoding.
