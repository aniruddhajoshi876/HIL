classdef TestCarMakerSteering < matlab.unittest.TestCase
    %TESTCARMAKERSTEERING Fanatec -> CarMaker -> 0x507 -> Speedgoat -> selector
    %   -> Bosch LWS 0x2B0. Covers the transport decode (golden vectors,
    %   boundaries, CRC, DLC, reserved, range), the coherent retainer
    %   (fresh/stale/counter), the source selector (CarMaker vs GUI dial,
    %   fallback, no unsafe jump), and the final Bosch frame.

    properties (Constant)
        Golden = TestCarMakerSteering.loadGolden();
    end

    methods (Test)
        function decoderMatchesHandDerivedGoldenVectors(testCase)
            vectors = TestCarMakerSteering.Golden.vectors.accepted;
            for index = 1:numel(vectors)
                v = vectors(index);
                payload = uint8(v.payloadBytes(:).');
                [ok, decoded, reason] = decodeCarMakerSteeringFrame( ...
                    uint32(hex2dec('507')), uint8(8), payload, false, false);
                testCase.verifyTrue(ok, sprintf('%s rejected: %s', v.name, reason));
                testCase.verifyEqual(decoded.angleDeg, v.angleDeg, 'AbsTol', 1e-9, ...
                    sprintf('%s angle', v.name));
                testCase.verifyEqual(decoded.speedDegPerSec, v.speedDegPerSec, ...
                    'AbsTol', 1e-9, sprintf('%s speed', v.name));
                testCase.verifyEqual(decoded.aliveCounter, uint8(v.aliveCounter), ...
                    sprintf('%s counter', v.name));
            end
        end

        function decoderRejectsMalformedAndOutOfRange(testCase)
            good = TestCarMakerSteering.payload(12.5, 30.0, 4);
            % wrong DLC
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(7), good, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'wrong_dlc');
            % wrong ID
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('508')), ...
                uint8(8), good, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'wrong_id');
            % extended / remote
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), good, true, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'extended_frame');
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), good, false, true);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'remote_frame');
            % reserved non-zero
            bad = good; bad(5) = uint8(1); bad(8) = TestCarMakerSteering.crc(bad(1:7));
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), bad, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'reserved_nonzero');
            % CRC failure
            bad = good; bad(8) = bitxor(bad(8), uint8(1));
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), bad, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'integrity_failure');
            % out-of-range angle (> Bosch 780 deg)
            over = TestCarMakerSteering.payload(0, 0, 1);
            word = typecast(int16(9000), 'uint16');
            over(1) = uint8(bitand(word, 255)); over(2) = uint8(bitshift(word, -8));
            over(8) = TestCarMakerSteering.crc(over(1:7));
            [ok, ~, r] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), over, false, false);
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'out_of_range');
        end

        function minZeroMaxAndSignRoundTrip(testCase)
            for angleDeg = [-780, -0.1, 0, 0.1, 780]
                payload = TestCarMakerSteering.payload(angleDeg, 0, 1);
                [ok, decoded] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                    uint8(8), payload, false, false);
                testCase.verifyTrue(ok);
                testCase.verifyEqual(decoded.angleDeg, angleDeg, 'AbsTol', 1e-9);
            end
            % Left is positive: +30 deg encodes to a positive int16.
            payload = TestCarMakerSteering.payload(30, 0, 1);
            word = bitor(uint16(payload(1)), bitshift(uint16(payload(2)), 8));
            testCase.verifyGreaterThan(double(typecast(word, 'int16')), 0);
        end

        function retainerProvesFreshnessAndCounterAdvance(testCase)
            bank = initialCarMakerSteeringBank();
            f = @(a, s, c) struct('id', uint32(hex2dec('507')), 'dlc', uint8(8), ...
                'payload', TestCarMakerSteering.payload(a, s, c), ...
                'isExtended', false, 'isRemote', false, 'drop', false);
            % First valid frame: retained but presence alone is not liveness.
            [bank, ok] = receiveCarMakerSteering(bank, f(10, 5, 40), uint32(0));
            testCase.verifyTrue(ok);
            snap = carMakerSteeringSnapshot(bank, uint32(0));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyFalse(snap.counterAdvanced);
            % Second, counter +1: now fresh.
            [bank, ok] = receiveCarMakerSteering(bank, f(12, 6, 41), uint32(10));
            testCase.verifyTrue(ok);
            snap = carMakerSteeringSnapshot(bank, uint32(10));
            testCase.verifyTrue(snap.fresh);
            testCase.verifyTrue(snap.counterAdvanced);
            testCase.verifyEqual(snap.angleDeg, 12, 'AbsTol', 1e-9);
            % Age beyond the 30 ms window: stale, value still retained.
            snap = carMakerSteeringSnapshot(bank, uint32(45));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyEqual(snap.ageMs, uint32(35));
            testCase.verifyEqual(snap.angleDeg, 12, 'AbsTol', 1e-9);
            % Frozen-but-repeating sender (same counter): not fresh.
            [bank, ok] = receiveCarMakerSteering(bank, f(12, 6, 41), uint32(50));
            testCase.verifyTrue(ok);
            snap = carMakerSteeringSnapshot(bank, uint32(50));
            testCase.verifyFalse(snap.fresh);
            testCase.verifyFalse(snap.counterAdvanced);
            % Counter wrap 255 -> 0 counts as advancing.
            bank2 = initialCarMakerSteeringBank();
            bank2 = receiveCarMakerSteering(bank2, f(1, 1, 255), uint32(0));
            bank2 = receiveCarMakerSteering(bank2, f(2, 2, 0), uint32(10));
            testCase.verifyTrue(carMakerSteeringSnapshot(bank2, uint32(10)).counterAdvanced);
            % Injected drop leaves the retained value untouched.
            dropped = f(99, 99, 42); dropped.drop = true;
            [bank, ok, r] = receiveCarMakerSteering(bank, dropped, uint32(55));
            testCase.verifyFalse(ok); testCase.verifyEqual(r, 'injected_drop');
            testCase.verifyEqual(bank.angleDeg, 12, 'AbsTol', 1e-9);
        end

        function selectorPrefersFreshCarMakerAndFallsBackToDial(testCase)
            fresh = struct('fresh', true, 'hasValue', true, ...
                'angleDeg', -47.3, 'speedDegPerSec', 88);
            [a, s, src, cmFresh] = selectSteeringSource(15, fresh, true);
            testCase.verifyEqual(a, -47.3, 'AbsTol', 1e-9);
            testCase.verifyEqual(s, 88, 'AbsTol', 1e-9);
            testCase.verifyEqual(src, uint8(1));
            testCase.verifyTrue(cmFresh);
            % Enabled but stale -> GUI dial, source 2, not neutral / fault.
            stale = fresh; stale.fresh = false;
            [a, s, src, cmFresh] = selectSteeringSource(15, stale, true);
            testCase.verifyEqual(a, 15); testCase.verifyEqual(s, 0);
            testCase.verifyEqual(src, uint8(2)); testCase.verifyFalse(cmFresh);
            % Disabled -> GUI dial, source 0, 0x507 ignored entirely.
            [a, ~, src] = selectSteeringSource(15, fresh, false);
            testCase.verifyEqual(a, 15); testCase.verifyEqual(src, uint8(0));
            % GUI value is saturated to the Bosch range on every path.
            [a, ~, src] = selectSteeringSource(5000, stale, true);
            testCase.verifyEqual(a, 780); testCase.verifyEqual(src, uint8(2));
            % Non-finite CarMaker angle is not usable even if "fresh".
            broken = fresh; broken.angleDeg = Inf;
            [~, ~, src] = selectSteeringSource(15, broken, true);
            testCase.verifyEqual(src, uint8(2));
        end

        function switchingSourceNeverReplaysAStaleRetainedValue(testCase)
            % Model the model's data flow: retainer -> snapshot -> selector.
            bank = initialCarMakerSteeringBank();
            f = @(a, c) struct('id', uint32(hex2dec('507')), 'dlc', uint8(8), ...
                'payload', TestCarMakerSteering.payload(a, 0, c), ...
                'isExtended', false, 'isRemote', false, 'drop', false);
            bank = receiveCarMakerSteering(bank, f(200, 10), uint32(0));
            bank = receiveCarMakerSteering(bank, f(200, 11), uint32(10));
            snap = carMakerSteeringSnapshot(bank, uint32(10));
            [angleFresh, ~, srcFresh] = selectSteeringSource(-5, snap, true);
            testCase.verifyEqual(angleFresh, 200, 'AbsTol', 1e-9);
            testCase.verifyEqual(srcFresh, uint8(1));
            % CarMaker link dies: snapshot goes stale, selector hands control
            % straight to the live GUI dial value -- it must NOT keep emitting
            % the retained 200 deg.
            snapStale = carMakerSteeringSnapshot(bank, uint32(200));
            [angleStale, ~, srcStale] = selectSteeringSource(-5, snapStale, true);
            testCase.verifyEqual(angleStale, -5);
            testCase.verifyEqual(srcStale, uint8(2));
        end

        function selectedAngleFeedsTheBoschLwsFrameEndToEnd(testCase)
            % 0x507 payload -> decode -> select -> packLwsPayload -> 0x2B0.
            payload = TestCarMakerSteering.payload(123.4, 40, 5);
            [ok, decoded] = decodeCarMakerSteeringFrame(uint32(hex2dec('507')), ...
                uint8(8), payload, false, false);
            testCase.verifyTrue(ok);
            snap = struct('fresh', true, 'hasValue', true, ...
                'angleDeg', decoded.angleDeg, 'speedDegPerSec', decoded.speedDegPerSec);
            [angleDeg, ~, src] = selectSteeringSource(0, snap, true);
            testCase.verifyEqual(src, uint8(1));
            % On the target the LWS speed is derived from successive angle
            % samples; here just confirm the selected angle packs to the
            % Bosch 0.1 deg/count wire value with a calibrated status byte.
            lws = packLwsPayload(angleDeg, 0, uint8(7));
            angleWord = bitor(uint16(lws(1)), bitshift(uint16(lws(2)), 8));
            testCase.verifyEqual(double(typecast(angleWord, 'int16')), 1234);
            testCase.verifyEqual(lws(4), uint8(7));
        end

        function configExposesTheBuildTimeGate(testCase)
            config = defaultVehicleStateConfig();
            testCase.verifyFalse(config.carMakerSteeringEnabled, ...
                'CarMaker steering must ship disabled, like carMakerTruthEnabled.');
            testCase.verifyEqual(config.carMakerSteeringFreshnessMs, 30);
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

        function payload = payload(angleDeg, speedDegPerSec, counter)
            angleRaw = int16(round(angleDeg / 0.1));
            speedRaw = int16(round(speedDegPerSec / 0.5));
            aw = typecast(angleRaw, 'uint16');
            sw = typecast(speedRaw, 'uint16');
            payload = zeros(1, 8, 'uint8');
            payload(1) = uint8(bitand(aw, 255));
            payload(2) = uint8(bitshift(aw, -8));
            payload(3) = uint8(bitand(sw, 255));
            payload(4) = uint8(bitshift(sw, -8));
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
