function frame = lwsNormalizeFrame(source)
%LWSNORMALIZEFRAME Validate one raw LWS frame into the canonical frame shape.
%   Split out of the former combined SENSORBUSMUX's NORMALIZEFRAME helper:
%   this half is purely per-sensor (nothing in it references any other
%   sensor), so it now lives with the rest of the steering-sensor driver
%   code. SENSORNORMALIZER.SENSORFRAMEORDER takes already-normalized frames
%   from this and IMUNORMALIZEFRAME and orders/filters them generically.
frame = emptyFrame();
frame.kind = 'steering';
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
frame.kind = 'steering';
end

function frame = emptyFrame()
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', NaN, ...
    'sequence', uint32(0), 'valid', false, 'kind', '');
end
