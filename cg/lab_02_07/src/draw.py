from math import (
    sin,
    cos,
    pi,
)


def draw_line(plot, pa, pb):
    plot.set_xdata([pa[0], pb[0]])
    plot.set_ydata([pa[1], pb[1]])


def draw_polygon(plot, points):
    obj_points = points
    obj_points.append(obj_points[0])
    plot.set_xdata([p[0] for p in obj_points])
    plot.set_ydata([p[1] for p in obj_points])
    obj_points.__delitem__(-1)


def draw_ellipse(plot, pa, pb, pc):
    n = 100
    obj_points = []
    for i in range(n):
        x = pa[0] + (pb[0] - pa[0]) * cos(2 * pi * (i / n)) + (pc[0] - pa[0]) * sin(2 * pi * (i / n))
        y = pa[1] + (pb[1] - pa[1]) * cos(2 * pi * (i / n)) + (pc[1] - pa[1]) * sin(2 * pi * (i / n))
        obj_points.append([x, y])
    draw_polygon(plot, obj_points)
