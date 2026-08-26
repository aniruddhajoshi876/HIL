import pytest
import inverterhilgui as gui


def test_contract_declares_every_current_entry_and_both_backings():
    contract = gui.parameterContract()
    assert len(contract) == 44
    assert len({x.name for x in contract}) == len(contract)
    for item in contract:
        assert item.type in {"double", "logical", "uint8", "uint16", "uint32"}
        assert item.minimum <= item.maximum
        assert item.structPath and item.flatPath and item.structPath != item.flatPath
        assert isinstance(item.required, bool) and item.group


@pytest.mark.parametrize("backing", ["struct", "flat"])
def test_single_backing_is_discovered(backing):
    contract = gui.parameterContract(); attr = backing + "Path"
    resolved = gui.discoverContract([getattr(x, attr) for x in contract])
    assert resolved.backing == backing and resolved.resolvedCount == len(contract)
    assert gui.contractEntry(resolved, "pedals.throttle").backing == backing


def test_mixed_and_struct_preference():
    contract = gui.parameterContract()
    paths = [x.structPath if i % 2 == 0 else x.flatPath for i, x in enumerate(contract)]
    assert gui.discoverContract(paths).backing == "mixed"
    both = [x.structPath for x in contract] + [x.flatPath for x in contract]
    resolved = gui.discoverContract(both)
    assert resolved.backing == "struct" and resolved.flatCount == 0


def test_missing_required_fails_and_optional_may_be_absent():
    contract = gui.parameterContract()
    paths = [x.structPath for x in contract if x.name not in {"pedals.throttle", "gui_heartbeat"}]
    with pytest.raises(RuntimeError) as caught:
        gui.discoverContract(paths)
    assert "pedals.throttle" in str(caught.value) and "gui_heartbeat" in str(caught.value)
    required = [x.structPath for x in contract if x.required]
    resolved = gui.discoverContract(required)
    assert "cal.pedals.released_v1" in resolved.missing


def test_connect_reads_target_values_and_writes_nothing():
    backend = gui.FakeTargetBackend(); backend.Values["hil_cmd.pedals.throttle"] = 0.375
    session = gui.TargetSession("FakePC", backend); result = session.connect()
    assert result["success"] and backend.WriteCount == 0
    assert session.readCached("pedals.throttle") == (0.375, True)


def test_wrong_application_contract_disconnects():
    backend = gui.FakeTargetBackend(["hil_cmd.something"])
    session = gui.TargetSession("FakePC", backend); result = session.connect()
    assert not result["success"] and "required" in result["reason"]
    assert session.Contract is None and session.State == "disconnected"
