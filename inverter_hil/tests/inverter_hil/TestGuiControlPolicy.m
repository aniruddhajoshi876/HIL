classdef TestGuiControlPolicy < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiControlPolicy.workspaceRoot()));
        end
    end

    methods (Test)
        function policyMatrixHoldsForEveryStateAndInterlockCombination(testCase)
            applicationStates = {'disconnected', 'connecting', 'connected', ...
                'loaded', 'running', 'stopped', 'error'};
            vcuStates = {'', 'LV_ON', 'PRECHARGING', 'ENABLE', 'BUZZING', ...
                'RTD', 'ERROR'};
            flags = TestGuiControlPolicy.allFlagCombinations();
            expertGroups = {'electrical', 'plantParameters', ...
                'calibration', 'faultInjection', 'canFaults'};
            stimulusGroups = {'pedals', 'digitalStimuli', 'momentary', ...
                'armPedals'};
            combinations = 0;

            for stateIndex = 1:numel(applicationStates)
                applicationState = applicationStates{stateIndex};
                lifecycle = inverterhilgui.connectionState(applicationState);
                for vcuIndex = 1:numel(vcuStates)
                    vcuState = vcuStates{vcuIndex};
                    inDrive = any(strcmp(vcuState, ...
                        {'ENABLE', 'BUZZING', 'RTD'}));
                    for flagIndex = 1:size(flags, 1)
                        interlocks = TestGuiControlPolicy.interlockStruct( ...
                            flags(flagIndex, :));
                        policy = inverterhilgui.controlPolicy( ...
                            applicationState, vcuState, interlocks);
                        combinations = combinations + 1;

                        label = sprintf('%s|%s|%d%d%d%d%d', ...
                            applicationState, vcuState, flags(flagIndex, :));
                        testCase.verifyTrue(policy.connectionControls, label);

                        % INTERLOCKS REMOVED 2026-08-02: connection is now
                        % the only gate. targetHealthy, heartbeatOk,
                        % contractResolved, expertMode and the Drive
                        % restriction no longer affect any group. This matrix
                        % therefore asserts that the policy is INDIFFERENT to
                        % those flags -- which is the property that would
                        % break first if a gate were accidentally reinstated
                        % or a new one added.
                        if ~lifecycle.isConnected
                            TestGuiControlPolicy.verifyAllFalse(testCase, ...
                                policy, [stimulusGroups expertGroups], label);
                            testCase.verifyEqual(policy.reason, ...
                                'not_connected', label);
                            continue;
                        end

                        % Stimuli still require a running application. That
                        % is functional, not safety: SETPARAM against a
                        % stopped target fails, so enabling those widgets
                        % would only produce write errors.
                        expectedStimuli = lifecycle.isRunning;
                        for groupIndex = 1:numel(stimulusGroups)
                            testCase.verifyEqual( ...
                                policy.(stimulusGroups{groupIndex}), ...
                                expectedStimuli, [label ' ' ...
                                stimulusGroups{groupIndex}]);
                        end
                        testCase.verifyEqual(policy.plausibilityViolation, ...
                            expectedStimuli, label);

                        % Expert groups are unconditionally open, including
                        % during Drive and regardless of expertMode.
                        for groupIndex = 1:numel(expertGroups)
                            testCase.verifyTrue( ...
                                policy.(expertGroups{groupIndex}), ...
                                [label ' ' expertGroups{groupIndex}]);
                        end
                        testCase.verifyTrue(policy.expertGroupsUnlocked, label);
                        if lifecycle.isRunning
                            testCase.verifyEqual(policy.reason, ...
                                'interlocks_removed_running', label);
                        else
                            testCase.verifyEqual(policy.reason, ...
                                'interlocks_removed_stopped', label);
                        end
                    end
                end
            end
            testCase.verifyEqual(combinations, ...
                numel(applicationStates) * numel(vcuStates) * size(flags, 1));
        end

        function driveNoLongerRestrictsExpertGroups(testCase)
            % Was DRIVEONLYPERMITSPEDALANDDIGITALSTIMULI. The Drive
            % restriction (open decision 18's conservative default) was
            % removed on 2026-08-02 by explicit operator decision, so every
            % group stays live while the VCU is in ENABLE/BUZZING/RTD.
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            policy = inverterhilgui.controlPolicy('running', 'RTD', ...
                interlocks);

            testCase.verifyTrue(policy.pedals);
            testCase.verifyTrue(policy.digitalStimuli);
            testCase.verifyTrue(policy.momentary);
            testCase.verifyTrue(policy.calibration);
            testCase.verifyTrue(policy.plantParameters);
            testCase.verifyTrue(policy.faultInjection);
            testCase.verifyTrue(policy.canFaults);
            testCase.verifyTrue(policy.electrical);
            testCase.verifyEqual(policy.reason, 'interlocks_removed_running');
        end

        function expertGroupsNoLongerRequireTheExpertInterlock(testCase)
            % Was EXPERTGROUPSREQUIRETHEEXPERTINTERLOCK. expertMode no longer
            % gates anything; the flag is still validated and carried, so
            % reinstating the gate is a one-line change in CONTROLPOLICY.
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            withoutExpert = inverterhilgui.controlPolicy('stopped', ...
                'LV_ON', interlocks);
            interlocks.expertMode = true;
            withExpert = inverterhilgui.controlPolicy('stopped', 'LV_ON', ...
                interlocks);

            for policy = [withoutExpert withExpert]
                testCase.verifyTrue(policy.faultInjection);
                testCase.verifyTrue(policy.plantParameters);
                testCase.verifyTrue(policy.calibration);
                testCase.verifyTrue(policy.canFaults);
                testCase.verifyEqual(policy.reason, ...
                    'interlocks_removed_stopped');
            end
        end

        function calibrationIsEditableWhileTheApplicationRuns(testCase)
            % Was CALIBRATIONSTAYSLOCKEDWHILETHEAPPLICATIONRUNS. Plan 7.1's
            % "hil_cal may change only while stopped until validated" is no
            % longer enforced.
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            policy = inverterhilgui.controlPolicy('running', 'LV_ON', ...
                interlocks);

            testCase.verifyTrue(policy.plantParameters);
            testCase.verifyTrue(policy.faultInjection);
            testCase.verifyTrue(policy.calibration);
        end

        function unhealthyTargetCanStillArmThePedalInterface(testCase)
            % Was UNHEALTHYTARGETCANNOTARMTHEPEDALINTERFACE. This is the
            % sharpest consequence of removing the interlocks and is asserted
            % explicitly rather than merely implied: pedal and digital
            % commands stay enabled against an unhealthy target, a lost
            % heartbeat, or an unresolved parameter contract.
            failures = {'targetHealthy', 'heartbeatOk', 'contractResolved'};
            for index = 1:numel(failures)
                interlocks = TestGuiControlPolicy.healthyInterlocks();
                interlocks.(failures{index}) = false;
                policy = inverterhilgui.controlPolicy('running', 'RTD', ...
                    interlocks);

                testCase.verifyTrue(policy.pedals, failures{index});
                testCase.verifyTrue(policy.armPedals, failures{index});
                testCase.verifyTrue(policy.digitalStimuli, failures{index});
                testCase.verifyTrue(policy.momentary, failures{index});
                testCase.verifyEqual(policy.reason, ...
                    'interlocks_removed_running', failures{index});
            end
        end

        function plausibilityViolationNeedsOnlyRunning(testCase)
            % Was PLAUSIBILITYVIOLATIONNEEDSBOTHRUNNINGANDTHEINTERLOCK. The
            % plausibilityOverride interlock no longer gates the group; only
            % the functional running requirement remains.
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            testCase.verifyTrue(inverterhilgui.controlPolicy('running', ...
                'LV_ON', interlocks).plausibilityViolation);

            interlocks.plausibilityOverride = true;
            testCase.verifyTrue(inverterhilgui.controlPolicy('running', ...
                'LV_ON', interlocks).plausibilityViolation);
            testCase.verifyFalse(inverterhilgui.controlPolicy('stopped', ...
                'LV_ON', interlocks).plausibilityViolation);
        end

        function malformedInputFailsClosed(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            groups = {'pedals', 'digitalStimuli', 'momentary', ...
                'armPedals', 'electrical', 'plantParameters', ...
                'calibration', 'faultInjection', 'canFaults'};

            malformed = {struct(), 42, {true}, ...
                rmfield(interlocks, 'expertMode')};
            for index = 1:numel(malformed)
                policy = inverterhilgui.controlPolicy('running', 'LV_ON', ...
                    malformed{index});
                TestGuiControlPolicy.verifyAllFalse(testCase, policy, ...
                    groups, sprintf('malformed %d', index));
            end

            badValues = {2, NaN, [true true], complex(1, 1), 'yes'};
            for index = 1:numel(badValues)
                candidate = interlocks;
                candidate.targetHealthy = badValues{index};
                policy = inverterhilgui.controlPolicy('running', 'LV_ON', ...
                    candidate);
                TestGuiControlPolicy.verifyAllFalse(testCase, policy, ...
                    groups, sprintf('bad value %d', index));
                testCase.verifyEqual(policy.reason, 'malformed_targetHealthy');
            end

            policy = inverterhilgui.controlPolicy('not_a_state', 'RTD', ...
                interlocks);
            TestGuiControlPolicy.verifyAllFalse(testCase, policy, groups, ...
                'unknown state');
            testCase.verifyEqual(policy.reason, 'unknown_application_state');
            testCase.verifyFalse(policy.connectionControls);
        end

        function canDrivingLocksOnlyPedalsAndDefaultsFalse(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            withoutArg = inverterhilgui.controlPolicy('running', 'RTD', interlocks);
            explicitFalse = inverterhilgui.controlPolicy('running', 'RTD', interlocks, false);
            testCase.verifyEqual(withoutArg, explicitFalse);
            driving = inverterhilgui.controlPolicy('running', 'RTD', interlocks, true);
            testCase.verifyFalse(driving.pedals);
            testCase.verifyTrue(driving.canDriving);
            testCase.verifyTrue(driving.digitalStimuli);
            testCase.verifyTrue(driving.momentary);
            malformed = inverterhilgui.controlPolicy('running', 'RTD', interlocks, 2);
            testCase.verifyEqual(malformed.reason, 'malformed_canDriving');
        end

        function policyIsTheOnlyEnableAuthorityInTheAppClass(testCase)
            root = TestGuiControlPolicy.workspaceRoot();
            text = fileread(fullfile(root, 'inverter_hil_app.m'));
            enableWrites = regexp(text, '\.Enable\s*=', 'match');
            testCase.verifyEmpty(enableWrites, ...
                ['Enable must only be set through applyEnable, which is ' ...
                'driven by inverterhilgui.controlPolicy.']);
            testCase.verifySubstring(text, 'inverterhilgui.controlPolicy');
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end

        function flags = allFlagCombinations()
            count = 5;
            rows = 2 ^ count;
            flags = false(rows, count);
            for row = 1:rows
                bits = bitget(uint8(row - 1), 1:count);
                flags(row, :) = logical(bits);
            end
        end

        function interlocks = interlockStruct(row)
            interlocks = struct( ...
                'expertMode', row(1), ...
                'plausibilityOverride', row(2), ...
                'targetHealthy', row(3), ...
                'heartbeatOk', row(4), ...
                'contractResolved', row(5));
        end

        function interlocks = healthyInterlocks()
            interlocks = struct( ...
                'expertMode', false, ...
                'plausibilityOverride', false, ...
                'targetHealthy', true, ...
                'heartbeatOk', true, ...
                'contractResolved', true);
        end

        function verifyAllFalse(testCase, policy, groups, label)
            for index = 1:numel(groups)
                testCase.verifyFalse(policy.(groups{index}), ...
                    [label ' ' groups{index}]);
            end
        end
    end
end
