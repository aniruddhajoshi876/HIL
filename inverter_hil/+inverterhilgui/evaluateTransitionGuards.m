function guards = evaluateTransitionGuards(snapshot, thresholds)
%EVALUATETRANSITIONGUARDS Pass/fail rows for the NEXT TRANSITION panel.
%
%   GUARDS = EVALUATETRANSITIONGUARDS(SNAPSHOT, THRESHOLDS) builds the guard
%   rows required by plan 7.3: main button, brake threshold shown as actual
%   versus required, DC-link pair 1/2, DC-link pair 3/4, and driver-input
%   plausibility.
%
%   SNAPSHOT fields used: mainButton (logical), brakePercent (double),
%   dcLink12V (double), dcLink34V (double), plausibilityOk (logical).
%   THRESHOLDS fields used: brakePercent, dcLinkMinimumV.
%
%   The evaluator FAILS CLOSED: an absent or malformed input yields PASS false
%   and KNOWN false with the actual value shown as dashes, so an unknown
%   condition is never displayed as a satisfied condition.

if nargin < 2
    thresholds = struct();
end
noData = inverterhilgui.guiTheme().text.noData;
brakeRequired = numericField(thresholds, 'brakePercent', 20);
dcRequired = numericField(thresholds, 'dcLinkMinimumV', 350);

guards = repmat(emptyGuard(), 0, 1);
guards(end + 1, 1) = logicalGuard(snapshot, 'mainButton', ...
    'Main button', 'PRESSED', noData);
guards(end + 1, 1) = thresholdGuard(snapshot, 'brakePercent', ...
    'Brake threshold', brakeRequired, '%', noData);
guards(end + 1, 1) = thresholdGuard(snapshot, 'dcLink12V', ...
    'DC-link pair 1/2', dcRequired, 'V', noData);
guards(end + 1, 1) = thresholdGuard(snapshot, 'dcLink34V', ...
    'DC-link pair 3/4', dcRequired, 'V', noData);
guards(end + 1, 1) = logicalGuard(snapshot, 'plausibilityOk', ...
    'Driver-input plausibility', 'VALID', noData);
end

function guard = emptyGuard()
guard = struct( ...
    'name', '', ...
    'actual', '--', ...
    'required', '--', ...
    'pass', false, ...
    'known', false);
end

function guard = logicalGuard(snapshot, field, name, requiredText, noData)
guard = emptyGuard();
guard.name = name;
guard.required = requiredText;
guard.actual = noData;
value = rawField(snapshot, field);
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    return;
end
guard.known = true;
guard.pass = logical(value);
if guard.pass
    guard.actual = requiredText;
else
    guard.actual = 'NOT MET';
end
end

function guard = thresholdGuard(snapshot, field, name, required, units, noData)
guard = emptyGuard();
guard.name = name;
guard.required = sprintf('>= %.1f %s', required, units);
guard.actual = noData;
value = rawField(snapshot, field);
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
        ~isfinite(value)
    return;
end
guard.known = true;
guard.actual = sprintf('%.1f %s', double(value), units);
guard.pass = double(value) >= required;
end

function value = rawField(snapshot, field)
value = [];
if isstruct(snapshot) && isscalar(snapshot) && isfield(snapshot, field)
    value = snapshot.(field);
end
end

function value = numericField(source, field, fallback)
value = fallback;
if ~isstruct(source) || ~isscalar(source) || ~isfield(source, field)
    return;
end
candidate = source.(field);
if isnumeric(candidate) && isscalar(candidate) && isreal(candidate) && ...
        isfinite(candidate)
    value = double(candidate);
end
end
