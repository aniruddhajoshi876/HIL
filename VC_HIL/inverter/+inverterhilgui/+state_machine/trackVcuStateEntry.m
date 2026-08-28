function [enteredS, timeInStateS] = trackVcuStateEntry(currentState, ...
    previousState, previousEnteredS, nowS)
%TRACKVCUSTATEENTRY Compute the VCU state-entry timestamp and elapsed time.
%
%   [ENTEREDS, TIMEINSTATES] = TRACKVCUSTATEENTRY(CURRENTSTATE,
%   PREVIOUSSTATE, PREVIOUSENTEREDS, NOWS) resets the tracked entry
%   timestamp to NOWS whenever CURRENTSTATE differs from PREVIOUSSTATE, or
%   whenever PREVIOUSENTEREDS is not a finite time (state was not
%   previously known, e.g. just reconnected). Otherwise the existing
%   PREVIOUSENTEREDS is kept. TIMEINSTATES is always NOWS - ENTEREDS, so a
%   caller polling this on every refresh tick gets a live-incrementing
%   elapsed time even while CURRENTSTATE stays the same.
%
%   Pure function: exists so time-in-state tracking is unit-testable
%   without the target session/backend machinery (INVERTER_HIL_APP takes
%   no injected backend and always talks to a real target -- see
%   FAKETARGETBACKEND).

if ~(ischar(currentState) || (isstring(currentState) && isscalar(currentState)))
    error('inverterhilgui:InvalidVcuState', ...
        'currentState must be a char row or scalar string.');
end
if ~(ischar(previousState) || (isstring(previousState) && isscalar(previousState)))
    error('inverterhilgui:InvalidVcuState', ...
        'previousState must be a char row or scalar string.');
end
if ~isnumeric(previousEnteredS) || ~isscalar(previousEnteredS) || ~isreal(previousEnteredS)
    error('inverterhilgui:InvalidStateTimestamp', ...
        'previousEnteredS must be a real numeric scalar.');
end
if ~isnumeric(nowS) || ~isscalar(nowS) || ~isreal(nowS) || ~isfinite(nowS)
    error('inverterhilgui:InvalidStateTimestamp', ...
        'nowS must be a finite real numeric scalar.');
end

if ~strcmp(char(currentState), char(previousState)) || ~isfinite(previousEnteredS)
    enteredS = nowS;
else
    enteredS = previousEnteredS;
end
timeInStateS = nowS - enteredS;
end
