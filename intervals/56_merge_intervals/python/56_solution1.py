from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        result = []

        for cur in intervals:
            if not result or result[-1][1] < cur[0]:
                result.append(cur)
            else:
                result[-1][1] = max(result[-1][1], cur[1])

        return result
