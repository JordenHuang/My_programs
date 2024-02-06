def unknown_function(p = '.'):
    import os
    if not os.path.isdir(p):
        return 1
    unknown_variable = os.listdir(p)
    return sum(map(unknown_function, unknown_variable))
