import random
import sys
from typing import List, Optional
import numpy.random as nr

from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QLineEdit,
    QHBoxLayout, QVBoxLayout, QPushButton
)
# from PyQt5.QtCore import Qt


class UniformGenerator:
    def __init__(self, mid: float, deviation: float):
        self.a = mid - deviation
        self.b = mid + deviation

    def generate(self) -> float:
        return nr.uniform(self.a, self.b)


class MassServiceSystem:
    def __init__(
            self,
            request_number: int,
            request_generator: UniformGenerator,
            operator_generators: List[UniformGenerator],
            operator_return_rates: List[float],
            computer_process_times: List[float]
    ):
        self._req_n: int = request_number
        self._req_gened: int = 0
        self._req_gen: UniformGenerator = request_generator
        self._gen_queue: int = 0
        self._op_gens: List[UniformGenerator] = operator_generators
        self._op_ret_rates: List[float] = operator_return_rates
        self._queues: List[int] = [0, 0]
        self._cpt: List[float] = computer_process_times
        self._req_passed: int = 0

        self._times: List[Optional[float]] = [None, None, None, None, None, None]    # g, op1, op2, op3, c1, c2
        self._last_time_compute: List[float] = [0.0, 0.0]
        self._times_idle: List[float] = [0.0, 0.0]
        self._times_work: List[float] = [0.0, 0.0]

    def generate_request(self) -> None:
        if self._times[0] is None:
            return

        self._req_gened += 1
        if self._gen_queue == 0:
            to_op = False
            for i in range(1, 4):
                if self._times[i] is None and to_op is False:
                    self._times[i] = self._times[0] + self._op_gens[i - 1].generate()
                    to_op = True
            if not to_op:
                self._gen_queue += 1
        else:
            self._gen_queue += 1

        if self._req_gened < self._req_n:
            self._times[0] += self._req_gen.generate()
        else:
            self._times[0] = None

    def operate_request(self, op: int) -> None:
        if self._times[1 + op] is None:
            return

        if random.random() > self._op_ret_rates[op]:
            if op in [0, 1]:
                q = 0
            else:
                q = 1
            if self._queues[q] == 0 and self._times[1 + 3 + q] is None:
                self._times[1 + 3 + q] = self._times[1 + op] + self._cpt[q]
            else:
                self._queues[q] += 1
        else:
            self._gen_queue += 1

        if self._gen_queue > 0:
            self._gen_queue -= 1
            self._times[1 + op] += self._op_gens[op].generate()
        else:
            self._times[1 + op] = None

    def compute(self, c: int) -> None:
        if self._times[1 + 3 + c] is None:
            return

        self._req_passed += 1

        self._times_idle[c] += self._times[1 + 3 + c] - self._cpt[c] - self._last_time_compute[c]
        self._times_work[c] += self._cpt[c]
        self._last_time_compute[c] = self._times[1 + 3 + c]

        if self._queues[c] > 0:
            self._queues[c] -= 1
            self._times[1 + 3 + c] += self._cpt[c]
        else:
            self._times[1 + 3 + c] = None

    def get_min_time_i(self) -> int:
        i_min = -1
        for i in range(len(self._times)):
            if self._times[i] is not None:
                i_min = i
        if i_min == -1:
            raise Exception

        for i in range(len(self._times)):
            if self._times[i] is not None and self._times[i] < self._times[i_min]:
                i_min = i
        return i_min

    def model(self):
        self._times[0] = self._req_gen.generate()
        while self._req_passed < self._req_n:
            print(self._req_gened, self._gen_queue, self._queues, self._req_passed, self._times, self._times_idle, self._times_work)
            i_min = self.get_min_time_i()
            if i_min in [0]:
                self.generate_request()
            elif i_min in [1, 2, 3]:
                self.operate_request(i_min - 1)
            elif i_min in [4, 5]:
                self.compute(i_min - 1 - 3)

        if self._last_time_compute[0] < self._last_time_compute[1]:
            self._times_idle[0] += self._last_time_compute[1] - self._last_time_compute[0]
        else:
            self._times_idle[1] += self._last_time_compute[0] - self._last_time_compute[1]
        print("Passed:", self._req_passed)
        return self._times_idle, self._times_work


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
            rr = QLabel("Возврат:")
            c = QLineEdit()
            row.addWidget(a)
            row.addWidget(pm)
            row.addWidget(b)
            row.addWidget(rr)
            row.addWidget(c)
            self.operator_inputs.append((a, b, c))
            ops_box.addLayout(row)
        root.addLayout(ops_box)

        self.operator_inputs[0][0].setText("20")
        self.operator_inputs[0][1].setText("5")
        self.operator_inputs[0][2].setText("0.2")
        self.operator_inputs[1][0].setText("40")
        self.operator_inputs[1][1].setText("10")
        self.operator_inputs[1][2].setText("0.2")
        self.operator_inputs[2][0].setText("40")
        self.operator_inputs[2][1].setText("20")
        self.operator_inputs[2][2].setText("0.2")

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
        self.result_time_value = QLabel("-")
        result_row = QHBoxLayout()

        col_labels = QVBoxLayout()
        col_labels.addWidget(self.result_time_value)
        col_labels.addWidget(QLabel("Первый:"))
        col_labels.addWidget(QLabel("Второй:"))
        result_row.addLayout(col_labels)

        col_work = QVBoxLayout()
        self.c1_work_value = QLabel("-")
        self.c2_work_value = QLabel("-")
        col_work.addWidget(QLabel("Время работы"))
        col_work.addWidget(self.c1_work_value)
        col_work.addWidget(self.c2_work_value)
        result_row.addLayout(col_work)

        col_work_perc = QVBoxLayout()
        self.c1_work_percent = QLabel("-%")
        self.c2_work_percent = QLabel("-%")
        col_work_perc.addWidget(QLabel())
        col_work_perc.addWidget(self.c1_work_percent)
        col_work_perc.addWidget(self.c2_work_percent)
        result_row.addLayout(col_work_perc)

        col_idle = QVBoxLayout()
        self.c1_idle_value = QLabel("—")
        self.c2_idle_value = QLabel("—")
        col_idle.addWidget(QLabel("Время простоя"))
        col_idle.addWidget(self.c1_idle_value)
        col_idle.addWidget(self.c2_idle_value)
        result_row.addLayout(col_idle)

        col_idle_perc = QVBoxLayout()
        self.c1_idle_percent = QLabel("—%")
        self.c2_idle_percent = QLabel("—%")
        col_idle_perc.addWidget(QLabel())
        col_idle_perc.addWidget(self.c1_idle_percent)
        col_idle_perc.addWidget(self.c2_idle_percent)
        result_row.addLayout(col_idle_perc)

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
        for a_edit, b_edit, c_edit in self.operator_inputs:
            a = check_float(a_edit.text())
            b = check_float(b_edit.text())
            c = check_float(c_edit.text())
            if a is None or b is None or c is None:
                return
            operators.append((a, b, c))
        op1, op2, op3 = operators
        operator1_generator = UniformGenerator(op1[0], op1[1])
        operator2_generator = UniformGenerator(op2[0], op2[1])
        operator3_generator = UniformGenerator(op3[0], op3[1])
        operator_return_rates = [op1[2], op2[2], op3[2]]

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
            [
                operator1_generator,
                operator2_generator,
                operator3_generator
            ],
            operator_return_rates,
            [
                computer1_process_time,
                computer2_process_time
            ],
        )

        times_idle, times_work = mss.model()
        print(times_idle, times_work)
        print(times_idle[0] + times_work[0], times_idle[1] + times_work[1])
        total = times_idle[0] + times_work[0]

        self.result_time_value.setText(f"Σ={total:.3f}")

        self.c1_work_value.setText(f"{times_work[0]:.3f}")
        self.c1_idle_value.setText(f"{times_idle[0]:.3f}")
        self.c1_work_percent.setText(f"{100*times_work[0]/total:.3f}%")
        self.c1_idle_percent.setText(f"{100*times_idle[0]/total:.3f}%")

        self.c2_work_value.setText(f"{times_work[1]:.3f}")
        self.c2_idle_value.setText(f"{times_idle[1]:.3f}")
        self.c2_work_percent.setText(f"{100*times_work[1]/total:.3f}%")
        self.c2_idle_percent.setText(f"{100*times_idle[1]/total:.3f}%")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())
