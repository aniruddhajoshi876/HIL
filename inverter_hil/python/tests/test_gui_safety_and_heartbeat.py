import math
import pytest
import inverterhilgui as gui


def healthy(**updates):
    value = {"applicationRunning": True, "targetConnected": True, "applicationLoaded": True,
             "ioHealthy": True, "armed": True, "heartbeatAgeS": .1, "heartbeatTimeoutS": 3.0}
    value.update(updates); return value


def test_heartbeat_wrap_and_expiry():
    first = gui.heartbeatState({"counter": 4294967295, "lastUpdateS": 10.0}, 10.1, .5)
    assert first["counter"] == 0 and not first["expired"]
    stalled = gui.heartbeatState({"counter": 10, "lastUpdateS": 1.0}, 5.0, 3.0)
    assert stalled["expired"] and stalled["reason"] == "heartbeat_expired"


def test_heartbeat_fails_closed_on_missing_and_bad_clock():
    assert gui.heartbeatState({}, 1, 3)["expired"]
    assert gui.heartbeatState({"counter": 1, "lastUpdateS": 2}, 1, 3)["reason"] == "host_clock_went_backwards"
    no_previous = gui.heartbeatState({"counter": 1, "lastUpdateS": math.nan}, 1, 3)
    assert no_previous["counter"] == 2 and no_previous["expired"]


def test_healthy_fallback_and_removed_armed_gate():
    assert not gui.safeFallbackPlan(healthy())["applyFallback"]
    assert not gui.safeFallbackPlan(healthy(armed=False))["applyFallback"]


@pytest.mark.parametrize("changes,reason", [
    ({"targetConnected": False}, "target_disconnected"), ({"applicationLoaded": False}, "application_unloaded"),
    ({"applicationRunning": False}, "application_stopped"), ({"ioHealthy": False}, "io_unhealthy"),
    ({"heartbeatAgeS": 4}, "heartbeat_expired")])
def test_unhealthy_conditions_fall_back(changes, reason):
    plan = gui.safeFallbackPlan(healthy(**changes))
    assert plan["applyFallback"] and plan["reason"] == reason
    assert plan["analogV"] == [0] * 4 and plan["digital"] == [False] * 8


def test_lifecycle_transitions_and_allowed_actions():
    assert gui.connectionState("disconnected")["allowed"]["connect"]
    assert gui.connectionState("disconnected", "connect")["state"] == "connecting"
    assert gui.connectionState("connecting", "connectSucceeded")["state"] == "connected"
    assert gui.connectionState("connected", "loadSucceeded")["state"] == "loaded"
    assert gui.connectionState("loaded", "startSucceeded")["state"] == "running"
    assert gui.connectionState("running", "stopSucceeded")["state"] == "stopped"


def test_lifecycle_and_session_fail_closed():
    assert not gui.connectionState("unknown")["valid"]
    rejected = gui.connectionState("running", "start")
    assert not rejected["valid"] and rejected["state"] == "running"
    backend = gui.FakeTargetBackend(); session = gui.TargetSession("FakePC", backend)
    assert session.start()["reason"] == "action_not_allowed" or session.start()["reason"] == "not_connected"
    assert session.connect()["success"]
    backend.FailNextCall = True
    failed = session.stop()
    assert not failed["success"] and session.State == "error"


def test_host_timeout_matches_target_calibration_cap():
    assert gui.hostHeartbeatTimeout() == 3.0
