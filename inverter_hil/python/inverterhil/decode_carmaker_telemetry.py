from ._wire import payload8, payload_to_u64, field, signed


def decodeCarMakerTelemetry(torquePayload, readyPayload):
    torque, ready = payload8(torquePayload), payload8(readyPayload)
    if ready[0] & 0xF0 or any(ready[1:]):
        raise ValueError("0x502 reserved bits 4..63 must be zero.")
    traw, rraw = payload_to_u64(torque), payload_to_u64(ready)
    return {"torqueSetpointNm": [signed(field(traw, 16 * i, 16), 1 / 32, 16) for i in range(4)],
            "ready": [bool(field(rraw, i, 1)) for i in range(4)]}
