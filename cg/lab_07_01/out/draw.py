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
        self.clipper_color = (256, 0, 0)                # цвет отсекателя
        self.line_segment_color = (0, 0, 0)             # цвет отрезков
        self.clipped_line_segment_color = (0, 0, 256)   # цвет отсеченных отрезков
        self.callback = callback

    def mousePressEvent(self, ev: QMouseEvent) -> None:
        point = int(ev.position().x()), int(ev.position().y())
        if ev.button() == Qt.MouseButton.LeftButton:
            self.callback.add_line_segment_point(point)
        if ev.button() == Qt.MouseButton.RightButton:
            self.callback.add_clipper_point(point)

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

    def draw_rect(self, point_1: tuple[int, int], point_2: tuple[int, int], color: tuple[int, int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        x1, y1 = point_1
        x2, y2 = point_2
        painter.drawRect(x1, y1, x2 - x1, y2 - y1)
        painter.end()
        self.setPixmap(pixmap)

    def draw_clipper_point(self, point: tuple[int, int]):
        self.draw_point(point, self.clipper_color)

    def draw_clipper(self, p1: tuple[int, int], p2: tuple[int, int]):
        self.draw_rect(p1, p2, self.clipper_color)

    def draw_line_segment_point(self, point: tuple[int, int]):
        self.draw_point(point, self.line_segment_color)

    def draw_line_segment(self, p1: tuple[int, int], p2: tuple[int, int]):
        self.draw_line(p1, p2, self.line_segment_color)

    def draw_clipped_line_segment(self, p1: tuple[int, int], p2: tuple[int, int]):
        self.draw_line(p1, p2, self.clipped_line_segment_color)

    def clear_canvas(self):
        pixmap = self.pixmap()
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)
