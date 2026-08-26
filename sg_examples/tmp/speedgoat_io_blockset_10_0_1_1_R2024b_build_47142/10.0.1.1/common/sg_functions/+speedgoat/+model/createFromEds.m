% speedgoat.model.createFromEds - Autogenerate Simulink models from CANopen EDS files
%
%   Description
%   -----------
%   This Speedgoat API function reads CANopen Electronic Data Sheets (EDS) and autogenerates a
%   communication interface in Simulink ready for use with the IO644 CANopen Slave I/O module. During
%   runtime, the module simulates the device the EDS file represents and allows data to be exchanged
%   with devices connected to the I/O module, such as the CANopen master.
%
%   According to the objects defined in the EDS file, the function places the IO644 Setup, PDO and
%   Object driver blocks into the model and automatically sets the block parameters according to the
%   objects' data types and values.
%
%   Examples
%   --------
%   Autogenerate the Simulink model by selecting the EDS file using the file dialog:
%       speedgoat.model.createFromEds
%
%   Autogenerate the Simulink model by specifying the EDS file as an argument:
%       speedgoat.model.createFromEds('FileName', 'MyCanOpenDevice.eds')
%
%   Prevent two objects from being represented by Object blocks in the model and in the resulting object
%   dictionary during runtime:
%       speedgoat.model.createFromEds(___, 'ExcludeObjects', [0x6040, 0x6041])
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'FileName' - Name of the EDS file including the file extension
%           [character vector].
%           Pass the file name if the corresponding directory is the current working directory or
%           is included in the MATLAB path. Otherwise, pass the full or relative path of the file.
%
%       'CanNodeId' - CANopen Node ID
%           [numeric]. The address of the device in the CANopen network in the range 1 to 127. The
%           number is passed to the CAN Node ID parameter of the Setup block created. If not
%           defined, the default Node ID is 1.
%
%       'ModuleId' - Module ID
%           [numeric]. The Module ID of the relevant IO644 I/O module. The number is passed to the
%           Module ID parameter of all the IO644 driver blocks added to the model. If not defined,
%           the default Module ID is 1.
%
%       'ExcludeObjects' - Objects to be excluded from the object dictionary created
%           [numeric vector]. The object indices for which no Object blocks should be added to the
%           model.

function createFromEds(varargin)
    sg.public.createFromEds(varargin{:});
end
