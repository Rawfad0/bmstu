class Time:
    @staticmethod
    def str2time(string):
        timestr = string.split()
        if len(timestr) == 1:
            h, m = map(int, timestr[0].split(':'))
            if 0 <= h < 24 and 0 <= m < 60:
                hours = h
                minutes = m
            else:
                raise ValueError
        elif len(timestr) == 2:
            d = timestr[1]
            if d != "AM" and d != "PM":
                raise ValueError
            else:
                d = 1 if d == "PM" else 0
            h, m = map(int, timestr[0].split(':'))
            if 0 <= h < 12 and 0 <= m < 60:
                hours = h + d * 12
                minutes = m
            else:
                raise ValueError
        else:
            raise ValueError
        return hours, minutes

    def __init__(self, *args):
        if len(args) == 1:
            arg = args[0]
            if type(arg) is str:
                self.hours, self.minutes = self.str2time(arg)
        elif len(args) == 2:
            h, m = args
            if type(h) is int and type(m) is int:
                if 0 <= h < 24 and 0 <= m < 60:
                    self.hours = h
                    self.minutes = m
                else:
                    raise ValueError
        else:
            raise ValueError

    def is_night(self):
        return Time("22:00") <= self or self <= Time("06:00")

    def difference(self, other):
        return abs(self.hours * 60 + self.minutes - other.hours * 60 - other.minutes)

    def __eq__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours == hours and self.minutes == minutes

    def __ne__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours != hours or self.minutes != minutes

    def __gt__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours > hours or (self.hours == hours and self.minutes > minutes)

    def __ge__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours > hours or (self.hours == hours and self.minutes >= minutes)

    def __lt__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours < hours or (self.hours == hours and self.minutes < minutes)

    def __le__(self, other):
        if type(other) is Time:
            hours, minutes = other.hours, other.minutes
        elif type(other) is str:
            hours, minutes = self.str2time(other)
        else:
            raise ValueError
        return self.hours < hours or (self.hours == hours and self.minutes <= minutes)

    def __add__(self, other):
        if type(other) is Time:
            minutes = self.hours * 60 + self.minutes + other.hours * 60 + other.minutes
        elif type(other) is int:
            minutes = self.hours * 60 + self.minutes + other
        elif type(other) is str:
            str_hours, str_minutes = self.str2time(other)
            minutes = self.hours * 60 + self.minutes + str_hours * 60 + str_minutes
        else:
            raise ValueError
        return Time(minutes // 60 % 24, minutes % 60)

    def __sub__(self, other):
        if type(other) is Time:
            minutes = self.hours * 60 + self.minutes - other.hours * 60 - other.minutes
        elif type(other) is int:
            minutes = self.hours * 60 + self.minutes - other
        elif type(other) is str:
            str_hours, str_minutes = self.str2time(other)
            minutes = self.hours * 60 + self.minutes - str_hours * 60 - str_minutes
        else:
            raise ValueError
        if minutes < 0:
            raise ValueError
        return Time(minutes // 60 % 24, minutes % 60)

    def __repr__(self):
        return f"{self.hours:02g}:{self.minutes:02g}"


# Создание объектов класса Time
time1 = Time("12:30") # Соответствует времени 12:30
time2 = Time(14, 15)  # Соответствует времени 14:15
time3 = Time("10+:45 AM")  # Соответствует времени 10+:45
time4 = Time("10+:45 PM")  # Соответствует времени 22:45

# Пример операций с целым числом (минутами)
print(Time("12:30") + 45)  # Результат: 13:15
print(Time(14, 15) - 30)  # Результат: 13:45
print(Time("06:30 AM") + 30)  # Результат: 07:00

# Пример операций с другим объектом Time
print(Time("11:30 PM") + Time("02:15"))  # Результат: 01:45
print(Time("02:30 PM") - Time("02:45"))  # Результат: 11:45

#Пример операции с строкой
print(Time("13:30") + "02:30") # Результат: 16:00

# Пример операций сравнения
print(Time("13:30") == Time(13, 30))  # Результат: True
print(Time("13:30") == Time("01:30 PM"))  # Результат: True
print(Time("12:30") != Time("13:30"))  # Результат: True
print(Time("12:30") > Time("11:30"))  # Результат: True
print(Time("11:30") > Time("12:30"))  # Результат: False

# Пример сравнения со строкой
print(Time("01:30 PM") == "13:30")  # Результат: True

print(Time("13:30"))  # Вывод: 13:30
print(Time(13, 30))  # Вывод: 13:30
print(Time("10+:45 AM"))  # Вывод: 10+:45
print(Time("10+:45 PM"))  # Вывод: 22:45

time_0601 = Time("06:01")
print(time_0601.is_night())
