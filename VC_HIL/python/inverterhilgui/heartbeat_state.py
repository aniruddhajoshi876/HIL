import math
from .sequence_command import sequenceCommand


def heartbeatState(previous, nowS, timeoutS):
    result = {"counter": 0, "lastUpdateS": math.nan, "ageS": math.inf, "expired": True, "reason": "malformed_previous_state"}
    if not isinstance(previous, dict) or "counter" not in previous or "lastUpdateS" not in previous: return result
    counter = previous["counter"]
    if not isinstance(counter, (int, float, bool)) or not math.isfinite(float(counter)) or counter < 0 or counter > 4294967295 or float(counter) != int(counter):
        result["reason"] = "malformed_counter"; return result
    result["counter"] = int(counter)
    if not isinstance(nowS, (int, float)) or isinstance(nowS, bool) or not math.isfinite(nowS): result["reason"] = "malformed_now"; return result
    if not isinstance(timeoutS, (int, float)) or isinstance(timeoutS, bool) or not math.isfinite(timeoutS) or timeoutS <= 0: result["reason"] = "malformed_timeout"; return result
    last = previous["lastUpdateS"]
    if not isinstance(last, (int, float)) or isinstance(last, bool) or not math.isfinite(last):
        result.update(counter=sequenceCommand(counter), lastUpdateS=float(nowS), reason="no_previous_beat"); return result
    age = float(nowS) - float(last)
    if age < 0: result["reason"] = "host_clock_went_backwards"; return result
    expired = age > timeoutS
    result.update(counter=sequenceCommand(counter), lastUpdateS=float(nowS), ageS=age, expired=expired,
                  reason="heartbeat_expired" if expired else "healthy")
    return result
