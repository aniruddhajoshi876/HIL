# CarMakerPedalDemand CAN Frame Specification

**Status:** Implemented and host-tested on branch `CAN`. The direct
CarMaker-PCAN-to-Speedgoat path was observed on hardware in commit `61a9dd6`.
That observation did not include a real VCU.

The complete bench map and evidence boundary are in
[`real_vcu_can_signal_map.md`](real_vcu_can_signal_map.md).

## Wire contract

| Property | Requirement |
|---|---|
| CAN identifier | Standard 11-bit data frame `0x500` |
| DLC | 8 |
| Nominal cycle | 10 ms |
| Byte order | Intel/little-endian (`@1`) |

| Bits | Signal | Encoding | Constraint |
|---:|---|---|---|
| 0..15 | `ThrottleDemand` | unsigned u16, raw x 0.01% | raw 0..10000 |
| 16..31 | `BrakeDemand` | unsigned u16, raw x 0.01% | raw 0..10000 |
| 32 | `Active` | Boolean | 1 requests CAN ownership |
| 33..36 | `AliveCounter` | unsigned 4-bit | sender increments modulo 16 |
| 37..39 | `Reserved0` | unsigned 3-bit | zero |
| 40..47 | `Integrity` | unsigned 8-bit | CRC below |
| 48..63 | `Reserved1` | unsigned 16-bit | zero |

`Integrity` is CRC-8/SAE-J1850 over Bytes 1..5:

- width 8;
- polynomial `0x1D`;
- initial remainder `0xFF`;
- `RefIn=false`, `RefOut=false`;
- final XOR `0xFF`;
- no appended CAN ID or DLC; and
- check value for five zero bytes `0x10`.

## Sender behavior

`carmaker/FS_race/src_cm4sl/IO.c` implements direct PCAN transmission:

1. Convert `DrivMan.Gas` and `DrivMan.Brake` using
   `round(normalizedValue * 10000)` and clamp to 0..10000.
2. Encode both u16 values least-significant byte first.
3. Set `Active=1` and insert the current modulo-16 counter.
4. Leave both reserved regions zero.
5. Calculate the CRC over Bytes 1..5 and write Byte 6.
6. Transmit when `CycleNo % 10 == 0` and PCAN is ready.

This is not an RBS-generated frame. RBS cannot bind PCAN-USB in the tested
CarMaker configuration.

## Implemented receiver behavior

`decodePedalDemandFrame` rejects:

- extended or remote frames;
- an ID other than `0x500`;
- DLC other than 8;
- a payload other than a 1x8 `uint8` vector;
- either pedal raw value above 10000;
- nonzero `Reserved0` or `Reserved1`; and
- a CRC mismatch.

`receivePedalDemandFrame` and `pedalDemandSnapshot` then apply:

1. The first valid frame is retained but cannot prove counter advancement.
2. A later frame sets `counterAdvanced` only when its counter equals the
   previous counter plus one modulo 16. A repeated or skipped counter clears
   ownership for that tuple.
3. Every structurally valid frame refreshes the timestamp and replaces the
   tuple, including `Active=0` and non-sequential counters.
4. A rejected frame leaves the previous tuple, timestamp, and ownership inputs
   unchanged.
5. Freshness is `ageMs <= 100`; the tuple is stale at 101 ms.
6. `ownsPedals = fresh && counterAdvanced && active`.

Ownership always applies to throttle and brake together. When false, both
source switches use the configured GUI-command fallback.

## Boundary decisions

These are implementation facts, not inferred requirements:

- exact `+1 modulo 16` counter progression is required;
- 100 ms is fresh and 101 ms is stale; and
- isolated invalid frames are ignored instead of immediately invalidating the
  previous command.

Changing one requires corresponding receiver and unit-test changes. Do not
change only this document.

## Twenty-percent example

```text
ThrottleDemand = 2000 = 0x07D0
Byte 1 = D0
Byte 2 = 07
```

The remaining bytes depend on brake, counter, and CRC.

## CarMaker telemetry

`0x501` and `0x502` are independent Speedgoat-to-CarMaker telemetry
frames at 5 ms. Their layouts and the absence of a CarMaker receive timeout are
documented in `real_vcu_can_signal_map.md`.
