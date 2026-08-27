"""Single authority for GUI control-group enable state."""

import math
from .connection_state import connectionState


def _binary(value):
    return isinstance(value, (bool, int, float)) and math.isfinite(float(value)) and float(value) in (0, 1)


def controlPolicy(applicationState, vcuState, interlocks, canDriving=False):
    policy = {name: False for name in (
        "connectionControls", "pedals", "armPedals", "plausibilityViolation",
        "digitalStimuli", "sensorStimulus", "momentary", "electrical",
        "plantParameters", "calibration", "faultInjection", "canFaults",
        "canDriving", "expertGroupsUnlocked")}
    policy.update(logExport=True, reason="malformed_input")
    if not _binary(canDriving):
        policy["reason"] = "malformed_canDriving"
        return policy
    application = applicationState.strip() if isinstance(applicationState, str) else ""
    if not application:
        return policy
    lifecycle = connectionState(application)
    if not lifecycle["valid"]:
        policy["reason"] = "unknown_application_state"
        return policy
    policy["connectionControls"] = True
    required = ("expertMode", "plausibilityOverride", "targetHealthy", "heartbeatOk", "contractResolved")
    if not isinstance(interlocks, dict):
        policy["reason"] = "malformed_interlocks"
        return policy
    for name in required:
        if name not in interlocks:
            policy["reason"] = f"missing_{name}"
            return policy
        if not _binary(interlocks[name]):
            policy["reason"] = f"malformed_{name}"
            return policy
    if not lifecycle["isConnected"]:
        policy["reason"] = "not_connected"
        return policy
    running = lifecycle["isRunning"]
    policy.update(
        pedals=running and not bool(canDriving), canDriving=bool(canDriving),
        digitalStimuli=running, sensorStimulus=running, momentary=running,
        armPedals=running, plausibilityViolation=running,
        expertGroupsUnlocked=True, electrical=True, plantParameters=True,
        calibration=True, faultInjection=True, canFaults=True,
        reason="interlocks_removed_running" if running else "interlocks_removed_stopped",
    )
    return policy
