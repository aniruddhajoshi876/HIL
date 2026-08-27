function value = finiteScalar(value, name)
%FINITESCALAR Validate an engineering-unit packer input.

if ~isnumeric(value) && ~islogical(value)
    error('inverterhil:NonFinite', '%s must be numeric.', name);
end
if ~isscalar(value) || ~isfinite(double(value))
    error('inverterhil:NonFinite', '%s must be a finite scalar.', name);
end
value = double(value);
end
