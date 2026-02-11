import datetime
import inspect


# ожидаемое решение через inspect
def logging_decorator(logger):
    def decorator(func):
        def wrapper(*args, **kwargs):
            call_time = datetime.datetime.now()
            result = func(*args, **kwargs)
            dt = inspect.getcallargs(func, *args, **kwargs)
            logger.append(
                {
                    'name': func.__name__,
                    'arguments': dt,
                    'call_time': call_time,
                    'result': result
                }
            )
            return result
        return wrapper
    return decorator


# попытка решения без inspect (не работает)
def logging_decorator2(logger):
    def decorator(func):
        def wrapper(*args, **kwargs):
            call_time = datetime.datetime.now()
            result = func(*args, **kwargs)

            varnames = func.__code__.co_varnames
            ntotal = len(func.__code__.co_varnames)
            nargs = len(args)
            nkwargs = len(kwargs)
            ndefs = len(func.__defaults__)
            # d2 = dict(zip(varnames, args))
            # d2.update(kwargs)

            d3 = dict(zip(varnames, args))
            d3.update(kwargs)
            for i in range(ntotal - nargs - nkwargs):
                varname = varnames[ntotal - 1 - i]
                defname = func.__defaults__[ndefs - 1 - i]
                d3[varname] = defname
            print("D3", d3)
            logger.append(
                {
                    'name': func.__name__,
                    'arguments': d3,
                    'call_time': call_time,
                    'result': result
                }
            )
            return result
        return wrapper
    return decorator


logger = []  # этот словарь будет хранить наш "лог"


@logging_decorator(logger)  # в аргументы фабрики декораторов подается логгер
def test_simple(aa, bb, cc=0, dd=-1, *args, **kwargs):
    print("FUNC", aa, bb, cc, dd, args, kwargs)
    return 127


def test(a, b=0):
    return 127


# print("DICT", dict(inspect.signature(test).parameters))
# print("ARGS", inspect.signature(test).parameters.keys())
# print("ARGS", inspect.signature(test).parameters.values())
# print("ARGS", inspect.getfullargspec(test))

# test_simple(1)
test_simple(2, 3)
test_simple(3, 4, 5)
test_simple(4, bb=5)
test_simple(5, 6, cc=7)
test_simple(6, bb=7, cc=8)
test_simple(7, cc=8, bb=9)

test_simple(8, 9, 10, 11, 12, 13)
# test_simple(aa=8)
# test_simple(bb=9)
test_simple(aa=10, bb=11)
# при вызове функции в список logger должен добавиться словарь с
# информацией о вызове функции

print(*logger, sep='\n')

