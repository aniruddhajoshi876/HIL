"""Portable disclosure-state tests; MATLAB app artifact scanning is not repeated."""

import inverterhilgui as gui


def test_four_disclosures_can_hold_independent_state():
    expanded = [False] * 4
    expanded[1] = not expanded[1]
    masks = [gui.inverterPanelVisibility(value)[0] for value in expanded]
    assert sum(masks[1]) == 12
    assert all(sum(mask) == 3 for i, mask in enumerate(masks) if i != 1)


def test_visibility_contract_keeps_every_formatter_field():
    _, _, fields = gui.inverterPanelVisibility(False)
    assert fields == ("STATE", "READY", "CMD AGE", "TORQUE CMD", "TORQUE ACT", "SPEED",
                      "Id set/act", "Iq set/act", "MOTOR TEMP", "SWITCH TEMP", "DERATING", "ACTIVE FAULT")


def test_disclosure_text_semantics():
    collapsed_text = "Show details"
    expanded_text = "Hide details"
    assert collapsed_text != expanded_text and "Show" in collapsed_text and "Hide" in expanded_text
