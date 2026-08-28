function display = formatPinState(state)
%FORMATPINSTATE Render a monitored VCU output pin as text plus color.
%
%   Plan 7.3 requires TP6-TP10 pin cards to use ON/OFF text plus color so
%   state is never conveyed by color alone. The TEXT field is therefore
%   always authoritative and is never empty; COLOR is decoration only.
%
%   DISPLAY fields: text, color, known.

theme = inverterhilgui.live_telemetry.guiTheme();
display = struct( ...
    'text', theme.text.noData, ...
    'color', theme.color.secondaryText, ...
    'known', false);

if ~(islogical(state) || isnumeric(state)) || ~isscalar(state) || ...
        ~isreal(state) || ~isfinite(double(state)) || ...
        ~(double(state) == 0 || double(state) == 1)
    return;
end

if logical(state)
    display.text = 'ON';
    display.color = theme.color.healthy;
else
    display.text = 'OFF';
    display.color = theme.color.disabledText;
end
display.known = true;
end
