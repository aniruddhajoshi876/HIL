function frames = sensorFrameOrder(frames)
%SENSORFRAMEORDER Drop invalid frames and order the survivors for CAN TX.
%   FRAMES = SENSORFRAMEORDER(FRAMES) takes an array of already-normalized
%   sensor frames (see IMUNORMALIZEFRAME / LWSNORMALIZEFRAME, each producing
%   the same {id,dlc,payload,timestampS,sequence,valid,kind} shape) and
%   returns only the valid ones, ordered by (timestampS, sequence).
%
%   This is the piece of the former combined SENSORBUSMUX that had no
%   sensor-specific logic at all: it does not know or care whether a frame
%   came from the IMU, the LWS, or any other future producer, so it is not
%   owned by either sensor's folder and lives here instead, alongside
%   INVERTER's other cross-sensor plumbing. Typical call:
%       frames = sensorNormalizer.sensorFrameOrder( ...
%           [imuNormalizeFrame(imuRaw), lwsNormalizeFrame(lwsRaw)]);
valid = [frames.valid];
frames = frames(valid);
if numel(frames) > 1
    timestamps = [frames.timestampS];
    sequences = [frames.sequence];
    [~, order] = sortrows([timestamps(:), double(sequences(:))], [1 2]);
    frames = frames(order);
end
end
