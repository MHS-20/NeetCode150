from typing import List


class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        st = []  # max of each chunk, non-decreasing
        for x in arr:
            cur_max = x
            while st and st[-1] > x:
                cur_max = max(cur_max, st.pop())
            st.append(cur_max)
        return len(st)
