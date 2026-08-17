classdef TestCarMakerTelemetry < matlab.unittest.TestCase
    methods (Test)
        function packsAllFieldsAtExistingStatusTorqueScale(testCase)
            telemetry = struct('torqueSetpointNm', ...
                [-10.5 20.25 -1 / 32 0], ...
                'ready', [true false true false]);

            [torque, ready] = inverterhil.packCarMakerTelemetry(telemetry);
            testCase.verifyEqual(torque, uint8([hex2dec('B0') hex2dec('FE') ...
                hex2dec('88') hex2dec('02') hex2dec('FF') hex2dec('FF') 0 0]));
            testCase.verifyEqual(ready, uint8([5 0 0 0 0 0 0 0]));
        end

        function saturatesTorqueBeforeNarrowing(testCase)
            telemetry = struct('torqueSetpointNm', ...
                [realmax -realmax realmax -realmax], ...
                'ready', [false false false false]);

            [torque, ready] = inverterhil.packCarMakerTelemetry(telemetry);
            testCase.verifyEqual(torque, uint8([255 127 0 128 255 127 0 128]));
            testCase.verifyEqual(ready, zeros(1, 8, 'uint8'));
        end

        function roundTripsTorqueAndReady(testCase)
            telemetry = struct('torqueSetpointNm', ...
                [-1024 1023.96875 12.5 -12.5], ...
                'ready', [true true false true]);

            [torque, ready] = inverterhil.packCarMakerTelemetry(telemetry);
            decoded = inverterhil.decodeCarMakerTelemetry(torque, ready);
            testCase.verifyEqual(decoded.torqueSetpointNm, ...
                telemetry.torqueSetpointNm);
            testCase.verifyEqual(decoded.ready, logical(telemetry.ready));
        end

        function rejectsMalformedAndReservedPayloads(testCase)
            testCase.verifyError(@() inverterhil.decodeCarMakerTelemetry( ...
                zeros(1, 8, 'uint8'), zeros(8, 1, 'uint8')), ...
                'inverterhil:MalformedPayload');
            reserved = zeros(1, 8, 'uint8');
            reserved(8) = uint8(1);
            testCase.verifyError(@() inverterhil.decodeCarMakerTelemetry( ...
                zeros(1, 8, 'uint8'), reserved), 'inverterhil:ReservedBits');
        end
    end
end
