from unittest import TestCase, main
import src.alg as alg
from math import sin, cos

class DummyCanvas:
    def __init__(self):
        self.width = 500
        self.height = 500

    def draw_point(self, point: tuple[int, int]):
        pass

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int]):
        pass


class Test(TestCase):
    def test_rotate_ox(self):
        m = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        r = [
            [1, 0.0, 0.0, 0],
            [0, 0.8660254037844387, 0.49999999999999994, 0],
            [0, -0.49999999999999994, 0.8660254037844387, 0],
            [0, 0.0, 0.0, 1]
        ]
        oxr = 30
        self.assertEqual(alg.rotate_ox(m, oxr), r)

    def test_rotate_oy(self):
        m = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        r = [
            [0.8660254037844387, 0, -0.49999999999999994, 0],
            [0.0, 1, 0.0, 0],
            [0.49999999999999994, 0, 0.8660254037844387, 0],
            [0.0, 0, 0.0, 1]
        ]
        oyr = 30
        self.assertEqual(alg.rotate_oy(m, oyr), r)

    def test_rotate_oz(self):
        m = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        r = [
            [0.8660254037844387, 0.49999999999999994, 0, 0],
            [-0.49999999999999994, 0.8660254037844387, 0, 0],
            [0.0, 0.0, 1, 0],
            [0.0, 0.0, 0, 1]
        ]
        ozr = 30
        self.assertEqual(alg.rotate_oz(m, ozr), r)

    def test_float_horizon(self):
        canvas = DummyCanvas()
        matrix = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        self.assertEqual(alg.float_horizon(canvas, lambda x, z: sin(x) * cos(z), matrix,
                                           [-1, 1, 0.1], [-1, 1, 0.1], 10), None)


if __name__ == '__main__':
    main()
