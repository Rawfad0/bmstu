p = input()
if len(p) < 8:
    print("Слабый пароль")
else:
    u, l, d, s = 0, 0, 0, 0
    for ch in p:
        u = 1 if ch.isupper() else u
        l = 1 if ch.islower() else l
        d = 1 if ch.isdigit() else d
        s = 1 if ch in '!@#$%^&*(),.?":{}|<>' else s
    print(["Слабый", "Слабый", "Слабый", "Средний", "Сильный",][u + l + d + s], "пароль")
