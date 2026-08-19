# Decision 16 findings

Date: 2026-07-31
Release: R2024b (MATLAB 24.2), Simulink Real-Time 24.2, Speedgoat blockset 10.0.1.1

## Question

Plan open decision 16: *"Whether Simulink Real-Time R2024b supports independent
field-level `setparam` updates. If not, use separately tunable scalar
parameters."*

## Answer

**No. Use separately tunable flat scalars.** The flat backing in
`+inverterhilgui/parameterContract.m` is the one to keep.

## How this was determined without a compiler or a target

No C compiler is installed on this machine (`mex.getCompilerConfigurations('C',
'Installed')` returns 0), so no real-time application can be linked here. That
does not block the question, because the set of addressable parameters is fixed
at **code generation**, not at link or download time. `slbuild` with
`GenCodeOnly` produces the parameter metadata that `getparamlist` and `setparam`
resolve names against.

`build_decision16_spike.m` declares the same logical quantity three ways, each
referenced by a real block so nothing is pruned:

| Group | Shape | Result |
|---|---|---|
| A | 8 flat scalars | 8 separate entries |
| B | 4 scalar bus-typed structs | 4 entries, one per struct |
| C | 1x4 bus-typed struct array | 1 entry |

Group C built without complaint, so an array of buses from a `Constant` block is
*not* the obstacle.

## Evidence

`decision16_spike_sg_rtw/decision16_spikecal.mat` holds exactly **13** parameter
entries — `1 array + 4 structs + 8 scalars` — matching the number of
`Simulink.Parameter` objects, not the number of fields. Each struct is one entry:

```
name: 'spk_struct_ch3'    dt: 'SpkChannelBus'    fcn: 'get_spk_struct_ch3'
```

There is no `spk_struct_ch3.torque` entry and no `spk_array(1)` entry. The
generated `RTE_Param_Service_T` confirms the same layout — whole structs and
whole arrays, with one accessor per parameter:

```c
struct RTE_Param_Service_T {
  SpkChannelBus spk_array[4];
  SpkChannelBus spk_struct_ch1;
  ...
  real_T spk_flat_ch1_torque;
};
```

The API signature agrees. `setparam(target, block_path, parameter_name, value)`
documents `parameter_value` as accepting a **structure** and `parameter_name` as
a name, not a field path. Structs are written whole.

Note this is the SLRT **RTE parameter service**, not the classic C API table —
`rtwCAPI_ModelParameters` is emitted empty (`numModelParameters` is 0), so
reading that table alone would have wrongly suggested nothing is tunable.

## Consequence for the GUI

Field-level writes would have to become read-modify-write of the whole struct,
which is not atomic against the 1 ms model step. A torque change on channel 2
could write back a stale `enable` for channel 3 — one operator action silently
perturbing a different inverter. Flat scalars avoid this entirely.

## Consequence for the parameter contract

Two concrete implications for `+inverterhilgui/`:

1. **The struct backing can never resolve.** `structPath` values are dotted
   (`hil_cmd.pedals.throttle`, `hil_cmd.inverter(1).load_nm`). Those names will
   not appear in the registry — only `hil_cmd` would. `discoverContract.m` will
   therefore always select the flat backing. The dual-path design did its job:
   no callback changes are needed, and the struct paths are now dead weight that
   can be retired.

2. **`splitPath` is correct for the flat case, and only for it.**
   `slrealtimeBackend.m:134` splits on the last `/`; flat names contain no `/`,
   so it yields `blockPath = ''` and the bare name — exactly the documented
   `setparam(target, '', name, value)` shape. It would mis-split a dotted struct
   path, but since those never resolve, that path is unreachable.

## Still open

The model does not yet expose these tunables at all: `build_inverter_hil_model.m`
builds every Constant from literal values (lines 189-266), so none of the 33
contract names are referenced by any block and none would survive codegen.
Wiring the dictionary parameters into the model is the prerequisite for any
GUI-to-target test.

`confirm_decision16_on_target.m` re-checks all of the above against real
hardware. It needs a target computer and a compiler, but no VCU.

## Status of this directory

Throwaway. Not part of the inverter HIL deliverable; never deploy
`decision16_spike` alongside `inverter_hil`.
