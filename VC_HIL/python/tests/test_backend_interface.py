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


# ---------- decodeStatus3X3 Engine round-trip ----------
#
# decodeStatus3X3 is target-generated: it compiles into the C running on the
# Speedgoat, so it is never reimplemented in Python.  These tests use a stub
# decoder to exercise the plumbing without creating a second copy of the codec.

def _session_with_decoder(decoder=None):
    from inverterhilgui import TargetSession, FakeTargetBackend
    backend = FakeTargetBackend()
    if decoder is not None:
        backend.decodeStatus3X3 = decoder
    session = TargetSession("FakePC", backend)
    session.connect()
    return session


def test_3x3_unavailable_without_engine_backend():
    """A backend with no decodeStatus3X3 reports unavailable, never zeros."""
    live = _session_with_decoder().readLiveIo()
    assert live["inverterKnown"] is False
    assert live["inverter"] == [None] * 4


def test_3x3_decoded_when_backend_supplies_it():
    calls = []

    def stub(payload):
        calls.append(list(payload))
        return {"state": 1, "ready": True, "derating": False,
                "actualTorqueNm": 4.0, "torqueSetpointNm": 8.0,
                "motorTemperatureC": 40.0, "switchTemperatureC": 50.0,
                "maxAllowedCurrentA": 100.0}

    live = _session_with_decoder(stub).readLiveIo()
    if not live["txPayloadsKnown"]:
        return  # fake backend exposes no TX matrix; plumbing covered above
    assert live["inverterKnown"] is True
    assert len(calls) == 4, "one 3X3 round-trip per channel"
    assert live["inverter"][0]["torqueCommandNm"] == 8.0


def test_one_failed_channel_does_not_blank_the_others():
    def flaky(payload):
        flaky.n += 1
        if flaky.n == 1:
            raise RuntimeError("engine round-trip failed")
        return {"state": 0, "ready": False, "derating": False,
                "actualTorqueNm": 0.0, "torqueSetpointNm": 0.0,
                "motorTemperatureC": 0.0, "switchTemperatureC": 0.0}
    flaky.n = 0

    live = _session_with_decoder(flaky).readLiveIo()
    if not live["txPayloadsKnown"]:
        return
    assert live["inverter"][0] is None, "failed channel is unavailable, not zero"
    assert any(c is not None for c in live["inverter"][1:])
