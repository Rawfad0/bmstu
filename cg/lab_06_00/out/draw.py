from PyQt6.QtGui import QPixmap, QPainter, QColor, QMouseEvent
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QLabel


class Canvas(QLabel):
    def __init__(self, callback):
        super().__init__()
        self.width = 600
        self.height = 600
        pixmap = QPixmap(self.width, self.height)
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)
        self.border_color = (0, 0, 0)   # цвет граней многоугольника
        self.fill_color = (0, 0, 0)  # цвет заполнения
        self.callback = callback

    def mousePressEvent(self, ev: QMouseEvent) -> None:
        if ev.button() == Qt.MouseButton.LeftButton:
            x, y = int(ev.position().x()), int(ev.position().y())
            self.callback.add_point(x, y)
        if ev.button() == Qt.MouseButton.RightButton:
            self.callback.close_polyline()

    def draw_point(self, point: tuple[int, int], color: tuple[int, int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawPoint(*point)
        painter.end()
        self.setPixmap(pixmap)

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int], color: tuple[int, int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawLine(*point_beg, *point_end)
        painter.end()
        self.setPixmap(pixmap)

    def draw_ellipse(self, center_point: tuple[int, int], radius: tuple[int, int], color: tuple[int, int, int]):
        cx, cy = center_point
        rx, ry = radius
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawEllipse(cx - rx, cy - ry, 2 * rx, 2 * ry)
        painter.end()
        self.setPixmap(pixmap)

    def draw_border_point(self, point: tuple[int, int]):
        self.draw_point(point, self.border_color)

    def draw_border_line(self, point_beg: tuple[int, int], point_end: tuple[int, int]):
        self.draw_line(point_beg, point_end, self.border_color)

    def draw_border_ellipse(self, center_point: tuple[int, int], radius: tuple[int, int]):
        self.draw_ellipse(center_point, radius, self.border_color)

    def draw_fill_point(self, point: tuple[int, int]):
        self.draw_point(point, self.fill_color)

    def clear_canvas(self):
        pixmap = self.pixmap()
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)

    def get_point_color(self, point: tuple[int, int]) -> tuple[int, int, int]:
        pixmap = self.pixmap()
        img = pixmap.toImage()
        x, y = point
        if 0 <= x < self.width and 0 <= y < self.height:
            r, g, b, a = img.pixelColor(*point).getRgb()
            rgb_color = (int(r), int(g), int(b))
            return rgb_color
        else:
            return self.border_color
