% speedgoat.can.DbManagerConfig - Create a Database Manager Config instance
%
%   Description
%   -----------
%   This Database Manager Config class constructs a class object for managing .dbc database 
%   files configured for a Simulink® model. The Config instance is connected to the specified 
%   model. Upon construction, it checks for running instances of the Database Manager Config class 
%   for the same model - these must be closed to proceed.
%
%   Several methods are available to retrieve or modify the configured database options; these 
%   methods operate on the data managed by the Config instance itself. Only after saving the 
%   Config instance is data passed to the connected model.
%
%   Syntax
%   ------
%   Get a Database Manager Config instance for a specified model:
%       configObj = speedgoat.can.DbManagerConfig(modelPath)
%
%   Get the value for one or more specified parameters:
%       configObj.getParameter(parameter1,...,parameterN)
%
%   Add a new .dbc database file:
%       configObj.addDatabase(dbcName)
%
%   Set or update the path of a configured .dbc database file:
%       configObj.setDatabasePath(dbcName, newPath)
%
%   Remove a configured .dbc database file:
%       configObj.removeDatabase(dbcName)
%
%   Generate a Simulink library from a specified configured .dbc database file:
%       configObj.generateSlxLibrary(dbcName, destination)
%
%   Generate Simulink libraries for all configured .dbc database files:
%       configObj.generateAllSlxLibraries(destination)
%
%   Save persistent data to the connected model:
%       configObj.save()
%
%   Delete the Database Manager Config instance without saving persistent data:
%       configObj.delete()
%
%   Examples
%   --------
%   Get a Database Manager Config instance and connect it to a loaded Simulink model:
%       configObj = speedgoat.can.DbManagerConfig('myModel')
%
%   Get the table of configured .dbc files and related information:
%       databaseOptions = configObj.getParameter('DatabaseOptions')
%
%   Add a .dbc file not on the MATLAB™ path or current folder to the model database options:
%       configObj.addDatabase('C:\myDatabases\powertrain.dbc')
%
%   Add a .dbc file on the MATLAB path or current folder to the model database options:
%       configObj.addDatabase('batteryManagement.dbc')
%
%   Update the path of a configured .dbc file:
%       configObj.setDatabasePath('powertrain.dbc', 'D:\project\dbc\powertrain.dbc')
%
%   Remove a configured .dbc file:
%       configObj.removeDatabase('powertrain.dbc')
%
%   Generate a Simulink library for one configured .dbc file in the current folder:
%       configObj.generateSlxLibrary('powertrain.dbc')
%
%   Generate a Simulink library for one configured .dbc file in a specified destination:
%       configObj.generateSlxLibrary('powertrain.dbc', 'C:\temp\libraries')
%
%   Generate Simulink libraries for all configured .dbc files in a specified destination:
%       configObj.generateAllSlxLibraries('C:\temp\libraries')
%
%   Save persistent database options to the connected model:
%       configObj.save()
%
%   Delete the Database Manager Config instance without saving persistent data:
%       configObj.delete()
%
%   Input Arguments
%   ---------------
%   modelPath - Path or name of a Simulink model
%       [character vector | string].
%       The path or name of a Simulink model for which CAN database options are managed.
%
%   Output Arguments
%   ----------------
%   configObj - Instance of the Database Manager Config class
%       [DbManagerConfig]
%       The Database Manager Config instance initialized for interacting with the specified 
%       model. The model remains connected to the Config instance until the Config 
%       instance is deleted.
%
%   Notes
%   -----
%   This constructor requires a loaded Simulink model. Only one Database Manager Config 
%   instance per model can run at a time.

classdef DbManagerConfig < sg.public.can.DbManagerConfig
    methods (Access = public)
        function configObj = DbManagerConfig(modelPath)
            % DbManagerConfig - Constructor for the Database Manager Config class
            %
            %   Description
            %   -----------
            %   configObj = speedgoat.can.DbManagerConfig(modelPath)
            %       The DbManagerConfig constructor initializes an instance of the DbManagerConfig 
            %       class for managing CAN database files associated to a Simulink model. It checks 
            %       for existing instances of the Database Manager Config for this model; 
            %       these must be closed to proceed.
            %
            %   Examples
            %   --------
            %   Get a Database Manager Config instance for a Simulink model:
            %       configObj = speedgoat.can.DbManagerConfig('myModel');
            %
            %   Input Arguments
            %   ---------------
            %   modelPath - Path or name of a Simulink model
            %       character vector | string
            %       The path or name of a Simulink model. The corresponding model must be loaded
            %       or opened first.
            %
            %   Output Arguments
            %   ----------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance initialized for interacting with the
            %       specified model. The model remains connected to the Config instance until 
            %       the Config instance is deleted.

            arguments
                modelPath {mustBeText}
            end

           configObj@sg.public.can.DbManagerConfig(modelPath);
        end

        function delete(configObj)
            % delete - Destructor for the Database Manager Config class
            %
            %   Description
            %   -----------
            %   delete(configObj)
            %       The delete method prepares the Database Manager Config instance for 
            %       deletion. Any unsaved changes are discarded and no data is saved to the 
            %       connected model. To save the changes made using this Config instance, 
            %       call configObj.save() before deleting.
            %
            %   Examples
            %   --------
            %   Delete an instance of the Database Manager Config class:
            %       delete(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance to be deleted.

            delete@sg.public.can.DbManagerConfig(configObj);
        end
    end

    methods (Access = public)
        function param = getParameter(configObj, paramName)
            % getParameter - Get the value for one or more specified parameters
            %
            %   Description
            %   -----------
            %   getParameter(configObj, 'ParameterName1', ..., 'ParameterNameN')
            %       The getParameter function gets the value of one or more specified parameters.
            %       It supports predefined parameter names and returns the corresponding value in
            %       either the default format for this parameter or as a cell array for multiple
            %       requested parameters.
            %
            %   Examples
            %   --------
            %   Get the table of configured .dbc files and status of generated .slx files:
            %       databaseOptions = configObj.getParameter('DatabaseOptions');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which the parameter value is 
            %       being retrieved.
            %
            %   ParameterName - Name of the parameter to retrieve
            %       character vector | string
            %       Name of the parameter to retrieve. Supported value is:
            %           'DatabaseOptions' - Table of configured .dbc files and library status.
            %
            %   Output Arguments
            %   ----------------
            %   param - Result value
            %       table | cell
            %       Output value of the specified parameter.

            arguments(Input)
                configObj
            end

            arguments(Input, Repeating)
                paramName {mustBeMember(paramName, {'DatabaseOptions'})}
            end

            param = getParameter@sg.public.can.DbManagerConfig(configObj, paramName{:});
        end

        function addDatabase(configObj, dbcName)
            % addDatabase - Add a .dbc database file to the model configuration
            %
            %   Description
            %   -----------
            %   addDatabase(configObj, dbcName)
            %       The addDatabase function adds a .dbc file to the database configuration of the
            %       connected model. The .dbc file can be specified as a full path or by file name
            %       if it is available on the MATLAB path or the current working folder.
            %
            %   Examples
            %   --------
            %   Add a .dbc file using a full path:
            %       configObj.addDatabase('C:\myDatabases\powertrain.dbc');
            %
            %   Add a .dbc file available on the MATLAB path or current working folder:
            %       configObj.addDatabase('batteryManagement.dbc');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which a .dbc file is added.
            %
            %   dbcName - Path or file name of a .dbc file
            %       character vector | string
            %       .dbc file path or file name to add to the model database configuration.
            %
            %   Notes
            %   -----
            %   There are several cases in which the addDatabase method can fail and the .dbc file
            %   cannot be added:
            %       - The same .dbc file is already configured.
            %       - The file cannot be found or parsed as a valid CAN(-FD) database file.
            %       - The .dbc file does not define a protocol type; no BusType and no message
            %         ProtocolMode.
            %       - The .dbc file declares BusType CAN but contains CAN FD messages.
            %
            %   Duplicate file names on the MATLAB path or in the current folder can also trigger
            %   shadowing warnings; these warnings are non-fatal and do not necessarily block adding
            %   the selected file.

            arguments (Input)
                configObj
                dbcName {mustBeText}
            end

            addDatabase@sg.public.can.DbManagerConfig(configObj, dbcName);
        end

        function setDatabasePath(configObj, dbcName, newPath)
            % setDatabasePath - Set or update the path of a configured .dbc database file
            %
            %   Description
            %   -----------
            %   setDatabasePath(configObj, dbcName, newPath)
            %       The setDatabasePath function updates the file path of a configured .dbc file
            %       in the connected model. The configured database name remains unchanged.
            %
            %   Examples
            %   --------
            %   Update the path of a configured .dbc file:
            %       configObj.setDatabasePath('powertrain.dbc', 'D:\project\dbc\powertrain.dbc');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which a .dbc file path is 
            %       updated.
            %
            %   dbcName - Name of the configured .dbc file
            %       character vector | string
            %       Name of the .dbc entry in the current database configuration.
            %
            %   newPath - New .dbc file path
            %       character vector | string
            %       New path to the .dbc file for the specified configured database entry.

            arguments (Input)
                configObj
                dbcName {mustBeText}
                newPath {mustBeText}
            end

            setDatabasePath@sg.public.can.DbManagerConfig(configObj, dbcName, newPath);
        end

        function removeDatabase(configObj, dbcName)
            % removeDatabase - Remove a configured .dbc database file
            %
            %   Description
            %   -----------
            %   removeDatabase(configObj, dbcName)
            %       The removeDatabase function removes a previously configured .dbc file from the
            %       database options of the connected model.
            %
            %   Examples
            %   --------
            %   Remove a configured .dbc file:
            %       configObj.removeDatabase('powertrain.dbc');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which a .dbc file is removed.
            %
            %   dbcName - Name of the configured .dbc file to remove
            %       character vector | string
            %       Name of the configured .dbc file entry to remove.

            arguments (Input)
                configObj
                dbcName {mustBeText}
            end

            removeDatabase@sg.public.can.DbManagerConfig(configObj, dbcName);
        end

        function generateSlxLibrary(configObj, dbcName, destination)
            % generateSlxLibrary - Generate a Simulink library for one configured .dbc file
            %
            %   Description
            %   -----------
            %   generateSlxLibrary(configObj, dbcName)
            %       The generateSlxLibrary function generates or updates the .slx library for the
            %       specified configured .dbc file and saves it in the current folder.
            %
            %   generateSlxLibrary(configObj, dbcName, destination)
            %       The generated .slx library is saved to the specified destination folder.
            %
            %   Examples
            %   --------
            %   Generate a Simulink library for one configured .dbc file in the current folder:
            %       configObj.generateSlxLibrary('powertrain.dbc');
            %
            %   Generate a Simulink library for one configured .dbc file in a specified destination:
            %       configObj.generateSlxLibrary('powertrain.dbc', 'C:\temp\libraries');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which a library is generated.
            %
            %   dbcName - Name of the configured .dbc file
            %       character vector | string
            %       Name of the configured .dbc file entry for which to generate a library.
            %
            %   destination - Output folder for the generated .slx library
            %       character vector | string
            %       Path to a valid folder where the generated library is saved.

            arguments (Input)
                configObj
                dbcName {mustBeText}
                destination {mustBeText} = pwd
            end

            generateSlxLibrary@sg.public.can.DbManagerConfig(configObj, dbcName, destination);
        end

        function generateAllSlxLibraries(configObj, destination)
            % generateAllSlxLibraries - Generate Simulink libraries for all configured .dbc files
            %
            %   Description
            %   -----------
            %   generateAllSlxLibraries(configObj)
            %       The generateAllSlxLibraries function generates or updates .slx libraries for
            %       all configured .dbc files and saves them in the current folder.
            %
            %   generateAllSlxLibraries(configObj, destination)
            %       The generated .slx libraries are saved to the specified destination folder.
            %
            %   Examples
            %   --------
            %   Generate Simulink libraries for all configured .dbc files in the current folder:
            %       configObj.generateAllSlxLibraries();
            %
            %   Generate Simulink libraries for all configured .dbc files in a specified 
            %   destination:
            %       configObj.generateAllSlxLibraries('C:\temp\libraries');
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance for which all libraries are 
            %       generated.
            %
            %   destination - Output folder for the generated .slx libraries
            %       character vector | string
            %       Path to a valid folder where the generated libraries are saved.

            arguments (Input)
                configObj
                destination {mustBeText} = pwd
            end

            generateAllSlxLibraries@sg.public.can.DbManagerConfig(configObj, destination);
        end

        function save(configObj)
            % save - Save database configuration data to the connected model
            %
            %   Description
            %   -----------
            %   save(configObj)
            %       The save method stores persistent database configuration data of the Database
            %       Manager Config instance in the connected model.
            %
            %   Examples
            %   --------
            %   Save the current instance of the Database Manager Config class:
            %       save(configObj);
            %
            %   Input Arguments
            %   ---------------
            %   configObj - Database Manager Config instance
            %       DbManagerConfig
            %       The Database Manager Config instance from which database configuration 
            %       data is saved to the connected model.

            save@sg.public.can.DbManagerConfig(configObj);
        end
    end
end
