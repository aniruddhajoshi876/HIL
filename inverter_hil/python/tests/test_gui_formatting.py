import math
import pytest
import inverterhilgui as gui


def test_torque_counts_show_both_scales_and_dashes():
    x = gui.formatTorqueCandidates(512)
    assert x["raw"] == "512" and x["nm256"] == "2.000" and x["nm512"] == "1.000"
    assert "@1/256" in x["summary"] and "@1/512" in x["summary"]
    assert gui.formatTorqueCandidates(math.nan)["summary"] == "--"


def test_measurements_and_pin_states():
    x = gui.formatMeasurement(400.125, 32008, "V", True)
    assert x["value"] == "400.125 V" and x["raw"] == "32008" and "CAPTURE PENDING" in x["combined"]
    assert gui.formatMeasurement(math.nan, math.nan, "V", False)["combined"] == "--"
    assert gui.formatPinState(True)["text"] == "ON"
    assert gui.formatPinState(False)["text"] == "OFF"
    assert not gui.formatPinState(None)["known"]


def test_transition_guards_and_unknown_fail_closed():
    rows = gui.evaluateTransitionGuards({"mainButton": True, "brakePercent": 25, "dcLink12V": 360,
                                        "dcLink34V": 349, "plausibilityOk": True},
                                       {"brakePercent": 20, "dcLinkMinimumV": 350})
    assert [x["name"] for x in rows] == ["Main button", "Brake threshold", "DC-link pair 1/2", "DC-link pair 3/4", "Driver-input plausibility"]
    assert [x["pass"] for x in rows] == [True, True, True, False, True]
    assert not any(x["pass"] or x["known"] for x in gui.evaluateTransitionGuards({}))


def test_inverter_panels_do_not_leak_and_corner_mapping_is_confirmed():
    snap = gui.blankTelemetry(); snap["inverter"][0].update(state="RUN", torqueCommandRaw=256)
    snap["inverter"][1].update(state="FAULT", torqueCommandRaw=-512)
    a, b = gui.formatInverterPanel(snap, 1), gui.formatInverterPanel(snap, 2)
    assert a["state"] == "RUN" and "256 cnt" in a["torqueCommand"] and "-512 cnt" in b["torqueCommand"]
    assert [gui.formatInverterPanel(snap, i)["corner"] for i in range(1, 5)] == ["FL", "FR", "RR", "RL"]
    assert gui.formatInverterPanel(snap, 0)["corner"] == "UNVERIFIED"


def test_state_cards_and_live_state_timer():
    assert gui.stateCardStyle("ENABLE", "LV_ON") == "passed"
    assert gui.stateCardStyle("ENABLE", "ENABLE") == "active"
    assert gui.stateCardStyle("ENABLE", "RTD") == "upcoming"
    entered, elapsed = gui.trackVcuStateEntry("LV_ON", "", math.nan, 100)
    assert (entered, elapsed) == (100, 0)
    assert gui.trackVcuStateEntry("LV_ON", "LV_ON", entered, 102.5) == (100, 2.5)


def test_can_rates_stale_highlight_and_counts():
    observation = {"id": 0x186, "name": "CTRL INV1", "signal": "torque", "value": "8192 cnt",
                   "timestampsS": [x * .005 for x in range(11)], "lastChangeS": .05, "count": 8135}
    row = gui.canRowModel([observation], .052)[0]
    assert row["id"] == "0x186" and row["rateHz"] == pytest.approx(200) and row["live"] == "LIVE" and row["highlight"]
    assert row["count"] == "8135"
    assert gui.canRowModel([{**observation, "timestampsS": [.05]}], .052)[0]["rate"] == "--"
    assert gui.canRowModel([observation], 15)[0]["live"] == "STALE"


def test_blank_telemetry_has_no_fabricated_values_and_expected_can_order():
    snap = gui.blankTelemetry()
    assert not snap["valid"] and math.isnan(snap["targetTimeS"])
    assert [x["name"] for x in snap["pins"]] == ["VC_SD_OUT", "MAIN_EN_OUT", "PRECH_EN_OUT", "INV_CTRL_EN", "INV_CTRL_DIS"]
    rows = gui.canRowModel(snap["can"]["rx"], 1)
    assert [x["id"] for x in rows] == ["0x1F5", "0x186", "0x196", "0x1A6", "0x1B6"]
    assert all(x["value"] == "--" and x["count"] == "--" for x in rows)
    tx = gui.canRowModel(snap["can"]["tx"], 1)
    assert [x["id"] for x in tx[-5:]] == ["0x034", "0x032", "0x076", "0x2B0", "0x7C0"]


def test_can_ack_uses_controller_flags_only():
    assert gui.canAckStatus({"busOff": False, "errorWarning": False}, True)["acknowledged"] is True
    assert not gui.canAckStatus({"busOff": False, "errorWarning": False}, False)["known"]
    assert gui.canAckStatus({"busOff": True, "errorWarning": False}, True)["acknowledged"] is False
    assert gui.canAckStatus({"busOff": False, "errorWarning": True}, True)["acknowledged"] is False


def _luminance(rgb):
    c = [x / 12.92 if x <= .03928 else ((x + .055) / 1.055) ** 2.4 for x in rgb]
    return .2126 * c[0] + .7152 * c[1] + .0722 * c[2]


def _contrast(a, b):
    x, y = _luminance(a), _luminance(b); return (max(x, y) + .05) / (min(x, y) + .05)


def test_theme_palette_and_disclosure_text():
    t = gui.guiTheme(); c = t["color"]
    assert c["tabBar"] == (0, 0, 0) and c["tabBarText"] == (1, 1, 1)
    assert _contrast(c["primaryText"], c["background"]) > 4.5
    assert _contrast(c["background"], c["fault"]) > 4.5
    assert "TORQUE SCALE UNVERIFIED" in t["text"]["torqueBanner"]
