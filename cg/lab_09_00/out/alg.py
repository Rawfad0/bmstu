def form(clipper_points: list[tuple[int, int]]) -> list[tuple[int, int]]:
    y_max_index = 0
    for i in range(len(clipper_points)):
        if clipper_points[i][1] > clipper_points[y_max_index][1]:
            y_max_index = i

    for i in range(y_max_index):
        clipper_points.append(clipper_points.pop(0))

    if clipper_points[-1][0] > clipper_points[1][0]:
        fp = clipper_points.pop(0)
        clipper_points.reverse()
        clipper_points.insert(0, fp)

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


def vector_product(a: tuple[int, int], b: tuple[int, int]) -> int:
    xa, ya = a
    xb, yb = b
    return xa * xb - ya * yb


def get_intersection_point(t: float, p1: tuple[int, int], p2: tuple[int, int]) -> tuple[int, int]:
    x1, y1 = p1
    x2, y2 = p2
    point = round(x1 + (x2 - x1) * t), round(y1 + (y2 - y1) * t)
    return point


def is_visible(p: tuple[int, int], c: tuple[int, int], norm: tuple[int, int]) -> bool:
    vec = get_vector(c, p)
    res = scalar_product(vec, norm)
    return res > 0  # если вектор от точки отсекателя до точки
    # направлен как и вектор внутренней нормали внутрь многоугольника


def sutherland_hodgman_alg(clipper: list[tuple[int, int]], polygon: list[tuple[int, int]]) -> list[tuple[int, int]]:
    p = form(polygon)
    n_c = len(clipper)
    c = form(clipper)
    q = []
    for i in range(n_c):
        normal = get_normal(c[i - 1], c[i])
        n_p = len(p)
        for j in range(n_p):
            d = get_vector(p[j - 1], p[j])
            d_scalar = scalar_product(d, normal)
            if d_scalar != 0:
                w = get_vector(c[i - 1], p[j - 1])
                w_scalar = scalar_product(w, normal)
                t = - w_scalar / d_scalar
                if 0 <= t <= 1:
                    point = get_intersection_point(t, p[j - 1], p[j])
                    q.append(point)     # точка пересечения
            if is_visible(p[j], c[i - 1], normal):
                q.append(p[j])          # видимая точка
        p = q
        if len(p) != 0:
            p.append(p[0])
        q = []
    q = p
    return q
