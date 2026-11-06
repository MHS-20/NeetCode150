from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]

        def max_loot(idx: int, start: int) -> int:
            if idx < start:
                return 0
            if memo[idx] != -1:
                return memo[idx]
            memo[idx] = max(
                max_loot(idx - 1, start), max_loot(idx - 2, start) + nums[idx]
            )
            return memo[idx]

        memo = [-1] * n
        skip_last = max_loot(n - 2, 0)

        memo = [-1] * n  # reset: different subproblem
        skip_first = max_loot(n - 1, 1)

        return max(skip_last, skip_first)
