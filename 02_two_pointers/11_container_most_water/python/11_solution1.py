class Solution:
    def maxArea(self, height: list[int]) -> int:
        left, right, mx = 0, len(height) - 1, 0

        while left < right:
            width = right - left
            h = min(height[left], height[right])
            mx = max(mx, h * width)

            if height[left] > height[right]:
                right -= 1
            else:
                left += 1

        return mx
