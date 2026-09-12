import heapq
from collections import Counter


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        freq = Counter(nums)
        maxHeap = [(-cnt, val) for val, cnt in freq.items()]
        heapq.heapify(maxHeap)

        res = []
        for _ in range(k):
            _, val = heapq.heappop(maxHeap)
            res.append(val)
        return res
