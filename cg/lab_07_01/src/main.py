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
from .algs import simple_clip
from .objects import LineSegments, Clipper


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.line_segments = LineSegments()
        self.clipper = Clipper()

        self.setWindowTitle("Lab 7")
        self.resize(1000, 600)

        # Выбор цветов
        self.clipper_color_label = QLabel("Цвет отсекателя")
        self.clipper_color_combo_box = QComboBox()
        self.clipper_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.clipper_color_combo_box.currentIndexChanged.connect(self.set_clipper_color)
        self.line_segment_color_label = QLabel("Цвет отрезков")
        self.line_segment_color_combo_box = QComboBox()
        self.line_segment_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.line_segment_color_combo_box.currentIndexChanged.connect(self.set_line_segment_color)
        self.clipped_line_segment_color_label = QLabel("Цвет осеченных отрезков")
        self.clipped_line_segment_color_combo_box = QComboBox()
        self.clipped_line_segment_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.clipped_line_segment_color_combo_box.currentIndexChanged.connect(self.set_clipped_line_segment_color)
        # Ввод отрезка
        self.line_begin_x_label = QLabel("Координата X начала")
        self.line_begin_y_label = QLabel("Координата Y начала")
        self.line_end_x_label = QLabel("Координата X конца")
        self.line_end_y_label = QLabel("Координата Y конца")
        self.line_begin_x_entry = QLineEdit()
        self.line_begin_y_entry = QLineEdit()
        self.line_end_x_entry = QLineEdit()
        self.line_end_y_entry = QLineEdit()
        self.draw_line_button = QPushButton("Добавить отрезок")
        self.draw_line_button.clicked.connect(self.add_line_segment_with_check)
        # Ввод отсекателя
        self.clipper_begin_x_label = QLabel("Координата X первой точки")
        self.clipper_begin_y_label = QLabel("Координата Y первой точки")
        self.clipper_end_x_label = QLabel("Координата X второй точки")
        self.clipper_end_y_label = QLabel("Координата Y второй точки")
        self.clipper_begin_x_entry = QLineEdit()
        self.clipper_begin_y_entry = QLineEdit()
        self.clipper_end_x_entry = QLineEdit()
        self.clipper_end_y_entry = QLineEdit()
        self.draw_clipper_button = QPushButton("Добавить отсекатель")
        self.draw_clipper_button.clicked.connect(self.add_clipper_with_check)
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
        self.clipped_line_segment_color_combo_box.setCurrentIndex(4)

    def compose_color_section_layout(self):
        color_section_layout = QHBoxLayout()
        color_label_section_layout = QVBoxLayout()
        for c_label in [self.clipper_color_label,
                        self.line_segment_color_label,
                        self.clipped_line_segment_color_label]:
            color_label_section_layout.addWidget(c_label)
        color_combobox_section_layout = QVBoxLayout()
        for c_combobox in [self.clipper_color_combo_box,
                           self.line_segment_color_combo_box,
                           self.clipped_line_segment_color_combo_box]:
            color_combobox_section_layout.addWidget(c_combobox)
        color_section_layout.addLayout(color_label_section_layout)
        color_section_layout.addLayout(color_combobox_section_layout)
        return color_section_layout

    def compose_line_section_layout(self):
        line_section_layout = QVBoxLayout()
        line_columns_section_layout = QHBoxLayout()
        line_label_section_layout = QVBoxLayout()
        for l_label in [self.line_begin_x_label,
                        self.line_begin_y_label,
                        self.line_end_x_label,
                        self.line_end_y_label]:
            line_label_section_layout.addWidget(l_label)
        line_entry_section_layout = QVBoxLayout()
        for l_entry in [self.line_begin_x_entry,
                        self.line_begin_y_entry,
                        self.line_end_x_entry,
                        self.line_end_y_entry]:
            line_entry_section_layout.addWidget(l_entry)
        line_columns_section_layout.addLayout(line_label_section_layout)
        line_columns_section_layout.addLayout(line_entry_section_layout)
        line_section_layout.addLayout(line_columns_section_layout)
        line_section_layout.addWidget(self.draw_line_button)
        return line_section_layout

    def compose_clipper_section_layout(self):
        clipper_section_layout = QVBoxLayout()
        clipper_columns_section_layout = QHBoxLayout()
        clipper_label_section_layout = QVBoxLayout()
        for c_label in [self.clipper_begin_x_label,
                        self.clipper_begin_y_label,
                        self.clipper_end_x_label,
                        self.clipper_end_y_label]:
            clipper_label_section_layout.addWidget(c_label)
        clipper_entry_section_layout = QVBoxLayout()
        for c_entry in [self.clipper_begin_x_entry,
                        self.clipper_begin_y_entry,
                        self.clipper_end_x_entry,
                        self.clipper_end_y_entry]:
            clipper_entry_section_layout.addWidget(c_entry)
        clipper_columns_section_layout.addLayout(clipper_label_section_layout)
        clipper_columns_section_layout.addLayout(clipper_entry_section_layout)
        clipper_section_layout.addLayout(clipper_columns_section_layout)
        clipper_section_layout.addWidget(self.draw_clipper_button)
        return clipper_section_layout

    def compose(self):
        color_layout = self.compose_color_section_layout()
        line_layout = self.compose_line_section_layout()
        clipper_layout = self.compose_clipper_section_layout()

        left_layout = QVBoxLayout()
        left_layout.addLayout(color_layout)
        left_layout.addLayout(line_layout)
        left_layout.addLayout(clipper_layout)
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

    def add_line_segment_with_check(self):
        message = ""
        x1 = self.line_begin_x_entry.text()
        y1 = self.line_begin_y_entry.text()
        x2 = self.line_end_x_entry.text()
        y2 = self.line_end_y_entry.text()
        if not self.is_int(x1):
            message += f"Координата X начала отрезка не задана или не является целым числом;\n"
        if not self.is_int(y1):
            message += f"Координата Y начала отрезка не задана или не является целым числом;\n"
        if not self.is_int(x2):
            message += f"Координата X конца отрезка не задана или не является целым числом;\n"
        if not self.is_int(y2):
            message += f"Координата Y конца отрезка не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            line = (int(x1), int(y1)), (int(x2), int(y2))
            self.line_segments.add_line_segment(line)  # Список отрезков
            self.canvas.draw_line_segment(*line)  # Полотно

    def add_line_segment_point(self, point: tuple[int, int]):
        if self.line_segments.add_point(point):
            self.canvas.draw_line_segment(*self.line_segments.list[-1])
        else:
            self.canvas.draw_line_segment_point(self.line_segments.list[-1][0])

    def add_clipper_with_check(self):
        message = ""
        x1 = self.clipper_begin_x_entry.text()
        y1 = self.clipper_begin_y_entry.text()
        x2 = self.clipper_end_x_entry.text()
        y2 = self.clipper_end_y_entry.text()
        if not self.is_int(x1):
            message += f"Координата X первой точки не задана или не является целым числом;\n"
        if not self.is_int(y1):
            message += f"Координата Y первой точки не задана или не является целым числом;\n"
        if not self.is_int(x2):
            message += f"Координата X второй точки не задана или не является целым числом;\n"
        if not self.is_int(y2):
            message += f"Координата Y второй точки не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            rect = (int(x1), int(y1)), (int(x2), int(y2))
            self.redraw()
            self.clipper.set(*rect)
            self.canvas.draw_clipper(*rect)

    def add_clipper_point(self, point: tuple[int, int]):
        self.redraw()
        if self.clipper.add_point(point):
            self.canvas.draw_clipper(self.clipper.p1, self.clipper.p2)
        else:
            self.canvas.draw_clipper_point(point)

    def clip(self):
        message = ""
        if not self.clipper.is_valid():
            message = "Не задан отсекатель;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            for line_segment in self.line_segments.list:
                if line_segment[1] is not self.line_segments.none_point:
                    flag, p1, p2 = simple_clip((self.clipper.p1, self.clipper.p2), line_segment)
                    if flag:
                        self.canvas.draw_clipped_line_segment(p1, p2)

    def redraw(self):
        self.canvas.clear_canvas()
        for line_segment in self.line_segments.list:
            p1, p2 = line_segment
            if p2 is not self.line_segments.none_point:
                self.canvas.draw_line_segment(p1, p2)
            else:
                self.canvas.draw_line_segment_point(p1)

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

    def set_line_segment_color(self):
        self.canvas.line_segment_color = self.get_color(self.line_segment_color_combo_box)

    def set_clipped_line_segment_color(self):
        self.canvas.clipped_line_segment_color = self.get_color(self.clipped_line_segment_color_combo_box)

    def clear(self):
        self.line_segments.clear()
        self.clipper.clear()
        self.canvas.clear_canvas()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
