from ._wire import payload_to_u64, field, unsigned


def decodeSystemStatus(payload):
    raw = payload_to_u64(payload)
    return {"dcLink12V": unsigned(field(raw, 0, 16), 1 / 64, 16),
            "dcLink34V": unsigned(field(raw, 16, 16), 1 / 64, 16),
            "switchingFrequencyKHz": unsigned(field(raw, 32, 16), 1 / 512, 16),
            "dcLink12AboveMinimum": bool(field(raw, 48, 1)),
            "dcLink34AboveMinimum": bool(field(raw, 49, 1)),
            "controlEnable": bool(field(raw, 50, 1)), "controlDisable": bool(field(raw, 51, 1))}
