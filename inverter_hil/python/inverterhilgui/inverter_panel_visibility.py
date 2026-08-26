def inverterPanelVisibility(expanded):
    if not isinstance(expanded, bool):
        raise ValueError("Expanded state must be a logical scalar.")
    fields = ("STATE", "READY", "CMD AGE", "TORQUE CMD", "TORQUE ACT", "SPEED",
              "Id set/act", "Iq set/act", "MOTOR TEMP", "SWITCH TEMP", "DERATING", "ACTIVE FAULT")
    summary = {"TORQUE CMD", "TORQUE ACT", "MOTOR TEMP"}
    visible = tuple(True if expanded else name in summary for name in fields)
    return visible, tuple(20 if item else 0 for item in visible), fields
