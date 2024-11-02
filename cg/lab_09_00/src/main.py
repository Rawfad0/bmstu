import sys
from PyQt6.QtWidgets import (
    QApplication,
    QComboBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QVBoxLayout,
    QWidget,
)
from .draw import Canvas
from .alg import sutherland_hodgman_alg
from .objects import Polygon, Clipper


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 9")
        self.resize(1000, 600)

        # Выбор цветов
        self.clipper_color_label = QLabel("Цвет отсекателя")
        self.clipper_color_combo_box = QComboBox()
        self.clipper_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.clipper_color_combo_box.currentIndexChanged.connect(self.set_clipper_color)
        self.polygon_color_label = QLabel("Цвет многоугольника")
        self.polygon_color_combo_box = QComboBox()
        self.polygon_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.polygon_color_combo_box.currentIndexChanged.connect(self.set_polygon_color)
        self.clipped_polygon_color_label = QLabel("Цвет осеченных отрезков")
        self.clipped_polygon_color_combo_box = QComboBox()
        self.clipped_polygon_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.clipped_polygon_color_combo_box.currentIndexChanged.connect(self.set_clipped_polygon_color)
        # Ввод точки
        self.x_label = QLabel("Координата X")
        self.y_label = QLabel("Координата Y")
        self.x_entry = QLineEdit()
        self.y_entry = QLineEdit()
        # Кнопки добавления точки
        self.add_polygon_point_button = QPushButton("Добавить точку многоугольника")
        self.add_polygon_point_button.clicked.connect(self.add_polygon_point_with_check)
        self.add_clipper_point_button = QPushButton("Добавить точку отсекателя")
        self.add_clipper_point_button.clicked.connect(self.add_clipper_point_with_check)
        # Кнопки замыкания многоугольников
        self.close_polygon_button = QPushButton("Замкнуть многоугольник")
        self.close_polygon_button.clicked.connect(self.close_polygon)
        self.close_clipper_button = QPushButton("Замкнуть отсекатель")
        self.close_clipper_button.clicked.connect(self.close_clipper)
        # Кнопки
        self.clip_button = QPushButton("Отсечь")
        self.clip_button.clicked.connect(self.clip)
        self.clear_button = QPushButton("Очистить")
        self.clear_button.clicked.connect(self.clear)
        # График
        self.canvas = Canvas(self)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)
        # Предустановленные значения
        self.clipper_color_combo_box.setCurrentIndex(2)
        self.clipped_polygon_color_combo_box.setCurrentIndex(4)

        self.polygon = Polygon()
        self.clipper = Clipper()

    def compose_color_section_layout(self):
        color_section_layout = QHBoxLayout()
        color_label_section_layout = QVBoxLayout()
        for c_label in [self.clipper_color_label,
                        self.polygon_color_label,
                        self.clipped_polygon_color_label]:
            color_label_section_layout.addWidget(c_label)
        color_combobox_section_layout = QVBoxLayout()
        for c_combobox in [self.clipper_color_combo_box,
                           self.polygon_color_combo_box,
                           self.clipped_polygon_color_combo_box]:
            color_combobox_section_layout.addWidget(c_combobox)
        color_section_layout.addLayout(color_label_section_layout)
        color_section_layout.addLayout(color_combobox_section_layout)
        return color_section_layout

    def compose_point_section_layout(self):
        point_section_layout = QVBoxLayout()
        point_columns_section_layout = QHBoxLayout()
        point_label_section_layout = QVBoxLayout()
        point_label_section_layout.addWidget(self.x_label)
        point_label_section_layout.addWidget(self.y_label)
        point_entry_section_layout = QVBoxLayout()
        point_entry_section_layout.addWidget(self.x_entry)
        point_entry_section_layout.addWidget(self.y_entry)
        point_columns_section_layout.addLayout(point_label_section_layout)
        point_columns_section_layout.addLayout(point_entry_section_layout)
        point_section_layout.addLayout(point_columns_section_layout)
        point_section_layout.addWidget(self.add_polygon_point_button)
        point_section_layout.addWidget(self.add_clipper_point_button)
        point_section_layout.addWidget(self.close_polygon_button)
        point_section_layout.addWidget(self.close_clipper_button)
        return point_section_layout

    def compose(self):
        color_layout = self.compose_color_section_layout()
        point_layout = self.compose_point_section_layout()
        left_layout = QVBoxLayout()
        left_layout.addLayout(color_layout)
        left_layout.addLayout(point_layout)
        left_layout.addWidget(self.clip_button)
        left_layout.addWidget(self.clear_button)
        layout = QHBoxLayout()
        layout.addLayout(left_layout)
        layout.addWidget(self.canvas)
        return layout

    @staticmethod
    def show_popup_window(text, title):
        msg = QMessageBox()
        msg.setWindowTitle(title)
        msg.setText(text)
        msg.exec()

    @staticmethod
    def is_int(string):
        try:
            int(string)
            return True
        except ValueError:
            return False

    def get_point_with_check(self) -> [None, tuple[int, int]]:
        message = ""
        x = self.x_entry.text()
        y = self.y_entry.text()
        if not self.is_int(x):
            message += f"Координата X точки отсекателя не задана или не является целым числом;\n"
        if not self.is_int(y):
            message += f"Координата Y точки отсекателя не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
            return None
        else:
            return int(x), int(y)

    def add_point(self, object, point):
        if object.is_closed():
            object.clear()
            object.open()
            object.add(point)
            self.redraw()
            if type(object) is Clipper:
                self.canvas.draw_clipper_point(point)
            else:
                self.canvas.draw_polygon_point(point)
        else:
            prev_point = object.points[-1]
            object.add(point)
            if type(object) is Clipper:
                self.canvas.draw_clipper_line(prev_point, point)
            else:
                self.canvas.draw_polygon_line(prev_point, point)

    def add_polygon_point_with_check(self):
        point = self.get_point_with_check()
        if point is not None:
            self.add_polygon_point(point)

    def add_polygon_point(self, point: tuple[int, int]):
        self.add_point(self.polygon, point)

    def add_clipper_point_with_check(self):
        point = self.get_point_with_check()
        if point is not None:
            self.add_clipper_point(point)

    def add_clipper_point(self, point: tuple[int, int]):
        self.add_point(self.clipper, point)

    def close_polygon(self):
        self.polygon.close()
        if len(self.polygon.points) > 0:
            self.canvas.draw_polygon_line(self.polygon.points[0], self.polygon.points[-1])

    def close_clipper(self):
        self.clipper.close()
        if len(self.clipper.points) > 0:
            self.canvas.draw_clipper_line(self.clipper.points[0], self.clipper.points[-1])

    def clip(self):
        message = ""
        if not self.clipper.is_closed():
            message = "Отсекатель не замкнут\n"
        if not self.clipper.is_valid():
            message = "Отсекатель не задан или не является выпуклым многоугольником\n"
        if not self.polygon.is_closed():
            message = "Многоугольник не замкнут\n"
        if not self.polygon.is_valid():
            message = "Многоугольник не задан или не является выпуклым многоугольником\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            result = sutherland_hodgman_alg(self.clipper.points, self.polygon.points)

            n = len(result)
            for i in range(n):
                p1, p2 = result[i - 1], result[i]
                self.canvas.draw_clipped_polygon_line(p1, p2)

    def draw_polygon(self, object):
        n = len(object.points)
        if n == 1:
            if type(object) is Clipper:
                self.canvas.draw_clipper_point(object.points[0])
            else:
                self.canvas.draw_polygon_point(object.points[0])
        elif n > 1:
            for i in range(n - 1):
                p1, p2 = object.points[i], object.points[i + 1]
                if type(object) is Clipper:
                    self.canvas.draw_clipper_line(p1, p2)
                else:
                    self.canvas.draw_polygon_line(p1, p2)
            if object.is_closed():
                p1, p2 = object.points[-1], object.points[0]
                if type(object) is Clipper:
                    self.canvas.draw_clipper_line(p1, p2)
                else:
                    self.canvas.draw_polygon_line(p1, p2)

    def redraw(self):
        self.canvas.clear_canvas()
        self.draw_polygon(self.clipper)
        self.draw_polygon(self.polygon)

    @staticmethod
    def get_color(color_combo_box):
        color_dict = {
            0: (0, 0, 0),
            1: (255, 255, 255),
            2: (255, 0, 0),
            3: (0, 255, 0),
            4: (0, 0, 255),
        }
        return color_dict[color_combo_box.currentIndex()]

    def set_clipper_color(self):
        self.canvas.clipper_color = self.get_color(self.clipper_color_combo_box)

    def set_polygon_color(self):
        self.canvas.polygon_color = self.get_color(self.polygon_color_combo_box)

    def set_clipped_polygon_color(self):
        self.canvas.clipped_polygon_color = self.get_color(self.clipped_polygon_color_combo_box)

    def clear(self):
        self.polygon.clear()
        self.polygon.close()
        self.clipper.clear()
        self.clipper.close()
        self.canvas.clear_canvas()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
