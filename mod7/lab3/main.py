#!/usr/bin/env python3
import sys
import numpy as np
from math import factorial
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QGroupBox, QFormLayout, QDoubleSpinBox, QSpinBox, QPushButton, QSizePolicy
)
from PyQt5.QtCore import Qt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from scipy.special import erf


class DistributionControls(QGroupBox):
    def __init__(self, title: str, params: list):
        super().__init__(title)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        layout = QFormLayout()
        self.widgets = {}
        for name, wtype, kwargs in params:
            if wtype == 'double':
                w = QDoubleSpinBox()
                w.setDecimals(kwargs.get('decimals', 4))
                w.setSingleStep(kwargs.get('step', 0.1))
                w.setRange(kwargs.get('min', -1e9), kwargs.get('max', 1e9))
                w.setValue(kwargs.get('value', 0.0))
            elif wtype == 'int':
                w = QSpinBox()
                w.setSingleStep(kwargs.get('step', 1))
                w.setRange(kwargs.get('min', -2**31), kwargs.get('max', 2**31 - 1))
                w.setValue(kwargs.get('value', 0))
            layout.addRow(QLabel(name), w)
            self.widgets[name] = w
        self.setLayout(layout)

    def get(self):
        return {k: w.value() for k, w in self.widgets.items()}


class MplCanvas(FigureCanvas):
    def __init__(self, parent=None, width=10, height=8, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        # теперь первая строка — PDF, вторая — CDF
        self.axes = fig.subplots(2, 5)
        fig.tight_layout(pad=3.0)
        super().__init__(fig)
        self.setParent(parent)


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Lab3')
        self.resize(1400, 900)

        main_layout = QVBoxLayout(self)
        controls_layout = QHBoxLayout()
        controls_layout.setAlignment(Qt.AlignTop)
        self.controls = {}

        # параметры распределений
        self.controls['uniform'] = DistributionControls('Равномерное', [
            ('a', 'double', {'value': 0.0, 'step': 0.1}),
            ('b', 'double', {'value': 1.0, 'step': 0.1}),
        ])
        controls_layout.addWidget(self.controls['uniform'])

        self.controls['poisson'] = DistributionControls('Poisson', [
            ('lambda', 'double', {'value': 3.0, 'step': 0.1}),
            ('max_k', 'int', {'value': 20}),
        ])
        controls_layout.addWidget(self.controls['poisson'])

        self.controls['exponential'] = DistributionControls('Exponential', [
            ('1/lambda', 'double', {'value': 1.0, 'step': 0.1}),
        ])
        controls_layout.addWidget(self.controls['exponential'])

        self.controls['normal'] = DistributionControls('Normal', [
            ('mu', 'double', {'value': 0.0, 'step': 0.1}),
            ('sigma', 'double', {'value': 1.0, 'step': 0.1}),
        ])
        controls_layout.addWidget(self.controls['normal'])

        self.controls['erlang'] = DistributionControls('Erlang', [
            ('k', 'int', {'value': 3}),
            ('lambda', 'double', {'value': 1.0, 'step': 0.1}),
        ])
        controls_layout.addWidget(self.controls['erlang'])

        main_layout.addLayout(controls_layout)

        # кнопка
        self.btn_generate = QPushButton('Применить')
        self.btn_generate.clicked.connect(self.update_plots)
        main_layout.addWidget(self.btn_generate)

        # область графиков
        self.canvas = MplCanvas(self, width=8, height=8, dpi=100)
        main_layout.addWidget(self.canvas, stretch=1)
        self.setLayout(main_layout)
        self.update_plots()

    def update_plots(self):
        for row in self.canvas.axes:
            for ax in row:
                ax.clear()

        # Uniform
        u = self.controls['uniform'].get()
        a, b = u['a'], u['b']
        xs = np.linspace(a - (b - a) * 0.2, b + (b - a) * 0.2, 400)
        pdf = np.where((xs >= a) & (xs <= b), 1 / (b - a), 0)
        cdf = np.piecewise(xs, [xs < a, (xs >= a) & (xs <= b), xs > b],
                           [0, lambda x: (x - a) / (b - a), 1])
        self._plot_column(0, xs, pdf, cdf, 'Равномерное')

        # Poisson
        p = self.controls['poisson'].get()
        lam, max_k = p['lambda'], int(p['max_k'])
        ks = np.arange(0, max_k + 1)
        pmf = np.array([lam ** k * np.exp(-lam) / factorial(k) for k in ks])
        cdf = np.cumsum(pmf)
        ax_pdf, ax_cdf = self.canvas.axes[0][1], self.canvas.axes[1][1]
        ax_pdf.plot(ks, pmf, 'o-', markersize=4)
        ax_cdf.step(ks, cdf, where='mid')
        ax_pdf.set_title('Функция плотности\nраспределения')
        ax_cdf.set_title('Функция\nраспределения')
        ax_pdf.grid(True, alpha=0.3)
        ax_cdf.grid(True, alpha=0.3)

        # Exponential
        e = self.controls['exponential'].get()
        scale = e['1/lambda']
        xs = np.linspace(0, 10 * scale, 400)
        pdf = (1 / scale) * np.exp(-xs / scale)
        cdf = 1 - np.exp(-xs / scale)
        self._plot_column(2, xs, pdf, cdf, 'Exponential')

        # Normal
        n = self.controls['normal'].get()
        mu, sigma = n['mu'], n['sigma']
        xs = np.linspace(mu - 4 * sigma, mu + 4 * sigma, 400)
        pdf = 1 / (sigma * np.sqrt(2 * np.pi)) * np.exp(-0.5 * ((xs - mu) / sigma) ** 2)
        cdf = 0.5 * (1 + erf((xs - mu) / (sigma * np.sqrt(2))))
        self._plot_column(3, xs, pdf, cdf, 'Normal')

        # Erlang
        er = self.controls['erlang'].get()
        k, rate = int(er['k']), er['lambda']
        xs = np.linspace(0, 10 * k / rate, 400)
        pdf = (rate * (rate * xs) ** (k - 1) * np.exp(-rate * xs)) / factorial(k - 1)
        cdf = 1 - np.array([
            sum((rate * x) ** n / factorial(n) for n in range(k)) * np.exp(-rate * x)
            for x in xs
        ])
        self._plot_column(4, xs, pdf, cdf, 'Erlang')

        self.canvas.figure.tight_layout(pad=3.0)
        self.canvas.draw()

    def _plot_column(self, i, xs, pdf, cdf, title):
        ax_pdf, ax_cdf = self.canvas.axes[0][i], self.canvas.axes[1][i]
        ax_pdf.plot(xs, pdf)
        ax_cdf.plot(xs, cdf)
        ax_pdf.set_title(f'Функция плотности\nраспределения')
        ax_cdf.set_title(f'Функция\nраспределения')
        ax_pdf.grid(True, alpha=0.3)
        ax_cdf.grid(True, alpha=0.3)


def main():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    app.exec_()


if __name__ == '__main__':
    main()
