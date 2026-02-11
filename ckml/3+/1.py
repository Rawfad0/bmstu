def calculate_cost(*prices, discount=0, delivery_type="стандартная"):
    cost = sum(prices)
    if delivery_type == "стандартная" and cost < 5000:
        cost += 1000
    elif delivery_type == "экспресс":
        cost += 1500
    cost *= 1 - discount / 100
    return round(cost)


print(calculate_cost(1000, 2000, discount=10))  # должна вернуть 3600
print(calculate_cost(5000, 1000, discount=20, delivery_type='экспресс'))  # должна вернуть 6000
print(calculate_cost(10000, 5000, 2000))  # должна вернуть 17000
print(calculate_cost(4500))  # должна вернуть 5500
print(calculate_cost(11.9))
