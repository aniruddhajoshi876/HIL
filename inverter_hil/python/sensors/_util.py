import math


def matlab_round(value):
    return math.floor(value + 0.5) if value >= 0 else math.ceil(value - 0.5)
