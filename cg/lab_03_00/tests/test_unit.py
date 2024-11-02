from unittest import TestCase, main
import src.algs as algs


class DummyCanvas:
    def __init__(self):
        self.width = 500
        self.height = 500

    def draw_point(self, point: tuple[int, int], intensity: float = 1.0, color: (int, int, int) = (0, 0, 0)):
        pass

    def draw_points(self, points: list[((int, int), float)], color: (int, int, int) = (0, 0, 0)):
        pass

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int]):
        pass


class Test(TestCase):
    def test_dda(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.dda(canvas, (10, 10), (20, 20), (0, 0, 0)), None)

    def test_dda_point(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.dda(canvas, (10, 10), (10, 10), (0, 0, 0)), None)

    def test_dda_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.dda(canvas, (10, 10), (20, 20), (0, 0, 0), "step"), 10)

    def test_bresenham_float(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_float(canvas, (10, 10), (20, 15), (0, 0, 0)), None)

    def test_bresenham_float_2(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_float(canvas, (10, 10), (15, 20), (0, 0, 0)), None)

    def test_bresenham_float_reverse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_float(canvas, (20, 15), (10, 10), (0, 0, 0)), None)

    def test_bresenham_float_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_float(canvas, (10, 10), (20, 20), (0, 0, 0), "step"), 10)

    def test_bresenham_int_1(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_int(canvas, (10, 10), (20, 15), (0, 0, 0)), None)

    def test_bresenham_int_2(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_int(canvas, (10, 10), (15, 20), (0, 0, 0)), None)


    def test_bresenham_int_reverse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_int(canvas, (20, 20), (10, 10), (0, 0, 0)), None)

    def test_bresenham_int_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_int(canvas, (10, 10), (20, 20), (0, 0, 0), "step"), 10)

    def test_bresenham_antialiasing_1(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_antialiasing(canvas, (10, 10), (20, 15), (0, 0, 0)), None)

    def test_bresenham_antialiasing_2(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_antialiasing(canvas, (10, 10), (15, 20), (0, 0, 0)), None)

    def test_bresenham_antialiasing_reverse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_antialiasing(canvas, (20, 20), (10, 10), (0, 0, 0)), None)

    def test_bresenham_antialiasing_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_antialiasing(canvas, (10, 10), (20, 20), (0, 0, 0), "step"), 10)

    def test_wu_1(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (10, 10), (15, 20), (0, 0, 0)), None)

    def test_wu_1_reverse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (15, 20), (10, 10), (0, 0, 0)), None)

    def test_wu_2(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (10, 10), (20, 15), (0, 0, 0)), None)

    def test_wu_2_reverse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (20, 15), (10, 10), (0, 0, 0)), None)

    def test_wu_point(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (10, 10), (10, 10), (0, 0, 0)), None)

    def test_w_1_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (10, 10), (15, 20), (0, 0, 0), "step"), 4)

    def test_wu_2_step(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.wu(canvas, (10, 10), (20, 15), (0, 0, 0), "step"), 5)


if __name__ == '__main__':
    main()
