classdef TestSensorProtocol < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addIndependentSensorPaths(testCase) %#ok<INUSD>
            root = fileparts(fileparts(fileparts(mfilename('fullpath'))));
            addpath(fullfile(root, 'imu'));
            addpath(fullfile(root, 'steering-sensor'));
        end
    end

    methods (Test)
        function LwsGoldenFrame(testCase)
            frame = packLwsFrame(-12.3, 20, ...
                struct('trim', true, 'cal', true, 'ok', true));
            testCase.verifyEqual(frame.id, uint32(hex2dec('2B0')));
            testCase.verifyEqual(frame.dlc, uint8(5));
            testCase.verifyEqual(frame.payload, uint8([hex2dec('85') ...
                hex2dec('FF') 5 0 7]));
            measurement = decodeLwsFrame(frame);
            testCase.verifyEqual(measurement.angleDeg, -12.3, 'AbsTol', 0.05);
            testCase.verifyEqual(measurement.speedDegPerS, 20, 'AbsTol', 2);
            testCase.verifyTrue(measurement.valid);
        end

        function LwsInvalidStatusIsVisible(testCase)
            frame = packLwsFrame(0, 0, ...
                struct('trim', true, 'cal', false, 'ok', false));
            measurement = decodeLwsFrame(frame);
            testCase.verifyFalse(measurement.valid);
            testCase.verifyTrue(measurement.trim);
            testCase.verifyFalse(measurement.cal);
            testCase.verifyFalse(measurement.ok);
        end

        function LwsRangeIsRejected(testCase)
            testCase.verifyError(@() packLwsFrame(781, 0), ...
                'lws:AngleRange');
            testCase.verifyError(@() packLwsFrame(0, 1100), ...
                'lws:SpeedValue');
            testCase.verifyError(@() packLwsFrame(0, -1), ...
                'lws:SpeedValue');
        end

        function MtiAccelerationGoldenFrame(testCase)
            frame = packMti680Frame('acceleration', [1 -2 9.8]);
            testCase.verifyEqual(frame.id, uint32(hex2dec('034')));
            testCase.verifyEqual(frame.dlc, uint8(6));
            testCase.verifyEqual(frame.payload, uint8([1 0 254 0 9 hex2dec('CD')]));
            values = decodeMti680Frame(frame);
            testCase.verifyEqual(values, [1 -2 9.80078125], 'AbsTol', 1e-12);
        end

        function MtiRateOfTurnGoldenFrame(testCase)
            frame = packMti680Frame('rateOfTurn', [1 -1 0.5]);
            testCase.verifyEqual(frame.id, uint32(hex2dec('032')));
            testCase.verifyEqual(frame.payload, uint8([2 0 254 0 1 0]));
            values = decodeMti680Frame(frame);
            testCase.verifyEqual(values, [1 -1 0.5], 'AbsTol', 1e-12);
        end

        function MtiWrongPayloadDoesNotSilentlyPass(testCase)
            frame = packMti680Frame('acceleration', [1 -2 9.8]);
            frame.payload(2) = uint8(1);
            values = decodeMti680Frame(frame);
            testCase.verifyNotEqual(values(1), 1);
        end

        function MtiUnknownIdIsRejected(testCase)
            frame = struct('id', uint32(1), 'payload', zeros(1, 6, 'uint8'));
            testCase.verifyError(@() decodeMti680Frame(frame), ...
                'mti680:UnknownId');
        end

        function IndependentPayloadEncodersRejectOutOfRangeValues(testCase)
            testCase.verifyError(@() packLwsPayload(0, -1, 7), ...
                'lws:SpeedRange');
            testCase.verifyError(@() packMti680Payload('acceleration', ...
                [1e9 0 0]), 'mti680:PayloadRange');
        end
    end
end
