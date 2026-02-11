from unittest import TestCase, main
import src.algs as algs
import random


class Test(TestCase):
    def test_linear(self):
        random.seed(1337)
        X = 8172
        arr_len = X // 8 + (X % 1000 if (X >> 2) % 10 == 0 else (X >> 2) % 10 * (X % 10) + (X >> 1) % 10)
        arr = random.sample([i for i in range(100000)], k=arr_len)
        self.assertEqual(algs.linear_search(arr, 34772), (454, 455))

    def test_linear_negative(self):
        random.seed(1337)
        X = 8172
        arr_len = X // 8 + (X % 1000 if (X >> 2) % 10 == 0 else (X >> 2) % 10 * (X % 10) + (X >> 1) % 10)
        arr = random.sample([i for i in range(100000)], k=arr_len)
        self.assertEqual(algs.linear_search(arr, 34773), (-1, 1033))

    def test_binary(self):
        random.seed(1337)
        X = 8172
        arr_len = X // 8 + (X % 1000 if (X >> 2) % 10 == 0 else (X >> 2) % 10 * (X % 10) + (X >> 1) % 10)
        arr = random.sample([i for i in range(100000)], k=arr_len)
        arr.sort()
        self.assertEqual(algs.binary_search(arr, 34772), (331, 9))

    def test_binary_negative(self):
        random.seed(1337)
        X = 8172
        arr_len = X // 8 + (X % 1000 if (X >> 2) % 10 == 0 else (X >> 2) % 10 * (X % 10) + (X >> 1) % 10)
        arr = random.sample([i for i in range(100000)], k=arr_len)
        arr.sort()
        self.assertEqual(algs.binary_search(arr, 34773), (-1, 10))


if __name__ == '__main__':
    main()
