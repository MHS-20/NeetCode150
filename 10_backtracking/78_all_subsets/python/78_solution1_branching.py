from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        cur: List[int] = []

        def backtrack(idx: int) -> None:
            if idx == len(nums):
                result.append(cur[:])
                return
            # include nums[idx]
            cur.append(nums[idx])
            backtrack(idx + 1)
            cur.pop()  # undo

            # skip nums[idx]
            backtrack(idx + 1)

        backtrack(0)
        return result
