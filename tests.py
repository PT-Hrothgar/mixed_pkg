import unittest

import mixed_pkg
import mixed_pkg.c_helpers


class PackageTest(unittest.TestCase):
    def test_is_prime(self):
        for prime in (2, 3, 5, 7, 23, 211, 7454057939):
            self.assertTrue(mixed_pkg.is_prime(prime))

        for comp in (4, 6, 9, 51, 210, 7454057939 * 3):
            self.assertFalse(mixed_pkg.is_prime(comp))

        for val in (-2, 0, 1):
            self.assertRaises(ValueError, mixed_pkg.is_prime, val)

    def test_get_factors(self):
        for num, factors in (
            (2, [2]),
            (4, [2, 2]),
            (7, [7]),
            (9, [3, 3]),
            (75, [3, 5, 5]),
            (128, [2, 2, 2, 2, 2, 2, 2]),
            (169, [13, 13]),
            (7454057939, [7454057939])
        ):
            self.assertEqual(mixed_pkg.get_factors(num), factors)


class CHelpersTest(unittest.TestCase):
    def test_func(self):
        for num, factors in (
            (2, [2]),
            (4, [2, 2]),
            (7, [7]),
            (9, [3, 3]),
            (75, [3, 5, 5]),
            (128, [2, 2, 2, 2, 2, 2, 2]),
            (169, [13, 13]),
            (7454057939, [7454057939])
        ):
            self.assertEqual(mixed_pkg.c_helpers.get_factors(num), factors)

    def test_c_implementation(self):
        self.assertIs(mixed_pkg.get_factors, mixed_pkg.c_helpers.get_factors)
        # Assert get_factors() is of type 'builtin_function_or_method'
        self.assertIsInstance(mixed_pkg.c_helpers.get_factors, type(print))


if __name__ == "__main__":
    unittest.main()
