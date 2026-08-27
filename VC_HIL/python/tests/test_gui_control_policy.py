import itertools
import math
import pytest
import inverterhilgui as gui


def healthy(**updates):
    value = {"expertMode": True, "plausibilityOverride": True, "targetHealthy": True, "heartbeatOk": True, "contractResolved": True}
    value.update(updates); return value


@pytest.mark.parametrize("state", ["connected", "loaded", "running", "stopped"])
def test_interlocks_removed_policy_matrix(state):
    p = gui.controlPolicy(state, "RTD", healthy())
    assert p["expertGroupsUnlocked"] and all(p[x] for x in ("electrical", "plantParameters", "calibration", "faultInjection", "canFaults"))
    runtime = state == "running"
    assert p["pedals"] is runtime and p["digitalStimuli"] is runtime and p["sensorStimulus"] is runtime


def test_drive_and_expert_interlock_no_longer_restrict_expert_groups():
    for vcu in ("LV_ON", "ENABLE", "BUZZING", "RTD"):
        p = gui.controlPolicy("running", vcu, healthy(expertMode=False, targetHealthy=False, heartbeatOk=False, contractResolved=False))
        assert p["calibration"] and p["faultInjection"] and p["pedals"]


def test_can_driving_locks_only_pedals():
    p = gui.controlPolicy("running", "RTD", healthy(), True)
    assert not p["pedals"] and p["canDriving"] and p["digitalStimuli"] and p["calibration"]
    assert gui.controlPolicy("running", "RTD", healthy())["pedals"]


@pytest.mark.parametrize("bad", [2, math.nan, "yes", None])
def test_malformed_can_driving_fails_closed(bad):
    p = gui.controlPolicy("running", "RTD", healthy(), bad)
    assert p["reason"] == "malformed_canDriving" and not p["pedals"]


def test_disconnected_and_malformed_inputs_fail_closed():
    assert gui.controlPolicy("disconnected", "", healthy())["reason"] == "not_connected"
    assert gui.controlPolicy("bogus", "", healthy())["reason"] == "unknown_application_state"
    assert gui.controlPolicy("running", "", {})["reason"].startswith("missing_")
