% speedgoat_make_rtw_hook - Simulink Real-Time specific hook file for the build process (make_rtw).

function speedgoat_make_rtw_hook(hookMethod, modelName, rtwRoot, templateMakefile, buildOpts, ...
        buildArgs, buildInfo)
    args = {modelName, rtwRoot, templateMakefile, buildOpts, buildArgs, buildInfo};

    switch hookMethod
        case 'error'
            % Called if an error occurs anywhere during the build. If no error occurs during the
            % build, then this hook will not be called. Valid arguments at this stage are hookMethod
            % and modelName. This enables cleaning up any static or global data used by this hook
            % file.
            slrealtime.internal.build.BuildHooksImpl.error(args{:});

        case 'entry'
            % Called at start of code generation process (before anything happens). Valid arguments
            % at this stage are hookMethod, modelName, and buildArgs.
            slrealtime.internal.build.BuildHooksImpl.entry(args{:});
            sg.model.build.Hooks.entry(modelName);

        case 'before_tlc'
            % Called just prior to invoking TLC Compiler (actual code generation). Valid arguments
            % at this stage are hookMethod, modelName, and buildArgs.
            slrealtime.internal.build.BuildHooksImpl.before_tlc(args{:});
            sg.model.build.Hooks.before_tlc(modelName);

        case 'after_tlc'
            % Called just after to invoking TLC Compiler (actual code generation). Valid arguments
            % at this stage are hookMethod, modelName, and buildArgs.
            slrealtime.internal.build.BuildHooksImpl.after_tlc(args{:});
            sg.model.build.Hooks.after_tlc(modelName, buildInfo);

        case 'before_make'
            % Called after code generation is complete, and just prior to kicking off make process
            % (assuming code generation only is not selected). All arguments are valid at this
            % stage.
            slrealtime.internal.build.BuildHooksImpl.before_make(args{:});
            sg.model.build.Hooks.before_make(modelName, buildInfo);

        case 'after_make'
            % Called after make process is complete. All arguments are valid at this stage.
            slrealtime.internal.build.BuildHooksImpl.after_make(args{:});
            sg.model.build.Hooks.after_make(modelName, buildInfo);

        case 'exit'
            % Called at the end of the RTW build process. All arguments are valid at this stage.
            slrealtime.internal.build.BuildHooksImpl.exit(args{:});
            sg.model.build.Hooks.exit(modelName, buildInfo);
    end
end
