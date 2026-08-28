function style = stateCardStyle(currentState, cardState, errorActive)
%STATECARDSTYLE Classify one VCU state card for the live sequence graphic.
% Numeric IDs are 0=LV_ON, 1=PRECHARGING, 2=ENABLE, 3=BUZZING,
% 4=RTD, and 5=ERROR_SHUTDOWN. The GUI receives the corresponding name.
if nargin < 3
    errorActive = false;
end
style = 'unknown';
if ~(ischar(currentState) || (isstring(currentState) && isscalar(currentState)))
    return;
end
if isstring(currentState)
    currentState = char(currentState);
end
if isempty(strtrim(currentState)) || errorActive
    return;
end
names = {'LV_ON', 'PRECHARGING', 'ENABLE', 'BUZZING', 'RTD'};
currentIndex = find(strcmpi(names, currentState), 1);
cardIndex = find(strcmpi(names, cardState), 1);
if isempty(currentIndex) || isempty(cardIndex)
    return;
end
if currentIndex == cardIndex
    style = 'active';
elseif cardIndex < currentIndex
    style = 'passed';
else
    style = 'upcoming';
end
end
