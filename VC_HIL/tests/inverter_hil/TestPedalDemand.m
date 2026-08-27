classdef TestPedalDemand < matlab.unittest.TestCase
    methods (Test)
        function decoderRejectsTransportAndPayloadFailures(testCase)
            payload = TestPedalDemand.payload(25, 60, true, 3);
            cases = {uint32(hex2dec('501')), uint8(8), payload, false, false, 'wrong_id'; uint32(hex2dec('500')), uint8(7), payload, false, false, 'wrong_dlc'; uint32(hex2dec('500')), uint8(8), payload, true, false, 'extended_frame'; uint32(hex2dec('500')), uint8(8), payload, false, true, 'remote_frame'; uint32(hex2dec('500')), uint8(8), payload(1:7), false, false, 'malformed_payload'};
            for k = 1:size(cases, 1)
                [accepted, ~, reason] = decodePedalDemandFrame(cases{k,1}, cases{k,2}, cases{k,3}, cases{k,4}, cases{k,5});
                testCase.verifyFalse(accepted); testCase.verifyEqual(reason, cases{k,6});
            end
            outOfRange = TestPedalDemand.payload(101, 0, true, 0);
            [accepted, ~, reason] = decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), outOfRange, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'out_of_range');
            badCrc = payload; badCrc(6) = bitxor(badCrc(6), uint8(1));
            [accepted, ~, reason] = decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), badCrc, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'integrity_failure');
            % Reserved1 (B7:B8) must be zero; CRC is recomputed so this fails on
            % the reserved check alone rather than incidentally on integrity.
            reserved = payload; reserved(7) = uint8(1);
            [accepted, ~, reason] = decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), reserved, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'reserved_nonzero');
            % Reserved0 (B5 bits 5..7) must be zero too.
            reserved0 = payload; reserved0(5) = bitor(reserved0(5), uint8(32)); reserved0(6) = TestPedalDemand.crc8(reserved0(1:5));
            [accepted, ~, reason] = decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), reserved0, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'reserved_nonzero');
        end
        function ownershipRequiresAdvanceActiveAndFreshness(testCase)
            bank = initialPedalDemandBank();
            bank = receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 7), uint32(10));
            testCase.verifyFalse(pedalDemandSnapshot(bank, uint32(10)).ownsPedals);
            bank = receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 8), uint32(11));
            live = pedalDemandSnapshot(bank, uint32(11)); testCase.verifyTrue(live.ownsPedals); testCase.verifyEqual(live.throttlePercent, 20);
            stalled = receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 8), uint32(12));
            testCase.verifyFalse(pedalDemandSnapshot(stalled, uint32(12)).ownsPedals);
            inactive = receivePedalDemandFrame(stalled, TestPedalDemand.frame(20, 30, false, 9), uint32(13));
            testCase.verifyFalse(pedalDemandSnapshot(inactive, uint32(13)).ownsPedals);
            testCase.verifyFalse(pedalDemandSnapshot(bank, uint32(112)).fresh);
        end
    end
    methods (Static, Access = private)
        function frame = frame(throttle, brake, active, counter)
            frame = struct('id', uint32(hex2dec('500')), 'dlc', uint8(8), 'payload', TestPedalDemand.payload(throttle, brake, active, counter), 'isExtended', false, 'isRemote', false, 'drop', false);
        end
        function bytes = payload(throttle, brake, active, counter)
            % Wire layout per inverter_hil/docs/can_pedal_demand_frame_spec.md:
            % B1:B2 throttle uint16 LE at 0.01 %/bit, B3:B4 brake likewise,
            % B5 bit0 active + bits1..4 counter, B6 CRC over B1..B5, B7:B8 zero.
            throttleRaw = uint16(round(double(throttle) / 0.01));
            brakeRaw = uint16(round(double(brake) / 0.01));
            bytes = zeros(1, 8, 'uint8');
            bytes(1) = uint8(bitand(throttleRaw, uint16(255)));
            bytes(2) = uint8(bitshift(throttleRaw, -8));
            bytes(3) = uint8(bitand(brakeRaw, uint16(255)));
            bytes(4) = uint8(bitshift(brakeRaw, -8));
            bytes(5) = bitor(bitshift(uint8(counter), 1), uint8(active));
            bytes(6) = TestPedalDemand.crc8(bytes(1:5));
        end
        function value = crc8(bytes)
            value = uint8(255); for i = 1:numel(bytes), value = bitxor(value, bytes(i)); for j = 1:8, if bitand(value, uint8(128)) ~= 0, value = bitxor(bitshift(value, 1), uint8(29)); else, value = bitshift(value, 1); end, end, end; value = bitxor(value, uint8(255));
        end
    end
end
