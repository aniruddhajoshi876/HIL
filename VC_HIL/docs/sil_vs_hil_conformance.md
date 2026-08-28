# SIL / HIL / firmware conformance findings

Comparison of three implementations of the MFE26 vehicle-controller and Ephorus
inverter system:

| Key | Implementation | Root |
| --- | --- | --- |
| **A** | SIL reference (`sil/`), authoritative per the user | `MFE26-VC` clone, branch `todo`, HEAD `39ea8ef` |
| **B** | MATLAB HIL host core (`+inverterhil/`) | `inverter_hil/` |
| **C** | Real VCU firmware (`Core/`, `Drivers/Device_Drivers/`) | same `MFE26-VC` clone |

## Method and an important structural note

SIL compiles the **real production sources** into its `sil_prod` object library
(`sil/CMakeLists.txt:289-294`, manifest guard at `:44`; the configure log lists
`Core/Src/vcComms.cpp`, `Core/Src/vcStateMachine.cpp`,
`Core/Src/driverInputs.cpp`). A and C therefore share identical VCU-side code by
construction. Every A-vs-C divergence below lives in SIL's **inverter model
layer** (`sil/models/ephorus_model.cpp`, `hv_model.cpp`, `ads7066_model.cpp`),
which plays the same role as the HIL host core — so the meaningful three-way
comparison is:

- **A** = `sil/models/*` (emulated inverter/plant)
- **B** = `+inverterhil/*` (emulated inverter/plant)
- **C** = `Drivers/Device_Drivers/*` + `Core/Src/*` (the VCU that talks to both)

Evidence was produced by building and running SIL (MinGW-w64 gcc 16.1, CMake
4.3.2, Ninja) and by running the HIL suite in R2024b.

- `sil_conformance.exe ephorus_conformance` → `verdict=PASS errors=0`
- `sil_runner.exe --scenario ephorus_switch_temp_xfail` → `verdict=FAIL errors=1`
  (an intentional XFAIL; see CONF-1)
- `run_inverter_hil_tests` → **131 Passed, 0 Failed** (baseline unchanged; no
  file in either repo was modified by this investigation)

> **Amendment, 2026-08-02.** This document was written before the CAN
> decoder-bank-threading commits (`a308a7e`, `d5bcb8d`, `a5dc937`, `97bdea2`,
> `3bdb6e1`) and before CONF-2/SUSP-1 below were resolved (torque scale fixed
> to 1/256; GUI dc-link/load-torque tunables wired into `stepModel`; CAN
> control-frame and status-frame drop-mask fault injection added). The
> `run_inverter_hil_tests` baseline is now **161+ Passed, 0 Failed** (161
> before these fixes, plus new tests added alongside them: `TestCanDropMask`
> and `TestVcuCommandLoop.torqueLimitScaleMatchesFirmwareConformanceGoldenValue`).
> CONF-2 and SUSP-1 are marked resolved/updated in place below rather than
> rewritten, so the original investigation's evidence trail stays intact; every
> other finding in this document reflects the read-and-verify pass exactly as
> originally performed and has not been re-audited.

---

## CONFIRMED divergences

Both sides traced to source, and they genuinely differ.

### CONF-1 — 0x3X3 bits 52-63 switch temperature: unsigned in SIL, signed in HIL and firmware

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | Packs **u12** unsigned, 1/16 °C, saturating at 4095 (255.9 °C) | `sil/models/ephorus_model.cpp:567-568` (`clampUnsigned(s.switch_temp_c, 12, 1.0/16.0)`); asserted by `sil/tests/conformance/ephorus_conformance.cpp:484-489` — "145 C switch temperature encodes as unsigned u12 raw 0x910" |
| **B (HIL)** | Packs **s12** two's complement, saturating at 2047 (127.94 °C) | `+inverterhil/packStatus3X3.m:28-29` (`encodeSigned(... 1/16, 12 ...)`); `+inverterhil/private/encodeSigned.m:6-9` |
| **C (firmware)** | Decodes **s12** via sign extension | `Drivers/Device_Drivers/Src/ephorus_driver.cpp:311-315`; declared `s12` at `Drivers/Device_Drivers/Inc/ephorus_driver.hpp:66,89-90` |

- **Area:** CAN. **Frame:** `0x383/0x393/0x3A3/0x3B3`, bits 52-63. **Severity: HIGH.**
- SIL treats the firmware's sign extension as a **production defect** and pins it
  as a strict expected-failure:
  `sil/scenarios/ephorus_switch_temp_xfail.cpp:1-5` — *"The tracked Ephorus
  datasheet defines this field as u12 at 1/16 C; production currently
  sign-extends it as s12."* Reproduced:
  `sil_runner --scenario ephorus_switch_temp_xfail` →
  `ERROR[1] name=A2.ephorus.production_switch_temp_u12`.
- **HIL has silently sided with the firmware against the SIL reference.**
- Two concrete consequences:
  1. SIL's own golden encoding of 145 °C is raw `0x910` = 2320. The firmware
     decoder sign-extends: 2320 − 4096 = −1776, ×1/16 = **−111.0 °C**. SIL emits
     a shutdown-level temperature that the DUT reads as deeply negative.
  2. Conversely, the HIL packer **cannot emit anything above 127.94 °C**. The
     firmware/plant switch-overtemperature trip is at 145 °C
     (`sil/registry/params.hpp:73` `EPH_SWITCH_SHUTDOWN_C = 145.0`;
     `+inverterhil/stepChannelState.m:238` `input.switchTemperatureC > 145`), so
     **the HIL bench can never stimulate a real switch-overtemperature reading
     on the wire.** This is a hole in the test capability, not just a codec
     mismatch.
- The plan does not resolve this field. Reporting as a genuine A-vs-{B,C}
  disagreement rather than picking a winner.

### CONF-2 — RESOLVED 2026-08-02: control torque scale is 1/256 in SIL, firmware, and now HIL

**Originally filed as a divergence** (HIL defaulted to 1/512 against SIL's and
the firmware's 1/256); **resolved, not just flagged**, once independent
firmware evidence settled the ambiguity `inverter_hil_plan.md:303-354` had
left open. See `+inverterhil/protocol.m`'s `torqueProfiles.vcu256` comment for
the full citation set
(`Drivers/Device_Drivers/Inc/ephorus_driver.hpp:38-39,55`;
`sil/models/ephorus_model.cpp:37-38`;
`sil/tests/conformance/ephorus_conformance.cpp:252,440`;
`sil/tests/gui/can_decode_test.cpp:25`). The 1/512 value the HIL had defaulted
to was never a torque scale in either the firmware or SIL at all — it is
`switchingFreq_khz`'s unrelated scale
(`ephorus_driver.hpp:119,187`, `sil/models/ephorus_model.cpp` status packing) —
and confusing the two appears to be how the HIL's provisional profile picked
1/512 in the first place.

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | `/256.0`, and additionally clamps received counts to ±16384 (±64 Nm) | `sil/models/ephorus_model.cpp:35-43` |
| **B (HIL), before the fix** | Default profile was `provisional512`, **1/512** | `+inverterhil/protocol.m:21-24` (pre-fix); `+inverterhil/defaultCalibration.m:6-8` (pre-fix) |
| **B (HIL), after the fix** | Default profile is `vcu256`, **1/256**, `verified = true` | `+inverterhil/protocol.m` `torqueProfiles.vcu256`; `+inverterhil/defaultCalibration.m` |
| **C (firmware)** | `EPHORUS_TORQUE_CTRL_SCALE_NM = 1.0f/256.0f` | `Drivers/Device_Drivers/Inc/ephorus_driver.hpp:55`; applied at `Src/ephorus_driver.cpp:267-268` |

- **Area:** CAN. **Frame:** `0x186/0x196/0x1A6/0x1B6`, bytes 4-5 and 6-7. **Severity: HIGH (was), now closed.**
- The firmware commands up to 15 Nm (`Core/Src/vcComms.cpp:141`) → 3840 counts.
  SIL reads 15.0 Nm; the HIL previously read **7.5 Nm** under the 1/512
  default — a factor-of-two under-read of every torque command on the bench.
  With the HIL now defaulting to 1/256, all three agree: 15.0 Nm.
- The retired `provisional512` profile is kept in `+inverterhil/protocol.m`
  (still `verified = false`, now explicitly annotated as the switching-frequency
  mixup) only because `validateCalibration.m`'s profile whitelist and a handful
  of tests (`TestPlant.profileObservabilityIsCorrectAndImmutable`,
  `TestVcuCommandLoop.torqueLimitCountsAreDecodedAndRetainedExactly`) exercise it
  as a second, known-not-the-answer profile for regression coverage. It must
  never become the default again.
- A golden-value regression test now pins the resolved conversion directly to
  the firmware's own conformance numbers:
  `TestVcuCommandLoop.torqueLimitScaleMatchesFirmwareConformanceGoldenValue`
  asserts 3200 raw counts → +12.5 Nm through `DEFAULTCALIBRATION`'s default,
  matching `sil/tests/conformance/ephorus_conformance.cpp:252,440`.

### CONF-3 — Power-on with a silent bus: SIL latches Error, HIL holds Idle

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | Latches **Error (2)** at 500001 µs even if no command was **ever** received | `sil/models/ephorus_model.cpp:193-196` — the `now_us - m.last_command_us > command_error_us` check has **no `has_command` guard**, and `Motor::last_command_us` defaults to 0 (`ephorus_model.hpp:184-185`) |
| **B (HIL)** | Holds **Idle (0)** indefinitely on the never-received sentinel | `+inverterhil/stepChannelState.m:209-215` (explicit sentinel guard `< intmax('uint32')`); sentinel set at `+inverterhil/decoderSnapshot.m:10-16` |
| **C (firmware)** | Transmits control frames **only in RTD** | `Core/Src/vcComms.cpp:211-256` — `LV_ON/PRECHARGING/ENABLE/BUZZING` send only the CAN-501 pedal frame |

- **Area:** state. **States:** LV_ON, PRECHARGING, ENABLE, BUZZING. **Severity: HIGH.**
- Empirically confirmed on the SIL side by SIL's own **passing** assertion
  `A2.ephorus.initial_command_silence`
  (`sil/tests/conformance/ephorus_conformance.cpp:748-757`): *"after each power
  cycle, no command is allowed through 500 ms and faults at 500001 us"* — Idle
  at +500000 µs, Error at +500001 µs.
- The firmware's first control frame cannot arrive before RTD, which is at least
  7.5 s of precharge (`Core/Src/vcStateMachine.cpp:326`) plus 1.5 s of buzzer
  (`:362`) after the precharge button. **Under SIL, all four inverters are
  therefore in Error (state 2) throughout LV_ON, PRECHARGING, ENABLE and
  BUZZING. Under the HIL they are in Idle (0).** These are directly conflicting
  values on `0x383/0x393/0x3A3/0x3B3` bits 0-1 for four of the six VCU states.
- This is exactly the item flagged as "recently fixed in HIL". The fix is
  defensible in isolation, but it **diverges from the stated reference**. Either
  SIL's missing `has_command` guard is a bug in the reference, or the HIL fix
  needs to be reverted; the two cannot both be right. Recommend resolving
  explicitly rather than leaving it implicit.
- Blast radius today is limited because the VCU's `allInvertersReady()` gate is
  commented out of `shouldFault()` (`Core/Src/vcStateMachine.cpp:221-223`) —
  the VCU currently ignores inverter state entirely. If that check is
  re-enabled, SIL and HIL will produce opposite verdicts at boot.

### CONF-4 — DC-link minimum: 50 V in SIL, 350 V in HIL and firmware

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | `EPH_PAIR_MIN_V = 50.0` V — gates ready/Drive eligibility **and** `0x400` bits 48/49 | `sil/registry/params.hpp:52`; used at `sil/models/ephorus_model.cpp:272` (`readyEligible`) and `:598-601` (status bits) |
| **B (HIL)** | `dcLinkMinimumV = 350` — gates Drive entry and the undervoltage fault | `+inverterhil/defaultStateConfig.m:7`; `+inverterhil/defaultCalibration.m:9`; `stepChannelState.m:257` (`canEnterDrive`), `:230` (undervoltage) |
| **C (firmware)** | Requires **both** pairs strictly above 350 V | `Core/Src/vcStateMachine.cpp:143` (`sys.dcLink12_v <= 350 \|\| sys.dcLink34_v <= 350` → not complete) |

- **Area:** voltage. **States:** PRECHARGING → ENABLE → BUZZING → RTD. **Severity: HIGH.**
- **SIL is the outlier by 7×.** The plan agrees with the firmware:
  `inverter_hil_plan.md:874` — *"The pinned VCU requires valid `0x400` voltages
  above 350 V in ENABLE."*
- Concrete effect: with the DC link partway through its precharge ramp at, say,
  200 V (SIL pack is 400 V with a 500 ms ramp tau,
  `sil/registry/params.hpp:53-54`), SIL's inverters report ready and are
  Drive-eligible; HIL's hold Idle with reason
  `hold_idle_dc_link_below_minimum`. Any bench test of the precharge window will
  disagree between the two.
- Recommend reporting SIL's 50 V as the defect, but flagging rather than
  silently changing it — the value may be an intentional stand-in for a
  *configured inverter* minimum distinct from the VCU's precharge criterion.

### CONF-5 — Error-reset backoff timer measured from different origins

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | Backoff measured from **error entry**: `now_us - m.error_enter_us >= m.backoff_us` | `sil/models/ephorus_model.cpp:409-419`; `error_enter_us` set in `enterError` at `:295` |
| **B (HIL)** | Backoff measured from **fault clear**: `faultClearUs` is forced to 0 on every tick with an active fault and only accumulates afterwards | `+inverterhil/stepChannelState.m:96` (`next.faultClearUs = uint64(0)` while faulted) vs `:125,128` (accumulate, then `faultClearUs >= resetWaitUs`) |
| **C (firmware)** | No opinion — sends `resetError` unconditionally once on RTD entry | `Core/Src/vcComms.cpp:234-240`; `Drivers/Device_Drivers/Src/ephorus_driver.cpp:446-458` |

- **Area:** state. **State:** Error(2) → Idle(0). **Severity: MEDIUM.**
- For any fault that persists longer than the current backoff, SIL permits the
  reset immediately once the cause clears, whereas HIL demands a **further full
  backoff interval** after clearing. With the escalated backoff capped at 100 s
  (`params.hpp:75` `EPH_RESET_CAP_US = 100000000`;
  `defaultStateConfig.m:14` `resetBackoffMaxS = 100`) this is a difference of up
  to 100 s in recovery latency after a repeated fault.
- The base value and doubling/halving policy do match
  (500 µs floor: `params.hpp:74` vs `protocol.m:33`).

### CONF-6 — Motor over-temperature shutdown threshold: 160 °C vs 155 °C

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | 160 °C | `sil/registry/params.hpp:80` (`EPH_MOTOR_SHUTDOWN_C = 160.0`), consumed at `sil/models/ephorus_model.cpp:222` |
| **B (HIL)** | 155 °C | `+inverterhil/defaultStateConfig.m:23`; `+inverterhil/defaultCalibration.m:22`; consumed at `stepChannelState.m:236` |
| **C (firmware)** | No threshold of its own — decodes and displays only | `Drivers/Device_Drivers/Src/ephorus_driver.cpp:305-309` |

- **Area:** voltage/thermal. **State:** any → Error(2). **Severity: MEDIUM.**
- In the 155-160 °C band the two models take opposite actions: HIL latches
  `motor_overtemperature`, SIL keeps running. Derate start/end (120/150 °C) do
  agree (`params.hpp:81-82` vs `defaultCalibration.m:29-30`), which makes the
  shutdown mismatch look like drift rather than intent.

### CONF-7 — Pedal analog-output ceiling 5 V vs a 3.3 V ADC domain

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | ADS7066 domain is 3.3 V full scale; the model clamps to `VREF` | `sil/registry/params.hpp:30` (`ADS_VREF_V = 3.3`), `:34` (`ADS_FULL_SCALE = 65535`); `sil/models/ads7066_model.cpp:64-71` |
| **B (HIL)** | Pedal outputs clamp to `[0, 5]` V; validation *rejects* any `maximumV` above 5 but permits everything up to it | `+inverterhil/defaultCalibration.m:43-44`; `+inverterhil/validateCalibration.m:138-142`; `+inverterhil/safeIoOutputs.m:61-63` |
| **C (firmware)** | Calibration endpoints sit at roughly 0.45-3.20 V | `Core/Src/driverInputs.cpp:166-221`: throttle1 raw 20900-30100, throttle2 46500-63600, brake1 9025-31800, all of 65535 at 3.3 V |

- **Area:** voltage. **States:** all. **Severity: MEDIUM.**
- Converting the firmware's own endpoints: throttle1 spans **1.052-1.515 V**,
  throttle2 **2.342-3.202 V**, brake1 **0.454-1.601 V**. Nothing in the HIL core
  constrains a commanded pedal voltage to the 3.3 V ADC domain — the ceiling is
  5 V, and the plan configures the IO183 AO channels for 0-5 V
  (`inverter_hil_plan.md:93`, `:678`).
- **Currently mitigated**, and I want to be precise about that:
  `cal.pedals.releasedV`/`pressedV` default to `NaN`
  (`defaultCalibration.m:41-42`), and `safeIoOutputs.m:38-42` blocks all output
  with `pedal_calibration_unverified` until they are set. So this is a latent
  limit-value divergence, not a live overdrive. It becomes real the moment
  someone calibrates without independently bounding to 3.3 V.
- Note the per-channel structure is *correct*: `releasedV`/`pressedV` are 1×4, so
  the two APPS channels legitimately get different endpoints from the same pedal
  fraction (`safeIoOutputs.m:58-59`), matching the firmware's two differently
  supplied sensors. No finding there.

### CONF-8 — SIL ignores the negative torque limit in its plant

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | Decodes and reports `torque_negative_nm`, but the plant target uses **only** the positive limit | `sil/models/ephorus_model.cpp:318-321` (`s.requested_torque_nm = m.control.torque_positive_nm`); the negative limit only reaches the snapshot at `:369` |
| **B (HIL)** | Bounds the torque setpoint by both limits | `+inverterhil/stepPlant.m:92-100` (`clamp(..., lowerNm, upperNm)`) |
| **C (firmware)** | Always sends 0 negative (no regen) | `Core/Src/vcComms.cpp:142` |

- **Area:** CAN / plant. **State:** Drive(1). **Severity: LOW.**
- Unexercised today because the firmware never requests regen. Becomes a real
  divergence the moment regen is enabled: SIL will not model braking torque at
  all.

### CONF-9 — Received-command torque clamping differs

| | Behavior | Evidence |
| --- | --- | --- |
| **A (SIL)** | Clamps decoded counts to ±16384 → ±64 Nm, at decode time | `sil/models/ephorus_model.cpp:39-43` |
| **B (HIL)** | No decode clamp; raw `int16` is retained and the *plant* clamps at ±64 Nm | `+inverterhil/decodeControlFrame.m:55-60`; `+inverterhil/defaultCalibration.m:20-21` |
| **C (firmware)** | Clamps to `int16` range on **encode** only | `Drivers/Device_Drivers/Src/ephorus_driver.cpp:270-271` (`clampToI16`) |

- **Area:** CAN. **Frame:** `0x186/0x196/0x1A6/0x1B6` bytes 4-7. **Severity: LOW.**
- Plant behavior converges (both cap at ±64 Nm). The **reported/decoded command
  value** differs for any command above 64 Nm, which matters for diagnostics and
  for any test that asserts on the decoded limit rather than on the resulting
  torque. Also note the firmware **truncates** toward zero on encode
  (`(int32_t)(value / scale)`) while both models decode with round-half-away
  (`std::llround` / MATLAB `round`) — sub-count, no practical effect.

---

## SUSPECTED (could not fully verify)

### SUSP-1 — UPDATED 2026-08-02: `0x400` bits 48/49 ARE now computed in the HIL host core

**This finding predates the CAN decoder-bank-threading commits (`a308a7e`,
`d5bcb8d`, `a5dc937`, `97bdea2`, `3bdb6e1`) and the GUI dc-link/load-torque
wiring fix, and is stale.** `+inverterhil/stepModel.m` now derives both bits
directly from `cal.dcLinkMinimumV` and the per-pair DC-link voltage:
`systemStatus.dcLink12AboveMinimum = dcLink12V > cal.dcLinkMinimumV` and the
same for pair 3/4, immediately before `inverterhil.packStatusCycle` is called.
`+inverterhil/packSystemStatus.m:21-24` packs the two logicals into `0x400`
bits 48/49 exactly as this finding originally described; the producer is no
longer missing.

`dcLink12V`/`dcLink34V` themselves were, until the GUI-tunable wiring fix,
hardcoded to `+inverterhil/defaultPlantInput.m`'s constant 400 V for every
channel — so the bits were computed, but from a value the operator could not
change. `hil_cmd_dc_link12_v` and `hil_cmd_dc_link34_v` (GUI Command
Parameters) now route through `inverterhil.stepModel`'s `externalInputs`
argument into `plantInput.channels(*).dcLinkV`, so an operator-commanded
DC-link voltage genuinely changes both the plant input and these two wire
bits, matching what SIL derives from its own (numerically different, see
CONF-4) 50 V threshold.

The threshold *value* divergence (350 V HIL/firmware vs 50 V SIL) remains
exactly as CONF-4 describes; only the "is anything computed at all" question
this finding raised is resolved.

### SUSP-2 — APPS disagreement threshold: firmware 20 %, SIL registry 10 %, HIL absent

`Core/Src/driverInputs.cpp:289` returns `diff <= 0.20f` — directly under its own
comment at `:288` saying *"10% threshold for now"*. SIL's registry pins the FSAE
value at 10 % (`sil/registry/params.hpp:309`, `APPS_FSAE_DISAGREE_PCT = 0.10`,
citing EV.5.5 / T11.8). This is an A-registry vs C-firmware disagreement inside
the VC repo, marked suspected because I did not locate the SIL scenario that
consumes the constant and so cannot state whether SIL currently asserts on it or
tolerates it. **The HIL has no APPS plausibility model at all**, so it cannot
adjudicate — a coverage gap worth closing given this is an FSAE rule item.

---

## Verified as matching (no divergence)

Checked byte-for-byte and found identical across all three; recorded so the
negative results are not re-derived later.

| Item | Evidence |
| --- | --- |
| All 13 CAN IDs (`0x186/0x196/0x1A6/0x1B6`, `0x383/0x385/0x393/0x395/0x3A3/0x3A5/0x3B3/0x3B5`, `0x400`) | `ephorus_driver.hpp:10-28` = `ephorus_model.cpp:109-122` = `protocol.m:4-15` |
| Little-endian 64-bit payload packing, DLC 8, standard non-remote frames only | `ephorus_driver.cpp:68-91,217-219`; `ephorus_model.cpp:13-27,163-165`; `decodeControlFrame.m:16-33` |
| Control flag bits 0-3 (enable / resetError / ascAllowed / currentMode) | `ephorus_driver.hpp:41-49`; `ephorus_model.cpp:170-173`; `decodeControlFrame.m:50-53` |
| Control speed setpoint: `int16` at bit 16 | `ephorus_driver.hpp:51`; `ephorus_model.cpp:174`; `decodeControlFrame.m:54` |
| 3X3 bits 0-1 state, 2 ready, 3 derating, 4-15 u12 max current @1/32 Arms, 16-27 s12 actual torque @1/32, 28-39 s12 setpoint torque @1/32, 40-51 s12 motor temp @1/8 | `ephorus_driver.hpp:68-95`; `ephorus_model.cpp:552-566`; `packStatus3X3.m:17-27` |
| 3X5 layout: four s12 currents @1/16 Arms at bits 0/12/24/36, `int16` speed at bit 48 | `ephorus_driver.hpp:105-113`; `ephorus_model.cpp:571-585`; `packStatus3X5.m:14-23` |
| `0x400`: u16 DC-link @1/64 V at bits 0 and 16, u16 switching freq @1/512 kHz at bit 32, flag bits 48-51 | `ephorus_driver.hpp:126-143`; `ephorus_model.cpp:588-603`; `packSystemStatus.m:15-28` |
| Status cycle **order and cadence**: the nine frames in the order `383,385,393,395,3A3,3A5,3B3,3B5,400`, one burst per 5 ms | `ephorus_model.cpp:531-538` with `EPH_STATUS_PERIOD_MS = 5` (`params.hpp:48`); `protocol.m:11-15` + `packStatusCycle.m:8-20` |
| State enum Idle 0 / Drive 1 / Error 2 / ConfigMissing 3 | `ephorus_model.hpp:23-28`; `protocol.m:17-20`; `vcStateMachine.cpp:30-31` |
| Command staleness constants: 50 ms torque-zero, 500 ms error latch | `params.hpp:61-62`; `protocol.m:29-30`; `stepChannelState.m:34-35` |
| Other inverter fault limits: DC-link >700 V / <−10 V, phase overcurrent 120 A, tracking error 10 A for 50 ms, control-enable-low 200 ms, position timeout 350 µs, control-pin torque zero 100 µs, switch shutdown 145 °C | `params.hpp:63-73`; `protocol.m:31-36`; `stepChannelState.m:216-240` |
| Reset backoff base 500 µs, cap 100 s, recovery window 50 ms, stationary 100 rpm | `params.hpp:74-77`; `protocol.m:34-36`; `defaultStateConfig.m:13-15`, `stepChannelState.m:198-201` |
| Switching frequency 10 kHz | `params.hpp:92`; `defaultCalibration.m:10` |
| Buzzer duration ~1.5 s, inside the FSAE 1-3 s window | `vcStateMachine.cpp:362` (`osDelay(1500)`); window pinned at `params.hpp:213-214` |
| RTD entry guard: `mainButton && brakeValidPct >= 0.25` | `vcStateMachine.cpp:344`; pinned at `params.hpp:208` (`BRAKE_RTD_MIN_PCT`) |

---

## Coverage not achieved, and why

1. **`inverter_hil.slx` was not simulated**, at the time of this investigation.
   Opening it outside R2024b is prohibited, so simulation was out of scope for
   a read-and-verify pass regardless. **This item's premise is now stale**: at
   the time it was written the Ephorus Channel 1-4 subsystem was a
   constant-zero placeholder, but CAN status packing, transmission, reception,
   and decode are real (see the 2026-08-02 amendment above and SUSP-1 below).
   The dead "Ephorus Channel 1-4" subsystem itself (`buildChannel`, `Load
   Demux`/`DC Link Demux`/`Fault Demux`) has since been deleted outright from
   `build_inverter_hil_model.m` (2026-08-19), along with the rest of the
   always-inert decorative architecture tree around it. No signal that
   originates in the Simulink layer rather than `+inverterhil/` was compared
   by this investigation.
2. **No joint A/B execution.** There is no shared harness between the C++ SIL
   and the MATLAB host core. CONF-3's end-to-end consequence (four inverters in
   Error vs Idle throughout the pre-RTD states) is established from source plus
   SIL's own passing conformance assertion, not from a co-simulation. A joint
   run would require building a frame-level bridge, which is out of scope for a
   read-and-verify pass.
3. **Digital pin levels were not compared electrically.** The plan declares 5 V
   DIO unverified and pending a hardware rating check
   (`inverter_hil_plan.md:222-232`), and SIL models pins logically, not
   electrically (`sil/models/pin_map.*`). There is no common basis for
   comparison — this is a spec gap, not a divergence, so it is not listed as a
   finding.
4. **The HIL GUI layer (`+inverterhilgui/`) was only skimmed.** Effort went to
   the two areas called out as priorities: CAN frames and voltages.
5. **`Drivers/CMSIS` and `Drivers/STM32*` excluded** as instructed (vendor HAL).

## Reproduction

```sh
# A - SIL (from the MFE26-VC clone)
cmake -S sil -B <build> -G Ninja -DCMAKE_BUILD_TYPE=Release -DSIL_BUILD_GUI=OFF
cmake --build <build> -j 8
<build>/sil_conformance.exe ephorus_conformance          # PASS, 0 errors
<build>/sil_runner.exe --scenario ephorus_switch_temp_xfail   # FAIL, 1 error (intentional XFAIL)

# B - HIL (from inverter_hil/)
matlab -batch "addpath(fullfile(pwd,'tests','inverter_hil')); run_inverter_hil_tests;"
# 131 Passed, 0 Failed
```

No file in either repository was modified. Nothing was committed or pushed.
