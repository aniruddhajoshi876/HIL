function text = formatTorqueCandidates(rawCount)
%FORMATTORQUECANDIDATES Render a raw torque count under both candidate scales.
%
%   Plan 4.1.1 leaves the inbound torque scale unresolved between 1/256 and
%   1/512 Nm/count, and open decision 1 keeps it open. Every torque display
%   therefore shows the raw signed count together with BOTH candidate
%   engineering values, never one alone.
%
%   TEXT fields: raw, nm256, nm512, summary, hasData.

noData = '--';
text = struct( ...
    'raw', noData, ...
    'nm256', noData, ...
    'nm512', noData, ...
    'summary', noData, ...
    'hasData', false);

if ~isnumeric(rawCount) || ~isscalar(rawCount) || ~isreal(rawCount) || ...
        ~isfinite(rawCount) || rawCount ~= floor(rawCount) || ...
        rawCount < -32768 || rawCount > 32767
    return;
end

count = double(rawCount);
text.raw = sprintf('%d', count);
text.nm256 = sprintf('%.3f', count / 256);
text.nm512 = sprintf('%.3f', count / 512);
text.summary = sprintf('%s cnt | %s Nm @1/256 | %s Nm @1/512', ...
    text.raw, text.nm256, text.nm512);
text.hasData = true;
end
