def pedalCalibrationConstants():
    rows = (
        (1, "throttle 1", 30100, 23100, "convertThrottle1ToPercent (throttle1Max/Min)"),
        (2, "throttle 2", 63600, 46500, "convertThrottle2ToPercent (throttle2Max/Min)"),
        (3, "brake 1", 9025, 31800, "convertBrakeToPercent (brakeMin/Max)"),
        (4, "brake 2", 9025, 31800, "convertBrakeToPercent (brakeMin/Max)"),
    )
    return [{"channel": c, "name": n, "releasedRaw": r, "pressedRaw": p,
             "releasedV": r * 3.3 / 65535, "pressedV": p * 3.3 / 65535,
             "direction": "falling" if p < r else "rising", "source": s} for c, n, r, p, s in rows]
