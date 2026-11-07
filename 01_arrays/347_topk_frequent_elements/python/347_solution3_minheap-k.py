import heapq
from collections import Counter


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        freq = Counter(nums)
        minHeap = []

        for val, cnt in freq.items():
            heapq.heappush(minHeap, (cnt, val))
            if len(minHeap) > k:
                heapq.heappop(minHeap)

        return [val for _, val in minHeap]
