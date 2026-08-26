% speedgoat.migrateTarget - Open the Speedgoat tool to migrate a Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function opens the Speedgoat Migration Tool, which allows you to migrate your
%   Speedgoat real-time target machine's software for use with the current MATLAB release.
%   Further information and instructions can be found on the <a href="matlab:web('https://www.speedgoat.com/help/slrt/page/io_main/refentry_ref_software_migration')">Software Migration help page</a>.
%
%   Examples
%   --------
%   Open the Speedgoat Migration Tool:
%       speedgoat.migrateTarget

function migrateTarget()
    sg.public.migrateTarget();
end
