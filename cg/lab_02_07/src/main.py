import sys
from PyQt6.QtGui import QAction
from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QVBoxLayout,
    QWidget,
)
from matplotlib.backends.backend_qtagg import (
    FigureCanvasQTAgg as FigureCanvas,
    NavigationToolbar2QT,
)
from matplotlib.figure import Figure

from .draw import (
    draw_line,
    draw_polygon,
    draw_ellipse,
)
from .p_funcs import (
    move_points,
    rotate_points,
    scale_points
)
from .smile_face import figure, init_figure

commands = []


class MplCanvas(FigureCanvas):

    def __init__(self, width=5, height=4, dpi=200):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)
        super(MplCanvas, self).__init__(fig)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 2")
        self.resize(1000, 600)

        # Меню и действия меню
        self.menu_action_program_info = QAction("О программе")
        self.menu_action_program_info.triggered.connect(self.action_popup_program_info)
        self.menu_action_author_info = QAction("Об авторе")
        self.menu_action_author_info.triggered.connect(self.action_popup_author_info)
        menu_bar = self.menuBar()
        menu_bar.addActions([self.menu_action_program_info, self.menu_action_author_info])
        # График
        self.canvas = MplCanvas(width=6, height=6, dpi=100)
        self.canvas.axes.grid(True)
        self.canvas_toolbar = NavigationToolbar2QT(self.canvas, self)
        # Обозначения полей
        self.move_dx_label = QLabel("Смещение по X")
        self.move_dy_label = QLabel("Смещение по Y")
        self.rotate_center_x_label = QLabel("Координата X центра поворота")
        self.rotate_center_y_label = QLabel("Координата Y центра поворота")
        self.rotate_angle_label = QLabel("Угол поворота (против часовой)")
        self.scale_center_x_label = QLabel("Координата X центра масштабирования")
        self.scale_center_y_label = QLabel("Координата Y центра масштабирования")
        self.scale_kx_label = QLabel("Коэффициент масштабирования по X")
        self.scale_ky_label = QLabel("Коэффициент масштабирования по Y")
        # Поля ввода
        self.move_dx_entry = QLineEdit()
        self.move_dy_entry = QLineEdit()
        self.rotate_center_x_entry = QLineEdit()
        self.rotate_center_y_entry = QLineEdit()
        self.rotate_angle_entry = QLineEdit()
        self.scale_center_x_entry = QLineEdit()
        self.scale_center_y_entry = QLineEdit()
        self.scale_kx_entry = QLineEdit()
        self.scale_ky_entry = QLineEdit()
        # Кнопки
        self.move_button = QPushButton("Перенести")
        self.move_button.clicked.connect(self.move_figure)
        self.rotate_button = QPushButton("Повернуть")
        self.rotate_button.clicked.connect(self.rotate_figure)
        self.scale_button = QPushButton("Масштабировать")
        self.scale_button.clicked.connect(self.scale_figure)
        # Кнопки возврата
        self.restart_button = QPushButton("Вернуть к исходному")
        self.restart_button.clicked.connect(self.restart)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)
        # Создание изображения
        self.plots_triangles = [self.canvas.axes.plot([-20, 20], [-20, 20], 'b')[0]
                                for i in range(len(figure["triangles"]))]
        self.plots_circles = [self.canvas.axes.plot([-20, 20], [-20, 20], 'b')[0]
                              for i in range(len(figure["circles"]))]
        self.plots_lines = [self.canvas.axes.plot([-20, 20], [-20, 20], 'b')[0]
                            for i in range(len(figure["lines"]))]
        self.update_plot()

        if len(commands):
            self.apply_commands()

    def compose_move_section_layout(self):
        move_section_layout = QVBoxLayout()

        move_section_layout_dx = QHBoxLayout()
        move_section_layout_dx.addWidget(self.move_dx_label)
        move_section_layout_dx.addWidget(self.move_dx_entry)

        move_section_layout_dy = QHBoxLayout()
        move_section_layout_dy.addWidget(self.move_dy_label)
        move_section_layout_dy.addWidget(self.move_dy_entry)

        move_section_layout.addLayout(move_section_layout_dx)
        move_section_layout.addLayout(move_section_layout_dy)
        move_section_layout.addWidget(self.move_button)
        return move_section_layout

    def compose_rotate_section_layout(self):
        rotate_section_layout = QVBoxLayout()

        rotate_section_layout_cx = QHBoxLayout()
        rotate_section_layout_cx.addWidget(self.rotate_center_x_label)
        rotate_section_layout_cx.addWidget(self.rotate_center_x_entry)

        rotate_section_layout_cy = QHBoxLayout()
        rotate_section_layout_cy.addWidget(self.rotate_center_y_label)
        rotate_section_layout_cy.addWidget(self.rotate_center_y_entry)

        rotate_section_layout_angle = QHBoxLayout()
        rotate_section_layout_angle.addWidget(self.rotate_angle_label)
        rotate_section_layout_angle.addWidget(self.rotate_angle_entry)

        rotate_section_layout.addLayout(rotate_section_layout_cx)
        rotate_section_layout.addLayout(rotate_section_layout_cy)
        rotate_section_layout.addLayout(rotate_section_layout_angle)
        rotate_section_layout.addWidget(self.rotate_button)
        return rotate_section_layout

    def compose_scale_section_layout(self):
        scale_section_layout = QVBoxLayout()

        scale_section_layout_cx = QHBoxLayout()
        scale_section_layout_cx.addWidget(self.scale_center_x_label)
        scale_section_layout_cx.addWidget(self.scale_center_x_entry)

        scale_section_layout_cy = QHBoxLayout()
        scale_section_layout_cy.addWidget(self.scale_center_y_label)
        scale_section_layout_cy.addWidget(self.scale_center_y_entry)

        scale_section_layout_kx = QHBoxLayout()
        scale_section_layout_kx.addWidget(self.scale_kx_label)
        scale_section_layout_kx.addWidget(self.scale_kx_entry)

        scale_section_layout_ky = QHBoxLayout()
        scale_section_layout_ky.addWidget(self.scale_ky_label)
        scale_section_layout_ky.addWidget(self.scale_ky_entry)

        scale_section_layout.addLayout(scale_section_layout_cx)
        scale_section_layout.addLayout(scale_section_layout_cy)
        scale_section_layout.addLayout(scale_section_layout_kx)
        scale_section_layout.addLayout(scale_section_layout_ky)
        scale_section_layout.addWidget(self.scale_button)
        return scale_section_layout

    def compose(self):
        left_layout = QVBoxLayout()
        left_layout.addLayout(self.compose_move_section_layout())
        left_layout.addLayout(self.compose_rotate_section_layout())
        left_layout.addLayout(self.compose_scale_section_layout())
        # left_layout.addWidget(self.undo_button)
        left_layout.addWidget(self.restart_button)

        right_layout = QVBoxLayout()
        right_layout.addWidget(self.canvas_toolbar)
        right_layout.addWidget(self.canvas)

        layout = QHBoxLayout()
        layout.addLayout(left_layout)
        layout.addLayout(right_layout)
        return layout

    def action_popup_program_info(self):
        self.show_popup_window("Программа создана для решения следующей задачи: \n"
                               "Задача №7: Нарисовать следующий рисунок, затем \n"
                               "осуществить его перенос, масштабирование и поворот.",
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

    @staticmethod
    def is_float(string):
        try:
            float(string)
            return True
        except ValueError:
            return False

    def move_figure(self):
        message = ""
        dx = self.move_dx_entry.text()
        dy = self.move_dy_entry.text()
        if not self.is_float(dx):
            message += f"Смещение по X не задана или не является вещественным числом;\n"
        if not self.is_float(dy):
            message += f"Смещение по Y не задана или не является вещественным числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            for part_type, parts in figure.items():
                for part in parts:
                    move_points(part, float(dx), float(dy))
        self.update_plot()

    def rotate_figure(self):
        message = ""
        rcx = self.rotate_center_x_entry.text()
        rcy = self.rotate_center_y_entry.text()
        ra = self.rotate_angle_entry.text()
        if not self.is_float(rcx):
            message += f"Координата X центра поворота не задана или не является вещественным числом;\n"
        if not self.is_float(rcy):
            message += f"Координата Y центра поворота не задана или не является вещественным числом;\n"
        if not self.is_float(ra):
            message += f"Угол поворота не задан или не является вещественным числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            for part_type, parts in figure.items():
                for part in parts:
                    rotate_points(part, (float(rcx), float(rcy)), float(ra))
        self.update_plot()

    def scale_figure(self):
        message = ""
        scx = self.scale_center_x_entry.text()
        scy = self.scale_center_y_entry.text()
        kx = self.scale_kx_entry.text()
        ky = self.scale_ky_entry.text()
        if not self.is_float(scx):
            message += f"Координата X центра масштабирования не задана или не является вещественным числом;\n"
        if not self.is_float(scy):
            message += f"Координата Y центра масштабирования не задана или не является вещественным числом;\n"
        if not self.is_float(kx):
            message += f"Коэффициент масштабирования X не задан или не является вещественным числом;\n"
        if not self.is_float(ky):
            message += f"Коэффициент масштабирования Y не задан или не является вещественным числом;\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            for part_type, parts in figure.items():
                for part in parts:
                    scale_points(part, (float(scx), float(scy)), (float(kx), float(ky)))
        self.update_plot()

    def update_plot(self):
        for i, part in enumerate(figure["triangles"]):
            draw_polygon(self.plots_triangles[i], part)
        for i, part in enumerate(figure["circles"]):
            draw_ellipse(self.plots_circles[i], *part)
        for i, part in enumerate(figure["lines"]):
            draw_line(self.plots_lines[i], *part)
        self.canvas.draw()

    def restart(self):
        init_figure()
        self.update_plot()


if __name__ == "__main__":
    init_figure()
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
