classdef targetSession < handle
    %TARGETSESSION Seam wrapping the Simulink Real-Time target object.
    %
    %   s = INVERTERHILGUI.TARGETSESSION(targetName) uses the real Simulink
    %   Real-Time backend, which is only constructed when a target is actually
    %   addressed. s = INVERTERHILGUI.TARGETSESSION(targetName, backend)
    %   injects a backend so tests can substitute
    %   INVERTERHILGUI.FAKETARGETBACKEND. Plan assumption M4: the Simulink
    %   Real-Time target and instrument APIs cannot be exercised without
    %   hardware, so every target interaction goes through this seam.
    %
    %   Safety behavior (plan 7.2, 7.4):
    %     * CONNECT discovers the parameter contract and reads target values
    %       with GETPARAM. It NEVER pushes host defaults to the target.
    %     * WRITE validates and clamps through
    %       INVERTERHILGUI.VALIDATECOMMANDVALUE, writes with SETPARAM, reads
    %       the applied value back, and reports requested versus applied.
    %     * SETPARAM is never called with Force=true.

    properties (SetAccess = private)
        % Configured target name.
        TargetName = ''
        % Injected or lazily created backend.
        Backend = []
        % True when the backend was injected by a test.
        BackendInjected = false
        % Lifecycle state from INVERTERHILGUI.CONNECTIONSTATE.
        State = 'disconnected'
        % Resolved parameter contract, empty until CONNECT succeeds.
        Contract = []
        % Values read from the target on connect, keyed by logical name.
        TargetValues
        % Most recent failure reason.
        LastError = ''
    end

    methods
        function obj = targetSession(targetName, backend)
            %TARGETSESSION Construct a session, optionally with a fake backend.
            if nargin < 1 || isempty(targetName)
                targetName = 'TargetPC1';
            end
            if isstring(targetName) && isscalar(targetName)
                targetName = char(targetName);
            end
            if ~ischar(targetName) || isempty(targetName)
                error('inverterhilgui:InvalidTargetName', ...
                    'Target name must be a nonempty character vector.');
            end
            obj.TargetName = targetName;
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            if nargin >= 2 && ~isempty(backend)
                obj.Backend = backend;
                obj.BackendInjected = true;
            end
        end

        function result = connect(obj)
            %CONNECT Connect, ensure the application is running, discover the
            %contract, and read target values.
            %   CONNECT loads and starts INVERTER_HIL automatically so one
            %   Connect click always yields a usable session running the build
            %   currently on disk (see ENSUREAPPLICATIONRUNNING).
            %
            %   The hardware boundary is now live, so starting the application
            %   does drive the IO183 outputs and transmits the Ephorus status
            %   frames on CAN. It starts in the safe state the dictionary
            %   ships: pedal calibration is NaN so both analog pedal pairs
            %   hold 0 V, every digital stimulus is false, and the precharge
            %   counter is 0 so no pulse is generated. Physical levels change
            %   only when the operator moves a control.
            result = struct('success', false, 'state', obj.State, ...
                'reason', '', 'contract', []);
            obj.applyEvent('connect');
            try
                obj.ensureBackend();
                obj.Backend.connect();
                obj.applyEvent('connectSucceeded');
                obj.ensureApplicationRunning();
                obj.Contract = inverterhilgui.discoverContract( ...
                    obj.Backend.availableParameters());
                obj.readAllTargetValues();
                obj.syncStateFromBackend();
                result.success = true;
                result.reason = 'connected';
                result.contract = obj.Contract;
            catch err
                % A failed connect or a version-mismatched application must
                % never leave the session looking connected, so drop the
                % target and the partially resolved contract.
                obj.LastError = err.message;
                obj.Contract = [];
                obj.TargetValues = containers.Map('KeyType', 'char', ...
                    'ValueType', 'any');
                try
                    if ~isempty(obj.Backend)
                        obj.Backend.disconnect();
                    end
                catch
                    % The backend may already be gone; nothing to release.
                end
                obj.applyEvent('disconnect');
                result.reason = err.message;
            end
            result.state = obj.State;
        end

        function result = disconnect(obj)
            %DISCONNECT Drop the target and clear the resolved contract.
            result = struct('success', true, 'state', '', 'reason', '');
            try
                if ~isempty(obj.Backend)
                    obj.Backend.removeInstruments();
                    obj.Backend.disconnect();
                end
            catch err
                obj.LastError = err.message;
                result.success = false;
                result.reason = err.message;
            end
            obj.Contract = [];
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            obj.applyEvent('disconnect');
            result.state = obj.State;
        end

        function result = load(obj, applicationName)
            %LOAD Load a real-time application onto the target.
            if nargin < 2
                applicationName = '';
            end
            result = obj.lifecycleCall(@() obj.Backend.load(applicationName), ...
                'load', 'loadSucceeded');
        end

        function result = start(obj)
            %START Start the loaded real-time application.
            result = obj.lifecycleCall(@() obj.Backend.start(), ...
                'start', 'startSucceeded');
        end

        function result = stop(obj)
            %STOP Stop the running real-time application.
            result = obj.lifecycleCall(@() obj.Backend.stop(), ...
                'stop', 'stopSucceeded');
        end

        function result = reset(obj)
            %RESET Reset the target application.
            result = obj.lifecycleCall(@() obj.Backend.reset(), ...
                'reset', 'reset');
        end

        function result = write(obj, name, value)
            %WRITE Validate, clamp, write, and read back one logical command.
            result = struct( ...
                'name', name, ...
                'path', '', ...
                'requested', value, ...
                'applied', [], ...
                'success', false, ...
                'clamped', false, ...
                'mismatch', false, ...
                'reason', 'not_connected');
            if isempty(obj.Contract)
                result.reason = 'contract_unresolved';
                return;
            end
            validation = inverterhilgui.validateCommandValue( ...
                obj.Contract, name, value);
            if ~validation.accepted
                result.reason = validation.reason;
                return;
            end
            entry = inverterhilgui.contractEntry(obj.Contract, name);
            result.path = entry.path;
            result.requested = validation.value;
            result.clamped = validation.clamped;
            try
                obj.Backend.setparam(entry.path, validation.value);
                applied = obj.Backend.getparam(entry.path);
            catch err
                obj.LastError = err.message;
                result.reason = 'write_failed';
                return;
            end
            result.applied = applied;
            obj.TargetValues(name) = applied;
            result.success = true;
            result.mismatch = ~valuesMatch(validation.value, applied);
            if result.mismatch
                result.reason = 'mismatch';
            elseif result.clamped
                result.reason = 'clamped';
            else
                result.reason = 'applied';
            end
        end

        function [value, known] = readCached(obj, name)
            %READCACHED Value read from the target, without re-reading it.
            value = [];
            known = false;
            if isKey(obj.TargetValues, name)
                value = obj.TargetValues(name);
                known = true;
            end
        end

        function value = executionTimeS(obj)
            %EXECUTIONTIMES Elapsed target execution time, NaN when unknown.
            value = NaN;
            try
                if ~isempty(obj.Backend) && obj.Backend.isConnected()
                    value = double(obj.Backend.executionTimeS());
                end
            catch err
                obj.LastError = err.message;
            end
        end

        function value = describeState(obj)
            %DESCRIBESTATE Lifecycle description including allowed actions.
            value = inverterhilgui.connectionState(obj.State);
        end

        function success = addInstrument(obj, instrument)
            %ADDINSTRUMENT Register a Simulink Real-Time instrument.
            success = false;
            try
                obj.Backend.addInstrument(instrument);
                success = true;
            catch err
                obj.LastError = err.message;
            end
        end
    end

    methods (Access = private)
        function ensureBackend(obj)
            if ~isempty(obj.Backend)
                return;
            end
            if exist('slrealtime.Target', 'class') ~= 8
                error('inverterhilgui:RealTimeToolboxMissing', ...
                    ['Simulink Real-Time is required to address target ' ...
                    '%s and no backend was injected.'], obj.TargetName);
            end
            obj.Backend = inverterhilgui.slrealtimeBackend(obj.TargetName);
        end

        function result = lifecycleCall(obj, action, requestEvent, doneEvent)
            result = struct('success', false, 'state', obj.State, ...
                'reason', '');
            if isempty(obj.Backend)
                result.reason = 'not_connected';
                return;
            end
            allowed = inverterhilgui.connectionState(obj.State).allowed;
            actionName = strrep(requestEvent, 'Succeeded', '');
            if isfield(allowed, actionName) && ~allowed.(actionName)
                result.reason = 'action_not_allowed';
                result.state = obj.State;
                return;
            end
            obj.applyEvent(requestEvent);
            try
                action();
                obj.applyEvent(doneEvent);
                result.success = true;
                result.reason = doneEvent;
            catch err
                obj.LastError = err.message;
                obj.applyEvent('fail');
                result.reason = err.message;
            end
            result.state = obj.State;
        end

        function applyEvent(obj, event)
            transition = inverterhilgui.connectionState(obj.State, event);
            obj.State = transition.state;
        end

        function ensureApplicationRunning(obj)
            %ENSUREAPPLICATIONRUNNING Load the current build and start it.
            %   The application is loaded unconditionally rather than only
            %   when the target reports 'disconnected'/'stopped'. The loaded
            %   application is always named INVERTER_HIL, so its name cannot
            %   distinguish a freshly built INVERTER_HIL.MLDATX from one the
            %   target loaded before the model was rebuilt. Returning early on
            %   an already-'running' target would therefore silently leave the
            %   operator driving a stale build while the GUI reported success
            %   -- the failure mode is invisible, which is why this reloads
            %   instead of attaching. Reconnecting consequently restarts the
            %   run rather than resuming it.
            obj.Backend.load('inverter_hil');
            obj.Backend.start();
        end

        function syncStateFromBackend(obj)
            try
                reported = obj.Backend.applicationState();
            catch err
                obj.LastError = err.message;
                return;
            end
            if any(strcmp(reported, {'connected', 'loaded', 'running', ...
                    'stopped'}))
                obj.State = reported;
            end
        end

        function readAllTargetValues(obj)
            % Plan 7.4: read target values before enabling controls and never
            % push host defaults on connect. This method only reads.
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            for index = 1:numel(obj.Contract.entries)
                entry = obj.Contract.entries(index);
                try
                    obj.TargetValues(entry.name) = ...
                        obj.Backend.getparam(entry.path);
                catch err
                    obj.LastError = err.message;
                end
            end
        end
    end
end

function match = valuesMatch(requested, applied)
match = false;
if ~(isnumeric(applied) || islogical(applied)) || ~isscalar(applied)
    return;
end
requestedValue = double(requested);
appliedValue = double(applied);
if ~isfinite(requestedValue) || ~isfinite(appliedValue)
    return;
end
tolerance = max(1e-9, 1e-6 * abs(requestedValue));
match = abs(requestedValue - appliedValue) <= tolerance;
end
