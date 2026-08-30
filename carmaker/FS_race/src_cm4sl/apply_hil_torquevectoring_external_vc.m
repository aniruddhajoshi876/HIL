function applied = apply_hil_torquevectoring_external_vc(varargin)
%APPLY_HIL_TORQUEVECTORING_EXTERNAL_VC  Idempotent R2022a edit that turns
%   HIL_torquevectoring.mdl into the external-VC bridge model.
%
%   HIL_torquevectoring.mdl starts life as a copy of TorqueVect.mdl (same
%   CarMaker plant, sensor extraction, CAN transmission and actuator
%   plumbing). This script removes the local torque-vectoring controllers and
%   wires in a bridge that applies the VC's own per-inverter torque command
%   instead:
%
%       CarMaker sensors -> CM4SL truth CAN (0x503-0x507, unchanged)
%                        -> VC runs code-generated controls, sends motor torque
%                        -> Speedgoat republishes 0x501/0x502
%                        -> IO.c decodes -> MFE_CAN.Inverter*TorqueSetpointNm
%                        -> [THIS BRIDGE] validate / saturate / zero-fallback
%                        -> MotorOut0..3.Load -> CarMaker motors
%
%   REMOVED (from HIL_torquevectoring.mdl only; TorqueVect.mdl keeps all of
%   it), inside .../IPG Vehicle/PowerTrain/PTControl Example :
%       * PTControl_TV_MFE25           gain-scheduled TV + traction-control
%                                      PIDs; its Full Control Loop is what
%                                      needs kp/ki/kd/N/velocity_lookup
%       * PTControl_ALL_CTRL_VC_MFE24  the older MFE24 full controller
%       * Mux1 / Switch / Constant     the controller selector
%   KEPT
%       * PTControl_In / PTControl_Out CM4SL powertrain bus adapters
%       * CreateBus PTC * / Demux / Mux  actuator bus plumbing
%       * MFE_CAN CarMaker Truth       the 0x503-0x507 truth passthroughs
%
%   ADDED
%     .../PTControl Example/External VC Torque Bridge : a subsystem whose five
%       outputs (PTC MiscOut, MotorOut0..3) feed the existing Mux -> Demux ->
%       CreateBus chain. Inside:
%         - Read CM Dict of MFE_CAN.Inverter{1..4}TorqueSetpointNm,
%           MFE_CAN.Inverter{1..4}Ready, MFE_CAN.InverterTorque.RxTimeS
%         - a Clock for the model time base
%         - Constants T_i_max (base workspace) and the freshness window
%         - one MATLAB Function block calling hilTvExternalVcBridge()
%         - Demux + per-motor Mux([Load, -99999, -99999]) into MotorOut0..3
%         - Constants [4 0 4 1] muxed into PTC MiscOut
%         - Define + Write CM Dict diagnostics: MFE_CAN.Bridge.*
%
%   The bridge compiles with NO kp/ki/kd/N/velocity_lookup and no Kp/Ki/Kd.
%   It still needs T_i_max (per-motor torque limit, 21 N*m) in the base
%   workspace; that name is not on the removed list and open_carmaker_gui.m
%   keeps providing it.
%
%   RERUNNABLE: the bridge subsystem and its note are deleted and rebuilt on
%   every call; the structural deletes are guarded so a second run is a no-op.
%
%   NAME/VALUE OPTIONS
%     'Model'     HIL_torquevectoring.mdl path or a loaded model name.
%                 Default: ../vehicle_models/HIL_torquevectoring.mdl next to
%                 this file. NEVER point this at TorqueVect.mdl.
%     'TimeoutS'  command freshness window baked into the model as a Constant.
%                 Default 0.050 (10x the 5 ms 0x501 cycle).
%     'Save'      true (default) to save_system afterwards.
%
%   See also apply_torquevect_cm_truth, hilTvExternalVcBridge,
%   carmaker/docs/cm4sl_integration.md,
%   VC_HIL/docs/carmaker_real_vcu_can_interface_plan.md.

p = inputParser;
p.addParameter('Model', '', @(x) ischar(x) || isstring(x));
p.addParameter('TimeoutS', 0.050, @(x) isnumeric(x) && isscalar(x) && x > 0);
p.addParameter('Save', true, @(x) islogical(x) && isscalar(x));
p.parse(varargin{:});
opt = p.Results;

if ~strncmp(version('-release'), '2022', 4)
    warning('apply_hil_torquevectoring_external_vc:release', ...
        'HIL_torquevectoring.mdl is an R2022a model; running %s.', version('-release'));
end

if isempty(find_system('type', 'block_diagram', 'Name', 'CarMaker4SL'))
    try
        load_system('CarMaker4SL');
    catch
        error('apply_hil_torquevectoring_external_vc:noCM4SL', ...
            'CarMaker4SL library not found. Run cmenv first.');
    end
end

modelPath = local_resolveModel(opt.Model);
[~, model] = fileparts(modelPath);
if strcmpi(model, 'TorqueVect')
    error('apply_hil_torquevectoring_external_vc:wrongModel', ...
        ['Refusing to edit TorqueVect.mdl -- that is the internal-controls ' ...
         'reference model. Point ''Model'' at HIL_torquevectoring.mdl.']);
end
loadedHere = ~bdIsLoaded(model);
if loadedHere
    load_system(modelPath);
end

PE = [model '/CarMaker/IPG Vehicle/PowerTrain/PTControl Example'];
bridge = [PE '/External VC Torque Bridge'];
note   = [PE '/External VC Torque Bridge Note'];

% ------------------------------------------------------------------ cleanup
for stale = {bridge, note, [PE '/PTControl_In Sink'], [PE '/VhclCtrl_PT Sink']}
    if getSimulinkBlockHandle(stale{1}) ~= -1
        delete_block(stale{1});
    end
end

% -------------------------------------------------- structural controller removal
for b = {'Switch', 'Constant', 'Mux1', 'PTControl_TV_MFE25', ...
         'PTControl_ALL_CTRL_VC_MFE24'}
    h = getSimulinkBlockHandle([PE '/' b{1}]);
    if h ~= -1
        delete_block(h);
    end
end
% The lone Terminator that used to catch PTControl_TV_MFE25 port 6 (a|Slip).
for t = find_system(PE, 'SearchDepth', 1, 'LookUnderMasks', 'all', ...
        'BlockType', 'Terminator')'
    pc = get_param(t{1}, 'PortConnectivity');
    if isempty(pc) || all(~ishandle(pc(1).SrcBlock))
        delete_block(t{1});
    end
end

% delete_block leaves dangling line stubs on the far end of every line the
% deleted controllers had connected. Prune before touching those ports.
local_pruneDanglingLines(PE);

% Mux (5 wide) now feeds the Demux directly (was Mux -> Switch -> Demux).
local_clearInput([PE '/Demux'], 1);
local_wire([PE '/Mux'], 1, [PE '/Demux'], 1);

% Terminate the now-dangling adapter / inport outputs.
local_terminate([PE '/PTControl_In'], 1, [PE '/PTControl_In Sink'], [95 305]);
local_terminate([PE '/VhclCtrl.PT'],  1, [PE '/VhclCtrl_PT Sink'],  [95 150]);

% --------------------------------------------------------------- build the bridge
add_block('built-in/Subsystem', bridge, 'Position', [70 90 250 360]);
for d = find_system(bridge, 'SearchDepth', 1, 'LookUnderMasks', 'all', ...
        'Regexp', 'on', 'BlockType', 'In|Out')'
    delete_block(d{1});
end

built = local_buildBridge(bridge, opt.TimeoutS);

% Wire the five bridge outputs into the existing Mux (1..5):
%   1 PTC MiscOut, 2 MotorOut0, 3 MotorOut1, 4 MotorOut2, 5 MotorOut3
for k = 1:5
    local_wire(bridge, k, [PE '/Mux'], k);
end

add_block('built-in/Note', note, 'Position', [70 380], 'DropShadow', 'on', ...
    'Text', sprintf([ ...
    'External-VC torque bridge. The VC runs the code-generated controls and\n' ...
    'sends four motor-torque commands; the Speedgoat republishes them as\n' ...
    '0x501, IO.c decodes them into MFE_CAN.Inverter*TorqueSetpointNm. This\n' ...
    'subsystem validates freshness (RxTimeS, %g ms window) and the four\n' ...
    'InverterReady bits, saturates to +/-T_i_max, and applies\n' ...
    'appliedNm/T_i_max to MotorOut0..3.Load -- or zero on any fault.\n' ...
    'Logic lives in hilTvExternalVcBridge.m. NO local torque vectoring, no\n' ...
    'PID, no gain scheduling. Rebuilt by\n' ...
    'apply_hil_torquevectoring_external_vc.m; do not hand-edit.'], ...
    opt.TimeoutS * 1000));

if opt.Save
    save_system(model);
end
if loadedHere && opt.Save
    close_system(model, 0);
end
applied = built;
end


% =========================================================================
function built = local_buildBridge(bridge, timeoutS)
%LOCAL_BUILDBRIDGE  Populate the External VC Torque Bridge subsystem.

spNames  = arrayfun(@(i) sprintf('MFE_CAN.Inverter%dTorqueSetpointNm', i), 1:4, 'uni', 0);
rdyNames = arrayfun(@(i) sprintf('MFE_CAN.Inverter%dReady', i),            1:4, 'uni', 0);
for i = 1:4
    local_read(bridge, sprintf('Setpoint%d', i), spNames{i},  30 + 35 * (i - 1));
    local_read(bridge, sprintf('Ready%d', i),    rdyNames{i}, 200 + 35 * (i - 1));
end
local_read(bridge, 'RxTimeS', 'MFE_CAN.InverterTorque.RxTimeS', 360);

add_block('built-in/Clock', [bridge '/SimTimeS'], 'Position', [30 400 60 430]);
add_block('built-in/Constant', [bridge '/T_i_max'], 'Value', 'T_i_max', ...
    'Position', [30 450 150 480]);
add_block('built-in/Constant', [bridge '/TimeoutS'], ...
    'Value', num2str(timeoutS, '%.6g'), 'Position', [30 490 150 520]);

add_block('built-in/Mux', [bridge '/Setpoint Mux'], 'Inputs', '4', ...
    'Position', [230 30 240 150]);
add_block('built-in/Mux', [bridge '/Ready Mux'], 'Inputs', '4', ...
    'Position', [230 200 240 320]);
for i = 1:4
    local_wire([bridge '/Read Setpoint' num2str(i)], 1, [bridge '/Setpoint Mux'], i);
    local_wire([bridge '/Read Ready' num2str(i)],    1, [bridge '/Ready Mux'],    i);
end

% --- the one decision block ---
fcn = [bridge '/ExternalVcBridge'];
add_block('simulink/User-Defined Functions/MATLAB Function', fcn, ...
    'Position', [330 40 470 260]);
script = strjoin({ ...
    ['function [motorLoad, appliedNm, limitedNm, commandAgeS, fresh, ' ...
     'readyAll, enable, timedOut] = ExternalVcBridge(setpointNm, ready, ' ...
     'rxTimeS, simTimeS, tIMaxNm, timeoutS)'], ...
    '%#codegen', ...
    '% Thin wrapper: the logic lives in hilTvExternalVcBridge.m (on the path', ...
    '% via cmenv) so it stays unit-testable outside Simulink.', ...
    ['[motorLoad, appliedNm, limitedNm, commandAgeS, fresh, readyAll, ' ...
     'enable, timedOut] = hilTvExternalVcBridge(setpointNm, ready, rxTimeS, ' ...
     'simTimeS, tIMaxNm, timeoutS);'], ...
    'end'}, newline);
local_setFcnScript(fcn, script);

local_wire([bridge '/Setpoint Mux'], 1, fcn, 1);
local_wire([bridge '/Ready Mux'],    1, fcn, 2);
local_wire([bridge '/Read RxTimeS'], 1, fcn, 3);
local_wire([bridge '/SimTimeS'],     1, fcn, 4);
local_wire([bridge '/T_i_max'],      1, fcn, 5);
local_wire([bridge '/TimeoutS'],     1, fcn, 6);

% --- motor load -> per-motor bus -> outports 2..5 (MotorOut0..3) ---
add_block('built-in/Demux', [bridge '/Load Demux'], 'Outputs', '4', ...
    'Position', [540 60 550 160]);
local_wire(fcn, 1, [bridge '/Load Demux'], 1);
add_block('built-in/Constant', [bridge '/NotSet'], 'Value', '-99999', ...
    'Position', [540 200 620 230]);
for i = 1:4
    mux = [bridge '/' sprintf('MotorOut%d Mux', i - 1)];
    add_block('built-in/Mux', mux, 'Inputs', '3', ...
        'Position', [660 40 + 60 * (i - 1) 670 100 + 60 * (i - 1)]);
    local_wire([bridge '/Load Demux'], i, mux, 1);
    local_wire([bridge '/NotSet'], 1, mux, 2);
    local_wire([bridge '/NotSet'], 1, mux, 3);
    op = [bridge '/' sprintf('MotorOut%d', i - 1)];
    add_block('built-in/Outport', op, 'Port', num2str(i + 1), ...
        'Position', [740 60 + 60 * (i - 1) 770 74 + 60 * (i - 1)]);
    local_wire(mux, 1, op, 1);
end

% --- PTC MiscOut = [OperationState 4, OperationError 0, StrategyMode 4, Ignition 1] ---
miscVals = {'4', '0', '4', '1'};
add_block('built-in/Mux', [bridge '/Misc Mux'], 'Inputs', '4', ...
    'Position', [660 300 670 400]);
for i = 1:4
    c = [bridge '/' sprintf('Misc%d', i)];
    add_block('built-in/Constant', c, 'Value', miscVals{i}, ...
        'Position', [560 300 + 25 * (i - 1) 640 318 + 25 * (i - 1)]);
    local_wire(c, 1, [bridge '/Misc Mux'], i);
end
add_block('built-in/Outport', [bridge '/PTC MiscOut'], 'Port', '1', ...
    'Position', [740 340 770 354]);
local_wire([bridge '/Misc Mux'], 1, [bridge '/PTC MiscOut'], 1);

% --- diagnostics: Define + Write CM Dict, all MFE_CAN.Bridge.* ---
scalarDiag = { ...
    'MFE_CAN.Bridge.CommandAgeS', 's', 4; ...
    'MFE_CAN.Bridge.Fresh',       '-', 5; ...
    'MFE_CAN.Bridge.ReadyAll',    '-', 6; ...
    'MFE_CAN.Bridge.Enable',      '-', 7; ...
    'MFE_CAN.Bridge.TimedOut',    '-', 8};
y = 460;
for k = 1:size(scalarDiag, 1)
    w = local_diag(bridge, scalarDiag{k, 1}, scalarDiag{k, 2}, y);
    local_wire(fcn, scalarDiag{k, 3}, w, 1);
    y = y + 40;
end

vecDiag = {'MFE_CAN.Bridge.LimitedNm', 3; 'MFE_CAN.Bridge.AppliedTorqueNm', 2};
for v = 1:size(vecDiag, 1)
    base = vecDiag{v, 1};
    dm = [bridge '/' base ' Demux'];
    add_block('built-in/Demux', dm, 'Outputs', '4', 'Position', [540 y 550 y + 80]);
    local_wire(fcn, vecDiag{v, 2}, dm, 1);
    for i = 1:4
        w = local_diag(bridge, sprintf('%s.%d', base, i), 'N*m', y + 20 * (i - 1));
        local_wire(dm, i, w, 1);
    end
    y = y + 120;
end

built = struct('subsystem', bridge, 'timeoutS', timeoutS, ...
    'setpointQuantities', {spNames}, 'readyQuantities', {rdyNames}, ...
    'freshnessQuantity', 'MFE_CAN.InverterTorque.RxTimeS');
end


% =========================================================================
function local_read(sub, tag, name, y)
b = [sub '/Read ' tag];
add_block('CarMaker4SL/Read CM Dict', b, 'Position', [30 y 150 y + 24]);
set_param(b, 'xname', name);
set_param(b, 'xstime', 'Inherited');
end

function w = local_diag(sub, name, unit, y)
d = [sub '/Define ' name];
add_block('CarMaker4SL/Define CM Dict', d, 'Position', [660 y 900 y + 24]);
set_param(d, 'xname', name);
set_param(d, 'xtype', 'Double');
set_param(d, 'xunit', unit);
set_param(d, 'xdvaplace', 'None');
w = [sub '/Write ' name];
add_block('CarMaker4SL/Write CM Dict', w, 'Position', [930 y 1150 y + 24]);
set_param(w, 'xname', name);
end

function local_wire(srcBlk, srcPort, dstBlk, dstPort)
% add_line by port handle -- immune to '.' / '/' in block names.
sp = get_param(srcBlk, 'PortHandles');
dp = get_param(dstBlk, 'PortHandles');
sys = get_param(srcBlk, 'Parent');
add_line(sys, sp.Outport(srcPort), dp.Inport(dstPort), 'autorouting', 'on');
end

function local_clearInput(dstBlk, dstPort)
dp = get_param(dstBlk, 'PortHandles');
lh = get_param(dp.Inport(dstPort), 'Line');
if lh ~= -1
    delete_line(lh);
end
end

function local_pruneDanglingLines(sys)
lines = find_system(sys, 'SearchDepth', 1, 'FindAll', 'on', ...
    'LookUnderMasks', 'all', 'Type', 'line');
kill = false(size(lines));
for k = 1:numel(lines)
    kill(k) = get_param(lines(k), 'SrcPortHandle') < 0 || ...
        any(get_param(lines(k), 'DstPortHandle') < 0);
end
for h = lines(kill)'
    if ishandle(h)
        delete_line(h);
    end
end
end

function local_terminate(srcBlk, srcPort, termPath, pos)
h = getSimulinkBlockHandle(srcBlk);
if h == -1
    return;
end
ph = get_param(h, 'PortHandles');
if srcPort > numel(ph.Outport) || get_param(ph.Outport(srcPort), 'Line') ~= -1
    return;
end
add_block('built-in/Terminator', termPath, ...
    'Position', [pos(1) pos(2) pos(1) + 20 pos(2) + 20]);
local_wire(srcBlk, srcPort, termPath, 1);
end

function local_setFcnScript(block, script)
rt = sfroot;
chart = rt.find('-isa', 'Stateflow.EMChart', 'Path', block);
if isempty(chart)
    error('apply_hil_torquevectoring_external_vc:noChart', ...
        'Could not resolve the MATLAB Function block %s.', block);
end
chart.Script = script;
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
    fullfile(here, 'vehicle_models', 'HIL_torquevectoring.mdl'), ...
    fullfile(here, 'HIL_torquevectoring.mdl')};
for k = 1:numel(candidates)
    if isfile(candidates{k})
        model = candidates{k}; return;
    end
end
if bdIsLoaded('HIL_torquevectoring')
    model = 'HIL_torquevectoring'; return;
end
model = 'HIL_torquevectoring';
end
