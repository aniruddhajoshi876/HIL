%Script to calkibrate the ADC with DACs of the PMSM HIL reference
%application. Possible only using CAN variant.

tg = slrealtime;
mdl = 'ADCCalibrationCAN';
open_system(mdl, 'loadonly');

% Build and Download
            
rtwbuild(mdl);
% Run and Plot Logged Data
load(tg, mdl);
tg.start;
pause(5);
tg.stop;

runObj = Simulink.sdi.Run.getLatest;
Ia_Signal = runObj.getSignalsByName('Ia_fbk');
Ib_Signal = runObj.getSignalsByName('Ib_fbk');
Ia_data = Ia_Signal.Values.Data;
Ib_data = Ib_Signal.Values.Data;

%Removing bad data
Ia_data=Ia_data(1000:end);
Ib_data=Ib_data(1000:end);

Ia_data(Ia_data==0) = [];
Ib_data(Ib_data==0) = [];

avgI_aOffset = sum(Ia_data) / length(Ia_data);
avgI_bOffset = sum(Ib_data) / length(Ib_data);

if abs(avgI_aOffset)<=30 && abs(avgI_bOffset)<=30
    dd = Simulink.data.dictionary.open('PMSM3P2LInverterDd.sldd');
    setValue(getEntry(dd.getSection('Design Data'), 'Ia_offset'),avgI_aOffset);
    setValue(getEntry(dd.getSection('Design Data'), 'Ib_offset'),avgI_bOffset);
    dd.saveChanges;
else 
    fprintf(' WARNING Calibration did not work : unrealistic offset \n')
end

%Close model
close_system(mdl, 0);