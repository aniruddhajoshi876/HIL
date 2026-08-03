function payload = packLwsPayload(angleDeg, speedDegPerS, status)
%PACKLWSPAYLOAD Return the Bosch LWS standard frame payload.
p = lwsProtocol();
if double(angleDeg) < p.minimumAngleDeg || double(angleDeg) > p.maximumAngleDeg
    error('lws:AngleRange', 'Angle exceeds the Bosch LWS range.');
end
if double(speedDegPerS) < p.minimumSpeedDegPerS || ...
        double(speedDegPerS) > p.maximumSpeedDegPerS
    error('lws:SpeedRange', 'Speed exceeds the Bosch LWS range.');
end
angleRaw = round(double(angleDeg) / p.angleScaleDegPerCount);
speedRaw = round(double(speedDegPerS) / p.speedScaleDegPerSPerCount);
if angleRaw < p.minimumAngleDeg / p.angleScaleDegPerCount || ...
        angleRaw > p.maximumAngleDeg / p.angleScaleDegPerCount
    error('lws:AngleRange', 'Angle exceeds the Bosch LWS range.');
end
if speedRaw < p.minimumSpeedDegPerS / p.speedScaleDegPerSPerCount || ...
        speedRaw > p.maximumSpeedDegPerS / p.speedScaleDegPerSPerCount
    error('lws:SpeedRange', 'Speed exceeds the Bosch LWS range.');
end
angleCount = int16(angleRaw);
speedCount = uint8(speedRaw);
payload = zeros(1, 8, 'uint8');
raw = typecast(angleCount, 'uint8');
payload(1:2) = raw; % Bosch LWS angle is little-endian.
payload(3) = speedCount;
payload(4) = uint8(status);
end
