import time


def compare_point_color(canvas, point: tuple[int, int]) -> bool:
    point_color = canvas.get_point_color(point)
    return point_color != canvas.border_color and point_color != canvas.fill_color


def fill_right(canvas, x: int, y: int) -> int:
    while x < canvas.width and compare_point_color(canvas, (x, y)):
        canvas.draw_fill_point((x, y))
        x += 1
    return x - 1


def fill_left(canvas, x: int, y: int) -> int:
    while x >= 0 and compare_point_color(canvas, (x, y)):
        canvas.draw_fill_point((x, y))
        x -= 1
    return x + 1


def find_upper_gaps(canvas, stack: list[tuple[int, int]], x_r: int, x: int, y: int):
    while x <= x_r:
        x_tmp = x
        while x <= x_r and compare_point_color(canvas, (x, y)):
            x += 1
        # Правый пиксель в стек
        if x != x_tmp and y >= 0:
            if x == x_r and compare_point_color(canvas, (x, y)):
                stack.append((x, y))
            else:
                stack.append((x - 1, y))
        # Пропуск границ до следующего отрезка
        x_tmp = x
        while x < x_r and not compare_point_color(canvas, (x, y)):
            x += 1
        if x == x_tmp:
            x += 1


def find_lower_gaps(canvas, stack: list[tuple[int, int]], x_r: int, x: int, y: int):
    while x <= x_r:
        x_tmp = x
        while x <= x_r and compare_point_color(canvas, (x, y)):
            x += 1
        # Правый пиксель в стек
        if x != x_tmp and y < canvas.height:
            if x == x_r and compare_point_color(canvas, (x, y)):
                stack.append((x, y))
            else:
                stack.append((x - 1, y))
        # Пропуск границ до следующего отрезка
        x_tmp = x
        while x < x_r and not compare_point_color(canvas, (x, y)):
            x += 1
        if x == x_tmp:
            x += 1


def filling_with_seed_point(canvas, seed_point: tuple[int, int], event, delay: int = 0):
    tb = time.time()
    counter = 0
    width, height = canvas.width, canvas.height
    stack = [seed_point]
    while stack:
        seed_pixel = stack.pop()
        x, y = seed_pixel
        canvas.draw_fill_point((x, y))
        x_r = fill_right(canvas, x + 1, y)                      # Закраска вправо
        x_l = fill_left(canvas, x - 1, y)                       # Закраска влево
        find_upper_gaps(canvas, stack, x_r, x_l, y - 1)         # Верхняя строка
        if y < height:
            find_lower_gaps(canvas, stack, x_r, x_l, y + 1)     # Нижняя строка
        if delay:
            event()
            time.sleep(delay / 1000)
            counter += 1
    return time.time() - tb - delay * counter / 1000
