class Figure:
    def __init__(self):
        self.points = []

    def add(self, point: tuple[int, int]) -> None:
        self.points.append(point)

    def clear(self) -> None:
        self.points = []


class SeedPoint:
    def __init__(self, x=None, y=None):
        self.x = x
        self.y = y

    def is_valid(self) -> bool:
        return self.x is not None and self.y is not None

    def set(self, point: tuple[int, int]) -> None:
        self.x, self.y = point

    def get(self) -> tuple[int, int]:
        return self.x, self.y
