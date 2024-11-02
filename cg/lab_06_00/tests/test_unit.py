from unittest import TestCase, main
import src.algs as algs
import src.objects as objs


class DummyCanvas():
    def __init__(self):
        super().__init__()
        self.width = 600
        self.height = 600
        self.pixmap = [[(255, 255, 255) for i in range(self.width)] for j in range(self.height)]
        self.border_color = (0, 0, 0)   # цвет граней многоугольника
        self.fill_color = (0, 0, 256)  # цвет заполнения

    def draw_point(self, point: tuple[int, int], color: tuple[int, int, int]):
        x, y = point
        self.pixmap[y][x] = color

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int], color: tuple[int, int, int]):
        pass

    def draw_border_point(self, point: tuple[int, int]):
        self.draw_point(point, self.border_color)

    def draw_border_line(self, point_beg: tuple[int, int], point_end: tuple[int, int]):
        self.draw_line(point_beg, point_end, self.border_color)

    def draw_fill_point(self, point: tuple[int, int]):
        self.draw_point(point, self.fill_color)

    def clear_canvas(self):
        self.pixmap = [[(255, 255, 255) for i in range(self.width)] for j in range(self.height)]

    def get_point_color(self, point: tuple[int, int]) -> tuple[int, int, int]:
        x, y = point
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.pixmap[y][x]
        else:
            return self.border_color


def dummy_event():
    pass


class Test(TestCase):
    def test_filling_with_seed_point(self):
        canvas = DummyCanvas()
        canvas.draw_border_line((100, 100), (100, 200))
        canvas.draw_border_line((100, 200), (200, 200))
        canvas.draw_border_line((200, 200), (200, 100))
        canvas.draw_border_line((200, 100), (100, 100))
        canvas.draw_fill_point((150, 150))
        seed_point = objs.SeedPoint(150, 150)
        self.assertGreaterEqual(
            algs.filling_with_seed_point(canvas, seed_point.get(), dummy_event), 0
        )


if __name__ == '__main__':
    main()
