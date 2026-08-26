% speedgoat.can.DbParserBlockConfig - Create a DB Parser Block Config instance
%
%   Description
%   -----------
%   This DB Parser Block Config class constructs a class object for interacting with a CAN DB 
%   Parser Read or Write block in Simulink®. The Config instance is connected to the 
%   specified block. Upon construction, it checks for instances of the CAN DB Parser Read or Write 
%   application — these must be closed to proceed.
%
%   Several methods are available to retrieve or modify settings relevant to the functionality of 
%   instance the connected DB Parser block; these methods operate on the data managed by the 
%   Config class itself. Only after applying or saving the Config instance is data passed to 
%   the connected DB Parser block.
%
%   Syntax
%   ------
%   Get a DB Parser Block Config instance for a specified CAN DB Parser Read or Write block:
%       configObj = speedgoat.can.DbParserBlockConfig(blockPath)
%
%   Get the value for one or more specified parameters:
%       configObj.getParameter(parameter1,...,parameterN)
%
%   Set the value for one or more specified parameters:
%       configObj.setParameter(parameter1,value1,...,parameterN,valueN)
%
%   Select or update from a .dbc file previously configured using the Database Manager:
%       configObj.selectDatabase(databaseName, ignoreMissingItems)
%
%   Refresh the list of Simulink input signals on the input port of the connected CAN DB Parser
%   Write block:
%       configObj.refreshSimulinkInputSignals()
%
%   Add a predefined or custom CRC Message Protection profile:
%       configObj.addCrcProfile(label, type, customFile, customFunction)
%
%   Remove a CRC Message Protection profile:
%       configObj.removeCrcProfile(label)
%
%   Add a Counter Message Protection profile:
%       configObj.addCounterProfile(label, startValue, stopValue, stepValue, bitLength)
%
%   Remove a Counter Message Protection profile:
%       configObj.removeCounterProfile(label)
%
%   Get message structure for a specified message identifier:
%       messages = configObj.getMessage(messageIdentifier, value)
%
%   Enable or disable one or more messages:
%       configObj.setEnable(messages, action)
%
%   Get mapping item structure for a specified mapping item identifier:
%       mappingItems = configObj.getMappingItems(itemIdentifier, value)
%
%   Map one or more input items (Simulink input signals or Message Protection profiles) to 
%   corresponding mapping items:
%       configObj.setMapping(inputSignals, mappingItems)
%
%   Save persistent data to the connected CAN DB Parser Read or Write block without applying
%   changes:
%       configObj.save()
%
%   Apply the mapping to the connected CAN DB Parser Read or Write block and save persistent data:
%       configObj.apply(ignoreMissingInputSignals)
%
%   Delete the DB Parser Block Config instance without saving persistent data or applying 
%   changes to the connected CAN DB Parser Read or Write block:
%       configObj.delete()
%
%   Examples
%   ------
%   Get a DB Parser Block Config instance and connect it to the currently selected CAN DB 
%   Parser Read or Write block in a loaded Simulink model:
%       configObj = speedgoat.can.DbParserBlockConfig(gcb)
%
%   Get a DB Parser Block Config instance and connect it to the specified CAN DB Parser Read 
%   or Write block in a loaded Simulink model:
%       configObj = speedgoat.can.DbParserBlockConfig('myModel/CAN DB Parser Write 1')
%
%   Get the sample time of the connected CAN DB Parser Read or Write block:
%       sampleTime = configObj.getParameter('SampleTime')
%
%   Get the list of available Simulink input signals:
%       inputSignals = configObj.getParameter('SimulinkInputSignals')
%
%   Get the module ID of the selected CAN and LIN Setup block:
%       moduleId = configObj.getParameter('ModuleId')
%
%   Get the struct of all CAN messages for the selected .dbc file:
%       dbItems = configObj.getParameter('Messages')
%
%   Get the table of all .dbc file options and the currently selected .dbc file:
%       databaseConfiguration = configObj.getParameter('DatabaseOptions', 'SelectedDatabase')
%
%   Set the module ID to select the CAN and LIN Setup block:
%       configObj.setParameter('ModuleId', 2)
%
%   Set the module type and ID to select the CAN and LIN Setup block and the sample time:
%       configObj.setParameter('ModuleType', 'IO602-4', 'ModuleId', '1', 'SampleTime', '0.01')
%
%   Set the Setup block path directly to select the CAN and LIN Setup block:
%       configObj.setParameter('SetupBlock', 'myModel/CAN and LIN Setup 1')
%
%   Set the block port type to change the way Simulink input signals are input to the CAN DB 
%   Parser Write block or output for the CAN DB Parser Read block:
%        configObj.setParameter('BlockPortType', 'Signals')
%
%   Select or update from a .dbc file previously configured using the Database Manager (must be
%   available in the DatabaseOptions parameter of the DB Parser Block Config instance):
%       configObj.selectDatabase('myDatabase')
%
%   Refresh the list of Simulink input signals on the input port of the connected CAN DB Parser
%   Write block:
%       configObj.refreshSimulinkInputSignals()
%
%   Add a predefined CRC message protection profile with a specified label:
%       configObj.addCrcProfile('CRC_1_8-bit', 'CRC8-SAEJ1850')
%
%   Add a custom CRC message protection profile with a specified label (refer to the usage notes 
%   for more detailed information about custom CRC message protection):
%       configObj.addCrcProfile('CRC_2_12-bit', 'Custom', 'custom_crc.cpp', 'custom_crc_func')
%
%   Remove a CRC message protection profile using its label:
%       configObj.removeCrcProfile('CRC_1_12-bit')
%
%   Add a Counter message protection profile with a specified label:
%       configObj.addCounterProfile('Counter_1_8-bit', 0, 255, 2, 8)
%
%   Remove a Counter message protection profile using its label:
%       configObj.removeCounterProfile('Counter_1_8-bit')
%
%   Get message structure for CAN messages with a specified ID:
%       messages = configObj.getMessage('ID', 257)
%
%   Get message structure for CAN messages with a specified message name:
%       messages = configObj.getMessage('Name', 'CANMsg1')
%
%   Get message structure for CAN messages which contain a signal with a specified signal name:
%       messages = configObj.getMessage('SignalName', 'CANSignal1')
%
%   Get message structure for all CAN messages in the selected .dbc file:
%       messages = configObj.getMessage('All')
%
%   Set enabled state for a specified message structure:
%       configObj.setEnable(messages(1:end), true)
%
%   Get mapping items structure for CAN messages with a specified ID:
%       mappingItems = configObj.getMappingItems('ID', 257)
%
%   Get mapping items structure of items which contain a signal with a specified signal name:
%       mappingItems = configObj.getMappingItems('SignalName', 'CANSignal1')
%
%   Get mapping items structure of items which have been mapped to a specific Simulink input signal 
%   or message protection profile:
%       mappingItems = configObj.getMappingItems('MappedSignal', 'CRC_1_8-bit')
%
%   Get mapping items structure of all enabled items:
%       mappingItems = configObj.getMappingItems('All')
%
%   Map one Simulink input signal to a specified mapping items structure element:
%       configObj.setMapping('simulink.signal', mappingItems(1))
%
%   Map each Simulink input signal to a single mapping item:
%       configObj.setMapping(inputSignals(1:5), mappingItems(1:5))
%
%   Clear the mapping for a mapping item by mapping it to 'Ground(0)':
%       configObj.setMapping('Ground(0)', mappingItems(1))
%
%   Clear the mapping for all mapping items by mapping them to 'Ground(0)':
%       configObj.setMapping('Ground(0)', mappingItems)
%
%   Apply the mapping to the connected CAN DB Parser Read or Write block and save persistent data:
%       configObj.apply()
%
%   Save persistent data to the connected CAN DB Parser Read or Write block without applying 
%   changes:
%       configObj.save()
%
%   Delete the DB Parser Block Config instance without saving persistent data or applying 
%   changes to the connected CAN DB Parser Read or Write block:
%       configObj.delete()
%
%   Input Arguments
%   ---------------
%   'blockPath' - Path to a CAN DB Parser Read or Write Simulink block
%       [character vector | string].
%       The path to a CAN DB Parser Read or Write block in a loaded Simulink model file.
%
%   Output Arguments
%   ----------------
%   'configObj' – Instance of the DB Parser Block Config class
%       [DbParserBlockConfig]
%       The DB Parser Block Config instance initialized for interacting with the specified 
%       CAN DB Parser Read or Write block. The block remains connected to the Config instance 
%       until the Config instance is deleted.
%
%   Notes
%   -----
%   This constructor requires a loaded Simulink model with at least one CAN and LIN Setup block and
%   one CAN DB Parser Read or Write block.

classdef DbParserBlockConfig < sg.public.can.DbParserBlockConfig
    methods (Access = public)
        function configObj = DbParserBlockConfig(blockPath)
            % DbParserBlockConfig - Constructor for the DB Parser Block Config class
            %
            %   Description
            %   -----------
            %   configObj = DbParserBlockConfig(blockPath)
            %       The DbParserBlockConfig constructor initializes an instance of the 
            %       DbParserBlockConfig class for interacting with a CAN DB Parser Read or Write
            %       block in Simulink. It checks for instances of the CAN DB Parser Read or Write
            %       application to this block, these must be closed to proceed.
            %
            %   Examples
            %   --------
            %   Get an DB Parser Block Config object for a CAN DB Parser Write block:
            %       configObj = DbParserBlockConfig('myModel/CAN DB Parser Write 1');
            %
            %   Input Arguments
            %   ---------------
            %   blockPath - Path to a CAN DB Parser Read or Write Simulink block
            %       character vector | string
            %       The path to a CAN DB Parser Read or Write Simulink block. The corresponding
            %       Simulink model must be loaded or opened first.
            %
            %   Output Arguments
            %   ----------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance initialized for interacting with the
            %       specified CAN DB Parser Read or Write block. The block remains connected to the
            %       Config instance until the Config instance is deleted.

            arguments
                blockPath{mustBeText}
            end

            configObj@sg.public.can.DbParserBlockConfig(blockPath);
        end

        function delete(configObj)
            % delete - Destructor for the DB Parser Block Config class
            %
            %   Description
            %   -----------
            %   delete(configObj)
            %       The delete method prepares the DB Parser Block Config instance for
            %       deletion. Any unsaved changes are discarded. No data is saved to the connected
            %       CAN DB Parser Read or Write block, nor is the mapping applied to this block. To
            %       save the changes made using this Config instance, call configObj.save()
            %       before deleting. To save and apply the changes made using this Config
            %       instance, call configObj.apply() before deleting.
            %
            %   Examples
            %   --------
            %   Delete an instance of the DB Parser Block Config class:
            %       delete(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance to be deleted.

            delete@sg.public.can.DbParserBlockConfig(configObj);
        end
    end

    methods (Access = public)
        function param = getParameter(configObj, paramName)
            % getParameter - Get the value for one or more specified parameters
            %
            %   Description
            %   -----------
            %   getParameter(configObj, 'ParameterName1', ..., 'ParameterNameN')
            %       The getParameter method gets the value of one or more specified parameters. It
            %       supports several predefined parameters and returns the corresponding value in
            %       either the default format for this parameter or as a cell array for multiple
            %       requested parameters.
            %
            %   Examples
            %   --------
            %   Get the module ID of the selected CAN and LIN Setup block:
            %       moduleId = configObj.getParameter('ModuleId')
            %
            %   Get the list of Simulink input signals:
            %       inputSignals = getParameter(configObj, 'SimulinkInputSignals');
            %
            %   Get all CRC and Counter message protection profiles:
            %       msgProtProfiles = getParameter(configObj, 'CrcProfiles', 'CounterProfiles');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the parameter value is
            %       being retrieved.
            %
            %   ParameterName - Name of the parameter to retrieve
            %       character vector | string
            %       Name of the parameter to retrieve. Supported values are:
            %           'ModuleOptions'             - Table of available Setup blocks to select.
            %           'ModuleType'                - Module type of the selected Setup block.
            %           'ModuleId'                  - Module ID of the selected Setup block.
            %           'SetupBlock'                - Path of the selected Setup block.
            %           'ChannelNumber'             - Selected channel number.
            %           'SampleTime'                - Sample time of the connected DB Parser block.
            %           'IDsInHex'                  - ID interpretation: hex or decimal.
            %           'DatabaseOptions'           - List of available .dbc database files.
            %           'SelectedDatabase'          - Selected .dbc database file.
            %           'Database'                  - Full .dbc database content as a struct.
            %           'SimulinkInputSignals'      - List of Simulink input signals.
            %           'CrcProfiles'               - List of configured CRC Profiles.
            %           'CounterProfiles'           - List of configured Counter Profiles.
            %           'BlockPortType'             - Input port type to CAN DB Parser Write block.
            %           'ShowEnableInput'           - Status of optional 'Enable' input port.
            %           'UseCycleTimesFromDatabase' - Message Tx timing: Cycle Time or Sample Time.
            %           'Messages'                  - Struct of messages in the .dbc database file.
            %           'MappingTable'              - Struct of enabled and mapped items.
            %
            %   Output Arguments
            %   ----------------
            %   param - Result value
            %       numeric | character vector | cell array of character vectors | structure | cell
            %       Output values of the specified parameters.

            arguments(Input)
                configObj
            end

            arguments(Input, Repeating)
                paramName{mustBeMember(paramName, {'ModuleOptions', 'ModuleType', ...
                    'ModuleId', 'SetupBlock', 'ChannelNumber', 'SampleTime', 'IDsInHex', ...
                    'DatabaseOptions', 'SelectedDatabase', 'Database', 'SimulinkInputSignals', ...
                    'CrcProfiles', 'CounterProfiles', 'BlockPortType', 'ShowEnableInput', ...
                    'UseCycleTimesFromDatabase', 'Messages', 'MappingTable'})}
            end

            param = getParameter@sg.public.can.DbParserBlockConfig(configObj, paramName{:});
        end

        function setParameter(configObj, paramName, param)
            % setParameter - Set the value for one or more specified parameters
            %
            %   Description
            %   -----------
            %   setParameter(configObj, 'ParameterName1', Value1, 'ParameterName2', Value2, ...)
            %       Values of various parameters can be set using the setParameter method. It
            %       parses input name-value pairs, validates data types, and triggers corresponding
            %       update processes based on the specified parameter.
            %
            %   Examples
            %   --------
            %   Select the specified CAN and LIN Setup block identified by module type IO603 and 
            %   ID 2 for use with this CAN DB Parser block, and configure the sample time to 0.01s:
            %       setParameter(configObj, 'ModuleType', 'IO603', 'ModuleId', 2, ...
            %           'SampleTime', 0.01);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which parameters are being set.
            %
            %   Optional Name-Value Pair Arguments
            %   ----------------------------------
            %   'ModuleType' - Module type for a CAN and LIN Setup block
            %       character vector | string
            %       Module type of a CAN and LIN Setup block, selectable in the Module Type
            %       dropdown. Currently available are 'IO602-4', 'IO602-2', 'IO603', 'IO691',
            %       'IO610', 'IO611', 'IO612', 'IO613', 'IO614'. A matching setup block for this
            %       module type is then searched for in the model and the parameters 'SetupBlock'
            %       and 'ChannelNumber' are updated accordingly. The previously configured
            %       'ModuleId' is attempted to be kept, however a different one may be selected if
            %       there is no matching Setup block existent in the model.
            %
            %   'ModuleId' - Identifier for a unique CAN I/O module and CAN and LIN Setup block
            %       numeric | character vector | string
            %       Module ID of a CAN and LIN Setup block existing in this model. A matching setup
            %       block for this module ID is then searched for in the model and the parameters
            %       'SetupBlock' and 'ChannelNumber' are updated accordingly. The previously
            %       configured 'ModuleType' is attempted to be kept, however a different one may be
            %       selected if there is no matching Setup block existent in the model.
            %
            %   'SetupBlock' - Path of a unique CAN and LIN Setup block
            %       character vector | string
            %       Path of a CAN and LIN Setup block existing in this model. Triggers an update to 
            %       the 'ModuleType', 'ModuleId' and 'ChannelNumber' parameters.
            %
            %   'SampleTime' - CAN DB Parser Read or Write block sample time
            %       numeric | character vector | string
            %       Sample time at which the connected CAN DB Parser Read or Write block is
            %       executed.
            %
            %   'IDsInHex' - Toggle CAN message ID interpretation: hex or decimal
            %       logical
            %       CAN message IDs are represented and expected as decimal if this parameter is on
            %       false. If true, IDs are in hexadecimal format preceeded by '0x'.
            %
            %   'BlockPortType' - Simulink signal inport or outport type for the CAN DB Parser block
            %       character vector | string
            %       Different options are available for the CAN DB Parser Read block and the Write
            %       block.
            %       CAN DB Parser Read: 'Signals' block port type creates one output port for each
            %       signal in all enabled CAN messages. 'Single Bus' block port type creates one
            %       output port in total with a nested virtual bus containing all enabled CAN
            %       messages.
            %       CAN DB Parser Write: 'Signals' block port type creates one input port for each
            %       signal in all enabled CAN messages. Mapping Simulink input signals or message
            %       protection profiles is not possible anymore with this setting. 'Bus (Mapping)'
            %       block port type creates one input port in total and expects a valid Simulink
            %       bus. Signals of this bus may then be mapped to signals defined in the enabled
            %       CAN messages.
            %
            %   'ShowEnableInput' - Toggle optional 'Enable' input port on CAN DB Parser Write block
            %       logical
            %       Only available for CAN DB Parser Write blocks. Enabling this shows the optional
            %       'Enable' input port to control transmission of CAN messages during runtime. Each
            %       message may be controlled using an n-elements boolean vector, where n represents
            %       the number of messages from the *.dbc file that are enabled. The indexing of the
            %       messages aligns with the sorted ID numbers of all enabled messages, in ascending
            %       order.
            %
            %   'UseCycleTimesFromDatabase' - Toggle message Tx timing: Cycle Time or Sample Time
            %       logical
            %       Only available for CAN DB Parser Write blocks. Enable this to transmit CAN
            %       messages with the cycle time defined in the selected *.dbc file. If disabled,
            %       CAN messages are transmitted at the selected block sample time by default.

            arguments(Input)
                configObj
            end

            arguments(Input, Repeating)
                paramName{mustBeMember(paramName, {'ModuleType', 'ModuleId', 'SetupBlock', ...
                    'ChannelNumber', 'SampleTime', 'IDsInHex', 'BlockPortType', ...
                    'ShowEnableInput', 'UseCycleTimesFromDatabase'})}
                param
            end

            setParameter@sg.public.can.DbParserBlockConfig(configObj, paramName, param);
        end

        function selectDatabase(configObj, databaseName, ignoreMissingItems)
            % selectDatabase - Select or update from a .dbc file configured in the Database Manager
            %
            %   Description
            %   -----------
            %   selectDatabase(configObj, databaseName)
            %   selectDatabase(configObj, databaseName, ignoreMissingItems)
            %       The selectDatabase method configures the specified .dbc database for use with
            %       the connected CAN DB Parser Read or Write block and updates the configuration
            %       from the selected database. The .dbc file must already be configured in the
            %       Database Manager.
            %
            %   Examples
            %   --------
            %   Select a new .dbc database for use with this CAN DB Parser Read or Write block:
            %       configObj.selectDatabase('myDBC');
            %
            %   Update the currently configured .dbc database:
            %       configObj.selectDatabase('myDBC');
            %
            %   Update the currently configured .dbc database and highlight previously enabled and
            %   mapped items, which are not existing anymore in the new .dbc database version:
            %       configObj.selectDatabase('myDBC', false);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the .dbc database is being
            %       newly selected or updated.
            %
            %   databaseName - Name of a configured .dbc database file
            %       character vector | string
            %       Name of a database option configured with speedgoat.can.DbManagerConfig.
            %
            %   ignoreMissingItems - Handle missing mapped rows after database update
            %       logical
            %       If true (default), missing mapped messages or signals are discarded without
            %       user interaction. If false, missing mapped rows are listed and you are prompted
            %       to discard them or cancel and keep the previous configuration.

            arguments (Input)
                configObj
            end

            arguments (Input)
                databaseName {mustBeText}
                ignoreMissingItems {logical} = true
            end

            selectDatabase@sg.public.can.DbParserBlockConfig(configObj, databaseName, ...
                ignoreMissingItems);
        end

        function refreshSimulinkInputSignals(configObj)
            % refreshSimulinkInputSignals - Refresh the list of Simulink input signals
            %
            %   Description
            %   -----------
            %   refreshSimulinkInputSignals(configObj)
            %       The refreshSimulinkInputSignals method updates the list of Simulink input
            %       signals on the input port of the connected CAN DB Parser Write block. It checks
            %       if the connected Simulink bus signal is valid, issuing a warning if it is not.
            %
            %   Examples
            %   --------
            %   Refresh the list of Simulink input signals on the input port of the connected CAN DB
            %   Parser Write block:
            %       refreshSimulinkInputSignals(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the Simulink input signals 
            %       list is being refreshed.

            refreshSimulinkInputSignals@sg.public.can.DbParserBlockConfig(configObj);
        end

        function addCrcProfile(configObj, label, type, customFile, customFunction)
            % addCrcProfile - Add a predefined or custom CRC Message Protection profile
            %
            %   Description
            %   -----------
            %   addCrcProfile(configObj, label, type)
            %       Add a predefined CRC profile with a specified label as a unique identifier. This
            %       label can then be mapped to mapping items. The CRC calculation is applied
            %       to the parenting CAN message and the CRC value stored to or extracted and
            %       validated from the mapped item.
            %
            %   addCrcProfile(configObj, label, type, customFile, customFunction)
            %       Add a custom CRC profile with a specified label as a unique identifier. For this
            %       the 'type' parameter must be set to 'Custom'. Check the CAN Custom CRC Usage
            %       Notes for more information about the 'customFile' and 'customFunction'
            %       arguments.
            %
            %   Examples
            %   --------
            %   Add a predefined CRC message protection profile based on the CRC8-SAEJ1850
            %   algorithm:
            %       configObj.addCrcProfile('CRC_1_8-bit', 'CRC8-SAEJ1850');
            %
            %   Add a custom 12-bit CRC message protection profile:
            %       configObj.addCrcProfile('CRC_1_12-bit', 'Custom', 'customCrc.cpp', ...
            %           'customCrc12BitFnc');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which a CRC profile is added.
            %
            %   label - Unique label of the CRC profile
            %       character vector | string
            %       Label used to identify the CRC profile in mapping operations.
            %
            %   type - CRC profile type
            %       character vector | string
            %       CRC algorithm identifier. Use 'Custom' to define a custom CRC implementation.
            %
            %   customFile - Name of a custom CRC source file
            %       character vector | string
            %       Required only when type is 'Custom'. Specify a .c or .cpp file available on
            %       the MATLAB path.
            %
            %   customFunction - Name of a custom CRC function
            %       character vector | string
            %       Required only when type is 'Custom'. Specify the function implemented in
            %       customFile.
            
            arguments
                configObj
                label {mustBeText}
                type {mustBeText}
                customFile {mustBeText} = ''
                customFunction {mustBeText} = ''
            end

            addCrcProfile@sg.public.can.DbParserBlockConfig(configObj, label, type, customFile, ...
                customFunction);
        end

        function removeCrcProfile(configObj, label)
            % removeCrcProfile - Remove a CRC message protection profile using its label
            %
            %   Description
            %   -----------
            %   removeCrcProfile(configObj, label)
            %      Remove a previously defined CRC profile by using its specified unique label.
            %      Mapping items with this label as a mapped signal will be cleared to
            %      'Ground (0)'.
            %
            %   Examples
            %   --------
            %   Remove a previously defined CRC message protection profile:
            %       configObj.removeCrcProfile('CRC_1_8-bit');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the CRC profile is removed.
            %
            %   label - Unique label of the CRC profile to remove
            %       character vector | string
            %       Label of a previously configured CRC profile.

            arguments
                configObj
                label {mustBeText}
            end

            removeCrcProfile@sg.public.can.DbParserBlockConfig(configObj, label);
        end

        function addCounterProfile(configObj, label, startValue, stopValue, stepValue, bitLength)
            % addCounterProfile - Add a Counter Message Protection profile
            %
            %   Description
            %   -----------
            %   addCounterProfile(configObj, label, startValue, stopValue, stepValue, bitLength)
            %       Add a custom Counter profile with a specified label as a unique identifier. This
            %       label can then be mapped to mapping items. The Counter value is inserted
            %       to or extracted and validated from the mapped item.
            %
            %   Examples
            %   --------
            %   Add a custom Counter profile:
            %       configObj.addCounterProfile('Counter_1_16-bit', 0, 255, 2, 16);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which a Counter profile is added.
            %
            %   label - Unique label of the Counter profile
            %       character vector | string
            %       Label used to identify the Counter profile in mapping operations.
            %
            %   startValue - Start value of the Counter sequence
            %       numeric
            %       Initial value used for Counter progression.
            %
            %   stopValue - Stop value of the Counter sequence
            %       numeric
            %       Upper bound of the Counter progression before wrap-around.
            %
            %   stepValue - Step increment of the Counter sequence
            %       numeric
            %       Increment applied between two Counter values.
            %
            %   bitLength - Bit length of the Counter signal
            %       numeric
            %       Number of bits used to represent the Counter value.

            arguments
                configObj
                label {mustBeText}
                startValue {mustBeNumeric}
                stopValue {mustBeNumeric}
                stepValue {mustBeNumeric}
                bitLength {mustBeNumeric}
            end
            
            addCounterProfile@sg.public.can.DbParserBlockConfig(configObj, label, startValue, ...
                stopValue, stepValue, bitLength);
        end

        function removeCounterProfile(configObj, label)
            % removeCounterProfile - Remove a Counter message protection profile using its label
            %
            %   Description
            %   -----------
            %   removeCounterProfile(configObj, label)
            %      Remove a previously defined Counter profile by using its specified unique label.
            %      Mapping items with this label as a mapped signal will be cleared to
            %      'Ground (0)'.
            %
            %   Examples
            %   --------
            %   Remove a previously defined Counter message protection profile:
            %       configObj.removeCounterProfile('Counter_1_16-bit');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the Counter profile is
            %       removed.
            %
            %   label - Unique label of the Counter profile to remove
            %       character vector | string
            %       Label of a previously configured Counter profile.

            arguments
                configObj
                label {mustBeText}
            end
            
            removeCounterProfile@sg.public.can.DbParserBlockConfig(configObj, label);
        end

        function messages = getMessage(configObj, messageIdentifier, value)
            % getMessage - Get message structs for a specified identifier
            %
            %   Description
            %   -----------
            %   messages = getMessage(configObj, messageIdentifier, value)
            %   messages = getMessage(configObj, 'All')
            %       The getMessage method returns one or more message structs from the selected
            %       database based on the specified identifier and value.
            %
            %   Examples
            %   --------
            %   Get message structs for messages with a specified ID:
            %       messages = configObj.getMessage('ID', 257);
            %
            %   Get message structs for messages with a specified message name:
            %       messages = configObj.getMessage('Name', 'CANMsg1');
            %
            %   Get message structs for messages containing a specified signal name:
            %       messages = configObj.getMessage('SignalName', 'CANSignal1');
            %
            %   Get message structs for all messages in the selected .dbc file:
            %       messages = configObj.getMessage('All');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance from which messages are retrieved.
            %
            %   messageIdentifier - Message identifier filter
            %       character vector | string
            %       Identifier used to filter messages. Supported values are:
            %           'ID'         - Match CAN messages by message ID.
            %           'Name'       - Match CAN messages by message name.
            %           'SignalName' - Match CAN messages containing the signal name.
            %           'All'        - Return all CAN messages in the selected database.
            %
            %   value - Filter value for the selected message identifier
            %       numeric | character vector | string
            %       Value associated with messageIdentifier. This input is ignored when
            %       messageIdentifier is 'All'.
            %
            %   Output Arguments
            %   ----------------
            %   messages - Matching message structs
            %       struct | array of structs
            %       Struct array of messages that match the requested identifier value.

            arguments (Input)
                configObj
                messageIdentifier {mustBeMember(messageIdentifier, {'ID', 'Name', ...
                    'SignalName', 'All'})}
                value = ''
            end

            messages = getMessage@sg.public.can.DbParserBlockConfig(configObj, ...
                messageIdentifier, value);
        end

        function setEnable(configObj, messages, action)
            % setEnable - Enable or disable one or more messages for transmitting or receiving
            %
            %   Description
            %   -----------
            %   setEnable(configObj, messages, action)
            %       The setEnable method enables or disables specified messages for transmitting
            %       on a CAN DB Parser Write block or receiving on a CAN DB Parser Read block.
            %
            %   Examples
            %   --------
            %   Enable a single message:
            %       configObj.setEnable(message, true)
            %
            %   Disable a subset of a message struct array:
            %       configObj.setEnable(messages(2:5), false)
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance in which the message is enabled or
            %       disabled.
            %
            %   messages - Messages to be enabled or disabled
            %       struct | array of structs
            %       Uniquely identifiable CAN messages exisiting in the selected database file.
            %       Messages are uniquely identified by message name and message ID, passed as a
            %       struct or array of structs with fields 'Name' and 'ID'. This message struct may
            %       be constructed manually or can be retrieved using the configObj.getMessage()
            %       method. A full struct array of all messages in the selected database file can be
            %       retrieved using the 'configObj.getParameter('Messages')'' method.
            %
            %   action - Enable or disable action
            %       numeric | logical
            %       Boolean value where true enables the messages and false disables them.

            arguments
                configObj
                messages {isstruct}
                action {mustBeNumericOrLogical}
            end

            setEnable@sg.public.can.DbParserBlockConfig(configObj, messages, action);
        end

        function mappingItems = getMappingItems(configObj, itemIdentifier, value)
            % getMappingItems - Get mapping item structs for a specified identifier
            %
            %   Description
            %   -----------
            %   mappingItems = getMappingItems(configObj, itemIdentifier, value)
            %   mappingItems = getMappingItems(configObj, 'All')
            %       The getMappingItems method returns one or more mapping item structs from the
            %       selected database based on the specified identifier and value.
            %
            %   Examples
            %   --------
            %   Get mapping items for CAN messages with a specified ID:
            %       mappingItems = configObj.getMappingItems('ID', 257);
            %
            %   Get mapping items containing a specified signal name:
            %       mappingItems = configObj.getMappingItems('SignalName', 'CANSignal1');
            %
            %   Get mapping items mapped to a specific input item:
            %       mappingItems = configObj.getMappingItems('MappedSignal', 'CRC_1_8-bit');
            %
            %   Get mapping items of all enabled items:
            %       mappingItems = configObj.getMappingItems('All');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance from which mapping items are 
            %       retrieved.
            %
            %   itemIdentifier - Mapping item filter identifier
            %       character vector | string
            %       Identifier used to filter mapping items. Supported values are:
            %           'ID'                - Match mapping items by CAN message ID.
            %           'Name'              - Match mapping items by CAN message name.
            %           'SignalName'        - Match mapping items by signal name.
            %           'MappedSignal'   - Match mapping items by mapped input item name.
            %           'All'               - Return mapping items for all enabled items.
            %
            %   value - Filter value for the selected mapping item identifier
            %       numeric | character vector | string
            %       Value associated with itemIdentifier. This input is ignored when
            %       itemIdentifier is 'All'.
            %
            %   Output Arguments
            %   ----------------
            %   mappingItems - Matching mapping item structs
            %       struct | array of structs
            %       Struct array of mapping items that match the requested identifier.

            arguments (Input)
                configObj
                itemIdentifier {mustBeMember(itemIdentifier, {'ID', 'Name', 'SignalName', ...
                    'MappedSignal', 'All'})}
                value = ''
            end

            mappingItems = getMappingItems@sg.public.can.DbParserBlockConfig(configObj, ...
                itemIdentifier, value);
        end

        function setMapping(configObj, inputSignals, mappingItems)
            % setMapping - Map one or more Simulink input signals to mapping items
            %
            %   Description
            %   -----------
            %   setMapping(configObj, inputSignals, mappingItems)
            %       The setMapping method establishes a mapping between Simulink input signals or
            %       message protection labels and the corresponding mapping item. Mapping items are
            %       signals in a CAN message of the selected database file. They are uniquely
            %       identified by the CAN message name, ID and the signal name. Simulink input
            %       signals are uniquely identified by their signal name concatenated with their
            %       full bus hierarchy, delimited by a dot at each hierarchy level. Message
            %       protection labels are uniquely identified by their specified label.
            %       The setMapping method ensures that the input item and mapping item
            %       inputs are of equal length and that each mapping item is unique. The method
            %       then confirms the availability of the specified input item (Simulink input
            %       signal or message protection label) and sets the mapping.
            %
            %   Examples
            %   --------
            %   Map one Simulink input signal to one mapping item:
            %       configObj.setMapping('simulink.signal', mappingItem)
            %
            %   Map multiple Simulink input signals to each one mapping item:
            %       configObj.setMapping({'simulink.signal1', 'simulink.signal2'}, ...
            %           mappingItems(2:3))
            %
            %   Map multiple message protection labels to each one mapping item:
            %       configObj.setMapping({'CRC_1_12-bit', 'Counter_1_16-bit'}, mappingItems(4:5))
            %
            %   Clear the mapping for a mapping item by mapping it to 'Ground(0)':
            %       configObj.setMapping('Ground(0)', mappingItem)
            %
            %   Clear the mapping for all mapping items by mapping them to 'Ground(0)':
            %       configObj.setMapping('Ground(0)', configObj.getMappingItems('All'))
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which Simulink input signals or
            %       message protection labels are mapped to mapping items.
            %
            %   inputSignals - Simulink input signals or message protection labels to map
            %       character vector | cell array of character vectors | 'Ground(0)'
            %       Names of the Simulink input signals or message protection labels to be mapped to
            %       mapping items. A list of all available Simulink input signals can be retrieved
            %       with 'getParameter(configObj, 'SimulinkInputSignals')'. Equally for message
            %       protection labels 'getParameter(configObj, 'CrcProfiles', 'CounterProfiles')'
            %       can be called to retrieve all. One Simulink input signal or message protection
            %       label can be mapped to multiple mapping items. Additionally, 'Ground(0)' can be
            %       specified as a character vector to clear the mapping of a mapping item.
            %
            %   mappingItems - Mapping items in the selected database to map input items
            %       struct | array of structs
            %       Uniquely identifiable mappingItems which are signals of CAN messages exisiting
            %       in the selected database file. The mappingItems are uniquely identified by
            %       signal name, message name and message ID, passed as a struct or array of structs
            %       with fields 'SignalName', 'Name' and 'ID'. This message struct may be
            %       constructed manually or can be retrieved using the
            %       'configObj.getMappingItems()'' method. A full struct array of all messages in
            %       the selected database file can be retrieved using the
            %       'configObj.getMappingItems('All')'' method. Only one input item can be mapped
            %       to each mapping item.

            arguments
                configObj
                inputSignals {mustBeText}
                mappingItems {isstruct}
            end

            setMapping@sg.public.can.DbParserBlockConfig(configObj, inputSignals, mappingItems);
        end

        function apply(configObj, ignoreMissingInputSignals)
            % apply - Apply mapping and save data to connected CAN DB Parser Read or Write block
            %
            %   Description
            %   -----------
            %   apply(configObj)
            %   apply(configObj, ignoreMissingInputSignals)
            %       The apply method checks the validity of the mapping and builds the configured
            %       mapping on the connected CAN DB Parser Read or Write block. Further it saves
            %       persistent data of the DB Parser Block Config instance to the connected
            %       block. Input items which have been mapped but are not existing anymore, are
            %       ignored and deleted from the mapping. This avoids errors during compilation for
            %       missing Simulink input signals or message protection profiles.
            %
            %   Examples
            %   --------
            %   Apply the current mapping to the connected CAN DB Parser Read or Write block:
            %       apply(configObj);
            %
            %   Apply the current mapping to the connected CAN DB Parser Read or Write block and
            %   warn about missing input items:
            %       apply(configObj, false)
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance for which the mapping is being applied
            %       and the connected CAN DB Parser Read or Write block is being configured.
            %
            %   ignoreMissingInputSignals - Flag to ignore missing input items in the mapping
            %       logical
            %       If true (default), mapped Simulink input signals that are missing in the
            %       connected bus are cleared automatically and apply continues. If false, apply
            %       errors out when mapped Simulink input signals are missing.

            arguments
                configObj
                ignoreMissingInputSignals {mustBeNumericOrLogical} = true
            end

            apply@sg.public.can.DbParserBlockConfig(configObj, ignoreMissingInputSignals);
        end

        function save(configObj)
            % save - Save data to connected CAN DB Parser Read or Write block without applying
            %
            %   Description
            %   -----------
            %   save(configObj)
            %       The save method stores persistent data of the DB Parser Block Config
            %       instance in the connected CAN DB Parser Read or Write block. It does not apply
            %       the mapping to the connected Interface block, so the functionality of this block
            %       is not changed.
            %
            %   Examples
            %   --------
            %   Save the current instance of the DB Parser Block Config class:
            %       save(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - DB Parser Block Config instance
            %       DbParserBlockConfig
            %       The DB Parser Block Config instance from which to save data to the
            %       connected CAN DB Parser Read or Write block.

            save@sg.public.can.DbParserBlockConfig(configObj);
        end
    end
end
