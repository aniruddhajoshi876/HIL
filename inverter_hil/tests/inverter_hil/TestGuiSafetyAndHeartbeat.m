classdef TestGuiSafetyAndHeartbeat < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiSafetyAndHeartbeat.workspaceRoot()));
        end
    end

    methods (Test)
        function heartbeatAdvancesAsAWrapSafeUint32Counter(testCase)
            state = struct('counter', uint32(0), 'lastUpdateS', NaN);
            result = inverterhilgui.heartbeatState(state, 10, 0.5);

            testCase.verifyEqual(result.counter, uint32(1));
            testCase.verifyClass(result.counter, 'uint32');
            testCase.verifyTrue(result.expired);
            testCase.verifyEqual(result.reason, 'no_previous_beat');

            state = struct('counter', result.counter, ...
                'lastUpdateS', result.lastUpdateS);
            result = inverterhilgui.heartbeatState(state, 10.25, 0.5);
            testCase.verifyEqual(result.counter, uint32(2));
            testCase.verifyEqual(result.ageS, 0.25, 'AbsTol', 1e-12);
            testCase.verifyFalse(result.expired);
            testCase.verifyEqual(result.reason, 'healthy');

            state = struct('counter', uint32(4294967295), ...
                'lastUpdateS', 10);
            result = inverterhilgui.heartbeatState(state, 10.1, 0.5);
            testCase.verifyEqual(result.counter, uint32(0));
        end

        function stalledHostTimerIsReportedAsAnExpiredHeartbeat(testCase)
            state = struct('counter', uint32(7), 'lastUpdateS', 100);

            result = inverterhilgui.heartbeatState(state, 100.5, 0.5);
            testCase.verifyFalse(result.expired);

            result = inverterhilgui.heartbeatState(state, 100.51, 0.5);
            testCase.verifyTrue(result.expired);
            testCase.verifyEqual(result.reason, 'heartbeat_expired');
            testCase.verifyEqual(result.ageS, 0.51, 'AbsTol', 1e-12);
        end

        function heartbeatFailsClosedOnMalformedInput(testCase)
            good = struct('counter', uint32(3), 'lastUpdateS', 5);
            cases = { ...
                {42, 6, 0.5, 'malformed_previous_state'}, ...
                {struct('counter', uint32(1)), 6, 0.5, ...
                    'malformed_previous_state'}, ...
                {struct('counter', -1, 'lastUpdateS', 5), 6, 0.5, ...
                    'malformed_counter'}, ...
                {struct('counter', 1.5, 'lastUpdateS', 5), 6, 0.5, ...
                    'malformed_counter'}, ...
                {good, NaN, 0.5, 'malformed_now'}, ...
                {good, 6, 0, 'malformed_timeout'}, ...
                {good, 6, NaN, 'malformed_timeout'}, ...
                {good, 4, 0.5, 'host_clock_went_backwards'}};
            for index = 1:numel(cases)
                item = cases{index};
                result = inverterhilgui.heartbeatState(item{1}, item{2}, ...
                    item{3});
                testCase.verifyTrue(result.expired, item{4});
                testCase.verifyEqual(result.reason, item{4});
            end
        end

        function healthyArmedApplicationDoesNotFallBack(testCase)
            health = TestGuiSafetyAndHeartbeat.healthyHealth();
            plan = inverterhilgui.safeFallbackPlan(health);

            testCase.verifyFalse(plan.applyFallback);
            testCase.verifyEqual(plan.reason, 'healthy_armed');
            testCase.verifyEqual(plan.analogV, zeros(1, 4));
            testCase.verifyEqual(plan.digital, false(1, 8));
        end

        function heartbeatLossTargetStopAndUnloadAllFallBack(testCase)
            base = TestGuiSafetyAndHeartbeat.healthyHealth();

            expired = base;
            expired.heartbeatAgeS = base.heartbeatTimeoutS + 1e-6;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(expired), ...
                'heartbeat_expired');

            stopped = base;
            stopped.applicationRunning = false;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(stopped), ...
                'application_stopped');

            unloaded = base;
            unloaded.applicationLoaded = false;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(unloaded), ...
                'application_unloaded');

            disconnected = base;
            disconnected.targetConnected = false;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(disconnected), ...
                'target_disconnected');

            unhealthy = base;
            unhealthy.ioHealthy = false;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(unhealthy), 'io_unhealthy');

            unarmed = base;
            unarmed.armed = false;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(unarmed), 'not_armed');
        end

        function fallbackFailsClosedOnMalformedInput(testCase)
            base = TestGuiSafetyAndHeartbeat.healthyHealth();

            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(42), 'malformed_health');
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(struct()), ...
                'missing_applicationRunning');
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(rmfield(base, 'armed')), ...
                'missing_armed');

            malformedFlags = {NaN, 2, [true true], complex(1, 1), 'on'};
            for index = 1:numel(malformedFlags)
                candidate = base;
                candidate.ioHealthy = malformedFlags{index};
                TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                    inverterhilgui.safeFallbackPlan(candidate), ...
                    'malformed_health_flag');
            end

            malformedAges = {NaN, Inf, -1e-9, complex(0, 1), [0 0]};
            for index = 1:numel(malformedAges)
                candidate = base;
                candidate.heartbeatAgeS = malformedAges{index};
                TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                    inverterhilgui.safeFallbackPlan(candidate), ...
                    'heartbeat_expired');
            end

            candidate = base;
            candidate.heartbeatTimeoutS = 0;
            TestGuiSafetyAndHeartbeat.verifyFallback(testCase, ...
                inverterhilgui.safeFallbackPlan(candidate), ...
                'malformed_heartbeat_timeout');
        end

        function lifecycleTransitionsFollowTheAllowedActions(testCase)
            state = 'disconnected';
            expected = {'connect', 'connecting'; ...
                'connectSucceeded', 'connected'; ...
                'loadSucceeded', 'loaded'; ...
                'startSucceeded', 'running'; ...
                'stopSucceeded', 'stopped'; ...
                'reset', 'loaded'; ...
                'disconnect', 'disconnected'};
            for index = 1:size(expected, 1)
                result = inverterhilgui.connectionState(state, ...
                    expected{index, 1});
                testCase.verifyTrue(result.valid, expected{index, 1});
                testCase.verifyEqual(result.state, expected{index, 2});
                state = result.state;
            end

            testCase.verifyTrue(inverterhilgui.connectionState( ...
                'disconnected').allowed.connect);
            testCase.verifyFalse(inverterhilgui.connectionState( ...
                'disconnected').allowed.start);
            testCase.verifyTrue(inverterhilgui.connectionState( ...
                'running').allowed.stop);
            testCase.verifyFalse(inverterhilgui.connectionState( ...
                'running').allowed.load);
            testCase.verifyTrue(inverterhilgui.connectionState( ...
                'running').isRunning);
            testCase.verifyTrue(inverterhilgui.connectionState( ...
                'stopped').isConnected);
            testCase.verifyFalse(inverterhilgui.connectionState( ...
                'error').isConnected);
        end

        function lifecycleFailsClosedOnUnknownStatesAndEvents(testCase)
            result = inverterhilgui.connectionState('flying');
            testCase.verifyFalse(result.valid);
            testCase.verifyEqual(result.state, 'error');
            testCase.verifyEqual(result.reason, 'unknown_state');
            testCase.verifyFalse(result.isConnected);
            testCase.verifyFalse(result.allowed.start);

            result = inverterhilgui.connectionState('disconnected', 'start');
            testCase.verifyFalse(result.valid);
            testCase.verifyEqual(result.state, 'disconnected');
            testCase.verifyEqual(result.reason, 'rejected_event');

            result = inverterhilgui.connectionState('running', 'fail');
            testCase.verifyTrue(result.valid);
            testCase.verifyEqual(result.state, 'error');
            testCase.verifyFalse(result.isRunning);

            result = inverterhilgui.connectionState(42);
            testCase.verifyFalse(result.valid);
            testCase.verifyEqual(result.state, 'error');
        end

        function targetSessionRefusesActionsTheLifecycleForbids(testCase)
            backend = inverterhilgui.fakeTargetBackend();
            session = inverterhilgui.targetSession('FakePC', backend);

            testCase.verifyEqual(session.start().reason, ...
                'action_not_allowed');
            testCase.verifyEqual( ...
                inverterhilgui.targetSession('FakePC').start().reason, ...
                'not_connected');

            session.connect();
            testCase.verifyEqual(session.State, 'connected');
            testCase.verifyEqual(session.start().reason, ...
                'action_not_allowed');

            testCase.verifyTrue(session.load('inverter_hil').success);
            testCase.verifyEqual(session.State, 'loaded');
            testCase.verifyTrue(session.start().success);
            testCase.verifyEqual(session.State, 'running');
            testCase.verifyTrue(session.describeState().isRunning);
            testCase.verifyTrue(session.stop().success);
            testCase.verifyEqual(session.State, 'stopped');

            session.disconnect();
            testCase.verifyEqual(session.State, 'disconnected');
            testCase.verifyEmpty(session.Contract);
        end

        function lifecycleFailureLeavesTheSessionInError(testCase)
            backend = inverterhilgui.fakeTargetBackend();
            session = inverterhilgui.targetSession('FakePC', backend);
            session.connect();
            backend.FailNextCall = true;

            result = session.load('inverter_hil');

            testCase.verifyFalse(result.success);
            testCase.verifyEqual(session.State, 'error');
            testCase.verifyFalse(session.describeState().isConnected);
            testCase.verifyTrue(session.describeState().allowed.reset);
        end

        function noTestRequiresALiveSpeedgoat(testCase)
            session = inverterhilgui.targetSession('NoSuchTarget');
            testCase.verifyFalse(session.BackendInjected);
            testCase.verifyEmpty(session.Backend);
            testCase.verifyEqual(session.State, 'disconnected');
            testCase.verifyEqual(session.executionTimeS(), NaN);
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end

        function health = healthyHealth()
            health = struct( ...
                'applicationRunning', true, ...
                'targetConnected', true, ...
                'applicationLoaded', true, ...
                'ioHealthy', true, ...
                'armed', true, ...
                'heartbeatAgeS', 0.05, ...
                'heartbeatTimeoutS', 0.5);
        end

        function verifyFallback(testCase, plan, reason)
            testCase.verifyTrue(plan.applyFallback, reason);
            testCase.verifyEqual(plan.analogV, zeros(1, 4), reason);
            testCase.verifyEqual(plan.digital, false(1, 8), reason);
            testCase.verifyEqual(plan.reason, reason);
        end
    end
end
