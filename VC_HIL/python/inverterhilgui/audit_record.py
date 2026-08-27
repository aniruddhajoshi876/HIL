import math
from datetime import datetime


def _text(info, name):
    value = info.get(name)
    return value if isinstance(value, str) else ""


def _value_text(value):
    if isinstance(value, str): return value or "--"
    if isinstance(value, bool): return "true" if value else "false"
    if isinstance(value, int): return str(value)
    if isinstance(value, float) and math.isnan(value): return "--"
    if isinstance(value, float) and not isinstance(value, complex): return f"{value:.6g}"
    return "--"


def _timestamp(value=None):
    if isinstance(value, str) and value: return value
    if isinstance(value, datetime): return value.strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    return datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]


def auditRecord(info):
    record = {"hostTime": "", "targetTimeS": math.nan, "logicalName": "", "targetPath": "",
              "requested": "--", "applied": "--", "result": "rejected", "detail": "malformed_audit_input"}
    if not isinstance(info, dict):
        record["hostTime"] = _timestamp()
        return record
    record["hostTime"] = _timestamp(info.get("hostTime"))
    target = info.get("targetTimeS")
    if isinstance(target, (int, float)) and not isinstance(target, bool): record["targetTimeS"] = float(target)
    record["logicalName"] = _text(info, "logicalName"); record["targetPath"] = _text(info, "targetPath")
    if "requested" in info: record["requested"] = _value_text(info["requested"])
    if "applied" in info: record["applied"] = _value_text(info["applied"])
    if "detail" in info: record["detail"] = _text(info, "detail")
    if not record["logicalName"]:
        record["detail"] = "missing_logical_name"; return record
    result = _text(info, "result")
    if result not in {"applied", "clamped", "mismatch", "failed", "rejected", "fallback", "lifecycle"}:
        record["detail"] = "unknown_result_code"; return record
    record["result"] = result
    return record
