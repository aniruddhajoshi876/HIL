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

- **A1 — byte order is assumed, not verified.** MT1604P never states the
  byte order of CAN output payloads. Big-endian is inherited from the MT Low
  Level Communication Protocol Documentation section 5.1.1 and is
  *independently assumed by the MFE26-VC decoder as well*. Because both
  sides assume the same thing, a passing HIL test proves nothing about what
  the real sensor emits. `imuProtocol.byteOrderVerified` is `false`. Golden
  vector `edge_little_endian_confusion_probe` exists to settle it against
  hardware.
- **A3 — VelocityXYZ ID.** MT1604P Table 4 lists `0x75` while section 6.8.3
  lists `0x076`. `0x076` is adopted because that is what the firmware
  decodes. Unresolved against a real sensor.
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
- **Which gyro axis the VCU reads as vehicle yaw is still not documented.**
  `references/sensors/imu_contract_delta.md` assumption A9 explicitly places
  vehicle-frame axis conventions out of scope for the wire contract, and the
  MFE26-VC `gyroCANRx` decoder is not quoted anywhere in `references/` as
  treating gyrY or gyrZ as yaw. This simulator now emits yaw rate on the
  sensor Z axis (gyrZ) on the physical basis that yaw is rotation about
  vehicle vertical; confirm against the VCU control model before trusting a
  closed-loop yaw result.
- **No DBC exists in MFE26-VC** for these messages, so there is no third
  artifact to cross-check against.

There is one further gate outside this repository: the MFE26-VC CAN
acceptance filter is currently configured to admit only `0x383`-`0x400`,
which rejects every MTi and LWS identifier before software sees it. Until
that is widened, none of these frames reach the VCU regardless of whether
this contract is right. That is firmware work, not HIL work.

The simulator must not import or call the VCU MTi decoder. Its golden
vectors are the test oracle for both simulator encoding and VCU decoding.
