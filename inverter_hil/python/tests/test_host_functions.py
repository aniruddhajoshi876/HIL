import math
import pytest
import inverterhil as hil
from sensors import decodeMti680Frame, decodeLwsFrame, packMti680Frame, packLwsFrame


def test_status_decoders_use_little_endian_bit_layout():
    raw = (16 << 0) | ((-16 % 4096) << 12) | (32 << 24) | ((-32 % 4096) << 36) | ((-1000 % 65536) << 48)
    status = hil.decodeStatus3X5(list(raw.to_bytes(8, "little")))
    assert status == {"idSetpointA": 1, "idActualA": -1, "iqSetpointA": 2,
                      "iqActualA": -2, "speedRpm": -1000}
    sysraw = 400 * 64 | (350 * 64 << 16) | (10 * 512 << 32) | (1 << 48) | (1 << 50)
    system = hil.decodeSystemStatus(list(sysraw.to_bytes(8, "little")))
    assert system["dcLink12V"] == 400 and system["controlEnable"] is True and system["controlDisable"] is False


def test_carmaker_reserved_bits_and_values():
    torque = b"".join(int(x * 32 % 65536).to_bytes(2, "little") for x in (1, -2, 3, -4))
    result = hil.decodeCarMakerTelemetry(torque, bytes([0b0101, 0, 0, 0, 0, 0, 0, 0]))
    assert result["torqueSetpointNm"] == [1, -2, 3, -4] and result["ready"] == [True, False, True, False]
    with pytest.raises(ValueError): hil.decodeCarMakerTelemetry(torque, bytes([0x10]) + bytes(7))


def test_can_diagnostics_mask():
    result = hil.evaluateCanDiagnostics([True, False, True, False, True, True, True, True, True], 0, 0, 0, 0)
    assert result["failedWriteMask"] == 0b1010 and not result["cycleSucceeded"]


def test_calibration_constants_and_safe_outputs():
    constants = hil.pedalCalibrationConstants()
    assert len(constants) == 4 and constants[0]["direction"] == "falling" and constants[2]["direction"] == "rising"
    cal = {"guiHeartbeatTimeoutS": 3, "pedals": {"releasedV": [x["releasedV"] for x in constants],
           "pressedV": [x["pressedV"] for x in constants], "minimumV": 0, "maximumV": 5}}
    command = {"applicationRunning": True, "ioHealthy": True, "armed": True, "heartbeatAgeS": .1,
               "throttle": .5, "brake": .25, "digital": [0, 1, 0, 1, 0, 1, 0, 1]}
    output = hil.safeIoOutputs(command, cal)
    assert output["armed"] and output["reason"] == "armed" and output["digital"][1]


def test_mti_round_trip_and_documented_range():
    frame = packMti680Frame("acceleration", [.5, -.25, 9.8])
    values = decodeMti680Frame(frame)
    assert values == pytest.approx([.5, -.25, round(9.8 * 256) / 256])
    with pytest.raises(ValueError): packMti680Frame("acceleration", [101, 0, 0])


def test_lws_truth_table_and_status_byte_position():
    frame = packLwsFrame(-30.1, 8, {"trim": True, "cal": True, "ok": True})
    assert frame["payload"][3] == 7 and frame["payload"][4] == 0
    decoded = decodeLwsFrame(frame)
    assert decoded["angleDeg"] == pytest.approx(-30.1) and decoded["speedDegPerS"] == 8 and decoded["valid"]
    failure = packLwsFrame(math.inf, math.inf, {"trim": True, "cal": False, "ok": False})
    assert failure["payload"][:3] == [0xFF, 0x7F, 0xFF]
