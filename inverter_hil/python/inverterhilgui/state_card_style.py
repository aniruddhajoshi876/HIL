def stateCardStyle(currentState, cardState, errorActive=False):
    if not isinstance(currentState, str) or not currentState.strip() or errorActive:
        return "unknown"
    names = ("LV_ON", "PRECHARGING", "ENABLE", "BUZZING", "RTD")
    try:
        current, card = names.index(currentState.upper()), names.index(cardState.upper())
    except (ValueError, AttributeError):
        return "unknown"
    return "active" if current == card else "passed" if card < current else "upcoming"
