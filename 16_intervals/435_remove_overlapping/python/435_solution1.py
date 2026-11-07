from typing import List


class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        kept = 0
        lastEnd = 0  # end of the last kept interval

        for start, end in intervals:
            if kept == 0 or lastEnd <= start:
                kept += 1
                lastEnd = end
            elif lastEnd > end:
                lastEnd = end  # overlap: keep the one that ends earlier

        return len(intervals) - kept
