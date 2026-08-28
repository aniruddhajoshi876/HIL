classdef TestGuiParameterContract < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiParameterContract.workspaceRoot()));
        end
    end

    methods (Test)
        function contractDeclaresTypeRangeAndBothBackings(testCase)
            contract = inverterhilgui.params.parameterContract();
            testCase.verifyGreaterThan(numel(contract), 20);

            allowedTypes = {'double', 'logical', 'uint8', 'uint16', 'uint32'};
            names = cell(1, numel(contract));
            for index = 1:numel(contract)
                item = contract(index);
                names{index} = item.name;
                testCase.verifyTrue(any(strcmp(item.type, allowedTypes)), ...
                    item.name);
                testCase.verifyTrue(isnumeric(item.minimum) && ...
                    isscalar(item.minimum) && isfinite(item.minimum));
                testCase.verifyTrue(isnumeric(item.maximum) && ...
                    isscalar(item.maximum) && isfinite(item.maximum));
                testCase.verifyLessThanOrEqual(item.minimum, item.maximum);
                testCase.verifyNotEmpty(item.structPath);
                testCase.verifyNotEmpty(item.flatPath);
                testCase.verifyNotEqual(item.structPath, item.flatPath);
                testCase.verifyTrue(islogical(item.required));
                testCase.verifyNotEmpty(item.group);
            end
            testCase.verifyEqual(numel(unique(names)), numel(names));

            required = {'pedals.throttle', 'pedals.brake', ...
                'steering.stale', 'steering.malformed', ...
                'steering.invalid_status', 'steering.angle_sentinel', ...
                'steering.speed_sentinel', ...
                'steering.calibration_sequence', 'imu.stale', ...
                'imu.malformed', ...
                'digital.main_button', 'digital.cooling_switch', ...
                'digital.shutdown_feedback', 'digital.precharge_sequence', ...
                'can.drop_control_mask', 'can.drop_status_mask', ...
                'gui_heartbeat'};
            for index = 1:numel(required)
                testCase.verifyNotEmpty( ...
                    inverterhilgui.params.contractEntry(contract, required{index}), ...
                    required{index});
            end
        end

        function nestedStructBackingIsDiscovered(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = TestGuiParameterContract.pathsOf(contract, 'structPath');
            resolved = inverterhilgui.params.discoverContract(paths, contract);

            testCase.verifyEqual(resolved.backing, 'struct');
            testCase.verifyEqual(resolved.resolvedCount, numel(contract));
            testCase.verifyEmpty(resolved.missing);
            entry = inverterhilgui.params.contractEntry(resolved, 'pedals.throttle');
            testCase.verifyEqual(entry.path, 'hil_cmd.pedals.throttle');
            testCase.verifyEqual(entry.backing, 'struct');
        end

        function flatScalarBackingIsDiscovered(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = TestGuiParameterContract.pathsOf(contract, 'flatPath');
            resolved = inverterhilgui.params.discoverContract(paths, contract);

            testCase.verifyEqual(resolved.backing, 'flat');
            testCase.verifyEqual(resolved.resolvedCount, numel(contract));
            entry = inverterhilgui.params.contractEntry(resolved, 'pedals.brake');
            testCase.verifyEqual(entry.path, 'hil_cmd_pedals_brake');
            testCase.verifyEqual(entry.backing, 'flat');
        end

        function mixedBackingResolvesEachNameIndependently(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = cell(1, numel(contract));
            for index = 1:numel(contract)
                if mod(index, 2) == 0
                    paths{index} = contract(index).flatPath;
                else
                    paths{index} = contract(index).structPath;
                end
            end
            resolved = inverterhilgui.params.discoverContract(paths, contract);

            testCase.verifyEqual(resolved.backing, 'mixed');
            testCase.verifyEqual(resolved.resolvedCount, numel(contract));
            testCase.verifyGreaterThan(resolved.structCount, 0);
            testCase.verifyGreaterThan(resolved.flatCount, 0);
        end

        function structBackingWinsWhenBothArePresent(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = [TestGuiParameterContract.pathsOf(contract, 'structPath'), ...
                TestGuiParameterContract.pathsOf(contract, 'flatPath')];
            resolved = inverterhilgui.params.discoverContract(paths, contract);

            testCase.verifyEqual(resolved.backing, 'struct');
            testCase.verifyEqual(resolved.flatCount, 0);
        end

        function missingRequiredPathIsAVersionMismatchNotAFallback(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = TestGuiParameterContract.pathsOf(contract, 'structPath');
            keep = ~strcmp(paths, 'hil_cmd.pedals.throttle') & ...
                ~strcmp(paths, 'hil_cmd.gui_heartbeat');

            testCase.verifyError( ...
                @() inverterhilgui.params.discoverContract(paths(keep), contract), ...
                'inverterhilgui:VersionMismatch');

            err = [];
            try
                inverterhilgui.params.discoverContract(paths(keep), contract);
            catch caught
                err = caught;
            end
            testCase.verifyNotEmpty(err);
            testCase.verifySubstring(err.message, 'pedals.throttle');
            testCase.verifySubstring(err.message, 'gui_heartbeat');
            testCase.verifySubstring(err.message, 'hil_cmd_pedals_throttle');
        end

        function optionalPathsMayBeAbsentWithoutError(testCase)
            contract = inverterhilgui.params.parameterContract();
            paths = {};
            for index = 1:numel(contract)
                if contract(index).required
                    paths{end + 1} = contract(index).structPath; %#ok<AGROW>
                end
            end
            resolved = inverterhilgui.params.discoverContract(paths, contract);

            testCase.verifyNotEmpty(resolved.missing);
            testCase.verifyTrue(any(strcmp(resolved.missing, ...
                'cal.pedals.released_v1')));
            testCase.verifyEmpty( ...
                inverterhilgui.params.contractEntry(resolved, 'cal.pedals.pressed_v1'));
        end

        function emptyApplicationListingFailsLoudly(testCase)
            testCase.verifyError( ...
                @() inverterhilgui.params.discoverContract({}), ...
                'inverterhilgui:VersionMismatch');
            testCase.verifyError( ...
                @() inverterhilgui.params.discoverContract(42), ...
                'inverterhilgui:InvalidContract');
        end

        function connectReadsTargetValuesAndPushesNoHostDefaults(testCase)
            backend = inverterhilgui.sg_adapters.fakeTargetBackend();
            backend.Values('hil_cmd.pedals.throttle') = 0.375;
            session = inverterhilgui.live_telemetry.targetSession('FakePC', backend);

            result = session.connect();

            testCase.verifyTrue(result.success);
            testCase.verifyEqual(backend.WriteCount, 0, ...
                'Connect must not push host defaults to the target.');
            [value, known] = session.readCached('pedals.throttle');
            testCase.verifyTrue(known);
            testCase.verifyEqual(value, 0.375);
            testCase.verifyNotEmpty(session.Contract);
        end

        function connectAgainstAWrongApplicationReportsVersionMismatch(testCase)
            backend = inverterhilgui.sg_adapters.fakeTargetBackend({'hil_cmd.something'});
            session = inverterhilgui.live_telemetry.targetSession('FakePC', backend);

            result = session.connect();

            testCase.verifyFalse(result.success);
            testCase.verifySubstring(result.reason, 'required');
            testCase.verifyEmpty(session.Contract);
            testCase.verifyEqual(session.State, 'disconnected');
        end

        function noGuiSourceUsesForceOrStructReadModifyWrite(testCase)
            root = TestGuiParameterContract.workspaceRoot();
            % +inverterhilgui's members now live one level down, split by
            % role into +sg_adapters/+params/+writes/+state_machine/
            % +live_telemetry/+logging sub-packages, so this must recurse
            % rather than list '+inverterhilgui' itself (which no longer
            % holds any .m files directly and would silently check zero
            % files, disabling this safety-policy scan).
            files = dir(fullfile(root, '+inverterhilgui', '**', '*.m'));
            files(end + 1) = dir(fullfile(root, 'inverter_hil_app.m'));
            for index = 1:numel(files)
                code = TestGuiParameterContract.strippedCode(fullfile( ...
                    files(index).folder, files(index).name));
                testCase.verifyEmpty(regexp(code, ...
                    '[Ff]orce\s*=\s*true|''Force''', 'once'), ...
                    files(index).name);
                testCase.verifyEmpty(regexp(code, ...
                    'setparam\([^)]*hil_cmd\s*\)', 'once'), ...
                    files(index).name);
            end
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end

        function code = strippedCode(fileName)
            % Executable lines only; documentation may legitimately mention
            % the prohibited constructs while explaining why they are absent.
            lines = strsplit(fileread(fileName), newline);
            keep = true(1, numel(lines));
            for index = 1:numel(lines)
                trimmed = strtrim(lines{index});
                keep(index) = ~isempty(trimmed) && trimmed(1) ~= '%';
            end
            code = strjoin(lines(keep), newline);
        end

        function paths = pathsOf(contract, field)
            paths = cell(1, numel(contract));
            for index = 1:numel(contract)
                paths{index} = contract(index).(field);
            end
        end
    end
end
