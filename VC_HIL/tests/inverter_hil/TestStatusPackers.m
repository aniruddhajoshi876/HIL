classdef TestStatusPackers < matlab.unittest.TestCase
    methods (Test)
        function packs3X3GoldenBytes(testCase)
            status = TestStatusPackers.status3X3();
            status.state = uint8(2);
            status.ready = true;
            status.derating = true;
            status.maxAllowedCurrentA = 18.125;       % 0x244 counts
            status.actualTorqueNm = -10.5;            % 0xEB0 counts
            status.torqueSetpointNm = 20.25;          % 0x288 counts
            status.motorTemperatureC = -12.5;         % 0xF9C counts
            status.switchTemperatureC = 80;           % 0x500 counts

            expected = uint8([hex2dec('4E') hex2dec('24') ...
                hex2dec('B0') hex2dec('8E') hex2dec('28') ...
                hex2dec('9C') hex2dec('0F') hex2dec('50')]);
            testCase.verifyEqual(packStatus3X3(status), expected);
        end

        function packs3X5GoldenBytes(testCase)
            status = TestStatusPackers.status3X5();
            status.idSetpointA = 18.1875;       % 0x123 counts
            status.idActualA = -84.25;          % 0xABC counts
            status.iqSetpointA = 69.375;        % 0x456 counts
            status.iqActualA = -33.0625;        % 0xDEF counts
            status.speedRpm = -30293;           % 0x89AB counts

            expected = uint8([hex2dec('23') hex2dec('C1') ...
                hex2dec('AB') hex2dec('56') hex2dec('F4') ...
                hex2dec('DE') hex2dec('AB') hex2dec('89')]);
            testCase.verifyEqual(packStatus3X5(status), expected);
        end

        function decodes3X3GoldenBytes(testCase)
            % Decodes the SAME golden bytes PACKS3X3GOLDENBYTES asserts, so
            % this verifies the decoder against a fixed wire format rather
            % than against the packer -- a shared bug in both would not pass.
            payload = uint8([hex2dec('4E') hex2dec('24') ...
                hex2dec('B0') hex2dec('8E') hex2dec('28') ...
                hex2dec('9C') hex2dec('0F') hex2dec('50')]);

            status = decodeStatus3X3(payload);
            testCase.verifyEqual(status.state, 2);
            testCase.verifyTrue(status.ready);
            testCase.verifyTrue(status.derating);
            testCase.verifyEqual(status.maxAllowedCurrentA, 18.125);
            testCase.verifyEqual(status.actualTorqueNm, -10.5);
            testCase.verifyEqual(status.torqueSetpointNm, 20.25);
            testCase.verifyEqual(status.motorTemperatureC, -12.5);
            testCase.verifyEqual(status.switchTemperatureC, 80);
        end

        function decodes3X5GoldenBytes(testCase)
            payload = uint8([hex2dec('23') hex2dec('C1') ...
                hex2dec('AB') hex2dec('56') hex2dec('F4') ...
                hex2dec('DE') hex2dec('AB') hex2dec('89')]);

            status = decodeStatus3X5(payload);
            testCase.verifyEqual(status.idSetpointA, 18.1875);
            testCase.verifyEqual(status.idActualA, -84.25);
            testCase.verifyEqual(status.iqSetpointA, 69.375);
            testCase.verifyEqual(status.iqActualA, -33.0625);
            testCase.verifyEqual(status.speedRpm, -30293);
        end

        function roundTripsExactlyRepresentableValues(testCase)
            % Every value here is exactly representable at its field scale,
            % so pack->decode must be lossless. Values that are not on a
            % scale boundary quantise instead; that is covered separately by
            % QUANTISESVALUESOFFTHESCALEBOUNDARY.
            status = TestStatusPackers.status3X3();
            status.state = uint8(1);
            status.ready = true;
            status.derating = false;
            status.maxAllowedCurrentA = 7.5;
            status.actualTorqueNm = -0.25;
            status.torqueSetpointNm = 63.96875;
            status.motorTemperatureC = 25.125;
            status.switchTemperatureC = -40.0625;

            decoded = decodeStatus3X3( ...
                packStatus3X3(status));
            testCase.verifyEqual(decoded.state, double(status.state));
            testCase.verifyEqual(decoded.ready, logical(status.ready));
            testCase.verifyEqual(decoded.derating, logical(status.derating));
            testCase.verifyEqual(decoded.maxAllowedCurrentA, ...
                status.maxAllowedCurrentA);
            testCase.verifyEqual(decoded.actualTorqueNm, ...
                status.actualTorqueNm);
            testCase.verifyEqual(decoded.torqueSetpointNm, ...
                status.torqueSetpointNm);
            testCase.verifyEqual(decoded.motorTemperatureC, ...
                status.motorTemperatureC);
            testCase.verifyEqual(decoded.switchTemperatureC, ...
                status.switchTemperatureC);

            wide = TestStatusPackers.status3X5();
            % -128 is exactly the signed 12-bit floor at 1/16 A (-2048
            % counts). One step lower saturates, which is why the round trip
            % must be asserted at the boundary, not past it.
            wide.idSetpointA = -128;
            wide.idActualA = 0;
            wide.iqSetpointA = 12.5;
            wide.iqActualA = -0.0625;
            wide.speedRpm = 12000;

            decodedWide = decodeStatus3X5( ...
                packStatus3X5(wide));
            testCase.verifyEqual(decodedWide.idSetpointA, wide.idSetpointA);
            testCase.verifyEqual(decodedWide.idActualA, wide.idActualA);
            testCase.verifyEqual(decodedWide.iqSetpointA, wide.iqSetpointA);
            testCase.verifyEqual(decodedWide.iqActualA, wide.iqActualA);
            testCase.verifyEqual(decodedWide.speedRpm, wide.speedRpm);
        end

        function quantisesValuesOffTheScaleBoundary(testCase)
            % A value between two representable counts must come back as the
            % nearest one. The GUI shows the wire value, not the commanded
            % double, and this pins that behaviour so it is never mistaken
            % for a decoder defect.
            status = TestStatusPackers.status3X3();
            status.actualTorqueNm = 1 / 64;   % half of the 1/32 Nm step

            decoded = decodeStatus3X3( ...
                packStatus3X3(status));
            testCase.verifyEqual(decoded.actualTorqueNm, 1 / 32);
        end

        function decodersRejectMalformedPayloads(testCase)
            bad = {uint8(zeros(1, 7)), uint8(zeros(8, 1)), ...
                zeros(1, 8), 'eightchr'};
            for k = 1:numel(bad)
                testCase.verifyError( ...
                    @() decodeStatus3X3(bad{k}), ...
                    'inverterhil:MalformedPayload');
                testCase.verifyError( ...
                    @() decodeStatus3X5(bad{k}), ...
                    'inverterhil:MalformedPayload');
                testCase.verifyError( ...
                    @() decodeSystemStatus(bad{k}), ...
                    'inverterhil:MalformedPayload');
            end
        end

        function decodesSystemStatusGoldenBytes(testCase)
            % The SAME golden bytes PACKSSYSTEMSTATUSGOLDENBYTES asserts, so
            % the decoder is checked against a fixed wire format rather than
            % against the packer. Byte 6 = 0x05 sets bits 48 and 50, i.e.
            % dcLink12AboveMinimum and controlEnable but not the other two.
            payload = uint8([hex2dec('10') hex2dec('64') ...
                hex2dec('A0') hex2dec('57') hex2dec('80') ...
                hex2dec('14') hex2dec('05') 0]);

            status = decodeSystemStatus(payload);
            testCase.verifyEqual(status.dcLink12V, 400.25);
            testCase.verifyEqual(status.dcLink34V, 350.5);
            testCase.verifyEqual(status.switchingFrequencyKHz, 10.25);
            testCase.verifyTrue(status.dcLink12AboveMinimum);
            testCase.verifyFalse(status.dcLink34AboveMinimum);
            testCase.verifyTrue(status.controlEnable);
            testCase.verifyFalse(status.controlDisable);
        end

        function roundTripsSystemStatusAcrossFlagCombinations(testCase)
            % Each flag occupies its own bit, so a bug that swapped or
            % aliased two of them survives any single-flag test. Sweeping all
            % 16 combinations pins each bit to its own field.
            for mask = 0:15
                status = TestStatusPackers.systemStatus();
                status.dcLink12V = 0;
                status.dcLink34V = 1023.984375;   % 0xFFFF counts, the ceiling
                status.switchingFrequencyKHz = 8;
                status.dcLink12AboveMinimum = logical(bitget(mask, 1));
                status.dcLink34AboveMinimum = logical(bitget(mask, 2));
                status.controlEnable = logical(bitget(mask, 3));
                status.controlDisable = logical(bitget(mask, 4));

                decoded = decodeSystemStatus( ...
                    packSystemStatus(status));
                testCase.verifyEqual(decoded.dcLink12V, status.dcLink12V);
                testCase.verifyEqual(decoded.dcLink34V, status.dcLink34V);
                testCase.verifyEqual(decoded.switchingFrequencyKHz, ...
                    status.switchingFrequencyKHz);
                testCase.verifyEqual(decoded.dcLink12AboveMinimum, ...
                    status.dcLink12AboveMinimum);
                testCase.verifyEqual(decoded.dcLink34AboveMinimum, ...
                    status.dcLink34AboveMinimum);
                testCase.verifyEqual(decoded.controlEnable, ...
                    status.controlEnable);
                testCase.verifyEqual(decoded.controlDisable, ...
                    status.controlDisable);
            end
        end

        function systemStatusDecoderIgnoresUnassignedBits(testCase)
            % PACKSYSTEMSTATUS never writes bits 52-63. A frame with those
            % bits set -- which a real transmitter may legitimately use for
            % fields this protocol revision does not define -- must not
            % perturb any field the decoder does report.
            clean = uint8([hex2dec('10') hex2dec('64') ...
                hex2dec('A0') hex2dec('57') hex2dec('80') ...
                hex2dec('14') hex2dec('05') 0]);
            dirty = clean;
            dirty(7) = bitor(dirty(7), uint8(hex2dec('F0')));
            dirty(8) = uint8(hex2dec('FF'));

            testCase.verifyEqual(decodeSystemStatus(dirty), ...
                decodeSystemStatus(clean));
        end

        function packsSystemStatusGoldenBytes(testCase)
            status = TestStatusPackers.systemStatus();
            status.dcLink12V = 400.25;                  % 0x6410 counts
            status.dcLink34V = 350.5;                   % 0x57A0 counts
            status.switchingFrequencyKHz = 10.25;       % 0x1480 counts
            status.dcLink12AboveMinimum = true;
            status.dcLink34AboveMinimum = false;
            status.controlEnable = true;
            status.controlDisable = false;

            expected = uint8([hex2dec('10') hex2dec('64') ...
                hex2dec('A0') hex2dec('57') hex2dec('80') ...
                hex2dec('14') hex2dec('05') 0]);
            testCase.verifyEqual(packSystemStatus(status), expected);
        end

        function packsCompleteOrderedCycleWithGoldenBytes(testCase)
            channels = repmat(struct( ...
                'status3X3', TestStatusPackers.status3X3(), ...
                'status3X5', TestStatusPackers.status3X5()), 1, 4);

            channels(1).status3X3.state = uint8(2);
            channels(1).status3X3.ready = true;
            channels(1).status3X3.derating = true;
            channels(1).status3X3.maxAllowedCurrentA = 18.125;
            channels(1).status3X3.actualTorqueNm = -10.5;
            channels(1).status3X3.torqueSetpointNm = 20.25;
            channels(1).status3X3.motorTemperatureC = -12.5;
            channels(1).status3X3.switchTemperatureC = 80;
            channels(1).status3X5.idSetpointA = 18.1875;
            channels(1).status3X5.idActualA = -84.25;
            channels(1).status3X5.iqSetpointA = 69.375;
            channels(1).status3X5.iqActualA = -33.0625;
            channels(1).status3X5.speedRpm = -30293;

            channels(2).status3X3.state = uint8(1);

            channels(3).status3X3.ready = true;
            channels(3).status3X3.maxAllowedCurrentA = 1 / 32;
            channels(3).status3X5.idSetpointA = 1 / 16;

            channels(4).status3X3.state = uint8(3);
            channels(4).status3X3.derating = true;
            channels(4).status3X3.maxAllowedCurrentA = 2 / 32;
            channels(4).status3X3.actualTorqueNm = -1 / 32;
            channels(4).status3X3.motorTemperatureC = -1 / 8;
            channels(4).status3X5.idSetpointA = -1 / 16;
            channels(4).status3X5.iqSetpointA = 1 / 16;
            channels(4).status3X5.speedRpm = -1;

            system = TestStatusPackers.systemStatus();
            system.dcLink12V = 400.25;
            system.dcLink34V = 350.5;
            system.switchingFrequencyKHz = 10.25;
            system.dcLink12AboveMinimum = true;
            system.controlEnable = true;

            expectedIds = uint32([hex2dec('383') hex2dec('385') ...
                hex2dec('393') hex2dec('395') hex2dec('3A3') ...
                hex2dec('3A5') hex2dec('3B3') hex2dec('3B5') ...
                hex2dec('400')]);
            expectedPayloads = uint8([ ...
                78 36 176 142 40 156 15 80; ...
                35 193 171 86 244 222 171 137; ...
                1 0 0 0 0 0 0 0; ...
                0 0 0 0 0 0 0 0; ...
                20 0 0 0 0 0 0 0; ...
                1 0 0 0 0 0 0 0; ...
                43 0 255 15 0 255 15 0; ...
                255 15 0 1 0 0 255 255; ...
                16 100 160 87 128 20 5 0]);

            cycle = packStatusCycle(channels, system);
            testCase.verifyEqual(cycle.ids, expectedIds);
            testCase.verifyEqual(cycle.dlc, repmat(uint8(8), 1, 9));
            testCase.verifyEqual(cycle.payloads, expectedPayloads);
        end

        function saturatesBeforeNarrowingWithoutWrap(testCase)
            status3X3 = TestStatusPackers.status3X3();
            status3X3.state = uint8(3);
            status3X3.maxAllowedCurrentA = realmax;
            status3X3.actualTorqueNm = -realmax;
            status3X3.torqueSetpointNm = realmax;
            status3X3.motorTemperatureC = -realmax;
            status3X3.switchTemperatureC = realmax;
            expected3X3 = uint8([243 255 0 248 127 0 248 127]);
            testCase.verifyEqual( ...
                packStatus3X3(status3X3), expected3X3);

            status3X5 = TestStatusPackers.status3X5();
            status3X5.idSetpointA = realmax;
            status3X5.idActualA = -realmax;
            status3X5.iqSetpointA = realmax;
            status3X5.iqActualA = -realmax;
            status3X5.speedRpm = realmax;
            expected3X5 = uint8([255 7 128 255 7 128 255 127]);
            testCase.verifyEqual( ...
                packStatus3X5(status3X5), expected3X5);

            system = TestStatusPackers.systemStatus();
            system.dcLink12V = -realmax;
            system.dcLink34V = realmax;
            system.switchingFrequencyKHz = realmax;
            system.dcLink12AboveMinimum = true;
            system.dcLink34AboveMinimum = true;
            system.controlEnable = true;
            system.controlDisable = true;
            expectedSystem = uint8([0 0 255 255 255 255 15 0]);
            testCase.verifyEqual( ...
                packSystemStatus(system), expectedSystem);
        end

        function rejectsNonfiniteAndInvalidEnumInputs(testCase)
            status3X3 = TestStatusPackers.status3X3();
            status3X3.actualTorqueNm = NaN;
            testCase.verifyError(@() packStatus3X3(status3X3), ...
                'inverterhil:NonFinite');
            status3X3 = TestStatusPackers.status3X3();
            status3X3.ready = 2;
            testCase.verifyError(@() packStatus3X3(status3X3), ...
                'inverterhil:InvalidEnum');

            status3X5 = TestStatusPackers.status3X5();
            status3X5.iqActualA = Inf;
            testCase.verifyError(@() packStatus3X5(status3X5), ...
                'inverterhil:NonFinite');

            system = TestStatusPackers.systemStatus();
            system.switchingFrequencyKHz = -Inf;
            testCase.verifyError(@() packSystemStatus(system), ...
                'inverterhil:NonFinite');
            system = TestStatusPackers.systemStatus();
            system.busy = true;
            system.controlDisable = NaN;
            testCase.verifyError(@() packSystemStatus(system), ...
                'inverterhil:InvalidEnum');
        end

        function cyclePackingPreservesChannelIsolation(testCase)
            channels = repmat(struct( ...
                'status3X3', TestStatusPackers.status3X3(), ...
                'status3X5', TestStatusPackers.status3X5()), 1, 4);
            system = TestStatusPackers.systemStatus();
            baseline = packStatusCycle(channels, system);

            changed = channels;
            changed(2).status3X3.actualTorqueNm = 5;
            torqueCycle = packStatusCycle(changed, system);
            changedRows = find(any(torqueCycle.payloads ~= baseline.payloads, 2));
            testCase.verifyEqual(changedRows, 3);

            changed = channels;
            changed(3).status3X5.speedRpm = -500;
            speedCycle = packStatusCycle(changed, system);
            changedRows = find(any(speedCycle.payloads ~= baseline.payloads, 2));
            testCase.verifyEqual(changedRows, 6);
            testCase.verifyEqual(speedCycle.ids, baseline.ids);
        end
    end

    methods (Static, Access = private)
        function status = status3X3()
            status = struct( ...
                'state', uint8(0), ...
                'ready', false, ...
                'derating', false, ...
                'maxAllowedCurrentA', 0, ...
                'actualTorqueNm', 0, ...
                'torqueSetpointNm', 0, ...
                'motorTemperatureC', 0, ...
                'switchTemperatureC', 0);
        end

        function status = status3X5()
            status = struct( ...
                'idSetpointA', 0, ...
                'idActualA', 0, ...
                'iqSetpointA', 0, ...
                'iqActualA', 0, ...
                'speedRpm', 0);
        end

        function status = systemStatus()
            status = struct( ...
                'dcLink12V', 0, ...
                'dcLink34V', 0, ...
                'switchingFrequencyKHz', 0, ...
                'dcLink12AboveMinimum', false, ...
                'dcLink34AboveMinimum', false, ...
                'controlEnable', false, ...
                'controlDisable', false);
        end
    end
end
