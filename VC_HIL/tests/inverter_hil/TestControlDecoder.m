classdef TestControlDecoder < matlab.unittest.TestCase
    methods (Test)
        function rxObservationReportsWhatWasActuallyReceived(testCase)
            % The GUI's RX table is fed entirely from this matrix, so the
            % column layout is a contract with TARGETSESSION.READLIVEIO and
            % is asserted position by position.
            bank = inverterhil.initialDecoderBank();
            payload = uint8([hex2dec('AD') hex2dec('5A') hex2dec('C7') ...
                hex2dec('CF') 0 hex2dec('20') 0 hex2dec('E0')]);
            frame = TestControlDecoder.frame(hex2dec('196'), payload);

            bank = inverterhil.receiveControlFrame(bank, frame, uint32(1000));
            observation = inverterhil.rxObservation(bank, uint32(1075));

            testCase.assertSize(observation, [4 14]);
            % Channel 2 received; its raw bytes are retained verbatim.
            testCase.verifyEqual(observation(2, 1:8), double(payload));
            testCase.verifyEqual(observation(2, 9), 1);     % hasCommand
            testCase.verifyEqual(observation(2, 10), 1);    % acceptedCount
            testCase.verifyEqual(observation(2, 11), 75);   % ageMs
            testCase.verifyEqual(observation(2, 12), 0);    % outOfDomain

            % Every other channel must read as never-received, NOT as zero
            % age -- a silent 0 ms would look like a live command.
            for channel = [1 3 4]
                testCase.verifyEqual(observation(channel, 1:8), zeros(1, 8));
                testCase.verifyEqual(observation(channel, 9), 0);
                testCase.verifyEqual(observation(channel, 11), ...
                    double(intmax('uint32')), ...
                    'never-received must be the sentinel, not 0 ms.');
            end

            % Bank-wide columns are repeated on every row.
            testCase.verifyEqual(observation(:, 13), zeros(4, 1));
            testCase.verifyEqual(observation(:, 14), zeros(4, 1));
        end

        function rxObservationDistinguishesZeroPayloadFromNoFrame(testCase)
            % An all-zero payload is a frame a VCU can legitimately send.
            % If absence were inferred from the bytes, this frame would be
            % indistinguishable from silence and the RX table would show
            % dashes for a channel that is actually being commanded.
            bank = inverterhil.initialDecoderBank();
            frame = TestControlDecoder.frame(hex2dec('186'), ...
                zeros(1, 8, 'uint8'));

            bank = inverterhil.receiveControlFrame(bank, frame, uint32(500));
            observation = inverterhil.rxObservation(bank, uint32(500));

            testCase.verifyEqual(observation(1, 1:8), zeros(1, 8));
            testCase.verifyEqual(observation(1, 9), 1, ...
                'hasCommand must report the frame despite zero bytes.');
            testCase.verifyEqual(observation(1, 11), 0);
        end

        function rxObservationCountsRejectionsWithoutAttributingThem(testCase)
            % A rejected frame cannot be attributed to a channel, so it must
            % raise the bank-wide counter and leave every per-channel field
            % untouched.
            bank = inverterhil.initialDecoderBank();
            bad = TestControlDecoder.frame(hex2dec('7FF'), ...
                zeros(1, 8, 'uint8'));

            bank = inverterhil.receiveControlFrame(bank, bad, uint32(10));
            observation = inverterhil.rxObservation(bank, uint32(10));

            testCase.verifyEqual(observation(:, 13), 1 * ones(4, 1));
            testCase.verifyEqual(observation(:, 14), 2 * ones(4, 1));
            testCase.verifyEqual(observation(:, 9), zeros(4, 1));
        end

        function retainedPayloadTracksOnlyAcceptedFrames(testCase)
            % A later rejected frame must not overwrite the last good bytes.
            bank = inverterhil.initialDecoderBank();
            good = uint8([1 2 3 4 5 6 7 8]);
            bank = inverterhil.receiveControlFrame(bank, ...
                TestControlDecoder.frame(hex2dec('1A6'), good), uint32(1));
            rejected = TestControlDecoder.frame(hex2dec('1A6'), ...
                uint8([9 9 9 9 9 9 9 9]));
            rejected.isRemote = true;

            bank = inverterhil.receiveControlFrame(bank, rejected, uint32(2));
            observation = inverterhil.rxObservation(bank, uint32(2));

            testCase.verifyEqual(observation(3, 1:8), double(good));
            testCase.verifyEqual(observation(3, 10), 1, ...
                'a rejected frame must not raise acceptedCount.');
        end

        function decodesGoldenVector(testCase)
            payload = uint8([hex2dec('AD') hex2dec('5A') ...
                hex2dec('C7') hex2dec('CF') 0 hex2dec('20') ...
                0 hex2dec('E0')]);

            [accepted, channel, command, reason] = ...
                inverterhil.decodeControlFrame(uint32(hex2dec('186')), ...
                uint8(8), payload, false, false);

            testCase.verifyTrue(accepted);
            testCase.verifyEqual(channel, uint8(1));
            testCase.verifyEqual(reason, 'accepted');
            testCase.verifyTrue(command.enable);
            testCase.verifyFalse(command.resetError);
            testCase.verifyTrue(command.ascAllowed);
            testCase.verifyTrue(command.currentMode);
            testCase.verifyEqual(command.speedSetpointRpm, int16(-12345));
            testCase.verifyEqual(command.rawTorquePosCounts, int16(8192));
            testCase.verifyEqual(command.rawTorqueNegCounts, int16(-8192));
            testCase.verifyEqual(command.torquePosNm256, 32);
            testCase.verifyEqual(command.torqueNegNm256, -32);
            testCase.verifyEqual(command.torquePosNm512, 16);
            testCase.verifyEqual(command.torqueNegNm512, -16);
            testCase.verifyEqual(command.reservedRaw, uint16(hex2dec('A5A')));
        end

        function mapsAllFourCanonicalIds(testCase)
            ids = uint32([hex2dec('186') hex2dec('196') ...
                hex2dec('1A6') hex2dec('1B6')]);
            payload = zeros(1, 8, 'uint8');
            for index = 1:4
                [accepted, channel, ~, reason] = ...
                    inverterhil.decodeControlFrame(ids(index), uint8(8), ...
                    payload, false, false);
                testCase.verifyTrue(accepted);
                testCase.verifyEqual(channel, uint8(index));
                testCase.verifyEqual(reason, 'accepted');
            end
        end

        function rejectsMalformedFramesWithoutRefreshingRetention(testCase)
            bank = inverterhil.initialDecoderBank();
            frame = TestControlDecoder.validFrame(hex2dec('186'));
            [bank, accepted] = inverterhil.receiveControlFrame( ...
                bank, frame, uint32(10));
            testCase.assertTrue(accepted);
            retained = bank.commands(1);

            cases = {
                TestControlDecoder.withField(frame, 'dlc', uint8(7)), 'wrong_dlc';
                TestControlDecoder.withField(frame, 'isExtended', true), 'extended_frame';
                TestControlDecoder.withField(frame, 'isRemote', true), 'remote_frame';
                TestControlDecoder.withField(frame, 'id', uint32(hex2dec('187'))), 'wrong_id';
                TestControlDecoder.withField(frame, 'payload', zeros(8, 1, 'uint8')), 'malformed_payload';
                TestControlDecoder.withField(frame, 'drop', true), 'injected_drop'};

            for index = 1:size(cases, 1)
                beforeRejects = bank.rejectedCount;
                [bank, accepted, reason] = inverterhil.receiveControlFrame( ...
                    bank, cases{index, 1}, uint32(100 + index));
                testCase.verifyFalse(accepted);
                testCase.verifyEqual(reason, cases{index, 2});
                testCase.verifyEqual(bank.lastValidTickMs(1), uint32(10));
                testCase.verifyEqual(bank.commands(1), retained);
                testCase.verifyEqual(bank.rejectedCount, beforeRejects + uint32(1));
            end
        end

        function retentionIsIndependentAcrossChannels(testCase)
            bank = inverterhil.initialDecoderBank();
            for index = 1:4
                frame = TestControlDecoder.validFrame( ...
                    [hex2dec('186') hex2dec('196') ...
                    hex2dec('1A6') hex2dec('1B6')]);
                frame.id = frame.id(index);
                frame.payload(3:4) = typecast(int16(100 * index), 'uint8');
                [bank, accepted] = inverterhil.receiveControlFrame( ...
                    bank, frame, uint32(10 * index));
                testCase.assertTrue(accepted);
            end

            before = bank;
            update = TestControlDecoder.validFrame(hex2dec('1A6'));
            update.payload(3:4) = typecast(int16(-777), 'uint8');
            [bank, accepted] = inverterhil.receiveControlFrame( ...
                bank, update, uint32(99));

            testCase.verifyTrue(accepted);
            testCase.verifyEqual(bank.commands(3).speedSetpointRpm, int16(-777));
            testCase.verifyEqual(bank.lastValidTickMs(3), uint32(99));
            testCase.verifyEqual(bank.commands([1 2 4]), before.commands([1 2 4]));
            testCase.verifyEqual(bank.lastValidTickMs([1 2 4]), ...
                before.lastValidTickMs([1 2 4]));
            testCase.verifyEqual(bank.acceptedCount, uint32([1 1 2 1]));
        end

        function computesRolloverSafeAgeAndStrictBoundaries(testCase)
            bank = inverterhil.initialDecoderBank();
            frame = TestControlDecoder.validFrame(hex2dec('186'));
            receivedAt = intmax('uint32') - uint32(3);
            [bank, accepted] = inverterhil.receiveControlFrame( ...
                bank, frame, receivedAt);
            testCase.assertTrue(accepted);

            snapshot = inverterhil.decoderSnapshot(bank, uint32(5));
            testCase.verifyEqual(snapshot.ageMs(1), uint32(9));
            testCase.verifyEqual(snapshot.ageMs(2:4), ...
                repmat(intmax('uint32'), 1, 3));

            bank.lastValidTickMs(1) = uint32(0);
            at50 = inverterhil.decoderSnapshot(bank, uint32(50));
            at51 = inverterhil.decoderSnapshot(bank, uint32(51));
            at500 = inverterhil.decoderSnapshot(bank, uint32(500));
            at501 = inverterhil.decoderSnapshot(bank, uint32(501));
            testCase.verifyFalse(at50.torqueTimedOut(1));
            testCase.verifyTrue(at51.torqueTimedOut(1));
            testCase.verifyFalse(at500.errorTimedOut(1));
            testCase.verifyTrue(at501.errorTimedOut(1));
        end

        function malformedCanIdFailsClosedWithoutThrowing(testCase)
            payload = zeros(1, 8, 'uint8');
            malformedIds = { ...
                uint32([hex2dec('186') hex2dec('196')]), ...
                uint32([hex2dec('186'); hex2dec('196')]), ...
                [], NaN, Inf, -1, 1.5, hex2dec('800'), ...
                complex(hex2dec('186'), 1), '390', "390", struct()};
            for index = 1:numel(malformedIds)
                [accepted, channel, ~, reason] = ...
                    inverterhil.decodeControlFrame( ...
                    malformedIds{index}, uint8(8), payload, false, false);
                testCase.verifyFalse(accepted);
                testCase.verifyEqual(channel, uint8(0));
                testCase.verifyTrue(any(strcmp(reason, ...
                    {'wrong_id', 'malformed_id'})));
            end
        end

        function nonnumericScalarMetadataCannotMasqueradeAsValid(testCase)
            id = uint32(hex2dec('186'));
            payload = zeros(1, 8, 'uint8');

            [accepted, ~, ~, reason] = inverterhil.decodeControlFrame( ...
                id, char(8), payload, false, false);
            testCase.verifyFalse(accepted);
            testCase.verifyEqual(reason, 'wrong_dlc');

            [accepted, ~, ~, reason] = inverterhil.decodeControlFrame( ...
                id, uint8(8), payload, char(0), false);
            testCase.verifyFalse(accepted);
            testCase.verifyTrue(any(strcmp(reason, ...
                {'extended_frame', 'malformed_frame_type'})));

            [accepted, ~, ~, reason] = inverterhil.decodeControlFrame( ...
                id, uint8(8), payload, false, char(0));
            testCase.verifyFalse(accepted);
            testCase.verifyTrue(any(strcmp(reason, ...
                {'remote_frame', 'malformed_frame_type'})));
        end
    end

    methods (Static, Access = private)
        function frame = frame(id, payload)
            %FRAME A valid frame carrying PAYLOAD, for the RX observation
            %   tests. VALIDFRAME below is payload-free and kept as is so the
            %   existing decoder tests are untouched.
            frame = struct( ...
                'id', uint32(id), ...
                'dlc', uint8(8), ...
                'payload', payload, ...
                'isExtended', false, ...
                'isRemote', false, ...
                'drop', false);
        end

        function frame = validFrame(id)
            frame = struct( ...
                'id', uint32(id), ...
                'dlc', uint8(8), ...
                'payload', zeros(1, 8, 'uint8'), ...
                'isExtended', false, ...
                'isRemote', false, ...
                'drop', false);
        end

        function value = withField(value, name, fieldValue)
            value.(name) = fieldValue;
        end
    end
end
