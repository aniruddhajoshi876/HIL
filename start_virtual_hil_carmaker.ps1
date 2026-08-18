<#
.SYNOPSIS
    Open the CM4SL MATLAB workflow and CarMaker GUI.

.DESCRIPTION
    This launcher deliberately stops before selecting or starting a CarMaker
    test run. It initializes the CM4SL MATLAB workspace, opens TorqueVect.mdl,
    and invokes the same
    CM_Simulink callback used by the model's Open CarMaker GUI block.

    CarMaker/HIL/CAN_Bringup is intentionally not loaded here.
#>
[CmdletBinding()]
param(
    [string]$ControlsRoot = 'C:\Users\MFE-HPC\Documents\GitHub\MFE25-Controls'
)

$ErrorActionPreference = 'Stop'

$repo = Split-Path -Parent $MyInvocation.MyCommand.Path
# Use the integrated project copy: it now contains the full IPG-MFE assets
# plus the branch's CAN configuration and CM4SL source changes.
$cmSource = Join-Path $repo 'carmaker\FS_race\src_cm4sl'
$vehicleDir = Join-Path $ControlsRoot '01 Vehicle Model'
$controlDir = Join-Path $ControlsRoot '02 Controls Model'
$matlabR2022a = 'C:\Program Files\MATLAB\R2022a\bin\matlab.exe'

foreach ($required in @($matlabR2022a, $cmSource,
        $vehicleDir, $controlDir)) {
    if (-not (Test-Path -LiteralPath $required)) {
        throw "Required path not found: $required"
    }
}

Write-Host 'Starting MATLAB R2022a CM4SL workflow ...'

# Keep this as one MATLAB command string. builtin('cd',...) is intentional:
# the controls script defines a variable named cd, which would otherwise
# shadow MATLAB's cd function after the initialization sections run.
$cmCode = @"
try
    controlsRoot='$ControlsRoot';
    vehicleDir=fullfile(controlsRoot,'01 Vehicle Model');
    controlDir=fullfile(controlsRoot,'02 Controls Model');
    addpath(genpath(vehicleDir));
    addpath(genpath(controlDir));
    builtin('cd',controlDir);
    controlText=fileread('Control_FL_Combined_Run.m');
    stopAt=strfind(controlText,'%% Other Controller and Optimization Parameters');
    eval(controlText(1:stopAt(1)-1));
    builtin('cd','$cmSource');
    cmenv;
    % TorqueVect evaluates PID block sample times in the base workspace.
    % Reassert this after cmenv, which may refresh the MATLAB workspace.
    Ts=1/200;
    freq_model=200;
    assignin('base','Ts',Ts);
    assignin('base','freq_model',freq_model);
    open_system('TorqueVect.mdl');
    cmblockmagic('gui_fix_display');
    CM_Simulink;
    disp('CM4SL/CarMaker startup complete. MATLAB is intentionally left open.');
catch ME
    fprintf(2,'CM4SL startup failed; MATLAB is being left open.\\n');
    disp(getReport(ME,'extended'));
end
"@

$matlab = Start-Process -FilePath $matlabR2022a -WorkingDirectory $cmSource `
    -ArgumentList @('-desktop', '-cefdisablegpu', '-softwareopengl', '-r', $cmCode) -PassThru

Write-Host "MATLAB CM4SL started (PID $($matlab.Id))."
Write-Host 'CarMaker GUI will open from TorqueVect.mdl.'
Write-Host 'No Speedgoat model was deployed or started.'
Write-Host 'Stopped before loading HIL/CAN_Bringup; select it manually when ready.'
