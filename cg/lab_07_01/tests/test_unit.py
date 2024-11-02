from unittest import TestCase, main
import src.algs as alg
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

    def test_clipper_set(self):
        clipper = Clipper()
        self.assertEqual(clipper.set((0, 0), (1, 2)), None)
        self.assertEqual(clipper.p1, (0, 0))
        self.assertEqual(clipper.p2, (1, 2))

    def test_clipper_add_point(self):
        clipper = Clipper()
        self.assertEqual(clipper.add_point((0, 0)), False)
        self.assertEqual(clipper.p1, (0, 0))
        self.assertEqual(clipper.p2, (None, None))

    def test_clipper_add_two_points(self):
        clipper = Clipper()
        self.assertEqual(clipper.add_point((0, 0)), False)
        self.assertEqual(clipper.add_point((1, 1)), True)
        self.assertEqual(clipper.p1, (0, 0))
        self.assertEqual(clipper.p2, (1, 1))

    def test_clipper_clear(self):
        clipper = Clipper()
        self.assertEqual(clipper.add_point((0, 0)), False)
        self.assertEqual(clipper.clear(), None)
        self.assertEqual(clipper.p1, (None, None))
        self.assertEqual(clipper.p2, (None, None))

    def test_clipper_is_valid(self):
        clipper = Clipper()
        self.assertEqual(clipper.add_point((0, 0)), False)
        self.assertEqual(clipper.add_point((1, 1)), True)
        self.assertEqual(clipper.is_valid(), True)

    def test_clipper_is_not_valid_1(self):
        clipper = Clipper()
        self.assertEqual(clipper.is_valid(), False)

    def test_clipper_is_not_valid_2(self):
        clipper = Clipper()
        self.assertEqual(clipper.add_point((0, 0)), False)
        self.assertEqual(clipper.is_valid(), False)

    def test_alg_t_func(self):
        self.assertEqual(alg.t_func((0, 1), 1, 2, 1, 2), (1, 0, 0, 0))

    def test_alg_s_func(self):
        self.assertEqual(alg.s_func((1, 0, 1, 0)), 2)

    def test_alg_p_func(self):
        self.assertEqual(alg.p_func((1, 0, 1, 0), (0, 1, 0, 0)), 0)

    def test_alg_vertical_1(self):
        self.assertEqual(alg.vertical(1, 1, 0, 2), (1, 1))

    def test_alg_vertical_2(self):
        self.assertEqual(alg.vertical(1, 3, 0, 2), (1, 2))

    def test_alg_vertical_3(self):
        self.assertEqual(alg.vertical(1, -1, 0, 2), (1, 0))

    def test_alg_simple_clip_1(self):
        clipper = ((0, 0), (2, 2))
        line_segment = [(1, 0), (2, 3)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (1, 0), (2, 2)))

    def test_alg_simple_clip_2(self):
        clipper = ((0, 0), (2, 2))
        line_segment = [(0, 0), (3, 3)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (0, 0), (2, 2)))

    def test_alg_simple_clip_out(self):
        clipper = ((0, 0), (2, 2))
        line_segment = [(3, 3), (4, 3)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (False, (3, 3), (4, 3)))

    def test_alg_simple_clip_parallel(self):
        clipper = ((0, 0), (2, 2))
        line_segment = [(0, 2), (3, 2)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (0, 2), (2, 2)))

    def test_alg_simple_clip_vertical_1(self):
        clipper = ((0, 0), (3, 3))
        line_segment = [(1, 1), (1, 2)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (1, 1), (1, 2)))

    def test_alg_simple_clip_vertical_2(self):
        clipper = ((0, 0), (3, 3))
        line_segment = [(1, -1), (1, 3)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (1, 3), (1, 0)))

    def test_alg_simple_clip_3(self):
        clipper = ((0, 0), (10, 10))
        line_segment = [(-1, -1), (11, 2)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (3, 0), (10, 2)))

    def test_alg_simple_clip_4(self):
        clipper = ((0, 0), (10, 10))
        line_segment = [(-1, -1), (2, 11)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (0, 3), (2, 10)))

    def test_alg_simple_clip_compl_visible(self):
        clipper = ((0, 0), (10, 10))
        line_segment = [(1, 1), (2, 2)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (True, (1, 1), (2, 2)))

    def test_alg_simple_clip_5(self):
        clipper = ((0, 0), (10, 10))
        line_segment = [(-2, 9), (2, 13)]
        self.assertEqual(alg.simple_clip(clipper, line_segment), (False, (-2, 9), (2, 13)))


if __name__ == '__main__':
    main()
