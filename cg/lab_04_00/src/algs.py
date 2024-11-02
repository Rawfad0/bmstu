from math import sqrt, pi, sin, cos


def get_symmetrical_points(center_point: tuple[int, int], point: tuple[int, int], mode: str = "ellipse"):
    cx, cy = center_point
    dx, dy = point
    points = [(cx + dx, cy + dy), (cx - dx, cy + dy), (cx + dx, cy - dy), (cx - dx, cy - dy)]
    if mode == "circle":
        points.extend([(cx + dy, cy + dx), (cx - dy, cy + dx), (cx + dy, cy - dx), (cx - dy, cy - dx)])
    return points


def standard_circle(canvas, center_point: tuple[int, int], radius: int, color: tuple[int, int, int]):
    sqr_r = radius**2
    points = []
    sector_45 = round(radius / sqrt(2))
    for dx in range(sector_45 + 1):
        dy = round(sqrt(sqr_r - dx**2))
        points.extend(get_symmetrical_points(center_point, (dx, dy), "circle"))
    canvas.draw_points(points, color)


def standard_ellipse(canvas, center_point: tuple[int, int], radius: tuple[int, int], color: (int, int, int)):
    a, b = radius
    sqr_a = a**2
    sqr_b = b**2
    points = []
    for dx in range(a + 1):
        dy = round(sqrt(sqr_a * sqr_b - dx**2 * sqr_b) / a)
        points.extend(get_symmetrical_points(center_point, (dx, dy)))
    for dy in range(b + 1):
        dx = round(sqrt(sqr_a * sqr_b - dy**2 * sqr_a) / b)
        points.extend(get_symmetrical_points(center_point, (dx, dy)))
    canvas.draw_points(points, color)


def parametric_circle(canvas, center_point: tuple[int, int], radius: int, color: (int, int, int)):
    step = 1 / radius
    points = []
    i = 0
    while i <= pi / 4 + step:
        dx = round(radius * cos(i))
        dy = round(radius * sin(i))
        points.extend(get_symmetrical_points(center_point, (dx, dy)))
        i += step
    canvas.draw_points(points, color)


def parametric_ellipse(canvas, center_point: tuple[int, int], radius: tuple[int, int], color: (int, int, int)):
    a, b = radius
    step = 1 / a if a > b else 1 / b
    points = []
    i = 0
    while i <= pi / 2 + step:
        dx = round(a * cos(i))
        dy = round(b * sin(i))
        points.extend(get_symmetrical_points(center_point, (dx, dy)))
        i += step
    canvas.draw_points(points, color)


def bresenham_circle(canvas, center_point: tuple[int, int], radius: int, color: (int, int, int)):
    x = 0
    y = radius
    delta = 2 * (1 - radius)

    points = []
    points.extend(get_symmetrical_points(center_point, (x, y), "circle"))
    while x < y:
        d = 2 * (delta + y) - 1
        x += 1
        if d >= 0:
            y -= 1
            delta += 2 * (x - y + 1)
        else:
            delta += x + x + 1
        points.extend(get_symmetrical_points(center_point, (x, y), "circle"))
    canvas.draw_points(points, color)


def bresenham_ellipse(canvas, center_point: tuple[int, int], radius: tuple[int, int], color: (int, int, int)):
    a, b = radius
    x, y = 0, b
    sqr_a = a**2
    sqr_b = b**2
    delta = sqr_b - sqr_a * (2*b + 1)

    points = []
    points.extend(get_symmetrical_points(center_point, (x, y)))
    while y >= 0:
        if delta <= 0:
            d = 2 * delta + sqr_a * (2 * y + 2)
            x += 1
            delta += sqr_b * (2 * x + 1)
            if d >= 0:
                y -= 1
                delta += sqr_a * (-2 * y + 1)
        else:
            d = 2 * delta + sqr_b * (-2 * x + 2)
            y -= 1
            delta += sqr_a * (-2 * y + 1)
            if d <= 0:
                x += 1
                delta += sqr_b * (2 * x + 1)
        points.extend(get_symmetrical_points(center_point, (x, y)))
    canvas.draw_points(points, color)
