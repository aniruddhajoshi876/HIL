from ._wire import payload_to_u64, field, signed


def decodeStatus3X5(payload):
    raw = payload_to_u64(payload)
    return {"idSetpointA": signed(field(raw, 0, 12), 1 / 16, 12),
            "idActualA": signed(field(raw, 12, 12), 1 / 16, 12),
            "iqSetpointA": signed(field(raw, 24, 12), 1 / 16, 12),
            "iqActualA": signed(field(raw, 36, 12), 1 / 16, 12),
            "speedRpm": signed(field(raw, 48, 16), 1, 16)}
