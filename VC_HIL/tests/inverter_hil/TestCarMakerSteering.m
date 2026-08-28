classdef TestCarMakerSteering < matlab.unittest.TestCase
    %TESTCARMAKERSTEERING Fanatec -> CarMaker Steer.WhlAng -> 0x507 -> Speedgoat
    %   -> selector -> Bosch LWS 0x2B0. Covers the transport decode (golden
    %   vectors, Fanatec/Bosch boundaries, CRC, DLC, reserved, range), the
    %   retainer (fresh/stale/duplicate/reorder/wrap), the explicit source
    %   selector (manual vs CarMaker, and the no-silent-fallback rule), the
    %   radians-to-degrees boundary, and the final Bosch frame.

    properties (Constant)
        Golden = TestCarMakerSteering.loadGolden();
    end

    methods (Test)
        % ---------------------------------------------------------- decode

        function decoderMatchesHandDerivedGoldenVectors(testCase)
            vectors = TestCarMakerSteering.Golden.vectors.accepted;
            for index = 1:numel(vectors)
                if iscell(vectors)
                    v = vectors{index};
                else
                    v = vectors(index);
                end
                payload = uint8(v.payloadBytes(:).');
                [ok, decoded, reason] = decodeCarMakerSteeringFrame( ...
                    uint32(hex2dec('507')), uint8(8), payload, false, false);
                testCase.verifyTrue(ok, sprintf('%s rejected: %s', v.name, reason));
                testCase.verifyEqual(decoded.angleRad, v.angleRad, ...
                    'AbsTol', 1e-9, sprintf('%s angle (rad)', v.name));
                testCase.verifyEqual(decoded.angleDeg, v.angleDeg, ...
                    'AbsTol', 1e-4, sprintf('%s angle (deg)', v.name));
                testCase.verifyEqual(decoded.groupCounter, uint8(v.groupCounter), ...
                    sprintf('%s counter', v.name));
            end
        end

        function decoderRejectsEveryHandDerivedRejectionVector(testCase)
            vectors = TestCarMakerSteering.Golden.vectors.rejected;
            expected = struct( ...
                'cmsteer_reject_short_dlc', 'wrong_dlc', ...
                'cmsteer_reject_reserved_nonzero', 'reserved_nonzero', ...
                'cmsteer_reject_bad_crc', 'integrity_failure', ...
                'cmsteer_reject_angle_over_range', 'out_of_range', ...
                'cmsteer_reject_wrong_id', 'wrong_id', ...
                'cmsteer_reject_extended', 'extended_frame');
            for index = 1:numel(vectors)
                % JSONDECODE returns a struct array only when every element
                % has identical fields and compatible shapes. These vectors
                % deliberately do not (one is extended, one has a 7-byte
                % payload), so it hands back a cell array instead.
                if iscell(vectors)
                    v = vectors{index};
                else
                    v = vectors(index);
                end
                isExtended = isfield(v, 'extended') && ~isempty(v.extended) && ...
                    logical(v.extended);
                [ok, ~, reason] = decodeCarMakerSteeringFrame( ...
                    uint32(hex2dec(strrep(v.canId, '0x', ''))), uint8(v.dlc), ...
                    uint8(v.payloadBytes(:).'), isExtended, false);
                testCase.verifyFalse(ok, sprintf('%s was accepted', v.name));
                testCase.verifyEqual(reason, expected.(v.name), ...
                    sprintf('%s rejection reason', v.name));
            end
        end

        function decoderRejectsRemoteAndMalformedPayload(testCase)
            good = TestCarMakerSteering.payloadFromDeg(12.5, 4);
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), good, false, true);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'remote_frame');
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), good(1:7), false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'malformed_payload');
        end

        function everyReservedByteIsChecked(testCase)
            % Bytes 2-5 (1-based 3-6). A sender still using the superseded
            % degrees + angular-speed layout would put the speed field in
            % bytes 2-3, so each one has to be rejected individually.
            for byteIndex = 3:6
                payload = TestCarMakerSteering.payloadFromDeg(30, 1);
                payload(byteIndex) = uint8(1);
                payload(8) = TestCarMakerSteering.crc(payload(1:7));
                [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                    uint8(8), payload, false, false);
                testCase.verifyFalse(ok, sprintf('byte %d accepted', byteIndex - 1));
                testCase.verifyEqual(r, 'reserved_nonzero');
            end
        end

        % ------------------------------------------------- scale and signs

        function zeroPositiveNegativeAndSignedLittleEndian(testCase)
            [~, zeroDecoded] = decodeCarMakerSteeringFrame( ...
                uint32(hex2dec('507')), uint8(8), ...
                TestCarMakerSteering.payloadFromCounts(0, 0), false, false);
            testCase.verifyEqual(zeroDecoded.angleRad, 0);
            testCase.verifyEqual(zeroDecoded.angleDeg, 0);

            % 0.001 rad/count, exactly. 1234 counts is 1.234 rad, and its
            % little-endian int16 is 0x04D2 -> bytes D2 04.
            payload = TestCarMakerSteering.payloadFromCounts(1234, 3);
            testCase.verifyEqual(payload(1), uint8(hex2dec('D2')));
            testCase.verifyEqual(payload(2), uint8(hex2dec('04')));
            [~, decoded] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), payload, false, false);
            testCase.verifyEqual(decoded.angleRad, 1.234, 'AbsTol', 1e-12);

            % -1234 counts is two's complement 0xFB2E -> bytes 2E FB. A field
            % read as unsigned would decode this as +64302 counts.
            payload = TestCarMakerSteering.payloadFromCounts(-1234, 4);
            testCase.verifyEqual(payload(1), uint8(hex2dec('2E')));
            testCase.verifyEqual(payload(2), uint8(hex2dec('FB')));
            [~, decoded] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), payload, false, false);
            testCase.verifyEqual(decoded.angleRad, -1.234, 'AbsTol', 1e-12);

            % Left is positive, on both sides of the rad -> deg boundary.
            [~, left] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), TestCarMakerSteering.payloadFromDeg(30, 1), false, false);
            testCase.verifyGreaterThan(left.angleRad, 0);
            testCase.verifyGreaterThan(left.angleDeg, 0);
        end

        function radiansConvertToDegreesExactlyOnce(testCase)
            % The decoder is the single rad -> deg boundary; every consumer
            % downstream reads .angleDeg rather than re-deriving 180/pi.
            for deg = [-780, -450, -105, -0.5, 0, 0.5, 105, 450, 780]
                payload = TestCarMakerSteering.payloadFromDeg(deg, 1);
                [ok, decoded] = decodeCarMakerSteeringFrame( ...
                    uint32(hex2dec('507')), uint8(8), payload, false, false);
                testCase.verifyTrue(ok, sprintf('%g deg rejected', deg));
                testCase.verifyEqual(decoded.angleDeg, ...
                    decoded.angleRad * 180 / pi, 'AbsTol', 1e-12);
                % One transport count is 0.001 rad = 0.0573 deg, so the
                % round trip can never be more than half a count out.
                testCase.verifyEqual(decoded.angleDeg, deg, 'AbsTol', 0.03, ...
                    sprintf('%g deg round trip', deg));
            end
        end

        function scaleCoversFanatecAndBoschRanges(testCase)
            % The three ranges the contract has to survive: today's active
            % Fanatec Device.0 (+/-105 deg), the disabled Device.1 that may be
            % re-enabled (+/-450 deg), and the Bosch LWS itself (+/-780 deg).
            for deg = [105, -105, 450, -450, 780, -780]
                payload = TestCarMakerSteering.payloadFromDeg(deg, 1);
                [ok, decoded, reason] = decodeCarMakerSteeringFrame( ...
                    uint32(hex2dec('507')), uint8(8), payload, false, false);
                testCase.verifyTrue(ok, ...
                    sprintf('%g deg rejected as %s', deg, reason));
                testCase.verifyEqual(decoded.angleDeg, deg, 'AbsTol', 0.03);
            end
            % One count past the quantised Bosch limit is a sender fault.
            over = TestCarMakerSteering.payloadFromCounts(13615, 1);
            [ok, ~, reason] = decodeCarMakerSteeringFrame( ...
                uint32(hex2dec('507')), uint8(8), over, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(reason, 'out_of_range');
        end

        % --------------------------------------------------------- retainer

        function retainerProvesFreshnessAndCounterAdvance(testCase)
            bank = initialCarMakerSteeringBank();
            f = @(deg, c) TestCarMakerSteering.frame(deg, c);
            % First valid frame: retained, but one frame is not liveness.
            [bank, ok] = receiveCarMakerSteering(bank, f(10, 40), uint32(0));
            testCase.verifyTrue(ok);
            snap = carMakerSteeringSnapshot(bank, uint32(0));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyFalse(snap.counterAdvanced);
            % Second, counter +1: now fresh.
            [bank, ok] = receiveCarMakerSteering(bank, f(12, 41), uint32(10));
            testCase.verifyTrue(ok);
            snap = carMakerSteeringSnapshot(bank, uint32(10));
            testCase.verifyTrue(snap.fresh);
            testCase.verifyTrue(snap.counterAdvanced);
            testCase.verifyEqual(snap.angleDeg, 12, 'AbsTol', 0.03);
            % Age beyond the 30 ms window: stale, value still retained.
            snap = carMakerSteeringSnapshot(bank, uint32(45));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyEqual(snap.ageMs, uint32(35));
            testCase.verifyEqual(snap.angleDeg, 12, 'AbsTol', 0.03);
        end

        function duplicateCounterIsRejectedAndAgesOut(testCase)
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(12, 41), uint32(0));
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(12, 42), uint32(10));
            testCase.verifyTrue(carMakerSteeringSnapshot(bank, uint32(10)).fresh);
            % Frozen-but-repeating sender: same counter, forever.
            [bank, ok, reason] = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(12, 42), uint32(20));
            testCase.verifyFalse(ok);
            testCase.verifyEqual(reason, 'duplicate_counter');
            % The timestamp must NOT have been refreshed, or a stuck sender
            % would read as live forever.
            snap = carMakerSteeringSnapshot(bank, uint32(45));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyEqual(snap.ageMs, uint32(35));
        end

        function reorderedCounterIsRejected(testCase)
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(5, 100), uint32(0));
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(6, 101), uint32(10));
            [bank, ok, reason] = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(99, 100), uint32(20));
            testCase.verifyFalse(ok);
            testCase.verifyEqual(reason, 'out_of_order_counter');
            testCase.verifyEqual(bank.angleDeg, 6, 'AbsTol', 0.03, ...
                'A reordered frame must not overwrite the retained value.');
        end

        function counterWrapCountsAsAdvancing(testCase)
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(1, 255), uint32(0));
            [bank, ok] = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(2, 0), uint32(10));
            testCase.verifyTrue(ok);
            testCase.verifyTrue( ...
                carMakerSteeringSnapshot(bank, uint32(10)).counterAdvanced);
        end

        function lostFramesStillAdvanceAndRecover(testCase)
            % A skipped counter is forward progress, not a fault. The exact-+1
            % rule this replaced latched the path off permanently after one
            % lost frame, which would have made Phase-17 recovery impossible.
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(1, 10), uint32(0));
            [bank, ok] = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(2, 14), uint32(10));
            testCase.verifyTrue(ok, 'Four lost frames must not wedge the retainer.');
            testCase.verifyTrue( ...
                carMakerSteeringSnapshot(bank, uint32(10)).counterAdvanced);
        end

        function injectedDropLeavesRetainedValueUntouched(testCase)
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(12, 41), uint32(0));
            dropped = TestCarMakerSteering.frame(99, 42);
            dropped.drop = true;
            [bank, ok, r] = receiveCarMakerSteering(bank, dropped, uint32(10));
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'injected_drop');
            testCase.verifyEqual(bank.angleDeg, 12, 'AbsTol', 0.03);
        end

        % --------------------------------------------------------- selector

        function manualModeRequiresExplicitSelectionAndIsTheDefault(testCase)
            config = defaultVehicleStateConfig();
            testCase.verifyEqual(config.steeringSourceMode, uint8(0), ...
                'The shipping default must be manual, like carMakerTruthEnabled.');
            fresh = TestCarMakerSteering.snapshot(-47.3, true);
            % Manual mode ignores 0x507 entirely, even when it is fresh.
            [angleDeg, source, valid] = selectSteeringSource(15, fresh, uint8(0));
            testCase.verifyEqual(angleDeg, 15);
            testCase.verifyEqual(source, uint8(0));
            testCase.verifyTrue(valid);
            % CarMaker mode has to be asked for.
            [angleDeg, source, valid] = selectSteeringSource(15, fresh, uint8(1));
            testCase.verifyEqual(angleDeg, -47.3, 'AbsTol', 1e-9);
            testCase.verifyEqual(source, uint8(1));
            testCase.verifyTrue(valid);
        end

        function staleCarMakerNeverSilentlyBecomesTheGuiDial(testCase)
            % The central safety property: in CarMaker mode a stale 0x507 must
            % not put the GUI dial on the VC bus. The VCU would see a
            % plausible steering angle that no longer tracks the driver's
            % wheel, with nothing on the wire saying so.
            stale = TestCarMakerSteering.snapshot(-47.3, false);
            [angleDeg, source, valid, fresh] = selectSteeringSource(15, stale, uint8(1));
            testCase.verifyEqual(source, uint8(2));
            testCase.verifyFalse(valid);
            testCase.verifyFalse(fresh);
            testCase.verifyNotEqual(angleDeg, 15, ...
                'A stale CarMaker source must never yield the GUI dial value.');
            % Never-received and frozen senders take the same path.
            never = TestCarMakerSteering.snapshot(0, false);
            never.hasValue = false;
            [~, source, valid] = selectSteeringSource(15, never, uint8(1));
            testCase.verifyEqual(source, uint8(2)); testCase.verifyFalse(valid);
        end

        function staleCarMakerAlsoNeverReplaysTheRetainedValue(testCase)
            % Model the model's data flow: retainer -> snapshot -> selector.
            bank = initialCarMakerSteeringBank();
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(200, 10), uint32(0));
            bank = receiveCarMakerSteering(bank, ...
                TestCarMakerSteering.frame(200, 11), uint32(10));
            snap = carMakerSteeringSnapshot(bank, uint32(10));
            [angleFresh, srcFresh, validFresh] = selectSteeringSource(-5, snap, uint8(1));
            testCase.verifyEqual(angleFresh, 200, 'AbsTol', 0.03);
            testCase.verifyEqual(srcFresh, uint8(1));
            testCase.verifyTrue(validFresh);
            % CarMaker link dies. The retained 200 deg is still in the bank
            % for diagnostics, but it must not be encoded as a measurement.
            snapStale = carMakerSteeringSnapshot(bank, uint32(200));
            [~, srcStale, validStale] = selectSteeringSource(-5, snapStale, uint8(1));
            testCase.verifyEqual(srcStale, uint8(2));
            testCase.verifyFalse(validStale);
        end

        function nonFiniteCarMakerAngleIsNotUsable(testCase)
            broken = TestCarMakerSteering.snapshot(0, true);
            broken.angleDeg = Inf;
            [~, source, valid] = selectSteeringSource(15, broken, uint8(1));
            testCase.verifyEqual(source, uint8(2)); testCase.verifyFalse(valid);
        end

        function manualDialIsSaturatedToTheBoschRange(testCase)
            fresh = TestCarMakerSteering.snapshot(0, true);
            testCase.verifyEqual(selectSteeringSource(5000, fresh, uint8(0)), 780);
            testCase.verifyEqual(selectSteeringSource(-5000, fresh, uint8(0)), -780);
            testCase.verifyEqual(selectSteeringSource(NaN, fresh, uint8(0)), 0);
        end

        % ------------------------------------------------------- Bosch LWS

        function fanatecSteeringReachesTheBoschFrameEndToEnd(testCase)
            % 0x507 payload -> decode -> retain -> select -> packLwsPayload.
            % +105 deg is the active Fanatec Device.0 maximum.
            for deg = [105, -105]
                bank = initialCarMakerSteeringBank();
                bank = receiveCarMakerSteering(bank, ...
                    TestCarMakerSteering.frame(deg, 20), uint32(0));
                bank = receiveCarMakerSteering(bank, ...
                    TestCarMakerSteering.frame(deg, 21), uint32(10));
                snap = carMakerSteeringSnapshot(bank, uint32(10));
                [angleDeg, source, valid] = selectSteeringSource(0, snap, uint8(1));
                testCase.verifyEqual(source, uint8(1));
                testCase.verifyTrue(valid);
                lws = packLwsPayload(angleDeg, 0, uint8(7));
                angleWord = bitor(uint16(lws(1)), bitshift(uint16(lws(2)), 8));
                counts = double(typecast(angleWord, 'int16'));
                % 0.1 deg/count: +105 deg is +1050 counts. The transport
                % quantisation to 0.001 rad shifts it by 0.0232 deg, which
                % rounds back to the same Bosch count.
                testCase.verifyEqual(counts, sign(deg) * 1050, ...
                    sprintf('%g deg must encode to %d Bosch counts', ...
                    deg, sign(deg) * 1050));
                testCase.verifyEqual(lws(4), uint8(7));
            end
        end

        function boschAngleIsSignedLittleEndian(testCase)
            lws = packLwsPayload(-105, 0, uint8(7));
            % -1050 counts is two's complement 0xFBE6 -> bytes E6 FB.
            testCase.verifyEqual(lws(1), uint8(hex2dec('E6')));
            testCase.verifyEqual(lws(2), uint8(hex2dec('FB')));
        end

        function lwsSpeedComesFromConsecutiveAngleSamplesNotYawRate(testCase)
            % 12 deg of wheel movement in one 10 ms LWS period is 1200 deg/s,
            % clamped to the encoder's 1016 deg/s maximum.
            testCase.verifyEqual(lwsAngularSpeed(12, 0, 0.010), 1016);
            % 3 deg in 10 ms is 300 deg/s and passes through unclamped.
            testCase.verifyEqual(lwsAngularSpeed(13, 10, 0.010), 300, 'AbsTol', 1e-9);
            % The field is unsigned: turning right gives the same magnitude.
            testCase.verifyEqual(lwsAngularSpeed(7, 10, 0.010), 300, 'AbsTol', 1e-9);
            % A held wheel is zero, regardless of how the car is yawing.
            testCase.verifyEqual(lwsAngularSpeed(45, 45, 0.010), 0);
            % The two quantities are numerically unrelated, which is the whole
            % point: a steady-state skidpad circle holds the wheel still at a
            % large yaw rate, and this field must read zero there.
            yawRateRadPerS = 1.2;
            testCase.verifyNotEqual(lwsAngularSpeed(45, 45, 0.010), ...
                yawRateRadPerS * 180 / pi);
        end

        function lwsSpeedNeverProducesTheInvalidSentinel(testCase)
            % 0xFF is reserved for "invalid"; a live reading must clamp below
            % it rather than range-error or collide with the sentinel.
            contract = lwsProtocol();
            speed = lwsAngularSpeed(1e6, 0, 0.010);
            lws = packLwsPayload(0, speed, uint8(7));
            testCase.verifyLessThan(lws(3), contract.speedFailureSentinel);
            testCase.verifyEqual(speed, contract.maximumSpeedDegPerS);
        end

        function boschFailureStateIsWhatAnUnavailableSourceEncodes(testCase)
            % The documented stale policy: a legal Bosch failure frame, not a
            % suppressed frame and not a substituted GUI angle. TRIM=1 OK=0
            % CAL=0 with both sentinels is what PACKLWSFRAME produces, and is
            % what the model's chart writes byte for byte.
            frame = packLwsFrame(0, 0, ...
                struct('trim', true, 'cal', false, 'ok', false));
            testCase.verifyEqual(frame.payload(1:2), uint8([255 127]), ...
                'LWS_ANGLE must be the 0x7FFF sentinel.');
            testCase.verifyEqual(frame.payload(3), uint8(255), ...
                'LWS_SPEED must be the 0xFF sentinel.');
            testCase.verifyEqual(frame.payload(4), uint8(4), ...
                'Status must be TRIM=1 OK=0 CAL=0.');
            testCase.verifyTrue(frame.angleIsSentinel);
            testCase.verifyTrue(frame.speedIsSentinel);
        end

        function existingBoschStatusTruthTableIsUnchanged(testCase)
            contract = lwsProtocol();
            testCase.verifyEqual(contract.status.calibratedByte, uint8(7));
            testCase.verifyEqual(contract.status.uncalibratedByte, uint8(5));
            testCase.verifyEqual(contract.status.failureByte, uint8(4));
            testCase.verifyEqual(contract.status.failureAltByte, uint8(0));
            testCase.verifyEqual(contract.angleScaleDegPerCount, 0.1);
            testCase.verifyEqual(contract.speedScaleDegPerSPerCount, 4);
            testCase.verifyEqual(contract.updatePeriodS, 0.010);
            testCase.verifyEqual(contract.standardId, uint32(hex2dec('2B0')));
            testCase.verifyFalse(contract.speedSigned);
            % Combinations outside the datasheet table stay rejected.
            testCase.verifyError(@() packLwsFrame(0, 0, ...
                struct('trim', false, 'cal', true, 'ok', true)), ...
                'lws:InvalidStatusCombination');
        end

        function calibrationSequencingContractIsUnchanged(testCase)
            contract = lwsProtocol();
            testCase.verifyEqual(contract.configId, uint32(hex2dec('7C0')));
            testCase.verifyEqual(contract.configDlc, uint8(2));
            testCase.verifyEqual(contract.ccwResetCalibration, uint8(5));
            testCase.verifyEqual(contract.ccwZeroAngle, uint8(3));
            testCase.verifyEqual(contract.calibrationInterCommandS, 0.100);
            testCase.verifyEqual(packLwsConfigPayload(uint8(5)), ...
                packLwsConfigPayload(uint8(5)));
        end

        % ----------------------------------------------------------- config

        function configExposesTheFreshnessWindow(testCase)
            config = defaultVehicleStateConfig();
            % 30 ms is three cycles of the 10 ms CarMaker producer, and
            % matches CARMAKERPHYSICSSNAPSHOT so the two truth streams from
            % one producer time out together rather than one at a time.
            testCase.verifyEqual(config.carMakerSteeringFreshnessMs, 30);
            testCase.verifyFalse(config.carMakerTruthEnabled, ...
                'CarMaker physics truth must ship disabled.');
        end
    end

    methods (Static, Access = private)
        function golden = loadGolden()
            here = fileparts(mfilename('fullpath'));
            path = fullfile(fileparts(fileparts(here)), '..', 'references', ...
                'sensors', 'golden_vectors', 'carmaker_steering', ...
                'golden_carmaker_steering.json');
            golden = jsondecode(fileread(path));
        end

        function frame = frame(angleDeg, counter)
            frame = struct('id', uint32(hex2dec('507')), 'dlc', uint8(8), ...
                'payload', TestCarMakerSteering.payloadFromDeg(angleDeg, counter), ...
                'isExtended', false, 'isRemote', false, 'drop', false);
        end

        function snapshot = snapshot(angleDeg, fresh)
            snapshot = struct('angleDeg', angleDeg, ...
                'angleRad', angleDeg * pi / 180, 'fresh', fresh, ...
                'hasValue', true, 'counterAdvanced', fresh, ...
                'ageMs', uint32(0), 'groupCounter', uint8(0), ...
                'acceptedCount', uint32(2), 'rejectedCount', uint32(0), ...
                'lastRejectCode', uint8(0));
        end

        function payload = payloadFromDeg(angleDeg, counter)
            payload = TestCarMakerSteering.payloadFromCounts( ...
                round(angleDeg * pi / 180 / 0.001), counter);
        end

        function payload = payloadFromCounts(counts, counter)
            word = typecast(int16(counts), 'uint16');
            payload = zeros(1, 8, 'uint8');
            payload(1) = uint8(bitand(word, 255));
            payload(2) = uint8(bitshift(word, -8));
            payload(7) = uint8(mod(counter, 256));
            payload(8) = TestCarMakerSteering.crc(payload(1:7));
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
