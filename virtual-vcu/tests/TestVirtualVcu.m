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
