function tau = controlsModelStep(inputs, reset)
%CONTROLSMODELSTEP Execute the vendored generated allocator through its MEX.
if nargin < 2, reset = false; end
if exist('vvcu_controls_mex','file') ~= 3
    error('virtualvcu:ControlsMexMissing', [ ...
        'Build the pinned generated model first with ' ...
        'build_controls_model_mex.']);
end
if reset
    vvcu_controls_mex('reset');
end
tau = reshape(vvcu_controls_mex(double(inputs(:))),1,4);
end
