function payload = packStatus3X5(status)
%PACKSTATUS3X5 Pack one bit-exact Ephorus 3X5 status payload.

required = {'idSetpointA', 'idActualA', 'iqSetpointA', 'iqActualA', ...
    'speedRpm'};
for k = 1:numel(required)
    if ~isfield(status, required{k})
        error('inverterhil:MalformedStatus', ...
            'Status is missing field %s.', required{k});
    end
end

raw = uint64(0);
raw = putField(raw, encodeSigned(status.idSetpointA, ...
    1 / 16, 12, 'idSetpointA'), 0, 12);
raw = putField(raw, encodeSigned(status.idActualA, ...
    1 / 16, 12, 'idActualA'), 12, 12);
raw = putField(raw, encodeSigned(status.iqSetpointA, ...
    1 / 16, 12, 'iqSetpointA'), 24, 12);
raw = putField(raw, encodeSigned(status.iqActualA, ...
    1 / 16, 12, 'iqActualA'), 36, 12);
raw = putField(raw, encodeSigned(status.speedRpm, ...
    1, 16, 'speedRpm'), 48, 16);
payload = u64ToPayload(raw);
end
