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
        self.color = (0, 0, 255)
        self.callback = callback

    def draw_point(self, point: tuple[int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*self.color))
        painter.drawPoint(*point)
        painter.end()
        self.setPixmap(pixmap)

    def draw_line(self, point_beg: tuple[int, int], point_end: tuple[int, int]):
        pixmap = self.pixmap()
        painter = QPainter(pixmap)
        painter.setPen(QColor(*self.color))
        painter.drawLine(*point_beg, *point_end)
        painter.end()
        self.setPixmap(pixmap)

    def clear_canvas(self):
        pixmap = self.pixmap()
        pixmap.fill(Qt.GlobalColor.white)
        self.setPixmap(pixmap)
