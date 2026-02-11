import time


def time_decorator(func):
    def wrapper():
        tb = time.time()
        result = func()
        te = time.time()
        print(int(te - tb))     # вывод в целых секундах
        return result
    return wrapper


# Оборачиваем функцию в декоратор
@time_decorator
def sleep_1_sec():
    time.sleep(1)
    print("function")
    return 25


result = sleep_1_sec()
# Выведет
# function
# 1

print(result)  # Вывод: 25