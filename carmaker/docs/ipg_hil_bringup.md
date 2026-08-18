# IPG ↔ Speedgoat HIL bring-up — CAN status

**Confirmed.** `inverter_hil` is deployed, running, and configured as the
startup application on TargetPC1 (`10.10.10.5`).  The physical CAN path is
healthy when the PCAN-USB FD is on IO614 connector B (CAN channel 1; connector
A is channel 2).  The expected receive baseline is the 12 IDs and cadences in
`carmaker/docs/can_setup_walkthrough.md`.  Local source:
`carmaker/docs/can_setup_walkthrough.md:3-18`.

**Confirmed.** CarMaker's direct PCAN parameters are `device=pcan_usb (5)`,
`channel=1` (`PCAN_USBBUS1`), `rate=1000000`, `is_canfd=0`, with both FD timing
pointers NULL.  The reviewable implementation and error/status handling are
in `carmaker/src/IO_Init_can_snippet.c:9-52`.  API citation:
`C:\IPG\carmaker\win64-12.0.1\include\pcanio.h:56-70`.

**Proposed design not built.** The first active live test is a cyclic 10-ms
`0x500` frame, passive reception proven first.  It carries both 0.01%-scaled
pedal demands, `Active`, modulo-16 alive counter, zero reserved fields, and
CRC-8/SAE-J1850 over bytes 1-5.  Local source:
`carmaker/config/MFE26_Inverter_CarMaker.dbc:97-110`.

**Open question.** Do not trust operation under load until the persistent
Speedgoat `busLoad=88`, `txOverrun=1`, `busWarning=1` signature is explained.
Measured traffic predicts only about 29% bus utilisation; termination is the
prime suspect.  Confirm exactly two 120-ohm terminators across IO614 pins 2
and 7; IO614 supplies none.  Local source: `PINOUTS.md:section 5.2`.

**Open question.** RBS’s documented CANIf modules are M51, M410, and vCAN,
not PCAN-USB; no RBS ScriptControl namespace was found.  Use the GUI for RBS
creation and retain the generated configuration, while resolving the PCAN/RBS
binding with a passive live test.  Manual citations: CarMaker Programmer's
Guide 12.0.1, sections 15.1 pp. 686-690 and 24.4.5 pp. 1164-1167.
