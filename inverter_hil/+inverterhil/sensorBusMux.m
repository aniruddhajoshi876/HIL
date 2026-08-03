function frames = sensorBusMux(imuFrame, steeringFrame)
%SENSORBUSMUX Combine due sensor frames without cross-channel overwriting.
frames = repmat(emptyFrame(), 1, 2);
frames(1) = normalizeFrame(imuFrame, 'imu');
frames(2) = normalizeFrame(steeringFrame, 'steering');
valid = [frames.valid];
frames = frames(valid);
if numel(frames) > 1
    timestamps = [frames.timestampS];
    sequences = [frames.sequence];
    [~, order] = sortrows([timestamps(:), double(sequences(:))], [1 2]);
    frames = frames(order);
end
end

function frame = normalizeFrame(source, kind)
frame = emptyFrame();
frame.kind = kind;
if isempty(source) || ~isstruct(source) || ~isfield(source, 'valid') || ...
        ~source.valid
    return;
end
required = {'id', 'dlc', 'payload', 'timestampS', 'sequence'};
for index = 1:numel(required)
    if ~isfield(source, required{index})
        error('inverterhil:MalformedSensorFrame', ...
            'Sensor frame lacks %s.', required{index});
    end
end
frame.id = uint32(source.id);
frame.dlc = uint8(source.dlc);
frame.payload = uint8(source.payload(:).');
frame.timestampS = double(source.timestampS);
frame.sequence = uint32(source.sequence);
frame.valid = logical(source.valid);
frame.kind = kind;
end

function frame = emptyFrame()
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', NaN, ...
    'sequence', uint32(0), 'valid', false, 'kind', '');
end
