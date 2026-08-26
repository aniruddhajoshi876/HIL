hModel = new_system('host_model');
open_system(hModel)

if exist('host_ip','var') == 0
    host_ip = inputdlg('No host_ip defined. Please enter the IP address of your host PC:');
    host_ip = host_ip{1};
end
if exist('target_ip','var') == 0
    target_ip = inputdlg('No target_ip defined. Please enter the IP address of your target machine:');
    target_ip = target_ip{1};
end

udpReceiveBlock1 = add_block('slrealtimeiplib/UDP Receive',[bdroot,'/UDP Receive'],...
    'ipAddress',host_ip, 'localPort', '25000', 'rcvWidth', '62500', 'fmAddress', ...
    target_ip, 'useHostTargetConn', 'on', 'rcvFmAny', 'off', 'sampleTime', '0.5');
udpReceiveBlock2 = add_block('slrealtimeiplib/UDP Receive',[bdroot,'/UDP Receive1'],...
    'ipAddress',host_ip, 'localPort', '25001', 'rcvWidth', '62500', 'fmAddress', ...
    target_ip, 'useHostTargetConn', 'on', 'rcvFmAny', 'off', 'sampleTime', '0.5');
udpReceiveBlock3 = add_block('slrealtimeiplib/UDP Receive',[bdroot,'/UDP Receive2'],...
    'ipAddress',host_ip, 'localPort', '25002', 'rcvWidth', '62500', 'fmAddress', ...
    target_ip, 'useHostTargetConn', 'on', 'rcvFmAny', 'off', 'sampleTime', '0.5');
udpReceiveBlock4 = add_block('slrealtimeiplib/UDP Receive',[bdroot,'/UDP Receive3'],...
    'ipAddress',host_ip, 'localPort', '25003', 'rcvWidth', '62500', 'fmAddress', ...
    target_ip, 'useHostTargetConn', 'on', 'rcvFmAny', 'off', 'sampleTime', '0.5');

udp1Ports = get_param(udpReceiveBlock1,'PortHandles');
udp2Ports = get_param(udpReceiveBlock2,'PortHandles');
udp3Ports = get_param(udpReceiveBlock3,'PortHandles');
udp4Ports = get_param(udpReceiveBlock4,'PortHandles');

unpackBlock1 = add_block('slrealtimeutilitieslib/Byte Unpacking',[bdroot,'/Byte Unpacking'], ...
    'MaskUnpackedDataSizes', '{[250,250]}');
unpackBlock2 = add_block('slrealtimeutilitieslib/Byte Unpacking',[bdroot,'/Byte Unpacking1'], ...
    'MaskUnpackedDataSizes', '{[250,250]}');
unpackBlock3 = add_block('slrealtimeutilitieslib/Byte Unpacking',[bdroot,'/Byte Unpacking2'], ...
    'MaskUnpackedDataSizes', '{[250,250]}');
unpackBlock4 = add_block('slrealtimeutilitieslib/Byte Unpacking',[bdroot,'/Byte Unpacking3'], ...
    'MaskUnpackedDataSizes', '{[250,250]}');

terminator1 = add_block('simulink/Commonly Used Blocks/Terminator',[bdroot,'/Terminator']);
terminator2 = add_block('simulink/Commonly Used Blocks/Terminator',[bdroot,'/Terminator1']);
terminator3 = add_block('simulink/Commonly Used Blocks/Terminator',[bdroot,'/Terminator2']);
terminator4 = add_block('simulink/Commonly Used Blocks/Terminator',[bdroot,'/Terminator3']);

unpack1Ports = get_param(unpackBlock1,'PortHandles');
unpack2Ports = get_param(unpackBlock2,'PortHandles');
unpack3Ports = get_param(unpackBlock3,'PortHandles');
unpack4Ports = get_param(unpackBlock4,'PortHandles');

terminator1Ports = get_param(terminator1,'PortHandles');
terminator2Ports = get_param(terminator2,'PortHandles');
terminator3Ports = get_param(terminator3,'PortHandles');
terminator4Ports = get_param(terminator4,'PortHandles');

add_line(bdroot,udp1Ports.Outport(1),unpack1Ports.Inport(1));
add_line(bdroot,udp2Ports.Outport(1),unpack2Ports.Inport(1));
add_line(bdroot,udp3Ports.Outport(1),unpack3Ports.Inport(1));
add_line(bdroot,udp4Ports.Outport(1),unpack4Ports.Inport(1));

add_line(bdroot,udp1Ports.Outport(2),terminator1Ports.Inport(1));
add_line(bdroot,udp2Ports.Outport(2),terminator2Ports.Inport(1));
add_line(bdroot,udp3Ports.Outport(2),terminator3Ports.Inport(1));
add_line(bdroot,udp4Ports.Outport(2),terminator4Ports.Inport(1));

matrixConcat1 = add_block('simulink/Math Operations/Matrix Concatenate',[bdroot,'/Matrix Concatenate'], ...
    'NumInputs', '2', 'Mode', 'Multidimensional array', 'ConcatenateDimension', '1');
matrixConcat2 = add_block('simulink/Math Operations/Matrix Concatenate',[bdroot,'/Matrix Concatenate1'], ...
    'NumInputs', '2', 'Mode', 'Multidimensional array', 'ConcatenateDimension', '1');
matrixConcat3 = add_block('simulink/Math Operations/Matrix Concatenate',[bdroot,'/Matrix Concatenate2'], ...
    'NumInputs', '2', 'Mode', 'Multidimensional array', 'ConcatenateDimension', '2');

concat1Ports = get_param(matrixConcat1,'PortHandles');
concat2Ports = get_param(matrixConcat2,'PortHandles');
concat3Ports = get_param(matrixConcat3,'PortHandles');

add_line(bdroot,unpack1Ports.Outport(1),concat1Ports.Inport(1));
add_line(bdroot,unpack2Ports.Outport(1),concat1Ports.Inport(2));
add_line(bdroot,unpack3Ports.Outport(1),concat2Ports.Inport(1));
add_line(bdroot,unpack4Ports.Outport(1),concat2Ports.Inport(2));
add_line(bdroot,concat1Ports.Outport(1),concat3Ports.Inport(1));
add_line(bdroot,concat2Ports.Outport(1),concat3Ports.Inport(2));

videoViewer = add_block('visionsinks/Video Viewer',[bdroot,'/Video Viewer'], ...
    'OpenAtMdlStart','off');
videoViewerPorts = get_param(videoViewer,'PortHandles');
add_line(bdroot,concat3Ports.Outport(1),videoViewerPorts.Inport(1));

Simulink.BlockDiagram.arrangeSystem(hModel);
set_param(hModel, 'EnablePacing', 'on');
set_param(hModel, 'PacingRate', 1);
set_param(hModel, 'StopTime', 'inf');
pause(0.5);
set_param(hModel,'Zoomfactor','fit to view');

%% cleanup
clear udpReceiveBlock1 udpReceiveBlock2 udpReceiveBlock3 udpReceiveBlock4;
clear dp1Ports udp2Ports udp3Ports udp4Ports;
clear unpackBlock1 unpackBlock2 unpackBlock3 unpackBlock4;
clear terminator1 terminator2 terminator3 terminator4;
clear unpack1Ports unpack2Ports unpack3Ports unpack4Ports;
clear terminator1Ports terminator2Ports terminator3Ports terminator4Ports;
clear matrixConcat1 matrixConcat2 matrixConcat3 matrixConcat4;
clear concat1Ports concat2Ports concat3Ports;
clear videoViewer videoViewerPorts;
