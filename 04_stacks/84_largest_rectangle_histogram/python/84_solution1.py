class Solution:
    def largestRectangleArea(self, heights: list[int]) -> int:
        n = len(heights)
        st = []  # indices of increasing heights
        best = 0

        for i in range(n + 1):
            h = heights[i] if i < n else 0  # sentinel flushes the stack
            while st and heights[st[-1]] > h:
                height = heights[st.pop()]
                prev = st[-1] if st else -1
                best = max(best, height * (i - prev - 1))
            st.append(i)
        return best
