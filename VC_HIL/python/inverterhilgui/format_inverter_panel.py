import math
from .gui_theme import guiTheme
from .format_measurement import formatMeasurement
from .format_torque_candidates import formatTorqueCandidates


def _numeric(item, field):
    value = item.get(field, math.nan) if isinstance(item, dict) else math.nan
    return float(value) if isinstance(value, (int, float)) and not isinstance(value, bool) else math.nan


def _flag(item, field, yes, no, fallback):
    value = item.get(field) if isinstance(item, dict) else None
    return yes if value is True or value == 1 else no if value is False or value == 0 else fallback


def formatInverterPanel(snapshot, index):
    theme = guiTheme(); nd = theme["text"]["noData"]
    panel = dict.fromkeys(("title", "corner", "state", "ready", "commandAge", "torqueCommand",
                           "torqueActual", "torqueCommandRaw", "torqueActualRaw", "speed", "idCurrent",
                           "iqCurrent", "motorTemperature", "switchTemperature", "derating", "activeFault"), nd)
    panel.update(corner=theme["text"]["cornerLabel"], cornerVerified=False, hasData=False)
    if not isinstance(index, int) or isinstance(index, bool) or index not in range(1, 5):
        return panel
    panel.update(title=f"INV{index}", corner=("FL", "FR", "RR", "RL")[index - 1], cornerVerified=True)
    items = snapshot.get("inverter") if isinstance(snapshot, dict) else None
    if not isinstance(items, (list, tuple)) or len(items) < index or not isinstance(items[index - 1], dict):
        return panel
    item = items[index - 1]
    state = item.get("state")
    panel["state"] = state if isinstance(state, str) and state.strip() else nd
    panel["ready"] = _flag(item, "ready", "READY", "NOT READY", nd)
    panel["derating"] = _flag(item, "derating", "ACTIVE", "NONE", nd)
    fault = item.get("activeFault")
    panel["activeFault"] = fault if isinstance(fault, str) and fault.strip() else "NONE"
    age, speed = _numeric(item, "commandAgeS"), _numeric(item, "speedRpm")
    panel["commandAge"] = f"{age:.3f} s" if math.isfinite(age) else nd
    panel["speed"] = f"{speed:.0f} rpm" if math.isfinite(speed) else nd
    for key, a, b in (("idCurrent", "idSetpointA", "idActualA"), ("iqCurrent", "iqSetpointA", "iqActualA")):
        av, bv = _numeric(item, a), _numeric(item, b)
        if math.isfinite(av) or math.isfinite(bv):
            panel[key] = f'{av:.1f}' if math.isfinite(av) else nd
            panel[key] += f' / {bv:.1f}' if math.isfinite(bv) else f' / {nd}'
            panel[key] += " A"
    command = formatTorqueCandidates(_numeric(item, "torqueCommandRaw"))
    actual = formatTorqueCandidates(_numeric(item, "torqueActualRaw"))
    panel.update(torqueCommand=command["summary"], torqueActual=actual["summary"],
                 torqueCommandRaw=command["raw"], torqueActualRaw=actual["raw"])
    motor = formatMeasurement(_numeric(item, "motorTemperatureC"), _numeric(item, "motorTemperatureRaw"), "C", True)
    switch = formatMeasurement(_numeric(item, "switchTemperatureC"), _numeric(item, "switchTemperatureRaw"), "C", False)
    panel.update(motorTemperature=motor["combined"], switchTemperature=switch["combined"])
    panel["hasData"] = command["hasData"] or actual["hasData"] or motor["hasData"] or switch["hasData"] or panel["state"] != nd
    return panel
