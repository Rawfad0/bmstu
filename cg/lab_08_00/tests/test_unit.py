from unittest import TestCase, main
import src.alg as alg
from src.objects import LineSegments, Clipper


class Test(TestCase):

    def test_line_segments_add_segment(self):
        segments = LineSegments()
        self.assertEqual(segments.add_line_segment(((0, 0), (1, 1))), None)
        self.assertEqual(segments.list, [((0, 0), (1, 1))])

    def test_line_segments_add_one_point(self):
        segments = LineSegments()
        self.assertEqual(segments.add_point((0, 0)), False)
        self.assertEqual(segments.list, [((0, 0), (None, None))])

    def test_line_segments_add_two_points(self):
        segments = LineSegments()
        self.assertEqual(segments.add_point((0, 0)), False)
        self.assertEqual(segments.add_point((1, 1)), True)
        self.assertEqual(segments.list, [((0, 0), (1, 1))])

    def test_line_segments_clear(self):
        segments = LineSegments()
        self.assertEqual(segments.add_point((0, 0)), False)
        self.assertEqual(segments.add_point((1, 1)), True)
        self.assertEqual(segments.clear(), None)
        self.assertEqual(segments.list, [])

    def test_clipper_add(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.points, [(0, 0)])

    def test_polygon_add_same_point(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.points, [(0, 0)])

    def test_polygon_clear(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.clear(), None)
        self.assertEqual(clipper.points, [])

    def test_polygon_open(self):
        clipper = Clipper()
        self.assertEqual(clipper.open(), None)
        self.assertEqual(clipper.closed, False)

    def test_polygon_closed(self):
        clipper = Clipper()
        self.assertEqual(clipper.close(), None)
        self.assertEqual(clipper.closed, True)

    def test_polygon_is_closed(self):
        clipper = Clipper()
        self.assertEqual(clipper.close(), None)
        self.assertEqual(clipper.is_closed(), True)
        self.assertEqual(clipper.closed, True)

    def test_polygon_is_valid(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((0, 1)), None)
        self.assertEqual(clipper.add((1, 1)), None)
        self.assertEqual(clipper.is_valid(), True)

    def test_clipper_get_vector(self):
        p1 = (0, 0)
        p2 = (1, 1)
        self.assertEqual(Clipper.get_vector(p1, p2), (1, 1))

    def test_clipper_vector_prod(self):
        v1 = (0, 0)
        v2 = (1, 1)
        self.assertEqual(Clipper.vector_prod(v1, v2), 0)

    def test_clipper_sign_pos(self):
        x = 10
        self.assertEqual(Clipper.sign(x), 1)

    def test_clipper_sign_zero(self):
        x = 0
        self.assertEqual(Clipper.sign(x), 0)

    def test_clipper_sign_neg(self):
        x = -10
        self.assertEqual(Clipper.sign(x), -1)

    def test_clipper_is_convex_pos(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((0, 1)), None)
        self.assertEqual(clipper.add((1, 1)), None)
        self.assertEqual(clipper.is_convex(), True)

    def test_clipper_is_convex_neg(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((1, 0)), None)
        self.assertEqual(clipper.add((1, 1)), None)
        self.assertEqual(clipper.add((2, 1)), None)
        self.assertEqual(clipper.is_convex(), False)

    def test_clipper_is_convex_line(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((0, 1)), None)
        self.assertEqual(clipper.add((0, 3)), None)
        self.assertEqual(clipper.is_convex(), False)

    def test_clipper_is_valid(self):
        clipper = Clipper()
        self.assertEqual(clipper.add((0, 0)), None)
        self.assertEqual(clipper.add((0, 1)), None)
        self.assertEqual(clipper.add((1, 1)), None)
        self.assertEqual(clipper.is_valid(), True)

    def test_alg_vector_sum(self):
        a = (1, 3)
        b = (2, 4)
        self.assertEqual(alg.vector_sum(a, b), (3, 7))

    def test_alg_form(self):
        points = [(0, 0), (1, 1), (1, 0)]
        self.assertEqual(alg.form(points), [(1, 1), (1, 0), (0, 0)])

    def test_alg_get_vector(self):
        p1 = (0, 0)
        p2 = (1, 1)
        self.assertEqual(alg.get_vector(p1, p2), (1, 1))

    def test_alg_get_normal(self):
        p1 = (0, 0)
        p2 = (1, 1)
        self.assertEqual(alg.get_normal(p1, p2), (1, -1))

    def test_alg_scalar_product(self):
        a = (1, 3)
        b = (2, 4)
        self.assertEqual(alg.scalar_product(a, b), 14)

    def test_alg_cyrus_beck(self):
        clipper = [(1, 2), (2, 0), (4, 2)]
        line_segment = [(1, 0), (2, 3)]
        self.assertEqual(alg.cyrus_beck(clipper, line_segment), (True, (1, 1), (2, 2)))

    def test_alg_cyrus_beck_2(self):
        clipper = [(1, 2), (2, 0), (4, 2)]
        line_segment = [(0, 0), (3, 3)]
        self.assertEqual(alg.cyrus_beck(clipper, line_segment), (True, (1, 1), (2, 2)))

    def test_alg_cyrus_beck_out(self):
        clipper = [(1, 2), (2, 0), (4, 2)]
        line_segment = [(0, 0), (0, 1)]
        self.assertEqual(alg.cyrus_beck(clipper, line_segment), (False, (0, 0), (0, 1)))

    def test_alg_cyrus_beck_parallel(self):
        clipper = [(1, 2), (2, 0), (4, 2)]
        line_segment = [(2, 2), (3, 2)]
        self.assertEqual(alg.cyrus_beck(clipper, line_segment), (True, (2, 2), (3, 2)))


if __name__ == '__main__':
    main()
