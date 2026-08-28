function applied = apply_torquevect_steering(varargin)
%APPLY_TORQUEVECT_STEERING Idempotent R2022a edit: add the Fanatec / driver
%   steering-wheel CM-Dict path to TorqueVect.mdl.
%
%   Builds one self-contained subsystem
%       <root>/MFE_CAN Driver Steering
%   holding, for angle and for angular speed:
%
%     Read CM Dict (<source quantity>, rad or rad/s)
%        -> Gain  180/pi              (radians -> degrees, VISIBLE, no magic)
%        -> Gain  SignConvention      (+1 default; CarMaker & Bosch LWS are
%                                      both left-hand-positive, so no flip)
%        -> Saturation [-780, 780] deg / [-3600, 3600] deg/s
%        -> Write CM Dict (MFE_CAN.Driver.SteeringAngleDeg / SteeringSpeedDegPerSec)
%
%   DEGREES is the CarMaker -> Speedgoat contract unit (see
%   carmaker/config/MFE26_Inverter_CarMaker.dbc BO_ 1287 and
%   VC_HIL/docs/carmaker_fanatec_lws_steering.md). IO.c samples the two
%   MFE_CAN.Driver.* dictionary quantities in IO_Out() and sends the internal
%   0x507 CarMakerDriverSteering frame at 100 Hz.
%
%   Rerunnable: the subsystem is deleted and rebuilt on every call, so there
%   are never duplicate blocks or lines. Existing TorqueVect behaviour is
%   untouched -- this subsystem has no output ports and feeds nothing in the
%   model; it only pushes values into the CarMaker dictionary.
%
%   NAME/VALUE OPTIONS
%     'Model'          TorqueVect.mdl path or an already-loaded model name.
%                      Default: TorqueVect.mdl next to this file's parent
%                      (../vehicle_models/TorqueVect.mdl) or on the path.
%     'AngleQuantity'  CarMaker DD quantity for the steering-WHEEL angle,
%                      radians, left-hand-positive (CarMaker / ISO 8855).
%                      Default 'DM.Steer.Ang' -- the DrivMan desired
%                      steering-wheel angle, chosen for consistency with the
%                      0x500 pedal path, which IO.c sources from
%                      DrivMan.Gas / DrivMan.Brake.
%                      *** CONFIRM IN THE R2022a "Read CM Dict" QUANTITY
%                      BROWSER against this rig's actual Fanatec wiring ***
%                      (all confirmed present in
%                      <CarMakerInstall>/CM4SL/startup.dict):
%                        DM.Steer.Ang     DrivMan desired wheel angle
%                        VC.Steer.Ang     VehicleControl external interface
%                                         (use this if the Fanatec feeds
%                                         VehicleControl, not DrivMan)
%                        Driver.Steer.Ang IPGDriver output (already read by a
%                                         Read CM Dict block elsewhere in
%                                         TorqueVect.mdl)
%                        Steer.WhlAng /   post-steering-column ACTUAL wheel
%                        Vhcl.Steer.Ang   angle (what a column-mounted LWS
%                                         physically measures)
%                      It must be the steering-WHEEL angle, never a
%                      road-wheel angle (Car.SteerAngle.*) or vehicle yaw.
%     'SpeedQuantity'  CarMaker DD quantity for the steering-wheel angular
%                      speed, rad/s. Default 'DM.Steer.AngVel' (pair the
%                      matching *.AngVel to whatever AngleQuantity you
%                      confirm). Set to '' to skip the speed path entirely
%                      and let the Speedgoat derive steering speed from
%                      successive angle samples.
%     'SignConvention' +1 (default) or -1. Applied as a visible Gain.
%     'Save'           true (default) to save_system afterwards.
%
%   Returns a struct describing what was built.

p = inputParser;
p.addParameter('Model', '', @(x) ischar(x) || isstring(x));
p.addParameter('AngleQuantity', 'DM.Steer.Ang', @(x) ischar(x) || isstring(x));
p.addParameter('SpeedQuantity', 'DM.Steer.AngVel', @(x) ischar(x) || isstring(x));
p.addParameter('SignConvention', 1, @(x) isscalar(x) && (x == 1 || x == -1));
p.addParameter('Save', true, @(x) islogical(x) && isscalar(x));
p.parse(varargin{:});
opt = p.Results;

if ~strncmp(version('-release'), '2022', 4)
    warning('apply_torquevect_steering:release', ...
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
        error('apply_torquevect_steering:noCM4SL', ...
            ['CarMaker4SL library not found. Run cmenv (or add ' ...
             '<CarMakerInstall>/CM4SL/R2022a to the path) first.']);
    end
end

model = local_resolveModel(opt.Model);
loadedHere = ~bdIsLoaded(model);
if loadedHere
    load_system(model);
end

sub = [model '/MFE_CAN Driver Steering'];
if getSimulinkBlockHandle(sub) ~= -1
    delete_block(sub);
end
add_block('built-in/Subsystem', sub, 'Position', [40 40 340 260]);
% Remove the default In1/Out1 Simulink puts in a fresh Subsystem.
for b = find_system(sub, 'SearchDepth', 1, 'LookUnderMasks', 'all', ...
        'Regexp', 'on', 'BlockType', 'In|Out')'
    delete_block(b{1});
end

built = struct('subsystem', sub, 'angle', [], 'speed', []);
built.angle = local_chain(sub, 'Angle', opt.AngleQuantity, ...
    'MFE_CAN.Driver.SteeringAngleDeg', opt.SignConvention, 780, 40);
if ~isempty(char(opt.SpeedQuantity))
    built.speed = local_chain(sub, 'Speed', opt.SpeedQuantity, ...
        'MFE_CAN.Driver.SteeringSpeedDegPerSec', opt.SignConvention, 3600, 150);
end

add_block('built-in/Note', [model '/MFE_CAN Driver Steering Note'], ...
    'Position', [40 270], ...
    'Text', sprintf(['Fanatec / driver steering -> 0x507 CarMakerDriverSteering.\n' ...
    'rad -> deg (Gain 180/pi), sign %+d, saturate +/-780 deg, Write CM Dict.\n' ...
    'See VC_HIL/docs/carmaker_fanatec_lws_steering.md. Rebuilt by ' ...
    'apply_torquevect_steering.m.'], opt.SignConvention), ...
    'DropShadow', 'on');

if opt.Save
    save_system(model);
end
if loadedHere && opt.Save
    close_system(model, 0);
end
applied = built;
end

function chain = local_chain(sub, tag, sourceQuantity, targetQuantity, ...
        signConvention, saturationDeg, y)
%LOCAL_CHAIN Read CM Dict -> deg -> sign -> saturate -> Write CM Dict.
read = [sub '/Read ' tag];
add_block('CarMaker4SL/Read CM Dict', read, 'Position', [30 y 110 y+30]);
% xname must be set before xstime -- the S-function validates on every mask
% parameter change and rejects an empty variable name. xstime is a popup
% (Continuous|Inherited); Inherited resolves to the CM4SL base step (1 ms),
% which is what the physics CM-Dict blocks use.
set_param(read, 'xname', char(sourceQuantity));
set_param(read, 'xstime', 'Inherited');

deg = [sub '/' tag ' rad to deg'];
add_block('built-in/Gain', deg, 'Gain', '180/pi', ...
    'Position', [150 y 200 y+30]);

sgn = [sub '/' tag ' sign'];
add_block('built-in/Gain', sgn, 'Gain', num2str(signConvention), ...
    'Position', [230 y 280 y+30]);

sat = [sub '/' tag ' saturate deg'];
add_block('built-in/Saturate', sat, ...
    'UpperLimit', num2str(saturationDeg), ...
    'LowerLimit', num2str(-saturationDeg), ...
    'Position', [310 y 360 y+30]);

write = [sub '/Write ' tag];
add_block('CarMaker4SL/Write CM Dict', write, 'Position', [400 y 480 y+30]);
set_param(write, 'xname', char(targetQuantity));

add_line(sub, ['Read ' tag '/1'], [tag ' rad to deg/1'], 'autorouting', 'on');
add_line(sub, [tag ' rad to deg/1'], [tag ' sign/1'], 'autorouting', 'on');
add_line(sub, [tag ' sign/1'], [tag ' saturate deg/1'], 'autorouting', 'on');
add_line(sub, [tag ' saturate deg/1'], ['Write ' tag '/1'], 'autorouting', 'on');

chain = struct('sourceQuantity', char(sourceQuantity), ...
    'targetQuantity', char(targetQuantity), ...
    'saturationDeg', saturationDeg, 'signConvention', signConvention);
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
