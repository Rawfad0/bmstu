from unittest import TestCase, main
import src.alg as alg
from src.objects import Polygon, Clipper


class Test(TestCase):
    def test_polygon_add(self):
        polygon = Polygon()
        self.assertEqual(polygon.add((0, 0)), None)
        self.assertEqual(polygon.points, [(0, 0)])

    def test_polygon_add_same_point(self):
        polygon = Polygon()
        self.assertEqual(polygon.add((0, 0)), None)
        self.assertEqual(polygon.add((0, 0)), None)
        self.assertEqual(polygon.points, [(0, 0)])

    def test_polygon_clear(self):
        polygon = Polygon()
        self.assertEqual(polygon.add((0, 0)), None)
        self.assertEqual(polygon.clear(), None)
        self.assertEqual(polygon.points, [])

    def test_polygon_open(self):
        polygon = Polygon()
        self.assertEqual(polygon.open(), None)
        self.assertEqual(polygon.closed, False)

    def test_polygon_closed(self):
        polygon = Polygon()
        self.assertEqual(polygon.close(), None)
        self.assertEqual(polygon.closed, True)

    def test_polygon_is_closed(self):
        polygon = Polygon()
        self.assertEqual(polygon.close(), None)
        self.assertEqual(polygon.is_closed(), True)
        self.assertEqual(polygon.closed, True)

    def test_polygon_is_valid(self):
        polygon = Polygon()
        self.assertEqual(polygon.add((0, 0)), None)
        self.assertEqual(polygon.add((0, 1)), None)
        self.assertEqual(polygon.add((1, 1)), None)
        self.assertEqual(polygon.is_valid(), True)

    def test_clipper_get_vector(self):
        p1 = (0, 0)
        p2 = (1, 1)
        self.assertEqual(Clipper.get_vector(p1, p2), (1, 1))

    def test_clipper_vecto_prod(self):
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

    def test_alg_vector_product(self):
        a = (1, 3)
        b = (2, 4)
        self.assertEqual(alg.vector_product(a, b), -10)

    def test_alg_get_intersection_point(self):
        t = 0.5
        p1 = (1, 3)
        p2 = (2, 4)
        self.assertEqual(alg.get_intersection_point(t, p1, p2), (2, 4))

    def test_alg_is_visible(self):
        c = (1, 3)
        p = (2, 4)
        norm = (5, 0)
        self.assertEqual(alg.is_visible(p, c, norm), True)

    def test_alg_sutherland_hodhman(self):
        clipper = [(1, 2), (2, 0), (4, 2)]
        polygon = [(1, 0), (2, 3), (4, 1)]
        self.assertEqual(alg.sutherland_hodgman_alg(clipper, polygon),
                         [(1, 1), (2, 2), (3, 2), (4, 2), (2, 0), (2, 0), (1, 1), (1, 1), (1, 1)])


if __name__ == '__main__':
    main()
