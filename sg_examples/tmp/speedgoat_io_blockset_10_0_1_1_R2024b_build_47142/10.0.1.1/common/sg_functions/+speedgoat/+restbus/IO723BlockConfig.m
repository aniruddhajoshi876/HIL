% speedgoat.restbus.IO723BlockConfig - Create an IO723 Block Config instance
%
%   Description
%   -----------
%   This IO723 Block Config class constructs a class object for interacting with an IO723 
%   Read or Write Interface block in Simulink®. The Config instance is connected to the 
%   specified Interface block. Upon construction, it checks for instances of the IO723 Read or 
%   Write Interface application—these must be closed to proceed.
%
%   Several methods are available to retrieve or modify settings relevant to the functionality of 
%   the connected Interface block; these methods operate on the data managed by the Config 
%   instance itself. Only after applying or saving the Config instance, is data passed to the 
%   connected Interface block.
%
%   Some methods act on the IO723 Setup block, which itself is linked to the Interface block, 
%   referenced by the Config instance. The linked Setup block may be changed to a different 
%   one using the 'ModuleID' or 'SetupBlock' parameter of the Config instance.
%
%   Syntax
%   ------
%   Get an IO723 Block Config instance for a specified IO723 Read or Write Interface block:
%       configObj = speedgoat.restbus.IO723BlockConfig(blockPath)
%
%   Get the value for one or more specified parameters:
%       configObj.getParameter(parameter1,...,parameterN)
%
%   Set the value for one or more specified parameters:
%       configObj.setParameter(parameter1,value1,...,parameterN,valueN)
%
%   Update data from the RBS project file defined in the linked IO723 Setup block:
%       configObj.updateFromProjectFile()
%
%   Enable or disable one or more network items, global variables, or manipulation values including 
%   any underlying items:
%       configObj.setEnable(itemType, items, action)
%
%   Map one or more Simulink input signals to corresponding network signals, global variables, or 
%   manipulation values in a network:
%       configObj.setMapping(itemType, inputSignals, items)
%
%   Refresh the list of Simulink input signals on the input port of the connected IO723 Read or 
%   Write Interface block:
%       configObj.refreshSimulinkInputSignals()
%
%   Save persistent data to the connected IO723 Read or Write Interface block without applying 
%   changes:
%       configObj.save()
%
%   Apply the mapping to the connected IO723 Read or Write Interface block and save persistent data:
%       configObj.apply()
%
%   Delete the IO723 Block Config instance without saving persistent data or applying changes 
%   to the connected IO723 Read or Write Interface block:
%       configObj.delete()
%
%   Examples
%   ------
%   Get an IO723 Block Config instance and connect it to the currently selected IO723 Read or 
%   Write Interface block in a loaded Simulink model:
%       configObj = speedgoat.restbus.IO723BlockConfig(gcb)
%
%   Get an IO723 Block Config instance and connect it to the specified IO723 Read or Write 
%   Interface block in a loaded Simulink model:
%       configObj = speedgoat.restbus.IO723BlockConfig('myModel/IO723 Interface block ')
%
%   Get the sample time of the connected IO723 Read or Write Interface block:
%       sampleTime = configObj.getParameter('SampleTime')
%
%   Get the list of available Simulink input signals:
%       inputSignals = configObj.getParameter('SimulinkInputSignals')
%
%   Get the module ID of the linked IO723 Setup block:
%       moduleId = configObj.getParameter('ModuleId')
%
%   Get the list of all signal items for all networks:
%       dbItems = configObj.getParameter('SignalItems')
%
%   Get the table of all networks configurations:
%       networks = configObj.getParameter('Networks')
%
%   Set the module ID to select the IO723 Setup block to link (clears all persistent data on the 
%   connected IO723 Read or Write Interface block):
%       configObj.setParameter('ModuleId', 2)
%
%   Set the module ID to select the IO723 Setup block to link (clears all persistent data on the 
%   connected IO723 Read or Write Interface block) and the sample time:
%       configObj.setParameter('ModuleId', 2, 'SampleTime', '0.01')
%
%   Set the Setup block path directly to select the IO723 Setup block to link (clears all 
%   persistent data on the connected IO723 Read or Write Interface block):
%       configObj.setParameter('SetupBlock', 'myModel/IO723 Setup')
%
%   Set the RBS Project file to be used in the linked IO723 Setup block (also parses the project):
%        configObj.setParameter('ProjectFile', [pwd, '/myProject.fcr'])
%
%   Update from the RBS project file defined in the linked IO723 Setup block:
%       configObj.updateFromProjectFile()
%
%   Enable a single network item including underlying items:
%       configObj.setEnable('SignalItems', 'CAN.Ecu.signal', true)
%
%   Disable the mapping of a single global variable in order to use the default value from the RBS
%   project file:
%       configObj.setEnable('GlobalVariables', 'globalVar1', false)
%
%   Enable multiple network items including underlying items:
%       configObj.setEnable('SignalItems', {'CAN.Ecu1.signal1', 'CAN.Ecu1.signal2', ...
%           'CAN.Ecu2'}, true)
%
%   Map one Simulink input signal to one signal item in a network:
%       configObj.setMapping('SignalItems', 'simulink.signal', 'CAN.Ecu.signal')
%
%   Map each Simulink input signal to a single signal item in the network:
%       configObj.setMapping('SignalItems',  ...
%           {'simulink.signal1', 'simulink.signal2'}, ...
%           {'CAN.Ecu1.signal1', 'CAN.Ecu1.signal2'})
%
%   Map specific Simulink input signals and scalars to specific manipulation values:
%       configObj.setMapping('Manipulations', ...
%       {{1, 'simulink.signal1'}, {'simulink.enableSignal1', '1', '12', '3e3'}}, ...
%       {'OffsetManipulation1', 'RampManipulation1'})
%
%   Clear the mapping for a signal item in a network by mapping it to 'Ground(0)':
%       configObj.setMapping('SignalItems', 'Ground(0)', 'CAN.Ecu.signal')
%
%   Clear the mapping for manipulation values by mapping to '0':
%       configObj.setMapping('Manipulations', '0', 'RampManipulation1')
%
%   Refresh the list of Simulink input signals on the input port of the connected IO723 Read or 
%   Write Interface block:
%       configObj.refreshSimulinkInputSignals()
%
%   Save persistent data to the connected IO723 Read or Write Interface block without applying 
%   changes:
%       configObj.save()
%
%   Apply the mapping to the connected IO723 Read or Write Interface block and save persistent data:
%       configObj.apply()
%
%   Delete the IO723 Block Config instance without saving persistent data or applying changes 
%   to the connected IO723 Read or Write Interface block:
%       configObj.delete()
%
%   Input Arguments
%   ---------------
%   'blockPath' - Path to an IO723 Read or Write Simulink block 
%       [character vector | string]. 
%       The path to an IO723 Read or Write Interface block in a loaded Simulink model file.
%
%   Output Arguments
%   ----------------
%   'configObj' – Instance of the IO723 Block Config class 
%       [IO723BlockConfig]. 
%       The IO723 Block Config instance initialized for interacting with the specified IO723 
%       Read or Write Interface block. The Interface block remains connected to the Config 
%       instance until the Config instance is deleted.
%
%   Notes
%   -----
%   This constructor requires a loaded Simulink model with at least one IO723 Setup block and one 
%   IO723 Read or Write Interface block.

classdef IO723BlockConfig < sg.public.restbus.IO723BlockConfig
    methods (Access = public)
        function configObj = IO723BlockConfig(blockPath)
            % IO723BlockConfig - Constructor for the IO723 Block Config class
            %
            %   Description
            %   -----------
            %   configObj = IO723BlockConfig(blockPath)
            %       The IO723BlockConfig constructor initializes an instance of the IO723BlockConfig
            %       class for interacting with an IO723 Read or Write Interface block in Simulink.
            %       It checks for instances of the IO723 Read or Write Interface application, these
            %       must be closed to proceed.
            %
            %   Examples
            %   --------
            %   Get an IO723 Block Config instance for an IO723 Read Interface block:
            %       configObj = IO723BlockConfig('myModel/IO723 Read Interface ');
            %
            %   Input Arguments
            %   ---------------
            %   blockPath - Path to an IO723 Read or Write Interface Simulink block
            %       character vector | string
            %       The path to an IO723 Read or Write Interface Simulink block. The corresponding
            %       Simulink model must be loaded or opened first.
            %
            %   Output Arguments
            %   ----------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance initialized for interacting with the
            %       specified IO723 Read or Write Interface block. The Interface block remains
            %       connected to the Config instance until the Config instance is
            %       deleted.

            arguments
                blockPath{mustBeText}
            end

            configObj@sg.public.restbus.IO723BlockConfig(blockPath);
        end

        function delete(configObj)
            % delete - Destructor for the IO723 Block Config class
            %
            %   Description
            %   -----------
            %   delete(configObj)
            %       The delete method prepares the IO723 Block Config instance for deletion.
            %       Any unsaved changes are discarded. No data is saved to the connected IO723 Read
            %       or Write Interface block, nor is the mapping applied to this block. To save the
            %       changes made using this Config instance, call configObj.save() before
            %       deleting. To save and apply the changes made using this Config instance,
            %       call configObj.apply() before deleting.
            %
            %   Examples
            %   --------
            %   Delete an instance of the IO723 Block Config class:
            %       delete(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance to be deleted.

            delete@sg.public.restbus.IO723BlockConfig(configObj);
        end
    end

    methods (Access = public)
        function param = getParameter(configObj, paramName)
            % getParameter - Get the value for one or more specified parameters
            %
            %   Description
            %   -----------
            %   getParameter(configObj, 'ParameterName1', ..., 'ParameterNameN')
            %       The getParameter function gets the value of one or more specified parameters. It
            %       supports several predefined parameters and returns the corresponding value in
            %       either the default format for this parameter or as a cell array for multiple
            %       requested parameters.
            %
            %   Examples
            %   --------
            %   Get the module ID of the linked IO723 Setup block:
            %       moduleId = configObj.getParameter('ModuleId')
            %
            %   Retrieve the list of Simulink input signals:
            %       inputSignals = getParameter(configObj, 'SimulinkInputSignals');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which the parameter value is being
            %       retrieved.
            %
            %   ParameterName - Name of the parameter to retrieve
            %       character vector | string
            %       Name of the parameter to retrieve. Supported values are:
            %           'BlockPath'            - Block path of the connected Interface block.
            %           'SimulinkInputSignals' - List of Simulink input signals.
            %           'SetupBlockOptions'    - Table of available Setup blocks to link.
            %           'Networks'             - Table of network configurations.
            %           'SampleTime'           - Sample time of the connected Interface block.
            %           'ModuleId'             - Module ID of the linked Setup block.
            %           'SetupBlock'           - Path of the linked Setup block.
            %           'SignalItems'          - List of all signal items in all networks.
            %           'ProjectFile'          - RBS project file path from the linked Setup block.
            %           'GlobalVariables'      - Table of global variables in this RBS project file.
            %           'Manipulations'        - Table of manipulations in this RBS project file.
            %           'Sequences'            - Table of sequences in this RBS project file.
            %           'SequenceControl'      - Control signal or value for sequences.
            %           'ManipulationValueMode'- Control if mapped or project file values are used
            %                                    for manipulations.
            %
            %   Output Arguments
            %   ----------------
            %   param - Result value
            %       numeric | character vector | cell array of character vectors
            %       Output values of the specified parameters.

            arguments(Input)
                configObj
            end

            arguments(Input, Repeating)
                paramName{mustBeMember(paramName, {'BlockPath', 'SimulinkInputSignals', ...
                    'SetupBlockOptions', 'Networks', 'SampleTime', 'ModuleId', 'SetupBlock', ...
                    'SignalItems', 'ProjectFile', 'GlobalVariables', 'Manipulations', ...
                    'Sequences', 'SequenceControl', 'ManipulationValueMode'})}
            end

            param = getParameter@sg.public.restbus.IO723BlockConfig(configObj, paramName{:});
        end

        function setParameter(configObj, paramName, param)
            % setParameter - Set the value for one or more specified parameters
            %
            %   Description
            %   -----------
            %   setParameter(configObj, 'ParameterName1', Value1, 'ParameterName2', Value2, ...)
            %       Values of various parameters can be set using the setParameter function. It
            %       parses input name-value pairs, validates data types, and triggers corresponding
            %       update functions based on the specified parameter.
            %
            %   Examples
            %   --------
            %   Link the connected IO723 Read or Write Interface block to the IO723 Setup block
            %   identified by ID 2 and configure the sample time to 0.01s:
            %       setParameter(configObj, 'ModuleId', 2, 'SampleTime', '0.01');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which parameters are being set.
            %
            %   Optional Name-Value Pair Arguments
            %   ----------------------------------
            %   'ModuleId' - Identifier for a unique IO723 I/O module and IO723 Setup block to link
            %       numeric | character vector | string
            %       Module ID of an IO723 Setup block existing in this model. Triggers an update to
            %       the 'SetupBlock', 'ProjectFile', 'Networks', 'SignalItems', 'GlobalVariables',
            %       'Manipulations' and 'Sequences' parameters. This updating process will delete
            %       any persistent data and previous mapping done on the connected IO723 Read or
            %       Write Interface block. The specified Setup block is then linked to the connected
            %       Interface block after completing the update process. Any previous linked Setup
            %       block is discarded.
            %
            %   'SetupBlock' - Path of a unique IO723 Setup block to link
            %       character vector | string
            %       Path of an IO723 Setup block existing in this model. Triggers an update to the
            %       'ModuleId', 'ProjectFile', 'Networks', 'SignalItems', 'GlobalVariables',
            %       'Manipulations' and 'Sequences' parameters. This updating process will delete
            %       any persistent data and previous mapping done on the connected IO723 Read or
            %       Write Interface block. The specified Setup block is then linked to the connected
            %       Interface block after completing the update process. Any previous linked Setup
            %       block is discarded.
            %
            %   'SampleTime' - IO723 Read or Write Interface block sample time
            %       numeric | character vector | string
            %       Sample time at which the connected IO723 Read or Write Interface block is
            %       executed. Determines the update rate of signal data.
            %
            %   'ProjectFile' - Path to RBS project file
            %       character vector | string
            %       Path to the RBS project file to be used in the linked IO723 Setup block.
            %       Triggers parsing and updating of RBS project file data.
            %
            %   'SequenceControl' - Control signal or scalar value for sequences
            %       character vector | string | numeric
            %       The value on this parameter controls which sequence is active if any. Sequences
            %       are identified by their ID specified in the sequence table
            %       'getParameter('Sequences')'. Either a Simulink input signal
            %       'getParameter('SimulinkInputSignals')' or a scalar may be assigned to the
            %       SequenceControl parameter. Specifying a value of 0 turns all sequences off.
            %
            %   'ManipulationValueMode' - Control value for value mode on manipulations
            %       character vector | string
            %       Either 'Mapping' or 'Project File' mode to control the values used for
            %       manipulations. On 'Mapping' mode, the values mapped for manipulations are used
            %       as such. On 'Project File' mode, these mappings are ignored and the default
            %       values from the RBS project file are used.

            arguments(Input)
                configObj
            end

            arguments(Input, Repeating)
                paramName{mustBeMember(paramName, ...
                    {'ModuleId', 'SetupBlock', 'SampleTime', 'ProjectFile', 'SequenceControl', ...
                    'ManipulationValueMode'})}
                param
            end

            setParameter@sg.public.restbus.IO723BlockConfig(configObj, paramName{:}, param{:});
        end

        function setEnable(configObj, itemType, items, action)
            % setEnable - Enable or disable one or more network items or global variables
            %
            %   Description
            %   -----------
            %   setEnable(configObj, itemType, items, action)
            %       The setEnable function enables or disables specified network items including
            %       all underlying items. Network items are uniquely identified using the hierarchy
            %       inside the network by concatenating network item names with a dot delimiter,
            %       starting from the network name. The underlying items are all network items at a
            %       lower level in the hierarchy, parented by the specified network item.
            %
            %       Global variables and manipulations can be enabled or disabled by specifying
            %       their name. For global variables this enables overwriting default values defined
            %       in the RBS project file. For manipulations this sets the 'EnableSignal' to
            %       control if the manipulation is active '1' or not '0'.
            %
            %   Examples
            %   --------
            %   Enable multiple network items including underlying items:
            %       configObj.setEnable('NetworkItems', ...
            %           {'CAN.Ecu1.signal1', 'CAN.Ecu1.signal2', 'CAN.Ecu2'}, true)
            %
            %   Disable a single network item including underlying items:
            %       configObj.setEnable('NetworkItems', 'CAN.Ecu.signal', false)
            %
            %   Enable one global variable:
            %       configObj.setEnable('GlobalVariables', 'globalVar1', true)
            %
            %   Disable one manipulation:
            %       configObj.setEnable('Manipulations', 'OffsetManipulation1', false)
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance in which the network item, global variable or
            %       manipulation is enabled or disabled.
            %
            %   itemType - Specifier for what type of item is to be enabled or disabled
            %       character vector | string
            %       'NetworkItems', 'GlobalVariables' and 'Manipulations' are available.
            %
            %   items - Network items, global variables or manipulations to be enabled or disabled
            %       character vector | cell array of character vectors | table
            %       Uniquely identifiable hierarchy name paths, global variable or manipulation
            %       names of the items whose enable state is modified. A table of the network
            %       hierarchy can be retrieved with 'getParameter(configObj, 'Networks')'. A table
            %       of global variable can be retrieved with 'getParameter(configObj, ...
            %       'GlobalVariables')'. A table of manipulations can be retrieved with
            %       'getParameter(configObj, 'Manipulations')'.
            %
            %   action - Enable or disable action
            %       numeric | logical
            %       Boolean value where true enables the items and false disables them.

            arguments
                configObj
                itemType {mustBeMember(itemType, {'NetworkItems', 'GlobalVariables', ...
                    'Manipulations'})}
                items{mustBeText}
                action{mustBeNumericOrLogical}
            end

            setEnable@sg.public.restbus.IO723BlockConfig(configObj, itemType, items, action);
        end

        function setMapping(configObj, itemType, inputSignals, items)
            % setMapping - Map Simulink input signals to network signal items, global variables or
            %              manipulations
            %
            %   Description
            %   -----------
            %   setMapping(configObj, itemType, inputSignals, signalItems)
            %       The setMapping function establishes a mapping between Simulink input signals and
            %       the corresponding items of the RBS project file.
            %
            %       Items of type 'SignalItems' are items in a network on the lowest hierarchy level
            %       and therefore have no underlying network items. They are uniquely identified
            %       using the hierarchy inside the network by concatenating network item names with
            %       a dot delimiter, starting from the network name.
            %
            %       Items of type 'GlobalVariables' can be mapped to Simulink input signals by
            %       specifying their name.
            %
            %       Items of type 'Manipulations' can be mapped to Simulink input signals by
            %       specifying their name. Depending on the type of manipulation, 1 to 4 input
            %       signals can be mapped to its values (e.g. 'Freeze' has only one 1 map-able
            %       value, 'Ramp' has 4 map-able values). The order of values is always -
            %       'EnableSignal', 'Value1', 'Value2', 'Value3'. Alternatively to Simulink input
            %       signals, scalar values can be mapped to manipulation values.
            %
            %       The setMapping function ensures that the Simulink input signal and item inputs
            %       are of equal length and that each passed item is unique. The function then
            %       confirms the availability of the specified items and Simulink input signals and
            %       sets the mapping, providing warnings for any issues encountered.
            %
            %   Examples
            %   --------
            %   Map one Simulink input signal to one signal item in a network:
            %       configObj.setMapping('SignalItems', 'simulink.signal', 'CAN.Ecu.signal')
            %
            %   Map multiple Simulink input signals to each one signal item in a network:
            %       configObj.setMapping('SignalItems', ...
            %           {'simulink.signal1', 'simulink.signal2'}, ...
            %           {'CAN.Ecu1.signal1', 'CAN.Ecu1.signal2'})
            %
            %   Map some Simulink input signals and scalars to some manipulation values:
            %       configObj.setMapping('Manipulations', ...
            %           {{1, 'simulink.signal1'}, {'simulink.enableSignal1', '1', '12', '3e3'}}, ...
            %           {'OffsetManipulation1', 'RampManipulation1'})
            %
            %   Clear the mapping for a signal item in a network by mapping it to 'Ground(0)':
            %       configObj.setMapping('SignalItems', 'Ground(0)', 'CAN.Ecu.signal')
            %
            %   Clear the mapping for all signal items in all networks by mapping them to 
            %   'Ground(0)':
            %       configObj.setMapping('SignalItems', 'Ground(0)', ...
            %           getParameter(configObj, 'SignalItems'))
            %
            %   Map one Simulink input signal to one global variable:
            %       configObj.setMapping('GlobalVariables', 'simulink.signal', 'globalVar1')
            %
            %   Clear the mapping for one global variable:
            %       configObj.setMapping('GlobalVariables', 'Ground(0)', 'globalVar1')
            %
            %   Clear the mapping for all values in a manipulation by mapping it to '0':
            %       configObj.setMapping('Manipulations', '0', 'RampManipulation1')
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which Simulink input signals are mapped to
            %       signal items or global variables.
            %
            %   itemType - Specifier for what type of item is to be enabled or disabled
            %       character vector | string
            %       'SignalItems', 'GlobalVariables' and 'Manipulations' are available.
            %
            %   inputSignals - Simulink input signals or scalars to map to items
            %       character vector | numeric | cell array of character vectors or numeric
            %       Names of the Simulink input signals to be mapped to items. A list of all
            %       available input signals can be retrieved with 'getParameter(configObj,
            %       'SimulinkInputSignals')'. One Simulink input signal can be mapped to multiple
            %       items. Additionally, 'Ground(0)' can be specified as a character vector to clear
            %       the mapping of an item.
            %       1 to 4 inputSignals can be passed for items of type 'Manipulation', depending on
            %       the amount of values for this manipulation type (e.g. 'Freeze' has only one 1
            %       map-able value, 'Ramp' has 4 map-able values). The order of values is always -
            %       'EnableSignal', 'Value1', 'Value2', 'Value3'. Alternatively to Simulink input
            %       signals, scalar values can be mapped to manipulation values. These input signals
            %       or scalar values per manipulation must be passed in a nested cell array to group
            %       the values.
            %
            %   items - Signal items, global variables or manipulations to map input signals to
            %       character vector | cell array of character vectors
            %       Uniquely identifiable hierarchy name paths, global variable or manipulation
            %       names of the items to map input signals to. A table of the network hierarchy
            %       can be retrieved with 'getParameter(configObj, 'Networks')'. A table of global
            %       variable can be retrieved with 'getParameter(configObj, 'GlobalVariables')'.
            %       A table of manipulations can be retrieved with 'getParameter(configObj, ...
            %       'Manipulations')'.

            arguments
                configObj
                itemType {mustBeMember(itemType, {'SignalItems', 'GlobalVariables', ...
                    'Manipulations'})}
                inputSignals
                items{mustBeText}
            end

            setMapping@sg.public.restbus.IO723BlockConfig(configObj, itemType, inputSignals, ...
                items);
        end

        function setUsePhysical(configObj, items, action)
            % setUsePhysical - Set physical or non-physical mode for signal items in a network:
            %
            %   Description
            %   -----------
            %   setUsePhysical(configObj, signalItems, action)
            %       The setUsePhysical function sets the pysical or non-physical interpretation mode
            %       for a signal item in a network. This defines how Simulink input signals are
            %       packed into the payload or unpacked from the payload of the signal item.
            %       Physical interpretation mode requires the mapped Simulink input signal to be a
            %       double datatype. Non-physical interpretation mode accepts various datatypes for
            %       the mapped Simulink input signal.
            %       Not all signal items in a network have a physical interpretation mode defined.
            %       These may not be set to physical and will issue a warning if tried to.
            %       Signal items are on the lowest hierarchy level and therefore have no underlying
            %       network items. They are uniquely identified using the hierarchy inside the
            %       network by concatenating network item names with a dot delimiter, starting from
            %       the network name.
            %
            %   Examples
            %   --------
            %   Set a signal item in a network to use physical interpretation:
            %       configObj.setUsePhysical('CAN.Ecu.signal', true)
            %
            %   Set multiple signal items in a network to use non-physical interpretation:
            %       configObj.setUsePhysical({'CAN.Ecu1.signal1', 'CAN.Ecu1.signal2'}, false)
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which physical or non-physical
            %       interpretation mode of signal items is edited.
            %
            %   signalItems - Signal items in a network to set physical or non-physical mode
            %       character vector | cell array of character vectors
            %       Uniquely identifiable hierarchy name paths of the signal items for which
            %       physical or non-physical interpretation mode is set. A list of all available
            %       signal items can be retrieved with 'getParameter(configObj, 'SignalItems')'.

            arguments
                configObj
                items{mustBeText}
                action{mustBeNumericOrLogical}
            end

            setUsePhysical@sg.public.restbus.IO723BlockConfig(configObj, items, action);
        end

        function refreshSimulinkInputSignals(configObj)
            % refreshSimulinkInputSignals - Refresh the list of Simulink input signals
            %
            %   Description
            %   -----------
            %   refreshSimulinkInputSignals(configObj)
            %       The refreshSimulinkInputSignals function updates the list of Simulink input
            %       signals on the input port of the connected IO723 Read or Write Interface block.
            %       It checks if the connected Simulink bus signal is valid, issuing a warning if it
            %       is not.
            %
            %   Examples
            %   --------
            %   Refresh the list of Simulink input signals on the input port of the connected IO723
            %   Read or Write Interface block:
            %       refreshSimulinkInputSignals(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which the Simulink input signals list
            %       is being refreshed.

            refreshSimulinkInputSignals@sg.public.restbus.IO723BlockConfig(configObj);
        end

        function updateFromProjectFile(configObj)
            % updateFromProjectFile - Update from project file in the linked IO723 Setup block
            %
            %   Description
            %   -----------
            %   updateFromProjectFile(configObj)
            %       The updateFromProjectFile function updates the network data of the IO723 Block
            %       Config instance from the RBS project file defined in the linked IO723
            %       Setup block. This triggers the RBS project file update process that can also be
            %       issued from the linked Setup block.
            %       Previously enabled or mapped signals keep their configuration if they are still
            %       present in the updated RBS project file.
            %
            %   Examples
            %   --------
            %   Update network data from the RBS project file defined in the linked IO723 Setup
            %   block:
            %       updateFromProjectFile(configObj)
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance that is updated from the RBS project file.

            updateFromProjectFile@sg.public.restbus.IO723BlockConfig(configObj);
        end

        function save(configObj)
            % save - Save data to connected IO723 Read or Write Interface block without applying
            %
            %   Description
            %   -----------
            %   save(configObj)
            %       The save method stores persistent data of the IO723 Block Config instance
            %       in the connected IO723 Read or Write Interface block. It does not apply the
            %       mapping to the connected Interface block, so the functionality of this block is
            %       not changed.
            %
            %   Examples
            %   --------
            %   Save the current instance of the IO723 Block Config class:
            %       save(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance from which to save data to the connected
            %       IO723 Read or Write Interface block.

            save@sg.public.restbus.IO723BlockConfig(configObj);
        end

        function apply(configObj)
            % apply - Apply mapping and save data to connected IO723 Read or Write Interface block
            %
            %   Description
            %   -----------
            %   apply(configObj)
            %       The apply function checks the validity of the mapping and builds the configured
            %       mapping on the connected IO723 Read or Write Interface block. Further it saves
            %       persistent data of the IO723 Block Config instance to the connected 
            %       Interface block.
            %
            %   Examples
            %   --------
            %   Apply the current mapping to the connected IO723 Read or Write Interface block:
            %       apply(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - IO723 Block Config instance
            %       IO723BlockConfig
            %       The IO723 Block Config instance for which the mapping is being applied and
            %       the connected IO723 Read or Write Interface block is being configured.

            apply@sg.public.restbus.IO723BlockConfig(configObj);
        end
    end
end
