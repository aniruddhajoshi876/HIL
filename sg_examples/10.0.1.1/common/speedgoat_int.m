function board = speedgoat_int
% speedgoat_int Returns a structure that describes an interrupt service routine
%   for xPC Target.
%
%   If you are writing a driver that requires an interrupt from your board,
%   then you need to extend this file for your board or boards.  The output can
%   be a vector of board(1), board(2) structures, etc.
%
%   The board.name entry is the string that will be displayed in the interrupt
%   source list in both the asynchronous interrupt block and on the xPC Target
%   options page of the configuration parameters for a model.
%
%   The VendorId and DeviceId values must be given for your board if it is a
%   PCI board.  If you need to specify the Subsystem vendor ID and Subsystem
%   device ID to uniquely identify your board, then fill those in.  They are
%   ignored if set to -1.  Not all boards require these.  Most board suppliers
%   will give these values in hexidecimal.  Use the hex2dec() function to
%   convert to numeric as shown.
%
%   If you are creating an interrupt service routine for an ISA board or a
%   PC/104 board, then you won't have PCI vendor and device IDs.  Set the
%   VendorId to -1 and the DeviceId to 1.
%
%   HookIncludeFile is the name of the C file that contains your interrupt
%   controlling functions.
%
%   StartFunction is the name of the function that enables interrupts on your
%   board and performs any final preparation before the model execution starts.
%   This is called after all mdlStart routines have been called for all blocks
%   in the model.
%
%   StopFunction is the name of the function that disables interrupts and
%   performs any shutdown functions for interrupts. This function is called
%   just before all mdlTerminate routines will be called in the model.
%
%   PreHookFunction is the interrupt service routine.  Perform any required
%   register read/write to acknowledge the interrupt on the board and stop it
%   from interrupting.  Interrupts will be enabled after this routine returns
%   and before the model executes.
%
%   PostHookFunction is not useful and should just be set to 'NULL'.
%
% VERY IMPORTANT STEPS:
%
%   After making any change to the board.name entry, you must exit Matlab and
%   restart it.  The menus are only populated the first time they are requested
%   after starting Matlab.
%
%   ORDER MATTERS in this structure.  If the order is incorrect, combining this
%   structure with the built in interrupt list will fail.
%
%   So, the steps to adding a new file or editing an existing file are:
%   1.  Create the new file, or edit an existing one
%   2.  Exit MATLAB and restart it
%   3.  Execute 'rehash toolbox' to put the new file on the hash list
%   4.  Open a model and check for your new entry on the interrupt list

    board = [];
    i = 0;

    % Keep the order of these structure elements the same or you will get an
    % error and the entry in the list won't work.

    % IO104
    i = i + 1;
    board(i).name             = 'IO104 DMA INT';
    board(i).VendorId         = hex2dec('10b5');
    board(i).DeviceId         = hex2dec('9056');
    board(i).SubVendorId      = hex2dec('10b5');
    board(i).SubDeviceId      = hex2dec('3172');
    board(i).PreHookFunction  = 'xpcio104dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO104dmahooks';
    board(i).StartFunction    = 'xpcio104dmastart';
    board(i).StopFunction     = 'xpcio104dmastop';

    % IO106
    i = i + 1;
    board(i).name             = 'IO106 DMA INT';
    board(i).VendorId         = hex2dec('10b5');
    board(i).DeviceId         = hex2dec('9056');
    board(i).SubVendorId      = hex2dec('10b5');
    board(i).SubDeviceId      = hex2dec('3101');
    board(i).PreHookFunction  = 'xpcio106dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO106dmahooks';
    board(i).StartFunction    = 'xpcio106dmastart';
    board(i).StopFunction     = 'xpcio106dmastop';

    % IO108
    i = i + 1;
    board(i).name             = 'IO108 DMA INT';
    board(i).VendorId         = hex2dec('10b5');
    board(i).DeviceId         = hex2dec('9056');
    board(i).SubVendorId      = hex2dec('10b5');
    board(i).SubDeviceId      = hex2dec('3120');
    board(i).PreHookFunction  = 'xpcio108dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO108dmahooks';
    board(i).StartFunction    = 'xpcio108dmastart';
    board(i).StopFunction     = 'xpcio108dmastop';

    % IO109
    i = i + 1;
    board(i).name             = 'IO109 DMA INT';
    board(i).VendorId         = hex2dec('10b5');
    board(i).DeviceId         = hex2dec('9080');
    board(i).SubVendorId      = hex2dec('10b5');
    board(i).SubDeviceId      = hex2dec('3100');
    board(i).PreHookFunction  = 'xpcio109dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO109dmahooks';
    board(i).StartFunction    = 'xpcio109dmastart';
    board(i).StopFunction     = 'xpcio109dmastop';

    % IO112
    i = i + 1;
    board(i).name             = 'IO112 DMA INT';
    board(i).VendorId         = hex2dec('10b5');
    board(i).DeviceId         = hex2dec('9056');
    board(i).SubVendorId      = hex2dec('10b5');
    board(i).SubDeviceId      = hex2dec('3431');
    board(i).PreHookFunction  = 'xpcio112dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO112dmahooks';
    board(i).StartFunction    = 'xpcio112dmastart';
    board(i).StopFunction     = 'xpcio112dmastop';

    % IO130
    i = i + 1;
    board(i).name             = 'IO130 DMA INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0212');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('0014');
    board(i).PreHookFunction  = 'xpcio130_131dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO130_131dmahooks';
    board(i).StartFunction    = 'xpcio130_131dmastart';
    board(i).StopFunction     = 'xpcio130_131dmastop';

    % IO131
    i = i + 1;
    board(i).name             = 'IO131 DMA INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0212');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcio130_131dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO130_131dmahooks';
    board(i).StartFunction    = 'xpcio130_131dmastart';
    board(i).StopFunction     = 'xpcio130_131dmastop';

    % IO132
    i = i + 1;
    board(i).name             = 'Speedgoat IO132';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0214');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('0014');
    board(i).PreHookFunction  = 'xpcio132_io133dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio132_io133dmahooks';
    board(i).StartFunction    = 'xpcio132_io133dmastart';
    board(i).StopFunction     = 'xpcio132_io133dmastop';

    % IO133
    i = i + 1;
    board(i).name             = 'Speedgoat IO133';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0214');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcio132_io133dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio132_io133dmahooks';
    board(i).StartFunction    = 'xpcio132_io133dmastart';
    board(i).StopFunction     = 'xpcio132_io133dmastop';

    % IO134
    i = i + 1;
    board(i).name             = 'Speedgoat IO134';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0215');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('0014');
    board(i).PreHookFunction  = 'xpcio132_io133dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio132_io133dmahooks';
    board(i).StartFunction    = 'xpcio132_io133dmastart';
    board(i).StopFunction     = 'xpcio132_io133dmastop';

    % IO135
    i = i + 1;
    board(i).name             = 'Speedgoat IO135';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('0215');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcio132_io133dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio132_io133dmahooks';
    board(i).StartFunction    = 'xpcio132_io133dmastart';
    board(i).StopFunction     = 'xpcio132_io133dmastop';

    % IO141
    i = i + 1;
    board(i).name             = 'Speedgoat IO141';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('021D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('0014');
    board(i).PreHookFunction  = 'xpcio141_io142dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio141_io142dmahooks';
    board(i).StartFunction    = 'xpcio141_io142dmastart';
    board(i).StopFunction     = 'xpcio141_io142dmastop';

    % IO142
    i = i + 1;
    board(i).name             = 'Speedgoat IO142';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('021D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcio141_io142dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio141_io142dmahooks';
    board(i).StartFunction    = 'xpcio141_io142dmastart';
    board(i).StopFunction     = 'xpcio141_io142dmastop';

    % IO301
    i = i + 1;
    board(i).name             = 'Speedgoat IO301 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('4350');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('4350');
    board(i).PreHookFunction  = 'xpcIO301intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO301intahooks';
    board(i).StartFunction    = 'xpcIO301intastart';
    board(i).StopFunction     = 'xpcIO301intastop';

    % IO302
    i = i + 1;
    board(i).name             = 'Speedgoat IO302 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('4357');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('4357');
    board(i).PreHookFunction  = 'xpcIO302intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO302intahooks';
    board(i).StartFunction    = 'xpcIO302intastart';
    board(i).StopFunction     = 'xpcIO302intastop';

    % IO303
    i = i + 1;
    board(i).name             = 'Speedgoat IO303 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('4253');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('4253');
    board(i).PreHookFunction  = 'xpcIO303intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO303intahooks';
    board(i).StartFunction    = 'xpcIO303intastart';
    board(i).StopFunction     = 'xpcIO303intastop';

    % IO304
    i = i + 1;
    board(i).name             = 'Speedgoat IO304 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('504');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('504');
    board(i).PreHookFunction  = 'xpcIO304intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO304intahooks';
    board(i).StartFunction    = 'xpcIO304intastart';
    board(i).StopFunction     = 'xpcIO304intastop';

    % IO306
    i = i + 1;
    board(i).name             = 'Speedgoat IO306-25k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcIO30xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xintahooks';
    board(i).StartFunction    = 'xpcIO30xintastart';
    board(i).StopFunction     = 'xpcIO30xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO306-25k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcIO30xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xinta2hooks';
    board(i).StartFunction    = 'xpcIO30xinta2start';
    board(i).StopFunction     = 'xpcIO30xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO306 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000A');
    board(i).PreHookFunction  = 'xpcIO30xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xserialhooks';
    board(i).StartFunction    = 'xpcIO30xserialstart';
    board(i).StopFunction     = 'xpcIO30xserialstop';

    % IO307
    i = i + 1;
    board(i).name             = 'Speedgoat IO307-25k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000C');
    board(i).PreHookFunction  = 'xpcIO30xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xintahooks';
    board(i).StartFunction    = 'xpcIO30xintastart';
    board(i).StopFunction     = 'xpcIO30xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO307-25k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000C');
    board(i).PreHookFunction  = 'xpcIO30xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xinta2hooks';
    board(i).StartFunction    = 'xpcIO30xinta2start';
    board(i).StopFunction     = 'xpcIO30xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO307 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000C');
    board(i).PreHookFunction  = 'xpcIO30xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xserialhooks';
    board(i).StartFunction    = 'xpcIO30xserialstart';
    board(i).StopFunction     = 'xpcIO30xserialstop';
    
    % IO308
    i = i + 1;
    board(i).name             = 'Speedgoat IO308-25k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000B');
    board(i).PreHookFunction  = 'xpcIO30xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xintahooks';
    board(i).StartFunction    = 'xpcIO30xintastart';
    board(i).StopFunction     = 'xpcIO30xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO308-25k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000B');
    board(i).PreHookFunction  = 'xpcIO30xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xinta2hooks';
    board(i).StartFunction    = 'xpcIO30xinta2start';
    board(i).StopFunction     = 'xpcIO30xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO308 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('027A');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('000B');
    board(i).PreHookFunction  = 'xpcIO30xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO30xserialhooks';
    board(i).StartFunction    = 'xpcIO30xserialstart';
    board(i).StopFunction     = 'xpcIO30xserialstop';

    % IO311
    i = i + 1;
    board(i).name             = 'Speedgoat IO311 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('524D');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('524D');
    board(i).PreHookFunction  = 'xpcIO311intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO311intahooks';
    board(i).StartFunction    = 'xpcIO311intastart';
    board(i).StopFunction     = 'xpcIO311intastop';

    % IO312
    i = i + 1;
    board(i).name             = 'Speedgoat IO312 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('424B');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('424B');
    board(i).PreHookFunction  = 'xpcIO312intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO312intahooks';
    board(i).StartFunction    = 'xpcIO312intastart';
    board(i).StopFunction     = 'xpcIO312intastop';

    % IO313
    i = i + 1;
    board(i).name             = 'Speedgoat IO313 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('4353');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('4353');
    board(i).PreHookFunction  = 'xpcIO313intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO313intahooks';
    board(i).StartFunction    = 'xpcIO313intastart';
    board(i).StopFunction     = 'xpcIO313intastop';

    % IO314
    i = i + 1;
    board(i).name             = 'Speedgoat IO314 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('2004');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('2004');
    board(i).PreHookFunction  = 'xpcIO314intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO314intahooks';
    board(i).StartFunction    = 'xpcIO314intastart';
    board(i).StopFunction     = 'xpcIO314intastop';

    % IO316
    i = i + 1;
    board(i).name             = 'Speedgoat IO316 IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO316intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO316intahooks';
    board(i).StartFunction    = 'xpcIO316intastart';
    board(i).StopFunction     = 'xpcIO316intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316 IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316 MSI';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO316MSIprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO316MSIhooks';
    board(i).StartFunction    = 'xpcIO316MSIstart';
    board(i).StopFunction     = 'xpcIO316MSIstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316-100k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904b');
    board(i).PreHookFunction  = 'xpcIO316100intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO316100intahooks';
    board(i).StartFunction    = 'xpcIO316100intastart';
    board(i).StopFunction     = 'xpcIO316100intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316-100k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904b');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO316-100k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904b');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    % IO317
    i = i + 1;
    board(i).name             = 'Speedgoat IO317 IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903e');
    board(i).PreHookFunction  = 'xpcIO317intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO317intahooks';
    board(i).StartFunction    = 'xpcIO317intastart';
    board(i).StopFunction     = 'xpcIO317intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO317 IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903e');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO317 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903e');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO317-100k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904d');
    board(i).PreHookFunction  = 'xpcIO317100intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO317100intahooks';
    board(i).StartFunction    = 'xpcIO317100intastart';
    board(i).StopFunction     = 'xpcIO317100intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO317-100k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904d');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO317-100k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904d');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    % IO318
    i = i + 1;
    board(i).name             = 'Speedgoat IO318 IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903d');
    board(i).PreHookFunction  = 'xpcIO318intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO318intahooks';
    board(i).StartFunction    = 'xpcIO318intastart';
    board(i).StopFunction     = 'xpcIO318intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO318 IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903d');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO318 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903d');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO318-100k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904c');
    board(i).PreHookFunction  = 'xpcIO318100intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO318100intahooks';
    board(i).StartFunction    = 'xpcIO318100intastart';
    board(i).StopFunction     = 'xpcIO318100intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO318-100k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904c');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO318-100k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('9279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('904c');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    % IO321
    i = i + 1;
    board(i).name             = 'Speedgoat IO321 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('4c40');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('4c40');
    board(i).PreHookFunction  = 'xpcIO321intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO321intahooks';
    board(i).StartFunction    = 'xpcIO321intastart';
    board(i).StopFunction     = 'xpcIO321intastop';

    % IO322
    i = i + 1;
    board(i).name             = 'Speedgoat IO322 IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO322intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO322intahooks';
    board(i).StartFunction    = 'xpcIO322intastart';
    board(i).StopFunction     = 'xpcIO322intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO322 IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO322 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('903c');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    % IO323
    i = i + 1;
    board(i).name             = 'Speedgoat IO323 IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('9047');
    board(i).PreHookFunction  = 'xpcIO323intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO323intahooks';
    board(i).StartFunction    = 'xpcIO323intastart';
    board(i).StopFunction     = 'xpcIO323intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO323 IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('9047');
    board(i).PreHookFunction  = 'xpcIO31x_IO32x_inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31x_IO32x_inta2hooks';
    board(i).StartFunction    = 'xpcIO31x_IO32x_inta2start';
    board(i).StopFunction     = 'xpcIO31x_IO32x_inta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO323 Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927b');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('9047');
    board(i).PreHookFunction  = 'xpcIO31xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO31xserialhooks';
    board(i).StartFunction    = 'xpcIO31xserialstart';
    board(i).StopFunction     = 'xpcIO31xserialstop';

    % IO331
    i = i + 1;
    board(i).name             = 'Speedgoat IO331 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('5701');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('5701');
    board(i).PreHookFunction  = 'xpcIO331intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO331intahooks';
    board(i).StartFunction    = 'xpcIO331intastart';
    board(i).StopFunction     = 'xpcIO331intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO331 IntA2';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('5701');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('5701');
    board(i).PreHookFunction  = 'xpcIO331inta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO331inta2hooks';
    board(i).StartFunction    = 'xpcIO331inta2start';
    board(i).StopFunction     = 'xpcIO331inta2stop';

    % IO324
    i = i + 1;
    board(i).name             = 'Speedgoat IO324-200k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('100A');
    board(i).PreHookFunction  = 'xpcIO33xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xintahooks';
    board(i).StartFunction    = 'xpcIO33xintastart';
    board(i).StopFunction     = 'xpcIO33xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO324-200k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('100A');
    board(i).PreHookFunction  = 'xpcIO33xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xinta2hooks';
    board(i).StartFunction    = 'xpcIO33xinta2start';
    board(i).StopFunction     = 'xpcIO33xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO324-200k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('100A');
    board(i).PreHookFunction  = 'xpcIO33xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xserialhooks';
    board(i).StartFunction    = 'xpcIO33xserialstart';
    board(i).StopFunction     = 'xpcIO33xserialstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO324-200k Analog input';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('100A');
    board(i).PreHookFunction  = 'xpcIO324dmareadprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO324dmareadhooks';
    board(i).StartFunction    = 'xpcIO324dmareadstart';
    board(i).StopFunction     = 'xpcIO324dmareadstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO324-200k Analog output';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('927D');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('100A');
    board(i).PreHookFunction  = 'xpcIO324dmawriteprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO324dmawritehooks';
    board(i).StartFunction    = 'xpcIO324dmawritestart';
    board(i).StopFunction     = 'xpcIO324dmawritestop';

    % IO332
    i = i + 1;
    board(i).name             = 'Speedgoat IO332-200k IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7006');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7006');
    board(i).PreHookFunction  = 'xpcIO33xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xintahooks';
    board(i).StartFunction    = 'xpcIO33xintastart';
    board(i).StopFunction     = 'xpcIO33xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO332-200k IntA2';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7006');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7006');
    board(i).PreHookFunction  = 'xpcIO33xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xinta2hooks';
    board(i).StartFunction    = 'xpcIO33xinta2start';
    board(i).StopFunction     = 'xpcIO33xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO332-200k Serial INT';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7006');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7006');
    board(i).PreHookFunction  = 'xpcIO33xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xserialhooks';
    board(i).StartFunction    = 'xpcIO33xserialstart';
    board(i).StopFunction     = 'xpcIO33xserialstop';

    % IO333
    i = i + 1;
    board(i).name             = 'Speedgoat IO333 IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7002');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7002');
    board(i).PreHookFunction  = 'xpcIO33xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xintahooks';
    board(i).StartFunction    = 'xpcIO33xintastart';
    board(i).StopFunction     = 'xpcIO33xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO333 IntA2';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7002');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7002');
    board(i).PreHookFunction  = 'xpcIO33xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xinta2hooks';
    board(i).StartFunction    = 'xpcIO33xinta2start';
    board(i).StopFunction     = 'xpcIO33xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO333-325k Serial INT';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7002');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7002');
    board(i).PreHookFunction  = 'xpcIO33xserial2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xserialhooks';
    board(i).StartFunction    = 'xpcIO33xserialstart';
    board(i).StopFunction     = 'xpcIO33xserialstop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO333-410k IntA';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7003');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7003');
    board(i).PreHookFunction  = 'xpcIO33xintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xintahooks';
    board(i).StartFunction    = 'xpcIO33xintastart';
    board(i).StopFunction     = 'xpcIO33xintastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO333-410k IntA2';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7003');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7003');
    board(i).PreHookFunction  = 'xpcIO33xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xinta2hooks';
    board(i).StartFunction    = 'xpcIO33xinta2start';
    board(i).StopFunction     = 'xpcIO33xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO333-410k Serial INT';
    board(i).VendorId         = hex2dec('16d5');
    board(i).DeviceId         = hex2dec('7003');
    board(i).SubVendorId      = hex2dec('16d5');
    board(i).SubDeviceId      = hex2dec('7003');
    board(i).PreHookFunction  = 'xpcIO33xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO33xserialhooks';
    board(i).StartFunction    = 'xpcIO33xserialstart';
    board(i).StopFunction     = 'xpcIO33xserialstop';

    % IO383
    i = i + 1;
    board(i).name             = 'Speedgoat IO383-25k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a279');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a032');
    board(i).PreHookFunction  = 'xpcIO38325intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO38325intahooks';
    board(i).StartFunction    = 'xpcIO38325intastart';
    board(i).StopFunction     = 'xpcIO38325intastop';

    % IO391
    i = i + 1;
    board(i).name             = 'Speedgoat IO391-50k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO391intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio391intahooks';
    board(i).StartFunction    = 'xpcIO391intastart';
    board(i).StopFunction     = 'xpcIO391intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO391-50k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO39xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xinta2hooks';
    board(i).StartFunction    = 'xpcIO39xinta2start';
    board(i).StopFunction     = 'xpcIO39xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO391-50k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO39xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xserialhooks';
    board(i).StartFunction    = 'xpcIO39xserialstart';
    board(i).StopFunction     = 'xpcIO39xserialstop';

    % IO392
    i = i + 1;
    board(i).name             = 'Speedgoat IO392-50k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00b');
    board(i).PreHookFunction  = 'xpcIO392intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio392intahooks';
    board(i).StartFunction    = 'xpcIO392intastart';
    board(i).StopFunction     = 'xpcIO392intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO392-50k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00b');
    board(i).PreHookFunction  = 'xpcIO39xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xinta2hooks';
    board(i).StartFunction    = 'xpcIO39xinta2start';
    board(i).StopFunction     = 'xpcIO39xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO392-50k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00b');
    board(i).PreHookFunction  = 'xpcIO39xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xserialhooks';
    board(i).StartFunction    = 'xpcIO39xserialstart';
    board(i).StopFunction     = 'xpcIO39xserialstop';

    % IO393
    i = i + 1;
    board(i).name             = 'Speedgoat IO393-50k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a032');
    board(i).PreHookFunction  = 'xpcIO393intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio393intahooks';
    board(i).StartFunction    = 'xpcIO393intastart';
    board(i).StopFunction     = 'xpcIO393intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO393-50k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a032');
    board(i).PreHookFunction  = 'xpcIO39xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xinta2hooks';
    board(i).StartFunction    = 'xpcIO39xinta2start';
    board(i).StopFunction     = 'xpcIO39xinta2stop';
    
    i = i + 1;
    board(i).name             = 'Speedgoat IO393-50k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a032');
    board(i).PreHookFunction  = 'xpcIO39xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xserialhooks';
    board(i).StartFunction    = 'xpcIO39xserialstart';
    board(i).StopFunction     = 'xpcIO39xserialstop';
    
    % IO394
    i = i + 1;
    board(i).name             = 'Speedgoat IO394-50k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00c');
    board(i).PreHookFunction  = 'xpcIO394intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio394intahooks';
    board(i).StartFunction    = 'xpcIO394intastart';
    board(i).StopFunction     = 'xpcIO394intastop';
    
    i = i + 1;
    board(i).name             = 'Speedgoat IO394-50k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00c');
    board(i).PreHookFunction  = 'xpcIO39xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xinta2hooks';
    board(i).StartFunction    = 'xpcIO39xinta2start';
    board(i).StopFunction     = 'xpcIO39xinta2stop';
    
    i = i + 1;
    board(i).name             = 'Speedgoat IO394-50k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a26f');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00c');
    board(i).PreHookFunction  = 'xpcIO39xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xserialhooks';
    board(i).StartFunction    = 'xpcIO39xserialstart';
    board(i).StopFunction     = 'xpcIO39xserialstop';
    
    % IO397
    i = i + 1;
    board(i).name             = 'Speedgoat IO397-50k IntA';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a273');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO397intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio397intahooks';
    board(i).StartFunction    = 'xpcIO397intastart';
    board(i).StopFunction     = 'xpcIO397intastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO397-50k IntA2';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a273');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO39xinta2prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xinta2hooks';
    board(i).StartFunction    = 'xpcIO39xinta2start';
    board(i).StopFunction     = 'xpcIO39xinta2stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO397-50k Serial INT';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('a273');
    board(i).SubVendorId      = hex2dec('1498');
    board(i).SubDeviceId      = hex2dec('a00a');
    board(i).PreHookFunction  = 'xpcIO39xserialprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcio39xserialhooks';
    board(i).StartFunction    = 'xpcIO39xserialstart';
    board(i).StopFunction     = 'xpcIO39xserialstop';

    % IO503
    i = i + 1;
    board(i).name             = 'Speedgoat IO503';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('01D2');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1; %Changes if not standart clock used
    board(i).PreHookFunction  = 'xpcIO5XXintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO5XXintahooks';
    board(i).StartFunction    = 'xpcIO5XXintastart';
    board(i).StopFunction     = 'xpcIO5XXintastop';

    % IO504
    i = i + 1;
    board(i).name             = 'Speedgoat IO504';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('01D1');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1;
    board(i).PreHookFunction  = 'xpcIO5XXintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO5XXintahooks';
    board(i).StartFunction    = 'xpcIO5XXintastart';
    board(i).StopFunction     = 'xpcIO5XXintastop';

    % IO505
    i = i + 1;
    board(i).name             = 'Speedgoat IO505';
    board(i).VendorId         = hex2dec('1498');
    board(i).DeviceId         = hex2dec('01D6');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1;
    board(i).PreHookFunction  = 'xpcIO5XXintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO5XXintahooks';
    board(i).StartFunction    = 'xpcIO5XXintastart';
    board(i).StopFunction     = 'xpcIO5XXintastop';

    % IO511
    i = i + 1;
    board(i).name             = 'Speedgoat IO511 IntA';
    board(i).VendorId         = hex2dec('10B5');
    board(i).DeviceId         = hex2dec('9080');
    board(i).SubVendorId      = hex2dec('10B5');
    board(i).SubDeviceId      = hex2dec('2401');
    board(i).PreHookFunction  = 'xpcIO511intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO511intahooks';
    board(i).StartFunction    = 'xpcIO511intastart';
    board(i).StopFunction     = 'xpcIO511intastop';
    
    % IO512
    i = i + 1;
    board(i).name             = 'Speedgoat IO512 IntA';
    board(i).VendorId         = hex2dec('10B5');
    board(i).DeviceId         = hex2dec('9056');
    board(i).SubVendorId      = hex2dec('10B5');
    board(i).SubDeviceId      = hex2dec('3198');
    board(i).PreHookFunction  = 'xpcIO512intaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO512intahooks';
    board(i).StartFunction    = 'xpcIO512intastart';
    board(i).StopFunction     = 'xpcIO512intastop';

    % IO581
    i = i + 1;
    board(i).name             = 'Speedgoat IO581';
    board(i).VendorId         = hex2dec('13A8');
    board(i).DeviceId         = hex2dec('0354');
    board(i).SubVendorId      = hex2dec('0000');
    board(i).SubDeviceId      = hex2dec('0000');
    board(i).PreHookFunction  = 'xpcIO5XXintaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO5XXintahooks';
    board(i).StartFunction    = 'xpcIO5XXintastart';
    board(i).StopFunction     = 'xpcIO5XXintastop';

    % IO623
    i = i + 1;
    board(i).name             = 'Speedgoat IO623 CC1 interrupt';
    board(i).VendorId         = hex2dec('1974');
    board(i).DeviceId         = hex2dec('0009');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1;
    board(i).PreHookFunction  = 'xpcio623prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO623hooks';
    board(i).StartFunction    = 'xpcio623start';
    board(i).StopFunction     = 'xpcio623stop';

    % IO75X
    i = i + 1;
    board(i).name             = 'Speedgoat IO75X';
    board(i).VendorId         = hex2dec('15cf');
    board(i).DeviceId         = hex2dec('0000');
    board(i).SubVendorId      = hex2dec('0000');
    board(i).SubDeviceId      = hex2dec('0000');
    board(i).PreHookFunction  = 'xpcIO75Xprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO75Xhooks';
    board(i).StartFunction    = 'xpcIO75Xstart';
    board(i).StopFunction     = 'xpcIO75Xstop';
    
    % IO901/IO902
    i = i + 1;
    board(i).name = 'SCRAMNet_GT200';
    board(i).VendorId = hex2dec('1387');
    board(i).DeviceId = hex2dec('5310');
    board(i).SubVendorId = -1;
    board(i).SubDeviceId = -1;
    board(i).PreHookFunction = 'xpcscgtprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile = 'cwcec_scgthooks';
    board(i).StartFunction = 'xpcscgtstart';
    board(i).StopFunction = 'xpcscgtstop';

    % IO811
    i = i + 1;
    board(i).name             = 'BitFlow NEON';
    board(i).VendorId         = hex2dec('118d');
    board(i).DeviceId         = hex2dec('4000');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1;
    board(i).PreHookFunction  = 'xpcbfneonprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'mw_xpcbfneonhooks';
    board(i).StartFunction    = 'xpcbfneonstart';
    board(i).StopFunction     = 'xpcbfneonstop';

    % IO821
    i = i + 1;
    board(i).name             = 'Speedgoat IO821 INT';
    board(i).VendorId         = hex2dec('1ad7');
    board(i).DeviceId         = hex2dec('8000');
    board(i).SubVendorId      = -1;
    board(i).SubDeviceId      = -1;
    board(i).PreHookFunction  = 'xpcio821prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO821hooks';
    board(i).StartFunction    = 'xpcio821start';
    board(i).StopFunction     = 'xpcio821stop';

    % IO907
    i = i + 1;
    board(i).name             = 'Speedgoat IO907';
    board(i).VendorId         = hex2dec('114A');
    board(i).DeviceId         = hex2dec('5565');
    board(i).SubVendorId      = hex2dec('1556');
    board(i).SubDeviceId      = hex2dec('0080');
    board(i).PreHookFunction  = 'xpcio907prehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO907hooks';
    board(i).StartFunction    = 'xpcio907start';
    board(i).StopFunction     = 'xpcio907stop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO907 DMA';
    board(i).VendorId         = hex2dec('114A');
    board(i).DeviceId         = hex2dec('5565');
    board(i).SubVendorId      = hex2dec('1556');
    board(i).SubDeviceId      = hex2dec('0080');
    board(i).PreHookFunction  = 'xpcIO907dmaprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO907dmahooks';
    board(i).StartFunction    = 'xpcIO907dmastart';
    board(i).StopFunction     = 'xpcIO907dmastop';

    i = i + 1;
    board(i).name             = 'Speedgoat IO907 (preserve Interrupts messages)';
    board(i).VendorId         = hex2dec('114A');
    board(i).DeviceId         = hex2dec('5565');
    board(i).SubVendorId      = hex2dec('1556');
    board(i).SubDeviceId      = hex2dec('0080');
    board(i).PreHookFunction  = 'xpcio907msgprehook';
    board(i).PostHookFunction = 'NULL';
    board(i).HookIncludeFile  = 'xpcIO907msghooks';
    board(i).StartFunction    = 'xpcio907msgstart';
    board(i).StopFunction     = 'xpcio907msgstop';

    % New interrupts
    newInts = sg.db.getInterrupts('RequireAccessToThisDataBase', '20Goats');
    % New interrupts that replace existing interrupts -> take over new configuration
    for i = 1:length(board)
        matchIdx = find(strcmp(board(i).name, {newInts.Replaces}));
        if ~isempty(matchIdx)
            for field = fieldnames(board)'
                if ~strcmp(field{1}, 'name')
                    board(i).(field{1}) = newInts(matchIdx).(field{1});
                end
            end
        end
    end
    % New interrupts that do not replace existing interrupts -> add to list
    noMatches = find(cellfun(@isempty,{newInts.Replaces}));
    for matchIdx = 1:length(noMatches)
        boardIdx = length(board) + 1;
        for field = fieldnames(board)'
            if ~strcmp(field{1}, 'name')
                board(boardIdx).(field{1}) = newInts(noMatches(matchIdx)).(field{1});
            end
        end
        board(boardIdx).name = newInts(noMatches(matchIdx)).PublicName;
    end

    % Sort interrupt entries by name
    [~, sortedIdx] = sort({board.name});
    board = board(sortedIdx);
end
