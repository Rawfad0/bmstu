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
    def test_standard_circle(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.standard_circle(canvas, (100, 100), 50, (0, 0, 0)), None)

    def test_standard_ellipse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.standard_ellipse(canvas, (100, 100), (50, 30), (0, 0, 0)), None)

    def test_parametric_circle(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.parametric_circle(canvas, (100, 100), 50, (0, 0, 0)), None)

    def test_parametric_ellipse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.parametric_ellipse(canvas, (100, 100), (50, 30), (0, 0, 0)), None)

    def test_bresenham_circle(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_circle(canvas, (100, 100), 50, (0, 0, 0)), None)

    def test_bresenham_ellipse(self):
        canvas = DummyCanvas()
        self.assertEqual(algs.bresenham_ellipse(canvas, (100, 100), (50, 30), (0, 0, 0)), None)


if __name__ == '__main__':
    main()
