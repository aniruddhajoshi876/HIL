classdef TestStateMachine < matlab.unittest.TestCase
    methods (Test)
        function defaultsAndInitialStateAreDeterministic(testCase)
            config = TestStateMachine.config();
            testCase.verifyEqual(inverterhil.defaultStateConfig(), config);
            testCase.verifyEqual(inverterhil.defaultChannelStateInput(), ...
                TestStateMachine.channelInput());
            testCase.verifyEqual(inverterhil.defaultStateInput(), ...
                TestStateMachine.systemInput());

            state = inverterhil.initialChannelState( ...
                config.channels(1), config, true);
            testCase.verifyEqual(state.mode, uint8(0));
            testCase.verifyEqual(state.modeName, 'Idle');
            testCase.verifyEqual(state.transitionReason, 'initial_idle');
            testCase.verifyTrue(state.zeroTorque);
            testCase.verifyTrue(state.ready);
            testCase.verifyFalse(state.errorLatched);
            testCase.verifyFalse(state.configErrorLatched);
            testCase.verifyEqual(state.resetWaitUs, uint64(500));
        end

        function exercisesIdleDriveAndExplicitExitTransitions(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            state = inverterhil.initialChannelState(channel, config, true);
            input = TestStateMachine.channelInput();

            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, ...
                'hold_idle_can_disabled');
            testCase.verifyTrue(output.zeroTorque);

            input.commandEnable = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(1));
            testCase.verifyEqual(output.transitionReason, 'idle_to_drive');
            testCase.verifyFalse(output.zeroTorque);
            testCase.verifyTrue(output.ready);

            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.transitionReason, 'hold_drive');
            testCase.verifyFalse(output.zeroTorque);

            input.commandEnable = false;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, 'can_enable_cleared');
            testCase.verifyTrue(output.zeroTorque);

            input.commandEnable = true;
            [state, ~] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            input.controlDisable = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, ...
                'control_disable_provisional_idle');
            testCase.verifyTrue(output.zeroTorque);
        end

        function commandTimeoutBoundariesAreStrict(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            ages = [50 51 500 501];
            expectedModes = uint8([1 1 1 2]);
            expectedZero = [false true true true];
            expectedTorqueTimeout = [false true true true];
            expectedErrorTimeout = [false false false true];
            expectedReasons = {'hold_drive', ...
                'hold_drive_command_timeout_zero_torque', ...
                'hold_drive_command_timeout_zero_torque', ...
                'error_command_timeout'};

            for index = 1:numel(ages)
                [state, input] = TestStateMachine.drive(testCase, config, channel);
                input.commandAgeMs = uint32(ages(index));
                [~, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, expectedModes(index));
                testCase.verifyEqual(output.zeroTorque, expectedZero(index));
                testCase.verifyEqual(output.commandTorqueTimeout, ...
                    expectedTorqueTimeout(index));
                testCase.verifyEqual(output.commandErrorTimeout, ...
                    expectedErrorTimeout(index));
                testCase.verifyEqual(output.transitionReason, ...
                    expectedReasons{index});
            end
        end

        function positionAndControlPinThresholdsUseFirstSamplePolicy(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            [state, input] = TestStateMachine.drive(testCase, config, channel);

            input.positionAgeS = 350e-6;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(1));
            testCase.verifyFalse(output.positionTimeoutQuantized);

            input.positionAgeS = 350e-6 + eps(350e-6);
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.activeFault, 'position_timeout');
            testCase.verifyTrue(output.positionTimeoutQuantized);

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.controlEnable = false;
            for sample = 1:200
                [state, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, uint8(1));
                testCase.verifyTrue(output.zeroTorque);
                if sample == 1
                    testCase.verifyEqual(output.transitionReason, ...
                        'hold_drive_control_enable_low');
                end
            end
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.activeFault, 'control_enable_low');
            testCase.verifyEqual(output.transitionReason, ...
                'error_control_enable_low');
        end

        function evaluatesEnDatAndDisconnectedConfigurationSemantics(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);

            [valid, reason] = inverterhil.evaluateMandatoryConfiguration(channel);
            testCase.verifyTrue(valid);
            testCase.verifyEqual(reason, 'valid');

            channel.encoderType = 'Resolver';
            [valid, reason] = inverterhil.evaluateMandatoryConfiguration(channel);
            testCase.verifyFalse(valid);
            testCase.verifyEqual(reason, 'missing_encoder_reference');
            channel.encoderReference = 0;
            [valid, reason] = inverterhil.evaluateMandatoryConfiguration(channel);
            testCase.verifyTrue(valid);
            testCase.verifyEqual(reason, 'valid');

            channel = config.channels(1);
            channel.motorPolePairs = NaN;
            [valid, reason] = inverterhil.evaluateMandatoryConfiguration(channel);
            testCase.verifyFalse(valid);
            testCase.verifyEqual(reason, 'missing_motor_pole_pairs');

            channel = config.channels(1);
            channel.connected = false;
            [valid, reason] = inverterhil.evaluateMandatoryConfiguration(channel);
            testCase.verifyTrue(valid);
            testCase.verifyEqual(reason, 'valid');
            state = inverterhil.initialChannelState(channel, config, true);
            testCase.verifyEqual(state.mode, uint8(0));
            testCase.verifyFalse(state.ready);
            testCase.verifyFalse(state.configErrorLatched);
            input = TestStateMachine.channelInput();
            input.commandEnable = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, 'disconnected');
        end

        function appliesPerChannelAndUnitWideConfigErrorScopes(testCase)
            config = TestStateMachine.config();
            config.channels(2).motorPolePairs = NaN;
            config.configErrorScope = uint8(0);
            state = inverterhil.initialSystemState(config);
            testCase.verifyEqual([state.channels.mode], uint8([0 3 0 0]));
            testCase.verifyEqual(state.channels(2).configurationReason, ...
                'missing_motor_pole_pairs');

            config.configErrorScope = uint8(1);
            state = inverterhil.initialSystemState(config);
            testCase.verifyEqual([state.channels.mode], uint8([3 3 3 3]));
            testCase.verifyEqual(state.channels(1).configurationReason, ...
                'unit_configuration_invalid');
            testCase.verifyEqual(state.channels(2).configurationReason, ...
                'missing_motor_pole_pairs');
        end

        function configErrorRequiresPowerCycleToClear(testCase)
            invalidConfig = TestStateMachine.config();
            invalidConfig.channels(1).rotationDirection = NaN;
            state = inverterhil.initialChannelState( ...
                invalidConfig.channels(1), invalidConfig, true);
            testCase.verifyEqual(state.mode, uint8(3));
            testCase.verifyTrue(state.configErrorLatched);

            validConfig = TestStateMachine.config();
            input = TestStateMachine.channelInput();
            input.resetError = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, validConfig.channels(1), validConfig, true);
            testCase.verifyEqual(output.mode, uint8(3));
            testCase.verifyEqual(output.transitionReason, ...
                'hold_config_error_power_cycle_required');

            input.powerCycle = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, validConfig.channels(1), validConfig, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, ...
                'power_cycle_valid_configuration');
            testCase.verifyFalse(state.configErrorLatched);
            testCase.verifyTrue(output.zeroTorque);

            state = inverterhil.initialChannelState( ...
                invalidConfig.channels(1), invalidConfig, true);
            input = TestStateMachine.channelInput();
            input.powerCycle = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, invalidConfig.channels(1), invalidConfig, true);
            testCase.verifyEqual(output.mode, uint8(3));
            testCase.verifyEqual(output.transitionReason, ...
                'power_cycle_missing_rotation_direction');
        end

        function operationalFaultBoundariesAreStrict(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            safeCases = { ...
                'dcLinkV', 700; ...
                'dcLinkV', -10; ...
                'phaseCurrentsA', [120 0 0]; ...
                'motorTemperatureC', channel.motorShutdownC; ...
                'switchTemperatureC', 145};
            for index = 1:size(safeCases, 1)
                state = inverterhil.initialChannelState(channel, config, true);
                input = TestStateMachine.channelInput();
                input.(safeCases{index, 1}) = safeCases{index, 2};
                [~, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyNotEqual(output.mode, uint8(2));
            end

            faultCases = { ...
                'dcLinkV', 700 + eps(700), 'dc_link_overvoltage'; ...
                'dcLinkV', -10 - eps(10), 'dc_link_invalid_low'; ...
                'phaseCurrentsA', [120 + eps(120) 0 0], 'phase_overcurrent'; ...
                'desaturation', true, 'desaturation'; ...
                'motorTemperatureC', channel.motorShutdownC + eps(155), 'motor_overtemperature'; ...
                'switchTemperatureC', 145 + eps(145), 'switch_overtemperature'; ...
                'phaseCurrentMeasurementFailure', true, 'phase_current_measurement'; ...
                'dcLinkMeasurementFailure', true, 'dc_link_measurement'; ...
                'switchTemperatureMeasurementFailure', true, 'switch_temperature_measurement'};
            for index = 1:size(faultCases, 1)
                state = inverterhil.initialChannelState(channel, config, true);
                input = TestStateMachine.channelInput();
                input.(faultCases{index, 1}) = faultCases{index, 2};
                [~, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, uint8(2));
                testCase.verifyEqual(output.activeFault, faultCases{index, 3});
                testCase.verifyEqual(output.transitionReason, ...
                    ['error_' faultCases{index, 3}]);
                testCase.verifyTrue(output.zeroTorque);
            end

            state = inverterhil.initialChannelState(channel, config, true);
            input = TestStateMachine.channelInput();
            input.commandEnable = true;
            input.dcLinkV = config.dcLinkMinimumV;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, ...
                'hold_idle_dc_link_below_minimum');

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.dcLinkV = config.dcLinkMinimumV - eps(config.dcLinkMinimumV);
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.activeFault, 'dc_link_undervoltage');
        end

        function trackingFaultRequiresStrictMagnitudeAndDuration(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.idTrackingErrorA = 10;
            for sample = 1:60
                [state, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, uint8(1));
            end

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.iqTrackingErrorA = 10 + eps(10);
            for sample = 1:50
                [state, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, uint8(1));
            end
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.activeFault, 'current_tracking');
        end

        function resetRefusesActiveFaultAndHonorsQuantizedFloor(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.desaturation = true;
            input.resetError = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.transitionReason, ...
                'reset_refused_active_fault');
            testCase.verifyEqual(output.resetWaitS, 500e-6);

            input.desaturation = false;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, 'error_reset');
            testCase.verifyTrue(output.zeroTorque);
            testCase.verifyFalse(state.errorLatched);
        end

        function resetBackoffDoublesCapsAndRecoversToBase(testCase)
            config = TestStateMachine.config();
            config.resetBackoffMaxS = 0.004;
            inverterhil.validateStateConfig(config);
            channel = config.channels(1);
            state = inverterhil.initialChannelState(channel, config, true);
            expectedWaitUs = uint64([500 1000 2000 4000 4000]);

            for occurrence = 1:numel(expectedWaitUs)
                input = TestStateMachine.channelInput();
                input.commandEnable = true;
                [state, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.assertEqual(output.mode, uint8(1));

                input.phaseCurrentsA = [121 0 0];
                [state, output] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
                testCase.verifyEqual(output.mode, uint8(2));
                testCase.verifyEqual(state.resetWaitUs, ...
                    expectedWaitUs(occurrence));
                testCase.verifyEqual(state.errorOccurrences, ...
                    uint32(occurrence));

                input.phaseCurrentsA = [0 0 0];
                input.resetError = true;
                clearSamples = max(1, ceil(double(expectedWaitUs(occurrence)) / 1000));
                for sample = 1:clearSamples
                    [state, output] = inverterhil.stepChannelState( ...
                        state, input, channel, config, true);
                    if sample < clearSamples
                        testCase.verifyEqual(output.mode, uint8(2));
                        testCase.verifyEqual(output.transitionReason, ...
                            'reset_refused_backoff');
                    else
                        testCase.verifyEqual(output.mode, uint8(0));
                        testCase.verifyEqual(output.transitionReason, 'error_reset');
                    end
                end
            end

            input = TestStateMachine.channelInput();
            input.speedRpm = 100;
            for sample = 1:51
                [state, ~] = inverterhil.stepChannelState( ...
                    state, input, channel, config, true);
            end
            testCase.verifyEqual(state.errorOccurrences, uint32(5));
            testCase.verifyEqual(state.resetWaitUs, uint64(4000));

            input.speedRpm = 99;
            [state, ~] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(state.errorOccurrences, uint32(0));
            testCase.verifyEqual(state.resetWaitUs, uint64(500));
        end

        function resetRefusesReassertedUndervoltageBeforeClear(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.dcLinkV = 300;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.assertEqual(output.activeFault, 'dc_link_undervoltage');

            input.dcLinkV = 400;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.assertEqual(output.mode, uint8(2));

            input.dcLinkV = 300;
            input.resetError = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(2));
            testCase.verifyEqual(output.activeFault, 'dc_link_undervoltage');
            testCase.verifyEqual(output.transitionReason, ...
                'reset_refused_active_fault');
        end

        function idleOriginErrorCanResetBelowDriveMinimum(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            state = inverterhil.initialChannelState(channel, config, true);
            input = TestStateMachine.channelInput();
            input.desaturation = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.assertEqual(output.mode, uint8(2));
            testCase.assertEqual(output.activeFault, 'desaturation');

            input.desaturation = false;
            input.dcLinkV = 300;
            input.resetError = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, 'error_reset');
            testCase.verifyEqual(output.activeFault, 'none');
        end

        function currentModeAndAscRequireExplicitConjunctions(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.currentMode = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(0));
            testCase.verifyEqual(output.transitionReason, ...
                'unsupported_current_mode');
            testCase.verifyTrue(output.unsupportedCurrentMode);
            testCase.verifyTrue(output.zeroTorque);
            testCase.verifyFalse(output.ready);

            input.currentMode = false;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyEqual(output.mode, uint8(1));
            testCase.verifyEqual(output.transitionReason, 'idle_to_drive');

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.ascAllowed = true;
            input.speedRpm = channel.ascThresholdRpm + 1;
            input.dischargeActive = true;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyFalse(output.unsupportedAscEntry);
            testCase.verifyFalse(output.zeroTorque);

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.ascAllowed = true;
            input.speedRpm = channel.ascThresholdRpm;
            input.dischargeActive = true;
            input.controlEnable = false;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyFalse(output.unsupportedAscEntry);

            [state, input] = TestStateMachine.drive(testCase, config, channel);
            input.ascAllowed = true;
            input.speedRpm = channel.ascThresholdRpm + 1;
            input.dischargeActive = true;
            input.controlEnable = false;
            [~, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.verifyTrue(output.unsupportedAscEntry);
            testCase.verifyEqual(output.mode, uint8(1));
            testCase.verifyTrue(output.zeroTorque);
            testCase.verifyEqual(output.transitionReason, ...
                'hold_drive_unsupported_asc_entry');
        end

        function systemMaintainsChannelAndPairIsolation(testCase)
            config = TestStateMachine.config();
            [state, input] = TestStateMachine.driveSystem(testCase, config);
            input.channels(2).commandAgeMs = uint32(501);
            [~, output] = inverterhil.stepSystemState(state, input, config);
            testCase.verifyEqual(output.mode, uint8([1 2 1 1]));
            testCase.verifyEqual(output.zeroTorque, [false true false false]);
            testCase.verifyEqual(output.channels(2).activeFault, ...
                'command_timeout');

            [state, input] = TestStateMachine.driveSystem(testCase, config);
            input.dcLinkV = [300 400];
            [~, output] = inverterhil.stepSystemState(state, input, config);
            testCase.verifyEqual(output.mode, uint8([2 2 1 1]));
            testCase.verifyEqual({output.channels.activeFault}, ...
                {'dc_link_undervoltage', 'dc_link_undervoltage', 'none', 'none'});

            [state, input] = TestStateMachine.driveSystem(testCase, config);
            input.dcLinkV = [400 300];
            [~, output] = inverterhil.stepSystemState(state, input, config);
            testCase.verifyEqual(output.mode, uint8([1 1 2 2]));

            [state, input] = TestStateMachine.driveSystem(testCase, config);
            input.controlDisable = true;
            [~, output] = inverterhil.stepSystemState(state, input, config);
            testCase.verifyEqual(output.mode, uint8([0 0 0 0]));
            testCase.verifyEqual(output.zeroTorque, true(1, 4));

            [state, input] = TestStateMachine.driveSystem(testCase, config);
            input.controlEnable = false;
            [~, output] = inverterhil.stepSystemState(state, input, config);
            testCase.verifyEqual(output.mode, uint8([1 1 1 1]));
            testCase.verifyEqual(output.zeroTorque, true(1, 4));
        end

        function malformedConfigurationFailsWithDomainError(testCase)
            config = TestStateMachine.config();
            bad = rmfield(config, 'sampleTimeS');
            testCase.verifyError(@() inverterhil.validateStateConfig(bad), ...
                'inverterhil:InvalidStateConfig');
            bad = config;
            bad.sampleTimeS = complex(1e-3, 1);
            testCase.verifyError(@() inverterhil.validateStateConfig(bad), ...
                'inverterhil:InvalidStateConfig');
            bad = config;
            bad.channels = bad.channels.';
            testCase.verifyError(@() inverterhil.validateStateConfig(bad), ...
                'inverterhil:InvalidStateConfig');
            bad = config.channels(1);
            bad.connected = char(1);
            testCase.verifyError( ...
                @() inverterhil.evaluateMandatoryConfiguration(bad), ...
                'inverterhil:InvalidStateConfig');
            bad = config.channels(1);
            bad.encoderType = ["EnDat" "Resolver"];
            testCase.verifyError( ...
                @() inverterhil.evaluateMandatoryConfiguration(bad), ...
                'inverterhil:InvalidStateConfig');
        end

        function malformedChannelInputsFailClosed(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            state = inverterhil.initialChannelState(channel, config, true);
            cases = { ...
                'commandAgeMs', [1 2]; ...
                'commandEnable', char(1); ...
                'speedRpm', complex(10, 1); ...
                'positionAgeS', -eps; ...
                'dcLinkV', NaN; ...
                'phaseCurrentsA', zeros(3, 1); ...
                'motorTemperatureC', Inf};
            for index = 1:size(cases, 1)
                input = TestStateMachine.channelInput();
                input.(cases{index, 1}) = cases{index, 2};
                testCase.verifyError(@() inverterhil.stepChannelState( ...
                    state, input, channel, config, true), ...
                    'inverterhil:InvalidStateInput');
            end

            systemState = inverterhil.initialSystemState(config);
            systemInput = TestStateMachine.systemInput();
            systemInput.dcLinkV = [400; 400];
            testCase.verifyError(@() inverterhil.stepSystemState( ...
                systemState, systemInput, config), ...
                'inverterhil:InvalidStateInput');
        end

        function malformedRetainedStateFailsClosed(testCase)
            config = TestStateMachine.config();
            channel = config.channels(1);
            input = TestStateMachine.channelInput();
            base = inverterhil.initialChannelState(channel, config, true);

            bad = base;
            bad.errorLatched = [false false];
            testCase.verifyError(@() inverterhil.stepChannelState( ...
                bad, input, channel, config, true), ...
                'inverterhil:InvalidChannelState');

            bad = base;
            bad.zeroTorque = [true true];
            testCase.verifyError(@() inverterhil.stepChannelState( ...
                bad, input, channel, config, true), ...
                'inverterhil:InvalidChannelState');

            bad = base;
            bad.modeName = 42;
            testCase.verifyError(@() inverterhil.stepChannelState( ...
                bad, input, channel, config, true), ...
                'inverterhil:InvalidChannelState');

            bad = base;
            bad.latchedFaultCause = 42;
            testCase.verifyError(@() inverterhil.stepChannelState( ...
                bad, input, channel, config, true), ...
                'inverterhil:InvalidChannelState');

            bad = base;
            bad.latchedFaultCause = 'not_a_fault';
            testCase.verifyError(@() inverterhil.stepChannelState( ...
                bad, input, channel, config, true), ...
                'inverterhil:InvalidChannelState');

            systemState = inverterhil.initialSystemState(config);
            systemState = rmfield(systemState, 'configErrorScope');
            testCase.verifyError(@() inverterhil.stepSystemState( ...
                systemState, TestStateMachine.systemInput(), config), ...
                'inverterhil:InvalidSystemState');
        end
    end

    methods (Static, Access = private)
        function config = config()
            config = struct( ...
                'sampleTimeS', 1e-3, ...
                'dcLinkMinimumV', 350, ...
                'configErrorScope', uint8(0), ...
                'controlPinTorqueZeroS', 100e-6, ...
                'positionTimeoutS', 350e-6, ...
                'controlEnableErrorS', 0.200, ...
                'trackingErrorS', 0.050, ...
                'resetFloorS', 500e-6, ...
                'resetBackoffMaxS', 100, ...
                'recoveryS', 0.050);
            channel = struct( ...
                'connected', true, ...
                'motorPolePairs', 4, ...
                'rotationDirection', 1, ...
                'encoderType', 'EnDat', ...
                'encoderReference', NaN, ...
                'motorShutdownC', 155, ...
                'ascThresholdRpm', 1000);
            config.channels = repmat(channel, 1, 4);
        end

        function input = channelInput()
            input = struct( ...
                'commandAgeMs', uint32(0), ...
                'commandEnable', false, ...
                'resetError', false, ...
                'ascAllowed', false, ...
                'currentMode', false, ...
                'speedRpm', 0, ...
                'positionAgeS', 0, ...
                'controlEnable', true, ...
                'controlDisable', false, ...
                'dcLinkV', 400, ...
                'phaseCurrentsA', zeros(1, 3), ...
                'desaturation', false, ...
                'motorTemperatureC', 25, ...
                'switchTemperatureC', 25, ...
                'idTrackingErrorA', 0, ...
                'iqTrackingErrorA', 0, ...
                'phaseCurrentMeasurementFailure', false, ...
                'dcLinkMeasurementFailure', false, ...
                'switchTemperatureMeasurementFailure', false, ...
                'dischargeActive', false, ...
                'powerCycle', false);
        end

        function input = systemInput()
            input = struct( ...
                'controlEnable', true, ...
                'controlDisable', false, ...
                'powerCycle', false, ...
                'dcLinkV', [400 400], ...
                'channels', repmat(TestStateMachine.channelInput(), 1, 4));
        end

        function [state, input] = drive(testCase, config, channel)
            state = inverterhil.initialChannelState(channel, config, true);
            input = TestStateMachine.channelInput();
            input.commandEnable = true;
            [state, output] = inverterhil.stepChannelState( ...
                state, input, channel, config, true);
            testCase.assertEqual(output.mode, uint8(1));
            testCase.assertEqual(output.transitionReason, 'idle_to_drive');
            testCase.assertFalse(output.zeroTorque);
        end

        function [state, input] = driveSystem(testCase, config)
            state = inverterhil.initialSystemState(config);
            input = TestStateMachine.systemInput();
            for channel = 1:4
                input.channels(channel).commandEnable = true;
            end
            [state, output] = inverterhil.stepSystemState(state, input, config);
            testCase.assertEqual(output.mode, uint8([1 1 1 1]));
            testCase.assertEqual(output.zeroTorque, false(1, 4));
        end
    end
end
