import heapq
from typing import List


class KthLargest:
    def __init__(self, k: int, nums: List[int]):
        self.cap = k
        self.pq = nums
        heapq.heapify(self.pq)
        while len(self.pq) > k:
            heapq.heappop(self.pq)

    def add(self, val: int) -> int:
        heapq.heappush(self.pq, val)
        if len(self.pq) > self.cap:
            heapq.heappop(self.pq)
        return self.pq[0]
