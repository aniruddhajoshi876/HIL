function [visible, rowHeights, fieldNames] = inverterPanelVisibility(expanded)
%INVERTERPANELVISIBILITY Summary of outbound inverter-panel field visibility.
%
%   [VISIBLE, ROWHEIGHTS, FIELDNAMES] = INVERTERPANELVISIBILITY(EXPANDED)
%   returns the ordered 12-field contract, its visibility mask, and compact
%   grid-row heights for one outbound inverter panel. Hidden rows retain their
%   labels and use zero height so refreshInverters can keep updating all fields.

if ~islogical(expanded) || ~isscalar(expanded)
    error('inverterhilgui:InvalidExpandedState', ...
        'Expanded state must be a logical scalar.');
end

fieldNames = {'STATE', 'READY', 'CMD AGE', 'TORQUE CMD', ...
    'TORQUE ACT', 'SPEED', 'Id set/act', 'Iq set/act', ...
    'MOTOR TEMP', 'SWITCH TEMP', 'DERATING', 'ACTIVE FAULT'};
summaryFields = {'TORQUE CMD', 'TORQUE ACT', 'MOTOR TEMP'};
visible = ismember(fieldNames, summaryFields);
if expanded
    visible(:) = true;
end
rowHeights = num2cell(20 * double(visible));
end
