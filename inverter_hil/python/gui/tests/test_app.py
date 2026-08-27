import ast
import os
from pathlib import Path

os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")

from PyQt5 import QtWidgets

from gui import build_fake_window


_APP = None


def application():
    global _APP
    _APP = QtWidgets.QApplication.instance() or QtWidgets.QApplication([])
    return _APP


def window(connect=False):
    application()
    view = build_fake_window(start_timer=False)
    backend = view.session.Backend
    if connect:
        assert view.session.connect()["success"]
        view.refresh_all()
    return view, backend


def test_window_constructs_and_populates_against_fake_backend():
    view, backend = window(connect=True)
    try:
        view.refresh_all()
        assert view.tabs.count() == 5
        assert view.can_tx_table.rowCount() == 14
        assert view.raw_tx_table.rowCount() == 9
        assert view.raw_rx_table.rowCount() == 13
        assert len(view.inverter_value_labels) == 4
        assert "decodeStatus3X3" in view.inverter_source_label.text()
        assert backend.Connected
        assert view.analog_input_labels[0].text().endswith("0.500 V")
        assert view.log.Count == 0
    finally:
        view.close()


def test_apply_enable_is_only_set_enabled_authority():
    source_path = Path(__file__).parents[1] / "app.py"
    tree = ast.parse(source_path.read_text(encoding="utf-8"))
    calls = []
    parents = {}
    for node in ast.walk(tree):
        for child in ast.iter_child_nodes(node):
            parents[child] = node
        if isinstance(node, ast.Call) and isinstance(node.func, ast.Attribute) and node.func.attr == "setEnabled":
            calls.append(node)
    assert len(calls) == 1
    node = calls[0]
    while node in parents and not isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)):
        node = parents[node]
    assert isinstance(node, ast.FunctionDef) and node.name == "apply_enable"


def test_pedal_write_gate_drains_pending_values_under_can_ownership():
    view, backend = window(connect=True)
    try:
        view.throttle_coalescer.submit(10, 0.0)
        view.throttle_coalescer.submit(80, 0.001)
        view.brake_coalescer.submit(20, 0.0)
        view.brake_coalescer.submit(70, 0.001)
        view.can_pedals_driving = True
        view.host_time_s = lambda: 1.0
        before = backend.WriteCount
        view.poll_coalescers()
        assert backend.WriteCount == before
        assert not view.throttle_coalescer.HasPending
        assert not view.brake_coalescer.HasPending
        view.can_pedals_driving = False
        view.poll_coalescers()
        assert backend.WriteCount == before
    finally:
        view.close()


def test_lifecycle_busy_tick_is_skipped_not_deferred_and_never_reaches_session():
    view, backend = window(connect=True)
    try:
        calls = []
        view.tick_heartbeat = lambda: calls.append("heartbeat")
        view.poll_coalescers = lambda: calls.append("coalescers")
        view.refresh_all = lambda: calls.append("refresh")
        before = backend.WriteCount
        view.target_busy = True
        view.on_status_timer()
        assert calls == []
        assert backend.WriteCount == before
        assert not view.status_timer.isActive()
    finally:
        view.target_busy = False
        view.close()


def test_policy_updates_widget_states_through_central_path():
    view, _ = window(connect=True)
    try:
        view.refresh_policy()
        assert view.policy["pedals"]
        assert view.throttle_slider.isEnabled()
        view.can_pedals_driving = True
        view.refresh_policy()
        assert not view.policy["pedals"]
        assert not view.throttle_slider.isEnabled()
    finally:
        view.close()


def test_sensor_digital_momentary_and_fault_controls_write_through_session():
    view, backend = window(connect=True)
    try:
        before = backend.WriteCount
        view.cooling_checkbox.click()
        view.sensor_checkboxes[0].click()
        view.precharge_button.click()
        view.lws_calibration_button.click()
        view.fault_mask_fields[0].setValue(7)
        view.fault_mask_fields[0].editingFinished.emit()
        view.drop_control_field.setValue(3)
        view.drop_control_field.editingFinished.emit()
        assert backend.WriteCount == before + 6
        assert backend.Values["hil_cmd.digital.cooling_switch"] is True
        assert backend.Values["hil_cmd.steering.dropout"] is True
        assert backend.Values["hil_cmd.digital.precharge_sequence"] == 1
        assert backend.Values["hil_cmd.steering.calibration_sequence"] == 1
        assert backend.Values["hil_cmd.inverter(1).fault_mask"] == 7
        assert backend.Values["hil_cmd.can.drop_control_mask"] == 3
    finally:
        view.close()
