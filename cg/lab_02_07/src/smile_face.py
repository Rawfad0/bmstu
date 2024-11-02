figure = {
    "triangles": [],
    "circles": [],
    "lines": []
}


def init_figure():
    figure["triangles"].clear()
    figure["circles"].clear()
    figure["lines"].clear()
    # полигоны
    figure["triangles"].append([[-5, -4], [0, 5], [5, -4]])         # нос
    figure["triangles"].append([[-10, -5], [0, -10], [10, -5]])     # рот
    # эллипсы
    figure["circles"].append([[0, 0], [15, 0], [0, 15]])            # голова
    figure["circles"].append([[-5, 5], [-9, 5], [-5, 7]])           # левый глаз
    figure["circles"].append([[5, 5], [9, 5], [5, 7]])              # правый глаз
    # отрезки
    figure["lines"].append([[0, 15], [-10, 10]])
    figure["lines"].append([[0, 15], [-5, 10]])
    figure["lines"].append([[0, 15], [0, 10]])
    figure["lines"].append([[0, 15], [5, 10]])
    figure["lines"].append([[0, 15], [10, 10]])
