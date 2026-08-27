"""Versioned host/model ABI for hard-coded Simulink block output ports.

A model block rename, port reorder, or observation shape change invalidates
this schema and requires a coordinated host-port version bump.
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class ModelSchema:
    version: str = "inverter_hil@36f99bd-v1"
    application_name: str = "inverter_hil"
    hardware_root: str = "inverter_hil/Hardware I O - PRE-FLIGHT DISABLED"
    digital_inputs_block: str = (
        "inverter_hil/Hardware I O - PRE-FLIGHT DISABLED/"
        "IO183 DIO09-DIO13 VCU Monitor"
    )
    can_diagnostics_block: str = (
        "inverter_hil/Hardware I O - PRE-FLIGHT DISABLED/IO614 CAN Diagnostics"
    )
    sensor_payloads_block: str = (
        "inverter_hil/Hardware I O - PRE-FLIGHT DISABLED/"
        "Synchronized Sensor Payloads"
    )
    vcu_observability_block: str = "inverter_hil/Virtual VCU Observability"
    system_status_block: str = "inverter_hil/Ephorus System Status"
    rx_observation_shape: tuple[int, int] = (13, 14)
    tx_payload_shape: tuple[int, int] = (9, 8)
    digital_input_ports: tuple[int, ...] = (1, 2, 3, 4, 5)
    gui_pin_order: tuple[int, ...] = (0, 1, 2, 4, 3)
    can_diagnostic_ports: tuple[int, ...] = (1, 2, 3, 4, 5, 6)
    can_write_status_port: int = 1
    vcu_pedal_payload_port: int = 1
    vcu_state_id_port: int = 2
    vcu_pedal_tx_count_port: int = 6
    vcu_apps_brake_fault_port: int = 8
    status_tx_payloads_port: int = 1
    status_rx_observation_port: int = 2
    status_analog_inputs_port: int = 3
    status_tx_count_port: int = 4
    status_vehicle_state_port: int = 5
    status_can_pedals_port: int = 6
    sensor_counts_port: int = 11
    sensor_ages_port: int = 12
    sensor_calibration_state_port: int = 13
    sensor_runtime_dlc_ports: tuple[int, ...] = (14, 15, 16, 17, 18)
    status_write_ids: tuple[str, ...] = (
        "383", "385", "393", "395", "3A3", "3A5", "3B3", "3B5", "400"
    )

    def status_write_block(self, can_id: str) -> str:
        return f"{self.hardware_root}/CAN Write 0x{can_id}"

    def sensor_write_block(self, can_id: int) -> str:
        return f"{self.hardware_root}/CAN Write Sensor 0x{can_id:03X}"


MODEL_SCHEMA = ModelSchema()
