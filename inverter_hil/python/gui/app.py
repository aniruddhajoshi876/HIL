"""PyQt5 view over :mod:`inverterhilgui`.

The view deliberately contains no target decoding, command validation, or
enable-policy decisions.  Those remain in the existing host layer.
"""

from __future__ import annotations

import math
import os
import sys
import time
from contextlib import contextmanager
from functools import partial

from PyQt5 import QtCore, QtGui, QtWidgets

from inverterhilgui import (
    FakeTargetBackend,
    SliderCoalescer,
    TargetSession,
    blankTelemetry,
    canAckStatus,
    canRowModel,
    connectionState,
    controlPolicy,
    contractEntry,
    evaluateTransitionGuards,
    formatInverterPanel,
    formatMeasurement,
    formatPinState,
    guiTheme,
    heartbeatState,
    hostHeartbeatTimeout,
    inverterPanelVisibility,
    parameterContract,
    safeFallbackPlan,
    sequenceCommand,
    sessionLog,
    stateCardStyle,
    trackVcuStateEntry,
)
from inverterhilgui.model_schema import MODEL_SCHEMA


VCU_STATES = ("LV_ON", "PRECHARGING", "ENABLE", "BUZZING", "RTD")
INVERTER_FIELDS = (
    "STATE", "READY", "CMD AGE", "TORQUE CMD", "TORQUE ACT", "SPEED",
    "Id set/act", "Iq set/act", "MOTOR TEMP", "SWITCH TEMP", "DERATING",
    "ACTIVE FAULT",
)
PARAMETERS = parameterContract()


def _rgb(value):
    return "rgb({},{},{})".format(*(round(component * 255) for component in value))


def _finite(value):
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value)


def _seconds(value):
    return f"{float(value):.3f} s" if _finite(value) else "--"


class InverterHilWindow(QtWidgets.QMainWindow):
    """Dense operator console backed exclusively by ``TargetSession``.

    A session must be injected.  This prevents constructing the GUI from
    silently selecting the MATLAB/Speedgoat backend.
    """

    POLL_INTERVAL_MS = 250

    def __init__(self, session: TargetSession, parent=None, start_timer=True):
        if not isinstance(session, TargetSession):
            raise TypeError("InverterHilWindow requires an injected TargetSession.")
        super().__init__(parent)
        self.session = session
        self.theme = guiTheme()
        self.log = sessionLog()
        self.telemetry = blankTelemetry()
        self.policy = {}
        self.target_busy = False
        self.can_pedals_driving = False
        self.throttle_coalescer = SliderCoalescer(0.030)
        self.brake_coalescer = SliderCoalescer(0.030)
        self.steering_coalescer = SliderCoalescer(0.030)
        self.heartbeat = {"counter": 0, "lastUpdateS": math.nan}
        self.heartbeat_timeout_s = hostHeartbeatTimeout()
        self.precharge_sequence = 0
        self.main_button_sequence = 0
        self.lws_calibration_sequence = 0
        self.main_button_last_pressed_s = -math.inf
        self.requested_steering_deg = math.nan
        self.vcu_state_entered_s = math.nan
        self.vcu_state_last = ""
        self.last_tx_message_count = math.nan
        self.tx_transmitting = False
        self.enable_groups = {}
        self.inverter_value_labels = []
        self.inverter_detail_widgets = []
        self.inverter_expanded = [False] * 4
        self._build_ui()
        self.status_timer = QtCore.QTimer(self)
        self.status_timer.setInterval(self.POLL_INTERVAL_MS)
        self.status_timer.setTimerType(QtCore.Qt.CoarseTimer)
        self.status_timer.timeout.connect(self.on_status_timer)
        self.refresh_all()
        if start_timer:
            self.status_timer.start()

    # ---------- construction ----------
    def _build_ui(self):
        self.setObjectName("InverterHilWindow")
        self.setWindowTitle("MFE26 VC INVERTER HIL")
        self.resize(1680, 980)
        central = QtWidgets.QWidget(self)
        root = QtWidgets.QVBoxLayout(central)
        root.setContentsMargins(6, 6, 6, 6)
        root.setSpacing(4)
        self.setCentralWidget(central)
        self._build_toolbar(root)
        self.torque_banner = QtWidgets.QLabel(self.theme["text"]["torqueBanner"])
        self.torque_banner.setAlignment(QtCore.Qt.AlignCenter)
        self.torque_banner.setObjectName("torqueBanner")
        root.addWidget(self.torque_banner)
        self.tabs = QtWidgets.QTabWidget()
        root.addWidget(self.tabs, 1)
        self.overview_tab = QtWidgets.QWidget()
        self.inverters_tab = QtWidgets.QWidget()
        self.io_can_tab = QtWidgets.QWidget()
        self.faults_tab = QtWidgets.QWidget()
        self.logging_tab = QtWidgets.QWidget()
        for title, page in zip(
            ("Overview", "Inverters", "I/O & CAN", "Faults & Scenarios", "Logging"),
            (self.overview_tab, self.inverters_tab, self.io_can_tab, self.faults_tab, self.logging_tab),
        ):
            self.tabs.addTab(page, title)
        self._build_overview()
        self._build_inverters()
        self._build_io_can()
        self._build_faults()
        self._build_logging()
        self._apply_theme()

    def _build_toolbar(self, parent):
        bar = QtWidgets.QHBoxLayout()
        self.title_label = QtWidgets.QLabel("MFE26 VC INVERTER HIL")
        self.target_name_label = QtWidgets.QLabel("TARGET --")
        self.connection_state_label = QtWidgets.QLabel("DISCONNECTED")
        self.application_state_label = QtWidgets.QLabel("APP --")
        self.elapsed_time_label = QtWidgets.QLabel("TARGET T --")
        for widget in (self.title_label, self.target_name_label, self.connection_state_label,
                       self.application_state_label, self.elapsed_time_label):
            bar.addWidget(widget)
        bar.addStretch(1)
        self.connect_button = self._button("Connect", self.on_connect)
        self.load_button = self._button("Load", partial(self._run_lifecycle, "load"))
        self.start_button = self._button("Start", partial(self._run_lifecycle, "start"))
        self.stop_button = self._button("Stop", partial(self._run_lifecycle, "stop"))
        self.reset_button = self._button("Reset", partial(self._run_lifecycle, "reset"))
        for button in (self.connect_button, self.load_button, self.start_button,
                       self.stop_button, self.reset_button):
            bar.addWidget(button)
        parent.addLayout(bar)

    def _build_overview(self):
        outer = QtWidgets.QVBoxLayout(self.overview_tab)
        state_row = QtWidgets.QHBoxLayout()
        self.state_cards = {}
        for index, state in enumerate(VCU_STATES):
            label = QtWidgets.QLabel(state)
            label.setAlignment(QtCore.Qt.AlignCenter)
            label.setMinimumWidth(90)
            self.state_cards[state] = label
            state_row.addWidget(label)
            if index != len(VCU_STATES) - 1:
                state_row.addWidget(QtWidgets.QLabel(">"))
        self.state_error_label = QtWidgets.QLabel("ERROR")
        self.state_error_label.setAlignment(QtCore.Qt.AlignCenter)
        self.time_in_state_label = QtWidgets.QLabel("TIME IN STATE --")
        state_row.addWidget(self.state_error_label)
        state_row.addWidget(self.time_in_state_label)
        state_row.addStretch(1)
        outer.addLayout(state_row)
        columns = QtWidgets.QHBoxLayout()
        columns.addWidget(self._build_driver_inputs(), 1)
        columns.addWidget(self._build_electrical(), 1)
        outer.addLayout(columns, 1)

    def _build_driver_inputs(self):
        box = QtWidgets.QGroupBox("DRIVER INPUTS")
        grid = QtWidgets.QGridLayout(box)
        self.throttle_slider, self.throttle_field, self.throttle_applied_label = self._pedal_row(
            grid, 0, "THROTTLE %", "pedals.throttle", self.throttle_coalescer)
        self.brake_slider, self.brake_field, self.brake_applied_label = self._pedal_row(
            grid, 1, "BRAKE %", "pedals.brake", self.brake_coalescer)
        grid.addWidget(QtWidgets.QLabel("STEERING ANGLE deg"), 2, 0)
        self.steering_slider = QtWidgets.QSlider(QtCore.Qt.Horizontal)
        self.steering_slider.setRange(-780, 780)
        self.steering_field = self._double_spin("steering.angle_deg")
        self.steering_applied_label = QtWidgets.QLabel("REQUESTED -- | APPLIED -- | SPEED -- | LWS --")
        self.steering_slider.valueChanged.connect(self._steering_slider_changed)
        self.steering_field.editingFinished.connect(self._steering_field_changed)
        grid.addWidget(self.steering_slider, 2, 1)
        grid.addWidget(self.steering_field, 2, 2)
        grid.addWidget(self.steering_applied_label, 2, 3)
        grid.addWidget(QtWidgets.QLabel("APPLIED PEDAL V"), 3, 0)
        voltage_row = QtWidgets.QHBoxLayout()
        self.pedal_voltage_labels = []
        for name in ("AO01 THR1", "AO02 THR2", "AO03 BRK1", "AO04 BRK2"):
            label = QtWidgets.QLabel(f"{name} --")
            self.pedal_voltage_labels.append(label)
            voltage_row.addWidget(label)
        grid.addLayout(voltage_row, 3, 1, 1, 3)
        self.plausibility_checkbox = QtWidgets.QCheckBox("INTERLOCK: allow pedal-plausibility violation")
        self.plausibility_checkbox.toggled.connect(
            lambda value: self._write_and_refresh("pedals.plausibility_override", value))
        self.expert_checkbox = QtWidgets.QCheckBox("INTERLOCK: expert mode (calibration, plant, faults)")
        self.expert_checkbox.toggled.connect(self.refresh_all)
        grid.addWidget(self.plausibility_checkbox, 4, 0, 1, 4)
        grid.addWidget(self.expert_checkbox, 5, 0, 1, 4)
        grid.addWidget(QtWidgets.QLabel("DIGITAL STIMULI"), 6, 0)
        self.cooling_checkbox = self._command_checkbox("COOLING_SW_IN", "digital.cooling_switch")
        self.shutdown_checkbox = self._command_checkbox("SD_FB_IN", "digital.shutdown_feedback")
        grid.addWidget(self.cooling_checkbox, 6, 1)
        grid.addWidget(self.shutdown_checkbox, 6, 2)
        self.digital_applied_labels = [QtWidgets.QLabel("--"), QtWidgets.QLabel("--")]
        grid.addWidget(QtWidgets.QLabel("APPLIED"), 7, 0)
        grid.addWidget(self.digital_applied_labels[0], 7, 1)
        grid.addWidget(self.digital_applied_labels[1], 7, 2)
        grid.addWidget(QtWidgets.QLabel("MOMENTARY (uint32 seq)"), 8, 0)
        self.precharge_button = self._button("PRECHARGE", partial(self._momentary, "precharge"))
        self.main_button = self._button("MAIN BUTTON", partial(self._momentary, "main"))
        self.precharge_sequence_label = QtWidgets.QLabel("seq 0")
        self.main_sequence_label = QtWidgets.QLabel("seq 0")
        grid.addWidget(self.precharge_button, 8, 1)
        grid.addWidget(self.main_button, 8, 2)
        grid.addWidget(self.precharge_sequence_label, 8, 3)
        grid.addWidget(self.main_sequence_label, 9, 1)
        self.enable_groups.update(
            pedals=[self.throttle_slider, self.throttle_field, self.brake_slider, self.brake_field],
            sensorStimulus=[self.steering_slider, self.steering_field],
            plausibilityViolation=[self.plausibility_checkbox],
            expertGroupsUnlocked=[self.expert_checkbox],
            digitalStimuli=[self.cooling_checkbox, self.shutdown_checkbox],
            momentary=[self.precharge_button, self.main_button],
        )
        return box

    def _pedal_row(self, grid, row, title, logical_name, coalescer):
        grid.addWidget(QtWidgets.QLabel(title), row, 0)
        slider = QtWidgets.QSlider(QtCore.Qt.Horizontal)
        slider.setRange(0, 100)
        field = QtWidgets.QDoubleSpinBox()
        field.setRange(0, 100)
        field.setDecimals(1)
        applied = QtWidgets.QLabel("APPLIED --")
        slider.valueChanged.connect(lambda value, c=coalescer, n=logical_name: self.submit_pedal(c, n, value))
        slider.sliderReleased.connect(lambda s=slider, f=field: f.setValue(s.value()))
        field.editingFinished.connect(lambda s=slider, f=field, c=coalescer, n=logical_name: self._pedal_field_changed(s, f, c, n))
        grid.addWidget(slider, row, 1)
        grid.addWidget(field, row, 2)
        grid.addWidget(applied, row, 3)
        return slider, field, applied

    def _build_electrical(self):
        column = QtWidgets.QWidget()
        layout = QtWidgets.QVBoxLayout(column)
        guard_box = QtWidgets.QGroupBox("NEXT TRANSITION")
        guard_layout = QtWidgets.QVBoxLayout(guard_box)
        self.guard_table = self._table(("GUARD", "ACTUAL", "REQUIRED", "RESULT"))
        guard_layout.addWidget(self.guard_table)
        layout.addWidget(guard_box, 2)
        dc_box = QtWidgets.QGroupBox("TWIN DC-LINK MIMIC")
        dc = QtWidgets.QGridLayout(dc_box)
        self.dc_value_labels = [QtWidgets.QLabel("--"), QtWidgets.QLabel("--")]
        self.dc_flag_labels = [QtWidgets.QLabel("ABOVE MIN --"), QtWidgets.QLabel("ABOVE MIN --")]
        for row, title in enumerate(("PAIR 1/2", "PAIR 3/4")):
            dc.addWidget(QtWidgets.QLabel(title), row, 0)
            dc.addWidget(self.dc_value_labels[row], row, 1)
            dc.addWidget(self.dc_flag_labels[row], row, 2)
        self.switching_label = QtWidgets.QLabel("--")
        dc.addWidget(QtWidgets.QLabel("SWITCHING"), 2, 0)
        dc.addWidget(self.switching_label, 2, 1)
        layout.addWidget(dc_box)
        pin_box = QtWidgets.QGroupBox("VCU OUTPUT PINS")
        pins = QtWidgets.QGridLayout(pin_box)
        self.pin_state_labels = []
        for index, item in enumerate(self.telemetry["pins"]):
            pins.addWidget(QtWidgets.QLabel(f'{item["name"]} ({item["testPoint"]})'), 0, index)
            label = QtWidgets.QLabel("--")
            label.setAlignment(QtCore.Qt.AlignCenter)
            self.pin_state_labels.append(label)
            pins.addWidget(label, 1, index)
        layout.addWidget(pin_box)
        rail_box = QtWidgets.QGroupBox("VCU SENSOR RAILS")
        rails = QtWidgets.QHBoxLayout(rail_box)
        self.analog_input_labels = []
        for name in ("AI01 5V_THR1", "AI02 5V_THR2", "AI03 5V_BP1", "AI04 5V_BP2"):
            label = QtWidgets.QLabel(f"{name} --")
            self.analog_input_labels.append(label)
            rails.addWidget(label)
        layout.addWidget(rail_box)
        return column

    def _build_inverters(self):
        outer = QtWidgets.QVBoxLayout(self.inverters_tab)
        self.inverter_source_label = QtWidgets.QLabel(
            "DEGRADED: decodeStatus3X3 is target-generated and is not ported. "
            "Raw 9x8 TX status payloads remain visible in I/O & CAN; per-inverter "
            "3X3 values are unavailable and no values are inferred."
        )
        self.inverter_source_label.setWordWrap(True)
        outer.addWidget(self.inverter_source_label)
        panels = QtWidgets.QGridLayout()
        outer.addLayout(panels, 1)
        for channel in range(4):
            box = QtWidgets.QGroupBox(f"INVERTER {channel + 1}")
            layout = QtWidgets.QGridLayout(box)
            title = QtWidgets.QLabel(f"INV{channel + 1}  {('FL', 'FR', 'RR', 'RL')[channel]}")
            button = self._button("> DETAILS", partial(self._toggle_inverter, channel))
            layout.addWidget(title, 0, 0, 1, 2)
            layout.addWidget(button, 0, 2)
            values, details = [], []
            visible, _, _ = inverterPanelVisibility(False)
            for row, field_name in enumerate(INVERTER_FIELDS, 1):
                name = QtWidgets.QLabel(field_name)
                value = QtWidgets.QLabel("--")
                layout.addWidget(name, row, 0)
                layout.addWidget(value, row, 1, 1, 2)
                values.append(value)
                details.append((name, value))
                name.setVisible(visible[row - 1])
                value.setVisible(visible[row - 1])
            self.inverter_value_labels.append(values)
            self.inverter_detail_widgets.append((button, details))
            panels.addWidget(box, channel // 2, channel % 2)

    def _build_io_can(self):
        outer = QtWidgets.QVBoxLayout(self.io_can_tab)
        self.instrument_status_label = QtWidgets.QLabel(
            "HIGH-RATE INSTRUMENT STREAMING NOT REGISTERED. Polling shows only target-retained raw observations."
        )
        outer.addWidget(self.instrument_status_label)
        tables = QtWidgets.QHBoxLayout()
        self.can_rx_table = self._table(("LIVE", "ID", "NAME", "SIGNAL", "VALUE", "COUNT"))
        self.can_tx_table = self._table(("LIVE", "ID", "NAME", "SIGNAL", "VALUE", "COUNT"))
        for title, table in (("VCU TX / HIL RX", self.can_rx_table), ("HIL TX / VCU RX", self.can_tx_table)):
            box = QtWidgets.QGroupBox(title)
            lay = QtWidgets.QVBoxLayout(box)
            lay.addWidget(table)
            tables.addWidget(box)
        outer.addLayout(tables, 1)
        raw_tabs = QtWidgets.QTabWidget()
        self.raw_tx_table = self._table(tuple(f"B{index}" for index in range(1, 9)))
        self.raw_rx_table = self._table(tuple(f"C{index}" for index in range(1, 15)))
        raw_tabs.addTab(self.raw_tx_table, "RAW TX MATRIX 9x8")
        raw_tabs.addTab(self.raw_rx_table, "RAW RX MATRIX 13x14")
        raw_tabs.setMaximumHeight(170)
        outer.addWidget(raw_tabs)
        sensor_box = QtWidgets.QGroupBox("SENSOR SIMULATION - MTi-680G / BOSCH LWS")
        sensor = QtWidgets.QGridLayout(sensor_box)
        self.sensor_labels = [QtWidgets.QLabel(text) for text in (
            "STEERING --", "MTi ACCEL 0x034 --", "MTi RATE 0x032 --",
            "MTi VELOCITY 0x076 --", "LWS CALIBRATION --")]
        definitions = (
            ("INJECT: LWS 0x2B0 dropout", "steering.dropout"),
            ("INJECT: LWS stale payload", "steering.stale"),
            ("INJECT: LWS wrong DLC", "steering.malformed"),
            ("INJECT: illegal TRIM/CAL/OK", "steering.invalid_status"),
            ("INJECT: LWS angle 0x7FFF", "steering.angle_sentinel"),
            ("INJECT: LWS speed 0xFF", "steering.speed_sentinel"),
            ("INJECT: MTi all-frame dropout", "imu.dropout"),
            ("INJECT: MTi stale payloads", "imu.stale"),
            ("INJECT: MTi wrong DLC", "imu.malformed"),
        )
        self.sensor_checkboxes = []
        for index, (text, name) in enumerate(definitions):
            checkbox = self._command_checkbox(text, name)
            self.sensor_checkboxes.append(checkbox)
            sensor.addWidget(checkbox, index // 2, 1 + index % 2)
        for row, label in enumerate(self.sensor_labels):
            sensor.addWidget(label, row, 0)
        self.lws_calibration_button = self._button(
            "RESET 0x05 -> CHECK -> ZERO 0x03", self._calibrate_lws)
        sensor.addWidget(self.lws_calibration_button, 4, 2)
        outer.addWidget(sensor_box)
        self.can_diagnostics_label = QtWidgets.QLabel("CAN --")
        outer.addWidget(self.can_diagnostics_label)
        self.enable_groups["sensorStimulus"].extend(self.sensor_checkboxes)
        self.enable_groups["calibration"] = [self.lws_calibration_button]

    def _build_faults(self):
        outer = QtWidgets.QVBoxLayout(self.faults_tab)
        inverter_box = QtWidgets.QGroupBox("PER-INVERTER SCENARIO")
        grid = QtWidgets.QGridLayout(inverter_box)
        for column, header in enumerate(("CHANNEL", "fault_mask (uint32)", "load_nm", "connected")):
            grid.addWidget(QtWidgets.QLabel(header), 0, column)
        self.fault_mask_fields, self.load_torque_fields, self.connected_checkboxes = [], [], []
        for channel in range(1, 5):
            fault = self._double_spin(f"inverter{channel}.fault_mask")
            fault.setDecimals(0)
            load = self._double_spin(f"inverter{channel}.load_nm")
            connected = QtWidgets.QCheckBox("connected")
            fault.editingFinished.connect(partial(self._spin_write, fault, f"inverter{channel}.fault_mask", True))
            load.editingFinished.connect(partial(self._spin_write, load, f"inverter{channel}.load_nm", False))
            connected.toggled.connect(partial(self._write_and_refresh, f"inverter{channel}.connected"))
            self.fault_mask_fields.append(fault)
            self.load_torque_fields.append(load)
            self.connected_checkboxes.append(connected)
            grid.addWidget(QtWidgets.QLabel(f"INV{channel}"), channel, 0)
            grid.addWidget(fault, channel, 1)
            grid.addWidget(load, channel, 2)
            grid.addWidget(connected, channel, 3)
        outer.addWidget(inverter_box)
        can_box = QtWidgets.QGroupBox("CAN FAULT INJECTION")
        can = QtWidgets.QGridLayout(can_box)
        self.drop_control_field = self._integer_spin("can.drop_control_mask")
        self.drop_status_field = self._integer_spin("can.drop_status_mask")
        self.drop_control_field.editingFinished.connect(partial(self._spin_write, self.drop_control_field, "can.drop_control_mask", True))
        self.drop_status_field.editingFinished.connect(partial(self._spin_write, self.drop_status_field, "can.drop_status_mask", True))
        can.addWidget(QtWidgets.QLabel("drop_control_mask (uint8)"), 0, 0)
        can.addWidget(self.drop_control_field, 0, 1)
        can.addWidget(QtWidgets.QLabel("0x186 0x196 0x1A6 0x1B6"), 0, 2)
        can.addWidget(QtWidgets.QLabel("drop_status_mask (uint16)"), 1, 0)
        can.addWidget(self.drop_status_field, 1, 1)
        can.addWidget(QtWidgets.QLabel("nine-frame status cycle"), 1, 2)
        outer.addWidget(can_box)
        health = QtWidgets.QHBoxLayout()
        self.heartbeat_label = QtWidgets.QLabel("GUI HEARTBEAT --")
        self.fallback_label = QtWidgets.QLabel("FALLBACK --")
        health.addWidget(self.heartbeat_label)
        health.addWidget(self.fallback_label)
        outer.addLayout(health)
        outer.addStretch(1)
        self.enable_groups.update(
            faultInjection=self.fault_mask_fields,
            plantParameters=self.load_torque_fields + self.connected_checkboxes,
            canFaults=[self.drop_control_field, self.drop_status_field],
        )

    def _build_logging(self):
        outer = QtWidgets.QVBoxLayout(self.logging_tab)
        self.log_table = self._table(("HOST TIME", "TARGET T", "LOGICAL NAME", "TARGET PATH", "REQUESTED", "APPLIED", "RESULT", "DETAIL"))
        outer.addWidget(self.log_table, 1)
        footer = QtWidgets.QHBoxLayout()
        self.export_log_button = self._button("Export log...", self._export_log)
        self.log_summary_label = QtWidgets.QLabel("0 records (append-only)")
        footer.addWidget(self.export_log_button)
        footer.addWidget(self.log_summary_label)
        footer.addStretch(1)
        outer.addLayout(footer)
        self.enable_groups["logExport"] = [self.export_log_button]

    # ---------- small widget factories ----------
    def _button(self, text, callback):
        button = QtWidgets.QPushButton(text)
        button.clicked.connect(callback)
        return button

    def _command_checkbox(self, text, logical_name):
        checkbox = QtWidgets.QCheckBox(text)
        checkbox.toggled.connect(partial(self._write_and_refresh, logical_name))
        return checkbox

    def _double_spin(self, logical_name):
        item = contractEntry(PARAMETERS, logical_name)
        spin = QtWidgets.QDoubleSpinBox()
        spin.setRange(float(item.minimum), float(item.maximum))
        spin.setDecimals(1 if item.type == "double" else 0)
        spin.setKeyboardTracking(False)
        return spin

    def _integer_spin(self, logical_name):
        item = contractEntry(PARAMETERS, logical_name)
        spin = QtWidgets.QSpinBox()
        spin.setRange(int(item.minimum), int(item.maximum))
        spin.setKeyboardTracking(False)
        return spin

    def _table(self, headers):
        table = QtWidgets.QTableWidget(0, len(headers))
        table.setHorizontalHeaderLabels(headers)
        table.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        table.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows)
        table.horizontalHeader().setStretchLastSection(True)
        table.verticalHeader().hide()
        return table

    def _apply_theme(self):
        colors = self.theme["color"]
        self.setStyleSheet(f"""
            QMainWindow, QWidget {{ background: {_rgb(colors['background'])}; color: {_rgb(colors['primaryText'])}; font-family: Consolas; }}
            QGroupBox {{ background: {_rgb(colors['panel'])}; border: 1px solid {_rgb(colors['panelEdge'])}; margin-top: 8px; padding-top: 8px; }}
            QGroupBox::title {{ subcontrol-origin: margin; left: 8px; }}
            QPushButton, QSpinBox, QDoubleSpinBox {{ background: {_rgb(colors['panel'])}; border: 1px solid {_rgb(colors['panelEdge'])}; padding: 4px; }}
            QTabBar::tab {{ background: black; color: {_rgb(colors['tabBarInactiveText'])}; padding: 7px 30px; }}
            QTabBar::tab:selected {{ color: white; font-weight: bold; }}
            QHeaderView::section {{ background: {_rgb(colors['panel'])}; color: {_rgb(colors['secondaryText'])}; border: 1px solid {_rgb(colors['panelEdge'])}; }}
            QTableWidget {{ background: {_rgb(colors['panel'])}; gridline-color: {_rgb(colors['panelEdge'])}; }}
            QLabel#torqueBanner {{ background: {_rgb(colors['fault'])}; color: white; font-weight: bold; }}
        """)

    # ---------- single enable authority ----------
    def apply_enable(self, widgets, enabled):
        """The only location allowed to call QWidget.setEnabled."""
        for widget in widgets:
            widget.setEnabled(bool(enabled))

    def refresh_policy(self):
        lifecycle = self.session.describeState()
        interlocks = {
            "expertMode": self.expert_checkbox.isChecked(),
            "plausibilityOverride": self.plausibility_checkbox.isChecked(),
            "targetHealthy": self.telemetry["io"]["healthy"],
            "heartbeatOk": lifecycle["isConnected"],
            "contractResolved": self.session.Contract is not None,
        }
        self.policy = controlPolicy(lifecycle["state"], self.telemetry["vcu"]["state"], interlocks, self.can_pedals_driving)
        for group, widgets in self.enable_groups.items():
            self.apply_enable(widgets, self.policy.get(group, False))
        allowed = connectionState(lifecycle["state"])["allowed"]
        self.apply_enable([self.connect_button], allowed["connect"] or allowed["disconnect"])
        self.apply_enable([self.load_button], allowed["load"])
        self.apply_enable([self.start_button], allowed["start"])
        self.apply_enable([self.stop_button], allowed["stop"])
        self.apply_enable([self.reset_button], allowed["reset"])

    # ---------- lifecycle and timer safety ----------
    @contextmanager
    def target_section(self):
        self.target_busy = True
        try:
            yield
        finally:
            self.target_busy = False

    def on_connect(self):
        with self.target_section():
            result = self.session.disconnect() if self.session.describeState()["isConnected"] else self.session.connect()
            self._record_lifecycle("disconnect" if result["state"] == "disconnected" else "connect", result)
            self.refresh_all()

    def _run_lifecycle(self, action):
        with self.target_section():
            result = self.session.load("inverter_hil") if action == "load" else getattr(self.session, action)()
            self._record_lifecycle(action, result)
            self.refresh_all()

    def on_status_timer(self):
        # Deliberate drop semantics: no queued/deferred retry is scheduled.
        if self.target_busy:
            return
        try:
            self.tick_heartbeat()
            self.poll_coalescers()
            self.refresh_all()
        except Exception as exc:  # timer errors must remain visible in the log
            self._report_error("status_timer", exc)
            self.refresh_log()

    # ---------- command pipeline ----------
    def submit_pedal(self, coalescer, name, percent):
        emission = coalescer.submit(percent, self.host_time_s())
        self._commit_pedal_emission(name, emission)

    def _commit_pedal_emission(self, name, emission):
        if emission["hasValue"] and not self.can_pedals_driving:
            self.commit_write(name, emission["value"] / 100.0, True)

    def poll_coalescers(self):
        # Always poll/drain both pedal queues.  Ownership gates only commits.
        throttle = self.throttle_coalescer.poll(self.host_time_s())
        self._commit_pedal_emission("pedals.throttle", throttle)
        brake = self.brake_coalescer.poll(self.host_time_s())
        self._commit_pedal_emission("pedals.brake", brake)
        steering = self.steering_coalescer.poll(self.host_time_s())
        if steering["hasValue"]:
            self.commit_write("steering.angle_deg", steering["value"], True)

    def commit_write(self, name, value, log_result=True):
        result = self.session.write(name, value)
        if log_result or not result["success"] or result["mismatch"]:
            code = "failed" if not result["success"] else "mismatch" if result["mismatch"] else "clamped" if result["clamped"] else "applied"
            self.log.append({
                "targetTimeS": self.session.executionTimeS(), "logicalName": name,
                "targetPath": result["path"], "requested": result["requested"],
                "applied": result["applied"], "result": code, "detail": result["reason"],
            })
        return result

    def _pedal_field_changed(self, slider, field, coalescer, name):
        slider.setValue(round(field.value()))
        self.submit_pedal(coalescer, name, field.value())

    def _steering_slider_changed(self, value):
        self.steering_field.setValue(value)
        self._submit_steering(value)

    def _steering_field_changed(self):
        value = self.steering_field.value()
        self.steering_slider.setValue(round(value))
        self._submit_steering(value)

    def _submit_steering(self, value):
        emission = self.steering_coalescer.submit(value, self.host_time_s())
        if emission["hasValue"]:
            self.commit_write("steering.angle_deg", emission["value"], True)
        self.requested_steering_deg = value

    def _write_and_refresh(self, name, value):
        self.commit_write(name, value, True)
        self.refresh_all()

    def _spin_write(self, widget, name, integer):
        value = round(widget.value()) if integer else widget.value()
        self._write_and_refresh(name, value)

    def _momentary(self, which):
        if which == "precharge":
            self.precharge_sequence = sequenceCommand(self.precharge_sequence)
            self.commit_write("digital.precharge_sequence", self.precharge_sequence, True)
        else:
            self.main_button_sequence = sequenceCommand(self.main_button_sequence)
            self.main_button_last_pressed_s = self.host_time_s()
            self.commit_write("digital.main_button_sequence", self.main_button_sequence, True)
        self.refresh_all()

    def _calibrate_lws(self):
        self.lws_calibration_sequence = sequenceCommand(self.lws_calibration_sequence)
        self._write_and_refresh("steering.calibration_sequence", self.lws_calibration_sequence)

    # ---------- polling and presentation ----------
    def tick_heartbeat(self):
        beat = heartbeatState(self.heartbeat, self.host_time_s(), self.heartbeat_timeout_s)
        self.heartbeat = {"counter": beat["counter"], "lastUpdateS": beat["lastUpdateS"]}
        lifecycle = self.session.describeState()
        if lifecycle["isRunning"]:
            self.commit_write("gui_heartbeat", beat["counter"], False)
        plan = safeFallbackPlan({
            "applicationRunning": lifecycle["isRunning"], "targetConnected": lifecycle["isConnected"],
            "applicationLoaded": lifecycle["isConnected"], "ioHealthy": self.telemetry["io"]["healthy"],
            "armed": self.telemetry["pedals"]["armed"], "heartbeatAgeS": beat["ageS"],
            "heartbeatTimeoutS": self.heartbeat_timeout_s,
        })
        self.heartbeat_label.setText(f'GUI HEARTBEAT {beat["counter"]}  age {_seconds(beat["ageS"])}')
        self.fallback_label.setText(f'FALLBACK {plan["reason"].upper()} : AO {plan["analogV"]} / DIO {[int(x) for x in plan["digital"]]}')

    def refresh_all(self):
        self.refresh_live_io()
        self.refresh_policy()
        self.refresh_toolbar()
        self.refresh_state()
        self.refresh_guards()
        self.refresh_driver_inputs()
        self.refresh_electrical()
        self.refresh_inverters()
        self.refresh_can()
        self.refresh_log()

    def refresh_live_io(self):
        try:
            live = self.session.readLiveIo()
        except Exception as exc:
            # A backend may have lifecycle/parameter support but no seeded
            # optional signal vectors (the stock fake backend is one such
            # case).  Preserve the no-data snapshot and keep the view alive.
            self._report_error("read_live_io", exc)
            live = {"known": False}
        if not live["known"]:
            self.telemetry["io"] = {"healthy": False, "healthyKnown": False}
            for pin in self.telemetry["pins"]:
                pin["state"] = None
            self.telemetry["analogInV"] = [math.nan] * 4
            self.telemetry["pedals"]["appliedV"] = [math.nan] * 4
            self.can_pedals_driving = False
            self.vcu_state_entered_s = math.nan
            self.vcu_state_last = ""
            self.telemetry["vcu"]["timeInStateS"] = math.nan
            return
        self.telemetry["io"] = dict(live["io"])
        for pin, state in zip(self.telemetry["pins"], live["pins"]):
            pin["state"] = state
        analog = list(live.get("analogInV", [math.nan] * 4))
        self.telemetry["analogInV"] = analog
        self.telemetry["pedals"]["appliedV"] = analog
        if live.get("vcuStateKnown"):
            names = VCU_STATES + ("ERROR_SHUTDOWN",)
            index = round(live["vcuStateId"])
            if 0 <= index < len(names):
                state = names[index]
                entered, elapsed = trackVcuStateEntry(state, self.vcu_state_last, self.vcu_state_entered_s, self.host_time_s())
                self.vcu_state_entered_s, self.vcu_state_last = entered, state
                self.telemetry["vcu"].update(state=state, timeInStateS=elapsed, errorKnown=index == 5, errorActive=index == 5)
        was_driving = self.can_pedals_driving
        if live.get("canPedalsKnown"):
            self.can_pedals_driving = bool(live["canPedalsDriving"])
            if self.can_pedals_driving:
                self._set_pedal_display(live["canPedals"])
            elif was_driving:
                self.commit_write("pedals.throttle", 0, True)
                self.commit_write("pedals.brake", 0, True)
        else:
            self.can_pedals_driving = False
        self.telemetry["appsBrakeFault"] = live["appsBrakeFault"] if live.get("appsBrakeFaultKnown") else None
        diagnostics = live.get("can", {}).get("diagnostics")
        if live.get("can", {}).get("known") and diagnostics:
            self.telemetry["can"]["diagnostics"].update(diagnostics)
        self._apply_raw_can(live)

    def _set_pedal_display(self, values):
        for slider, field, value in ((self.throttle_slider, self.throttle_field, values[0]),
                                     (self.brake_slider, self.brake_field, values[1])):
            slider.blockSignals(True)
            field.blockSignals(True)
            slider.setValue(round(value))
            field.setValue(value)
            slider.blockSignals(False)
            field.blockSignals(False)

    def _apply_raw_can(self, live):
        now = self.host_time_s()
        payloads = live.get("txPayloads", [])
        if live.get("txPayloadsKnown") and len(payloads) == 9:
            self._fill_table(self.raw_tx_table, payloads)
            count = live.get("txMessageCount", math.nan)
            transmitting = _finite(count) and _finite(self.last_tx_message_count) and count > self.last_tx_message_count
            self.tx_transmitting = transmitting
            self.last_tx_message_count = count
            ack = canAckStatus(self.telemetry["can"]["diagnostics"], transmitting)
            for item, payload in zip(self.telemetry["can"]["tx"][:9], payloads):
                encoded = " ".join(f"{int(byte) & 0xFF:02X}" for byte in payload)
                if item["value"] != encoded:
                    item["lastChangeS"] = now
                item.update(value=encoded, signal=f'raw target-retained payload | {ack["text"]}', timestampsS=[now], count=count)
        raw_rx = live.get("rxObservation", [])
        if live.get("rxKnown") and raw_rx:
            # Preserve the matrix exactly.  Its 13 rows are transport
            # observations, not the five semantic CAN rows beside it.
            self._fill_table(self.raw_rx_table, raw_rx)
        if live.get("pedalPayloadKnown"):
            item = self.telemetry["can"]["rx"][0]
            item.update(signal="raw VCU pedal payload", value=" ".join(f"{x:02X}" for x in live["pedalPayload"]), timestampsS=[now], count=live.get("pedalTxCount", math.nan))

    def refresh_toolbar(self):
        lifecycle = self.session.describeState()
        self.target_name_label.setText(f"TARGET {self.session.TargetName}")
        self.connection_state_label.setText(lifecycle["state"].upper())
        self.application_state_label.setText("APP RUNNING" if lifecycle["isRunning"] else f'APP {lifecycle["state"].upper()}')
        self.elapsed_time_label.setText(f"TARGET T {_seconds(self.session.executionTimeS())}")
        self.connect_button.setText("Disconnect" if lifecycle["isConnected"] else "Connect")

    def refresh_state(self):
        current = self.telemetry["vcu"]["state"]
        error = self.telemetry["vcu"]["errorKnown"] and self.telemetry["vcu"]["errorActive"]
        colors = self.theme["color"]
        for state, label in self.state_cards.items():
            style = stateCardStyle(current, state, error)
            color = colors["healthy"] if style == "active" else colors["electrical"] if style == "passed" else colors["disabledText"]
            background = colors["highlight"] if style == "active" else colors["background"]
            label.setStyleSheet(f"color: {_rgb(color)}; background: {_rgb(background)}; padding: 5px;")
        self.state_error_label.setStyleSheet(f"background: {_rgb(colors['fault'])}; color: white; padding: 5px;" if error else f"color: {_rgb(colors['disabledText'])};")
        self.time_in_state_label.setText(f'TIME IN STATE {_seconds(self.telemetry["vcu"]["timeInStateS"])}')

    def refresh_guards(self):
        self.telemetry["guards"]["mainButton"] = self.host_time_s() - self.main_button_last_pressed_s <= 1.0
        guards = evaluateTransitionGuards(self.telemetry["guards"], {})
        self._fill_table(self.guard_table, [[g["name"], g["actual"], g["required"], "--" if not g["known"] else "PASS" if g["pass"] else "FAIL"] for g in guards])

    def refresh_driver_inputs(self):
        pedals = self.telemetry["pedals"]
        self.throttle_applied_label.setText(f'APPLIED {self._percent(pedals["throttleAppliedPercent"])}')
        self.brake_applied_label.setText(f'APPLIED {self._percent(pedals["brakeAppliedPercent"])}')
        steering = self.telemetry["steering"]
        self.steering_applied_label.setText(
            f'REQUESTED {self._steering(self.requested_steering_deg, "deg")} | '
            f'APPLIED {self._steering(steering["appliedAngleDeg"], "deg")} | '
            f'SPEED {self._steering(steering["speedDegPerS"], "deg/s")} | '
            f'LWS {self._steering(steering["observedAngleDeg"], "deg")}')
        for label, name, value in zip(self.pedal_voltage_labels, ("AO01 THR1", "AO02 THR2", "AO03 BRK1", "AO04 BRK2"), pedals["appliedV"]):
            label.setText(f'{name} {formatMeasurement(value, math.nan, "V", False)["value"]}')
        for label, name in zip(self.digital_applied_labels, ("digital.cooling_switch", "digital.shutdown_feedback")):
            value, known = self.session.readCached(name)
            label.setText(formatPinState(value)["text"] if known else "--")
        self.precharge_sequence_label.setText(f"seq {self.precharge_sequence}")
        self.main_sequence_label.setText(f"seq {self.main_button_sequence}")

    def refresh_electrical(self):
        for index, link in enumerate(self.telemetry["dcLink"]):
            self.dc_value_labels[index].setText(formatMeasurement(link["voltageV"], link["rawCount"], "V", link["capturePending"])["combined"])
            self.dc_flag_labels[index].setText(f'ABOVE MIN {formatPinState(link["aboveMinimum"])["text"]}')
        self.switching_label.setText(formatMeasurement(self.telemetry["switchingFrequencyKHz"], self.telemetry["switchingFrequencyRaw"], "kHz", True)["combined"])
        for label, pin in zip(self.pin_state_labels, self.telemetry["pins"]):
            label.setText(formatPinState(pin["state"])["text"])
        for label, name, value in zip(self.analog_input_labels, ("AI01 5V_THR1", "AI02 5V_THR2", "AI03 5V_BP1", "AI04 5V_BP2"), self.telemetry["analogInV"]):
            label.setText(f'{name} {formatMeasurement(value, math.nan, "V", False)["value"]}')

    def refresh_inverters(self):
        keys = ("state", "ready", "commandAge", "torqueCommand", "torqueActual", "speed", "idCurrent", "iqCurrent", "motorTemperature", "switchTemperature", "derating", "activeFault")
        for channel in range(4):
            panel = formatInverterPanel(self.telemetry, channel + 1)
            for label, key in zip(self.inverter_value_labels[channel], keys):
                label.setText(panel[key] if panel["hasData"] else "--")

    def refresh_can(self):
        now = self.host_time_s()
        for table, observations in ((self.can_rx_table, self.telemetry["can"]["rx"]), (self.can_tx_table, self.telemetry["can"]["tx"])):
            rows = canRowModel(observations, now)
            self._fill_table(table, [[r["live"], r["id"], r["name"], r["signal"], r["value"], r["count"]] for r in rows])
        d = self.telemetry["can"]["diagnostics"]
        writes = f'{sum(bool(x) for x in d["writeSucceeded"])}/{len(d["writeSucceeded"])} OK' if d["writeKnown"] else "--"
        self.can_diagnostics_label.setText(
            f'CAN WRITE {writes} | BUS LOAD {formatMeasurement(d["busLoadPercent"], math.nan, "%", False)["value"]} | '
            f'TX OVERRUN {formatPinState(d["transmitOverrun"])["text"]} | RX OVERRUN {formatPinState(d["receiveOverrun"])["text"]} | '
            f'ERROR WARNING {formatPinState(d["errorWarning"])["text"]} | BUS-OFF {formatPinState(d["busOff"])["text"]}')

    def refresh_log(self):
        self._fill_table(self.log_table, self.log.toCell())
        self.log_summary_label.setText(f"{self.log.Count} records (append-only)")

    def _fill_table(self, table, rows):
        table.setRowCount(len(rows))
        for row, values in enumerate(rows):
            for column, value in enumerate(values):
                table.setItem(row, column, QtWidgets.QTableWidgetItem(str(value)))
        table.resizeColumnsToContents()

    def _toggle_inverter(self, channel):
        self.inverter_expanded[channel] = not self.inverter_expanded[channel]
        visible, _, _ = inverterPanelVisibility(self.inverter_expanded[channel])
        button, details = self.inverter_detail_widgets[channel]
        button.setText("v DETAILS" if self.inverter_expanded[channel] else "> DETAILS")
        for show, pair in zip(visible, details):
            for widget in pair:
                widget.setVisible(show)

    def _record_lifecycle(self, action, result):
        self.log.append({
            "targetTimeS": self.session.executionTimeS(), "logicalName": f"lifecycle.{action}",
            "targetPath": self.session.TargetName, "requested": action, "applied": result["state"],
            "result": "lifecycle" if result["success"] else "failed", "detail": result["reason"],
        })

    def _report_error(self, context, exc):
        self.log.append({"targetTimeS": math.nan, "logicalName": context, "targetPath": "", "requested": "--", "applied": "--", "result": "failed", "detail": str(exc)})

    def _export_log(self):
        filename, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Export session log", "inverter_hil_session_log.csv", "CSV (*.csv)")
        if filename:
            self.log.export(filename)
            self.refresh_log()

    @staticmethod
    def host_time_s():
        return time.monotonic()

    @staticmethod
    def _percent(value):
        return f"{value:.1f} %" if _finite(value) else "--"

    @staticmethod
    def _steering(value, unit):
        return f"{value:.1f} {unit}" if _finite(value) else "--"

    def closeEvent(self, event):
        self.status_timer.stop()
        self.session.disconnect()
        event.accept()


def build_fake_window(start_timer=True):
    """Construct the application view with the no-hardware fake backend."""
    backend = FakeTargetBackend()
    schema = MODEL_SCHEMA
    # TargetSession expects vectors/matrices at these retained-signal ports;
    # seed honest synthetic shapes because the generic fake defaults to a
    # scalar zero for every otherwise-unconfigured signal.
    backend.Signals.update({
        (schema.vcu_observability_block, schema.vcu_pedal_payload_port): [0] * 8,
        (schema.vcu_observability_block, schema.vcu_state_id_port): 0,
        (schema.vcu_observability_block, schema.vcu_pedal_tx_count_port): 0,
        (schema.vcu_observability_block, schema.vcu_apps_brake_fault_port): 0,
        (schema.system_status_block, schema.status_tx_payloads_port): [[0] * 8 for _ in range(9)],
        (schema.system_status_block, schema.status_rx_observation_port): [[0] * 14 for _ in range(13)],
        (schema.system_status_block, schema.status_analog_inputs_port): [0.5, 1.0, 1.5, 2.0],
        (schema.system_status_block, schema.status_tx_count_port): 1,
        (schema.system_status_block, schema.status_can_pedals_port): [0, 0, 0],
    })
    return InverterHilWindow(TargetSession("FakeTarget", backend), start_timer=start_timer)


def main(argv=None):
    """Launch safely against ``FakeTargetBackend``; never selects hardware."""
    args = list(sys.argv if argv is None else argv)
    if "--offscreen" in args:
        os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")
    app = QtWidgets.QApplication.instance() or QtWidgets.QApplication(args)
    window = build_fake_window()
    window.show()
    if "--smoke-test" in args:
        QtCore.QTimer.singleShot(50, app.quit)
    return app.exec_()
