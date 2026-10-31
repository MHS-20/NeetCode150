from typing import List


class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        st = []

        for n in arr:
            if not st or n >= st[-1]:
                st.append(n)
            else:
                mx = st.pop()
                while st and n < st[-1]:
                    st.pop()
                st.append(mx)

        return len(st)

# ---- Alternative Compact Version ----
# class Solution:
#     def maxChunksToSorted(self, arr: List[int]) -> int:
#         st = []  # max of each chunk, non-decreasing
#         for x in arr:
#             cur_max = x
#             while st and st[-1] > x:
#                 cur_max = max(cur_max, st.pop())
#             st.append(cur_max)
#         return len(st)
