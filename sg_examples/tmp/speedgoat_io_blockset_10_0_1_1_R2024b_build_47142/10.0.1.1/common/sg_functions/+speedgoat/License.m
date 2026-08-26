% speedgoat.License - Provide licensing tools for your Speedgoat real-time target machine.
%
%   Description
%   -----------
%   This Speedgoat API class provides all the required functionality to view and update the
%   licensing information on your Speedgoat real-time target machine.
%
%   Syntax
%   ------
%   Construct the API class:
%       licObj = speedgoat.License()
%
%   Construct the API class using additional options and one or more name-value pair arguments:
%       licObj = speedgoat.License(___, name, value)
%
%   Get the current runtime license file of your target machine:
%       licObj.getFile()
%
%   Get the serial number of your target machine:
%       licObj.getSerialNumber()
%
%   Automatically update the runtime license of your target machine (user confirmation is
%       required):
%       licObj.update()
%
%   Update the runtime license of your target machine with one name-value pair argument (for
%       scripting):
%       licObj.update(name, value)
%
%   Examples
%   --------
%   Construct the license object for the default target machine:
%       licObj = speedgoat.License
%
%   Construct the license object for a specified target machine using the target name
%       (for example, 'TargetPC1'):
%       licObj = speedgoat.License(___, 'TargetName', 'TargetPC1')
%
%   Construct the license object for a specified target machine using the target object
%       (for example, tg):
%       licObj = speedgoat.License(___, 'TargetObject', tg)
%
%   Get the current runtime license file of your target machine:
%       licObj.getFile
%
%   Get the serial number of your target machine:
%       licObj.getSerialNumber
%
%   Automatically update the runtime license of your target machine (user confirmation is
%       required). A dialog box explorer opens if the license file cannot be found:
%       licObj.update
%
%   Update the runtime license of your target machine with the file (sg1234.lic) located
%       in your MATLAB Current Folder (for scripting):
%       licObj.update('FileName', 'sg1234.lic')
%
%   Update the runtime license of your target machine with the complete file path (for
%       script version):
%       licObj.update('FilePath', 'C:\runtimelicense\sg1234.lic')
%
%   Update the runtime license of your target machine with the folder path. The function will
%       automatically take the correct one (for scripting):
%       licObj.update('FilePath', 'C:\runtimelicense')
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'TargetName' - Target machine name
%           [character vector].
%           The name of the target machine you want to use.
%
%       'TargetObject' - Target object
%           [target object].
%           The target object of the target machine you want to use.
%
%       'FileName' - Runtime license filename
%           [character vector].
%           The runtime license filename in the following format: 'sg1234.lic'
%
%       'FilePath' - Runtime license file path
%           [character vector].
%           It could either be the full file path (including the filename):
%           'C:\runtimelicense\sg1234.lic'. Or the folder path containing the file:
%           'C:\runtimelicense'. In the latter case, the correct license file is automatically
%           taken.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.
%
%   Finally, the 'FileName' argument takes precedence: if both arguments are supplied,
%   'FilePath' will therefore be ignored.

classdef License < sg.public.License
    methods (Access = public)
        function licObj = License(varargin)
            licObj@sg.public.License(varargin{:});
        end
    end
end
