function observation = rxObservation(bank, tickMs)
%RXOBSERVATION Flatten the decoder bank into a fixed-size numeric signal.
%
%   OBSERVATION = RXOBSERVATION(BANK, TICKMS) returns a 4x14 double matrix,
%   one row per control channel, that the Simulink model can emit as an
%   ordinary signal and the GUI can read back with GETSIGNAL.
%
%   Why flatten at all: the retained bank lives in a PERSISTENT variable
%   inside a MATLAB Function block, and GETSIGNAL cannot read persistents --
%   only signals on wires. Without this the GUI has no way to observe what
%   the target actually received, and the RX table could only ever show
%   dashes or invented content. A plain numeric matrix is used rather than a
%   bus because emitting a struct from a MATLAB Function block would require
%   a SIMULINK.BUS definition, and rows are fixed at 4 so the size is
%   constant for code generation.
%
%   Column layout (all double; the caller casts back):
%      1- 8  raw bytes of the last ACCEPTED frame, byte 1 first
%         9  hasCommand (1 = at least one frame accepted since startup)
%        10  acceptedCount for this channel
%        11  ageMs since the last accepted frame, INTMAX('UINT32') if never
%        12  commandOutOfDomain (1 = torque limits were clamped)
%        13  rejectedCount, bank-wide (repeated on every row)
%        14  lastRejectCode, bank-wide (repeated on every row)
%
%   Columns 13-14 are bank-wide, not per channel: a rejected frame is by
%   definition one that could not be attributed to a channel, so there is no
%   honest per-row value for it. They are repeated rather than split into a
%   second output to keep the model wiring to a single extra port.
%
%   AGEMS comes from DECODERSNAPSHOT, so it uses the same rollover-safe
%   modulo arithmetic and the same never-received sentinel as the control
%   path. A reader must treat INTMAX('UINT32') as "no frame yet" and must use
%   column 9 rather than all-zero bytes to detect absence -- an all-zero
%   payload is a legal frame a VCU can genuinely send.

snapshot = decoderSnapshot(bank, tickMs);

observation = zeros(4, 14);
for index = 1:4
    observation(index, 1:8) = double(bank.lastPayload(index, :));
    observation(index, 9) = double(bank.hasCommand(index));
    observation(index, 10) = double(bank.acceptedCount(index));
    observation(index, 11) = double(snapshot.ageMs(index));
    observation(index, 12) = double(bank.commandOutOfDomain(index));
    observation(index, 13) = double(bank.rejectedCount);
    observation(index, 14) = double(bank.lastRejectCode);
end
end
