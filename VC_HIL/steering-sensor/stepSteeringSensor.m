function [next, frame] = stepSteeringSensor(previous, timeS, input)
%STEPSTEERINGSENSOR Produce the synchronized Bosch LWS observation.
if nargin < 1 || isempty(previous)
    previous = struct('angleDeg', 0, 'sequence', uint32(0));
end
if nargin < 3 || isempty(input)
    input = struct('angleDeg', 0, 'status', ...
        struct('trim', true, 'cal', true, 'ok', true), 'dropout', false);
end
next = previous;
next.sequence = previous.sequence + uint32(1);
if ~isfield(input, 'angleDeg')
    error('lws:MissingAngle', 'Steering input must contain angleDeg.');
end
next.angleDeg = input.angleDeg;
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', timeS, ...
    'sequence', next.sequence, 'valid', false);
if isfield(input, 'dropout') && input.dropout
    return;
end
status = input.status;
frame = packLwsFrame(input.angleDeg, 0, status);
frame.timestampS = timeS;
frame.sequence = next.sequence;
frame.valid = true;
end
