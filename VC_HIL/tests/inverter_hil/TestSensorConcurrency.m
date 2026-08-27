classdef TestSensorConcurrency < matlab.unittest.TestCase
    methods (Test)
        function SharedStateProducesIndependentFrames(testCase)
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'imu'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'steering-sensor'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'inverter', 'sensorNormalizer'));
            vehicle = struct('accelerationMps2', [0.5 -0.25 9.8], ...
                'rateOfTurnRadPerS', [0.1 0.2 0.3]);
            [~, imu] = stepImuSimulation([], 0.010, vehicle, []);
            steeringInput = struct('angleDeg', 30, 'dropout', false, ...
                'status', struct('trim', true, 'cal', true, 'ok', true));
            [~, lws] = stepSteeringSensor([], 0.010, steeringInput);
            frames = sensorFrameOrder( ...
                [imuNormalizeFrame(imu), lwsNormalizeFrame(lws)]);
            testCase.verifyEqual(numel(frames), 2);
            testCase.verifyEqual([frames.timestampS], [0.010 0.010]);
            testCase.verifyEqual({frames.kind}, {'imu', 'steering'});
        end

        function OneDropoutDoesNotSuppressOtherSensor(testCase)
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'imu'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'steering-sensor'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'inverter', 'sensorNormalizer'));
            vehicle = struct('accelerationMps2', [0 0 9.8], ...
                'rateOfTurnRadPerS', [0 0 0]);
            [~, imu] = stepImuSimulation([], 0.020, vehicle, ...
                struct('enabled', true, 'dropout', true));
            [~, lws] = stepSteeringSensor([], 0.020, ...
                struct('angleDeg', -20, 'dropout', false, ...
                'status', struct('trim', true, 'cal', true, 'ok', true)));
            frames = sensorFrameOrder( ...
                [imuNormalizeFrame(imu), lwsNormalizeFrame(lws)]);
            testCase.verifyEqual(numel(frames), 1);
            testCase.verifyEqual(frames.kind, 'steering');
        end

        function BothSensorsShareTimestampOnFirstTick(testCase)
            [imuState, imuDue] = imuScheduler([], 0, 0.005);
            [lwsState, lwsDue] = lwsScheduler([], 0, 0.010);
            testCase.verifyTrue(imuDue.imu);
            testCase.verifyTrue(lwsDue.lws);
            testCase.verifyEqual(imuDue.timestampS, 0);
            testCase.verifyEqual(imuDue.imuSequence, uint32(1));
            testCase.verifyEqual(lwsDue.lwsSequence, uint32(1));
            testCase.verifyEqual(imuState.lastImuS, lwsState.lastLwsS);
        end

        function IndependentRatesDoNotBlockEachOther(testCase)
            [imuState, imuDue] = imuScheduler([], 0, 0.005);
            [lwsState, lwsDue] = lwsScheduler([], 0, 0.010);
            testCase.verifyTrue(imuDue.imu && lwsDue.lws);
            [imuState, imuDue] = imuScheduler(imuState, 0.005, 0.005);
            testCase.verifyTrue(imuDue.imu);
            [lwsState, lwsDue] = lwsScheduler(lwsState, 0.005, 0.010);
            testCase.verifyFalse(lwsDue.lws);
            [imuState, imuDue] = imuScheduler(imuState, 0.010, 0.005);
            [lwsState, lwsDue] = lwsScheduler(lwsState, 0.010, 0.010);
            testCase.verifyTrue(imuDue.imu && lwsDue.lws);
            testCase.verifyEqual(imuState.imuSequence, uint32(3));
            testCase.verifyEqual(lwsState.lwsSequence, uint32(2));
        end

        function SensorPeriodsRejectInvalidConfiguration(testCase)
            testCase.verifyError(@() imuScheduler([], 0, 0), ...
                'inverterhil:InvalidSensorPeriod');
            testCase.verifyError(@() lwsScheduler([], 0, 0), ...
                'inverterhil:InvalidSensorPeriod');
            testCase.verifyError(@() imuScheduler([], -1, 0.005), ...
                'inverterhil:InvalidSensorTime');
            testCase.verifyError(@() lwsScheduler([], -1, 0.01), ...
                'inverterhil:InvalidSensorTime');
        end
    end
end
