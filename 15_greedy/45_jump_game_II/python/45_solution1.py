from typing import List


class Solution:
    def jump(self, nums: List[int]) -> int:
        end = far = count = 0

        for i in range(len(nums) - 1):
            far = max(far, i + nums[i])
            if i == end:
                # I've used up everything reachable with k jumps,
                # so now I'm entering the area that needs k+1 jumps.
                count += 1
                end = far

        return count
