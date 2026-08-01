# IO614 CAN visibility test

Implements `io614_can_visibility_test_plan.md`. A minimal Speedgoat
Simulink Real-Time application that proves IO614 CAN channel 1 can
transmit and receive classic CAN frames and that every field the plan
asks for (ID, DLC, payload bytes, counters, timing, CAN status) is
visible as a named signal in Simulink Real-Time Explorer (View Values /
Add Instrument). It does not decode payload semantics and does not claim
correctness of any Ephorus signal meaning; see
`io614_can_visibility_test.dbc` for the caveats on that file.

Status: this model has been built and its diagram compiles cleanly
(`update diagram`) under MATLAB/Simulink R2024b. It has **not** been run
against real IO614 hardware, a PCAN adapter, or the VCU bus yet. Do not
connect it to the VCU harness without redoing the termination/ground
checks in `io614_can_visibility_test_plan.md`.

## Files

- `io614_can_visibility_test_R2024b.slx` / `.sldd` — the model and its
  tunable-parameter data dictionary. Generated; do not hand-edit, rerun
  `build_io614_can_visibility_test.m` instead.
- `build_io614_can_visibility_test.m` — regenerates the model from
  scratch. Must be run under MATLAB R2024b (it checks
  `version('-release')` and errors otherwise, matching the
  `inverter_hil` project convention). `build_io614_can_visibility_test(true)`
  overwrites existing output.
- `io614_can_visibility_test.dbc` — reference-only DBC inspired by the
  Ephorus CAN contract in `inverter_hil/inverter_hil_plan.md` section 4.
  The model does **not** use this DBC (it uses raw IO614 CAN Read/Write
  blocks, per the plan's raw-mode decision in section 6.1); it exists so
  the message IDs are documented in one place and can seed the eventual
  canonical `inverter_hil.dbc`.
- `captures/` — drop PCAN/bus-logger captures here during test runs.

## Model structure

- `IO614 CAN Setup` — CAN1, High-Speed CAN, 1 Mbit/s, standard 11-bit IDs.
- Receive path: `IO614 CAN FIFO Read Raw` (single FIFO read per 1 ms
  step) &rarr; Bus Selector &rarr; `Rx Decoder` (MATLAB Function block)
  &rarr; named outputs. The decoder latches the last valid frame so
  `rx_id_dec`/`rx_id_hex`/`rx_dlc`/`rx_payload_b0..b7` stay showing the
  most recent frame between arrivals, while `rx_valid` is only true on
  the step a frame actually arrived. `rx_count` and
  `rx_interarrival_ms` are cumulative/most-recent-gap counters.
- Transmit path: tunable parameters (`tx_enable`, `tx_id`, `tx_dlc`,
  `tx_payload_u8`, `tx_period_ms`) feed a `Tx Generator` (MATLAB Function
  block) that produces the IO614 CAN Write block's `Tx Control` pulse
  (`uint32(1)` = send this 1 ms step, `uint32(0)` = skip) whenever
  `tx_enable` is true and `tx_period_ms` has elapsed. **`tx_enable`
  defaults to `false`** — nothing transmits until an operator arms it.
- `IO614 CAN Diagnostics` — bus load, bus-off, recovery count, transmit
  buffer overrun, receive buffer overrun, and bus-warning-limit status.

## Signal name -> plan field mapping

Everything below is a named root-level Outport, which is what makes it
show up in Simulink Real-Time Explorer without extra configuration.

| Plan field | Signal name(s) |
| --- | --- |
| Received ID | `rx_id_dec`, `rx_id_hex` (same uint32 value; set the instrument's numeric format to hex for the `_hex` one — Simulink Real-Time Explorer does not have a separate hex signal type) |
| DLC | `rx_dlc` |
| Payload bytes | `rx_payload_b0` .. `rx_payload_b7` |
| Receive count | `rx_count` |
| Extended/remote flags | `rx_is_extended`, `rx_is_remote` |
| Frame-present-this-step | `rx_valid` |
| Hardware receive timestamp | `rx_last_timestamp` |
| Time since previous valid frame | `rx_interarrival_ms` |
| Transmit ID | `tx_id_dec`, `tx_id_hex` (same value; same hex-display note) |
| Transmit DLC | `tx_dlc` |
| Transmit payload bytes | `tx_payload_b0` .. `tx_payload_b7` |
| Transmit count | `tx_count` |
| Transmit period / enable (readback) | `tx_period_ms`, `tx_enable` |
| Bus-off | `can_bus_off` |
| Error/warning | `can_error_warning` (CAN Status "Bus-Warning Limit") |
| Receive overrun | `can_receive_overrun` |
| Transmit pending/overrun | `can_transmit_pending` (channel-level, from CAN Status), `can_write_status` (per-write-call overrun, from the CAN Write block itself) |
| (bonus, not in plan) | `can_bus_load`, `can_recovery_count` |

## Tunable parameters

`tx_enable`, `tx_id`, `tx_dlc`, `tx_payload_u8`, and `tx_period_ms` are
`Simulink.Parameter` objects with `StorageClass = SimulinkGlobal` in
`io614_can_visibility_test_R2024b.sldd`, so they can be changed from
Simulink Real-Time Explorer (or `tg.setparam`) while the target
application is running, without a rebuild — matching the plan's
requirement. Defaults: `tx_enable = false`, `tx_id = 0x383`,
`tx_dlc = 8`, `tx_payload_u8 = [1 2 3 4 5 6 7 8]`, `tx_period_ms = 100`.

To use the VCU-facing presets from the plan, just change `tx_id` at
runtime to one of the nine status IDs (`0x383`..`0x400`); the receive
path is promiscuous raw-FIFO and needs no configuration change to see
any of the four VCU control IDs (`0x186`, `0x196`, `0x1A6`, `0x1B6`).

## Known gaps / follow-ups

- Not yet built for the Speedgoat target or run on hardware.
- `tx_period_ms` and command-age timing are quantized to the 1 ms base
  rate, same caveat as `inverter_hil_plan.md` documents for its own
  timing.
- The DBC's bit layout/scale is unverified (see the file's own header
  comment) and is not used by the model at runtime.
- Follow the PCAN smoke test and VCU connectivity procedures in
  `io614_can_visibility_test_plan.md` before connecting real hardware —
  termination, ground strategy, and digital-level checks from
  `inverter_hil_plan.md` sections 3.3/3.4 still apply.
