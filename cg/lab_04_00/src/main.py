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
from .algs import (
    standard_circle,
    standard_ellipse,
    parametric_circle,
    parametric_ellipse,
    bresenham_circle,
    bresenham_ellipse,
)
import matplotlib.pyplot as plt
from time import time


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 4")
        self.resize(1000, 600)

        # Полотно
        self.canvas = Canvas()
        # Выбор алгоритма
        self.algs_label = QLabel("Алгоритм")
        self.algs_combo_box = QComboBox()
        self.algs_combo_box.addItems(["Каноническое ур-е",
                                      "Параметрическое ур-е",
                                      "Алгоритм Брезенхема",
                                      "Библиотечная реализация"])
        # Выбор цвета
        self.color_label = QLabel("Цвет")
        self.color_combo_box = QComboBox()
        self.color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        # Обозначение полей
        self.ellipse_center_x_label = QLabel("Координата X центра")
        self.ellipse_center_y_label = QLabel("Координата Y центра")
        self.ellipse_radius_x_label = QLabel("Радиус Rx")
        self.ellipse_radius_y_label = QLabel("Радиус Ry")
        self.spectre_step_x_label = QLabel("Шаг по X")
        self.spectre_step_y_label = QLabel("Шаг по Y")
        self.spectre_number_label = QLabel("Количество")
        self.spectre_radius_x_label = QLabel("Радиус Rx")
        self.spectre_radius_y_label = QLabel("Радиус Ry")
        # Поля ввода
        self.ellipse_center_x_entry = QLineEdit()
        self.ellipse_center_y_entry = QLineEdit()
        self.ellipse_radius_x_entry = QLineEdit()
        self.ellipse_radius_y_entry = QLineEdit()
        self.spectre_step_x_entry = QLineEdit()
        self.spectre_step_y_entry = QLineEdit()
        self.spectre_number_entry = QLineEdit()
        self.spectre_radius_x_entry = QLineEdit()
        self.spectre_radius_y_entry = QLineEdit()

        self.ellipse_center_x_entry.setText("200")
        self.ellipse_center_y_entry.setText("200")
        self.ellipse_radius_x_entry.setText("100")
        self.ellipse_radius_y_entry.setText("100")
        self.spectre_step_x_entry.setText("10")
        self.spectre_step_y_entry.setText("10")
        self.spectre_number_entry.setText("5")
        self.spectre_radius_x_entry.setText("100")
        self.spectre_radius_y_entry.setText("100")
        # Кнопки
        self.draw_ellipse_button = QPushButton("Построить эллипс")
        self.draw_ellipse_button.clicked.connect(self.draw_ellipse)
        self.draw_spectre_button = QPushButton("Построить спектр")
        self.draw_spectre_button.clicked.connect(self.draw_spectre)
        self.compare_time_button = QPushButton("Сравнение по времени")
        self.compare_time_button.clicked.connect(self.compare_time_circle_spectre)
        self.clear_canvas_button = QPushButton("Очистить")
        self.clear_canvas_button.clicked.connect(self.canvas.clear_canvas)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)

    def compose_ellipse_section_layout(self):
        ellipse_section_layout = QVBoxLayout()
        ellipse_columns_section_layout = QHBoxLayout()
        ellipse_label_section_layout = QVBoxLayout()
        for l_label in [self.ellipse_center_x_label,
                        self.ellipse_center_y_label,
                        self.ellipse_radius_x_label,
                        self.ellipse_radius_y_label]:
            ellipse_label_section_layout.addWidget(l_label)
        ellipse_entry_section_layout = QVBoxLayout()
        for l_entry in [self.ellipse_center_x_entry,
                        self.ellipse_center_y_entry,
                        self.ellipse_radius_x_entry,
                        self.ellipse_radius_y_entry]:
            ellipse_entry_section_layout.addWidget(l_entry)
        ellipse_columns_section_layout.addLayout(ellipse_label_section_layout)
        ellipse_columns_section_layout.addLayout(ellipse_entry_section_layout)
        ellipse_section_layout.addLayout(ellipse_columns_section_layout)
        ellipse_section_layout.addWidget(self.draw_ellipse_button)
        return ellipse_section_layout

    def compose_spectre_section_layout(self):
        spectre_section_layout = QVBoxLayout()
        spectre_columns_section_layout = QHBoxLayout()
        spectre_label_section_layout = QVBoxLayout()
        for s_label in [self.spectre_step_x_label,
                        self.spectre_step_y_label,
                        self.spectre_number_label,
                        self.spectre_radius_x_label,
                        self.spectre_radius_y_label]:
            spectre_label_section_layout.addWidget(s_label)
        spectre_entry_section_layout = QVBoxLayout()
        for s_entry in [self.spectre_step_x_entry,
                        self.spectre_step_y_entry,
                        self.spectre_number_entry,
                        self.spectre_radius_x_entry,
                        self.spectre_radius_y_entry]:
            spectre_entry_section_layout.addWidget(s_entry)
        spectre_columns_section_layout.addLayout(spectre_label_section_layout)
        spectre_columns_section_layout.addLayout(spectre_entry_section_layout)
        spectre_section_layout.addLayout(spectre_columns_section_layout)
        spectre_section_layout.addWidget(self.draw_spectre_button)
        spectre_section_layout.addWidget(self.compare_time_button)
        return spectre_section_layout

    def compose(self):
        left_layout = QVBoxLayout()
        left_layout.addWidget(self.canvas)

        algs_layout = QHBoxLayout()
        algs_layout.addWidget(self.algs_label)
        algs_layout.addWidget(self.algs_combo_box)

        color_layout = QHBoxLayout()
        color_layout.addWidget(self.color_label)
        color_layout.addWidget(self.color_combo_box)

        right_layout = QVBoxLayout()
        right_layout.addLayout(algs_layout)
        right_layout.addLayout(color_layout)
        right_layout.addLayout(self.compose_ellipse_section_layout())
        right_layout.addLayout(self.compose_spectre_section_layout())
        right_layout.addWidget(self.clear_canvas_button)

        layout = QHBoxLayout()
        layout.addLayout(left_layout)
        layout.addLayout(right_layout)
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

    def alg_controller(self, mode="ellipse"):
        ellipse_func_dict = {
            0: standard_ellipse,
            1: parametric_ellipse,
            2: bresenham_ellipse,
            3: self.canvas.draw_ellipse
            }
        circle_func_dict = {
            0: standard_circle,
            1: parametric_circle,
            2: bresenham_circle,
            3: self.canvas.draw_circle
        }
        if mode == "ellipse":
            return ellipse_func_dict[self.algs_combo_box.currentIndex()]
        elif mode == "circle":
            return circle_func_dict[self.algs_combo_box.currentIndex()]

    def color_controller(self):
        color_dict = {
            0: (0, 0, 0),
            1: (255, 255, 255),
            2: (255, 0, 0),
            3: (0, 255, 0),
            4: (0, 0, 255),
        }
        return color_dict[self.color_combo_box.currentIndex()]

    def draw_ellipse(self):
        message = ""
        cx = self.ellipse_center_x_entry.text()
        cy = self.ellipse_center_y_entry.text()
        rx = self.ellipse_radius_x_entry.text()
        ry = self.ellipse_radius_y_entry.text()
        if not self.is_int(cx):
            message += f"Координата X центра эллипса не задана или не является целым числом;\n"
        if not self.is_int(cy):
            message += f"Координата Y центра эллипса не задана или не является целым числом;\n"
        if not self.is_int(rx):
            message += f"Радиус Rx эллипса не задан или не является целым числом;\n"
        if not self.is_int(ry):
            message += f"Радиус Ry эллипса не задан или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            color = self.color_controller()
            if rx == ry:
                # Circe
                func = self.alg_controller("circle")
                func(self.canvas, (int(cx), int(cy)), int(rx), color)
            else:
                # Ellipse
                func = self.alg_controller("ellipse")
                func(self.canvas, (int(cx), int(cy)), (int(rx), int(ry)), color)

    def get_spectre_section_fields(self):
        message = ""
        step_x = self.spectre_step_x_entry.text()
        step_y = self.spectre_step_y_entry.text()
        number = self.spectre_number_entry.text()
        rx = self.spectre_radius_x_entry.text()
        ry = self.spectre_radius_y_entry.text()
        if not self.is_int(step_x):
            message += f"Шаг X между эллипсами не задан или не является целым числом;\n"
        if not self.is_int(step_y):
            message += f"Шаг Y между эллипсами не задан или не является целым числом;\n"
        if not self.is_int(number):
            message += f"Количество эллипсов не задано или не является целым числом;\n"
        if not self.is_int(rx):
            message += f"Начальный радиус Rx эллипса не задан или не является целым числом;\n"
        if not self.is_int(ry):
            message += f"Начальный радиус Rx эллипса не задан или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
            return None
        else:
            return int(step_x), int(step_y), int(number), int(rx), int(ry)

    def draw_spectre(self):
        res = self.get_spectre_section_fields()
        if res is not None:
            color = self.color_controller()
            cx, cy = int(self.canvas.width / 2), int(self.canvas.height / 2)
            step_x, step_y, number, rx, ry = res
            if rx == ry and step_x == step_y:
                # Circe
                func = self.alg_controller("circle")
                for i in range(number):
                    func(self.canvas, (cx, cy), rx, color)
                    rx += step_x
            else:
                # Ellipse
                func = self.alg_controller("ellipse")
                for i in range(number):
                    func(self.canvas, (cx, cy),  (rx, ry), color)
                    rx += step_x
                    ry += step_y

    def compare_time_circle_spectre(self):
        res = self.get_spectre_section_fields()
        if res is not None:
            cx, cy = int(self.canvas.width / 2), int(self.canvas.height / 2)
            step_x, step_y, number, rx, ry = res
            color = self.color_controller()
            times = []
            if rx == ry and step_x == step_y:
                # Circe
                funcs = [standard_circle, parametric_circle, bresenham_circle, self.canvas.draw_circle]
                for func in funcs:
                    func_time = 0.0
                    for i in range(number):
                        tb = time()
                        func(self.canvas, (cx, cy), rx, color)
                        te = time()
                        func_time += te - tb
                        rx += step_x
                    times.append(func_time)
                plt.title(f"Время работы алгоритмов для построения спектра окружностей")
            else:
                # Ellipse
                funcs = [standard_ellipse, parametric_ellipse, bresenham_ellipse, self.canvas.draw_ellipse]
                for func in funcs:
                    func_time = 0.0
                    for i in range(number):
                        tb = time()
                        func(self.canvas, (cx, cy),  (rx, ry), color)
                        te = time()
                        func_time += te - tb
                        rx += step_x
                        ry += step_y
                    times.append(func_time)
                plt.title(f"Время работы алгоритмов для построения спектра эллипсов")
            self.canvas.clear_canvas()
            func_names = ["Каноническое", "Параметрическое", "Брезенхем", "Библиотечная\nфункция"]
            plt.xticks([i for i in range(4)], func_names)
            plt.ylabel("Время")
            plt.bar([i for i in range(4)], times, align="center", alpha=1)
            plt.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
