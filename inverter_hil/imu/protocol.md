# MTi-680G HIL protocol

The independent contract in `imuProtocol.m` is based on Xsens **MT CAN
Protocol Documentation**, document MT1604P, Revision A, 16 Sept 2019
(`references/sensors/datasheets/MTCANProtocolDocumentation.pdf`). No
`2020.A` revision of this document exists; that earlier citation was wrong.

Implemented message contracts:

| Message | CAN ID | DLC | Scale | Axes |
|---|---:|---:|---:|---|
| Acceleration | `0x034` | 6 | `2^-8 m/s^2/count` | X, Y, Z |
| Rate of turn | `0x032` | 6 | `2^-9 rad/s/count` | X, Y, Z |
| Euler angles | `0x022` | 6 | `2^-7 deg/count` | roll, pitch, yaw |

The wire byte order is explicit in the independent encoder/decoder and is
covered by golden vectors. Before physical deployment, compare it with the
installed MTi CAN DBC and capture a real sensor frame.

The simulator must not import or call the VCU MTi decoder. Its golden vectors
are the test oracle for both simulator encoding and VCU decoding.
