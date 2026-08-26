"""Real SLRT adapter through an existing MATLAB Engine installation."""

from dataclasses import dataclass
from typing import Any, Iterable

from .parameter_contract import parameterContract


@dataclass(frozen=True)
class SignalSelection:
    block_path: str
    port: int


@dataclass(frozen=True)
class MatlabInstrumentSubscription:
    """Python-native description materialized as a MATLAB Instrument handle."""
    application_name: str
    signals: tuple[SignalSelection, ...]

    @classmethod
    def from_signals(cls, application_name: str, signals: Iterable[tuple[str, int]]):
        return cls(application_name, tuple(SignalSelection(*item) for item in signals))


class MatlabEngineBackend:
    """The 17-method backend interface used by TargetSession.

    Construction starts MATLAB only when no engine object is injected.  No
    system installation or environment modification is attempted.
    """

    def __init__(self, targetName="TargetPC1", engine=None, start_options=None):
        self.Name = targetName
        if engine is None:
            try:
                import matlab.engine
            except ImportError as exc:
                raise RuntimeError(
                    "MATLAB Engine for Python is not installed for this interpreter. "
                    "Install it from the R2024b matlabroot/extern/engines/python directory."
                ) from exc
            engine = matlab.engine.start_matlab(start_options or "-nodesktop -nosplash")
        self.Engine = engine
        # R2024b restricts the package-qualified Target constructor; use the
        # same slrealtime(name) shorthand as slrealtimeBackend.m.
        self.Target = self.Engine.slrealtime(targetName, nargout=1)
        self.Instruments: list[Any] = []

    def connect(self):
        self.Engine.connect(self.Target, nargout=0)

    def disconnect(self):
        self.Engine.disconnect(self.Target, nargout=0)

    def load(self, applicationName):
        self.Engine.load(self.Target, applicationName, nargout=0)

    def start(self):
        self.Engine.start(self.Target, nargout=0)

    def stop(self):
        self.Engine.stop(self.Target, nargout=0)

    def reset(self):
        self.Engine.stop(self.Target, nargout=0)

    @staticmethod
    def _split_path(path):
        if "/" not in path:
            return "", path
        return tuple(path.rsplit("/", 1))

    def getparam(self, path):
        block_path, parameter_name = self._split_path(path)
        return self.Engine.getparam(self.Target, block_path, parameter_name, nargout=1)

    def setparam(self, path, value):
        block_path, parameter_name = self._split_path(path)
        self.Engine.setparam(self.Target, block_path, parameter_name, value, nargout=0)

    def getsignal(self, blockPath, port):
        return self.Engine.getsignal(self.Target, blockPath, float(port), nargout=1)

    def isConnected(self):
        return bool(self.Engine.isConnected(self.Target, nargout=1))

    def applicationState(self):
        if not self.isConnected():
            return "disconnected"
        if bool(self.Engine.isRunning(self.Target, nargout=1)):
            return "running"
        if bool(self.Engine.isLoaded(self.Target, nargout=1)):
            return "loaded"
        return "connected"

    def currentApplicationName(self):
        return str(self.Engine.getLastApplication(self.Target, nargout=1))

    def executionTimeS(self):
        return float(self.Engine.getExecTime(self.Target, nargout=1))

    def targetName(self):
        return self.Name

    def availableParameters(self):
        """Probe declared candidates with getparam; do not introspect metadata."""
        candidates = []
        for entry in parameterContract():
            for path in (entry.structPath, entry.flatPath):
                if path not in candidates:
                    candidates.append(path)
        paths = []
        for path in candidates:
            try:
                # Match slrealtimeBackend.m exactly: top-level candidate name,
                # empty block path, and exclusion when GETPARAM throws.
                self.Engine.getparam(self.Target, "", path, nargout=1)
                paths.append(path)
            except Exception:
                pass
        return paths

    def addInstrument(self, instrument):
        if isinstance(instrument, MatlabInstrumentSubscription):
            materialized = self.Engine.feval("slrealtime.Instrument", instrument.application_name, nargout=1)
            for signal in instrument.signals:
                self.Engine.addSignal(materialized, signal.block_path, float(signal.port), nargout=0)
            instrument = materialized
        self.Engine.addInstrument(self.Target, instrument, nargout=0)
        self.Instruments.append(instrument)

    def removeInstruments(self):
        for instrument in self.Instruments:
            try:
                self.Engine.removeInstrument(self.Target, instrument, nargout=0)
            except Exception:
                pass
        self.Instruments.clear()
