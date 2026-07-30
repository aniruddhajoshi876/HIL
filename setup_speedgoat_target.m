% Configure a direct-connect Speedgoat target for Simulink Real-Time.
% Run this from the MATLAB Command Window:
%   run('C:\Users\aniru\OneDrive - McGill University\mfe\HIL\setup_speedgoat_target.m')

targetName = 'Speedgoat';
targetIp = '192.168.7.5';

targets = slrealtime.Targets;
names = targets.getTargetNames;

if ~any(strcmp(names, targetName))
    settings = slrealtime.TargetSettings( ...
        'name', targetName, ...
        'address', targetIp, ...
        'sshPort', 22, ...
        'xcpPort', 5555, ...
        'username', 'slrt', ...
        'userPassword', 'slrt', ...
        'rootPassword', 'root');
    addTarget(targets, settings);
end

setDefaultTargetName(targets, targetName);

fprintf('Default Simulink Real-Time target: %s\n', targets.getDefaultTargetName);
fprintf('Trying to connect to %s at %s...\n', targetName, targetIp);

tg = slrealtime(targetName);
connect(tg);

fprintf('Connected: %d\n', isConnected(tg));
