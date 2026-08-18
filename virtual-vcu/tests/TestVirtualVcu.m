classdef TestVirtualVcu < matlab.unittest.TestCase
    methods (Test)
        function calibrationEndpoints(testCase)
            c = virtualvcu.config();
            [p, ok] = virtualvcu.rawToPedal(c.throttleRestRaw(1), 'throttle', 1);
            testCase.verifyTrue(ok); testCase.verifyEqual(p, 0, 'AbsTol', 1e-12);
            [p, ok] = virtualvcu.rawToPedal(c.throttlePressedRaw(1), 'throttle', 1);
            testCase.verifyTrue(ok); testCase.verifyEqual(p, 100, 'AbsTol', 1e-12);
            mid = round((c.throttleRestRaw(1) + c.throttlePressedRaw(1)) / 2);
            [p, ok] = virtualvcu.rawToPedal(mid, 'throttle', 1);
            testCase.verifyTrue(ok); testCase.verifyEqual(p, 50, 'AbsTol', 0.01);
        end
        function voltageRawRoundTrip(testCase)
            testCase.verifyEqual(virtualvcu.voltageToRaw(0), uint16(0));
            testCase.verifyEqual(virtualvcu.voltageToRaw(5), uint16(65535));
            testCase.verifyEqual(virtualvcu.voltageToRaw(2.5), uint16(32768));
        end
        function goldenControlBytes(testCase)
            payload = virtualvcu.packControlFrame(1, true, 18000, 12.5);
            testCase.verifyEqual(payload, uint8([1 0 80 70 128 12 0 0]));
            testCase.verifyEqual(virtualvcu.config().controlIds(1), uint32(hex2dec('186')));
        end
        function goldenPedalBytes(testCase)
            testCase.verifyEqual(virtualvcu.packPedalFrame(12.5, 1), ...
                uint8([13 138 2 138 2 0 0 0]));
            testCase.verifyEqual(virtualvcu.config().pedalCanId, uint32(501));
        end
        function lvOnUsesMeasuredInputsOnly(testCase)
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw] / c.adcFullScale * c.io183FullScaleV;
            out = virtualvcu.step(volts, true);
            testCase.verifyEqual(out.state, 'LV_ON');
            testCase.verifyTrue(all(out.valid));
            testCase.verifyEqual(out.pedalPct(1), 0, 'AbsTol', 0.1);
            testCase.verifyEqual(size(out.controlPayloads), [4 8]);
        end
        function hardwareSeparationIsExplicit(testCase)
            c = virtualvcu.config();
            testCase.verifyEqual(c.moduleId, 2);
            testCase.verifyEqual(c.canChannel, 2);
            testCase.verifyEqual(c.canPort, 'A');
            testCase.verifyNotEqual(c.moduleId, 1);
            testCase.verifyNotEqual(c.canChannel, 1);
        end
        function suppliedDbcMatchesFirmwareContract(testCase)
            dbc = virtualvcu.verifyDbcContract();
            testCase.verifyEqual(dbc.torqueScaleNmPerCount, 1 / 256);
            testCase.verifyEqual(dbc.controlIds, ...
                uint32([390 406 422 438]));
            testCase.verifyEqual(dbc.statusIds, ...
                uint32([899 901 915 917 931 933 947 949 1024]));
        end
        function stateMachineUsesDigitalInputs(testCase)
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakePressedRaw] / c.adcFullScale * c.io183FullScaleV;
            di = false(1,8); di(1) = true;
            out = virtualvcu.step(volts, true, di);
            testCase.verifyEqual(out.state, 'PRECHARGING');
            ctx = out.context; ctx.ticks = c.prechargeTicks - 1;
            di(1) = false; out = virtualvcu.step(volts, true, di, [], ctx);
            testCase.verifyEqual(out.state, 'ENABLE');
            di(2) = true; out = virtualvcu.step(volts, true, di, [], out.context);
            testCase.verifyEqual(out.state, 'BUZZING');
            ctx = out.context; ctx.ticks = c.buzzingTicks - 1;
            out = virtualvcu.step(volts, true, di, [], ctx);
            testCase.verifyEqual(out.state, 'RTD');
            testCase.verifyEqual(out.controlPayloads(1,1), uint8(1));
        end
        function deployedChartScriptReachesRtdOnBrakeHeld(testCase)
            % Regression test for a real bug: virtualVcuDeployStep.m (the
            % script deployed into the Stateflow chart, maintained
            % separately from +virtualvcu/step.m used above) computed b1/b2
            % as fractions in [0,1] but compared mean([b1 b2]) against the
            % literal 25 -- a value only reachable by a percent-scale
            % quantity. A fraction can never reach 25, so ENABLE never
            % advanced to BUZZING/RTD no matter how hard the brake was
            % pressed. +virtualvcu/step.m was not affected: it keeps b1/b2
            % in percent scale, so its identical-looking ">= 25" check was
            % already correct. Only a test that calls the deployed chart
            % script itself, not step.m, can catch this class of bug.
            here = fileparts(mfilename('fullpath'));
            modelsDir = fullfile(fileparts(here), 'models');
            testCase.applyFixture( ...
                matlab.unittest.fixtures.PathFixture(modelsDir));
            clear('virtualVcuDeployStep'); %#ok<CLFUN>

            c = virtualvcu.config();
            % virtualVcuDeployStep.m takes u(1:4) as volts, converted back to
            % raw counts internally on the firmware's real 3.3 V ADC
            % reference (PINOUTS.md S4.2: ADS7066 VREF, ADS_VREF_V=3.3) --
            % NOT c.io183FullScaleV (5 V), which is the IO183 channel's own
            % electrical range and only applies to the separate host/SIL
            % voltageToRaw.m round trip that step.m (above) uses. Using
            % c.io183FullScaleV here would regenerate the pre-fix scale bug
            % this test exists to catch, just relocated into the test itself.
            toVolts = @(raw) double(raw) / c.adcFullScale * 3.3;
            throttleRestV = toVolts(c.throttleRestRaw(1));
            brakePressedV = toVolts(c.brakePressedRaw(1));

            u = zeros(17, 1);
            u(1) = throttleRestV; u(2) = throttleRestV;
            u(3) = brakePressedV; u(4) = brakePressedV;

            u(5) = 1; % precharge button
            payloads = virtualVcuDeployStep(u);
            testCase.verifyEqual(payloads(41), uint8(1)); % PRECHARGING

            u(5) = 0;
            for k = 1:double(c.prechargeTicks)
                payloads = virtualVcuDeployStep(u);
            end
            testCase.verifyEqual(payloads(41), uint8(2), ...
                'Expected ENABLE after the 7.5 s precharge delay.');

            u(6) = 1; % main button, brake already held above
            payloads = virtualVcuDeployStep(u);
            testCase.verifyEqual(payloads(41), uint8(3), ...
                ['Expected BUZZING once main button is pressed with ' ...
                'brake held -- this is exactly the transition the ' ...
                '25-vs-0.25 scale bug silently blocked.']);

            for k = 1:double(c.buzzingTicks)
                payloads = virtualVcuDeployStep(u);
            end
            testCase.verifyEqual(payloads(41), uint8(4)); % RTD
        end

        function torqueRequestNmIsNamedAndGatedLikeControlPayloads(testCase)
            % out.torqueRequestNm (host/SIL step.m) must be the same
            % quantity packed into controlPayloads -- named, not a separate
            % derivation -- and zero whenever drive is false, exactly like
            % those payloads already are.
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakePressedRaw] / c.adcFullScale * c.io183FullScaleV;
            volts2 = [c.throttlePressedRaw c.brakePressedRaw] / c.adcFullScale * c.io183FullScaleV;
            di = false(1,8); di(1) = true;
            out = virtualvcu.step(volts, true, di);
            testCase.verifyEqual(out.torqueRequestNm, 0, ...
                'Not RTD yet: torque request must be zero.');

            ctx = out.context; ctx.ticks = c.prechargeTicks - 1;
            di(1) = false; out = virtualvcu.step(volts, true, di, [], ctx);
            di(2) = true; out = virtualvcu.step(volts, true, di, [], out.context);
            ctx = out.context; ctx.ticks = c.buzzingTicks - 1;
            out = virtualvcu.step(volts, true, di, [], ctx);
            testCase.verifyEqual(out.state, 'RTD');
            testCase.verifyEqual(out.torqueRequestNm, 0, ...
                'RTD but throttle still at rest: expected zero torque request.');

            out = virtualvcu.step(volts2, true, di, [], out.context);
            testCase.verifyEqual(out.state, 'RTD');
            testCase.verifyGreaterThan(out.torqueRequestNm, 0, ...
                'RTD with throttle pressed: expected nonzero torque request.');
            expectedNm = 15 * mean(out.pedalPct(1:2)) / 100;
            testCase.verifyEqual(out.torqueRequestNm, expectedNm, 'AbsTol', 1e-9);
            % controlPayloads' torque bytes (5-6 of each 8-byte frame) must
            % decode back to the same Nm value at the DBC's 1/256 Nm/count
            % scale (suppliedDbcMatchesFirmwareContract already asserts
            % this scale factor).
            countsFromPayload = double(out.controlPayloads(1,5)) + ...
                256 * double(out.controlPayloads(1,6));
            testCase.verifyEqual(countsFromPayload / 256, out.torqueRequestNm, ...
                'AbsTol', 1/256);

            out = virtualvcu.step(volts2, false, di, [], out.context);
            testCase.verifyEqual(out.torqueRequestNm, 0, ...
                'Disabled: torque request must be zero.');
        end

        function deployedChartTorqueRequestNmMatchesControlPayload(testCase)
            % Same property as the host/SIL test above, but for the
            % separately-maintained deployed chart script -- see
            % deployedChartScriptReachesRtdOnBrakeHeld's header for why a
            % divergence here needs its own direct test.
            here = fileparts(mfilename('fullpath'));
            modelsDir = fullfile(fileparts(here), 'models');
            testCase.applyFixture( ...
                matlab.unittest.fixtures.PathFixture(modelsDir));
            clear('virtualVcuDeployStep'); %#ok<CLFUN>

            c = virtualvcu.config();
            toVolts = @(raw) double(raw) / c.adcFullScale * 3.3;
            % Both throttle channels use their OWN rest/pressed raw counts
            % (channel 1 and channel 2 have different spans -- see
            % config.m) so appsOk's dual-sensor-agreement check actually
            % passes and DRIVE can go true; deployedChartScriptReachesRtd-
            % OnBrakeHeld reuses channel 1's rest value for both channels,
            % which is fine there since it never checks torque/drive, only
            % the state transition (brake-gated, not throttle-gated).
            throttleRestV = toVolts(c.throttleRestRaw);
            throttlePressedV = toVolts(c.throttlePressedRaw);
            brakePressedV = toVolts(c.brakePressedRaw(1));
            u = zeros(17, 1);
            u(1) = throttleRestV(1); u(2) = throttleRestV(2);
            u(3) = brakePressedV; u(4) = brakePressedV;

            u(5) = 1; virtualVcuDeployStep(u); % precharge button
            u(5) = 0;
            for k = 1:double(c.prechargeTicks)
                virtualVcuDeployStep(u);
            end
            u(6) = 1; % main button, brake already held
            virtualVcuDeployStep(u);
            [payloads, ~, ~, torqueRequestNm] = deal([], [], [], []);
            for k = 1:double(c.buzzingTicks)
                [payloads, ~, ~, torqueRequestNm] = virtualVcuDeployStep(u);
            end
            testCase.verifyEqual(payloads(41), uint8(4)); % RTD
            testCase.verifyEqual(torqueRequestNm, 0, ...
                'RTD but throttle still at rest: expected zero torque request.');

            u(1) = throttlePressedV(1); u(2) = throttlePressedV(2);
            [payloads, ~, ~, torqueRequestNm] = virtualVcuDeployStep(u);
            testCase.verifyEqual(payloads(41), uint8(4)); % still RTD
            testCase.verifyGreaterThan(torqueRequestNm, 0, ...
                'RTD with throttle pressed: expected nonzero torque request.');
            countsFromPayload = double(payloads(13)) + 256 * double(payloads(14));
            testCase.verifyEqual(countsFromPayload / 256, torqueRequestNm, ...
                'AbsTol', 1/256);

            u(6) = 0; u(5) = 1; % re-enter PRECHARGING: drive must clear
            [~, ~, ~, torqueRequestNm] = virtualVcuDeployStep(u);
            testCase.verifyEqual(torqueRequestNm, 0);
        end

        function canStatusIsDecodedAndRetained(testCase)
            payload = uint8([4 0 4 0 0 0 0 0]);
            out = virtualvcu.step(zeros(1,4), true, false(1,8), ...
                struct('id',uint32(hex2dec('383')),'payload',payload));
            testCase.verifyTrue(out.can.valid);
            testCase.verifyEqual(out.can.lastId, uint32(hex2dec('383')));
            testCase.verifyTrue(out.can.inverterReady);
        end
    end
end
