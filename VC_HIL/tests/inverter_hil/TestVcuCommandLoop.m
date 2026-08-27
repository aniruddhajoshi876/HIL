classdef TestVcuCommandLoop < matlab.unittest.TestCase
    %TESTVCUCOMMANDLOOP Host simulation of a VCU commanding the virtual inverter.
    %
    %   These tests stand in for the VCU and the CAN analyser that are not
    %   physically connected. They build Ephorus control frames byte by byte,
    %   push them through INVERTERHIL.STEPMODEL exactly as the deployed model
    %   does (one received frame per 1 ms tick, a caller-owned decoder bank
    %   carried across ticks), and decode the transmitted status cycle with
    %   INVERTERHIL.DECODESTATUS3X3/DECODESTATUS3X5 so every assertion is made
    %   against the bytes that would leave the CAN transceiver.
    %
    %   PROVENANCE OF THE EXPECTED VALUES. The frame layout asserted here is
    %   INVERTER_HIL_PLAN.MD section 4.1 (byte 0 bit 0 enable, bit 1 reset
    %   error, bit 2 ASC allowed, bit 3 current-control mode, byte 0 bits 4-7
    %   and byte 1 reserved and required to be zero in generated vectors,
    %   bytes 2-3 int16 speed setpoint in RPM, bytes 4-5 and 6-7 int16 positive
    %   and negative torque limits). The frame builder below encodes that table
    %   directly with explicit byte arithmetic; it deliberately does NOT reuse
    %   INVERTERHIL.DECODECONTROLFRAME's own field extraction, so a decoder
    %   regression cannot cancel itself out against the stimulus.
    %
    %   The MFE26-VC firmware (DRIVERS/DEVICE_DRIVERS/INC/EPHORUS_DRIVER.HPP
    %   and .../SRC/EPHORUS_DRIVER.CPP) is the device under test, not the
    %   specification. It was read to confirm the interface and it agrees with
    %   the plan on every CAN identifier, bit position and status scale. Where
    %   it takes a position the plan calls unresolved -- the inbound torque
    %   scale -- these tests follow the plan and refuse to assert either value.
    %
    %   TORQUE SCALE. INVERTER_HIL_PLAN.MD section 4.1.1 records that Ephorus
    %   table 6.11 is internally inconsistent: it names 1/256 Nm/count but
    %   prints a range that only 1/512 Nm/count produces. The VCU encodes 1/256
    %   (EPHORUS_TORQUE_CTRL_SCALE_NM).
    %
    %   RESOLVED 2026-08-02. Independent firmware evidence (MFE26-VC clone,
    %   branch 'todo') settles this: EPHORUS_TORQUE_CTRL_SCALE_NM
    %   (ephorus_driver.hpp:55) is 1/256 Nm and is explicitly labeled (lines
    %   38-39) as the torque-limit scale for exactly these fields; the SIL
    %   model (ephorus_model.cpp:37-38) and its own golden-value conformance
    %   tests agree. The 1/512 value the plan's older analysis found was
    %   never a torque scale at all -- it is the unrelated switchingFreq_khz
    %   field's scale (ephorus_driver.hpp:119,187), and confusing the two
    %   appears to be how the HIL's provisional profile picked 1/512. See
    %   INVERTERHIL.PROTOCOL's torqueProfiles.vcu256 comment.
    %
    %   Every torque assertion below is nonetheless still made on the RAW
    %   COUNT wherever practical: it is unambiguous under either
    %   interpretation and was not worth rewriting now that the ambiguity
    %   is closed. Scenario 4a below additionally asserts the resolved
    %   verification state directly.

    methods (Test)

        % ---------------------------------------------------------------
        % Scenario 1 - cold start, no VCU on the bus.
        % ---------------------------------------------------------------
        function coldStartHoldsEveryChannelIdleWithRealAmbientStatus(testCase)
            % No control frame is ever received: the hardware boundary
            % publishes a frame marked DROP on every tick when the CAN RX
            % block reports no data (see BUILD_INVERTER_HIL_MODEL's
            % 'drop', ~logical(rxDataPresent)). Nothing here fabricates a
            % quiet bus; it is represented the same way the model represents
            % it.
            run = TestVcuCommandLoop.newRun();
            for tick = 1:10
                run = TestVcuCommandLoop.step(run, TestVcuCommandLoop.silentFrame());
            end

            testCase.verifyEqual(run.bank.hasCommand, false(1, 4), ...
                'A silent bus must not retain any command.');
            testCase.verifyEqual(run.bank.acceptedCount, zeros(1, 4, 'uint32'));

            snapshot = inverterhil.decoderSnapshot(run.bank, uint32(10));
            testCase.verifyEqual(snapshot.ageMs, repmat(intmax('uint32'), 1, 4), ...
                'Never-received must report the sentinel age, not a real age.');

            testCase.verifyEqual(run.cycle.ids, inverterhil.protocol().statusCycleIds);
            testCase.verifyEqual(run.cycle.dlc, repmat(uint8(8), 1, 9));

            for channel = 1:4
                status3X3 = inverterhil.decodeStatus3X3( ...
                    run.cycle.payloads(2 * channel - 1, :));
                status3X5 = inverterhil.decodeStatus3X5( ...
                    run.cycle.payloads(2 * channel, :));

                testCase.verifyEqual(status3X3.state, ...
                    double(inverterhil.protocol().state.idle), ...
                    sprintf('Channel %d must report Idle on the wire.', channel));
                testCase.verifyTrue(status3X3.ready, ...
                    'A connected, unfaulted, Idle channel reports ready.');
                testCase.verifyFalse(status3X3.derating);
                testCase.verifyEqual(status3X3.actualTorqueNm, 0, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X3.torqueSetpointNm, 0, 'AbsTol', 1e-9);

                % Ambient, from CAL.AMBIENTTEMPERATUREC = 25 C, round-tripped
                % through the 1/8 C and 1/16 C status fields.
                testCase.verifyEqual(status3X3.motorTemperatureC, 25, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X3.switchTemperatureC, 25, 'AbsTol', 1e-9);

                testCase.verifyEqual(status3X5.idSetpointA, 0, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X5.idActualA, 0, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X5.iqSetpointA, 0, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X5.iqActualA, 0, 'AbsTol', 1e-9);
                testCase.verifyEqual(status3X5.speedRpm, 0, 'AbsTol', 1e-9);

                % A never-received command is not a 500 ms dropout: holding
                % Idle is correct, latching Error would not be.
                testCase.verifyEqual(run.stateOutput.channels(channel).activeFault, ...
                    'none', 'A silent bus must not latch a command timeout.');
            end
        end

        % ---------------------------------------------------------------
        % Scenario 2 - one commanded channel reaches Drive, the rest do not.
        % ---------------------------------------------------------------
        function enablingChannelOneLeavesTheOtherThreeIdle(testCase)
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            frame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            for tick = 1:5
                run = TestVcuCommandLoop.step(run, frame);
            end

            protocolIds = inverterhil.protocol();
            testCase.verifyEqual(run.stateOutput.mode(1), protocolIds.state.drive, ...
                'A commanded, enabled channel must leave Idle for Drive.');
            testCase.verifyEqual(run.stateOutput.mode(2:4), ...
                repmat(protocolIds.state.idle, 1, 3), ...
                'Uncommanded channels must stay Idle (channel isolation).');

            % Confirm the isolation on the wire, not only in the state struct.
            testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 1), 1);
            testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 2), 0);
            testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 3), 0);
            testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 4), 0);
        end

        % ---------------------------------------------------------------
        % Scenario 3 - every channel answers only its own control identifier.
        % ---------------------------------------------------------------
        function eachChannelRespondsOnlyToItsOwnControlId(testCase)
            controlIds = inverterhil.protocol().controlIds;
            % Same identifiers the VCU emits (EPHORUS_CAN_ID_INV*_CONTROL).
            testCase.assertEqual(controlIds, ...
                uint32([hex2dec('186') hex2dec('196') ...
                hex2dec('1A6') hex2dec('1B6')]));

            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            payload = TestVcuCommandLoop.controlPayload(command);

            for target = 1:4
                run = TestVcuCommandLoop.newRun();
                frame = TestVcuCommandLoop.controlFrame(controlIds(target), payload);
                for tick = 1:5
                    run = TestVcuCommandLoop.step(run, frame);
                end

                expected = repmat(inverterhil.protocol().state.idle, 1, 4);
                expected(target) = inverterhil.protocol().state.drive;
                testCase.verifyEqual(run.stateOutput.mode, expected, ...
                    sprintf(['Only the channel addressed by 0x%03X may ' ...
                    'respond to it.'], controlIds(target)));

                expectedRetention = false(1, 4);
                expectedRetention(target) = true;
                testCase.verifyEqual(run.bank.hasCommand, expectedRetention);
            end
        end

        % ---------------------------------------------------------------
        % Scenario 4a - the raw torque counts survive decode and retention.
        % ---------------------------------------------------------------
        function torqueLimitCountsAreDecodedAndRetainedExactly(testCase)
            % 8192 counts is the plan's own worked example (section 4.1.1):
            % 32 Nm at 1/256, 16 Nm at 1/512. Asserting the COUNT keeps this
            % test valid whichever scale the bench eventually proves.
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            command.speedSetpointRpm = int16(3000);
            command.rawTorquePosCounts = int16(8192);
            command.rawTorqueNegCounts = int16(-8192);
            frame = TestVcuCommandLoop.controlFrame(hex2dec('196'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            run = TestVcuCommandLoop.step(run, frame);

            retained = run.bank.commands(2);
            testCase.verifyTrue(retained.enable);
            testCase.verifyEqual(retained.speedSetpointRpm, int16(3000));
            testCase.verifyEqual(retained.rawTorquePosCounts, int16(8192));
            testCase.verifyEqual(retained.rawTorqueNegCounts, int16(-8192));

            % The two candidate interpretations remain exactly a factor of
            % two apart -- both are still carried side by side on the wire
            % decode, which is scale-independent by construction.
            testCase.verifyEqual(retained.torquePosNm256, ...
                2 * retained.torquePosNm512, 'AbsTol', 1e-12);
            testCase.verifyEqual(retained.torqueNegNm256, ...
                2 * retained.torqueNegNm512, 'AbsTol', 1e-12);
            % RESOLVED 2026-08-02 by firmware evidence (see this class's
            % TORQUE SCALE note above and INVERTERHIL.PROTOCOL): 1/256 is
            % verified true; 1/512 was never a torque scale in the firmware
            % at all and stays unverified, retained only as a known-wrong
            % profile.
            profiles = inverterhil.protocol().torqueProfiles;
            testCase.verifyFalse(profiles.provisional512.verified, ...
                'The 1/512 profile was never a real torque scale (see the ' + ...
                "switchingFreq_khz mixup) and must stay unverified.");
            testCase.verifyTrue(profiles.vcu256.verified, ...
                'The 1/256 profile is resolved by firmware evidence.');
        end

        % ---------------------------------------------------------------
        % Scenario 4a-2 - the firmware's own golden torque-limit value, run
        % end to end through DEFAULTCALIBRATION's now-resolved scale.
        % ---------------------------------------------------------------
        function torqueLimitScaleMatchesFirmwareConformanceGoldenValue(testCase)
            % MFE26-VC sil/tests/conformance/ephorus_conformance.cpp:252,440
            % and sil/tests/gui/can_decode_test.cpp:25 assert this exact
            % conversion for the control-frame torque-limit fields: 3200 raw
            % counts at EPHORUS_TORQUE_CTRL_SCALE_NM (1/256 Nm/count,
            % ephorus_driver.hpp:55) is +12.5 Nm. INVERTERHIL.PROTOCOL's
            % torqueProfiles.vcu256 comment cites the same evidence. Unlike
            % Scenario 4a above (which only checks the scale-independent
            % wire decode), this asserts the golden value survives all the
            % way through DEFAULTCALIBRATION's resolved default (Fix 3) and
            % CAL.TORQUESCALENMPERCOUNT into the plant input the transmitted
            % status is built from.
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            command.rawTorquePosCounts = int16(3200);
            command.rawTorqueNegCounts = int16(-3200);
            frame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            testCase.assertEqual(run.cal.protocolProfileId, ...
                'ephorus3-v1.03-candidate-1over256', ...
                'Precondition: DEFAULTCALIBRATION must default to the resolved 1/256 profile.');
            testCase.assertEqual(run.cal.torqueScaleNmPerCount, 1 / 256);
            run = TestVcuCommandLoop.step(run, frame);

            testCase.verifyEqual(run.bank.commands(1).torquePosNm256, 12.5, ...
                'AbsTol', 1e-9);
            testCase.verifyEqual(run.bank.commands(1).torqueNegNm256, -12.5, ...
                'AbsTol', 1e-9);
            testCase.verifyEqual( ...
                run.plantOutput.channels(1).selectedTorquePositiveNm, 12.5, ...
                'AbsTol', 1e-9, ...
                'CAL.TORQUESCALENMPERCOUNT must convert 3200 counts to the firmware''s own +12.5 Nm golden value.');
            testCase.verifyEqual( ...
                run.plantOutput.channels(1).selectedTorqueNegativeNm, -12.5, ...
                'AbsTol', 1e-9);
            testCase.verifyEqual(run.plantOutput.torqueScaleNmPerCount, 1 / 256);
        end

        % ---------------------------------------------------------------
        % Scenario 4b - a commanded torque must actually reach the plant and
        % the transmitted status.
        % ---------------------------------------------------------------
        function commandedTorqueAndSpeedReachThePlantAndTheStatusFrames(testCase)
            % INVERTER_HIL_PLAN.MD section 5.1 requires each inverter instance
            % to receive "its own decoded CAN enable, reset, ASC, speed
            % setpoint, and positive/negative torque limits", and section 5.3
            % requires the speed-error controller to act on "the CAN speed
            % setpoint" saturated "between the CAN negative and positive
            % torque limits". A channel held in Drive with a large positive
            % speed error and a positive torque limit must therefore develop
            % torque and report it.
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            command.speedSetpointRpm = int16(3000);
            command.rawTorquePosCounts = int16(8192);
            command.rawTorqueNegCounts = int16(-8192);
            frame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            for tick = 1:100
                run = TestVcuCommandLoop.step(run, frame);
            end

            % Preconditions: the channel really is in Drive with torque
            % authority granted, so a zero result cannot be blamed on a safety
            % gate having correctly fired.
            testCase.assertEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.drive);
            testCase.assertFalse(run.plantOutput.channels(1).zeroTorqueApplied, ...
                'Torque authority must be granted before this can be judged.');

            % Raw counts only - the Nm value depends on the unresolved scale.
            testCase.verifyEqual(run.plantOutput.channels(1).rawTorquePosCounts, ...
                int16(8192), ['The positive torque limit the VCU sent must ' ...
                'reach the plant as the same raw count.']);
            testCase.verifyEqual(run.plantOutput.channels(1).rawTorqueNegCounts, ...
                int16(-8192), ['The negative torque limit the VCU sent must ' ...
                'reach the plant as the same raw count.']);
            testCase.verifyEqual(run.plantOutput.channels(1).speedSetpointRpm, 3000, ...
                'The CAN speed setpoint must reach the plant.');

            status3X3 = inverterhil.decodeStatus3X3(run.cycle.payloads(1, :));
            status3X5 = inverterhil.decodeStatus3X5(run.cycle.payloads(2, :));
            testCase.verifyGreaterThan(status3X3.torqueSetpointNm, 0, ...
                ['A positive speed error under a positive torque limit must ' ...
                'produce a positive torque setpoint on the wire.']);
            testCase.verifyGreaterThan(status3X5.iqSetpointA, 0, ...
                'Positive torque implies positive Iq on the wire.');
            testCase.verifyGreaterThan(status3X5.speedRpm, 0, ...
                'A driven motor must report a nonzero speed on the wire.');
        end

        % ---------------------------------------------------------------
        % Scenario 5 - command timeouts at the protocol's own boundaries.
        % ---------------------------------------------------------------
        function commandDropoutZeroesTorqueAtFiftyMsAndLatchesErrorAtFiveHundred(testCase)
            timing = inverterhil.protocol().timing;
            testCase.assertEqual(timing.commandTorqueZeroMs, uint32(50));
            testCase.assertEqual(timing.commandErrorMs, uint32(500));

            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            frame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(command));

            % Command lands on tick 0, then the bus goes silent. Command age
            % after N further 1 ms ticks is exactly N.
            run = TestVcuCommandLoop.newRun();
            run = TestVcuCommandLoop.step(run, frame);
            observed = struct('age', {}, 'mode', {}, 'zeroTorque', {}, 'fault', {});
            for age = 1:601
                run = TestVcuCommandLoop.step(run, TestVcuCommandLoop.silentFrame());
                observed(age).age = age;
                observed(age).mode = run.stateOutput.mode(1);
                observed(age).zeroTorque = run.stateOutput.channels(1).zeroTorque;
                observed(age).fault = run.stateOutput.channels(1).activeFault;
            end

            drive = inverterhil.protocol().state.drive;
            errorMode = inverterhil.protocol().state.error;
            torqueLimit = double(timing.commandTorqueZeroMs);
            errorLimit = double(timing.commandErrorMs);

            % The datasheet boundaries are strict: "greater than" 50 / 500 ms.
            testCase.verifyEqual(observed(torqueLimit).mode, drive);
            testCase.verifyFalse(observed(torqueLimit).zeroTorque, ...
                'Torque must survive to exactly 50 ms of command age.');
            testCase.verifyTrue(observed(torqueLimit + 1).zeroTorque, ...
                'Torque must be zeroed once command age exceeds 50 ms.');
            testCase.verifyEqual(observed(torqueLimit + 1).mode, drive, ...
                'Exceeding 50 ms zeroes torque WITHOUT leaving Drive.');

            testCase.verifyEqual(observed(errorLimit).mode, drive, ...
                'Error must not latch at exactly 500 ms of command age.');
            testCase.verifyEqual(observed(errorLimit + 1).mode, errorMode, ...
                'Exceeding 500 ms must latch Error.');
            testCase.verifyEqual(observed(errorLimit + 1).fault, 'command_timeout');

            % And the VCU sees it: the state field on the wire is Error (2).
            testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 1), 2);
            status3X3 = inverterhil.decodeStatus3X3(run.cycle.payloads(1, :));
            testCase.verifyFalse(status3X3.ready, ...
                'A channel in Error must not report ready.');
            testCase.verifyEqual(status3X3.actualTorqueNm, 0, 'AbsTol', 1e-9);
        end

        % ---------------------------------------------------------------
        % Scenario 6 - recovery once the VCU resumes commanding.
        % ---------------------------------------------------------------
        function channelRecoversWhenTheVcuResumesWithAResetCommand(testCase)
            % INVERTER_HIL_PLAN.MD section 5.2: "Reset succeeds only when no
            % error cause is active, the wait has elapsed, and a reset command
            % is present." All three become true here: the command age returns
            % to 0 so no cause is active, 300 ms of healthy time far exceeds
            % the 500 us reset floor, and byte 0 bit 1 is set on every frame.
            % This is exactly the frame EphorusDriver::queueResetEnable emits.
            enableOnly = TestVcuCommandLoop.emptyCommand();
            enableOnly.enable = true;
            resetAndEnable = enableOnly;
            resetAndEnable.resetError = true;

            driveFrame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(enableOnly));
            resetFrame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(resetAndEnable));

            run = TestVcuCommandLoop.newRun();
            run = TestVcuCommandLoop.step(run, driveFrame);
            for age = 1:600
                run = TestVcuCommandLoop.step(run, TestVcuCommandLoop.silentFrame());
            end
            testCase.assertEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.error, ...
                'Precondition: the dropout must have latched Error.');

            for tick = 1:300
                run = TestVcuCommandLoop.step(run, resetFrame);
            end

            % The reset bit is decoded and retained, so the only question is
            % whether it reaches the state machine.
            testCase.assertTrue(run.bank.commands(1).resetError, ...
                'Precondition: the reset bit must have been decoded.');
            testCase.verifyFalse(run.state.channels(1).errorLatched, ...
                ['A commanded reset with no active cause and the wait ' ...
                'elapsed must clear the latched Error.']);
            testCase.verifyEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.drive, ...
                ['After a successful reset the still-enabled channel must ' ...
                'return to Drive.']);
        end

        % ---------------------------------------------------------------
        % Scenario 7 - frames that must never retain a command.
        % ---------------------------------------------------------------
        function invalidFramesNeverRetainOrRefreshACommand(testCase)
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            payload = TestVcuCommandLoop.controlPayload(command);
            valid = TestVcuCommandLoop.controlFrame(hex2dec('186'), payload);

            invalid = { ...
                TestVcuCommandLoop.withField(valid, 'isExtended', true), 'extended frame'; ...
                TestVcuCommandLoop.withField(valid, 'isRemote', true), 'remote frame'; ...
                TestVcuCommandLoop.withField(valid, 'dlc', uint8(7)), 'DLC 7'; ...
                TestVcuCommandLoop.withField(valid, 'dlc', uint8(0)), 'DLC 0'; ...
                TestVcuCommandLoop.controlFrame(hex2dec('187'), payload), 'unknown ID 0x187'; ...
                TestVcuCommandLoop.controlFrame(hex2dec('400'), payload), 'own status ID 0x400'; ...
                TestVcuCommandLoop.withField(valid, 'drop', true), 'injected drop'};

            % (a) From a cold bank, none of them may create a command.
            for index = 1:size(invalid, 1)
                run = TestVcuCommandLoop.newRun();
                for tick = 1:5
                    run = TestVcuCommandLoop.step(run, invalid{index, 1});
                end
                testCase.verifyEqual(run.bank.hasCommand, false(1, 4), ...
                    sprintf('%s must not retain a command.', invalid{index, 2}));
                testCase.verifyEqual(run.stateOutput.mode, ...
                    repmat(inverterhil.protocol().state.idle, 1, 4), ...
                    sprintf('%s must not move any channel out of Idle.', ...
                    invalid{index, 2}));
            end

            % (b) An already-retained command must not have its age refreshed
            % by an invalid frame, or a malformed transmitter could hold a
            % channel alive forever.
            for index = 1:size(invalid, 1)
                run = TestVcuCommandLoop.newRun();
                run = TestVcuCommandLoop.step(run, valid);
                retainedAt = run.bank.lastValidTickMs(1);
                for tick = 1:20
                    run = TestVcuCommandLoop.step(run, invalid{index, 1});
                end
                testCase.verifyEqual(run.bank.lastValidTickMs(1), retainedAt, ...
                    sprintf('%s must not refresh command age.', invalid{index, 2}));
                snapshot = inverterhil.decoderSnapshot(run.bank, uint32(20));
                testCase.verifyEqual(snapshot.ageMs(1), uint32(20), ...
                    sprintf('Command age must keep growing through %s.', ...
                    invalid{index, 2}));
            end
        end

        % ---------------------------------------------------------------
        % Scenario 8 - retention across ticks with no new frame.
        % ---------------------------------------------------------------
        function retainedCommandIsHonouredOnLaterTicksWithinTheTimeout(testCase)
            % The real bus carries one control frame per channel every few
            % milliseconds, not one per 1 ms model tick, so the channel MUST
            % stay in Drive on the ticks in between. Before the bank was
            % threaded through STEPMODEL this was impossible.
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            frame = TestVcuCommandLoop.controlFrame(hex2dec('1B6'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            run = TestVcuCommandLoop.step(run, frame);
            testCase.assertEqual(run.stateOutput.mode(4), ...
                inverterhil.protocol().state.drive);

            for age = 1:50
                run = TestVcuCommandLoop.step(run, TestVcuCommandLoop.silentFrame());
                testCase.verifyEqual(run.stateOutput.mode(4), ...
                    inverterhil.protocol().state.drive, ...
                    sprintf('Retention must hold Drive at %d ms of age.', age));
                testCase.verifyFalse(run.stateOutput.channels(4).zeroTorque, ...
                    sprintf('Retention must hold torque authority at %d ms.', age));
                testCase.verifyTrue(run.bank.hasCommand(4));
                testCase.verifyEqual(TestVcuCommandLoop.wireState(run, 4), 1, ...
                    'Retention must be visible in the transmitted state field.');
            end

            % A refresh arriving inside the window restarts the clock.
            run = TestVcuCommandLoop.step(run, frame);
            snapshot = inverterhil.decoderSnapshot(run.bank, run.lastTick);
            testCase.verifyEqual(snapshot.ageMs(4), uint32(0), ...
                'A refresh must reset the command age.');
        end

        % ---------------------------------------------------------------
        % Scenario 9 - uint32 tick rollover.
        % ---------------------------------------------------------------
        function commandAgesStaySaneAcrossTheUint32TickRollover(testCase)
            % A free-running millisecond counter wraps after about 49.7 days.
            % Note that MATLAB's uint32 addition SATURATES rather than wraps,
            % so the tick is advanced with explicit modulo arithmetic here;
            % otherwise this test would silently exercise a frozen clock
            % instead of a rollover.
            command = TestVcuCommandLoop.emptyCommand();
            command.enable = true;
            frame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(command));

            run = TestVcuCommandLoop.newRun();
            run.tick = intmax('uint32') - uint32(20);

            % Command straddles the wrap while being refreshed every tick.
            for tick = 1:40
                run = TestVcuCommandLoop.step(run, frame);
                snapshot = inverterhil.decoderSnapshot(run.bank, run.lastTick);
                testCase.verifyEqual(snapshot.ageMs(1), uint32(0), ...
                    'A just-refreshed command has age 0 on either side of the wrap.');
            end
            testCase.verifyEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.drive, ...
                'Drive must survive the tick rollover.');
            testCase.assertLessThan(double(run.lastTick), 100, ...
                'Precondition: the tick counter must actually have wrapped.');

            % Now go silent across a second wrap and confirm the age grows by
            % exactly 1 ms per tick and the timeouts still fire at 50/500 ms.
            run = TestVcuCommandLoop.newRun();
            run.tick = intmax('uint32') - uint32(20);
            run = TestVcuCommandLoop.step(run, frame);
            timing = inverterhil.protocol().timing;
            for age = 1:601
                run = TestVcuCommandLoop.step(run, TestVcuCommandLoop.silentFrame());
                snapshot = inverterhil.decoderSnapshot(run.bank, run.lastTick);
                testCase.assertEqual(snapshot.ageMs(1), uint32(age), ...
                    sprintf('Age must be exactly %d ms across the wrap.', age));
                if age == double(timing.commandTorqueZeroMs)
                    testCase.verifyFalse(run.stateOutput.channels(1).zeroTorque);
                elseif age == double(timing.commandTorqueZeroMs) + 1
                    testCase.verifyTrue(run.stateOutput.channels(1).zeroTorque);
                elseif age == double(timing.commandErrorMs)
                    testCase.verifyEqual(run.stateOutput.mode(1), ...
                        inverterhil.protocol().state.drive);
                elseif age == double(timing.commandErrorMs) + 1
                    testCase.verifyEqual(run.stateOutput.mode(1), ...
                        inverterhil.protocol().state.error, ...
                        'The 500 ms boundary must still fire across a wrap.');
                end
            end
        end

        % ---------------------------------------------------------------
        % Unsupported current-control mode (plan section 4.1.2 refusal policy).
        % ---------------------------------------------------------------
        function currentControlModeBitRefusesDriveAndZeroesTorque(testCase)
            % INVERTER_HIL_PLAN.MD section 4.1.2: a command with byte 0 bit 3
            % set must "refresh command age", "set unsupported_current_mode,
            % mark the affected inverter not ready, force its normal torque
            % and Id/Iq commands to zero, and refuse Idle-to-Drive", and if
            % asserted while already in Drive must "leave Drive for Idle on
            % the next model sample". The VCU header marks the same bit
            % "test bench only; do not use in car", so the HIL refusing it is
            % the behaviour that catches a firmware mistake.
            plain = TestVcuCommandLoop.emptyCommand();
            plain.enable = true;
            currentMode = plain;
            currentMode.currentMode = true;

            driveFrame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(plain));
            currentModeFrame = TestVcuCommandLoop.controlFrame(hex2dec('186'), ...
                TestVcuCommandLoop.controlPayload(currentMode));

            % (a) Refuse Idle-to-Drive.
            run = TestVcuCommandLoop.newRun();
            for tick = 1:5
                run = TestVcuCommandLoop.step(run, currentModeFrame);
            end
            testCase.assertTrue(run.bank.commands(1).currentMode, ...
                'Precondition: bit 3 must have been decoded and retained.');
            testCase.verifyEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.idle, ...
                'Current-control mode must refuse Idle-to-Drive.');
            testCase.verifyTrue(run.stateOutput.channels(1).unsupportedCurrentMode, ...
                'The unsupported_current_mode diagnostic must be raised.');
            testCase.verifyFalse(TestVcuCommandLoop.wireReady(run, 1), ...
                'The affected inverter must report not ready.');

            % (b) Leave Drive if asserted while driving.
            run = TestVcuCommandLoop.newRun();
            for tick = 1:5
                run = TestVcuCommandLoop.step(run, driveFrame);
            end
            testCase.assertEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.drive);
            run = TestVcuCommandLoop.step(run, currentModeFrame);
            testCase.verifyEqual(run.stateOutput.mode(1), ...
                inverterhil.protocol().state.idle, ...
                'Current-control mode asserted in Drive must return to Idle.');
        end

        % ---------------------------------------------------------------
        % The frame builder must itself agree with the decoder, or every
        % assertion above would be built on an unverified stimulus.
        % ---------------------------------------------------------------
        function frameBuilderRoundTripsThroughTheProductionDecoder(testCase)
            cases = { ...
                struct('enable', true, 'resetError', false, 'ascAllowed', false, ...
                    'currentMode', false, 'speedSetpointRpm', int16(0), ...
                    'rawTorquePosCounts', int16(0), 'rawTorqueNegCounts', int16(0)), ...
                struct('enable', true, 'resetError', true, 'ascAllowed', true, ...
                    'currentMode', true, 'speedSetpointRpm', int16(-12345), ...
                    'rawTorquePosCounts', int16(8192), 'rawTorqueNegCounts', int16(-8192)), ...
                struct('enable', false, 'resetError', false, 'ascAllowed', false, ...
                    'currentMode', false, 'speedSetpointRpm', intmax('int16'), ...
                    'rawTorquePosCounts', intmin('int16'), ...
                    'rawTorqueNegCounts', intmax('int16'))};

            for index = 1:numel(cases)
                expected = cases{index};
                payload = TestVcuCommandLoop.controlPayload(expected);

                % Plan section 4.1: byte 0 bits 4-7 and byte 1 are reserved
                % and must be zero in generated test vectors.
                testCase.verifyEqual(bitand(payload(1), uint8(240)), uint8(0));
                testCase.verifyEqual(payload(2), uint8(0));

                [accepted, channel, decoded, reason] = ...
                    inverterhil.decodeControlFrame(uint32(hex2dec('186')), ...
                    uint8(8), payload, false, false);
                testCase.verifyTrue(accepted);
                testCase.verifyEqual(channel, uint8(1));
                testCase.verifyEqual(reason, 'accepted');
                testCase.verifyEqual(decoded.enable, expected.enable);
                testCase.verifyEqual(decoded.resetError, expected.resetError);
                testCase.verifyEqual(decoded.ascAllowed, expected.ascAllowed);
                testCase.verifyEqual(decoded.currentMode, expected.currentMode);
                testCase.verifyEqual(decoded.speedSetpointRpm, ...
                    expected.speedSetpointRpm);
                testCase.verifyEqual(decoded.rawTorquePosCounts, ...
                    expected.rawTorquePosCounts);
                testCase.verifyEqual(decoded.rawTorqueNegCounts, ...
                    expected.rawTorqueNegCounts);
            end
        end
    end

    methods (Static, Access = private)

        function command = emptyCommand()
            %EMPTYCOMMAND A quiescent Ephorus control command.
            command = struct( ...
                'enable', false, ...
                'resetError', false, ...
                'ascAllowed', false, ...
                'currentMode', false, ...
                'speedSetpointRpm', int16(0), ...
                'rawTorquePosCounts', int16(0), ...
                'rawTorqueNegCounts', int16(0));
        end

        function payload = controlPayload(command)
            %CONTROLPAYLOAD Encode INVERTER_HIL_PLAN.MD section 4.1 byte by byte.
            %
            %   Written from the protocol table rather than by inverting
            %   INVERTERHIL.DECODECONTROLFRAME, so the two are independent.
            %   Byte and bit arithmetic is explicit so the result does not
            %   depend on host endianness.
            payload = zeros(1, 8, 'uint8');
            flags = uint8(0);
            if command.enable
                flags = bitor(flags, uint8(1));      % bit 0
            end
            if command.resetError
                flags = bitor(flags, uint8(2));      % bit 1
            end
            if command.ascAllowed
                flags = bitor(flags, uint8(4));      % bit 2
            end
            if command.currentMode
                flags = bitor(flags, uint8(8));      % bit 3
            end
            payload(1) = flags;
            payload(2) = uint8(0);                   % reserved, must be zero
            payload(3:4) = TestVcuCommandLoop.int16Bytes(command.speedSetpointRpm);
            payload(5:6) = TestVcuCommandLoop.int16Bytes(command.rawTorquePosCounts);
            payload(7:8) = TestVcuCommandLoop.int16Bytes(command.rawTorqueNegCounts);
        end

        function bytes = int16Bytes(value)
            %INT16BYTES Little-endian low/high byte pair for a signed int16.
            raw = double(value);
            if raw < 0
                raw = raw + 65536;
            end
            bytes = uint8([mod(raw, 256), floor(raw / 256)]);
        end

        function frame = controlFrame(id, payload)
            %CONTROLFRAME One received frame in RECEIVECONTROLFRAME's format.
            frame = struct( ...
                'id', uint32(id), ...
                'dlc', uint8(8), ...
                'payload', payload, ...
                'isExtended', false, ...
                'isRemote', false, ...
                'drop', false);
        end

        function frame = silentFrame()
            %SILENTFRAME The "no CAN data this tick" frame the model publishes.
            frame = TestVcuCommandLoop.controlFrame(0, zeros(1, 8, 'uint8'));
            frame.dlc = uint8(0);
            frame.drop = true;
        end

        function value = withField(value, name, fieldValue)
            value.(name) = fieldValue;
        end

        function run = newRun()
            %NEWRUN A cold model: initial state, plant, and empty decoder bank.
            run.config = inverterhil.defaultStateConfig();
            run.cal = inverterhil.defaultCalibration();
            run.state = inverterhil.initialSystemState(run.config);
            run.plantState = inverterhil.initialPlantState(run.cal);
            run.bank = inverterhil.initialDecoderBank();
            run.tick = uint32(0);
            run.lastTick = uint32(0);
            run.cycle = [];
            run.stateOutput = [];
            run.plantOutput = [];
        end

        function run = step(run, frame)
            %STEP Advance one 1 ms tick with one received frame.
            run.lastTick = run.tick;
            [run.state, run.plantState, run.cycle, run.stateOutput, ...
                run.plantOutput, run.bank] = inverterhil.stepModel( ...
                run.state, run.plantState, run.tick, run.config, run.cal, ...
                run.bank, frame);
            % MATLAB's uint32 addition saturates at INTMAX; a millisecond
            % counter wraps. Modulo arithmetic keeps the rollover real.
            run.tick = uint32(mod(double(run.tick) + 1, 2^32));
        end

        function value = wireState(run, channel)
            %WIRESTATE The two-bit state field as the VCU would decode it.
            status = inverterhil.decodeStatus3X3(run.cycle.payloads(2 * channel - 1, :));
            value = status.state;
        end

        function value = wireReady(run, channel)
            status = inverterhil.decodeStatus3X3(run.cycle.payloads(2 * channel - 1, :));
            value = status.ready;
        end
    end
end
