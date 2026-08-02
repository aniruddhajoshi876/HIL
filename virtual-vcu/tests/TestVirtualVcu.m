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
            testCase.verifyEqual(c.moduleId, 3);
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
    end
end
