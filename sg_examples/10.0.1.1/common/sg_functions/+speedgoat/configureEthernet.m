% speedgoat.configureEthernet - Open the Speedgoat tool to configure the Ethernet interfaces
%
%   Description
%   -----------
%   This Speedgoat API function opens the Speedgoat Ethernet Configuration Tool
%   (<a href="matlab:web('https://www.speedgoat.com/help/slrt/page/io_main/refentry_ethernet_configuration')"
%   >help documentation</a>), which allows you to configure all general-purpose
%   Ethernet interfaces on your Speedgoat real-time target machine.
%   This includes both on-board interfaces as well as additional interfaces provided by I/O modules
%   such as IO71X or IO791.
%
%   The tool enables you to set the IP address and subnet mask for all IP-based protocols or
%   dedicate an interface to be used by the EtherCAT Main Device protocol stack.
%
%   You can also use the tool to configure the Host Link to use a different interface, and change
%   the default gateway of your Speedgoat real-time target machine.
%
%   Examples
%   --------
%   Open the Speedgoat Ethernet Configuration Tool:
%       speedgoat.configureEthernet
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.

function configureEthernet
    sg.public.configureEthernet();
end
