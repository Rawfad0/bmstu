import datetime
dt = datetime.datetime.strptime(input(), '%d-%m-%Y')
print((dt - datetime.timedelta(days=dt.weekday())).strftime("%d-%m-%Y"))
