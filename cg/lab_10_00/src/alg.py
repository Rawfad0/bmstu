from math import pi, sin, cos
from numpy import arange


def matrix_rotate(matrix_a, matrix_b):
    res_matrix = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
    for i in range(4):
        for j in range(4):
            for k in range(4):
                res_matrix[i][j] += matrix_a[i][k] * matrix_b[k][j]
    return res_matrix


def rotate_ox(matrix, oxr):
    val = oxr / 180 * pi
    r_matrix = [
        [1, 0, 0, 0],
        [0, cos(val), sin(val), 0],
        [0, -sin(val), cos(val), 0],
        [0, 0, 0, 1]
    ]
    return matrix_rotate(matrix, r_matrix)


def rotate_oy(matrix, oyr):
    val = oyr / 180 * pi
    r_matrix = [
        [cos(val), 0, -sin(val), 0],
        [0, 1, 0, 0],
        [sin(val), 0, cos(val), 0],
        [0, 0, 0, 1]
    ]
    return matrix_rotate(matrix, r_matrix)


def rotate_oz(matrix, ozr):
    val = ozr / 180 * pi
    r_matrix = [
        [cos(val), sin(val), 0, 0],
        [-sin(val), cos(val), 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ]
    return matrix_rotate(matrix, r_matrix)


def is_visible(canvas, point: tuple[int, int]):
    return 0 <= point[0] < canvas.width and 0 <= point[1] < canvas.height


def draw_point(canvas, point, up_hor, low_hor):
    if 0 <= point[0] < canvas.width and 0 <= point[1] < canvas.height:
        x, y = point
        if y > up_hor[x]:
            up_hor[x] = y
            canvas.draw_line((x, y), (x + 1, y + 1))
        elif y < low_hor[x]:
            low_hor[x] = y
            canvas.draw_line((x, y), (x + 1, y + 1))
        return True
    return False


def predraw_horizon(canvas, fp, sp, up_hor, low_hor):
    if fp[0] > sp[0]:
        fp, sp = sp, fp
    dx = sp[0] - fp[0]
    dy = sp[1] - fp[1]

    l = max(dx, dy)
    dx /= l
    dy /= l
    x, y, z = fp
    for i in range(int(l) + 1):
        x = int(round(x))
        if not draw_point(canvas, (x, y), up_hor, low_hor):
            return
        x += dx
        y += dy


def trans_point(canvas, matrix, scale, point):
    point.append(1)
    res_point = [0, 0, 0, 0]
    for i in range(4):
        for j in range(4):
            res_point[i] += point[j] * matrix[j][i]
    for i in range(3):
        res_point[i] *= scale
    res_point[0] += canvas.width / 2
    res_point[1] += canvas.height / 2
    return res_point[:3]


def draw_horizon(canvas, func, matrix, scale, up_hor, low_hor, start, end, step, z):
    def f(x):
        return func(x, z)

    prev = None
    for x in arange(start, end + step, step):
        cur = trans_point(canvas, matrix, scale, [x, f(x), z])
        if prev:
            predraw_horizon(canvas, prev, cur, up_hor, low_hor)
        prev = cur


def float_horizon(canvas, func, matrix, x_args, z_args, scale):
    up_hor = [0 for i in range(canvas.width)]
    low_hor = [canvas.height for i in range(canvas.width)]
    x_from, x_to, x_step = x_args
    z_from, z_to, z_step = z_args

    for z in arange(z_from, z_to + z_step, z_step):
        draw_horizon(canvas, func, matrix, scale, up_hor, low_hor, x_from, x_to, x_step, z)

    for z in arange(z_from, z_to, z_step):
        fp = trans_point(canvas, matrix, scale, [x_from, func(x_from, z), z])[:2]
        sp = trans_point(canvas, matrix, scale, [x_from, func(x_from, z + z_step), z + z_step])[:2]
        canvas.draw_line(fp, sp)
        fp = trans_point(canvas, matrix, scale, [x_to, func(x_to, z), z])[:2]
        sp = trans_point(canvas, matrix, scale,[x_to, func(x_to, z + z_step), z + z_step])[:2]
        canvas.draw_line(fp, sp)
