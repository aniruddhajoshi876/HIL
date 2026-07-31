function panel = formatInverterPanel(snapshot, index)
%FORMATINVERTERPANEL Display fields for one inverter from a telemetry snapshot.
%
%   PANEL = FORMATINVERTERPANEL(SNAPSHOT, INDEX) reads only
%   SNAPSHOT.INVERTER(INDEX), so status from one inverter can never leak into
%   another panel. Plan 4.1.3 requires the canonical inverter number to remain
%   visible and the provisional corner label to stay UNVERIFIED until the
%   FL/FR/RL/RR mapping is confirmed, so CORNER is a constant here.
%
%   Torque is rendered by INVERTERHILGUI.FORMATTORQUECANDIDATES, which always
%   shows the raw count and both candidate scales.

theme = inverterhilgui.guiTheme();
noData = theme.text.noData;

panel = struct( ...
    'title', noData, ...
    'corner', theme.text.cornerLabel, ...
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
