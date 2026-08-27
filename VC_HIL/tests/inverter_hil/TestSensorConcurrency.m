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

        function ImuSimulationEmitsRateOfTurnAndScalarGroup(testCase)
            %IMUSIMULATIONEMITSRATEOFTURNANDSCALARGROUP rateOfTurn (0x032) is
            %   in imuProtocol.decodedByVcu, so it must be transmitted like
            %   acceleration. The scalar group (groupCounter, sampleTime,
            %   statusWord, errorCode) accompanies every inertial group. All
            %   quantities are in the sensor frame -- the 180-deg-Z mounting
            %   transform has negated vehicle X/Y.
            addpath(fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
                'imu'));
            vehicle = struct('accelerationMps2', [1 2 9.81], ...
                'rateOfTurnRadPerS', [0.1 0.2 0.3], ...
                'velocityMps', [10 -4 0]);
            [~, accelFrame, velocityFrame, eulerFrame, rateFrame, scalarFrames] = ...
                stepImuSimulation([], 0.010, vehicle, []);

            testCase.verifyTrue(rateFrame.valid);
            testCase.verifyEqual(rateFrame.id, uint32(hex2dec('032')));
            % Sensor-frame rate of turn: vehicle X and Y negated.
            testCase.verifyEqual(decodeMti680Frame(rateFrame), ...
                [-0.099609375 -0.19921875 0.30078125], 'AbsTol', 1e-6);
            % Sensor-frame acceleration: vehicle X and Y negated, Z kept.
            testCase.verifyEqual(decodeMti680Frame(accelFrame), ...
                [-1 -2 9.80859375], 'AbsTol', 1e-6);
            testCase.verifyEqual(decodeMti680Frame(velocityFrame), ...
                [-10 4 0], 'AbsTol', 1e-6);
            testCase.verifyFalse(eulerFrame.valid);

            testCase.verifyEqual(numel(scalarFrames), 4);
            testCase.verifyEqual([scalarFrames.id], ...
                uint32([hex2dec('006') hex2dec('005') hex2dec('011') hex2dec('001')]));
            testCase.verifyTrue(all([scalarFrames.valid]));
            % groupCounter starts at 0, sampleTime is 10000 us at t = 0.010.
            testCase.verifyEqual(scalarFrames(1).payload, uint8([0 0]));
            testCase.verifyEqual(scalarFrames(2).payload, uint8([0 0 39 16]));
            testCase.verifyEqual(scalarFrames(3).payload, uint8([0 0 0 3]));
            testCase.verifyEqual(scalarFrames(4).payload, uint8(0));

            % groupCounter increments once per group.
            state = struct('sequence', uint32(0));
            [state, ~, ~, ~, ~, s1] = stepImuSimulation(state, 0.010, vehicle, []);
            [~, ~, ~, ~, ~, s2] = stepImuSimulation(state, 0.020, vehicle, []);
            testCase.verifyEqual(s1(1).payload, uint8([0 0]));
            testCase.verifyEqual(s2(1).payload, uint8([0 1]));
        end

        function PlantYawRateSurvivesToTheWireWithCorrectSign(testCase)
            %PLANTYAWRATESURVIVESTOTHEWIREWITHCORRECTSIGN End-to-end plant
            %   check: stepVehicleState publishes yaw rate on the vehicle Z
            %   axis (index 6), stepImuSimulation's 180-deg-Z mounting
            %   transform leaves Z sign-invariant, so the decoded 0x032 frame
            %   must carry the SAME sign and magnitude as the plant yaw rate,
            %   on the Z axis, with X and Y at zero. A regression against the
            %   old "yaw on index 5 (Y)" layout, which the mounting transform
            %   silently inverted.
            root = fileparts(fileparts(fileparts(mfilename('fullpath'))));
            addpath(fullfile(root, 'imu'));
            addpath(fullfile(root, 'inverter', 'state-machine'));
            addpath(fullfile(root, 'inverter', 'contructors'));

            plantOutput = struct('torqueActualNm', [0 0 0 0]);
            initialState = [12, 0, 0, 0];   % 12 m/s, straight
            dt = 0.005;

            for steeringAngleDeg = [25, -25]
                [~, obs] = stepVehicleState(initialState, plantOutput, ...
                    steeringAngleDeg, dt);
                plantYawRate = obs(6);
                % Plant publishes yaw rate on Z, nothing on the X/Y rate axes.
                testCase.verifyEqual(obs(4:5), [0 0]);
                testCase.verifyNotEqual(plantYawRate, 0);
                testCase.verifyEqual(sign(plantYawRate), sign(steeringAngleDeg));

                vehicle = struct('accelerationMps2', obs(1:3), ...
                    'rateOfTurnRadPerS', obs(4:6), 'velocityMps', obs(7:9));
                [~, ~, ~, ~, rateFrame] = stepImuSimulation([], dt, vehicle, []);
                decoded = decodeMti680Frame(rateFrame);

                testCase.verifyEqual(rateFrame.id, uint32(hex2dec('032')));
                % Same sign as the plant -- NOT negated.
                testCase.verifyEqual(sign(decoded(3)), sign(plantYawRate));
                % Same magnitude to within one rate-of-turn LSB (2^-9 rad/s).
                testCase.verifyEqual(decoded(3), plantYawRate, ...
                    'AbsTol', 2^-9);
                % Roll-rate / pitch-rate axes stay zero.
                testCase.verifyEqual(decoded(1:2), [0 0]);
            end
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
