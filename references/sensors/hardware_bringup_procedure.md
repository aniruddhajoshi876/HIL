# MTi-680G and LWS hardware bring-up procedure

Status: bench procedure; record evidence before closing A1, A3, A9, or the
MTi configuration gate. Host tests and HIL-generated frames do not satisfy
this procedure.

Primary contract: `mti680_can_contract.md` and `imu_contract_delta.md`.
Protocol citation: **MT1604P Revision A, 16 September 2019**. Do not cite a
"2020.A" revision; no such document has been located.

## 1. Equipment and common setup

Required equipment:

- MTi-680G, its official Xsens UART/RS232/configuration cable, and a PC with
  the installed MT Manager version recorded below;
- isolated two-channel CAN interface/analyzer capable of 250 and 500 kbit/s,
  raw timestamped logging, standard-ID filtering, and error-frame display;
- breakout harness that exposes CAN-H, CAN-L, supply, and ground without
  back-probing a powered connector;
- regulated 4.5--24 V bench supply with current limit, DMM, and two 120 ohm
  CAN terminators;
- nonmagnetic square/level and a marked turntable or rate table for repeatable
  90 degree orientations and rotations;
- the exact MTi bracket/harness intended for the car, plus the vehicle datum
  drawing or a physically marked forward/left/up reference.

Record before applying power:

| Item | Actual |
|---|---|
| Date / operator | |
| MTi serial number / firmware | |
| MT Manager version | |
| CAN analyzer make / firmware | |
| Xsens cable / interface part number | |
| Supply setpoint / current limit | |
| Harness revision | |
| VCU firmware commit, if connected | |

With all devices unpowered, measure resistance from CAN-H to CAN-L at the two
physical ends of the completed bench bus. Expected: **60 ohm nominal** (two
120 ohm terminators in parallel). Record the measured value. Connect analyzer
ground to the bench reference, then power only the sensor and analyzer first.
Do not connect the Speedgoat or vehicle VCU until the standalone captures pass.

Save every analyzer log as raw frames with ID, DLC, bytes, timestamp, bitrate,
and error counters. Photograph each physical orientation. Never infer bitrate
from decoded traffic alone; record the analyzer channel setting that produces
error-free frames.

## 2. MTi CAN enable and 500 kbit/s configuration gate

The factory state is CAN output disabled and 250 kbit/s (baud code `0x00`).
The required state is CAN output enabled and 500 kbit/s (baud code `0x0A`).
Configuration is over UART/RS232 in Config State, not over CAN.

1. Leave the CAN analyzer listening at 250 kbit/s. Connect the MTi through the
   official Xsens configuration cable and let MT Manager identify it. Record
   the detected serial number and firmware; do not guess a serial baud rate.
2. Enter Config State. Read the current CAN configuration and export/save the
   complete pre-change configuration. Expected factory result on an untouched
   unit: output disabled, baud code `0x00`. Record the actual values even if
   they differ.
3. Set CAN baud to **500 kbit/s / code `0x0A`** and enable CAN output. Configure
   only the messages needed by the following tests: Acceleration, RateOfTurn,
   and VelocityXYZ. Record every displayed CAN ID and output frequency before
   accepting the change; MT1604P defines no default message frequency.
4. Write/apply the configuration, return to Measurement State, and power-cycle
   the MTi. Disconnect the UART/RS232 configuration path so the CAN capture is
   standalone evidence.
5. At analyzer 250 kbit/s, observe for 10 s. Expected after the change: no
   valid MTi frames. Save the log and error counters.
6. Change only the analyzer to 500 kbit/s and observe for 30 s. Expected:
   error-free standard frames at the configured IDs and measured rates. Confirm
   rate from analyzer timestamps/counts, not host GUI polling.
7. Reconnect MT Manager, re-enter Config State, read the configuration back,
   and save/export it. Expected: CAN enabled and baud code `0x0A` persisted.

| Check | Expected | Actual | Evidence file |
|---|---|---|---|
| Pre-change enable / baud | disabled / `0x00` | | |
| Post-cycle traffic at 250 kbit/s | no valid frames | | |
| Post-cycle traffic at 500 kbit/s | valid, no error frames | | |
| Read-back enable / baud | enabled / `0x0A` | | |
| Accel / gyro / velocity configured rates | recorded values | | |

Do not close this gate merely because a simulator and VCU communicate at
500 kbit/s. The physical MTi read-back and power-cycle capture are required.

## 3. A1 -- payload byte order

The decisive observation must come from the physical MTi or an Xsens-supplied
DBC/decoder, not from agreement between this simulator and MFE26-VC.

1. Configure only Acceleration output and log raw ID `0x034`, DLC 6 at
   500 kbit/s. Mount the MTi motionless with its case-marked **+X axis aligned
   downward**, so X reads approximately **+9.809 m/s^2**, while Y and Z are
   approximately zero. Photograph the orientation and collect at least 5 s.
2. Repeat with +X upward; X should change sign. Reject the run if vibration or
   the other axes make the gravity assignment ambiguous.
3. Inspect the first two raw payload bytes of stable samples. Decode both ways:
   big-endian signed int16 times `2^-8`, and little-endian signed int16 times
   `2^-8`. Only one interpretation may agree in sign and magnitude with the
   known gravity orientation on both captures.
4. Run the committed diagnostic vector
   `edge_little_endian_confusion_probe`: ID `0x034`, DLC 6, bytes
   `CF 09 00 00 00 00`. Feed it to the independent Xsens-supplied DBC/decoder
   if one is available, or replay it only as a decoder sanity check. Expected:
   big-endian = **-48.99609375 m/s^2**; little-endian =
   **+9.80859375 m/s^2**. A VCU/HIL round trip is not independent evidence.

| Evidence | Big-endian expected | Little-endian expected | Actual |
|---|---:|---:|---|
| Probe `CF 09 00 00 00 00`, X | -48.99609375 | +9.80859375 | |
| Physical +X-down stable bytes | approximately +9.809 only if byte order matches | approximately +9.809 only if byte order matches | |
| Physical +X-up sign reversal | approximately -9.809 | approximately -9.809 | |

Close A1 only after recording the physical raw bytes and the independently
correct interpretation. Keep A1 open if only repository-owned decoders agree.

## 4. A3 -- VelocityXYZ ID `0x075` versus `0x076`

MT1604P Table 4 says `0x075`; section 6.8.3 says `0x076`. Do not resolve the
contradiction from firmware or simulator behavior.

1. In MT Manager, enable only VelocityXYZ at a recorded rate; disable other
   GNSS/navigation CAN outputs that could use neighboring IDs. Save/export the
   configuration screen showing the product's chosen ID if the UI exposes it.
2. Give the MTi a valid GNSS solution outdoors or through the approved GNSS
   simulator/antenna setup. Record fix/status evidence. A stationary unit is
   acceptable for ID discovery, but move it several metres in a straight line
   if needed to make the payload visibly change.
3. Capture all standard IDs `0x070`--`0x079` at 500 kbit/s for at least 60 s.
   Record ID, DLC, frame count, measured period, and changing bytes.
4. Disable VelocityXYZ without changing anything else and repeat. The ID that
   disappears is the physical product's answer. Re-enable it and confirm the
   same ID returns.

| Candidate | Expected if authoritative | Enabled capture | Disabled capture | Re-enabled capture |
|---|---|---|---|---|
| `0x075`, DLC 6 | Table 4 wins | | | |
| `0x076`, DLC 6 | section 6.8.3 wins | | | |

Close A3 only if the enable/disable/re-enable capture isolates exactly one
candidate. Record an unexpected ID rather than forcing either expected answer.

## 5. A9 -- axes, signs, and installed mounting orientation

This test produces the missing vehicle-to-sensor transform. Perform it first
on the bare sensor and then with the production bracket installed.

1. Mark vehicle **forward, left, and up** on the bench fixture. Photograph the
   MTi case axes and bracket in that coordinate frame. Record connector and
   label orientation so the installation is reproducible.
2. With the sensor stationary, place each case axis (+X, +Y, +Z) downward in
   turn. For each pose capture 5 s of `0x034`. The aligned axis must show about
   +9.81 m/s^2 or -9.81 m/s^2; record the actual sign. This determines all
   accelerometer axis permutations and signs without assuming them.
3. Return the fixture level. Rotate it at a measured positive rate about
   vehicle Up, then about vehicle Left, then about vehicle Forward. Capture
   `0x032`; record which MTi axis responds and its sign. Repeat each rotation
   in the opposite direction to reject bias.
4. Install the bracket in its actual vehicle holes and repeat one gravity pose
   plus positive/negative yaw. Any difference from the bench transform is a
   mounting error, not a software convention.
5. For the Bosch LWS, mark straight ahead, complete zero calibration using the
   physical sensor procedure, then turn the steering wheel a measured 90
   degrees left and 90 degrees right. Capture `0x2B0`; record raw angle counts,
   decoded degrees, TRIM/CAL/OK, and which direction is positive.
6. Write the resulting explicit mapping (for example, vehicle-forward equals
   MTi case axis with recorded sign) into the vehicle integration document and
   reference the photos/logs. Do not substitute the MTi Figure 8 case axes for
   the as-installed vehicle transform.

| Vehicle quantity / action | Responding sensor axis or signal | Expected magnitude | Actual sign / mapping | Evidence |
|---|---|---:|---|---|
| Gravity with vehicle Up downward | one accel axis | about 9.81 m/s^2 | | |
| Positive vehicle yaw | one gyro axis | rate-table setting | | |
| Positive vehicle pitch | one gyro axis | rate-table setting | | |
| Positive vehicle roll | one gyro axis | rate-table setting | | |
| Wheel 90 deg left | LWS angle | about 90 deg | | |
| Wheel 90 deg right | LWS angle | about 90 deg opposite sign | | |

## 6. Completion record

Attach analyzer logs, MT Manager exports, photographs, and instrument settings.
For each item mark PASS only when the expected-versus-actual table is filled.

| Gate | Result | Reviewer / date |
|---|---|---|
| MTi CAN enabled and persisted at 500 kbit/s (`0x0A`) | OPEN | |
| A1 payload byte order | OPEN | |
| A3 VelocityXYZ physical ID | OPEN | |
| A9 vehicle axes/signs and mounting transform | OPEN | |

Until those rows pass, retain A1, A3, A9, and MTi reconfiguration as open
hardware gates. HIL host tests may verify packing, sequencing, counters, ages,
and GUI behavior; they do not establish wiring, termination, bitrate, CAN ACK,
physical mounting, or calibration correctness.
