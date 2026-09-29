class Solution {
  findMedianSortedArrays(nums1, nums2) {
    // Always binary search on the smaller array
    if (nums1.length > nums2.length) return this.findMedianSortedArrays(nums2, nums1);

    const n = nums1.length, m = nums2.length;
    let left = 0, right = n; // number of elements taken from nums1 into left half
    const total = n + m;
    const halfLeft = Math.floor((total + 1) / 2); // size of left half (handles odd/even uniformly)

    while (left <= right) {
      const i = left + Math.floor((right - left) / 2); // elements taken from nums1
      const j = halfLeft - i; // elements taken from nums2

      // Sentinels for out-of-range boundaries
      const nums1Left = i === 0 ? -Infinity : nums1[i - 1];
      const nums1Right = i === n ? Infinity : nums1[i];
      const nums2Left = j === 0 ? -Infinity : nums2[j - 1];
      const nums2Right = j === m ? Infinity : nums2[j];

      if (nums1Left <= nums2Right && nums2Left <= nums1Right) {
        // Valid partition found
        if (total % 2 === 1) {
          return Math.max(nums1Left, nums2Left);
        } else {
          const a = Math.max(nums1Left, nums2Left);
          const b = Math.min(nums1Right, nums2Right);
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
}
