struct Solution;

impl Solution {
    pub fn find_duplicate(nums: Vec<i32>) -> i32 {
        let (mut left, mut right) = (1, nums.len() as i32 - 1); // right = n

        while left < right {
            let mid = left + (right - left) / 2;

            // count how many numbers are <= mid
            let count = nums.iter().filter(|&&x| x <= mid).count() as i32;

            if count > mid {
                right = mid; // duplicate is in [left, mid]
            } else {
                left = mid + 1; // duplicate is in [mid + 1, right]
            }
        }

        left
    }
}
