classdef TestModelOrchestration < matlab.unittest.TestCase
    methods (Test)
        function noVcuHoldsIdleAndPacksRealNotZeroStatus(testCase)
            config = inverterhil.defaultStateConfig();
            cal = inverterhil.defaultCalibration();
            state = inverterhil.initialSystemState(config);
            plantState = inverterhil.initialPlantState(cal);

            [state, plantState, cycle, stateOutput, plantOutput] = ...
                inverterhil.stepModel(state, plantState, uint32(0), ...
                config, cal);

            for channel = 1:4
                testCase.verifyEqual(stateOutput.channels(channel).mode, ...
                    uint8(0), 'Channel must hold Idle with no VCU.');
                testCase.verifyEqual( ...
                    stateOutput.channels(channel).activeFault, 'none', ...
                    ['A never-received command must not latch Error ' ...
                    '(see plan LV_ON decision).']);
                testCase.verifyTrue( ...
                    plantOutput.channels(channel).zeroTorqueApplied);
                testCase.verifyEqual( ...
                    plantOutput.channels(channel).authorityReason, ...
                    'mode_not_drive');
                testCase.verifyEqual( ...
                    plantOutput.channels(channel).torqueActualNm, 0);
            end

            testCase.verifyEqual(cycle.ids, uint32(hex2dec( ...
                {'383', '385', '393', '395', '3A3', '3A5', ...
                '3B3', '3B5', '400'}))');
            testCase.verifyEqual(cycle.dlc, repmat(uint8(8), 1, 9));

            % The 3X3 frames pack maxAllowedCurrentA/temperature fields that
            % are nonzero even at Idle (25 C ambient, full current headroom),
            % so a genuinely-packed frame must NOT be all-zero bytes -- that
            % would mean a zero-constant placeholder survived instead.
            testCase.verifyNotEqual(cycle.payloads(1, :), ...
                zeros(1, 8, 'uint8'), ...
                '3X3 status must be packed, not a zero placeholder.');

            % The 0x400 general status packs the DC-link voltage; verify the
            % round trip against the same encoding PACKSYSTEMSTATUS uses
            % (1/64 V per LSB, 16-bit little-endian) rather than trusting an
            % opaque byte pattern.
            raw = double(cycle.payloads(9, 1)) + 256 * double(cycle.payloads(9, 2));
            testCase.verifyEqual(raw / 64, 400, 'AbsTol', 1e-9);
        end

        function stateAndPlantPersistAcrossTicks(testCase)
            config = inverterhil.defaultStateConfig();
            cal = inverterhil.defaultCalibration();
            state = inverterhil.initialSystemState(config);
            plantState = inverterhil.initialPlantState(cal);

            for tick = 0:4
                [state, plantState] = inverterhil.stepModel(state, ...
                    plantState, uint32(tick), config, cal);
            end
            testCase.verifyEqual(state.stepCount, uint64(5));
            testCase.verifyEqual(plantState.stepCount, uint64(5));
        end

        function rejectsNonUint32Tick(testCase)
            config = inverterhil.defaultStateConfig();
            cal = inverterhil.defaultCalibration();
            state = inverterhil.initialSystemState(config);
            plantState = inverterhil.initialPlantState(cal);
            testCase.verifyError(@() inverterhil.stepModel(state, ...
                plantState, 0, config, cal), 'inverterhil:InvalidTick');
        end
    end
end
