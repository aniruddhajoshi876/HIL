import math


def trackVcuStateEntry(currentState, previousState, previousEnteredS, nowS):
    if not isinstance(currentState, str) or not isinstance(previousState, str):
        raise ValueError("VCU states must be strings.")
    if not isinstance(previousEnteredS, (int, float)) or isinstance(previousEnteredS, bool):
        raise ValueError("previousEnteredS must be a real numeric scalar.")
    if not isinstance(nowS, (int, float)) or isinstance(nowS, bool) or not math.isfinite(nowS):
        raise ValueError("nowS must be finite.")
    entered = nowS if currentState != previousState or not math.isfinite(previousEnteredS) else previousEnteredS
    return entered, nowS - entered
