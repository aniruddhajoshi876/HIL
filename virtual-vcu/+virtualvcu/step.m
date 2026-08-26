function out = step(measuredVoltageV, enabled, digitalInputs, rx, context)
%STEP Run one deterministic virtual-VCU state-machine sample.
%   Inputs are physical Module 2 AI/DI values and an optional decoded CAN
%   frame.  No GUI command or Module 1 signal is accepted.
if nargin < 2, enabled = true; end
if nargin < 3 || isempty(digitalInputs), digitalInputs = false(1,8); end
if nargin < 4, rx = []; end
if nargin < 5 || isempty(context), context = virtualvcu.initialContext(); end
c = virtualvcu.config();
v = double(measuredVoltageV(:)');
di = logical(digitalInputs(:)');
if numel(v) ~= 4, error('virtualvcu:InvalidAnalogVector', 'Expected 4 AI values.'); end
if numel(di) ~= 8, error('virtualvcu:InvalidDigitalVector', 'Expected 8 DI values.'); end

raw = double(virtualvcu.voltageToRaw(v));
[t1, tv1] = virtualvcu.rawToPedal(raw(1), 'throttle', 1);
[t2, tv2] = virtualvcu.rawToPedal(raw(2), 'throttle', 2);
[b1, bv1] = virtualvcu.rawToPedal(raw(3), 'brake', 1);
[b2, bv2] = virtualvcu.rawToPedal(raw(4), 'brake', 2);
appsPlausible = tv1 && tv2 && abs(t1-t2) <= 20;
brakePlausible = bv1 && bv2;
pedalValid = [tv1 tv2 bv1 bv2] & appsPlausible;

if isstruct(rx) && isfield(rx,'id') && isfield(rx,'payload')
    decoded = virtualvcu.decodeStatusFrame(rx.id, rx.payload);
    if decoded.known
        context.can.valid = true;
        context.can.lastId = uint32(rx.id);
        if mod(double(rx.id),16) == 3
            motor = 1 + floor((double(rx.id)-double(hex2dec('383'))) / 16);
            if motor >= 1 && motor <= 4
                context.can.seenMask = bitor(context.can.seenMask, bitshift(uint16(1), motor-1));
            end
            context.can.inverterReady = context.can.inverterReady || decoded.fields.inverterReady;
            context.can.inverterFault = context.can.inverterFault || ...
                decoded.fields.inverterState == 2 || decoded.fields.inverterState == 3;
        elseif uint32(rx.id) == uint32(hex2dec('400'))
            context.can.dcLink12V = decoded.fields.dcLink12V;
            context.can.dcLink34V = decoded.fields.dcLink34V;
        end
    end
end

if ~enabled
    context.state = uint8(0); context.ticks = uint32(0);
elseif di(c.digitalMap.shutdownFeedback)
    context.state = uint8(5); context.ticks = uint32(0);
elseif context.state == 5
    context.state = uint8(0); context.ticks = uint32(0);
elseif context.state == 0 && di(c.digitalMap.precharge)
    context.state = uint8(1); context.ticks = uint32(0);
elseif context.state == 1
    context.ticks = context.ticks + 1;
    if context.ticks >= c.prechargeTicks, context.state = uint8(2); context.ticks = uint32(0); end
elseif context.state == 2
    if di(c.digitalMap.main) && brakePlausible && mean([b1 b2]) >= 25
        context.state = uint8(3); context.ticks = uint32(0);
    end
elseif context.state == 3
    context.ticks = context.ticks + 1;
    if context.ticks >= c.buzzingTicks, context.state = uint8(4); context.ticks = uint32(0); end
elseif context.state == 4 && di(c.digitalMap.precharge)
    context.state = uint8(1); context.ticks = uint32(0);
end

active = context.state >= 2 && context.state <= 4;
drive = context.state == 4 && appsPlausible && brakePlausible;
% Named Nm value, not inlined: this is the same quantity packControlFrame
% packs into the four control payloads below, now also exposed as its own
% typed field (out.torqueRequestNm) rather than existing only inside a
% raw CAN payload byte pair. Formula unchanged from before this field
% existed.
torqueRequestNm = 15 * mean([t1 t2]) / 100 * double(drive);
out = struct('state', c.stateNames{double(context.state)+1}, ...
    'stateId', context.state, 'enabled', logical(enabled), 'context', context, ...
    'raw', raw, 'pedalPct', [t1 t2 b1 b2], 'valid', pedalValid, ...
    'appsPlausible', appsPlausible, 'brakePlausible', brakePlausible, ...
    'digitalInputs', di, 'can', context.can, ...
    'torqueRequestNm', torqueRequestNm, ...
    'pedalPayload', virtualvcu.packPedalFrame(mean([t1 t2]), ...
    mean([b1 b2]) / 100), ...
    'controlPayloads', zeros(4, 8, 'uint8'));
for i = 1:4
    out.controlPayloads(i,:) = virtualvcu.packControlFrame(i, active, 18000, ...
        torqueRequestNm);
end
if ~enabled
    out.pedalPayload(:) = 0; out.controlPayloads(:) = 0;
    out.torqueRequestNm = 0;
end
end
