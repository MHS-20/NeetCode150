from typing import List


class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        st = []

        for n in arr:
            if not st or n > st[-1]:
                st.append(n)
            else:
                mx = st.pop()
                while st and n <= st[-1]:
                    st.pop()
                st.append(mx)

        return len(st)
