# IMU / LWS CAN contract — three-way delta report

Date: 2026-08-16. Branch: `imu-can-contract`.

Compares three sources that all claim to describe the same wire format:

| # | Source | What it is |
|---|---|---|
| **DOC** | Xsens *MT CAN Protocol Documentation* MT1604P Rev A (16 Sept 2019) + Bosch LWS F02U.V02.894-01 datasheet | the authority |
| **VCU** | `McGillFormulaElectric/MFE26-VC` branch `controls` — `Drivers/Device_Drivers/{Inc,Src}/MTi680G_driver.*`, `LWSSteering.*`, `Core/Src/vcComms.cpp`, `Core/Src/main.c`, `Core/Src/fdcan.c`, `Drivers/HAL_Drivers/Src/CANDriver.cpp` | what the real firmware decodes |
| **SIM** | HIL `master` — `inverter_hil/imu/imuProtocol.m`, `packMti680Frame.m`, `packMti680Payload.m`, `inverter_hil/steering-sensor/lwsProtocol.m`, `packLwsPayload.m` | what the simulator transmits |

Full verified contract and citations: [`mti680_can_contract.md`](mti680_can_contract.md).

---

## Executive answer

> **Would the simulator, as it stands, be decoded correctly by the real VCU?**
>
> **No.** Two independent blockers, either one fatal:
>
> 1. **D-0** — the VCU's FDCAN acceptance filter admits only IDs `0x383…0x400`.
>    Every IMU ID (`0x022`, `0x032`, `0x034`, `0x076`) and the LWS ID (`0x2B0`)
>    is rejected in hardware, on every bus, before any driver runs. Zero frames
>    reach `MTi680GDriver`. (Source-level finding — branch `controls` does not
>    compile as-is, so confirm against the flashed binary; see the caveat under
>    D-0.)
> 2. **D-1** — even with the filter opened, the simulator emits no `0x076`
>    velocity frame, which the VCU decodes and which `CONTROLS.md` marks as a
>    live control input (`vy`, and `vehicle_speed` via `use_imu_vel_x`); and it
>    emits `0x022` Euler frames, which the VCU never listens for at all.
>
> Of the payload encoding itself, the news is good: **acceleration `0x034` and
> rate-of-turn `0x032` are byte-identical across all three sources** — same ID,
> same DLC 6, same big-endian int16 layout at offsets 0/2/4, same `2^-8` and
> `2^-9` scale factors. If D-0 and D-1 are fixed, those two messages will decode
> correctly.

Bottom line: the simulator's *encoding* is right where it overlaps; its
*message set* is wrong at both ends, and the VCU's *filter* is wrong.

---

## Part 1 — MTi message-set delta

Legend: ✅ present and correct, ⚠️ present but wrong, ❌ absent.

| Message | ID | DOC | VCU | SIM | Verdict |
|---|---|---|---|---|---|
| `XCDI_Acceleration` | `0x034` | ✅ §6.4.4 | ✅ `accelCANRx` | ✅ `p.acceleration` | agreed |
| `XCDI_RateOfTurn` | `0x032` | ✅ §6.4.2 | ✅ `gyroCANRx` | ✅ `p.rateOfTurn` | agreed |
| `XCDI_VelocityXYZ` | `0x076` | ✅ §6.8.3 (ID disputed, [A3]) | ✅ `velCANRx` | ❌ **missing** | **SIM wrong — D-1a** |
| `XCDI_EulerAngles` | `0x022` | ✅ §6.3.2 | ❌ **not decoded** | ✅ `p.eulerAngles` | **SIM emits dead traffic — D-1b** |
| `XCID_GroupCounter` | `0x006` | ✅ §6.1.3 | ❌ | ⚠️ declared, never packed | **D-2** |
| `XCID_SampleTime` | `0x005` | ✅ §6.1.2 | ❌ | ⚠️ declared, never packed | **D-2** |
| `XCDI_StatusWord` | `0x011` | ✅ §6.2.1 | ❌ | ❌ | **D-3** (health signalling absent everywhere) |
| `XCID_Error` | `0x001` | ✅ §6.1.1 | ❌ | ❌ | **D-3** |

### D-1a — SIM does not emit `XCDI_VelocityXYZ` (`0x076`). **SIM is wrong.**

`MTi680G_driver.hpp` defines `MTI680G_ID_VELOCITY_RAW 0x076`,
`MTI680G_VEL_SCALING 0.015625f` (= `2^-6`), `MTI680G_VEL_MAX_MPS 500.0f`, and
`velCANRx` writes `imu_data.v_x / v_y / v_z`. `vcComms.cpp:330` routes it.
MFE26-VC `CONTROLS.md` lists `vy` ("Lateral vehicle velocity", live signal) and
gates `use_imu_vel_x` / `use_imu_vel_y` on "a configured, fresh, unit-checked
MTi longitudinal/lateral-velocity signal". Without `0x076` on the wire the
simulator can never exercise that path.

Every value the VCU uses matches DOC §6.8.3 exactly (`2^-6`, ±500, int16 ×3,
total size 6, offsets 0/2/4). Adding it to SIM is a pure gap-fill, not a fix.

Caveat: DOC contradicts itself on this ID — Table 4 says `0x75`, §6.8.3 says
`0x076`. VCU and this contract both adopt `0x076`. **If the real sensor emits
`0x075`, SIM and VCU will be wrong together and HIL will not catch it.** Verify
on hardware. ([A3])

### D-1b — SIM emits `XCDI_EulerAngles` (`0x022`) that the VCU never reads. **Neither is "wrong", but the pairing is.**

DOC §6.3.2 is correct and SIM's encoding of it (`0x022`, DLC 6, `2^-7` deg,
big-endian int16 ×3) matches DOC field-for-field — this is the one place SIM got
something right that nobody else has. But `MTi680G_driver.hpp` has no Euler ID,
no Euler scale, and no `eulerCANRx`; `vcComms::handleRxInterrupt` has no fourth
branch. Every `0x022` frame lands in the `else` and increments
`canRxUnknownIdCount`.

So SIM currently generates bus load and a decoder-side "unknown ID" counter
increment that the HIL will silently absorb. Either:

* keep `0x022` in the contract but mark it **not consumed by MFE26 firmware**
  and default its scheduler rate to 0 (recommended — the contract stays complete
  and the traffic stops), or
* add a Euler decoder to the VCU if the control model ever needs roll/pitch/yaw.

Do **not** silently drop `0x022` from `imuProtocol.m`: it is a real MTi message
and its golden vectors are already written.

### D-2 — `0x006` GroupCounter and `0x005` SampleTime are declared but dead. **SIM half-wrong, VCU absent.**

`imuProtocol.m` declares both; `packMti680Frame` rejects them
(`if ~isfield(contract, kind)` passes, then `values` must be a 3-vector — a
scalar counter errors with `mti680:InvalidValues`), and `packMti680Payload`
explicitly `error`s on anything but `acceleration`/`rateofturn`. So they are
contract entries with no encoder.

Both are correct per DOC (`0x006` uint16 DLC 2 §6.1.3; `0x005` uint32 DLC 4
§6.1.2) — but note SIM declares only `id` and `dlc` for them and never says they
are **unsigned**, while every other entry is stamped `'signed', true`. A future
implementer reading the struct would reasonably assume signed. **Fix: give them
explicit `signed=false`.**

The VCU decodes neither. Since `imu_data.valid` is a latch that is never cleared
(see D-8), a group counter or sample-time timeout is the natural staleness
mechanism and neither side has one.

### D-3 — no health/status path anywhere. **All three "agree" by omission; DOC is the only one that provides for it.**

DOC provides `XCDI_StatusWord` (`0x011`) and `XCID_Error` (`0x001`) as the
*only* invalidity signalling on the MTi bus (there is no per-message sentinel —
see contract §1.5). Neither VCU nor SIM implements either. A HIL that cannot
inject "MTi reports itself unhealthy" cannot test the VCU's response to it,
because the VCU has no response to test.

Recommendation: add `statusWord` and `error` to the SIM contract with `signed=false`
so the capability exists; wiring them into the scheduler can wait.

---

## Part 2 — MTi field-level delta (the messages that overlap)

| Property | DOC | VCU | SIM | Verdict |
|---|---|---|---|---|
| Accel ID | `0x034` §6.4.4 | `MTI680G_ID_ACCEL_RAW 0x034u` | `hex2dec('034')` | **all agree** |
| Accel DLC | 6 ("Total size 6") | `if (len < 6u) return false` | `uint8(6)` | **all agree** |
| Accel scale | `2^-8` | `0.00390625f  // 1/256` | `2^-8` | **all agree**, and `2^-8 == 1/256 == 0.00390625` exactly |
| Accel unit | m/s² | m/s² | `'m/s^2'` | agree |
| Accel field order | accX@0, accY@2, accZ@4 | `data[0..1], [2..3], [4..5]` | bytes 1-2, 3-4, 5-6 | agree |
| Gyro ID | `0x032` §6.4.2 | `0x032u` | `hex2dec('032')` | **all agree** |
| Gyro scale | `2^-9` | `0.001953125f //scales by 2^-9` | `2^-9` | **all agree** |
| Gyro unit | rad/s | rad/s | `'rad/s'` | agree |
| Signedness | int16, two's complement | `(int16_t)(...)` | `'signed', true` | **all agree** |
| **Byte order** | **not stated** ([A1]) | big-endian: `data[0]<<8 | data[1]` | `'big'`; `payload(k)=bitshift(raw,-8)` | VCU and SIM agree; **DOC is silent — this is the top open risk** |
| Additive offset | none | none | none | agree |
| Euler scale | `2^-7` deg §6.3.2 | n/a | `2^-7` | SIM matches DOC |
| Velocity scale | `2^-6` §6.8.3 | `0.015625f //sclaes by 2^-6` | absent | VCU matches DOC |

### D-4 — endianness is agreed but **unproven**. Nobody is wrong; everybody is guessing the same way.

The task asked specifically to confirm this. Findings:

* **DOC does not state it.** MT1604P's only endianness sentence
  (§5.2.1, `SetCanOutputConfig`: "make sure to serialize to BigEndian prior to
  sending the message") is about the XBus *configuration* message travelling
  over UART, not about CAN output payloads. Section 6 never mentions byte order.
* **Supporting evidence is strong but indirect:** MT Low Level Communication
  Protocol Documentation §5.1.1, "Big endian output format — All binary data
  communication is done in big-endian format."
* **VCU assumes big-endian** and says so: `// DBC @0 (Motorola) => big-endian
  int16 at byte offsets 0,2,4` in all three `*CANRx` functions.
* **SIM assumes big-endian**: `p.byteOrder = 'big'`, and `packMti680Frame` packs
  MSB then LSB. `packMti680Payload` reaches the same result a different way
  (`typecast` then `raw([2 1])` to reverse little-endian host order) — two
  implementations, one answer, which at least rules out a SIM-internal
  inconsistency.

**Verdict: big-endian is almost certainly right, but the HIL currently proves
nothing about it** — SIM and VCU share the same assumption, so a HIL pass is not
evidence. Golden vector `edge_little_endian_confusion_probe`
(`0x034`, `CF 09 00 00 00 00`) exists to settle it against real hardware: a
big-endian reader sees −48.996 m/s², a little-endian reader sees +9.809 m/s².
Capture one real MTi-680G acceleration frame at a known non-symmetric tilt, or
open the Xsens DBC, and close [A1].

### D-5 — accel scale `2^-8` vs "1/256". **Not a discrepancy. Confirmed on all three sides.**

The task flagged this as a possible conflict. It is not one:

* DOC §6.4.4 Scaling column reads `2-8` (i.e. `2^-8`), Resolution column
  `0.0039`, Range `±100 m/s²`, "Note: +/- 10 g".
* VCU: `#define MTI680G_ACC_LSB_MPS2 0.00390625f  // 1/256`.
* SIM: `2^-8`.

`2^-8 = 1/256 = 0.00390625` exactly, and all three are binary-exact in float —
no rounding divergence is possible. The DOC's `0.0039` is a display rounding of
the same number, not a third value. Case closed.

### D-6 — range guards: DOC's Range column is narrower than the int16 encoding. **VCU behaviour is a policy choice SIM does not model.**

DOC ranges are ±100 m/s² and ±35 rad/s; [MT600] confirms ±10 g and ±2000 °/s
physical full-scale. But int16 at `2^-8` reaches ±127.996 m/s² and at `2^-9`
reaches ±63.998 rad/s. The wire can carry values the sensor cannot produce.

The VCU turns this into a hard rule and **drops the entire frame** if *any* axis
is out of range:

```cpp
if (ax > MTI680G_ACC_MAX_MPS2 || ax < -MTI680G_ACC_MAX_MPS2 || ... ) return false;
```

with `MTI680G_ACC_MAX_MPS2 = 100.0f`, `MTI680G_GYRO_MAX_RADPS = 35.0f`,
`MTI680G_VEL_MAX_MPS = 500.0f`. All three match DOC's Range columns — **VCU is
correct here.** Note the guard is exclusive (`>`), so exactly ±100.0 is accepted;
`acc_doc_range_max` (`64 00 64 00 64 00`) decodes to exactly 100.0 and passes.

SIM only clamps to int16 (`packMti680Frame`: `error` if `counts < -32768 |
counts > 32767`). It will happily encode 120 m/s², which is legal on the wire and
which the VCU silently discards. Golden vectors `acc_int16_max`,
`acc_doc_range_min`, `rot_int16_max`, `edge_accel_beyond_doc_range` cover this
boundary precisely.

**Recommendation:** SIM should carry the documented ranges as contract data
(`p.acceleration.rangeMax = 100` etc.) and default to clamping there, with an
explicit opt-in to emit out-of-range frames as a fault-injection case. That makes
"VCU drops the frame" a testable behaviour rather than an accident.

### D-7 — DOC's Offset column is typo'd; both implementations already ignore it. **DOC is wrong.**

DOC §6.3.2, §6.4.2, §6.4.4, §6.4.5, §6.5.1, §6.7.1, §6.7.2 all print the third
field's Offset as `3` where it must be `4` (three `Size 2` fields, `Total size 6`).
§6.8.3 prints the correct `0, 2, 4`. VCU reads `data[4..5]` and SIM writes bytes
5-6 — both correct. Recorded so nobody "fixes" a working implementation to match
a typo.

### D-8 — `imu_data.valid` is a latch. **VCU defect, out of scope for the contract but affects HIL interpretation.**

`accelCANRx`, `gyroCANRx` and `velCANRx` each set `imu_data.valid = true` and
nothing ever sets it false. One acceptable accel frame at power-on marks the
whole struct valid forever, including `Gyrx/Gyry/Gyrz` and `v_x/v_y/v_z` that may
never have been received. A HIL dropout test will therefore **pass while proving
nothing**: cutting the IMU stream leaves `valid == true` and stale values in
place. Fix on the VCU side (per-message timestamp + timeout, or per-group valid
flags) before any IMU-dropout HIL result is quoted.

Related: `clampI32ToI16` at the top of `MTi680G_driver.cpp` is dead code —
declared `static inline`, never called. Harmless, but it suggests a saturation
path that was intended and never wired.

Also: each `*CANRx` does a blocking `HAL_UART_Transmit(&huart3, ..., 5)` **inside
the CAN RX interrupt**, and `vcComms.cpp` does a second one per frame. At 500
kbit/s and a few hundred Hz of IMU traffic this will not keep up and will drop
frames in FIFO0. Strip the debug UART before any timing-sensitive HIL run.

---

## Part 3 — bus, bitrate and the filter

### D-0 — **the VCU's CAN acceptance filter rejects every sensor ID. VCU is wrong. This is the blocker.**

`Core/Src/main.c:105`:

```c
bm = BoardManager_create(899, 1024);
```

Decimal — `899 = 0x383`, `1024 = 0x400`. `BoardManager` passes the same pair to
`canDriver1`, `canDriver2` and `canDriver3`, and `CANDriver::initialize()`
installs a single `FDCAN_FILTER_RANGE` `0x383…0x400` into FIFO0 with
`HAL_FDCAN_ConfigGlobalFilter(..., FDCAN_REJECT, FDCAN_REJECT, ...)` — non-matching
standard **and** extended frames are dropped by hardware.

That range is exactly the Ephorus inverter status set (`0x383, 0x385, 0x393,
0x395, 0x3A3, 0x3A5, 0x3B3, 0x3B5`) plus system status `0x400`. It was sized for
the inverters and never widened when the IMU driver landed.

| ID | Sensor | Admitted? |
|---|---|---|
| `0x022` | MTi Euler | **no** |
| `0x032` | MTi RateOfTurn | **no** |
| `0x034` | MTi Acceleration | **no** |
| `0x076` | MTi VelocityXYZ | **no** |
| `0x2B0` | Bosch LWS | **no** |

`accelCANRx` / `gyroCANRx` / `velCANRx` are unreachable as built. MFE26-VC's own
`TODO.md` says *"IMU driver untested — Driver is complete and sensor is on the
car, but `accelCANRx` is commented out in the CAN RX handler"* — that comment is
now stale (the calls are live at `vcComms.cpp:324-332`) but the conclusion still
holds for a different reason: the filter, not the handler.

**Recommended VCU fix** (firmware side, not this repo — file it against MFE26-VC):
add filter entries for the sensor IDs rather than widening the range, e.g. a
second `FDCAN_FILTER_RANGE 0x022…0x076` at `FilterIndex 1` with
`StdFiltersNbr = 2` (or `StdFiltersNbr = 3` with two `FDCAN_FILTER_DUAL` entries
if `0x2B0` is added for the LWS). Widening `FilterID1` to `0x022` instead would
admit the pedal/steering `0x1F5` echo and everything else on the bus into the
same FIFO0 drain loop.

**Until that lands, no HIL IMU result on a real VCU means anything.** A Speedgoat
transmitting perfect frames will produce zero decoder activity and zero error
counters — the frames never reach software.

> **Caveat on "as shipped".** Branch `controls` does not currently compile:
> `VCComms::update_ctrls_inputs()` (`Core/Src/vcComms.cpp:343-371`) is a stub of
> the form `controls_inputs->vehicle_speed = /* live vehicle speed */;` — an
> empty initialiser, not inside any `#if 0`. So the analysis above describes the
> filter *as configured in source*, and whatever binary is on the car was built
> from a different tree. Confirm `BoardManager_create(899, 1024)` against the
> flashed firmware before treating D-0 as the on-car behaviour. The IMU sign,
> unit and scale conclusions are independent of this.

### D-9 — bitrate. **SIM has no opinion; DOC and VCU disagree with each other.**

Per firmware (`main.c` `SystemClock_Config` + `fdcan.c`):
SYSCLK 80 MHz → PCLK1 80 MHz → FDCAN kernel clock 80 MHz.

| Bus | Prescaler / Seg1 / Seg2 | Bitrate | Sample point | Role (per MFE26-VC `README.md`) |
|---|---|---|---|---|
| FDCAN1 | 32 / 2 / 2 | **500 kbit/s** | **60 %** | pedal/steering + sensors |
| FDCAN2 | 5 / 13 / 2 | 1 Mbit/s | 87.5 % | unassigned |
| FDCAN3 | 5 / 13 / 2 | 1 Mbit/s | 87.5 % | Ephorus inverters |

* **IMU and LWS ride FDCAN1 at 500 kbit/s.** The LWS is hard-wired to 500 kbaud
  (Bosch datasheet, stated twice) so it can only be FDCAN1; `README.md` assigns
  CAN1 to "pedal/steering data"; `sendPedalSteeringCAN` transmits `0x1F5` on
  `canDriver1`. Note the RX path itself is bus-agnostic — `handleRxInterrupt`
  runs the same Ephorus→accel→gyro→vel chain on whichever instance fires — so
  this is inference from README plus the LWS constraint, not a hard code fact.
* **The MTi's default 250 kbit/s matches nothing.** MT1604P Table 3 marks
  `250k (default)`, and CAN output is disabled by default. The MTi-680G must be
  configured over UART/RS232 (MT Manager or `SetCanConfig`) to **baud code 10
  (`0x0A`) = 500 kbit/s** before it will talk to this VCU at all.
* **FDCAN1's 60 % sample point is out of spec practice** (2 tq before, 2 after,
  in a 5 tq bit). MT1604P §5.2.1 says the MTi targets 70–75 %. Mismatched sample
  points cause marginal-cable bit errors that look like random frame loss.
  `NominalPrescaler = 10, Seg1 = 13, Seg2 = 2` gives 500 kbit/s at 87.5 % and
  should replace it. **File against MFE26-VC.** The HIL must be set to
  500 kbit/s regardless.

### D-10 — no DBC exists. **All three sources are prose; nothing is machine-checked.**

Searched `McGillFormulaElectric/MFE26-VC` branch `controls` for `*.dbc`, `*.sym`,
`*.arxml`: **none**. The `// DBC @0 (Motorola)` comments in `MTi680G_driver.cpp`
refer to a DBC that is not in the repository. Every ID/scale/endianness fact in
the firmware is a hand-typed constant with no shared source of truth.

The golden vectors in `references/sensors/golden_vectors/` are now the closest
thing this project has to one. Consider generating a DBC from the verified
contract and vendoring it in both repos.

---

## Part 4 — Bosch LWS delta

| Property | DOC | VCU (`LWSSteering.cpp`) | SIM (`lwsProtocol.m`, `packLwsPayload.m`) | Verdict |
|---|---|---|---|---|
| Standard ID | `0x2B0` | `LWS_Standard_ID 0x2B0` | `hex2dec('2B0')` | agree |
| Standard DLC | 5 | `if (message.getLength() != 5) return false` | `zeros(1,5)` | agree |
| Config ID / DLC | `0x7C0` / 2 | `LWS_Config_ID 0x7C0`, `setMessage(pBuffer, 2)` | `0x7C0` / 2 | agree |
| Byte order | **little-endian**, explicitly ("Byte order LSB (Intel)") | `pBuffer[1]<<8 \| pBuffer[0]` = little-endian | `typecast` on little-endian host, comment "Bosch LWS angle is little-endian" | **all agree, and DOC actually says so** |
| Angle format | int16, 0.1 °/count ([A7]) | `int16_t`, no scaling applied (raw counts stored) | `int16(angle/0.1)` | agree on wire; see D-L2 |
| **Speed format** | **uint8**, 4 (°/s)/count, `0xFF` = invalid | **`int8_t`** — `speed = (int8_t)pBuffer[2]` | `uint8(speedRaw)` — correct | **VCU wrong — D-L1** |
| Status bits | byte 3: bit2 TRIM, bit1 CAL, bit0 OK | `&0x04`, `&0x02`, `&0x01` | `trimMask 4`, `calMask 2`, `okMask 1` | agree |
| Validity policy | only TRIM=1 OK=1 CAL=1 gives valid angle+speed | requires `trim && cal && ok`, else no update | masks declared, policy not encoded | agree; SIM should encode the truth table |
| Angle sentinel | `0x7FFF` when not calibrated / failed | never checked (the status gate makes it unreachable) | **absent** | **D-L3** |
| Speed sentinel | `0xFF` when failed | never checked | **absent** | **D-L3** |
| Update rate | 100 Hz / 10 ms | comment says "should be called at 100 Hz" | `p.updatePeriodS = 0.010` | agree |
| Bitrate | 500 kbaud | FDCAN1 = 500 kbit/s | n/a | agree |
| Range | ±780°, 0–1016 °/s | not range-checked | `error` outside range | SIM stricter; fine |

### D-L1 — `LWS_SPEED` is unsigned; the VCU casts it to `int8_t`. **VCU is wrong.**

```cpp
speed = (int8_t)pBuffer[2];   // LWSSteering.cpp:32
volatile int8_t speed = 0;    // LWSSteering.hpp:24
int8_t getSpeed() const;
```

The Bosch datasheet gives speed as `0 to 1016 °/s` — no negative values — with
absolute resolution 4 °/s, so 1016/4 = **254 counts**, and `0xFF` (255) is the
failure sentinel. The field is unambiguously **uint8 spanning 0…254**.

Consequences of the signed cast:

| True speed | Wire byte | `int8_t` reads | Reported |
|---|---|---|---|
| 508 °/s | `0x7F` | 127 | 508 °/s ✅ last correct value |
| 512 °/s | `0x80` | −128 | −512 °/s ❌ |
| 1016 °/s | `0xFE` | −2 | −8 °/s ❌ |
| failure sentinel | `0xFF` | −1 | −4 °/s ❌ (and unrecognised as a sentinel) |

Everything above 508 °/s — which is only half the sensor's range, and reachable
in a genuine steering input — is reported as a large negative speed.
`getSpeed()` returns `int8_t`, so the bug is in the public API, not just the
storage.

**Fix (MFE26-VC):** change the member and getter to `uint8_t`, keep the raw count,
and expose degrees/s as `count * 4.0f` with `0xFF` treated as invalid.

SIM already does this correctly (`speedCount = uint8(speedRaw)`), so the golden
vectors `lws_speed_508dps` (`00 00 7F 07 00`), `lws_speed_512dps`
(`00 00 80 07 00`) and `lws_speed_max_1016dps` (`00 00 FE 07 00`) will expose the
firmware bug on a real HIL run the moment the filter (D-0) is opened.

### D-L2 — angle scaling is applied nowhere in the VCU. **Not wrong, but undocumented.**

`getAngle()` returns raw int16 counts. `CONTROLS.md` expects `SWA` as a
steering-wheel angle. The `× 0.1 °/count` conversion, plus the `0.225`
steering-wheel-to-road-wheel ratio, live in neither `LWSSteering` nor
`update_ctrls_inputs` (which is still a stub with `/* steering-wheel angle */`
placeholders that do not compile). Record 0.1 °/count in the firmware when that
stub is filled, and note it is a datasheet "resolution" figure, not a stated LSB
([A7]).

### D-L3 — nobody models the sentinels. **SIM gap.**

`lwsProtocol.m` has no `0x7FFF` / `0xFF` sentinel constants and
`packLwsPayload` cannot produce them (`angleDeg` is range-checked to ±780° first,
so `0x7FFF` = 3276.7° is unreachable). The simulator therefore cannot generate
"sensor uncalibrated" or "sensor in failure mode" — the only two abnormal states
the sensor can actually report. Add them as explicit sentinel constants and a
status-driven encode path; golden vectors `lws_uncalibrated`,
`lws_failure_trim_only`, `lws_failure_all_clear` define the exact bytes.

### D-L4 — the LWS is not instantiated in firmware at all. **VCU gap.**

Grepping all of `Core/` for `LWS` returns nothing. `BoardManager` constructs
`ephorusDriver` and `imu` but no `LWSSteering`; `handleRxInterrupt` has no
`0x2B0` branch; `updateValues()` and `calibrate()` have no callers. The class
compiles and is dead. MFE26-VC `TODO.md` confirms: *"Steering sensor driver
untested — Sensor is not yet on the car."*

Also, already logged in their TODO and confirmed here:
`LWSSteering::calibrate()` queues two messages but calls `transmitMessage()`
once, and `transmitMessage()` pops exactly one entry — so `CCW = 3h` (zero the
angle) is queued and never sent. The datasheet's zeroing procedure requires both,
in order.

---

## Part 5 — recommended diff to the HIL simulator

The concurrent `virtual-vcu` port had **not** landed at the time of writing
(`git log --oneline virtual-vcu` HEAD = `2f4567f`, all XCP/A2L work, no
`inverter_hil/imu/**`). Per instructions, `imuProtocol.m` and `protocol.md` were
**not** edited. The exact intended change is below; apply it after the port lands.

### 5.1 `inverter_hil/imu/imuProtocol.m`

```diff
 function p = imuProtocol()
 %PROTOCOL Independent MTi-680G CAN output contract.
-%   Contract source: Xsens MT CAN Protocol Documentation, MT1604P,
-%   revision 2020.A. This file is deliberately independent of VCU source.
+%   Contract source: Xsens MT CAN Protocol Documentation, document MT1604P,
+%   Revision A, 16 Sept 2019. This file is deliberately independent of VCU
+%   source. Verified against the primary document and against the MFE26-VC
+%   firmware decoder; see references/sensors/mti680_can_contract.md and
+%   references/sensors/imu_contract_delta.md.
 
-p.source = 'Xsens MT CAN Protocol Documentation MT1604P 2020.A';
-p.acceleration = message(uint32(hex2dec('034')), uint8(6), 2^-8, 'm/s^2');
-p.rateOfTurn = message(uint32(hex2dec('032')), uint8(6), 2^-9, 'rad/s');
-p.eulerAngles = message(uint32(hex2dec('022')), uint8(6), 2^-7, 'deg');
-p.groupCounter = struct('id', uint32(hex2dec('006')), 'dlc', uint8(2));
-p.sampleTime = struct('id', uint32(hex2dec('005')), 'dlc', uint8(4));
+p.source = ['Xsens MT CAN Protocol Documentation, document MT1604P, ' ...
+    'Revision A, 16 Sept 2019'];
+
+% Vector messages: three int16 fields at byte offsets 0, 2, 4 (MT1604P
+% section 6; the Offset column misprints the third field as 3 -- Total size 6
+% makes 4 the only consistent value).
+% rangeMax is the documented physical Range column, which is NARROWER than the
+% int16 encoding limit. The MFE26 VCU drops any frame with an axis outside it.
+p.acceleration = message(uint32(hex2dec('034')), uint8(6), 2^-8, 'm/s^2', 100);
+p.rateOfTurn   = message(uint32(hex2dec('032')), uint8(6), 2^-9, 'rad/s', 35);
+p.eulerAngles  = message(uint32(hex2dec('022')), uint8(6), 2^-7, 'deg', 180);
+p.velocityXyz  = message(uint32(hex2dec('076')), uint8(6), 2^-6, 'm/s', 500);
+
+% Scalar messages. Unsigned, unlike every vector message above.
+p.groupCounter = scalarMessage(uint32(hex2dec('006')), uint8(2), 'uint16');
+p.sampleTime   = scalarMessage(uint32(hex2dec('005')), uint8(4), 'uint32');
+p.statusWord   = scalarMessage(uint32(hex2dec('011')), uint8(4), 'uint32');
+p.errorCode    = scalarMessage(uint32(hex2dec('001')), uint8(1), 'uint8');
+
+% Messages the MFE26-VC firmware actually decodes, as of branch `controls`.
+% XCDI_EulerAngles (0x022) is a real MTi message but the VCU has no decoder for
+% it; frames land in the unknown-ID counter. Keep it in the contract, default
+% its scheduler rate to zero.
+p.decodedByVcu = {'acceleration', 'rateOfTurn', 'velocityXyz'};
+
+% MT1604P specifies NO per-message data-invalid sentinel for the MTi. Health is
+% signalled out of band by statusWord (0x011) and errorCode (0x001). Do not
+% carry Bosch LWS sentinel habits (0x7FFF / 0xFF) onto this bus.
+p.hasDataInvalidSentinel = false;
+
+% Output rate is a SIMULATOR CHOICE. MT1604P gives an 11-bit per-message
+% frequency field and no default. Mirror whatever the real MTi-680G is
+% programmed to.
+p.defaultOutputRateHz = struct('acceleration', 100, 'rateOfTurn', 100, ...
+    'eulerAngles', 0, 'velocityXyz', 100);
+
+% Bus configuration the MFE26 VCU expects (FDCAN1). The MTi's factory default
+% is 250 kbit/s with CAN output DISABLED; the sensor must be reconfigured to
+% baud code 10 (0x0A) before it will talk to this VCU.
+p.bitrateBitsPerSecond = 500000;
+p.identifierType = 'standard';   % 11-bit; MT1604P also supports 29-bit
 
-% The MT CAN tables define signed integer fields and offsets. Keep byte order
-% explicit at this boundary and cover it with independent golden vectors.
+% MT1604P does NOT state the byte order of CAN output payloads. Big-endian is
+% inherited from MT Low Level Communication Protocol Documentation section
+% 5.1.1 ("All binary data communication is done in big-endian format") and is
+% independently assumed by the MFE26-VC decoder. It is UNPROVEN against real
+% hardware -- see ASSUMPTION A1. Golden vector
+% edge_little_endian_confusion_probe exists to settle it.
 p.byteOrder = 'big';
+p.byteOrderVerified = false;
 end
 
-function item = message(id, dlc, scale, unit)
+function item = message(id, dlc, scale, unit, rangeMax)
 item = struct('id', id, 'dlc', dlc, 'scale', scale, 'unit', unit, ...
-    'signed', true, 'byteOrder', 'big');
+    'signed', true, 'byteOrder', 'big', 'fieldCount', uint8(3), ...
+    'fieldOffsets', uint8([0 2 4]), 'rangeMax', rangeMax);
+end
+
+function item = scalarMessage(id, dlc, format)
+item = struct('id', id, 'dlc', dlc, 'format', format, 'signed', false, ...
+    'byteOrder', 'big');
 end
```

Downstream consequences to handle in the same change:

* `packMti680Payload.m` — add a `'velocityxyz'` case (`scale = protocol.velocityXyz.scale`).
* `packMti680Frame.m` — the `isfield(contract, kind)` guard now admits the new
  scalar entries, which would then fail the "three finite values" check with a
  confusing message. Gate on `item.fieldCount == 3` and give scalars their own
  packer.
* `stepImuSimulation.m` — emit `velocityXyz`; drive `eulerAngles` from the new
  per-message rate table so it defaults off.
* `TestSensorProtocol.m` — load `mti680GoldenVectors.m` and assert
  `packMti680Frame` reproduces `payload` byte-for-byte for all 46 vectors, plus
  the JSON edge cases for reject behaviour.

### 5.2 `inverter_hil/imu/protocol.md`

Replace the revision citation `MT1604P revision 2020.A` with
`MT1604P Revision A, 16 Sept 2019`; add the `0x076` row; annotate `0x022` as
not-decoded-by-VCU; add the range columns; and replace the closing paragraph
("Before physical deployment, compare it with the installed MTi CAN DBC") with a
pointer to `references/sensors/mti680_can_contract.md` and the note that **no DBC
exists in MFE26-VC** (D-10).

### 5.3 `inverter_hil/steering-sensor/lwsProtocol.m`

Add the sentinel constants and the truth table so failure modes are simulable:

```diff
 p.status.trimMask = uint8(4);
 p.status.calMask = uint8(2);
 p.status.okMask = uint8(1);
+
+% Bosch truth table. Only these three combinations are valid; the datasheet
+% says "Other combinations for TRIM, OK and CAL are not valid".
+p.status.calibratedByte   = uint8(7);  % TRIM=1 OK=1 CAL=1, angle+speed valid
+p.status.uncalibratedByte = uint8(5);  % TRIM=1 OK=1 CAL=0, angle = sentinel
+p.status.failureByte      = uint8(4);  % TRIM=1 OK=0 CAL=0, both = sentinel
+p.status.failureAltByte   = uint8(0);  % TRIM=0 OK=0 CAL=0, both = sentinel
+
+p.angleInvalidRaw = uint16(hex2dec('7FFF'));
+p.speedInvalidRaw = uint8(hex2dec('FF'));
+
+% LWS_SPEED is UNSIGNED (0..254 counts, 0xFF = invalid). The MFE26-VC driver
+% casts it to int8_t, which corrupts every value above 508 deg/s -- see
+% references/sensors/imu_contract_delta.md finding D-L1.
+p.speedSigned = false;
+p.speedMaxRaw = uint8(254);
+
+p.byteOrder = 'little';   % stated explicitly: "Byte order LSB (Intel)"
+p.bitrateBitsPerSecond = 500000;
```

### 5.4 Firmware changes to file against `McGillFormulaElectric/MFE26-VC`

These are **not** HIL changes. Ordered by severity:

1. **D-0** — widen/extend the FDCAN acceptance filter to admit `0x022`, `0x032`,
   `0x034`, `0x076`, `0x2B0`. Nothing else matters until this is done.
2. **D-L1** — `LWSSteering::speed` and `getSpeed()` must be `uint8_t`.
3. **D-8** — `imu_data.valid` must be clearable; add per-message freshness.
4. **D-8b** — remove the blocking `HAL_UART_Transmit` calls from the CAN RX ISR.
5. **D-9** — retime FDCAN1 to an 87.5 % sample point.
6. **D-L4** — instantiate `LWSSteering`, route `0x2B0`, and fix `calibrate()`
   to transmit both queued messages.

---

## Summary: who was wrong about what

| Finding | DOC | VCU | SIM |
|---|---|---|---|
| D-0 CAN filter rejects all sensor IDs | — | **wrong** | — |
| D-1a `0x076` velocity missing | — | ok | **wrong** |
| D-1b `0x022` Euler not decoded | — | gap | emits dead traffic |
| D-2 scalar messages declared, unimplemented, signedness unstated | — | gap | **wrong** |
| D-3 no status/error path | ok | gap | gap |
| D-4 endianness | **silent — unproven** | assumes big | assumes big |
| D-5 accel scale `2^-8` vs 1/256 | ok | ok | ok — **no discrepancy** |
| D-6 range guards | ok | ok | **gap** |
| D-7 Offset column typo | **wrong** | ok | ok |
| D-8 `valid` latch, ISR UART | — | **wrong** | — |
| D-9 MTi 250 k default vs 500 k bus; FDCAN1 60 % sample point | ok | **suspect** | silent |
| D-10 no DBC anywhere | — | gap | gap |
| D-L1 `LWS_SPEED` signedness | ok | **wrong** | ok |
| D-L2 angle scaling not applied | ok | gap | ok |
| D-L3 LWS sentinels not modelled | ok | gap | **gap** |
| D-L4 LWS never instantiated | — | **gap** | — |
| Revision citation `MT1604P 2020.A` | — | — | **wrong** (no such revision) |
