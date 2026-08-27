classdef TestGuiCommandPipeline < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiCommandPipeline.workspaceRoot()));
        end
    end

    methods (Test)
        function doubleCommandsAreClampedToTheirDeclaredRange(testCase)
            contract = inverterhilgui.parameterContract();

            accepted = inverterhilgui.validateCommandValue(contract, ...
                'pedals.throttle', 0.25);
            testCase.verifyTrue(accepted.accepted);
            testCase.verifyFalse(accepted.clamped);
            testCase.verifyEqual(accepted.value, 0.25);
            testCase.verifyEqual(accepted.reason, 'accepted');

            high = inverterhilgui.validateCommandValue(contract, ...
                'pedals.throttle', 4.5);
            testCase.verifyTrue(high.accepted);
            testCase.verifyTrue(high.clamped);
            testCase.verifyEqual(high.value, 1);
            testCase.verifyEqual(high.reason, 'clamped');

            low = inverterhilgui.validateCommandValue(contract, ...
                'pedals.brake', -3);
            testCase.verifyTrue(low.clamped);
            testCase.verifyEqual(low.value, 0);
        end

        function integerAndLogicalCommandsAreTypeChecked(testCase)
            contract = inverterhilgui.parameterContract();

            result = inverterhilgui.validateCommandValue(contract, ...
                'can.drop_control_mask', 200);
            testCase.verifyTrue(result.accepted);
            testCase.verifyEqual(result.value, uint8(200));

            result = inverterhilgui.validateCommandValue(contract, ...
                'can.drop_control_mask', 300);
            testCase.verifyTrue(result.clamped);
            testCase.verifyEqual(result.value, uint8(255));

            result = inverterhilgui.validateCommandValue(contract, ...
                'can.drop_control_mask', 12.5);
            testCase.verifyFalse(result.accepted);
            testCase.verifyEqual(result.reason, 'value_not_integer');

            result = inverterhilgui.validateCommandValue(contract, ...
                'can.drop_control_mask', -1);
            testCase.verifyFalse(result.accepted);
            testCase.verifyEqual(result.reason, 'value_negative');

            result = inverterhilgui.validateCommandValue(contract, ...
                'digital.main_button', true);
            testCase.verifyTrue(result.accepted);
            testCase.verifyEqual(result.value, true);

            result = inverterhilgui.validateCommandValue(contract, ...
                'digital.main_button', 2);
            testCase.verifyFalse(result.accepted);
            testCase.verifyEqual(result.reason, 'value_not_logical');
        end

        function validationFailsClosedOnMalformedInput(testCase)
            contract = inverterhilgui.parameterContract();
            malformed = {NaN, Inf, complex(1, 1), [0.1 0.2], {}, 'high'};
            for index = 1:numel(malformed)
                result = inverterhilgui.validateCommandValue(contract, ...
                    'pedals.throttle', malformed{index});
                testCase.verifyFalse(result.accepted, sprintf('%d', index));
                testCase.verifyEqual(result.reason, 'malformed_value');
            end

            unknown = inverterhilgui.validateCommandValue(contract, ...
                'pedals.clutch', 0.5);
            testCase.verifyFalse(unknown.accepted);
            testCase.verifyEqual(unknown.reason, 'unknown_logical_name');

            nameless = inverterhilgui.validateCommandValue(contract, 42, 0.5);
            testCase.verifyFalse(nameless.accepted);
            testCase.verifyEqual(nameless.reason, 'malformed_logical_name');
        end

        function coalescerEmitsTheNewestValueAndDropsIntermediates(testCase)
            coalescer = inverterhilgui.sliderCoalescer(0.020);

            first = coalescer.submit(10, 0);
            testCase.verifyTrue(first.hasValue);
            testCase.verifyEqual(first.value, 10);

            testCase.verifyFalse(coalescer.submit(20, 0.001).hasValue);
            testCase.verifyFalse(coalescer.submit(30, 0.002).hasValue);
            testCase.verifyFalse(coalescer.submit(40, 0.003).hasValue);
            testCase.verifyFalse(coalescer.poll(0.010).hasValue);

            emitted = coalescer.poll(0.021);
            testCase.verifyTrue(emitted.hasValue);
            testCase.verifyEqual(emitted.value, 40, ...
                'Only the newest pending value may be emitted.');
            testCase.verifyEqual(coalescer.EmittedCount, 2);
            testCase.verifyEqual(coalescer.DroppedCount, 2, ...
                'Values 20 and 30 were replaced before they could be sent.');
            testCase.verifyFalse(coalescer.poll(0.5).hasValue);
        end

        function coalescerNeverReordersEmissions(testCase)
            coalescer = inverterhilgui.sliderCoalescer(0.030);
            values = 1:200;
            times = linspace(0, 1, numel(values));
            emitted = [];
            emittedTimes = [];
            for index = 1:numel(values)
                out = coalescer.submit(values(index), times(index));
                if out.hasValue
                    emitted(end + 1) = out.value; %#ok<AGROW>
                    emittedTimes(end + 1) = out.timeS; %#ok<AGROW>
                end
            end

            testCase.verifyTrue(issorted(emitted, 'strictascend'));
            testCase.verifyTrue(issorted(emittedTimes, 'strictascend'));
            testCase.verifyGreaterThanOrEqual(min(diff(emittedTimes)), ...
                0.030 - 1e-12);
            testCase.verifyLessThan(numel(emitted), numel(values));
            testCase.verifyEqual(emitted(end), max(emitted));
        end

        function coalescerRateIsRestrictedToTheHostWindow(testCase)
            testCase.verifyError( ...
                @() inverterhilgui.sliderCoalescer(0.010), ...
                'inverterhilgui:InvalidCoalescerRate');
            testCase.verifyError( ...
                @() inverterhilgui.sliderCoalescer(0.060), ...
                'inverterhilgui:InvalidCoalescerRate');
            testCase.verifyError( ...
                @() inverterhilgui.sliderCoalescer(NaN), ...
                'inverterhilgui:InvalidCoalescerRate');
            testCase.verifyEqual( ...
                inverterhilgui.sliderCoalescer(0.050).RateS, 0.050);
            testCase.verifyEqual( ...
                inverterhilgui.sliderCoalescer().RateS, 0.030);

            coalescer = inverterhilgui.sliderCoalescer(0.020);
            testCase.verifyError(@() coalescer.submit(NaN, 0), ...
                'inverterhilgui:InvalidCoalescerValue');
            testCase.verifyError(@() coalescer.submit(1, NaN), ...
                'inverterhilgui:InvalidCoalescerTime');
        end

        function sequenceCounterIsMonotonicModuloTwoToThe32(testCase)
            testCase.verifyEqual(inverterhilgui.sequenceCommand(uint32(0)), ...
                uint32(1));
            testCase.verifyEqual(inverterhilgui.sequenceCommand(0), uint32(1));
            testCase.verifyEqual( ...
                inverterhilgui.sequenceCommand(uint32(4294967294)), ...
                uint32(4294967295));
            testCase.verifyEqual( ...
                inverterhilgui.sequenceCommand(uint32(4294967295)), ...
                uint32(0), 'The counter must wrap, not saturate.');

            value = uint32(4294967290);
            seen = zeros(1, 10, 'uint32');
            for index = 1:10
                value = inverterhilgui.sequenceCommand(value);
                seen(index) = value;
            end
            testCase.verifyEqual(seen, uint32([4294967291 4294967292 ...
                4294967293 4294967294 4294967295 0 1 2 3 4]));
            testCase.verifyEqual(numel(unique(seen)), 10);

            bad = {-1, 1.5, NaN, Inf, 4294967296, [1 2], 'a', complex(1, 1)};
            for index = 1:numel(bad)
                testCase.verifyError( ...
                    @() inverterhilgui.sequenceCommand(bad{index}), ...
                    'inverterhilgui:InvalidSequenceCounter', ...
                    sprintf('%d', index));
            end
        end

        function auditRecordsUseAFixedFieldOrder(testCase)
            record = inverterhilgui.auditRecord(struct( ...
                'hostTime', '2026-07-31 12:00:00.000', ...
                'targetTimeS', 12.5, ...
                'logicalName', 'pedals.throttle', ...
                'targetPath', 'hil_cmd.pedals.throttle', ...
                'requested', 0.25, ...
                'applied', 0.25, ...
                'result', 'applied', ...
                'detail', 'ok'));

            testCase.verifyEqual(fieldnames(record), {'hostTime'; ...
                'targetTimeS'; 'logicalName'; 'targetPath'; 'requested'; ...
                'applied'; 'result'; 'detail'});
            testCase.verifyEqual(record.hostTime, '2026-07-31 12:00:00.000');
            testCase.verifyEqual(record.targetTimeS, 12.5);
            testCase.verifyEqual(record.requested, '0.25');
            testCase.verifyEqual(record.result, 'applied');

            logical = inverterhilgui.auditRecord(struct( ...
                'logicalName', 'digital.main_button', ...
                'requested', true, 'applied', false, 'result', 'mismatch'));
            testCase.verifyEqual(logical.requested, 'true');
            testCase.verifyEqual(logical.applied, 'false');
            testCase.verifyEqual(logical.result, 'mismatch');
            testCase.verifyNotEmpty(logical.hostTime);
            testCase.verifyEqual(logical.targetTimeS, NaN);
        end

        function auditRecordsRejectUnattributableCommands(testCase)
            record = inverterhilgui.auditRecord(struct('result', 'applied'));
            testCase.verifyEqual(record.result, 'rejected');
            testCase.verifyEqual(record.detail, 'missing_logical_name');

            record = inverterhilgui.auditRecord(struct( ...
                'logicalName', 'pedals.brake', 'result', 'succeeded'));
            testCase.verifyEqual(record.result, 'rejected');
            testCase.verifyEqual(record.detail, 'unknown_result_code');

            record = inverterhilgui.auditRecord(42);
            testCase.verifyEqual(record.result, 'rejected');
            testCase.verifyEqual(record.applied, '--');
        end

        function sessionLogIsAppendOnlyAndExportsWithoutMutating(testCase)
            log = inverterhilgui.sessionLog();
            testCase.verifyEqual(log.Count, 0);
            for index = 1:5
                log.append(struct('logicalName', ...
                    sprintf('pedals.throttle%d', index), ...
                    'requested', index, 'applied', index, ...
                    'result', 'applied', 'targetTimeS', index));
            end
            testCase.verifyEqual(log.Count, 5);

            before = log.snapshot();
            folder = TestGuiCommandPipeline.temporaryFolder(testCase);
            target = fullfile(folder, 'log.csv');
            log.export(target);

            testCase.verifyEqual(log.Count, 5);
            testCase.verifyEqual(log.snapshot(), before);
            testCase.verifyEqual(exist(target, 'file'), 2);
            text = fileread(target);
            testCase.verifySubstring(text, 'hostTime');
            testCase.verifySubstring(text, 'pedals.throttle3');
            testCase.verifyEqual(numel(strfind(text, newline)), 6);

            % The log has no method that removes or edits a record.
            names = methods(log);
            forbidden = {'clear', 'remove', 'delete_record', 'set'};
            for index = 1:numel(forbidden)
                testCase.verifyFalse(any(strcmp(names, forbidden{index})));
            end
            testCase.verifyError(@() log.export(''), ...
                'inverterhilgui:InvalidExportTarget');
        end

        function targetWriteReportsRequestedAppliedClampAndMismatch(testCase)
            backend = inverterhilgui.fakeTargetBackend();
            session = inverterhilgui.targetSession('FakePC', backend);
            session.connect();

            applied = session.write('pedals.throttle', 0.4);
            testCase.verifyTrue(applied.success);
            testCase.verifyFalse(applied.mismatch);
            testCase.verifyFalse(applied.clamped);
            testCase.verifyEqual(applied.requested, 0.4);
            testCase.verifyEqual(applied.applied, 0.4);
            testCase.verifyEqual(applied.path, 'hil_cmd.pedals.throttle');
            testCase.verifyEqual(applied.reason, 'applied');

            clamped = session.write('pedals.throttle', 2.5);
            testCase.verifyTrue(clamped.success);
            testCase.verifyTrue(clamped.clamped);
            testCase.verifyEqual(clamped.requested, 1);
            testCase.verifyEqual(clamped.reason, 'clamped');

            backend.AppliedOverride = 0.125;
            mismatched = session.write('pedals.brake', 0.75);
            testCase.verifyTrue(mismatched.success);
            testCase.verifyTrue(mismatched.mismatch);
            testCase.verifyEqual(mismatched.requested, 0.75);
            testCase.verifyEqual(mismatched.applied, 0.125);
            testCase.verifyEqual(mismatched.reason, 'mismatch');
        end

        function failedWritesAreReportedAndNeverLookApplied(testCase)
            backend = inverterhilgui.fakeTargetBackend();
            session = inverterhilgui.targetSession('FakePC', backend);
            session.connect();
            backend.FailNextCall = true;

            failed = session.write('pedals.throttle', 0.5);

            testCase.verifyFalse(failed.success);
            testCase.verifyEmpty(failed.applied);
            testCase.verifyEqual(failed.reason, 'write_failed');

            log = inverterhilgui.sessionLog();
            log.append(struct('logicalName', 'pedals.throttle', ...
                'targetPath', failed.path, 'requested', failed.requested, ...
                'applied', failed.applied, 'result', 'failed', ...
                'detail', failed.reason));
            record = log.snapshot();
            testCase.verifyEqual(record(1).result, 'failed');
            testCase.verifyEqual(record(1).applied, '--');
            testCase.verifyEqual(record(1).detail, 'write_failed');
        end

        function writingBeforeConnectionIsRefused(testCase)
            session = inverterhilgui.targetSession('FakePC', ...
                inverterhilgui.fakeTargetBackend());

            result = session.write('pedals.throttle', 0.5);

            testCase.verifyFalse(result.success);
            testCase.verifyEqual(result.reason, 'contract_unresolved');
        end

        function logSurvivesDisconnectAndReconnect(testCase)
            backend = inverterhilgui.fakeTargetBackend();
            session = inverterhilgui.targetSession('FakePC', backend);
            log = inverterhilgui.sessionLog();

            session.connect();
            result = session.write('pedals.throttle', 0.5);
            log.append(struct('logicalName', 'pedals.throttle', ...
                'requested', result.requested, 'applied', result.applied, ...
                'result', 'applied'));
            session.disconnect();
            testCase.verifyEqual(log.Count, 1);

            session.connect();
            result = session.write('pedals.brake', 0.25);
            log.append(struct('logicalName', 'pedals.brake', ...
                'requested', result.requested, 'applied', result.applied, ...
                'result', 'applied'));

            testCase.verifyEqual(log.Count, 2);
            records = log.snapshot();
            testCase.verifyEqual(records(1).logicalName, 'pedals.throttle');
            testCase.verifyEqual(records(2).logicalName, 'pedals.brake');
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end

        function folder = temporaryFolder(testCase)
            fixture = testCase.applyFixture( ...
                matlab.unittest.fixtures.TemporaryFolderFixture);
            folder = fixture.Folder;
        end
    end
end
