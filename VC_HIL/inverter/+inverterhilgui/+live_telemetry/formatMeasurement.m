function text = formatMeasurement(value, rawCount, units, capturePending)
%FORMATMEASUREMENT Render one measurement with its raw count and status.
%
%   Plan 7.3 requires DC-link and motor-temperature rows to show their raw
%   counts beside the selected engineering value with a quiet CAPTURE PENDING
%   status until each known-value check is recorded. When there is no
%   telemetry the row shows dashes, never a fabricated zero.
%
%   TEXT fields: value, raw, status, combined, hasData.

noData = '--';
text = struct( ...
    'value', noData, ...
    'raw', noData, ...
    'status', '', ...
    'combined', noData, ...
    'hasData', false);

if nargin < 3 || isempty(units)
    units = '';
end
if isstring(units) && isscalar(units)
    units = char(units);
end
if ~ischar(units)
    units = '';
end
if nargin < 4
    capturePending = false;
end
pending = false;
if (islogical(capturePending) || isnumeric(capturePending)) && ...
        isscalar(capturePending) && isreal(capturePending) && ...
        isfinite(double(capturePending))
    pending = double(capturePending) ~= 0;
end
if pending
    theme = inverterhilgui.live_telemetry.guiTheme();
    text.status = theme.text.capturePending;
end

hasValue = isnumeric(value) && isscalar(value) && isreal(value) && ...
    isfinite(value);
hasRaw = isnumeric(rawCount) && isscalar(rawCount) && isreal(rawCount) && ...
    isfinite(rawCount) && rawCount == floor(rawCount);

if hasValue
    if isempty(units)
        text.value = sprintf('%.3f', double(value));
    else
        text.value = sprintf('%.3f %s', double(value), units);
    end
end
if hasRaw
    text.raw = sprintf('%d', double(rawCount));
end
if ~hasValue && ~hasRaw
    text.combined = noData;
    return;
end

text.hasData = true;
text.combined = sprintf('%s (%s cnt)', text.value, text.raw);
if ~isempty(text.status)
    text.combined = sprintf('%s  %s', text.combined, text.status);
end
end
