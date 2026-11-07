struct Solution;

impl Solution {
    fn search(nums: Vec<i32>, target: i32) -> i32 {
        let mut left = 0i32;
        let mut right = nums.len() as i32 - 1;

        while left <= right {
            let mid = left + (right - left) / 2;
            let (l, m) = (left as usize, mid as usize);

            if nums[m] == target {
                return mid;
            }

            if nums[m] >= nums[l] {
                if target < nums[m] && target >= nums[l] {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                let r = right as usize;
                if target <= nums[r] && target > nums[m] {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        -1
    }
}
