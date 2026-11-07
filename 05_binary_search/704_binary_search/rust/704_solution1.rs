struct Solution;

impl Solution {
    fn search(nums: Vec<i32>, target: i32) -> i32 {
        let (mut left, mut right) = (0i32, nums.len() as i32 - 1);

        while left <= right {
            let mid = left + (right - left) / 2;
            let val = nums[mid as usize];
            if val == target {
                return mid;
            }
            if val > target {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        -1
    }
}
