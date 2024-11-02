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
    dda,
    bresenham_float,
    bresenham_int,
    bresenham_antialiasing,
    wu,
)
import matplotlib.pyplot as plt
from math import cos, sin, radians
from time import time


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 3")
        self.resize(1000, 600)

        # Полотно
        self.canvas = Canvas()
        # Выбор алгоритма
        self.algs_label = QLabel("Алгоритм")
        self.algs_combo_box = QComboBox()
        self.algs_combo_box.addItems(["ЦДА",
                                      "Брезенхем (float)",
                                      "Брезенхем (int)",
                                      "Березенхем (с устр.)",
                                      "Алгоритм Ву",
                                      "Библиотечная реализация"])
        # Выбор цвета
        self.color_label = QLabel("Цвет")
        self.color_combo_box = QComboBox()
        self.color_combo_box.addItems(["Черный", "Красный", "Зеленый", "Синий"])
        # Обозначение полей
        self.line_begin_x_label = QLabel("Координата X начала")
        self.line_begin_y_label = QLabel("Координата Y начала")
        self.line_end_x_label = QLabel("Координата X конца")
        self.line_end_y_label = QLabel("Координата Y конца")
        self.spectre_degree_label = QLabel("Угол между отрезками")
        self.spectre_length_label = QLabel("Длина отрезка")
        # Поля ввода
        self.line_begin_x_entry = QLineEdit()
        self.line_begin_y_entry = QLineEdit()
        self.line_end_x_entry = QLineEdit()
        self.line_end_y_entry = QLineEdit()
        self.spectre_degree_entry = QLineEdit()
        self.spectre_length_entry = QLineEdit()
        # Кнопки
        self.draw_line_button = QPushButton("Построить отрезок")
        self.draw_line_button.clicked.connect(self.draw_line)
        self.draw_spectre_button = QPushButton("Построить спектр")
        self.draw_spectre_button.clicked.connect(self.draw_spectre)
        self.compare_time_button = QPushButton("Сравнение по времени")
        self.compare_time_button.clicked.connect(self.compare_time_spectre)
        self.compare_step_button = QPushButton("Сравнение по ступенчатости")
        self.compare_step_button.clicked.connect(self.compare_step_spectre)
        self.clear_canvas_button = QPushButton("Очистить")
        self.clear_canvas_button.clicked.connect(self.canvas.clear_canvas)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)

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

    def compose_spectre_section_layout(self):
        spectre_section_layout = QVBoxLayout()
        spectre_columns_section_layout = QHBoxLayout()
        spectre_label_section_layout = QVBoxLayout()
        for s_label in [self.spectre_degree_label,
                        self.spectre_length_label]:
            spectre_label_section_layout.addWidget(s_label)
        spectre_entry_section_layout = QVBoxLayout()
        for s_entry in [self.spectre_degree_entry,
                        self.spectre_length_entry]:
            spectre_entry_section_layout.addWidget(s_entry)
        spectre_columns_section_layout.addLayout(spectre_label_section_layout)
        spectre_columns_section_layout.addLayout(spectre_entry_section_layout)
        spectre_section_layout.addLayout(spectre_columns_section_layout)
        spectre_section_layout.addWidget(self.draw_spectre_button)
        spectre_section_layout.addWidget(self.compare_time_button)
        spectre_section_layout.addWidget(self.compare_step_button)
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
        right_layout.addLayout(self.compose_line_section_layout())
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

    def alg_controller(self):
        func_dict = {
            0: dda,
            1: bresenham_float,
            2: bresenham_int,
            3: bresenham_antialiasing,
            4: wu,
            5: self.canvas.draw_line,
        }
        return func_dict[self.algs_combo_box.currentIndex()]

    def color_controller(self):
        color_dict = {
            0: (0, 0, 0),
            1: (255, 0, 0),
            2: (0, 255, 0),
            3: (0, 0, 255),
        }
        return color_dict[self.color_combo_box.currentIndex()]

    def draw_line(self):
        message = ""
        xb = self.line_begin_x_entry.text()
        yb = self.line_begin_y_entry.text()
        xe = self.line_end_x_entry.text()
        ye = self.line_end_y_entry.text()
        if not self.is_int(xb):
            message += f"Координата X начала отрезка не задана или не является целым числом;\n"
        if not self.is_int(yb):
            message += f"Координата Y начала отрезка не задана или не является целым числом;\n"
        if not self.is_int(xe):
            message += f"Координата X конца отрезка не задана или не является целым числом;\n"
        if not self.is_int(ye):
            message += f"Координата Y конца отрезка не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            func = self.alg_controller()
            color = self.color_controller()
            func(self.canvas, (int(xb), int(yb)), (int(xe), int(ye)), color)

    def draw_spectre(self):
        message = ""
        degree = self.spectre_degree_entry.text()
        length = self.spectre_length_entry.text()
        if not self.is_int(degree):
            message += f"Угол между отрезками не задан или не является целым числом;\n"
        if not self.is_int(length):
            message += f"Длина отрезков не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            func = self.alg_controller()
            color = self.color_controller()
            xb, yb = self.canvas.width / 2, self.canvas.height / 2
            degree = int(degree)
            length = int(length)
            angle = 0
            while angle < 360:
                xe, ye = xb + length * cos(radians(angle)), yb + length * sin(radians(angle))
                func(self.canvas, (int(xb), int(yb)), (int(xe), int(ye)), color, "draw")
                angle += degree

    def compare_time_spectre(self):
        message = ""
        degree = self.spectre_degree_entry.text()
        length = self.spectre_length_entry.text()
        if not self.is_int(degree):
            message += f"Угол между отрезками не задан или не является целым числом;\n"
        if not self.is_int(length):
            message += f"Длина отрезков не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            color = self.color_controller()
            xb, yb = self.canvas.width / 2, self.canvas.height / 2
            degree = int(degree)
            length = int(length)
            times = []
            funcs = [dda, bresenham_float, bresenham_int, bresenham_antialiasing, wu, self.canvas.draw_line]
            for func in funcs:
                func_time = 0.0
                angle = 0
                while angle < 360:
                    xe, ye = xb + length * cos(radians(angle)), yb + length * sin(radians(angle))
                    tb = time()
                    func(self.canvas, (int(xb), int(yb)), (int(xe), int(ye)), color, "time")
                    te = time()
                    func_time += te - tb
                    angle += degree
                times.append(func_time / (angle // degree))
            self.canvas.clear_canvas()
            plt.title(f"Время работы алгоритмов для построения спектра")
            func_names = ["ЦДА", "Брезенхем\n(float)", "Брезенхем\n(int)",
                          "Брезенхем\n(с устр. ступ.)", "Ву", "Библиотечная\nфункция"]
            plt.xticks([i for i in range(6)], func_names)
            plt.ylabel("Время")
            plt.bar([i for i in range(6)], times, align="center", alpha=1)
            plt.show()

    def compare_step_spectre(self):
        message = ""
        degree = self.spectre_degree_entry.text()
        length = self.spectre_length_entry.text()
        if not self.is_int(degree):
            message += f"Угол между отрезками не задан или не является целым числом;\n"
        if not self.is_int(length):
            message += f"Длина отрезков не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            color = self.color_controller()
            xb = self.canvas.width / 2
            yb = self.canvas.height / 2
            degree = int(degree)
            length = int(length)
            steps = []
            angles = [angle for angle in range(0, 91, degree)]
            funcs = [dda, bresenham_float, bresenham_int, bresenham_antialiasing, wu]
            for i, func in enumerate(funcs):
                func_steps = []
                angle = 0
                while angle < 91:
                    xe, ye = xb + length * cos(radians(angle)), yb + length * sin(radians(angle))
                    func_steps.append(func(self.canvas, (int(xb), int(yb)), (int(xe), int(ye)), color, "step"))
                    angle += degree
                steps.append(func_steps)
            labels = ["ЦДА", "Брезенхем (float)", "Брезенхем (int)", "Брезенхем (с устр. ступ.)", "Ву"]
            for i, func_steps in enumerate(steps):
                plt.plot(angles, func_steps, label=labels[i])
            plt.title("Cтупенчатость")
            plt.legend()
            plt.xticks([i for i in range(0, 91, 5)])
            plt.ylabel("Количество ступенек")
            plt.xlabel("Угол в градусах")
            plt.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
