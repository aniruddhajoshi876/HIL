# CarMaker CAN Rest Bus Simulation setup — real VC bench

## Status and boundary

**Confirmed.** The intended topology is one CarMaker physical CAN node, joined as a third node on the existing 1-Mbaud Speedgoat IO614-channel-1 / real-VC bus. CarMaker passively receives the VC control frames and Speedgoat status frames; it must not transmit any existing inverter or sensor ID. RBS imports DBC, classifies ECUs as real or simulated, maps signals to Data Dictionary quantities/functions, and selects one active physical CAN channel. UsersGuide_HIL.pdf, section 4, pp. 53, 55-62; section 4.5.2 “CAN”, p. 68.

**Proposed design not built.** The sole new transmission is standard-ID `0x500` (`CarMakerPedalDemand`), DLC 8, from CarMaker to SpeedgoatHIL. `carmaker/config/MFE26_Inverter_CarMaker.dbc` is placed beside this walkthrough—not under `FS_race`—because it is the bench CAN contract imported by the project, rather than a generated project configuration. It retains source DBC scaling for limits (1/256 Nm), status torque (1/32 Nm), and DC link (1/64 V). Local source: `virtual-vcu/config/MFE26_Inverter.dbc:71-161` (historical tree).

**Open question.** `0x500` is provisional until the complete vehicle namespace/live bus is audited. The cycle time shown in the DBC (10 ms) is a proposal, and its counter/integrity algorithm and timeout are not agreed. Do not treat `Active` or transport freshness as real-VC pedal plausibility.

## Before starting the GUI

**Confirmed.** CarMaker holds configuration in memory and rewrites the generated configuration at TestRun load. Close CarMaker before editing or copying configuration; after a run, re-read the generated file to learn what CarMaker retained. A clean mapping log only proves names resolved, not that data flowed.

**Proposed design not built.** `Data/Config/CANIfParameters` is deliberately only an InfoFile skeleton, and `ECUParameters` points `CANIfParameters` at it. No RBS-specific keys are hand-authored because no local GUI-generated CANIf InfoFile establishes their syntax. Let the Rest Bus Configurator create and overwrite it.

## GUI procedure

1. **Confirmed — the CarMaker-side adapter exists and is supported.** This was the largest open risk in the plan; it is now closed by direct inspection of this machine, not by assumption. The full chain is present:

   | Layer | Evidence |
   |---|---|
   | Hardware | `PCAN-USB FD` (PEAK-System, `USB\VID_0C72&PID_0012`), `Get-PnpDevice` status `OK` |
   | Vendor driver | `C:\Windows\System32\PCANBasic.dll`, version 4.9.0.942 |
   | CarMaker API | `C:\IPG\carmaker\win64-12.0.1\include\pcanio.h`, which declares `pcan_usb = 5` and CAN-FD structs |
   | CarMaker implementation | `PCANIO_*` symbols are present in `C:\IPG\carmaker\win64-12.0.1\lib\libcarmaker.a` — compiled in, not merely declared |

   So CarMaker 12.0.1 on this installation can drive a physical CAN channel through the connected PCAN-USB FD. **Confirmed — the Speedgoat IO614 still does not satisfy CarMaker's side**; that remains true and is precisely why this separate adapter is required.

   In the IO Configurator, select that channel and activate it at 1 Mbaud, classic CAN (the bench bus is not CAN FD, even though the adapter and `pcanio.h` both support it). If the channel is otherwise unused, extend `FS_race/src/IO.c` in IPG-MFE to initialize it in `IO_Init()` and rebuild the CarMaker executable. UsersGuide_HIL.pdf, section 4.5.2 “CAN”, p. 68.

   **Confirmed — the API that `IO_Init()` must call**, from `pcanio.h`:

   ```c
   int PCANIO_Init(void);
   int PCANIO_SetCommParam(int device, int channel, int rate, int is_canfd,
           struct pcanfd_cfg *nominal, struct pcanfd_cfg *data);
   int PCANIO_Send(int device, int channel, struct CAN_Msg *msg);
   int PCANIO_Recv(int device, int channel, struct CAN_Msg *msg);
   int PCANIO_CloseComm(int device, int channel);
   unsigned int PCANIO_GetStatus(int device, int channel, char *status_text);
   ```

   Use `device = pcan_usb` (5), `rate = 1000000`, `is_canfd = 0`.

   **Open question — channel index and termination.** Which `channel` value maps to the physical port, and whether the bus is correctly terminated once CarMaker joins as a third node, are still unverified. `PINOUTS.md` section 5.2 is explicit that the IO614 provides no termination itself and that a bus needs exactly two 120 Ω end terminators between pins 2 and 7; adding a third node must not add a third terminator. Missing or excess termination shows up as roughly 100 % bus load with `transmit_pending` stuck true and no successful ACK — check `PCANIO_GetStatus` before blaming the mapping.
2. **Confirmed — create/import RBS.** Open the Rest Bus Configurator and import `carmaker/config/MFE26_Inverter_CarMaker.dbc` as a CANdb database. Select the active physical channel.
3. **Proposed design not built — declare ownership.** Classify `VC` and `SpeedgoatHIL` as real ECUs, and `CarMaker` as the simulated ECU. Configure all existing control/status/sensor IDs as receive-only at CarMaker. Configure only `0x500` for CarMaker transmission.
4. **Proposed design not built — map signals.** Map received torque limits, status torque/state/ready, d/q current/speed, and DC-link signals to approved Data Dictionary names. Map `DM.Gas` to `ThrottleDemand` and `DM.Brake` to `BrakeDemand` with **factor 100 and offset 0**: `DM.Gas`/`DM.Brake` are **0..1** (CarMaker ReferenceManual), whereas `ThrottleDemand`/`BrakeDemand` are defined in **percent, range [0|100]**, in `carmaker/config/MFE26_Inverter_CarMaker.dbc:97-98`. **Confirmed — this exact conversion was already got wrong once on the XCP path, where factor 1 delivered full throttle as 1 %.** Verify the resulting percent value on the wire rather than trusting the mapping dialog. Map `Active`, counter, and integrity according to the approved receiver contract. RBS supports Data Dictionary mapping including factor/offset/min/max conversion. UsersGuide_HIL.pdf, section 4.5, pp. 58-62.
5. **Open question — sensor semantics.** The DBC contains `0x034`, `0x032`, and `0x2B0` as raw payload only because their signal layouts are not grounded here. Do not create semantic mappings until their authoritative definitions are supplied.
6. **Proposed design not built — timing/integrity.** Set `CarMakerPedalDemand` cyclic at the reviewed period and configure the approved alive-counter and integrity behavior. The RBS UI can configure cyclic/event transmission and has counter/CRC hooks; it does not supply the bench’s contract. UsersGuide_HIL.pdf, section 4.9, pp. 73-75.
7. **Confirmed — save and activate.** Save the GUI-generated CAN communication/interface information under `Data/Config`, then keep/activate its name through `ECUParameters`’ `CANIfParameters` entry. UsersGuide_HIL.pdf, section 4.2, pp. 55-56; section 4.6, pp. 70-71.
8. **Proposed design not built — proof order.** First prove passive reception with no unexpected CarMaker transmission. Then run `HIL/CAN_Bringup`, which ramps and holds a non-zero pedal demand. Capture `0x500` and confirm its values, counter, integrity, timing, and receiver fallback after cable loss/timeout.

## IPG-MFE handoff — do not implement in this repository

**Proposed design not built.** In IPG-MFE, add physical CAN initialization to `FS_race/src/IO.c` (`IO_Init()`), rebuild the CarMaker executable, and replace `TorqueVect.mdl`’s existing Read CM Dict inputs `TorqueVect.XcpTorqueRequestNm` and `TorqueVect.XcpTorqueActive` with CAN-sourced equivalents. Do not hand-edit `TorqueVect.mdl`; make that model change in its supported toolchain. The CAN source must not fabricate a single torque-request scalar, authoritative VCU state/stateId, or pedal-validity/plausibility feedback: each remains an open real-VC publication question.
