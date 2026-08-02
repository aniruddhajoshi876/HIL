function theme = guiTheme()
%GUITHEME Dense light engineering-console colors, typography, and spacing.
%   High-contrast black-on-white variant for readability (panels, tab bar,
%   and body text all resolve to near-black on near-white).

theme.color.background = hexColor('FFFFFF');
theme.color.panel = hexColor('F1F3F6');
theme.color.panelEdge = hexColor('B7C0CC');
theme.color.healthy = hexColor('1B7A3D');
theme.color.electrical = hexColor('0F5FB8');
theme.color.waiting = hexColor('9A6300');
theme.color.fault = hexColor('C4291D');
theme.color.primaryText = hexColor('000000');
theme.color.secondaryText = hexColor('33404D');
theme.color.disabledText = hexColor('8A93A0');
theme.color.highlight = hexColor('D6E4F5');

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
