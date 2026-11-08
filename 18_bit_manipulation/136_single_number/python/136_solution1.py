from typing import List


class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        xr = 0
        for n in nums:
            xr = xr ^ n
        return xr
