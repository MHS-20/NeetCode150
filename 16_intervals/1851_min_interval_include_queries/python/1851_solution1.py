import heapq
from typing import List


class Solution:
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:
        result = [0] * len(queries)
        min_heap = []  # (size, end)

        intervals.sort()
        idx = sorted(range(len(queries)), key=lambda k: queries[k])

        i, n = 0, len(intervals)
        for j in idx:
            q = queries[j]

            while i < n and intervals[i][0] <= q:
                left, right = intervals[i]
                heapq.heappush(min_heap, (right - left + 1, right))
                i += 1

            while min_heap and min_heap[0][1] < q:
                heapq.heappop(min_heap)

            result[j] = min_heap[0][0] if min_heap else -1

        return result
