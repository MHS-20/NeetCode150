class MedianFinder:
    def __init__(self):
        self.cnt = [0] * 101
        self.total = 0

    def _kth(self, k: int) -> int:  # k-th smallest, 1-indexed
        seen = 0
        for v in range(101):
            seen += self.cnt[v]
            if seen >= k:
                return v
        return -1  # unreachable if 1 <= k <= total

    def addNum(self, num: int) -> None:
        self.cnt[num] += 1
        self.total += 1

    def findMedian(self) -> float:
        a = self._kth((self.total + 1) // 2)
        b = self._kth(self.total // 2 + 1)
        return (a + b) / 2
