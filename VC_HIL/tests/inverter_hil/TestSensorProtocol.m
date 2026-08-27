classdef TestSensorProtocol < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addIndependentSensorPaths(testCase) %#ok<INUSD>
            root = fileparts(fileparts(fileparts(mfilename('fullpath'))));
            addpath(fullfile(root, 'imu'));
            addpath(fullfile(root, 'steering-sensor'));
            addpath(fullfile(root, 'inverter', 'sensorNormalizer'));
        end
    end

    methods (Test)
        function SensorTxIdsMatchTheProtocolContracts(testCase)
            %   IMUTXIDS/LWSTXIDS state the sensor/config IDs literally so
            %   INVERTERHILGUI.BLANKTELEMETRY does not have to put IMU/ and
            %   STEERING-SENSOR/ on the path. This test is what stops that
            %   duplication from drifting: it runs where those folders ARE
            %   on the path and compares the two.
            imu = imuProtocol();
            lws = lwsProtocol();
            expectedImu = uint32([imu.acceleration.id, imu.rateOfTurn.id, ...
                imu.velocityXyz.id]);
            expectedLws = uint32([lws.standardId, lws.configId]);
            [actualImu, imuDlc] = imuTxIds();
            [actualLws, lwsDlc] = lwsTxIds();
            testCase.verifyEqual(actualImu, expectedImu, ...
                'imuTxIds must match imuProtocol in both value and transmit order.');
            testCase.verifyEqual(actualLws, expectedLws, ...
                'lwsTxIds must match lwsProtocol in both value and transmit order.');
            testCase.verifyEqual(imuDlc, uint8([6 6 6]));
            testCase.verifyEqual(lwsDlc, uint8([5 2]));
        end


        function LwsConfigCommandsAreSeparateTwoBytePayloads(testCase)
            p = lwsProtocol();
            reset = packLwsConfigPayload(p.ccwResetCalibration);
            zero = packLwsConfigPayload(p.ccwZeroAngle);
            testCase.verifyEqual(reset, uint8([hex2dec('05') 0]));
            testCase.verifyEqual(zero, uint8([hex2dec('03') 0]));
            testCase.verifyNumElements(reset, double(p.configDlc));
            testCase.verifyNumElements(zero, double(p.configDlc));
            testCase.verifyError(@() packLwsConfigPayload(uint8(4)), ...
                'lws:InvalidConfigCommand');
        end

        function LwsGoldenFrame(testCase)
            frame = packLwsFrame(-12.3, 20, ...
                struct('trim', true, 'cal', true, 'ok', true));
            testCase.verifyEqual(frame.id, uint32(hex2dec('2B0')));
            testCase.verifyEqual(frame.dlc, uint8(5));
            % Byte 3 is the status byte and byte 4 is reserved, per the
            % Bosch CAN Message table and the independently derived vector
            % set in references/sensors/golden_vectors/lws/. This expectation
            % previously read [.. 5 0 7], which put the status into the
            % RESERVED byte; it round-tripped only because decodeLwsFrame
            % read it back from the same wrong offset.
            testCase.verifyEqual(frame.payload, uint8([hex2dec('85') ...
                hex2dec('FF') 5 7 0]));
            measurement = decodeLwsFrame(frame);
            testCase.verifyEqual(measurement.angleDeg, -12.3, 'AbsTol', 0.05);
            testCase.verifyEqual(measurement.speedDegPerS, 20, 'AbsTol', 2);
            testCase.verifyTrue(measurement.valid);
        end

        function LwsInvalidStatusIsVisible(testCase)
            frame = packLwsFrame(0, 0, ...
                struct('trim', true, 'cal', false, 'ok', false));
            measurement = decodeLwsFrame(frame);
            testCase.verifyFalse(measurement.valid);
            testCase.verifyTrue(measurement.trim);
            testCase.verifyFalse(measurement.cal);
            testCase.verifyFalse(measurement.ok);
        end

        function LwsMatchesDerivedGoldenVectors(testCase)
            %LWSMATCHESDERIVEDGOLDENVECTORS Check the encoder against the
            %   vectors derived from the Bosch datasheet alone (see
            %   references/sensors/golden_vectors/lws/derive_lws_vectors.py).
            %   These are the oracle; the encoder is what changes if they
            %   disagree.
            cases = { ...
                'lws_centred_still',      0,     0,    [1 1 1], ...
                    uint8([0 0 0 7 0]); ...
                'lws_one_lsb_angle',      0.1,   0,    [1 1 1], ...
                    uint8([1 0 0 7 0]); ...
                'lws_plus90_100dps',      90,    100,  [1 1 1], ...
                    uint8([hex2dec('84') 3 25 7 0]); ...
                'lws_minus90_100dps',    -90,    100,  [1 1 1], ...
                    uint8([hex2dec('7C') hex2dec('FC') 25 7 0]); ...
                'lws_full_left',          780,   0,    [1 1 1], ...
                    uint8([hex2dec('78') hex2dec('1E') 0 7 0]); ...
                'lws_full_right',        -780,   0,    [1 1 1], ...
                    uint8([hex2dec('88') hex2dec('E1') 0 7 0]); ...
                'lws_speed_max_1016dps',  0,     1016, [1 1 1], ...
                    uint8([0 0 hex2dec('FE') 7 0])};
            for index = 1:size(cases, 1)
                bits = cases{index, 4};
                status = struct('trim', logical(bits(1)), ...
                    'ok', logical(bits(2)), 'cal', logical(bits(3)));
                frame = packLwsFrame(cases{index, 2}, cases{index, 3}, status);
                testCase.verifyEqual(frame.payload, cases{index, 5}, ...
                    sprintf('Golden vector %s disagrees.', cases{index, 1}));
            end
        end

        function LwsTruthTableSentinelsAreEncoded(testCase)
            %LWSTRUTHTABLESENTINELSAREENCODED The datasheet truth table says
            %   an invalid value is transmitted as 0x7FFF / 0xFF, not as a
            %   live reading with the status bits cleared.

            % TRIM=1 OK=1 CAL=0: angle sentinel, speed still valid.
            frame = packLwsFrame(123.4, 200, ...
                struct('trim', true, 'ok', true, 'cal', false));
            testCase.verifyEqual(frame.payload(1:2), ...
                uint8([hex2dec('FF') hex2dec('7F')]));
            testCase.verifyEqual(frame.payload(3), uint8(50));
            testCase.verifyEqual(frame.payload(4), uint8(5));
            measurement = decodeLwsFrame(frame);
            testCase.verifyTrue(measurement.angleIsSentinel);
            testCase.verifyFalse(measurement.speedIsSentinel);
            testCase.verifyEqual(measurement.speedDegPerS, 200, 'AbsTol', 2);
            testCase.verifyFalse(measurement.valid);

            % TRIM=1 OK=0 CAL=0 and TRIM=0 OK=0 CAL=0: both sentinels.
            for trim = [true false]
                frame = packLwsFrame(123.4, 200, ...
                    struct('trim', trim, 'ok', false, 'cal', false));
                testCase.verifyEqual(frame.payload(1:3), ...
                    uint8([hex2dec('FF') hex2dec('7F') hex2dec('FF')]));
                measurement = decodeLwsFrame(frame);
                testCase.verifyTrue(measurement.angleIsSentinel);
                testCase.verifyTrue(measurement.speedIsSentinel);
                testCase.verifyFalse(measurement.valid);
            end
        end

        function LwsInvalidStatusCombinationIsRejected(testCase)
            %LWSINVALIDSTATUSCOMBINATIONISREJECTED "Other combinations for
            %   TRIM, OK and CAL are not valid" -- the encoder must refuse
            %   them rather than invent a frame the sensor cannot send.
            testCase.verifyError(@() packLwsFrame(0, 0, ...
                struct('trim', false, 'ok', false, 'cal', true)), ...
                'lws:InvalidStatusCombination');
            testCase.verifyError(@() packLwsFrame(0, 0, ...
                struct('trim', false, 'ok', true, 'cal', true)), ...
                'lws:InvalidStatusCombination');

            % A decoder must flag one that arrives from the wire anyway.
            frame = struct('id', uint32(hex2dec('2B0')), ...
                'payload', uint8([hex2dec('84') 3 25 2 0]));
            measurement = decodeLwsFrame(frame);
            testCase.verifyFalse(measurement.statusCombinationValid);
            testCase.verifyFalse(measurement.valid);
        end

        function LwsReservedByteIsNotTheStatusByte(testCase)
            %LWSRESERVEDBYTEISNOTTHESTATUSBYTE Mutation guard: moving the
            %   status into the reserved byte must not still decode as valid.
            frame = packLwsFrame(0, 0, ...
                struct('trim', true, 'ok', true, 'cal', true));
            testCase.verifyEqual(frame.payload(5), uint8(0));
            frame.payload(4) = uint8(0);
            frame.payload(5) = uint8(7);
            measurement = decodeLwsFrame(frame);
            testCase.verifyFalse(measurement.valid);
        end

        function LwsRangeIsRejected(testCase)
            testCase.verifyError(@() packLwsFrame(781, 0), ...
                'lws:AngleRange');
            testCase.verifyError(@() packLwsFrame(0, 1100), ...
                'lws:SpeedValue');
            testCase.verifyError(@() packLwsFrame(0, -1), ...
                'lws:SpeedValue');
        end

        function MtiAccelerationGoldenFrame(testCase)
            frame = packMti680Frame('acceleration', [1 -2 9.8]);
            testCase.verifyEqual(frame.id, uint32(hex2dec('034')));
            testCase.verifyEqual(frame.dlc, uint8(6));
            testCase.verifyEqual(frame.payload, uint8([1 0 254 0 9 hex2dec('CD')]));
            values = decodeMti680Frame(frame);
            testCase.verifyEqual(values, [1 -2 9.80078125], 'AbsTol', 1e-12);
        end

        function MtiRateOfTurnGoldenFrame(testCase)
            frame = packMti680Frame('rateOfTurn', [1 -1 0.5]);
            testCase.verifyEqual(frame.id, uint32(hex2dec('032')));
            testCase.verifyEqual(frame.payload, uint8([2 0 254 0 1 0]));
            values = decodeMti680Frame(frame);
            testCase.verifyEqual(values, [1 -1 0.5], 'AbsTol', 1e-12);
        end

        function MtiWrongPayloadDoesNotSilentlyPass(testCase)
            frame = packMti680Frame('acceleration', [1 -2 9.8]);
            frame.payload(2) = uint8(1);
            values = decodeMti680Frame(frame);
            testCase.verifyNotEqual(values(1), 1);
        end

        function MtiVelocityXyzGoldenFrame(testCase)
            %MTIVELOCITYXYZGOLDENFRAME 0x076 is the message the MFE26-VC
            %   firmware decodes for its velocity path; without it that
            %   input receives nothing. Scale is 2^-6 m/s per count.
            frame = packMti680Frame('velocityXyz', [1 -2 0.5]);
            testCase.verifyEqual(frame.id, uint32(hex2dec('076')));
            testCase.verifyEqual(frame.dlc, uint8(6));
            % 1 m/s = 64 counts = 0x0040; -2 = -128 = 0xFF80; 0.5 = 32 = 0x0020.
            testCase.verifyEqual(frame.payload, ...
                uint8([0 hex2dec('40') hex2dec('FF') hex2dec('80') 0 hex2dec('20')]));
            values = decodeMti680Frame(frame);
            testCase.verifyEqual(values, [1 -2 0.5], 'AbsTol', 1e-12);
        end

        function MtiDocumentedRangeViolationIsVisible(testCase)
            %MTIDOCUMENTEDRANGEVIOLATIONISVISIBLE The VCU discards the whole
            %   frame if any axis exceeds the documented Range column, which
            %   is narrower than the int16 encoding limit. Saturating only at
            %   int16 would emit frames the VCU silently drops.
            testCase.verifyError(@() packMti680Frame('acceleration', ...
                [101 0 0]), 'mti680:DocRange');
            testCase.verifyError(@() packMti680Frame('rateOfTurn', ...
                [0 36 0]), 'mti680:DocRange');
            testCase.verifyError(@() packMti680Frame('velocityXyz', ...
                [0 0 501]), 'mti680:DocRange');
            % Inside the documented range still encodes.
            testCase.verifyEqual(packMti680Frame('acceleration', ...
                [100 0 0]).id, uint32(hex2dec('034')));
            % The payload encoders enforce the same bound.
            testCase.verifyError(@() packMti680Payload('velocityxyz', ...
                [501 0 0]), 'mti680:PayloadRange');
        end

        function MtiScalarMessagesAreNotVectorPacked(testCase)
            %MTISCALARMESSAGESARENOTVECTORPACKED groupCounter/sampleTime and
            %   friends are scalar messages; asking the vector packer for one
            %   must fail clearly rather than with a "three finite values"
            %   complaint.
            testCase.verifyError(@() packMti680Frame('groupCounter', ...
                [1 2 3]), 'mti680:UnknownKind');
            testCase.verifyError(@() packMti680Frame('statusWord', ...
                [1 2 3]), 'mti680:UnknownKind');
        end

        function MtiByteOrderIsRecordedAsUnverified(testCase)
            %MTIBYTEORDERISRECORDEDASUNVERIFIED MT1604P never states CAN
            %   payload endianness. Both this simulator and the VCU assume
            %   big-endian, so agreement between them proves nothing. The
            %   contract must not claim it is verified.
            p = imuProtocol();
            testCase.verifyEqual(p.byteOrder, 'big');
            testCase.verifyFalse(p.byteOrderVerified);
            testCase.verifyEqual(p.defaultOutputRateHz.eulerAngles, 0, ...
                'Euler 0x022 has no VCU handler and must default to 0 Hz.');
        end

        function MtiUnknownIdIsRejected(testCase)
            frame = struct('id', uint32(1), 'payload', zeros(1, 6, 'uint8'));
            testCase.verifyError(@() decodeMti680Frame(frame), ...
                'mti680:UnknownId');
        end

        function IndependentPayloadEncodersRejectOutOfRangeValues(testCase)
            testCase.verifyError(@() packLwsPayload(0, -1, 7), ...
                'lws:SpeedRange');
            testCase.verifyError(@() packMti680Payload('acceleration', ...
                [1e9 0 0]), 'mti680:PayloadRange');
        end

        function MtiEulerPitchRangeIsPerAxis(testCase)
            %MTIEULERPITCHRANGEISPERAXIS MT1604P section 6.3.2 specifies roll
            %   +/-180, PITCH +/-90, yaw +/-180. The range guard must reject
            %   a pitch outside +/-90 while roll and yaw at the same
            %   magnitude still encode -- same reject-not-saturate behaviour
            %   the other messages use.
            p = imuProtocol();
            testCase.verifyEqual(double(p.eulerAngles.rangeMax), ...
                [180 90 180]);
            testCase.verifyError(@() packMti680Frame('eulerAngles', ...
                [0 90.5 0]), 'mti680:DocRange');
            testCase.verifyError(@() packMti680Frame('eulerAngles', ...
                [0 -120 0]), 'mti680:DocRange');
            % Roll and yaw at a magnitude that would fail as pitch still pass.
            testCase.verifyEqual(packMti680Frame('eulerAngles', ...
                [170 0 -170]).id, uint32(hex2dec('022')));
            % Pitch exactly +/-90 is inside the (inclusive) documented range.
            testCase.verifyEqual(packMti680Frame('eulerAngles', ...
                [0 90 0]).id, uint32(hex2dec('022')));
        end

        function MtiScalarFramesArePackedBigEndianUnsigned(testCase)
            %MTISCALARFRAMESAREPACKEDBIGENDIANUNSIGNED groupCounter (0x006),
            %   sampleTime (0x005), statusWord (0x011) and errorCode (0x001)
            %   big-endian-pack a single uintN into their DLC. Bytes are
            %   hand-derived from MT1604P sections 6.1.1-6.1.3, 6.2.1.
            group = packMti680ScalarFrame('groupCounter', 4660);
            testCase.verifyEqual(group.id, uint32(hex2dec('006')));
            testCase.verifyEqual(group.dlc, uint8(2));
            testCase.verifyEqual(group.payload, uint8([hex2dec('12') hex2dec('34')]));

            sample = packMti680ScalarFrame('sampleTime', 1e6);
            testCase.verifyEqual(sample.id, uint32(hex2dec('005')));
            testCase.verifyEqual(sample.payload, uint8([0 15 66 64]));

            statusWord = packMti680ScalarFrame('statusWord', 3);
            testCase.verifyEqual(statusWord.id, uint32(hex2dec('011')));
            testCase.verifyEqual(statusWord.payload, uint8([0 0 0 3]));

            errorCode = packMti680ScalarFrame('errorCode', 0);
            testCase.verifyEqual(errorCode.id, uint32(hex2dec('001')));
            testCase.verifyEqual(errorCode.payload, uint8(0));

            % Wrong shape / signedness is rejected, not silently truncated.
            testCase.verifyError(@() packMti680ScalarFrame('groupCounter', ...
                -1), 'mti680:InvalidValues');
            testCase.verifyError(@() packMti680ScalarFrame('groupCounter', ...
                70000), 'mti680:Range');
            testCase.verifyError(@() packMti680ScalarFrame('acceleration', ...
                1), 'mti680:UnknownKind');
        end

        function MtiMountingTransformIs180AboutZ(testCase)
            %MTIMOUNTINGTRANSFORMIS180ABOUTZ The physical IMU is mounted
            %   rotated 180 deg about the vehicle Z (yaw) axis. X and Y of
            %   every vector negate; Z keeps sign. Euler roll and pitch
            %   negate; yaw offsets 180 deg and wraps to (-180, 180].
            p = imuProtocol();
            testCase.verifyEqual(p.mounting.axisSign, [-1 -1 1]);
            sensor = mountingTransform(struct( ...
                'accelerationMps2', [1 2 9.81], ...
                'rateOfTurnRadPerS', [0.1 -0.2 0.3], ...
                'velocityMps', [10 -4 0], ...
                'eulerAnglesDeg', [10 20 30]));
            testCase.verifyEqual(sensor.accelerationMps2, [-1 -2 9.81], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(sensor.rateOfTurnRadPerS, [-0.1 0.2 0.3], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(sensor.velocityMps, [-10 4 0], ...
                'AbsTol', 1e-12);
            testCase.verifyEqual(sensor.eulerAnglesDeg, [-10 -20 -150], ...
                'AbsTol', 1e-12);
            % Yaw wrap boundary: vehicle yaw 0 -> sensor yaw 180 (not -180).
            wrapped = mountingTransform(struct('eulerAnglesDeg', [0 0 0]));
            testCase.verifyEqual(wrapped.eulerAnglesDeg(3), 180);
        end

        function MtiSchedulerDerivesBaseTickFromContract(testCase)
            %MTISCHEDULERDERIVESBASETICKFROMCONTRACT imuProtocol is the
            %   single source of truth for output rates. The scheduler's base
            %   tick is 1 / (fastest non-zero rate) = 0.01 s = 100 Hz, and
            %   eulerAngles at 0 Hz is never due.
            [~, dueAtZero] = imuScheduler([], 0);
            testCase.verifyTrue(dueAtZero.imu);
            testCase.verifyTrue(dueAtZero.acceleration);
            testCase.verifyTrue(dueAtZero.rateOfTurn);
            testCase.verifyTrue(dueAtZero.velocityXyz);
            testCase.verifyFalse(dueAtZero.eulerAngles);

            % 100 Hz base tick: due at 0.01 s, not before.
            state = imuScheduler([], 0);
            [state, dueEarly] = imuScheduler(state, 0.004);
            testCase.verifyFalse(dueEarly.imu);
            [~, dueOnTick] = imuScheduler(state, 0.01);
            testCase.verifyTrue(dueOnTick.imu);
        end
    end
end
