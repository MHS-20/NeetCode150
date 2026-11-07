class Solution:
    def trap(self, height: list[int]) -> int:
        stack = []
        total = 0

        for i, h in enumerate(height):
            while stack and h > height[stack[-1]]:
                bottom = stack.pop()

                if not stack:
                    break

                left = stack[-1]
                width = i - left - 1
                depth = min(height[left], h) - height[bottom]
                total += width * depth

            stack.append(i)

        return total
