import math
from inverterhil.host_constants import CONTROL_IDS, STATUS_CYCLE_IDS
from inverterhil.sensor_tx_ids import sensorTxIds


def _obs(can_id, name):
    return {"id": can_id, "name": name, "signal": "", "value": "", "timestampsS": [], "lastChangeS": math.nan, "count": math.nan}


def _inverter(index):
    return {"index": index, "state": "", "ready": None, "commandAgeS": math.nan,
            "torqueCommandRaw": math.nan, "torqueActualRaw": math.nan, "speedRpm": math.nan,
            "idSetpointA": math.nan, "idActualA": math.nan, "iqSetpointA": math.nan, "iqActualA": math.nan,
            "motorTemperatureC": math.nan, "motorTemperatureRaw": math.nan,
            "switchTemperatureC": math.nan, "switchTemperatureRaw": math.nan,
            "derating": None, "activeFault": ""}


def blankTelemetry():
    nan = math.nan
    pins = [{"name": n, "testPoint": t, "state": None} for n, t in zip(
        ("VC_SD_OUT", "MAIN_EN_OUT", "PRECH_EN_OUT", "INV_CTRL_EN", "INV_CTRL_DIS"),
        ("TP6", "TP7", "TP8", "TP9", "TP10"))]
    sensor_ids, _ = sensorTxIds()
    rx_names = ("VCU PEDALS", "CTRL INV1", "CTRL INV2", "CTRL INV3", "CTRL INV4")
    tx_names = ("3X3 INV1", "3X5 INV1", "3X3 INV2", "3X5 INV2", "3X3 INV3", "3X5 INV3",
                "3X3 INV4", "3X5 INV4", "GENERAL", "MTI ACCEL", "MTI RATE", "MTI VELOCITY", "LWS STEERING", "LWS CONFIG")
    return {
        "valid": False, "sourceTimeS": nan, "targetTimeS": nan,
        "vcu": {"state": "", "timeInStateS": nan, "errorActive": False, "errorKnown": False},
        "appsBrakeFault": None,
        "guards": {"mainButton": None, "brakePercent": nan, "dcLink12V": nan, "dcLink34V": nan, "plausibilityOk": None},
        "pedals": {"throttleRequestedPercent": nan, "throttleAppliedPercent": nan,
                   "brakeRequestedPercent": nan, "brakeAppliedPercent": nan, "appliedV": [nan] * 4, "armed": False},
        "steering": {"requestedAngleDeg": nan, "appliedAngleDeg": nan, "observedAngleDeg": nan,
                     "speedDegPerS": nan, "valid": None, "ageS": nan, "dropout": False, "stale": False,
                     "malformed": False, "invalidStatus": False, "angleSentinel": False,
                     "speedSentinel": False, "calibrationState": nan, "known": False},
        "imu": {"accelerationMps2": [nan] * 3, "rateOfTurnRadPerS": [nan] * 3,
                "velocityMps": [nan] * 3, "valid": None, "ageS": nan, "dropout": False,
                "stale": False, "malformed": False},
        "analogInV": [nan] * 4, "pins": pins,
        "dcLink": [{"label": "PAIR 1/2", "voltageV": nan, "rawCount": nan, "aboveMinimum": None, "capturePending": True},
                   {"label": "PAIR 3/4", "voltageV": nan, "rawCount": nan, "aboveMinimum": None, "capturePending": True}],
        "switchingFrequencyKHz": nan, "switchingFrequencyRaw": nan,
        "inverter": [_inverter(i) for i in range(1, 5)],
        "can": {
            "rx": [_obs(i, n) for i, n in zip((0x1F5,) + CONTROL_IDS, rx_names)],
            "tx": [_obs(i, n) for i, n in zip(STATUS_CYCLE_IDS + sensor_ids, tx_names)],
            "diagnostics": {"writeSucceeded": [False] * (len(STATUS_CYCLE_IDS) + len(sensor_ids)),
                            "writeKnown": False, "receiveOverrun": None, "errorWarning": None,
                            "busOff": None, "queueDepth": nan, "burstDurationS": nan,
                            "busLoadPercent": nan, "recoveryCount": nan, "transmitOverrun": None},
        },
        "io": {"healthy": False, "healthyKnown": False},
    }
