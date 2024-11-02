from math import (
    sin,
    cos,
    radians,
)


def move_point(p: tuple[float, float], dx: float, dy: float) -> tuple[float, float]:
    x, y = p
    return x + dx, y + dy


def rotate_point(p: tuple[float, float], pc: tuple[float, float], angle: float) -> tuple[float, float]:
    x, y = p
    cx, cy = pc
    return cx + (x - cx) * cos(radians(angle)) - (y - cy) * sin(radians(angle)), \
        cy + (x - cx) * sin(radians(angle)) + (y - cy) * cos(radians(angle))


def scale_point(p: tuple[float, float], pc: tuple[float, float], k: tuple[float, float]) -> tuple[float, float]:
    x, y = p
    cx, cy = pc
    kx, ky = k
    return cx + kx * (x - cx), cy + ky * (y - cy)


def move_points(points: list[tuple[float, float]], dx: float, dy: float):
    for i, p in enumerate(points):
        points[i][0], points[i][1] = move_point(p, dx, dy)


def rotate_points(points: list[tuple[float, float]], pc: tuple[float, float], angle: float):
    for i, p in enumerate(points):
        points[i][0], points[i][1] = rotate_point(p, pc, angle)


def scale_points(points: list[tuple[float, float]], pc: tuple[float, float], k: tuple[float, float]):
    for i, p in enumerate(points):
        points[i][0], points[i][1] = scale_point(p, pc, k)
