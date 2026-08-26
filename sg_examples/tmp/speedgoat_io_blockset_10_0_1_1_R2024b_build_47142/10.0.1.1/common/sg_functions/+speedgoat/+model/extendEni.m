% speedgoat.model.extendEni - Extend ENI files with object dictionary information
%
%   Description
%   -----------
%   This Speedgoat API function copies object dictionary information from EtherCAT subordinate
%   information (ESI) files to the initial EtherCAT network information (ENI) file, and creates the
%   extended EtherCAT network information (EXI) file for use with the EtherCAT Emulator Setup block.
%
%   The function saves a copy of the initial ENI file in EXI format. For each subordinate device
%   defined in the ENI file, the function searches the ESI folder for the corresponding ESI file,
%   adds a new entry to the ExtendedConfig section and copies the object dictionary to that
%   section.
%
%   Examples
%   --------
%   Extend an ENI file with information from ESI files:
%       speedgoat.model.extendEni('EniFile', 'old.xml', 'ExiFile', 'new.xml', 'EsiDir', 'C:\esi')
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'EniFile' - Name of the initial ENI file including the file extension
%           [character vector]. Pass the file name if the corresponding directory is the current
%           working directory or is included in the MATLAB path. Otherwise, pass the full or
%           relative path of the file.
%
%       'ExiFile' - Name of the EXI file to be created including the file extension
%           [character vector]. Pass the file name if the corresponding directory is the current
%           working directory or is included in the MATLAB path. Otherwise, pass the full or
%           relative path of the file.
%
%       'EsiDir' - Path to the ESI files
%           [character vector]. Pass the full or relative path of the folder that contains the ESI
%           files. Sub-folders will not be taken into account.

function extendEni(varargin)
    sg.public.extendEni(varargin{:});
end
