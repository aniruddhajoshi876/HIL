function theme = guiTheme()
%GUITHEME VS Code 2017-style dark engineering-console colors.
%   Near-black chrome, charcoal panels, white text, and restrained semantic
%   accents keep dense telemetry readable without inventing status through
%   color alone.

theme.color.background = hexColor('1E1E1E');
theme.color.panel = hexColor('252526');
theme.color.panelEdge = hexColor('3E3E42');
theme.color.healthy = hexColor('89D185');
theme.color.electrical = hexColor('569CD6');
theme.color.waiting = hexColor('D7BA7D');
theme.color.fault = hexColor('F48771');
theme.color.primaryText = hexColor('F0F0F0');
theme.color.secondaryText = hexColor('CCCCCC');
theme.color.disabledText = hexColor('858585');
theme.color.highlight = hexColor('264F78');

% Tab header bar. Pure black with pure white text, deliberately stronger
% than the 1E1E1E/F0F0F0 chrome around it: this strip sits directly on
% MATLAB's own white native tab header, which R2024b exposes no supported
% way to recolour, so the custom bar must cover it opaquely and stay legible
% at a glance rather than blending into the panels behind it.
%
% Selection is carried by TEXT WEIGHT AND BRIGHTNESS, not by a background
% swap, so every tab keeps the black background that was asked for.
% TABBARINACTIVETEXT is still light (13:1 on black, well past WCAG AA), so
% an unselected tab reads as unselected without becoming hard to read.
theme.color.tabBar = hexColor('000000');
theme.color.tabBarText = hexColor('FFFFFF');
theme.color.tabBarInactiveText = hexColor('CCCCCC');

theme.font.name = 'Consolas';
theme.font.title = 15;
theme.font.heading = 12;
theme.font.body = 11;
theme.font.small = 10;

theme.spacing.padding = [6 6 6 6];
theme.spacing.rowSpacing = 4;
theme.spacing.columnSpacing = 6;
theme.spacing.toolbarHeight = 34;
theme.spacing.stripHeight = 30;
theme.spacing.rowHeight = 20;
theme.spacing.cardHeight = 54;

theme.text.noData = '--';
theme.text.torqueBanner = ['TORQUE SCALE UNVERIFIED - PROVISIONAL PROFILE ' ...
    'ephorus3-v1.03-provisional-1over512 (1/512 Nm/count)'];
theme.text.capturePending = 'CAPTURE PENDING';
theme.text.cornerLabel = 'UNVERIFIED';
end

function rgb = hexColor(hex)
rgb = double([hex2dec(hex(1:2)), hex2dec(hex(3:4)), hex2dec(hex(5:6))]) / 255;
end
