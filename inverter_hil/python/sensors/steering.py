"""Host Bosch LWS frame chain with the status-byte truth table preserved."""

import math
from ._util import matlab_round

_C = {"standardId": 0x2B0, "standardDlc": 5, "angleScale": 0.1, "speedScale": 4,
      "minimumAngle": -780, "maximumAngle": 780, "minimumSpeed": 0, "maximumSpeed": 1016,
      "trimMask": 4, "calMask": 2, "okMask": 1, "angleSentinel": 0x7FFF, "speedSentinel": 0xFF}


def _contract(contract):
    if contract is None: return _C
    # Accept either the compact Python shape or a MATLAB-like nested dict.
    if "byteIndex" not in contract: return contract
    return {"standardId": contract["standardId"], "standardDlc": contract["standardDlc"],
            "angleScale": contract["angleScaleDegPerCount"], "speedScale": contract["speedScaleDegPerSPerCount"],
            "minimumAngle": contract["minimumAngleDeg"], "maximumAngle": contract["maximumAngleDeg"],
            "minimumSpeed": contract["minimumSpeedDegPerS"], "maximumSpeed": contract["maximumSpeedDegPerS"],
            "trimMask": contract["status"]["trimMask"], "calMask": contract["status"]["calMask"],
            "okMask": contract["status"]["okMask"], "angleSentinel": contract["angleFailureSentinel"],
            "speedSentinel": contract["speedFailureSentinel"]}


def packLwsFrame(angleDeg, speedDegPerS, status=None, contract=None):
    c = _contract(contract); status = {"trim": True, "cal": True, "ok": True} if status is None else status
    trim, cal, ok = bool(status["trim"]), bool(status["cal"]), bool(status["ok"])
    combo = (trim, ok, cal)
    if combo == (True, True, True): angle_sentinel = speed_sentinel = False
    elif combo == (True, True, False): angle_sentinel, speed_sentinel = True, False
    elif combo in ((True, False, False), (False, False, False)): angle_sentinel = speed_sentinel = True
    else: raise ValueError(f'TRIM={int(trim)} OK={int(ok)} CAL={int(cal)} is listed under "Other combinations for TRIM, OK and CAL are not valid".')
    if not angle_sentinel:
        if not isinstance(angleDeg, (int, float)) or isinstance(angleDeg, bool) or not math.isfinite(angleDeg) or not c["minimumAngle"] <= angleDeg <= c["maximumAngle"]: raise ValueError("LWS angle is outside the Bosch range.")
        angle_raw = matlab_round(angleDeg / c["angleScale"])
        if not -32768 <= angle_raw <= 32767: raise ValueError("LWS angle cannot be represented on the wire.")
    else: angle_raw = c["angleSentinel"]
    if not speed_sentinel:
        if not isinstance(speedDegPerS, (int, float)) or isinstance(speedDegPerS, bool) or not math.isfinite(speedDegPerS) or not c["minimumSpeed"] <= speedDegPerS <= c["maximumSpeed"]: raise ValueError("LWS speed is outside the Bosch range.")
        speed_raw = matlab_round(speedDegPerS / c["speedScale"])
        if not 0 <= speed_raw < c["speedSentinel"]: raise ValueError("LWS speed cannot be represented on the wire.")
    else: speed_raw = c["speedSentinel"]
    status_byte = int(trim) * c["trimMask"] + int(cal) * c["calMask"] + int(ok) * c["okMask"]
    raw = angle_raw % 65536; payload = [raw & 255, (raw >> 8) & 255, speed_raw, status_byte, 0]
    return {"id": c["standardId"], "dlc": c["standardDlc"], "payload": payload,
            "angleDeg": math.nan if angle_sentinel else angle_raw * c["angleScale"],
            "speedDegPerS": math.nan if speed_sentinel else speed_raw * c["speedScale"],
            "status": {"trim": trim, "cal": cal, "ok": ok}, "angleIsSentinel": angle_sentinel,
            "speedIsSentinel": speed_sentinel, "timestampS": math.nan}


def decodeLwsFrame(frame, contract=None):
    c = _contract(contract); payload = list(frame["payload"])
    if int(frame["id"]) != c["standardId"] or len(payload) < c["standardDlc"]: raise ValueError("Frame ID or DLC does not match LWS_Standard.")
    angle_u16 = payload[0] | payload[1] << 8; speed_raw = payload[2]; status = payload[3]
    trim, cal, ok = bool(status & c["trimMask"]), bool(status & c["calMask"]), bool(status & c["okMask"])
    valid_combo = (trim, ok, cal) in ((True, True, True), (True, True, False), (True, False, False), (False, False, False))
    angle_sentinel, speed_sentinel = angle_u16 == c["angleSentinel"], speed_raw == c["speedSentinel"]
    angle = math.nan if angle_sentinel else (angle_u16 - 65536 if angle_u16 >= 32768 else angle_u16) * c["angleScale"]
    speed = math.nan if speed_sentinel else speed_raw * c["speedScale"]
    return {"angleDeg": angle, "speedDegPerS": speed, "trim": trim, "cal": cal, "ok": ok,
            "statusCombinationValid": valid_combo, "angleIsSentinel": angle_sentinel,
            "speedIsSentinel": speed_sentinel, "reservedByte": payload[4],
            "valid": valid_combo and trim and cal and ok and not angle_sentinel and not speed_sentinel}


def stepSteeringSensor(previous, timeS, input=None):
    previous = {"angleDeg": 0, "sequence": 0} if not previous else dict(previous)
    input = {"angleDeg": 0, "status": {"trim": True, "cal": True, "ok": True}, "dropout": False} if not input else input
    nxt = dict(previous); nxt["sequence"] = previous["sequence"] + 1
    if "angleDeg" not in input: raise ValueError("Steering input must contain angleDeg.")
    nxt["angleDeg"] = input["angleDeg"]
    frame = {"id": 0, "dlc": 0, "payload": [0] * 8, "timestampS": timeS, "sequence": nxt["sequence"], "valid": False}
    if input.get("dropout"): return nxt, frame
    frame = packLwsFrame(input["angleDeg"], 0, input["status"])
    frame.update(timestampS=timeS, sequence=nxt["sequence"], valid=True)
    return nxt, frame
