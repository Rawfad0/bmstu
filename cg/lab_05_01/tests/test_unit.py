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


def dummy_event():
    pass


class Test(TestCase):
    def test_alg_with_ordered_edges_list(self):
        canvas = DummyCanvas()
        self.assertEqual(
            algs.alg_with_ordered_edges_list(canvas, [(10, 10), (10, 30), (30, 50), (10, 10)], dummy_event), None)

    def test_alg_with_ordered_edges_list_with_delay(self):
        canvas = DummyCanvas()
        self.assertEqual(
            algs.alg_with_ordered_edges_list(canvas, [(10, 10), (10, 30), (30, 50), (10, 10)], dummy_event, 10), None)


if __name__ == '__main__':
    main()
