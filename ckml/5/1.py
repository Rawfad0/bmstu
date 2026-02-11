class Calculator:
    last = None

    def __init__(self):
        self.hist = []

    def log(self, log_str):
        self.hist.append(log_str)
        Calculator.last = log_str

    @staticmethod
    def clear():
        Calculator.last = None

    def sum(self, a, b):
        r = a + b
        self.log(f"sum({a}, {b}) == {round(r, 1)}")
        return r

    def sub(self, a, b):
        r = a - b
        self.log(f"sub({a}, {b}) == {round(r, 1)}")
        return r

    def mul(self, a, b):
        r = a * b
        self.log(f"mul({a}, {b}) == {round(r, 1)}")
        return r

    def div(self, a, b, mod=False):
        r = a % b if mod else a / b
        self.log(f"div({a}, {b}) == {round(r, 1)}")
        return r

    def history(self, n):
        return None if len(self.hist) < n else self.hist[-n]

    # def last(self):
    #     return None if len(self.log) == 0 else self.log[-1]


print(Calculator.last)
clc = Calculator()
print(clc.sum(5, 15))
print(Calculator.last)
print(clc.history(1))
