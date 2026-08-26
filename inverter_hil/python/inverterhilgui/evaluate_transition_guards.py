import math


def _numeric(source, field, fallback):
    value = source.get(field) if isinstance(source, dict) else None
    return float(value) if isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value) else fallback


def _logical(snapshot, field, name, required):
    result = {"name": name, "actual": "--", "required": required, "pass": False, "known": False}
    value = snapshot.get(field) if isinstance(snapshot, dict) else None
    if isinstance(value, (bool, int, float)) and math.isfinite(float(value)) and float(value) in (0, 1):
        result.update(actual=required if bool(value) else "NOT MET", **{"pass": bool(value)}, known=True)
    return result


def _threshold(snapshot, field, name, required, units):
    result = {"name": name, "actual": "--", "required": f">= {required:.1f} {units}", "pass": False, "known": False}
    value = snapshot.get(field) if isinstance(snapshot, dict) else None
    if isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value):
        result.update(actual=f"{float(value):.1f} {units}", **{"pass": value >= required}, known=True)
    return result


def evaluateTransitionGuards(snapshot, thresholds=None):
    thresholds = thresholds if isinstance(thresholds, dict) else {}
    brake = _numeric(thresholds, "brakePercent", 20); dc = _numeric(thresholds, "dcLinkMinimumV", 350)
    return [
        _logical(snapshot, "mainButton", "Main button", "PRESSED"),
        _threshold(snapshot, "brakePercent", "Brake threshold", brake, "%"),
        _threshold(snapshot, "dcLink12V", "DC-link pair 1/2", dc, "V"),
        _threshold(snapshot, "dcLink34V", "DC-link pair 3/4", dc, "V"),
        _logical(snapshot, "plausibilityOk", "Driver-input plausibility", "VALID"),
    ]
