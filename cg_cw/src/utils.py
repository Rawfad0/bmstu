from time import time


def record_procedure_time(func, *args, v=False, text="funcs", reps=1, **kwargs) -> float:
    tb = time()
    for i in range(reps):
        func(*args, **kwargs)
    te = time()
    rt = (te - tb) / reps
    if v:
        print(f"{text} time: {rt} func {func}")
    return rt


def record_func_time(func, *args, v=False, reps=1, text="funcs", **kwargs) -> tuple[float, any]:
    tb = time()
    res = None
    for i in range(reps):
        res = func(*args, **kwargs)
    te = time()
    rt = (te - tb) / reps
    if v:
        print(f"{text} time: {rt} func {func}")
    return rt, res


def record_procedure_time_compare(funcs, *args, v=False, reps=1, text="funcs", **kwargs):
    print(f"{text} compare:")
    ts = [0 for i in range(len(funcs))]
    for i in range(reps):
        for j, func in enumerate(funcs):
            tb = time()
            func(*args, **kwargs)
            te = time()
            rt = (te - tb) / reps
            ts[j] += rt
    if v:
        for i, rt in enumerate(ts):
            print(f"{i} time: {rt}")
    print("end compare")
