import time

cache_dict = dict()


def cache_results(func):
    def wrapper(*args, **kwargs):
        key = f"{args}; {kwargs}"
        if cache_dict.get(key) is None:
            tb = time.time()
            cache_dict[key] = func(*args, **kwargs)
            te = time.time()
            print(f"Выполнено за {int(te-tb)} секунды")
        else:
            print("Результат взят из кэша")
        return cache_dict[key]
    return wrapper


@cache_results
def slow_function(x):
    time.sleep(2)  # Симулируем долгую обработку
    return x * 2

result = slow_function(25)
# Вывод: Выполнено за 2 секунды

print(result)  # Вывод: 625


result2 = slow_function(25)
# Вывод: Результат взят из кэша

print(result2)  # Вывод: 625