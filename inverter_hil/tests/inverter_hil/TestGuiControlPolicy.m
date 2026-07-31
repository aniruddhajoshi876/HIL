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

                        healthy = lifecycle.isConnected && ...
                            interlocks.contractResolved && ...
                            interlocks.targetHealthy && ...
                            interlocks.heartbeatOk;
                        if ~healthy
                            % An unhealthy or unresolved target must not be
                            % able to arm anything at all.
                            TestGuiControlPolicy.verifyAllFalse(testCase, ...
                                policy, [stimulusGroups expertGroups], label);
                            continue;
                        end

                        expectedStimuli = lifecycle.isRunning;
                        for groupIndex = 1:numel(stimulusGroups)
                            testCase.verifyEqual( ...
                                policy.(stimulusGroups{groupIndex}), ...
                                expectedStimuli, [label ' ' ...
                                stimulusGroups{groupIndex}]);
                        end
                        testCase.verifyEqual(policy.plausibilityViolation, ...
                            expectedStimuli && ...
                            interlocks.plausibilityOverride, label);

                        if inDrive
                            % Conservative default for open decision 18:
                            % during Drive only pedal and digital stimuli.
                            TestGuiControlPolicy.verifyAllFalse(testCase, ...
                                policy, expertGroups, label);
                            continue;
                        end
                        if ~interlocks.expertMode
                            TestGuiControlPolicy.verifyAllFalse(testCase, ...
                                policy, expertGroups, label);
                            continue;
                        end

                        quiescent = ~lifecycle.isRunning || ...
                            strcmp(vcuState, 'LV_ON') || isempty(vcuState);
                        testCase.verifyEqual(policy.faultInjection, ...
                            quiescent, label);
                        testCase.verifyEqual(policy.plantParameters, ...
                            quiescent, label);
                        testCase.verifyEqual(policy.canFaults, ...
                            quiescent, label);
                        testCase.verifyEqual(policy.electrical, ...
                            quiescent, label);
                        testCase.verifyEqual(policy.calibration, ...
                            quiescent && ~lifecycle.isRunning, label);
                    end
                end
            end
            testCase.verifyEqual(combinations, ...
                numel(applicationStates) * numel(vcuStates) * size(flags, 1));
        end

        function driveOnlyPermitsPedalAndDigitalStimuli(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            interlocks.expertMode = true;
            policy = inverterhilgui.controlPolicy('running', 'RTD', ...
                interlocks);

            testCase.verifyTrue(policy.pedals);
            testCase.verifyTrue(policy.digitalStimuli);
            testCase.verifyTrue(policy.momentary);
            testCase.verifyFalse(policy.calibration);
            testCase.verifyFalse(policy.plantParameters);
            testCase.verifyFalse(policy.faultInjection);
            testCase.verifyFalse(policy.canFaults);
            testCase.verifyFalse(policy.electrical);
            testCase.verifyEqual(policy.reason, 'drive_restricted');
        end

        function expertGroupsRequireTheExpertInterlock(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            locked = inverterhilgui.controlPolicy('stopped', 'LV_ON', ...
                interlocks);
            testCase.verifyFalse(locked.faultInjection);
            testCase.verifyFalse(locked.calibration);
            testCase.verifyEqual(locked.reason, 'idle_locked');

            interlocks.expertMode = true;
            unlocked = inverterhilgui.controlPolicy('stopped', 'LV_ON', ...
                interlocks);
            testCase.verifyTrue(unlocked.faultInjection);
            testCase.verifyTrue(unlocked.plantParameters);
            testCase.verifyTrue(unlocked.calibration);
            testCase.verifyTrue(unlocked.canFaults);
            testCase.verifyEqual(unlocked.reason, 'expert_unlocked');
        end

        function calibrationStaysLockedWhileTheApplicationRuns(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            interlocks.expertMode = true;
            policy = inverterhilgui.controlPolicy('running', 'LV_ON', ...
                interlocks);

            testCase.verifyTrue(policy.plantParameters);
            testCase.verifyTrue(policy.faultInjection);
            testCase.verifyFalse(policy.calibration, ...
                'Plan 7.1 restricts hil_cal edits to a stopped application.');
        end

        function unhealthyTargetCannotArmThePedalInterface(testCase)
            failures = {'targetHealthy', 'heartbeatOk', 'contractResolved'};
            reasons = {'target_unhealthy', 'heartbeat_lost', ...
                'contract_unresolved'};
            for index = 1:numel(failures)
                interlocks = TestGuiControlPolicy.healthyInterlocks();
                interlocks.expertMode = true;
                interlocks.(failures{index}) = false;
                policy = inverterhilgui.controlPolicy('running', 'RTD', ...
                    interlocks);

                testCase.verifyFalse(policy.pedals, failures{index});
                testCase.verifyFalse(policy.armPedals, failures{index});
                testCase.verifyFalse(policy.digitalStimuli, failures{index});
                testCase.verifyFalse(policy.momentary, failures{index});
                testCase.verifyEqual(policy.reason, reasons{index});
            end
        end

        function plausibilityViolationNeedsBothRunningAndTheInterlock(testCase)
            interlocks = TestGuiControlPolicy.healthyInterlocks();
            testCase.verifyFalse(inverterhilgui.controlPolicy('running', ...
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
