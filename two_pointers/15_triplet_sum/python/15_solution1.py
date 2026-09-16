class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        nums.sort()
        result = []

        for idx in range(len(nums)):
            if idx > 0 and nums[idx] == nums[idx - 1]:
                continue

            left, right = idx + 1, len(nums) - 1

            while left < right:
                total = nums[idx] + nums[left] + nums[right]

                if total == 0:
                    result.append([nums[idx], nums[left], nums[right]])
                    left += 1
                    right -= 1
                    while left < right and nums[left] == nums[left - 1]:
                        left += 1
                    while left < right and nums[right] == nums[right + 1]:
                        right -= 1
                elif total > 0:
                    right -= 1
                else:
                    left += 1

        return result
