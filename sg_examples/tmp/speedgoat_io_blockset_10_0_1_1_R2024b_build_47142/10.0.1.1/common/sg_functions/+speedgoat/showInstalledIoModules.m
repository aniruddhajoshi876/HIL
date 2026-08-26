% speedgoat.showInstalledIoModules - Show all I/O modules installed of Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function* shows a list of all the I/O modules and Ethernet interfaces
%   available on your Speedgoat real-time target machine. This list includes the PCI bus and slot
%   numbers as well as the associated IRQ number. The following additional information is displayed
%   for the Ethernet Controller devices: controller type, interface label or I/O module name, and
%   the interface index (refer also to the Notes section below).
%
%   Examples
%   --------
%   Show the list from the default target machine:
%       speedgoat.showInstalledIoModules
%
%   Show the list of all installed IO modules:
%       speedgoat.showInstalledIoModules('Type', 'All')
%
%   Show the list of all installed Ethernet controller modules only:
%       speedgoat.showInstalledIoModules('Type', 'Ethernet')
%
%   Show the list of all installed Speedgoat modules only:
%       speedgoat.showInstalledIoModules('Type', 'Modules')
%
%   Show the list of all supported Speedgoat modules (doesn't need a target connection):
%       speedgoat.showInstalledIoModules('Type', 'Supported')
%
%   Show the list from a specific target machine using the target name (e.g. 'TargetPC1'):
%       speedgoat.showInstalledIoModules(___, 'TargetName', 'TargetPC1')
%
%   Show the list from a specific target machine using the target object (e.g. tg):
%       speedgoat.showInstalledIoModules(___, 'TargetObject', tg)
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
%       'Type' - Type of IO modules
%           [character vector].
%           The type of IO modules to be shown: 'All' (default), 'Ethernet' (show only the Ethernet
%           controller modules currently installed on you target machine), 'Modules' (show only
%           the Speedgoat modules currently installed on you target machine), 'Supported'
%           (show the list of all supported Speedgoat modules).
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.
%
%   Regarding the additional information displayed for the Ethernet Controller devices: controller
%   type is displayed when running MATLAB R2020a and earlier and MATLAB R2020b and later; the
%   interface label or I/O module name, and the interface index are displayed only when running
%   MATLAB R2020b and later.
%
%   <strong>*This function is deprecated and will be removed from the Speedgoat I/O Blockset in a
%   future release. Please use speedgoat.getIoInterfaces instead.</strong>

function showInstalledIoModules(varargin)
    sg.public.showInstalledIoModules(varargin{:});
    sg.warning(['This function is deprecated and will be removed from the Speedgoat I/O ', ...
        'Blockset in a future release.\nPlease use speedgoat.getIoInterfaces instead.']);
end
