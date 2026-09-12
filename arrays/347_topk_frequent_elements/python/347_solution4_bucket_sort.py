from collections import Counter


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        freq = Counter(nums)
        buckets = [[] for _ in range(len(nums) + 1)]

        for val, cnt in freq.items():
            buckets[cnt].append(val)

        res = []
        for i in range(len(buckets) - 1, -1, -1):
            for val in buckets[i]:
                res.append(val)
                if len(res) == k:
                    return res

        return res
