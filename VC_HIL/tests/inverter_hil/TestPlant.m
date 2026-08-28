classdef TestPlant < matlab.unittest.TestCase
    methods (Test)
        function positiveNegativeErrorAndAllTorqueBounds(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = repmat(0.1, 1, 4);
            cal.speedKi = zeros(1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            cal.modelTorqueMinNm(3) = -12;
            cal.modelTorqueMaxNm(3) = 15;
            cal.modelCurrentMaxA(4) = 5;
            cal.torqueConstantNmPerA(4) = 2;
            validateCalibration(cal);

            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            for index = 1:4
                input.channels(index).torqueLimitNegativeNm = -100;
                input.channels(index).torqueLimitPositiveNm = 100;
                input.channels(index).speedSetpointRpm = 1000;
            end
            input.channels(1).torqueLimitNegativeNm = -20;
            input.channels(1).torqueLimitPositiveNm = 20;
            input.channels(2).torqueLimitNegativeNm = -20;
            input.channels(2).torqueLimitPositiveNm = 20;
            input.channels(2).speedSetpointRpm = -1000;

            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.torqueSetpointNm, [20 -20 15 10], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual( ...
                [output.channels.rawControllerTorqueNm], [100 -100 100 100], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual( ...
                [output.channels.normalTorqueLowerNm], [-20 -20 -12 -10]);
            testCase.verifyEqual( ...
                [output.channels.normalTorqueUpperNm], [20 20 15 10]);

            bad = input;
            bad.channels(1).torqueLimitPositiveNm = -1;
            testCase.verifyError(@() stepPlant(state, bad, cal), ...
                'inverterhil:InvalidPlantInput');
            bad = input;
            bad.channels(1).torqueLimitNegativeNm = 1;
            testCase.verifyError(@() stepPlant(state, bad, cal), ...
                'inverterhil:InvalidPlantInput');
        end

        function proportionalAndPiControllersUseExpectedTerms(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = repmat(0.2, 1, 4);
            cal.speedKi = zeros(1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).speedSetpointRpm = 100;
            [next, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.channels(1).rawControllerTorqueNm, 20, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(next.speedIntegratorNm(1), 0);

            cal.speedKp = repmat(0.1, 1, 4);
            cal.speedKi = repmat(2, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).speedSetpointRpm = 100;
            [next, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(next.speedIntegratorNm(1), 0.2, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).rawControllerTorqueNm, 10.2, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 10.2, ...
                'AbsTol', 1e-12);
        end

        function antiWindupFreezesAndRecovers(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = repmat(0.1, 1, 4);
            cal.speedKi = repmat(10, 1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).torqueLimitNegativeNm = -10;
            input.channels(1).torqueLimitPositiveNm = 10;
            input.channels(1).speedSetpointRpm = 1000;

            [state, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(state.speedIntegratorNm(1), 0);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 10);

            state.omegaRadPerS(1) = 0;
            input.channels(1).speedSetpointRpm = -20;
            [state, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(state.speedIntegratorNm(1), -0.2, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).rawControllerTorqueNm, -2.2, ...
                'AbsTol', 1e-12);
        end

        function integralOnlyControllerStillReachesSaturation(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = zeros(1, 4);
            cal.speedKi = repmat(100, 1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).torqueLimitNegativeNm = -10;
            input.channels(1).torqueLimitPositiveNm = 10;
            input.channels(1).speedSetpointRpm = 1000;

            torqueSetpointNm = zeros(1, 5);
            for stepIndex = 1:5
                [state, output] = stepPlant(state, input, cal);
                torqueSetpointNm(stepIndex) = ...
                    output.channels(1).torqueSetpointNm;
            end
            testCase.verifyEqual(torqueSetpointNm, repmat(10, 1, 5), ...
                'Pure integral control must not freeze indefinitely at zero.');
            testCase.verifyEqual(state.speedIntegratorNm(1), 10);

            state.omegaRadPerS(1) = 0;
            input.channels(1).speedSetpointRpm = -1;
            [state, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(state.speedIntegratorNm(1), 9.9, ...
                'AbsTol', 1e-12, ...
                'Reverse error must unwind a saturated pure-I controller.');
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 9.9, ...
                'AbsTol', 1e-12);

            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).torqueLimitNegativeNm = -10;
            input.channels(1).torqueLimitPositiveNm = 10;
            input.channels(1).speedSetpointRpm = -1000;
            [state, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(state.speedIntegratorNm(1), -10);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, -10, ...
                'Pure integral control must reach negative saturation.');
        end

        function slewLagAndFinalAuthorityAreExact(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = ones(1, 4);
            cal.speedKi = zeros(1, 4);
            cal.torqueSlewNmPerS = repmat(1000, 1, 4);
            cal.torqueLagS = repmat(0.01, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).speedSetpointRpm = 100;
            alpha = 1 - exp(-0.001 / 0.01);

            [state, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 1, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).torqueActualNm, alpha, ...
                'AbsTol', 1e-12);
            firstActual = alpha;
            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 2, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).torqueActualNm, ...
                firstActual + alpha * (2 - firstActual), 'AbsTol', 1e-12);

            state = initialPlantState(cal);
            state.torqueSetpointNm(1) = 5;
            state.torqueActualNm(1) = 4;
            state.speedIntegratorNm(1) = 7;
            input = TestPlant.driveInput(cal);
            input.channels(1).speedSetpointRpm = 1000;
            input.channels(1).zeroTorque = true;
            input.channels(1).authorityReason = 'test_block';
            [next, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.channels(1).torqueSetpointNm, 0);
            testCase.verifyEqual(output.channels(1).torqueActualNm, 0);
            testCase.verifyEqual(next.speedIntegratorNm(1), 7);
            testCase.verifyTrue(output.channels(1).zeroTorqueApplied);
            testCase.verifyEqual(output.channels(1).authorityReason, 'test_block');

            input.channels(1).zeroTorque = false;
            input.channels(1).commandTorqueTimeout = true;
            [next, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(next.speedIntegratorNm(1), 7);
            testCase.verifyEqual(output.channels(1).torqueActualNm, 0);
            testCase.verifyEqual(output.channels(1).authorityReason, ...
                'command_torque_timeout');
        end

        function mechanicalEquationLoadsDragSpeedLimitAndIqAreExact(testCase)
            cal = TestPlant.calibration();
            cal.sampleTimeS = 0.1;
            cal.speedKp = zeros(1, 4);
            cal.speedKi = zeros(1, 4);
            cal.inertiaKgM2 = repmat(2, 1, 4);
            cal.dragNmPerRadS = repmat(0.5, 1, 4);
            cal.torqueConstantNmPerA = repmat(2, 1, 4);
            cal.torqueSlewNmPerS = repmat(1e6, 1, 4);
            cal.speedMaxRpm(3) = 100;
            validateCalibration(cal);
            state = initialPlantState(cal);
            state.omegaRadPerS(1:2) = 20;
            state.torqueSetpointNm(1:3) = 10;
            state.torqueActualNm(1:3) = 10;
            state.speedIntegratorNm(1:3) = 10;
            state.omegaRadPerS(3) = 100 * 2 * pi / 60;
            input = TestPlant.driveInput(cal);
            input.channels(1).loadTorqueNm = 3;
            input.channels(2).loadTorqueNm = -3;
            input.channels(3).loadTorqueNm = -20;

            [~, output] = stepPlant(state, input, cal);
            expectedOmega1 = 20 + 0.1 * ((10 - 3 - 0.5 * 20) / 2);
            expectedOmega2 = 20 + 0.1 * ((10 + 3 - 0.5 * 20) / 2);
            testCase.verifyEqual(output.channels(1).speedRpm, ...
                expectedOmega1 * 60 / (2 * pi), 'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(2).speedRpm, ...
                expectedOmega2 * 60 / (2 * pi), 'AbsTol', 1e-12);
            testCase.verifyTrue(output.channels(3).speedLimited);
            testCase.verifyEqual(output.channels(3).speedRpm, 100, ...
                'AbsTol', 1e-12);
            testCase.verifyGreaterThan(output.channels(3).unboundedSpeedRpm, 100);
            testCase.verifyEqual(output.channels(1).idSetpointA, 0);
            testCase.verifyEqual(output.channels(1).idActualA, 0);
            testCase.verifyEqual(output.channels(1).iqSetpointA, 5);
            testCase.verifyEqual(output.channels(1).iqActualA, 5);
        end

        function dcPowerSignsFloorsAndThermalStepAreExact(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = zeros(1, 4);
            cal.speedKi = zeros(1, 4);
            cal.dragNmPerRadS = zeros(1, 4);
            cal.torqueConstantNmPerA = repmat(2, 1, 4);
            cal.motoringEfficiency = repmat(0.8, 1, 4);
            cal.regenEfficiency = repmat(0.7, 1, 4);
            cal.dcVoltageFloorV = repmat(10, 1, 4);
            state = initialPlantState(cal);
            state.omegaRadPerS = repmat(100, 1, 4);
            state.torqueSetpointNm = [10 -10 10 10];
            state.torqueActualNm = [10 -10 10 10];
            state.speedIntegratorNm = [10 -10 10 10];
            input = TestPlant.driveInput(cal);
            input.channels(1).loadTorqueNm = 10;
            input.channels(2).loadTorqueNm = -10;
            input.channels(3).loadTorqueNm = 10;
            input.channels(4).loadTorqueNm = 10;
            input.channels(1).dcLinkV = 400;
            input.channels(2).dcLinkV = 400;
            input.channels(3).dcLinkV = 0;
            input.channels(4).dcLinkV = -400;

            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual([output.channels.mechanicalPowerW], ...
                [1000 -1000 1000 1000], 'AbsTol', 1e-10);
            testCase.verifyEqual([output.channels.dcPowerW], ...
                [1250 -700 1250 1250], 'AbsTol', 1e-10);
            testCase.verifyEqual([output.channels.dcCurrentA], ...
                [3.125 -1.75 125 3.125], 'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).motorLossW, 150, ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).switchLossW, 100, ...
                'AbsTol', 1e-12);

            motorAlpha = 1 - exp(-0.001 / 30);
            switchAlpha = 1 - exp(-0.001 / 10);
            expectedMotorC = 25 + motorAlpha * ((25 + 150 * 0.02) - 25);
            expectedSwitchC = 25 + switchAlpha * ((25 + 100 * 0.01) - 25);
            testCase.verifyEqual(output.channels(1).motorTemperatureC, ...
                expectedMotorC, 'AbsTol', 1e-12);
            testCase.verifyEqual(output.channels(1).switchTemperatureC, ...
                expectedSwitchC, 'AbsTol', 1e-12);
        end

        function switchAndMotorDeratingEndpointsAreIsolated(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = repmat(0.1, 1, 4);
            cal.speedKi = zeros(1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            state = initialPlantState(cal);
            state.switchTemperatureC = [90 115 140 25];
            input = TestPlant.driveInput(cal);
            for index = 1:4
                input.channels(index).speedSetpointRpm = 1000;
                input.channels(index).torqueLimitNegativeNm = -50;
                input.channels(index).torqueLimitPositiveNm = 50;
            end
            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual([output.channels.switchDeratingFactor], ...
                [1 0.5 0 1], 'AbsTol', 1e-12);
            testCase.verifyEqual(output.torqueSetpointNm, [50 25 0 50], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.maxAllowedCurrentA, [100 50 0 100], ...
                'AbsTol', 1e-12);

            state = initialPlantState(cal);
            state.motorTemperatureC = [120 135 150 25];
            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual([output.channels.motorDeratingFactor], ...
                [1 0.5 0 1], 'AbsTol', 1e-12);
            testCase.verifyEqual(output.torqueSetpointNm, [50 25 0 50], ...
                'AbsTol', 1e-12);
        end

        function fourChannelsRemainIsolatedAndFeedStatusPackers(testCase)
            cal = TestPlant.calibration();
            cal.speedKp = repmat(0.1, 1, 4);
            cal.speedKi = zeros(1, 4);
            cal.torqueSlewNmPerS = repmat(1e9, 1, 4);
            cal.torqueLagS = repmat(1e-6, 1, 4);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(2).speedSetpointRpm = 100;
            input.channels(2).rawTorquePosCounts = int16(8192);
            input.channels(2).rawTorqueNegCounts = int16(-8192);
            [~, output] = stepPlant(state, input, cal);

            testCase.verifyEqual(output.torqueSetpointNm([1 3 4]), [0 0 0]);
            testCase.verifyEqual(output.speedRpm([1 3 4]), [0 0 0]);
            testCase.verifyGreaterThan(output.torqueSetpointNm(2), 0);
            testCase.verifyEqual(output.channels(2).rawTorquePosCounts, int16(8192));
            testCase.verifyEqual(output.channels(2).torquePosNm256, 32);
            testCase.verifyEqual(output.channels(2).torquePosNm512, 16);

            channelStatus = repmat(struct('status3X3', struct(), ...
                'status3X5', struct()), 1, 4);
            for index = 1:4
                channelStatus(index).status3X3 = output.channels(index).status3X3;
                channelStatus(index).status3X5 = output.channels(index).status3X5;
            end
            systemStatus = struct('dcLink12V', 400, 'dcLink34V', 400, ...
                'switchingFrequencyKHz', 10, ...
                'dcLink12AboveMinimum', true, ...
                'dcLink34AboveMinimum', true, ...
                'controlEnable', true, 'controlDisable', false);
            cycle = packStatusCycle(channelStatus, systemStatus);
            testCase.verifyEqual(size(cycle.payloads), [9 8]);
            testCase.verifyClass(cycle.payloads, 'uint8');
            testCase.verifyEqual(cycle.ids, uint32([899 901 915 917 ...
                931 933 947 949 1024]));
        end

        function profileObservabilityIsCorrectAndImmutable(testCase)
            % Torque scale resolved 2026-08-02 (see INVERTERHIL.PROTOCOL's
            % torqueProfiles.vcu256 comment, citing MFE26-VC firmware
            % ephorus_driver.hpp:55): DEFAULTCALIBRATION now defaults to the
            % verified 1/256 profile, not the retired 1/512 provisional one.
            cal = TestPlant.calibration();
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            input.channels(1).rawTorquePosCounts = int16(8192);
            input.channels(1).rawTorqueNegCounts = int16(-8192);
            input.channels(1).torqueLimitPositiveNm = 32;
            input.channels(1).torqueLimitNegativeNm = -32;
            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.protocolProfileId, ...
                'ephorus3-v1.03-candidate-1over256');
            testCase.verifyEqual(output.torqueScaleNmPerCount, 1 / 256);
            testCase.verifyTrue(output.torqueScaleVerified);
            testCase.verifyEqual(output.channels(1).torquePosNm256, 32);
            testCase.verifyEqual(output.channels(1).torqueNegNm256, -32);
            testCase.verifyEqual(output.channels(1).torquePosNm512, 16);
            testCase.verifyEqual(output.channels(1).torqueNegNm512, -16);

            badInput = input;
            badInput.protocolProfileId = ...
                'ephorus3-v1.03-provisional-1over512';
            testCase.verifyError(@() stepPlant( ...
                state, badInput, cal), 'inverterhil:InvalidPlantInput');
            badState = state;
            badState.protocolProfileId = ...
                'ephorus3-v1.03-provisional-1over512';
            testCase.verifyError(@() stepPlant( ...
                badState, input, cal), 'inverterhil:InvalidPlantState');

            % Switching explicitly to the retired, still-unverified 1/512
            % profile must still work and must still report itself
            % correctly -- it is kept only as a known-not-the-answer
            % profile (INVERTERHIL.PROTOCOL), not deleted.
            cal.protocolProfileId = 'ephorus3-v1.03-provisional-1over512';
            cal.torqueScaleNmPerCount = 1 / 512;
            cal.torqueScaleVerified = false;
            validateCalibration(cal);
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            [~, output] = stepPlant(state, input, cal);
            testCase.verifyEqual(output.torqueScaleNmPerCount, 1 / 512);
            testCase.verifyFalse(output.torqueScaleVerified);
        end

        function malformedPlantStateAndInputFailClosed(testCase)
            cal = TestPlant.calibration();
            state = initialPlantState(cal);
            input = TestPlant.driveInput(cal);
            stateCases = { ...
                'omegaRadPerS', zeros(4, 1); ...
                'torqueActualNm', [0 0 NaN 0]; ...
                'speedIntegratorNm', [0 0 complex(0, 1) 0]; ...
                'motorTemperatureC', 'cold'; ...
                'stepCount', uint32(0)};
            for index = 1:size(stateCases, 1)
                bad = state;
                bad.(stateCases{index, 1}) = stateCases{index, 2};
                testCase.verifyError(@() stepPlant(bad, input, cal), ...
                    'inverterhil:InvalidPlantState');
            end

            inputCases = { ...
                'speedSetpointRpm', complex(1, 1); ...
                'loadTorqueNm', NaN; ...
                'dcLinkV', Inf; ...
                'torqueLimitPositiveNm', '60'; ...
                'ready', [true true]; ...
                'rawTorquePosCounts', 1.5; ...
                'rawTorqueNegCounts', double(intmin('int16')) - 1};
            for index = 1:size(inputCases, 1)
                bad = input;
                bad.channels(1).(inputCases{index, 1}) = inputCases{index, 2};
                testCase.verifyError(@() stepPlant(state, bad, cal), ...
                    'inverterhil:InvalidPlantInput');
            end
            bad = input;
            bad.channels = bad.channels.';
            testCase.verifyError(@() stepPlant(state, bad, cal), ...
                'inverterhil:InvalidPlantInput');
        end

        function invalidPlantCalibrationIsRejected(testCase)
            cal = TestPlant.calibration();
            fields = {'torqueConstantNmPerA', 'inertiaKgM2', 'torqueLagS'};
            for index = 1:numel(fields)
                bad = cal;
                bad.(fields{index})(1) = 0;
                testCase.verifyError(@() validateCalibration(bad), ...
                    'inverterhil:InvalidCalibration');
            end
            bad = cal;
            bad.inertiaKgM2 = bad.inertiaKgM2.';
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.torqueConstantNmPerA = 'four';
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.inertiaKgM2(1) = NaN;
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.motorThermalTimeConstantS(1) = Inf;
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.torqueLagS(2) = complex(0.01, 1);
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.motoringEfficiency(1) = 1 + eps(1);
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.regenEfficiency(1) = 0;
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.motorDerateStartC(1) = bad.motorDerateEndC(1);
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
            bad = cal;
            bad.motorLossFraction(1) = -eps;
            testCase.verifyError(@() validateCalibration(bad), ...
                'inverterhil:InvalidCalibration');
        end
    end

    methods (Static, Access = private)
        function cal = calibration()
            cal = defaultCalibration();
        end

        function input = driveInput(cal)
            channel = struct( ...
                'mode', uint8(1), ...
                'ready', true, ...
                'zeroTorque', false, ...
                'activeFault', 'none', ...
                'commandTorqueTimeout', false, ...
                'commandErrorTimeout', false, ...
                'authorityReason', 'torque_enabled', ...
                'speedSetpointRpm', 0, ...
                'torqueLimitPositiveNm', 60, ...
                'torqueLimitNegativeNm', -60, ...
                'rawTorquePosCounts', int16(0), ...
                'rawTorqueNegCounts', int16(0), ...
                'loadTorqueNm', 0, ...
                'dcLinkV', 400);
            input = struct('protocolProfileId', cal.protocolProfileId, ...
                'channels', repmat(channel, 1, 4));
        end
    end
end
