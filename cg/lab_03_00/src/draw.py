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
    def draw_line(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
        pixmap = canvas.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*color))
        painter.drawLine(*point_begin, *point_end)
        painter.end()
        canvas.setPixmap(pixmap)

    def draw_point(self, point: (int, int), intensity: float = 1.0, color: (int, int, int) = (0, 0, 0)):
        r, g, b = color
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(255 - int(intensity*(255 - r)),
                              255 - int(intensity*(255 - g)),
                              255 - int(intensity*(255 - b))))
        painter.drawPoint(*point)
        painter.end()
        self.setPixmap(pixmap)

    def draw_points(self, points: list[((int, int), float)], color: (int, int, int) = (0, 0, 0)):
        r, g, b = color
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        for (px, py), intensity in points:
            painter.setPen(QColor(255 - int(intensity*(255 - r)),
                                  255 - int(intensity*(255 - g)),
                                  255 - int(intensity*(255 - b))))
            painter.drawPoint(px, py)
        painter.end()
        self.setPixmap(pixmap)

    def clear_canvas(self):
        pixmap = self.pixmap()
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)
