% speedgoat.setPassword - Set user or root password on your Speedgoat real-time target machine
%
%   Description
%   -----------
%   For security reasons, you should change the passwords on your Speedgoat real-time target machine.
%   This Speedgoat API function will do all the required steps for you.
%
%   Speedgoat systems are pre-configured with a user named 'slrt', which is used for most of the
%   interactions with the target. As with every UNIX-like system, there is also a 'root'
%   user with privileged access rights.
%   Both user name and password are saved in the TargetSettings of every target computer defined
%   in your Simulink® Real-Time™ installation, as shown in the Simulink
%   Real-Time Explorer.
%
%   Examples
%   --------
%   Set the password for the 'slrt' user in your default target machine to 'pwd123':
%       speedgoat.setPassword('slrt', 'pwd123')
%
%   Set the root password in your default target machine to 'superpwd132':
%       speedgoat.setPassword('root', 'superpwd132')
%
%   Set the password on a specified target machine using the target object (e.g. tg):
%       tg = speedgoat.setPassword(___, 'TargetObject', tg)
%
%   Change the password saved in the TargetSettings of the target computer defined
%   in your Simulink Real-Time installation. No connection to target needed.
%       speedgoat.setPassword(___, 'SlrtTargetEntryOnly', true)
%
%   Input Arguments
%   ---------------
%
%   user  - User name for which the password will be changed
%           [character vector | string].
%           This argument specifies the user name for which the password will be changed.
%           Speedgoat systems are configured with a user named 'slrt', which is used for most of the
%           interactions with the target. As with every unix-like system, there is also a 'root'
%           user with privileged access rights. Other user names are not supported.
%
%   password - User password that will be set for the specified user
%           [character vector | string].
%           This argument specifies the password that will be set on the target computer and in 
%           the TargetSettings on the host.
%
%   Name-Value Pair Arguments:
%       'TargetName' - Target machine name
%           [character vector].
%           The name of the target computer for which you want to change the passwords.
%
%       'TargetObject' - Target object
%           [target object].
%           The target object of the target computer for which you want to change the passwords.
%
%       'SlrtTargetEntryOnly' - change only the host-side target entry
%           [boolean]
%           This setting will only change the saved password in the slrtExplorer entry, not
%           changing the password of the target computer. Use this option to adapt your Simulink
%           Real-Time development computer after the target computer's password has been
%           changed from a different development computer.
%
%   Output Arguments
%   ---------------
%   tg - slrealtime.Target object containing the updated  password in the TargetSettings property.
%   The target object is only returned if the API is called with a 'TargetObject' name-value pair 
%   argument.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine
%   (except for 'SlrtTargetEntryOnly').
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will be ignored.
%
%   In R2026a and later the TargetSettings property, which stores the passwords, is immutable.
%   This API will therefore replace the given entry with a new one and, if the 'TargetObject'
%   argument is used, also return a new target object.
%

function varargout = setPassword(user, password, varargin)
    if nargout > 0
        [varargout{1:nargout}] = sg.public.setPassword(user, password, varargin{:});
    else
        sg.public.setPassword(user, password, varargin{:});
    end
end
