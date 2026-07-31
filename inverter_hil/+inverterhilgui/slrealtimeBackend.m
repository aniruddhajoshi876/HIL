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
            obj.Name = targetName;
            obj.Target = slrealtime.Target(targetName);
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

        function value = executionTimeS(obj)
            value = double(obj.Target.getExecTime());
        end

        function value = targetName(obj)
            value = obj.Name;
        end

        function paths = availableParameters(obj)
            % The tunable-parameter listing is read from the loaded
            % application. A missing or empty listing is reported honestly as
            % an empty cell so DISCOVERCONTRACT raises a version mismatch.
            paths = {};
            listing = obj.Target.getparamlist();
            if isempty(listing)
                return;
            end
            if istable(listing)
                names = listing.Properties.VariableNames;
                if any(strcmp('BlockPath', names)) && ...
                        any(strcmp('ParameterName', names))
                    paths = cell(1, height(listing));
                    for index = 1:height(listing)
                        paths{index} = sprintf('%s/%s', ...
                            char(listing.BlockPath(index)), ...
                            char(listing.ParameterName(index)));
                    end
                    return;
                end
            end
            if iscell(listing)
                paths = listing(:)';
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
