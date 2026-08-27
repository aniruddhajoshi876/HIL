import math


def _flag(value, name):
    if not isinstance(value, (bool, int, float)) or not math.isfinite(float(value)) or float(value) not in (0, 1):
        raise ValueError(f"{name} must be logical 0 or 1.")
    return bool(value)


def evaluateCanDiagnostics(writeSucceeded, backlog, receiveOverrun, errorWarning, busOff):
    if not isinstance(writeSucceeded, (list, tuple)) or len(writeSucceeded) != 9 or any(not isinstance(x, bool) for x in writeSucceeded):
        raise ValueError("writeSucceeded must be a 1x9 logical vector.")
    flags = [_flag(v, n) for v, n in zip((backlog, receiveOverrun, errorWarning, busOff),
                                         ("backlog", "receiveOverrun", "errorWarning", "busOff"))]
    mask = sum(1 << i for i, ok in enumerate(writeSucceeded) if not ok)
    return {"writeSucceeded": list(writeSucceeded), "failedWriteMask": mask, "backlog": flags[0],
            "receiveOverrun": flags[1], "errorWarning": flags[2], "busOff": flags[3],
            "cycleSucceeded": all(writeSucceeded) and not any(flags)}
