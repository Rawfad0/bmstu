from unittest import TestCase, main
import src.p_funcs as p_funcs
from src.smile_face import init_figure


class Test(TestCase):
    def test_move_point(self):
        self.assertEqual(p_funcs.move_point((0, 0), 1, 1), (1, 1))
        self.assertEqual(p_funcs.move_point((1, 2), 3, 5), (4, 7))
        self.assertEqual(p_funcs.move_point((121, 14.13), 0, -13.13), (121, 1))
        self.assertEqual(p_funcs.move_point((-12, 1.2), -21, 0.1), (-33, 1.3))

    def test_rotate_point(self):
        self.assertEqual(p_funcs.rotate_point((0, 0), (0, 0), 90), (0, 0))
        self.assertEqual(p_funcs.rotate_point((0, 1), (0, 0), 90), (-1.0,  6.123233995736766e-17))      # (-1, 0)
        self.assertEqual(p_funcs.rotate_point((2, 0), (1, 1), -90), (0.0,  -6.123233995736766e-17))     # (0, 0)

    def test_scale_point(self):
        self.assertEqual(p_funcs.scale_point((0, 0), (0, 0), (0, 0)), (0, 0))
        self.assertEqual(p_funcs.scale_point((0, 1), (0, 0), (2, 2)), (0, 2))
        self.assertEqual(p_funcs.scale_point((3, 3), (1, 1), (1.5, 1.5)), (4.0, 4.0))
        self.assertEqual(p_funcs.scale_point((3, 3), (1, 1), (-1, -1)), (-1.0, -1.0))

    def test_points(self):
        self.assertEqual(p_funcs.move_points([[0, 0], ], 1, 1), None)
        self.assertEqual(p_funcs.rotate_points([[0, 0], ], (1, 1), 90), None)
        self.assertEqual(p_funcs.scale_points([[0, 0], ], (1, 1), (1, 1)), None)

    def test_init_figure(self):
        self.assertEqual(init_figure(), None)


if __name__ == '__main__':
    main()
