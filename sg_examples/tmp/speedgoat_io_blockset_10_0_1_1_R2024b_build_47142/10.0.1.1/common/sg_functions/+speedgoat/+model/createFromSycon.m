% speedgoat.model.createFromSycon - Autogenerate Simulink models from SYCON.net configuration files
%
%   Description
%   -----------
%   This Speedgoat API function reads configuration files exported from SYCON.net and autogenerates
%   a communication interface in Simulink ready for use with the following I/O modules:
%
%   - IO641 PROFIBUS Master
%
%   - IO643 CANopen Master
%
%   - IO751 PROFINET Controller
%
%   - IO755 EtherNet/IP Scanner
%
%   According to the process data items and their addresses defined in the configuration file, the
%   function puts Byte Packing, Byte Unpacking, and the respective Send and Receive blocks into the
%   model and automatically connects them.
%
%   The function creates one subsystem for sending and one for receiving, where input and output
%   ports represent the process data items. This allows for easy data exchange with devices
%   connected to the I/O modules mentioned above.
%
%   To export a configuration file from SYCON.net, right-click the Master node in the network view
%   and select Additional Functions --> Export --> XML
%
%   Examples
%   --------
%   Autogenerate the Simulink model by selecting the configuration file using the file dialog:
%       speedgoat.model.createFromSycon
%
%   Autogenerate the Simulink model by specifing the configuration file as an argument:
%       speedgoat.model.createFromSycon('MyProfinetConfig.xml')
%
%   Create additional input and output ports allowing access to status information related to the
%   process data items:
%       speedgoat.model.createFromSycon(___, 'ShowStatusSignals', true)
%
%   Input Arguments
%   ---------------
%   fileName - Name of the configuration file including the file extension
%       [character vector].
%       Pass the file name if the corresponding directory is the current working directory or
%       included in the MATLAB Path. Otherwise, pass the full or relative path of the file.
%
%   Name-Value Pair Arguments:
%       'ShowStatusSignals' - Show status signals
%           [boolean].
%           If true, the function creates additional ports to access the status information related
%           to the process data objects. If false, the status signals remain hidden.
%           This argument has impact only on PROFINET configuration files where so-called sub-slots
%           provide producer (IOPS) and consumer status information (IOCS).

function createFromSycon(varargin)
    sg.public.createFromSycon(varargin{:});
end
