"""Duck-typed backend session corresponding to MATLAB targetSession.

Lifecycle methods intentionally preserve MATLAB behavior, including the fact
that connect() ensures the inverter_hil application is running.  Do not use
TargetSession.connect against physical hardware for a read-only check; use the
MatlabEngineBackend directly or hardware_smoke_readonly.py.
"""

import math
from .connection_state import connectionState
from .parameter_contract import contractEntry, discoverContract
from .validate_command_value import validateCommandValue
from .model_schema import MODEL_SCHEMA
from inverterhil.decode_status_3x5 import decodeStatus3X5


def _values_match(requested, applied):
    try:
        a, b = float(requested), float(applied)
        return math.isfinite(a) and math.isfinite(b) and abs(a - b) <= max(1e-9, 1e-6 * abs(a))
    except (TypeError, ValueError):
        return False


class TargetSession:
    def __init__(self, targetName="TargetPC1", backend=None):
        if not isinstance(targetName, str) or not targetName:
            raise ValueError("Target name must be nonempty.")
        self.TargetName = targetName
        self.Backend = backend
        self.BackendInjected = backend is not None
        self.State = "disconnected"
        self.Contract = None
        self.TargetValues = {}
        self.LastError = ""

    def _apply(self, event):
        self.State = connectionState(self.State, event)["state"]

    def _ensure_backend(self):
        if self.Backend is None:
            from .matlab_engine_backend import MatlabEngineBackend
            self.Backend = MatlabEngineBackend(self.TargetName)

    def _ensure_application_running(self):
        state = self.Backend.applicationState()
        if state == "running":
            if self.Backend.currentApplicationName().lower() != MODEL_SCHEMA.application_name.lower():
                self.Backend.stop()
                state = "stopped"
            else:
                return
        if state != "loaded":
            self.Backend.load(MODEL_SCHEMA.application_name)
        self.Backend.start()

    def connect(self):
        result = {"success": False, "state": self.State, "reason": "", "contract": None}
        self._apply("connect")
        try:
            self._ensure_backend()
            self.Backend.connect()
            self._apply("connectSucceeded")
            self._ensure_application_running()
            self.Contract = discoverContract(self.Backend.availableParameters())
            self._read_all_target_values()
            reported = self.Backend.applicationState()
            if reported in {"connected", "loaded", "running", "stopped"}:
                self.State = reported
            result.update(success=True, reason="connected", contract=self.Contract)
        except Exception as exc:
            self.LastError = str(exc)
            self.Contract = None
            self.TargetValues = {}
            try:
                if self.Backend is not None:
                    self.Backend.disconnect()
            except Exception:
                pass
            self._apply("disconnect")
            result["reason"] = str(exc)
        result["state"] = self.State
        return result

    def disconnect(self):
        result = {"success": True, "state": "", "reason": ""}
        try:
            if self.Backend is not None:
                self.Backend.removeInstruments()
                self.Backend.disconnect()
        except Exception as exc:
            self.LastError = str(exc)
            result.update(success=False, reason=str(exc))
        self.Contract = None
        self.TargetValues = {}
        self._apply("disconnect")
        result["state"] = self.State
        return result

    def _lifecycle(self, method, request, done, *args):
        result = {"success": False, "state": self.State, "reason": ""}
        if self.Backend is None:
            result["reason"] = "not_connected"
            return result
        if not connectionState(self.State)["allowed"].get(request, False):
            result["reason"] = "action_not_allowed"
            return result
        self._apply(request)
        try:
            getattr(self.Backend, method)(*args)
            self._apply(done)
            result.update(success=True, reason=done)
        except Exception as exc:
            self.LastError = str(exc)
            self._apply("fail")
            result["reason"] = str(exc)
        result["state"] = self.State
        return result

    def load(self, applicationName=""):
        return self._lifecycle("load", "load", "loadSucceeded", applicationName)

    def start(self):
        return self._lifecycle("start", "start", "startSucceeded")

    def stop(self):
        return self._lifecycle("stop", "stop", "stopSucceeded")

    def reset(self):
        return self._lifecycle("reset", "reset", "reset")

    def write(self, name, value):
        result = {"name": name, "path": "", "requested": value, "applied": None,
                  "success": False, "clamped": False, "mismatch": False,
                  "reason": "not_connected"}
        if self.Contract is None:
            result["reason"] = "contract_unresolved"
            return result
        validation = validateCommandValue(self.Contract, name, value)
        if not validation["accepted"]:
            result["reason"] = validation["reason"]
            return result
        entry = contractEntry(self.Contract, name)
        result.update(path=entry.path, requested=validation["value"], clamped=validation["clamped"])
        try:
            self.Backend.setparam(entry.path, validation["value"])
            applied = self.Backend.getparam(entry.path)
        except Exception as exc:
            self.LastError = str(exc)
            result["reason"] = "write_failed"
            return result
        result["applied"] = applied
        self.TargetValues[name] = applied
        result["success"] = True
        result["mismatch"] = not _values_match(validation["value"], applied)
        result["reason"] = "mismatch" if result["mismatch"] else "clamped" if result["clamped"] else "applied"
        return result

    def readCached(self, name):
        return (self.TargetValues.get(name), name in self.TargetValues)

    def executionTimeS(self):
        try:
            return float(self.Backend.executionTimeS()) if self.Backend and self.Backend.isConnected() else math.nan
        except Exception as exc:
            self.LastError = str(exc)
            return math.nan

    def describeState(self):
        return connectionState(self.State)

    def addInstrument(self, instrument):
        try:
            self.Backend.addInstrument(instrument)
            return True
        except Exception as exc:
            self.LastError = str(exc)
            return False

    def _read_all_target_values(self):
        self.TargetValues = {}
        for entry in self.Contract.entries:
            try:
                self.TargetValues[entry.name] = self.Backend.getparam(entry.path)
            except Exception as exc:
                self.LastError = str(exc)

    def readLiveIo(self):
        """Read model signals without inventing unavailable values.

        This port covers the live I/O, diagnostics, observer and raw status/RX
        transport. Per-inverter 3X3 decoding is never reimplemented in Python:
        decodeStatus3X3 is target-generated, so it is run through the backend's
        Engine round-trip when one is available (see _decode_inverters) and
        reported unavailable otherwise. Raw 9x8 TX and 13x14 RX matrices remain
        available to callers either way.
        """
        nan = math.nan
        snapshot = {
            "known": False, "pins": [], "pedalsAppliedV": [nan] * 4,
            "analogInV": [nan] * 4,
            "io": {"healthy": False, "healthyKnown": False},
            "can": {"known": False, "diagnostics": {}},
            "vcuStateId": nan, "vcuStateKnown": False,
            "pedalPayload": [], "pedalPayloadKnown": False,
            "pedalTxCount": nan, "pedalTxCountKnown": False,
            "appsBrakeFault": None, "appsBrakeFaultKnown": False,
            "txPayloads": [], "txPayloadsKnown": False, "txMessageCount": nan,
            "rxObservation": [], "rxKnown": False,
            "inverter": [None] * 4, "inverterKnown": False,
            "canPedals": [nan, nan], "canPedalsKnown": False, "canPedalsDriving": False,
        }
        if not self.Backend or not self.Backend.isConnected():
            return snapshot
        s = MODEL_SCHEMA
        try:
            di = [float(self.Backend.getsignal(s.digital_inputs_block, p)) for p in s.digital_input_ports]
            snapshot["pins"] = [bool(di[i]) for i in s.gui_pin_order]
            ports = [self.Backend.getsignal(s.can_diagnostics_block, p) for p in s.can_diagnostic_ports]
            bus_load, bus_off, recovery, tx_overrun, rx_overrun, warning = ports
            status_ok = [not bool(self.Backend.getsignal(s.status_write_block(i), s.can_write_status_port)) for i in s.status_write_ids]
            from inverterhil.sensor_tx_ids import sensorTxIds
            sensor_ok = [not bool(self.Backend.getsignal(s.sensor_write_block(i), s.can_write_status_port)) for i in sensorTxIds()[0]]
            snapshot["can"] = {"known": True, "diagnostics": {
                "busLoadPercent": float(bus_load), "busOff": bool(bus_off),
                "recoveryCount": float(recovery), "transmitOverrun": bool(tx_overrun),
                "receiveOverrun": bool(rx_overrun), "errorWarning": bool(warning),
                "writeSucceeded": status_ok + sensor_ok, "writeKnown": True}}
            snapshot["io"] = {"healthy": not bool(bus_off) and not bool(warning), "healthyKnown": True}
            snapshot["known"] = True
        except Exception as exc:
            self.LastError = str(exc)
            return snapshot
        def optional(block, port, default=None):
            try:
                return self.Backend.getsignal(block, port)
            except Exception as exc:
                self.LastError = str(exc)
                return default
        pedal = optional(s.vcu_observability_block, s.vcu_pedal_payload_port)
        if _sized(pedal, 8):
            snapshot.update(pedalPayload=[int(x) & 0xFF for x in pedal], pedalPayloadKnown=True)
        state_id = optional(s.vcu_observability_block, s.vcu_state_id_port)
        if _finite_scalar(state_id):
            snapshot.update(vcuStateId=float(state_id), vcuStateKnown=True)
        txc = optional(s.vcu_observability_block, s.vcu_pedal_tx_count_port)
        if _finite_scalar(txc):
            snapshot.update(pedalTxCount=float(txc), pedalTxCountKnown=True)
        fault = optional(s.vcu_observability_block, s.vcu_apps_brake_fault_port)
        if _finite_scalar(fault):
            snapshot.update(appsBrakeFault=bool(fault), appsBrakeFaultKnown=True)
        analog = optional(s.system_status_block, s.status_analog_inputs_port)
        if _sized(analog, 4):
            snapshot["analogInV"] = [float(x) for x in analog]
        payloads = optional(s.system_status_block, s.status_tx_payloads_port)
        matrix = _matrix(payloads)
        if _shape(matrix) == s.tx_payload_shape:
            snapshot.update(txPayloads=[[int(x) & 0xFF for x in row] for row in matrix], txPayloadsKnown=True)
        count = optional(s.system_status_block, s.status_tx_count_port)
        if _finite_scalar(count):
            snapshot["txMessageCount"] = float(count)
        pedals = optional(s.system_status_block, s.status_can_pedals_port)
        if _sized(pedals, 3) and all(_finite_scalar(x) for x in pedals) and float(pedals[2]) in (0, 1):
            snapshot.update(canPedals=[float(pedals[0]), float(pedals[1])], canPedalsKnown=True, canPedalsDriving=bool(pedals[2]))
        observation = _matrix(optional(s.system_status_block, s.status_rx_observation_port))
        if _shape(observation) == s.rx_observation_shape:
            snapshot.update(rxObservation=observation, rxKnown=True)
        self._decode_inverters(snapshot)
        return snapshot

    def _decode_inverters(self, snapshot):
        """Decode the four per-inverter panels from the retained TX payloads.

        Mirrors targetSession.m: PROTOCOL.STATUSCYCLEIDS interleaves 3X3/3X5
        per channel (0x383,0x385, 0x393,0x395, 0x3A3,0x3A5, 0x3B3,0x3B5) then
        0x400, so channel N occupies rows 2N and 2N+1 of the 9x8 matrix.

        3X5 uses the ported Python decoder.  3X3 does NOT: it is compiled into
        the target application, so it is decoded by asking the backend to run
        the real MATLAB function (see MatlabEngineBackend.decodeStatus3X3).
        A backend without that capability -- FakeTargetBackend, or any host
        with no MATLAB Engine -- leaves inverterKnown False and the panel
        renders as unavailable.  Nothing here fabricates a value.
        """
        decode3x3 = getattr(self.Backend, "decodeStatus3X3", None)
        if not callable(decode3x3) or not snapshot["txPayloadsKnown"]:
            return
        rows = snapshot["txPayloads"]
        channels = []
        for channel in range(4):
            try:
                three_x3 = decode3x3(rows[2 * channel])
                three_x5 = decodeStatus3X5(rows[2 * channel + 1])
            except Exception:
                # One bad channel must not blank the other three, and a decode
                # failure is "unavailable", never zero.
                channels.append(None)
                continue
            channels.append({
                "state": three_x3.get("state"),
                "ready": bool(three_x3.get("ready")),
                "derating": bool(three_x3.get("derating")),
                "torqueActualNm": three_x3.get("actualTorqueNm"),
                "torqueCommandNm": three_x3.get("torqueSetpointNm"),
                "motorTemperatureC": three_x3.get("motorTemperatureC"),
                "switchTemperatureC": three_x3.get("switchTemperatureC"),
                "maxAllowedCurrentA": three_x3.get("maxAllowedCurrentA"),
                "speedRpm": three_x5.get("speedRpm"),
                "idSetpointA": three_x5.get("idSetpointA"),
                "idActualA": three_x5.get("idActualA"),
                "iqSetpointA": three_x5.get("iqSetpointA"),
                "iqActualA": three_x5.get("iqActualA"),
            })
        snapshot.update(inverter=channels, inverterKnown=any(c is not None for c in channels))


def _sized(value, length):
    """True when value is a sequence of exactly `length` items.

    getsignal returns whatever the backend has for that port, which may be a
    bare scalar when a port is unavailable or stubbed.  Calling len() on that
    raises TypeError and takes down the whole poll, so the length check has to
    tolerate a non-sequence rather than assume one.
    """
    if value is None or isinstance(value, (str, bytes, dict)):
        return False
    try:
        return len(value) == length
    except TypeError:
        return False


def _finite_scalar(value):
    try:
        return not isinstance(value, (list, tuple, dict)) and math.isfinite(float(value))
    except (TypeError, ValueError):
        return False


def _matrix(value):
    if value is None:
        return []
    if hasattr(value, "tolist"):
        value = value.tolist()
    return value if isinstance(value, list) else []


def _shape(value):
    return (len(value), len(value[0])) if value and all(isinstance(r, list) for r in value) and all(len(r) == len(value[0]) for r in value) else (0, 0)


targetSession = TargetSession
