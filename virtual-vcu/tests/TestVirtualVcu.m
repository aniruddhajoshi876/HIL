classdef TestVirtualVcu < matlab.unittest.TestCase
    methods (Test)
        function calibrationAndMarginsMatchControlsBranch(testCase)
            c = virtualvcu.config();
            [p,ok] = virtualvcu.rawToPedal(c.throttlePressedRaw(1),'throttle',1);
            testCase.verifyTrue(ok); testCase.verifyEqual(p,100,'AbsTol',1e-12);
            [~,ok] = virtualvcu.rawToPedal(22500,'throttle',1);
            testCase.verifyTrue(ok); % inside 15% margin
            [~,ok] = virtualvcu.rawToPedal(21000,'throttle',1);
            testCase.verifyFalse(ok);
            [p,ok] = virtualvcu.rawToPedal(9025,'brake',2);
            testCase.verifyTrue(ok); testCase.verifyEqual(p,0,'AbsTol',1e-12);
        end

        function voltageRawRoundTrip(testCase)
            testCase.verifyEqual(virtualvcu.voltageToRaw(0),uint16(0));
            testCase.verifyEqual(virtualvcu.voltageToRaw(5),uint16(65535));
            testCase.verifyEqual(virtualvcu.voltageToRaw(2.5),uint16(32768));
        end

        function goldenControlBytesAndReset(testCase)
            payload = virtualvcu.packControlFrame(1,true,18000,12.5,false);
            testCase.verifyEqual(payload,uint8([1 0 80 70 128 12 0 0]));
            reset = virtualvcu.packControlFrame(1,true,0,0,true);
            testCase.verifyEqual(reset,uint8([3 0 0 0 0 0 0 0]));
            capped = virtualvcu.packControlFrame(1,true,18000,20,false);
            testCase.verifyEqual(capped(5:6),uint8([0 15]));
        end

        function goldenPedalBytesPreserveFrontRear(testCase)
            payload = virtualvcu.packPedalFrame(12.5,1,0.5);
            testCase.verifyEqual(payload,uint8([13 138 2 69 1 0 0 0]));
            testCase.verifyEqual(virtualvcu.config().pedalCanId,uint32(501));
        end

        function brakeTwoDoesNotGateBrakePlausibility(testCase)
            c = virtualvcu.config();
            raw = [c.throttleRestRaw c.brakePressedRaw(1) 0];
            volts = raw/c.adcFullScale*c.io183FullScaleV;
            out = virtualvcu.step(volts,true);
            testCase.verifyTrue(out.brakePlausible);
            testCase.verifyEqual(out.pedalPct(3),100,'AbsTol',0.1);
            testCase.verifyEqual(out.pedalPct(4),0,'AbsTol',0.1);
        end

        function appsBrakeInterlockLatchesAndClears(testCase)
            c = virtualvcu.config();
            pressed = [c.throttlePressedRaw c.brakePressedRaw];
            volts = pressed/c.adcFullScale*c.io183FullScaleV;
            out = virtualvcu.step(volts,true);
            testCase.verifyTrue(out.appsError);
            testCase.verifyEqual(out.torqueRequestPct,0);
            rest = [c.throttleRestRaw c.brakePressedRaw]/c.adcFullScale*c.io183FullScaleV;
            out = virtualvcu.step(rest,true,false(1,8),[],out.context);
            testCase.verifyFalse(out.appsError);
        end

        function stateMachineUsesFiveMillisecondTicksAndDcHealth(testCase)
            c = virtualvcu.config();
            testCase.verifyEqual(c.sampleTimeS,0.005);
            testCase.verifyEqual(c.prechargeTicks,uint32(1500));
            volts = [c.throttleRestRaw c.brakePressedRaw]/c.adcFullScale*c.io183FullScaleV;
            di = false(1,8); di(1) = true;
            out = virtualvcu.step(volts,true,di);
            ctx = out.context;
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
            ctx.ticks = c.prechargeTicks-1;
            di(1) = false; out = virtualvcu.step(volts,true,di,[],ctx);
            testCase.verifyEqual(out.state,'ENABLE');
            di(2) = true; out = virtualvcu.step(volts,true,di,[],out.context);
            testCase.verifyEqual(out.state,'BUZZING');
            ctx = out.context; ctx.ticks = c.buzzingTicks-1;
            out = virtualvcu.step(volts,true,di,[],ctx);
            testCase.verifyEqual(out.state,'RTD');
            testCase.verifyEqual(out.controlPayloads(:,1),uint8(3*ones(4,1)));
        end

        function bothDcLinkPairsAreRequired(testCase)
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(2);
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 349;
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyEqual(out.state,'ERROR_SHUTDOWN');
        end

        function neitherDcLinkPairValidFaultsActiveHv(testCase)
            % Firmware prechargeComplete(): "if (!sys.valid) return false;"
            % before the 350 V comparison. With no 0x400 ever decoded, both
            % per-pair valid flags stay false and ENABLE must fault.
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(2);
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400; % voltages fine
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyEqual(out.state,'ERROR_SHUTDOWN');
        end

        function onePairValidButBelowFloorFaultsRtd(testCase)
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(4); ctx.resetSent = true;
            ctx.can.systemValid = true;
            ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 340; % pair 34 sagged
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyEqual(out.state,'ERROR_SHUTDOWN');
        end

        function prechargeEnableHeldClosedThroughEnable(testCase)
            % vcStateMachine.cpp holds prechargeEnable = true in PRECHARGING
            % AND ENABLE (lines 307, 325), dropping it only on the ENABLE ->
            % BUZZING transition.
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(1);
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyTrue(out.outputs.prechargeEnable);
            ctx = virtualvcu.initialContext(); ctx.state = uint8(2);
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyEqual(out.state,'ENABLE');
            testCase.verifyTrue(out.outputs.prechargeEnable);
            testCase.verifyTrue(out.outputs.mainEnable);
        end

        function allocatorThrottleIsNotGatedByAppsLatch(testCase)
            % driverInputs.cpp latches appsError and zeroes torqueRequestPct,
            % but update_ctrls_inputs() still feeds ungated throttleValidPct as
            % rThrottlePedal. The interlock only zeroes the 0x1F5 throttle byte.
            c = virtualvcu.config();
            pressed = [c.throttlePressedRaw c.brakePressedRaw];
            volts = pressed/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(4); ctx.resetSent = true;
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
            tau = [5 6 7 8];
            out = virtualvcu.step(volts,true,false(1,8),[],ctx,tau);
            testCase.verifyTrue(out.appsError);
            testCase.verifyEqual(out.torqueRequestPct,0);          % interlock cut
            testCase.verifyEqual(out.pedalPayload(1),uint8(0));    % 0x1F5 throttle byte gated
            testCase.verifyEqual(out.torqueRequestNm,min(tau,c.maxTorqueNm)); % allocator path unaffected
        end

        function brakeTwoIsTransmittedAsRearPressure(testCase)
            % driverInputs.cpp converts brake2 and vcComms.cpp sends it as the
            % 0x1F5 rear-brake pressure even though it is excluded from
            % plausibility.
            c = virtualvcu.config();
            raw = [c.throttleRestRaw c.brakePressedRaw(1) c.brakePressedRaw(2)];
            volts = raw/c.adcFullScale*c.io183FullScaleV;
            out = virtualvcu.step(volts,true);
            rearPsi = double(out.pedalPayload(4)) + 256*double(out.pedalPayload(5));
            testCase.verifyEqual(rearPsi,650,'AbsTol',1);
        end

        function cornerMappingUsesAllocatorOutputs(testCase)
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext(); ctx.state = uint8(4); ctx.resetSent = true;
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true; ctx.can.dcLink34Valid = true;
            ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
            tau = [1 2 3 4]; % FL FR RL RR
            out = virtualvcu.step(volts,true,false(1,8),[],ctx,tau);
            expected = [3 4 2 1]; % INV1 RL, INV2 RR, INV3 FR, INV4 FL
            for inverter = 1:4
                counts = double(out.controlPayloads(inverter,5)) + ...
                    256*double(out.controlPayloads(inverter,6));
                testCase.verifyEqual(counts/256,expected(inverter));
            end
            testCase.verifyEqual(out.torqueRequestNm,tau);
        end

        function physicalThreeByFiveSpeedIsDecoded(testCase)
            rpm = int16(1339);
            bytes = zeros(1,8,'uint8'); bytes(7:8) = typecast(rpm,'uint8');
            decoded = virtualvcu.decodeStatusFrame(hex2dec('385'),bytes);
            expected = double(rpm)*(2*pi/60)/virtualvcu.config().gearRatio;
            testCase.verifyEqual(decoded.fields.wheelSpeedRadS,expected,'AbsTol',1e-12);
        end

        function controlsInputContractMatchesFirmware(testCase)
            x = virtualvcu.controlsInputVector(0.4,[1 2 3 4]);
            testCase.verifySize(x,[32 1]);
            testCase.verifyEqual(x(3),0.5);
            testCase.verifyEqual(x(4),80000);
            testCase.verifyEqual(x(8:11),[1;2;3;4]);
            testCase.verifyEqual(x(18),0.4);
            testCase.verifyEqual(x(20),15);
            testCase.verifyEqual(x(25:26),[1;1]);
        end

        function generatedControlsModelExecutes(testCase)
            x = virtualvcu.controlsInputVector(0,zeros(1,4));
            tau = virtualvcu.controlsModelStep(x,true);
            testCase.verifySize(tau,[1 4]);
            testCase.verifyTrue(all(isfinite(tau)));
        end

        function deployedChartUsesResetThenRealAllocator(testCase)
            here = fileparts(mfilename('fullpath'));
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                fullfile(fileparts(here),'models')));
            clear('virtualVcuDeployStep');
            c = virtualvcu.config();
            toVolts = @(raw) double(raw)/c.adcFullScale*c.io183FullScaleV;
            u = zeros(29,1); % 1:25 IO + CAN, 26:29 retained wheel speeds
            u(1:2) = toVolts(c.throttleRestRaw);
            u(3:4) = toVolts(c.brakePressedRaw);
            u(5) = 1; virtualVcuDeployStep(u);
            u(5) = 0;
            for k = 1:double(c.prechargeTicks), virtualVcuDeployStep(u); end
            u(6) = 1; virtualVcuDeployStep(u);
            payloads = zeros(48,1,'uint8');
            for k = 1:double(c.buzzingTicks)
                payloads = virtualVcuDeployStep(u);
            end
            testCase.verifyEqual(payloads(41),uint8(4));
            testCase.verifyEqual(payloads([9 17 25 33]),uint8(3*ones(4,1)));
            [payloads,~,~,tau] = virtualVcuDeployStep(u);
            testCase.verifyTrue(all(isfinite(tau)));
            testCase.verifyEqual(payloads([9 17 25 33]),uint8(ones(4,1)));
            testCase.verifyEqual(payloads([11 19 27 35]),uint8(80*ones(4,1)));
            testCase.verifyEqual(payloads([12 20 28 36]),uint8(70*ones(4,1)));
        end

        function rxRetentionKeepsAllFourCornersInAWindow(testCase)
            % Item 2: virtualVcuRxRetain latches each 0x3X5 frame at the 1 ms
            % base rate, so four frames arriving in one 5 ms window all reach
            % the chart instead of only the last.
            here = fileparts(mfilename('fullpath'));
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                fullfile(fileparts(here),'models')));
            clear('virtualVcuRxRetain');
            ids = [901 917 933 949];        % 0x385 0x395 0x3A5 0x3B5 = INV1..4
            rpm = int16([100 -200 300 -400]);
            om = zeros(4,1);
            for k = 1:4
                data = zeros(8,1);
                data(7:8) = double(typecast(rpm(k),'uint8'));
                om = virtualVcuRxRetain(1, ids(k), 0, 0, 8, data);
            end
            expected = double(rpm(:)) * (2*pi/60) / 13.39;
            testCase.verifyEqual(om, expected, 'AbsTol', 1e-12);
            % A tick with no frame present holds every slot.
            omHeld = virtualVcuRxRetain(0, 0, 0, 0, 0, zeros(8,1));
            testCase.verifyEqual(omHeld, expected, 'AbsTol', 1e-12);
        end

        function hostContextRetainsPerCornerWheelSpeed(testCase)
            % Host-reference equivalent: context.can.wheelSpeedRadS keeps each
            % corner across 5 ms samples even when frames arrive one per call.
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            ctx = virtualvcu.initialContext();
            ids = {'385','395','3A5','3B5'};
            rpm = int16([120 240 360 480]);
            for k = 1:4
                bytes = zeros(1,8,'uint8');
                bytes(7:8) = typecast(rpm(k),'uint8');
                rx = struct('id',uint32(hex2dec(ids{k})),'payload',bytes);
                out = virtualvcu.step(volts,true,false(1,8),rx,ctx);
                ctx = out.context;
            end
            testCase.verifyTrue(all(ctx.can.wheelSpeedValid));
            testCase.verifyEqual(ctx.can.wheelSpeedRadS(:), ...
                double(rpm(:))*(2*pi/60)/c.gearRatio, 'AbsTol', 1e-12);
        end

        function canFrameTransmissionGatingMatchesFirmwareStates(testCase)
            % Items 8/9: control frames only in RTD; 0x1F5 in every state but
            % ERROR_SHUTDOWN, skipped on the first RTD (reset-only) cycle.
            c = virtualvcu.config();
            volts = [c.throttleRestRaw c.brakeRestRaw]/c.adcFullScale*c.io183FullScaleV;
            % LV_ON: pedal on, control off
            ctx0 = virtualvcu.initialContext(); ctx0.state = uint8(0);
            out = virtualvcu.step(volts,true,false(1,8),[],ctx0);
            testCase.verifyFalse(out.controlFrameTxEnabled);
            testCase.verifyTrue(out.pedalFrameTxEnabled);
            % First RTD cycle (resetSent false): control on, pedal skipped
            ctx = virtualvcu.initialContext(); ctx.state = uint8(4); ctx.resetSent = false;
            ctx.can.systemValid = true; ctx.can.dcLink12Valid = true;
            ctx.can.dcLink34Valid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
            out = virtualvcu.step(volts,true,false(1,8),[],ctx);
            testCase.verifyTrue(out.controlFrameTxEnabled);
            testCase.verifyFalse(out.pedalFrameTxEnabled);
            % Ordinary RTD cycle: both on
            out = virtualvcu.step(volts,true,false(1,8),[],out.context);
            testCase.verifyTrue(out.controlFrameTxEnabled);
            testCase.verifyTrue(out.pedalFrameTxEnabled);
            % ERROR_SHUTDOWN held by shutdown feedback: both off
            di5 = false(1,8); di5(c.digitalMap.shutdownFeedback) = true;
            ctx5 = virtualvcu.initialContext(); ctx5.state = uint8(5);
            ctx5.can.dcLink12Valid = true; ctx5.can.dcLink34Valid = true;
            out = virtualvcu.step(volts,true,di5,[],ctx5);
            testCase.verifyEqual(out.state,'ERROR_SHUTDOWN');
            testCase.verifyFalse(out.controlFrameTxEnabled);
            testCase.verifyFalse(out.pedalFrameTxEnabled);
        end

        function suppliedDbcMatchesFirmwareContract(testCase)
            dbc = virtualvcu.verifyDbcContract();
            testCase.verifyEqual(dbc.torqueScaleNmPerCount,1/256);
            testCase.verifyEqual(dbc.controlIds,uint32([390 406 422 438]));
        end
    end
end
