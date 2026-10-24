from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        result: List[List[int]] = []
        cur = nums[:]

        def backtrack(idx: int) -> None:
            if idx == len(cur):
                result.append(cur[:])
                return

            for i in range(idx, len(cur)):
                cur[idx], cur[i] = cur[i], cur[idx]
                backtrack(idx + 1)
                cur[idx], cur[i] = cur[i], cur[idx]

        backtrack(0)
        return result
