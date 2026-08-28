classdef TestCarMakerPhysics < matlab.unittest.TestCase
    %TESTCARMAKERPHYSICS CarMaker 0x503-0x506 -> Speedgoat coherent retainer
    %   -> observation selector -> MTi mounting transform -> MTi frames.
    %   Covers scale, byte order, CRC, counter coherence, partial and
    %   reordered groups, wrap, staleness, range rejection, and the rule that
    %   nothing publishes from an incomplete group.

    methods (Test)
        % ---------------------------------------------------------- decode

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

        function everyFrameScaleAndByteOrderMatchesTheDbc(testCase)
            % Scales from BO_ 1283/1284/1285/1286: 0.01 m/s^2, 0.002 rad/s,
            % 0.01 m/s, 0.0001 rad. Signed Intel int16 at byte offsets 0/2/4.
            scales = [0.01 0.002 0.01 0.0001];
            for kind = 1:4
                id = uint32(hex2dec('502') + kind);
                % One count on each axis proves the scale and the field order.
                payload = TestCarMakerPhysics.payloadCounts([1 -1 2], 3);
                [ok, decoded] = decodeCarMakerPhysicsFrame(id, uint8(8), ...
                    payload, false, false);
                testCase.verifyTrue(ok, sprintf('0x%03X rejected', id));
                testCase.verifyEqual(decoded.values, ...
                    [1 -1 2] * scales(kind), 'AbsTol', 1e-12, ...
                    sprintf('0x%03X scale', id));
                testCase.verifyEqual(decoded.kind, uint8(kind));
            end
            % Little-endian, signed: -1234 counts is 0xFB2E -> bytes 2E FB.
            payload = TestCarMakerPhysics.payloadCounts([-1234 0 0], 0);
            testCase.verifyEqual(payload(1), uint8(hex2dec('2E')));
            testCase.verifyEqual(payload(2), uint8(hex2dec('FB')));
            [~, decoded] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), payload, false, false);
            testCase.verifyEqual(decoded.values(1), -12.34, 'AbsTol', 1e-12);
        end

        function rejectsMetadataAndPhysicalRange(testCase)
            payload = TestCarMakerPhysics.payload([100.01 0 0], .01, 1);
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), payload, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'out_of_range');
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(7), payload, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'wrong_dlc');
            good = TestCarMakerPhysics.payload([1 1 1], .01, 1);
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('507')), ...
                uint8(8), good, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'wrong_id');
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), good, true, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'extended_frame');
            [ok, ~, reason] = decodeCarMakerPhysicsFrame(uint32(hex2dec('503')), ...
                uint8(8), good, false, true);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'remote_frame');
        end

        % --------------------------------------------------------- retainer

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

            % Counter wrap 255 -> 0 is ordinary forward progress.
            for kind = 1:3
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [0 0 0], uint8(0)), uint32(40));
            end
            testCase.verifyEqual(carMakerPhysicsSnapshot(bank, uint32(40)).counter, uint8(0));
        end

        function partialGroupNeverPublishes(testCase)
            % Two of the three required members: nothing may become visible.
            bank = initialCarMakerPhysicsBank();
            for kind = 1:2
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [1 1 1], uint8(4)), uint32(0));
            end
            snapshot = carMakerPhysicsSnapshot(bank, uint32(0));
            testCase.verifyFalse(snapshot.complete);
            testCase.verifyFalse(snapshot.fresh);
            % 0x506 Euler is optional and cannot substitute for a member.
            bank = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(4, [0.1 0.1 0.1], uint8(4)), uint32(1));
            testCase.verifyFalse(carMakerPhysicsSnapshot(bank, uint32(1)).complete);
            % The missing member arrives: now it publishes.
            bank = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(3, [1 1 1], uint8(4)), uint32(2));
            testCase.verifyTrue(carMakerPhysicsSnapshot(bank, uint32(2)).complete);
        end

        function duplicateAndReorderedGroupsAreRejected(testCase)
            bank = TestCarMakerPhysics.publishedBank(uint8(7), uint32(0));
            % A repeat of the published counter is a duplicate.
            [bank, ok, reason] = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [9 9 9], uint8(7)), uint32(10));
            testCase.verifyFalse(ok);
            testCase.verifyEqual(reason, 'duplicate_counter');
            % A counter in the backward half-window is a reorder or replay.
            [bank, ok, reason] = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [9 9 9], uint8(6)), uint32(11));
            testCase.verifyFalse(ok);
            testCase.verifyEqual(reason, 'out_of_order_counter');
            testCase.verifyEqual( ...
                carMakerPhysicsSnapshot(bank, uint32(11)).counter, uint8(7));
        end

        function anIncompleteGroupIsAbandonedRatherThanWedgingThePath(testCase)
            % A group starts, loses members, and a NEWER group begins. The
            % partial group must be discarded unpublished -- and assembly must
            % continue, not latch. The exact-+1 rule this replaced rejected
            % every subsequent frame forever after a single loss, which would
            % have made the Phase-17 "restore CarMaker and confirm controlled
            % recovery" step impossible to pass.
            bank = TestCarMakerPhysics.publishedBank(uint8(7), uint32(0));
            bank = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [9 9 9], uint8(8)), uint32(10));
            testCase.verifyTrue(bank.hasPending);
            % Group 8's remaining members never arrive; group 9 starts.
            [bank, ok] = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [3 3 3], uint8(9)), uint32(20));
            testCase.verifyTrue(ok, 'A newer group must not be rejected.');
            testCase.verifyEqual(bank.abandonedGroupCount, uint32(1));
            testCase.verifyEqual(bank.pendingCounter, uint8(9));
            % The abandoned partial group was never published.
            testCase.verifyEqual( ...
                carMakerPhysicsSnapshot(bank, uint32(20)).counter, uint8(7));
            % Group 9 completes and publishes normally: the path recovered.
            for kind = 2:3
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [3 3 3], uint8(9)), uint32(21));
            end
            snapshot = carMakerPhysicsSnapshot(bank, uint32(21));
            testCase.verifyEqual(snapshot.counter, uint8(9));
            testCase.verifyTrue(snapshot.fresh);
        end

        function aStragglerFromAnOlderGroupIsStillRejected(testCase)
            bank = TestCarMakerPhysics.publishedBank(uint8(7), uint32(0));
            bank = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(1, [3 3 3], uint8(9)), uint32(10));
            [bank, ok, reason] = receiveCarMakerPhysics(bank, ...
                TestCarMakerPhysics.frame(2, [3 3 3], uint8(8)), uint32(11));
            testCase.verifyFalse(ok);
            testCase.verifyEqual(reason, 'counter_mismatch');
            testCase.verifyEqual(bank.pendingCounter, uint8(9), ...
                'A straggler must not disturb the group being assembled.');
        end

        function aLongCarMakerPauseRecoversWhenItComesBack(testCase)
            % Phase-17 stale behaviour end to end: publish, go quiet past the
            % freshness window, then resume with a counter that has moved on.
            bank = TestCarMakerPhysics.publishedBank(uint8(100), uint32(0));
            testCase.verifyTrue(carMakerPhysicsSnapshot(bank, uint32(0)).fresh);
            testCase.verifyFalse(carMakerPhysicsSnapshot(bank, uint32(500)).fresh, ...
                'A paused CarMaker must go stale.');
            bank = TestCarMakerPhysics.publishGroup(bank, uint8(120), uint32(500));
            snapshot = carMakerPhysicsSnapshot(bank, uint32(500));
            testCase.verifyTrue(snapshot.fresh, ...
                'The physics path must recover when CarMaker returns.');
            testCase.verifyEqual(snapshot.counter, uint8(120));
        end

        % --------------------------------------------------------- selector

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

        function selectorRefusesIncompleteOrNonFiniteTruth(testCase)
            kinematic = 1:9;
            incomplete = struct('values', 11:22, 'fresh', true, 'complete', false);
            testCase.verifyEqual( ...
                selectVehicleObservation(kinematic, incomplete, true), kinematic);
            broken = struct('values', [11:18 Inf 0 0 0], 'fresh', true, ...
                'complete', true);
            testCase.verifyEqual( ...
                selectVehicleObservation(kinematic, broken, true), kinematic);
        end

        function uninitialisedZerosAreNeverPublishedAsTruth(testCase)
            % A fresh bank has never seen a group, so its zeroed published
            % values must not be visible as complete truth -- and the selector
            % must not take them even with the truth gate forced on. The
            % CarMaker side additionally refuses to transmit zero-initialised
            % frames at all (MFE_CAN.Physics.Valid, asserted in
            % TESTCM4SLTRUTHSOURCES); this is the receiver-side half.
            bank = initialCarMakerPhysicsBank();
            snapshot = carMakerPhysicsSnapshot(bank, uint32(0));
            testCase.verifyFalse(snapshot.complete);
            testCase.verifyFalse(snapshot.fresh);
            testCase.verifyEqual(snapshot.values, zeros(1, 12));
            kinematic = 1:9;
            [obs, source] = selectVehicleObservation(kinematic, snapshot, true);
            testCase.verifyEqual(obs, kinematic);
            testCase.verifyEqual(source, uint8(0));
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
        function bank = publishedBank(counter, tickMs)
            bank = TestCarMakerPhysics.publishGroup( ...
                initialCarMakerPhysicsBank(), counter, tickMs);
        end

        function bank = publishGroup(bank, counter, tickMs)
            for kind = 1:3
                bank = receiveCarMakerPhysics(bank, ...
                    TestCarMakerPhysics.frame(kind, [1 1 1], counter), tickMs);
            end
        end

        function frame = frame(kind, values, counter)
            scales = [.01 .002 .01 .0001];
            frame = struct('id', uint32(hex2dec('502') + kind), 'dlc', uint8(8), ...
                'payload', TestCarMakerPhysics.payload(values, scales(kind), counter), ...
                'isExtended', false, 'isRemote', false, 'drop', false);
        end

        function payload = payload(values, scale, counter)
            payload = TestCarMakerPhysics.payloadCounts( ...
                round(values ./ scale), counter);
        end

        function payload = payloadCounts(counts, counter)
            raw = int16(counts);
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
