"""
Лабораторная работа №1: Оценка случайности последовательности чисел.
- Таблица с 2 способами: "Табличный" и "Алгоритмический".
- Каждый способ — 3 подколонки: цифры, двузначные, трёхзначные.
- Столбец "Ввод" — для ввода цифры в каждую ячейку (+валидация).
- Последняя строка: результат проверки "случайности" последовательности по своему критерию.
"""

import sys
import random
from PyQt5 import QtWidgets, QtGui, QtCore


def find_min_period_strict(s):
    n = len(s)
    for p in range(1, n//2 + 1):
        ok = True
        for i in range(n - p):
            if s[i] != s[i + p]:
                ok = False
                break
        if ok:
            return p
    return None


def criteria(arr, k):
    print("col", k)
    k2 = 9*10**k / 2
    if len(arr) == 0:
        return 0, 0, 0
    d1 = [(arr[i + 1] - arr[i]) / 2 for i in range(len(arr) - 1)]
    avg_crit = 1 - abs(k2 - sum(arr) / len(arr)) / k2
    avg_d1_crit = 1 - abs(sum(d1) / len(d1)) / (k2 / len(d1))
    print((k2 / len(d1)))
    period_crit = 1 if find_min_period_strict(arr) is None else 0
    criteria = 0.3 * avg_crit + 0.3 * avg_d1_crit + 0.4 * period_crit
    return criteria, avg_crit, avg_d1_crit


class RandNumGen:
    def __init__(self):
        self.rand_nums = []
        with open('random.txt', 'r') as f:
            while line := f.readline():
                self.rand_nums.extend(line.split()[1:])

    def get(self):
        n = self.rand_nums[0]
        del self.rand_nums[0]
        return n


class RandomLabApp(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("LAB №1")
        self.resize(900, 500)

        # Параметры
        self.default_n = 10
        self.threshold_variation_distance = 0.7
        self.seed = 12345
        self.rand_num_gen = RandNumGen()

        self._build_ui()

    def _build_ui(self):
        vbox = QtWidgets.QVBoxLayout(self)

        # Верхняя панель управления
        ctrl = QtWidgets.QHBoxLayout()
        ctrl.addWidget(QtWidgets.QLabel("Строк(>=10):"))
        self.spin_n = QtWidgets.QSpinBox()
        self.spin_n.setRange(10, 1000)
        self.spin_n.setValue(self.default_n)
        ctrl.addWidget(self.spin_n)

        btn_gen = QtWidgets.QPushButton("Сгенерировать")
        btn_gen.clicked.connect(self.generate_table_data)
        ctrl.addWidget(btn_gen)

        btn_clear = QtWidgets.QPushButton("Очистить")
        btn_clear.clicked.connect(self.clear_input_column)
        ctrl.addWidget(btn_clear)

        btn_assess = QtWidgets.QPushButton("Оценить случайность")
        btn_assess.clicked.connect(self.assess_sequences)
        ctrl.addWidget(btn_assess)

        ctrl.addStretch()

        vbox.addLayout(ctrl)

        # Таблица
        self.table = QtWidgets.QTableWidget()
        self.col_names = ["Табл 1", "Табл 2", "Табл 3", "Алг 1", "Алг 2", "Алг 3", "Ввод"]
        self.table.setColumnCount(len(self.col_names))
        self.table.setHorizontalHeaderLabels(self.col_names)
        self.table.verticalHeader().setVisible(False)
        self.table.horizontalHeader().setSectionResizeMode(QtWidgets.QHeaderView.Stretch)
        vbox.addWidget(self.table, 1)

        self._init_table_structure()
        self.generate_table_data()

    def _init_table_structure(self):
        n = self.spin_n.value()
        rows = n + 1
        self.table.setRowCount(rows)

        # Создаём QLineEdit только один раз
        for r in range(n):
            le = QtWidgets.QLineEdit()
            le.setMaxLength(1)
            validator = QtGui.QIntValidator(0, 9, le)
            le.setValidator(validator)
            le.setAlignment(QtCore.Qt.AlignCenter)
            self.table.setCellWidget(r, 6, le)

    def _tabular_number(self, digits_count):
        return self.rand_num_gen.get()[:digits_count]

    def _lcg(self, a=1103515245, c=12345, m=2**31):
        next_seed = (a * self.seed + c) % m
        return next_seed, next_seed

    def generate_table_data(self):
        n = self.spin_n.value()
        if self.table.rowCount() != n + 1:
            self._init_table_structure()

        seed = random.randrange(1, 2 ** 30)

        for r in range(n):
            # Табличный способ
            for i, digits_count in enumerate([1, 2, 3]):
                val = self._tabular_number(digits_count)
                item = self.table.item(r, i)
                if item is None:
                    item = QtWidgets.QTableWidgetItem()
                    self.table.setItem(r, i, item)
                item.setText(str(val))
                item.setFlags(item.flags() & ~QtCore.Qt.ItemIsEditable)

            # Алгоритмический способ
            for j, digits_count in enumerate([1, 2, 3]):
                seed, v = self._lcg(seed)
                if digits_count == 1:
                    num = v % 10
                elif digits_count == 2:
                    num = 10 + (v % 90)
                else:
                    num = 100 + (v % 900)
                col = 3 + j
                item = self.table.item(r, col)
                if item is None:
                    item = QtWidgets.QTableWidgetItem()
                    self.table.setItem(r, col, item)
                item.setText(str(num))
                item.setFlags(item.flags() & ~QtCore.Qt.ItemIsEditable)

        self.assess_sequences()

    def assess_sequences(self):
        n = self.table.rowCount() - 1
        c = self.table.columnCount()
        for i in range(c):
            self.table.setItem(n, i, QtWidgets.QTableWidgetItem(""))
        for col in range(c):
            digits = []
            for r in range(n):
                item = self.table.item(r, col)
                if col == 6:
                    widget = self.table.cellWidget(r, col)
                    if isinstance(widget, QtWidgets.QLineEdit):
                        item = widget
                if item is None:
                    continue
                s = item.text()
                if s.isdigit():
                    digits.append(int(s))
            # критерий
            crit, c1, c2 = criteria(digits, col % 3)
            print(digits, crit, c1, c2)
            crit_txt = f"{crit:.3f}"
            it = QtWidgets.QTableWidgetItem(crit_txt)
            it.setFlags(QtCore.Qt.ItemIsEnabled)
            self.table.setItem(n, col, it)

    def clear_input_column(self):
        rows = self.table.rowCount()
        for r in range(rows - 1):
            widget = self.table.cellWidget(r, 6)
            if isinstance(widget, QtWidgets.QLineEdit):
                widget.clear()


def main():
    app = QtWidgets.QApplication(sys.argv)
    win = RandomLabApp()
    win.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
