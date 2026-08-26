%SLBLOCKS Defines the Simulink library block representation in the library browser
function blkStruct = slblocks
    openFcn = 'speedgoatlib';
    name = 'Simulink Real-Time: Speedgoat I/O Blockset';

    browser(1).Library = openFcn;
    browser(1).Name = name;
    browser(1).IsFlat = 0;

    blkStruct.Name = name;
    blkStruct.OpenFcn = openFcn;
    blkStruct.MaskInitialization = '';
    blkStruct.Browser = browser;
end
