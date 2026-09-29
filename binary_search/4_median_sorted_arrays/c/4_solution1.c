#include <limits.h>

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    // Always binary search on the smaller array
    if (nums1Size > nums2Size)
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);

    int n = nums1Size, m = nums2Size;
    int left = 0, right = n; // number of elements taken from nums1 into left half
    int total = n + m;
    int halfLeft = (total + 1) / 2; // size of left half (handles odd/even uniformly)

    while (left <= right) {
        int i = left + (right - left) / 2; // elements taken from nums1
        int j = halfLeft - i;              // elements taken from nums2

        // Sentinels for out-of-range boundaries
        int nums1Left = (i == 0) ? INT_MIN : nums1[i - 1];
        int nums1Right = (i == n) ? INT_MAX : nums1[i];
        int nums2Left = (j == 0) ? INT_MIN : nums2[j - 1];
        int nums2Right = (j == m) ? INT_MAX : nums2[j];

        if (nums1Left <= nums2Right && nums2Left <= nums1Right) {
            // Valid partition found
            if (total % 2 == 1) {
                return (double)(nums1Left > nums2Left ? nums1Left : nums2Left);
            } else {
                int a = nums1Left > nums2Left ? nums1Left : nums2Left;
                int b = nums1Right < nums2Right ? nums1Right : nums2Right;
                return (a + b) / 2.0;
            }
        } else if (nums1Left > nums2Right) {
            right = i - 1; // too many from nums1, shrink
        } else {
            left = i + 1; // too few from nums1, grow
        }
    }

    return 0.0; // unreachable if inputs are valid sorted arrays
}
