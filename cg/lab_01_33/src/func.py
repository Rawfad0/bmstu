from math import (
    acos,
    degrees,
    hypot,
)

EPS = 1e-6


# Скалярное произведение x1*x2 + y1*y2
def sum_prod(v1: tuple[float, float], v2: tuple[float, float]) -> float:
    return sum((a*b) for a, b in zip(v1, v2))


# Существует ли треугольник
# Если наибольшая сторона треугольника больше или равна сумме двух других, то треугольника не существует
def is_triangle(a: float, b: float, c: float):
    return sum([a, b, c]) - 2*max(a, b, c) < EPS


# Сумма векторов
def vsum(va: tuple[float, float], vb: tuple[float, float]) -> tuple[float, float]:
    return va[0] + vb[0], va[1] + vb[1]


# Умножение вектора на число
def vmul(v: tuple[float, float], k: float) -> tuple[float, float]:
    return k * v[0], k * v[1]


# Направляющий вектор медианы
def median_dir_vector(va: tuple[float, float], vb: tuple[float, float]) -> tuple[float, float]:
    return vsum(va, vb)     # Сумма векторов прилежащих к углу сторон


# Вектор медианы
def median_vector(va: tuple[float, float], vb: tuple[float, float]) -> tuple[float, float]:
    return vmul(vsum(va, vb), 1/2)  # Сумма векторов прилежащих к углу сторон поделенная пополам


# Единичный направляющий вектор
def vdir(v: tuple[float, float]) -> tuple[float, float]:
    vmod = hypot(*v)             # Модуль вектора
    return vmul(v, 1 / vmod)    # Разделить на модуль вектора


# Направляющий вектор биссектрисы (направляющий вектор медианы в треугольнике единичных направляющих векторов)
def bisector_dir_vector(va: tuple[float, float], vb: tuple[float, float]) -> tuple[float, float]:
    return median_dir_vector(vdir(va), vdir(vb))


# Вектор биссектрисы (сумма вектора a и вектора c (из треугольника веторов abc: c = b - a), умноженного на |a|/|b|)
def bisector_vector(va: tuple[float, float], vb: tuple[float, float]) -> tuple[float, float]:
    va_mod = hypot(*va)
    vb_mod = hypot(*vb)
    coef = va_mod / (va_mod + vb_mod)      # Отношение длин векторов прилежащих сторон
    vc = vsum(vb, vmul(va, -1))         # Вектор третьей стороны
    return vsum(va, vmul(vc, coef))


# Угол между векторами
def angle(v1: tuple[float, float], v2: tuple[float, float]) -> tuple[float, float]:
    return acos(sum_prod(v1, v2) / (hypot(*v1) * hypot(*v2)))


def calc_triangle(p1: tuple[float, float], p2: tuple[float, float], p3: tuple[float, float]):
    v12 = vsum(p2, vmul(p1, -1))
    v13 = vsum(p3, vmul(p1, -1))
    v21 = vmul(v12, -1)
    v23 = vsum(p3, vmul(p2, -1))
    v31 = vmul(v13, -1)
    v32 = vmul(v23, -1)

    if is_triangle(hypot(*v12), hypot(*v23), hypot(*v31)):
        return None

    a1 = angle(median_dir_vector(v12, v13), bisector_dir_vector(v12, v13))
    a2 = angle(median_dir_vector(v21, v23), bisector_dir_vector(v21, v23))
    a3 = angle(median_dir_vector(v31, v32), bisector_dir_vector(v31, v32))

    if a1 < a2 and a1 < a3:
        return [a1, p1, p2, p3]
    elif a2 < a1 and a2 < a3:
        return [a2, p2, p1, p3]
    else:
        return [a3, p3, p1, p2]


def compose_answer(angle, p1, p2, p3):
    v12 = vsum(p2, vmul(p1, -1))
    v13 = vsum(p3, vmul(p1, -1))

    vmed = median_vector(v12, v13)
    vbis = bisector_vector(v12, v13)

    return [p1, p2, p3], [p1, vsum(p1, vmed)], [p1, vsum(p1, vbis)], angle


# Перебор всех треугольников
def solve(points):
    min_ang_triangle = [None, None, None, None]   # угол и три вершины
    lp = len(points)
    for i in range(0, lp - 2):
        for j in range(i + 1, lp - 1):
            for k in range(j + 1, lp):
                ang_triangle = calc_triangle(points[i], points[j], points[k])
                if ang_triangle is not None and \
                        (min_ang_triangle[0] is None or ang_triangle[0] < min_ang_triangle[0]):
                    min_ang_triangle = ang_triangle
    if None in min_ang_triangle:
        return None
    min_ang_triangle[0] = degrees(min_ang_triangle[0])
    return compose_answer(*min_ang_triangle)
