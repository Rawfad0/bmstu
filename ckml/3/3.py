def get_balances(transactions):
    balances = dict()
    for transaction in transactions:
        if balances.get(transaction["name"]) is None:
            balances[transaction["name"]] = transaction["amount"]
        else:
            balances[transaction["name"]] += transaction["amount"]
    return balances


def get_balance(name, transactions) -> int:
    balances = get_balances(transactions)
    if balances.get(name) is None:
        return 0
    else:
        return balances[name]


def count_debts(names, amount, transactions):
    balances = get_balances(transactions)
    res = dict()
    for name in names:
        if balances.get(name) is None:
            res[name] = amount
        elif balances[name] > amount:
            res[name] = 0
        else:
            res[name] = amount - balances[name]
    return res


transactions = [ {"name": "Василий", "amount": 500}, {"name": "Петя", "amount": -100}, {"name": "Василий", "amount": -300}, ]
# get_balances(transactions)
print(get_balance("Василий", transactions))
print(get_balance("Вова", transactions))
print((count_debts(["Василий", "Петя", "Вова"], 150, transactions)))
