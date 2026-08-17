# CarMakerPedalDemand CAN Frame Specification

**Status:** Proposed design not built. This document is the single authority for
the wire contract of `CarMakerPedalDemand`; it replaces the incompatible
independent interpretations described below. “Byte 1” means the first CAN data
byte and DBC bit 0 is its least-significant bit.

## 1. Investigation findings

### 1. Existing pedal-frame precedent

**Confirmed.** The historical `virtual-vcu` implementation creates an eight-byte
pedal payload in little-endian byte order. It writes throttle to byte 1 as an
unsigned integer percentage, rounded and clamped to 0..100; it writes brake as
an unsigned 16-bit integer in PSI (`round(650 * normalizedBrake)`) to bytes
2..3 and duplicates that word in bytes 4..5. On a little-endian host,
`typecast(uint16, 'uint8')` produces low byte first. Local source:
`virtual-vcu/+virtualvcu/packPedalFrame.m:1-10` (read-only `git show
virtual-vcu:...`).

**Confirmed.** The preceding conversion produces a continuous, clamped 0..100
percentage from firmware-style raw ADC values; conversion to raw uses a rounded
16-bit full-scale value. Local source: `virtual-vcu/+virtualvcu/rawToPedal.m:1-16`;
`virtual-vcu/+virtualvcu/voltageToRaw.m:1-5` (read-only `git show
virtual-vcu:...`).

**Confirmed.** `virtual-vcu/config/MFE26_Inverter.dbc` contains the inverter
control/status frames but no `BO_ 501`/`0x1F5` pedal frame. Thus the helper is
real encoding precedent, but the stated historical DBC does not independently
define its pedal wire contract. Local source:
`virtual-vcu/config/MFE26_Inverter.dbc:50-161` (read-only `git show
virtual-vcu:...`); `virtual-vcu/+virtualvcu/packPedalFrame.m:1-10`.

**Proposed design not built.** Preserve the project’s Intel/little-endian
convention, but do *not* copy the legacy throttle-u8, brake-PSI, duplicated-word
layout: it neither represents the new named field list nor preserves the
demonstrated percentage resolution. The specified frame below instead uses two
u16 values in 0.01 percentage-point units.

### 2. Real-VC pedal resolution

**Confirmed.** The local `PINOUTS.md` records that the GUI-to-firmware pedal
round trip was verified at 0.0000 percentage-point error at seven stated test
points, and that the ADC is 12-bit, left-justified to a 16-bit word (raw steps
of 16). It identifies the conversion routines as firmware evidence, but the
referenced `MFE26-VC/Core/Src/driverInputs.cpp` source itself is not present in
this worktree. Local source: `PINOUTS.md:281-299`.

**Confirmed.** A whole-percent CAN representation is lossy relative to this
existing path: integer percent can represent only 101 values whereas the
bench/firmware path carries sub-percent values and was verified without the
rounding error that a whole-percent boundary introduces. This conclusion is an
inference from the cited continuous calibration/round-trip record, not a claim
that every fractional value has separately been bench-measured. Local source:
`PINOUTS.md:292-299`; `virtual-vcu/+virtualvcu/rawToPedal.m:5-16`.

**Open question.** Obtain and review `driverInputs.cpp` before treating any
specific internal firmware percentage type, quantisation rule, or required
minimum resolution as confirmed. The source is absent here.

### 3. House style on the inverter bus

**Confirmed.** The inverter payload convention is Intel/little-endian:
packers place fields at ascending least-significant bit offsets in a `uint64`,
and the control decoder reconstructs `int16` as low byte plus high byte shifted
by eight. Local source: `inverter_hil/+inverterhil/packStatus3X3.m:16-30`;
`inverter_hil/+inverterhil/decodeControlFrame.m:49-62,85-91`.

**Confirmed.** Existing signal scaling is fractional and engineering-unit
specific, not limited to integers: 1/256 Nm command-limit profile, 1/32 Nm
status torque, and 1/64 V DC link are explicit examples. Local source:
`inverter_hil/+inverterhil/protocol.m:22-51`;
`inverter_hil/+inverterhil/packStatus3X3.m:20-29`;
`inverter_hil/+inverterhil/packSystemStatus.m:14-28`.

**Confirmed.** No existing inverter control/status frame implementation uses a
CAN alive counter or CRC. The only such code in this worktree is the newly
introduced pedal path and its tests. Local source:
`inverter_hil/+inverterhil/decodeControlFrame.m:1-97`;
`inverter_hil/+inverterhil/packStatus3X3.m:1-48`;
`inverter_hil/+inverterhil/packStatus3X5.m:1-24`;
`inverter_hil/+inverterhil/packSystemStatus.m:1-38`;
`inverter_hil/+inverterhil/decodePedalDemandFrame.m:1-58`.

### 4. Integrity and counter basis

**Confirmed.** The current Speedgoat implementation invented a CRC-8/SAE-J1850
check over its own bytes 1..3 and a four-bit counter; neither has an equivalent
on the existing inverter frames. Local source:
`inverter_hil/+inverterhil/decodePedalDemandFrame.m:4-5,23-31,40-52`.

**Confirmed.** The local project plan cites *UsersGuide_HIL.pdf* section 4.9,
pp. 73-75 for RBS “counters/CRC hooks”; it does not record an RBS-defined CRC
polynomial, initial value, final XOR, covered bytes, or an assertion that RBS
can implement an arbitrary custom CRC. Local source:
`carmaker_real_vcu_can_interface_plan.md:120,136`.

**Open question.** `UsersGuide_HIL.pdf` is not present in this worktree (nor was
it found in the accessible IPG worktree), so section 4.9 pp. 73-75 could not be
independently read. Confirm that the intended CarMaker/RBS version can generate
the exact proposed algorithm below, or implement/configure it by a supported
explicit mechanism; do not rely on the generic “hooks” citation.

**Proposed design not built.** A counter plus CRC is warranted for this new
pedal-authority command because timeout alone cannot detect a held/replayed
otherwise timely payload and CAN’s link-layer CRC does not supply an
application-level freshness sequence. This is a design decision for this new
frame, not existing-bus precedent. The CRC covers every semantic byte before
the CRC (bytes 1..5), rather than only the first three bytes.

### 5. Root cause

**Confirmed.** The shared description fixed ID and field names but omitted bit
positions, byte order, field scales/widths, CRC parameters and coverage, and
counter acceptance behavior. CarMaker consequently put 16-bit 0.01%-scaled
pedals first and integrity in byte 6, while the decoder expects u8 pedals,
integrity in byte 4, and bytes 5..8 zero. Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:1-8` (accessible IPG worktree);
`inverter_hil/+inverterhil/decodePedalDemandFrame.m:4-31`.

**Proposed design not built.** A versioned byte/bit table, exact CRC test
vectors, and one joint golden-payload test before either implementation would
have prevented the divergence.

## 2. Authoritative wire contract

**Proposed design not built.** All requirements in this section are normative.

| Property | Requirement |
|---|---|
| CAN identifier | Standard (11-bit) data frame, `0x500` (decimal 1280), not extended and not remote. |
| DLC / cycle | DLC exactly 8; transmit cyclically every 10 ms. |
| Bit convention | Intel/little-endian DBC convention (`@1`): a signal start bit is its least-significant bit; multi-byte least-significant byte is sent first. |

| Byte(s), DBC start bit | Signal | Wire type and raw range | Physical value / constraint |
|---|---|---|---|
| 1..2, bit 0 | `ThrottleDemand` | unsigned 16-bit, 0..10000 | `raw * 0.01 %`; transmit and accept 0.00..100.00 %. |
| 3..4, bit 16 | `BrakeDemand` | unsigned 16-bit, 0..10000 | `raw * 0.01 %`; transmit and accept 0.00..100.00 %. |
| 5 bit 0, bit 32 | `Active` | unsigned 1-bit, 0 or 1 | 1 grants CAN ownership only when all receiver rules below pass; 0 is valid but grants no ownership. |
| 5 bits 1..4, bit 33 | `AliveCounter` | unsigned 4-bit, 0..15 | Sender increments modulo 16 on every cyclic transmission. Initial value after sender start is arbitrary. |
| 5 bits 5..7, bits 37..39 | `Reserved0` | unsigned 3-bit | Must transmit zero; receiver rejects nonzero. |
| 6, bit 40 | `Integrity` | unsigned 8-bit | CRC-8/SAE-J1850 specified below. |
| 7..8, bits 48..63 | `Reserved1` | unsigned 16-bit | Must transmit zero; receiver rejects nonzero. |

**Proposed design not built.** `Integrity` is CRC-8/SAE-J1850 over bytes 1
through 5 in transmission order, including `Active`, `AliveCounter`, and the
three zero reserved bits. Parameters are: width 8; polynomial `0x1D`
(`x^8 + x^4 + x^3 + x^2 + 1`); initial remainder `0xFF`; non-reflected input
and output (`RefIn=false`, `RefOut=false`); final XOR `0xFF`; no appended CAN
ID, DLC, byte 6, or bytes 7..8. The expected check value for five zero bytes is
`0x10`. These parameters remove all algorithm decisions from a DBC writer or
decoder author.

**Proposed design not built.** Sender rule: encode physical percentage as
`round(valuePercent / 0.01)` and reject/clamp policy must be resolved by the
sender before transmission; on the wire, values outside 0..10000 are invalid.
The sender shall set both reserved regions to zero, increment the counter once
per 10-ms emission, compute the CRC last, and place it in byte 6.

**Proposed design not built.** Receiver acceptance rule:

1. Reject a frame unless it is standard, data, ID `0x500`, DLC 8, and has an
   eight-`uint8` payload.
2. Reject when either pedal raw value exceeds 10000, `Reserved0` is nonzero,
   `Reserved1` is nonzero, or byte 6 differs from the specified CRC over bytes
   1..5.
3. For the first otherwise-valid frame after startup, timeout, or receiver
   reset, accept any counter value and store it. For each later otherwise-valid
   frame, accept only a counter different from the last accepted counter;
   reject an unchanged counter as `counter_not_advanced`. A skipped counter is
   acceptable so a lost CAN frame does not prevent recovery.
4. Only an accepted frame refreshes the receipt time and replaces the retained
   atomic throttle/brake/active tuple. Invalid frames never refresh it.
5. The tuple is fresh for strictly less than 100 ms after its accepted receipt
   time; at 100 ms or later it is stale. Grant CAN pedal ownership only when the
   retained tuple is fresh and `Active=1`. On stale, invalid, or inactive input,
   withdraw ownership of *both* pedals together and use the separately selected
   non-CAN fallback.

**Confirmed.** The 100-ms timeout is already the configured pedal demand
timeout, and the existing documentation states atomic dual-pedal ownership with
active/counter/integrity/range/reserved/age checks. Local source:
`inverter_hil/+inverterhil/protocol.m:53-58`; `PINOUTS.md:218-225`.

## 3. Required implementation alignment (not performed here)

### CarMaker DBC

**Proposed design not built.** The current CarMaker field placement already
matches this table: `ThrottleDemand 0|16@1+ (0.01,0)`, `BrakeDemand
16|16@1+ (0.01,0)`, `Active 32|1@1+`, `AliveCounter 33|4@1+`, `Integrity
40|8@1+`, and reserved bits 48..63. Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:1-8` (accessible IPG worktree).

**Proposed design not built.** DBC diff-level work: retain those six field
locations; replace `Reserved : 48|16` with `Reserved0 : 37|3` and `Reserved1 :
48|16`; add comments/attributes stating the 10-ms cycle, exact counter rule,
CRC-8/SAE-J1850 parameters and bytes 1..5 coverage, and reserved-zero rule.
No pedal scaling or byte-order change is required on this side.

### Speedgoat decoder and protocol

**Proposed design not built.** `decodePedalDemandFrame.m` must change
substantially: decode little-endian u16 bytes 1..2 and 3..4 at 0.01%, parse
flags in byte 5, validate byte 5 bits 5..7 and bytes 7..8 as zero, and validate
byte 6 using the specified CRC over bytes 1..5. It must remove the current u8
0..100 interpretation, byte-4 CRC, and bytes-5..8-reserved interpretation.
Local source: `inverter_hil/+inverterhil/decodePedalDemandFrame.m:4-31,40-52`.

**Proposed design not built.** The retainer must implement the explicit
different-from-last-counter rule and strict 100-ms boundary above; update its
tests with byte-level CRC vectors and an accepted frame such as throttle
`12.34%` / brake `56.78%`. `protocol.m` retains `pedalDemandId = 0x500` and
`pedalDemandTimeoutMs = 100`; add only protocol constants/comments needed to
centralize the 10-ms period and CRC/counter contract. Local source:
`inverter_hil/+inverterhil/protocol.m:10-11,53-58`;
`inverter_hil/+inverterhil/receivePedalDemandFrame.m:1-22`.

**Proposed design not built.** Therefore the Speedgoat decoder is the side that
must change materially. The CarMaker DBC needs only clarification/splitting of
its reserved declaration and integrity metadata, provided its transmitter is
configured for the exact CRC/counter rules above.

## 4. Open decisions that cannot be inferred here

**Open question.** Confirm against the actual RBS manual and target version that
the exact CRC can be generated, rather than merely that a counter/CRC hook
exists.

**Open question.** Confirm from the unavailable firmware source whether 0.01%
is sufficient for every real control decision. It is deliberately far less
lossy than whole-percent encoding, but this repository cannot establish a
firmware-mandated minimum granularity.

**Open question.** The fallback behavior after CAN ownership withdrawal (zero,
immediate GUI, or operator-armed GUI) remains a safety/product decision. The
frame contract only requires withdrawal of both pedals atomically.
