% speedgoat.showPtpInterfaces - Show all ethernet controllers of Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function shows a list of all Ethernet interfaces available on your
%   Speedgoat real-time target machine. This list includes the Speedgoat label, the index number,
%   whether or not PTP is supported and the current IP configuration.
%
%   Examples
%   --------
%   Show the PTP-capable interfaces of the default target machine:
%       speedgoat.showPtpInterfaces
%
%   Show the interfaces of a specific target machine using the target name (e.g. 'TargetPC1'):
%       speedgoat.showPtpInterfaces('TargetName', 'TargetPC1')
%
%   Show the interfaces of a specific target machine using the target object (e.g. tg):
%       speedgoat.showPtpInterfaces('TargetObject', tg)
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
%   Notes
%   -----
%   This function requires an ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function showPtpInterfaces(varargin)
    sg.public.showPtpInterfaces(varargin{:});
end
