class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        # Always binary search on the smaller array
        if len(nums1) > len(nums2):
            return self.findMedianSortedArrays(nums2, nums1)

        n, m = len(nums1), len(nums2)
        left, right = 0, n  # number of elements taken from nums1 into left half
        total = n + m
        halfLeft = (total + 1) // 2  # size of left half (handles odd/even uniformly)

        while left <= right:
            i = left + (right - left) // 2  # elements taken from nums1
            j = halfLeft - i  # elements taken from nums2

            # Sentinels for out-of-range boundaries
            nums1Left = float("-inf") if i == 0 else nums1[i - 1]
            nums1Right = float("inf") if i == n else nums1[i]
            nums2Left = float("-inf") if j == 0 else nums2[j - 1]
            nums2Right = float("inf") if j == m else nums2[j]

            if nums1Left <= nums2Right and nums2Left <= nums1Right:
                # Valid partition found
                if total % 2 == 1:
                    return float(max(nums1Left, nums2Left))
                else:
                    a = max(nums1Left, nums2Left)
                    b = min(nums1Right, nums2Right)
                    return (a + b) / 2.0
            elif nums1Left > nums2Right:
                right = i - 1  # too many from nums1, shrink
            else:
                left = i + 1  # too few from nums1, grow

        return 0.0  # unreachable if inputs are valid sorted arrays
