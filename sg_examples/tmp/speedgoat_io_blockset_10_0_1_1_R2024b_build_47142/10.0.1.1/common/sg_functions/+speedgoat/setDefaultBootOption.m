% speedgoat.setDefaultBootOption - Set default boot OS for your Speedgoat real-time target machine
%
%   Description
%   -----------
%   If your Speedgoat real-time target machine is configured for dual-boot, this Speedgoat API
%   function lets you define which operating system is loaded by default at startup.
%
%   You can run this function without input arguments, in which case you will be prompted to
%   select one of the different OS options. Alternatively, you can run the function using input
%   arguments and directly specify the exact release.
%
%   Additionally, you can specify the timeout for the dual-boot selection menu. By default, this
%   menu is displayed on the target monitor with a timeout of 10 s. This can be changed to 0 s
%   (i.e., no menu), a value in seconds, or simply no timeout.
%
%   Moreover, you can specify whether the target automatically reboots to the newly selected
%   operating system.
%
%   Compatibility
%   -------------
%   The default boot option can be changed across host/target versions:
%
%   - Host running: MATLAB R2026a and later with SLRT.
%     Target running: 'Simulink Real-Time R2020b to R2025b'.
%     Automatic reboot: supported.
%
%   - Host running: MATLAB R2020b to R2025b with SLRT.
%     Target running: 'Simulink Real-Time R2026a and later (Antelope RTOS)'.
%     Automatic reboot: supported.
%
%   - Host running: MATLAB R2020a and earlier with SLRT.
%     Target running: 'Simulink Real-Time R2020b to R2025b'.
%     Automatic reboot: not supported.
%
%   Examples
%   --------
%   Set the default target machine to boot on a different OS using the dialog box:
%       speedgoat.setDefaultBootOption
%
%   Set the default target machine to boot the OS for R2025b:
%       speedgoat.setDefaultBootOption('R2025b')
%
%   Set the default target machine to boot the OS for R2025a:
%       speedgoat.setDefaultBootOption('R2025a')
%
%   Set the default target machine to boot the OS for R2025b and set the dual-boot timeout to 3 s:
%       speedgoat.setDefaultBootOption('R2025b', 'DualBootTimeout', 3)
%
%   Set the default target machine to boot the OS for R2026a and reboot the target automatically:
%       speedgoat.setDefaultBootOption('R2026a', 'AutoReboot', true)
%
%   Set the default boot option on a specified target machine using the target name
%       (e.g. 'TargetPC1'):
%       speedgoat.setDefaultBootOption(___, 'TargetName', 'TargetPC1')
%
%   Set the default boot option on a specified target machine using the target object (e.g., tg):
%       speedgoat.setDefaultBootOption(___, 'TargetObject', tg)
%
%   Input Arguments
%   ---------------
%   release - Default boot entry
%       [character vector | string].
%       This argument is optional. If no argument is given, then the function displays a dialog box
%       to choose which release should be the new default boot option. A value between 'R2020b' and
%       'R2025b' sets the default boot entry to 'Simulink Real-Time R2020b to R2025b'.
%       A value of 'R2026a' or later sets the default boot entry to 'Simulink Real-Time R2026a and
%       later (Antelope RTOS)'.
%
%   Name-Value Pair Arguments:
%       'DualBootTimeout' - Dual-boot timeout value
%           [numerical].
%           This name-value pair argument specifies the time, in seconds, to wait for a keyboard
%           input before booting the default operating system. A timeout of 0 causes the system to
%           boot the default operating system immediately without displaying the menu. A value of
%           -1 causes the system to wait indefinitely for a keyboard input.
%           You have to specify the release version if you use this name-value pair argument.
%
%       'AutoReboot' - Reboot the target automatically
%           [boolean].
%           This name-value pair argument specifies whether the target reboots automatically to the
%           operating system specified by the release argument. The default value is set to false.
%
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
%   is used. In addition, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.
%
%   The target machine must have previously been configured for dual-boot using
%   the <strong>speedgoat.migrateTarget</strong> function.

function setDefaultBootOption(varargin)
    sg.public.setDefaultBootOption(varargin{:});
end
