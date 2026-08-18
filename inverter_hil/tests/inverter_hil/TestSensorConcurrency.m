classdef TestSensorConcurrency < matlab.unittest.TestCase
    methods (Test)
        function SharedStateProducesIndependentFrames(testCase)
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'imu'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'steering-sensor'));
            vehicle = struct('accelerationMps2', [0.5 -0.25 9.8], ...
                'rateOfTurnRadPerS', [0.1 0.2 0.3]);
            [~, imu] = stepImuSimulation([], 0.010, vehicle, []);
            steeringInput = struct('angleDeg', 30, 'dropout', false, ...
                'status', struct('trim', true, 'cal', true, 'ok', true));
            [~, lws] = stepSteeringSensor([], 0.010, steeringInput);
            frames = inverterhil.sensorBusMux(imu, lws);
            testCase.verifyEqual(numel(frames), 2);
            testCase.verifyEqual([frames.timestampS], [0.010 0.010]);
            testCase.verifyEqual({frames.kind}, {'imu', 'steering'});
        end

        function OneDropoutDoesNotSuppressOtherSensor(testCase)
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'imu'));
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'steering-sensor'));
            vehicle = struct('accelerationMps2', [0 0 9.8], ...
                'rateOfTurnRadPerS', [0 0 0]);
            [~, imu] = stepImuSimulation([], 0.020, vehicle, ...
                struct('enabled', true, 'dropout', true));
            [~, lws] = stepSteeringSensor([], 0.020, ...
                struct('angleDeg', -20, 'dropout', false, ...
                'status', struct('trim', true, 'cal', true, 'ok', true)));
            frames = inverterhil.sensorBusMux(imu, lws);
            testCase.verifyEqual(numel(frames), 1);
            testCase.verifyEqual(frames.kind, 'steering');
        end

        function BothSensorsShareTimestampOnFirstTick(testCase)
            previous = [];
            input = struct('imuPeriodS', 0.005, 'lwsPeriodS', 0.010);
            [state, due] = inverterhil.sensorScheduler(previous, 0, input);
            testCase.verifyTrue(due.imu);
            testCase.verifyTrue(due.lws);
            testCase.verifyEqual(due.timestampS, 0);
            testCase.verifyEqual(due.imuSequence, uint32(1));
            testCase.verifyEqual(due.lwsSequence, uint32(1));
            testCase.verifyEqual(state.lastImuS, state.lastLwsS);
        end

        function IndependentRatesDoNotBlockEachOther(testCase)
            input = struct('imuPeriodS', 0.005, 'lwsPeriodS', 0.010);
            [state, due] = inverterhil.sensorScheduler([], 0, input);
            testCase.verifyTrue(due.imu && due.lws);
            [state, due] = inverterhil.sensorScheduler(state, 0.005, input);
            testCase.verifyTrue(due.imu);
            testCase.verifyFalse(due.lws);
            [state, due] = inverterhil.sensorScheduler(state, 0.010, input);
            testCase.verifyTrue(due.imu && due.lws);
            testCase.verifyEqual(state.imuSequence, uint32(3));
            testCase.verifyEqual(state.lwsSequence, uint32(2));
        end

        function SensorPeriodsRejectInvalidConfiguration(testCase)
            testCase.verifyError(@() inverterhil.sensorScheduler([], 0, ...
                struct('imuPeriodS', 0, 'lwsPeriodS', 0.01)), ...
                'inverterhil:InvalidSensorPeriod');
            testCase.verifyError(@() inverterhil.sensorScheduler([], -1, ...
                struct('imuPeriodS', 0.005, 'lwsPeriodS', 0.01)), ...
                'inverterhil:InvalidSensorTime');
        end
    end
end
