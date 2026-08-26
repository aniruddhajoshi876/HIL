import math


def _flag(item, name):
    value = item.get(name) if isinstance(item, dict) else None
    return bool(value) if isinstance(value, (bool, int, float)) and math.isfinite(float(value)) and float(value) in (0, 1) else None


def canAckStatus(diagnostics, transmitting=False):
    result = {"text": "--", "acknowledged": None, "known": False}
    bus_off, warning = _flag(diagnostics, "busOff"), _flag(diagnostics, "errorWarning")
    if bus_off is None or warning is None: return result
    if bus_off: return {"text": "NOT ACKED (bus-off)", "acknowledged": False, "known": True}
    if warning: return {"text": "ACK ERRORS (error-warning)", "acknowledged": False, "known": True}
    valid_tx = isinstance(transmitting, (bool, int, float)) and math.isfinite(float(transmitting)) and bool(transmitting)
    return {"text": "ACK OK (no bus errors)", "acknowledged": True, "known": True} if valid_tx else result
