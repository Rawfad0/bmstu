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
from .alg import float_horizon, rotate_ox, rotate_oy, rotate_oz
from .funcs import functions


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab 9")
        self.resize(1000, 600)
        self.function = None
        self.matrix = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]
        # Выбор цвета
        self.color_label = QLabel("Цвет")
        self.color_combo_box = QComboBox()
        self.color_combo_box.addItems(["Синий", "Черный", "Белый", "Красный", "Зеленый"])
        self.color_combo_box.currentIndexChanged.connect(self.set_color)
        # Выбор функции
        self.function_label = QLabel("Функция")
        self.function_combo_box = QComboBox()
        self.function_combo_box.addItems([key for key in functions.keys()])
        self.function_combo_box.currentIndexChanged.connect(self.set_function)
        # Ввод пределов и шага
        self.x_from_label = QLabel("Предел X от")
        self.x_from_entry = QLineEdit()
        self.x_to_label = QLabel("Предел X до")
        self.x_to_entry = QLineEdit()
        self.x_step_label = QLabel("Шаг X ")
        self.x_step_entry = QLineEdit()
        self.z_from_label = QLabel("Предел Z от")
        self.z_from_entry = QLineEdit()
        self.z_to_label = QLabel("Предел Z до")
        self.z_to_entry = QLineEdit()
        self.z_step_label = QLabel("Шаг Z")
        self.z_step_entry = QLineEdit()
        # Вращение
        self.ox_rotate_label = QLabel("Вращение вокруг OX")
        self.ox_rotate_entry = QLineEdit()
        self.ox_rotate_button = QPushButton("Повернуть")
        self.ox_rotate_button.clicked.connect(self.rotate_ox)
        self.oy_rotate_label = QLabel("Вращение вокруг OY")
        self.oy_rotate_entry = QLineEdit()
        self.oy_rotate_button = QPushButton("Повернуть")
        self.oy_rotate_button.clicked.connect(self.rotate_oy)
        self.oz_rotate_label = QLabel("Вращение вокруг OZ")
        self.oz_rotate_entry = QLineEdit()
        self.oz_rotate_button = QPushButton("Повернуть")
        self.oz_rotate_button.clicked.connect(self.rotate_oz)
        # Масштабирование
        self.scale_label = QLabel("Коэффициент масштабирования")
        self.scale_entry = QLineEdit()
        # Кнопки
        self.draw_button = QPushButton("Построить")
        self.draw_button.clicked.connect(self.draw)
        self.clear_button = QPushButton("Очистить")
        self.clear_button.clicked.connect(self.clear)
        self.reset_button = QPushButton("Обнулить поворот")
        self.reset_button.clicked.connect(self.reset)
        # График
        self.canvas = Canvas(self)
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)
        # Предустановленные значения
        self.set_function()
        self.x_from_entry.setText("-30")
        self.z_from_entry.setText("-30")
        self.x_to_entry.setText("30")
        self.z_to_entry.setText("30")
        self.x_step_entry.setText("0.3")
        self.z_step_entry.setText("0.3")
        self.ox_rotate_entry.setText("15")
        self.oy_rotate_entry.setText("15")
        self.oz_rotate_entry.setText("15")
        self.scale_entry.setText("10")

    def compose_limits_section_layout(self):
        limits_columns_section_layout = QHBoxLayout()
        limits_label_section_layout = QVBoxLayout()
        limits_label_section_layout.addWidget(self.x_from_label)
        limits_label_section_layout.addWidget(self.x_to_label)
        limits_label_section_layout.addWidget(self.x_step_label)
        limits_label_section_layout.addWidget(self.z_from_label)
        limits_label_section_layout.addWidget(self.z_to_label)
        limits_label_section_layout.addWidget(self.z_step_label)
        limits_entry_section_layout = QVBoxLayout()
        limits_entry_section_layout.addWidget(self.x_from_entry)
        limits_entry_section_layout.addWidget(self.x_to_entry)
        limits_entry_section_layout.addWidget(self.x_step_entry)
        limits_entry_section_layout.addWidget(self.z_from_entry)
        limits_entry_section_layout.addWidget(self.z_to_entry)
        limits_entry_section_layout.addWidget(self.z_step_entry)
        limits_columns_section_layout.addLayout(limits_label_section_layout)
        limits_columns_section_layout.addLayout(limits_entry_section_layout)
        return limits_columns_section_layout

    def compose_rotate_section_layout(self):
        rotate_columns_section_layout = QHBoxLayout()
        rotate_label_section_layout = QVBoxLayout()
        rotate_label_section_layout.addWidget(self.ox_rotate_label)
        rotate_label_section_layout.addWidget(self.oy_rotate_label)
        rotate_label_section_layout.addWidget(self.oz_rotate_label)
        rotate_entry_section_layout = QVBoxLayout()
        rotate_entry_section_layout.addWidget(self.ox_rotate_entry)
        rotate_entry_section_layout.addWidget(self.oy_rotate_entry)
        rotate_entry_section_layout.addWidget(self.oz_rotate_entry)
        rotate_button_section_layout = QVBoxLayout()
        rotate_button_section_layout.addWidget(self.ox_rotate_button)
        rotate_button_section_layout.addWidget(self.oy_rotate_button)
        rotate_button_section_layout.addWidget(self.oz_rotate_button)
        rotate_columns_section_layout.addLayout(rotate_label_section_layout)
        rotate_columns_section_layout.addLayout(rotate_entry_section_layout)
        rotate_columns_section_layout.addLayout(rotate_button_section_layout)
        return rotate_columns_section_layout

    def compose(self):
        color_layout = QHBoxLayout()
        color_layout.addWidget(self.color_label)
        color_layout.addWidget(self.color_combo_box)
        function_layout = QHBoxLayout()
        function_layout.addWidget(self.function_label)
        function_layout.addWidget(self.function_combo_box)
        scale_layout = QHBoxLayout()
        scale_layout.addWidget(self.scale_label)
        scale_layout.addWidget(self.scale_entry)
        left_layout = QVBoxLayout()
        left_layout.addLayout(color_layout)
        left_layout.addLayout(self.compose_limits_section_layout())
        left_layout.addLayout(function_layout)
        left_layout.addLayout(self.compose_rotate_section_layout())
        left_layout.addLayout(scale_layout)
        left_layout.addWidget(self.draw_button)
        left_layout.addWidget(self.clear_button)
        left_layout.addWidget(self.reset_button)
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
    def is_float(string):
        try:
            float(string)
            return True
        except ValueError:
            return False

    def rotate_ox(self):
        message = ""
        oxr = self.ox_rotate_entry.text()
        if not self.is_float(oxr):
            message = "Поворот вокруг OX не задан\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            self.matrix = rotate_ox(self.matrix, float(oxr))

    def rotate_oy(self):
        message = ""
        oyr = self.oy_rotate_entry.text()
        if not self.is_float(oyr):
            message = "Поворот вокруг OY не задан\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            self.matrix = rotate_oy(self.matrix, float(oyr))

    def rotate_oz(self):
        message = ""
        ozr = self.oz_rotate_entry.text()
        if not self.is_float(ozr):
            message = "Поворот вокруг OZ не задан\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            self.matrix = rotate_oz(self.matrix, float(ozr))

    def draw(self):
        message = ""
        x_from = self.x_from_entry.text()
        x_to = self.x_to_entry.text()
        x_step = self.x_step_entry.text()
        z_from = self.z_from_entry.text()
        z_to = self.z_to_entry.text()
        z_step = self.z_step_entry.text()
        scale = self.scale_entry.text()
        oxr = self.ox_rotate_entry.text()
        oyr = self.oy_rotate_entry.text()
        ozr = self.oz_rotate_entry.text()
        if not self.is_float(x_from):
            message = "Предел Х от не задан\n"
        if not self.is_float(x_to):
            message = "Предел Х до не задан\n"
        if not self.is_float(x_step):
            message = "Шаг Х не задан\n"
        if not self.is_float(z_from):
            message = "Предел Z от не задан\n"
        if not self.is_float(z_to):
            message = "Предел Z до не задан\n"
        if not self.is_float(z_step):
            message = "Шаг Z не задан\n"
        if not self.is_float(scale):
            message = "Масштабирование не задано\n"
        if not self.is_float(oxr):
            message = "Поворот вокруг OX не задан\n"
        if not self.is_float(oyr):
            message = "Поворот вокруг OY не задан\n"
        if not self.is_float(ozr):
            message = "Поворот вокруг OZ не задан\n"
        if message != "":
            self.show_popup_window(message, "Ошибка")
        else:
            self.clear()
            func = self.function
            float_horizon(self.canvas, func, self.matrix,
                          [float(x_from),float(x_to), float(x_step)],
                          [float(z_from), float(z_to), float(z_step)],
                          float(scale))

    @staticmethod
    def get_color(color_combo_box):
        color_dict = {
            0: (0, 0, 255),
            1: (0, 0, 0),
            2: (255, 255, 255),
            3: (255, 0, 0),
            4: (0, 255, 0),
            5: (0, 0, 255),
        }
        return color_dict[color_combo_box.currentIndex()]

    def set_color(self):
        self.canvas.color = self.get_color(self.color_combo_box)

    def set_function(self):
        self.function = functions[self.function_combo_box.currentText()]

    def clear(self):
        self.canvas.clear_canvas()

    def reset(self):
        self.matrix = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        ]


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
