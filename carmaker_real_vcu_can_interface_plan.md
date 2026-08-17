# CarMaker - real-VC CAN interface port and gap analysis

## 0. Scope, labels, and recommendation

**Confirmed - scope.** This plan targets only the real VCU and the existing `inverter_hil` bus on IO614 channel 1 / connector B: standard HS CAN at 1 Mbaud. HIL transmits `0x383 0x385 0x393 0x395 0x3A3 0x3A5 0x3B3 0x3B5 0x400`; it receives real-VC IDs `0x186 0x196 0x1A6 0x1B6`. Local source: `PINOUTS.md:373-409`; `inverter_hil/+inverterhil/protocol.m:4-14`.

**Confirmed - labels.** Every substantive conclusion is marked **Confirmed**, **Proposed design not built**, or **Open question**. Confirmed behavior is traced to source lines or to a cited CarMaker manual passage. Proposed items are not current behavior.

**Confirmed - current integration state.** CarMaker and `inverter_hil` are separate today; CarMaker does not talk to Speedgoat. Local source: `speedgoat_ipg_integration.md:3-21`.

**Proposed design not built - recommendation.** First prove CarMaker RBS through a supported physical CAN adapter as a third node on the existing channel-1 bus. Let CarMaker passively decode the existing VC control and HIL status frames. Add only one CarMaker-to-HIL pedal-demand frame plus a timeout-safe CAN-versus-GUI selector. Do not duplicate telemetry already on the bus. Full parity remains blocked until authoritative real-VC state and pedal-plausibility results are published; master neither receives nor computes those semantics.

**Open question - largest gate.** The manuals document an active CarMaker-side physical CAN channel, but the installed adapter/platform/license is unconfirmed. IO614 on Speedgoat does not satisfy that CarMaker-side requirement. UsersGuide_HIL.pdf, section 4, pp. 53-56, 58; section 4.5.2 "CAN", p. 68.

## 1. Evidence reviewed and discrepancies

**Confirmed - historical design.** The complete historical `virtual-vcu/docs/carmaker_speedgoat_interface.md` was read with `git show` because it is absent here. Its section 5 boundary is: 0-100% throttle/brake into the bench; decoded torque request, VCU state/stateId/enable, validity/plausibility, and inverter/DC-link observations back. Local source: `virtual-vcu/docs/carmaker_speedgoat_interface.md:160-173` (historical `virtual-vcu` tree).

**Confirmed - historical RBS finding.** RBS imports CANdb/DBC, distinguishes real and simulated ECUs, maps signals to Data Dictionary quantities/functions, and uses one active physical CAN channel. The prior research did not establish a CarMaker-to-Speedgoat deployment or virtual-CAN tunnel. UsersGuide_HIL.pdf, section 4, pp. 53-56, 58, 68; section 3.6.4, p. 51. Local source: `virtual-vcu/docs/carmaker_speedgoat_interface.md:27-43,75-110` (historical tree).

**Confirmed - XCP practical constraint.** Project-supplied bench evidence says the installed XCP setup produced MEASUREMENT/DAQ reads but not CHARACTERISTIC writes. This motivates CAN command-path research; it does not prove RBS hardware support.

**Confirmed - DBC discrepancy.** Master/CAN-interface has no production inverter DBC; `rg --files -g ''*.dbc''` finds only unrelated `tests/io614_can_visibility_test.dbc`. The historical `virtual-vcu/config/MFE26_Inverter.dbc` describes the four control and nine status frames. Local source: `virtual-vcu/config/MFE26_Inverter.dbc:50-161` (historical tree).

**Confirmed - additional collision set.** The current channel-1 model also transmits sensor IDs `0x034`, `0x032`, and `0x2B0`; an ID audit must include them. Local source: `inverter_hil/build_inverter_hil_model.m:722-789`.

## 2. What master already does

### 2.1 Real-VC command receive

**Confirmed - accepted frames.** `decodeControlFrame` accepts only standard, non-remote, DLC-8 frames at the four control IDs and rejects other IDs/malformed frames. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:16-47`.

**Confirmed - decoded fields.** Each accepted frame yields per-inverter enable, reset, ASC, current-mode, signed speed setpoint, signed positive/negative torque-limit counts, and 1/256 and 1/512 Nm interpretations. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-66,69-82`.

**Confirmed - scale.** The selected and verified control scale is 1/256 Nm/count; 1/512 remains only as a known-not-the-answer test profile. Local source: `inverter_hil/+inverterhil/protocol.m:21-50`.

**Confirmed - retention/observation.** Accepted commands retain typed fields and exact wire bytes. The deployed public observation is a 4x14 numeric matrix containing raw payload, presence/count/age, out-of-domain, and rejection data--not independently named torque/state/plausibility wires. Local source: `inverter_hil/+inverterhil/receiveControlFrame.m:23-39`; `inverter_hil/+inverterhil/rxObservation.m:1-48`.

**Confirmed - model use.** `stepModel` forwards all decoded command bits and converts torque limits using the selected calibration. Invalid sign pairs are clamped into the plant domain and flagged. Local source: `inverter_hil/+inverterhil/stepModel.m:94-144,166-210`.

**Confirmed - deployed cadence.** One unfiltered FIFO frame is drained per 1-ms tick; retained control payloads are re-decoded before the 5-ms state/plant/status step. Local source: `inverter_hil/build_inverter_hil_model.m:645-715,1000-1058,1095-1189`.

### 2.2 Inverter state/status

**Confirmed - state identity.** Master computes per-inverter Idle, Drive, Error, or Config Error plus ready, torque authority, timeouts, and faults. This is HIL inverter-emulator state, not real-VC state. Local source: `inverter_hil/+inverterhil/protocol.m:16-19`; `inverter_hil/+inverterhil/stepSystemState.m:22-60`; `inverter_hil/+inverterhil/stepChannelState.m:327-343`.

**Confirmed - torque behavior.** The plant consumes the VC's positive/negative limits, intersects them with model/current/thermal limits, derives a speed-controller setpoint, and produces actual torque. Master does not reproduce the virtual VCU's single pedal-derived torque formula. Local source: `inverter_hil/+inverterhil/stepPlant.m:21-102,167-225`.

**Confirmed - transmitted fields.** Each `3X3` frame carries state, ready, derating, current limit, actual torque, torque setpoint, and temperatures. Each `3X5` carries d/q currents and speed. `0x400` carries two DC-link voltages, switching frequency, above-minimum flags, and control-enable/disable mirrors. Local source: `inverter_hil/+inverterhil/packStatus3X3.m:4-30`; `inverter_hil/+inverterhil/packStatus3X5.m:4-24`; `inverter_hil/+inverterhil/packSystemStatus.m:4-29`.

**Confirmed - ownership/cadence.** Nine standard status frames are transmitted by IO614 channel 1 every 5 ms, subject to individual transmit gates. Local source: `inverter_hil/build_inverter_hil_model.m:796-845`; `inverter_hil/+inverterhil/statusTransmitMask.m:1-23`.

**Confirmed - status observation.** `receiveStatusFrame` and `statusObservation` only retain raw matching frames plus presence/count/age for GUI observation; they do not create new semantics. Local source: `inverter_hil/+inverterhil/receiveStatusFrame.m:1-15`; `inverter_hil/+inverterhil/statusObservation.m:1-16`.

### 2.3 Pedal stimulus

**Confirmed - named inputs.** Master creates `hil_cmd_pedals_throttle` and `hil_cmd_pedals_brake` as scalar 0-1 parameters. Local source: `inverter_hil/build_inverter_hil_model.m:76-95`.

**Confirmed - direct routing.** Those entries feed `Pedal Voltage Calibration` directly; its outputs feed IO183 AO01-AO04. Master has no `hil_cmd_xcp_pedals_active`-style selector. Local source: `inverter_hil/build_inverter_hil_model.m:881-912`; `PINOUTS.md:218-225`.

## 3. Boundary port/gap table

| Boundary | Classification and master evidence | CAN consequence |
|---|---|---|
| Throttle/brake demand | **Confirmed -** named 0-1 GUI-owned inputs directly drive existing voltage calibration/AO. Local source: `inverter_hil/build_inverter_hil_model.m:89-90,881-912`. | **Proposed design not built -** decode scaled CAN fields, validate freshness, normalize once, and select before unchanged calibration. |
| Decoded torque request | **Confirmed -** no virtual-VCU single value exists. Closest authoritative inputs are four VC positive/negative limits; typed values are internal and raw bytes are observable. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:54-60`; `inverter_hil/+inverterhil/stepModel.m:180-210`; `inverter_hil/+inverterhil/rxObservation.m:17-24`. | **Proposed design not built -** shared-bus RBS maps existing `TorqueLimitPositive/Negative`. Do not invent a scalar aggregation. |
| VCU state/stateId | **Confirmed -** absent from accepted VC format; available state is inverter state. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-62`; `inverter_hil/+inverterhil/protocol.m:16-19`. | **Open question -** real VC must publish an authoritative state; inverter state cannot be relabeled. |
| Enable | **Confirmed -** per-inverter VC enable exists; inverter ready/state also exists. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-53`; `inverter_hil/+inverterhil/packStatus3X3.m:16-25`. | **Proposed design not built -** map distinctly as `vcuCommandEnable[i]` and `inverterReady[i]`. |
| `valid` | **Confirmed -** no virtual-VC pedal-valid semantic. Master has only transport/decoder freshness and domain facts. Local source: `inverter_hil/+inverterhil/rxObservation.m:17-35`. | **Open question -** publish VC validity or clearly rename a weaker proxy `canCommandFresh`. |
| `appsPlausible` | **Confirmed -** not decoded/received/computed. `hil_cmd_pedals_plausibility_override` is an operator command, not feedback. Local source: `inverter_hil/build_inverter_hil_model.m:94-95,1359-1363`; `inverter_hil/+inverterhil/decodeControlFrame.m:49-62`. | **Open question -** requires a real-VC-owned feedback signal. |
| `brakePlausible` | **Confirmed -** not decoded, received, or computed. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-62`; `inverter_hil/+inverterhil/rxObservation.m:17-24`. | **Open question -** requires a real-VC-owned feedback signal. |
| DC-link 12/34 | **Confirmed -** pair inputs feed the plant and are packed into `0x400`. Local source: `inverter_hil/build_inverter_hil_model.m:105-108,1147-1165`; `inverter_hil/+inverterhil/stepModel.m:219-230`. | **Proposed design not built -** read existing `0x400`; no duplicate frame. |
| Inverter ready | **Confirmed -** four ready bits are packed into existing `3X3` frames. Local source: `inverter_hil/+inverterhil/packStatus3X3.m:13-25`. | **Proposed design not built -** map four bits; define any aggregate separately. |
| Inverter fault | **Confirmed -** no explicit bit with this name; two-bit state distinguishes Error/Config Error. Local source: `inverter_hil/+inverterhil/protocol.m:16-19`; `inverter_hil/+inverterhil/packStatus3X3.m:9-19`. | **Proposed design not built -** define `fault := state in {Error, Config Error}` only if that lossy summary is accepted. |

**Confirmed - torque conclusion.** The real VC already interprets pedals and sends four inverter command frames. Master decodes limit pairs, then derives HIL torque setpoint/actual. It does not freshly compute the historical virtual-VCU value. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-60`; `inverter_hil/+inverterhil/stepModel.m:166-213`; `inverter_hil/+inverterhil/stepPlant.m:21-102`.

**Open question - CarMaker torque input.** The vehicle-dynamics owner must choose four requested limits, four HIL setpoints, four actual torques, or a documented aggregate. The manuals document mapping, not this project-specific insertion. ProgrammersGuide.pdf, section 6.3, pp. 228-234.

## 4. CAN topology and frame contract

### 4.1 Recommended shared bus

**Proposed design not built - topology.** Join a supported CarMaker/HIL physical CAN channel as a third node, standard 11-bit at 1 Mbaud, while preserving grounding and exactly two end terminators.

**Confirmed - manual basis.** RBS imports DBC, classifies ECUs real/simulated, maps signals, and selects an active physical CAN channel. If otherwise unused, `IO.c` initialization and a rebuilt CarMaker executable are documented. UsersGuide_HIL.pdf, section 4, pp. 53, 55-56; section 4.5.2, p. 68.

**Confirmed - limitation.** The manuals do not make CarMaker vCAN an external tunnel or let it directly use IO614. UsersGuide_HIL.pdf, section 3.6.4, p. 51; section 4.5.2, p. 68.

**Proposed design not built - ownership.** CarMaker receives but never transmits the existing inverter or sensor IDs. It alone transmits one new standard DLC-8 `CarMakerPedalDemand` frame, provisionally `0x500`, containing throttle, brake, active, alive counter, and integrity/reserved fields.

**Open question - allocation.** `0x500` does not collide with IDs instantiated by this HIL model, but that is not a vehicle-wide proof. Audit the complete database/live bus before reservation. Local source for known IDs: `inverter_hil/+inverterhil/protocol.m:4-14`; `inverter_hil/build_inverter_hil_model.m:768-816`.

**Proposed design not built - telemetry.** Add no duplicate torque/state/ready/DC-link frames on the shared bus. RBS can map existing traffic. If the VC later publishes VCU state/plausibility, provisionally allocate a separate `CarMakerVcuObservation` (candidate `0x501`) only after its authoritative source and vehicle-wide ID are approved.

### 4.2 Dedicated CarMaker-Speedgoat CAN alternative

**Proposed design not built - alternative.** Another IO614 channel could isolate CarMaker from the real bus without importing any virtual-VCU model. This is a new physical interface, not the old virtual channel.

**Confirmed - current gap.** Master enables only channel 1; channels 2-4, read, and writes are disabled/not configured for this role. Local source: `inverter_hil/build_inverter_hil_model.m:645-682,781-816`; `PINOUTS.md:375-389`.

**Proposed design not built - bridge cost.** Isolation requires new IO614 setup/read/write blocks, harness/termination, named/flattened signals, and a bridge. A candidate separate-bus set is `0x500` pedals, `0x501` four positive limits, `0x502` four negative limits, `0x503` state/enable/validity bits, and `0x504` DC-link/ready/fault. These are placeholders, not allocations.

**Proposed design not built - choice.** Prefer the shared-bus proof because it uses the real wire contract and avoids a telemetry bridge. Choose isolation only if safety, loading, hardware support, or policy prohibits the third node.

## 5. Pedal ownership and failure behavior

**Proposed design not built - receiver.** Add a separate 1-ms decoder/retainer for `CarMakerPedalDemand`; keep `decodeControlFrame` strict for Ephorus IDs.

**Proposed design not built - selector.** Retain CAN throttle/brake plus computed activity, then select CAN versus existing GUI immediately before `Pedal Voltage Calibration`. All calibration and AO wiring remains unchanged.

**Proposed design not built - atomic authority.** CAN owns both pedals only when active is asserted, counter/integrity passes, and age is below the agreed timeout. Otherwise both leave CAN ownership together.

**Proposed design not built - range.** Put 0-100% engineering units in DBC/RBS, validate at one boundary, then normalize once to existing 0-1 inputs.

**Open question - fallback.** Decide zero hold, immediate GUI fallback, or operator-armed GUI fallback. Immediate pickup of stale slider positions can step demand; the historical XCP automatic-reversion decision should not be copied without reviewing physical-CAN failure behavior.

## 6. Is RBS now viable?

**Confirmed - documented capability.** RBS supports DBC import, real/simulated ECU assignment, Data Dictionary mapping with conversions, cyclic/event transmission, counters/CRC hooks, and physical channel selection. UsersGuide_HIL.pdf, section 4, pp. 53, 55-62; section 4.9, pp. 73-75.

**Confirmed - unchanged dependency.** It still needs supported CarMaker-side physical CAN I/O; Speedgoat IO614 alone is insufficient. UsersGuide_HIL.pdf, section 4.5.2, p. 68.

**Proposed design not built - revised assessment.** RBS is more relevant because CarMaker can consume actual real-VC/HIL frames, removing the need for a virtual-VCU bridge. It is conditionally viable, not confirmed, until physical CarMaker CAN works.

**Proposed design not built - proof rule.** Identify adapter/runtime, activate 1-Mbaud CAN, attach safely, prove passive receipt, then transmit only the isolated pedal ID. If physical I/O cannot be activated, stop; do not substitute undocumented vCAN bridging.

## 7. DBC plan

**Confirmed - reusable definitions.** The historical DBC has the four control/nine status definitions and matching scaling: 1/256-Nm limits, enable, 1/32-Nm status torque, state/ready, and 1/64-V DC link. Local source: `virtual-vcu/config/MFE26_Inverter.dbc:71-161` (historical tree); `inverter_hil/+inverterhil/decodeControlFrame.m:49-60`; `inverter_hil/+inverterhil/packStatus3X3.m:16-30`; `inverter_hil/+inverterhil/packSystemStatus.m:14-29`.

**Proposed design not built - location.** At implementation time, review/copy it to `inverter_hil/config/MFE26_Inverter.dbc`, making the real HIL the owner instead of depending on `virtual-vcu/config/`.

**Proposed design not built - additions.** Define nodes/ownership and `CarMakerPedalDemand` fields, cycle, counter/integrity, scaling, and timeout comments. Include `0x032/0x034/0x2B0` if the file is to describe the complete channel. Add no duplicate shared-bus telemetry. Add VCU observation only when authoritative fields exist.

**Confirmed - CarMaker storage.** Generated RBS mapping/CAN information belongs under the CarMaker project's `Data/Config` and may be referenced by `ECUParameters`. UsersGuide_HIL.pdf, section 4.2, pp. 55-56; section 4.5, pp. 58-62; section 4.6, pp. 70-71; section 4.9, pp. 73-75.

## 8. Work classification

**Confirmed - reuse as-is.**

- **Confirmed -** IO614 channel-1 setup, FIFO receive, existing status writes. Local source: `inverter_hil/build_inverter_hil_model.m:645-720,796-817`.
- **Confirmed -** Strict real-VC decoding/retention and inverter state/plant/status packers. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:16-66`; `inverter_hil/+inverterhil/stepModel.m:94-230`.
- **Confirmed -** Pedal calibration and AO path after the new selector. Local source: `inverter_hil/build_inverter_hil_model.m:881-912`.

**Proposed design not built - rebuild for CAN.**

- **Proposed design not built -** Replace writable XCP characteristics with pedal CAN decode, retention, freshness, and source ownership.
- **Proposed design not built -** Replace XCP measurements with RBS mappings of existing frames.
- **Proposed design not built -** Create a production DBC and CarMaker `Data/Config` RBS setup.

**Open question - genuinely new semantic work.**

- **Open question -** Authoritative real-VC state, validity, APPS plausibility, and brake plausibility publication.
- **Open question -** CarMaker torque quantity/aggregation and detailed fault-summary contract.

## 9. Recommended sequence

1. **Open question -** identify and activate the exact supported CarMaker physical CAN hardware/license. UsersGuide_HIL.pdf, section 4.5.2, p. 68.
2. **Proposed design not built -** inventory live IDs, owners, periods, loading, grounding, and termination; reserve the pedal ID.
3. **Proposed design not built -** review the historical DBC, add ownership/pedal contract, and place the future production copy under `inverter_hil/config/`.
4. **Proposed design not built -** prove listen-only RBS decoding of all control, torque/state/ready, and `0x400` fields with zero unexpected transmissions.
5. **Proposed design not built -** unit-test a pure pedal decoder/retainer: wrong ID/DLC/type, malformed, out-of-range, stale, counter/integrity failures all fail safe.
6. **Proposed design not built -** add the source selector while preserving exact AO mapping; test ownership and timeout.
7. **Proposed design not built -** bench-test zero demand, sweeps, AO/VC response, and cable-loss fallback.
8. **Open question -** add VC-owned state/plausibility only after each field is traceable to authoritative firmware output.
9. **Proposed design not built -** validate CarMaker torque selection, units/signs, four-motor aggregation, authority, latency, and stale behavior.
10. **Proposed design not built -** design the dedicated-channel bridge only if the shared-bus proof is rejected; import no virtual-VCU machinery.

## 10. Explicit open questions and non-claims

- **Open question -** Which supported CarMaker adapter/runtime/license will host RBS?
- **Open question -** Can the real VC publish VCU state and pedal validity/plausibility, at what approved IDs/rates?
- **Open question -** Does CarMaker consume requested limits, HIL setpoints, actual torques, or an aggregate?
- **Open question -** Are provisional `0x500/0x501` free in the complete vehicle namespace?
- **Open question -** Is a third node acceptable, and what is the reviewed fallback policy?
- **Confirmed - non-claim.** No claim is made that vCAN bridges to IO614, RBS runs on Speedgoat, or supported CarMaker CAN hardware is installed. UsersGuide_HIL.pdf, section 3.6.4, p. 51; section 4.5.2, p. 68.
- **Confirmed - non-claim.** Inverter state is not VCU state; CAN freshness is not pedal validity; the GUI plausibility override is not VC feedback. Local source: `inverter_hil/+inverterhil/decodeControlFrame.m:49-62`; `inverter_hil/+inverterhil/rxObservation.m:17-24`; `inverter_hil/build_inverter_hil_model.m:94-95`.
- **Confirmed - non-claim.** No XCP, virtual-VCU, second virtual loop, binary model, or CarMaker-project change is part of this investigation.

