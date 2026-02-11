import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QLineEdit,
    QHBoxLayout, QVBoxLayout, QPushButton
)
from PyQt5.QtCore import Qt
import numpy.random as nr


class UniformGenerator:
    def __init__(self, mid, deviation):
        self.a = mid - deviation
        self.b = mid + deviation

    def generate(self):
        return nr.uniform(self.a, self.b)


class MassServiceSystem:
    def __init__(
            self,
            request_number: int,
            request_generator: UniformGenerator,
            operator1_generator: UniformGenerator,
            operator2_generator: UniformGenerator,
            operator3_generator: UniformGenerator,
            computer1_process_time: float,
            computer2_process_time: float,
    ):
        self._req_n = request_number
        self._req_passed = 0
        self._req_dos = 0
        self._req_gen = request_generator
        self._op_gens = [operator1_generator, operator2_generator, operator3_generator]
        self._op_status = [0, 0, 0]

    def generate_request(self):
        self._req_n -= 1
        for i in range(len(self._op_status)):
            if self._op_status[i] == 0:
                self._op_status[i] = 1
                return i
        self._req_dos += 1
        return None

    def operate_request(self, n):
        self._op_status[n] = 0
        self._req_passed += 1

    @staticmethod
    def get_min_time_i(times):
        i_min = 0
        for i in range(len(times)):
            if times[i] is not None and times[i] < times[i_min]:
                i_min = i
        return i_min

    def model(self):
        times = [None, None, None, None]
        times[0] = self._req_gen.generate()
        while self._req_n > 0:
            print(self._req_n, self._req_passed, self._req_dos, times, self._op_status)
            i_min = self.get_min_time_i(times)
            if i_min == 0:
                res = self.generate_request()
                if res is not None:
                    times[1 + res] = times[0] + self._op_gens[res].generate()
                times[0] += self._req_gen.generate()
            else:
                self.operate_request(i_min - 1)
                times[i_min] = None

        return self._req_passed, self._req_dos


def check_int(str):
    try:
        res = int(str)
        return res
    except Exception as ex:
        print(f"{str} to int causing {Exception}")
        return None


def check_float(str):
    try:
        res = float(str)
        return res
    except Exception as ex:
        print(f"{str} to float causing {Exception}")
        return None


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Лабораторная работа 5")

        root = QVBoxLayout()

        req_row = QHBoxLayout()
        req_row.addWidget(QLabel("Количество заявок:"))
        self.requests_input = QLineEdit()
        self.requests_input.setText("300")
        req_row.addWidget(self.requests_input)
        root.addLayout(req_row)

        row = QHBoxLayout()
        row.addWidget(QLabel(f"Генератор:"))
        a = QLineEdit()
        a.setText("10")
        pm = QLabel(" ± ")
        b = QLineEdit()
        b.setText("2")
        row.addWidget(a)
        row.addWidget(pm)
        row.addWidget(b)
        self.generator = (a, b)
        root.addLayout(row)

        ops_box = QVBoxLayout()
        ops_box.addWidget(QLabel("<b>Операторы</b>"))

        self.operator_inputs = []
        for i in range(1, 4):
            row = QHBoxLayout()
            row.addWidget(QLabel(f"Оператор {i}:"))
            a = QLineEdit()
            pm = QLabel(" ± ")
            b = QLineEdit()
            row.addWidget(a)
            row.addWidget(pm)
            row.addWidget(b)
            self.operator_inputs.append((a, b))
            ops_box.addLayout(row)
        root.addLayout(ops_box)

        self.operator_inputs[0][0].setText("20")
        self.operator_inputs[0][1].setText("5")
        self.operator_inputs[1][0].setText("40")
        self.operator_inputs[1][1].setText("10")
        self.operator_inputs[2][0].setText("40")
        self.operator_inputs[2][1].setText("20")

        pcs_box = QVBoxLayout()
        pcs_box.addWidget(QLabel("<b>Компьютеры</b>"))

        self.computer_inputs = []
        for i in range(1, 3):
            row = QHBoxLayout()
            row.addWidget(QLabel(f"Компьютер {i}:"))
            c = QLineEdit()
            row.addWidget(c)
            self.computer_inputs.append(c)
            pcs_box.addLayout(row)
        root.addLayout(pcs_box)

        self.computer_inputs[0].setText("15")
        self.computer_inputs[1].setText("30")

        self.calc_button = QPushButton("Рассчитать")
        self.calc_button.clicked.connect(self.calculate)
        root.addWidget(self.calc_button)

        root.addWidget(QLabel("<b>Результат</b>"))
        result_row = QHBoxLayout()

        col_labels = QVBoxLayout()
        col_labels.addWidget(QLabel("Обработано:"))
        col_labels.addWidget(QLabel("Отказано в обслуживании:"))
        result_row.addLayout(col_labels)

        col_values = QVBoxLayout()
        self.processed_value = QLabel("—")
        self.denied_value = QLabel("—")
        col_values.addWidget(self.processed_value)
        col_values.addWidget(self.denied_value)
        result_row.addLayout(col_values)

        col_perc = QVBoxLayout()
        self.processed_percent = QLabel("—%")
        self.denied_percent = QLabel("—%")
        col_perc.addWidget(self.processed_percent)
        col_perc.addWidget(self.denied_percent)
        result_row.addLayout(col_perc)

        root.addLayout(result_row)
        self.setLayout(root)

    def calculate(self):
        x = check_int(self.requests_input.text())
        if x is None:
            return
        request_number = x

        a_edit, b_edit = self.generator
        a = check_float(a_edit.text())
        b = check_float(b_edit.text())
        if a is None or b is None:
            return
        request_generator = UniformGenerator(a, b)

        operators = []
        for a_edit, b_edit in self.operator_inputs:
            a = check_float(a_edit.text())
            b = check_float(b_edit.text())
            if a is None or b is None:
                return
            operators.append((a, b))
        op1, op2, op3 = operators
        operator1_generator = UniformGenerator(*op1)
        operator2_generator = UniformGenerator(*op2)
        operator3_generator = UniformGenerator(*op3)

        computers = []
        for computer_edit in self.computer_inputs:
            x = check_float(computer_edit.text())
            if x is None:
                return
            computers.append(x)
        computer1_process_time, computer2_process_time = computers


        print(
            f"request_number: {request_number}\n"
            f"request_generator: {request_generator}\n",
            f"operator1_generator: {operator1_generator}\n",
            f"operator2_generator: {operator2_generator}\n",
            f"operator3_generator: {operator3_generator}\n",
            f"computer1_process_time: {computer1_process_time}\n",
            f"computer2_process_time: {computer2_process_time}\n"
        )
        mss = MassServiceSystem(
            request_number,
            request_generator,
            operator1_generator,
            operator2_generator,
            operator3_generator,
            computer1_process_time,
            computer2_process_time
        )

        passed, dos = mss.model()

        self.processed_value.setText(f"{passed}")
        # self.processed_percent.setText(f"{100*passed/request_number:.3f}%")
        self.processed_percent.setText(f"{100*(1 - dos/request_number):.3f}%")
        self.denied_value.setText(f"{dos}")
        self.denied_percent.setText(f"{100*dos/request_number:.3f}%")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
