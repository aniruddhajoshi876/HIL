# Bosch LWS HIL protocol

The independent contract in `lwsProtocol.m` is derived from the Bosch
Motorsport **Steering Wheel Angle Sensor LWS**, order number
`F02U.V02.894-01`.

Primary source, committed in this repository:

- `references/sensors/datasheets/STEERING_F02U.V02.894-01 (BOSCH).pdf`
- Independently derived golden vectors and their derivation script:
  `references/sensors/golden_vectors/lws/` (`derive_lws_vectors.py`,
  `lws_golden_vectors.json`)

The vectors are hand-derived from the datasheet tables only. They are not
produced by running or transcribing either the MFE26-VC `LWSSteering`
decoder or this repository's encoder, so they are a genuine external
oracle rather than a mirror of the code under test.

## Bus

- 500 kbit/s, LSB (Intel) byte order, 100 Hz / 10 ms CAN update rate.

Note that the HIL rig's IO614 CAN channel is configured at 1 Mbit/s for the
existing inverter/virtual-VCU traffic, not at the sensor's native 500 kbit/s.
That is a property of the bench bus, not of this contract; a real LWS on a
real harness runs at 500 kbit/s.

## `LWS_Standard`, CAN ID `0x2B0`, DLC 5

Datasheet byte numbering is 0-based; MATLAB indices are 1-based.

| Datasheet byte | MATLAB index | Field |
| --- | --- | --- |
| 0-1 | 1-2 | `LWS_ANGLE`, signed `int16`, little-endian, 0.1 deg/count |
| 2 | 3 | `LWS_SPEED`, unsigned `uint8`, 4 deg/s per count |
| 3 | 4 | bits 7:3 reserved, bit 2 `TRIM`, bit 1 `CAL`, bit 0 `OK` |
| 4 | 5 | reserved |

Range is +/-780 deg; angular speed is 0 to 1016 deg/s, so the largest live
speed count is 254.

### Truth table

The datasheet column order is `TRIM`, `OK`, `CAL`.

| TRIM | OK | CAL | ANGLE | SPEED | Meaning |
| --- | --- | --- | --- | --- | --- |
| 1 | 1 | 1 | value | value | calibrated, information valid |
| 1 | 1 | 0 | `0x7FFF` | value | not calibrated, speed still valid |
| 1 | 0 | 0 | `0x7FFF` | `0xFF` | failure mode |
| 0 | 0 | 0 | `0x7FFF` | `0xFF` | failure mode |

Any other combination is explicitly not valid. `packLwsFrame` refuses to
encode one and `decodeLwsFrame` reports it through
`statusCombinationValid`. A measurement is valid only when all three bits
are set and neither sentinel is present.

`0xFF` is reserved as the speed sentinel, so a live reading can never
encode speed count 255.

## `LWS_Config`, CAN ID `0x7C0`, DLC 2

Command code word `CCW` in the low bits: `0x05` resets the calibration
status of the angle, `0x03` sets `LWS_Angle` to 0 deg. The datasheet's
zeroing procedure is ordered -- reset with `0x05` first, then calibrate
with `0x03` -- and a zero adjustment is required after every assembly.
The model enforces the ordering. It transmits `0x05` once, waits at least
**100 ms** (ten nominal 0x2B0 update periods), and requires its target-side
0x2B0 response to show the legal uncalibrated row (`ANGLE=0x7FFF`, status
`0x05`) before a later CAN Write invocation transmits `0x03` once. After
`0x03`, it requires a subsequent 0x2B0 update with angle zero and calibrated
status `0x07`; absence of that update for 100 ms fails the sequence. The
100 ms hold/timeout is an explicit conservative HIL policy; Bosch
does not specify a delay in the available datasheet. Stale, dropout, illegal
status, and sentinel injection can make the result check fail, but can never
skip it or collapse both commands into one transmit call. These are simulator
self-checks, not CAN acknowledgement and not physical-calibration evidence.

## Corrections applied relative to the original `master` implementation

Two defects were found when this contract was checked against the
datasheet during the port to `virtual-vcu`:

1. **Status byte offset.** `packLwsFrame` wrote the status bits into
   datasheet byte 4 (the reserved byte) and `decodeLwsFrame` read them back
   from the same wrong offset, so the round-trip test passed while the
   bytes on the wire were wrong. `packLwsPayload`, which feeds the actual
   Simulink CAN Pack block, already used the correct byte 3, so the
   golden-vector path and the transmitted path disagreed with each other.
   Both now use byte 3. The golden vector in `TestSensorProtocol` was
   corrected from `85 FF 05 00 07` to `85 FF 05 07 00`.

2. **Missing truth-table sentinels.** The encoder emitted a live angle and
   speed regardless of the status bits, so an injected fault produced a
   frame no real sensor would send. `0x7FFF` / `0xFF` are now encoded per
   the table above, which is also what makes the GUI's invalid-status and
   sentinel fault injection meaningful.

A third correction lives in `build_inverter_hil_model.m`: `LWS_SPEED` was
being filled from the vehicle **yaw rate**. The datasheet defines it as the
steering wheel's angular speed, i.e. the rate of change of `LWS_ANGLE`.
Yaw rate is a different quantity carried by the MTi rate-of-turn frame.

## Open items

- The ordered `0x05` then `0x03` calibration sequence and its timing are
  not enforced or tested.
- Nothing here has been confirmed against a physical LWS or a real VCU.
  Bus bitrate, termination, connector wiring, sensor mounting orientation
  and zero calibration remain separate hardware evidence gates.
