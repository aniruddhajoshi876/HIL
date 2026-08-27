function rows = canRowModel(observations, nowS, options)
%CANROWMODEL Build CAN table rows with measured rates and change highlights.
%
%   ROWS = CANROWMODEL(OBSERVATIONS, NOWS, OPTIONS) turns the observed CAN
%   traffic into the split-table rows required by plan 7.3: live state,
%   ID/name, decoded signal, value, and measured rate. The rate is computed
%   from consecutive observed timestamps and is NEVER assumed from the 5 ms
%   nominal cycle: with fewer than two timestamps the rate reads as dashes.
%
%   OBSERVATIONS is a structure array with fields ID, NAME, SIGNAL, VALUE,
%   TIMESTAMPSS (observed arrival times, seconds), LASTCHANGES (host time
%   of the most recent payload change), and COUNT (a genuine, target-
%   measured cumulative message count -- e.g. INVERTERHIL.RXOBSERVATION's
%   ACCEPTEDCOUNT, or EPHORUSSYSTEMSTATUSSTEP's TXCOUNT -- shown verbatim,
%   never derived or estimated here, the same "only show what is actually
%   measured" rule the rate calculation already follows).
%
%   OPTIONS fields: HIGHLIGHTS (change-highlight window, default 0.5 s) and
%   STALES (age past which a row reads STALE, default 0.1 s).
%
%   Rows for malformed observations read NO DATA rather than being dropped, so
%   an expected frame never silently disappears from the table.

if nargin < 3
    options = struct();
end
highlightS = numericOption(options, 'highlightS', 0.5);
staleS = numericOption(options, 'staleS', 0.1);
noData = inverterhilgui.guiTheme().text.noData;

rows = repmat(emptyRow(noData), 0, 1);
if ~isstruct(observations) || isempty(observations)
    return;
end
validNow = isnumeric(nowS) && isscalar(nowS) && isreal(nowS) && isfinite(nowS);
if validNow
    nowS = double(nowS);
end

for index = 1:numel(observations)
    item = observations(index);
    row = emptyRow(noData);
    row.id = idText(item, noData);
    row.name = textOr(item, 'name', noData);
    row.signal = textOr(item, 'signal', noData);
    row.value = textOr(item, 'value', noData);
    row.count = countText(item, noData);

    stamps = timestampVector(item);
    if numel(stamps) >= 2
        intervals = diff(stamps);
        intervals = intervals(intervals > 0);
        if ~isempty(intervals)
            row.rateHz = 1 / median(intervals);
            row.rate = sprintf('%.1f Hz', row.rateHz);
        end
    end

    if ~isempty(stamps)
        row.lastSeenS = stamps(end);
        if validNow
            age = nowS - stamps(end);
            if age < 0
                row.live = 'NO DATA';
            elseif age <= staleS
                row.live = 'LIVE';
            else
                row.live = 'STALE';
            end
        else
            row.live = 'STALE';
        end
    end

    lastChangeS = scalarOr(item, 'lastChangeS');
    if validNow && isfinite(lastChangeS)
        delta = nowS - lastChangeS;
        row.highlight = delta >= 0 && delta <= highlightS;
    end

    rows(end + 1, 1) = row; %#ok<AGROW>
end
end

function row = emptyRow(noData)
row = struct( ...
    'live', 'NO DATA', ...
    'id', noData, ...
    'name', noData, ...
    'signal', noData, ...
    'value', noData, ...
    'rate', noData, ...
    'rateHz', NaN, ...
    'count', noData, ...
    'lastSeenS', NaN, ...
    'highlight', false);
end

function text = countText(item, noData)
%COUNTTEXT A whole, non-negative message count, verbatim from the target.
%   Never fabricated: a missing, non-scalar, negative, or non-integer
%   COUNT reads as NODATA rather than being rounded or clamped into
%   looking like a real one.
text = noData;
if ~isfield(item, 'count')
    return;
end
value = item.count;
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
        ~isfinite(value) || value < 0 || value ~= floor(value)
    return;
end
text = sprintf('%d', value);
end

function text = idText(item, noData)
text = noData;
if ~isfield(item, 'id')
    return;
end
value = item.id;
if isnumeric(value) && isscalar(value) && isreal(value) && ...
        isfinite(double(value)) && double(value) >= 0
    text = sprintf('0x%03X', double(value));
end
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

function stamps = timestampVector(item)
stamps = [];
if ~isfield(item, 'timestampsS')
    return;
end
value = item.timestampsS;
if ~isnumeric(value) || ~isreal(value) || isempty(value)
    return;
end
value = double(value(:))';
value = value(isfinite(value));
stamps = sort(value);
end

function value = scalarOr(item, field)
value = NaN;
if ~isfield(item, field)
    return;
end
candidate = item.(field);
if isnumeric(candidate) && isscalar(candidate) && isreal(candidate)
    value = double(candidate);
end
end

function value = numericOption(options, field, fallback)
value = fallback;
if ~isstruct(options) || ~isscalar(options) || ~isfield(options, field)
    return;
end
candidate = options.(field);
if isnumeric(candidate) && isscalar(candidate) && isreal(candidate) && ...
        isfinite(candidate) && candidate >= 0
    value = double(candidate);
end
end
