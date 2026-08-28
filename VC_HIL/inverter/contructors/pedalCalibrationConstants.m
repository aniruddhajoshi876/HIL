function constants = pedalCalibrationConstants()
%PEDALCALIBRATIONCONSTANTS The pedal endpoints, and where each number is from.
%
%   CONSTANTS = PEDALCALIBRATIONCONSTANTS() returns a 1x4 struct array, one
%   per IO183 analog output, with fields:
%
%     channel      1..4, matching HIL_CAL_PEDALS_*_V<channel> and AO01..AO04
%     name         the logical pedal channel
%     releasedRaw  ADC count the VCU maps to 0 %
%     pressedRaw   ADC count the VCU maps to 100 %
%     releasedV    releasedRaw converted through the ADS7066 domain
%     pressedV     pressedRaw converted through the ADS7066 domain
%     direction    'falling' or 'rising', derived, not asserted
%     source       the exact device-under-test line each raw count came from
%
%   Split out from APPLY_PEDAL_CALIBRATION so tests can assert the shipped
%   dictionary matches these constants without opening a dictionary, and so
%   the numbers have one home. See APPLY_PEDAL_CALIBRATION's help for the
%   provenance limits -- in particular that these are derived from the device
%   under test and therefore cannot validate it.

% ADS7066 domain, as the device under test's own SIL model declares it in
% sil/registry/params.hpp (ADS_VREF_V, ADS_FULL_SCALE). Both caveats on
% these two numbers -- external VREF assumed 3.3 V, and 12-bit results
% left-justified so full scale is really 65520 -- are documented in
% APPLY_PEDAL_CALIBRATION.
vrefV = 3.3;
fullScaleCounts = 65535;

% Raw counts read directly from MFE26-VC/Core/Src/driverInputs.cpp. Released
% is whatever that file's conversion maps to 0 %, pressed to 100 %, so the
% rising/falling difference between the throttle and brake channels needs no
% special case here.
raw = { ...
    1, 'throttle 1', 30100, 23100, 'convertThrottle1ToPercent (throttle1Max/Min)'; ...
    2, 'throttle 2', 63600, 46500, 'convertThrottle2ToPercent (throttle2Max/Min)'; ...
    3, 'brake 1',     9025, 31800, 'convertBrakeToPercent (brakeMin/Max)'; ...
    4, 'brake 2',     9025, 31800, 'convertBrakeToPercent (brakeMin/Max)'};

constants = repmat(struct('channel', 0, 'name', '', 'releasedRaw', 0, ...
    'pressedRaw', 0, 'releasedV', 0, 'pressedV', 0, 'direction', '', ...
    'source', ''), 1, size(raw, 1));
for index = 1:size(raw, 1)
    releasedRaw = raw{index, 3};
    pressedRaw = raw{index, 4};
    constants(index).channel = raw{index, 1};
    constants(index).name = raw{index, 2};
    constants(index).releasedRaw = releasedRaw;
    constants(index).pressedRaw = pressedRaw;
    constants(index).releasedV = releasedRaw * vrefV / fullScaleCounts;
    constants(index).pressedV = pressedRaw * vrefV / fullScaleCounts;
    if pressedRaw < releasedRaw
        constants(index).direction = 'falling';
    else
        constants(index).direction = 'rising';
    end
    constants(index).source = raw{index, 5};
end

% Both brake channels share one conversion in the device under test
% (CONVERTBRAKETOPERCENT is called for brake1Raw and brake2Raw alike), so
% AO03 and AO04 are identical by derivation rather than by copy-paste. If the
% VCU ever splits them, these two rows diverge and nothing else changes.
end
