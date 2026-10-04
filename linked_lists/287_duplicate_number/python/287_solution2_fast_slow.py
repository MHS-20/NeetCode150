from typing import List


class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow = fast = 0

        # Phase 1: find a meeting point inside the cycle
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break

        # Phase 2: find the cycle entrance (the duplicate)
        slow = 0
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]

        return slow
