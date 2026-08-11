# Outbound CAN inverter-panel disclosure plan

## 1. Status and scope

This is an implementation plan only. It proposes a display/layout change for
the `Inverters` tab and a later inbound-control display. It does not change the
decoder, formatter, Simulink model, data dictionary, generated app artifact, or
any application source in this planning phase.

The implementation target is Part 32 of
`inverter_hil/inverter_hil_plan.md`. The new document is standalone because it
adds a focused interaction design and acceptance delta to the living plan
without rewriting that plan's numbered Part 32 table. Its implementation steps
and verification language follow section 8 of the living plan.

The repository is the reconciled protocol authority for this work:

- `+inverterhil/protocol.m` owns the CAN IDs, states, and torque profiles.
- `decodeStatus3X3.m`, `decodeStatus3X5.m`, and `decodeSystemStatus.m` own
  outbound status decoding.
- `decodeControlFrame.m` owns inbound control decoding and already returns
  enable, reset-error, ASC-allowed, current mode, speed setpoint, raw torque
  limits, and both candidate torque-limit scales.
- `+inverterhilgui/formatInverterPanel.m` already formats the complete outbound
  per-inverter display snapshot.

The datasheet review was limited to section 6.2 as requested. It describes
little-endian CAN, the four inbound IDs `0x186`, `0x196`, `0x1A6`, and `0x1B6`,
the eight-byte control message, and the `3X3`/`3X5` outbound status messages
sent every 5 ms. Those observations ground the direction and terminology here;
the repository files above remain authoritative where the datasheet's torque
scale/range presentation is inconsistent with the reconciled implementation.

## 2. Current implementation facts to preserve

`inverter_hil_app.m` is a 1,778-line programmatic `uifigure` classdef. Its
`InverterFieldNames` property has exactly these 12 entries, in this order:

```text
STATE, READY, CMD AGE, TORQUE CMD, TORQUE ACT, SPEED,
Id set/act, Iq set/act, MOTOR TEMP, SWITCH TEMP, DERATING, ACTIVE FAULT
```

`createInvertersTab` creates four `INVERTER 1` through `INVERTER 4` panels in a
two-by-two outer grid. Each panel currently creates one title row, one corner
row, and one fixed-height row for every field. `refreshInverters` calls
`formatInverterPanel(app.Telemetry, channel)` and writes all 12 returned values
on every refresh. The formatter remains the only source for those values; the
layout change must not copy or re-derive its protocol logic.

The formatter's torque strings retain the raw count and both candidate
interpretations through the existing torque-formatting helper. The plan does
not add a second torque formatter or select a scale in the GUI.

The corner behavior is out of scope. The acceptance contract and this feature
request require the corner label to remain `UNVERIFIED`, with
`cornerVerified` governing that presentation, and the persistent red `TORQUE
SCALE UNVERIFIED` banner must remain untouched. A live-file review found a
pre-existing discrepancy: the current `formatInverterPanel.m` contains
`FL/FR/RR/RL` names and sets `cornerVerified` true for valid indices. The
future implementation must not silently alter that formatter as part of this
layout work; the acceptance owner must reconcile that discrepancy before
claiming G2/hard-constraint compliance. The disclosure callback and row-height
helper must not read, write, or reinterpret either corner value.

## 3. Design decision: disclosure button, not a value dropdown

The request says “dropdown” but describes an independent collapsed/expanded
disclosure per inverter. Two interpretations were considered:

1. A `uidropdown` with `Basic` and `Detailed` values could toggle row
   visibility. It would be a selector, however, and would spend scarce panel
   width on a value-editing control whose two choices duplicate the requested
   disclosure state.
2. A compact `uibutton` disclosure toggle can show `> DETAILS` when collapsed
   and `v DETAILS` when expanded. Its callback changes only that panel's row
   heights, preserving the live values and the panel's independent state.

Choose option 2. It matches the existing dense, scan-oriented console and uses
only primitives already used by the app (`makeGrid`, `makeLabel`, `makeButton`,
and `makePanel`). R2024b `uigridlayout` has no native accordion or collapsible
panel component, so the accordion must be composed from those primitives. A
push button is also clearer for the described click-to-expand behavior than a
value selector.

The hidden rows will be retained as real labels and assigned a zero row height;
they will not be destroyed or recreated on every click. This keeps the
`InverterFieldLabels(channel, field)` mapping stable, lets `refreshInverters`
continue to update all 12 fields, and avoids losing no-data or fault text when a
panel is reopened. The disclosure button must have an accessible text label in
addition to the glyph, and its state must never be communicated by color alone.

## 4. Outbound panel implementation plan

### 4.1 Collapsed and expanded contract

The default state for all four panels is collapsed. Exactly three of the 12
existing fields remain visible:

| Existing field | Formatter property | Collapsed | Expanded |
|---|---|---:|---:|
| STATE | `state` | hidden | shown |
| READY | `ready` | hidden | shown |
| CMD AGE | `commandAge` | hidden | shown |
| TORQUE CMD | `torqueCommand` | shown | shown |
| TORQUE ACT | `torqueActual` | shown | shown |
| SPEED | `speed` | hidden | shown |
| Id set/act | `idCurrent` | hidden | shown |
| Iq set/act | `iqCurrent` | hidden | shown |
| MOTOR TEMP | `motorTemperature` | shown | shown |
| SWITCH TEMP | `switchTemperature` | hidden | shown |
| DERATING | `derating` | hidden | shown |
| ACTIVE FAULT | `activeFault` | hidden | shown |

Thus collapsed is exactly `TORQUE ACT`, `MOTOR TEMP`, and `TORQUE CMD`; the
expanded state reveals the remaining nine: `STATE`, `READY`, `CMD AGE`,
`SPEED`, `Id set/act`, `Iq set/act`, `SWITCH TEMP`, `DERATING`, and `ACTIVE
FAULT`. The order of all rows remains the existing `InverterFieldNames` order.

### 4.2 Class properties and methods

The later implementation should add the following app-owned layout state and
handles to `inverter_hil_app.m`:

- `InverterExpanded`, a private logical `1x4` property initialized to
  `false(1,4)`.
- `InverterStatusGrids`, a `1x4` array of the four per-inverter grids whose row
  heights are changed by the disclosure callback.
- `InverterDisclosureButtons`, a `1x4` array of the four push buttons.
- A fixed row-index mapping from the 12 field indices to grid rows, or a small
  pure helper that returns the visibility mask and row-height decisions. The
  mapping must be derived from `InverterFieldNames`/the declared field groups,
  not duplicated as unexplained numeric literals in multiple callbacks.

`createInvertersTab` should create the disclosure button in a compact row near
the title/corner identification, then create the existing 12 field label pairs
and record the grid handles. It should apply the collapsed layout once after
construction. The panel title, canonical `INV1`-`INV4` label, corner label, and
the disclosure control must remain visible in both states.

Add a private `onInverterDisclosurePushed(app, source, ~)` callback and a
private `setInverterExpanded(app, channel, expanded)` method. The callback must
identify only its own channel, invert that element of `InverterExpanded`, update
the button text/accessibility text, and call the setter. The setter must validate
the channel and logical scalar using the established `+inverterhil`-style
validation idiom, then assign zero height to hidden field rows and the normal
compact height to shown rows. It must not mutate telemetry, protocol state,
corner state, banner state, or any target parameter.

`refreshInverters` should continue to format once per channel and update all 12
labels. It should not decide visibility and should not skip hidden labels. The
visibility setter is a layout concern; the formatter remains a pure per-channel
data concern.

If a pure helper is useful for reviewability, add one new function under
`inverter_hil/+inverterhilgui/`, such as `inverterPanelVisibility.m`, with a
`%INVERTERPANELVISIBILITY Summary` header. It should accept a validated logical
expanded flag and return the 12-element visibility mask (and, if needed, the
normal/hidden row-height values). It must use an `inverterhilgui:*` identifier
for malformed input, have no UI handles or telemetry dependency, and be tested
for both states. No helper is needed for formatting: `formatInverterPanel.m`
already computes every requested value.

### 4.3 Release-specific authoring precondition

Before any future implementation work begins, the authoring session must be
MATLAB R2024b. Edit and save `inverter_hil_app.m` and any new pure
`+inverterhilgui` helpers, then regenerate `inverter_hil_app.mlapp` by running
`build_inverter_hil_app.m` from
`C:\Program Files\MATLAB\R2024b\bin\matlab.exe -batch`, and only then run the
test suite. Do not author or save these files in R2024a or R2026a. The `.mlapp`
format and App Designer save behavior are release-specific; mixing releases can
corrupt or silently alter the thin shell. The MATLAB MCP session, which runs
R2026a, is permitted for lint only and must not save the `.mlapp` or run the
authoritative suite.

## 5. Later-phase inbound VCU-to-inverter section

This section is a proposal only and is not part of the outbound layout change.
It should be placed beneath the outbound disclosure in each inverter panel,
using the same disclosure pattern and a separate state so operators can inspect
outbound status without opening inbound control details. The future section
would show, in a compact collapsed summary, `enable`, `currentMode`, speed
setpoint, and the two raw torque-limit counts. Expansion would show `resetError`,
`ascAllowed`, the full speed setpoint, and both positive/negative torque limits
under both `1/256` and `1/512` candidate engineering scales. Raw counts must
remain visible and the unresolved-scale warning must remain visible.

The future section should use the same four-channel indexing and stable label
arrays as the outbound section, with a separate `InboundExpanded(1,4)` state.
That makes the later data binding a new snapshot-to-label operation rather than
a second redesign of the panel grid. Its display formatter should be a pure
function in `+inverterhilgui`, using the already-authoritative
`decodeControlFrame` result and the repository's error/header conventions.

### 5.1 What exists today

The inbound transport and decoder plumbing is partly present:

- `receiveControlFrame` validates and decodes each accepted standard DLC-8
  frame, stores the decoded command in a four-channel decoder bank, records
  `hasCommand`, age/count data, torque-domain status, and the last accepted raw
  payload.
- `rxObservation` exposes a fixed `4x14` numeric observation for the model
  boundary: eight raw payload bytes, `hasCommand`, accepted count, age,
  command-out-of-domain, and two bank-wide rejection fields.
- The generated model wrapper combines those four control rows with nine status
  rows into the `13x14` observation. `targetSession` reads that signal when it
  exists, and the app's existing VCU TX / HIL RX table re-decodes each retained
  payload with `decodeControlFrame` to show enable/reset/ASC/current-mode,
  speed, raw torque counts, count, age, and clamping.

### 5.2 What is missing for a real per-inverter inbound panel

The current target observation does not export the decoded command struct or
its individual decoded fields. The app therefore has no typed per-inverter
inbound snapshot parallel to the outbound `Telemetry.inverter` snapshot; it
only has the generic CAN-row data assembled from raw bytes. A later phase must:

1. Define and document a fixed, code-generation-safe inbound observation
   contract, or add a pure host-side conversion immediately after reading the
   existing raw rows. The preferred contract should preserve raw bytes and
   presence/age while exposing every decoded field and both candidate scales.
2. Ensure the conversion distinguishes never received from a legal all-zero
   frame, preserves per-channel age, and carries rejection/domain diagnostics
   without inventing values.
3. Add the inbound snapshot to the GUI telemetry contract and blank snapshot so
   a disconnected or legacy target renders honest no-data values.
4. Bind the future section to that snapshot through a pure formatter and unit
   tests, then verify the generic CAN table and the dedicated panel agree on
   the same retained frame.

No outbound GUI change in this plan may assume that inbound decoded fields are
already available. The existing generic table is useful evidence of received
bytes and a decoder check, but it is not the missing dedicated per-inverter
telemetry contract.

## 6. Acceptance-checklist delta

The future implementation should edit
`inverter_hil/docs/inverter_hil_gui_acceptance.md` in its existing table style.
Keep G1, G2, G5, and G9 as written, subject to the pre-existing corner-label
reconciliation noted in section 2. Reword the following existing G rows so
they describe visibility across the two valid states rather than assuming all
12 rows are simultaneously visible:

| Existing row | Required rewording | Verify |
|---|---|---|
| G3 | Each panel shows state, ready, and command age when expanded; their values remain current while collapsed. | manual |
| G4 | Each panel shows torque command and actual in collapsed and expanded states, including the existing raw-count/candidate-scale formatting. | manual |
| G6 | Each panel shows speed and Id/Iq when expanded. | manual |
| G7 | Each panel shows motor and switch temperatures when expanded, with the existing raw-count formatting. | manual |
| G8 | Each panel shows derating and active fault when expanded. | manual |

Add a new lettered section after G and before the existing H section:

```markdown
## N. Part 32A - Collapsible outbound status and inbound-ready panel layout

| ID | Requirement | Verify |
|---|---|---|
| N1 | Four inverter panels default to collapsed independently; each collapsed panel shows exactly TORQUE CMD, TORQUE ACT, and MOTOR TEMP from the existing 12-field contract. | manual + unittest |
| N2 | Clicking one disclosure button expands only that inverter and reveals STATE, READY, CMD AGE, SPEED, Id set/act, Iq set/act, SWITCH TEMP, DERATING, and ACTIVE FAULT. | manual + unittest |
| N3 | Repeated refreshes update all 12 formatter-backed labels without resetting any panel's expansion state. | unittest |
| N4 | Disclosure state is layout-only and does not alter telemetry, corner labels, the UNVERIFIED presentation, or the persistent red TORQUE SCALE UNVERIFIED banner. | manual + unittest |
| N5 | R2024b App Designer primitives compose the disclosure; no native accordion is assumed, and no decorative graphics are added. | manual + lint |
| N6 | A future inbound Control section has a reserved per-inverter structure and documents that decoded fields require a dedicated telemetry contract beyond the current raw 4x14 observation. | manual + unittest |
```

The exact letter N is intentional: the existing checklist ends at M, while H
through M remain the established GUI parts and assumptions. The new section is
an acceptance delta for Part 32A, not a replacement for Part 33 CAN-table
requirements.

## 7. Verification and test plan

### 7.1 Focused tests to add later

Add tests under `inverter_hil/tests/inverter_hil` in the existing folder-based
style, without requiring Speedgoat hardware:

- A pure visibility-helper test verifies the 12-field mask for collapsed and
  expanded states, exactly three versus nine fields, field order, invalid-input
  rejection, and no cross-channel state coupling.
- A GUI layout test (or the narrowest available app construction test) verifies
  four independent disclosure buttons, all four default collapsed states, one
  channel expanding without changing the others, and refresh preserving state.
- Extend the existing formatter isolation coverage only if needed to assert that
  the layout path passes each channel through unchanged; do not duplicate or
  alter `formatInverterPanel` protocol behavior.
- A future inbound test should use a golden control frame and verify agreement
  between the raw observation, `decodeControlFrame`, the generic CAN row, and
  the proposed dedicated inbound formatter. It must cover a legal all-zero
  payload, never-received state, age, rejection, and both torque candidates.

Preserve the existing G9 rule: per-inverter formatting remains a pure function,
has no cross-channel leakage, uses the established validation idiom and
`inverterhilgui:*` identifiers, and follows the `%FUNCNAME Summary` header
convention.

### 7.2 R2024b batch verification sequence

The authoritative suite is always run from a shell with R2024b, never through
the R2026a MATLAB MCP. Before implementation changes, record the baseline with:

```powershell
& 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "cd('C:\Users\aniru\OneDrive - McGill University\mfe\HIL'); run('inverter_hil/tests/inverter_hil/run_inverter_hil_tests.m');"
```

The documented baseline is 66 passed and 1 failed of 67. The one failure is the
pre-existing unrelated `TestModelArtifacts/executionAndDictionaryAttachmentAreExact`
failure caused by the model's `speedgoat.tlc` versus the test's expected
`slrealtime.tlc`; it must not be fixed as part of this feature and must not get
worse.

The future implementation order is:

1. Edit `inverter_hil_app.m` and, only if justified by the pure visibility
   contract, add the new helper under `inverter_hil/+inverterhilgui/`.
2. Under the same R2024b MATLAB executable, regenerate the `.mlapp` through
   `build_inverter_hil_app.m`:

   ```powershell
   & 'C:\Program Files\MATLAB\R2024b\bin\matlab.exe' -batch "cd('C:\Users\aniru\OneDrive - McGill University\mfe\HIL\inverter_hil'); build_inverter_hil_app(true);"
   ```

3. Run the complete authoritative suite again with the first command.
4. Confirm the new focused tests are discovered, the 66 previously passing
   tests still pass, and the same one unrelated baseline failure remains the
   only failure. Also run the permitted R2026a MCP lint only if needed; it must
   not save the `.mlapp`, edit an authoritative artifact, or replace the
   R2024b suite.
5. Perform the manual acceptance checks for collapsed/expanded visibility,
   one-panel independence, refresh persistence, corner/banner invariants, and
   generated-app instantiation under R2024b.

No implementation step should touch `inverter_hil.slx`, any `.sldd`,
`+inverterhil`, the generated real-time build, or unrelated workspace content.
