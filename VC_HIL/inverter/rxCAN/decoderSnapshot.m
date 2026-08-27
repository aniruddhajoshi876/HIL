function snapshot = decoderSnapshot(bank, tickMs)
%DECODERSNAPSHOT Compute rollover-safe independent command ages.

if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.');
end
p = protocol();
% AGEMS is built as a plain local variable, not a struct field, before
% SNAPSHOT is constructed in one pass: MATLAB Coder locks a struct's field
% set once any field is read or indexed into, so mutating SNAPSHOT.AGEMS
% inside the loop and then adding TORQUETIMEDOUT/ERRORTIMEDOUT afterward
% fails code generation even though it is valid, correct MATLAB.
ageMs = repmat(intmax('uint32'), 1, 4);
for index = 1:4
    if bank.hasCommand(index)
        delta = mod(double(tickMs) - double(bank.lastValidTickMs(index)), 2^32);
        ageMs(index) = uint32(delta);
    end
end

snapshot.commands = bank.commands;
snapshot.hasCommand = bank.hasCommand;
snapshot.ageMs = ageMs;
snapshot.torqueTimedOut = ageMs > p.timing.commandTorqueZeroMs;
snapshot.errorTimedOut = ageMs > p.timing.commandErrorMs;
end
