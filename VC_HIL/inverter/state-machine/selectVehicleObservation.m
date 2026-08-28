function [observation, source] = selectVehicleObservation(kinematicObservation, carMakerSnapshot, truthEnabled)
%SELECTVEHICLEOBSERVATION Atomically select CarMaker truth when enabled.
if ~isequal(size(kinematicObservation), [1 9]) || ...
        any(~isfinite(double(kinematicObservation)))
    error('inverterhil:InvalidVehicleObservation', ...
        'kinematicObservation must be a finite 1x9 row.');
end
config = defaultVehicleStateConfig();
if nargin < 3, truthEnabled = config.carMakerTruthEnabled; end
useCarMaker = logical(truthEnabled) && carMakerSnapshot.fresh && ...
    carMakerSnapshot.complete && isequal(size(carMakerSnapshot.values), [1 12]) && ...
    all(isfinite(carMakerSnapshot.values(1:9)));
if useCarMaker
    observation = double(carMakerSnapshot.values(1:9));
    source = uint8(1);
else
    observation = double(kinematicObservation);
    source = uint8(0);
end
end
