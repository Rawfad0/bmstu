from PyQt6.QtGui import QPixmap, QPainter, QColor
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QLabel


class Canvas(QLabel):
    def __init__(self):
        super().__init__()
        self.width = 600
        self.height = 600
        pixmap = QPixmap(self.width, self.height)
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)

    @staticmethod
    def draw_ellipse(canvas, center_point: tuple[int, int], radius: tuple[int, int], color: tuple[int, int, int], mode: str = "draw"):
        cx, cy = center_point
        rx, ry = radius
        pixmap = canvas.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawEllipse(cx - rx, cy - ry, 2*rx, 2*ry)
        painter.end()
        canvas.setPixmap(pixmap)

    @staticmethod
    def draw_circle(canvas, center_point: tuple[int, int], radius, color=(0, 0, 0)):
        cx, cy = center_point
        pixmap = canvas.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawEllipse(cx - radius, cy - radius, 2*radius, 2*radius)
        painter.end()
        canvas.setPixmap(pixmap)

    def draw_point(self, point: tuple[int, int], color: (int, int, int) = (0, 0, 0)):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawPoint(*point)
        painter.end()
        self.setPixmap(pixmap)

    def draw_points(self, points: list[tuple[int, int]], color: (int, int, int) = (0, 0, 0)):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        for px, py in points:
            painter.setPen(QColor(*color))
            painter.drawPoint(px, py)
        painter.end()
        self.setPixmap(pixmap)

    def clear_canvas(self):
        pixmap = self.pixmap()
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)
