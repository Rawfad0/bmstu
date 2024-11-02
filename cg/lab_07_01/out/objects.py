class LineSegments:
    def __init__(self):
        self.list = []
        self.none_point = (None, None)

    def add_line_segment(self, line_segment: tuple[tuple[int, int], tuple[int, int]]) -> None:
        self.list.append(line_segment)

    def add_point(self, point: tuple[int, int]) -> bool:
        if self.list != [] and self.list[-1][1] == self.none_point:
            self.list[-1] = self.list[-1][0], point
            return True
        else:
            self.list.append((point, self.none_point))
            return False

    def clear(self) -> None:
        self.list = []


class Clipper:
    def __init__(self):
        self.none_point = (None, None)
        self.p1 = self.none_point
        self.p2 = self.none_point

    def set(self, p1: tuple[int, int], p2: tuple[int, int]) -> None:
        x1, y1 = p1
        x2, y2 = p2
        self.p1 = min(x1, x2), min(y1, y2)
        self.p2 = max(x1, x2), max(y1, y2)

    def add_point(self, point: tuple[int, int]) -> bool:
        if self.p1 != self.none_point and self.p2 == self.none_point:
            self.p2 = point
            return True
        else:
            self.p1, self.p2 = point, self.none_point
            return False

    def clear(self) -> None:
        self.p1 = self.none_point
        self.p2 = self.none_point

    def is_valid(self) -> bool:
        return self.p1 is not self.none_point and self.p2 is not self.none_point
