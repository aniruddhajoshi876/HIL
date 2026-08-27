import math
import pytest
import inverterhilgui as gui


def test_double_commands_clamp():
    c = gui.parameterContract()
    assert gui.validateCommandValue(c, "pedals.throttle", .25) == {"name": "pedals.throttle", "value": .25, "accepted": True, "clamped": False, "reason": "accepted"}
    assert gui.validateCommandValue(c, "pedals.throttle", 4.5)["value"] == 1
    assert gui.validateCommandValue(c, "pedals.brake", -3)["value"] == 0


def test_integer_and_logical_type_checks():
    c = gui.parameterContract()
    assert gui.validateCommandValue(c, "can.drop_control_mask", 200)["value"] == 200
    assert gui.validateCommandValue(c, "can.drop_control_mask", 300)["value"] == 255
    assert gui.validateCommandValue(c, "can.drop_control_mask", 12.5)["reason"] == "value_not_integer"
    assert gui.validateCommandValue(c, "can.drop_control_mask", -1)["reason"] == "value_negative"
    assert gui.validateCommandValue(c, "digital.main_button", True)["value"] is True
    assert gui.validateCommandValue(c, "digital.main_button", 2)["reason"] == "value_not_logical"


@pytest.mark.parametrize("value", [math.nan, math.inf, 1 + 1j, [0.1, 0.2], {}, "high"])
def test_validation_fails_closed(value):
    assert not gui.validateCommandValue(gui.parameterContract(), "pedals.throttle", value)["accepted"]


def test_coalescer_keeps_newest_and_never_reorders():
    c = gui.SliderCoalescer(.020)
    assert c.submit(10, 0)["value"] == 10
    for value, now in ((20, .001), (30, .002), (40, .003)): assert not c.submit(value, now)["hasValue"]
    assert c.poll(.021)["value"] == 40
    assert (c.EmittedCount, c.DroppedCount) == (2, 2)


@pytest.mark.parametrize("rate", [.01, .06, math.nan])
def test_coalescer_rejects_bad_rates(rate):
    with pytest.raises(ValueError): gui.SliderCoalescer(rate)


def test_sequence_wraps_modulo_uint32():
    assert [gui.sequenceCommand(x) for x in (0, 4294967294, 4294967295)] == [1, 4294967295, 0]
    for bad in (-1, 1.5, math.nan, math.inf, 4294967296, [1, 2], "a", 1 + 1j):
        with pytest.raises(ValueError): gui.sequenceCommand(bad)


def test_audit_record_and_log_export(tmp_path):
    record = gui.auditRecord({"hostTime": "2026-07-31 12:00:00.000", "targetTimeS": 12.5,
                              "logicalName": "pedals.throttle", "targetPath": "hil_cmd.pedals.throttle",
                              "requested": .25, "applied": .25, "result": "applied", "detail": "ok"})
    assert list(record) == ["hostTime", "targetTimeS", "logicalName", "targetPath", "requested", "applied", "result", "detail"]
    assert record["requested"] == "0.25"
    log = gui.SessionLog()
    for i in range(5): log.append({"logicalName": f"pedals.throttle{i}", "requested": i, "applied": i, "result": "applied"})
    before = log.snapshot(); target = tmp_path / "log.csv"; log.export(target)
    assert log.snapshot() == before and len(target.read_text().splitlines()) == 6


def test_target_write_reports_clamp_mismatch_and_failure():
    backend = gui.FakeTargetBackend(); session = gui.TargetSession("FakePC", backend); assert session.connect()["success"]
    applied = session.write("pedals.throttle", .4)
    assert applied["success"] and applied["reason"] == "applied" and backend.WriteCount == 1
    assert session.write("pedals.throttle", 2.5)["reason"] == "clamped"
    backend.AppliedOverride = .125
    assert session.write("pedals.brake", .75)["reason"] == "mismatch"
    backend.AppliedOverride = None; backend.FailNextCall = True
    failed = session.write("pedals.throttle", .5)
    assert not failed["success"] and failed["reason"] == "write_failed" and failed["applied"] is None


def test_write_before_connection_is_refused():
    assert gui.TargetSession("FakePC", gui.FakeTargetBackend()).write("pedals.throttle", .5)["reason"] == "contract_unresolved"
