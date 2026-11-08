from collections import Counter
from typing import List


class DetectSquares:
    def __init__(self):
        self.cnt = Counter()

    def add(self, point: List[int]) -> None:
        self.cnt[tuple(point)] += 1

    def count(self, point: List[int]) -> int:
        x, y = point
        res = 0

        for (px, py), c in self.cnt.items():
            if px == x or abs(px - x) != abs(py - y):
                continue  # must be a diagonal corner with side length > 0
            res += c * self.cnt[(x, py)] * self.cnt[(px, y)]
        return res
