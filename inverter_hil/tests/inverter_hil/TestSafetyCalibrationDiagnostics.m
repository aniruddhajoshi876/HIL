classdef TestSafetyCalibrationDiagnostics < matlab.unittest.TestCase
    methods (Test)
        function uncalibratedChannelsNoLongerBlockTheWholeOutputSet(testCase)
            % Was DEFAULTCALIBRATIONISEXPLICITLYUNARMED. The
            % pedal_calibration_unverified gate was removed on 2026-08-02 by
            % explicit operator decision, so NaN endpoints no longer halt
            % every pedal AND digital output.
            %
            % IMPORTANT, and NOT what removing the gate was expected to do:
            % the output now ARMS with an uncalibrated channel. The remaining
            % nonfinite_output_blocked check does NOT catch it, because
            % MATLAB's MIN/MAX ignore NaN -- min(max(NaN,0),5) returns 0, so
            % the clamp erases the NaN before the nonfinite test ever sees
            % it. An uncalibrated channel therefore drives a real 0 V and
            % reports 'armed', rather than being refused.
            %
            % 0 V is still the intended out-of-range stimulus (plan 3.1: the
            % VCU's lower-bound raw-count checks should reject it), so this
            % is not silently plausible at the VCU. But the GUI now says
            % 'armed' for a channel nobody calibrated, which is the honest
            % description of the current behaviour and is pinned here so the
            % next reader is not surprised by it.
            cal = inverterhil.defaultCalibration();
            command = TestSafetyCalibrationDiagnostics.validCommand();
            output = inverterhil.safeIoOutputs(command, cal);

            testCase.verifyTrue(output.armed);
            testCase.verifyEqual(output.analogV, zeros(1, 4), ...
                'Uncalibrated channels must still land at 0 V, not NaN.');
            testCase.verifyEqual(output.reason, 'armed');

            % NOTE for whoever restores the gate: the nonfinite_output_blocked
            % check below the clamp is now effectively UNREACHABLE from
            % calibration values. MIN/MAX ignore NaN in both directions, so a
            % NaN endpoint AND a NaN clamp bound are both scrubbed to a finite
            % number before that check runs. It is not a second line of
            % defence for an uncalibrated channel; only the removed gate was.
            broken = cal;
            broken.pedals.maximumV = [NaN 5 5 5];
            stillArmed = inverterhil.safeIoOutputs(command, broken);
            testCase.verifyTrue(stillArmed.armed, ...
                'Documents that a NaN clamp bound is scrubbed, not caught.');
        end

        function calibratedArmedOutputsAreMappedAndClamped(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            command = TestSafetyCalibrationDiagnostics.validCommand();
            command.throttle = 0.25;
            command.brake = 0.5;
            command.digital = logical([1 0 1 0 1 0 1 0]);
            output = inverterhil.safeIoOutputs(command, cal);

            testCase.verifyTrue(output.armed);
            testCase.verifyEqual(output.reason, 'armed');
            testCase.verifyEqual(output.analogV, [1.5 1.475 2.2 2.1], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(output.digital, command.digital);

            command.throttle = -100;
            command.brake = 100;
            output = inverterhil.safeIoOutputs(command, cal);
            testCase.verifyEqual(output.analogV, ...
                [cal.pedals.releasedV(1:2) cal.pedals.pressedV(3:4)]);
        end

        function everyInterlockAndHeartbeatFailureReturnsSafeZero(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            base = TestSafetyCalibrationDiagnostics.validCommand();
            fields = {'applicationRunning', 'ioHealthy', 'armed'};
            for index = 1:numel(fields)
                command = base;
                command.(fields{index}) = false;
                output = inverterhil.safeIoOutputs(command, cal);
                TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
                testCase.verifyEqual(output.reason, 'not_armed');
            end

            command = base;
            command.heartbeatAgeS = cal.guiHeartbeatTimeoutS;
            output = inverterhil.safeIoOutputs(command, cal);
            testCase.verifyTrue(output.armed);

            badAges = [cal.guiHeartbeatTimeoutS + eps(cal.guiHeartbeatTimeoutS), ...
                -eps, NaN, Inf];
            for age = badAges
                command = base;
                command.heartbeatAgeS = age;
                output = inverterhil.safeIoOutputs(command, cal);
                TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
                testCase.verifyEqual(output.reason, 'heartbeat_expired');
            end
        end

        function malformedCommandsFailClosed(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            base = TestSafetyCalibrationDiagnostics.validCommand();

            command = rmfield(base, 'armed');
            output = inverterhil.safeIoOutputs(command, cal);
            TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
            testCase.verifyEqual(output.reason, 'missing_armed');

            command = base;
            command.throttle = NaN;
            output = inverterhil.safeIoOutputs(command, cal);
            TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
            testCase.verifyEqual(output.reason, 'malformed_pedal_command');

            command = base;
            command.digital = [1 0 1 NaN 0 0 0 0];
            output = inverterhil.safeIoOutputs(command, cal);
            TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
            testCase.verifyEqual(output.reason, 'malformed_digital_command');
        end

        function nonscalarInterlockCannotArmOutputs(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            fields = {'applicationRunning', 'ioHealthy', 'armed'};
            malformed = {[true true], true(2, 1), char(1), ...
                complex(1, 1), NaN, 2, {true}};
            for fieldIndex = 1:numel(fields)
                for valueIndex = 1:numel(malformed)
                    command = TestSafetyCalibrationDiagnostics.validCommand();
                    command.(fields{fieldIndex}) = malformed{valueIndex};
                    output = inverterhil.safeIoOutputs(command, cal);
                    TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
                    testCase.verifyEqual(output.reason, ...
                        'malformed_interlock');
                end
            end
        end

        function complexHostCommandsFailClosed(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            command = TestSafetyCalibrationDiagnostics.validCommand();
            command.heartbeatAgeS = complex(0, 1);
            output = inverterhil.safeIoOutputs(command, cal);
            TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
            testCase.verifyEqual(output.reason, 'heartbeat_expired');

            fields = {'throttle', 'brake'};
            for index = 1:numel(fields)
                command = TestSafetyCalibrationDiagnostics.validCommand();
                command.(fields{index}) = complex(0.5, 0.25);
                output = inverterhil.safeIoOutputs(command, cal);
                TestSafetyCalibrationDiagnostics.verifySafe(testCase, output);
                testCase.verifyEqual(output.reason, ...
                    'malformed_pedal_command');
            end
        end

        function calibrationRejectsCoreInvalidValues(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            invalid = cal;
            invalid.sampleTimeS = 0;
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.configErrorScope = uint8(2);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.torqueScaleNmPerCount = 1 / 256;
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.inertiaKgM2(4) = Inf;
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.modelTorqueMinNm(2) = invalid.modelTorqueMaxNm(2);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.pedals.maximumV(1) = 5 + eps(5);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');
        end

        function calibrationRejectsDestabilizingNegativeCoefficients(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            fields = {'speedKp', 'speedKi', 'dragNmPerRadS'};
            for index = 1:numel(fields)
                invalid = cal;
                invalid.(fields{index})(2) = -0.01;
                testCase.verifyError( ...
                    @() inverterhil.validateCalibration(invalid), ...
                    'inverterhil:InvalidCalibration', fields{index});
            end
        end

        function calibrationRejectsFinitePedalValuesOutsideClamps(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();
            invalid = cal;
            invalid.pedals.releasedV(1) = 5.5;
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.pedals.pressedV(3) = -0.5;
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');
        end

        function calibrationRejectsShapeAndComplexTypeBypasses(testCase)
            cal = TestSafetyCalibrationDiagnostics.calibrated();

            invalid = cal;
            invalid.torqueScaleNmPerCount = ...
                [cal.torqueScaleNmPerCount cal.torqueScaleNmPerCount];
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.torqueScaleVerified = [false false];
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.sampleTimeS = complex(cal.sampleTimeS, 1);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.speedKp(2) = complex(invalid.speedKp(2), 1);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');

            invalid = cal;
            invalid.pedals.minimumV(2) = complex(0, 1);
            testCase.verifyError(@() inverterhil.validateCalibration(invalid), ...
                'inverterhil:InvalidCalibration');
        end

        function diagnosticsExposeEveryFailedWriteAndControllerFault(testCase)
            healthy = inverterhil.evaluateCanDiagnostics( ...
                true(1, 9), false, false, false, false);
            testCase.verifyTrue(healthy.cycleSucceeded);
            testCase.verifyEqual(healthy.failedWriteMask, uint16(0));

            for index = 1:9
                writes = true(1, 9);
                writes(index) = false;
                result = inverterhil.evaluateCanDiagnostics( ...
                    writes, false, false, false, false);
                testCase.verifyFalse(result.cycleSucceeded);
                testCase.verifyEqual(result.failedWriteMask, ...
                    bitshift(uint16(1), index - 1));
            end

            flags = eye(4, 'logical');
            for index = 1:4
                result = inverterhil.evaluateCanDiagnostics( ...
                    true(1, 9), flags(index, 1), flags(index, 2), ...
                    flags(index, 3), flags(index, 4));
                testCase.verifyFalse(result.cycleSucceeded);
            end
        end

        function diagnosticsRejectMalformedInputs(testCase)
            testCase.verifyError(@() inverterhil.evaluateCanDiagnostics( ...
                ones(1, 9), false, false, false, false), ...
                'inverterhil:MalformedDiagnostics');
            testCase.verifyError(@() inverterhil.evaluateCanDiagnostics( ...
                true(1, 8), false, false, false, false), ...
                'inverterhil:MalformedDiagnostics');
            testCase.verifyError(@() inverterhil.evaluateCanDiagnostics( ...
                true(1, 9), NaN, false, false, false), ...
                'inverterhil:MalformedDiagnostics');
        end
    end

    methods (Static, Access = private)
        function cal = calibrated()
            cal = inverterhil.defaultCalibration();
            cal.pedals.releasedV = [0.5 0.7 0.4 0.6];
            cal.pedals.pressedV = [4.5 3.8 4.0 3.6];
            inverterhil.validateCalibration(cal);
        end

        function command = validCommand()
            command = struct( ...
                'applicationRunning', true, ...
                'ioHealthy', true, ...
                'armed', true, ...
                'heartbeatAgeS', 0, ...
                'throttle', 0, ...
                'brake', 0, ...
                'digital', false(1, 8));
        end

        function verifySafe(testCase, output)
            testCase.verifyFalse(output.armed);
            testCase.verifyEqual(output.analogV, zeros(1, 4));
            testCase.verifyEqual(output.digital, false(1, 8));
        end
    end
end
