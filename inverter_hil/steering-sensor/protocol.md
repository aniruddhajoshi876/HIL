# Bosch LWS HIL protocol

The independent contract in `lwsProtocol.m` is based on the supplied Bosch
F02U.V02.894-01 Steering Wheel Angle Sensor datasheet.

- Standard CAN ID `0x2B0`, DLC 5, 500 kbit/s, 100 Hz.
- Angle is little-endian signed `int16`, 0.1 degree/count, range +/-780 deg.
- Speed is signed byte with 4 degree/s/count resolution.
- Status byte uses `TRIM=bit 2`, `CAL=bit 1`, and `OK=bit 0`.
- A measurement is valid only when all three status bits are set.
- Configuration ID `0x7C0`, DLC 2: `0x05` resets calibration and `0x03`
  zeros the angle.

The simulator and VCU tests use independent golden frames. The simulator does
not call the VCU LWS decoder as a correctness oracle.
