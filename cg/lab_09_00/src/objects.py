class Polygon:
    def __init__(self):
        self.points = []
        self.closed = True

    def add(self, point: tuple[int, int]) -> None:
        if point not in self.points:
            self.points.append(point)

    def clear(self) -> None:
        self.points = []

    def is_valid(self) -> bool:
        return len(self.points) > 2

    def open(self) -> None:
        self.closed = False

    def close(self) -> None:
        self.closed = True

    def is_closed(self) -> bool:
        return self.closed


class Clipper(Polygon):
    @staticmethod
    def get_vector(p1: tuple[int, int], p2: tuple[int, int]) -> tuple[int, int]:
        x1, y1 = p1
        x2, y2 = p2
        return x2 - x1, y2 - y1

    @staticmethod
    def vector_prod(v1: tuple[int, int], v2: tuple[int, int]) -> int:
        x1, y1 = v1
        x2, y2 = v2
        return x1 * y2 - y1 * x2

    @staticmethod
    def sign(x: int) -> int:
        if x > 0:
            return 1
        elif x < 0:
            return -1
        else:
            return 0

    def is_convex(self) -> bool:
        sign = None
        for i in range(len(self.points)):
            v1 = self.get_vector(self.points[i - 2], self.points[i - 1])
            v2 = self.get_vector(self.points[i - 1], self.points[i])
            sign_t = self.sign(self.vector_prod(v1, v2))
            if sign_t == 0:
                continue
            elif sign is None:
                sign = sign_t
            elif sign_t != sign:
                return False
        return sign is not None

    def is_valid(self) -> bool:
        return len(self.points) > 2 and self.is_convex()
