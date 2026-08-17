classdef TestPedalDemand < matlab.unittest.TestCase
    methods (Test)
        function decoderRejectsTransportAndPayloadFailures(testCase)
            payload = TestPedalDemand.payload(25, 60, true, 3);
            cases = {uint32(hex2dec('501')), uint8(8), payload, false, false, 'wrong_id'; uint32(hex2dec('500')), uint8(7), payload, false, false, 'wrong_dlc'; uint32(hex2dec('500')), uint8(8), payload, true, false, 'extended_frame'; uint32(hex2dec('500')), uint8(8), payload, false, true, 'remote_frame'; uint32(hex2dec('500')), uint8(8), payload(1:7), false, false, 'malformed_payload'};
            for k = 1:size(cases, 1)
                [accepted, ~, reason] = inverterhil.decodePedalDemandFrame(cases{k,1}, cases{k,2}, cases{k,3}, cases{k,4}, cases{k,5});
                testCase.verifyFalse(accepted); testCase.verifyEqual(reason, cases{k,6});
            end
            outOfRange = TestPedalDemand.payload(101, 0, true, 0);
            [accepted, ~, reason] = inverterhil.decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), outOfRange, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'out_of_range');
            badCrc = payload; badCrc(4) = bitxor(badCrc(4), uint8(1));
            [accepted, ~, reason] = inverterhil.decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), badCrc, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'integrity_failure');
            reserved = payload; reserved(5) = uint8(1);
            [accepted, ~, reason] = inverterhil.decodePedalDemandFrame(uint32(hex2dec('500')), uint8(8), reserved, false, false);
            testCase.verifyFalse(accepted); testCase.verifyEqual(reason, 'reserved_nonzero');
        end
        function ownershipRequiresAdvanceActiveAndFreshness(testCase)
            bank = inverterhil.initialPedalDemandBank();
            bank = inverterhil.receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 7), uint32(10));
            testCase.verifyFalse(inverterhil.pedalDemandSnapshot(bank, uint32(10)).ownsPedals);
            bank = inverterhil.receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 8), uint32(11));
            live = inverterhil.pedalDemandSnapshot(bank, uint32(11)); testCase.verifyTrue(live.ownsPedals); testCase.verifyEqual(live.throttlePercent, 20);
            stalled = inverterhil.receivePedalDemandFrame(bank, TestPedalDemand.frame(20, 30, true, 8), uint32(12));
            testCase.verifyFalse(inverterhil.pedalDemandSnapshot(stalled, uint32(12)).ownsPedals);
            inactive = inverterhil.receivePedalDemandFrame(stalled, TestPedalDemand.frame(20, 30, false, 9), uint32(13));
            testCase.verifyFalse(inverterhil.pedalDemandSnapshot(inactive, uint32(13)).ownsPedals);
            testCase.verifyFalse(inverterhil.pedalDemandSnapshot(bank, uint32(112)).fresh);
        end
    end
    methods (Static, Access = private)
        function frame = frame(throttle, brake, active, counter)
            frame = struct('id', uint32(hex2dec('500')), 'dlc', uint8(8), 'payload', TestPedalDemand.payload(throttle, brake, active, counter), 'isExtended', false, 'isRemote', false, 'drop', false);
        end
        function bytes = payload(throttle, brake, active, counter)
            bytes = uint8([throttle brake bitor(bitshift(uint8(counter), 1), uint8(active)) 0 0 0 0 0]); bytes(4) = TestPedalDemand.crc8(bytes(1:3));
        end
        function value = crc8(bytes)
            value = uint8(255); for i = 1:numel(bytes), value = bitxor(value, bytes(i)); for j = 1:8, if bitand(value, uint8(128)) ~= 0, value = bitxor(bitshift(value, 1), uint8(29)); else, value = bitshift(value, 1); end, end, end; value = bitxor(value, uint8(255));
        end
    end
end
