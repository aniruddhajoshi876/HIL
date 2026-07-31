function payload = packStatus3X3(status)
%PACKSTATUS3X3 Pack one bit-exact Ephorus 3X3 status payload.

required = {'state', 'ready', 'derating', 'maxAllowedCurrentA', ...
    'actualTorqueNm', 'torqueSetpointNm', 'motorTemperatureC', ...
    'switchTemperatureC'};
requireFields(status, required);

state = finiteScalar(status.state, 'state');
if state ~= fix(state) || state < 0 || state > 3
    error('inverterhil:InvalidEnum', 'state must be an integer from 0 to 3.');
end
ready = logicalScalar(status.ready, 'ready');
derating = logicalScalar(status.derating, 'derating');

raw = uint64(0);
raw = putField(raw, uint64(state), 0, 2);
raw = putField(raw, uint64(ready), 2, 1);
raw = putField(raw, uint64(derating), 3, 1);
raw = putField(raw, encodeUnsigned(status.maxAllowedCurrentA, ...
    1 / 32, 12, 'maxAllowedCurrentA'), 4, 12);
raw = putField(raw, encodeSigned(status.actualTorqueNm, ...
    1 / 32, 12, 'actualTorqueNm'), 16, 12);
raw = putField(raw, encodeSigned(status.torqueSetpointNm, ...
    1 / 32, 12, 'torqueSetpointNm'), 28, 12);
raw = putField(raw, encodeSigned(status.motorTemperatureC, ...
    1 / 8, 12, 'motorTemperatureC'), 40, 12);
raw = putField(raw, encodeSigned(status.switchTemperatureC, ...
    1 / 16, 12, 'switchTemperatureC'), 52, 12);
payload = u64ToPayload(raw);
end

function requireFields(value, fields)
for k = 1:numel(fields)
    if ~isfield(value, fields{k})
        error('inverterhil:MalformedStatus', ...
            'Status is missing field %s.', fields{k});
    end
end
end

function value = logicalScalar(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isfinite(double(value)) || ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:InvalidEnum', '%s must be logical 0 or 1.', name);
end
value = logical(value);
end
