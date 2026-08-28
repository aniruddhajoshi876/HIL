# MTi-680G IMU and Bosch LWS integration plan

## Goal

Add independently testable MTi-680G and Bosch LWS sensor simulation to
`inverter_hil`, with the steering dial driving the LWS angle. The simulators
share one vehicle-state tick with the inverter plant, but do not call or copy
VCU production logic. The master branch remains usable for real VCU HIL;
Virtual VCU-specific stimuli can be layered later.

## Repository layout

```text
inverter_hil/
  imu/
    imuProtocol.m
    packMti680Frame.m
    packMti680Payload.m
    decodeMti680Frame.m
    stepImuSimulation.m
    protocol.md
  steering-sensor/
    lwsProtocol.m
    packLwsFrame.m
    packLwsPayload.m
    decodeLwsFrame.m
    stepSteeringSensor.m
    protocol.md
  +inverterhil/
    sensorScheduler.m
    sensorBusMux.m
    defaultVehicleStateConfig.m
    stepVehicleState.m
  tests/inverter_hil/
    TestSensorProtocol.m
    TestSensorConcurrency.m
  inverter_hil_app.m
  inverter_hil_app.mlapp
  build_inverter_hil_model.m
```

## Implementation slices

1. Keep protocol encoders and decoders as black-box oracles. Test CAN ID,
   DLC, byte order, scale, range, status validity, and malformed frames
   without importing VCU code.
2. Advance one independent vehicle-state model from inverter plant output and
   steering angle. Publish that state once per status-cycle tick.
3. Feed the shared state to the MTi and LWS encoders. Run both on the VC bus
   (IO614 channel 2 / Port A) alongside the Ephorus status frames — the sensors
   are things the real VC reads. They are not on the channel-1 CarMaker bus.
   Independent rates and dropout controls.
4. Expose steering angle, steering dropout, and IMU dropout as tunable GUI
   parameters. The dial is bounded by the LWS range of -780 to +780 degrees.
5. Verify source app instantiation, regenerated `.mlapp`, host protocol tests,
   scheduler/concurrency tests, model update, and only then target deployment.

## Branch and promotion strategy

The current implementation is developed on clean `master` in this worktree.
No Virtual VCU dependency is introduced. After master host/model tests pass,
the shared sensor folders, vehicle-state helper, model boundary, GUI controls,
and tests can be merged into `virtual-vcu`. Virtual VCU stimulus adapters stay
separate so the same sensor simulation can later be used with a real VCU for
HIL without changing sensor contracts.

## Ownership

- Implementer: protocol files, shared vehicle-state path, model CAN boundary,
  GUI dial, and tests.
- Manager/deployer: review the independent-oracle boundary, check the test
  evidence, supervise model generation, and deploy only after hardware
  preflight and target-specific checks pass.

## Acceptance gates

- All sensor protocol and concurrency tests pass in MATLAB R2024b.
- GUI source and `.mlapp` instantiate with the steering control present.
- Model update proves the sensor CAN Pack/CAN Write paths and dictionary
  parameters resolve.
- Target evidence distinguishes host simulation from a real VCU receiving
  frames; no host smoke test is reported as physical HIL coverage.
