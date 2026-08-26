"""Faithful in-memory backend for host tests; contains no MATLAB dependency."""

from .parameter_contract import parameterContract


class FakeTargetBackend:
    def __init__(self, available_paths=None):
        if not available_paths:
            available_paths = [entry.structPath for entry in parameterContract()]
        self.AvailablePaths = list(available_paths)
        self.Values = {path: 0 for path in self.AvailablePaths}
        self.Signals = {}
        self.FailNextCall = False
        self.AppliedOverride = None
        self.WriteCount = 0
        self.WriteLog = []
        self.InstrumentCount = 0
        self.Connected = False
        self.Loaded = False
        self.Running = False
        self.Name = "FakeTarget"
        self.ExecutionTimeS = 0.0
        self.CurrentApplication = ""

    def _fail_if_requested(self, action):
        if self.FailNextCall:
            self.FailNextCall = False
            raise RuntimeError(f"The fake target was told to fail {action}.")

    def _require_connected(self):
        if not self.Connected:
            raise RuntimeError("The fake target is not connected.")

    def connect(self):
        self._fail_if_requested("connect")
        self.Connected = True

    def disconnect(self):
        self.Connected = self.Loaded = self.Running = False

    def load(self, applicationName):
        self._fail_if_requested("load")
        self._require_connected()
        self.Loaded = True
        self.Running = False
        self.CurrentApplication = "inverter_hil"

    def start(self):
        self._fail_if_requested("start")
        self._require_connected()
        if not self.Loaded:
            raise RuntimeError("No application is loaded on the fake target.")
        self.Running = True

    def stop(self):
        self._fail_if_requested("stop")
        self.Running = False

    def reset(self):
        self._fail_if_requested("reset")
        self.Running = False
        self.ExecutionTimeS = 0.0

    def getparam(self, path):
        self._require_connected()
        if path not in self.Values:
            raise KeyError(f"The fake target does not expose {path}.")
        return self.Values[path]

    def setparam(self, path, value):
        self._fail_if_requested("setparam")
        self._require_connected()
        if path not in self.Values:
            raise KeyError(f"The fake target does not expose {path}.")
        self.Values[path] = value if self.AppliedOverride is None else self.AppliedOverride
        self.WriteCount += 1
        self.WriteLog.append((path, value))

    def getsignal(self, blockPath, port):
        self._require_connected()
        return self.Signals.get((blockPath, port), 0)

    def isConnected(self):
        return self.Connected

    def applicationState(self):
        if not self.Connected:
            return "disconnected"
        if self.Running:
            return "running"
        if self.Loaded:
            return "loaded"
        return "connected"

    def currentApplicationName(self):
        return self.CurrentApplication

    def executionTimeS(self):
        return self.ExecutionTimeS

    def targetName(self):
        return self.Name

    def availableParameters(self):
        return list(self.AvailablePaths)

    def addInstrument(self, instrument):
        self.InstrumentCount += 1

    def removeInstruments(self):
        self.InstrumentCount = 0
