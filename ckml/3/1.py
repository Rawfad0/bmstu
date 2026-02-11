def gift_count(budget, month, birthdays):
    c = sum(1 for bd in birthdays.values() if bd.month == month)
    if c == 0:
        print("В этом месяце нет именинников.")
    else:
        print(f"Именинники в месяце {month}:",
              ', '.join([f"{person} ({bd.strftime('%d.%m.%Y')})"
                         for person, bd in birthdays.items() if bd.month == month]) + '.',
              f"При бюджете {budget} они получат по {int(budget / c)} рублей.")


s = input()
while s:
    exec(s)
    s = input()
