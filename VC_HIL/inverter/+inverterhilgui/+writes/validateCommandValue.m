function result = validateCommandValue(source, name, value)
%VALIDATECOMMANDVALUE Validate and clamp one logical command before writing.
%
%   RESULT = VALIDATECOMMANDVALUE(SOURCE, NAME, VALUE) checks VALUE against
%   the declared type and range for logical NAME. SOURCE is either the
%   declarative contract or the resolved contract. This evaluator FAILS
%   CLOSED: a malformed value, an unknown name, or a malformed contract entry
%   returns ACCEPTED false with a REASON string instead of throwing, so no
%   callback can push an unvalidated value at the target.
%
%   RESULT fields:
%     name     - the requested logical name
%     value    - the value that may be written when ACCEPTED is true
%     accepted - true only when the value is safe to write
%     clamped  - true when VALUE was outside the declared range
%     reason   - 'accepted', 'clamped' or a specific rejection reason

result = struct( ...
    'name', '', ...
    'value', [], ...
    'accepted', false, ...
    'clamped', false, ...
    'reason', 'unknown_logical_name');
if isstring(name) && isscalar(name)
    name = char(name);
end
if ~ischar(name) || isempty(name)
    result.reason = 'malformed_logical_name';
    return;
end
result.name = name;

entry = inverterhilgui.params.contractEntry(source, name);
if isempty(entry)
    return;
end
required = {'type', 'minimum', 'maximum'};
for index = 1:numel(required)
    if ~isfield(entry, required{index})
        result.reason = ['missing_contract_' required{index}];
        return;
    end
end
if ~isnumeric(entry.minimum) || ~isscalar(entry.minimum) || ...
        ~isreal(entry.minimum) || ~isfinite(entry.minimum) || ...
        ~isnumeric(entry.maximum) || ~isscalar(entry.maximum) || ...
        ~isreal(entry.maximum) || ~isfinite(entry.maximum) || ...
        entry.minimum > entry.maximum
    result.reason = 'malformed_contract_range';
    return;
end

if ~(isnumeric(value) || islogical(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value))
    result.reason = 'malformed_value';
    return;
end
numericValue = double(value);

switch entry.type
    case 'double'
        clamped = min(max(numericValue, entry.minimum), entry.maximum);
        result.clamped = clamped ~= numericValue;
        result.value = clamped;
    case 'logical'
        if numericValue ~= 0 && numericValue ~= 1
            result.reason = 'value_not_logical';
            return;
        end
        result.value = logical(numericValue);
    case {'uint8', 'uint16', 'uint32'}
        if numericValue ~= floor(numericValue)
            result.reason = 'value_not_integer';
            return;
        end
        if numericValue < 0
            result.reason = 'value_negative';
            return;
        end
        clamped = min(max(numericValue, entry.minimum), entry.maximum);
        result.clamped = clamped ~= numericValue;
        result.value = cast(clamped, entry.type);
    otherwise
        result.reason = 'unsupported_contract_type';
        return;
end

result.accepted = true;
if result.clamped
    result.reason = 'clamped';
else
    result.reason = 'accepted';
end
end
