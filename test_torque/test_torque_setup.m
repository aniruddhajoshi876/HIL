function root = test_torque_setup()
%TEST_TORQUE_SETUP Configure the R2024b minimal throttle-to-torque workspace.
%
%   Mirrors inverter_hil/inverter_hil_setup.m's release check and
%   Speedgoat-library path resolution, but additionally puts
%   inverter_hil/+inverterhil on the path: TEST_TORQUE reuses
%   inverterhil.decodePedalDemandFrame/receivePedalDemandFrame/
%   pedalDemandSnapshot/initialPedalDemandBank (the CarMakerPedalDemand
%   0x500 CRC-8/SAE-J1850 + alive-counter + freshness decode, the same
%   package used by inverter_hil.slx) rather than re-implementing that
%   logic. This model does NOT touch inverter_hil.slx or build/depend on
%   the rest of the inverter_hil model -- only the pure, side-effect-free
%   +inverterhil pedal-demand functions.

if ~strcmp(version('-release'), '2024b')
    error('testTorque:WrongRelease', ...
        'test_torque requires MATLAB/Simulink R2024b; running %s.', ...
        version('-release'));
end

root = fileparts(mfilename('fullpath'));
workspaceRoot = fileparts(root);
inverterHilRoot = fullfile(workspaceRoot, 'inverter_hil');
if ~isfolder(inverterHilRoot)
    error('testTorque:MissingInverterHil', ...
        'inverter_hil (source of the reused pedal-demand decoder) not found near %s.', ...
        root);
end

speedgoatCandidates = { ...
    fullfile(root, '10.0.1.1', 'R2024B_SLX', 'sg_blocks'), ...
    fullfile(workspaceRoot, '10.0.1.1', 'R2024B_SLX', 'sg_blocks'), ...
    fullfile(workspaceRoot, 'examples', '10.0.1.1', ...
        'R2024B_SLX', 'sg_blocks')};
speedgoatBlocks = '';
for index = 1:numel(speedgoatCandidates)
    if isfolder(speedgoatCandidates{index})
        speedgoatBlocks = speedgoatCandidates{index};
        break
    end
end
if isempty(speedgoatBlocks) && isempty(which('speedgoat.tlc'))
    % Some installs register the Speedgoat target/block library globally
    % (e.g. C:\ProgramData\Speedgoat\speedgoatlib\...) rather than under a
    % project-relative 10.0.1.1 folder. Only error if speedgoat.tlc truly
    % cannot be found anywhere on the current path.
    error('testTorque:MissingSpeedgoatLibraries', ...
        'R2024b Speedgoat block libraries are missing near %s and not on the global path.', ...
        root);
end

addpath(root, inverterHilRoot);
if ~isempty(speedgoatBlocks)
    addpath(speedgoatBlocks);
end

cacheFolder = fullfile(root, '.simulink', 'cache');
codegenFolder = fullfile(root, '.simulink', 'codegen');
if ~isfolder(cacheFolder)
    mkdir(cacheFolder);
end
if ~isfolder(codegenFolder)
    mkdir(codegenFolder);
end
Simulink.fileGenControl('set', 'CacheFolder', cacheFolder, ...
    'CodeGenFolder', codegenFolder, 'createDir', true);
end
