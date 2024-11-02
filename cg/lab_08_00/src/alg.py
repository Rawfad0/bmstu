# Сумма векторов
def vector_sum(va: tuple[int, int], vb: tuple[int, int]) -> tuple[int, int]:
    return va[0] + vb[0], va[1] + vb[1]


def form(clipper_points: list[tuple[int, int]]) -> list[tuple[int, int]]:
    y_max_index = 0
    for i in range(len(clipper_points)):
        if clipper_points[i][1] > clipper_points[y_max_index][1]:
            y_max_index = i

    for i in range(y_max_index):
        clipper_points.append(clipper_points.pop(0))

    if clipper_points[-1][0] > clipper_points[1][0]:
        clipper_points.reverse()

    return clipper_points


def get_vector(p1: tuple[int, int], p2: tuple[int, int]) -> tuple[int, int]:
    x1, y1 = p1
    x2, y2 = p2
    return x2 - x1, y2 - y1


def get_normal(p1: tuple[int, int], p2: tuple[int, int]) -> tuple[int, int]:
    x, y = get_vector(p1, p2)
    normal = (y, -x)
    return normal


def scalar_product(a: tuple[int, int], b: tuple[int, int]) -> int:
    xa, ya = a
    xb, yb = b
    return xa * xb + ya * yb


def cyrus_beck(clipper: list[tuple[int, int]], line_segment: tuple[tuple[int, int], tuple[int, int]]) \
        -> tuple[bool, tuple[int, int], tuple[int, int]]:
    points = form(clipper)
    p1, p2 = line_segment
    d = get_vector(p1, p2)
    t_bot = 0
    t_top = 1
    for i in range(len(points)):
        normal = get_normal(points[i - 1], points[i])
        w = get_vector(points[i - 1], p1)
        d_scalar = scalar_product(d, normal)
        w_scalar = scalar_product(w, normal)
        if d_scalar == 0 and w_scalar < 0:
            return False, p1, p2    # невидимый вырожденный отрезок
        elif d_scalar == 0:
            continue                # видимый вырожденный отрезок
        t = -w_scalar / d_scalar
        if d_scalar > 0 and t <= 1:
            t_bot = max(t_bot, t)
        elif d_scalar < 0 <= t:
            t_top = min(t_top, t)
        elif d_scalar != 0:
            return False, p1, p2    # невидимый отрезок
        if t_bot > t_top:
            break
    if t_bot <= t_top:
        point_1_result = (round(p1[0] + d[0] * t_bot), round(p1[1] + d[1] * t_bot))
        point_2_result = (round(p1[0] + d[0] * t_top), round(p1[1] + d[1] * t_top))
        return True, point_1_result, point_2_result
    else:
        return False, p1, p2        # невидимый отрезок
