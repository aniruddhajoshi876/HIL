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
