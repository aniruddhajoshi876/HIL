function diag = rawControlDiagnostics(bank)
%RAWCONTROLDIAGNOSTICS Flatten the TEMPORARY raw control-frame diagnostic
%fields (see INITIALDECODERBANK) into a fixed-size numeric signal.
%
%   DIAG = RAWCONTROLDIAGNOSTICS(BANK) returns a 1x6 double row:
%      1  rawControlMatchCount, monotonic, bank-wide
%      2  maskForcedDropCount, monotonic, bank-wide
%      3  rawControlLastId, latched
%      4  rawControlLastDlc, latched
%      5  rawControlLastExtended, latched (0/1)
%      6  rawControlLastRemote, latched (0/1)
%
%   Remove this function once the root cause behind the control channels'
%   permanent rejection is found and INITIALDECODERBANK's diagnostic fields
%   are removed.

diag = zeros(1, 6);
diag(1) = double(bank.rawControlMatchCount);
diag(2) = double(bank.maskForcedDropCount);
diag(3) = double(bank.rawControlLastId);
diag(4) = double(bank.rawControlLastDlc);
diag(5) = double(bank.rawControlLastExtended);
diag(6) = double(bank.rawControlLastRemote);
end
