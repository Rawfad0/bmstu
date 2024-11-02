import sys
from PyQt6.QtGui import QAction
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)
from pyqtgraph import PlotWidget, mkPen
from func import solve

points = []


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 1")
        self.resize(1000, 600)

        # Меню и действия меню
        self.menu_action_program_info = QAction("О программе")
        self.menu_action_program_info.triggered.connect(self.action_popup_program_info)
        self.menu_action_author_info = QAction("Об авторе")
        self.menu_action_author_info.triggered.connect(self.action_popup_author_info)
        menu_bar = self.menuBar()
        menu_bar.addActions([self.menu_action_program_info, self.menu_action_author_info])
        # Таблица точек
        self.table = QTableWidget()
        self.set_table()
        # Кнопки управления таблицей точек
        self.add_row_button = QPushButton("Добавить точку")
        self.add_row_button.clicked.connect(self.add_row)
        self.del_row_button = QPushButton("Удалить выбранные точки")
        self.del_row_button.clicked.connect(self.del_row)
        # График
        self.graphWidget = PlotWidget()
        self.graphWidget.setBackground('w')
        self.graphWidget.showGrid(x=True, y=True)
        self.graphWidget.scene().sigMouseClicked.connect(self.mouse_clicked)
        self.plot = self.graphWidget.plot()
        self.triangle = self.graphWidget.plot(pen=mkPen(color=(255, 0, 0)), symbol='x', symbolSize=10)
        self.bisector = self.graphWidget.plot(pen=mkPen(color=(0, 255, 0)), symbol='x', symbolSize=10)
        self.median = self.graphWidget.plot(pen=mkPen(color=(0, 0, 255)), symbol='x', symbolSize=10)
        # Кнопки
        self.solve_button = QPushButton("Решить задачу")
        self.solve_button.clicked.connect(self.draw_solution)
        self.clear_result_button = QPushButton("Убрать ответ")
        self.clear_result_button.clicked.connect(self.clear_result)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)

    def compose(self):
        left_up_layout = QHBoxLayout()
        left_up_layout.addWidget(self.add_row_button)
        left_up_layout.addWidget(self.del_row_button)

        left_layout = QVBoxLayout()
        left_layout.addLayout(left_up_layout)
        left_layout.addWidget(self.table)

        right_layout = QVBoxLayout()
        right_layout.addWidget(self.graphWidget)

        up_layout = QHBoxLayout()
        up_layout.addWidget(self.solve_button)
        up_layout.addWidget(self.clear_result_button)

        down_layout = QHBoxLayout()
        down_layout.addLayout(left_layout)
        down_layout.addLayout(right_layout)

        layout = QVBoxLayout()
        layout.addLayout(up_layout)
        layout.addLayout(down_layout)
        return layout

    def set_table(self):
        self.table.setColumnCount(2)
        self.table.setRowCount(0)
        self.table.setHorizontalHeaderLabels(["X", "Y"])
        self.table.itemChanged.connect(self.update_points)
        self.table.setColumnWidth(0, 150)
        self.table.setColumnWidth(1, 150)

    def add_row(self):
        self.table.insertRow(self.table.rowCount())

    def del_row(self):
        indices = self.table.selectionModel().selectedRows()
        for index in sorted(indices, reverse=True):
            self.table.removeRow(index.row())
        self.update_points()

    def action_popup_program_info(self):
        self.show_popup_window("Программа создана для решения следующей задачи: \n"
                               "Задача №33: На плоскости дано множество точек. \n"
                               "Найти такой треугольник с вершинами в этих точках\n"
                               "у которого угол, образованный медианой и биссектрисой\n"
                               "исходящими из одной вершины, минимален.\n"
                               "Вывести изображение в графическом режиме.\n"
                               "Примечание: треугольник нарисован красным,\n"
                               "медина - синим, биссектриса - зеленым.",
                               "О программе")

    def action_popup_author_info(self):
        self.show_popup_window("Автор программы: Равашдех Фадей ИУ7-45Б",
                               "Об авторе")

    # @staticmethod
    # def action_popup_exit():
    #     msg = QMessageBox()
    #     msg.setWindowTitle("Выход")
    #     msg.setText("Вы действительно хотите выйти")
    #     msg.exec()

    @staticmethod
    def show_popup_window(text, title):
        msg = QMessageBox()
        msg.setWindowTitle(title)
        msg.setText(text)
        msg.exec()

    # def closeEvent(self, event):
    #     self.action_popup_exit()

    def mouse_clicked(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            vb = self.graphWidget.plotItem.vb
            coords = event.scenePos()
            if self.graphWidget.sceneBoundingRect().contains(coords):
                mouse_point = vb.mapSceneToView(coords)
                self.add_point_table(mouse_point.x(), mouse_point.y())

    def add_point_table(self, x, y):
        new_row_count = self.table.rowCount()
        self.table.insertRow(new_row_count)
        self.table.setItem(new_row_count, 0, QTableWidgetItem(f"{x}"))
        self.table.setItem(new_row_count, 1, QTableWidgetItem(f"{y}"))

    @staticmethod
    def is_float(string):
        try:
            float(string)
            return True
        except ValueError:
            return False

    def update_plot(self):
        self.plot.setData([p[0] for p in points], [p[1] for p in points], pen=None, symbol='o', symbolSize=5)

    def update_points(self):
        points.clear()
        for row_i in range(self.table.rowCount()):
            x = self.table.item(row_i, 0)
            y = self.table.item(row_i, 1)
            if x is not None and self.is_float(x.text()) and y is not None and self.is_float(y.text()):
                points.append((float(x.text()), float(y.text())))
        self.update_plot()

    @staticmethod
    def draw_figure(obj, obj_points):
        if len(obj_points) > 0:
            obj_points.append(obj_points[0])
        obj.setData([p[0] for p in obj_points], [p[1] for p in obj_points])

    def draw_solution(self):
        if self.check_points():
            result = solve(points)
            if result is None:
                self.show_popup_window("Не нашлось ни одного треугольника", "Ошибка")
            else:
                triangle, median, bisector, angle = result
                self.draw_figure(self.triangle, triangle)
                self.draw_figure(self.median, median)
                self.draw_figure(self.bisector, bisector)

    def check_points(self):
        message = ""
        points.clear()
        for row_i in range(self.table.rowCount()):
            x = self.table.item(row_i, 0)
            y = self.table.item(row_i, 1)
            if x is None:
                message += f"Точка {row_i + 1}: Координата X не задана;\n"
            elif not self.is_float(x.text()):
                message += f"Точка {row_i + 1}: Координата X не является вещественным числом;\n"
            if y is None:
                message += f"Точка {row_i + 1}: Координата Y не задана;\n"
            elif not self.is_float(y.text()):
                message += f"Точка {row_i + 1}: Координата Y не является вещественным числом;\n"
            if x is not None and self.is_float(x.text()) and y is not None and self.is_float(y.text()):
                point = (float(x.text()), float(y.text()))
                if point in points:
                    message += f"Точка {row_i + 1}: уже существует точка с этими координатами;\n"
                else:
                    points.append((float(x.text()), float(y.text())))
        if len(points) < 3:
            message += "Количество корректных точек меньше трех."
        if message == "":
            return True
        else:
            self.show_popup_window(message, "Ошибка")
            return False

    def clear_result(self):
        self.draw_figure(self.triangle, [])
        self.draw_figure(self.median, [])
        self.draw_figure(self.bisector, [])


app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()
