class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:
        tracker = set()

        for x in nums:
            if x in tracker:
                return True
            tracker.add(x)

        return False
