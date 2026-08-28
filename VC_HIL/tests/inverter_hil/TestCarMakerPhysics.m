classdef TestCarMakerPhysics < matlab.unittest.TestCase
    methods (Test)
        function decoderGoldenVectorsAndCrc(testCase)
            payload = TestCarMakerPhysics.payload([1.25 -2.5 3.75], .01, 9);
            [ok, decoded] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), payload, false, false);
            testCase.verifyTrue(ok);
            testCase.verifyEqual(decoded.values, [1.25 -2.5 3.75], 'AbsTol', 1e-12);
            testCase.verifyEqual(decoded.groupCounter, uint8(9));
            payload(8) = bitxor(payload(8), uint8(1));
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), payload, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'integrity_failure');
        end

        function rejectsMetadataAndPhysicalRange(testCase)
            payload = TestCarMakerPhysics.payload([100.01 0 0], .01, 1);
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), payload, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'out_of_range');
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(7), payload, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'wrong_dlc');
        end

        function coherentReorderedGroupAndStaleness(testCase)
            bank = initialCarMakerPhysicsBank();
            order = [2 1 3]; counter = uint8(255);
            for kind = order
                frame = TestCarMakerPhysics.frame(kind, [kind kind+1 kind+2], counter);
                [bank, ok] = receiveCarMakerPhysics(bank, frame, uint32(kind));
                testCase.verifyTrue(ok);
            end
            snapshot = carMakerPhysicsSnapshot(bank, uint32(3));
            testCase.verifyTrue(snapshot.complete); testCase.verifyTrue(snapshot.fresh);
            testCase.verifyEqual(snapshot.counter, counter);
            testCase.verifyEqual(snapshot.values(1:9), [1 2 3 2 3 4 3 4 5]);
            testCase.verifyFalse(carMakerPhysicsSnapshot(bank, uint32(34)).fresh);

            for kind = 1:3
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [0 0 0], uint8(0)), uint32(40));
            end
            testCase.verifyEqual(carMakerPhysicsSnapshot(bank, uint32(40)).counter, uint8(0));
        end

        function partialMismatchNeverRefreshes(testCase)
            bank = initialCarMakerPhysicsBank();
            for kind = 1:3
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [0 0 0], uint8(7)), uint32(0));
            end
            bank = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [9 9 9], uint8(8)), uint32(20));
            snapshot = carMakerPhysicsSnapshot(bank, uint32(31));
            testCase.verifyFalse(snapshot.fresh);
            testCase.verifyEqual(snapshot.counter, uint8(7));
            [bank, ok, reason] = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(2, [0 0 0], uint8(9)), uint32(32));
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'counter_mismatch');
            testCase.verifyEqual(carMakerPhysicsSnapshot(bank, uint32(32)).counter, uint8(7));
        end

        function selectorFallbackAndForcedTruth(testCase)
            kinematic = 1:9;
            snapshot = struct('values', 11:22, 'fresh', true, 'complete', true);
            [obs, source] = selectVehicleObservation(kinematic, snapshot);
            testCase.verifyEqual(obs, kinematic); testCase.verifyEqual(source, uint8(0));
            [obs, source] = selectVehicleObservation(kinematic, snapshot, true);
            testCase.verifyEqual(obs, 11:19); testCase.verifyEqual(source, uint8(1));
            snapshot.fresh = false;
            testCase.verifyEqual(selectVehicleObservation(kinematic, snapshot, true), kinematic);
        end

        function carMakerAxesReachBackwardMountedMti(testCase)
            snapshot = struct('values', [1 2 3 4 5 6 7 8 9 0 0 0], ...
                'fresh', true, 'complete', true);
            obs = selectVehicleObservation(zeros(1, 9), snapshot, true);
            state = struct('accelerationMps2', obs(1:3), ...
                'rateOfTurnRadPerS', obs(4:6), 'velocityMps', obs(7:9));
            mounted = mountingTransform(state);
            testCase.verifyEqual(mounted.accelerationMps2, [-1 -2 3]);
            frame = packMti680Frame('acceleration', mounted.accelerationMps2, imuProtocol());
            testCase.verifyEqual(frame.payload, uint8([255 0 254 0 3 0]));
        end
    end

    methods (Static, Access = private)
        function frame = frame(kind, values, counter)
            scales = [.01 .002 .01 .0001];
            frame = struct('id', uint32(hex2dec('502') + kind), 'dlc', uint8(8), ...
                'payload', TestCarMakerPhysics.payload(values, scales(kind), counter), ...
                'isExtended', false, 'isRemote', false, 'drop', false);
        end

        function payload = payload(values, scale, counter)
            raw = int16(round(values ./ scale));
            payload = zeros(1, 8, 'uint8');
            for k = 1:3
                word = typecast(raw(k), 'uint16');
                payload(2*k-1) = uint8(bitand(word, 255));
                payload(2*k) = uint8(bitshift(word, -8));
            end
            payload(7) = uint8(counter);
            payload(8) = TestCarMakerPhysics.crc(payload(1:7));
        end

        function value = crc(bytes)
            value = uint8(255);
            for k = 1:numel(bytes)
                value = bitxor(value, bytes(k));
                for bit = 1:8
                    if bitand(value, uint8(128))
                        value = bitxor(bitshift(value, 1), uint8(29));
                    else
                        value = bitshift(value, 1);
                    end
                end
            end
            value = bitxor(value, uint8(255));
        end
    end
end
