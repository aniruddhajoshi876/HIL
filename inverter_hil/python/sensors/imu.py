"""Host MTi frame chain. Only constants consumed by these host functions live here."""

import math
from ._util import matlab_round

_VECTOR = {
    "acceleration": {"id": 0x034, "dlc": 6, "scale": 2 ** -8, "unit": "m/s^2", "rangeMax": 100},
    "rateOfTurn": {"id": 0x032, "dlc": 6, "scale": 2 ** -9, "unit": "rad/s", "rangeMax": 35},
    "eulerAngles": {"id": 0x022, "dlc": 6, "scale": 2 ** -7, "unit": "deg", "rangeMax": 180},
    "velocityXyz": {"id": 0x076, "dlc": 6, "scale": 2 ** -6, "unit": "m/s", "rangeMax": 500},
}


def packMti680Frame(kind, values, contract=None):
    # A custom contract may be supplied in the same dictionary shape.
    source = _VECTOR if contract is None else contract
    if not isinstance(kind, str) or kind not in source or not all(k in source[kind] for k in ("id", "dlc", "scale")):
        raise ValueError(f"Unsupported MTi message kind: {kind}.")
    item = source[kind]
    if item.get("fieldCount", 3) != 3: raise ValueError(f"MTi message {kind} is not a three-axis vector message.")
    if not isinstance(values, (list, tuple)) or len(values) != 3 or any(not isinstance(x, (int, float)) or isinstance(x, bool) or not math.isfinite(x) for x in values):
        raise ValueError("MTi vector must contain three finite values.")
    if "rangeMax" in item and any(abs(x) > item["rangeMax"] for x in values):
        raise ValueError(f"MTi {kind} value exceeds the documented +/-{item['rangeMax']:g} {item.get('unit', '')} range; the VCU discards the entire frame.")
    counts = [matlab_round(x / item["scale"]) for x in values]
    if any(x < -32768 or x > 32767 for x in counts): raise ValueError("MTi value exceeds signed int16 range.")
    payload = []
    for count in counts:
        raw = count % 65536; payload.extend(((raw >> 8) & 255, raw & 255))
    return {"id": int(item["id"]), "dlc": int(item["dlc"]), "payload": payload,
            "kind": kind, "values": list(values), "timestampS": math.nan}


def decodeMti680Frame(frame, contract=None):
    source = _VECTOR if contract is None else contract
    if not isinstance(frame, dict) or "id" not in frame or "payload" not in frame: raise ValueError("Frame must contain id and payload.")
    kind = next((name for name, item in source.items() if int(frame["id"]) == int(item["id"])), None)
    if kind is None: raise ValueError(f"Unknown MTi CAN ID 0x{int(frame['id']):03X}.")
    item = source[kind]; payload = list(frame["payload"])
    if len(payload) < item["dlc"]: raise ValueError("MTi payload is shorter than its contract DLC.")
    result = []
    for i in range(3):
        raw = (int(payload[2 * i]) << 8) | int(payload[2 * i + 1])
        result.append((raw - 65536 if raw >= 32768 else raw) * item["scale"])
    return result


def _blank(timeS, sequence):
    return {"id": 0, "dlc": 0, "payload": [0] * 8, "timestampS": timeS, "sequence": sequence, "valid": False, "kind": ""}


def _stamp(frame, timeS, sequence):
    frame.update(timestampS=timeS, sequence=sequence, valid=True); return frame


def stepImuSimulation(previous, timeS, vehicleState, input=None):
    previous = {"sequence": 0} if not previous else dict(previous)
    input = {"enabled": True, "dropout": False} if not input else dict(input)
    input.setdefault("enabled", True); input.setdefault("dropout", False)
    nxt = dict(previous); nxt["sequence"] = previous["sequence"] + 1
    frame = _blank(timeS, nxt["sequence"]); velocity = _blank(timeS, nxt["sequence"]); euler = _blank(timeS, nxt["sequence"])
    if not input["enabled"] or input["dropout"]: return nxt, frame, velocity, euler
    for name in ("accelerationMps2", "rateOfTurnRadPerS"):
        if not isinstance(vehicleState, dict) or name not in vehicleState: raise ValueError(f"Vehicle state lacks {name}.")
    frame = _stamp(packMti680Frame("acceleration", vehicleState["accelerationMps2"]), timeS, nxt["sequence"])
    if "velocityMps" in vehicleState: velocity = _stamp(packMti680Frame("velocityXyz", vehicleState["velocityMps"]), timeS, nxt["sequence"])
    if input.get("eulerEnabled") and "eulerAnglesDeg" in vehicleState: euler = _stamp(packMti680Frame("eulerAngles", vehicleState["eulerAnglesDeg"]), timeS, nxt["sequence"])
    return nxt, frame, velocity, euler
