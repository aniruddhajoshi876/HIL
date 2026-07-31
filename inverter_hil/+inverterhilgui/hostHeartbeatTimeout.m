function timeoutS = hostHeartbeatTimeout()
%HOSTHEARTBEATTIMEOUT Host heartbeat timeout, never looser than the target's.
%
%   The target-side fallback in INVERTERHIL.SAFEIOOUTPUTS drops the analog
%   pedal outputs to 0 V once the heartbeat age exceeds
%   CAL.GUIHEARTBEATTIMEOUTS. If the host used a longer timeout, the GUI would
%   keep showing the pedal interface as armed and healthy after the target had
%   already gone safe. The GUI must never look healthier than the target, so
%   the host timeout is the MINIMUM of a conservative host default and the
%   calibrated target timeout.
%
%   This evaluator FAILS CLOSED: if the calibration cannot be read, the
%   conservative host default is used, which can only make the host stricter
%   than the target, never looser.

hostDefaultS = 0.250;

timeoutS = hostDefaultS;
try
    calibrated = inverterhil.defaultCalibration().guiHeartbeatTimeoutS;
catch
    return;
end
if ~isnumeric(calibrated) || ~isscalar(calibrated) || ~isreal(calibrated) || ...
        ~isfinite(calibrated) || calibrated <= 0
    return;
end
timeoutS = min(hostDefaultS, double(calibrated));
end
