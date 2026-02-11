import datetime
dt1 = datetime.datetime.strptime(input(), '%Y-%m-%d')
dt2 = datetime.datetime.strptime(input(), '%Y-%m-%d')
if dt2.month > dt1.month or (dt2.month == dt1.month and dt2.day >= dt1.day):
    y = dt2.year - dt1.year
else:
    y = dt2.year - dt1.year - 1
if y % 10 == 1 and y//10 != 1:
    print(f"{y} год")
elif 2 <= y % 10 <= 4 and y//10 != 1:
    print(f"{y} года")
else:
    print(f"{y} лет")
