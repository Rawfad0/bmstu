import datetime
answers = {
    "ru": {
        "intro": "День недели - ",
        0: "Понедельник",
        1: "Вторник",
        2: "Среда",
        3: "Четверг",
        4: "Пятница",
        5: "Суббота",
        6: "Воскресенье"
    },
    "en": {
        "intro": "Day of the week - ",
        0: "Monday",
        1: "Tuesday",
        2: "Wednesday",
        3: "Thursday",
        4: "Friday",
        5: "Saturday",
        6: "Sunday"
    }
}
dt = datetime.datetime.strptime(input(), '%d-%m-%Y')
lo = input()
print(answers[lo]["intro"]+answers[lo][dt.weekday()] if lo in ["ru", "en"] else "Непонятный язык")
