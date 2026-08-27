"""Fail-closed command type/range validation."""

import math
from .parameter_contract import contractEntry


def _scalar_number(value):
    return isinstance(value, (int, float, bool)) and not isinstance(value, complex) and math.isfinite(float(value))


def validateCommandValue(source, name, value):
    result = {"name": "", "value": None, "accepted": False, "clamped": False, "reason": "unknown_logical_name"}
    if not isinstance(name, str) or not name:
        result["reason"] = "malformed_logical_name"
        return result
    result["name"] = name
    entry = contractEntry(source, name)
    if entry is None:
        return result
    for field in ("type", "minimum", "maximum"):
        if not hasattr(entry, field):
            result["reason"] = f"missing_contract_{field}"
            return result
    if not all(_scalar_number(x) for x in (entry.minimum, entry.maximum)) or entry.minimum > entry.maximum:
        result["reason"] = "malformed_contract_range"
        return result
    if not _scalar_number(value):
        result["reason"] = "malformed_value"
        return result
    numeric = float(value)
    if entry.type == "double":
        output = min(max(numeric, entry.minimum), entry.maximum)
        result["clamped"] = output != numeric
        result["value"] = output
    elif entry.type == "logical":
        if numeric not in (0, 1):
            result["reason"] = "value_not_logical"
            return result
        result["value"] = bool(numeric)
    elif entry.type in ("uint8", "uint16", "uint32"):
        if numeric != math.floor(numeric):
            result["reason"] = "value_not_integer"
            return result
        if numeric < 0:
            result["reason"] = "value_negative"
            return result
        output = int(min(max(numeric, entry.minimum), entry.maximum))
        result["clamped"] = output != numeric
        result["value"] = output
    else:
        result["reason"] = "unsupported_contract_type"
        return result
    result["accepted"] = True
    result["reason"] = "clamped" if result["clamped"] else "accepted"
    return result
