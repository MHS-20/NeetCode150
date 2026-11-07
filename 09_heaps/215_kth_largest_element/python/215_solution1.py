import heapq
from typing import List


class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        pq: List[int] = []
        for x in nums:
            if len(pq) < k:
                heapq.heappush(pq, x)
            elif x > pq[0]:
                heapq.heapreplace(pq, x)
        return pq[0]
