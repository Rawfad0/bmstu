class Fraction:
    def __init__(self, a, b):
        if b <= 0:
            raise ValueError
        gcd = self.gcd(a, b)
        if gcd == 0:
            self.numerator = 0
            self.denominator = 1
        else:
            self.numerator = int(a / gcd)
            self.denominator = int(b / gcd)

    # НОД
    @staticmethod
    def gcd(a, b) -> int:
        a, b = abs(a), abs(b)
        # print("start gcd: ", a, b)
        if a == 0 or b == 0:
            return 0
        if a % b == 0:
            return b
        if b % a == 0:
            return a
        # simple euclidean alg
        while a > 0 and b > 0:
            if a > b:
                a -= b
            else:
                b -= a
        # print("gcd: ", a, b)
        return a + b

    # НОК
    def lcm(self, a, b) -> int:
        return a * b / self.gcd(a, b)

    def __add__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        a = self.numerator * other.denominator / b_gcd + other.numerator * self.denominator / b_gcd
        b = self.lcm(self.denominator, other.denominator)
        return Fraction(a, b)

    def __sub__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        a = self.numerator * other.denominator / b_gcd - other.numerator * self.denominator / b_gcd
        b = self.lcm(self.denominator, other.denominator)
        return Fraction(a, b)

    def __mul__(self, other):
        a = self.numerator * other.numerator
        b = self.denominator * other.denominator
        return Fraction(a, b)

    def __truediv__(self, other):
        if other.numerator == 0:
            raise ZeroDivisionError
        a = self.numerator * other.denominator
        b = self.denominator * other.numerator
        return Fraction(a, b)

    def __eq__(self, other):
        return self.numerator == other.numerator and self.denominator == other.denominator

    def __ne__(self, other):
        return self.numerator != other.numerator or self.denominator != other.denominator

    def __gt__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        return self.numerator * other.denominator / b_gcd > other.numerator * self.denominator / b_gcd

    def __lt__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        return self.numerator * other.denominator / b_gcd < other.numerator * self.denominator / b_gcd

    def __ge__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        return self.numerator * other.denominator / b_gcd >= other.numerator * self.denominator / b_gcd

    def __le__(self, other):
        b_gcd = self.gcd(self.denominator, other.denominator)
        return self.numerator * other.denominator / b_gcd <= other.numerator * self.denominator / b_gcd

    def __repr__(self):
        return f"{self.numerator}/{self.denominator:}"


print(Fraction(1, 2))   # Создание дроби 1/2
print(Fraction(2, 4))   # Создание дроби 1/2 (автоматическое сокращение)
print(Fraction(-1, 2))      # Создание дроби -1/2

# Сложение двух дробей:
print(Fraction(1, 2) + Fraction(3, 4))  # Результат: 5/4
# Вычитание одной дроби из другой:
print(Fraction(1, 2) - Fraction(3, 4))  # Результат: -1/4
# Умножение двух дробей:
print(Fraction(1, 2) * Fraction(3, 4))  # Результат: 3/8
# Деление одной дроби на другую:
print(Fraction(1, 2) / Fraction(3, 4))  # Результат: 2/3

# Проверка на равенство
print(Fraction(1, 2) == Fraction(2, 4))  # Результат: True
print(Fraction(0, 6) == Fraction(0, 200))  # Результат: True
# Проверка на неравенство
print(Fraction(1, 2) != Fraction(3, 4))  # Результат: True
# Проверка на меньше или больше:
print(Fraction(1, 2) < Fraction(3, 4))  # Результат: True
print(Fraction(1, 2) > Fraction(3, 4))  # Результат: False

# Строковое представление должно показывать саму дробь:
print(Fraction(1, 2))  # Вывод: 1/2
