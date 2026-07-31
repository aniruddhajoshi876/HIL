classdef TestControlDecoder < matlab.unittest.TestCase
    methods (Test)
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
