function observation = statusObservation(bank, tickMs)
%STATUSOBSERVATION Flatten genuine received inverter status into 9x11.
% Columns 1-8 payload, 9 hasFrame, 10 acceptedCount, 11 ageMs.
observation = zeros(9, 11);
for index = 1:9
    observation(index, 1:8) = double(bank.lastPayload(index, :));
    observation(index, 9) = double(bank.hasFrame(index));
    observation(index, 10) = double(bank.acceptedCount(index));
    if bank.hasFrame(index)
        observation(index, 11) = double(uint32(tickMs) - ...
            bank.lastValidTickMs(index));
    else
        observation(index, 11) = double(intmax('uint32'));
    end
end
end
