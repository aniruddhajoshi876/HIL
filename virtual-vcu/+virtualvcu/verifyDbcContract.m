function result = verifyDbcContract(dbcPath)
%VERIFYDBCCONTRACT Check the supplied MFE26 inverter DBC against raw layout.
if nargin < 1
    dbcPath = fullfile(fileparts(fileparts(mfilename('fullpath'))), ...
        'config', 'MFE26_Inverter.dbc');
end
text = fileread(dbcPath);
controlIds = regexp(text, '(?m)^BO_\s+(390|406|422|438)\s+', 'match');
statusIds = regexp(text, '(?m)^BO_\s+(899|901|915|917|931|933|947|949|1024)\s+', 'match');
assert(numel(controlIds) == 4, 'virtualvcu:DbcControlIds', ...
    'DBC must contain all four control IDs.');
assert(numel(statusIds) == 9, 'virtualvcu:DbcStatusIds', ...
    'DBC must contain all nine status IDs.');
assert(contains(text, 'TorqueLimitPositive : 32|16@1- (0.00390625,0)'), ...
    'virtualvcu:DbcTorqueScale', 'DBC torque scale is not 1/256 Nm/count.');
assert(contains(text, 'SpeedSetpoint : 16|16@1-'), ...
    'virtualvcu:DbcSpeedLayout', 'DBC speed field layout changed.');
result.path = dbcPath;
result.controlIds = uint32([390 406 422 438]);
result.statusIds = uint32([899 901 915 917 931 933 947 949 1024]);
result.torqueScaleNmPerCount = 1 / 256;
end
