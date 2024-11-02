def t_func(p: tuple[int, int], xl: int, xr: int, yd: int, yu: int) -> tuple[int, int, int, int]:
    x, y = p
    t = (x < xl, x > xr, y < yd, y > yu)
    return t


def s_func(t: tuple[int, int, int, int]) -> int:
    return sum(t)


def p_func(t1: tuple[int, int, int, int], t2: tuple[int, int, int, int]) -> int:
    p = [t1[i] * t2[i] for i in range(4)]
    return sum(p)


def vertical(x: int, y: int, yd: int, yu: int) -> tuple[int, int]:
    if y > yu:
        return x, yu
    elif y < yd:
        return x, yd
    else:
        return x, y


def find_points(clipper: tuple[tuple[int, int], tuple[int, int]], p1: tuple[int, int], p2: tuple[int, int],
                res: list[tuple[int, int]], i: int) -> None:
    clipper_p1, clipper_p2 = clipper
    xl, yd = clipper_p1
    xr, yu = clipper_p2
    x1, y1 = p1
    x2, y2 = p2
    while i < 2:
        p = (x1, y1) if i == 0 else (x2, y2)
        x, y = p
        if x1 == x2:
            res.append(vertical(*p, yd, yu))
            i += 1
            continue
        m = (y2 - y1) / (x2 - x1)
        if x < xl and yd <= (yt := round(m * (xl - x) + y)) <= yu:
            res.append((xl, yt))
            i += 1
            continue
        elif x > xr and yd <= (yt := round(m * (xr - x) + y)) <= yu:
            res.append((xr, yt))
            i += 1
            continue
        if y < yd and xl <= (xt := round((yd - y) / m + x)) <= xr:
            res.append((xt, yd))
            i += 1
            continue
        elif y > yu and xl <= (xt := round((yu - y) / m + x)) <= xr:
            res.append((xt, yu))
            i += 1
            continue
        i += 1


def simple_clip(clipper: tuple[tuple[int, int], tuple[int, int]],
                line_segment: tuple[tuple[int, int], tuple[int, int]]) \
        -> tuple[bool, tuple[int, int], tuple[int, int]]:
    p1, p2 = line_segment
    clipper_p1, clipper_p2 = clipper
    xl, yd = clipper_p1
    xr, yu = clipper_p2
    t1, t2 = t_func(p1, xl, xr, yd, yu), t_func(p2, xl, xr, yd, yu)
    s1, s2 = s_func(t1), s_func(t2)
    if s1 == 0 and s2 == 0:
        return True, p1, p2     # полная видимость
    p = p_func(t1, t2)
    if p > 0:
        return False, p1, p2    # полная невидимость
    res = []    # результат
    i = 0       # количество найденных точек
    if s1 == 0:
        res.append(p1)
        i += 1
    if s2 == 0:
        res.append(p2)
        i += 1
        p1, p2 = p2, p1
    find_points(clipper, p1, p2, res, i)
    if len(res) == 2:
        p1, p2 = res
        return True, p1, p2     # отрезок частично видим
    else:
        return False, p1, p2    # отрезок полностью невидим
