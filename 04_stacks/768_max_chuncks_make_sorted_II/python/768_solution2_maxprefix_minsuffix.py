from typing import List


class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        n = len(arr)
        suf_min = [float("inf")] * (n + 1)
        for i in range(n - 1, -1, -1):
            suf_min[i] = min(suf_min[i + 1], arr[i])

        chunks, pref_max = 0, float("-inf")
        for i in range(n):
            pref_max = max(pref_max, arr[i])
            if pref_max <= suf_min[i + 1]:
                chunks += 1  # valid cut after i (i = n-1 always counts)
        return chunks
