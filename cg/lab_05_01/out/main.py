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
from .algs import alg_with_ordered_edges_list


class PointList:
    def __init__(self):
        self.points = []

    def add(self, point: tuple[int, int]):
        self.points.append(point)

    def clear(self):
        self.points = []


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 5")
        self.resize(1000, 600)
        self.point_list = PointList()
        # Выбор цвета
        self.color_label = QLabel("Цвет")
        self.color_combo_box = QComboBox()
        self.color_combo_box.addItems(["Черный", "Белый", "Красный", "Зеленый", "Синий"])
        self.color_combo_box.currentIndexChanged.connect(self.set_color)
        # Задержка
        self.delay_label = QLabel("Задержка (мс)")
        self.delay_entry = QLineEdit()
        self.delay_entry.setText("5")
        # Таблица точек
        self.table = QTableWidget()
        self.set_table()
        # Ввод точек
        self.add_point_x_label = QLabel("Координата Y")
        self.add_point_x_entry = QLineEdit()
        self.add_point_y_label = QLabel("Координата X")
        self.add_point_y_entry = QLineEdit()
        # Кнопки управления точками
        self.add_point_button = QPushButton("Добавить точку")
        self.add_point_button.clicked.connect(self.add_point_with_check)
        self.close_polyline_button = QPushButton("Замкнуть ломаную")
        self.close_polyline_button.clicked.connect(self.close_polyline)
        # График
        self.canvas = Canvas(self)
        # Кнопки
        self.clear_button = QPushButton("Очистить")
        self.clear_button.clicked.connect(self.clear)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)

    def compose(self):
        color_layout = QHBoxLayout()
        color_layout.addWidget(self.color_label)
        color_layout.addWidget(self.color_combo_box)

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
        left_layout.addWidget(self.table)
        left_layout.addWidget(self.close_polyline_button)
        left_layout.addWidget(self.clear_button)

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

    def add_point_with_check(self):
        message = ""
        x = self.add_point_x_entry.text()
        y = self.add_point_y_entry.text()
        if not self.is_int(x):
            message += f"Координата X точки не задана или не является целым числом;\n"
        if not self.is_int(y):
            message += f"Координата Y точки не задана или не является целым числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            self.add_point(int(x), int(y))

    def add_point(self, x: int, y: int):
        # Таблица
        row_count = self.table.rowCount()
        self.table.insertRow(row_count)
        self.table.setItem(row_count, 0, QTableWidgetItem(f"{x}"))
        self.table.setItem(row_count, 1, QTableWidgetItem(f"{y}"))
        # Список точек
        point = x, y
        self.point_list.add(point)
        # Полотно
        if row_count == 0:
            self.canvas.draw_point(point)
        else:
            prev_i = row_count - 1
            prev_point = (int(self.table.item(prev_i, 0).text()),
                          int(self.table.item(prev_i, 1).text()))
            self.canvas.draw_line(prev_point, point)

    def fill(self):
        delay = self.delay_entry.text()
        if not self.is_int(delay):
            self.show_popup_window("Задержка не задана или не является целым числом.", "Ошибка")
        else:
            alg_with_ordered_edges_list(self.canvas, self.point_list.points, QApplication.processEvents, int(delay))
            self.point_list.clear()
            self.table.setRowCount(0)

    def close_polyline(self):
        if self.table.item(0, 0) is None:
            self.show_popup_window("Отсутствуют точки ломанной. Нельзя замкнуть.", "Ошибка")
        else:
            x, y = (int(self.table.item(0, 0).text()),
                    int(self.table.item(0, 1).text()))
            self.add_point(x, y)
            self.fill()

    def set_color(self):
        color_dict = {
            0: (0, 0, 0),
            1: (255, 255, 255),
            2: (255, 0, 0),
            3: (0, 255, 0),
            4: (0, 0, 255),
        }
        self.canvas.color = color_dict[self.color_combo_box.currentIndex()]

    def clear(self):
        self.point_list.clear()
        self.table.setRowCount(0)
        self.canvas.clear_canvas()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
