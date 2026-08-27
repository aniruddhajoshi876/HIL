function [next, output] = stepPlant(state, input, cal)
%STEPPLANT Advance four independent torque, mechanical, and thermal plants.
% Positive DC current is battery discharge; negative DC current is charge.

if nargin < 3
    cal = inverterhil.defaultCalibration();
end
inverterhil.validateCalibration(cal);
validatePlantState(state, cal);
validatePlantInput(input, cal);

next = state;
if state.stepCount == intmax('uint64')
    next.stepCount = state.stepCount;
else
    next.stepCount = state.stepCount + uint64(1);
end
output = initialOutput(cal);
dt = cal.sampleTimeS;

for channelIndex = 1:4
    channelInput = input.channels(channelIndex);
    speedRpm = radPerSecondToRpm(state.omegaRadPerS(channelIndex));
    speedErrorRpm = channelInput.speedSetpointRpm - speedRpm;

    currentTorqueNm = cal.modelCurrentMaxA(channelIndex) * ...
        cal.torqueConstantNmPerA(channelIndex);
    normalLowerNm = max([channelInput.torqueLimitNegativeNm, ...
        cal.modelTorqueMinNm(channelIndex), -currentTorqueNm]);
    normalUpperNm = min([channelInput.torqueLimitPositiveNm, ...
        cal.modelTorqueMaxNm(channelIndex), currentTorqueNm]);
    if normalLowerNm > normalUpperNm
        error('inverterhil:InvalidPlantInput', ...
            'Channel %d torque limits have no safe intersection.', ...
            channelIndex);
    end

    switchFactor = switchDeratingFactor( ...
        state.switchTemperatureC(channelIndex));
    motorFactor = linearDeratingFactor( ...
        state.motorTemperatureC(channelIndex), ...
        cal.motorDerateStartC(channelIndex), ...
        cal.motorDerateEndC(channelIndex));
    torquePermission = min(switchFactor, motorFactor);
    lowerNm = normalLowerNm * torquePermission;
    upperNm = normalUpperNm * torquePermission;

    proportionalNm = cal.speedKp(channelIndex) * speedErrorRpm;
    integralDeltaNm = cal.speedKi(channelIndex) * speedErrorRpm * dt;
    requireFiniteResult(proportionalNm, 'speed proportional term');
    requireFiniteResult(integralDeltaNm, 'speed integral increment');
    integratorCandidateNm = state.speedIntegratorNm(channelIndex) + ...
        integralDeltaNm;
    requireFiniteResult(integratorCandidateNm, 'speed integrator');
    controllerCandidateNm = proportionalNm + integratorCandidateNm;
    requireFiniteResult(controllerCandidateNm, 'speed controller output');

    heldControllerNm = proportionalNm + ...
        state.speedIntegratorNm(channelIndex);
    requireFiniteResult(heldControllerNm, 'held speed controller output');
    pushesUpperLimit = controllerCandidateNm > upperNm && speedErrorRpm > 0;
    pushesLowerLimit = controllerCandidateNm < lowerNm && speedErrorRpm < 0;
    if pushesUpperLimit
        if heldControllerNm >= upperNm
            integratorNm = state.speedIntegratorNm(channelIndex);
        else
            integratorNm = upperNm - proportionalNm;
        end
    elseif pushesLowerLimit
        if heldControllerNm <= lowerNm
            integratorNm = state.speedIntegratorNm(channelIndex);
        else
            integratorNm = lowerNm - proportionalNm;
        end
    else
        integratorNm = integratorCandidateNm;
    end
    requireFiniteResult(integratorNm, 'bounded speed integrator');
    rawControllerTorqueNm = proportionalNm + integratorNm;
    requireFiniteResult(rawControllerTorqueNm, 'limited controller output');
    boundedTorqueNm = clamp(rawControllerTorqueNm, lowerNm, upperNm);

    [authorityZero, authorityReason] = torqueAuthority(channelInput);
    if authorityZero
        % Final safety authority is immediate and does not integrate or lag.
        integratorNm = state.speedIntegratorNm(channelIndex);
        torqueSetpointNm = 0;
        torqueActualNm = 0;
    else
        slewDeltaNm = cal.torqueSlewNmPerS(channelIndex) * dt;
        requireFiniteResult(slewDeltaNm, 'torque slew increment');
        torqueSetpointNm = state.torqueSetpointNm(channelIndex) + clamp( ...
            boundedTorqueNm - state.torqueSetpointNm(channelIndex), ...
            -slewDeltaNm, slewDeltaNm);
        lagAlpha = 1 - exp(-dt / cal.torqueLagS(channelIndex));
        torqueActualNm = state.torqueActualNm(channelIndex) + lagAlpha * ...
            (torqueSetpointNm - state.torqueActualNm(channelIndex));
        requireFiniteResult(torqueSetpointNm, 'torque setpoint');
        requireFiniteResult(torqueActualNm, 'actual torque');
        torqueSetpointNm = clamp(torqueSetpointNm, lowerNm, upperNm);
        torqueActualNm = clamp(torqueActualNm, lowerNm, upperNm);
    end

    omegaDot = (torqueActualNm - channelInput.loadTorqueNm - ...
        cal.dragNmPerRadS(channelIndex) * ...
        state.omegaRadPerS(channelIndex)) / ...
        cal.inertiaKgM2(channelIndex);
    requireFiniteResult(omegaDot, 'angular acceleration');
    candidateOmega = state.omegaRadPerS(channelIndex) + dt * omegaDot;
    requireFiniteResult(candidateOmega, 'motor speed');
    candidateSpeedRpm = radPerSecondToRpm(candidateOmega);
    speedLimited = abs(candidateSpeedRpm) > cal.speedMaxRpm(channelIndex);
    limitedSpeedRpm = clamp(candidateSpeedRpm, ...
        -cal.speedMaxRpm(channelIndex), cal.speedMaxRpm(channelIndex));
    omegaRadPerS = rpmToRadPerSecond(limitedSpeedRpm);

    idSetpointA = 0;
    idActualA = 0;
    iqSetpointA = torqueSetpointNm / ...
        cal.torqueConstantNmPerA(channelIndex);
    iqActualA = torqueActualNm / ...
        cal.torqueConstantNmPerA(channelIndex);
    requireFiniteResult(iqSetpointA, 'Iq setpoint');
    requireFiniteResult(iqActualA, 'actual Iq');

    mechanicalPowerW = torqueActualNm * omegaRadPerS;
    if mechanicalPowerW >= 0
        dcPowerW = mechanicalPowerW / ...
            cal.motoringEfficiency(channelIndex);
        conversionLossW = max(dcPowerW - mechanicalPowerW, 0);
    else
        dcPowerW = mechanicalPowerW * cal.regenEfficiency(channelIndex);
        conversionLossW = max(abs(mechanicalPowerW) - abs(dcPowerW), 0);
    end
    dcCurrentA = dcPowerW / max(abs(channelInput.dcLinkV), ...
        cal.dcVoltageFloorV(channelIndex));
    requireFiniteResult(mechanicalPowerW, 'mechanical power');
    requireFiniteResult(dcPowerW, 'DC power');
    requireFiniteResult(dcCurrentA, 'DC current');
    requireFiniteResult(conversionLossW, 'conversion loss');

    motorLossW = conversionLossW * cal.motorLossFraction(channelIndex);
    switchLossW = conversionLossW - motorLossW;
    motorTemperatureC = thermalStep( ...
        state.motorTemperatureC(channelIndex), ...
        cal.ambientTemperatureC(channelIndex), motorLossW, ...
        cal.motorThermalResistanceCPerW(channelIndex), ...
        cal.motorThermalTimeConstantS(channelIndex), dt);
    switchTemperatureC = thermalStep( ...
        state.switchTemperatureC(channelIndex), ...
        cal.ambientTemperatureC(channelIndex), switchLossW, ...
        cal.switchThermalResistanceCPerW(channelIndex), ...
        cal.switchThermalTimeConstantS(channelIndex), dt);

    maxAllowedCurrentA = min(cal.modelCurrentMaxA(channelIndex), ...
        max(abs([lowerNm upperNm])) / ...
        cal.torqueConstantNmPerA(channelIndex));
    derating = torquePermission < 1;

    next.omegaRadPerS(channelIndex) = omegaRadPerS;
    next.torqueSetpointNm(channelIndex) = torqueSetpointNm;
    next.torqueActualNm(channelIndex) = torqueActualNm;
    next.speedIntegratorNm(channelIndex) = integratorNm;
    next.motorTemperatureC(channelIndex) = motorTemperatureC;
    next.switchTemperatureC(channelIndex) = switchTemperatureC;

    result = emptyChannelOutput();
    % AUTHORITYREASON takes strings of different lengths across branches in
    % TORQUEAUTHORITY below; MATLAB Coder locks the field's size at the fixed
    % 'default_safe' value EMPTYCHANNELOUTPUT assigns unless told otherwise.
    coder.varsize('result.authorityReason', [1, 48], [0, 1]);
    result.speedSetpointRpm = channelInput.speedSetpointRpm;
    result.speedRpm = limitedSpeedRpm;
    result.unboundedSpeedRpm = candidateSpeedRpm;
    result.speedErrorRpm = speedErrorRpm;
    result.speedLimited = speedLimited;
    result.rawControllerTorqueNm = rawControllerTorqueNm;
    result.normalTorqueLowerNm = normalLowerNm;
    result.normalTorqueUpperNm = normalUpperNm;
    result.allowedTorqueLowerNm = lowerNm;
    result.allowedTorqueUpperNm = upperNm;
    result.torqueSetpointNm = torqueSetpointNm;
    result.torqueActualNm = torqueActualNm;
    result.idSetpointA = idSetpointA;
    result.idActualA = idActualA;
    result.iqSetpointA = iqSetpointA;
    result.iqActualA = iqActualA;
    result.motorTemperatureC = motorTemperatureC;
    result.switchTemperatureC = switchTemperatureC;
    result.switchDeratingFactor = switchFactor;
    result.motorDeratingFactor = motorFactor;
    result.torquePermission = torquePermission;
    result.maxAllowedCurrentA = maxAllowedCurrentA;
    result.derating = derating;
    result.zeroTorqueApplied = authorityZero;
    result.authorityReason = authorityReason;
    result.mechanicalPowerW = mechanicalPowerW;
    result.dcPowerW = dcPowerW;
    result.dcCurrentA = dcCurrentA;
    result.motorLossW = motorLossW;
    result.switchLossW = switchLossW;
    result.rawTorquePosCounts = int16(channelInput.rawTorquePosCounts);
    result.rawTorqueNegCounts = int16(channelInput.rawTorqueNegCounts);
    result.torquePosNm256 = double(result.rawTorquePosCounts) / 256;
    result.torqueNegNm256 = double(result.rawTorqueNegCounts) / 256;
    result.torquePosNm512 = double(result.rawTorquePosCounts) / 512;
    result.torqueNegNm512 = double(result.rawTorqueNegCounts) / 512;
    result.selectedTorquePositiveNm = channelInput.torqueLimitPositiveNm;
    result.selectedTorqueNegativeNm = channelInput.torqueLimitNegativeNm;
    result.status3X3 = struct( ...
        'state', channelInput.mode, ...
        'ready', logical(channelInput.ready), ...
        'derating', derating, ...
        'maxAllowedCurrentA', maxAllowedCurrentA, ...
        'actualTorqueNm', torqueActualNm, ...
        'torqueSetpointNm', torqueSetpointNm, ...
        'motorTemperatureC', motorTemperatureC, ...
        'switchTemperatureC', switchTemperatureC);
    result.status3X5 = struct( ...
        'idSetpointA', idSetpointA, ...
        'idActualA', idActualA, ...
        'iqSetpointA', iqSetpointA, ...
        'iqActualA', iqActualA, ...
        'speedRpm', limitedSpeedRpm);
    output.channels(channelIndex) = result;
end

output.torqueSetpointNm = [output.channels.torqueSetpointNm];
output.torqueActualNm = [output.channels.torqueActualNm];
output.speedRpm = [output.channels.speedRpm];
output.idSetpointA = [output.channels.idSetpointA];
output.idActualA = [output.channels.idActualA];
output.iqSetpointA = [output.channels.iqSetpointA];
output.iqActualA = [output.channels.iqActualA];
output.motorTemperatureC = [output.channels.motorTemperatureC];
output.switchTemperatureC = [output.channels.switchTemperatureC];
output.maxAllowedCurrentA = [output.channels.maxAllowedCurrentA];
output.derating = [output.channels.derating];
output.speedLimited = [output.channels.speedLimited];
output.dcCurrentA = [output.channels.dcCurrentA];
end

function output = initialOutput(cal)
output.protocolProfileId = cal.protocolProfileId;
output.torqueScaleNmPerCount = cal.torqueScaleNmPerCount;
output.torqueScaleVerified = logical(cal.torqueScaleVerified);
output.channels = repmat(emptyChannelOutput(), 1, 4);
% AUTHORITYREASON is overwritten per channel below with strings of different
% lengths than the 'default_safe' literal EMPTYCHANNELOUTPUT assigns.
coder.varsize('output.channels.authorityReason', [1, 48], [0, 1]);
output.torqueSetpointNm = zeros(1, 4);
output.torqueActualNm = zeros(1, 4);
output.speedRpm = zeros(1, 4);
output.idSetpointA = zeros(1, 4);
output.idActualA = zeros(1, 4);
output.iqSetpointA = zeros(1, 4);
output.iqActualA = zeros(1, 4);
output.motorTemperatureC = zeros(1, 4);
output.switchTemperatureC = zeros(1, 4);
output.maxAllowedCurrentA = zeros(1, 4);
output.derating = false(1, 4);
output.speedLimited = false(1, 4);
output.dcCurrentA = zeros(1, 4);
end

function result = emptyChannelOutput()
result = struct( ...
    'speedSetpointRpm', 0, 'speedRpm', 0, 'unboundedSpeedRpm', 0, ...
    'speedErrorRpm', 0, 'speedLimited', false, ...
    'rawControllerTorqueNm', 0, 'normalTorqueLowerNm', 0, ...
    'normalTorqueUpperNm', 0, 'allowedTorqueLowerNm', 0, ...
    'allowedTorqueUpperNm', 0, 'torqueSetpointNm', 0, ...
    'torqueActualNm', 0, 'idSetpointA', 0, 'idActualA', 0, ...
    'iqSetpointA', 0, 'iqActualA', 0, 'motorTemperatureC', 0, ...
    'switchTemperatureC', 0, 'switchDeratingFactor', 1, ...
    'motorDeratingFactor', 1, 'torquePermission', 1, ...
    'maxAllowedCurrentA', 0, 'derating', false, ...
    'zeroTorqueApplied', true, 'authorityReason', 'default_safe', ...
    'mechanicalPowerW', 0, 'dcPowerW', 0, 'dcCurrentA', 0, ...
    'motorLossW', 0, 'switchLossW', 0, ...
    'rawTorquePosCounts', int16(0), ...
    'rawTorqueNegCounts', int16(0), ...
    'torquePosNm256', 0, 'torqueNegNm256', 0, ...
    'torquePosNm512', 0, 'torqueNegNm512', 0, ...
    'selectedTorquePositiveNm', 0, 'selectedTorqueNegativeNm', 0, ...
    'status3X3', emptyStatus3X3(), 'status3X5', emptyStatus3X5());
end

function status = emptyStatus3X3()
status = struct('state', uint8(0), 'ready', false, ...
    'derating', false, 'maxAllowedCurrentA', 0, ...
    'actualTorqueNm', 0, 'torqueSetpointNm', 0, ...
    'motorTemperatureC', 0, 'switchTemperatureC', 0);
end

function status = emptyStatus3X5()
status = struct('idSetpointA', 0, 'idActualA', 0, ...
    'iqSetpointA', 0, 'iqActualA', 0, 'speedRpm', 0);
end

function [blocked, reason] = torqueAuthority(channelInput)
coder.varsize('reason', [1, 48], [0, 1]);
p = inverterhil.protocol();
if channelInput.mode ~= p.state.drive
    blocked = true;
    reason = 'mode_not_drive';
elseif ~logical(channelInput.ready)
    blocked = true;
    reason = 'not_ready';
elseif ~strcmp(char(channelInput.activeFault), 'none')
    blocked = true;
    reason = 'active_fault';
elseif logical(channelInput.commandErrorTimeout)
    blocked = true;
    reason = 'command_error_timeout';
elseif logical(channelInput.commandTorqueTimeout)
    blocked = true;
    reason = 'command_torque_timeout';
elseif logical(channelInput.zeroTorque)
    blocked = true;
    reason = char(channelInput.authorityReason);
else
    blocked = false;
    reason = 'torque_enabled';
end
end

function factor = switchDeratingFactor(temperatureC)
% Fixed Ephorus switch-permission profile: 1 at 90 C, 0 at 140 C.
factor = linearDeratingFactor(temperatureC, 90, 140);
end

function factor = linearDeratingFactor(value, startValue, endValue)
if value <= startValue
    factor = 1;
elseif value >= endValue
    factor = 0;
else
    factor = (endValue - value) / (endValue - startValue);
end
end

function temperatureC = thermalStep(temperatureC, ambientC, lossW, ...
        resistanceCPerW, timeConstantS, dt)
targetC = ambientC + lossW * resistanceCPerW;
alpha = 1 - exp(-dt / timeConstantS);
temperatureC = temperatureC + alpha * (targetC - temperatureC);
requireFiniteResult(temperatureC, 'thermal state');
end

function validatePlantState(state, cal)
required = {'protocolProfileId', 'omegaRadPerS', 'torqueSetpointNm', ...
    'torqueActualNm', 'speedIntegratorNm', 'motorTemperatureC', ...
    'switchTemperatureC', 'stepCount'};
requireFields(state, required, 'inverterhil:InvalidPlantState');
if ~isTextScalar(state.protocolProfileId) || ...
        ~strcmp(char(state.protocolProfileId), cal.protocolProfileId)
    error('inverterhil:InvalidPlantState', ...
        'Plant state protocol profile must match calibration.');
end
vectorFields = {'omegaRadPerS', 'torqueSetpointNm', ...
    'torqueActualNm', 'speedIntegratorNm', 'motorTemperatureC', ...
    'switchTemperatureC'};
for fieldIndex = 1:numel(vectorFields)
    value = state.(vectorFields{fieldIndex});
    if ~isnumeric(value) || ~isequal(size(value), [1 4]) || ...
            ~isreal(value) || any(~isfinite(value))
        error('inverterhil:InvalidPlantState', ...
            '%s must be a real finite 1x4 vector.', ...
            vectorFields{fieldIndex});
    end
end
if ~isa(state.stepCount, 'uint64') || ~isscalar(state.stepCount)
    error('inverterhil:InvalidPlantState', ...
        'stepCount must be a uint64 scalar.');
end
end

function validatePlantInput(input, cal)
requireFields(input, {'protocolProfileId', 'channels'}, ...
    'inverterhil:InvalidPlantInput');
if ~isTextScalar(input.protocolProfileId) || ...
        ~strcmp(char(input.protocolProfileId), cal.protocolProfileId)
    error('inverterhil:InvalidPlantInput', ...
        'Plant input protocol profile must match calibration.');
end
if ~isstruct(input.channels) || ~isequal(size(input.channels), [1 4])
    error('inverterhil:InvalidPlantInput', ...
        'channels must be a 1x4 structure array.');
end

required = {'mode', 'ready', 'zeroTorque', 'activeFault', ...
    'commandTorqueTimeout', 'commandErrorTimeout', 'authorityReason', ...
    'speedSetpointRpm', 'torqueLimitPositiveNm', ...
    'torqueLimitNegativeNm', 'rawTorquePosCounts', ...
    'rawTorqueNegCounts', 'loadTorqueNm', 'dcLinkV'};
p = inverterhil.protocol();
for channelIndex = 1:4
    channelInput = input.channels(channelIndex);
    requireFields(channelInput, required, 'inverterhil:InvalidPlantInput');
    if ~isa(channelInput.mode, 'uint8') || ~isscalar(channelInput.mode) || ...
            ~any(channelInput.mode == [p.state.idle p.state.drive ...
            p.state.error p.state.configError])
        error('inverterhil:InvalidPlantInput', ...
            'Channel %d mode is invalid.', channelIndex);
    end
    binaryFields = {'ready', 'zeroTorque', 'commandTorqueTimeout', ...
        'commandErrorTimeout'};
    for fieldIndex = 1:numel(binaryFields)
        validateBinary(channelInput.(binaryFields{fieldIndex}), ...
            binaryFields{fieldIndex}, channelIndex);
    end
    textFields = {'activeFault', 'authorityReason'};
    for fieldIndex = 1:numel(textFields)
        if ~isTextScalar(channelInput.(textFields{fieldIndex}))
            error('inverterhil:InvalidPlantInput', ...
                'Channel %d %s must be nonempty scalar text.', ...
                channelIndex, textFields{fieldIndex});
        end
    end
    finiteFields = {'speedSetpointRpm', 'torqueLimitPositiveNm', ...
        'torqueLimitNegativeNm', 'loadTorqueNm', 'dcLinkV'};
    for fieldIndex = 1:numel(finiteFields)
        validateFiniteScalar(channelInput.(finiteFields{fieldIndex}), ...
            finiteFields{fieldIndex}, channelIndex);
    end
    if channelInput.torqueLimitPositiveNm < 0 || ...
            channelInput.torqueLimitNegativeNm > 0 || ...
            channelInput.torqueLimitNegativeNm > ...
            channelInput.torqueLimitPositiveNm
        error('inverterhil:InvalidPlantInput', ...
            ['Channel %d torque limits must be ordered with a nonpositive ' ...
            'negative limit and nonnegative positive limit.'], channelIndex);
    end
    validateRawCount(channelInput.rawTorquePosCounts, ...
        'rawTorquePosCounts', channelIndex);
    validateRawCount(channelInput.rawTorqueNegCounts, ...
        'rawTorqueNegCounts', channelIndex);
end
end

function validateFiniteScalar(value, name, channelIndex)
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
        ~isfinite(value)
    error('inverterhil:InvalidPlantInput', ...
        'Channel %d %s must be a real finite numeric scalar.', ...
        channelIndex, name);
end
end

function validateRawCount(value, name, channelIndex)
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
        ~isfinite(double(value)) || double(value) ~= fix(double(value)) || ...
        double(value) < double(intmin('int16')) || ...
        double(value) > double(intmax('int16'))
    error('inverterhil:InvalidPlantInput', ...
        'Channel %d %s must be an integer in the int16 range.', ...
        channelIndex, name);
end
end

function validateBinary(value, name, channelIndex)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:InvalidPlantInput', ...
        'Channel %d %s must be logical 0 or 1.', channelIndex, name);
end
end

function requireFields(value, fields, identifier)
if ~isstruct(value) || ~isscalar(value)
    error(identifier, 'Value must be a scalar structure.');
end
for fieldIndex = 1:numel(fields)
    if ~isfield(value, fields{fieldIndex})
        error(identifier, 'Value is missing field %s.', fields{fieldIndex});
    end
end
end

function valid = isTextScalar(value)
if ischar(value)
    valid = isrow(value) && ~isempty(value);
elseif isstring(value)
    valid = isscalar(value) && ~ismissing(value) && strlength(value) > 0;
else
    valid = false;
end
end

function result = clamp(value, lower, upper)
result = min(max(value, lower), upper);
end

function rpm = radPerSecondToRpm(omega)
rpm = omega * 60 / (2 * pi);
requireFiniteResult(rpm, 'speed conversion');
end

function omega = rpmToRadPerSecond(rpm)
omega = rpm * (2 * pi) / 60;
requireFiniteResult(omega, 'speed conversion');
end

function requireFiniteResult(value, label)
if ~isreal(value) || ~isscalar(value) || ~isfinite(value)
    error('inverterhil:NumericalPlantFailure', ...
        '%s produced a non-finite plant result.', label);
end
end
