# MTi-680G and Bosch LWS CAN contract (verified)

Status: **verified against primary documents**, 2026-08-16.
Verifier: HIL contract audit, branch `imu-can-contract`.

This file replaces the unverified contract that `inverter_hil/imu/imuProtocol.m`
was carrying. Every value below is traced to a document, a revision, and a
section or table. Where a document does **not** pin a value down, it is listed
under [Assumptions](#assumptions) instead of being invented.

## Source documents

All four are vendored under `references/sensors/datasheets/` so this repo is
self-contained. They were copied from `McGillFormulaElectric/MFE26-VC`, branch
`controls`, directory `data_sheets/`.

| Short name | Document | Revision / date |
|---|---|---|
| **[MTCAN]** | Xsens, *MTi 600-series MT CAN Protocol Documentation*, document **MT1604P** | **Revision A, 16 Sept 2019** (page footers read `Document MT0101P.2019.A`) |
| **[MT600]** | Xsens, *MTi 600-series Datasheet*, document **MT1603P** | Revision **2020.B**, Sept 2020 |
| **[MTLL]** | Xsens, *MT Low Level Communication Protocol Documentation* | see file |
| **[LWS]** | Bosch Motorsport, *Steering Wheel Angle Sensor LWS*, order no. **F02U.V02.894-01**, document 54425995 | en, 26 Aug 2025 |

> **Revision correction.** `imuProtocol.m` cites "MT1604P **2020.A**". No such
> revision exists. MT1604P's own revision table has exactly one row:
> `A | Sept 2019 | AKO | Initial Version`. `2020.A` is the revision of the
> *datasheet* MT1603P, which is a different document. The citation string must
> be fixed.

## MTi-680G product applicability

[MTCAN] section 2 gates each message on a product column `610 / 620 / 630 / 670`
(IMU / VRU / AHRS / GNSS-INS). MT1604P Rev A predates the MTi-680G, which
[MT600] revision `2020.A (Jun 2020)` added. The MTi-680G is an RTK GNSS/INS, so
it maps onto the **670** column. That is the column that enables
`XCDI_VelocityXYZ`, `XCDI_Latitude`, `XCDI_AltitudeEllipsoid`. See
[ASSUMPTION A2](#a2).

## 1. MTi CAN output message contract

Common to every message below:

* **Identifier type:** 11-bit standard by default; 11-bit vs 29-bit is
  selectable per message via the *ID length flag* in `SetCanOutputConfig`
  ([MTCAN] section 5.2.1, and section 4: "At the top right of the CAN output
  configuration screen the CAN frame Format can be set, (11-bit or 29-bit)").
* **Identifier value:** **user-configurable.** `SetCanOutputConfig` (MID 232 /
  `0xE8`) takes `Xsens CAN data id (7 bits), ID length flag (1 bit), ID mask
  (29 bits), Output frequency (11 bits)` per output. The IDs tabulated below are
  the defaults printed in [MTCAN] section 6 headings. **They are not immutable.**
* **Frame type:** classic CAN data frames, up to 8 data bytes, up to 1 Mbps
  ([MTCAN] section 6, Figure 5 text).
* **Byte order:** big-endian / MSB-first / DBC `@0` Motorola. See
  [ASSUMPTION A1](#a1) — [MTCAN] itself never says this.
* **Signedness:** as given in the Format column; `int16` is two's complement.
* **Offset:** every message has offset 0; there is no additive offset term
  anywhere in [MTCAN] section 6. Physical value = `raw_count * scaling`.

### 1.1 Messages the MFE26 vehicle needs

| Message | Default CAN ID | DLC | Fields (wire order) | Format | Byte offsets | Scaling (LSB) | Resolution | Doc range | Unit | Citation |
|---|---|---|---|---|---|---|---|---|---|---|
| `XCDI_Acceleration` | `0x034` | **6** | accX, accY, accZ | int16 | 0, 2, 4 | `2^-8` = 0.00390625 | 0.0039 | ±100 | m/s² | [MTCAN] §6.4.4 |
| `XCDI_RateOfTurn` | `0x032` | **6** | gyrX, gyrY, gyrZ | int16 | 0, 2, 4 | `2^-9` = 0.001953125 | 0.0020 | ±35 | rad/s | [MTCAN] §6.4.2 |
| `XCDI_EulerAngles` | `0x022` | **6** | roll, pitch, yaw | int16 | 0, 2, 4 | `2^-7` = 0.0078125 | 0.0078 | roll ±180, pitch ±90, yaw ±180 | deg | [MTCAN] §6.3.2 |
| `XCDI_VelocityXYZ` | `0x076` | **6** | velX, velY, velZ | int16 | 0, 2, 4 | `2^-6` = 0.015625 | 0.0156 | ±500 | *(blank in doc)* | [MTCAN] §6.8.3 |
| `XCID_SampleTime` | `0x005` | **4** | SampleTimeUs | uint32 | 0 | 1 | — | — | µs | [MTCAN] §6.1.2 |
| `XCID_GroupCounter` | `0x006` | **2** | GroupCounter | uint16 | 0 | 1 | — | — | — | [MTCAN] §6.1.3 |
| `XCDI_StatusWord` | `0x011` | **4** | StatusWord | uint32 | 0 | — | — | — | bitfield | [MTCAN] §6.2.1 |
| `XCID_Error` | `0x001` | **1** | Error Code | uint8 | 0 | — | — | — | enum | [MTCAN] §6.1.1 |

> **Doc typo, resolved.** In §6.3.2, §6.4.2, §6.4.4, §6.4.5, §6.5.1, §6.7.1 and
> §6.7.2 the Offset column of the *third* field reads `3`. That is wrong: with
> three `int16` fields of `Size 2` and a stated `Total size 6`, the only
> consistent layout is offsets **0, 2, 4**. §6.8.3 (VelocityXYZ) prints the
> correct `0, 2, 4`, which confirms the others are authoring errors, not a real
> packed layout. Use 0/2/4 everywhere.

### 1.2 Other messages defined by [MTCAN] section 6 (not used by MFE26)

| Message | Default CAN ID | DLC | Format | Scaling | Citation |
|---|---|---|---|---|---|
| `XCID_UTC` | `0x007` | 8 | uint8 ×6 + uint16 | TENTHMS = 1e-4 s | §6.1.4 |
| `XCDI_Quaternion` | `0x021` | 8 | int16 ×4 | `1/(2^15-1)` = 1/32767 | §6.3.1 |
| `XCDI_DeltaV` | `0x031` | **7** | int16 ×3 + uint8 exponent | `2^-x`, x transmitted in byte 6 and ODR-dependent | §6.4.1 |
| `XCDI_DeltaQ` | `0x033` | 8 | int16 ×4 | `1/(2^15-1)` | §6.4.3 |
| `XCDI_FreeAcceleration` | `0x035` | 6 | int16 ×3 | `2^-8` m/s² | §6.4.5 |
| `XCDI_MagneticField` | `0x041` | 6 | int16 ×3 | `2^-10` a.u. | §6.5.1 |
| `XCDI_Temperature` | `0x051` | 2 | int16 | `2^-8` °C | §6.6.1 |
| `XCDI_BaroPressure` | `0x052` | 4 | uint32 | `2^-15` Pa | §6.6.2 |
| `XCDI_AccelerationHR` | `0x061` | 6 | int16 ×3 | `2^-8` m/s² | §6.7.1 |
| `XCDI_RateOfTurnHR` | `0x062` | 6 | int16 ×3 | `2^-9` rad/s | §6.7.2 |
| `XCDI_Latitude` (lat+lon) | `0x071` | 8 | int32 ×2 | lat `2^-24` deg, lon `2^-23` deg | §6.8.1 |
| `XCDI_AltitudeEllipsoid` | `0x072` | 4 | uint32 | `2^-15` m | §6.8.2 |

`XCDI_DeltaV` at DLC **7** is the only inertial message that is not 6 bytes, and
the only one whose scaling is not fixed — it varies with the configured output
data rate and is transmitted as a `2^-x` exponent in the last byte
([MTCAN] §6.4.1 lookup table, exponent 8 at 1 Hz through 17 at 400 Hz).

### 1.3 XsCanDataIdentifier codes are *not* CAN IDs

[MTCAN] Table 4 lists `XsCanDataIdentifier` values — 7-bit selector codes used
inside `SetCanOutputConfig`, not arbitration IDs:

```
0x05 XCDI_SampleTime   0x22 XCDI_EulerAngles   0x32 XCDI_RateOfTurn
0x06 XCDI_GroupCounter 0x31 XCDI_DeltaV        0x34 XCDI_Acceleration
0x11 XCDI_StatusWord   0x33 XCDI_DeltaQ        0x35 XCDI_FreeAcceleration
0x21 XCDI_Quaternion   0x75 XCDI_VelocityXYZ   ...
```

For every message the MFE26 uses *except VelocityXYZ*, the default arbitration
ID happens to equal the XCDI code, which is why the two are easy to conflate.
They are different fields and can be decoupled by configuration. See
[ASSUMPTION A3](#a3) for the VelocityXYZ discrepancy.

### 1.4 CAN bus configuration of the MTi

`SetCanConfig`, MID 231 / `0xE7` (the doc misprints the MID as `230 (0xE7)`;
`ReqCanConfig` on the same page is `230 (0xE6)`, and `ReqCanOutputConfig` /
`SetCanOutputConfig` are both `232 (0xE8)`, so the MID/hex pairs in §5.2.1 are
internally inconsistent — see [ASSUMPTION A5](#a5)).

* Payload: `enable flag (bit 8)` + `baud rate code (bits 7:0)`
  ([MTCAN] Table 2).
* **Default baud rate: 250 kbit/s** (code `0`). [MTCAN] Table 3 marks
  `250k (default)`. Supported codes: 1M = 12, 800k = 11, 500k = 10, 250k = 0,
  125k = 1, 100k = 2, 83k3 = 3, 62k5 = 4, 50k = 5, 33k3 = 6, 20k = 7,
  10k = 8, 5k = 9.
* Sample point: the MTi "is internally automatically configured to best as
  possible match a Sample-Point of 70% to 75%" ([MTCAN] §5.2.1).
* CAN output is **disabled by default** and must be enabled; configuration is
  only possible over UART/RS232 in Config State, not over CAN ([MTCAN] §5).
* Per-message **output frequency** is an 11-bit field in `SetCanOutputConfig`.
  [MTCAN] gives no default frequency for any message. See
  [ASSUMPTION A6](#a6).

### 1.5 Invalid-data signalling

[MTCAN] defines **no per-message data-invalid sentinel** for the MTi. There is
no `0x7FFF`-style marker, and an all-`0xFF` payload is an ordinary value
(`-1` count on each axis). Health is signalled out of band by
`XCDI_StatusWord` (`0x011`) and `XCID_Error` (`0x001`,
`CEI_OutputBufferOverflow = 0x01`, "Output Buffer is full, at least one Message
was dropped", and the doc notes this error message can be disabled).

This is the opposite of the Bosch LWS, which *does* use sentinels. A simulator
must not carry LWS sentinel habits onto the MTi bus.

### 1.6 Physical sensor ranges (for plausibility guards)

From [MT600] system specifications:

| Quantity | Standard full range | In CAN units | int16 encoding limit at the given scale |
|---|---|---|---|
| Gyroscope | ±2000 °/s | ±34.9 rad/s (matches [MTCAN] ±35) | ±63.998 rad/s (`0x7FFF` @ `2^-9`) |
| Accelerometer | ±10 g | ±98.1 m/s² (matches [MTCAN] ±100 and its "Note: +/- 10 g") | ±127.996 m/s² (`0x7FFF` @ `2^-8`) |
| Magnetometer | ±8 G | — | — |
| Barometer | 300–1250 hPa | — | — |

**The encoding is wider than the physical range.** A frame can be perfectly
legal on the wire and still exceed the documented range. Any range guard is a
receiver policy decision, not a protocol rule.

## 2. Bosch LWS contract

All from [LWS], a 3-page datasheet with no numbered sections; citations refer to
its named tables.

| Item | Value | Citation |
|---|---|---|
| `LWS_Standard` CAN ID | `0x2B0` | "CAN Message" table |
| `LWS_Standard` DLC | **5** | same table, bytes 0–4 |
| `LWS_Config` CAN ID | `0x7C0` | same table |
| `LWS_Config` DLC | **2** | same table, bytes 0–1 |
| **Byte order** | **little-endian** — "Byte order LSB (Intel)" | "CAN Parameters" table |
| **Bitrate** | **500 kbaud** (stated twice) | "Electrical Data" and "CAN Parameters" |
| **Update rate** | **100 Hz / 10 ms** | "CAN Parameters" |
| Angle range | ±780° | "Application", "Characteristics" |
| Angle resolution | 0.1° | "Characteristics" → see [ASSUMPTION A7](#a7) |
| Speed range | 0 to 1016 °/s (over-range limit ±2500 °/s) | "Characteristics" |
| Speed resolution | 4 °/s | "Characteristics" → see [ASSUMPTION A7](#a7) |

### 2.1 `LWS_Standard` (0x2B0) layout

| Byte | Bits 7:3 | Bit 2 | Bit 1 | Bit 0 |
|---|---|---|---|---|
| 0 | `LWS_ANGLE` low byte | | | |
| 1 | `LWS_ANGLE` high byte | | | |
| 2 | `LWS_SPEED` | | | |
| 3 | Reserved | `TRIM` | `CAL` | `OK` |
| 4 | Reserved | | | |

* `LWS_ANGLE`: **int16, little-endian**, 0.1 °/count, ±7800 counts over the
  ±780° range.
* `LWS_SPEED`: **uint8**, 4 (°/s)/count. 1016 / 4 = **254 counts max**, and the
  invalid sentinel is `0xFF` (255) — so the field cannot be signed. See the
  delta report, finding D-L1.
* Status bits, per the truth table, are only valid in these three combinations:

| TRIM | OK | CAL | ANGLE | SPEED | Byte 3 | State |
|---|---|---|---|---|---|---|
| 1 | 1 | 1 | value | value | `0x07` | calibrated, all information valid |
| 1 | 1 | 0 | `0x7FFF` | value | `0x05` | not calibrated, speed valid |
| 1 | 0 | 0 | `0x7FFF` | `0xFF` | `0x04` | failure mode |
| 0 | 0 | 0 | `0x7FFF` | `0xFF` | `0x00` | failure mode |

"Other combinations for TRIM, OK and CAL are not valid."

### 2.2 `LWS_Config` (0x7C0)

Byte 0 bits 3:0 carry the command code word `CCW`; the rest is reserved.

* `CCW = 3h` — set `LWS_Angle` to 0°.
* `CCW = 5h` — reset the calibration status of the angle.

Zeroing procedure per [LWS] "Installation Notes": reset calibration with
`CCW = 5h` **first**, then start a new calibration with `CCW = 3h`. Zero after
every assembly.

## 3. Which bus, which bitrate (per MFE26-VC firmware)

MCU is an **STM32G4** (`Drivers/STM32G4xx_HAL_Driver`), three classic-CAN FDCAN
peripherals, FDCAN kernel clock = `PCLK1`.

Clock chain (`Core/Src/main.c` `SystemClock_Config`, `Core/Src/fdcan.c`
`HAL_FDCAN_MspInit`): HSI 16 MHz → PLLM `DIV1` → PLLN 10 → VCO 160 MHz →
PLLR `DIV2` → **SYSCLK 80 MHz**; AHB `DIV1`, APB1 `DIV1` → **PCLK1 80 MHz**;
`FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1` on all three instances.

| Peripheral | Prescaler | Seg1 | Seg2 | tq/bit | **Bitrate** | Sample point | Role |
|---|---|---|---|---|---|---|---|
| FDCAN1 | 32 | 2 | 2 | 5 | **500 kbit/s** | **60 %** | pedal/steering + sensors |
| FDCAN2 | 5 | 13 | 2 | 16 | **1 Mbit/s** | 87.5 % | unassigned |
| FDCAN3 | 5 | 13 | 2 | 16 | **1 Mbit/s** | 87.5 % | Ephorus inverters |

`README.md` of MFE26-VC states: "3x FDCAN — CAN1: pedal/steering data, CAN3:
Ephorus inverter control". `VCComms::sendPedalSteeringCAN` transmits ID
`501` = `0x1F5` on `canDriver1`; `BoardManager` binds `ephorusDriver` to
`canDriver3`.

**Therefore the IMU and LWS ride on FDCAN1 at 500 kbit/s.** Caveats:

* The RX path is bus-agnostic. `HAL_FDCAN_RxFifo0Callback` →
  `BoardManager::onCanRx(hfdcan)` → `VCComms::handleRxInterrupt(hfdcan)` drains
  FIFO0 of *whichever* instance fired and tries Ephorus, then accel, gyro, vel.
  Nothing in the code restricts the IMU to a bus. The FDCAN1 assignment is an
  inference from README + the LWS's hard-wired 500 kbaud, not a code fact.
* **FDCAN1's 60 % sample point is out of the usual 75–87.5 % band.** The MTi
  targets 70–75 % ([MTCAN] §5.2.1) and Bosch does not publish theirs. This is a
  firmware bit-timing defect worth fixing independently of this contract
  (`NominalTimeSeg1 = 13, NominalTimeSeg2 = 2, NominalPrescaler = 10` would give
  500 kbit/s at 87.5 %).
* The MTi's **250 kbit/s default does not match any configured bus.** The
  MTi-680G must be reconfigured to baud code **10 (0x0A) = 500 kbit/s** over
  UART/RS232 with MT Manager before it will communicate at all.

### 3.1 The RX acceptance filter rejects every sensor ID

`Core/Src/main.c:105` → `bm = BoardManager_create(899, 1024);`

Those are decimal: **899 = `0x383`**, **1024 = `0x400`**. They are passed
unchanged to all three `CANDriver` instances, and `CANDriver::initialize()`
installs:

```
sFilterConfig.IdType      = FDCAN_STANDARD_ID;
sFilterConfig.FilterType  = FDCAN_FILTER_RANGE;
sFilterConfig.FilterID1   = 0x383;   // low
sFilterConfig.FilterID2   = 0x400;   // high
HAL_FDCAN_ConfigGlobalFilter(..., FDCAN_REJECT, FDCAN_REJECT, ...);
```

Accepted range is `0x383 … 0x400` — exactly the Ephorus inverter status IDs
(`0x383/0x385/0x393/0x395/0x3A3/0x3A5/0x3B3/0x3B5`) plus system status `0x400`.
Everything else is rejected in hardware.

| ID | Sensor | Inside `0x383…0x400`? |
|---|---|---|
| `0x022` Euler | MTi | **no** |
| `0x032` RateOfTurn | MTi | **no** |
| `0x034` Acceleration | MTi | **no** |
| `0x076` VelocityXYZ | MTi | **no** |
| `0x2B0` LWS_Standard | Bosch | **no** |

**As shipped, the VCU cannot receive any IMU or LWS frame on any bus.** This is
the single most important interop fact in this document. See delta report
finding D-0.

## Assumptions

Values the documents do **not** pin down. Each is an open item, not a fact.

<a id="a1"></a>
### A1 — MTi CAN payload byte order is big-endian *(high confidence, not stated in [MTCAN])*

[MTCAN] never states the byte order of CAN output payloads. The only endianness
sentence in the whole document is about the *XBus configuration* message:
"NOTE: If this message is sent without using XDA, make sure to serialize to
BigEndian prior to sending the message" (§5.2.1, `SetCanOutputConfig`).

Supporting evidence for big-endian on the CAN payloads:

* [MTLL] §5.1.1 "Big endian output format": *"All binary data communication is
  done in big-endian format."*
* [MTLL] elsewhere: "The resulting 32-bit integer value is transmitted in
  big-endian order (MSB first)".
* The MFE26-VC driver independently assumes it (`// DBC @0 (Motorola)`).

**Resolution required:** capture a real MTi-680G frame with a known non-symmetric
value, or open the Xsens-supplied DBC in MT Software Suite. Golden vector
`edge_little_endian_confusion_probe` exists for exactly this measurement.

<a id="a2"></a>
### A2 — MTi-680G supports the `670` message set

MT1604P Rev A (Sept 2019) predates the MTi-680G (added to the datasheet in
Jun 2020). The 680G is not named anywhere in [MTCAN]. Mapping it onto the `670`
GNSS/INS column is an inference from product class. This matters only for
`XCDI_VelocityXYZ`, `XCDI_Latitude` and `XCDI_AltitudeEllipsoid`, which are
`670`-only. Confirm against a 680G-era revision of MT1604P or against MT Manager.

<a id="a3"></a>
### A3 — `XCDI_VelocityXYZ` CAN ID is `0x076`, not `0x075`

[MTCAN] contradicts itself. Table 4 lists `0x75 XCDI_VelocityXYZ`; §6.8.3's
heading reads `XCDI_VelocityXYZ (0x076)`. The same section 6.8 has two more
Table-4-vs-heading conflicts (`XCDI_AltitudeEllipsoid` is `0x73` in Table 4 but
`0x072` in §6.8.2; §6.8.1 folds `XCDI_Latitude 0x71` and `XCDI_Longitude 0x72`
into one `0x071` message), so section 6.8 is the less reliable half — yet
section 6 headings are the ones that carry the CAN identifiers everywhere else.

MFE26-VC uses `0x076`. **This document adopts `0x076` to match firmware**, but it
is unverified. If the sensor actually emits `0x075`, both the simulator and the
VCU are wrong together, and a HIL run would still pass. Verify on hardware.

<a id="a4"></a>
### A4 — `XCDI_VelocityXYZ` unit is m/s

[MTCAN] §6.8.3 leaves the Unit column as a dash for all three velocity fields.
m/s is inferred from the XBus equivalent `XDI_VelocityXYZ` and from `±500` being
a sensible m/s range. Not stated.

<a id="a5"></a>
### A5 — `SetCanConfig` MID

[MTCAN] §5.2.1 prints `SetCanConfig | MID 230 (0xE7)`. 230 decimal is `0xE6`,
which is what the same page assigns to `ReqCanConfig`. Convention across the MT
protocol is request = even MID, set = MID + 1, so `SetCanConfig` is almost
certainly **231 (`0xE7`)**. Irrelevant to the HIL simulator (which never
configures a real MTi) but relevant to anyone bringing up the sensor.

<a id="a6"></a>
### A6 — Default output rates

[MTCAN] specifies an 11-bit per-message output-frequency field and gives **no
default** for any message. The DeltaV table implies supported ODRs of
1, 2, 4, 5, 8, 10, 16, 20, 25, 40, 50, 80, 100, 200, 400 Hz. The HIL scheduler's
IMU rate is therefore a **simulator configuration choice**, not a protocol fact,
and must be documented as such. Whatever rate the real MTi is programmed to is
what the HIL must mirror; record it when the sensor is configured.

<a id="a7"></a>
### A7 — LWS angle/speed LSB scaling

[LWS] gives `0.1°` and `4 °/s` under **"Absolute physical resolution"**, not as
an explicit "scaling" or "LSB" figure, and never writes an encoding formula.
0.1 °/count is corroborated arithmetically: ±780° / 0.1 = ±7800 counts, which
fits int16 and leaves `0x7FFF` free as the invalid sentinel. 4 (°/s)/count is
corroborated: 1016 / 4 = 254 counts, which fits uint8 and leaves `0xFF` free as
the sentinel. Both are consistent to the point of near-certainty, but neither is
stated as a scaling factor.

<a id="a8"></a>
### A8 — LWS byte 4 and the reserved bits

[LWS] marks byte 4 and byte 3 bits 7:3 "Reserved" without specifying a fill
value. The simulator transmits zeros. A receiver must mask rather than compare
the whole byte.

<a id="a9"></a>
### A9 — Sign and axis conventions

Neither [MTCAN] nor [LWS] is used here to establish vehicle-frame sign
conventions (which way is positive yaw, which sensor axis is vehicle-longitudinal,
LWS positive = left or right turn). [MT600] Figure 8 defines the MTi-680G sensor
coordinate system; the mounting orientation on MFE26 is a vehicle-integration
fact recorded nowhere in either repo. **This contract covers wire format only.**
Sign conventions must be settled separately before any closed-loop HIL result is
meaningful.

## Golden vectors

`references/sensors/golden_vectors/mti680/` and `.../lws/`.

* `mti680_golden_vectors.json` — 49 well-formed vectors plus 11 invalid/edge
  cases (the edge cases are payload-level and have no "physical value in").
* `mti680GoldenVectors.m` — 46 of those well-formed vectors as a MATLAB struct
  array. Payload bytes were cross-checked byte-for-byte against the JSON
  (45 automatically matched by name; `error_buffer_overflow` is the single-byte
  `0x01` case). Verified to load and self-check in MATLAB R2024b.
* `lws_golden_vectors.json` — 12 well-formed vectors plus 8 invalid/edge cases.
* `derive_*.py` — the derivation scripts, kept so the arithmetic is auditable.

They were hand-derived from [MTCAN] and [LWS] tables only. Per the test-oracle
separation rule in `mti680_lws_integration_plan.md` slice 1, they were **not**
produced by running or transcribing either the VCU decoder or the HIL encoder;
both of those are units under test. Do not regenerate them from either side.
