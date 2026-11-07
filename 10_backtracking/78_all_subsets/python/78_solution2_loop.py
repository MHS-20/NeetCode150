from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        cur: List[int] = []

        def backtrack(start: int) -> None:
            result.append(cur[:])  # every path is a valid subset

            for i in range(start, len(nums)):
                cur.append(nums[i])
                backtrack(i + 1)
                cur.pop()  # undo

        backtrack(0)
        return result
