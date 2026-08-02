# IO614 CAN visibility test plan

Status: planning document only. Do not build hardware from this file without
reviewing the IO614 channel, bus termination, and VCU CAN assignment.

## Goal

Create a very small Speedgoat/Simulink Real-Time test model that proves IO614
CAN channel 1 can transmit and receive classic CAN frames, and that the frames
are visible from Simulink Real-Time Explorer using View Values and instruments.

The test should support two bench modes:

- Speedgoat IO614 connected to a PCAN adapter.
- Speedgoat IO614 connected to the VCU CAN bus.

The operator must be able to see at least the received CAN identifier, DLC,
payload bytes, receive count, transmit count, and error/status fields while the
application is running on the Speedgoat.

## Proposed folder

Place the eventual test under:

```text
inverter_hil/io614_can_visibility_test/
```

Suggested contents:

```text
io614_can_visibility_test/
  README.md
  io614_can_visibility_test.slx
  build_io614_can_visibility_test.m
  inverter_hil.dbc
  captures/
```

`inverter_hil.dbc` should be copied from the canonical inverter HIL CAN database
once that file exists. If the DBC has not been generated yet, the temporary test
can use raw CAN IDs/payloads from `inverter_hil_plan.md` and record that the DBC
copy step is pending.

## CAN configuration

Use the same physical assumption as the inverter HIL plan:

- Module: IO614.
- Channel: CAN channel 1.
- Mode: High-Speed CAN.
- Baud rate: 1 Mbit/s.
- Frame type: classic CAN, standard 11-bit identifiers.
- DLC: 8 bytes for all inverter HIL control/status frames.
- Termination: exactly two 120 ohm terminators on the bus, verified with power
  off before connecting equipment.

Expected wiring from the current plan:

| IO614 pin | Signal | Planned connection |
| --- | --- | --- |
| 7 | CAN High | `CAN1_P`, VCU pin 119 |
| 2 | CAN Low | `CAN1_N`, VCU pin 117 |
| 3 | CAN ground | CAN/logic reference ground after ground review |

## Minimal model behavior

The test model should contain only the IO614 CAN setup, one receive path, one
transmit path, status diagnostics, counters, and dashboard-visible signals.

### Receive path

Use an IO614 CAN Read block in raw/FIFO mode and expose these signals as named
observable outputs:

- `rx_valid`
- `rx_id`
- `rx_is_extended`
- `rx_is_remote`
- `rx_dlc`
- `rx_payload_u8[8]`
- `rx_count`
- `rx_last_timestamp`
- `rx_interarrival_ms`

The model should keep the last valid received frame in retained signals so the
operator can click View Values and inspect the most recent ID and payload even
when frames are intermittent.

### Transmit path

Use one simple periodic transmit frame first, with tunable fields:

- `tx_enable`
- `tx_id`
- `tx_dlc`
- `tx_payload_u8[8]`
- `tx_period_ms`

Default PCAN smoke-test transmit frame:

| Field | Default |
| --- | --- |
| ID | `0x383` |
| DLC | `8` |
| Payload | `01 02 03 04 05 06 07 08` |
| Period | `100 ms` |

The operator should be able to change `tx_id` and each payload byte from
Simulink Real-Time Explorer or an instrument without rebuilding.

### VCU-facing presets

After PCAN smoke testing works, add presets for the inverter HIL IDs:

VCU to Speedgoat receive IDs:

- `0x186`
- `0x196`
- `0x1A6`
- `0x1B6`

Speedgoat to VCU transmit IDs:

- `0x383`
- `0x385`
- `0x393`
- `0x395`
- `0x3A3`
- `0x3A5`
- `0x3B3`
- `0x3B5`
- `0x400`

Do not claim semantic correctness of payload fields in this test. Its purpose is
transport visibility: ID, DLC, payload bytes, timing, and bus health.

## Instrument/view requirements

The final test must expose named signals suitable for View Values and Add
Instrument, similar to the voltage loopback test:

- `rx_id_hex`
- `rx_id_dec`
- `rx_dlc`
- `rx_payload_b0` through `rx_payload_b7`
- `rx_count`
- `tx_id_hex`
- `tx_id_dec`
- `tx_payload_b0` through `tx_payload_b7`
- `tx_count`
- `can_bus_off`
- `can_error_warning`
- `can_receive_overrun`
- `can_transmit_pending`
- `can_write_status`

Prefer separate scalar signals for each payload byte because they are easier to
add to instruments and watch live than a vector signal.

## Test procedure

### PCAN smoke test

1. Power off the bus and verify resistance across CAN High and CAN Low.
2. Connect IO614 CAN1 to PCAN CAN High, CAN Low, and CAN ground.
3. Start PCAN at 1 Mbit/s, classic CAN.
4. Build and run the Speedgoat test application. `tx_enable` now
   defaults to `true`, so transmission starts immediately on run — no
   separate arming step.
5. (If `tx_enable` was overridden to `false` during a previous run, set
   it back to `true` in Simulink Real-Time Explorer.)
6. Confirm PCAN sees periodic ID `0x383` with payload
   `01 02 03 04 05 06 07 08`.
7. Transmit a manual PCAN frame, for example ID `0x186`, DLC 8, payload
   `10 20 30 40 50 60 70 80`.
8. Confirm Simulink Real-Time View Values shows `rx_id = 0x186`,
   `rx_dlc = 8`, and matching payload bytes.
9. Confirm `rx_count` increments and CAN status signals remain healthy.

### VCU connectivity test

1. Disconnect PCAN transmit if it would disturb the VCU bus.
2. Confirm CAN1 wiring and termination against the VCU harness.
3. `tx_enable` now defaults to `true` and transmission starts the instant
   the target application runs — **before connecting to the live VCU
   harness, force `tx_enable = false`** (edit the default in the
   dictionary and rebuild, or set it in Simulink Real-Time Explorer and
   confirm it took effect before the app starts) so nothing is sent
   until the VCU test state has been confirmed safe. Run the Speedgoat
   test with `tx_enable = false`.
4. Observe whether VCU control IDs `0x186`, `0x196`, `0x1A6`, and `0x1B6`
   appear in View Values.
5. Enable one low-risk periodic Speedgoat status frame only after confirming the
   VCU test state is safe.
6. Confirm the VCU or bus logger sees the transmitted ID and payload.
7. Record received IDs, payloads, rates, and CAN diagnostics.

## Pass criteria

PCAN mode passes when:

- PCAN receives the Speedgoat transmit frame with the configured ID and payload.
- Speedgoat receives the PCAN transmit frame with the configured ID and payload.
- Counters increment monotonically.
- Bus-off, warning, and receive-overrun are not asserted during normal traffic.

VCU mode passes when:

- Speedgoat receives at least one expected VCU control ID.
- Speedgoat can transmit at least one expected inverter status ID.
- The operator can see IDs and payload bytes live through View Values or an
  added instrument while the Speedgoat application is running.
- CAN diagnostics remain visible even if the bus is unhealthy.

## Fault checks

Include deliberate checks after the basic pass:

- Wrong baud rate produces no valid receive traffic and raises diagnostics.
- Missing termination or disconnected CAN Low/High causes unhealthy status.
- Invalid `tx_dlc` is clamped or rejected before it reaches the write block.
- `tx_enable = false` stops periodic transmission.
- Receive-overrun is visible if PCAN floods the bus faster than the model can
  drain it.

## Open decisions

- Exact source path for the canonical inverter HIL DBC.
- Whether the test should use raw IO614 blocks only or Speedgoat database
  parser blocks once the DBC is available.
- Whether VCU receive testing should be passive-only at first.
- Whether the VCU expects status frames only after specific ignition, RTD, or
  enable conditions.
