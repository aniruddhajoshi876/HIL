import math


def safeFallbackPlan(health):
    plan = {"analogV": [0.0] * 4, "digital": [False] * 8, "applyFallback": True, "reason": "malformed_health"}
    required = ("applicationRunning", "targetConnected", "applicationLoaded", "ioHealthy", "heartbeatAgeS", "heartbeatTimeoutS")
    if not isinstance(health, dict): return plan
    for name in required:
        if name not in health: plan["reason"] = f"missing_{name}"; return plan
    for name, reason in zip(("targetConnected", "applicationLoaded", "applicationRunning", "ioHealthy"),
                            ("target_disconnected", "application_unloaded", "application_stopped", "io_unhealthy")):
        value = health[name]
        if not isinstance(value, (bool, int, float)) or not math.isfinite(float(value)) or float(value) not in (0, 1): plan["reason"] = "malformed_health_flag"; return plan
        if not bool(value): plan["reason"] = reason; return plan
    age, timeout = health["heartbeatAgeS"], health["heartbeatTimeoutS"]
    if not isinstance(timeout, (int, float)) or isinstance(timeout, bool) or not math.isfinite(timeout) or timeout <= 0: plan["reason"] = "malformed_heartbeat_timeout"; return plan
    if not isinstance(age, (int, float)) or isinstance(age, bool) or not math.isfinite(age) or age < 0 or age > timeout: plan["reason"] = "heartbeat_expired"; return plan
    plan.update(applyFallback=False, reason="healthy")
    return plan
