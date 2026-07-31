function result = evaluateCanDiagnostics(writeSucceeded, backlog, ...
        receiveOverrun, errorWarning, busOff)
%EVALUATECANDIAGNOSTICS Decide whether a nine-frame cycle really succeeded.

if ~islogical(writeSucceeded) || ~isequal(size(writeSucceeded), [1 9])
    error('inverterhil:MalformedDiagnostics', ...
        'writeSucceeded must be a 1x9 logical vector.');
end
backlog = logicalScalar(backlog, 'backlog');
receiveOverrun = logicalScalar(receiveOverrun, 'receiveOverrun');
errorWarning = logicalScalar(errorWarning, 'errorWarning');
busOff = logicalScalar(busOff, 'busOff');

result.writeSucceeded = writeSucceeded;
result.failedWriteMask = uint16(0);
for index = 1:9
    if ~writeSucceeded(index)
        result.failedWriteMask = bitor(result.failedWriteMask, ...
            bitshift(uint16(1), index - 1));
    end
end
result.backlog = backlog;
result.receiveOverrun = receiveOverrun;
result.errorWarning = errorWarning;
result.busOff = busOff;
result.cycleSucceeded = all(writeSucceeded) && ~backlog && ...
    ~receiveOverrun && ~errorWarning && ~busOff;
end

function value = logicalScalar(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isfinite(double(value)) || ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:MalformedDiagnostics', ...
        '%s must be logical 0 or 1.', name);
end
value = logical(value);
end
