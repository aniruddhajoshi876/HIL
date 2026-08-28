function result = connectionState(currentState, event)
%CONNECTIONSTATE Pure target lifecycle transitions and allowed actions.
%
%   RESULT = CONNECTIONSTATE(CURRENTSTATE) describes CURRENTSTATE without
%   changing it. RESULT = CONNECTIONSTATE(CURRENTSTATE, EVENT) applies EVENT.
%
%   States   : disconnected, connecting, connected, loaded, running, stopped,
%              error.
%   Events   : connect, connectSucceeded, connectFailed, disconnect, load,
%              loadSucceeded, start, startSucceeded, stop, stopSucceeded,
%              reset, fail.
%
%   The evaluator FAILS CLOSED: an unknown state or an event that is not
%   allowed leaves the state at 'error' or unchanged with VALID false, and the
%   allowed-action set of an unknown state permits nothing but 'disconnect'.

states = {'disconnected', 'connecting', 'connected', 'loaded', ...
    'running', 'stopped', 'error'};

result = struct( ...
    'state', 'error', ...
    'valid', false, ...
    'reason', 'unknown_state', ...
    'allowed', allowedActions('error'), ...
    'isConnected', false, ...
    'isRunning', false);

currentState = normalizeText(currentState);
if isempty(currentState) || ~any(strcmp(currentState, states))
    return;
end

if nargin < 2
    result.state = currentState;
    result.valid = true;
    result.reason = 'described';
    result.allowed = allowedActions(currentState);
    result.isConnected = isConnectedState(currentState);
    result.isRunning = strcmp(currentState, 'running');
    return;
end

event = normalizeText(event);
if isempty(event)
    result.state = currentState;
    result.reason = 'malformed_event';
    result.allowed = allowedActions(currentState);
    result.isConnected = isConnectedState(currentState);
    result.isRunning = strcmp(currentState, 'running');
    return;
end

nextState = currentState;
reason = 'rejected_event';
valid = false;

if strcmp(event, 'fail')
    nextState = 'error';
    reason = 'failed';
    valid = true;
elseif strcmp(event, 'disconnect')
    nextState = 'disconnected';
    reason = 'disconnected';
    valid = true;
else
    switch currentState
        case 'disconnected'
            if strcmp(event, 'connect')
                nextState = 'connecting';
                valid = true;
            end
        case 'connecting'
            if strcmp(event, 'connectSucceeded')
                nextState = 'connected';
                valid = true;
            elseif strcmp(event, 'connectFailed')
                nextState = 'disconnected';
                valid = true;
            end
        case 'connected'
            if strcmp(event, 'load')
                nextState = 'connected';
                valid = true;
            elseif strcmp(event, 'loadSucceeded')
                nextState = 'loaded';
                valid = true;
            end
        case 'loaded'
            if strcmp(event, 'start')
                nextState = 'loaded';
                valid = true;
            elseif strcmp(event, 'startSucceeded')
                nextState = 'running';
                valid = true;
            elseif strcmp(event, 'loadSucceeded')
                nextState = 'loaded';
                valid = true;
            end
        case 'running'
            if strcmp(event, 'stop')
                nextState = 'running';
                valid = true;
            elseif strcmp(event, 'stopSucceeded')
                nextState = 'stopped';
                valid = true;
            end
        case 'stopped'
            if strcmp(event, 'startSucceeded')
                nextState = 'running';
                valid = true;
            elseif strcmp(event, 'reset')
                nextState = 'loaded';
                valid = true;
            elseif strcmp(event, 'loadSucceeded')
                nextState = 'loaded';
                valid = true;
            end
        case 'error'
            if strcmp(event, 'reset')
                nextState = 'connected';
                valid = true;
            end
        otherwise
            valid = false;
    end
    if valid
        reason = event;
    end
end

result.state = nextState;
result.valid = valid;
result.reason = reason;
result.allowed = allowedActions(nextState);
result.isConnected = isConnectedState(nextState);
result.isRunning = strcmp(nextState, 'running');
end

function allowed = allowedActions(state)
allowed = struct( ...
    'connect', false, ...
    'disconnect', false, ...
    'load', false, ...
    'start', false, ...
    'stop', false, ...
    'reset', false);
switch state
    case 'disconnected'
        allowed.connect = true;
    case 'connecting'
        allowed.disconnect = true;
    case 'connected'
        allowed.disconnect = true;
        allowed.load = true;
    case 'loaded'
        allowed.disconnect = true;
        allowed.load = true;
        allowed.start = true;
    case 'running'
        allowed.disconnect = true;
        allowed.stop = true;
    case 'stopped'
        allowed.disconnect = true;
        allowed.load = true;
        allowed.start = true;
        allowed.reset = true;
    case 'error'
        allowed.disconnect = true;
        allowed.reset = true;
    otherwise
        allowed.disconnect = true;
end
end

function value = isConnectedState(state)
value = any(strcmp(state, {'connected', 'loaded', 'running', 'stopped'}));
end

function text = normalizeText(text)
if isstring(text) && isscalar(text)
    text = char(text);
end
if ~ischar(text)
    text = '';
end
text = strtrim(text);
end
