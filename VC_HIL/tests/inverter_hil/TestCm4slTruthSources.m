classdef TestCm4slTruthSources < matlab.unittest.TestCase
    %TESTCM4SLTRUTHSOURCES Static verification of the CarMaker side of the
    %   truth path and of the DBC that both sides are written against.
    %
    %   These are SOURCE assertions, not runtime ones: the CM4SL C code only
    %   executes inside CarMaker, and TorqueVect.mdl only opens in R2022a, so
    %   neither can be exercised from the R2024b test suite. What can be
    %   checked here is that the two sides still describe the SAME contract --
    %   the failure this catches is one side being updated and the other not,
    %   which produces a silently mis-scaled or silently zero signal rather
    %   than an error.
    %
    %   Passing this class is NOT evidence that the CM4SL code compiles, that
    %   TorqueVect.mdl has been edited, or that anything reached a real VCU.

    properties (Constant)
        Root = TestCm4slTruthSources.repoRoot();
    end

    methods (Test)
        % ------------------------------------------------ transmission gate

        function physicsAndSteeringTransmissionAreGatedOnModelValidity(testCase)
            io = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'IO.c'));
            % The whole point of the gate: without it IO_Out transmits
            % CRC-valid, counter-advancing, all-zero frames from the moment
            % the PCAN link comes up, and a zero group is indistinguishable
            % downstream from a genuinely stationary, straight-ahead vehicle.
            testCase.verifySubstring(io, 'MFE_CAN_PhysicsValid', ...
                'IO.c must read a model-written physics validity flag.');
            testCase.verifySubstring(io, 'MFE_CAN_SteeringValid', ...
                'IO.c must read a model-written steering validity flag.');
            testCase.verifySubstring(io, 'if (physicsValid) {', ...
                'The 0x503-0x506 group must be inside the validity gate.');
            testCase.verifySubstring(io, 'if (steeringValid)', ...
                'The 0x507 frame must be inside the validity gate.');
            % Every physics send has to be gated, so none may appear before
            % the gate opens.
            gateIndex = strfind(io, 'if (physicsValid) {');
            sendIndices = strfind(io, 'MFE_SendPhysicsFrame(0x');
            testCase.verifyNumElements(gateIndex, 1);
            testCase.verifyNumElements(sendIndices, 4, ...
                'Exactly the four physics frames 0x503-0x506 are transmitted.');
            testCase.verifyTrue(all(sendIndices > gateIndex), ...
                'No physics frame may be transmitted outside the gate.');
        end

        function suppressionIsReportedOnTheEdgeNotEveryCycle(testCase)
            io = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'IO.c'));
            % An unpopulated model is an expected state for the first cycles
            % of every run. Logging it per 10 ms cycle would bury the CarMaker
            % log; logging it as an error would misclassify it.
            testCase.verifySubstring(io, 'MFE_ReportTruthGate');
            testCase.verifySubstring(io, 'MFE_PCAN_PhysicsSuppressed');
            testCase.verifySubstring(io, 'MFE_PCAN_SteeringSuppressed');
            gateFn = extractBetween(io, 'MFE_ReportTruthGate (int suppressedNow', ...
                'return suppressedNow;');
            testCase.verifyNumElements(gateFn, 1);
            testCase.verifyEmpty(strfind(gateFn{1}, 'LogErrF'), ...
                'An unpopulated model is an expected state, not an error.');
        end

        function validityIsClearedAtEveryTestRunStart(testCase)
            user = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'User.c'));
            % The flags live in the CM4SL DLL. Without a per-run clear they
            % stay raised for the rest of the process once any run set them,
            % so a later run with the truth writers removed from the model
            % would keep transmitting stale zeros that IO_Out believes are
            % model-written.
            block = extractBetween(user, 'User_TestRun_Start_atBegin (void)', ...
                'User_TestRun_Start_atEnd');
            testCase.verifyNumElements(block, 1);
            testCase.verifySubstring(block{1}, 'MFE_CAN_PhysicsValid  = 0.0;');
            testCase.verifySubstring(block{1}, 'MFE_CAN_SteeringValid = 0.0;');
        end

        % ------------------------------------------------- dictionary names

        function everyModelWrittenQuantityIsRegisteredAsDvaIoOut(testCase)
            user = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'User.c'));
            declared = extractBetween(user, 'User_DeclQuants (void)', ...
                'User_Param_Add');
            testCase.verifyNumElements(declared, 1);
            declared = declared{1};
            % Model writes, IO reads. Registering these as DVA_IO_In instead
            % would silently make the dictionary the writer and drop every
            % value the model produced.
            expected = { ...
                'MFE_CAN.Physics.Valid', '&MFE_CAN_PhysicsValid'; ...
                'MFE_CAN.Steering.WheelAngleRad', '&MFE_CAN_SteeringWheelAngleRad'; ...
                'MFE_CAN.Steering.Valid', '&MFE_CAN_SteeringValid'};
            for index = 1:size(expected, 1)
                name = expected{index, 1};
                testCase.verifySubstring(declared, sprintf('"%s"', name), ...
                    sprintf('%s must be registered.', name));
                registration = extractBetween(declared, sprintf('"%s"', name), ');');
                testCase.verifyNotEmpty(registration);
                testCase.verifySubstring(registration{1}, 'DVA_IO_Out', ...
                    sprintf('%s is model-written and must be DVA_IO_Out.', name));
                testCase.verifySubstring(registration{1}, expected{index, 2});
            end
            % The steering quantity must carry radians, matching Steer.WhlAng
            % and the 0x507 wire unit. A "deg" registration here would be the
            % signature of the superseded degrees contract.
            radRegistration = extractBetween(declared, ...
                '"MFE_CAN.Steering.WheelAngleRad"', ');');
            testCase.verifySubstring(radRegistration{1}, '"rad"');
            % The superseded degrees/speed quantities must be gone, so no
            % half-migrated model can still find something to write into.
            testCase.verifyEmpty(strfind(user, 'MFE_CAN.Driver.SteeringAngleDeg'));
            testCase.verifyEmpty(strfind(user, 'MFE_CAN.Driver.SteeringSpeedDegPerSec'));
        end

        function torqueVectApplyScriptWritesExactlyThoseQuantities(testCase)
            script = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'apply_torquevect_cm_truth.m'));
            % Sources named in the task contract, confirmed present in
            % <CarMakerInstall>/CM4SL/startup.dict (Steer.WhlAng "rad",
            % Car.Roll/Pitch/Yaw "rad") or created at runtime by the
            % Param_B00 inertial sensor configured in the MFE24_V3 / MFE26_V1
            % vehicle data sets.
            for source = {'Sensor.Inertial.%s.Acc_B', ...
                    'Sensor.Inertial.%s.Omega_B', 'Sensor.Inertial.%s.Vel_B'}
                testCase.verifySubstring(script, source{1});
            end
            testCase.verifySubstring(script, '''Param_B00''');
            testCase.verifySubstring(script, '''Steer.WhlAng''');
            testCase.verifySubstring(script, 'Car.Roll');
            for target = {'MFE_CAN.Physics.Acceleration', ...
                    'MFE_CAN.Physics.AngularRate', 'MFE_CAN.Physics.Velocity', ...
                    'MFE_CAN.Physics.Euler', 'MFE_CAN.Physics.Valid', ...
                    'MFE_CAN.Steering.WheelAngleRad', 'MFE_CAN.Steering.Valid'}
                testCase.verifySubstring(script, target{1}, ...
                    sprintf('%s must have a writer.', target{1}));
            end
            % Straight passthroughs only. A Gain would be a unit conversion
            % the Speedgoat then has to undo; a Delay would hand IO_Out the
            % previous cycle's value; a Saturation would silently clip truth.
            for forbidden = {'built-in/Gain', 'built-in/Saturate', ...
                    'built-in/UnitDelay', 'built-in/Memory'}
                testCase.verifyEmpty(strfind(script, forbidden{1}), ...
                    sprintf('%s has no place in a truth passthrough.', forbidden{1}));
            end
            testCase.verifySubstring(script, 'CarMaker4SL/Read CM Dict');
            testCase.verifySubstring(script, 'CarMaker4SL/Write CM Dict');
            % Base step, not a private rate.
            testCase.verifySubstring(script, '''xstime'', ''Inherited''');
        end

        function torqueVectActuallyContainsTheTruthWriters(testCase)
            % The one failure the rest of this class cannot see: the C code,
            % the DBC and the apply script can all be perfectly consistent
            % while TorqueVect.mdl has simply never been edited -- and then
            % every MFE_CAN.* quantity stays at its zero-initialised C value
            % and IO.c transmits nothing (or, without the validity gate,
            % transmits zeros). A text scan of the saved model is enough to
            % tell "edited" from "not edited", and it works from R2024b, which
            % cannot open an R2022a .mdl.
            %
            % This is STATIC evidence only. It says the writers exist in the
            % file; it does not say the model compiles, runs, or that the
            % source quantities resolve at runtime -- the Param_B00 inertial
            % quantities are created by the vehicle's sensor instance and only
            % exist once a TestRun is loaded.
            model = TestCm4slTruthSources.readFile(fullfile( ...
                TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'vehicle_models', 'TorqueVect.mdl'));
            targets = { ...
                'MFE_CAN.Physics.Acceleration.x', 'MFE_CAN.Physics.Acceleration.y', ...
                'MFE_CAN.Physics.Acceleration.z', 'MFE_CAN.Physics.AngularRate.x', ...
                'MFE_CAN.Physics.AngularRate.y', 'MFE_CAN.Physics.AngularRate.z', ...
                'MFE_CAN.Physics.Velocity.x', 'MFE_CAN.Physics.Velocity.y', ...
                'MFE_CAN.Physics.Velocity.z', 'MFE_CAN.Physics.Euler.x', ...
                'MFE_CAN.Physics.Euler.y', 'MFE_CAN.Physics.Euler.z', ...
                'MFE_CAN.Physics.Valid', 'MFE_CAN.Steering.WheelAngleRad', ...
                'MFE_CAN.Steering.Valid'};
            for index = 1:numel(targets)
                testCase.verifySubstring(model, targets{index}, sprintf( ...
                    ['TorqueVect.mdl has no writer for %s. Run ' ...
                    'apply_torquevect_cm_truth.m in R2022a.'], targets{index}));
            end
            % The sources, so a model edited against the wrong quantity names
            % is caught too.
            for source = {'Sensor.Inertial.Param_B00.Acc_B.x', ...
                    'Sensor.Inertial.Param_B00.Omega_B.z', ...
                    'Sensor.Inertial.Param_B00.Vel_B.x', 'Steer.WhlAng'}
                testCase.verifySubstring(model, source{1}, sprintf( ...
                    'TorqueVect.mdl does not read %s.', source{1}));
            end
            % The superseded degrees contract must be gone from the model, or
            % a half-migrated TorqueVect would still be feeding a quantity
            % User.c no longer registers -- which fails silently, because a
            % Write CM Dict to an unknown name is not an error.
            testCase.verifyEmpty(strfind(model, 'MFE_CAN.Driver.SteeringAngleDeg'));
            testCase.verifyEmpty(strfind(model, 'MFE_CAN.Driver.SteeringSpeedDegPerSec'));
            % NOT asserted here: that Steer.WhlAng is the block actually wired
            % to MFE_CAN.Steering.WheelAngleRad. A text scan cannot follow a
            % signal line, and Car.SteerAngle* legitimately appears elsewhere
            % in this model -- the pre-existing torque-vectoring logic reads
            % road-wheel angle for its own purposes, which is correct there and
            % wrong only as a steering-TRUTH source. The wiring is proven by
            % the apply script (asserted above, and the only thing that builds
            % this subsystem) and by the Phase-17 runtime comparison of
            % Steer.WhlAng against the decoded 0x507 angle.
            testCase.verifySubstring(model, 'Steer.WhlAng');
        end

        % -------------------------------------------------------------- DBC

        function dbcParsesAndIdsAreUniqueWithinHil(testCase)
            [ids, names, lengths] = TestCm4slTruthSources.parseDbcMessages();
            testCase.verifyNotEmpty(ids, 'The DBC must contain BO_ messages.');
            testCase.verifyNumElements(unique(ids), numel(ids), ...
                'Every HIL CAN ID must be unique within the DBC.');
            testCase.verifyNumElements(unique(names), numel(names), ...
                'Every HIL message name must be unique within the DBC.');
            testCase.verifyTrue(all(lengths >= 1 & lengths <= 8), ...
                'Classic CAN payloads are 1-8 bytes.');
            testCase.verifyTrue(all(ids >= 0 & ids <= 2047), ...
                'Every frame in this contract is an 11-bit standard ID.');
            % 0x507 is provisional. This is a HIL-LOCAL uniqueness audit only:
            % no authoritative vehicle-wide CAN ID registry exists, so passing
            % here is not vehicle-wide approval.
            testCase.verifyEqual(sum(ids == 1287), 1);
        end

        function steeringFrameLayoutMatchesTheDecoder(testCase)
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            testCase.verifySubstring(dbc, 'BO_ 1287 CarMakerSteeringTruth: 8 CarMaker');
            % Signed Intel int16 at bit 0, 0.001 rad/count. Every field of
            % this line is load-bearing: @1 is Intel byte order, the trailing
            % minus is signedness, and the factor is the scale IO.c divides by.
            testCase.verifySubstring(dbc, ...
                'SG_ SteeringWheelAngleRad : 0|16@1- (0.001,0)');
            testCase.verifySubstring(dbc, '"rad" SpeedgoatHIL');
            % Reserved bytes 2-5 = bits 16..47, counter at 48, CRC at 56.
            testCase.verifySubstring(dbc, 'SG_ SteeringReserved : 16|32@1+ (1,0) [0|0]');
            testCase.verifySubstring(dbc, 'SG_ SteeringGroupCounter : 48|8@1+');
            testCase.verifySubstring(dbc, 'SG_ SteeringIntegrity : 56|8@1+');
            % The superseded degrees + angular-speed layout must be gone.
            testCase.verifyEmpty(strfind(dbc, 'SteeringWheelAngleDeg'));
            testCase.verifyEmpty(strfind(dbc, 'SteeringWheelSpeedDegPerSec'));
            testCase.verifyEmpty(strfind(dbc, 'CarMakerDriverSteering'));
        end

        function dbcScalesMatchTheDecodersOnBothSides(testCase)
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            io = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'IO.c'));
            % Scale appears in three places -- the DBC, the C sender, and the
            % MATLAB receiver -- and a mismatch is silent, so all three are
            % checked against each other rather than against a local copy.
            physics = { ...
                '1283 CarMakerPhysicsAcceleration', '(0.01,0)', '0x503, MFE_CAN_PhysicsAcceleration, 0.01'; ...
                '1284 CarMakerPhysicsAngularRate',  '(0.002,0)', '0x504, MFE_CAN_PhysicsAngularRate,  0.002'; ...
                '1285 CarMakerPhysicsVelocity',     '(0.01,0)', '0x505, MFE_CAN_PhysicsVelocity,     0.01'; ...
                '1286 CarMakerPhysicsEuler',        '(0.0001,0)', '0x506, MFE_CAN_PhysicsEuler,        0.0001'};
            for index = 1:size(physics, 1)
                testCase.verifySubstring(dbc, physics{index, 1});
                testCase.verifySubstring(dbc, physics{index, 2});
                testCase.verifySubstring(io, physics{index, 3}, ...
                    sprintf('IO.c scale for %s', physics{index, 1}));
            end
            % The MATLAB receiver's own table.
            decoder = TestCm4slTruthSources.readFile(fullfile( ...
                TestCm4slTruthSources.Root, 'VC_HIL', 'inverter', 'rxCAN', ...
                'decodeCarMakerPhysicsFrame.m'));
            testCase.verifySubstring(decoder, 'scales = [0.01 0.002 0.01 0.0001];');
            % Steering: DBC 0.001 rad, IO.c 0.001 rad, decoder 0.001 rad.
            testCase.verifySubstring(io, ...
                'MFE_PhysicsRoundSaturate(angleRad, 0.001)');
            steeringDecoder = TestCm4slTruthSources.readFile(fullfile( ...
                TestCm4slTruthSources.Root, 'VC_HIL', 'inverter', 'rxCAN', ...
                'decodeCarMakerSteeringFrame.m'));
            testCase.verifySubstring(steeringDecoder, ...
                'typecast(angleWord, ''int16'')) * 0.001');
        end

        function dbcCycleTimesMatchTheTenMillisecondProducer(testCase)
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            for id = {'1280', '1283', '1284', '1285', '1286', '1287'}
                testCase.verifySubstring(dbc, ...
                    sprintf('BA_ "GenMsgCycleTime" BO_ %s 10;', id{1}), ...
                    sprintf('BO_ %s is produced on the 10 ms IO_Out cycle.', id{1}));
            end
            % IO_Out runs at 1 ms and gates the CAN block on every tenth
            % cycle; if that ever changes, the DBC above is wrong.
            io = TestCm4slTruthSources.readFile( ...
                fullfile(TestCm4slTruthSources.Root, 'carmaker', 'FS_race', ...
                'src_cm4sl', 'src', 'IO.c'));
            testCase.verifySubstring(io, 'CycleNo % 10 != 0');
        end

        function dbcOwnershipAndDirectionMatchTheRouting(testCase)
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            % Channel 1 is CarMaker <-> Speedgoat only; channel 2 is Speedgoat
            % <-> VC only. The two buses must not be bridged, and the sensor
            % frames must not appear on the CarMaker bus.
            carMakerSent = {'1280', '1283', '1284', '1285', '1286', '1287'};
            for id = carMakerSent
                line = TestCm4slTruthSources.messageLine(dbc, id{1});
                testCase.verifyTrue(endsWith(strtrim(line), 'CarMaker'), ...
                    sprintf('BO_ %s must be transmitted by CarMaker.', id{1}));
            end
            for id = {'1281', '1282'}
                line = TestCm4slTruthSources.messageLine(dbc, id{1});
                testCase.verifyTrue(endsWith(strtrim(line), 'SpeedgoatHIL'), ...
                    sprintf('BO_ %s must be transmitted by the Speedgoat.', id{1}));
            end
            % The sensor frames the VCU reads are Speedgoat-sourced.
            for id = {'52', '50', '118', '688'}
                line = TestCm4slTruthSources.messageLine(dbc, id{1});
                testCase.verifyTrue(endsWith(strtrim(line), 'SpeedgoatHIL'), ...
                    sprintf('BO_ %s is a sensor frame the Speedgoat emits.', id{1}));
            end
            % And CarMaker must never be named as a receiver of them.
            for id = {'52', '50', '118', '688'}
                block = TestCm4slTruthSources.messageBlock(dbc, id{1});
                testCase.verifyEmpty(strfind(block, 'CarMaker'), ...
                    sprintf('BO_ %s must not be routed to CarMaker.', id{1}));
            end
            testCase.verifySubstring(dbc, ...
                'Frame 1287 stays on the CarMaker bus and is never forwarded to the VC bus.');
        end

        function dbcCounterAndCrcCommentsMatchTheImplementation(testCase)
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            % Same CRC parameters everywhere; a differing init or xorout is
            % the classic silent-integrity bug.
            crcText = 'CRC-8/SAE-J1850 over bytes 0..6 (poly 0x1D, init 0xFF, non-reflected, xorout 0xFF)';
            testCase.verifyGreaterThanOrEqual(numel(strfind(dbc, crcText)), 5, ...
                'Every 0x503-0x507 frame must document the same CRC.');
            % The shared truth-group counter is the coherence claim the
            % Speedgoat relies on to correlate steering with physics.
            testCase.verifyGreaterThanOrEqual(numel(strfind(dbc, ...
                'truth-group counter shared by 1283/1284/1285/1286 and 1287')), 4);
            testCase.verifySubstring(dbc, ...
                'Byte 6 is the SAME modulo-256 truth-group counter as 1283-1286');
        end
    end

    methods (Static, Access = private)
        function root = repoRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(fileparts(here)));
        end

        function path = dbcPath()
            path = fullfile(TestCm4slTruthSources.Root, 'carmaker', 'config', ...
                'MFE26_Inverter_CarMaker.dbc');
        end

        function text = readFile(path)
            assert(isfile(path), 'Missing file: %s', path);
            text = fileread(path);
        end

        function line = messageLine(dbc, id)
            token = sprintf('BO_ %s ', id);
            index = strfind(dbc, token);
            assert(~isempty(index), 'No BO_ %s in the DBC.', id);
            % The first hit is the definition; CM_ BO_ lines carry a prefix.
            for k = 1:numel(index)
                if index(k) == 1 || dbc(index(k) - 1) == newline || ...
                        dbc(index(k) - 1) == sprintf('\r')
                    tail = dbc(index(k):end);
                    stop = find(tail == newline, 1, 'first');
                    line = strtrim(tail(1:stop - 1));
                    return
                end
            end
            error('No standalone BO_ %s definition line.', id);
        end

        function block = messageBlock(dbc, id)
            line = TestCm4slTruthSources.messageLine(dbc, id);
            start = strfind(dbc, line);
            tail = dbc(start(1):end);
            % A message block runs to the first line that is not a SG_ entry.
            lines = strsplit(tail, newline);
            keep = lines(1);
            for k = 2:numel(lines)
                if startsWith(strtrim(lines{k}), 'SG_ ')
                    keep{end+1} = lines{k}; %#ok<AGROW>
                else
                    break
                end
            end
            block = strjoin(keep, newline);
        end

        function [ids, names, lengths] = parseDbcMessages()
            dbc = TestCm4slTruthSources.readFile( ...
                TestCm4slTruthSources.dbcPath());
            tokens = regexp(dbc, '(?m)^BO_\s+(\d+)\s+(\w+)\s*:\s*(\d+)\s+(\w+)\s*$', ...
                'tokens');
            ids = zeros(1, numel(tokens));
            names = cell(1, numel(tokens));
            lengths = zeros(1, numel(tokens));
            for k = 1:numel(tokens)
                ids(k) = str2double(tokens{k}{1});
                names{k} = tokens{k}{2};
                lengths(k) = str2double(tokens{k}{3});
            end
        end
    end
end
