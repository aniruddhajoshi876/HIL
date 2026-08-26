import math
from .gui_theme import guiTheme


def formatPinState(state):
    theme = guiTheme()
    result = {"text": theme["text"]["noData"], "color": theme["color"]["secondaryText"], "known": False}
    if not isinstance(state, (bool, int, float)) or not math.isfinite(float(state)) or float(state) not in (0, 1):
        return result
    result.update(text="ON" if bool(state) else "OFF",
                  color=theme["color"]["healthy"] if bool(state) else theme["color"]["disabledText"], known=True)
    return result
