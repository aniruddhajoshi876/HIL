import math


def sensorScheduler(previous, timeS, input=None):
    previous = {"lastImuS": -math.inf, "lastLwsS": -math.inf, "imuSequence": 0, "lwsSequence": 0} if not previous else dict(previous)
    input = {"imuPeriodS": 0.005, "lwsPeriodS": 0.010} if not input else input
    if not isinstance(timeS, (int, float)) or isinstance(timeS, bool) or not math.isfinite(timeS) or timeS < 0: raise ValueError("Sensor time must be finite and nonnegative.")
    if any(name not in input or not isinstance(input[name], (int, float)) or input[name] <= 0 for name in ("imuPeriodS", "lwsPeriodS")): raise ValueError("Sensor periods must be positive.")
    nxt = dict(previous); due = {"imu": False, "lws": False, "timestampS": timeS, "imuSequence": previous["imuSequence"], "lwsSequence": previous["lwsSequence"]}
    epsilon = math.ulp(timeS + 1)
    if timeS - previous["lastImuS"] + epsilon >= input["imuPeriodS"]:
        due["imu"] = True; nxt["lastImuS"] = timeS; nxt["imuSequence"] = previous["imuSequence"] + 1; due["imuSequence"] = nxt["imuSequence"]
    if timeS - previous["lastLwsS"] + epsilon >= input["lwsPeriodS"]:
        due["lws"] = True; nxt["lastLwsS"] = timeS; nxt["lwsSequence"] = previous["lwsSequence"] + 1; due["lwsSequence"] = nxt["lwsSequence"]
    return nxt, due
