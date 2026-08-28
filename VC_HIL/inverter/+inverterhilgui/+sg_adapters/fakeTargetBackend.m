classdef fakeTargetBackend < handle
    %FAKETARGETBACKEND In-memory test double for the Simulink Real-Time seam.
    %
    %   This class exists ONLY so that INVERTERHILGUI.TARGETSESSION can be
    %   unit-tested without a Speedgoat. It is NOT a demo mode and it is NEVER
    %   wired into INVERTER_HIL_APP: the app constructs a target session with
    %   no injected backend, which yields the real Simulink Real-Time backend
    %   and a hard failure when no target is present.
    %
    %   It implements the backend interface expected by TARGETSESSION:
    %     connect, disconnect, load, start, stop, reset, getparam, setparam,
    %     getsignal, isConnected, applicationState, executionTimeS,
    %     targetName, availableParameters, addInstrument, removeInstruments.

    properties
        % Parameter paths this fake application claims to expose.
        AvailablePaths = {}
        % Values keyed by parameter path.
        Values
        % When true, the next write or lifecycle call fails.
        FailNextCall = false
        % Value the target reports back regardless of what was written.
        AppliedOverride
        % Number of writes performed.
        WriteCount = 0
        % Ordered log of {path, value} pairs actually written.
        WriteLog = {}
        % Number of times an instrument was registered.
        InstrumentCount = 0
    end

    properties (SetAccess = private)
        Connected = false
        Loaded = false
        Running = false
        Name = 'FakeTarget'
        ExecutionTimeS = 0
        CurrentApplication = ''
    end

    methods
        function obj = fakeTargetBackend(availablePaths)
            %FAKETARGETBACKEND Construct a fake backend with known parameters.
            obj.Values = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            if nargin < 1 || isempty(availablePaths)
                contract = inverterhilgui.params.parameterContract();
                availablePaths = cell(1, numel(contract));
                for index = 1:numel(contract)
                    availablePaths{index} = contract(index).structPath;
                end
            end
            obj.AvailablePaths = availablePaths;
            for index = 1:numel(obj.AvailablePaths)
                obj.Values(obj.AvailablePaths{index}) = 0;
            end
        end

        function connect(obj)
            obj.failIfRequested('connect');
            obj.Connected = true;
        end

        function disconnect(obj)
            obj.Connected = false;
            obj.Loaded = false;
            obj.Running = false;
        end

        function load(obj, ~)
            obj.failIfRequested('load');
            obj.requireConnected();
            obj.Loaded = true;
            obj.Running = false;
            obj.CurrentApplication = 'inverter_hil';
        end

        function start(obj)
            obj.failIfRequested('start');
            obj.requireConnected();
            if ~obj.Loaded
                error('inverterhilgui:FakeTargetNotLoaded', ...
                    'No application is loaded on the fake target.');
            end
            obj.Running = true;
        end

        function stop(obj)
            obj.failIfRequested('stop');
            obj.Running = false;
        end

        function name = currentApplicationName(obj)
            name = obj.CurrentApplication;
        end

        function reset(obj)
            obj.failIfRequested('reset');
            obj.Running = false;
            obj.ExecutionTimeS = 0;
        end

        function value = getparam(obj, path)
            obj.requireConnected();
            if ~obj.Values.isKey(path)
                error('inverterhilgui:FakeTargetUnknownParameter', ...
                    'The fake target does not expose %s.', path);
            end
            value = obj.Values(path);
        end

        function setparam(obj, path, value)
            obj.failIfRequested('setparam');
            obj.requireConnected();
            if ~obj.Values.isKey(path)
                error('inverterhilgui:FakeTargetUnknownParameter', ...
                    'The fake target does not expose %s.', path);
            end
            if ~isempty(obj.AppliedOverride)
                obj.Values(path) = obj.AppliedOverride;
            else
                obj.Values(path) = value;
            end
            obj.WriteCount = obj.WriteCount + 1;
            obj.WriteLog{end + 1, 1} = {path, value};
        end

        function value = getsignal(obj, ~, ~)
            % No fake test currently exercises READLIVEIO; this exists only
            % so FAKETARGETBACKEND keeps satisfying the backend interface.
            obj.requireConnected();
            value = 0;
        end

        function value = isConnected(obj)
            value = obj.Connected;
        end

        function state = applicationState(obj)
            if ~obj.Connected
                state = 'disconnected';
            elseif obj.Running
                state = 'running';
            elseif obj.Loaded
                state = 'loaded';
            else
                state = 'connected';
            end
        end

        function value = executionTimeS(obj)
            value = obj.ExecutionTimeS;
        end

        function value = targetName(obj)
            value = obj.Name;
        end

        function paths = availableParameters(obj)
            paths = obj.AvailablePaths;
        end

        function addInstrument(obj, ~)
            obj.InstrumentCount = obj.InstrumentCount + 1;
        end

        function removeInstruments(obj)
            obj.InstrumentCount = 0;
        end
    end

    methods (Access = private)
        function failIfRequested(obj, action)
            if obj.FailNextCall
                obj.FailNextCall = false;
                error('inverterhilgui:FakeTargetFailure', ...
                    'The fake target was told to fail %s.', action);
            end
        end

        function requireConnected(obj)
            if ~obj.Connected
                error('inverterhilgui:FakeTargetNotConnected', ...
                    'The fake target is not connected.');
            end
        end
    end
end
