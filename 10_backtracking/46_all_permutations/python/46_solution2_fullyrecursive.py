from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []

        def backtrack(idx: int, i: int) -> None:
            if idx == len(nums):
                result.append(nums[:])
                return
            if i == len(nums):
                return

            # choose nums[i] for position idx, then fix the next position
            nums[idx], nums[i] = nums[i], nums[idx]
            backtrack(idx + 1, idx + 1)
            nums[idx], nums[i] = nums[i], nums[idx]  # undo

            # try the next candidate for the same position
            backtrack(idx, i + 1)

        backtrack(0, 0)
        return result
