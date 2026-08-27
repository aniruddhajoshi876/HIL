import math


def payload8(payload):
    if isinstance(payload, (bytes, bytearray)):
        values = list(payload)
    elif isinstance(payload, (list, tuple)):
        values = list(payload)
    else:
        raise ValueError("payload must be eight uint8 values")
    if len(values) != 8 or any(not isinstance(x, int) or isinstance(x, bool) or not 0 <= x <= 255 for x in values):
        raise ValueError("payload must be eight uint8 values")
    return values


def payload_to_u64(payload): return int.from_bytes(bytes(payload8(payload)), "little")
def field(raw, offset, width): return (raw >> offset) & ((1 << width) - 1)
def signed(bits, scale, width):
    bits &= (1 << width) - 1
    return (bits - (1 << width) if bits >= 1 << (width - 1) else bits) * scale
def unsigned(bits, scale, width): return (bits & ((1 << width) - 1)) * scale


def finite_scalar(value): return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(float(value))
