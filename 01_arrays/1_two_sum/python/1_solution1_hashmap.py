class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        seen = {}

        for i, num in enumerate(nums):
            if num in seen:
                return [seen[num], i]
            else:
                seen[target - num] = i

        return []
