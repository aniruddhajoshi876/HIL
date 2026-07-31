function theme = guiTheme()
%GUITHEME Dense dark engineering-console colors, typography, and spacing.

theme.color.background = hexColor('090C0E');
theme.color.panel = hexColor('19232D');
theme.color.panelEdge = hexColor('27333F');
theme.color.healthy = hexColor('3FCF6A');
theme.color.electrical = hexColor('4A9EFF');
theme.color.waiting = hexColor('E0A52A');
theme.color.fault = hexColor('E1483C');
theme.color.primaryText = hexColor('DCE3EA');
theme.color.secondaryText = hexColor('7B8CA0');
theme.color.disabledText = hexColor('4A5765');
theme.color.highlight = hexColor('2E4256');

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
