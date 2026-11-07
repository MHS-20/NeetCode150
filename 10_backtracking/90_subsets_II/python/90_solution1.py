from typing import List


class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        cur: List[int] = []
        nums.sort()

        def backtrack(idx: int) -> None:
            if idx == len(nums):
                result.append(cur[:])
                return

            cur.append(nums[idx])
            backtrack(idx + 1)
            cur.pop()

            i = idx + 1
            while i < len(nums) and nums[idx] == nums[i]:
                i += 1

            backtrack(i)

        backtrack(0)
        return result
