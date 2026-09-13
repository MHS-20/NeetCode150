class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        n = len(nums)
        prefixes = [1] * n
        suffixes = [1] * n
        ans = [1] * n

        for i in range(1, n):
            prefixes[i] = prefixes[i - 1] * nums[i - 1]

        for i in range(n - 2, -1, -1):
            suffixes[i] = suffixes[i + 1] * nums[i + 1]

        for i in range(n):
            ans[i] = prefixes[i] * suffixes[i]

        return ans
