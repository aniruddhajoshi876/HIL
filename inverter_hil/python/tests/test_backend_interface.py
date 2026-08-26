from inverterhilgui import FakeTargetBackend
from inverterhilgui.matlab_engine_backend import MatlabEngineBackend


REQUIRED = {
    "connect", "disconnect", "load", "start", "stop", "reset",
    "getparam", "setparam", "getsignal", "isConnected", "applicationState",
    "currentApplicationName", "executionTimeS", "targetName",
    "availableParameters", "addInstrument", "removeInstruments",
}


def test_both_backends_supply_all_17_methods():
    assert len(REQUIRED) == 17
    assert all(callable(getattr(FakeTargetBackend, name, None)) for name in REQUIRED)
    assert all(callable(getattr(MatlabEngineBackend, name, None)) for name in REQUIRED)


class StubEngine:
    def __init__(self): self.probed = []
    def slrealtime(self, name, nargout=1): return object()
    def getparam(self, target, block, name, nargout=1):
        self.probed.append((block, name))
        if name == "hil_cmd_pedals_throttle": return .25
        raise RuntimeError("missing")


def test_real_backend_discovery_probes_declared_candidates_without_metadata_introspection():
    engine = StubEngine(); backend = MatlabEngineBackend("Fake", engine=engine)
    assert backend.availableParameters() == ["hil_cmd_pedals_throttle"]
    assert ("", "hil_cmd.pedals.throttle") in engine.probed
    assert ("", "hil_cmd_pedals_throttle") in engine.probed
    assert len(engine.probed) == 88
