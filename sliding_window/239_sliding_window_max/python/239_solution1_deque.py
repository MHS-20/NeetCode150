from collections import deque


class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        maxs = []
        dq = deque()  # indices, values decreasing

        # i is the right pointer
        # i - k + 1 is the left pointer
        for i, n in enumerate(nums):
            if dq and dq[0] < i - k + 1:
                dq.popleft()

            while dq and n > nums[dq[-1]]:
                dq.pop()
            dq.append(i)

            if i >= k - 1:
                maxs.append(nums[dq[0]])

        return maxs
