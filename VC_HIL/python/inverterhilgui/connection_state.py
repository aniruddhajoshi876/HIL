"""Pure target lifecycle state machine."""

STATES = {"disconnected", "connecting", "connected", "loaded", "running", "stopped", "error"}


def _allowed(state):
    result = dict.fromkeys(("connect", "disconnect", "load", "start", "stop", "reset"), False)
    mapping = {
        "disconnected": ("connect",), "connecting": ("disconnect",),
        "connected": ("disconnect", "load"),
        "loaded": ("disconnect", "load", "start"),
        "running": ("disconnect", "stop"),
        "stopped": ("disconnect", "load", "start", "reset"),
        "error": ("disconnect", "reset"),
    }
    for name in mapping.get(state, ("disconnect",)):
        result[name] = True
    return result


def _result(state, valid, reason):
    return {"state": state, "valid": valid, "reason": reason, "allowed": _allowed(state),
            "isConnected": state in {"connected", "loaded", "running", "stopped"},
            "isRunning": state == "running"}


def connectionState(currentState, event=None):
    current = currentState.strip() if isinstance(currentState, str) else ""
    if current not in STATES:
        return _result("error", False, "unknown_state")
    if event is None:
        return _result(current, True, "described")
    event = event.strip() if isinstance(event, str) else ""
    if not event:
        return _result(current, False, "malformed_event")
    if event == "fail":
        return _result("error", True, "failed")
    if event == "disconnect":
        return _result("disconnected", True, "disconnected")
    transitions = {
        ("disconnected", "connect"): "connecting",
        ("connecting", "connectSucceeded"): "connected",
        ("connecting", "connectFailed"): "disconnected",
        ("connected", "load"): "connected", ("connected", "loadSucceeded"): "loaded",
        ("loaded", "start"): "loaded", ("loaded", "startSucceeded"): "running",
        ("loaded", "loadSucceeded"): "loaded",
        ("running", "stop"): "running", ("running", "stopSucceeded"): "stopped",
        ("stopped", "startSucceeded"): "running", ("stopped", "reset"): "loaded",
        ("stopped", "loadSucceeded"): "loaded", ("error", "reset"): "connected",
    }
    if (current, event) not in transitions:
        return _result(current, False, "rejected_event")
    return _result(transitions[(current, event)], True, event)
