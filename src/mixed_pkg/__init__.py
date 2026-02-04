__version__ = "0.12"

from mixed_pkg.c_helpers import get_factors

def is_prime(num):
    return get_factors(num) == [num]
