class BaseWallet:
    exchange_rate = 0

    def __init__(self, name, amount):
        self.name = name
        self.amount = amount

    def __add__(self, other):
        if type(other) is int:
            self.amount += other
            return self
        else:
            amount = self.amount + other.exchange_rate * other.amount / self.exchange_rate
            r = self.__class__(self.name, amount)
            return r

    def __radd__(self, other):
        if type(other) is int:
            self.amount += other
            return self

    def __sub__(self, other):
        if type(other) is int:
            self.amount -= other
            return self
        else:
            amount = self.amount - other.exchange_rate * other.amount / self.exchange_rate
            return self.__class__(self.name, amount)

    def __rsub__(self, other):
        if type(other) is int:
            self.amount = other - self.amount
        return self

    def __mul__(self, other):
        if type(other) is int:
            self.amount *= other
        return self

    def __truediv__(self, other):
        if type(other) is int:
            self.amount /= other
            return self

    def __rmul__(self, other):
        if type(other) is int:
            self.amount *= other
        return self

    def __eq__(self, other):
        return self.__class__ == other.__class__ and self.amount == other.amount

    def spend_all(self):
        if self.amount > 0:
            self.amount = 0

    def to_base(self):
        return self.exchange_rate * self.amount

    def __repr__(self):
        return f'{type(self).__name__[:-6]} Wallet {self.name} {self.amount}'


class RubleWallet(BaseWallet):
    exchange_rate = 1


class DollarWallet(BaseWallet):
    exchange_rate = 60


class EuroWallet(BaseWallet):
    exchange_rate = 70


def test(n, expression, expected):
    print(f'Test #{n}: {"PASSED" if expression == expected else "FAILED"}; expected: {expected}, given: {expression}')


print(RubleWallet("", 10) / 2)

# print("Tests:")
#
# test(1, RubleWallet("Первый кошелек", 10+).amount, 10+)
#
# r = RubleWallet("X", 10+) + 20
# test(2, r, RubleWallet("X", 30))
#
# r = RubleWallet("X", 10+)
# r += 20
# test(3, r.amount, 30)
#
# r = 20 + RubleWallet("X", 10+)
# test(4, r.amount, 30)
#
# r = RubleWallet("X", 20) + DollarWallet("D", 10+)
# test(5, r, RubleWallet("X", 620))
#
# r = DollarWallet("D", 2) + RubleWallet("X", 60)
# test(6, r, DollarWallet("D", 3))
#
# r = DollarWallet("D", 2)
# r += RubleWallet("X", 60)
# test(7, r, DollarWallet("D", 3))
#
# r = RubleWallet("X", 10+) * 20
# test(8, r, RubleWallet("X", 200))
#
# r = RubleWallet("X", 10+)
# r *= 20
# test(9, r, RubleWallet("X", 200))
