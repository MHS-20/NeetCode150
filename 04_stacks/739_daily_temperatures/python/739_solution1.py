class Solution:
    def dailyTemperatures(self, temps: list[int]) -> list[int]:
        res = [0] * len(temps)
        st = []  # indices with no warmer day yet

        for i, t in enumerate(temps):
            while st and t > temps[st[-1]]:
                j = st.pop()
                res[j] = i - j
            st.append(i)
        return res
