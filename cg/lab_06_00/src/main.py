import sys
from PyQt6.QtWidgets import (
    QAbstractItemView,
    QApplication,
    QComboBox,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)
from .draw import Canvas
from .algs import filling_with_seed_point
from .objects import Figure, SeedPoint


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 6")
        self.resize(1000, 600)
        self.figure = Figure()
        self.seed_point = SeedPoint()
        # Выбор цвета
        self.border_color_label = QLabel("Цвет заполнения")
        self.border_color_combo_box = QComboBox()
        self.border_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.border_color_combo_box.currentIndexChanged.connect(self.set_border_color)
        self.fill_color_label = QLabel("Цвет заполнения")
        self.fill_color_combo_box = QComboBox()
        self.fill_color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.fill_color_combo_box.currentIndexChanged.connect(self.set_fill_color)
        # Задержка
        self.delay_label = QLabel("Задержка (мс)")
        self.delay_entry = QLineEdit()
        # Таблица точек
        self.table = QTableWidget()
        self.set_table()
        # Ввод точек
        self.add_point_x_label = QLabel("Координата X")
        self.add_point_x_entry = QLineEdit()
        self.add_point_y_label = QLabel("Координата Y")
        self.add_point_y_entry = QLineEdit()
        # Кнопки управления точками
        self.add_point_button = QPushButton("Добавить точку")
        self.add_point_button.clicked.connect(self.add_point_with_check)
        self.add_seed_point_button = QPushButton("Добавить затравочный пиксель")
        self.add_seed_point_button.clicked.connect(self.add_seed_point)
        self.close_polyline_button = QPushButton("Замкнуть ломаную")
        self.close_polyline_button.clicked.connect(self.close_polyline)
        # Ввод кривых
        self.ellipse_center_x_label = QLabel("Координата X центра")
        self.ellipse_center_y_label = QLabel("Координата Y центра")
        self.ellipse_radius_x_label = QLabel("Радиус Rx")
        self.ellipse_radius_y_label = QLabel("Радиус Ry")
        self.ellipse_center_x_entry = QLineEdit()
        self.ellipse_center_y_entry = QLineEdit()
        self.ellipse_radius_x_entry = QLineEdit()
        self.ellipse_radius_y_entry = QLineEdit()
        self.draw_ellipse_button = QPushButton("Построить эллипс")
        self.draw_ellipse_button.clicked.connect(self.draw_ellipse)
        # Время выполения алгоритма
        self.time_label = QLabel("Время выполнения алгоритма: ")
        # График
        self.canvas = Canvas(self)
        # Кнопки
        self.fill_button = QPushButton("Заполнить")
        self.fill_button.clicked.connect(self.fill)
        self.clear_button = QPushButton("Очистить")
        self.clear_button.clicked.connect(self.clear)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)
        # Предустановленные значения
        self.fill_color_combo_box.setCurrentIndex(4)
        self.delay_entry.setText("25")
        self.add_point_x_entry.setText("300")
        self.add_point_y_entry.setText("300")

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

    def compose(self):
        color_layout = QHBoxLayout()
        color_layout.addWidget(self.border_color_label)
        color_layout.addWidget(self.border_color_combo_box)
        color_layout.addWidget(self.fill_color_label)
        color_layout.addWidget(self.fill_color_combo_box)

        delay_layout = QHBoxLayout()
        delay_layout.addWidget(self.delay_label)
        delay_layout.addWidget(self.delay_entry)

        add_point_layout_labels = QVBoxLayout()
        add_point_layout_labels.addWidget(self.add_point_x_label)
        add_point_layout_labels.addWidget(self.add_point_y_label)
        add_point_layout_entries = QVBoxLayout()
        add_point_layout_entries.addWidget(self.add_point_x_entry)
        add_point_layout_entries.addWidget(self.add_point_y_entry)
        add_point_layout = QHBoxLayout()
        add_point_layout.addLayout(add_point_layout_labels)
        add_point_layout.addLayout(add_point_layout_entries)

        left_layout = QVBoxLayout()
        left_layout.addLayout(color_layout)
        left_layout.addLayout(delay_layout)
        left_layout.addLayout(add_point_layout)
        left_layout.addWidget(self.add_point_button)
        left_layout.addWidget(self.add_seed_point_button)
        left_layout.addWidget(self.table)
        left_layout.addWidget(self.close_polyline_button)
        left_layout.addLayout(self.compose_ellipse_section_layout())
        left_layout.addWidget(self.fill_button)
        left_layout.addWidget(self.clear_button)
        left_layout.addWidget(self.time_label)

        layout = QHBoxLayout()
        layout.addLayout(left_layout)
        layout.addWidget(self.canvas)
        return layout

    def set_table(self):
        self.table.setColumnCount(2)
        self.table.setRowCount(0)
        self.table.setHorizontalHeaderLabels(["X", "Y"])
        self.table.setColumnWidth(0, 150)
        self.table.setColumnWidth(1, 150)
        self.table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

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

    def get_point_with_check(self):
        message = ""
        x = self.add_point_x_entry.text()
        y = self.add_point_y_entry.text()
        if not self.is_int(x):
            message += f"Координата X точки не задана или не является целым числом;\n"
        if not self.is_int(y):
            message += f"Координата Y точки не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
            return None
        else:
            return int(x), int(y)

    def add_point_with_check(self):
        point = self.get_point_with_check()
        if point is not None:
            self.add_point(*point)

    def add_point(self, x: int, y: int):
        # Таблица
        row_count = self.table.rowCount()
        self.table.insertRow(row_count)
        self.table.setItem(row_count, 0, QTableWidgetItem(f"{x}"))
        self.table.setItem(row_count, 1, QTableWidgetItem(f"{y}"))
        # Список точек
        point = x, y
        self.figure.add(point)
        # Полотно
        if row_count == 0:
            self.canvas.draw_border_point(point)
        else:
            prev_i = row_count - 1
            prev_point = (int(self.table.item(prev_i, 0).text()),
                          int(self.table.item(prev_i, 1).text()))
            self.canvas.draw_border_line(prev_point, point)

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
            self.canvas.draw_border_ellipse((int(cx), int(cy)), (int(rx), int(ry)))

    def fill(self):
        message = ""
        delay = self.delay_entry.text()
        if not self.is_int(delay):
            message = "Задержка не задана или не является целым числом;\n"
        if not self.seed_point.is_valid():
            message = "Не задан затравочный пиксель;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            time = filling_with_seed_point(self.canvas, self.seed_point.get(), QApplication.processEvents, int(delay))
            self.time_label.setText(f"Время выполнения алгоритма: {time:.6} (s).")
            self.clear_figure()

    def close_polyline(self):
        if self.table.item(0, 0) is None:
            self.show_popup_window("Отсутствуют точки ломанной. Нельзя замкнуть.", "Ошибка")
        else:
            point = (int(self.table.item(0, 0).text()),
                     int(self.table.item(0, 1).text()))
            prev_i = self.table.rowCount() - 1
            prev_point = (int(self.table.item(prev_i, 0).text()),
                          int(self.table.item(prev_i, 1).text()))
            self.canvas.draw_border_line(prev_point, point)
            self.clear_figure()

    def add_seed_point(self):
        point = self.get_point_with_check()
        if point is not None:
            self.seed_point.set(point)
            self.canvas.draw_fill_point(point)

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

    def set_border_color(self):
        self.canvas.border_color = self.get_color(self.border_color_combo_box)

    def set_fill_color(self):
        self.canvas.fill_color = self.get_color(self.fill_color_combo_box)

    def clear_figure(self):
        self.figure.clear()
        self.table.setRowCount(0)

    def clear(self):
        self.clear_figure()
        self.canvas.clear_canvas()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
