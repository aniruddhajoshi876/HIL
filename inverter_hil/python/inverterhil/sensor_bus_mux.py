import math


def _normalize(source, kind):
    blank = {"id": 0, "dlc": 0, "payload": [0] * 8, "timestampS": math.nan, "sequence": 0, "valid": False, "kind": kind}
    if not isinstance(source, dict) or not source.get("valid"): return blank
    for name in ("id", "dlc", "payload", "timestampS", "sequence"):
        if name not in source: raise ValueError(f"Sensor frame lacks {name}.")
    blank.update(id=int(source["id"]), dlc=int(source["dlc"]), payload=[int(x) & 255 for x in source["payload"]],
                 timestampS=float(source["timestampS"]), sequence=int(source["sequence"]), valid=bool(source["valid"]))
    return blank


def sensorBusMux(imuFrame, steeringFrame):
    return sorted((x for x in (_normalize(imuFrame, "imu"), _normalize(steeringFrame, "steering")) if x["valid"]),
                  key=lambda x: (x["timestampS"], x["sequence"]))
