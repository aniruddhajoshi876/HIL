% speedgoat.setTargetAuthentication - Authenticate your Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function starts the step-by-step instruction to authenticate your Speedgoat
%   real-time target machine.
%
%   It must be used if you have already run the <strong>speedgoat.getTargetAuthentication</strong> function and
%   have received the serial file from Speedgoat Support. When you are ready to install the serial
%   file, simply run this function and follow the instructions displayed in your MATLAB Command
%   Window.
%
%   Examples
%   --------
%   Set the serial file on the default target machine:
%       speedgoat.setTargetAuthentication
%
%   Set the serial file on a specified target machine using the target name (e.g. 'TargetPC1'):
%       speedgoat.setTargetAuthentication('TargetName', 'TargetPC1')
%
%   Set the serial file on a specified target machine using the target object (e.g. tg):
%       speedgoat.setTargetAuthentication('TargetObject', tg)
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
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function setTargetAuthentication(varargin)
    sg.public.setTargetAuthentication(varargin{:});
end
