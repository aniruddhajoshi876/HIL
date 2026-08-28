function out = step(measuredVoltageV, enabled, digitalInputs, rx, context, controlsTauNm)
%STEP Run one 5 ms host-reference virtual-VCU sample.
%   CONTROLSTAUNM is the real allocator output in [FL FR RL RR] order. The
%   host reference deliberately delegates allocator execution; the deployed
%   chart calls the vendored generated C directly.
if nargin < 2, enabled = true; end
if nargin < 3 || isempty(digitalInputs), digitalInputs = false(1,8); end
if nargin < 4, rx = []; end
if nargin < 5 || isempty(context), context = virtualvcu.initialContext(); end
if nargin < 6 || isempty(controlsTauNm), controlsTauNm = zeros(1,4); end
c = virtualvcu.config();
v = double(measuredVoltageV(:)');
di = logical(digitalInputs(:)');
tau = double(controlsTauNm(:)');
if numel(v) ~= 4, error('virtualvcu:InvalidAnalogVector', 'Expected 4 AI values.'); end
if numel(di) ~= 8, error('virtualvcu:InvalidDigitalVector', 'Expected 8 DI values.'); end
if numel(tau) ~= 4, error('virtualvcu:InvalidTorqueVector', 'Expected [FL FR RL RR].'); end

raw = double(virtualvcu.voltageToRaw(v));
[t1, tv1] = virtualvcu.rawToPedal(raw(1), 'throttle', 1);
[t2, tv2] = virtualvcu.rawToPedal(raw(2), 'throttle', 2);
[b1, bv1] = virtualvcu.rawToPedal(raw(3), 'brake', 1);
[b2, bv2] = virtualvcu.rawToPedal(raw(4), 'brake', 2);
appsPlausible = tv1 && tv2 && abs(t1-t2) <= 20;
brakePlausible = bv1; % Brake 2 is inactive in controls-branch firmware.
if appsPlausible
    throttleValidPct = mean([t1 t2]);
else
    t1 = 0; t2 = 0; throttleValidPct = 0;
end
if brakePlausible
    brakeValidPct = b1;
else
    b1 = 0; b2 = 0; brakeValidPct = 0;
end
if throttleValidPct >= 25 && brakeValidPct >= 25
    context.appsError = true;
elseif context.appsError && throttleValidPct <= 5
    context.appsError = false;
end
torqueRequestPct = throttleValidPct;
if ~appsPlausible || context.appsError
    torqueRequestPct = 0;
end

if isstruct(rx) && isfield(rx,'id') && isfield(rx,'payload')
    decoded = virtualvcu.decodeStatusFrame(rx.id, rx.payload);
    if decoded.known
        context.can.valid = true;
        context.can.lastId = uint32(rx.id);
        ids3x3 = uint32(hex2dec({'383','393','3A3','3B3'}));
        ids3x5 = uint32(hex2dec({'385','395','3A5','3B5'}));
        motor = find(uint32(rx.id) == ids3x3, 1);
        if ~isempty(motor)
            context.can.seenMask = bitor(context.can.seenMask, bitshift(uint16(1), motor-1));
            context.can.inverterReady = context.can.inverterReady || decoded.fields.inverterReady;
            context.can.inverterFault = context.can.inverterFault || ...
                decoded.fields.inverterState == 2 || decoded.fields.inverterState == 3;
        else
            motor = find(uint32(rx.id) == ids3x5, 1);
            if ~isempty(motor)
                context.can.wheelSpeedRadS(motor) = decoded.fields.wheelSpeedRadS;
                context.can.wheelSpeedValid(motor) = true;
            elseif uint32(rx.id) == uint32(hex2dec('400'))
                context.can.dcLink12V = decoded.fields.dcLink12V;
                context.can.dcLink34V = decoded.fields.dcLink34V;
                context.can.systemValid = true;
            end
        end
    end
end

dcHealthy = context.can.systemValid && ...
    context.can.dcLink12V > c.prechargeFloorV && ...
    context.can.dcLink34V > c.prechargeFloorV;
if ~enabled
    context.state = uint8(0); context.ticks = uint32(0); context.resetSent = false;
elseif (context.state == 2 || context.state == 3) && ~dcHealthy
    context.state = uint8(5); context.ticks = uint32(0);
elseif context.state == 4 && (~dcHealthy || di(c.digitalMap.shutdownFeedback))
    context.state = uint8(5); context.ticks = uint32(0);
elseif context.state == 5 && di(c.digitalMap.shutdownFeedback)
    % Deliberate bench deviation: hold an observable shutdown fault.
elseif context.state == 5
    context.state = uint8(0); context.ticks = uint32(0);
elseif context.state == 0 && di(c.digitalMap.precharge)
    context.state = uint8(1); context.ticks = uint32(0);
elseif context.state == 1
    context.ticks = context.ticks + 1;
    if context.ticks >= c.prechargeTicks, context.state = uint8(2); context.ticks = uint32(0); end
elseif context.state == 2 && di(c.digitalMap.main) && brakeValidPct >= 25
    context.state = uint8(3); context.ticks = uint32(0);
elseif context.state == 3
    context.ticks = context.ticks + 1;
    if context.ticks >= c.buzzingTicks, context.state = uint8(4); context.ticks = uint32(0); end
elseif context.state == 4 && di(c.digitalMap.precharge)
    context.state = uint8(1); context.ticks = uint32(0);
end

if context.state ~= 4
    context.resetSent = false;
end
controlPayloads = zeros(4,8,'uint8');
cornerTorqueNm = zeros(1,4);
if context.state == 4 && ~context.resetSent
    for inverter = 1:4
        controlPayloads(inverter,:) = virtualvcu.packControlFrame( ...
            inverter, true, 0, 0, true);
    end
    context.resetSent = true;
elseif context.state == 4
    cornerTorqueNm = min(tau, c.maxTorqueNm);
    inverterTau = cornerTorqueNm(double(c.controlsTauToInverter));
    for inverter = 1:4
        controlPayloads(inverter,:) = virtualvcu.packControlFrame( ...
            inverter, true, c.speedLimitRpm, inverterTau(inverter), false);
    end
end

pedalThrottlePct = throttleValidPct;
if context.state == 4
    pedalThrottlePct = torqueRequestPct;
end
if ~enabled
    pedalThrottlePct = 0; b1 = 0; b2 = 0; controlPayloads(:) = 0; cornerTorqueNm(:) = 0;
end

outputs = struct('mainEnable',context.state == 2 || context.state == 3 || context.state == 4, ...
    'prechargeEnable',context.state == 1 || context.state == 2, ...
    'inverterControlEnable',context.state >= 1 && context.state <= 4, ...
    'coolingRelays',di(c.digitalMap.cooling), 'fanRelay',di(c.digitalMap.fan));
out = struct('state', c.stateNames{double(context.state)+1}, ...
    'stateId', context.state, 'enabled', logical(enabled), 'context', context, ...
    'raw', raw, 'pedalPct', [t1 t2 b1 b2], 'valid', [tv1 tv2 bv1 bv2], ...
    'appsPlausible', appsPlausible, 'brakePlausible', brakePlausible, ...
    'appsError',context.appsError,'torqueRequestPct',torqueRequestPct, ...
    'digitalInputs', di, 'outputs',outputs,'can', context.can, ...
    'torqueRequestNm', cornerTorqueNm, ...
    'pedalPayload', virtualvcu.packPedalFrame(pedalThrottlePct, b1/100, b2/100), ...
    'controlPayloads', controlPayloads);
end
