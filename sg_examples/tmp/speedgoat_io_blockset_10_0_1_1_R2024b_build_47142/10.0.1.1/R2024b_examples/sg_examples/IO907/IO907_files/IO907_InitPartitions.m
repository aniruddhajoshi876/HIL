%% Skript to initialize the partitions for the IO907 shared memory module
clear Partitions
% create partition structure
Partitions(1).Address = '0x1000';
Partitions(1).Type    = 'double'; 
Partitions(1).Size    = '1';

Partitions(2).Type    = 'uint32';   
Partitions(2).Size    = '1';

Partitions(3).Type = 'double'; 
Partitions(3).Size = '1'; 

Partitions(4).Type = 'uint32';   
Partitions(4).Size = '1';

Partitions = completepartitionstruct(Partitions,'5565');

% Define the controller and plant node structures.
node1=completenodestruct([],'5565');            % create empty note structure
node1.Interface.NodeID = 'any';
node1.Partitions = Partitions;
node1=completenodestruct(node1,'5565'); 

node2=completenodestruct([],'5565');            % create empty note structure
node2.Interface.NodeID = 'any';
node2.Interface.Interrupts.PendingInt1 = 'on';
node2.Partitions = Partitions;
node2=completenodestruct(node2,'5565');
