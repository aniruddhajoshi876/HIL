import math


def formatTorqueCandidates(rawCount):
    result = {"raw": "--", "nm256": "--", "nm512": "--", "summary": "--", "hasData": False}
    if not isinstance(rawCount, (int, float)) or isinstance(rawCount, bool) or not math.isfinite(float(rawCount)) or float(rawCount) != int(rawCount) or not -32768 <= rawCount <= 32767:
        return result
    count = int(rawCount)
    result.update(raw=str(count), nm256=f"{count / 256:.3f}", nm512=f"{count / 512:.3f}", hasData=True)
    result["summary"] = f'{result["raw"]} cnt | {result["nm256"]} Nm @1/256 | {result["nm512"]} Nm @1/512'
    return result
