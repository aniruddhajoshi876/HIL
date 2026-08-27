import math


def _field(source, path):
    value = source
    for part in path.split("."): value = value[part]
    return value


def safeIoOutputs(command, cal):
    out = {"analogV": [0.0] * 4, "digital": [False] * 8, "armed": False, "reason": "safe_zero"}
    required = ("applicationRunning", "ioHealthy", "armed", "heartbeatAgeS", "throttle", "brake", "digital")
    if not isinstance(command, dict): return out
    for name in required:
        if name not in command: out["reason"] = f"missing_{name}"; return out
    for name in ("applicationRunning", "ioHealthy", "armed"):
        value = command[name]
        if not isinstance(value, (bool, int, float)) or not math.isfinite(float(value)) or float(value) not in (0, 1): out["reason"] = "malformed_interlock"; return out
        if not bool(value): out["reason"] = "not_armed"; return out
    age = command["heartbeatAgeS"]
    try: timeout = cal["guiHeartbeatTimeoutS"]
    except (TypeError, KeyError): timeout = math.nan
    if not isinstance(age, (int, float)) or isinstance(age, bool) or not math.isfinite(age) or age < 0 or age > timeout: out["reason"] = "heartbeat_expired"; return out
    pedals = (command["throttle"], command["brake"])
    if any(not isinstance(x, (int, float)) or isinstance(x, bool) or not math.isfinite(x) for x in pedals): out["reason"] = "malformed_pedal_command"; return out
    digital = command["digital"]
    if not isinstance(digital, (list, tuple)) or len(digital) != 8 or any(not isinstance(x, (bool, int, float)) or not math.isfinite(float(x)) or float(x) not in (0, 1) for x in digital): out["reason"] = "malformed_digital_command"; return out
    try:
        pcal = cal["pedals"]; released = list(pcal["releasedV"]); pressed = list(pcal["pressedV"])
        lo, hi = pcal["minimumV"], pcal["maximumV"]
        demand = [max(0.0, min(1.0, float(command["throttle"]))) ] * 2 + [max(0.0, min(1.0, float(command["brake"]))) ] * 2
        voltage = [max(lo, min(hi, r + d * (p - r))) for r, p, d in zip(released, pressed, demand)]
    except (KeyError, TypeError): voltage = [math.nan] * 4
    if any(not math.isfinite(x) for x in voltage): out["reason"] = "nonfinite_output_blocked"; return out
    out.update(analogV=voltage, digital=[bool(x) for x in digital], armed=True, reason="armed")
    return out
