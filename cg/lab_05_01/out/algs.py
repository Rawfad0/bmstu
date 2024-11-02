import time


class Node:
    def __init__(self, x=0, dx=0, dy=0):
        self.x = x
        self.dx = dx
        self.dy = dy


def update_y_group(y_groups, point_beg: list[int, int], point_end: [int, int]):
    xb, yb = point_beg
    xe, ye = point_end
    if yb > ye:
        xb, yb, xe, ye = xe, ye, xb, yb
    dy = abs(ye - yb)
    if dy != 0:
        x_step = (xb - xe) / dy
        if ye not in y_groups:
            y_groups[ye] = [Node(xe, x_step, dy)]
        else:
            y_groups[ye].append(Node(xe, x_step, dy))


def iter_active_edges(active_edges):
    i = 0
    while i < len(active_edges):
        active_edges[i].x += active_edges[i].dx
        active_edges[i].dy -= 1
        if active_edges[i].dy < 1:
            active_edges.pop(i)
        else:
            i += 1


def add_active_edges(y_groups, active_edges, y):
    if y in y_groups:
        for y_group in y_groups.get(y):
            active_edges.append(y_group)
    active_edges.sort(key=lambda edge: edge.x)


def draw_act(canvas, active_edges, y):
    for i in range(0, len(active_edges), 2):
        point_beg, point_end = (round(active_edges[i].x), y), (round(active_edges[i + 1].x), y)
        canvas.draw_line(point_beg, point_end)


def alg_with_ordered_edges_list(canvas, polygon: list[tuple[int, int]], event, delay: int = 0):
    edges = [[polygon[i], polygon[i + 1]] for i in range(len(polygon) - 1)]
    ys = [y for x, y in polygon]
    y_min, y_max = min(ys), max(ys)
    y_groups = {i: list() for i in range(y_max, y_min, -1)}
    for edge in edges:
        point_beg, point_end = edge
        update_y_group(y_groups, point_beg, point_end)
    yb, ye = y_min, y_max
    active_edges = []
    while ye > yb:
        iter_active_edges(active_edges)
        add_active_edges(y_groups, active_edges, ye)
        if delay:
            event()
            time.sleep(delay / 1000)
        draw_act(canvas, active_edges, ye)
        ye -= 1
