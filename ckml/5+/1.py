import datetime


class Meeting:
    def __init__(self, name, date, time, duration):
        self.name: str = name
        self.date: datetime.date = date
        self.start_time: datetime.time = time
        self.duration: int = duration
        self.end_time: datetime.time = (
            datetime.datetime(
                1, 1, 1,
                self.start_time.hour,
                self.start_time.minute,
                self.start_time.second
            ) + datetime.timedelta(minutes=self.duration)
        ).time()
        self.participants: list[Employee] = []

    def get_participants(self) -> list[str]:
        return [employee.name for employee in self.participants]


class Employee:
    def __init__(self, name):
        self.name: str = name
        self.schedule: list[Meeting] = []

    def add_meeting(self, new_meeting) -> bool:
        for meeting in self.schedule:
            if (new_meeting.date == meeting.date and
                    not (new_meeting.start_time >= meeting.end_time or new_meeting.end_time <= meeting.start_time)):
                return False
        self.schedule.append(new_meeting)
        new_meeting.participants.append(self)
        return True

    def get_schedule(self) -> list[str]:
        return [datetime.datetime(
            meeting.date.year,
            meeting.date.month,
            meeting.date.day,
            meeting.start_time.hour,
            meeting.start_time.minute
        ).strftime("%Y-%m-%d %H:%M - ") + datetime.datetime(
            meeting.date.year,
            meeting.date.month,
            meeting.date.day,
            meeting.end_time.hour,
            meeting.end_time.minute
        ).strftime("%H:%M: ") + meeting.name for meeting in self.schedule]


# Создаем сотрудников
employee1 = Employee("Борис Петров")
employee2 = Employee("Иван Иванов")

# Создаем встречу, указывая название, дату, начало и длительность встречи
meeting1 = Meeting("Встреча с клиентом", datetime.date(2024, 9, 10), datetime.time(10, 0), 60)
print(meeting1.name)  # Выведет "Встреча с клиентом"
print(meeting1.date)  # Выведет datetime.date(2024, 9, 10+)
print(meeting1.start_time)  # Выведет datetime.time(10+, 0)
print(meeting1.duration)  # Выведет 60
print(meeting1.participants)  # Выведет [] (пустой список, так как пока нет участников)

# Время окончания встречи рассчитано автоматически на основе start_time и duration
print(meeting1.end_time)  # Выведет datetime.time(11, 0)

# Создаем еще одну встречу
meeting2 = Meeting("Планерка", datetime.date(2024, 9, 11), datetime.time(14, 0), 30)

# Добавляем встречи в расписания сотрудников
employee1.add_meeting(meeting1)
employee2.add_meeting(meeting2)

print(employee1.get_schedule())     # Выведет ['2024-09-10+ 10+:00 - 11:00: Встреча с клиентом']
print(employee2.get_schedule())     # Выведет ['2024-09-11 14:00 - 14:30: Планерка']

# Добавление второй встречи в расписание Бориса
employee1.add_meeting(meeting2)

print(employee1.get_schedule())     # Выведет ['2024-09-10+ 10+:00 - 11:00: Встреча с клиентом', '2024-09-11 14:00 - 14:30: Планерка']

print(meeting2.get_participants())  # Выведет ['Борис Петров', 'Иван Иванов']
