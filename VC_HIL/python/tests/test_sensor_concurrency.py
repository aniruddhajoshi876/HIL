import pytest
from sensors import stepImuSimulation, stepSteeringSensor
from inverterhil import sensorBusMux, sensorScheduler


def test_shared_state_produces_independent_frames():
    vehicle = {"accelerationMps2": [.5, -.25, 9.8], "rateOfTurnRadPerS": [.1, .2, .3]}
    _, imu, _, _ = stepImuSimulation(None, .010, vehicle)
    _, lws = stepSteeringSensor(None, .010, {"angleDeg": 30, "dropout": False,
                                             "status": {"trim": True, "cal": True, "ok": True}})
    frames = sensorBusMux(imu, lws)
    assert [x["timestampS"] for x in frames] == [.010, .010]
    assert [x["kind"] for x in frames] == ["imu", "steering"]


def test_one_dropout_does_not_suppress_other_sensor():
    vehicle = {"accelerationMps2": [0, 0, 9.8], "rateOfTurnRadPerS": [0, 0, 0]}
    _, imu, _, _ = stepImuSimulation(None, .020, vehicle, {"enabled": True, "dropout": True})
    _, lws = stepSteeringSensor(None, .020, {"angleDeg": -20, "dropout": False,
                                             "status": {"trim": True, "cal": True, "ok": True}})
    assert [x["kind"] for x in sensorBusMux(imu, lws)] == ["steering"]


def test_first_tick_shared_timestamp_and_independent_rates():
    config = {"imuPeriodS": .005, "lwsPeriodS": .010}
    state, due = sensorScheduler(None, 0, config)
    assert due["imu"] and due["lws"] and due["imuSequence"] == due["lwsSequence"] == 1
    state, due = sensorScheduler(state, .005, config)
    assert due["imu"] and not due["lws"]
    state, due = sensorScheduler(state, .010, config)
    assert due["imu"] and due["lws"] and state["imuSequence"] == 3 and state["lwsSequence"] == 2


def test_periods_reject_invalid_configuration():
    with pytest.raises(ValueError): sensorScheduler(None, 0, {"imuPeriodS": 0, "lwsPeriodS": .01})
    with pytest.raises(ValueError): sensorScheduler(None, -1, {"imuPeriodS": .005, "lwsPeriodS": .01})
