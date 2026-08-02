classdef TestCanDropMask < matlab.unittest.TestCase
    %TESTCANDROPMASK Fix 4: hil_cmd_can_drop_control_mask/drop_status_mask.
    %
    %   Covers INVERTERHIL.APPLYCONTROLDROPMASK (received control frames) and
    %   INVERTERHIL.STATUSTRANSMITMASK (the nine-frame status cycle), the two
    %   host-verifiable functions the GUI's drop-mask tunables now drive (see
    %   BUILD_INVERTER_HIL_MODEL's ADDARCHITECTURE and ADDHARDWAREBOUNDARY).
    %
    %   "Genuinely absent, not zeroed" is asserted directly for the control
    %   path: a masked frame must never reach INVERTERHIL.RECEIVECONTROLFRAME
    %   as a retained command (HASCOMMAND stays false, ACCEPTEDCOUNT stays 0,
    %   the bank's decoded command stays the untouched default), not merely
    %   have its fields zeroed. The status path's "genuinely absent" property
    %   (a CAN Write block's Tx Control input gating actual transmission) is a
    %   Simulink hardware-boundary guarantee that cannot be exercised without
    %   a target; STATUSTRANSMITMASK's host-testable contract is the keep/drop
    %   bit vector it computes, asserted below.

    methods (Test)
        function controlMaskDropsOnlyItsOwnChannel(testCase)
            ids = inverterhil.protocol().controlIds; % 0x186 0x196 0x1A6 0x1B6
            for bitIndex = 1:4
                mask = uint8(bitshift(1, bitIndex - 1));
                for channel = 1:4
                    frame = TestCanDropMask.validFrame(ids(channel));
                    [outFrame, dropped] = inverterhil.applyControlDropMask( ...
                        frame, mask);
                    if channel == bitIndex
                        testCase.verifyTrue(dropped);
                        testCase.verifyTrue(outFrame.drop);
                    else
                        testCase.verifyFalse(dropped);
                        testCase.verifyFalse(outFrame.drop);
                    end
                end
            end
        end

        function unmatchedIdIsNeverAffected(testCase)
            frame = TestCanDropMask.validFrame(hex2dec('7FF'));
            [outFrame, dropped] = inverterhil.applyControlDropMask( ...
                frame, uint8(255));
            testCase.verifyFalse(dropped);
            testCase.verifyFalse(outFrame.drop);
        end

        function alreadyDroppedFrameStaysDropped(testCase)
            % An upstream drop (e.g. genuinely no CAN data this tick) must
            % not be un-dropped just because the mask bit for its channel
            % happens to be clear.
            frame = TestCanDropMask.validFrame(hex2dec('186'));
            frame.drop = true;
            [outFrame, dropped] = inverterhil.applyControlDropMask( ...
                frame, uint8(0));
            testCase.verifyTrue(outFrame.drop);
            testCase.verifyFalse(dropped, ...
                'DROPPED reports only drops THIS call forced.');
        end

        function malformedFrameErrors(testCase)
            frame = TestCanDropMask.validFrame(hex2dec('186'));
            frame = rmfield(frame, 'dlc');
            testCase.verifyError(@() inverterhil.applyControlDropMask( ...
                frame, uint8(1)), 'inverterhil:MalformedFrame');
        end

        function invalidMaskErrors(testCase)
            frame = TestCanDropMask.validFrame(hex2dec('186'));
            testCase.verifyError(@() inverterhil.applyControlDropMask( ...
                frame, -1), 'inverterhil:InvalidDropMask');
            testCase.verifyError(@() inverterhil.applyControlDropMask( ...
                frame, 256), 'inverterhil:InvalidDropMask');
            testCase.verifyError(@() inverterhil.applyControlDropMask( ...
                frame, [1 2]), 'inverterhil:InvalidDropMask');
        end

        function droppedControlFrameIsGenuinelyAbsentFromTheBank(testCase)
            % The whole point of Fix 4: masking a channel must make its
            % command genuinely never-retained, not a zeroed-out command
            % that would still read as HASCOMMAND true.
            payload = uint8([hex2dec('AD') hex2dec('5A') hex2dec('C7') ...
                hex2dec('CF') 0 hex2dec('20') 0 hex2dec('E0')]);
            frame = TestCanDropMask.frameWithPayload(hex2dec('186'), payload);

            bank = inverterhil.initialDecoderBank();
            masked = inverterhil.applyControlDropMask(frame, uint8(1));
            [bank, accepted, reason] = inverterhil.receiveControlFrame( ...
                bank, masked, uint32(100));

            testCase.verifyFalse(accepted);
            testCase.verifyEqual(reason, 'injected_drop');
            testCase.verifyFalse(bank.hasCommand(1));
            testCase.verifyEqual(bank.acceptedCount(1), uint32(0));
            testCase.verifyEqual(bank.rejectedCount, uint32(1));
            testCase.verifyEqual(bank.lastRejectCode, uint8(1));
            % Not merely zeroed: the retained command struct is the
            % never-decoded default, and the raw payload was never copied in.
            testCase.verifyEqual(bank.lastPayload(1, :), zeros(1, 8, 'uint8'));
        end

        function nonDroppedControlFrameArrivesUnchanged(testCase)
            % The same frame, with a mask that does not cover its channel,
            % must decode and retain exactly as it would with no mask at all.
            payload = uint8([hex2dec('AD') hex2dec('5A') hex2dec('C7') ...
                hex2dec('CF') 0 hex2dec('20') 0 hex2dec('E0')]);
            frame = TestCanDropMask.frameWithPayload(hex2dec('186'), payload);

            bankNoMask = inverterhil.initialDecoderBank();
            [bankNoMask, acceptedNoMask] = inverterhil.receiveControlFrame( ...
                bankNoMask, frame, uint32(100));

            bankMasked = inverterhil.initialDecoderBank();
            passedThrough = inverterhil.applyControlDropMask( ...
                frame, uint8(bitshift(1, 1))); % bit for channel 2, not 1
            [bankMasked, acceptedMasked] = inverterhil.receiveControlFrame( ...
                bankMasked, passedThrough, uint32(100));

            testCase.verifyTrue(acceptedNoMask);
            testCase.verifyTrue(acceptedMasked);
            testCase.verifyEqual(bankMasked.hasCommand(1), ...
                bankNoMask.hasCommand(1));
            testCase.verifyEqual(bankMasked.commands(1), bankNoMask.commands(1));
            testCase.verifyEqual(bankMasked.lastPayload(1, :), ...
                bankNoMask.lastPayload(1, :));
            testCase.verifyEqual(bankMasked.lastPayload(1, :), payload);
        end

        function statusTransmitMaskKeepsAllNineWhenMaskIsZero(testCase)
            keep = inverterhil.statusTransmitMask(uint16(0));
            testCase.verifySize(keep, [1 9]);
            testCase.verifyTrue(islogical(keep));
            testCase.verifyTrue(all(keep));
        end

        function statusTransmitMaskDropsExactlyTheMaskedFrame(testCase)
            ids = inverterhil.protocol().statusCycleIds;
            testCase.assertNumElements(ids, 9);
            for frameIndex = 1:9
                mask = uint16(bitshift(1, frameIndex - 1));
                keep = inverterhil.statusTransmitMask(mask);
                expected = true(1, 9);
                expected(frameIndex) = false;
                testCase.verifyEqual(keep, expected);
            end
        end

        function statusTransmitMaskUnusedHighBitsHaveNoEffect(testCase)
            % Only bits 0-8 map to the nine status frames; bits 9-15 are
            % documented as unused and must not affect any frame's gate.
            keep = inverterhil.statusTransmitMask(uint16(bitshift(1, 15)));
            testCase.verifyTrue(all(keep));
        end

        function statusTransmitMaskInvalidMaskErrors(testCase)
            testCase.verifyError( ...
                @() inverterhil.statusTransmitMask(-1), ...
                'inverterhil:InvalidDropMask');
            testCase.verifyError( ...
                @() inverterhil.statusTransmitMask(65536), ...
                'inverterhil:InvalidDropMask');
        end
    end

    methods (Static)
        function frame = validFrame(id)
            frame = struct( ...
                'id', uint32(id), ...
                'dlc', uint8(8), ...
                'payload', zeros(1, 8, 'uint8'), ...
                'isExtended', false, ...
                'isRemote', false, ...
                'drop', false);
        end

        function frame = frameWithPayload(id, payload)
            frame = TestCanDropMask.validFrame(id);
            frame.payload = payload;
        end
    end
end
