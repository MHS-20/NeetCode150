struct Solution;

impl Solution {
    fn find_median_sorted_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {
        // Always binary search on the smaller array
        if nums1.len() > nums2.len() {
            return Solution::find_median_sorted_arrays(nums2, nums1);
        }

        let (n, m) = (nums1.len() as i32, nums2.len() as i32);
        let (mut left, mut right) = (0, n); // number of elements taken from nums1 into left half
        let total = n + m;
        let half_left = (total + 1) / 2; // size of left half (handles odd/even uniformly)

        while left <= right {
            let i = left + (right - left) / 2; // elements taken from nums1
            let j = half_left - i; // elements taken from nums2

            // Sentinels for out-of-range boundaries
            let nums1_left = if i == 0 { i32::MIN } else { nums1[(i - 1) as usize] };
            let nums1_right = if i == n { i32::MAX } else { nums1[i as usize] };
            let nums2_left = if j == 0 { i32::MIN } else { nums2[(j - 1) as usize] };
            let nums2_right = if j == m { i32::MAX } else { nums2[j as usize] };

            if nums1_left <= nums2_right && nums2_left <= nums1_right {
                // Valid partition found
                if total % 2 == 1 {
                    return nums1_left.max(nums2_left) as f64;
                } else {
                    let a = nums1_left.max(nums2_left);
                    let b = nums1_right.min(nums2_right);
                    return (a as f64 + b as f64) / 2.0;
                }
            } else if nums1_left > nums2_right {
                right = i - 1; // too many from nums1, shrink
            } else {
                left = i + 1; // too few from nums1, grow
            }
        }

        0.0 // unreachable if inputs are valid sorted arrays
    }
}
