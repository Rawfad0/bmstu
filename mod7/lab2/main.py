import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QSpinBox, QPushButton, QTableWidget, QTableWidgetItem,
    QMessageBox, QHeaderView
)
from PyQt5.QtCore import Qt
from probs import solve_probs, solve_times
from matrix import matrix


def safe_str_to_float(s):
    """Преобразует строку в float, допускает ',' как десятичный разделитель."""
    if s is None:
        raise ValueError("Пустое значение")
    s = s.strip()
    if s == "":
        raise ValueError("Пустая строка")
    s = s.replace(",", ".")
    return float(s)


class MatrixWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("ЛР №2")
        self.resize(900, 400)
        self._build_ui()

    def _build_ui(self):
        main_layout = QVBoxLayout()
        top_row = QHBoxLayout()

        top_row.addWidget(QLabel("Размер:"))
        self.spin_n = QSpinBox()
        self.spin_n.setRange(1, 10)
        self.spin_n.setValue(len(matrix))
        self.spin_n.valueChanged.connect(self.create_matrix_table)
        top_row.addWidget(self.spin_n)

        btn_read = QPushButton("Рассчитать")
        btn_read.clicked.connect(self.on_read_matrix)
        top_row.addWidget(btn_read)

        top_row.addStretch()
        main_layout.addLayout(top_row)

        # Основная таблица n×n
        body_row = QVBoxLayout()
        self.table_nxn = QTableWidget()
        self.table_nxn.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table_nxn.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        body_row.addWidget(self.table_nxn)

        # Таблица 2×n
        self.table_2n = QTableWidget()
        self.table_2n.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table_2n.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        body_row.addWidget(self.table_2n)

        main_layout.addLayout(body_row)
        self.setLayout(main_layout)

        # Инициализация при старте
        self.create_matrix_table()

    def _fill_table(self, table):
        n = table.rowCount()
        for i in range(n):
            for j in range(n):
                if i == j:
                    x = 0
                else:
                    x = 1
                x = matrix[i][j]
                item = QTableWidgetItem(f"{x:.2f}")
                item.setTextAlignment(Qt.AlignCenter)
                table.setItem(i, j, item)

    def fill_p(self, values):
        n = self.table_2n.columnCount()
        if len(values) != n:
            raise ValueError(f"Длина массива должна быть {n}, а получено {len(values)}")

        for j, val in enumerate(values):
            item = QTableWidgetItem(f"{val:.3f}")
            item.setTextAlignment(Qt.AlignCenter)
            self.table_2n.setItem(0, j, item)

    def fill_t(self, values):
        n = self.table_2n.columnCount()
        if len(values) != n:
            raise ValueError(f"Длина массива должна быть {n}, а получено {len(values)}")

        for j, val in enumerate(values):
            item = QTableWidgetItem(f"{val:.3f}")
            item.setTextAlignment(Qt.AlignCenter)
            self.table_2n.setItem(1, j, item)

    def create_matrix_table(self):
        n = self.spin_n.value()
        self.table_nxn.clear()
        self.table_nxn.setRowCount(n)
        self.table_nxn.setColumnCount(n)
        self.table_nxn.setHorizontalHeaderLabels([f"{j+1}" for j in range(n)])
        self.table_nxn.setVerticalHeaderLabels([f"{i+1}" for i in range(n)])
        self._fill_table(self.table_nxn)

        # обновляем правую таблицу под размер 2×n
        self.table_2n.clear()
        self.table_2n.setRowCount(2)
        self.table_2n.setColumnCount(n)
        self.table_2n.setHorizontalHeaderLabels([f"{j+1}" for j in range(n)])
        self.table_2n.setVerticalHeaderLabels(["P", "t"])

    def read_matrix(self):
        """Считывает матрицу n×n как список списков float."""
        n_rows = self.table_nxn.rowCount()
        n_cols = self.table_nxn.columnCount()
        matrix = []
        for i in range(n_rows):
            row = []
            for j in range(n_cols):
                item = self.table_nxn.item(i, j)
                text = item.text() if item is not None else ""
                try:
                    val = safe_str_to_float(text)
                except Exception as e:
                    raise ValueError(f"Невалидное значение в ячейке ({i+1},{j+1}): '{text}'") from e
                row.append(val)
            matrix.append(row)
        return matrix

    def on_read_matrix(self):
        try:
            m = self.read_matrix()
        except ValueError as e:
            QMessageBox.warning(self, "Ошибка ввода", str(e))
            return

        p = solve_probs(m)
        self.fill_p(p)

        t = solve_times(m)
        self.fill_t(t)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MatrixWindow()
    w.show()
    sys.exit(app.exec_())
