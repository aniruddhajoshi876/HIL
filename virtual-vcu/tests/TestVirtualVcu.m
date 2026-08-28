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
            ctx.can.systemValid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
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
            ctx.can.systemValid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 349;
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
            ctx.can.systemValid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
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
            ctx.can.systemValid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
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
            ctx.can.systemValid = true; ctx.can.dcLink12V = 400; ctx.can.dcLink34V = 400;
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
            clear('virtualVcuDeployStep'); %#ok<CLFUN>
            c = virtualvcu.config();
            toVolts = @(raw) double(raw)/c.adcFullScale*c.io183FullScaleV;
            u = zeros(25,1);
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

        function suppliedDbcMatchesFirmwareContract(testCase)
            dbc = virtualvcu.verifyDbcContract();
            testCase.verifyEqual(dbc.torqueScaleNmPerCount,1/256);
            testCase.verifyEqual(dbc.controlIds,uint32([390 406 422 438]));
        end
    end
end
