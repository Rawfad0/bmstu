import datetime
import json
from api import register_booking


class Booking:
    def __init__(self, room_name, start, end):
        if start > end:
            raise ValueError
        self.room_name = room_name
        self._start = start
        self._end = end
        self.duration = (end - start).seconds // 60
        self.start_date = start.date().strftime(f"%Y-%m-%d")
        self.end_date = end.date().strftime(f"%Y-%m-%d")
        self.start_time = start.time().strftime(f"%H:%M")
        self.end_time = end.time().strftime(f"%H:%M")

    @property
    def start(self):
        return self._start

    @start.setter
    def start(self, start):
        if start > self._end:
            raise ValueError
        self.start_date = start.date().strftime(f"%Y-%m-%d")
        self.start_time = start.time().strftime(f"%H:%M")

    @property
    def end(self):
        return self._end

    @end.setter
    def end(self, end):
        if self._start > end:
            raise ValueError
        self.end_date = end.date().strftime(f"%Y-%m-%d")
        self.end_time = end.time().strftime(f"%H:%M")


def create_booking(room_name, start, end):
    print("Начинаем создание бронирования")
    try:
        booking = Booking(room_name, start, end)
        bool_msg = register_booking(booking)
        created = True
        if bool_msg:
            msg = "Бронирование создано"
        else:
            msg = "Комната занята"
    except ValueError:
        created = False
    except KeyError:
        created = False
        msg = "Комната не найдена"
    result = {
        "created": created,
        "msg": msg,
        "booking": {
            "room_name": booking.room_name,
            "start_date": booking.start_date,
            "start_time": booking.start_time,
            "end_date": booking.end_date,
            "end_time": booking.end_time,
            "duration": booking.duration
        }
    }
    print("Заканчиваем создание бронирования")
    return result


s = datetime.datetime(2022, 9, 1, 14)
e = datetime.datetime(2022, 9, 1, 15, 15)
print((e - s).seconds // 60)
print(s.time().strftime(f"%H:%M"))

print(create_booking(
    "Вагнер",
    datetime.datetime(2022, 9, 1, 14),
    datetime.datetime(2022, 9, 1, 15, 15)
    )
)