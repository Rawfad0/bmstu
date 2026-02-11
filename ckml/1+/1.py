x1, op, x2 = input().split()
if op not in ['+', '-', '*', '/', '%']:
    print("Неверная операция.")
elif (op == '/' or op == '%') and float(x2) == 0:
    print("Деление на ноль невозможно.")
else:
    print("Результат:", round(eval(' '.join([x1, op, x2])), 2))
