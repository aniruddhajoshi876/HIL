classdef slrealtimeBackend < handle
    %SLREALTIMEBACKEND Real Simulink Real-Time backend for TARGETSESSION.
    %
    %   This adapter is the only place in the GUI that names a Simulink
    %   Real-Time API. It is constructed lazily by
    %   INVERTERHILGUI.TARGETSESSION and only when a target is actually
    %   addressed, so the app runs with no Speedgoat present.
    %
    %   Plan assumption M4: none of these calls can be exercised without
    %   hardware, so this class is deliberately a thin, untested pass-through
    %   and every behavior the GUI depends on is tested against
    %   INVERTERHILGUI.FAKETARGETBACKEND instead. Nothing here fabricates a
    %   value: a failing call throws and TARGETSESSION reports it.
    %
    %   SETPARAM is called without Force=true, per plan 7.2.

    properties (SetAccess = private)
        Name = ''
        Target = []
        Instruments = {}
    end

    methods
        function obj = slrealtimeBackend(targetName)
            %SLREALTIMEBACKEND Wrap the Simulink Real-Time target object.
            %   Constructed via the SLREALTIME(name) shorthand, not the
            %   package-qualified SLREALTIME.TARGET(name) form: R2024b
            %   restricts direct access to the classdef constructor
            %   (confirmed against real hardware: MATLAB:class:MethodRestricted).
            obj.Name = targetName;
            obj.Target = slrealtime(targetName);
        end

        function connect(obj)
            connect(obj.Target);
        end

        function disconnect(obj)
            disconnect(obj.Target);
        end

        function load(obj, applicationName)
            load(obj.Target, applicationName);
        end

        function start(obj)
            start(obj.Target);
        end

        function stop(obj)
            stop(obj.Target);
        end

        function reset(obj)
            stop(obj.Target);
        end

        function value = getparam(obj, path)
            [blockPath, parameterName] = obj.splitPath(path);
            value = getparam(obj.Target, blockPath, parameterName);
        end

        function setparam(obj, path, value)
            [blockPath, parameterName] = obj.splitPath(path);
            setparam(obj.Target, blockPath, parameterName, value);
        end

        function value = getsignal(obj, blockPath, port)
            %GETSIGNAL Read one streamed output-port value by block path.
            %   Unlike GETPARAM/SETPARAM (tunable parameters), this reads a
            %   live signal value off a running application, e.g. an I/O
            %   driver block's measured output. Confirmed against real
            %   Speedgoat hardware: SLREALTIME.TARGET/GETSIGNAL(target,
            %   blockPath, portIndex).
            value = getsignal(obj.Target, blockPath, port);
        end

        function value = isConnected(obj)
            value = logical(isConnected(obj.Target));
        end

        function state = applicationState(obj)
            state = 'connected';
            if ~obj.isConnected()
                state = 'disconnected';
                return;
            end
            if logical(isRunning(obj.Target))
                state = 'running';
            elseif logical(isLoaded(obj.Target))
                state = 'loaded';
            end
        end

        function name = currentApplicationName(obj)
            %CURRENTAPPLICATIONNAME Return the target's current app name.
            name = char(getLastApplication(obj.Target));
        end

        function value = executionTimeS(obj)
            value = double(obj.Target.getExecTime());
        end

        function value = targetName(obj)
            value = obj.Name;
        end

        function paths = availableParameters(obj)
            % Simulink Real-Time R2024b's SLREALTIME.TARGET has no bulk
            % parameter-listing method (confirmed against real Speedgoat
            % hardware: no GETPARAMLIST, and METHODS(target) lists only
            % GETPARAM/SETPARAM and named param-set save/load functions).
            % Every candidate name from INVERTERHILGUI.PARAMETERCONTRACT is
            % therefore probed individually with GETPARAM; a thrown error
            % means that name is not exposed by the loaded application and is
            % silently excluded rather than treated as a connection failure.
            contract = inverterhilgui.parameterContract();
            candidates = cell(1, 2 * numel(contract));
            for index = 1:numel(contract)
                candidates{2 * index - 1} = contract(index).structPath;
                candidates{2 * index} = contract(index).flatPath;
            end
            candidates = unique(candidates, 'stable');
            paths = {};
            for index = 1:numel(candidates)
                try
                    getparam(obj.Target, '', candidates{index});
                    paths{end + 1} = candidates{index}; %#ok<AGROW>
                catch
                    % Not exposed by this application build; excluded, not an
                    % error. DISCOVERCONTRACT decides whether the omission of
                    % a required name is a version mismatch.
                end
            end
        end

        function addInstrument(obj, instrument)
            addInstrument(obj.Target, instrument);
            obj.Instruments{end + 1} = instrument;
        end

        function removeInstruments(obj)
            for index = 1:numel(obj.Instruments)
                try
                    removeInstrument(obj.Target, obj.Instruments{index});
                catch
                    % The target may already be gone; nothing to remove.
                end
            end
            obj.Instruments = {};
        end
    end

    methods (Static, Access = private)
        function [blockPath, parameterName] = splitPath(path)
            % Logical contract paths are dotted names. The Simulink Real-Time
            % API takes a block path plus a parameter name; for a top-level
            % tunable parameter the block path is empty.
            separator = find(path == '/', 1, 'last');
            if isempty(separator)
                blockPath = '';
                parameterName = path;
            else
                blockPath = path(1:separator - 1);
                parameterName = path(separator + 1:end);
            end
        end
    end
end
