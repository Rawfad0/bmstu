import requests


def get_exchange_rate(base_currency, target_currency):
    base_currency = base_currency.lower()
    target_currency = target_currency.lower()
    # date = datetime.date.strftime(datetime.date.today(), "YYYY-MM-DD")
    date = "latest"
    apiVersion = "v1"
    endpoint = base_currency
    response = requests.get(
        f"https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@{date}/{apiVersion}/currencies/{endpoint}.json"
        # f"https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/eur.json"
    ).json()
    return response[base_currency][target_currency]


def convert_currency(base_currency, target_currency, amount):
    exchange_rate = get_exchange_rate(base_currency, target_currency)
    return round(amount * exchange_rate, 2)


base_currency = "USD"  # Валюта, из которой нужно конвертировать
target_currency = "eur"  # Валюта, в которую нужно конвертировать
exchange_rate = get_exchange_rate(base_currency, target_currency)

print(f"Текущий курс {base_currency} к {target_currency}: {exchange_rate}")
# Вывод: Текущий курс USD к EUR: 0.9189

amount = 20 # Вводим кол-во базовой валюты, в данном примере - 20 USD
converted_amount = convert_currency(base_currency, target_currency, amount)

print(f"{amount} {base_currency} равно {converted_amount} {target_currency}")
# 20 USD равно 18.38 EUR