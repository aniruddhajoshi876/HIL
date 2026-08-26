import math


def sequenceCommand(current):
    if not isinstance(current, (int, float, bool)) or isinstance(current, complex) or not math.isfinite(float(current)):
        raise ValueError("Sequence counter must be a real finite numeric scalar.")
    value = float(current)
    if value < 0 or value > 4294967295 or not value.is_integer():
        raise ValueError("Sequence counter must be a whole number within uint32 range.")
    return 0 if value == 4294967295 else int(value) + 1
