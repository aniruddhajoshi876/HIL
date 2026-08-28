function payload = packSystemStatus(status)
%PACKSYSTEMSTATUS Pack general Ephorus status ID 0x400.

required = {'dcLink12V', 'dcLink34V', 'switchingFrequencyKHz', ...
    'dcLink12AboveMinimum', 'dcLink34AboveMinimum', ...
    'controlEnable', 'controlDisable'};
for k = 1:numel(required)
    if ~isfield(status, required{k})
        error('inverterhil:MalformedStatus', ...
            'Status is missing field %s.', required{k});
    end
end

raw = uint64(0);
raw = putField(raw, encodeUnsigned(status.dcLink12V, ...
    1 / 64, 16, 'dcLink12V'), 0, 16);
raw = putField(raw, encodeUnsigned(status.dcLink34V, ...
    1 / 64, 16, 'dcLink34V'), 16, 16);
raw = putField(raw, encodeUnsigned(status.switchingFrequencyKHz, ...
    1 / 512, 16, 'switchingFrequencyKHz'), 32, 16);
raw = putField(raw, uint64(logicalScalar(status.dcLink12AboveMinimum, ...
    'dcLink12AboveMinimum')), 48, 1);
raw = putField(raw, uint64(logicalScalar(status.dcLink34AboveMinimum, ...
    'dcLink34AboveMinimum')), 49, 1);
raw = putField(raw, uint64(logicalScalar(status.controlEnable, ...
    'controlEnable')), 50, 1);
raw = putField(raw, uint64(logicalScalar(status.controlDisable, ...
    'controlDisable')), 51, 1);
payload = u64ToPayload(raw);
end

function value = logicalScalar(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isfinite(double(value)) || ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:InvalidEnum', '%s must be logical 0 or 1.', name);
end
value = logical(value);
end
