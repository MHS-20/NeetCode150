import heapq
from typing import List

"""
Definition of Interval:
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end
"""


class Solution:
    def minMeetingRooms(self, intervals: List[Interval]) -> int:
        mx = 0
        min_heap = []  # end times of the meetings still running

        intervals.sort(key=lambda i: i.start)

        for i in intervals:
            while min_heap and min_heap[0] <= i.start:
                heapq.heappop(min_heap)
            heapq.heappush(min_heap, i.end)
            mx = max(mx, len(min_heap))

        return mx
