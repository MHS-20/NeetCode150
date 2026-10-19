class MedianFinder:
    def __init__(self):
        self.cnt = [0] * 101
        self.below = 0  # numbers < 0
        self.above = 0  # numbers > 100
        self.total = 0

    def _kth(self, k: int) -> int:
        seen = self.below  # outliers below the range come first in sorted order
        for v in range(101):
            seen += self.cnt[v]
            if seen >= k:
                return v
        return -1

    def addNum(self, num: int) -> None:
        if num < 0:
            self.below += 1
        elif num > 100:
            self.above += 1
        else:
            self.cnt[num] += 1
        self.total += 1

    def findMedian(self) -> float:
        a = self._kth((self.total + 1) // 2)
        b = self._kth(self.total // 2 + 1)
        return (a + b) / 2
