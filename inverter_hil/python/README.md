# Inverter HIL Python host layer

This directory is an additive Python port of the MATLAB host-side code.  It
does not replace the Simulink model or any target-generated MATLAB code.

The public packages are `inverterhil` (host protocol helpers),
`inverterhilgui` (session, policy, formatting, and backends), and `sensors`.
Python 3.10 or newer is supported.

## Backends

`FakeTargetBackend` is an in-memory test double and needs no MATLAB install.
`MatlabEngineBackend` is the only real-target route.  It calls R2024b's
`slrealtime` API through MATLAB Engine; it does not implement A2L, XCP, or a
private socket protocol.

The MATLAB `addInstrument` argument is a MATLAB object.  Python callers should
instead create a `MatlabInstrumentSubscription` containing signal selections;
the backend materializes the MATLAB `slrealtime.Instrument` and keeps it alive
until `removeInstruments`.  A pre-existing Engine-side MATLAB object can also
be passed through, but ordinary Python objects cannot faithfully impersonate a
MATLAB handle object.

## Safety

`hardware_smoke_readonly.py` contains only the approved read-only target calls:
connect/status queries, candidate-parameter probing, and getparam round trips.
It intentionally has no write/lifecycle-changing command-line option.

The paths and output ports read by `TargetSession` are centralized in
`inverterhilgui.model_schema`.  They are a versioned host/model ABI: changing a
model block path, port, or observation shape invalidates that schema.

The task description calls `parameterContract.m` a 41-entry declaration.  At
the specified HEAD (`36f99bd`) it contains 44 `entry(...)` declarations.  This
port intentionally carries all 44 so it cannot silently discard current model
controls.

`decodeStatus3X3.m` is target-generated and was explicitly outside the portable
bucket.  Consequently `TargetSession.readLiveIo()` preserves the raw 9x8 TX and
13x14 RX matrices but does not duplicate 3X3 decoding into Python.  The portable
3X5 and system-status decoders remain available in `inverterhil`.

Run tests from this directory with `python -m pytest`.
