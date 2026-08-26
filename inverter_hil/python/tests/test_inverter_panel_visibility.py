import pytest
import inverterhilgui as gui


def test_collapsed_state_shows_only_three_summary_fields():
    visible, heights, names = gui.inverterPanelVisibility(False)
    assert [name for name, show in zip(names, visible) if show] == ["TORQUE CMD", "TORQUE ACT", "MOTOR TEMP"]
    assert [height for height in heights if height] == [20, 20, 20]


def test_expanded_state_shows_all_fields():
    visible, heights, names = gui.inverterPanelVisibility(True)
    assert len(names) == 12 and all(visible) and heights == (20,) * 12


@pytest.mark.parametrize("bad", [0, 1, None, "true", [True]])
def test_malformed_expanded_state_rejected(bad):
    with pytest.raises(ValueError): gui.inverterPanelVisibility(bad)


def test_one_panel_state_does_not_affect_another():
    first = gui.inverterPanelVisibility(True)
    second = gui.inverterPanelVisibility(False)
    assert all(first[0]) and sum(second[0]) == 3
