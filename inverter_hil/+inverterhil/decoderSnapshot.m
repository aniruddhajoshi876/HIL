function snapshot = decoderSnapshot(bank, tickMs)
%DECODERSNAPSHOT Compute rollover-safe independent command ages.

if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.');
end
p = inverterhil.protocol();
snapshot.commands = bank.commands;
snapshot.hasCommand = bank.hasCommand;
snapshot.ageMs = repmat(intmax('uint32'), 1, 4);
for index = 1:4
    if bank.hasCommand(index)
        delta = mod(double(tickMs) - double(bank.lastValidTickMs(index)), 2^32);
        snapshot.ageMs(index) = uint32(delta);
    end
end
snapshot.torqueTimedOut = snapshot.ageMs > p.timing.commandTorqueZeroMs;
snapshot.errorTimedOut = snapshot.ageMs > p.timing.commandErrorMs;
end
