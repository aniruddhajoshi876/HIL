import math
from .gui_theme import guiTheme


def _finite(value):
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(float(value))


def formatMeasurement(value, rawCount, units="", capturePending=False):
    units = units if isinstance(units, str) else ""
    pending = isinstance(capturePending, (bool, int, float)) and math.isfinite(float(capturePending)) and float(capturePending) != 0
    result = {"value": "--", "raw": "--", "status": guiTheme()["text"]["capturePending"] if pending else "",
              "combined": "--", "hasData": False}
    has_value = _finite(value)
    has_raw = _finite(rawCount) and float(rawCount).is_integer()
    if has_value:
        result["value"] = f"{float(value):.3f}" + (f" {units}" if units else "")
    if has_raw:
        result["raw"] = str(int(rawCount))
    if not has_value and not has_raw:
        return result
    result["hasData"] = True
    result["combined"] = f'{result["value"]} ({result["raw"]} cnt)'
    if result["status"]:
        result["combined"] += f'  {result["status"]}'
    return result
