function applied = apply_torquevect_cm_truth(varargin)
%APPLY_TORQUEVECT_CM_TRUTH Idempotent R2022a edit: give the CarMaker-truth
%   dictionary quantities behind CAN 0x503-0x507 a writer in TorqueVect.mdl.
%
%   Without this the MFE_CAN.Physics.* / MFE_CAN.Steering.* quantities that
%   IO.c samples in IO_Out() have no producer at all: they stay at their
%   zero-initialised C values while IO.c happily transmits CRC-valid,
%   counter-advancing frames full of zeros -- indistinguishable downstream
%   from a stationary, straight-ahead vehicle. This script builds the
%   producers, and the validity quantities that let IO.c refuse to transmit
%   until they have run.
%
%   Builds one self-contained, port-free subsystem
%       <root>/MFE_CAN CarMaker Truth
%   containing only Read CM Dict -> Write CM Dict passthroughs plus two
%   Constant -> Write CM Dict validity writers:
%
%     PHYSICS (0x503-0x506), direct passthrough, no scaling, no delay:
%       Sensor.Inertial.<Sensor>.Acc_B.{x,y,z}   -> MFE_CAN.Physics.Acceleration.{x,y,z}
%       Sensor.Inertial.<Sensor>.Omega_B.{x,y,z} -> MFE_CAN.Physics.AngularRate.{x,y,z}
%       Sensor.Inertial.<Sensor>.Vel_B.{x,y,z}   -> MFE_CAN.Physics.Velocity.{x,y,z}
%       Car.{Roll,Pitch,Yaw}                     -> MFE_CAN.Physics.Euler.{x,y,z}   (optional)
%       Constant 1                               -> MFE_CAN.Physics.Valid
%
%     STEERING (0x507), direct passthrough, RADIANS end to end:
%       Steer.WhlAng                             -> MFE_CAN.Steering.WheelAngleRad
%       Constant 1                               -> MFE_CAN.Steering.Valid
%
%   DELIBERATELY NOT DONE HERE
%     * No unit conversion. Steer.WhlAng is radians in the CarMaker data
%       dictionary and radians is the 0x507 wire unit; the Speedgoat converts
%       to degrees just before Bosch LWS encoding. Converting here would only
%       give the Speedgoat something to undo.
%     * No MTi scaling and no IMU mounting transform. Those belong downstream
%       of the Speedgoat observation selector (VC_HIL/imu/mountingTransform.m),
%       so that CarMaker truth and the internal kinematic model feed the same
%       transform. Applying either here would bake a sensor into the plant.
%     * No Rate Transition, Memory or Unit Delay. The blocks inherit the CM4SL
%       base step and pass the value through in the same step it is read, so
%       IO_Out() samples the current cycle rather than the previous one.
%     * No steering-wheel angular speed. The Bosch LWS_SPEED field is derived
%       on the Speedgoat from successive 10 ms samples of this angle; a
%       transported rate would be a second, redundant source of it.
%     * Nothing is connected to the existing torque-vectoring signal path.
%       The subsystem has no ports and feeds nothing; it only pushes values
%       into the CarMaker dictionary.
%
%   VALIDITY
%     The two Constant 1 -> Write CM Dict pairs live in the SAME subsystem as
%     the passthroughs, so they are raised if and only if that subsystem has
%     executed. USER_TESTRUN_START_ATBEGIN clears both at the start of every
%     TestRun, so validity is a per-run statement, not a once-per-process one.
%
%   RERUNNABLE
%     The subsystem is deleted and rebuilt on every call, so there are never
%     duplicate blocks or lines. Existing TorqueVect behaviour is untouched.
%
%   NAME/VALUE OPTIONS
%     'Model'           TorqueVect.mdl path or an already-loaded model name.
%                       Default: ../vehicle_models/TorqueVect.mdl next to this
%                       file, i.e. the HIL copy. Never point this at a copy in
%                       another CarMaker project.
%     'InertialSensor'  Name of the CarMaker inertial sensor whose quantities
%                       carry the vehicle physics. Default 'Param_B00' -- the
%                       Sensor.Param.1.Name / Sensor.1.name of the MFE24_V3
%                       and MFE26_V1 vehicle data sets in
%                       carmaker/FS_race/Data/Vehicle/Examples_FS/.
%                       *** These quantities are created at runtime by the
%                       configured sensor instance and are NOT in
%                       <CarMakerInstall>/CM4SL/startup.dict, so the R2022a
%                       "Read CM Dict" browser only lists them once a TestRun
%                       using such a vehicle is loaded. CONFIRM THERE. ***
%     'SteeringQuantity' CarMaker DD quantity for the steering-WHEEL angle,
%                       radians. Default 'Steer.WhlAng' -- the applied
%                       steering-wheel position after the CarMaker cockpit
%                       scales the active Fanatec Device.0 axis 0, confirmed
%                       present with unit "rad" in
%                       <CarMakerInstall>/CM4SL/startup.dict. It must be the
%                       steering-WHEEL angle, never a road-wheel angle
%                       (Car.SteerAngleFL/FR) and never vehicle yaw.
%     'IncludeEuler'    true (default) to write MFE_CAN.Physics.Euler.* from
%                       Car.{Roll,Pitch,Yaw}. 0x506 is optional to the
%                       Speedgoat's coherent-group test either way.
%     'Save'            true (default) to save_system afterwards.
%
%   Returns a struct describing what was built.
%
%   See also carmaker/docs/carmaker_readcmdict_checklist.md,
%   VC_HIL/docs/carmaker_fanatec_lws_steering.md,
%   VC_HIL/docs/carmaker_imu_truth_source_plan.md.

p = inputParser;
p.addParameter('Model', '', @(x) ischar(x) || isstring(x));
p.addParameter('InertialSensor', 'Param_B00', @(x) ischar(x) || isstring(x));
p.addParameter('SteeringQuantity', 'Steer.WhlAng', @(x) ischar(x) || isstring(x));
p.addParameter('IncludeEuler', true, @(x) islogical(x) && isscalar(x));
p.addParameter('Save', true, @(x) islogical(x) && isscalar(x));
p.parse(varargin{:});
opt = p.Results;

if ~strncmp(version('-release'), '2022', 4)
    warning('apply_torquevect_cm_truth:release', ...
        ['TorqueVect.mdl is an R2022a model; running %s. Open it in ' ...
         'R2022a for a clean save.'], version('-release'));
end

% Make sure the CarMaker-for-Simulink library is available (Read/Write CM
% Dict live in CarMaker4SL). cmenv.m is the supported way; a bare addpath of
% the version-specific CM4SL folder is enough just to resolve the library.
if isempty(find_system('type', 'block_diagram', 'Name', 'CarMaker4SL'))
    try
        load_system('CarMaker4SL');
    catch
        error('apply_torquevect_cm_truth:noCM4SL', ...
            ['CarMaker4SL library not found. Run cmenv (or add ' ...
             '<CarMakerInstall>/CM4SL/R2022a to the path) first.']);
    end
end

% BDISLOADED and every SET_PARAM below take a block-diagram NAME, not a
% path, so the path is only used to load the right file and the name is what
% the rest of this function addresses.
modelPath = local_resolveModel(opt.Model);
[~, model] = fileparts(modelPath);
loadedHere = ~bdIsLoaded(model);
if loadedHere
    load_system(modelPath);
end

sub = [model '/MFE_CAN CarMaker Truth'];
% The superseded steering-only subsystem, if a previous revision of this
% script left one behind. Removing it is what keeps a repository that has
% been through both revisions from carrying two competing steering writers.
legacy = [model '/MFE_CAN Driver Steering'];
for stale = {legacy, [model '/MFE_CAN Driver Steering Note'], sub}
    if getSimulinkBlockHandle(stale{1}) ~= -1
        delete_block(stale{1});
    end
end
add_block('built-in/Subsystem', sub, 'Position', [40 40 620 640]);
% Remove the default In1/Out1 Simulink puts in a fresh Subsystem.
for b = find_system(sub, 'SearchDepth', 1, 'LookUnderMasks', 'all', ...
        'Regexp', 'on', 'BlockType', 'In|Out')'
    delete_block(b{1});
end

sensor = char(opt.InertialSensor);
axes = {'x', 'y', 'z'};
built = struct('subsystem', sub, 'physics', struct([]), ...
    'steering', [], 'validity', struct([]), 'includeEuler', opt.IncludeEuler);

groups = { ...
    'Acc',   sprintf('Sensor.Inertial.%s.Acc_B',   sensor), 'MFE_CAN.Physics.Acceleration'; ...
    'Omega', sprintf('Sensor.Inertial.%s.Omega_B', sensor), 'MFE_CAN.Physics.AngularRate'; ...
    'Vel',   sprintf('Sensor.Inertial.%s.Vel_B',   sensor), 'MFE_CAN.Physics.Velocity'};
if opt.IncludeEuler
    groups(end+1, :) = {'Euler', '', 'MFE_CAN.Physics.Euler'};
end
eulerSources = {'Car.Roll', 'Car.Pitch', 'Car.Yaw'};

row = 0;
physics = struct('tag', {}, 'sourceQuantity', {}, 'targetQuantity', {});
for g = 1:size(groups, 1)
    for a = 1:3
        if strcmp(groups{g, 1}, 'Euler')
            source = eulerSources{a};
        else
            source = sprintf('%s.%s', groups{g, 2}, axes{a});
        end
        target = sprintf('%s.%s', groups{g, 3}, axes{a});
        tag = sprintf('%s %s', groups{g, 1}, upper(axes{a}));
        physics(end+1) = local_passthrough(sub, tag, source, target, ...
            40 + 45 * row); %#ok<AGROW>
        row = row + 1;
    end
end
built.physics = physics;

built.steering = local_passthrough(sub, 'Steering WheelAngle', ...
    char(opt.SteeringQuantity), 'MFE_CAN.Steering.WheelAngleRad', ...
    40 + 45 * row);
row = row + 1;

validity = struct('tag', {}, 'targetQuantity', {});
validity(1) = local_validity(sub, 'Physics Valid', 'MFE_CAN.Physics.Valid', ...
    40 + 45 * row);
validity(2) = local_validity(sub, 'Steering Valid', 'MFE_CAN.Steering.Valid', ...
    40 + 45 * (row + 1));
built.validity = validity;

add_block('built-in/Note', [model '/MFE_CAN CarMaker Truth Note'], ...
    'Position', [40 660], ...
    'Text', sprintf(['CarMaker truth -> CAN 0x503-0x507 (CarMaker bus, channel 1).\n' ...
    'Straight Read CM Dict -> Write CM Dict passthroughs: no scaling, no\n' ...
    'unit conversion, no delay, no IMU mounting transform -- all of that is\n' ...
    'the Speedgoat''s job. Steering is RADIANS (%s).\n' ...
    'The two Valid constants let IO.c refuse to transmit zero-initialised\n' ...
    'frames. Rebuilt by apply_torquevect_cm_truth.m; do not hand-edit.'], ...
    char(opt.SteeringQuantity)), ...
    'DropShadow', 'on');

if opt.Save
    save_system(model);
end
if loadedHere && opt.Save
    close_system(model, 0);
end
applied = built;
end


function chain = local_passthrough(sub, tag, sourceQuantity, targetQuantity, y)
%LOCAL_PASSTHROUGH Read CM Dict -> Write CM Dict, nothing in between.
read = [sub '/Read ' tag];
add_block('CarMaker4SL/Read CM Dict', read, 'Position', [30 y 150 y+30]);
% xname must be set before xstime -- the S-function validates on every mask
% parameter change and rejects an empty variable name. xstime is a popup
% (Continuous|Inherited); Inherited resolves to the CM4SL base step, which is
% the rate IO_Out() samples these quantities at.
set_param(read, 'xname', char(sourceQuantity));
set_param(read, 'xstime', 'Inherited');

write = [sub '/Write ' tag];
add_block('CarMaker4SL/Write CM Dict', write, 'Position', [330 y 450 y+30]);
set_param(write, 'xname', char(targetQuantity));

add_line(sub, ['Read ' tag '/1'], ['Write ' tag '/1'], 'autorouting', 'on');

chain = struct('tag', tag, 'sourceQuantity', char(sourceQuantity), ...
    'targetQuantity', char(targetQuantity));
end


function entry = local_validity(sub, tag, targetQuantity, y)
%LOCAL_VALIDITY Constant 1 -> Write CM Dict. Raised only by execution.
source = [sub '/' tag ' Constant'];
add_block('built-in/Constant', source, 'Value', '1', ...
    'Position', [30 y 150 y+30]);

write = [sub '/Write ' tag];
add_block('CarMaker4SL/Write CM Dict', write, 'Position', [330 y 450 y+30]);
set_param(write, 'xname', char(targetQuantity));

add_line(sub, [tag ' Constant/1'], ['Write ' tag '/1'], 'autorouting', 'on');

entry = struct('tag', tag, 'targetQuantity', char(targetQuantity));
end


function model = local_resolveModel(requested)
requested = char(requested);
if ~isempty(requested)
    [~, name] = fileparts(requested);
    if bdIsLoaded(name)
        model = name; return;
    end
    model = requested; return;
end
here = fileparts(mfilename('fullpath'));
candidates = { ...
    fullfile(here, 'vehicle_models', 'TorqueVect.mdl'), ...
    fullfile(here, 'TorqueVect.mdl')};
for k = 1:numel(candidates)
    if isfile(candidates{k})
        model = candidates{k}; return;
    end
end
if bdIsLoaded('TorqueVect')
    model = 'TorqueVect'; return;
end
model = 'TorqueVect';   % last resort: rely on the MATLAB path
end
