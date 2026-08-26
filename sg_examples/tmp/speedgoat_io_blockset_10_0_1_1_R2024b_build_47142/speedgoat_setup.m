% speedgoat_setup - Install the Speedgoat I/O Blockset
%
%   Description
%   -----------
%   This function installs the Speedgoat I/O Blockset and uninstalls the previous one, if desired.
%   All required files will be copied to
%       C:\ProgramData\Speedgoat\speedgoatlib\[MATLAB Release]\[version number]
%   The PATH gets updated and saved.
%
%   Examples
%   --------
%   Install Speedgoat I/O Blockset interactively (confirm each step in the MATLAB Command Window):
%       speedgoat_setup
%
%   Install without any questions asked (replaces any previous installation):
%       speedgoat_setup -forced -acceptEula
%
%   Input Arguments
%   ---------------
%       '-forced' - Do not ask any questions
%           character vector
%           Install this version and overwrite any Speedgoat I/O Blockset previously installed for
%           this MATLAB release. The EULA dialog will still display, unless you use -acceptEula too.
%
%       '-acceptEula' - Do not show the EULA and accept it implicitly
%           character vector
%           For automated installation, this option implies the user's acceptance of the EULA.
%           Please make sure you understand EULA_QNX.txt located in your root folder after the
%           installation or in the subfolder [version number]\common of this installer package.
%
%       '-donotopendoc': Skip opening the release notes page
%           character vector
%           Without this option, the installer will open the MATLAB Help browser or your default web
%           browser to show you the release notes of this version of the Speedgoat I/O Blockset. Use
%           this option to prevent that from happening.
%
%       '-donotrefreshlibbrowser': Skip refreshing the Simulink library browser
%           character vector
%           Under certain circumstances MATLAB is unable to refresh the library browser. This option
%           can help to resolve issues e.g. if MATLAB is running headless under Linux.
%
