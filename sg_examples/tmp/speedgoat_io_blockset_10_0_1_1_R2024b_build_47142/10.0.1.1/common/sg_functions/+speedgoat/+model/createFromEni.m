% speedgoat.model.createFromEni - Autogenerate Simulink models from EtherCAT ENI files
%
%   Description
%   -----------
%   This Speedgoat API function reads EtherCAT Network Information files (ENI) and autogenerates a
%   communication interface in Simulink ready for use with the built-in Ethernet interfaces and the
%   IO71x/IO79x I/O modules. During runtime, the real-time application emulates the EtherCAT subordinate devices
%   described in the ENI file and allows data to be exchanged with the remote EtherCAT main device
%   connected with the local Ethernet interface.
%
%   The function places the EtherCAT Emulator Setup, Send and Receive driver blocks into the model and
%   automatically sets the block parameters according to the devices and their input and output
%   signals defined in the ENI file.
%
%   In addition to the standard ENI files, this function also supports the extended ENI (EXI) file.
%
%   Examples
%   --------
%   Autogenerate the Simulink model by selecting the ENI file using the file dialog:
%       speedgoat.model.createFromEni
%
%   Autogenerate the Simulink model by specifying the ENI file as an argument:
%       speedgoat.model.createFromEni('FileName', 'MyNetwork.eni')
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'FileName' - Name of the ENI file including the file extension
%           [character vector]. Pass the file name if the corresponding directory is the current
%           working directory or is included in the MATLAB path. Otherwise, pass the full or
%           relative path of the file.
%
%       'InterfaceId' - Ethernet Interface ID
%           [numeric]. The ID of the relevant Ethernet Interface. The number is passed to the
%           Interface ID parameter of all the EtherCAT Emulator driver blocks added to the model. 
%           If not defined, the default Interface ID is 1.
%
%       'SampleTime' - Sample time [s]
%           [numeric]. The sample time is passed to the Sample Time parameter of all the EtherCAT
%           Emulator Send and Receive driver blocks added to the model. If not defined, the default
%           sample time is 0.001 seconds.

function createFromEni(varargin)
    sg.public.createFromEni(varargin{:});
end
