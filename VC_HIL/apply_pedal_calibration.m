function applied = apply_pedal_calibration(dictionaryPath)
%APPLY_PEDAL_CALIBRATION Write the four pedal analog-output endpoints.
%
%   APPLIED = APPLY_PEDAL_CALIBRATION() writes HIL_CAL_PEDALS_RELEASED_V1..4
%   and HIL_CAL_PEDALS_PRESSED_V1..4 into INVERTER_HIL.SLDD and returns the
%   applied table. APPLY_PEDAL_CALIBRATION(PATH) targets another dictionary.
%
%   WHY THIS IS A SCRIPT AND NOT JUST A VALUE IN THE DICTIONARY
%   -----------------------------------------------------------
%   BUILD_INVERTER_HIL_MODEL creates the dictionary from scratch and seeds
%   every endpoint at NaN (deliberately: an uncalibrated channel must be
%   detectable, not silently plausible). That means ANY rebuild silently
%   erases the calibration, and an erased endpoint is not loud -- it makes
%   PEDALVOLTAGECALIBRATION emit 0 V, so the GUI sliders keep moving while
%   the VCU pin never changes. That regression reached the deployed
%   application once already. Keeping the numbers in version-controlled
%   source, re-applied by BUILD_INVERTER_HIL_MODEL at the end of every
%   build, is what stops it recurring.
%
%   PROVENANCE AND ITS LIMITS -- READ BEFORE TRUSTING THESE NUMBERS
%   ---------------------------------------------------------------
%   These endpoints are DERIVED FROM THE DEVICE UNDER TEST, not measured.
%   They come from MFE26-VC/Core/Src/driverInputs.cpp's own threshold
%   constants, converted through the ADS7066 domain that repository's SIL
%   model declares (sil/registry/params.hpp: ADS_VREF_V = 3.3,
%   ADS_FULL_SCALE = 65535).
%
%   The consequence is a real and permanent limitation of this calibration:
%   because HIL 0-100 %% is defined BY the VCU's constants, a sweep can never
%   discover that those constants are themselves wrong. It verifies that the
%   VCU interprets a known voltage as the percentage it intends to; it does
%   NOT verify that the intended percentage matches the physical pedal.
%   Closing that gap needs endpoints measured at the connected VCU pin with
%   the real pedal at its mechanical stops (INVERTER_HIL_PLAN.MD S3.1), and
%   until that happens these values must be treated as provisional.
%
%   Three further uncertainties, none of them resolved by reading firmware:
%
%   1. VREF is ASSUMED. ADS7066.CPP:31 clears REF_EN, i.e. the internal
%      2.5 V reference is OFF and the external REF pin supplies the scale.
%      Its actual value is a board fact and appears nowhere in the firmware;
%      3.3 V comes from the SIL model's assertion. If REF is really 2.5 V
%      every voltage below is high by a factor of 1.32.
%   2. The ADS7066 is a 12-bit converter whose result is left-justified in
%      the 16-bit word ADS7066.CPP:126 assembles, so counts move in steps of
%      16 and full scale is 65520, not the 65535 the SIL model uses. The
%      resulting error is 1 part in 65535 (about 0.02 mV here), far below
%      anything measurable, so 65535 is retained to keep HIL and SIL
%      identical rather than introduce a difference that buys no accuracy.
%   3. THROTTLE1MIN is 23100 while the same file's comment puts full press
%      near 20900 (also the low bound of ISTHROTTLE1INRANGE). 23100 is used
%      because it is the constant the conversion actually applies; pressed_v1
%      is therefore the 100 %% POINT OF THE VCU'S MAP, not the pedal's
%      mechanical stop.
%
%   Direction is not assumed either -- it falls out of the endpoints.
%   PEDALVOLTAGECALIBRATION interpolates released->pressed, so a falling
%   channel is expressed simply by PRESSED_V < RELEASED_V.

if nargin < 1 || isempty(dictionaryPath)
    dictionaryPath = fullfile(fileparts(mfilename('fullpath')), ...
        'inverter_hil.sldd');
end
if ~isfile(dictionaryPath)
    error('inverterhil:MissingDictionary', ...
        'Data dictionary not found: %s', dictionaryPath);
end

applied = inverterhil.pedalCalibrationConstants();

dictionary = Simulink.data.dictionary.open(dictionaryPath);
cleanup = onCleanup(@() close(dictionary)); %#ok<NASGU>
section = getSection(dictionary, 'Design Data');

for index = 1:numel(applied)
    setEndpoint(section, ...
        sprintf('hil_cal_pedals_released_v%d', applied(index).channel), ...
        applied(index).releasedV);
    setEndpoint(section, ...
        sprintf('hil_cal_pedals_pressed_v%d', applied(index).channel), ...
        applied(index).pressedV);
end

fprintf('Applied pedal calibration to %s:\n', dictionaryPath);
for index = 1:numel(applied)
    fprintf('  AO%02d %-12s released %.6f V -> pressed %.6f V (%s)\n', ...
        applied(index).channel, applied(index).name, ...
        applied(index).releasedV, applied(index).pressedV, ...
        applied(index).direction);
end
end

function setEndpoint(section, name, volts)
%SETENDPOINT Overwrite one endpoint, preserving the entry's other metadata.
%   GETVALUE/SETVALUE round-trips the whole SIMULINK.PARAMETER so the Min,
%   Max and DataType the build assigned survive; assigning a bare double
%   would replace the parameter object with a plain value and drop the 0-5 V
%   range check with it.
entry = getEntry(section, name);
parameter = getValue(entry);
parameter.Value = volts;
setValue(entry, parameter);
end
