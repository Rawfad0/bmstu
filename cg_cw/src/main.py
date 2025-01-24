import sys
from PyQt6.QtWidgets import (
    QAbstractItemView,
    QApplication,
    QComboBox,
    QFileDialog,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMessageBox,
    QPushButton,
    QTableWidget,
    QTableWidgetItem,
    QTabWidget,
    QVBoxLayout,
    QWidget,
)
from draw import Canvas, Drawer
from objs import Scene, Camera, WireModel, MeshModel
from objs import translate_tm, rotate_x_tm, rotate_y_tm, rotate_z_tm, scale_tm
from utils import record_procedure_time


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("CW")
        self.resize(1200, 600)
        # Полотно
        self.canvas = Canvas(self)
        self.canvas.clear_canvas()
        #
        self.script = []

        # Выбор камеры
        self.camera_label = QLabel("Камера")
        self.camera_combo_box = QComboBox()
        self.camera_combo_box.addItems(["Основная", "Дополнительная"])
        self.camera_combo_box.currentIndexChanged.connect(self.set_camera)

        # Выбор паттерна
        self.pattern_label = QLabel("Паттерн")
        self.pattern_combo_box = QComboBox()
        self.pattern_combo_box.addItems(["Полностью", "Случайно", "Интервал", "Вертикальные линии", "Горизонтальные линии", "Решетка"])
        self.pattern_combo_box.currentIndexChanged.connect(self.set_pattern)
        self.pattern_arg = QLabel("Параметр")
        self.pattern_arg_entry = QLineEdit()
        self.pattern_arg_entry.clearFocus()
        self.pattern_arg_button = QPushButton("Применить")
        self.pattern_arg_button.clicked.connect(self.set_pattern_arg)
        # Сканировать
        self.scan_button = QPushButton("Сканировать")
        self.scan_button.clicked.connect(self.scan)

        #
        # self.tag_combo_box = QComboBox()
        # self.tag_combo_box.setInsertPolicy(QComboBox.InsertPolicy.InsertAlphabetically)
        # self.tag_combo_box.setEditable(True)

        # Выбор объекта из списка
        self.obj_label = QLabel("Объект")
        self.obj_combo_box = QComboBox()
        self.obj_combo_box.addItems(["Куб", "Тетраэдр", "Квадратная пирамида", "Шестигранная призма"])

        # Таблица объектов
        self.obj_table = QTableWidget()
        self.set_obj_table()
        self.add_object_button = QPushButton("Добавить объект на сцену")
        self.add_object_button.clicked.connect(self.add_object)
        self.del_object_button = QPushButton("Удалить выбранный объект со сцены")
        self.del_object_button.clicked.connect(self.del_object)
        # Перемещение
        self.move_label = QLabel("Перемещение")
        self.move_x_label = QLabel("X")
        self.move_x_entry = QLineEdit()
        self.move_y_label = QLabel("Y")
        self.move_y_entry = QLineEdit()
        self.move_z_label = QLabel("Z")
        self.move_z_entry = QLineEdit()
        self.move_object_button = QPushButton("Переместить объект")
        self.move_object_button.clicked.connect(self.move_object)
        # Поворот
        self.rotate_label = QLabel("Поворот")
        self.rotate_ox_label = QLabel("Вокруг OX")
        self.rotate_ox_entry = QLineEdit()
        self.rotate_oy_label = QLabel("OY")
        self.rotate_oy_entry = QLineEdit()
        self.rotate_oz_label = QLabel("OZ")
        self.rotate_oz_entry = QLineEdit()
        self.rotate_center_label = QLabel("Отн-но точки")
        self.rotate_x_label = QLabel("X")
        self.rotate_x_entry = QLineEdit()
        self.rotate_y_label = QLabel("Y")
        self.rotate_y_entry = QLineEdit()
        self.rotate_z_label = QLabel("Z")
        self.rotate_z_entry = QLineEdit()
        self.rotate_object_button = QPushButton("Повернуть объект")
        self.rotate_object_button.clicked.connect(self.rotate_object)

        # Таблица сценария
        self.script_table = QTableWidget()
        self.set_script_table()
        self.script_dx_label = QLabel("Координаты X")
        self.script_dx_entry = QLineEdit()
        self.script_dy_label = QLabel("Y")
        self.script_dy_entry = QLineEdit()
        self.script_dz_label = QLabel("Z")
        self.script_dz_entry = QLineEdit()
        self.script_lr_label = QLabel("Поворот влево-вправо")
        self.script_lr_entry = QLineEdit()
        self.script_ud_label = QLabel("Поворот вверх-вниз")
        self.script_ud_entry = QLineEdit()
        self.add_point_button = QPushButton("Добавить действие в сценарий")
        self.add_point_button.clicked.connect(self.add_script)
        self.del_point_button = QPushButton("Удалить выбранное действие из сценария")
        self.del_point_button.clicked.connect(self.del_script)
        self.execute_button = QPushButton("Выполнить сценарий")
        self.execute_button.clicked.connect(self.script_exec)

        # Таблица облаков точек
        self.point_cloud_table = QTableWidget()
        self.set_point_cloud_table()
        self.del_point_cloud_button = QPushButton("Удалить выбранное облако точек")
        self.del_point_cloud_button.clicked.connect(self.del_point_cloud)

        # Вкладки
        self.tabs = QTabWidget()
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QWidget()
        self.tabs.resize(300, 200)
        self.tabs.addTab(self.tab1, "Объекты")
        self.tabs.addTab(self.tab2, "Сканирование")
        self.tabs.addTab(self.tab3, "Облака точек")

        self.drawer = Drawer(self.canvas, Scene(), Camera(), Camera())
        self.draw_func = self.drawer.draw
        # Композиция интерфейса
        container = QWidget()
        container.setLayout(self.compose())
        self.setCentralWidget(container)

        # cube = MeshModel()
        # cube.read_from_file("models/cube_mesh_shift.txt")
        # self.drawer.scene.add_obj(cube)

        # cube2 = MeshModel()
        # cube2.read_from_file("models/cube_mesh_shift.txt")
        # cube2.transform(translate_tm((-5, -5, 0)))
        # self.drawer.scene.add_obj(cube2)
        #
        # for i in range(3):
        #     for j in range(3):
        #         cube = MeshModel()
        #         cube.read_from_file("models/cube_mesh_shift.txt")
        #         cube.transform(translate_tm((5*i, 5*j, 0)))
        #         self.drawer.scene.add_obj(cube)
        #
        # self.drawer.camera.move(translate_tm((11.5, 11.5, 25)))
        self.setFocus()
        record_procedure_time(self.drawer.draw, v=True, text="ALL")

    def move_compose(self):
        move_layout = QVBoxLayout()
        move_u_layout = QHBoxLayout()
        move_u_layout.addWidget(self.move_label)
        move_u_layout.addWidget(self.move_object_button)
        move_d_layout = QHBoxLayout()
        move_d_layout.addWidget(self.move_x_label)
        move_d_layout.addWidget(self.move_x_entry)
        move_d_layout.addWidget(self.move_y_label)
        move_d_layout.addWidget(self.move_y_entry)
        move_d_layout.addWidget(self.move_z_label)
        move_d_layout.addWidget(self.move_z_entry)
        move_layout.addLayout(move_u_layout)
        move_layout.addLayout(move_d_layout)
        return move_layout

    def rotate_compose(self):
        rotate_layout = QVBoxLayout()
        rotate_u_layout = QHBoxLayout()
        rotate_u_layout.addWidget(self.rotate_label)
        rotate_u_layout.addWidget(self.rotate_object_button)
        rotate_c_layout = QHBoxLayout()
        rotate_c_layout.addWidget(self.rotate_ox_label)
        rotate_c_layout.addWidget(self.rotate_ox_entry)
        rotate_c_layout.addWidget(self.rotate_oy_label)
        rotate_c_layout.addWidget(self.rotate_oy_entry)
        rotate_c_layout.addWidget(self.rotate_oz_label)
        rotate_c_layout.addWidget(self.rotate_oz_entry)
        rotate_d_layout = QHBoxLayout()
        rotate_d_layout.addWidget(self.rotate_center_label)
        rotate_d_layout.addWidget(self.rotate_x_label)
        rotate_d_layout.addWidget(self.rotate_x_entry)
        rotate_d_layout.addWidget(self.rotate_y_label)
        rotate_d_layout.addWidget(self.rotate_y_entry)
        rotate_d_layout.addWidget(self.rotate_z_label)
        rotate_d_layout.addWidget(self.rotate_z_entry)
        rotate_layout.addLayout(rotate_u_layout)
        rotate_layout.addLayout(rotate_c_layout)
        rotate_layout.addLayout(rotate_d_layout)
        return rotate_layout

    def script_compose(self):
        script_layout = QVBoxLayout()
        script_u_layout = QHBoxLayout()
        script_u_layout.addWidget(self.script_dx_label)
        script_u_layout.addWidget(self.script_dx_entry)
        script_u_layout.addWidget(self.script_dy_label)
        script_u_layout.addWidget(self.script_dy_entry)
        script_u_layout.addWidget(self.script_dz_label)
        script_u_layout.addWidget(self.script_dz_entry)
        script_c_layout = QHBoxLayout()
        script_c_layout.addWidget(self.script_lr_label)
        script_c_layout.addWidget(self.script_lr_entry)
        script_d_layout = QHBoxLayout()
        script_d_layout.addWidget(self.script_ud_label)
        script_d_layout.addWidget(self.script_ud_entry)
        script_layout.addLayout(script_u_layout)
        script_layout.addLayout(script_c_layout)
        script_layout.addLayout(script_d_layout)
        return script_layout

    def compose(self):
        pattern_layout = QHBoxLayout()
        pattern_layout.addWidget(self.pattern_label)
        pattern_layout.addWidget(self.pattern_combo_box)
        pattern_arg_layout = QHBoxLayout()
        pattern_arg_layout.addWidget(self.pattern_arg)
        pattern_arg_layout.addWidget(self.pattern_arg_entry)
        pattern_arg_layout.addWidget(self.pattern_arg_button)

        camera_layout = QHBoxLayout()
        camera_layout.addWidget(self.camera_label)
        camera_layout.addWidget(self.camera_combo_box)

        obj_layout = QHBoxLayout()
        obj_layout.addWidget(self.obj_label)
        obj_layout.addWidget(self.obj_combo_box)

        layout = QHBoxLayout()
        layout.addWidget(self.canvas)
        right_layout = QVBoxLayout()
        layout.addLayout(right_layout)

        self.tab1.layout = QVBoxLayout()
        self.tab1.layout.addLayout(obj_layout)
        self.tab1.layout.addWidget(self.add_object_button)
        self.tab1.layout.addWidget(self.del_object_button)
        self.tab1.layout.addWidget(self.obj_table)
        self.tab1.layout.addLayout(self.move_compose())
        self.tab1.layout.addLayout(self.rotate_compose())
        self.tab1.setLayout(self.tab1.layout)

        self.tab2.layout = QVBoxLayout()
        self.tab2.layout.addLayout(pattern_layout)
        self.tab2.layout.addLayout(pattern_arg_layout)
        self.tab2.layout.addWidget(self.scan_button)
        self.tab2.layout.addLayout(self.script_compose())
        self.tab2.layout.addWidget(self.add_point_button)
        self.tab2.layout.addWidget(self.del_point_button)
        self.tab2.layout.addWidget(self.script_table)
        self.tab2.layout.addWidget(self.execute_button)
        self.tab2.setLayout(self.tab2.layout)

        self.tab3.layout = QVBoxLayout()
        self.tab3.layout.addWidget(self.del_point_cloud_button)
        self.tab3.layout.addWidget(self.point_cloud_table)
        self.tab3.setLayout(self.tab3.layout)

        # right_layout.addWidget(self.tag_combo_box)
        # right_layout.addWidget(self.camera_combo_box)
        right_layout.addLayout(camera_layout)
        right_layout.addWidget(self.tabs)
        return layout

    def set_obj_table(self):
        self.obj_table.setColumnCount(1)
        self.obj_table.setRowCount(0)
        self.obj_table.setHorizontalHeaderLabels(["Модель"])
        # self.obj_table.setColumnWidth(0, 50)
        self.obj_table.setColumnWidth(0, 150)
        self.obj_table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

    def set_script_table(self):
        self.script_table.setColumnCount(5)
        self.script_table.setRowCount(0)
        self.script_table.setHorizontalHeaderLabels(["DX", "DY", "DZ", "LR_rotate", "UD_rotate"])
        self.script_table.setColumnWidth(0, 40)
        self.script_table.setColumnWidth(1, 40)
        self.script_table.setColumnWidth(2, 40)
        self.script_table.setColumnWidth(3, 80)
        self.script_table.setColumnWidth(4, 80)
        self.script_table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

    def set_point_cloud_table(self):
        self.point_cloud_table.setColumnCount(2)
        self.point_cloud_table.setRowCount(0)
        self.point_cloud_table.setHorizontalHeaderLabels(["Источник", "Количество точек"])
        self.point_cloud_table.setColumnWidth(0, 150)
        self.point_cloud_table.setColumnWidth(1, 150)
        self.point_cloud_table.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)

    def add_object(self):
        paths = {
            0: './models/cube.txt',
            1: './models/tetrahedron.txt',
            2: './models/square_pyramid.txt',
            3: './models/hex_prism.txt',
        }
        path = paths[self.obj_combo_box.currentIndex()]
        model = MeshModel()
        name = model.read_from_file(path)
        self.drawer.scene.add_obj(model)
        # таблица
        row_count = self.obj_table.rowCount()
        self.obj_table.insertRow(row_count)
        self.obj_table.setItem(row_count, 0, QTableWidgetItem(f"{name}"))
        # отрисовка
        self.draw()
        self.setFocus()

        # path = QFileDialog.getOpenFileName(directory='./models')[0]
        # print(f"PATH: {path}")
        # if path != "":
        #     model = MeshModel()
        #     name = model.read_from_file(path)
        #     self.drawer.scene.add_obj(model)
        #     # таблица
        #     row_count = self.obj_table.rowCount()
        #     self.obj_table.insertRow(row_count)
        #     self.obj_table.setItem(row_count, 0, QTableWidgetItem(f"{name}"))
        #     # отрисовка
        #     self.draw()

    def del_object(self):
        indices = self.obj_table.selectionModel().selectedRows()
        print(indices)
        for index in sorted(indices, reverse=True):
            self.obj_table.removeRow(index.row())
            del self.drawer.scene.objs[index.row()]
        # self.update_points()
        self.draw()
        self.setFocus()

    def add_script(self):
        dx = self.script_dx_entry.text()
        dy = self.script_dy_entry.text()
        dz = self.script_dz_entry.text()
        lr = self.script_lr_entry.text()
        ud = self.script_ud_entry.text()
        # indices = self.obj_table.selectionModel().selectedRows()
        # print(indices)
        # if len(indices) == 0:
        #     self.show_popup_window("Объект не выбран", "Ошибка")
        if not self.is_float(dx):
            self.show_popup_window("Значение DX должно быть числом", "Ошибка")
        elif not self.is_float(dy):
            self.show_popup_window("Значение DY должно быть числом", "Ошибка")
        elif not self.is_float(dz):
            self.show_popup_window("Значение DZ должно быть числом", "Ошибка")
        elif not self.is_float(lr):
            self.show_popup_window("Значение LR должно быть числом", "Ошибка")
        elif not self.is_float(ud):
            self.show_popup_window("Значение UD должно быть числом", "Ошибка")
        else:
            self.script.append([float(dx), float(dy), float(dz), float(lr), float(ud)])
            # таблица
            row_count = self.script_table.rowCount()
            self.script_table.insertRow(row_count)
            self.script_table.setItem(row_count, 0, QTableWidgetItem(f"{dx}"))
            self.script_table.setItem(row_count, 1, QTableWidgetItem(f"{dy}"))
            self.script_table.setItem(row_count, 2, QTableWidgetItem(f"{dz}"))
            self.script_table.setItem(row_count, 3, QTableWidgetItem(f"{lr}"))
            self.script_table.setItem(row_count, 4, QTableWidgetItem(f"{ud}"))
            # сброс фокуса
            self.script_dx_entry.clearFocus()
            self.script_dy_entry.clearFocus()
            self.script_dz_entry.clearFocus()
            self.script_lr_entry.clearFocus()
            self.script_ud_entry.clearFocus()
            # self.draw()
            self.setFocus()

    def del_script(self):
        indices = self.script_table.selectionModel().selectedRows()
        print(indices)
        for index in sorted(indices, reverse=True):
            self.script_table.removeRow(index.row())
            del self.script[index.row()]
            # del self.drawer.scene.objs[index.row()]
        # self.draw()
        self.setFocus()

    def scan(self):
        self.drawer.scan(self.add_point_cloud)
        self.draw()
        self.setFocus()

    def script_exec(self):
        if len(self.script) == 0:
            self.show_popup_window("Не заданы шаги сценария", "Ошибка")
        elif len(self.drawer.scene.objs) == 0:
            self.show_popup_window("Не заданы объекты сцены", "Ошибка")
        else:
            self.drawer.script_exec(self.script)
            # таблица
            row_count = self.point_cloud_table.rowCount()
            self.point_cloud_table.insertRow(row_count)
            self.point_cloud_table.setItem(row_count, 0, QTableWidgetItem(f"script"))
            pc_len = len(self.drawer.scene.point_clouds[-1].points)
            self.point_cloud_table.setItem(row_count, 1, QTableWidgetItem(f"{pc_len}"))
            self.draw()
            self.setFocus()

    def add_point_cloud(self):
        row_count = self.point_cloud_table.rowCount()
        self.point_cloud_table.insertRow(row_count)
        self.point_cloud_table.setItem(row_count, 0, QTableWidgetItem(f"scan"))
        pc_len = len(self.drawer.scene.point_clouds[-1].points)
        self.point_cloud_table.setItem(row_count, 1, QTableWidgetItem(f"{pc_len}"))

    def del_point_cloud(self):
        indices = self.point_cloud_table.selectionModel().selectedRows()
        print(indices)
        for index in sorted(indices, reverse=True):
            self.point_cloud_table.removeRow(index.row())
            del self.drawer.scene.point_clouds[index.row()]
        self.draw()
        self.setFocus()

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

    @staticmethod
    def is_float(string):
        try:
            float(string)
            return True
        except ValueError:
            return False

    def keyPressEvent(self, event):
        print(event.key())
        c_id = self.camera_combo_box.currentIndex()
        cams = {
            0: self.drawer.camera,
            1: self.drawer.camera2,
        }
        keys = {
            # 87: ['W', self.drawer.camera.move, translate_tm((0, 0, 1))],
            # 65: ['A', self.drawer.camera.move, translate_tm((-1, 0, 0))],
            # 83: ['S', self.drawer.camera.move, translate_tm((0, 0, -1))],
            # 68: ['D', self.drawer.camera.move, translate_tm((1, 0, 0))],
            # 81: ['Q', self.drawer.camera.move, translate_tm((0, 1, 0))],
            # 69: ['E', self.drawer.camera.move, translate_tm((0, -1, 0))],
            # 16777235: ['up', cams[c_id].rotate, rotate_x_tm(10)],
            # 16777234: ['left', cams[c_id].rotate, rotate_z_tm(10)],
            # 16777237: ['down', cams[c_id].rotate, rotate_x_tm(-10)],
            # 16777236: ['right', cams[c_id].rotate, rotate_z_tm(-10)],
            87: ['W', cams[c_id].move_up_down, -1],
            65: ['A', cams[c_id].move_left_right, -1],
            83: ['S', cams[c_id].move_up_down, 1],
            68: ['D', cams[c_id].move_left_right, 1],
            81: ['Q', cams[c_id].move_forward_back, 1],
            69: ['E', cams[c_id].move_forward_back, -1],
            16777235: ['up', cams[c_id].rotate_up_down, 10],
            16777234: ['left', cams[c_id].rotate_left_right, 10],
            16777237: ['down', cams[c_id].rotate_up_down, -10],
            16777236: ['right', cams[c_id].rotate_left_right, -10],
        }
        key = event.key()
        if key in keys:
            f = keys[key]
            f[1](f[2])
            self.draw()

    def move_object(self):
        dx = self.move_x_entry.text()
        dy = self.move_y_entry.text()
        dz = self.move_z_entry.text()
        indices = self.obj_table.selectionModel().selectedRows()
        print(indices)
        if len(indices) == 0:
            self.show_popup_window("Объект не выбран", "Ошибка")
        elif not self.is_float(dx):
            self.show_popup_window("X должен быть числом", "Ошибка")
        elif not self.is_float(dy):
            self.show_popup_window("Y должен быть числом", "Ошибка")
        elif not self.is_float(dz):
            self.show_popup_window("Z должен быть числом", "Ошибка")
        else:
            print("select", indices[0].row())
            self.drawer.scene.objs[indices[0].row()].transform(translate_tm((float(dx), float(dy), float(dz))))
            self.move_x_entry.clearFocus()
            self.move_y_entry.clearFocus()
            self.move_z_entry.clearFocus()
            self.draw()

    def rotate_object(self):
        rx = self.rotate_ox_entry.text()
        ry = self.rotate_oy_entry.text()
        rz = self.rotate_oz_entry.text()
        cx = self.rotate_x_entry.text()
        cy = self.rotate_y_entry.text()
        cz = self.rotate_z_entry.text()
        indices = self.obj_table.selectionModel().selectedRows()
        print(indices)
        if len(indices) == 0:
            self.show_popup_window("Объект не выбран", "Ошибка")
        elif not self.is_float(rx):
            self.show_popup_window("Значение OX должно быть числом", "Ошибка")
        elif not self.is_float(ry):
            self.show_popup_window("Значение OY должно быть числом", "Ошибка")
        elif not self.is_float(rz):
            self.show_popup_window("Значение OZ должно быть числом", "Ошибка")
        elif not self.is_float(cx):
            self.show_popup_window("Значение CX должно быть числом", "Ошибка")
        elif not self.is_float(cy):
            self.show_popup_window("Значение CY должно быть числом", "Ошибка")
        elif not self.is_float(cz):
            self.show_popup_window("Значение CZ должно быть числом", "Ошибка")
        else:
            print("select", indices[0].row())
            self.drawer.scene.objs[indices[0].row()].transform(translate_tm((-float(cx), -float(cy), -float(cz))))
            self.drawer.scene.objs[indices[0].row()].transform(rotate_x_tm(float(rx)))
            self.drawer.scene.objs[indices[0].row()].transform(rotate_x_tm(float(ry)))
            self.drawer.scene.objs[indices[0].row()].transform(rotate_x_tm(float(rz)))
            self.drawer.scene.objs[indices[0].row()].transform(translate_tm((float(cx), float(cy), float(cz))))
            self.rotate_ox_entry.clearFocus()
            self.rotate_oy_entry.clearFocus()
            self.rotate_oz_entry.clearFocus()
            self.rotate_x_entry.clearFocus()
            self.rotate_y_entry.clearFocus()
            self.rotate_z_entry.clearFocus()
            self.draw()

    def set_camera(self):
        camera_dict = {
            0: self.drawer.draw,
            1: self.drawer.draw_points,
        }
        self.draw_func = camera_dict[self.camera_combo_box.currentIndex()]
        self.draw()

    def set_pattern(self):
        pattern_dict = {
            0: self.drawer.ray_tracing,
            1: self.drawer.random_ray_tracing,
            2: self.drawer.lidar_eq_dist,
            3: self.drawer.lidar_vertical_lines,
            4: self.drawer.lidar_horizontal_lines,
            5: self.drawer.lidar_ort_grid
        }
        self.drawer.pattern = pattern_dict[self.pattern_combo_box.currentIndex()]
        self.drawer.pattern_arg = None
        self.draw()

    def set_pattern_arg(self):
        if self.pattern_combo_box.currentIndex() != 0:
            s = self.pattern_arg_entry.text()
            if not self.is_int(s):
                self.drawer.pattern_arg = None
                self.show_popup_window("Аргумент должен быть натуральным числом", "Ошибка")
            elif int(s) <= 0:
                self.drawer.pattern_arg = None
                self.show_popup_window("Аргумент должен быть натуральным числом", "Ошибка")
            elif self.pattern_combo_box.currentIndex() == 0:
                self.drawer.pattern_arg = None
            elif self.pattern_combo_box.currentIndex() == 1 and int(s) > self.drawer.height * self.drawer.width:
                self.drawer.pattern_arg = None
                self.show_popup_window(
                    f"Аргумент для данного паттерна должен быть не больше, чем {self.drawer.height * self.drawer.width}",
                    "Ошибка")
            elif self.pattern_combo_box.currentIndex() == 2 and int(s) > self.drawer.height * self.drawer.width:
                self.drawer.pattern_arg = None
                self.show_popup_window(
                    f"Аргумент для данного паттерна должен быть не больше, чем {self.drawer.height * self.drawer.width}",
                    "Ошибка")
            else:
                self.drawer.pattern_arg = int(s)
            # else:
            #     self.drawer.pattern_arg = None
            # self.pattern_arg_entry.deselect()
            # QLineEdit.deselect(self.pattern_arg_entry)
        self.pattern_arg_entry.clearFocus()
        self.draw()

    def draw(self):
        record_procedure_time(self.draw_func, v=True)
        # record_procedure_time(self.drawer.draw, v=True)

    def redraw(self):
        self.canvas.clear_canvas()
        self.drawer.draw()

    def clear(self):
        self.canvas.clear_canvas()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
