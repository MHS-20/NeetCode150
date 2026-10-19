import heapq
from typing import List


class KthLargest:
    def __init__(self, k: int, nums: List[int]):
        self.cap = k
        self.pq: List[int] = []
        for n in nums:
            self.add(n)

    def add(self, val: int) -> int:
        if len(self.pq) < self.cap:
            heapq.heappush(self.pq, val)
        elif val > self.pq[0]:
            heapq.heapreplace(self.pq, val)
        return self.pq[0]
