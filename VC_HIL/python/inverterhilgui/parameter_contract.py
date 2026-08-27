"""Declarative logical-name contract for GUI-owned parameters."""

from dataclasses import dataclass
from typing import Iterable, Sequence


@dataclass(frozen=True)
class ParameterEntry:
    name: str
    type: str
    minimum: float
    maximum: float
    structPath: str
    flatPath: str
    required: bool
    group: str


def _e(name, typ, lo, hi, struct_path, flat_path, required, group):
    return ParameterEntry(name, typ, lo, hi, struct_path, flat_path, required, group)


# This mirrors every declaration in parameterContract.m at HEAD 36f99bd.
PARAMETER_CONTRACT: tuple[ParameterEntry, ...] = (
    _e("pedals.throttle", "double", 0, 1, "hil_cmd.pedals.throttle", "hil_cmd_pedals_throttle", True, "pedals"),
    _e("pedals.brake", "double", 0, 1, "hil_cmd.pedals.brake", "hil_cmd_pedals_brake", True, "pedals"),
    _e("steering.angle_deg", "double", -780, 780, "hil_cmd.steering.angle_deg", "hil_cmd_steering_angle_deg", True, "sensorStimulus"),
    _e("steering.dropout", "logical", 0, 1, "hil_cmd.steering.dropout", "hil_cmd_steering_dropout", True, "sensorStimulus"),
    _e("steering.stale", "logical", 0, 1, "hil_cmd.steering.stale", "hil_cmd_steering_stale", True, "sensorStimulus"),
    _e("steering.malformed", "logical", 0, 1, "hil_cmd.steering.malformed", "hil_cmd_steering_malformed", True, "sensorStimulus"),
    _e("steering.invalid_status", "logical", 0, 1, "hil_cmd.steering.invalid_status", "hil_cmd_steering_invalid_status", True, "sensorStimulus"),
    _e("steering.angle_sentinel", "logical", 0, 1, "hil_cmd.steering.angle_sentinel", "hil_cmd_steering_angle_sentinel", True, "sensorStimulus"),
    _e("steering.speed_sentinel", "logical", 0, 1, "hil_cmd.steering.speed_sentinel", "hil_cmd_steering_speed_sentinel", True, "sensorStimulus"),
    _e("steering.calibration_sequence", "uint32", 0, 4294967295, "hil_cmd.steering.calibration_sequence", "hil_cmd_steering_calibration_sequence", True, "calibration"),
    _e("imu.dropout", "logical", 0, 1, "hil_cmd.imu.dropout", "hil_cmd_imu_dropout", True, "sensorStimulus"),
    _e("imu.stale", "logical", 0, 1, "hil_cmd.imu.stale", "hil_cmd_imu_stale", True, "sensorStimulus"),
    _e("imu.malformed", "logical", 0, 1, "hil_cmd.imu.malformed", "hil_cmd_imu_malformed", True, "sensorStimulus"),
    _e("digital.main_button", "logical", 0, 1, "hil_cmd.digital.main_button", "hil_cmd_digital_main_button", True, "digital"),
    _e("digital.cooling_switch", "logical", 0, 1, "hil_cmd.digital.cooling_switch", "hil_cmd_digital_cooling_switch", True, "digital"),
    _e("digital.shutdown_feedback", "logical", 0, 1, "hil_cmd.digital.shutdown_feedback", "hil_cmd_digital_shutdown_feedback", True, "digital"),
    _e("digital.precharge_sequence", "uint32", 0, 4294967295, "hil_cmd.digital.precharge_sequence", "hil_cmd_digital_precharge_sequence", True, "momentary"),
    _e("digital.main_button_sequence", "uint32", 0, 4294967295, "hil_cmd.digital.main_button_sequence", "hil_cmd_digital_main_button_sequence", True, "momentary"),
    _e("electrical.dc_link12_v", "double", 0, 1023.984375, "hil_cmd.dc_link12_v", "hil_cmd_dc_link12_v", True, "electrical"),
    _e("electrical.dc_link34_v", "double", 0, 1023.984375, "hil_cmd.dc_link34_v", "hil_cmd_dc_link34_v", True, "electrical"),
    _e("inverter1.load_nm", "double", -200, 200, "hil_cmd.inverter(1).load_nm", "hil_cmd_inverter1_load_nm", True, "plant"),
    _e("inverter2.load_nm", "double", -200, 200, "hil_cmd.inverter(2).load_nm", "hil_cmd_inverter2_load_nm", True, "plant"),
    _e("inverter3.load_nm", "double", -200, 200, "hil_cmd.inverter(3).load_nm", "hil_cmd_inverter3_load_nm", True, "plant"),
    _e("inverter4.load_nm", "double", -200, 200, "hil_cmd.inverter(4).load_nm", "hil_cmd_inverter4_load_nm", True, "plant"),
    _e("inverter1.connected", "logical", 0, 1, "hil_cmd.inverter(1).connected", "hil_cmd_inverter1_connected", True, "plant"),
    _e("inverter2.connected", "logical", 0, 1, "hil_cmd.inverter(2).connected", "hil_cmd_inverter2_connected", True, "plant"),
    _e("inverter3.connected", "logical", 0, 1, "hil_cmd.inverter(3).connected", "hil_cmd_inverter3_connected", True, "plant"),
    _e("inverter4.connected", "logical", 0, 1, "hil_cmd.inverter(4).connected", "hil_cmd_inverter4_connected", True, "plant"),
    _e("inverter1.fault_mask", "uint32", 0, 4294967295, "hil_cmd.inverter(1).fault_mask", "hil_cmd_inverter1_fault_mask", True, "fault"),
    _e("inverter2.fault_mask", "uint32", 0, 4294967295, "hil_cmd.inverter(2).fault_mask", "hil_cmd_inverter2_fault_mask", True, "fault"),
    _e("inverter3.fault_mask", "uint32", 0, 4294967295, "hil_cmd.inverter(3).fault_mask", "hil_cmd_inverter3_fault_mask", True, "fault"),
    _e("inverter4.fault_mask", "uint32", 0, 4294967295, "hil_cmd.inverter(4).fault_mask", "hil_cmd_inverter4_fault_mask", True, "fault"),
    _e("can.drop_control_mask", "uint8", 0, 255, "hil_cmd.can.drop_control_mask", "hil_cmd_can_drop_control_mask", True, "canFault"),
    _e("can.drop_status_mask", "uint16", 0, 65535, "hil_cmd.can.drop_status_mask", "hil_cmd_can_drop_status_mask", True, "canFault"),
    _e("gui_heartbeat", "uint32", 0, 4294967295, "hil_cmd.gui_heartbeat", "hil_cmd_gui_heartbeat", True, "heartbeat"),
    _e("pedals.plausibility_override", "logical", 0, 1, "hil_cmd.pedals.plausibility_override", "hil_cmd_pedals_plausibility_override", False, "pedals"),
    _e("cal.pedals.released_v1", "double", 0, 5, "hil_cal.pedals.releasedV(1)", "hil_cal_pedals_released_v1", False, "calibration"),
    _e("cal.pedals.released_v2", "double", 0, 5, "hil_cal.pedals.releasedV(2)", "hil_cal_pedals_released_v2", False, "calibration"),
    _e("cal.pedals.released_v3", "double", 0, 5, "hil_cal.pedals.releasedV(3)", "hil_cal_pedals_released_v3", False, "calibration"),
    _e("cal.pedals.released_v4", "double", 0, 5, "hil_cal.pedals.releasedV(4)", "hil_cal_pedals_released_v4", False, "calibration"),
    _e("cal.pedals.pressed_v1", "double", 0, 5, "hil_cal.pedals.pressedV(1)", "hil_cal_pedals_pressed_v1", False, "calibration"),
    _e("cal.pedals.pressed_v2", "double", 0, 5, "hil_cal.pedals.pressedV(2)", "hil_cal_pedals_pressed_v2", False, "calibration"),
    _e("cal.pedals.pressed_v3", "double", 0, 5, "hil_cal.pedals.pressedV(3)", "hil_cal_pedals_pressed_v3", False, "calibration"),
    _e("cal.pedals.pressed_v4", "double", 0, 5, "hil_cal.pedals.pressedV(4)", "hil_cal_pedals_pressed_v4", False, "calibration"),
)


def parameterContract() -> tuple[ParameterEntry, ...]:
    return PARAMETER_CONTRACT


@dataclass(frozen=True)
class ResolvedEntry:
    name: str
    type: str
    minimum: float
    maximum: float
    group: str
    required: bool
    path: str
    backing: str


@dataclass(frozen=True)
class ResolvedContract:
    entries: tuple[ResolvedEntry, ...]
    names: tuple[str, ...]
    missing: tuple[str, ...]
    structCount: int
    flatCount: int
    backing: str
    resolvedCount: int


def discoverContract(availablePaths: Iterable[str], contract: Sequence[ParameterEntry] | None = None) -> ResolvedContract:
    contract = tuple(PARAMETER_CONTRACT if contract is None else contract)
    if not contract:
        raise ValueError("Contract must be a nonempty structure array.")
    if isinstance(availablePaths, str):
        paths = (availablePaths,)
    else:
        try:
            paths = tuple(availablePaths)
        except TypeError as exc:
            raise TypeError("Available parameter paths must be a sequence of names.") from exc
    if any(not isinstance(path, str) or not path for path in paths):
        raise TypeError("Every available parameter path must be a nonempty name.")
    available = set(paths)
    entries, missing, missing_required = [], [], []
    struct_count = flat_count = 0
    for item in contract:
        if item.structPath in available:
            path, backing = item.structPath, "struct"
            struct_count += 1
        elif item.flatPath in available:
            path, backing = item.flatPath, "flat"
            flat_count += 1
        else:
            missing.append(item.name)
            if item.required:
                missing_required.append(f"{item.name} ({item.structPath} | {item.flatPath})")
            continue
        entries.append(ResolvedEntry(item.name, item.type, item.minimum, item.maximum, item.group, item.required, path, backing))
    if missing_required:
        raise RuntimeError(
            f"The connected application does not expose {len(missing_required)} required parameter(s):\n  "
            + "\n  ".join(missing_required)
        )
    backing = "mixed" if struct_count and flat_count else "flat" if flat_count else "struct" if struct_count else "none"
    return ResolvedContract(tuple(entries), tuple(x.name for x in entries), tuple(missing), struct_count, flat_count, backing, len(entries))


def contractEntry(source, name: object):
    if not isinstance(name, str) or not name:
        return None
    entries = source.entries if isinstance(source, ResolvedContract) else source
    try:
        return next(item for item in entries if item.name == name)
    except (StopIteration, TypeError, AttributeError):
        return None
