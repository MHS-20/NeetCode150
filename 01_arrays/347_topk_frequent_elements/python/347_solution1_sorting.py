from collections import Counter


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        freq = Counter(nums)
        items = sorted(freq.items(), key=lambda item: item[1], reverse=True)

        return [val for val, _ in items[:k]]
