import heapq


class MedianFinder:
    def __init__(self):
        self.max_heap: list[int] = []  # left half, negated
        self.min_heap: list[int] = []  # right half

    def addNum(self, num: int) -> None:
        if self.min_heap and num >= self.min_heap[0]:
            heapq.heappush(self.min_heap, num)
        else:
            heapq.heappush(self.max_heap, -num)

        if len(self.max_heap) > len(self.min_heap) + 1:
            heapq.heappush(self.min_heap, -heapq.heappop(self.max_heap))

        if len(self.min_heap) > len(self.max_heap):
            heapq.heappush(self.max_heap, -heapq.heappop(self.min_heap))

    def findMedian(self) -> float:
        if (len(self.min_heap) + len(self.max_heap)) % 2 == 0:
            return (self.min_heap[0] - self.max_heap[0]) / 2
        return -self.max_heap[0]
