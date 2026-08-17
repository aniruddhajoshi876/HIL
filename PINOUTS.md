# MFE HIL Bench — I/O Pinout Reference

Pinouts for the Speedgoat Baseline target machine (`TargetPC1`, 10.10.10.5) used by
the MFE26 VC inverter HIL bench, with emphasis on the **IO183 analog/digital**
module.

**Sources.** Every hardware fact below is quoted from the vendor documents in
`Speedgoat.zip`; nothing here is inferred from memory.

| Fact type | Source |
|---|---|
| IO183 electrical specs, connector part numbers | *IO183 Analog I/O Module — Hardware Reference Manual v1.0* (01 Oct 2019) |
| IO183 pin tables, differential pairing, driver-block params | *IO183 Simulink Driver Block Manual* (Nov 2019) |
| IO614 connector letters, DB9 pinout, termination | *IO614 Simulink Driver Block Manual* (Nov 2019) |
| IO391 terminal boards | *io391 Simulink Driver Block Manual* (Nov 2019) |
| Project signal/net/VCU-pin assignment | `inverter_hil/inverter_hil_plan.md` §3.1, §3.2 |
| As-built block configuration | `inverter_hil/build_inverter_hil_model.m` |

> Read [§7 Documentation conflicts](#7-documentation-conflicts) before trusting any
> single number. The two IO183 manuals disagree in four places, and one of them
> affects wiring.

---

## 1. Modules on this bench

| Module | Role | Used by `inverter_hil`? |
|---|---|---|
| **IO183** | 16-bit analog in/out + digital I/O — VCU pedal stimulus, rail monitoring, discrete stimulus/monitor | **Yes** — the focus of this document |
| **IO614** | 4× CAN (HS) + 1× LIN — VCU control/status bus | **Yes** — channel 1 only |
| **IO391** | Configurable FPGA I/O | **No** — manual ships in the bundle, module is not referenced anywhere in the project |

---

## 2. IO183 — electrical summary

Form factor mPCIe, PCI Express x1, 0.462 W @ 3.3 V, 50.95 × 30 mm, 8.5 g,
−40 °C to +85 °C.

### 2.1 Analog input (ADC)

Converter **LTC1859** (called `LT1859` in HW manual §5.1 — same part).

| Property | Value |
|---|---|
| Channels | 8 single-ended **or** 4 differential |
| Resolution | 16 bit |
| Sample rate | 100 kHz **maximum aggregate** (all active channels combined) |
| Ranges | ±10 V, ±5 V, 0–10 V, 0–5 V — **one setting for all channels** |
| Overvoltage protection | ±25 V |
| Input impedance | 31 kΩ typ. (bipolar), 42 kΩ typ. (unipolar) |
| Zero-scale error | ±28 LSB (±0.04 %) max, no offset adjustment |

Resolution per range (1 LSB):

| Polarity | Range | 1 LSB |
|---|---|---|
| Bipolar | ±10 V | 305 µV |
| Bipolar | ±5 V | 153 µV |
| Unipolar | 0–10 V | 153 µV |
| Unipolar | **0–5 V** | **76 µV** ← range used on this bench |

Source impedance matters: for ≤0.1 % error (66 LSB) the driving source must be
≤31 Ω (bipolar) / ≤42 Ω (unipolar); ideally <10 Ω.

### 2.2 Analog output (DAC)

Converter **AD5686R**.

| Property | Value |
|---|---|
| Channels | 4 single-ended |
| Resolution | 16 bit |
| Ranges | 0–2.5 V, 0–5 V — **one setting for all channels**, unipolar only |
| **Cannot output negative voltage** | straight binary, 0 → 0 V, 65535 → V_FS − 1 LSB |
| Output current | ≤5 mA per channel (1 kΩ minimum load) |
| Update | simultaneous or individual channel; 30 kHz capability |
| Zero-scale error | ±1.5 mV (±0.03 %) max |
| Drift | 2 ppm/°C internal reference |

1 LSB = 76.3 µV (0–5 V range), 38.1 µV (0–2.5 V range).

### 2.3 Digital I/O

- **3.3 V logic levels.**
- Direction individually configurable per line.
- Software-selectable pull-up / pull-down — **all lines share one setting**
  (up or down), stored in non-volatile memory and recalled at power-up.
- Buffered (1-bit transceivers) for current drive and FPGA protection.
- **On power-up or reset every line reverts to input and all data registers reset
  to 0.** This is the hardware-level safe state.

---

## 3. IO183 connector pinouts

Both connectors are 17-pin M12, A-coded.
Module-side part `SACC-CI-M12MS-17CON-L180` (Phoenix Contact 1442081).

| Connector | Carries | Module gender | Cable gender |
|---|---|---|---|
| **A** | Analog (AO, AI, grounds, supplies) | female | male |
| **B** | Digital (DIO 01–16, digital ground) | male | female |

### 3.1 Connector A — analog

| Pin | Single-ended mode | Differential mode |
|---:|---|---|
| 1 | Analog Output 01 | Analog Output 01 |
| 2 | Analog Output 02 | Analog Output 02 |
| 3 | Analog Output 03 | Analog Output 03 |
| 4 | Analog Output 04 | Analog Output 04 |
| 5 | Analog Ground | Analog Ground |
| 6 | Analog Ground | Analog Ground |
| 7 | Analog Input 01 | Analog Input 01 **(−)** |
| 8 | Analog Input 02 | Analog Input 01 **(+)** |
| 9 | Analog Input 03 | Analog Input 02 **(−)** |
| 10 | Analog Input 04 | Analog Input 02 **(+)** |
| 11 | Analog Input 05 | Analog Input 03 **(−)** |
| 12 | Analog Input 06 | Analog Input 03 **(+)** |
| 13 | Analog Input 07 | Analog Input 04 **(−)** |
| 14 | Analog Input 08 | Analog Input 04 **(+)** |
| 15 | 0 V | 0 V |
| 16 | +5 V | +5 V |
| 17 | Analog Ground | Analog Ground |

**Grounds are not interchangeable.** `0 V` (pin 15) is the **target machine**
ground; `Analog Ground` (pins 5, 6, 17) is the **I/O module** ground. `+5 V`
(pin 16) is supplied by the target machine, which can source 1 A continuous.

**Differential mode is not a free re-labelling** — it consumes pin *pairs*, so
switching modes changes which physical pins carry which channel. See §7 item 3:
the Hardware Reference Manual's differential column is wrong; the pairing above
is from the Driver Block Manual.

### 3.2 Connector B — digital

| Pin | Signal |
|---:|---|
| 1–15 | Digital I/O 01 – Digital I/O 15 (pin *n* = DIO *n*) |
| 16 | Digital I/O 16 — **factory option**: can be built as a +3.3 V source instead (must be specified before order; default is a normal digital line) |
| 17 | Digital Ground |

---

## 4. As configured in `inverter_hil`

All four IO183 driver blocks live inside the subsystem literally named:

```
inverter_hil/Hardware I O - PRE-FLIGHT DISABLED
```

> **That name is a permanent warning label, not a state indicator.** It always
> reads "PRE-FLIGHT DISABLED" regardless of whether hardware I/O is live. The
> actual gates are two separate things, both checked by
> `inverterhil.enforceHardwarePreflight`:
>
> | Gate | Meaning | Current value |
> |---|---|---|
> | subsystem `Commented` | `off` = live, `on` = disabled | **`off` → live** |
> | `hil_hardware_preflight_complete` (dictionary) | operator hands-on attestation of levels, grounds, J3 isolation, polarity, CAN termination | **`true`** |
>
> So on the current bench the hardware I/O **is active**. Do not read the block
> name as "disabled". (`enforceHardwarePreflight` also hard-requires R2024b.)

### 4.1 Setup block (`IO183 Setup`)

| Parameter | Value |
|---|---|
| `parModuleId` | `1` |
| `parPciSlot` | `-1` (autosearch) |
| `parAdCoupling` | `Single Ended` |
| `parAdRange` | `0..5V` |
| `parAdChannelLow` / `parAdChannelHigh` | `1` / `4` |
| `parDaChannels` | `[1 2 3 4]` |
| `parDaRange` | `0..5V` |
| `parDaInit` | `[0 0 0 0]` |
| `parDaSimult` | `on` (simultaneous update) |
| `parDoReset` | `[0 0 0 0 0 0 0 0]` |
| `parDiChannels` | `[9 10 11 12 13]` |
| `parIOPullReferenceFront` | `Pull-down` |

All four I/O blocks run at `parSampTime = 0.001` (1 kHz).

### 4.2 Connector A — project signal assignment

| Pin | Channel | Direction | Schematic net | VCU pin | Test point | GUI label |
|---|---|---|---|---:|---|---|
| A1 | AO01 | HIL → VCU | `ANA_THROTTLE_1` | 46 | J2 pin 21 | `AO01 THR1` |
| A2 | AO02 | HIL → VCU | `ANA_THROTTLE_2` | 48 | J2 pin 19 | `AO02 THR2` |
| A3 | AO03 | HIL → VCU | `ANA_BRAKE_P_1` | 53 | J2 pin 23 | `AO03 BRK1` |
| A4 | AO04 | HIL → VCU | `ANA_BRAKE_P_2` | 50 | J2 pin 17 | `AO04 BRK2` |
| A5, A6 | Analog Ground | Reference | Sensor ground | — | Harness ground | — |
| A7 | AI01 | VCU → HIL | `5V_THROTTLE_1` | 88 | harness tap | `AI01 5V_THR1` |
| A8 | AI02 | VCU → HIL | `5V_THROTTLE_2` | 86 | harness tap | `AI02 5V_THR2` |
| A9 | AI03 | VCU → HIL | `5V_BP_1` | 84 | harness tap | `AI03 5V_BP1` |
| A10 | AI04 | VCU → HIL | `5V_BP_2` | 82 | harness tap | `AI04 5V_BP2` |
| A11–A14 | AI05–AI08 | unused in baseline | reserved for differential returns | — | — | — |
| A15 | 0 V | unused in baseline | target-machine 0 V | — | — | — |
| A16 | +5 V | unused in baseline | target-machine +5 V — **do not use as a pedal supply without a current/ground review** | — | — | — |
| A17 | Analog Ground | Spare reference | Sensor ground | — | Harness ground | — |

> **A11–A14 are reserved, not spare.** The single-ended/differential decision is
> still open. If the bench moves to differential, A7–A14 become four fixed pairs
> and the A7–A10 assignment above is destroyed. Do not allocate A11–A14 to
> unrelated signals until that decision is closed.

Alternative differential allocation held open by the plan:

| VCU rail | Single-ended baseline | Differential channel | Differential pins |
|---|---|---|---|
| `5V_THROTTLE_1` | A7 / AI01 | AI01 | A8 (+), A7 (−) |
| `5V_THROTTLE_2` | A8 / AI02 | AI02 | A10 (+), A9 (−) |
| `5V_BP_1` | A9 / AI03 | AI03 | A12 (+), A11 (−) |
| `5V_BP_2` | A10 / AI04 | AI04 | A14 (+), A13 (−) |

**Confirmed - pedal voltage generation.** `pedalVoltageCalibration` maps selected
throttle → AO01/AO02 and selected brake → AO03/AO04 via measured released/pressed
endpoints, clamped to 0–5 V. **Proposed design not built -** `CarMakerPedalDemand`
is standard DLC-8 CAN ID `0x500`, cyclic 10 ms, Intel/little-endian: bytes 1–2 are
throttle and bytes 3–4 brake, each `uint16` raw 0–10000 at 0.01 %/bit; byte 5 holds
active in bit 0, a modulo-16 alive counter in bits 1–4, and zeros in bits 5–7; byte 6
is CRC-8/SAE-J1850 over bytes 1–5; bytes 7–8 are zero. CAN owns both pedals only with
active, an advancing counter, valid integrity/range/reserved fields, and age ≤100 ms.
The authoritative contract is `inverter_hil/docs/can_pedal_demand_frame_spec.md`;
the CarMaker DBC on branch `IPG-CAN` matches it byte for byte.
`verify_pinouts` checks the common selector control source plus all calibration/AO
routing. Local source: `inverter_hil/build_inverter_hil_model.m`.

| Function input | Dictionary source | Drives |
|---|---|---|
| `throttle` | `Throttle Source Switch`: fresh atomic CAN demand, else GUI `hil_cmd_pedals_throttle` | AO01 (with `…_v1` pair), AO02 (`…_v2`) |
| `brake` | `Brake Source Switch`: fresh atomic CAN demand, else GUI `hil_cmd_pedals_brake` | AO03 (`…_v3`), AO04 (`…_v4`) |

#### Calibration state — all 4 channels set

Single source of truth: **`+inverterhil/pedalCalibrationConstants.m`**, applied to
the dictionary by **`apply_pedal_calibration.m`**. Do not edit the `.sldd` by hand.

| Channel | Raw released → pressed | `released_v` | `pressed_v` | Direction |
|---|---|---|---|---|
| AO01 throttle 1 | 30100 → 23100 | 1.515679 V | 1.163195 V | falling |
| AO02 throttle 2 | 63600 → 46500 | 3.202564 V | 2.341497 V | falling |
| AO03 brake 1 | 9025 → 31800 | 0.454452 V | 1.601282 V | rising |
| AO04 brake 2 | 9025 → 31800 | 0.454452 V | 1.601282 V | rising |

All raw counts are read from `MFE26-VC/Core/Src/driverInputs.cpp`
(`convertThrottle1ToPercent`, `convertThrottle2ToPercent`, `convertBrakeToPercent`)
and converted through the ADC domain that repo's own SIL model declares
(`sil/registry/params.hpp`: `ADS_VREF_V = 3.3`, `ADS_FULL_SCALE = 65535`; see
`docs/sil_vs_hil_conformance.md` CONF-7). AO03 and AO04 are identical because the
firmware runs `brake1Raw` and `brake2Raw` through the *same* conversion.

`pressed_v < released_v` on the throttles is correct — those signals fall as the
pedal is pressed. `pedalVoltageCalibration` interpolates released → pressed, so
direction is expressed by the endpoints themselves and never declared separately.

> **⚠ A rebuild used to erase this.** `build_inverter_hil_model` creates the
> dictionary from scratch with every endpoint at `NaN`, and that silently wiped
> the applied calibration once — reaching the deployed target. The failure is
> quiet: `pedalVoltageCalibration` emits **0 V** for a non-finite endpoint, so the
> GUI sliders keep moving while the VCU pin never changes. The build now re-applies
> `apply_pedal_calibration` as its last step, and
> `TestModelArtifacts/dictionaryContractAndSafeDefaultsAreExact` asserts the
> dictionary equals the constants, so a recurrence fails the suite instead of
> shipping.

> ### ⚠ Derived from the device under test, not measured
>
> **1. These endpoints came from firmware constants, not from a measurement.**
> `inverter_hil_plan.md` §3.1 requires each endpoint be measured **at the
> connected VCU pin under load**, not at the IO183 connector — it warns that
> "typical pedal values must not be assumed". The numbers above assume the IO183
> output reaches the VCU ADC undivided and unloaded. **Confirm on the bench
> before trusting them quantitatively.**
>
> This has a permanent consequence worth stating plainly: because HIL 0–100 % is
> defined *by* the VCU's own constants, a pedal sweep **cannot discover that those
> constants are wrong**. It confirms the VCU interprets a known voltage as the
> percentage it intends to; it does not confirm that intent matches the physical
> pedal. Closing that gap needs measured endpoints.
>
> Two further uncertainties that reading firmware cannot settle:
>
> - **`VREF` is assumed.** `ADS7066.cpp:31` clears `REF_EN`, so the internal 2.5 V
>   reference is **off** and an external pin sets the scale. Its actual value is a
>   board fact absent from the firmware; 3.3 V comes from the SIL model's
>   assertion. If it is really 2.5 V, every voltage above is high by 1.32×.
> - **The ADS7066 is a 12-bit part** whose result `ADS7066.cpp:126` left-justifies
>   into a 16-bit word, so counts move in steps of 16 and true full scale is 65520,
>   not 65535. The resulting error is ~1 part in 65535 (≈0.02 mV), so 65535 is kept
>   to stay bit-identical with the SIL model.
>
> **2. `pressed_v1` is the VCU's 100 % point, not the pedal's stop.**
> `throttle1Min` is 23100 while the same file's comment and `isThrottle1InRange`
> put full press near 20900. 23100 is used because it is the constant the
> conversion actually applies, which makes **GUI throttle % map 1:1 onto firmware
> `throttle1Pct`**. Verified round-trip GUI → AO01 volts → 16-bit DAC quantisation
> → VCU ADC counts → firmware percent: **0.0000 % error** at 0/10/25/50/75/90/100 %,
> every raw count inside the in-range window `[19520, 31480]`. Using 20900 would
> saturate the firmware at ~76 % of GUI travel.
>
> **3. There is a second, separate calibration surface.**
> `+inverterhil/defaultCalibration.m` holds `cal.pedals.releasedV/pressedV` as
> 1×4 `NaN` vectors for the host/SIL core path. The dictionary entries documented
> here feed the **Simulink** `Pedal Voltage Calibration` block. Setting one does
> not set the other.

Digital command sources (all default to `false`/`0` at load):
`hil_cmd_digital_main_button`, `hil_cmd_digital_cooling_switch`,
`hil_cmd_digital_shutdown_feedback`, `hil_cmd_digital_precharge_sequence`.
Pedal command sources are separate: GUI writes `hil_cmd_pedals_throttle` and
`hil_cmd_pedals_brake`; **Proposed design not built -** CAN ID `0x500` may
atomically select its validated demand pair ahead of those GUI values. Local
source: `inverter_hil/build_inverter_hil_model.m`.

### 4.3 Connector B — project signal assignment

Channels 1–8 are HIL→VCU outputs, 9–13 are VCU→HIL inputs, 14–16 reserved.

| Pin | Channel | Direction | Schematic net | VCU pin / function | Test point | Baseline use |
|---|---|---|---|---|---|---|
| B1 | DIO01 | out, HIL → VCU | `PRECH_BTN_IN` | 99, `PRECH_BTN_IN` | J2 pin 1 | Precharge-button stimulus (pulse-generated) |
| B2 | DIO02 | out, HIL → VCU | `MAIN_BTN_IN` | 101, `MAN_BTN_IN` | J2 pin 3 | Main-button stimulus |
| B3 | DIO03 | out, HIL → VCU | `COOLING_SW_IN` | 103, `COAST_IN` | J2 pin 5 | Cooling/coast switch — **polarity TBD** |
| B4 | DIO04 | out, HIL → VCU | `SD_FB_IN` | 113, `SD_FB_IN` | J2 pin 15 | Shutdown-loop feedback stimulus |
| B5 | DIO05 | out, HIL → VCU | `SW_IN_1` | 111, `SW_IN_1` | J2 pin 13 | Optional switch — tied to constant 0 |
| B6 | DIO06 | out, HIL → VCU | `SW_IN_2` | 105, `SW_IN_2` | J2 pin 7 | Optional switch — tied to constant 0 |
| B7 | DIO07 | out, HIL → VCU | `SW_IN_3` | 107, `SW_IN_3` | J2 pin 9 | Optional switch — tied to constant 0 |
| B8 | DIO08 | out, HIL → VCU | `SW_IN_4` | 109, `SW_IN_4` | J2 pin 11 | Optional switch — tied to constant 0 |
| B9 | DIO09 | in, VCU → HIL | `VC_SD_OUT` | 25, `VC_SD_OUT` | TP6 | Monitor VCU shutdown output |
| B10 | DIO10 | in, VCU → HIL | `MAIN_EN_OUT` | 27, `MAIN_EN_OUT` | TP7 | Monitor main-contactor enable |
| B11 | DIO11 | in, VCU → HIL | `PRECH_EN_OUT` | 29, `PRECH_EN_OUT` | TP8 | Monitor precharge enable |
| B12 | DIO12 | in, VCU → HIL | `INV_CTRL_DIS` | 34, inverter output bank | TP10 | Ephorus Control Disable |
| B13 | DIO13 | in, VCU → HIL | `INV_CTRL_EN` | 36, inverter output bank | TP9 | Ephorus Control Enable |
| B14 | DIO14 | reserved | — | candidate `GRI_RELAY_1`, pin 35 | TBD | not connected |
| B15 | DIO15 | reserved | — | candidate `COMET_RELAY`, pin 37 | TBD | not connected |
| B16 | DIO16 | reserved | — | candidate `GRI_RELAY_2`, pin 39 | TBD | not connected |
| B17 | Digital Ground | Reference | Controller logic ground | — | Harness ground | **connect only after ground strategy review** |

**Digital output port wiring** (`IO183 DIO01-DIO08 Safe Zero`, port → source):

| Port | DIO | Driven by |
|---:|---|---|
| 1 | DIO01 | `Precharge Pulse Generator` (edge-triggered from `hil_cmd_digital_precharge_sequence`) |
| 2 | DIO02 | `hil_cmd_digital_main_button`, cast boolean → double |
| 3 | DIO03 | `hil_cmd_digital_cooling_switch`, cast boolean → double |
| 4 | DIO04 | `hil_cmd_digital_shutdown_feedback`, cast boolean → double |
| 5–8 | DIO05–08 | `Unused SW_IN_1..4` — Constant `0` |

The IO183 Digital Output ports accept **double**, so each boolean tunable is cast
explicitly rather than being redeclared at source; that keeps the Constant a
direct, addressable reference to the boolean dictionary entry the GUI writes.

> ### ⚠ GUI pin order ≠ DIO channel order
> `inverterhilgui.blankTelemetry` builds its `pins` array as
> `VC_SD_OUT, MAIN_EN_OUT, PRECH_EN_OUT, INV_CTRL_EN, INV_CTRL_DIS`
> (test points TP6, TP7, TP8, TP9, TP10).
>
> The **Digital Input block reads channels in numeric order** `[9 10 11 12 13]`,
> i.e. `… INV_CTRL_DIS (DIO12), INV_CTRL_EN (DIO13)`.
>
> **The last two entries are transposed between the two orderings.** GUI slot 4 is
> DIO13 and GUI slot 5 is DIO12. The name↔test-point pairing in the GUI is correct
> (TP9 = `INV_CTRL_EN`, TP10 = `INV_CTRL_DIS`), so this is a display-order
> difference, not a mislabel — but do **not** index the DI block's port vector with
> the GUI's array position. Note also that high-rate instrument streaming is not
> registered yet, so those GUI fields are inactive regardless.

### 4.4 Non-obvious safety behaviour

- IO183 initial **and** reset values are 0 V / 0 for every configured channel.
- A stopped, failed, or unloaded application is *intended* to present an
  out-of-range pedal fault rather than a healthy-looking pedal value. Per the
  plan, the current VCU firmware's lower-bound raw-count checks make a 0 V
  stimulus invalid for both throttle channels and brake channel 1 (brake channel 2
  plausibility is currently disabled). **This is a measured acceptance test, not a
  verified hardware assumption** — confirm on target before relying on 0 V as the
  fallback.
- Loss of the model heartbeat returns the channels to 0 V through the configured
  reset/fallback path.

---

## 5. IO614 — CAN (secondary, for cross-reference)

### 5.1 Connector letter → CAN channel

The four DB9 connectors are labelled A–D and **do not map to channel numbers in
order**:

| Connector | CAN channel |
|---|---|
| **A** | CAN 2 (+ LIN) |
| **B** | **CAN 1** |
| **C** | CAN 4 |
| **D** | CAN 3 |

`inverter_hil` and `io614_can_visibility_test_R2024b` both use **channel 1 → wire
to connector B**, `CAN (HS)` @ **1.0 MBaud**, channels 2–4 disabled.

### 5.2 DB9 pinout (identical on all four connectors)

| Pin | Signal | Condition |
|---:|---|---|
| 1 | CAN Low | low-speed (LS) — **channel 1 only** |
| 2 | **CAN Low** | **high-speed (HS)** ← used |
| 3 | GND | |
| 4 | CAN High | low-speed (LS) — channel 1 only |
| 5, 6 | — | |
| 7 | **CAN High** | **high-speed (HS)** ← used |
| 8 | LIN | channel 2 only |
| 9 | LIN VBAT (8–18 V DC) | channel 2 only |

> **Termination is not on the module.** A 120 Ω resistor is required **between
> pins 2 and 7**. Speedgoat's IO614 loopback cable includes it; a bare cable to a
> third-party analyser does not. Missing termination presents as ~100 % bus load
> with `transmit_pending` stuck true and no successful ACK.

CAN IDs in `inverter_hil`: HIL TX `0x383 0x385 0x393 0x395 0x3A3 0x3A5 0x3B3
0x3B5 0x400` plus CarMaker telemetry `0x501` (four torque setpoints) and
`0x502` (four ready bits), all on CAN 1; HIL RX `0x186 0x196 0x1A6 0x1B6`
plus CarMaker pedal demand `0x500`. The telemetry contract is authoritative in
`inverter_hil/docs/can_pedal_demand_frame_spec.md`.

---

## 6. IO391 — configurable FPGA I/O (not used here)

The IO391 has **no fixed pinout** — pin function is defined by the loaded FPGA
bitstream, so consult the custom implementation manual for the specific bitstream.
The terminal boards are:

- **Terminal Board A:** `1a`, `2a` Ground · `3a`–`14a` FPGA code-module function
  (TTL) · `15a` 0 V · `16a` 5 V · `17a` Ground
- **Terminal Board B:** `1b`, `2b` Ground · `3b`–`16b` FPGA code-module function
  (TTL) · `17b` Ground

Same ground caveat as IO183: `0 V` is target-machine ground, analog ground is
module ground; `5 V` comes from the target machine (1 A continuous).

---

## 7. Documentation conflicts

Found while cross-checking the two IO183 manuals against each other. These are
vendor-document inconsistencies, not project errors.

1. **Digital I/O line count — 14 vs 16.**
   HW Ref Manual §1 and the specs table say **14** lines; §4.3.1 says "pins 1–16
   are Digital I/O lines"; §5.4 says "16 + 1 digital I/O lines"; the Driver Block
   Manual says **16**. The connector pin table (both manuals) unambiguously lists
   **DIO 01–16 on pins 1–16**. *Treat 16 as correct; "14" appears to be stale.*
   The project only uses DIO01–13, so this does not currently bite.

2. **Pull resistor value — 10 kΩ vs 22 kΩ.**
   HW Ref Manual §4.3.1 and §5.4 say **10 kΩ**; Driver Block Manual §3.1 says
   "the resistance value is **22 kΩ**". *Unresolved — measure before relying on a
   specific pull strength.* The bench uses `Pull-down`.

3. **Differential pin mapping — HW manual is wrong.**
   HW Ref Manual §6.1's "Differential" column simply repeats the single-ended
   names (`Analog Input 01`…`08`), which is impossible for 4 differential channels
   on 8 pins. The Driver Block Manual gives the real pairing
   (7/8 = AI01 −/+, 9/10 = AI02 −/+, 11/12 = AI03 −/+, 13/14 = AI04 −/+), and it
   is consistent with `inverter_hil_plan.md`. **Use the Driver Block Manual.**
   This is the one conflict that would cause miswiring.

4. **"16 analog voltage inputs" (HW Ref Manual §5.4).**
   Contradicts the 8 single-ended / 4 differential stated everywhere else,
   including the same manual's own specs table and connector pinout. *Typo.*

5. Minor: the ADC is called `LTC1859` in §4.1.1 and `LT1859` in §5.1 — same part.

Also note the file named `IO614 OEM Datasheet.pdf` in `Speedgoat.zip` is
**mislabelled**: its contents are the *IXXAT PCIe/104 CAN Interface
(CAN-IB130/230/630)* user manual — a different manufacturer's PC-side card. It
does **not** document the Speedgoat IO614 and has no A/B/C/D connector mapping.
Use `IO614 Simulink Driver Block Manual.pdf` instead.

---

## 8. Verifying this document

`verify_pinouts.m` (same folder) checks the §4 "as configured" claims against the
real `inverter_hil.slx` — it loads the model and compares every IO183 block
parameter and every digital-output port source against the tables above.

```matlab
cd('C:\Users\aniru\OneDrive - McGill University\mfe\HIL')
verify_pinouts
```

It reports `PASS`/`FAIL` per check and errors out on any mismatch, so it is safe
to run from a test harness. It loads the model read-only and closes it again if
it was not already open.

**Last run: 53 checks, 53 passed, 0 failed**, covering:

- all 13 `IO183 Setup` parameters (coupling, ranges, channel spans, pull, init/reset)
- all 4 I/O blocks' channel vectors, init/reset values and 1 kHz sample time
- the hardware boundary being live (`Commented = off`)
- all 8 digital-output port sources (precharge, main, cooling, shutdown, 4× unused)
- all 4 analog-output port sources **including source-port index**, so a
  transposed throttle/brake line is caught
- all 10 pedal-calibration inputs in order
- the GUI-vs-DIO ordering caveat in §4.3

The suite was **negative-tested**: deliberately changing `parAdRange` to `0..10V`
in memory made it fail with `1 PINOUTS.MD claim(s) do not match the model`, then
the change was reverted and the model closed without saving. So the passes are
meaningful, not vacuous.

It also reports pedal-calibration state as a **warning, not a failure** (NaN
endpoints are the intended uncalibrated state).

**§2, §3, §5.2, §6 are vendor hardware facts and are not machine-checkable** —
they are verified by citation only, against the sources listed at the top. Nothing
in this document was written from memory.
