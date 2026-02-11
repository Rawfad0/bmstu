d = dict()
input_str = input()
while input_str != "конец":
    key, value = input_str.split(": ")
    value = int(value)
    d[key] = (value, 1) if d.get(key) is None else (d[key][0] + value, d[key][1] + 1)
    input_str = input()
print("Чек:\n---------------------")
s = 0
for k, v in d.items():
    print(f"{k}: {v[0]} ({v[1]} шт.)")
    s += v[0]
print("---------------------\nИтого:", s)
