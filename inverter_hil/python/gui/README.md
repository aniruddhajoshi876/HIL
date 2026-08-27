# PyQt5 inverter HIL dashboard

This package is an additive PyQt5 view over `inverterhilgui`. It never chooses
the hardware backend: `python -m gui` constructs a `TargetSession` with
`FakeTargetBackend`. Production integration must inject a session explicitly.

Headless smoke test:

```powershell
$env:QT_QPA_PLATFORM='offscreen'
C:\Users\MFE-HPC\anaconda3\python.exe -m gui --smoke-test
```

The inverter tab intentionally labels 3X3 values unavailable because
`decodeStatus3X3` is target-generated and is not duplicated in Python. The raw
9x8 retained TX matrix remains visible in the CAN table after connection.
