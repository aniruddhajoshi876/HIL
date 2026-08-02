function panel = formatInverterPanel(snapshot, index)
%FORMATINVERTERPANEL Display fields for one inverter from a telemetry snapshot.
%
%   PANEL = FORMATINVERTERPANEL(SNAPSHOT, INDEX) reads only
%   SNAPSHOT.INVERTER(INDEX), so status from one inverter can never leak into
%   another panel.
%
%   CORNER MAPPING - operator-confirmed 2026-08-01:
%     Ephorus index 1 = FL, 2 = FR, 3 = RR, 4 = RL
%   Plan 4.1.3 held the corner label at UNVERIFIED until the FL/FR/RL/RR to
%   Ephorus-index mapping was confirmed; this is that confirmation, recorded
%   here as its single source. The provenance is an operator assertion, NOT an
%   automated check - nothing in this repository can verify which physical
%   wheel an index drives, so if that assertion is wrong every corner label is
%   wrong in a way no test will catch. Plan 4.1.3 also requires the canonical
%   inverter number to stay visible beside the corner, which PANEL.TITLE does.
%   CORNERVERIFIED reports whether CORNER is a real mapping or the UNVERIFIED
%   placeholder, so the caller can colour it accordingly.
%
%   Torque is rendered by INVERTERHILGUI.FORMATTORQUECANDIDATES, which always
%   shows the raw count and both candidate scales.

theme = inverterhilgui.guiTheme();
noData = theme.text.noData;

% Index order is Ephorus 1-4; see the corner-mapping note in the help above.
cornerNames = {'FL', 'FR', 'RR', 'RL'};

panel = struct( ...
    'title', noData, ...
    'corner', theme.text.cornerLabel, ...
    'cornerVerified', false, ...
    'state', noData, ...
    'ready', noData, ...
    'commandAge', noData, ...
    'torqueCommand', noData, ...
    'torqueActual', noData, ...
    'torqueCommandRaw', noData, ...
    'torqueActualRaw', noData, ...
    'speed', noData, ...
    'idCurrent', noData, ...
    'iqCurrent', noData, ...
    'motorTemperature', noData, ...
    'switchTemperature', noData, ...
    'derating', noData, ...
    'activeFault', noData, ...
    'hasData', false);

if ~isnumeric(index) || ~isscalar(index) || ~isreal(index) || ...
        ~isfinite(index) || index < 1 || index > 4 || index ~= floor(index)
    return;
end
panel.title = sprintf('INV%d', index);
% Only reached once INDEX is a validated 1-4, so the lookup cannot go out of
% range and an invalid index keeps the UNVERIFIED placeholder set above.
panel.corner = cornerNames{index};
panel.cornerVerified = true;
if ~isstruct(snapshot) || ~isscalar(snapshot) || ...
        ~isfield(snapshot, 'inverter') || numel(snapshot.inverter) < index
    return;
end
item = snapshot.inverter(index);

panel.state = textOr(item, 'state', noData);
panel.ready = flagText(item, 'ready', 'READY', 'NOT READY', noData);
panel.derating = flagText(item, 'derating', 'ACTIVE', 'NONE', noData);
panel.activeFault = textOr(item, 'activeFault', 'NONE');
if isempty(strtrim(panel.activeFault))
    panel.activeFault = 'NONE';
end
panel.commandAge = scalarText(item, 'commandAgeS', '%.3f s', noData);
panel.speed = scalarText(item, 'speedRpm', '%.0f rpm', noData);
panel.idCurrent = pairText(item, 'idSetpointA', 'idActualA', 'A', noData);
panel.iqCurrent = pairText(item, 'iqSetpointA', 'iqActualA', 'A', noData);

commandTorque = inverterhilgui.formatTorqueCandidates( ...
    numericOr(item, 'torqueCommandRaw'));
actualTorque = inverterhilgui.formatTorqueCandidates( ...
    numericOr(item, 'torqueActualRaw'));
panel.torqueCommand = commandTorque.summary;
panel.torqueActual = actualTorque.summary;
panel.torqueCommandRaw = commandTorque.raw;
panel.torqueActualRaw = actualTorque.raw;

motor = inverterhilgui.formatMeasurement( ...
    numericOr(item, 'motorTemperatureC'), ...
    numericOr(item, 'motorTemperatureRaw'), 'C', true);
switchTemperature = inverterhilgui.formatMeasurement( ...
    numericOr(item, 'switchTemperatureC'), ...
    numericOr(item, 'switchTemperatureRaw'), 'C', false);
panel.motorTemperature = motor.combined;
panel.switchTemperature = switchTemperature.combined;

panel.hasData = commandTorque.hasData || actualTorque.hasData || ...
    motor.hasData || switchTemperature.hasData || ...
    ~strcmp(panel.state, noData);
end

function text = textOr(item, field, fallback)
text = fallback;
if ~isfield(item, field)
    return;
end
value = item.(field);
if isstring(value) && isscalar(value)
    value = char(value);
end
if ischar(value) && ~isempty(strtrim(value))
    text = value;
end
end

function value = numericOr(item, field)
value = NaN;
if ~isfield(item, field)
    return;
end
candidate = item.(field);
if isnumeric(candidate) && isscalar(candidate) && isreal(candidate)
    value = double(candidate);
end
end

function text = flagText(item, field, trueText, falseText, noData)
text = noData;
if ~isfield(item, field)
    return;
end
value = item.(field);
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    return;
end
if logical(value)
    text = trueText;
else
    text = falseText;
end
end

function text = scalarText(item, field, format, noData)
text = noData;
value = numericOr(item, field);
if isfinite(value)
    text = sprintf(format, value);
end
end

function text = pairText(item, setField, actualField, units, noData)
setValue = numericOr(item, setField);
actualValue = numericOr(item, actualField);
if ~isfinite(setValue) && ~isfinite(actualValue)
    text = noData;
    return;
end
text = sprintf('%s / %s %s', numberOrDash(setValue, noData), ...
    numberOrDash(actualValue, noData), units);
end

function text = numberOrDash(value, noData)
if isfinite(value)
    text = sprintf('%.1f', value);
else
    text = noData;
end
end
