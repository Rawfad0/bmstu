#!/usr/bin/env python3
import random
import sys
import numpy.random as nr
from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QLineEdit, QComboBox,
    QHBoxLayout, QVBoxLayout, QPushButton, QFormLayout
)
from PyQt5.QtGui import QDoubleValidator, QIntValidator


class BaseGenerator:
    def __init__(self, params):
        self.params = params

    def generate(self) -> float:
        pass


class UniformGenerator(BaseGenerator):
    def generate(self):
        return nr.uniform(self.params['a'], self.params['b'])


class PoissonGenerator(BaseGenerator):
    def generate(self):
        return nr.poisson(self.params['lambda'])


class ExponentialGenerator(BaseGenerator):
    def generate(self):
        return nr.exponential(self.params['lambda'])


class NormalGenerator(BaseGenerator):
    def generate(self):
        return nr.normal(self.params['mu'], self.params['sigma'])


class ErlangGenerator(BaseGenerator):
    def generate(self):
        return nr.gamma(self.params['k'], self.params['lambda'])


class MessageGenerator:
    def __init__(self, generator, message_processor, count):
        self._gen: BaseGenerator = generator
        self._message_processor: MessageProcessor = message_processor
        self._count = count

    @property
    def count(self):
        return self._count

    def send_message(self):
        if self._count > 0:
            self._message_processor.receive_message()
            self._count -= 1

    def generate(self):
        return self._gen.generate()


class MessageProcessor:
    def __init__(self, generator, return_rate, max_count):
        self._gen = generator
        self._return_rate = return_rate
        self._max_count = max_count
        self._queue_size = 0
        self._max_queue_size = 0
        self._processed_messages_count = 0

    @property
    def queue_size(self):
        return self._queue_size

    @property
    def max_queue_size(self):
        return self._max_queue_size

    @property
    def processed_messages_count(self):
        return self._processed_messages_count

    @property
    def max_count(self):
        return self._max_count

    def generate(self):
        return self._gen.generate()

    def receive_message(self):
        self._queue_size += 1
        if self._queue_size > self._max_queue_size:
            self._max_queue_size += 1

    def process_message(self):
        if self._queue_size > 0:
            self._queue_size -= 1
            if random.random() < self._return_rate:
                self.receive_message()
            else:
                self._processed_messages_count += 1


class Modeller:
    def __init__(self, generator, processor):
        self._generator: MessageGenerator = generator
        self._processor: MessageProcessor = processor

    def event_based_model(self):
        generator = self._generator
        processor = self._processor

        generate_time = generator.generate()
        process_time = generate_time + processor.generate()
        while processor.processed_messages_count < processor.max_count:
            print(f"{processor.processed_messages_count}: ({processor.queue_size}/{processor.max_queue_size}) {generate_time} {process_time}")
            if generate_time <= process_time:
                generator.send_message()
                generate_time += generator.generate()
            if generate_time >= process_time:
                processor.process_message()
                if processor.queue_size == 0:
                    process_time = generate_time + processor.generate()
                else:
                    process_time += processor.generate()
        return processor.max_queue_size

    def time_based_model(self, dt):
        generator = self._generator
        processor = self._processor
        time = 0

        generate_time = generator.generate()
        process_time = processor.generate()
        while processor.processed_messages_count < processor.max_count:
            if generate_time <= time:
                generator.send_message()
                generate_time += generator.generate()
            if process_time <= time:
                processor.process_message()
                if processor.queue_size == 0:
                    process_time = generate_time + processor.generate()
                else:
                    process_time += processor.generate()
            time += dt
        return processor.max_queue_size


def parse_float(txt):
    """Разрешаем ввод с запятой или точкой. Пустая или некорректная -> None."""
    if txt is None:
        return None
    s = str(txt).strip()
    if s == "":
        return None
    s = s.replace(",", ".")
    try:
        return float(s)
    except ValueError:
        return None


def parse_int(txt):
    """Парсинг int: убираем пробелы, заменяем запятую, приводим к int. Некорректно -> None."""
    if txt is None:
        return None
    s = str(txt).strip().replace(" ", "").replace(",", ".")
    if s == "":
        return None
    try:
        # Если ввели дробное число как "10.0", приведём к int, если оно целое по значению
        f = float(s)
        i = int(f)
        if abs(f - i) < 1e-9:
            return i
        return None
    except ValueError:
        return None


# m = Modeller(
#     MessageGenerator(UniformGenerator({"a": 0, "b": 1})),
#     MessageProcessor(UniformGenerator({"a": 0, "b": 1}), 0.5, 1000)
# )
# print(m.event_based_model(1000))
# print(m.time_based_model(1000, 0.5))


class DistRow(QWidget):
    def __init__(self, title):
        super().__init__()

        layout = QVBoxLayout()
        upper_lo = QHBoxLayout()
        mid_lo = QHBoxLayout()
        self.lower_lo = QHBoxLayout()
        layout.addLayout(upper_lo)
        layout.addLayout(mid_lo)
        layout.addLayout(self.lower_lo)

        upper_lo.addWidget(QLabel(title))
        mid_lo.addWidget(QLabel("Закон распределения и его параметры"))

        self.DISTRIBUTIONS = {
            "Равномерный": ["a", "b"],
            "Пуассона": ["lambda"],
            "Экспоненциальный": ["lambda"],
            "Нормальный": ["mu", "sigma"],
            "k-Эрланга": ["k", "lambda"],
        }

        self.combo = QComboBox()
        for name in self.DISTRIBUTIONS.keys():
            self.combo.addItem(name)
        self.lower_lo.addWidget(self.combo)

        self.param_widgets = []

        self.combo.currentTextChanged.connect(self.update_params)
        self.setLayout(layout)

        self.update_params()

    def update_params(self):
        for lbl, edit in self.param_widgets:
            lbl.deleteLater()
            edit.deleteLater()
        self.param_widgets.clear()

        params = self.DISTRIBUTIONS[self.combo.currentText()]
        for p in params:
            lbl = QLabel(p)
            edit = QLineEdit()
            edit.setValidator(QDoubleValidator())
            self.lower_lo.addWidget(lbl)
            self.lower_lo.addWidget(edit)
            self.param_widgets.append((lbl, edit))

    def get_values(self):
        params = {}
        for lbl, edit in self.param_widgets:
            txt = edit.text().strip()
            params[lbl.text()] = parse_float(txt) if txt else None
        return self.combo.currentText(), params


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Lab4")
        self.resize(500, 500)

        main = QVBoxLayout()

        # --- 2 строки: генератор, обработчик ---
        self.gen_row = DistRow("Генератор")
        self.hnd_row = DistRow("Обработчик")
        main.addWidget(self.gen_row)
        main.addWidget(self.hnd_row)

        # --- строка параметров моделирования ---
        params_layout = QVBoxLayout()

        req_layout = QHBoxLayout()
        self.req_edit = QLineEdit()
        self.req_edit.setValidator(QIntValidator(1, 10 ** 9))
        req_layout.addWidget(QLabel("Количество заявок"))
        req_layout.addWidget(self.req_edit)
        params_layout.addLayout(req_layout)

        return_layout = QHBoxLayout()
        self.return_edit = QLineEdit()
        self.return_edit.setValidator(QDoubleValidator(0.0, 1e9, 10))
        return_layout.addWidget(QLabel("Коэффициент возврата"))
        return_layout.addWidget(self.return_edit)
        params_layout.addLayout(return_layout)

        dt_edit_layout = QHBoxLayout()
        self.dt_edit = QLineEdit()
        self.dt_edit.setValidator(QDoubleValidator(0.0, 1e9, 10))
        dt_edit_layout.addWidget(QLabel("Δt"))
        dt_edit_layout.addWidget(self.dt_edit)
        params_layout.addLayout(dt_edit_layout)

        main.addLayout(params_layout)

        # кнопка
        run_btn = QPushButton("Моделировать")
        run_btn.clicked.connect(self.run)
        main.addWidget(run_btn)

        # результаты
        results = QFormLayout()
        results.addWidget(QLabel("Результаты"))
        self.step = QLineEdit()
        self.event = QLineEdit()
        self.step.setReadOnly(True)
        self.event.setReadOnly(True)

        results.addRow("Пошаговый:", self.step)
        results.addRow("Событийный:", self.event)

        main.addLayout(results)

        self.setLayout(main)
        self.show()

    @staticmethod
    def run_method(gen, hnd, ret, num_req, dt, method):
        processor = MessageProcessor(hnd, ret, num_req)
        generator = MessageGenerator(gen, processor, num_req)

        modeller = Modeller(generator, processor)
        if method == "step":
            return modeller.time_based_model(dt)
        elif method == "event":
            return modeller.event_based_model()

    def run(self):
        gen_type, gen_params = self.gen_row.get_values()
        hnd_type, hnd_params = self.hnd_row.get_values()

        num_req = parse_int(self.req_edit.text().strip())
        ret = parse_float(self.return_edit.text().strip())
        dt = parse_float(self.dt_edit.text().strip())

        str2gen = {
            "Равномерный": UniformGenerator,
            "Пуассона": PoissonGenerator,
            "Экспоненциальный": ExponentialGenerator,
            "Нормальный": NormalGenerator,
            "k-Эрланга": ErlangGenerator,
        }
        step = self.run_method(str2gen[gen_type](gen_params), str2gen[hnd_type](hnd_params), ret, num_req, dt, "step")
        event = self.run_method(str2gen[gen_type](gen_params), str2gen[hnd_type](hnd_params), ret, num_req, dt, "event")

        self.step.setText(f"{step}")
        self.event.setText(f"{event}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    sys.exit(app.exec_())
