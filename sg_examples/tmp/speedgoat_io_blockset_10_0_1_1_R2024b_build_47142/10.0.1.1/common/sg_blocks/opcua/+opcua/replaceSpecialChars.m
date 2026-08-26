function out = replaceSpecialChars(in)    
    
    % out = char(regexprep(in, '[^a-zA-Z0-9]', '_'));
    % out = regexprep(out, '_+', '_');
    % out = strip(str, 'left', '_');

    out = matlab.lang.makeValidName(in);
end
