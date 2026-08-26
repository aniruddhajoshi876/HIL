import math
from statistics import median


def canRowModel(observations, nowS, options=None):
    if not isinstance(observations, (list, tuple)):
        return []
    options = options if isinstance(options, dict) else {}
    highlight_s = _option(options, "highlightS", 0.5); stale_s = _option(options, "staleS", 0.1)
    valid_now = isinstance(nowS, (int, float)) and not isinstance(nowS, bool) and math.isfinite(nowS)
    rows = []
    for item in observations:
        item = item if isinstance(item, dict) else {}
        row = {"live": "NO DATA", "id": "--", "name": "--", "signal": "--", "value": "--",
               "rate": "--", "rateHz": math.nan, "count": "--", "lastSeenS": math.nan, "highlight": False}
        can_id = item.get("id")
        if isinstance(can_id, (int, float)) and not isinstance(can_id, bool) and math.isfinite(can_id) and can_id >= 0:
            row["id"] = f"0x{int(can_id):03X}"
        for key in ("name", "signal", "value"):
            value = item.get(key)
            if isinstance(value, str) and value.strip(): row[key] = value
        count = item.get("count")
        if isinstance(count, (int, float)) and not isinstance(count, bool) and math.isfinite(count) and count >= 0 and float(count).is_integer():
            row["count"] = str(int(count))
        stamps = item.get("timestampsS", [])
        stamps = sorted(float(x) for x in stamps if isinstance(x, (int, float)) and not isinstance(x, bool) and math.isfinite(x)) if isinstance(stamps, (list, tuple)) else []
        intervals = [b - a for a, b in zip(stamps, stamps[1:]) if b - a > 0]
        if intervals:
            row["rateHz"] = 1 / median(intervals); row["rate"] = f'{row["rateHz"]:.1f} Hz'
        if stamps:
            row["lastSeenS"] = stamps[-1]
            if valid_now:
                age = nowS - stamps[-1]
                row["live"] = "NO DATA" if age < 0 else "LIVE" if age <= stale_s else "STALE"
            else: row["live"] = "STALE"
        change = item.get("lastChangeS")
        if valid_now and isinstance(change, (int, float)) and not isinstance(change, bool) and math.isfinite(change):
            row["highlight"] = 0 <= nowS - change <= highlight_s
        rows.append(row)
    return rows


def _option(options, name, fallback):
    value = options.get(name)
    return float(value) if isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value) and value >= 0 else fallback
