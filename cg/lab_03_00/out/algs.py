from math import floor, fabs


def dda(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
    x1, y1 = point_begin
    x2, y2 = point_end
    dx, dy = x2 - x1, y2 - y1
    x, y = x1, y1
    if dx == 0 and dy == 0:
        canvas.draw_point((x, y), 1, color)
        return
    l = abs(dx) if abs(dx) >= abs(dy) else abs(dy)
    dx, dy = dx/l, dy/l
    points = []
    steps = 0
    for i in range(1, l + 1):
        x += dx
        y += dy
        points.append(((int(x), int(y)), 1.0))
        if mode == "step" and round(x - dx) != round(x) and round(y - dy) != round(y):
            steps += 1
    if mode == "draw" or mode == "time":
        canvas.draw_points(points, color)
    if mode == "step":
        return steps


def bresenham_float(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
    x1, y1 = point_begin
    x2, y2 = point_end
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 and dy == 0:
        canvas.draw_point((x1, y1), 1, color)
        return
    sign_x = 1 if dx > 0 else -1 if dx < 0 else 0
    sign_y = 1 if dy > 0 else -1 if dy < 0 else 0
    if dx < 0:
        dx = -dx
    if dy < 0:
        dy = -dy
    if dx < dy:
        dx, dy = dy, dx
        exchange = 1
    else:
        exchange = 0
    e = dy / dx - 0.5
    x, y = x1, y1
    x_buf, y_buf = x, y
    points = []
    steps = 0
    for i in range(dx):
        points.append(((x, y), 1.0))
        if e >= 0:
            if exchange:
                x += sign_x
            else:
                y += sign_y
            e -= 1
        if exchange:
            y += sign_y
        else:
            x += sign_x
        e += dy / dx
        if mode == "step":
            if x_buf != x and y_buf != y:
                steps += 1
            x_buf = x
            y_buf = y
    if mode == "draw" or mode == "time":
        canvas.draw_points(points, color)
    elif mode == "step":
        return steps


def bresenham_int(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
    x1, y1 = point_begin
    x2, y2 = point_end
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 and dy == 0:
        canvas.draw_point((x1, y1), 1, color)
        return
    sign_x = 1 if dx > 0 else -1 if dx < 0 else 0
    sign_y = 1 if dy > 0 else -1 if dy < 0 else 0
    if dx < 0:
        dx = -dx
    if dy < 0:
        dy = -dy
    if dx < dy:
        dx, dy = dy, dx
        exchange = 1
    else:
        exchange = 0
    e = 2*dy - dx
    x, y = x1, y1
    x_buf, y_buf = x, y
    points = []
    steps = 0
    for i in range(dx):
        points.append(((x, y), 1.0))
        if e >= 0:
            if exchange:
                x += sign_x
            else:
                y += sign_y
            e -= 2*dx
        if exchange:
            y += sign_y
        else:
            x += sign_x
        e += 2*dy
        if mode == "step":
            if x_buf != x and y_buf != y:
                steps += 1
            x_buf = x
            y_buf = y
    if mode == "draw" or mode == "time":
        canvas.draw_points(points, color)
    elif mode == "step":
        return steps


def bresenham_antialiasing(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
    x1, y1 = point_begin
    x2, y2 = point_end
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 and dy == 0:
        canvas.draw_point((x1, y1), 1, color)
        return
    sign_x = 1 if dx > 0 else -1 if dx < 0 else 0
    sign_y = 1 if dy > 0 else -1 if dy < 0 else 0
    if dx < 0:
        dx = -dx
    if dy < 0:
        dy = -dy
    if dx < dy:
        dx, dy = dy, dx
        exchange = 1
    else:
        exchange = 0
    m = dy / dx
    w = 1 - m
    e = 0.5
    points = []
    steps = 0
    x, y = x1, y1
    x_buf, y_buf = x, y
    for i in range(dx):
        points.append(((x, y), e))
        if e < w:
            if exchange:
                y += sign_y
            else:
                x += sign_x
            e += m
        else:
            x += sign_x
            y += sign_y
            e -= w
        if mode == "step":
            if x_buf != x and y_buf != y:
                steps += 1
            x_buf = x
            y_buf = y
    points.append(((x, y), e))
    if mode == "draw" or mode == "time":
        canvas.draw_points(points, color)
    elif mode == "step":
        return steps


def wu(canvas, point_begin: (int, int), point_end: (int, int), color: (int, int, int), mode: str = "draw"):
    x1, y1 = point_begin
    x2, y2 = point_end
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 and dy == 0:
        canvas.draw_point((x1, x2), 1, color)
        return
    m = 1
    step = 1
    points = []
    steps = 0
    if abs(dy) >= abs(dx):
        if dy != 0:
            m = dx / dy
        m1 = m
        if y1 > y2:
            m1 *= -1
            step *= -1
        bord = round(y2) - 1 if dy < dx else round(y2) + 1
        for y in range(round(y1), bord, step):
            d1 = x1 - floor(x1)
            d2 = 1 - d1
            points.append(((int(x1) + 1, y), 1 - fabs(d2)))
            points.append(((int(x1), y), 1 - fabs(d1)))
            if mode == "step" and y < round(x2) and int(y1) != int(x1 + m1):
                steps += 1
            x1 += m1
    else:
        if dx != 0:
            m = dy / dx
        m1 = m
        if x1 > x2:
            step *= -1
            m1 *= -1
        bord = round(x2) - 1 if dy > dx else round(x2) + 1
        for x in range(round(x1), bord, step):
            d1 = y1 - floor(y1)
            d2 = 1 - d1
            points.append(((x, int(y1) + 1), 1 - fabs(d2)))
            points.append(((x, int(y1)), 1 - fabs(d1)))
            if mode == "step" and x < round(x2) and int(y1) != int(y1 + m1):
                steps += 1
            y1 += m1
    if mode == "draw" or mode == "time":
        canvas.draw_points(points, color)
    elif mode == "step":
        return steps
