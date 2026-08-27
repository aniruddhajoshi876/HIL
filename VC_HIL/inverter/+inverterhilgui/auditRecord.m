function record = auditRecord(info)
%AUDITRECORD Build one operator-command audit record with a fixed field order.
%
%   Plan 7.4 requires the GUI to record every operator command with host time,
%   target time, old value, new value, and result. The field order below is
%   fixed and must not be reordered: the session log, its table view, and its
%   CSV export all depend on it.
%
%   Field order:
%     hostTime, targetTimeS, logicalName, targetPath, requested, applied,
%     result, detail
%
%   INFO is a scalar structure. Missing optional fields are filled with an
%   honest placeholder rather than a fabricated value; a missing LOGICALNAME
%   or RESULT yields RESULT 'rejected' with a DETAIL saying why, because an
%   unattributable command must never be recorded as if it succeeded.

record = struct( ...
    'hostTime', '', ...
    'targetTimeS', NaN, ...
    'logicalName', '', ...
    'targetPath', '', ...
    'requested', '--', ...
    'applied', '--', ...
    'result', 'rejected', ...
    'detail', 'malformed_audit_input');

if ~isstruct(info) || ~isscalar(info)
    record.hostTime = hostTimestamp([]);
    return;
end

if isfield(info, 'hostTime')
    record.hostTime = hostTimestamp(info.hostTime);
else
    record.hostTime = hostTimestamp([]);
end
if isfield(info, 'targetTimeS')
    value = info.targetTimeS;
    if isnumeric(value) && isscalar(value) && isreal(value)
        record.targetTimeS = double(value);
    end
end
record.logicalName = textField(info, 'logicalName');
record.targetPath = textField(info, 'targetPath');
if isfield(info, 'requested')
    record.requested = valueText(info.requested);
end
if isfield(info, 'applied')
    record.applied = valueText(info.applied);
end
if isfield(info, 'detail')
    record.detail = textField(info, 'detail');
end

allowed = {'applied', 'clamped', 'mismatch', 'failed', 'rejected', ...
    'fallback', 'lifecycle'};
resultText = textField(info, 'result');
if isempty(record.logicalName)
    record.result = 'rejected';
    record.detail = 'missing_logical_name';
    return;
end
if ~any(strcmp(resultText, allowed))
    record.result = 'rejected';
    record.detail = 'unknown_result_code';
    return;
end
record.result = resultText;
end

function text = textField(info, name)
text = '';
if ~isfield(info, name)
    return;
end
value = info.(name);
if isstring(value) && isscalar(value)
    value = char(value);
end
if ischar(value)
    text = value;
end
end

function text = hostTimestamp(value)
if isstring(value) && isscalar(value)
    value = char(value);
end
if ischar(value) && ~isempty(value)
    text = value;
    return;
end
if isdatetime(value) && isscalar(value)
    text = char(datetime(value, 'Format', 'yyyy-MM-dd HH:mm:ss.SSS'));
    return;
end
text = char(datetime('now', 'Format', 'yyyy-MM-dd HH:mm:ss.SSS'));
end

function text = valueText(value)
text = '--';
if isstring(value) && isscalar(value)
    value = char(value);
end
if ischar(value)
    if ~isempty(value)
        text = value;
    end
    return;
end
if islogical(value) && isscalar(value)
    if value
        text = 'true';
    else
        text = 'false';
    end
    return;
end
if isnumeric(value) && isscalar(value) && isreal(value)
    if isinteger(value)
        text = sprintf('%d', value);
    elseif isnan(value)
        text = '--';
    else
        text = sprintf('%.6g', double(value));
    end
end
end
