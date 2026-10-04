from typing import List


class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        left, right = 1, len(nums) - 1  # right = n

        while left < right:
            mid = left + (right - left) // 2

            # count how many numbers are <= mid
            count = sum(1 for x in nums if x <= mid)

            if count > mid:
                right = mid  # duplicate is in [left, mid]
            else:
                left = mid + 1  # duplicate is in [mid + 1, right]

        return left
